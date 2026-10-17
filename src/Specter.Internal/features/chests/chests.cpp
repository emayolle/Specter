// Specter.Internal — ouverture des coffres (case a cocher). See chests.h.

#include "pch-il2cpp.h"

#include "features/chests/chests.h"
#include "imgui.h"
#include "render/ui_widgets.h"

namespace specter::features {
namespace chests {
namespace {

// Les trois stockages. Un par fait, aucun duplique.
//
// g_enabled  lu par la case ET par `specter.var.coffres`. C'est la seule
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
int g_phase = 0;  // 0 inactif, 1 cherche, 2 ouvre, 3 attend, 4 auto-farm
// Les TP qui n'ont pas amene. Affiches, parce qu'un echec qu'on ne compte pas
// est un echec qu'on recommence en silence.
int g_echecs = 0;
// Les erreurs du pilote Lua. Le pilote est un pcall : sans ca, une erreur y est
// invisible et la boucle se repose en silence, indefiniment.
int g_erreurs = 0;
// Les coffres qui ont coute des PV. Affiches PARCE QUE l'ouverture compte :
// sans ce chiffre, une boucle qui enchainne des coffres dans une zone d'Aniipods
// prend six de moyenne, le compteur « ouverts » monte, et rien n'explique la
// vie qui descend.
int g_gagnes = 0;

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

int* echecs()
{
    return &g_echecs;
}

int* erreurs()
{
    return &g_erreurs;
}

int* gagnes()
{
    return &g_gagnes;
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
    case 1: return "cherche des coffres";
    case 2: return "ouvre";
    case 3: return "attend (plus rien a faire)";
    // Une case qui affiche « auto-farm » quand on l'a cochee vaut mieux qu'une
    // case cochee qui ne dit rien : le joueur voit la raison de l'inaction
    // au lieu de croire que la boucle est cassee.
    case 4: return "en attente (auto-farm)";
    // DISTINCTE de « attend ». Les deux donnent une boucle immobile, mais l'un
    // demande d'attendre et l'autre de ressusciter. Mesure : la boucle
    // telegraphait « cherche des coffres » et comptait cinq TP ratés sur un
    // joueur a 0/6 PV. Un mort ne se deplace pas -- les TP echouaient
    // legitiment, et c'etait le seul indice.
    case 5: return "ARRET (joueur mort)";
    default: return "inactif";
    }
}

void draw_ui()
{
    bool on = g_enabled;
    if (ImGui::Checkbox("Auto-open chests", &on)) {
        set_enabled(on);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "CHESTS ONLY. The game sets isChest on pickups and Aniipods too --\n"
            "measured: 19 targets kept, 1 was a chest.\n"
            "A target is kept only if Data.chest_data[template].markConfigId\n"
            "== 10506. Measured: 12 accepted, 0 disagreements.\n"
            "Counts only after the entity disappears. Same one-mover-at-a-time\n"
            "rule as auto-farm.");
    }

    // THE THREE NUMBERS THAT CAN GO WRONG. Each one is hidden until it is
    // wrong, because a line that always reads "0" is a line nobody reads.
    //
    // Driver error first: that is a loop that never started at all, which is
    // worse than a missed teleport, and it used to be silent -- a pcall
    // swallows, the loop sleeps, and the menu cheerfully says "searching".
    if (g_erreurs > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.30f, 1.0f),
                           "driver errors: %d", g_erreurs);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "The driver is a pcall, so its errors were silent.\n"
                "Message: tools/lua.sh -f scripts/erreurs-coffres.lua");
        }
    }
    if (g_gagnes > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.72f, 0.35f, 1.0f),
                           "chests that cost HP: %d", g_gagnes);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "Opened, and you paid for it. Those are skipped for the scene.\n"
                "HP is in hearts (measured: curHp=6, maxHp=6), and the check\n"
                "watches TWO signals -- curHp falling, lastHurtTime moving --\n"
                "because regeneration would mask the loss.\n"
                "Only skipped on PROOF of damage, never on missing data.");
        }
    }
    if (g_echecs > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f),
                           "teleports not reached: %d", g_echecs);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "If this climbs while \"opened\" stays at 0, the loop cannot\n"
                "move: the game holds the player on a spot, and any position\n"
                "write is reverted within 50 ms. A game state, not a bug.");
        }
    }

    // Un ESPACE entre le libelle et l'etat. Sans, la capture lisait
    // « Auto-farm off » colle — on ne sait pas si « off » est un mot du libelle
    // ou l'etat de la case.
    ImGui::SameLine(0.0f, 12.0f);
    ImGui::BeginDisabled();
    if (on) {
        ImGui::Text("%d opened", g_ouverts);
    } else {
        ImGui::TextDisabled("off");
    }
    ImGui::EndDisabled();

}

}  // namespace chests
}  // namespace features
