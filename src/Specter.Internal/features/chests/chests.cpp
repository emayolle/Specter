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
    render::section(render::ico::boite, "OUVERTURE DES COFFRES");

    bool on = g_enabled;
    if (ImGui::Checkbox("Auto-ouverture (SEULEMENT les coffres, rien d'autre)",
                        &on)) {
        set_enabled(on);
    }

    // Ce que la case fait, pas ce qu'elle a OUVERT. Une case qui dit « coche »
    // sans dire si la boucle tourne, c'est une case aveugle.
    //
    // La bulle porte sur la CASE. Elle portait sur le texte d'a cote, donc le
    // survol de la case — de la ou on regarde — n'affichait rien.
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Boucle permanente, demarree par scripts/chest-open.lua a chaque "
            "nouvel etat Lua.\n\n"
            "ELLE NE TOUCHE QU'AUX COFFRES. Le jeu pose `isChest` aussi sur les "
            "ramassages, les Aniipods et les oeufs -- mesure : 19 cibles "
            "retenues, 1 seul coffre. Une entite n'est gardee que si la config "
            "du jeu dit coffre : Data.chest_data[son template].markConfigId "
            "== 10506. Mesure : 12 coffres acceptes sur 12, 0 desaccord.\n\n"
            "Un coffre n'est compte qu'APRES la disparition de son entite. Un "
            "appel d'interaction qui rend sans erreur ne prouve rien.\n\n"
            "Une seule boucle se deplace a la fois : si l'auto-farm est "
            "cochee, celle-ci attend. Les deux se disputeraient le meme "
            "teletportement, et aucune n'arriverait.");
    }

    // UNE ERREUR DU PILOTE, EN TETE, ET EN ROUGE.
    //
    // Elle passe AVANT le compteur d'echecs de TP : une erreur du pilote, c'est
    // une boucle qui ne demarre pas du tout, ce qui est plus grave qu'un
    // teleport rate. Et elle se voit tout de suite, parce qu'elle est la seule
    // ligne de cette page qui dit « ca ne marche pas » sans ambiguite.
    if (g_erreurs > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.30f, 1.0f),
                           "ERREUR : le pilote Lua a echoue %d fois", g_erreurs);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "Le pilote est un pcall : sans ce compteur, une erreur y est\n"
                "muette. La boucle se repose, le pilote recommence, et le menu\n"
                "affiche « cherche des coffres » sans jamais rien ouvrir.\n\n"
                "Le message est dans le store :\n"
                "  tools/lua.sh -f scripts/erreurs-coffres.lua");
        }
    }

    // LES COFFRES QUI ONT COUTE DES PV.
    //
    // Affiche meme si l'ouverture compte, parce que c'est exactement ce que le
    // compteur d'ouverts ne peut pas dire : le coffre a bien ete ouvert, ET on
    // a paye. Un coup affiche ici est un coffre que la boucle ne retente pas
    // dans la scene -- pas un coffre qu'elle n'a pas reussi.
    if (g_gagnes > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.72f, 0.35f, 1.0f),
                           "%d coffre(s) ont coute des PV", g_gagnes);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "Le coffre a bien ete ouvert, et le joueur a perdu un coeur "
                "pendant le cycle : Aniipods, ou une chute en chemin.\n\n"
                "Ces coffres-la sont ecartes pour la scene en cours. Les PV "
                "sont en coeurs (mesure : curHp=6, maxHp=6), et le controle "
                "porte sur deux signaux -- curHp qui baisse, ou lastHurtTime "
                "qui avance -- parce que la regeneration ferait sinon remonter "
                "le compteur et masquerait une perte.\n\n"
                "Un coffre n'est ecarte que sur une PREUVE de degats, jamais "
                "sur une absence d'information.");
        }
    }

    // LES TP QUI N'ARRIVENT PAS.
    //
    // Ligne separee, en couleur d'alerte, parce que c'est le seul chiffre qui
    // distingue « la boucle cherche et ne trouve rien » de « la boucle ne peut
    // pas se deplacer ». Les deux affichent « cherche des coffres », et le
    // second peut durer une session entiere sans rien dire. Ca s'est produit :
    // le teleport a refuse toute ecriture de position pendant plusieurs heures,
    // et rien ne l'a signale parce que rien ne le comptait.
    if (g_echecs > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f),
                           "%d teleportation(s) sans arrivee", g_echecs);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "Un coffre n'a pas ete atteint dans le delai : la boucle passe "
                "au suivant et retente.\n\n"
                "Si ce chiffre monte et que « ouverts » reste a zero, la boucle "
                "ne se deplace pas. Le jeu peut alors maintenir le joueur sur "
                "un point : toute ecriture de position est ramenee en moins de "
                "50 ms, et aucun teleport n'aboutit.\n\n"
                "C'est un etat du jeu, pas un bug du filtre a coffres.");
        }
    }

    // La phase et les compteurs, en bas : ils expliquent le chiffre de la case.
    ImGui::BeginDisabled();
    if (on) {
        ImGui::Text("%s -- %d ouvert(s)", phase_label(g_phase), g_ouverts);
    } else {
        ImGui::TextColored(render::texte_faible(), "desactive");
    }
    ImGui::EndDisabled();
}

}  // namespace chests
}  // namespace features