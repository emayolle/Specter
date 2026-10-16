// Specter.Internal — no fall damage (implementation). Design in nofall.h.

#include "pch-il2cpp.h"

#include "features/nofall/nofall.h"
#include "imgui.h"

namespace specter::features {
namespace nofall {
namespace {

// THE flag, and the only one.
//
// Read by Lua through `specter.var.nofall` at every landing, written by the
// checkbox. Nothing else stores it, and nothing on the game's side stores a
// copy — the wrapper asks on each call.
bool g_enabled = false;

}  // namespace

bool* flag()
{
    return &g_enabled;
}

bool set_enabled(bool on)
{
    g_enabled = on;
    return true;
}

bool enabled()
{
    return g_enabled;
}

void draw_ui()
{
    bool on = g_enabled;
    if (ImGui::Checkbox("No fall damage", &on)) {
        set_enabled(on);
    }
    ImGui::SameLine();
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Patches receiveFallToGroundDamage on the ClientDyingComponent "
            "CLASS, so every instance is covered and a relog cannot lose it. "
            "The game already has an immunity path of its own "
            "(space:checkImmuneFallDamage); this one does not depend on where "
            "you are. Turning it off restores the normal behaviour immediately "
            "\u2014 the patch stays installed and becomes a pass-through.");
    }
}

}  // namespace nofall
}  // namespace specter
