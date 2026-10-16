// Specter.Internal — Lua on its own OS thread, in its own Lua universe
// (implementation). The contract is in worker.h; this file is the mechanism.

#include "pch-il2cpp.h"

#include "lua/worker.h"

#include "lua/capi.h"
#include "lua/worker_meta.h"
#include "platform/log.h"
#include "platform/nt.h"

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

// The hidden thread is entered OUTSIDE the loader, so its CRT state is not set
// up. We use _aligned_malloc, vsnprintf and WriteFile below, all of which are
// CRT, so the attach is not optional here.
extern "C" int __cdecl _CRT_INIT(void*, unsigned long, void*);
extern "C" unsigned char __ImageBase;

namespace specter::lua::worker {

// The resolved pointers, not the shim's global lua_* functions.
//
// Everything else in the binding layer calls the shim, and should: that is the
// indirection LuaBridge goes through. This file is the exception because it
// talks to a state that is NOT the game's and never goes through LuaBridge at
// all — it builds a runtime from scratch. Calling p_* directly states that.
using namespace capi;

namespace {

// A thread with its own Lua heap is not free. Six is enough to run the heavy
// things and small enough that a runaway script cannot starve the machine.
constexpr int kMaxWorkers = 6;
constexpr int kMaxCode = 64 * 1024;
constexpr int kMaxMeta = 16 * 1024;
constexpr unsigned kShutdownWaitMs = 2000;

enum Flag : int {
    kFree = 0,     // slot unused
    kStarting = 1, // claimed, thread not entered yet
    kRunning = 2,  // in lua_pcall
    kKillAsked = 3, // cooperative kill requested, waiting for a sleep()
    kDone = 4,     // returned on its own
    kKilled = 5,   // raised at a sleep() because of a kill
    kError = 6,    // raised on its own
};

// Static storage: zero-initialised before any dynamic initialiser runs, which is
// what makes this safe in a manually mapped image. std::atomic has no dynamic
// constructor either, so this whole table is constant-initialised.
struct Slot {
    std::atomic<int> flag;
    HANDLE thread;
    char error[256];
};
Slot g_slots[kMaxWorkers];

CRITICAL_SECTION g_lock;
INIT_ONCE g_lock_once = INIT_ONCE_STATIC_INIT;
BOOL CALLBACK init_lock(PINIT_ONCE, PVOID, PVOID*)
{
    InitializeCriticalSection(&g_lock);
    return TRUE;
}

void lock()
{
    InitOnceExecuteOnce(&g_lock_once, init_lock, nullptr, nullptr);
    EnterCriticalSection(&g_lock);
}

void unlock()
{
    LeaveCriticalSection(&g_lock);
}

// The job description travels to the thread by pointer, allocated here and freed
// by the worker when it is done. Not a static: 64 KB per spawn would be 384 KB
// of BSS for something that is usually short-lived.
// Per-worker allocation accounting. This used to be a pair of global atomics,
// and the "N blocs encore vivant(s)" line counted every OTHER worker's blocks
// too -- hence the absurd descending sequence 2605, 2084, 1563, 1042, 521:
// that is one global counter draining, not six leaks. The allocator's `ud` is
// exactly the place to keep per-state counters.
struct AllocCounters {
    std::size_t live;
    std::size_t bytes;
};

struct Job {
    int slot;
    char* code;
    int len;
    char* meta;      // upvalue descriptors, or null
    int meta_len;
    char error[256];
    AllocCounters alloc;
};

// Where the worker finds its Job*. The Lua registry is per-state, so this is the
// natural place: it is reachable from any C function on that state and needs no
// global and no thread_local (per-thread CRT state is not set up on a hidden
// thread). See worker.h for why the registry rather than a TLS slot.
constexpr const char* kJobKey = "specter.worker.job";

Job* job_of(lua_State* L)
{
    // lua_getfield, not the lua_pop/lua_getglobal shorthands: those are macros
    // in luaconf.h, they have no symbol behind them, and the ones that expand to
    // another lua_* would go through the shim — which is the game's binding
    // path. This is not the game's stack. Spelled out, on purpose.
    const int base = p_lua_gettop(L);
    p_lua_getfield(L, LUA_REGISTRYINDEX, kJobKey);
    Job* j = reinterpret_cast<Job*>(p_lua_touserdata(L, -1));
    p_lua_settop(L, base);
    return j;
}

void set_error(Job* job, const char* what)
{
    if (!job) {
        return;
    }
    const char* msg = (what && *what) ? what : "echec inconnu";
    std::snprintf(job->error, sizeof(job->error), "%s", msg);
}

// ---------------------------------------------------------------------------
// Our allocator.
//
// LuaJIT calls the allocator with the ORIGINAL size in osize, but we keep our
// own header anyway: it is what lets us report the true byte count, and it means
// a bad pointer is refused rather than freed. A worker thread allocating through
// malloc is not the problem; a worker thread allocating through OUR allocator
// after the image is unmapped is, and the header is what makes that a refusal
// instead of a wild free.
// ---------------------------------------------------------------------------

constexpr unsigned kAllocMagic = 0x53504553u;  // "SPES"

struct AllocHdr {
    std::size_t size;
    unsigned magic;
};

void* worker_alloc(void* ud, void* ptr, std::size_t osize, std::size_t nsize)
{
    (void)osize;  // our header is the authority, not the caller's bookkeeping
    auto* c = static_cast<AllocCounters*>(ud);

    if (ptr == nullptr) {
        if (nsize == 0) {
            return nullptr;
        }
        auto* h = static_cast<AllocHdr*>(
            _aligned_malloc(sizeof(AllocHdr) + nsize, 16));
        if (!h) {
            return nullptr;
        }
        h->size = nsize;
        h->magic = kAllocMagic;
        if (c) {
            c->bytes += nsize;
            ++c->live;
        }
        return h + 1;
    }

    auto* h = static_cast<AllocHdr*>(ptr) - 1;
    if (h->magic != kAllocMagic) {
        // Not ours. Returning nullptr makes Lua raise "not enough memory" at a
        // named place; freeing it would be a wild free.
        return nullptr;
    }

    const std::size_t old = h->size;
    if (nsize == 0) {
        if (c) {
            c->bytes -= old;
            --c->live;
        }
        h->magic = 0;
        _aligned_free(h);
        return nullptr;
    }

    void* moved = _aligned_realloc(h, sizeof(AllocHdr) + nsize, 16);
    if (!moved) {
        return nullptr;  // the old block is still valid: Lua retries or dies
    }
    auto* nh = static_cast<AllocHdr*>(moved);
    nh->size = nsize;
    if (c) {
        c->bytes += nsize;
        c->bytes -= old;
    }
    return nh + 1;
}

// ---------------------------------------------------------------------------
// What the worker world can see.
//
// Its own `specter` table, built from C functions. It is NOT the game's and NOT
// the sandbox's: a fresh state, a fresh table, and no route to either. `log` and
// `sleep` are the whole API for this build.
// ---------------------------------------------------------------------------

// specter.log(...) — the same sink as the DLL log, from the worker thread. The
// logger takes its own critical section, so this is safe cross-thread.
//
// Same shape as the sandbox's specter_log (lua/pump.cpp): a space before every
// part, into the same 1024-byte budget. Two implementations of "print", so
// they had better print the same thing.
int l_log(lua_State* L)
{
    const int top = p_lua_gettop(L);
    if (top < 1) {
        return 0;
    }
    char buf[1024];
    int n = 0;
    for (int i = 1; i <= top; ++i) {
        std::size_t len = 0;
        const char* s = p_lua_tolstring(L, i, &len);
        if (!s || len == 0) {
            continue;
        }
        if (n < static_cast<int>(sizeof(buf)) - 2) {
            buf[n++] = ' ';
        }
        const int room = static_cast<int>(sizeof(buf)) - n - 1;
        const int c = len < static_cast<std::size_t>(room)
                          ? static_cast<int>(len)
                          : room;
        std::memcpy(buf + n, s, static_cast<std::size_t>(c));
        n += c;
    }
    buf[n] = '\0';
    log::info("[worker]%s", buf);
    return 0;
}

// specter.sleep(ms) — and this is the kill checkpoint.
//
// Sleeps, then asks whether a kill is pending and raises if so. Raising is how
// a worker unwinds: it comes out of the body as a normal Lua error, which is
// what lua_pcall is for, so there is no unwinding of our own to get wrong.
int l_sleep(lua_State* L)
{
    Job* job = job_of(L);
    if (job) {
        const double ms = p_lua_tonumber(L, 1);
        if (ms > 0.0) {
            Sleep(ms > 60000.0 ? 60000 : static_cast<unsigned>(ms));
        }
        const int f = g_slots[job->slot].flag.load(std::memory_order_acquire);
        if (f == kKillAsked) {
            p_lua_pushstring(L, "arrete par specter.thread.kill()");
            p_lua_error(L);  // longjmps out to lua_pcall in worker_main
            return 0;        // not reached; keeps the compiler quiet
        }
    }
    return 0;
}

// specter.thread.id() — which slot this is, for log lines that interleave.
int l_id(lua_State* L)
{
    Job* job = job_of(L);
    p_lua_pushinteger(L, job ? job->slot : -1);
    return 1;
}

void set_fn(lua_State* L, const char* name, lua_CFunction fn)
{
    p_lua_pushcclosure(L, fn, 0);
    p_lua_setfield(L, -2, name);
}

void open_worker_api(lua_State* L, Job* job)
{
    // Reach the job from any C function without a global and without a
    // thread_local.
    p_lua_pushlightuserdata(L, job);
    p_lua_setfield(L, LUA_REGISTRYINDEX, kJobKey);

    p_lua_createtable(L, 0, 3);
    set_fn(L, "log", l_log);
    set_fn(L, "sleep", l_sleep);
    p_lua_createtable(L, 0, 1);
    set_fn(L, "id", l_id);
    p_lua_setfield(L, -2, "thread");
    p_lua_setfield(L, LUA_GLOBALSINDEX, "specter");
}

// ---------------------------------------------------------------------------
// Upvalues.
//
// string.dump keeps the SLOTS a closure captured and drops the VALUES. In the
// sandbox that used to be a wall, because the preamble captures the standard
// library as locals — so `specter.log('x', table.concat(t))` captured `table`,
// and on the worker that slot was nil.
//
// But the worker calls luaL_openlibs: it has the SAME standard library. So those
// upvalues are rebound to the worker's own globals, by name, and
// `table.concat` means exactly what it meant. That is the whole trick, and it is
// why the function form can work at all.

// Defined below, next to the rest of the flag table.
const char* flag_name(int f);

// The whole worker, as ONE protected call.
//
// This used to be inline C in worker_main, with no pcall anywhere around it. So
// any raise at all -- in luaL_openlibs, in a debug.* of the worker's own world,
// in something nobody thought of -- longjmped into nothing, LuaJIT printed
// PANIC, and the game died with it. Twice, and neither time with a log line
// pointing here.
//
// It is now a C function called under a pcall, and its single return value is
// either the error message or nil. A worker that misbehaves is a worker in
// error, with something to read.
int run_all(lua_State* L)
{
    Job* job =
        static_cast<Job*>(p_lua_touserdata(L, lua_upvalueindex(1)));
    if (!job) {
        return 0;
    }

    p_luaL_openlibs(L);
    open_worker_api(L, job);

    if (p_luaL_loadbuffer(L, job->code, job->len, "=specter-worker") != 0) {
        return 1;  // the message from loadbuffer is already on top
    }

    const int chunk = p_lua_gettop(L);
    char why[192] = "";
    if (job->meta && job->meta_len > 0 &&
        (meta::apply_meta(L, chunk, job->meta, job->meta_len, true, why,
                         sizeof(why)) < 0 ||
         meta::apply_meta(L, chunk, job->meta, job->meta_len, false, why,
                          sizeof(why)) < 0)) {
        p_lua_pushstring(L, why);
        return 1;
    }
    const int nargs = p_lua_gettop(L) - chunk;

    // The body runs under its OWN pcall: a kill raises from inside
    // specter.sleep(), and the state has to survive that to be closed
    // cleanly. This pcall is what returns that message, rather than the outer
    // one, so "killed" and "crashed" stay distinguishable.
    p_lua_pushvalue(L, chunk);
    if (p_lua_pcall(L, nargs, 0, 0) != 0) {
        return 1;
    }
    return 0;
}

DWORD WINAPI worker_main(LPVOID arg)
{
    Job* job = static_cast<Job*>(arg);
    _CRT_INIT(reinterpret_cast<void*>(&__ImageBase), DLL_THREAD_ATTACH, nullptr);

    Slot& slot = g_slots[job->slot];
    int terminal = kDone;
    const ULONGLONG t0 = GetTickCount64();

    lua_State* L = p_lua_newstate(&worker_alloc, &job->alloc);
    if (!L) {
        set_error(job, "lua_newstate a rendu NULL");
        terminal = kError;
    } else {
        // The single point that can raise. Everything else about the worker's
        // life happens inside this one call.
        p_lua_pushlightuserdata(L, job);
        p_lua_pushcclosure(L, &run_all, 1);
        if (p_lua_pcall(L, 0, 1, 0) != 0) {
            set_error(job, p_lua_tolstring(L, -1, nullptr));
            terminal = kError;
        } else if (p_lua_type(L, -1) == LUA_TNIL) {
            terminal = (slot.flag.load(std::memory_order_acquire) == kKillAsked)
                           ? kKilled
                           : kDone;
        } else {
            // run_all raised, or the body did: either way it is a message.
            set_error(job, p_lua_tolstring(L, -1, nullptr));
            terminal = (slot.flag.load(std::memory_order_acquire) == kKillAsked)
                           ? kKilled
                           : kError;
        }
        p_lua_close(L);
    }

    // ALWAYS printed, never only on failure.
    //
    // It used to be logged only when something was left, which is exactly the
    // way to miss a result: there is no line to read, and "nothing here" has to
    // be interpreted rather than read. A measurement you have to infer is not a
    // measurement. So the line states the numbers, 0 included, every time.
    //
    // The count is per worker -- carried by the allocator's `ud` -- so it means
    // something. It was a single global counter once, and the descending run
    // 2605, 2084, 1563, 1042, 521 that got printed back then was that one
    // counter draining, not six leaks.
    log::info("[worker %d] fin : %s en %.1f s, %zu bloc(s) / %zu o non rendu(s)",
              job->slot, flag_name(terminal),
              (GetTickCount64() - t0) / 1000.0, job->alloc.live,
              job->alloc.bytes);

    // Publish the message before the terminal flag: the reader only looks at
    // `error` once the flag is terminal, and release/acquire on the flag is what
    // orders those two writes.
    std::snprintf(slot.error, sizeof(slot.error), "%s", job->error);
    slot.flag.store(terminal, std::memory_order_release);

    std::free(job->code);
    std::free(job->meta);
    std::free(job);
    return 0;
}

// ---------------------------------------------------------------------------

const char* flag_name(int f)
{
    switch (f) {
    case kFree:      return "free";
    case kStarting:  return "starting";
    case kRunning:   return "running";
    case kKillAsked: return "kill asked";
    case kDone:      return "done";
    case kKilled:    return "killed";
    case kError:     return "error";
    default:         return "?";
    }
}

bool is_terminal(int f)
{
    return f == kFree || f == kDone || f == kKilled || f == kError;
}

// Free the slot of a worker whose body has finished.
//
// The thread publishes its terminal flag BEFORE it frees its job and returns,
// and from that point on it touches neither `slot` nor `error` — so the slot can
// be reused the moment the flag is seen. Waiting on the handle first is belt and
// braces: it is what turns "probably exited" into "has exited".
//
// Without this, spawn() looked only for kFree, and a slot stayed kDone forever:
// six spawns in a session, then "pas de slot libre" with nothing running.
void reclaim(int i)
{
    HANDLE t = nullptr;
    lock();
    t = g_slots[i].thread;
    g_slots[i].thread = nullptr;
    unlock();
    if (t) {
        WaitForSingleObject(t, 2000);
        CloseHandle(t);
    }
    g_slots[i].flag.store(kFree, std::memory_order_release);
    g_slots[i].error[0] = '\0';
}

char g_last_error[256] = "";

void set_last_error(const char* msg)
{
    std::snprintf(g_last_error, sizeof(g_last_error), "%s", msg ? msg : "");
}

}  // namespace

// ---------------------------------------------------------------------------
// The Lua side. Everything above is C++; this is what a script actually calls.
//
// All of it runs on the game's Lua thread, inside the sandbox, and touches no
// game state — a worker handle is just an integer in a table of ours.
// ---------------------------------------------------------------------------

namespace {

// Describe every upvalue of the closure at `idx` into `meta`, in the wire format
// bind_upvalues() reads. Returns false, with `refused` set to the variable's
// name, when something cannot cross.
//
// Uses char buffers rather than std::string on the error paths on purpose: a
// Lua error longjmps straight out of here, skipping every destructor between.
bool describe_upvalues(lua_State* L, int idx, std::string& meta,
                       char* refused, std::size_t refused_cap)
{
    const int base = p_lua_gettop(L);

    p_lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    if (p_lua_type(L, -1) != LUA_TTABLE) {
        p_lua_settop(L, base);
        std::snprintf(refused, refused_cap, "debug");
        return false;
    }
    p_lua_getfield(L, -1, "getupvalue");
    if (p_lua_type(L, -1) != LUA_TFUNCTION) {
        p_lua_settop(L, base);
        std::snprintf(refused, refused_cap, "debug.getupvalue");
        return false;
    }
    const int fn = p_lua_gettop(L);  // base+2 : [base+1]=debug [base+2]=getupvalue

    char buf[64];
    for (int i = 1;; ++i) {
        p_lua_pushvalue(L, fn);
        p_lua_pushvalue(L, idx);
        p_lua_pushinteger(L, i);
        p_lua_call(L, 2, 2);  // nom, valeur

        if (p_lua_type(L, -2) != LUA_TSTRING) {
            p_lua_settop(L, base);  // plus d'upvalue
            return true;
        }
        std::size_t nl = 0;
        const char* raw = p_lua_tolstring(L, -2, &nl);
        const std::string nm(raw ? raw : "", nl);
        const int vt = p_lua_type(L, -1);

        if (meta::is_stdlib_name(nm.c_str())) {
            // The sandbox captures the standard library as locals; the worker
            // called luaL_openlibs and has the same one. Rebind by name.
            std::snprintf(buf, sizeof(buf), "U L %d ", i);
            meta += buf;
            meta += nm;
            meta += '\n';
        } else {
            switch (vt) {
            case LUA_TNIL:
                std::snprintf(buf, sizeof(buf), "U Z %d\n", i);
                meta += buf;
                break;
            case LUA_TBOOLEAN:
                std::snprintf(buf, sizeof(buf), "U B %d %d\n", i,
                              p_lua_toboolean(L, -1) ? 1 : 0);
                meta += buf;
                break;
            case LUA_TNUMBER:
                std::snprintf(buf, sizeof(buf), "U N %d %.17g\n", i,
                              p_lua_tonumber(L, -1));
                meta += buf;
                break;
            case LUA_TSTRING: {
                std::size_t sl = 0;
                const char* sv = p_lua_tolstring(L, -1, &sl);
                std::snprintf(buf, sizeof(buf), "U S %d %zu\n", i, sl);
                meta += buf;
                meta.append(sv, sl);
                meta += '\n';
                break;
            }
            default:
                // A game table, a game function, a C closure. The worker's world
                // has no equivalent, so naming it is the whole service.
                std::snprintf(refused, refused_cap, "%s", nm.c_str());
                p_lua_settop(L, base);
                return false;
            }
        }
        p_lua_settop(L, base + 2);  // drop nom+valeur, keep debug/getupvalue
    }
}

// Describe the call arguments sitting at `first`..top. Same encodings as the
// upvalues, role 'A'. A game table or function is refused with its POSITION,
// because an argument has no name to quote.
bool describe_args(lua_State* L, int first, std::string& meta, char* refused,
                   std::size_t refused_cap)
{
    const int top = p_lua_gettop(L);
    char buf[64];
    for (int idx = first; idx <= top; ++idx) {
        const int n = idx - first + 1;
        switch (p_lua_type(L, idx)) {
        case LUA_TNIL:
            std::snprintf(buf, sizeof(buf), "A Z %d\n", n);
            meta += buf;
            break;
        case LUA_TBOOLEAN:
            std::snprintf(buf, sizeof(buf), "A B %d %d\n", n,
                          p_lua_toboolean(L, idx) ? 1 : 0);
            meta += buf;
            break;
        case LUA_TNUMBER:
            std::snprintf(buf, sizeof(buf), "A N %d %.17g\n", n,
                          p_lua_tonumber(L, idx));
            meta += buf;
            break;
        case LUA_TSTRING: {
            std::size_t sl = 0;
            const char* sv = p_lua_tolstring(L, idx, &sl);
            std::snprintf(buf, sizeof(buf), "A S %d %zu\n", n, sl);
            meta += buf;
            meta.append(sv, sl);
            meta += '\n';
            break;
        }
        default: {
            const int t = p_lua_type(L, idx);
            const char* nom = (t == LUA_TTABLE)     ? "une table du jeu"
                              : (t == LUA_TFUNCTION) ? "une fonction du jeu"
                              : (t == LUA_TUSERDATA) ? "un userdata du jeu"
                                                     : "une valeur du jeu";
            std::snprintf(refused, refused_cap, "l'argument %d est %s", n, nom);
            return false;
        }
        }
    }
    return true;
}

int api_spawn(lua_State* L)
{
    if (p_lua_gettop(L) < 1) {
        p_lua_pushstring(L, "specter.thread.spawn attend une fonction ou du code");
        p_lua_error(L);
        return 0;
    }

    std::string meta;
    // Arguments first: a refusal has to land before anything is spawned.
    char refused_args[160] = "";
    if (!describe_args(L, 2, meta, refused_args, sizeof(refused_args))) {
        char msg[512];
        std::snprintf(msg, sizeof(msg),
                      "specter.thread.spawn : %s, elle ne peut pas passer sur "
                      "un worker. Passe une valeur simple.",
                      refused_args);
        p_lua_pushstring(L, msg);
        p_lua_error(L);
        return 0;
    }

    if (p_lua_type(L, 1) == LUA_TFUNCTION) {
        // Descriptors BEFORE the dump: a refusal has to arrive before anything
        // is spawned, and it has to name the variable. "It did not work" is the
        // least useful error message there is.
        char refused[128] = "";
        if (!describe_upvalues(L, 1, meta, refused, sizeof(refused))) {
            char msg[512];
            std::snprintf(msg, sizeof(msg),
                          "specter.thread.spawn : l'upvalue '%s' ne peut pas "
                          "passer sur un worker (c'est une donnee du jeu). "
                          "Passe une fonction qui ne capture rien d'autre, ou "
                          "le SOURCE en chaine.",
                          refused);
            p_lua_pushstring(L, msg);
            p_lua_error(L);
            return 0;
        }

        // string.dump(f) -> bytecode. Leaving arg 1 as the function is not an
        // option: spawn() reads its payload from there.
        p_lua_getfield(L, LUA_GLOBALSINDEX, "string");
        p_lua_getfield(L, -1, "dump");
        p_lua_pushvalue(L, 1);
        p_lua_call(L, 1, 1);
        if (p_lua_type(L, -1) != LUA_TSTRING) {
            p_lua_pushstring(L, "specter.thread.spawn : string.dump a refuse "
                                "cette fonction");
            p_lua_error(L);
            return 0;
        }
        // pile : [1]=fonction [2]=table string [3]=bytecode
        p_lua_remove(L, 2);
        p_lua_replace(L, 1);
    }

    if (p_lua_type(L, 1) != LUA_TSTRING) {
        p_lua_pushstring(L, "specter.thread.spawn attend une chaine ou une "
                            "fonction");
        p_lua_error(L);
        return 0;
    }

    std::size_t len = 0;
    const char* code = p_lua_tolstring(L, 1, &len);
    const int h = spawn(code, static_cast<int>(len),
                        meta.empty() ? nullptr : meta.data(),
                        static_cast<int>(meta.size()));
    if (h < 0) {
        p_lua_pushstring(L, last_error());
        p_lua_error(L);
        return 0;
    }
    p_lua_pushinteger(L, h);
    return 1;
}

int api_kill(lua_State* L)
{
    p_lua_pushboolean(L, kill(static_cast<int>(p_lua_tonumber(L, 1))));
    return 1;
}

int api_join(lua_State* L)
{
    const double ms = p_lua_tonumber(L, 2);
    const unsigned t = (ms > 0.0) ? static_cast<unsigned>(ms) : 5000u;
    p_lua_pushboolean(L, join(static_cast<int>(p_lua_tonumber(L, 1)), t));
    return 1;
}

int api_status(lua_State* L)
{
    p_lua_pushstring(L, status(static_cast<int>(p_lua_tonumber(L, 1))));
    return 1;
}

int api_alive(lua_State* L)
{
    p_lua_pushinteger(L, alive());
    return 1;
}

int api_error(lua_State* L)
{
    p_lua_pushstring(L, error(static_cast<int>(p_lua_tonumber(L, 1))));
    return 1;
}

}  // namespace

bool register_api(lua_State* L, int specter_idx)
{
    if (!capi::ready()) {
        return false;
    }
    const int top = p_lua_gettop(L);
    if (specter_idx == 0 || specter_idx > top || specter_idx < -top) {
        return false;
    }

    // Work from a positive index. Everything below pushes, and a negative
    // specter_idx would slide under us mid-way.
    p_lua_pushvalue(L, specter_idx);
    const int target = p_lua_gettop(L);
    if (p_lua_type(L, target) != LUA_TTABLE) {
        p_lua_settop(L, top);
        return false;
    }

    p_lua_createtable(L, 0, 6);
    set_fn(L, "spawn", api_spawn);
    set_fn(L, "kill", api_kill);
    set_fn(L, "join", api_join);
    set_fn(L, "status", api_status);
    set_fn(L, "alive", api_alive);
    set_fn(L, "error", api_error);
    p_lua_setfield(L, target, "thread");

    p_lua_settop(L, top);
    log::info("lua: specter.thread enregistre (workers max %d)", kMaxWorkers);
    return true;
}

int spawn(const char* code, int len, const char* meta, int meta_len)
{
    if (!capi::ready()) {
        set_last_error("la couche C API n'est pas resolue");
        return -1;
    }
    if (!code || len <= 0) {
        set_last_error("code vide");
        return -1;
    }
    if (len > kMaxCode) {
        set_last_error("code trop long (max 64 Ko)");
        return -1;
    }
    if (meta && meta_len > kMaxMeta) {
        set_last_error("descripteurs d'upvalues trop longs");
        return -1;
    }

    lock();
    int slot_idx = -1;
    for (int i = 0; i < kMaxWorkers; ++i) {
        const int f = g_slots[i].flag.load(std::memory_order_acquire);
        if (is_terminal(f)) {
            slot_idx = i;
            break;
        }
    }
    if (slot_idx >= 0) {
        reclaim(slot_idx);
    }
    if (slot_idx >= 0) {
        g_slots[slot_idx].flag.store(kStarting, std::memory_order_relaxed);
    }
    unlock();

    if (slot_idx < 0) {
        set_last_error("pas de slot libre (max 6 workers)");
        return -1;
    }

    auto* job = static_cast<Job*>(std::calloc(1, sizeof(Job)));
    if (!job) {
        g_slots[slot_idx].flag.store(kFree, std::memory_order_relaxed);
        set_last_error("memoire epuisee");
        return -1;
    }
    job->code = static_cast<char*>(std::malloc(static_cast<std::size_t>(len)));
    if (!job->code) {
        std::free(job);
        g_slots[slot_idx].flag.store(kFree, std::memory_order_relaxed);
        set_last_error("memoire epuisee");
        return -1;
    }
    std::memcpy(job->code, code, static_cast<std::size_t>(len));
    job->len = len;
    job->slot = slot_idx;

    if (meta && meta_len > 0) {
        // +1 and the terminator: strtod/strtol in apply_meta are pointed at this
        // buffer and have no length of their own to stop at.
        job->meta = static_cast<char*>(std::malloc(static_cast<std::size_t>(meta_len) + 1));
        if (!job->meta) {
            std::free(job->code);
            std::free(job);
            g_slots[slot_idx].flag.store(kFree, std::memory_order_relaxed);
            set_last_error("memoire epuisee");
            return -1;
        }
        std::memcpy(job->meta, meta, static_cast<std::size_t>(meta_len));
        job->meta[meta_len] = '\0';
        job->meta_len = meta_len;
    }

    HANDLE h = nullptr;
    if (!nt::spawn_hidden_joined(&worker_main, job, &h)) {
        std::free(job->code);
        std::free(job->meta);
        std::free(job);
        g_slots[slot_idx].flag.store(kFree, std::memory_order_relaxed);
        set_last_error("le fil n'a pas demarre");
        return -1;
    }

    lock();
    g_slots[slot_idx].thread = h;
    // Starting -> running, unless a kill landed in the window between the claim
    // and here (possible: spawn and kill can come from the same tick).
    if (g_slots[slot_idx].flag.load(std::memory_order_relaxed) == kStarting) {
        g_slots[slot_idx].flag.store(kRunning, std::memory_order_relaxed);
    }
    unlock();

    log::info("lua: worker %d demarre (%d o)", slot_idx, len);
    return slot_idx;
}

bool kill(int h)
{
    if (h < 0 || h >= kMaxWorkers) {
        return false;
    }
    const int f = g_slots[h].flag.load(std::memory_order_acquire);
    if (f != kRunning && f != kStarting) {
        return false;
    }
    g_slots[h].flag.store(kKillAsked, std::memory_order_release);
    set_last_error("");
    return true;
}

bool join(int h, unsigned timeout_ms)
{
    if (h < 0 || h >= kMaxWorkers) {
        return false;
    }
    lock();
    HANDLE t = g_slots[h].thread;
    unlock();
    if (!t) {
        return is_terminal(g_slots[h].flag.load(std::memory_order_acquire));
    }
    const DWORD r = WaitForSingleObject(t, timeout_ms);
    return r == WAIT_OBJECT_0;
}

const char* status(int h)
{
    if (h < 0 || h >= kMaxWorkers) {
        return "handshake inconnu";
    }
    return flag_name(g_slots[h].flag.load(std::memory_order_acquire));
}

const char* error(int h)
{
    if (h < 0 || h >= kMaxWorkers) {
        return "handshake inconnu";
    }
    return g_slots[h].error;
}

const char* last_error()
{
    return g_last_error;
}

int alive()
{
    int n = 0;
    for (int i = 0; i < kMaxWorkers; ++i) {
        const int f = g_slots[i].flag.load(std::memory_order_acquire);
        if (f == kStarting || f == kRunning || f == kKillAsked) {
            ++n;
        }
    }
    return n;
}

void shutdown()
{
    for (int i = 0; i < kMaxWorkers; ++i) {
        HANDLE t = nullptr;
        lock();
        t = g_slots[i].thread;
        const int f = g_slots[i].flag.load(std::memory_order_acquire);
        unlock();

        if (f == kStarting || f == kRunning || f == kKillAsked) {
            g_slots[i].flag.store(kKillAsked, std::memory_order_release);
            if (t && WaitForSingleObject(t, kShutdownWaitMs) == WAIT_OBJECT_0) {
                log::info("lua: worker %d arrete et rejoint", i);
            } else {
                // Deliberately NOT TerminateThread. A worker inside lua_pcall may
                // be inside our allocator right now, and killing it there turns a
                // hung script into a crash. The cost of this choice is written
                // down in worker.h; the cost of the other one is a crash.
                log::error("lua: worker %d ne s'arrete pas -- il ne passe "
                           "probablement pas par specter.sleep(). Le fil reste "
                           "en vie ; on ne le tue pas au milieu d'un lua_pcall.",
                           i);
            }
        }

        if (t) {
            lock();
            CloseHandle(t);
            g_slots[i].thread = nullptr;
            const int fin = g_slots[i].flag.load(std::memory_order_acquire);
            // Free the slot only if the thread is really gone: a worker we could
            // not join must never have its slot handed to a second body.
            if (fin == kDone || fin == kKilled || fin == kError) {
                g_slots[i].flag.store(kFree, std::memory_order_release);
            }
            unlock();
        }
    }
}

}  // namespace specter::lua::worker