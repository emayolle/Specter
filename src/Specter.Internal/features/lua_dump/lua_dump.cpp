// Specter.Internal — runtime dumper for the game's Lua chunks (implementation).
//
// See lua_dump.h for the design. Short version: detour `xluaL_loadbuffer` in
// xlua.dll and write the chunk bytes to Z:\tmp\specter-lua-dump\.
//
// The hook runs on whatever thread the game loads scripts on (the Lua thread for
// the startup pack, possibly a download thread for XPatch chunks). It does file
// I/O, so it is serialised on a critical section and never calls into Lua.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "features/lua_dump/lua_dump.h"
#include "lua/pump.h"
#include "platform/log.h"
#include "platform/hook/detour.h"

namespace specter::features {
namespace lua_dump {
namespace {

using lua_State = void;

// LuaJIT's luaL_loadbuffer ABI: (L, buff, size, chunkname) -> int status.
using loadbuffer_fn = int(__cdecl*)(lua_State*, const char*, std::size_t,
                                    const char*);

loadbuffer_fn g_orig = nullptr;

std::atomic<bool> g_hook_installed{false};
std::atomic<bool> g_enabled{false};
std::atomic<unsigned long long> g_dumped{0};
std::atomic<int> g_suppress{0};

// Sequence number for the file name. Monotonic, never reused within a session,
// so a chunk reloaded (hot patch, module reload) lands in its own file instead of
// overwriting the previous capture.
std::atomic<unsigned long long> g_seq{0};

// One writer at a time: the hook can be entered concurrently by the Lua thread
// and a patch thread.
CRITICAL_SECTION g_lock;
bool g_lock_ready = false;

constexpr wchar_t kDumpDir[] = L"Z:\\tmp\\specter-lua-dump";

void ensure_lock()
{
    if (!g_lock_ready) {
        // Called from install(), which runs on the hidden worker thread; the
        // hook can only be reached after install() returned, so the init is
        // ordered before any use.
        ::InitializeCriticalSection(&g_lock);
        g_lock_ready = true;
    }
}

// Build "<seq>_<sanitised chunkname>.luac" under kDumpDir.
//
// The chunkname is the game's own Perforce path, e.g.
//   @C:\dev\jkroot\ws\workspace\XWinPublish\proj\p4dir\client\LuaScripts\Utils\ValueDisplayUtils.lua
// We flatten it into one component (backslash, slash, colon and space all
// become '_') and keep the tail, so the file is recognisable and the total path
// stays far below MAX_PATH. Wide chars throughout, like the CLI channel.
void make_path(wchar_t* out, std::size_t cap, const char* name)
{
    const unsigned long long seq =
        g_seq.fetch_add(1, std::memory_order_relaxed) + 1;

    std::size_t o = 0;
    auto put = [&](wchar_t c) {
        if (o + 1 < cap) out[o++] = c;
    };

    for (const wchar_t* p = kDumpDir; *p; ++p) put(*p);
    put(L'\\');

    // Zero-padded to 6 so the files sort in load order.
    wchar_t num[24];
    int n = 0;
    unsigned long long v = seq ? seq : 1;
    while (v && n < 20) {
        num[n++] = static_cast<wchar_t>(L'0' + static_cast<int>(v % 10));
        v /= 10;
    }
    while (n < 6) num[n++] = L'0';
    while (n > 0) put(num[--n]);
    put(L'_');

    if (name) {
        int t = 0;
        for (const char* p = name; *p && t < 96; ++p, ++t) {
            const unsigned char c = static_cast<unsigned char>(*p);
            const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                            (c >= '0' && c <= '9') || c == '.' || c == '_' ||
                            c == '-';
            put(ok ? static_cast<wchar_t>(c) : L'_');
        }
    }
    put(L'.');
    put(L'l');
    put(L'u');
    put(L'a');
    put(L'c');
    out[o] = L'\0';
}

void ensure_dump_dir()
{
    ::CreateDirectoryW(kDumpDir, nullptr);
    // ERROR_ALREADY_EXISTS is the normal case; anything else (no Z: drive yet,
    // permissions) simply means the write below fails and is reported once.
}

// ---- the hook ---------------------------------------------------------------

int __cdecl loadbuffer_hook(lua_State* L, const char* buff, std::size_t size,
                            const char* name)
{
    // Always forward first: the hook must never be able to break script loading.
    const int status = g_orig(L, buff, size, name);

    if (!g_enabled.load(std::memory_order_relaxed)) {
        return status;
    }
    if (g_suppress.load(std::memory_order_relaxed) > 0) {
        return status;
    }
    if (!buff || size == 0) {
        return status;
    }

    wchar_t path[320];
    {
        ::EnterCriticalSection(&g_lock);
        make_path(path, 320, name);
        ensure_dump_dir();
        std::FILE* f = nullptr;
        if (::_wfopen_s(&f, path, L"wb") == 0 && f) {
            std::fwrite(buff, 1, size, f);
            std::fclose(f);
            g_dumped.fetch_add(1, std::memory_order_relaxed);
        } else {
            log::error("lua_dump: cannot write the capture for chunk %s", name);
        }
        ::LeaveCriticalSection(&g_lock);
    }
    return status;
}

}  // namespace

// OFF. Do not flip this on without reading the note below.
//
// 2026-10-16, measured: this filled /tmp to 81% — 13 GB, 14 509 files — and
// it kept refilling after every deletion. /tmp is a 16 GB tmpfs, and a full
// tmpfs fails writes for EVERYTHING: ours and the game's. That was the only
// cause still standing after the worker crashes were eliminated one by one
// (six concurrent workers, allocator leaks, missing pcall, non-cooperative
// kill, a CPU-bound worker with no checkpoint — all cleared by measurement).
//
// This is also the feature with no cap anywhere in it. It writes one file per
// chunk the game loads, for as long as the game is played. A debugging tool
// that can exhaust the filesystem is not a debugging tool.
//
// Turning it back on is one edit, and it still works — but give it a cap first,
// or it will do it again.
constexpr bool kEnabled = false;

bool install()
{
    ensure_lock();

    if (!kEnabled) {
        log::info("lua_dump: coupe -- %ls n'est plus ecrit. "
                  "Raison : 13 Go remplis sur un tmpfs de 16 Go, sans plafond. "
                  "Le module xluaL_loadbuffer n'est meme pas detourne.",
                  kDumpDir);
        return true;
    }

    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        HMODULE m = ::GetModuleHandleW(L"xlua.dll");
        if (!m) {
            m = ::GetModuleHandleW(L"XLua.dll");
        }
        if (!m) {
            return false;
        }

        // Prefer the exact symbol the IL2CPP layer resolves ("xluaL_loadbuffer");
        // fall back to the upstream one if this build renamed it.
        auto* target = reinterpret_cast<void*>(::GetProcAddress(m, "xluaL_loadbuffer"));
        const char* which = "xluaL_loadbuffer";
        if (!target) {
            target = reinterpret_cast<void*>(::GetProcAddress(m, "luaL_loadbuffer"));
            which = "luaL_loadbuffer";
        }
        if (!target) {
            log::error("lua_dump: xlua.dll has neither xluaL_loadbuffer nor luaL_loadbuffer");
            return false;
        }

        if (!specter::hook::install(
                target, reinterpret_cast<void*>(&loadbuffer_hook),
                reinterpret_cast<void**>(&g_orig), which)) {
            log::error("lua_dump: detour on %s failed", which);
            return false;
        }
        g_hook_installed.store(true, std::memory_order_relaxed);
        log::info("lua_dump: hooked %s in xlua.dll (%p) -> %s", which, target, kDumpDir);
    }

