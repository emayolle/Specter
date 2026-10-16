// Specter.Internal — case « IA des Aniimoe ». See aniai.h for the design.

#include "pch-il2cpp.h"

#include "features/aniai/aniai.h"
#include "imgui.h"

namespace specter::features {
namespace aniai {
namespace {

// Les deux stockages, un par fait.
//
// g_enabled  lu par la case ET par `specter.var.ani_ia`. C'est la seule chose
//            qui la fait marcher : le script ecrit exactement l'octet que la
//            case vient d'ecrire.
// g_etat     ecrit par le script apres avoir applique le flag sur AiConst. Une
//            case qui dit « coche » sans dire si l'IA est reellement coupee au
//            jeu, c'est une case aveugle.

// ACTIVE PAR DEFAUT. L'IA des Aniimoe etait fausse dans le build qu'on a
// mesure (GLOBAL_OPEN_TICK = false au chargement) ; la case doit retrouver
// l'etat normal du jeu, pas le figer dans cet etat-la.
//
// Sans risque de piege : le pilote relit ce flag toutes les 250 ms et ecrit
// AiConst.GLOBAL_OPEN_TICK. Decocher, c'est un quart de seconde de plus.
bool g_enabled = true;
int g_etat = 0;  // 0 AiConst introuvable, 1 IA activee, 2 IA desactivee

}  // namespace

bool* flag()
{
    return &g_enabled;
}

int* etat()
{
    return &g_etat;
}

const char* etat_label(int v)
{
    switch (v) {
    case 1: return "IA activee";
    case 2: return "IA desactivee";
    default: return "AiConst introuvable";
    }
}

void draw_ui()
{
    bool on = g_enabled;
    if (ImGui::Checkbox("IA des Aniimoe\n( decochee : ils ne font plus rien )", &on)) {
        g_enabled = on;
    }

    ImGui::SameLine();
    ImGui::BeginDisabled();
    if (g_etat == 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f), "%s", etat_label(g_etat));
    } else {
        ImGui::Text("%s", etat_label(g_etat));
    }
    ImGui::EndDisabled();

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Ecrit Common.Const.AiConst.GLOBAL_OPEN_TICK.\n\n"
            "  decochee -> false : les Aniimoe ne poursuivent plus, ne "
            "reagissent plus\n"
            "  cochee   -> true  : leur IA reprend\n\n"
            "Applique par scripts/ani_ai.lua, joue a chaque nouvel etat Lua, "
            "qui relit `specter.var.ani_ia` toutes les 250 ms.\n\n"
            "Il ecrit inconditionnellement : le jeu peut remettre sa valeur "
            "entre deux passages, et une ecriture conditionnelle ne le "
            "remarkerait pas.");
    }
}

}  // namespace aniai
}  // namespace features