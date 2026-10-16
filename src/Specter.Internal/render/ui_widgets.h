// Specter.Internal — les widgets du menu.
//
// POURQUOI ILS EXISTENT
//
// Le menu d'avant faisait ses cases avec ImGui::Checkbox, qui dessine une
// case comme un CHAMP DE SAISIE : un cadre bleu pale quand elle est cochee, le
// meme qu'autour d'un champ de texte. C'est la premiere chose qui le rendait
// « pas assez representatif » — on ne distinguait pas une option d'une saisie.
//
// Ces widgets sont la, dans un en-tete, pour que les features les utilisent
// aussi. Les mettre dans l'overlay aurait oblige chaque feature a include un
// .cpp de rendu, ou a redefinir sa propre version — c'est-a-dire retrouver le
// probleme qu'on vient de resoudre.
//
// LA POLICE D'ICONES
//
// Lucide, sous-ensemble de 107 glyphes, integre dans la DLL par
// tools/embed-font.sh. Elle est AJOUTEE a l'atlas, pas mise par defaut : le
// defaut reste celui d'ImGui, sinon tous les libelles seraient des rectangles
// vides. Les icones se demandent avec la classe Icone.
//
// Les glyphes sont dans la zone privee d'Unicode, donc on passe par un petit
// wrapper PushIcon au lieu d'ecrire "\xEF\x80\x80" partout — une chaine brute
// serait illisible, et un caractere isole se coupe en fin de ligne.
//
// RIEN ICI NE DEPEND DU C++ DU MENU
//
// Widgets purs : ils connaissent le style d'ImGui et dessinent. Aucune feature,
// aucun registre.

#pragma once

#include "imgui.h"

#include <algorithm>

namespace specter::render {

// La couleur d'accent, et les quatre qui vont avec. Tout le ton du menu tient
// dans ces sept valeurs : un violet sur un fond presque noir.
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

// Emporte la police d'icones tant qu'on en a besoin.
class Icone {
public:
    Icone(ImFont* police, float taille)
        : held_(police != nullptr)
    {
        if (held_) {
            ImGui::PushFont(police);
            ImGui::SetWindowFontScale(taille / 16.0f);
        }
    }
    ~Icone()
    {
        if (held_) {
            ImGui::SetWindowFontScale(1.0f);
            ImGui::PopFont();
        }
    }
    Icone(const Icone&) = delete;
    Icone& operator=(const Icone&) = delete;

private:
    bool held_;
};

// Les glyphes qu'on utilise reellement, par nom plutot que par nombre.
// Lucide, zone privee d'Unicode.
namespace ico {
// Lucide, sous-ensemble de 107 glyphes. Les points de code viennent de
// Lucide.css via third_party/lucide/GLYPHES.txt ; les recopier a la main serait
// la facon sure de les derapper a la prochaine mise a jour.
constexpr unsigned int vise = 0xE0AC;        // crosshair
constexpr unsigned int carte = 0xE111;      // map-pin
constexpr unsigned int eclair = 0xE1B4;     // zap
constexpr unsigned int robot = 0xE1BB;      // bot
constexpr unsigned int bug = 0xE20C;        // bug
constexpr unsigned int terminal = 0xE181;   // terminal
constexpr unsigned int reglages = 0xE154;   // settings
constexpr unsigned int outil = 0xE1B1;      // wrench
constexpr unsigned int cible = 0xE345;      // circle-dot
constexpr unsigned int fleche = 0xE06F;     // chevron-right
constexpr unsigned int croix = 0xE1B2;      // x
constexpr unsigned int info = 0xE0F9;       // info
constexpr unsigned int alerte = 0xE193;     // triangle-alert
constexpr unsigned int ok = 0xE226;         // circle-check
constexpr unsigned int actif = 0xE140;      // power
constexpr unsigned int bannir = 0xE051;     // ban
constexpr unsigned int oeil = 0xE0BA;       // eye
constexpr unsigned int liste = 0xE106;      // list
}  // namespace ico

// Encode un point de code en UTF-8 et le rend.
//
// "%c" NE MARCHE PAS ICI, et c'est-evident apres coup. %c ecrit UN octet, alors
// que les glyphes de Lucide sont en zone privee d'Unicode : 0xE0AC tient sur
// trois octets en UTF-8. vsnprintf ecrivait donc 0xAC, un octet de continuation
// isole ; le decodeur UTF-8 d'ImGui le consomme sans produire de glyphe, et
// l'icone disparait SANS ERREUR. La mise en page reste correcte, c'est
// exactement ce qu'on a vu.
//
// Le passage en parametre, lui, ecrirait 0xE0 0xAC — deux octets, pas plus
// correct. Il faut donc encoder a la main.
inline void glyphe_dessine(unsigned int cp, ImVec4 couleur)
{
    char utf8[4];
    int n = 0;
    if (cp < 0x80u) {
        utf8[n++] = static_cast<char>(cp);
    } else if (cp < 0x800u) {
        utf8[n++] = static_cast<char>(0xC0u | (cp >> 6));
        utf8[n++] = static_cast<char>(0x80u | (cp & 0x3Fu));
    } else {
        utf8[n++] = static_cast<char>(0xE0u | (cp >> 12));
        utf8[n++] = static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu));
        utf8[n++] = static_cast<char>(0x80u | (cp & 0x3Fu));
    }
    utf8[n] = '\0';
    ImGui::TextColored(couleur, "%s", utf8);
}

