// Specter.Internal — Lua console bridge (implementation).
//
// See lua_console.h for the design. Summary:
//   * xlua.dll exports the LuaJIT 5.1 C API, resolved by name here;
//   * the lua_State is LuaManager.luaenv(@0x18)->rawL(@0x10), read on the Lua
//     thread inside our LuaManager.CommonUpdate detour;
//   * `submit()` (render thread) hands a chunk to that pump; `take_result()`
//     (render thread) picks up output/errors.
//
// We never call into managed code: the hook already gives us `this`
// (LuaManager*), and the Lua call itself is done entirely through the C API.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "features/lua_console.h"
#include "overlay/detour.h"
#include "runtime.h"
#include "log.h"

namespace specter::features {
namespace lua {
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

std::atomic<bool> g_api_ready{false};
std::atomic<bool> g_hook_installed{false};
std::atomic<bool> g_seen_state{false};
std::atomic<void*> g_lua_state{nullptr};
std::atomic<unsigned long long> g_ticks{0};
std::atomic<bool> g_inf_stamina{false};

// ---- detour ----------------------------------------------------------------

using common_update_fn = void (*)(void* self, void* method);
common_update_fn g_orig_common_update = nullptr;

// ---- cross-thread handoff (render thread <-> Lua thread) -------------------

CRITICAL_SECTION g_lock;
bool g_lock_ready = false;

constexpr int kMaxCode = 32 * 1024;
char g_code[kMaxCode];
int g_code_len = 0;
bool g_pending = false;
bool g_pending_silent = false;  // pump consumes without relaying a result

constexpr int kMaxOut = 48 * 1024;
char g_out[kMaxOut];
int g_out_len = 0;
bool g_out_okv = false;
std::atomic<bool> g_out_new{false};

// Dedicated teleport channel: pending chunks + their own captured result. Kept
// apart from the console slot above so UI position polling never shows up in
// the console log or the CLI channel. A small FIFO (rather than a single slot)
// so a position probe can't clobber a just-clicked teleport before the pump
// drains it.
constexpr int kTpQueue = 8;
char g_tp_code[kTpQueue][kMaxCode];
int g_tp_code_len[kTpQueue] = {};
int g_tp_head = 0;  // next read
int g_tp_tail = 0;  // next write

char g_tp_out[kMaxOut];
int g_tp_out_len = 0;
bool g_tp_out_okv = false;
std::atomic<bool> g_tp_new{false};

void ensure_lock()
{
    if (!g_lock_ready) {
        ::InitializeCriticalSection(&g_lock);
        g_lock_ready = true;
    }
}

// ---- host-visible mirrors (log pipe + out.txt) -----------------------------
//
// Every executed chunk's output is (a) mirrored to the log pipe line by line so
// it lands in the terminal/specter.log next to the rest of Specter's logs, and
// (b) published to Z:\tmp\specter-lua\out.txt so tools/lua.sh can read it back
// without a pipe reader. Both live in /tmp: nothing is ever written inside the
// game directory or the wine prefix.
//
// The CLI channel is the reverse direction: tools/lua.sh drops a chunk at
// cmd.lua (atomic rename), the pump claims it by renaming to cmd.run (also
// atomic, so a half-written file is never read), runs it, and deletes it.

const wchar_t* kCliDir = L"Z:\\tmp\\specter-lua";
const wchar_t* kCliIn = L"Z:\\tmp\\specter-lua\\cmd.lua";
const wchar_t* kCliRun = L"Z:\\tmp\\specter-lua\\cmd.run";
const wchar_t* kCliOutTmp = L"Z:\\tmp\\specter-lua\\out.tmp";
const wchar_t* kCliOut = L"Z:\\tmp\\specter-lua\\out.txt";

unsigned long long g_out_seq = 0;  // bump per published result (Lua thread only)

void ensure_cli_dir()
{
    ::CreateDirectoryW(kCliDir, nullptr);  // ignored if it already exists
}

// Read a whole (small) file; returns the length, or -1 if absent/unreadable.
int read_whole_file(const wchar_t* path, char* out, int cap)
{
    HANDLE h = ::CreateFileW(path, GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return -1;
    }
    int total = 0;
    while (total < cap - 1) {
        DWORD got = 0;
        if (!::ReadFile(h, out + total,
                        static_cast<DWORD>(cap - 1 - total), &got, nullptr) ||
            got == 0) {
            break;
        }
        total += static_cast<int>(got);
    }
    ::CloseHandle(h);
    out[total] = '\0';
    return total;
}

void write_file_atomic(const wchar_t* tmp, const wchar_t* dst, const char* data,
                       int len)
{
    HANDLE h = ::CreateFileW(tmp, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD wrote = 0;
    ::WriteFile(h, data, static_cast<DWORD>(len), &wrote, nullptr);
    ::CloseHandle(h);
    ::MoveFileExW(tmp, dst, MOVEFILE_REPLACE_EXISTING);
}

// log::info/error format into a 2 KB buffer, so split on newlines and clamp.
void log_result(bool ok, const char* text, int n)
{
    if (!text || n <= 0) {
        log::info("lua: (no output)");
        return;
    }
    const char* p = text;
    const char* end = text + n;
    int lines = 0;
    while (p < end) {
        if (lines >= 200) {
            log::info("lua| ... (output truncated in the pipe)");
            break;
        }
        ++lines;
        const char* nl = static_cast<const char*>(
            std::memchr(p, '\n', static_cast<std::size_t>(end - p)));
        int len = static_cast<int>(nl ? nl - p : end - p);
        char line[1500];
        int c = len < static_cast<int>(sizeof(line)) - 1
                    ? len
                    : static_cast<int>(sizeof(line)) - 1;
        std::memcpy(line, p, static_cast<std::size_t>(c));
        line[c] = '\0';
        if (ok) {
            log::info("lua| %s", line);
        } else {
            log::error("lua| %s", line);
        }
        p = nl ? nl + 1 : end;
    }
}

void publish_out(bool ok, const char* text, int n)
{
    static char buf[kMaxOut + 128];
    const unsigned long long seq = ++g_out_seq;
    int hl = std::snprintf(buf, sizeof(buf), "#seq=%llu ok=%d\n",
                           static_cast<unsigned long long>(seq), ok ? 1 : 0);
    if (hl < 0) {
        hl = 0;
    }
    if (text && n > 0) {
        std::memcpy(buf + hl, text, static_cast<std::size_t>(n));
        hl += n;
    }
    write_file_atomic(kCliOutTmp, kCliOut, buf, hl);
}

void store_result(bool ok, const char* s, int n)
{
    if (n < 0) {
        n = s ? static_cast<int>(std::strlen(s)) : 0;
    }
    if (n > kMaxOut - 1) {
        n = kMaxOut - 1;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    if (n > 0 && s) {
        std::memcpy(g_out, s, static_cast<std::size_t>(n));
    }
    g_out[n] = '\0';
    g_out_len = n;
    g_out_okv = ok;
    ::LeaveCriticalSection(&g_lock);
    g_out_new.store(true, std::memory_order_release);

    // Mirror to the host (log pipe -> terminal/specter.log, and out.txt).
    log_result(ok, s, n);
    publish_out(ok, s, n);
}

// Teleport-channel sibling of store_result(): captures into the dedicated
// buffer and mirrors to the log pipe only (no out.txt / seq bump).
void store_tp_result(bool ok, const char* s, int n)
{
    if (n < 0) {
        n = s ? static_cast<int>(std::strlen(s)) : 0;
    }
    if (n > kMaxOut - 1) {
        n = kMaxOut - 1;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    if (n > 0 && s) {
        std::memcpy(g_tp_out, s, static_cast<std::size_t>(n));
    }
    g_tp_out[n] = '\0';
    g_tp_out_len = n;
    g_tp_out_okv = ok;
    ::LeaveCriticalSection(&g_lock);
    g_tp_new.store(true, std::memory_order_release);
    log_result(ok, s, n);
}

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

// Wrap the user's chunk so that:
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

using result_sink = void (*)(bool ok, const char* s, int n);

void run_chunk_to(lua_State* L, const char* code, int len, result_sink sink)
{
    static char src[kMaxCode + sizeof(kPrefix) + sizeof(kSuffix)];
    const int plen = static_cast<int>(sizeof(kPrefix) - 1);
    const int slen = static_cast<int>(sizeof(kSuffix) - 1);
    std::memcpy(src, kPrefix, static_cast<std::size_t>(plen));
    std::memcpy(src + plen, code, static_cast<std::size_t>(len));
    std::memcpy(src + plen + len, kSuffix, static_cast<std::size_t>(slen));

    const int top = p_gettop(L);
    if (p_loadbuffer(L, src, static_cast<size_t>(plen + len + slen),
                     "@specter") != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua load error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (p_pcall(L, 0, 2, 0) != 0) {
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

void run_chunk(lua_State* L, const char* code, int len)
{
    run_chunk_to(L, code, len, store_result);
}

// Execute a chunk without relaying any result (used by the stamina toggle and
// its background maintenance so they never disturb the CLI channel/out.txt).
// Errors are silently discarded; the print-capture wrapper is reused so the
// code sees the same environment as a normal chunk.
void run_silent(lua_State* L, const char* code, int len)
{
    static char src[kMaxCode + sizeof(kPrefix) + sizeof(kSuffix)];
    const int plen = static_cast<int>(sizeof(kPrefix) - 1);
    const int slen = static_cast<int>(sizeof(kSuffix) - 1);
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    std::memcpy(src, kPrefix, static_cast<std::size_t>(plen));
    std::memcpy(src + plen, code, static_cast<std::size_t>(len));
    std::memcpy(src + plen + len, kSuffix, static_cast<std::size_t>(slen));

    const int top = p_gettop(L);
    if (p_loadbuffer(L, src, static_cast<size_t>(plen + len + slen),
                     "@specter") != 0) {
        p_settop(L, top);
        return;
    }
    (void)p_pcall(L, 0, 0, 0);
    p_settop(L, top);
}

// ---- the pump --------------------------------------------------------------

// Claim and run a chunk dropped by tools/lua.sh. Throttled: one filesystem
// probe every 200 ms is enough for a human/CLI-driven channel.
void poll_cli(lua_State* L)
{
    static unsigned long long last = 0;
    const unsigned long long now = ::GetTickCount64();
    if (now - last < 200) {
        return;
    }
    last = now;

    // Atomic claim: cmd.lua -> cmd.run. Fails (returns false) when there is no
    // pending chunk; the helper only ever publishes a complete file via rename.
    if (!::MoveFileExW(kCliIn, kCliRun, MOVEFILE_REPLACE_EXISTING)) {
        return;
    }
    static char code[kMaxCode];
    const int n = read_whole_file(kCliRun, code, kMaxCode);
    ::DeleteFileW(kCliRun);
    if (n <= 0) {
        store_result(false, "(empty cli command)", 20);
        return;
    }
    log::info("lua: cli chunk (%d bytes)", n);
    run_chunk(L, code, n);
}

// ---- infinite movement stamina (opt-in) ------------------------------------
//
// Sandbox discovery: chunks submitted to this bridge run in the game's
// sandboxed Lua environment. Reads of existing globals (pg, package.loaded, …)
// fall through to the real global table, but **writes** (even `_G.foo = …`)
// land in a per-chunk shadow and never reach the real _G. That is exactly why
// the first attempt — an install chunk defining `__SpecterStaminaTick` and a
// pump-side `lua_getglobal` + pcall per frame — silently did nothing.
//
// The robust lever is a per-instance method hook: assigning
// `actorCombatAttribute.changeStamina` on the player's instance shadows the
// metatable method for that object only. Instance field writes are ordinary
// writes on a live object, so they stick regardless of the sandbox. Movement
// costs (sprint/dash/glide/climb) all funnel through ClientStaminaComponent →
// `actorCombatAttribute:changeStamina(-cost)`; swallowing those negative
// deltas is "infinite stamina" at the source, and it does not race the game's
// per-frame drain (a pre-update refill would just be undone later in the
// frame).
//
// IMPORTANT (freeze fix): do NOT pin stamina with setAttribute() on every
// drain — each call runs the game's full attribute-change pipeline
// (recalc + HUD notifications + event dispatch) and stutters the frame. The
// hook swallows drains with a bare `return true` (nanoseconds), and stamina is
// pinned to max exactly ONCE when the hook is (re)installed.
//
// The toggle state lives in C++ (g_inf_stamina):
//   * ON  -> queue the idempotent installer (silently). The pump also re-runs
//            it silently every ~10 s so a fresh entity/aca after a relog gets
//            re-hooked. Stamina is pinned to max once at install time.
//   * OFF -> queue the restorer that puts the metatable method back.
// The silent path means none of this touches out.txt / the seq counter, so the
// CLI channel is never disturbed by maintenance traffic.

constexpr char kStaminaInstall[] =
    R"lua(local ent
for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do ent=_v break end
if not ent then return end
local aca=ent.actorCombatAttribute
if not aca then return end
local AC=package.loaded['Common.Const.AttributeConst']
if not AC then return end
if not aca.__SpecterHooked then
  local orig=aca.changeStamina
  if type(orig)~='function' then return end
  aca.changeStamina=function(self,delta)
    if delta and delta<0 then return true end
    return orig(self,delta)
  end
  aca.__SpecterHooked=true
end
local mx=aca:getMaxStamina()
if mx and mx>0 and aca:getAttribValue(AC.stamina_cur)<mx then
  aca:setAttribute(AC.stamina_cur,mx)
end
)lua";

constexpr char kStaminaDisable[] =
    R"lua(local ent
for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do ent=_v break end
if not ent then return end
local aca=ent.actorCombatAttribute
if not aca then return end
local mt=getmetatable(aca)
if mt and type(mt.changeStamina)=='function' then
  aca.changeStamina=mt.changeStamina
end
aca.__SpecterHooked=nil
)lua";

unsigned long long g_stamina_install_ticks = 0;  // Lua thread only

void pump(void* self)
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

    // Drain the pending chunk (copy it out under the lock, run it unlocked).
    static char local[kMaxCode];
    int len = 0;
    bool has = false;
    bool silent = false;
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    if (g_pending) {
        len = g_code_len;
        if (len > kMaxCode) {
            len = kMaxCode;
        }
        std::memcpy(local, g_code, static_cast<std::size_t>(len));
        g_pending = false;
        silent = g_pending_silent;
        g_pending_silent = false;
        has = true;
    }
    ::LeaveCriticalSection(&g_lock);

    if (has) {
        if (silent) {
            run_silent(L, local, len);
        } else {
            run_chunk(L, local, len);
        }
    }

    // Then the dedicated teleport channel (position get/set from the UI tab).
    // Same-thread, result captured into its own buffer (no console/out.txt).
    // Drain the whole FIFO so a probe and a teleport queued together both run.
    static char tp_local[kMaxCode];
    for (;;) {
        int tp_len = 0;
        bool tp_has = false;
        ensure_lock();
        ::EnterCriticalSection(&g_lock);
        if (g_tp_head != g_tp_tail) {
            tp_len = g_tp_code_len[g_tp_head];
            if (tp_len > kMaxCode) {
                tp_len = kMaxCode;
            }
            std::memcpy(tp_local, g_tp_code[g_tp_head],
                        static_cast<std::size_t>(tp_len));
            g_tp_head = (g_tp_head + 1) % kTpQueue;
            tp_has = true;
        }
        ::LeaveCriticalSection(&g_lock);
        if (!tp_has) {
            break;
        }
        run_chunk_to(L, tp_local, tp_len, store_tp_result);
    }

    // Then the CLI channel (tools/lua.sh), if a chunk is pending.
    poll_cli(L);

    // Infinite stamina: keep the cost hook applied. The installer is idempotent
    // and runs silently (no out.txt/seq traffic) about every 10 s while ON, so
    // a fresh player entity/aca after a relog gets re-hooked.
    if (g_inf_stamina.load(std::memory_order_relaxed)) {
        if (++g_stamina_install_ticks >= 600) {
            g_stamina_install_ticks = 0;
            run_silent(L, kStaminaInstall, sizeof(kStaminaInstall) - 1);
        }
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

bool install()
{
    ensure_lock();

    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        const std::uintptr_t base = runtime::module_base();
        if (base == 0) {
            log::error("lua: GameAssembly.dll not mapped - no Lua bridge");
            return false;
        }
        void* target = reinterpret_cast<void*>(base + kCommonUpdateRva);
        if (specter::overlay::detour::install(
                target, reinterpret_cast<void*>(&common_update_hook),
                reinterpret_cast<void**>(&g_orig_common_update),
                "LuaManager.CommonUpdate")) {
            g_hook_installed.store(true, std::memory_order_relaxed);
        } else {
            log::error("lua: CommonUpdate hook failed - Lua console disabled");
            return false;
        }
    }

    if (!resolve_xlua()) {
        log::info("lua: xlua.dll not loaded yet - will retry from the pump");
    }

    ensure_cli_dir();
    log::info("lua: cli channel ready - Z:\\tmp\\specter-lua (tools/lua.sh)");
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

bool submit(const char* code, int len)
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return false;
    }
    if (!code || len <= 0) {
        return false;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    std::memcpy(g_code, code, static_cast<std::size_t>(len));
    g_code_len = len;
    g_pending = true;
    ::LeaveCriticalSection(&g_lock);
    return true;
}

// Same as submit(), but the pump consumes the chunk with run_silent(): no
// result is relayed to the pipe or out.txt and the seq counter is untouched,
// so an in-flight tools/lua.sh command is never disturbed. Used by the stamina
// toggle (render thread) for its one-shot install/restore chunks.
bool submit_silent(const char* code, int len)
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return false;
    }
    if (!code || len <= 0) {
        return false;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    std::memcpy(g_code, code, static_cast<std::size_t>(len));
    g_code_len = len;
    g_pending = true;
    g_pending_silent = true;
    ::LeaveCriticalSection(&g_lock);
    return true;
}

bool set_infinite_stamina(bool on)
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return false;
    }
    const bool was = g_inf_stamina.exchange(on, std::memory_order_relaxed);
    if (on && !was) {
        // Apply now (render thread -> queue; the pump runs it silently).
        submit_silent(kStaminaInstall, sizeof(kStaminaInstall) - 1);
        log::info("lua: infinite movement stamina enabled");
    } else if (!on && was) {
        submit_silent(kStaminaDisable, sizeof(kStaminaDisable) - 1);
        log::info("lua: infinite movement stamina disabled");
    }
    return true;
}

bool infinite_stamina()
{
    return g_inf_stamina.load(std::memory_order_relaxed);
}

bool take_result(char* out, int cap, bool* out_ok)
{
    if (!out || cap <= 0) {
        return false;
    }
    if (!g_out_new.load(std::memory_order_acquire)) {
        return false;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    int n = g_out_len;
    if (n > cap - 1) {
        n = cap - 1;
    }
    std::memcpy(out, g_out, static_cast<std::size_t>(n));
    out[n] = '\0';
    if (out_ok) {
        *out_ok = g_out_okv;
    }
    ::LeaveCriticalSection(&g_lock);
    g_out_new.store(false, std::memory_order_release);
    return true;
}

bool tp_submit(const char* code, int len)
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return false;
    }
    if (!code || len <= 0) {
        return false;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    const int next = (g_tp_tail + 1) % kTpQueue;
    if (next == g_tp_head) {
        // Queue full (should not happen: probes are ~0.75 s apart). Dropping
        // the oldest would lose a teleport, so drop this one instead.
        ::LeaveCriticalSection(&g_lock);
        return false;
    }
    std::memcpy(g_tp_code[g_tp_tail], code, static_cast<std::size_t>(len));
    g_tp_code_len[g_tp_tail] = len;
    g_tp_tail = next;
    ::LeaveCriticalSection(&g_lock);
    return true;
}

bool tp_take_result(char* out, int cap, bool* out_ok)
{
    if (!out || cap <= 0) {
        return false;
    }
    if (!g_tp_new.load(std::memory_order_acquire)) {
        return false;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    int n = g_tp_out_len;
    if (n > cap - 1) {
        n = cap - 1;
    }
    std::memcpy(out, g_tp_out, static_cast<std::size_t>(n));
    out[n] = '\0';
    if (out_ok) {
        *out_ok = g_tp_out_okv;
    }
    ::LeaveCriticalSection(&g_lock);
    g_tp_new.store(false, std::memory_order_release);
    return true;
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

}  // namespace lua
}  // namespace specter::features
