// Specter.Internal — what Lua is allowed to see of ours.
//
// THE RULE: everything we expose lives in `specter`, and `specter` lives in
// our sandbox environment. Nothing is ever added to the game's _G.
//
// That is not a style preference, it is a measured property. On 2026-10-15 the
// leak sweep over the game's ~236 globals returned, for the env, the store and
// the specter table: 0, 0, 0. Registration must keep it that way, and
// getNamespaceFromStack is what does it — getGlobalNamespace is the one call in
// LuaBridge that would break it.
//
// Two things make that stick rather than merely intended:
//
//   - install() REFUSES when the C API is not fully bound. Registering against
//     unbound pointers builds bindings that trap on call, and the crash would
//     land in the game with nothing pointing here.
//   - the layer exposes a deliberately small, named surface. Every entry is a
//     line in bind.cpp, where a reviewer can see it.

#pragma once

#include "lua/capi.h"

namespace specter::lua::bind {

// Register the binding layer into the `specter` table.
//
// `specter_idx` is a stack index on L, as the caller found it. install() pushes
// and pops its own temporaries and leaves the stack exactly as it received it —
// checked at the boundary, because a binding layer that leaks one value shifts
// every index above it.
//
// Returns false, having registered nothing, when the layer is unavailable.
bool install(lua_State* L, int specter_idx);

}  // namespace specter::lua::bind