// Une entree de navigation : icone + libelle, comme sur la maquette.
// UNE LIGNE DE NAVIGATION.
//
// Le piege, et il a fallu une capture deplacee pour le voir : je lisais la
// position du curseur, je dessinais l'icone et le libelle avec SetCursorPos, et
// je posais la zone cliquable — mais entre les trois, le curseur normal
// AVAIT avance. Les lignes suivantes partaient donc de ou la ligne precedente
// s'etait arretee, et la colonne derivait vers la droite. A la position initiale
// c'est invisible ; des qu'on bouge la fenetre, le decalage s'accumule.
//
// La regle : une ligne ne doit JAMAIS deplacer le curseur de facon inattendue.
// Donc on dessine en absolu, puis on rend la main avec Dummy, et la zone
// cliquable est posee au point de depart. Le curseur descend d'exactement
// `hauteur` par ligne, quoi qu'il arrive.

inline void entree_nav(ImFont* police, const char* libelle, unsigned int glyphe,
                       bool actif, float largeur, float hauteur, float marge,
                       int id)
{
    // Un ID PAR LIGNE. Les sept InvisibleButton portaient tous "##nav", et
    // ImGui le signale tres exactement :
    //
    //     Programmer error: 7 visible items with conflicting ID!
    //
    // « 7 » etait le nombre de pages. Le libelle etant masque par « ## », il
    // ne sert pas d'identifiant : il faut un ID explicite. PushID encadre le
    // tout, donc il couvre aussi le glyphe et le libelle.
    ImGui::PushID(id);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 depart = ImGui::GetCursorScreenPos();
    const ImVec2 p(depart.x + marge, depart.y);
    const ImVec2 q(p.x + largeur, p.y + hauteur);

    if (actif || ImGui::IsMouseHoveringRect(p, q, true)) {
        dl->AddRect(p, q, coul(accent_doux()), 6.0f, 0, 1.0f);
    }
    if (actif) {
        dl->AddRectFilled(ImVec2(p.x, p.y + 3.0f), ImVec2(p.x + 3.0f, q.y - 3.0f),
                          coul(accent()), 1.5f);
    }

    // DEUX SYSTEMES DE COORDONNEES, ET C'EST LA QUE CA CASSAIT.
    //
    // GetCursorScreenPos() et SetCursorScreenPos() parlent ABSOLU : coordonnees
    // ecran. SetCursorPos() et GetCursorPos() parlent LOCAL : relatives a la
    // fenetre courante.
    //
    // Je lisais en absolu et j'ecrivais en local. L'ecart vaut exactement la
    // position de la fenetre : a 40 px du coin, il passait inapercu ; des que
    // la fenetre bougeait vers la droite, tout glissait de la meme quantite —
    // le logo, les icones, les libelles, tous du meme decalage.
    //
    // LA REGLE : on lit avec GetCursorScreenPos, on ecrit avec
    // SetCursorScreenPos. On ne melange jamais les deux.

    // Icone, police d'icones posee le temps du rendu.
    if (police) {
        Icone portee(police, 16.0f);
        ImGui::SetCursorScreenPos(
            ImVec2(p.x + 13.0f, p.y + (hauteur - 16.0f) * 0.5f));
        glyphe_dessine(glyphe, actif ? accent() : texte_faible());
    }

    // Libelle, a cote de l'icone.
    ImGui::SetCursorScreenPos(
        ImVec2(p.x + 37.0f, p.y + (hauteur - ImGui::GetTextLineHeight()) * 0.5f));
    ImGui::TextColored(actif ? texte() : texte_faible(), "%s", libelle);

    // On rend la main EXACTEMENT d'une ligne de haut, puis on pose la zone
    // cliquable a son point de depart.
    ImGui::SetCursorScreenPos(depart);
    ImGui::Dummy(ImVec2(largeur + marge, hauteur));
    ImGui::SetCursorScreenPos(depart);
    ImGui::InvisibleButton("##zone", ImVec2(largeur + marge, hauteur));

    ImGui::PopID();
}

// Un PANNEAU DE GROUPE : titre a l'accent, contenu en dessous.
//
// C'est ce qui remplace les `---` d'ImGui, qui reignent le menu en lignes de
// tirets et donnent l'impression d'une liste de debug plutot que d'un panneau.
//
// RAII, et BeginChild : une premiere version dessinait le fond a la main avec
// GetContentRegionAvail(), qui RETRECIT a chaque ligne ajoutee — la hauteur du
// cadre aurait donc dependre de l'ordre de dessin, et le panneau aurait ete
// trop court des que son contenu aurait grandi. BeginChild sait se mesurer
// seul.
class Panneau {
public:
    explicit Panneau(const char* titre) : titre_(titre)
    {
        const ImVec2 dispo = ImGui::GetContentRegionAvail();
        ImGui::Dummy(ImVec2(0.0f, 4.0f));

        ImGui::PushStyleColor(ImGuiCol_ChildBg, carte());
        ImGui::PushStyleColor(ImGuiCol_Border, bordure());
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(13.0f, 12.0f));

