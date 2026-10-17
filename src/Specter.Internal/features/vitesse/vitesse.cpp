// Specter.Internal — multiplicateurs de vitesse. See vitesse.h.

#include "pch-il2cpp.h"

#include "features/vitesse/vitesse.h"
#include "imgui.h"
#include "render/ui_widgets.h"

#include <cstring>

namespace specter::features {
namespace vitesse {
namespace {

bool g_actif = false;

// La liste des curseurs.
//
// L'ORDRE EST CELUI DU SCRIPT : scripts/vitesse.lua declare la meme table, et le
// C++ tire ses noms de `vit_<nom>`. Les deux listes portent les memes cles -- le
// binding `vit_<nom>` est le contrat, et il est ecrit en un seul endroit de
// chaque cote.
//
// `cout_stamina` est le seul dont le sens est inverse : c'est un COUT. A x10 de
// course, une stamina qui se vide dix fois plus vite annule tout le gain. C'est
// pour ca qu'il descend jusqu'a 0.
const Curseur kCurseurs[] = {
    { "course", "Course", 0.1f, 10.0f, 1.0f,
      "getRunSpeedRatio. Mesure : utilise (108 appels), mais\n"
      "a toi et a tes pets seulement." },
    { "sprint", "Sprint", 0.1f, 10.0f, 1.0f,
      "getSprintSpeedRatio. Le plus sollicite du jeu : 886 appels\n"
      "mesures. C'est celui qui a le plus d'effet." },
    { "dash", "Dash", 0.1f, 10.0f, 1.0f,
      "getDashSpeedRatio. Sans rapport avec le recharge :\n"
      "pour ca, voir « Dash illimite » dans les scripts de reference." },
    { "nage_rapide", "Nage rapide", 0.1f, 10.0f, 1.0f,
      "getSwimFastSpeedRatio. ATTENTION : le jeu n'a d'etat « nage\n"
      "rapide » qu'APRES un dash. Avant, ce curseur ne fait rien --\n"
      "c'est une machine a etats, pas un reglage." },
    { "vol", "Vol", 0.1f, 10.0f, 1.0f,
      "getGlideSpeedRatio. Consulte (45 appels mesurees).\n"
      "Pas encore verifie en vol -- laisse a 1 si tu n'as pas teste." },
    { "nage", "Nage", 0.1f, 10.0f, 1.0f,
      "getSwimSpeedRatio. Consulte, mais peu (6 appels) :\n"
      "ton passage dans l'eau etait court." },
    { "cout_stamina", "Cout de stamina", 0.0f, 10.0f, 1.0f,
      "getStaminaCostRatio. Un COUT, pas une vitesse : le MONTER\n"
      "vide la stamina d'autant plus vite et annule le gain.\n"
      "Consulte 208 fois, dont 58 pendant une escalade.\n"
      "C'est le SEUL levier qui reste sur l'escalade." },
};
constexpr int kN = static_cast<int>(sizeof(kCurseurs) / sizeof(kCurseurs[0]));

// Les stockages, un par curseur, dans un tableau indexe PAR LA MEME CLE que le
// script. La cle est cherchee, pas l'indice : un curseur ajoute au milieu decale
// tous les indices, et personne ne voit l'erreur tant que le menu est ouvert.
float g_mult[16] = {};

bool trouve(const char* nom, int* out)
{
    for (int i = 0; i < kN; ++i) {
        if (std::strcmp(kCurseurs[i].nom, nom) == 0) {
            if (out) *out = i;
            return true;
        }
    }
    return false;
}

}  // namespace

bool* actif()
{
    return &g_actif;
}

float* mult(const char* nom)
{
    int i = 0;
    if (!trouve(nom, &i)) {
        return nullptr;
    }
    if (g_mult[i] == 0.0f) {
        g_mult[i] = kCurseurs[i].defaut;  // 0 n'est pas une valeur : c'est « pas lu »
    }
    return &g_mult[i];
}

void draw_ui()
{
    bool on = g_actif;

    // LA HAUTEUR EST COMPTEE, PAS MESUREE.
    //
    // Une carte avec une case + un curseur par ratio : le nombre de curseurs est
    // connu (kN), donc la hauteur se calcule. C'est l'inverse d'AutoResizeY, et
    // c'est pourquoi ca ne peut pas boucler -- voir render/ui_widgets.h.
    const float h_mvt = 58.0f + (on ? static_cast<float>(kN) * 30.0f : 26.0f);
    { render::Group g("Movement", h_mvt);

    if (ImGui::Checkbox("Speed multipliers", &on)) {
        g_actif = on;
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("One slider per ratio, read live by the script.");
    }

    if (on) {
        for (int i = 0; i < kN; ++i) {
            const Curseur& c = kCurseurs[i];
            if (g_mult[i] == 0.0f) {
                g_mult[i] = c.defaut;   // 0 is not a value: it means "not read"
            }
            render::slider_row(c.label, &g_mult[i], c.min_v, c.max_v, "%.1fx");
            if (ImGui::IsItemHovered() && c.aide) {
                ImGui::SetTooltip("%s", c.aide);
            }
        }
    }
    }  // group

    // WHAT IT TOUCHES. Three lines on screen; the reasoning is on hover.
    { // Deux lignes de texte + titre : 76 px. 110 laissait 34 px vides —
    // visible sur la capture comme une bande noire au milieu de la page.
    render::Group g("Scope", 76.0f);
    ImGui::TextDisabled("You and your pets. NPCs keep their speed.");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "The patch wraps the CLASS methods -- that is where the game\n"
            "resolves them -- but it is CONDITIONAL: it only multiplies for\n"
            "your entity or your pets. Unconditional, 32 NPCs were measured\n"
            "at the player's speed.\n"
            "It is removed when you untick, and reapplied twice a second,\n"
            "because the game can recreate the attribute and a patch that\n"
            "vanished for no reason is a dead setting.");
    }
    ImGui::TextDisabled("Climbing is not here.");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Game source: getClimbSpeed = climbSpeedLevels[canClimb], no\n"
            "ratio anywhere, and SetAISpeed has ONE caller in the whole\n"
            "game -- AIControllerUtils. What you control goes another way.\n"
            "Stamina cost, below, is the only lever left on climbing.");
    }
    }  // group
}

}  // namespace vitesse
}  // namespace features