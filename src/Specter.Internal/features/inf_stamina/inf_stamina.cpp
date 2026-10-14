// Specter.Internal — infinite movement stamina (implementation). See inf_stamina.h.

#include "pch-il2cpp.h"

#include "features/console/console.h"
#include "features/inf_stamina/inf_stamina.h"
#include "imgui.h"

#include <cstring>

namespace specter::features {
namespace stamina {
namespace {

// The flag lives in the sandbox store, so it is ours and not one of the game's
// globals. `specter` is injected into the sandbox environment and is invisible to
// the game's own scripts.
constexpr char kGate[] = "inf_stamina";

constexpr char kEnable[] =
    "specter.store.inf_stamina = true\n"
    "local AC = require('Common.Ability.Attribute.ActorCombatAttribute')\n"
    "if not rawget(AC, '__specterStaminaHooked') then\n"
    "  local orig = rawget(AC, 'changeStamina')\n"
    "  if type(orig) ~= 'function' then return 'changeStamina is not a function' end\n"
    "  rawset(AC, '__specterStaminaOrig', orig)\n"
    "  AC.changeStamina = function(self, delta)\n"
    "    local d = tonumber(delta)\n"
    "    if d and d < 0 and specter.store.inf_stamina then\n"
    "      local e = self and self.entity\n"
    "      if e == pg.me or e == pg.pawn or (e and e.isMainPlayer == true) then\n"
    "        return true\n"
    "      end\n"
    "    end\n"
    "    return orig(self, delta)\n"
    "  end\n"
    "  rawset(AC, '__specterStaminaHooked', true)\n"
    "end\n"
    "return 'stamina hooked'\n";

constexpr char kDisable[] = "specter.store.inf_stamina = false\nreturn 'stamina off'\n";

// Cached so the menu can draw the checkbox without going through the Lua thread.
bool g_enabled = false;

}  // namespace

bool install()
{
    // Nothing to do: the patch is applied on demand, when the user toggles it.
    // Registering it up front would mean running Lua nobody asked for.
    return true;
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