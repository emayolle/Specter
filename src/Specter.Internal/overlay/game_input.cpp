// Specter.Internal — game input gate + OS cursor control (implementation).
//
// We hook seven user32 exports with our own inline-detour engine (detour.*,
// ported from Steam's overlay engine):
//   GetRawInputData, GetRawInputBuffer, GetAsyncKeyState, GetKeyState,
//   ClipCursor, ShowCursor, SetCursor
// Each proxy consults one atomic flag: menu closed -> forward to the trampoline
// (the real function); menu open -> return a neutral value. The cursor itself is
// released by our own code in set_menu_open(), which must call the trampolines
// (never the hooked exports) or its ClipCursor/ShowCursor calls would be
// swallowed by our own gate.
//
// Threading: the hooks run on whatever thread the game polls input from, so they
// only touch the atomic flag and the (immutable after install) trampolines.
// set_menu_open() runs on the render thread.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atomic>
#include <cstdint>

#include "overlay/game_input.h"
#include "overlay/detour.h"
#include "log.h"

namespace specter::overlay {
namespace game_input {
namespace {

std::atomic<bool> g_open{false};
std::atomic<bool> g_ungate{false};  // true only around a keyboard_sink call
std::atomic<keyboard_sink> g_sink{nullptr};
bool g_armed = false;
bool g_gave_up = false;

// Trampolines handed back by the engine (the original user32 code).
using GetRawInputData_t = UINT(WINAPI*)(HRAWINPUT, UINT, LPVOID, PUINT, UINT);
using GetRawInputBuffer_t = UINT(WINAPI*)(PRAWINPUT, PUINT, UINT);
using GetAsyncKeyState_t = SHORT(WINAPI*)(int);
using GetKeyState_t = SHORT(WINAPI*)(int);
using ClipCursor_t = BOOL(WINAPI*)(const RECT*);
using ShowCursor_t = int(WINAPI*)(BOOL);
using SetCursor_t = HCURSOR(WINAPI*)(HCURSOR);

GetRawInputData_t real_get_raw_input_data = nullptr;
GetRawInputBuffer_t real_get_raw_input_buffer = nullptr;
GetAsyncKeyState_t real_get_async_key_state = nullptr;
GetKeyState_t real_get_key_state = nullptr;
ClipCursor_t real_clip_cursor = nullptr;
ShowCursor_t real_show_cursor = nullptr;
SetCursor_t real_set_cursor = nullptr;

// ---- hook proxies --------------------------------------------------------

UINT WINAPI hk_get_raw_input_data(HRAWINPUT h, UINT cmd, LPVOID data, PUINT size,
                                  UINT hdr)
{
    if (g_open.load(std::memory_order_relaxed)) {
        if (size) {
            *size = 0;
        }
        return static_cast<UINT>(-1);
    }
    return real_get_raw_input_data(h, cmd, data, size, hdr);
}

UINT WINAPI hk_get_raw_input_buffer(PRAWINPUT data, PUINT size, UINT hdr)
{
    if (g_open.load(std::memory_order_relaxed)) {
        if (size) {
            *size = 0;
        }
        return 0;
    }
    return real_get_raw_input_buffer(data, size, hdr);
}

SHORT WINAPI hk_get_async_key_state(int vk)
{
    if (g_open.load(std::memory_order_relaxed) &&
        !g_ungate.load(std::memory_order_relaxed)) {
        return 0;
    }
    return real_get_async_key_state(vk);
}

SHORT WINAPI hk_get_key_state(int vk)
{
    if (g_open.load(std::memory_order_relaxed) &&
        !g_ungate.load(std::memory_order_relaxed)) {
        return 0;
    }
    return real_get_key_state(vk);
}

BOOL WINAPI hk_clip_cursor(const RECT* r)
{
    // While the menu is up we keep the cursor unclipped: swallow the game's
    // re-clip and report success.
    if (g_open.load(std::memory_order_relaxed)) {
        return TRUE;
    }
    return real_clip_cursor(r);
}

int WINAPI hk_show_cursor(BOOL show)
{
    // The game hides the hardware cursor; while the menu is up we do not let it.
    if (g_open.load(std::memory_order_relaxed)) {
        return 1;
    }
    return real_show_cursor(show);
}

HCURSOR WINAPI hk_set_cursor(HCURSOR c)
{
    // While the menu is up ImGui draws its own cursor (io.MouseDrawCursor) and
    // asks for the OS cursor to be hidden, so we neutralise every SetCursor —
    // the game's and ImGui's alike — to NULL.
    if (g_open.load(std::memory_order_relaxed)) {
        return real_set_cursor(nullptr);
    }
    return real_set_cursor(c);
}

// ---- cursor save/restore -------------------------------------------------

bool g_cursor_saved = false;
bool g_had_clip = false;
RECT g_saved_clip = {};

void enter_menu()
{
    if (!g_armed) {
        return;
    }

    // Capture and release the game's clip region so the cursor can travel.
    RECT cur = {};
    if (::GetClipCursor(&cur)) {
        g_saved_clip = cur;
        g_had_clip = true;
    } else {
        g_had_clip = false;
    }
    real_clip_cursor(nullptr);
    real_set_cursor(nullptr);

    g_cursor_saved = true;
    log::info("input: menu open - cursor released (clip=%d)", g_had_clip);
}

void leave_menu()
{
    if (!g_armed || !g_cursor_saved) {
        return;
    }

    if (g_had_clip) {
        real_clip_cursor(&g_saved_clip);
    } else {
        real_clip_cursor(nullptr);
    }

    // The game keeps its hardware cursor hidden by setting it to NULL; hand
    // the OS back exactly that state. The gate swallowed the game's
    // ShowCursor(FALSE) calls while the menu was open (each returned 1 without
    // touching the real display counter), so that counter is too positive for
    // the game's own show/hide pairs: on its native "show cursor" shortcut
    // (ALT) it does ShowCursor(TRUE) then ShowCursor(FALSE) on release, and
    // the FALSE lands on 0 = *shown* instead of negative = hidden — a cursor
    // stuck on screen even though the camera works. Force the counter into its
    // canonical hidden range (negative) so future TRUE/FALSE pairs balance out
    // from a known base.
    real_set_cursor(nullptr);
    int c = real_show_cursor(0);  // read, no change
    for (int i = 0; i < 64 && c >= 0; ++i) {
        real_show_cursor(FALSE);
        c = real_show_cursor(0);
    }
    g_cursor_saved = false;
    log::info("input: menu closed - cursor state restored (show_count=%d)", c);
}

// ---- window subclass -----------------------------------------------------
//
// The user32 hooks above cover raw input and polled key state, but Unity also
// reads mouse buttons / keys from window messages (DispatchMessage ->
// WndProc), which is why a left-click still reached the game. Subclassing the
// game window lets us (a) swallow every input message while the menu is up and
// (b) defeat DefWindowProc(WM_SETCURSOR) — which would otherwise restore the
// game's NULL class cursor and hide the cursor again.

WNDPROC g_orig_wndproc = nullptr;
HWND g_wnd = nullptr;

bool is_keyboard_msg(UINT msg)
{
    switch (msg) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_CHAR:
        case WM_SYSCHAR:
        case WM_DEADCHAR:
        case WM_UNICHAR:
            return true;
        default:
            return false;
    }
}

LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    if (g_open.load(std::memory_order_relaxed)) {
        // Keyboard: feed ImGui (the console needs text input) then swallow, so
        // the game never sees the keystroke. The gate is lifted for the callee
        // so the Win32 ImGui backend reads the real modifier state.
        if (is_keyboard_msg(msg)) {
            keyboard_sink sink = g_sink.load(std::memory_order_relaxed);
            if (sink) {
                g_ungate.store(true, std::memory_order_relaxed);
                sink(h, msg, static_cast<uintptr_t>(w),
                     static_cast<intptr_t>(l));
                g_ungate.store(false, std::memory_order_relaxed);
            }
            return 0;
        }

        switch (msg) {
            case WM_SETCURSOR:
                ::SetCursor(nullptr);
                return TRUE;
            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_XBUTTONDBLCLK:
            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
            case WM_INPUT:
                return 0;  // the game sees no input while the menu is open
            default:
                break;
        }
    }
    if (g_orig_wndproc) {
        return ::CallWindowProcW(g_orig_wndproc, h, msg, w, l);
    }
    return ::DefWindowProcW(h, msg, w, l);
}

}  // namespace

