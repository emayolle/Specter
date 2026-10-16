// Specter.Internal — no fall damage.
//
// The game applies it in one place: `ClientDyingComponent:receiveFallToGroundDamage(height)`.
// It checks whether the space grants immunity, then asks the server for the
// damage:
//
//     if Utils.isPlayer(self) or Utils.isPlayerPet(self) then
//         if self.space and self.space:checkImmuneFallDamage() then return end
//         self:serverMsg("RPC_CS_SpecialDamage",
//                         Utils.calcFallToGroundDamage(height),
//                         Const.LIFE_DEAD_BY_FALL_TO_GROUND)
//     end
//
// So there is nothing to intercept further down: the function is the decision,
// and it decides once per landing.
//
// WHY A CLASS PATCH
//
// `require(...)` returns the shared metatable of every ClientDyingComponent —
// the same property `changeStamina` has for stamina — so patching the class
// covers the player, the pet and anything else that lands. Patching the
// player's own instance would die with the object on relog.
//
// WHY THE FLAG IS C++
//
// Exactly the stamina argument. The wrapper is installed ONCE per lua_State and
// reads `specter.var.nofall` at every call, so enabling and disabling is one
// store write with nothing to desynchronise. It used to be the other way
// round on other features: a field written on the game class by a posted chunk,
// plus a second bool in C++, kept in agreement by hand across a thread and
// across a relog.
//
// TURNING IT OFF
//
// The wrapper stays installed and becomes a pass-through, exactly like the
// stamina one: no window where the game is left half-patched.

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
