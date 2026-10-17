// Specter.Internal — auto-farm (case a cocher). See autofarm.h for the design.

#include "pch-il2cpp.h"

#include "features/autofarm/autofarm.h"
#include "imgui.h"
#include "render/ui_widgets.h"

namespace specter::features {
namespace autofarm {
namespace {

// Les trois stockages. Un par fait, aucun duplique.
//
// g_enabled  lu par la case ET par `specter.var.autofarm`. C'est la seule
//            raison pour laquelle la case marche : le pilote Lua lit exactement
//            l'octet que la case vient d'ecrire.
// g_ouverts  ecrit par Lua apres chaque ouverture CONFIRMEE (l'entite a
//            disparu). Afficher un compteur qui compte des appels d'API plutot
//            que des ouvertures serait mensonger -- c'est exactement le defaut
//            qu'on a retire du script.
// g_phase    ecrit par Lua a chaque changement d'etat de la boucle. C'est ce
//            qui distingue « la case est cochee et rien ne se passe » de
//            « la case est cochee et ca cherche ».

bool g_enabled = false;
int g_ouverts = 0;
int g_phase = 0;  // 0 inactif, 1 cherche, 2 ouvre, 3 attend

}  // namespace

bool* flag()
{
    return &g_enabled;
}

int* ouverts()
{
    return &g_ouverts;
}

int* phase()
{
    return &g_phase;
}

void set_enabled(bool on)
{
    g_enabled = on;
}

bool enabled()
{
    return g_enabled;
}

const char* phase_label(int v)
{
    switch (v) {
    case 1: return "cherche des cibles";
    case 2: return "ouvre";
    case 3: return "attend (plus rien a faire)";
    default: return "inactif";
    }
}

void draw_ui()
{
    bool on = g_enabled;
    if (ImGui::Checkbox("Auto-farm", &on)) {
        set_enabled(on);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Loops forever over anything interactable, EXCEPT chests.\n"
            "A target only counts after its entity disappears -- an\n"
            "interaction call that returns cleanly proves nothing.\n"
            "If auto-open chests is on too, only one of the two moves at a\n"
            "time: the other waits. They would fight over the teleport.");
    }

    ImGui::SameLine();
    ImGui::BeginDisabled();
    if (on) {
        ImGui::Text("%d", g_ouverts);
    } else {
        ImGui::TextDisabled("off");
    }
    ImGui::EndDisabled();

}

}  // namespace autofarm
}  // namespace features