    // Tell the pump not to feed our own chunks back into this capture. Done from
    // the feature rather than from app::start(), so the wiring stays on the
    // feature -> lua side and start() keeps naming nothing.
    specter::lua::pump::set_chunk_filter(&filter);

    // Capturing is the whole point of the tool, so it writes as soon as it is
    // installed. This is a research tool, not a gameplay feature: it observes
    // chunks, it never executes anything.
    set_enabled(true);
    return true;
}

void tick()
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        install();
    }
}

void set_enabled(bool on)
{
    g_enabled.store(on, std::memory_order_relaxed);
    if (on) {
        log::info("lua_dump: armed - writing to %s", kDumpDir);
    } else {
        log::info("lua_dump: disarmed (%llu chunks captured so far)",
                  (unsigned long long)g_dumped.load(std::memory_order_relaxed));
    }
}

bool enabled()
{
    return g_enabled.load(std::memory_order_relaxed);
}

unsigned long long dumped()
{
    return g_dumped.load(std::memory_order_relaxed);
}

bool filter(const char* chunk_name)
{
    (void)chunk_name;
    return g_suppress.load(std::memory_order_relaxed) > 0;
}

void push_suppress()
{
    g_suppress.fetch_add(1, std::memory_order_relaxed);
}

void pop_suppress()
{
    g_suppress.fetch_sub(1, std::memory_order_relaxed);
}

}  // namespace lua_dump
}  // namespace specter::features