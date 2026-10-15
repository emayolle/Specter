// Specter.Internal — infinite movement stamina (sprint / dash / glide / climb).
// See inf_stamina.h for the design.

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

// THE flag.
//
// Read by Lua through `specter.var.stamina` — the binding layer hands Lua this
// bool's address — and written by the checkbox. One storage, one truth.
//
// It used to live the other way round: a field on the game class, set by a chunk
// that the toggle posted. Two copies of one truth on two sides of a thread, and
// a relog able to desynchronise them. See the header.

constexpr char kInstall[] =
    "local AC = require('Common.Ability.Attribute.ActorCombatAttribute')\n"
    "if type(rawget(AC, 'changeStamina')) ~= 'function' then\n"
    "  return 'changeStamina is not a function'\n"
    "end\n"
    "if not rawget(AC, '__specterStaminaHooked') then\n"
    "  local orig = rawget(AC, 'changeStamina')\n"
    "  local w\n"
    "w = function(self, delta)\n"
    "  local d = tonumber(delta)\n"
    // The gate, read at CALL time from C++. This one line is the whole change:
    // no field on the class, no chunk to toggle, no second copy of the flag.
    "  if d and d < 0 and specter.var.stamina then\n"
    "    local e = self and self.entity\n"
    "    if e == pg.me or e == pg.pawn or (e and e.isMainPlayer == true) then\n"
    "      return true\n"
    "    end\n"
    "  end\n"
    "  return orig(self, delta)\n"
    "end\n"
    "rawset(AC, '__specterStaminaOrig', orig)\n"
    "AC.changeStamina = w\n"
    "rawset(AC, '__specterStaminaHooked', true)\n"
    "end\n"
    "return 'stamina hooked'\n";

// Cached so the menu can draw the checkbox without going through the Lua thread.
// It IS g_enabled — not a copy of it. Two copies is what this change removed.
bool g_enabled = false;

// Installed once per lua_State, whatever the flag says. A relog rebuilds the
// class the patch lived on, so this is the one thing that has to be re-done —
// and nothing else: the flag is a C++ bool that survives the relog by itself, so
// there is nothing to copy across and nothing that can disagree.
//
// Idempotent on the Lua side: `__specterStaminaHooked` guards it.
void on_new_lua_state(void* L)
{
    if (L == nullptr) {
        return;
    }
    console::submit(console::kChannelStamina, kInstall,
                    static_cast<int>(std::strlen(kInstall)));
}

}  // namespace

bool install()
{
    // Register the recovery hook, nothing else. No Lua runs here: the patch is
    // installed when the Lua state appears, which is also when the sandbox
    // environment — and therefore `specter.var.stamina` — is created. Installing
    // before that would read a name that does not exist yet.
    return lua::pump::add_state_hook(&on_new_lua_state);
}

bool* flag()
{
    return &g_enabled;
}

bool set_enabled(bool on)
{
    // One store write. No chunk, no Lua, no thread hop, nothing to fail: the
    // checkbox changes a bool and the wrapper reads it on the next call.
    g_enabled = on;
    return true;
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
}  // namespace specter