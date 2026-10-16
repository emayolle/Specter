// Specter.Internal — auto-farm (case a cocher). See autofarm.h for the design.

#include "pch-il2cpp.h"

#include "features/autofarm/autofarm.h"
#include "imgui.h"

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
    if (ImGui::Checkbox("Auto-farm\n"
                        "(ramasse ce qui s'interagit, SAUF les coffres)",
                        &on)) {
        set_enabled(on);
    }

    // Ce que la case fait, pas ce qu'elle OUVERT. Une case qui dit « coche »
    // sans dire si la boucle tourne, c'est une case aveugle.
    ImGui::SameLine();
    ImGui::BeginDisabled();
    if (on) {
        ImGui::Text("%s -- %d ouvert(s)", phase_label(g_phase), g_ouverts);
    } else {
        ImGui::TextDisabled("desactive");
    }
    ImGui::EndDisabled();

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Boucle permanente, demarree par scripts/autofarm_loop.lua a chaque "
            "nouvel etat Lua.\n\n"
            "Elle ecarte les coffres (marque 10506 confirmee a moins de 3 u) et "
            "les objets a contact, et elle ne s'arrete jamais : quand il ne reste "
            "rien, elle attend et reessaie.\n\n"
            "Une cible n'est comptee qu'APRES la disparition de son entite. Un "
            "appel d'interaction qui rend sans erreur ne prouve rien.");
    }
}

}  // namespace autofarm
}  // namespace features