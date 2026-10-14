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
#include "platform/hook/detour.h"
#include "platform/log.h"

namespace specter::lua {
namespace pump {
namespace {

// ---- field offsets and RVAs (from generated/dump + appdata) ----------------

constexpr std::size_t kLuaManager_luaenv = 0x18;  // LuaManager.luaenv
constexpr std::size_t kLuaEnv_rawL = 0x10;        // LuaEnv.rawL
constexpr std::uintptr_t kCommonUpdateRva = 0x172ADC0;  // LuaManager.CommonUpdate

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

luaL_loadbuffer_fn p_loadbuffer = nullptr;
lua_pcall_fn p_pcall = nullptr;
lua_gettop_fn p_gettop = nullptr;
lua_settop_fn p_settop = nullptr;
lua_getglobal_fn p_getglobal = nullptr;
lua_type_fn p_type = nullptr;
lua_tolstring_fn p_tolstring = nullptr;
lua_toboolean_fn p_toboolean = nullptr;

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
    if (!p_loadbuffer || !p_pcall || !p_gettop || !p_settop || !p_tolstring ||
        !p_toboolean || !p_getglobal || !p_type) {
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
//   * the global `print` is always restored,
//   * the wrapper returns (text, ok) so the C side reads exactly two results.
constexpr char kPrefix[] =
    "local __o,__p={},print;print=function(...)local t={}for i=1,select('#',"
    "...)do t[#t+1]=tostring((select(i,...)))end __o[#__o+1]=table.concat(t,"
    "'\\t')end;local __r={pcall(function()\n";
constexpr char kSuffix[] =
    "\nend)};print=__p;local __ok=table.remove(__r,1);"
    "if not __ok then __o[#__o+1]='ERROR: '..tostring(__r[1])else if #__r>0 "
    "then local t={}for i=1,#__r do t[i]=tostring(__r[i])end __o[#__o+1]="
    "table.concat(t,'\\t')end end;return table.concat(__o,'\\n'),__ok";

// ---- the pump itself -------------------------------------------------------

void pump_impl(void* self)
{
    g_ticks.fetch_add(1, std::memory_order_relaxed);

    if (!resolve_xlua()) {
        return;
    }

    char* env = *reinterpret_cast<char**>(reinterpret_cast<char*>(self) +
                                          kLuaManager_luaenv);
    char* L = env ? *reinterpret_cast<char**>(env + kLuaEnv_rawL) : nullptr;
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

// Fault guard: a bug in our Lua work must never take the whole game down. MSVC
// / clang-cl lower __try/__except to SEH, which is available even in this
// manually mapped DLL (no CRT unveil needed).
int log_pump_exception(unsigned long code, EXCEPTION_POINTERS* ep)
{
    const void* addr = (ep != nullptr && ep->ExceptionRecord != nullptr)
                           ? ep->ExceptionRecord->ExceptionAddress
                           : nullptr;
    log::error("lua: pump exception code=0x%08lX at %p", code, addr);
    return code == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER
                                              : EXCEPTION_CONTINUE_SEARCH;
}

void pump(void* self)
{
    __try {
        pump_impl(self);
    } __except (log_pump_exception(GetExceptionCode(),
                                   GetExceptionInformation())) {
        log::error("lua: pump access violation swallowed - Lua work skipped "
                   "for this frame");
    }
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
        void* target = reinterpret_cast<void*>(base + kCommonUpdateRva);
        if (specter::hook::install(
                target, reinterpret_cast<void*>(&common_update_hook),
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