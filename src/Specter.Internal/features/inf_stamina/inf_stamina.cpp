// Specter.Internal — infinite movement stamina (sprint / dash / glide / climb).
// See inf_stamina.h for the design.

#include "pch-il2cpp.h"

#include "features/inf_stamina/inf_stamina.h"
#include "imgui.h"
#include "render/ui_widgets.h"

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

// Cached so the menu can draw the checkbox without going through the Lua thread.
// It IS g_enabled — not a copy of it. Two copies is what this change removed.
// ACTIVE PAR DEFAUT.
//
// Sans piege, meme raison que nofall : le patch de changeStamina est pose une
// fois, mais la porte `specter.var.stamina` est relue a chaque modification
// d'endurance (init.lua:141). Decocher, c'est immediat.
bool g_enabled = true;

}  // namespace

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
    if (ImGui::Checkbox("Infinite movement stamina (sprint / dash / glide / climb)",
                        &inf)) {
        set_enabled(inf);
    }
    // La bulle porte sur la CASE, pas sur ce qui suit a cote.
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