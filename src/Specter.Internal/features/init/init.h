// Specter.Internal — scripts/init.lua, run once per new lua_State.
//
// WHAT IT IS FOR
//
// Things that are easier to write in Lua than in C++, but that must survive a
// reconnect. A patch on a game table, a per-session state machine, an aura that
// reinstalls itself: all of it belongs in a script that the pump replays every
// time a new lua_State appears, instead of a chunk baked into a C++ constant
// with a flag to carry state across a relog.
//
// THE STAMINA HOOK IS THE EXAMPLE. It used to be a C++ chunk string submitted
// on a channel, with its gate in TWO places — a bool in C++ and a field on the
// game's class, kept in agreement by hand. In scripts/init.lua there is one
// gate (`specter.var.stamina`, read in C++ and written by the checkbox) and no
// C++ at all, and the patch re-installs itself on every state for free.
//
// WHY EMBEDDED, NOT READ FROM DISK
//
// No path to get wrong on the game's side, no file IO on the Lua thread while a
// state is being built, and nothing that can go missing between build and run.
// Same technique nova uses for its InitScript. tools/embed-lua.sh regenerates
// generated/lua_init.h from scripts/init.lua; build-dll.sh runs it.
//
// THE CONTRACT THE SCRIPT CAN RELY ON
//
//   - it runs INSIDE the sandbox, the same environment the overlay's Lua Editor
//     gets, so `specter.store`, `specter.var.*` and `specter.log` are there;
//   - it runs ONCE per lua_State, so a reconnect replays it;
//   - it runs BEFORE any player interaction: `pg.me` may not exist yet, so ask
//     rather than assume, or defer to the first tick;
//   - and it never has to touch the game's globals. A new name written here
//     goes into our store; putting something ON a game table is a deliberate,
//     visible act.

#pragma once

namespace specter::features::init {

// Register the state hook. Runs nothing by itself: the pump calls it when a
// lua_State it has not seen appears.
bool install();

}  // namespace specter::features::init
