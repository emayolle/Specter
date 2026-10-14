// Specter.Internal — the Lua thread pump.
//
// WHY: the game's Lua state belongs to the game's Lua thread. It is driven by
// LuaManager.CommonUpdate, which we detour; that per-frame call is the only
// moment we are *on* the Lua thread, and therefore the only moment we may call
// into the Lua C API. Calling from the render thread would unwind through
// unrelated frames (LuaJIT signals errors with longjmp) and the state is not
// thread safe to begin with.
//
// So this module owns three things and nothing else:
//   * the inline detour on LuaManager.CommonUpdate;
//   * discovery of the live lua_State (LuaManager.luaenv -> LuaEnv.rawL);
//   * the C API, resolved from xlua.dll by GetProcAddress.
//
// It deliberately knows nothing about any feature. Features register a hook
// (add_state_hook for "a new state appeared", add_tick_hook for "the Lua thread
// is idle") and do their own work there. The pump drains for whoever registered;
// it has no channels of its own.
//
// Everything runs on the Lua thread. Cross-thread transport is lua/mailbox.h.

#pragma once

namespace specter::lua {
namespace pump {

// The live lua_State*, or nullptr. Valid only on the Lua thread — that is, only
// inside a state or tick hook.
void* state();

// Run once for every new lua_State*, on the Lua thread. The game recreates the
// state on scene reload / re-login, so anything published into it must be
// re-published here rather than once at startup. Permanent, process-wide.
using state_fn = void (*)(void* L);
bool add_state_hook(state_fn fn);

// Run on every tick, on the Lua thread, after the state hooks. This is where a
// feature drains its own mailbox and runs whatever it queued.
using tick_fn = void (*)(void* L);
bool add_tick_hook(tick_fn fn);

// Register a filter consulted before each chunk we inject. Returning true means
// "this chunk is ours, do not surface it". Exists so a feature can keep its own
// chunks out of its own capture without `lua/` having to know that any feature
// exists — the dependency stays feature -> lua, never lua -> features.
using chunk_filter_fn = bool (*)(const char* chunk_name);
void set_chunk_filter(chunk_filter_fn fn);

// Runs a chunk on the Lua thread and captures whatever it printed. `sink` is
// called with the captured output, or with nullptr to discard it (the "silent"
// path). Always leaves the stack as it found it.
using result_sink = void (*)(bool ok, const char* text, int len);
void run(void* L, const char* code, int len, result_sink sink);

// Resolve the Lua C API and install the CommonUpdate detour. Called once from
// specter::start(). Idempotent; a missing xlua.dll is retried from the pump.
// Returns true once the detour is in place.
bool install();

// True once a live lua_State has been observed on the Lua thread.
bool ready();

// CommonUpdate ticks observed — liveness for the UI.
unsigned long long ticks();

// One-line status for the UI.
const char* status();

}  // namespace pump
}  // namespace specter::lua