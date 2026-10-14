// Specter.Internal — infinite movement stamina (sprint / dash / glide / climb).
//
// The game exposes the movement cost through one method:
// `actorCombatAttribute:changeStamina(-cost)`. Swallowing the negative deltas is
// "infinite stamina" at the source — before the cost is ever applied — and it
// does not race the per-frame drain the way a per-frame refill would.
//
// WHY A CLASS PATCH, NOT AN INSTANCE ONE
// An earlier version assigned `aca.changeStamina` on the player's own instance.
// That works, but it dies with the object: after a relog the game builds a new
// one and the patch is gone, which is why it needed a "re-apply every ~10 s"
// maintenance pass running Lua nobody asked for.
//
// Patching the CLASS instead fixes both problems at once. Verified in game on
// 2026-10-14:
//   * `require("Common.Ability.Attribute.ActorCombatAttribute")` returns
//     exactly the shared metatable of every actorCombatAttribute
//     (AC == getmetatable(aca), and mt.__index == mt);
//   * a patch on that class intercepts the real calls (the probe counter moved
//     while the player sprinted);
//   * putting it back restores the normal drain.
//
// So one patch per lua_State covers every present and future instance, needs no
// polling, and has no relog case: a new state is a new class, and the layer
// re-applies on demand when the toggle is next used.
//
// THE GATE
// The wrapper reads its flag at call time, so enabling and disabling is instant
// and costs no Lua at all. The flag lives in the sandbox store, which is ours —
// not a global of the game's.
//
//     gate OFF -> the wrapper calls the original, behaviour is identical
//     gate ON  -> negative deltas for the player return true, cost never applies
//
// Disabling leaves the wrapper in place on purpose: it becomes a pass-through,
// so there is no window where the game is left half-patched.

#pragma once

namespace specter::features {
namespace stamina {

// Register nothing and run nothing: this feature has no Lua to install, it only
// flips a flag. Returns true so the registry can treat it uniformly.
bool install();

// Turn the cheat on or off. Each call runs exactly one small chunk on the Lua
// thread — a deliberate user action, not a timer. Returns false if the pump is
// not reachable.
bool set_enabled(bool on);

// What set_enabled() last asked for. The menu reads this to draw the checkbox.
bool enabled();

// Draw the feature's own tab. The overlay does not know this feature exists: it
// calls whatever the registry hands it.
void draw_ui();

}  // namespace stamina
}  // namespace specter