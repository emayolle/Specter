// Specter.Internal — Lua on its own OS thread, in its own Lua universe.
//
// WHY THIS EXISTS
//
// Measured, in game: one coroutine resuming a 150M-iteration loop took 2.055 s
// and the game's own TimerManager fired ZERO times while it ran. A lua_State is
// one stack on one thread; the game's state is driven by the game's Lua thread.
// So anything that runs on the game's state and does not return in bounded time
// freezes the game, coroutine or not. `coroutine.yield` bounds it. Nothing else
// does.
//
// A worker sidesteps the problem instead of bounding it: a SEPARATE OS thread
// with a SEPARATE lua_State. It can burn three seconds and the game does not
// know it exists.
//
// WHAT A WORKER CANNOT DO — and this is not negotiable
//
// It cannot touch the game. Its _G is a fresh universe: no `require`, no `pg`,
// no game module, no shared table. The game's state and its _G belong to the
// game's thread, and sharing one state across threads is undefined behaviour in
// Lua and in LuaJIT alike. So a worker is for COMPUTATION — scanning, parsing,
// decrypting, crunching a table you copied in. It is not a way to cheat faster.
//
// The only shared surface is what we choose to share: `specter.var.*` (our own
// C++ scalars, by value) and whatever the worker posts back.
//
// THE KILL IS COOPERATIVE, AND IT HAS TO BE
//
// `kill` sets a flag; the worker notices it at its next `specter.sleep()`. We do
// not TerminateThread. A thread killed in the middle of lua_pcall may be inside
// our own allocator, and freeing the image out from under it turns a hung worker
// into a crash at the worst possible moment.
//
// The price is one line in the loop:
//
//     while true do step(); specter.sleep(0) end   -- sleep(0) is a yield + check
//
// A worker that never calls sleep cannot be killed, and shutdown() will say so
// rather than pretend. That is the same price as coroutine.yield, bought back
// with a thread.

#pragma once

#include "lua/capi.h"

namespace specter::lua::worker {

// Run `code` on its own thread, in its own lua_State. `code` is Lua source (or
// LuaJIT bytecode produced by string.dump — the worker state comes from the same
// xlua.dll, so it is the same version).
//
// Returns a handle >= 0, or -1 with last_error() saying why.
int spawn(const char* code, int len, const char* meta, int meta_len);

// Ask the worker to raise at its next specter.sleep(). Returns false if the
// handle is unknown or already finished.
bool kill(int h);

// Wait for the worker to finish. Cooperative: it returns when the body ends or
// after a kill lands, and gives up after `timeout_ms` rather than hanging the
// caller forever. Returns true if the thread actually finished.
bool join(int h, unsigned timeout_ms = 5000);

// "free" | "starting" | "running" | "kill asked" | "done" | "killed" | "error".
const char* status(int h);

// Why the worker finished. Empty while it runs, and after a clean return.
//
// This exists because a worker's syntax error CANNOT be reported by spawn: the
// chunk is compiled inside the worker, in the worker state, long after spawn has
// already returned a handle. Without this, a typo looks exactly like success.
const char* error(int h);

// Why the last spawn() or kill() refused. Empty when there was no refusal.
const char* last_error();

// How many slots are in use. The cap is deliberately small: a worker is a thread
// with its own Lua heap, and a script that can spawn them should not be able to
// fill the machine.
int alive();

// Kill and join every slot. Called from specter::stop(). A worker still running
// after the timeout is logged loudly and left alone rather than killed mid-lua.
void shutdown();

// Publish `specter.thread` into the `specter` table at `specter_idx`.
// Called from bind::install, on the Lua thread, once per environment.
//
//     local h = specter.thread.spawn(function() ... end)  -- or a source string
//     specter.thread.status(h)   -- 'running' | 'done' | 'killed' | 'error'
//     specter.thread.kill(h)     -- cooperative: lands at the next sleep()
//     specter.thread.join(h)     -- wait, with a timeout
//     specter.thread.alive()     -- how many slots are in use
//
// The function form is dumped to LuaJIT bytecode with string.dump and loaded in
// the worker's state — which works because the worker state comes from the same
// xlua.dll, so it is the same LuaJIT. A function with UPVALUES is refused: they
// belong to the game's state and would arrive as nil, so the failure would show
// up as a nil somewhere deep in the body instead of here.
bool register_api(lua_State* L, int specter_idx);

}  // namespace specter::lua::worker