// Specter.Internal — infinite movement stamina. DISABLED, NOT BUILT.
//
// WHY: running Lua is currently permitted through exactly one path — the
// Execute button in the Lua Editor (see features/console/). This feature needs
// Lua to run on its own: the toggle submits an installer chunk, and the pump
// silently re-submits it every ~10 s to re-hook a fresh entity after a relog.
// Neither is a person pressing Execute, so the feature is parked.
//
// The code is kept verbatim so it can come back without being rewritten. It is
// NOT listed in tools/build-dll.sh nor in Specter.Internal.vcxproj, so it is
// not compiled and cannot run.
//
// TO RE-ENABLE:
//   1. decide whether re-submitting Lua without the user asking is acceptable
//      (see docs/PLAN.md, invariant 3 — a question that is still open);
//   2. if yes, move the installer into the Lua layer instead of a C++-side
//      chunk: patch the CLASS (ActorCombatAttribute.changeStamina), gate on a
//      flag read at call time, and drop the ~10 s maintenance entirely. That was
//      verified in game on 2026-10-14: require("Common.Ability.Attribute."
//      "ActorCombatAttribute") returns exactly the shared metatable
//      (AC == getmetatable(aca), mt.__index == mt), so one class patch covers
//      every present and future instance with no polling and no relog case;
//   3. add the TU back to the build and the toggle back to the UI.

    run_chunk(L, code, n);
}

// ---- infinite movement stamina (opt-in) ------------------------------------
//
// Sandbox discovery: chunks submitted to this bridge run in the game's
// sandboxed Lua environment. Reads of existing globals (pg, package.loaded, …)
// fall through to the real global table, but **writes** (even `_G.foo = …`)
// land in a per-chunk shadow and never reach the real _G. That is exactly why
// the first attempt — an install chunk defining `__SpecterStaminaTick` and a
// pump-side `lua_getglobal` + pcall per frame — silently did nothing.
//
// The robust lever is a per-instance method hook: assigning
// `actorCombatAttribute.changeStamina` on the player's instance shadows the
// metatable method for that object only. Instance field writes are ordinary
// writes on a live object, so they stick regardless of the sandbox. Movement
// costs (sprint/dash/glide/climb) all funnel through ClientStaminaComponent →
// `actorCombatAttribute:changeStamina(-cost)`; swallowing those negative
// deltas is "infinite stamina" at the source, and it does not race the game's
// per-frame drain (a pre-update refill would just be undone later in the
// frame).
//
// IMPORTANT (freeze fix): do NOT pin stamina with setAttribute() on every
// drain — each call runs the game's full attribute-change pipeline
// (recalc + HUD notifications + event dispatch) and stutters the frame. The
// hook swallows drains with a bare `return true` (nanoseconds), and stamina is
// pinned to max exactly ONCE when the hook is (re)installed.
//
// The toggle state lives in C++ (g_inf_stamina):
//   * ON  -> queue the idempotent installer (silently). The pump also re-runs
//            it silently every ~10 s so a fresh entity/aca after a relog gets
//            re-hooked. Stamina is pinned to max once at install time.
//   * OFF -> queue the restorer that puts the metatable method back.
// The silent path means none of this touches out.txt / the seq counter, so the
// CLI channel is never disturbed by maintenance traffic.

constexpr char kStaminaInstall[] =
    R"lua(local ent
for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do ent=_v break end
if not ent then return end
local aca=ent.actorCombatAttribute
if not aca then return end
local AC=package.loaded['Common.Const.AttributeConst']
if not AC then return end
if not aca.__SpecterHooked then
  local orig=aca.changeStamina
  if type(orig)~='function' then return end
  aca.changeStamina=function(self,delta)
    if delta and delta<0 then return true end
    return orig(self,delta)
  end
  aca.__SpecterHooked=true
end
local mx=aca:getMaxStamina()
if mx and mx>0 and aca:getAttribValue(AC.stamina_cur)<mx then
  aca:setAttribute(AC.stamina_cur,mx)
end
)lua";

constexpr char kStaminaDisable[] =
    R"lua(local ent
for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do ent=_v break end
if not ent then return end
local aca=ent.actorCombatAttribute
if not aca then return end
local mt=getmetatable(aca)
if mt and type(mt.changeStamina)=='function' then
  aca.changeStamina=mt.changeStamina
end
aca.__SpecterHooked=nil
)lua";

unsigned long long g_stamina_install_ticks = 0;  // Lua thread only

void pump(void* self)
{
    g_ticks.fetch_add(1, std::memory_order_relaxed);
    if (!resolve_xlua()) {
        return;

// ---- public surface (disabled) -------------------------------------------

bool set_infinite_stamina(bool on) { /* see the note above */ return false; }
bool infinite_stamina()           { return false; }
