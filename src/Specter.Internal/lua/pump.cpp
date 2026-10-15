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

// This LuaJIT follows the Lua 5.0 convention: LUA_REGISTRYINDEX is -10000 (not
// the 0xFFF pseudo-index of 5.1), and _G is the registry entry number 2. Reading
// it the usual 5.1 way, through L->env / LUA_GLOBALSINDEX, can hand back an
// uninitialised pointer -- so everything here goes through registry[2].
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

// Wrap the chunk so that:
//   * `print` is captured line by line (tab-joined),
//   * errors are caught and reported,
//   * the chunk's own return values are appended,
//   * the wrapper returns (text, ok) so the C side reads exactly two results.
//
// `print` is captured through a LOCAL rather than by overwriting the global, so
// there is nothing to restore afterwards and the game's print is never disturbed
// even for the duration of the chunk.
//
// The sandbox environment is NOT built here: a Lua 5.1 chunk is not a vararg
// function, so it cannot receive anything through `...`. build_env() attaches it
// from C with lua_setfenv, before the pcall.
constexpr char kPrefix[] =
    "local __o={};\n"
    "local print=function(...)local t={}for i=1,select('#',...)do\n"
    "  t[#t+1]=tostring((select(i,...)))end\n"
    "  __o[#__o+1]=table.concat(t,'\\t')end\n"
    "local __r={pcall(function()\n";

constexpr char kSuffix[] =
    "\nend)};local __ok=table.remove(__r,1);"
    "if not __ok then __o[#__o+1]='ERROR: '..tostring(__r[1])else if #__r>0 "
    "then local t={}for i=1,#__r do t[i]=tostring(__r[i])end __o[#__o+1]="
    "table.concat(t,'\\t')end end;return table.concat(__o,'\\n'),__ok";
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
    // The game's real globals, reached the reliable way on this LuaJIT:
    // registry[2]. NOT LUA_GLOBALSINDEX -- L->env may be uninitialised on some
    // states and the read silently returns rubbish.
    //
    // This doubles as the sandbox's escape hatch, and as the way to verify the
    // assumption: if specter.env().pg resolves, then registry[2] is really _G.
    p_rawgeti(L, LUA_REGISTRYINDEX, 2);
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

// __index for the sandbox: our store first, then the game's globals.
//
// This has to be a function rather than a plain `__index = real_G`. With a plain
// table, a name that the sandbox created is invisible on the next read, because
// __index is only consulted for names the environment does not carry — so
// `x = 1` followed by `print(x)` would print nil.
//
// Like __newindex it fetches both tables from the registry rather than capturing
// them as upvalues, to avoid depending on lua_upvalueindex.
int sandbox_index(lua_State* L)
{
    const int top = p_gettop(L);  // [t=1, k=2]

    p_rawgeti(L, LUA_REGISTRYINDEX, kStoreKey);  // [t, k, store]
    p_pushvalue(L, 2);                          // [t, k, store, k]
    p_gettable(L, -2);                          // [t, k, store[k]]
    if (p_type(L, -1) != 0) {                   // the store had it
        return 1;
    }
    p_settop(L, top);

    // Fall through to the game's real globals.
    p_rawgeti(L, LUA_REGISTRYINDEX, 2);  // [t, k, realG]
    p_pushvalue(L, 2);                   // [t, k, realG, k]
    p_gettable(L, -2);                   // [t, k, realG[k]]
    p_settop(L, top + 1);
    return 1;
}

// __newindex for the sandbox: where a write to a global actually lands.
//
//   the game already owns the name  -> write the GAME's global
//   otherwise                      -> keep it in our store
//
// Both tables are fetched from the registry rather than captured as upvalues:
// a closure would need lua_upvalueindex, which is a macro whose value depends on
// the LUA_GLOBALSINDEX convention, and that is exactly the ambiguity this file
// is working around.
// Defined below; build_env needs it and build_specter needs build_env's sibling.
void build_specter(lua_State* L);

int sandbox_write(lua_State* L)
{
    const int top = p_gettop(L);  // [t=1, k=2, v=3]

    // Does the game own this name?
    p_rawgeti(L, LUA_REGISTRYINDEX, 2);  // [.., realG]
    p_pushvalue(L, 2);                   // [.., realG, k]
    p_gettable(L, -2);                   // [.., realG, realG[k]]

    const bool game_owns_it = p_type(L, -1) != 0;
    p_settop(L, top);

    // realG[k] = v, or store[k] = v.
    if (game_owns_it) {
        p_rawgeti(L, LUA_REGISTRYINDEX, 2);
    } else {
        p_rawgeti(L, LUA_REGISTRYINDEX, kStoreKey);
    }
    // [t, k, v, target]
    p_pushvalue(L, 3);  // v
    p_pushvalue(L, 2);  // k
    p_settable(L, -3);  // target[k] = v, pops k and v
    p_settop(L, top);
    return 0;
}

// Build the sandbox environment on top of the stack. Leaves exactly one value:
// the env, whose metatable is { __index = real_G, __newindex = sandbox_write }.
//
// A Lua chunk is NOT a vararg function in 5.1, so the preamble cannot receive
// these tables through `...`. They are attached here instead, which is also what
// nova does: build the tables on the stack, then lua_setfenv on the chunk.
//
// NOTE the ordering: `specter` is filled in BEFORE the metatable goes on,
// because with a metatable in place a plain setfield would trigger __newindex
// and send our own namespace into the game's globals.
void build_env(lua_State* L)
{
    build_specter(L);  // [specter]

    p_createtable(L, 0, 2);  // [specter, env]
    p_pushvalue(L, -2);
    p_setfield(L, -2, "specter");  // env.specter = specter  -> [specter, env]

    p_createtable(L, 0, 2);  // [specter, env, mt]
    p_pushcclosure(L, &sandbox_index, 0);
    p_setfield(L, -2, "__index");       // [specter, env, mt]
    p_pushcclosure(L, &sandbox_write, 0);
    p_setfield(L, -2, "__newindex");    // [specter, env, mt]

    p_pushvalue(L, -2);  // [specter, env, mt, env]
    p_setmetatable(L, -2);  // setmetatable(env, mt), pops mt -> [specter, env]
    p_settop(L, -2);        // drop the specter copy -> [env]
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
    // Attach the sandbox environment to the chunk before running it. A Lua 5.1
    // chunk cannot take arguments, so this has to happen from here.
    if (!suppressed) {
        build_env(L);                        // [chunk, env]
        if (p_setfenv(L, -2) == 0) {         // pops env
            sink(false, "chunk is not a Lua function", 28);
            p_settop(L, top);
            return;
        }
    }
    if (!suppressed && p_pcall(L, 0, 2, 0) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua runtime error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (suppressed) {
        sink(true, "", 0);
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