// Specter.Internal — infinite movement stamina (implementation). See inf_stamina.h.

#include "pch-il2cpp.h"

#include "features/console/console.h"
#include "features/inf_stamina/inf_stamina.h"
#include "lua/pump.h"
#include "platform/log.h"
#include "imgui.h"

#include <cstring>

namespace specter::features {
namespace stamina {
namespace {

// The gate is a FIELD ON THE PATCH ITSELF, not a flag in the sandbox store.
//
// It used to be `specter.store.inf_stamina`, which was correct while the store
// was keyed in the Lua registry. Removing the registry (the only index we could
// guess wrote through a wild pointer) made the store per-Execute, and that broke
// the toggle in both directions:
//
//   ON  in run N   -> sets the flag on run N's store
//   OFF in run N+1 -> sets the flag on run N+1's store, a DIFFERENT table
//
// The wrapper kept reading run N's store, where the flag was still true. So
// turning stamina off did nothing at all.
//
// The flag lives on the CLASS TABLE, not on the wrapper function -- and that is
// not a style choice. Measured in game: this build does NOT ship the standard
// rawset. The rawset in _G is a wrapper that rejects anything that is not a
// table ("bad argument #1 to 'raw_rawset' (table expected, got function)"),
// while every other library function checked -- rawget, setmetatable, pcall,
// select, tostring, table.concat, table.remove, type -- behaves normally.
//
// So the gate is a field on `AC`, the shared class metatable, which is exactly
// the object the patch is installed on: a TABLE, which this rawset accepts.
//
// (An own rawset/rawget in C was tried and withdrawn: two functions whose whole
// job is to be raw were the most crash-prone thing in the build. See git.)
//
// A field on AC cannot drift either: the wrapper closes over AC, so the copy it
// reads is the copy the toggle writes.

// `w` is referenced inside its own body, so it must be named before assignment.
constexpr char kEnable[] =
    "local AC = require('Common.Ability.Attribute.ActorCombatAttribute')\n"
    "if type(rawget(AC, 'changeStamina')) ~= 'function' then\n"
    "  return 'changeStamina is not a function'\n"
    "end\n"
    "if not rawget(AC, '__specterStaminaHooked') then\n"
    "  local orig = rawget(AC, 'changeStamina')\n"
    "  local w\n"
    "  w = function(self, delta)\n"
    "    local d = tonumber(delta)\n"
    "    if d and d < 0 and rawget(AC, '__specterStaminaOn') then\n"
    "      local e = self and self.entity\n"
    "      if e == pg.me or e == pg.pawn or (e and e.isMainPlayer == true) then\n"
    "        return true\n"
    "      end\n"
    "    end\n"
    "    return orig(self, delta)\n"
    "  end\n"
    "  rawset(AC, '__specterStaminaOrig', orig)\n"
    "  AC.changeStamina = w\n"
    "  rawset(AC, '__specterStaminaHooked', true)\n"
    "end\n"
    "rawset(AC, '__specterStaminaOn', true)\n"
    "return 'stamina hooked'\n";

constexpr char kDisable[] =
    "local AC = require('Common.Ability.Attribute.ActorCombatAttribute')\n"
    "if rawget(AC, '__specterStaminaHooked') then\n"
    "  rawset(AC, '__specterStaminaOn', false)\n"
    "end\n"
    "return 'stamina off'\n";

// Cached so the menu can draw the checkbox without going through the Lua thread.
bool g_enabled = false;

// A relog rebuilds the Lua state, and with it the class table the patch was
// installed on. The checkbox would stay lit and mean nothing. So on every new
// state, if the user had it on, put it back on — and say so, because a toggle
// that silently repairs itself is worse than one that visibly drops.
void on_new_lua_state(void* /*L*/)
{
    if (!g_enabled) {
        return;
    }
    log::info("stamina: nouvel etat Lua -- le patch etait mort avec la classe, "
              "il est reposte");
    g_enabled = false;  // so set_enabled() below is not short-circuited
    set_enabled(true);
}

}  // namespace

bool install()
{
    // The patch itself is applied on demand, when the user toggles it: running
    // Lua at startup would be running Lua nobody asked for.
    //
    // What IS registered here is the recovery hook, because a new lua_State
    // means the class the patch lived on has just been rebuilt from scratch.
    return lua::pump::add_state_hook(&on_new_lua_state);
}

bool set_enabled(bool on)
{
    const bool was = g_enabled;
    g_enabled = on;
    if (was == on) {
        return true;  // idempotent: no Lua run for a no-op toggle
    }
    const char* code = on ? kEnable : kDisable;
    return console::submit(console::kChannelStamina, code,
                           static_cast<int>(std::strlen(code)));
}

bool enabled()
{
    return g_enabled;
}

void draw_ui()
{
    bool inf = g_enabled;
    if (ImGui::Checkbox("Infinite movement stamina\n"
                        "(sprint / dash / glide / climb)",
                        &inf)) {
        set_enabled(inf);
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Patches the player's stamina cost function (changeStamina) on "
            "its CLASS, so every instance is covered and a relog cannot lose "
            "it. Movement costs are swallowed; stamina is not re-pinned every "
            "frame, which is what used to stutter. Turning it off restores the "
            "normal behaviour immediately.");
    }
}

}  // namespace stamina
}  // namespace specter::features