bool install(void* hwnd)
{
    (void)hwnd;
    if (g_armed) {
        return true;
    }
    if (g_gave_up) {
        return false;
    }

    HMODULE user32 = ::GetModuleHandleW(L"user32.dll");
    if (!user32) {
        log::error("input: user32.dll not found");
        return false;
    }

    struct Target {
        const char* name;
        const char* proc;
        void* hook;
        void** orig;
    };
    const Target targets[] = {
        {"GetRawInputData", "GetRawInputData", (void*)&hk_get_raw_input_data,
         (void**)&real_get_raw_input_data},
        {"GetRawInputBuffer", "GetRawInputBuffer", (void*)&hk_get_raw_input_buffer,
         (void**)&real_get_raw_input_buffer},
        {"GetAsyncKeyState", "GetAsyncKeyState", (void*)&hk_get_async_key_state,
         (void**)&real_get_async_key_state},
        {"GetKeyState", "GetKeyState", (void*)&hk_get_key_state,
         (void**)&real_get_key_state},
        {"ClipCursor", "ClipCursor", (void*)&hk_clip_cursor,
         (void**)&real_clip_cursor},
        {"ShowCursor", "ShowCursor", (void*)&hk_show_cursor,
         (void**)&real_show_cursor},
        {"SetCursor", "SetCursor", (void*)&hk_set_cursor, (void**)&real_set_cursor},
    };

    const int total = static_cast<int>(sizeof(targets) / sizeof(targets[0]));
    int hooked = 0;
    for (const Target& t : targets) {
        void* fn = reinterpret_cast<void*>(::GetProcAddress(user32, t.proc));
        if (!fn) {
            log::error("input: %s not found in user32", t.proc);
            continue;
        }
        if (detour::is_installed(fn)) {
            log::info("input: %s already detoured - reusing", t.name);
            ++hooked;
            continue;
        }
        if (detour::install(fn, t.hook, t.orig, t.name)) {
            ++hooked;
        }
    }

    if (hooked == 0) {
        g_gave_up = true;
        log::error("input: no hooks installed - input gate off");
        return false;
    }

    g_armed = true;

    // Subclass the game window: swallow input messages (the left-click leak)
    // and own WM_SETCURSOR while the menu is open.
    if (hwnd && !g_orig_wndproc) {
        g_wnd = reinterpret_cast<HWND>(hwnd);
        ::SetLastError(0);
        g_orig_wndproc = reinterpret_cast<WNDPROC>(::SetWindowLongPtrW(
            g_wnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wnd_proc)));
        if (!g_orig_wndproc) {
            const DWORD e = ::GetLastError();
            if (e) {
                log::error("input: window subclass failed (%lu) - the game may "
                           "still see message-level input",
                           e);
            }
        } else {
            log::info("input: game window subclassed (%p)", (void*)g_wnd);
        }
    }

    if (hooked == total) {
        log::info("input: gate armed (%d/%d user32 functions hooked)", hooked,
                  total);
    } else {
        log::error("input: gate armed PARTIAL (%d/%d hook failed - see above)",
                   hooked, total);
    }
    return true;
}

void set_keyboard_sink(keyboard_sink fn)
{
    g_sink.store(fn, std::memory_order_relaxed);
}

void set_menu_open(bool open)
{
    // Drive the hook proxies from the desired state even when the gate is not
    // armed yet, so that it takes effect the instant install() succeeds.
    g_open.store(open, std::memory_order_relaxed);

    if (!g_armed) {
        return;
    }
    // Compare against the *applied* cursor state, not the previous desired
    // state: the gate may arm while the menu is already open, in which case
    // enter_menu() still has to run.
    if (open && !g_cursor_saved) {
        enter_menu();
    } else if (!open && g_cursor_saved) {
        leave_menu();
    }
}

bool armed()
{
    return g_armed;
}

short real_async_key_state(int vk)
{
    if (real_get_async_key_state) {
        return real_get_async_key_state(vk);
    }
    return ::GetAsyncKeyState(vk);
}

}  // namespace game_input
}  // namespace specter::overlay
