// Specter.Internal — the Lua console.
//
// One deliberate way to run Lua: the Execute button in the Lua Editor tab.
//
// This module used to be the whole Lua bridge — the CommonUpdate detour, the
// transport, the teleport channel, the infinite-stamina chunks and a
// filesystem-triggered CLI all lived here, which is why it was 808 lines and why
// the pump sat inside a feature. Those pieces now live where they belong:
//
//   the detour + state + C API   -> lua/pump.h
//   the cross-thread transport   -> lua/mailbox.h
//   the runtime chunk dumper     -> features/lua_dump/
//
// What is left is a feature: a queue of chunks, a captured result, and the
// print-mirroring that makes it readable in the terminal.
//
// Note there is exactly ONE entry point here, submit(), and its only caller is
// the Execute button. There is no polling, no maintenance and no timer: nothing
// in this module runs Lua unless a person pressed Execute.

#pragma once

namespace specter::features::console {

// Register the console's tick hook with the Lua pump. Called once from
// specter::start(). Nothing here runs Lua by itself; it only makes the console
// ready to carry what the user asked for.
bool install();

// True once the pump has a live lua_State to drain into.
bool ready();

// Queue `len` bytes of Lua for execution on the game's Lua thread. Returns false
// if the pump is not up yet. A queued chunk not yet drained is replaced by the
// next one — the user wants the last thing they typed, not a backlog.
bool submit(const char* code, int len);

// Copy the newest captured output into `out` (NUL-terminated, capacity `cap`).
// Returns false when nothing fresh is pending; `*out_ok` reports whether the
// chunk ran without error. Single consumer: the render thread.
bool take_result(char* out, int cap, bool* out_ok);

// One-line, human-readable bridge status for the UI.
const char* status();

// Draw the console's tab. Called every frame from inside the tab the registry
// gave us, on the render thread.
//
// The feature owns its editor buffer and its output log: the overlay used to
// hold both, which meant the UI layer had to know about the console's internals
// just to display them. It also drains the captured result here, since that is
// the only thing that consumes it.
void draw_ui();

}  // namespace specter::features::console