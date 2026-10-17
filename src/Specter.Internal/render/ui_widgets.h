// Specter.Internal — le peu de rendu que le menu fait lui-meme.
//
// CE QUI RESTE, ET CE QUI A DISPARU
//
// Ce fichier a perdu sept widgets : Panneau, case_a_cocher, curseur, bouton,
// bouton_ligne, bouton_a_x, ligne_repere, titre_section, entree_nav. Le menu
// est revenu aux widgets d'ImGui -- ImGui::Checkbox, SliderFloat, Button,
// SeparatorText, BeginTabBar.
//
// Ce n'est pas un gout : ces widgets etaient une RECONSTRUCTION. ImGui dessine
// sa case a cocher en mode « frame », ce qui se lit comme un champ de saisie
// des qu'elle est cochee ; on avait donc reecrit la case, le bouton, le
// panneau, le curseur... et avec eux tous les pieges que ca implique.
//
// Les pieges ne sont pas theoriques, ils ont tous ete payes :
//   - GetCursorScreenPos() est ABSOLU, SetCursorPos() est LOCAL. Melanger les
//     deux decale tout d'autant que la position de la fenetre.
//   - Un Dummy meme de hauteur nulle fait passer le curseur A LA LIGNE
//     SUIVANTE. Les libelles se retrouvaient 300 px plus bas.
//   - Apres SetCursorScreenPos(), ImGui reclame un Dummy() de fin, et ce Dummy
//     devient le dernier item -- donc IsItemClicked() et IsItemHovered() portent
//     sur le Dummy, qui n'est pas cliquable. La navigation etait morte sans
//     jamais lever d'erreur.
//   - Deux BeginTabItem avec le meme libelle donnent deux onglets, un seul ID.
//     « Programmer error: 2 visible items with conflicting ID! »
//
// Chaque correction a ete faite, revue, puis la-reprise par une autre. Ce sont
// les bugs qu'ImGui ne signale pas. Le code natif les ecarte tous d'un coup,
// parce que ces pieges sont lies au fait de dessiner soi-meme.
//
// On revient donc au natif, et on garde deux choses seulement, qui ne sont pas
// des widgets : le TON (les couleurs ci-dessous) et les GLYPHES.
//
// RIEN ICI NE DEPEND DU C++ DU MENU
//
// Aucune feature, aucun registre. Juste des couleurs et du texte.

#pragma once

#include "imgui.h"

#include <cstring>

