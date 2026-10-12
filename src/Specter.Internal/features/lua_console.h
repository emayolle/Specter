// Specter.Internal — Lua console bridge.
//
// The whole gameplay layer of Aniimo (attributes, stamina, abilities, UI state)
// lives in Lua, not C#. To reach it we run code inside the game's own Lua state
// and on the game's own Lua thread:
//
//   * the LuaJIT 5.1 C API is exported by `xlua.dll`
//     (luaL_loadbuffer / lua_pcall / lua_gettop / lua_settop / lua_tolstring ...);
//   * the state pointer is reached the documented xLua way:
//       LuaManager.luaenv (@0x18) -> LuaEnv.rawL (@0x10);
//   * the state is only ever touched from the thread that runs Lua, so we
//     detour `LuaManager.CommonUpdate` (per-frame, main thread) and use it as a
//     pump: queued chunks from the UI are drained and executed there, never on
//     the render thread.
//
// This module therefore exposes a thread-safe "submit a chunk / poll the
// result" pair; the ImGui panel is just one client of it.

#pragma once

namespace specter::features {
namespace lua {

// Resolve xlua.dll's Lua C API and detour LuaManager.CommonUpdate. Called once
// from specter::start() (on the hidden worker thread). Safe to call again: the
// hook is installed at most once, and a missing xlua.dll is retried later from
// the pump. Returns true once the CommonUpdate hook is in place.
bool install();

// True once we have observed a live lua_State on the game's Lua thread.
bool ready();

// Queue `len` bytes of Lua to run on the game's Lua thread. Any chunk queued
// but not yet drained is replaced. Returns false if the hook is not installed.
bool submit(const char* code, int len);

// Copy the newest result into `out` (NUL-terminated, capacity `cap`). Returns
// false when no fresh result is pending; `*out_ok` reports whether the chunk
// ran without error. Single consumer (the render thread).
bool take_result(char* out, int cap, bool* out_ok);

// One-line, human-readable bridge status for the UI.
const char* status();

// Number of CommonUpdate ticks observed (liveness for the UI).
unsigned long long ticks();

// Opt-in "infinite movement stamina" (sprint/dash/glide/climb). While enabled,
// the game's own `actorCombatAttribute.changeStamina` is hooked (on the
// player's instance): negative deltas — the movement costs — are swallowed and
// stamina is pinned to max once at install time, through the game's own
// attribute API (so the HUD and stamina change notifications keep firing). The
// installer is re-run silently by the pump every ~10 s to re-hook a fresh
// entity/attribute object after a relog. Scope is the player's stamina only;
// unlike Const.NO_COST_MODE it does not also disable skill or water costs.
// Returns false if the bridge hook is not installed.
bool set_infinite_stamina(bool on);
bool infinite_stamina();

}  // namespace lua
}  // namespace specter::features
