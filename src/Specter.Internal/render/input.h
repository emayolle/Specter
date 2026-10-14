// Specter.Internal — game input gate + OS cursor control for the overlay menu.
//
// When the ImGui menu is open we want the OS cursor free and we want the game to
// receive *no* input at all. The game reads input through user32.dll:
//   * GetRawInputData / GetRawInputBuffer  (raw keyboard/mouse, Input System)
//   * GetAsyncKeyState / GetKeyState       (polled legacy key state)
//   * ClipCursor / ShowCursor / SetCursor  (the locked first-person cursor)
//
// We detour those user32 exports with our own inline-detour engine
// (platform/hook/detour.*), a port of the Steam overlay's engine (we cannot call
// Steam's own copy: it is manual-mapped but never initialised in this game — see
// docs/STEAM_HOOK.md). While the menu is open the proxies return neutral values
// (no keys, no raw input, no re-clip, cursor stays hidden); closed, each proxy
// forwards to the saved trampoline (the real function).
//
// Those hooks miss input that arrives as *window messages* (Unity reads mouse
// buttons from DispatchMessage -> WndProc), so install() also subclasses the
// game window and swallows input messages while the menu is up, and owns
// WM_SETCURSOR. The visible cursor is drawn by ImGui itself (io.MouseDrawCursor),
// which is why the OS cursor is forced hidden rather than shown.
//
// Our own overlay code (the SUPPR toggle, ImGui mouse buttons) must bypass the
// gate, so it calls real_async_key_state() instead of GetAsyncKeyState().

#pragma once

#include <cstdint>

namespace specter::overlay {
namespace game_input {

// Callback invoked (on the game's message thread) for every keyboard message
// the subclass swallows while the menu is open, so ImGui can still receive
// text input. Signatures use plain integers to keep Windows.h out of this
// header. The gate is temporarily lifted around the call so the callee sees
// the *real* key/modifier state (the Win32 ImGui backend reads GetKeyState).
using keyboard_sink = bool (*)(void* hwnd, unsigned msg, uintptr_t wparam,
                               intptr_t lparam);

// Install (or clear, with nullptr) the keyboard sink. Called once the ImGui
// context exists.
void set_keyboard_sink(keyboard_sink fn);

// Resolve user32 and detour the input/cursor exports. Call ONCE, when the menu
// pipeline is initialised. `hwnd` is currently unused (kept for a future window
// subclass). Returns true when the gate is armed (engine available + >=1 hook).
bool install(void* hwnd);

// Apply the menu state. Idempotent: called every frame from the render thread.
// While open the game's input is blocked and the OS cursor is released; closing
// restores exactly what was saved.
void set_menu_open(bool open);

// True once install() has actually armed the gate (engine ready + hooks in
// place). Callers can retry install() while this is false.
bool armed();

// Real, ungated GetAsyncKeyState (via the trampoline), so the overlay's own
// toggle/key handling keeps working while the gate is active. Falls back to the
// raw import when the gate is not armed.
short real_async_key_state(int vk);

}  // namespace game_input
}  // namespace specter::overlay