namespace specter::render {

// ---------------------------------------------------------------------------
// LE TON. Sept couleurs, et le menu entier tient dedans.
// ---------------------------------------------------------------------------
//
// Elles ne sont pasposees dans le style d'ImGui, sauf exception : ImGui n'a pas
// de concept de « couleur d'accent ». On s'en sert donc pour le texte coloured,
// et le style se charge du reste. Voir poser_style() dans d3d12_overlay.cpp.

inline ImVec4 accent() { return ImVec4(0.58f, 0.36f, 0.92f, 1.00f); }
inline ImVec4 accent_doux() { return ImVec4(0.22f, 0.15f, 0.34f, 1.00f); }
inline ImVec4 fond() { return ImVec4(0.07f, 0.07f, 0.09f, 1.00f); }
inline ImVec4 panneau() { return ImVec4(0.11f, 0.11f, 0.14f, 1.00f); }
inline ImVec4 carte() { return ImVec4(0.10f, 0.10f, 0.13f, 1.00f); }
inline ImVec4 survol() { return ImVec4(0.17f, 0.16f, 0.22f, 1.00f); }
inline ImVec4 texte() { return ImVec4(0.88f, 0.88f, 0.92f, 1.00f); }
inline ImVec4 texte_faible() { return ImVec4(0.50f, 0.48f, 0.57f, 1.00f); }
inline ImVec4 bordure() { return ImVec4(0.30f, 0.28f, 0.36f, 0.65f); }

// ImGui 1.92 ne prend plus de ImVec4 dans les draw lists : c'est ImU32.
inline ImU32 coul(ImVec4 v)
{
    return ImGui::ColorConvertFloat4ToU32(v);
}

// ---------------------------------------------------------------------------
// LES GLYPHES
// ---------------------------------------------------------------------------
//
// Lucide, sous-ensemble de 107 glyphes, integre dans la DLL par
// tools/embed-font.sh. Elle est AJOUTEE a l'atlas, pas mise par defaut : le
// defaut reste Fonts[0], celui du texte, sinon tous les libelles seraient des
// rectangles vides.
//
// Elle est globale, pas locale a l'overlay : un titre de section appartient a
// une feature, donc il faut que la feature puisse poser son icone. Elle est
// VIDE tant qu'elle n'a pas ete installee, et tous les helpers ci-dessous
// verifient — un glyphe sans police ne doit pas dessiner un rectangle.

inline ImFont*& police_icones()
{
    static ImFont* police = nullptr;
    return police;
}

// Les glyphes qu'on utilise reellement, par NOM plutot que par nombre.
// Lucide, zone privee d'Unicode. Les points de code viennent de Lucide.css via
// third_party/lucide/GLYPHES.txt ; les recopier a la main serait la facon
// sure de les derapper a la prochaine mise a jour.
namespace ico {
constexpr unsigned int vise = 0xE0AC;      // crosshair
constexpr unsigned int carte = 0xE111;     // map-pin
constexpr unsigned int eclair = 0xE1B4;    // zap
constexpr unsigned int robot = 0xE1BB;     // bot
constexpr unsigned int bug = 0xE20C;       // bug
constexpr unsigned int terminal = 0xE181;  // terminal
constexpr unsigned int reglages = 0xE154;  // settings
constexpr unsigned int curseurs = 0xE29A;  // sliders-horizontal
constexpr unsigned int outil = 0xE1B1;     // wrench
constexpr unsigned int cible = 0xE345;     // circle-dot
constexpr unsigned int fleche = 0xE06F;    // chevron-right
constexpr unsigned int croix = 0xE1B2;     // x
constexpr unsigned int info = 0xE0F9;      // info
constexpr unsigned int alerte = 0xE193;    // triangle-alert
constexpr unsigned int ok = 0xE226;        // circle-check
constexpr unsigned int actif = 0xE140;     // power
constexpr unsigned int bannir = 0xE051;    // ban
constexpr unsigned int oeil = 0xE0BA;      // eye
constexpr unsigned int liste = 0xE106;     // list
constexpr unsigned int monde = 0xE3B9;     // footprints
constexpr unsigned int sac = 0xE129;       // package
constexpr unsigned int boite = 0xE2D0;     // boxes
constexpr unsigned int boussole = 0xE09B;  // compass
constexpr unsigned int bouclier = 0xE158;  // shield
constexpr unsigned int pile = 0xE36E;      // heart-pulse
constexpr unsigned int balance = 0xE1BF;   // gauge
constexpr unsigned int divers = 0xE154;    // settings
constexpr unsigned int maison = 0xE0DF;    // gamepad-2
constexpr unsigned int sablier = 0xE1E0;   // timer
constexpr unsigned int flamme = 0xE412;    // sparkles
constexpr unsigned int etoiles = 0xE47E;   // sparkle
constexpr unsigned int cristaux = 0xE242;  // gem
constexpr unsigned int route = 0xE53E;     // route
}  // namespace ico

// Encode un point de code en UTF-8 dans `dst`, et renvoie la longueur.
//
// "%c" NE MARCHE PAS ICI, et c'est-evident apres coup. %c ecrit UN octet, alors
// que les glyphes de Lucide sont en zone privee d'Unicode : 0xE0AC tient sur
// trois octets en UTF-8. vsnprintf ecrivait donc 0xAC, un octet de continuation
// isole ; le decodeur UTF-8 d'ImGui le consomme sans produire de glyphe, et
// l'icone disparait SANS ERREUR. La mise en page reste correcte, c'est
// exactement ce qu'on a vu. Le passage en parametre ecrirait 0xE0 0xAC — deux
// octets, pas plus correct. Il faut donc encoder a la main.
inline int utf8_de(unsigned int cp, char* dst)
{
    if (cp < 0x80u) {
        dst[0] = static_cast<char>(cp);
        return 1;
    }
    if (cp < 0x800u) {
        dst[0] = static_cast<char>(0xC0u | (cp >> 6));
        dst[1] = static_cast<char>(0x80u | (cp & 0x3Fu));
        return 2;
    }
    dst[0] = static_cast<char>(0xE0u | (cp >> 12));
    dst[1] = static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu));
    dst[2] = static_cast<char>(0x80u | (cp & 0x3Fu));
    return 3;
}

