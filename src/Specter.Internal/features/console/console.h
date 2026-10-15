// Specter.Internal — running Lua chunks, and the channels they travel on.
//
// One deliberate way to run Lua from the menu: the Execute button in the Lua
// Editor. Features that need to run a chunk of their own use a *channel* here —
// same machinery, a different slot, so their traffic never lands in the console
// log and never disturbs an in-flight console run.
//
// What was extracted out of this module, and where it went:
//
//   the CommonUpdate detour, state discovery, C API   -> lua/pump.h
//   the cross-thread transport                         -> lua/mailbox.h
//   the runtime chunk dumper                           -> features/lua_dump/
//
// Every chunk, whatever it comes from, is executed by exactly one call site —
// lua::pump::run() — inside a per-run sandbox environment (see pump.cpp for the
// read/write policy).

#pragma once

namespace specter::features::console {

// Which lane a chunk travels in. Each channel has its own queue and its own
// result slot, so a position probe never shows up as console output and never
// clobbers a teleport that has not run yet.
//
// The count is fixed and the tables are zero-initialised: no constructor runs at
// load time (the image is manually mapped, the CRT guard is not set up).
enum Channel {
    kChannelConsole = 0,  // the Execute button
    kChannelTeleport = 1, // position probe + move
    kChannelStamina = 2, // install / restore the cost hook
    kChannelCli = 3,      // shell requests, only inside an armed window
    kChannelInit = 4,     // scripts/init.lua, once per new lua_State
    kChannelCount = 5,
};

// Register the drain hooks with the Lua pump. Called once from specter::start().
// Nothing here runs Lua by itself.
bool install();

// True once the pump has a live lua_State to drain into.
bool ready();

// Queue `len` bytes of Lua on the game's Lua thread for `ch`. Returns false if
// the pump is not up yet. A queued chunk not yet drained is replaced by the next
// one — the user wants the last thing they asked for, not a backlog.
bool submit(Channel ch, const char* code, int len);

// Copy the newest captured output for `ch` into `out` (NUL-terminated, capacity
// `cap`). Returns false when nothing fresh is pending; `*out_ok` reports whether
// the chunk ran without error. Single consumer: the render thread.
bool take_result(Channel ch, char* out, int cap, bool* out_ok);

// Append a line to the console's visible log, from anywhere. Used by features
// to report why an action failed (the button was pressed, but the pump is down)
// without the UI layer having to own a log of its own.
void note(const char* text);

// One-line, human-readable bridge status for the UI.
const char* status();

// Open the shell channel. It is OPEN AT LOAD: the checkbox in the Lua Editor
// tab closes it, and that is all it does.
//
// This reverses an earlier decision, and the reason is in console.cpp: a
// development channel on the operator's own machine, injected by hand, is not
// worth a checkbox that has to be re-armed every session — a control nobody
// reads is not a control. What it costs is written down there; what it buys is
// that every execution is mirrored to the host log.
void arm_cli();

// Draw the console's tab. Called every frame from inside the tab the registry
// gave us, on the render thread.
//
// The feature owns its editor buffer and its output log: the overlay used to
// hold both, which meant the UI layer had to know about the console's internals
// just to display them. It also drains the captured result here, since that is
// the only thing that consumes it.
void draw_ui();

}  // namespace specter::features::console