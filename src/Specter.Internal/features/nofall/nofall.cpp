// Specter.Internal — no fall damage (implementation). Design in nofall.h.

#include "pch-il2cpp.h"

#include "features/nofall/nofall.h"
#include "imgui.h"
#include "render/ui_widgets.h"

namespace specter::features {
namespace nofall {
namespace {

// THE flag, and the only one.
//
// Read by Lua through `specter.var.nofall` at every landing, written by the
// checkbox. Nothing else stores it, and nothing on the game's side stores a
// copy — the wrapper asks on each call.
// ACTIVE PAR DEFAUT.
//
// Sans piege, et c'est a verifier avant de le dire : le patch de
// checkImmuneFallDamage est pose UNE FOIS par init.lua, mais la porte
// `specter.var.nofall` est relue a CHAQUE appel, et decochee elle retombe sur
// la fonction d'origine (init.lua:416-423). Donc decocher prend effet
// immediatement, sans rejouer le script et sans retirer le patch.
bool g_enabled = true;

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
    // La bulle porte sur la CASE. Avant, elle etaitappelee apres un SameLine :
    // elle portait donc sur le texte de droite, et une zone cliquable sans
    // infobulle. Meme information, mauvaise cible.
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Patches checkImmuneFallDamage, the game's OWN fall-damage "
            "immunity decision, so both of its call sites are covered -- the "
            "player and the pet -- and the per-zone immunity it already "
            "implements is respected. This one does not depend on where you "
            "are. Turning it off restores the normal behaviour immediately: "
            "the patch stays installed and becomes a pass-through.");
    }
}

}  // namespace nofall
}  // namespace specter