// UN TITRE A ICONE : « glyphe libelle », rendu comme UNE SEULE chaine.
//
// C'est le seul dessin que le menu conserve, et il n'en est pas un : c'est du
// texte. Pas de draw list, pas de SetCursorScreenPos, pas de Dummy de
// compensation. Le curseur avance exactement comme ImGui le veut, donc aucun
// des pieges du haut ne peut se reproduire.
//
// LE POINT OU ON A MANQUE DE REUSSI, ET POURQUOI CE PASSE MAINTENANT.
//
// La premiere version faisait : PushFont(icones) / Text(glyphe) / PopFont /
// SameLine / SeparatorText(libelle). C'est FAUX, et silencieusement.
//
// SeparatorText ecrit son texte AU CURSEUR. Apres SameLine, le curseur n'est
// plus a la ligne suivante : il est revenu A GAUCHE, a cote de l'icone. Donc le
// libelle se retrouve ecrit SUR l'icone. Et comme SeparatorText reserve sa
// largeur depuis cette position, le trait part de la mauvaise colonne.
//
// La version qui suivait ajoutait SetCursorScreenPos pour « rattraper » la
// ligne -- c'est-a-dire reintroduire, dans le seul bout de code qui restait, le
// piege qu'on venait de supprimer. Le titre etait alors sur deux lignes.
//
// LA SOLUTION : deux items dans le flux normal, chacun avec SA police. Le
// glyphe d'un cote, le libelle de l'autre, un SameLine entre les deux. PushFont
// sert a rendre le glyphe avec la police qui le connait — et a rendre le
// libelle avec la police qui rend le texte lisible.
//
// Rien n'est pose en absolu, donc rien ne peut se desynchroniser quand la
// fenetre bouge ou que la page defile.
//
// SANS police d'icones, on rend le libelle seul : un glyphe manquant
// s'afficherait en carre vide, ou pire, en boites de remplacement. Un titre qui
// dit ce qu'il veut reste lisible.
inline void section(unsigned int glyphe, const char* libelle)
{
    if (!police_icones()) {
        ImGui::SeparatorText(libelle);
        return;
    }

    // Le glyphe, encode en UTF-8, plus UNE espace : c'est tout ce que la police
    // d'icones a rendre. Le libelle suit, avec la police de texte. Deux items,
    // chacun avec SA police — et c'est pourquoi la largeur du trait se mesure
    // apres coup, et non avant.
    char icone[5];
    int n = utf8_de(glyphe, icone);
    icone[n++] = ' ';
    icone[n] = '\0';

    // LE SEPARATEUR.
    //
    // SeparatorText ne sait pas dessiner une icone coloree : il ecrit le
    // libelle d'un bloc, dans la police courante. Donc on rend le titre nous-
    // memes — icone avec la police d'icones, libelle avec la police de texte,
    // chacune a sa place dans le flux normal — et on ne dessine QUE le trait.
    //
    // Ce qui compte ici : le trait est mesure APRES le rendu, et avec la
    // position de FIN de texte. Deux facons de se tromper, et toutes deux
    // silencieuses :
    //
    //   - mesurer la largeur AVANT, avec la mauvaise police. CalcTextSize sur
    //     une chaine meleee donne la largeur de l'icone pour le libelle aussi,
    //     et les deux polices n'ont pas les memes chassees : le trait part dans
    //     le libelle, ou 20 px apres.
    //   - GetContentRegionAvail() apres un SameLine. Ca mesure ce qui reste
    //     depuis le CURSEUR, donc depuis la fin du libelle, pas depuis le bord
    //     gauche : le trait sort alors trop court, de la largeur du texte.
    //
    // GetCursorScreenPos() apres le texte est donc la seule mesure qui soit
    // juste, et c'est ce que fait le code ci-dessous.
    const float h = ImGui::GetTextLineHeight();
    const ImVec2 d = ImGui::GetCursorScreenPos();
    // Le bord droit de la zone de contenu, AVANT tout rendu : apres, le curseur
    // est en fin de libelle et la mesure ne veut plus rien dire.
    const float bord = d.x + ImGui::GetContentRegionAvail().x;

    ImGui::PushFont(police_icones());
    ImGui::TextColored(accent(), "%.*s", n, icone);   // glyphe + espace
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::TextColored(texte(), "%s", libelle);

    // Position APRES le libelle : c'est la que commence le trait.
    //
    // Le bord droit, lui, se mesure au DEBUT — d.x plus toute la largeur
    // disponible. GetContentRegionAvail() rendu ici, apres le texte, mesurerait
    // le reste a partir du curseur, donc le trait serait trop court de la
    // largeur du libelle. On garde donc la largeur totale, lue avant le rendu.
    const float fin = ImGui::GetCursorScreenPos().x;
    const float y = d.y + h * 0.5f;
    if (bord > fin + 12.0f) {
        ImGui::GetWindowDrawList()->AddLine(ImVec2(fin + 12.0f, y),
                                            ImVec2(bord, y), coul(bordure()),
                                            1.0f);
    }

    // Une ligne reservee, et UNE SEULE : ce qu'on a rendu occupe deja la ligne.
    // Un Dummy meme de hauteur nulle ferait descendre tout ce qui suit d'une
    // ligne de trop — c'est exactement ce qui faisait que les titres decalent.
    ImGui::SetCursorScreenPos(d);
    ImGui::Dummy(ImVec2(0.0f, h));
}

