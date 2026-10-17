// Specter.Internal — case « IA des Aniimoe ». See aniai.h for the design.

#include "pch-il2cpp.h"

#include "features/aniai/aniai.h"
#include "imgui.h"
#include "render/ui_widgets.h"

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
    if (ImGui::Checkbox("Aniimoe AI", &on)) {
        g_enabled = on;
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Writes AiConst.GLOBAL_OPEN_TICK.\n"
            "  off -> false: Aniimoe stop chasing and reacting\n"
            "  on  -> true : their AI resumes\n"
            "Rewritten every 250 ms, because the game puts its own value back.");
    }

    // What the GAME reads, right of the checkbox that commands it. Greyed,
    // because clicking it does nothing.
    ImGui::SameLine();
    ImGui::BeginDisabled();
    if (g_etat == 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f), "%s",
                           etat_label(g_etat));
    } else {
        ImGui::TextDisabled("%s", etat_label(g_etat));
    }
    ImGui::EndDisabled();

}

}  // namespace aniai
}  // namespace features
