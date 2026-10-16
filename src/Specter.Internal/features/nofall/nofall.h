// Specter.Internal — no fall damage.
//
// WE DO NOT PATCH receiveFallToGroundDamage. We patch checkImmuneFallDamage,
// and that is strictly better.
//
// The game already has a fall-damage immunity, and it is a decision, not a
// value: `ClientSpace:checkImmuneFallDamage()` (ClientSpace.lua:1145) reads
// the scene's own flag, and two call sites consult it:
//
//     ClientDyingComponent:receiveFallToGroundDamage  -> the player and pet
//     ClientRobSpaceEgg                                -> the pet again
//
// So one patch on the decision covers BOTH call sites, adds no second
// mechanism beside the game's, and leaves the per-zone immunity alone.
//
// Patching the caller instead would have covered the same two cases by
// accident and cost a duplicate bypass of the game's own logic.
//
// WHY require() IS NOT ENOUGH
//
// Measured, not assumed:
//
//     require('...ClientDyingComponent') -> 11 keys, all metadata
//                                            (__Name2ComponentMethod__ ...)
//                                            and not one function
//     require('...ClientSpace')           -> the class, but the method sits
//                                            behind its metatable's __index
//
// And the same key lives in SEVERAL tables:
//
//     checkImmuneFallDamage       3 tables
//     receiveFallToGroundDamage   9 tables
//     changeStamina               1 table
//
// "Take the first one found" would patch a table nothing uses, and nothing
// would happen -- silently. scripts/init.lua therefore walks the reachable
// tables and patches every candidate. The walk is rawget-only (a `t[k]` would
// fire a proxy __index in this game) and costs 0.29 s, once per lua_State.
//
// The gate itself was measured in game before being written:
//
//     nofall ON  -> true
//     nofall OFF -> false
//
// WHY A CLASS PATCH
//
// Patching the class rather than the instance means the player, the pet and
// anything else covered by the same decision are all handled, and a relog
// cannot lose it: scripts/init.lua is replayed on every new state.
//
// WHY THE FLAG IS C++
//
// Exactly the stamina argument. The wrapper is installed ONCE per lua_State and
// reads `specter.var.nofall` at every call, so enabling and disabling is one
// store write with nothing to desynchronise.
//
// TURNING IT OFF
//
// The wrapper stays installed and becomes a pass-through, exactly like the
// stamina one: no window where the game is left half-patched.
//
// STILL UNKNOWN
//
// The damage request is an RPC to the server
// (`RPC_CS_SpecialDamage`). If the server validates landings itself, patching
// the client call will not be enough. Only jumping in game answers that.

#pragma once

namespace specter::features {
namespace nofall {

// The gate, as an ADDRESS, for the binding layer to hand to Lua as
// `specter.var.nofall`.
//
// Not `enabled()`: the checkbox needs a bool, the property needs the variable
// itself, so that reading and writing land on the same storage.
bool* flag();

bool set_enabled(bool on);
bool enabled();

void draw_ui();

}  // namespace nofall
}  // namespace specter
