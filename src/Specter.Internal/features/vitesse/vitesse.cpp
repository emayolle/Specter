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
    render::section(render::ico::eclair, "VITESSE");

    bool on = g_actif;
    if (ImGui::Checkbox("Multiplicateurs de vitesse", &on)) {
        g_actif = on;
    }

    if (on) {
        // UN CURSEUR PAR RATIO, ET LE RATIO EST DANS SON NOM.
        //
        // ImGui ecrit le libelle A DROITE de la piste en 1.92. C'est l'apparence
        // stock, et elle a un avantage qu'on ne voit pas : IsItemHovered et
        // IsItemDeactivatedAfterEdit portent sur le CURSEUR, alors que le
        // wrapper d'avant finissait sur un Dummy et donc rapportait le survol
        // de toute la ligne.
        for (int i = 0; i < kN; ++i) {
            const Curseur& c = kCurseurs[i];
            if (g_mult[i] == 0.0f) {
                g_mult[i] = c.defaut;   // 0 n'est pas une valeur : « pas lu »
            }
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::SliderFloat(c.label, &g_mult[i], c.min_v, c.max_v,
                                   "%.1fx")) {
                // Lu en direct par le script : un curseur bouge agit sans
                // qu'on ait a rejouer quoi que ce soit.
            }
            if (ImGui::IsItemHovered() && c.aide) {
                ImGui::SetTooltip("%s", c.aide);
            }
        }
    } else {
        ImGui::TextColored(render::texte_faible(),
                           "desactive -- les vitesses originales sont restaurees");
    }

    // CE QUE CELA TOUCHE, ET CE QUE CELA NE TOUCHE PAS.
    //
    // Le patch est pose sur la CLASSE -- c'est la que le jeu resout la methode.
    // Pose sur l'instance, personne ne bougeait : le champ pose la n'est pas la
    // ou le jeu va le chercher. Mais pose sur la classe sans condition, tout le
    // monde accelerait : 32 PNJ mesures a la meme valeur que le joueur.
    //
    // Donc le wrapper est CONDITIONNEL : il ne multiplie que si l'instance
    // appelante est la tienne ou celle d'un de tes pets.
    render::section(render::ico::boussole, "PORTEE");
    ImGui::TextColored(render::texte_faible(),
                       "Toi et tes pets. Les PNJ et les betes sauvages non.");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Le patch enveloppe les methodes de vitesse de la CLASSE,\n"
            "parce que c est la que le jeu les resout : pose sur\n"
            "l instance, il n etait jamais consulte.\n\n"
            "Mais il est CONDITIONNEL : le multiplicateur ne s applique\n"
            "que si l entite appelante est la tienne ou un de tes pets.\n"
            "Les PNJ et les betes sauvages gardent leur vitesse.\n\n"
            "Il est REPOSE quand tu decoches, et reapplique toutes les\n"
            "demi-secondes -- parce que le jeu peut recreer l attribut,\n"
            "et un patch disparu sans raison est un reglage inerte.\n\n"
            "L ESCALADE N'EST PAS LA. Le source du jeu dit\n"
            "getClimbSpeed = climbSpeedLevels[canClimb], sans aucun ratio, et\n"
            "SetAISpeed n'a QU'UN appelant dans tout le jeu : AIControllerUtils.\n"
            "Ce que TU controles passe par un autre chemin. Le seul levier\n"
            "restant sur l'escalade est « Cout de stamina » en dessous.");
    }
}

}  // namespace vitesse
}  // namespace features