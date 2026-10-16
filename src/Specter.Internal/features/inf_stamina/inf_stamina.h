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
// So one patch per lua_State covers every present and future instance, and needs
// no polling: a new state is a new class, and the patch is laid again when the
// state is.
//
// WHERE THE PATCH LIVES NOW: scripts/init.lua, NOT HERE
//
// It used to be a 35-line Lua chunk in a C++ constant, submitted on a channel
// every time a lua_State appeared. That was correct and it was also the last
// thing standing between us and a normal build.
//
// The log showed both running, every session:
//
//     lua| stamina hooked                              <- le chunk C++
//     lua| [init] stamina : patch posé sur la classe   <- Init.lua
//
// Which means `changeStamina` was wrapped TWICE — a wrapper around a wrapper,
// so every stamina change cost two Lua calls instead of one. Not fatal, not
// visible, and exactly the kind of thing that survives for months because
// nothing is wrong. Two installers of the same patch is one too many, so the C++
// one is gone and the file says why.
//
// The header used to promise "the layer re-applies on demand". It re-applies on
// EVERY new state, from the bootstrap, with no C++ involved. That is the whole
// point of having a bootstrap: a thing that must survive a relog belongs in a
// file that is replayed, not in a chunk a DLL remembers to send.
//
// So this module is now exactly three things: the gate, the checkbox, and the
// getter the binding layer needs. No Lua, no state hook, no channel.
//
// THE GATE
//
// The flag is a C++ bool, and it is read at call time through the binding layer:
// `specter.var.stamina`. Enabling and disabling is therefore one store — there is
// no second copy of the truth in Lua, which is what this used to be.
//
//     gate OFF -> the wrapper calls the original, behaviour is identical
//     gate ON  -> negative deltas for the player return true, cost never applies
//
// Disabling leaves the wrapper in place on purpose: it becomes a pass-through,
// so there is no window where the game is left half-patched. The patch is
// installed ONCE per lua_State whatever the flag says, and the flag decides —
// which is why the gate has to be a C++ variable the bootstrap can READ, and not
// something Lua owns.
//
// Why it moved off `AC.__specterStaminaOn`: the toggle used to post a chunk that
// wrote a flag on the game class, and the checkbox kept a second bool in C++.
// Two copies of one truth, on two sides of a thread, with a relog able to
// desynchronise them. The binding layer removes the seam entirely — Lua reads
// the same bool the checkbox writes.

#pragma once

namespace specter::features {
namespace stamina {

// The gate itself, as an ADDRESS, for the binding layer to hand to Lua.
//
// Not `enabled()`: the checkbox needs a bool, but `specter.var.stamina` needs the
// variable itself so that reading and writing go to the same storage. A getter
// plus a setter would reintroduce the two-copies problem this change removes.
bool* flag();

// Turn the cheat on or off. Writes the flag and nothing else — no chunk, no Lua,
// no thread hop. Safe to call from the UI thread, which is where the checkbox
// calls it from.
bool set_enabled(bool on);

// What the flag says. The menu reads this to draw the checkbox.
bool enabled();

// Draw the feature's own tab. The overlay does not know this feature exists: it
// calls whatever the registry hands it.
void draw_ui();

}  // namespace stamina
}  // namespace specter