// Un titre de section SANS icone : SeparatorText tel quel, trait compris.
inline void section(const char* libelle)
{
    ImGui::SeparatorText(libelle);
}

// L'ICONE DE L'EN-TETE, en plus grand.
//
// C'est le seul endroit du menu ou une icone est posee seule, sans libelle sur
// la meme ligne : le logo, a 18 px au lieu de 16. Un glyphe seul et plus gros
// se lit comme un logo ; un glyphe seul a la taille du texte se lit comme un
// caractere manquant.
//
// RAII : la police est rendue dans le constructeur et rendue dans le
// destructeur. Sans ca, un PopFont oublie laisse le reste du menu en police
// d'icones — et des libelles entiers en rectangles vides.
class Icone_titre_large {
public:
    explicit Icone_titre_large(unsigned int glyphe, float taille = 16.0f)
        : held_(police_icones() != nullptr)
    {
        if (!held_) {
            return;
        }
        ImGui::PushFont(police_icones());
        ImGui::SetWindowFontScale(taille / 16.0f);
        char utf8[4];
        const int n = utf8_de(glyphe, utf8);
        utf8[n] = '\0';
        ImGui::TextColored(accent(), "%s", utf8);
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopFont();
    }
    ~Icone_titre_large() = default;
    Icone_titre_large(const Icone_titre_large&) = delete;
    Icone_titre_large& operator=(const Icone_titre_large&) = delete;

private:
    bool held_;
};

}  // namespace specter::render