// Specter.Internal — the Lua thread pump (implementation).
//
// See pump.h for why this module exists. Nothing here knows about a feature:
// the detour, the state discovery, the C API resolution, the chunk runner and
// the hook dispatch are the whole of it.

#include "pch-il2cpp.h"

#include "lua/pump.h"

#include <Windows.h>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "il2cpp/runtime.h"
#include "il2cpp/target.h"
#include "platform/hook/detour.h"
#include "platform/log.h"
#include "platform/seh.h"

namespace specter::lua {
namespace pump {
namespace {

// ---- Lua C API (xlua.dll, LuaJIT 5.1 ABI) ----------------------------------

using lua_State = void;

using luaL_loadbuffer_fn = int(__cdecl*)(lua_State*, const char*, size_t,
                                         const char*);
using lua_pcall_fn = int(__cdecl*)(lua_State*, int, int, int);
using lua_gettop_fn = int(__cdecl*)(lua_State*);
using lua_settop_fn = void(__cdecl*)(lua_State*, int);
using lua_getglobal_fn = void(__cdecl*)(lua_State*, const char*);
using lua_type_fn = int(__cdecl*)(lua_State*, int);
using lua_tolstring_fn = const char*(__cdecl*)(lua_State*, int, size_t*);
using lua_toboolean_fn = int(__cdecl*)(lua_State*, int);
using lua_rawgeti_fn = void(__cdecl*)(lua_State*, int, int);
using lua_rawseti_fn = void(__cdecl*)(lua_State*, int, int);
using lua_createtable_fn = void(__cdecl*)(lua_State*, int, int);
using lua_setfield_fn = void(__cdecl*)(lua_State*, int, const char*);
using lua_pushcclosure_fn = void(__cdecl*)(lua_State*, int(__cdecl*)(lua_State*), int);
using lua_pushstring_fn = void(__cdecl*)(lua_State*, const char*);
using lua_pushvalue_fn = void(__cdecl*)(lua_State*, int);
using lua_gettable_fn = void(__cdecl*)(lua_State*, int);
using lua_settable_fn = void(__cdecl*)(lua_State*, int);
using lua_setfenv_fn = int(__cdecl*)(lua_State*, int);
using lua_setmetatable_fn = int(__cdecl*)(lua_State*, int);

luaL_loadbuffer_fn p_loadbuffer = nullptr;
lua_pcall_fn p_pcall = nullptr;
lua_gettop_fn p_gettop = nullptr;
lua_settop_fn p_settop = nullptr;
lua_getglobal_fn p_getglobal = nullptr;
lua_type_fn p_type = nullptr;
lua_tolstring_fn p_tolstring = nullptr;
lua_toboolean_fn p_toboolean = nullptr;
lua_rawgeti_fn p_rawgeti = nullptr;
lua_rawseti_fn p_rawseti = nullptr;
lua_createtable_fn p_createtable = nullptr;
lua_setfield_fn p_setfield = nullptr;
lua_pushcclosure_fn p_pushcclosure = nullptr;
lua_pushstring_fn p_pushstring = nullptr;
lua_pushvalue_fn p_pushvalue = nullptr;
lua_gettable_fn p_gettable = nullptr;
lua_settable_fn p_settable = nullptr;
lua_setfenv_fn p_setfenv = nullptr;
lua_setmetatable_fn p_setmetatable = nullptr;

// This LuaJIT follows the Lua 5.0 convention: LUA_REGISTRYINDEX is -10000, not
// the 0xFFF pseudo-index of 5.1. So the pseudo-index below is wrong for this
// build and the real one is spelled out.
//
// The registry is used for ONE thing: keying our sandbox store, so a variable
// set by one Execute survives to the next. It is deliberately NOT used to reach
// the game's globals -- see specter_env for why guessing there is a trap.
#ifndef LUA_REGISTRYINDEX
#define LUA_REGISTRYINDEX (-10000)
#endif

// ---- state ------------------------------------------------------------------

std::atomic<bool> g_api_ready{false};
std::atomic<bool> g_hook_installed{false};
std::atomic<bool> g_seen_state{false};
std::atomic<void*> g_lua_state{nullptr};
std::atomic<unsigned long long> g_ticks{0};
std::atomic<void*> g_last_state{nullptr};  // last state we fired hooks for

// ---- detour ----------------------------------------------------------------

using common_update_fn = void (*)(void* self, void* method);
common_update_fn g_orig_common_update = nullptr;

// ---- hook tables ------------------------------------------------------------
//
// Fixed capacity and zero-initialised on purpose: the DLL is manually mapped,
// so a container with a constructor would run before the CRT guard is set up.
// Registration is explicit and happens from app::start(), before the pump can
// ever fire.

constexpr int kMaxHooks = 8;
state_fn g_state_hooks[kMaxHooks];
tick_fn g_tick_hooks[kMaxHooks];

// Set by a feature that wants to filter our own chunks out of its capture
// (see features/lua_dump). A filter keeps `lua/` from having to know that a
// feature exists — the dependency stays feature -> lua.
using chunk_filter_fn = bool (*)(const char* chunk_name);
chunk_filter_fn g_chunk_filter = nullptr;

// ---- xlua resolution -------------------------------------------------------

template <typename T>
void bind(HMODULE m, const char* name, T& out)
{
    out = reinterpret_cast<T>(::GetProcAddress(m, name));
}

bool resolve_xlua()
{
    if (g_api_ready.load(std::memory_order_relaxed)) {
        return true;
    }
    HMODULE m = ::GetModuleHandleW(L"xlua.dll");
    if (!m) {
        m = ::GetModuleHandleW(L"XLua.dll");
    }
    if (!m) {
        return false;
    }
    bind(m, "luaL_loadbuffer", p_loadbuffer);
    bind(m, "lua_pcall", p_pcall);
    bind(m, "lua_gettop", p_gettop);
    bind(m, "lua_settop", p_settop);
    bind(m, "lua_getglobal", p_getglobal);
    bind(m, "lua_type", p_type);
    bind(m, "lua_tolstring", p_tolstring);
    bind(m, "lua_toboolean", p_toboolean);
    // Needed to build the per-run sandbox environment (see build_specter/run).
    bind(m, "lua_rawgeti", p_rawgeti);
    bind(m, "lua_rawseti", p_rawseti);
    bind(m, "lua_createtable", p_createtable);
    bind(m, "lua_setfield", p_setfield);
    bind(m, "lua_pushcclosure", p_pushcclosure);
    bind(m, "lua_pushstring", p_pushstring);
    bind(m, "lua_pushvalue", p_pushvalue);
    bind(m, "lua_gettable", p_gettable);
    bind(m, "lua_settable", p_settable);
    bind(m, "lua_setfenv", p_setfenv);
    bind(m, "lua_setmetatable", p_setmetatable);
    if (!p_loadbuffer || !p_pcall || !p_gettop || !p_settop || !p_tolstring ||
        !p_toboolean || !p_getglobal || !p_type || !p_rawgeti || !p_rawseti ||
        !p_createtable || !p_setfield || !p_pushcclosure ||
        !p_pushstring || !p_pushvalue || !p_gettable || !p_settable || !p_setfenv || !p_setmetatable) {
        log::error("lua: xlua.dll found but some Lua C API exports are missing");
        return false;
    }
    g_api_ready.store(true, std::memory_order_relaxed);
    log::info("lua: LuaJIT C API resolved from xlua.dll (%p)", (void*)m);
    return true;
}

// ---- chunk execution (runs on the Lua thread) ------------------------------

constexpr int kMaxCode = 32 * 1024;

// The chunk is a FACTORY: it returns a closure, and C then calls that closure
// with the specter table. The factory finds the real globals ITSELF, with
// getfenv(__f), read BEFORE it switches environments.
//
// Why not hand the globals in from C? Because C can only guess where they are.
// The usual guess is registry[2]; it is wrong on some builds, and when it is
// wrong nothing says so -- the sandbox still runs, it just falls through to a
// table that is not _G, and the suffix (which needs table.concat after the
// switch) blows up with a bare 'attempt to call a table value'. Reading the
// factory's own environment cannot be wrong: it IS the environment the chunk
// loaded into.
//
// And why not setfenv(0, env), the idiomatic 5.1 form? Because LuaJIT does not
// implement it. Measured on this interpreter: setfenv(0, t) leaves the
// environment untouched (the read comes back nil), while setfenv(f, t) works.
// So the factory names itself and passes that name.
//
// The standard library is captured as LOCALS before the switch. Locals are
// resolved lexically, so the suffix cannot be broken by whatever __g turns out
// to be.
//
//   read  k      -> our store first, then the game's real _G  (full access)
//   write k = v  -> the game already owns k, write the GAME's global
//   write k = v  -> otherwise keep it in our store
//
// `print` is captured through a LOCAL rather than by overwriting the global, so
// nothing has to be restored and the game's print is never disturbed.
constexpr char kPrefix[] =
    "local __f;\n"
    "__f=function(__sp)\n"
    "local __g=getfenv(__f)\n"
    "local rawget,rawset,setmetatable,setfenv,table,tostring,pcall,select=\n"
    "  rawget,rawset,setmetatable,setfenv,table,tostring,pcall,select\n"
    "local __store=__sp.__store\n"
    "local __o={}\n"
    "local print=function(...)local t={}for i=1,select('#',...)do\n"
    "  t[#t+1]=tostring((select(i,...)))end\n"
    "  __o[#__o+1]=table.concat(t,'\\t')end\n"
    "local __env=setmetatable({},{\n"
    "  __index=function(_,k)local v=rawget(__store,k)\n"
    "    if v~=nil then return v end return __g[k] end,\n"
    "  __newindex=function(_,k,v)if rawget(__g,k)~=nil then\n"
    "    rawset(__g,k,v) else rawset(__store,k,v) end end})\n"
    "rawset(__env,'specter',__sp)\n"
    "rawset(__sp,'__global',__g)\n"
    "setfenv(__f,__env)\n"
    "local __r={pcall(function()\n";

constexpr char kSuffix[] =
    "\nend)};local __ok=table.remove(__r,1);"
    "if not __ok then __o[#__o+1]='ERROR: '..tostring(__r[1])else if #__r>0 "
    "then local t={}for i=1,#__r do t[i]=tostring(__r[i])end __o[#__o+1]="
    "table.concat(t,'\\t')end end;return table.concat(__o,'\\n'),__ok\n"
    "end\nreturn __f\n";
// Registry key for the sandbox store: an anonymous integer slot in the game's
// registry. Not an entry in _G, and not a name anybody can look up by walking
// the globals. Ours, under a key we chose, holding only our scratch variables.
constexpr int kStoreKey = 0x53505254;  // 'SPRT'

// ---- the `specter` namespace ------------------------------------------------
//
// Built per run and injected into the sandbox env, NEVER into the game's _G.
// That is what makes it ours alone: a game script resolving `specter` goes
// through the real globals and finds nothing, while our own chunks resolve it in
// the environment we handed them. No global is created, so there is nothing to
// collide with and nothing to enumerate out of _G.

int specter_env(lua_State* L)
{
    // The real globals are NOT guessed here. The factory reads its own
    // environment (getfenv(__f)) before switching, and parks the table on the
    // specter table; this just hands it back.
    //
    // The C-side guess -- registry[2] -- is what this replaces. It is right on
    // most builds and silently wrong on others, and when it is wrong nothing
    // says so: the sandbox still runs, it just reads and writes a table that is
    // not _G. Returning the table the sandbox demonstrably read through cannot
    // have that failure mode.
    p_pushstring(L, "__global");
    p_gettable(L, 1);
    return 1;
}

int specter_log(lua_State* L)
{
    const int top = p_gettop(L);
    if (top < 1) {
        return 0;
    }
    char buf[1024];
    int n = 0;
    for (int i = 1; i <= top; ++i) {
        std::size_t len = 0;
        const char* s = p_tolstring(L, i, &len);
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
    log::info("specter| %s", buf);
    return 0;
}

// Build the specter table on top of the stack. Leaves exactly one value.
//
// The store is recovered from the registry per state and created on first use, so
// a variable set by one Execute is still there on the next -- without ever
// touching the game's globals.
void build_specter(lua_State* L)
{
    p_rawgeti(L, LUA_REGISTRYINDEX, kStoreKey);
    if (p_type(L, -1) != 5) {  // absent, or the state was recreated
        p_settop(L, -2);
        p_createtable(L, 0, 8);
        p_pushvalue(L, -1);
        p_rawseti(L, LUA_REGISTRYINDEX, kStoreKey);
    }
    // [store]

    p_createtable(L, 0, 4);  // [store, specter]

    p_pushstring(L, "1.0");
    p_setfield(L, -2, "version");

    p_pushvalue(L, -2);   // [store, specter, store]
    p_setfield(L, -2, "store");

    p_pushcclosure(L, &specter_env, 0);
    p_setfield(L, -2, "env");

    p_pushcclosure(L, &specter_log, 0);
    p_setfield(L, -2, "log");

    // Hand the store to the preamble under the internal name it reads.
    p_pushvalue(L, -2);   // [specter, store]
    p_setfield(L, -2, "__store");
    // [specter]
}


// ---- the pump itself -------------------------------------------------------

void pump_impl(void* self)
{
    g_ticks.fetch_add(1, std::memory_order_relaxed);

    if (!resolve_xlua()) {
        return;
    }

    char* env = *reinterpret_cast<char**>(reinterpret_cast<char*>(self) +
                                          target::kLuaManager_luaenv);
    char* L = env ? *reinterpret_cast<char**>(env + target::kLuaEnv_rawL) : nullptr;
    if (!L) {
        return;
    }
    g_seen_state.store(true, std::memory_order_relaxed);
    g_lua_state.store(L, std::memory_order_relaxed);

    // The game recreates the state on scene reload / re-login, so per-state
    // hooks fire again for a brand new pointer. Keyed on the pointer, never on a
    // boolean: a state can come back different after a disconnect.
    if (g_last_state.load(std::memory_order_relaxed) != L) {
        g_last_state.store(L, std::memory_order_relaxed);
        for (int i = 0; i < kMaxHooks; ++i) {
            if (g_state_hooks[i]) {
                g_state_hooks[i](L);
            }
        }
    }

    for (int i = 0; i < kMaxHooks; ++i) {
        if (g_tick_hooks[i]) {
            g_tick_hooks[i](L);
        }
    }
}

// A bug in our Lua work must never take the whole game down. platform/seh.h
// explains why SEH and not a C++ try/catch.
void pump(void* self)
{
    SPECTER_SEH_BEGIN
    pump_impl(self);
    SPECTER_SEH_END("lua: work skipped for this frame")
}

void common_update_hook(void* self, void* method)
{
    pump(self);
    if (g_orig_common_update) {
        g_orig_common_update(self, method);
    }
}

}  // namespace

// ---- public API ------------------------------------------------------------

void run(void* L, const char* code, int len, result_sink sink)
{
    if (!L || !code || len <= 0 || !sink) {
        return;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    static char src[kMaxCode + sizeof(kPrefix) + sizeof(kSuffix)];
    const int plen = static_cast<int>(sizeof(kPrefix) - 1);
    const int slen = static_cast<int>(sizeof(kSuffix) - 1);
    std::memcpy(src, kPrefix, static_cast<std::size_t>(plen));
    std::memcpy(src + plen, code, static_cast<std::size_t>(len));
    std::memcpy(src + plen + len, kSuffix, static_cast<std::size_t>(slen));

    constexpr char kChunkName[] = "@specter";
    const bool suppressed =
        g_chunk_filter != nullptr && g_chunk_filter(kChunkName);

    const int top = p_gettop(L);
    if (!suppressed &&
        p_loadbuffer(L, src, static_cast<size_t>(plen + len + slen),
                     kChunkName) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua load error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (suppressed) {
        sink(true, "", 0);
        p_settop(L, top);
        return;
    }

    // Call 1: the chunk returns its factory closure.
    if (p_pcall(L, 0, 1, 0) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua load error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (p_type(L, -1) != 6) {  // LUA_TFUNCTION
        sink(false, "chunk did not return a function", 29);
        p_settop(L, top);
        return;
    }

    // Call 2: hand it the specter table. The real globals travel WITH it -- the
    // factory reads its own environment and keeps the reference, so C never has
    // to guess where _G lives.
    build_specter(L);
    if (p_pcall(L, 1, 2, 0) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua runtime error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }

    // Stack: [text, ok]
    std::size_t n = 0;
    const char* text = p_tolstring(L, -2, &n);
    const bool ok = p_toboolean(L, -1) != 0;
    sink(ok, text ? text : "", static_cast<int>(n));
    p_settop(L, top);
}


bool install()
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        const std::uintptr_t base = il2cpp::module_base();
        if (base == 0) {
            log::error("lua: GameAssembly.dll not mapped - no Lua bridge");
            return false;
        }
        // Not named `target`: that would shadow the target namespace right
        // where we need to qualify the RVA.
        void* site = reinterpret_cast<void*>(base + target::kCommonUpdateRva);
        if (specter::hook::install(
                site, reinterpret_cast<void*>(&common_update_hook),
                reinterpret_cast<void**>(&g_orig_common_update),
                "LuaManager.CommonUpdate")) {
            g_hook_installed.store(true, std::memory_order_relaxed);
        } else {
            log::error("lua: CommonUpdate hook failed - Lua disabled");
            return false;
        }
    }

    if (!resolve_xlua()) {
        log::info("lua: xlua.dll not loaded yet - will retry from the pump");
    }
    return g_hook_installed.load(std::memory_order_relaxed);
}

bool ready()
{
    return g_hook_installed.load(std::memory_order_relaxed) &&
           g_seen_state.load(std::memory_order_relaxed);
}

unsigned long long ticks()
{
    return g_ticks.load(std::memory_order_relaxed);
}

void* state()
{
    return g_lua_state.load(std::memory_order_relaxed);
}

bool add_state_hook(state_fn fn)
{
    if (!fn) {
        return false;
    }
    for (int i = 0; i < kMaxHooks; ++i) {
        if (!g_state_hooks[i]) {
            g_state_hooks[i] = fn;
            return true;
        }
    }
    return false;
}

bool add_tick_hook(tick_fn fn)
{
    if (!fn) {
        return false;
    }
    for (int i = 0; i < kMaxHooks; ++i) {
        if (!g_tick_hooks[i]) {
            g_tick_hooks[i] = fn;
            return true;
        }
    }
    return false;
}

void set_chunk_filter(chunk_filter_fn fn)
{
    g_chunk_filter = fn;
}

const char* status()
{
    static char buf[160];
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return "hook not installed";
    }
    if (!g_api_ready.load(std::memory_order_relaxed)) {
        return "waiting for xlua.dll";
    }
    if (!g_seen_state.load(std::memory_order_relaxed)) {
        return "waiting for LuaManager.CommonUpdate";
    }
    std::snprintf(buf, sizeof(buf), "ready - L=%p, %llu ticks",
                  g_lua_state.load(std::memory_order_relaxed),
                  static_cast<unsigned long long>(
                      g_ticks.load(std::memory_order_relaxed)));
    return buf;
}

}  // namespace pump
}  // namespace specter::lua