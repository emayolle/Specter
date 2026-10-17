// Specter.Internal — game input gate for the overlay menu.
//
// WE DO NOT TOUCH THE CURSOR. See input.cpp for why the cursor hooks were
// removed; the short version is that ShowCursor's display counter is a STACK,
// not a boolean, so any save/restore was a reconstruction of Win32's bookkeeping
// against a game we do not control. The menu now draws a dot of its own and
// leaves the game's cursor entirely alone.
//
// What remains is the input gate, and it is here for one reason: without it a
// click inside the menu would pass through to the game and turn the character.
//
// The game reads input through user32.dll:
//   * GetRawInputData / GetRawInputBuffer  (raw keyboard/mouse, Input System)
//   * GetAsyncKeyState / GetKeyState       (polled legacy key state)
//   * and, for mouse buttons and keys, window messages (Unity reads them from
//     DispatchMessage -> WndProc)
//
// We detour the four polled exports with our own inline-detour engine
// (platform/hook/detour.*), a port of the Steam overlay's engine (we cannot call
// Steam's own copy: it is manual-mapped but never initialised in this game — see
// docs/STEAM_HOOK.md). While the menu is open the proxies return neutral values;
// closed, each proxy forwards to the saved trampoline (the real function).
//
// Because those hooks miss input that arrives as window messages, install() also
// subclasses the game window and swallows input messages while the menu is up.
//
// Our own overlay code (the SUPPR toggle, ImGui mouse buttons) must bypass the
// gate, so it calls real_async_key_state() instead of GetAsyncKeyState().

#pragma once

#include <cstdint>

namespace specter {
namespace input {

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


// THE MENU'S OWN CURSOR POSITION, in window-client pixels.
//
// Not the OS cursor: the game locks that one, so it does not move. This is fed
// by the raw-input deltas we already swallow, so the menu stays usable while the
// game keeps its mouse. False when the menu has never been positioned (the
// first frame), which is a position of "unknown", not of (0,0).
bool curseur_pos(int* x, int* y);

// Resolve user32 and detour the four INPUT exports. Call ONCE, when the menu
// pipeline is initialised. Returns true when the gate is armed (engine available
// + >=1 hook).
bool install(void* hwnd);

// Apply the menu state. Idempotent: called every frame from the render thread.
// While open the game's input is blocked. The cursor is NOT touched.
void set_menu_open(bool open);

// True once install() has actually armed the gate (engine ready + hooks in
// place). Callers can retry install() while this is false.
bool armed();

// Real, ungated GetAsyncKeyState (via the trampoline), so the overlay's own
// toggle/key handling keeps working while the gate is active. Falls back to the
// raw import when the gate is not armed.
short real_async_key_state(int vk);

}  // namespace game_input
}  // namespace specter::dxgi