        ImGui::BeginChild(titre, ImVec2(dispo.x, 0.0f),
                          ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,
                          ImGuiWindowFlags_NoScrollbar |
                              ImGuiWindowFlags_NoScrollWithMouse);

        ImGui::TextColored(accent(), "%s", titre_);
        ImGui::Dummy(ImVec2(0.0f, 6.0f));
    }

    ~Panneau()
    {
        ImGui::EndChild();
        ImGui::PopStyleVar(3);
        ImGui::PopStyleColor(2);
        ImGui::Dummy(ImVec2(0.0f, 12.0f));
    }

    Panneau(const Panneau&) = delete;
    Panneau& operator=(const Panneau&) = delete;

private:
    const char* titre_;
};

// Une case a cocher qui ressemble a une case a cocher : cadre sombre, coche
// blanche quand elle est pleine, cadre qui s'allume a l'accent au survol, et le
// libelle qui s'atténue quand elle est décochée.
inline bool case_a_cocher(const char* libelle, bool* valeur)
{
    ImGui::PushID(libelle);

    const float h = ImGui::GetTextLineHeight();
    const ImVec2 t(h * 1.05f, h * 1.05f);

    ImGui::InvisibleButton("##case", t);
    const bool survole = ImGui::IsItemHovered();
    bool change = false;
    if (ImGui::IsItemClicked()) {
        *valeur = !*valeur;
        change = true;
    }

    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 p = ImGui::GetItemRectMin();
    const ImVec2 q(p.x + t.x, p.y + t.y);
    const float r = t.x * 0.30f;

    if (*valeur) {
        dl->AddRectFilled(p, q, coul(accent()), r);
        const ImVec2 a(p.x + t.x * 0.26f, p.y + t.y * 0.52f);
        const ImVec2 b(p.x + t.x * 0.43f, p.y + t.y * 0.73f);
        const ImVec2 c(p.x + t.x * 0.76f, p.y + t.y * 0.28f);
        const ImVec2 pts[3] = {a, b, c};
        dl->AddPolyline(pts, 3, coul(fond()), 2.2f);
    } else {
        dl->AddRectFilled(p, q, coul(fond()), r);
        dl->AddRect(p, q, coul(survole ? accent() : ImVec4(0.34f, 0.32f, 0.40f, 1.0f)),
                    r, 0, survole ? 2.0f : 1.6f);
    }

    // Le libelle, centre sur la case.
    //
    // On ne convertit RIEN. `p` est deja en coordonnees ECRAN, donc on ecrit
    // en coordonnees ecran. C'est la seule facon de ne pas se tromper, et ca
    // resout d'un coup les trois versions de ce bug :
    //
    //   1. lire en ecran et ecrire en local  -> decalage = position fenetre
    //   2. ecran moins position fenetre, sans le scroll
    //      -> decalage = defilement, et le libelle remonte des qu'on scrolle
    //   3. le correctif 2, qui marchait... jusqu'au premier scroll
    //
    // Le correctif 2 etait deja faux et il a tenu : il ne se voyait qu'en
    // faisant defiler la fenetre, ce qu'on ne fait pas d'habitude.
    const float h_texte = ImGui::GetTextLineHeight();
    ImGui::SameLine(0.0f, 11.0f);
    ImGui::SetCursorScreenPos(
        ImVec2(p.x + t.x + 11.0f, p.y + (t.y - h_texte) * 0.5f));
    ImGui::TextColored(*valeur ? texte() : texte_faible(), "%s", libelle);

    ImGui::PopID();
    return change;
}

// Un curseur qui ressemble a un curseur : piste fine, poignée ronde violette,
// valeur en clair a droite.
inline bool curseur(const char* libelle, float* valeur, float mini, float maxi,
                    const char* format = "%.1f")
{
    ImGui::PushID(libelle);
    const float l = ImGui::GetContentRegionAvail().x - 62.0f;

    ImGui::TextUnformatted(libelle);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(std::max(l, 60.0f));
    const bool change = ImGui::SliderFloat("##v", valeur, mini, maxi, format);
    ImGui::PopID();
    return change;
}

// Titre de page, avec le trait d'accent qui donne le ton.
inline void entete(const char* titre)
{
    ImGui::Dummy(ImVec2(0.0f, 4.0f));
    ImGui::Spacing();
    ImGui::TextColored(texte(), "%s", titre);

    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(p.x, p.y + 3.0f), ImVec2(p.x + 34.0f, p.y + 5.0f), coul(accent()), 1.0f);
    ImGui::Dummy(ImVec2(0.0f, 12.0f));
}

}  // namespace specter::render