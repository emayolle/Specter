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
    // APRES le Dummy : c'est la ou le curseur doit se retrouver.
    const ImVec2 apres = ImGui::GetCursorScreenPos();

    // Zone cliquable par-dessus, posee SANS deplacer le curseur : un
    // InvisibleButton avance le curseur comme n'importe quel item, donc sans ce
    // retour les pages de la nav se reservaient DEUX lignes chacune — c'est
    // l'ecart enorme entre Joueur et Monde.
    ImGui::SetCursorScreenPos(depart);
    ImGui::InvisibleButton("##zone", ImVec2(largeur + marge, hauteur));
    ImGui::SetCursorScreenPos(apres);

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

// UN BOUTON SECONDAIRE : petit, sobre, a droite d'une ligne.
//
// SmallButton d'ImGui sort du theme : meme hauteur, meme police, mais un fond
// neutre sans le liseré des boutons du style, et il se lit comme un lien plutot
// qu'un bouton. Sur une liste de trente waypoints, trente liens a cote de
// coordonnees, c'est exactement ce qu'il ne faut pas.
//
// Ici le libelle s'aligne sur la ligne, et la zone cliquable a exactement la
// taille du texte — donc le bouton ne mange pas de largeur pour rien.
inline bool bouton_ligne(const char* libelle)
{
    ImGui::PushID(libelle);
    const ImVec2 d = ImGui::GetCursorScreenPos();
    const float h = ImGui::GetTextLineHeight();
    const ImVec2 txt = ImGui::CalcTextSize(libelle);

    // UNE CAPSULE BORDEE, pas du texte gris.
    //
    // Sans cadre, « Teleport » se lit comme une etiquette : rien ne dit qu'on
    // peut cliquer. Un panneau plein de reperes finit par avoir trente fois le
    // meme mot, et c'est exactement le genre de repetition qui fait qu'une
    // interface parait accidentelle.
    const float pad = 10.0f;
    const ImVec2 q(d.x + txt.x + pad * 2.0f, d.y + h);
    const ImVec2 p0(d.x, d.y + 1.0f);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    const bool survole = ImGui::IsMouseHoveringRect(p0, q, true);

    if (survole) {
        dl->AddRectFilled(p0, q, coul(accent()), 5.0f);
    } else {
        dl->AddRectFilled(p0, q, coul(panneau()), 5.0f);
        dl->AddRect(p0, q, coul(bordure()), 5.0f, 0, 1.0f);
    }

    // LE TEXTE PASSE PAR LE FLUX NORMAL : l'appelant a deja fait SameLine, donc
    // il se place sur la meme ligne, et le curseur avance comme ImGui veut.
    // Seule la zone cliquable est posee en absolu — un Dummy suivi d'un retour
    // en arriere faisait retomber le bouton a la ligne suivante.
    ImGui::Dummy(ImVec2(pad, 0.0f));
    ImGui::SetCursorScreenPos(ImVec2(d.x + pad, d.y + 1.0f));
    ImGui::TextColored(survole ? fond() : texte(), "%s", libelle);

    ImGui::SetCursorScreenPos(p0);
    ImGui::InvisibleButton("##b", ImVec2(q.x - p0.x, q.y - p0.y));
    const bool clic = ImGui::IsItemClicked();

    // On rend la main APRES le bouton, pas a sa place.
    ImGui::SetCursorScreenPos(q);
    ImGui::Dummy(ImVec2(0.0f, h));

    ImGui::PopID();
    return clic;
}

// Un TITRE DE SECTION a l'interieur d'un panneau : trait d'accent a gauche,
// libelle en dessous. Remplace le Separator + « Zone %d » colle au bord.
inline void titre_section(const char* libelle)
{
    const ImVec2 d = ImGui::GetCursorScreenPos();
    const float h = ImGui::GetTextLineHeight();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(ImVec2(d.x, d.y + 1.0f), ImVec2(d.x + 3.0f, d.y + h - 1.0f),
                      coul(accent()), 1.5f);

    // LE DUMMY QUI DECALAIT LE TIRET.
    //
    // La version d'avant faisait Dummy(11, 0) pour indenter, puis TextColored.
    // Or Dummy — meme de hauteur nulle — fait passer le curseur A LA LIGNE
    // SUIVANTE. Le tiret, dessine avant, se retrouvait donc une ligne au-dessus
    // du mot : on lisait « Zone 20200 » avec un trait flotte au-dessus.
    //
    // Tout en ecran, et une seule ligne reservee a la fin.
    ImGui::SetCursorScreenPos(ImVec2(d.x + 11.0f, d.y));
    ImGui::TextColored(texte(), "%s", libelle);

    ImGui::SetCursorScreenPos(d);
    ImGui::Dummy(ImVec2(0.0f, h));
}

// UNE LIGNE DE REPERE : nom, coordonnees, bouton.
//
// Les trois objets tenant sur UNE ligne. La version d'avant les empilait avec
// des Dummy(10, 0) d'indentation, et chacun faisait sauter une ligne : d'ou
// l'ecart enorme entre « Floraison » et « Colline de primepousse ».
//
// Ici tout est en ecran, et la ligne est reservee une seule fois, a la fin.
inline bool ligne_repere(const char* nom, float x, float y, float z,
                         const char* action)
{
    ImGui::PushID(nom);
    const ImVec2 d = ImGui::GetCursorScreenPos();
    const float h = ImGui::GetTextLineHeight();
    const float marge = 10.0f;

    // Nom, puis coordonnees attenuees, cote a cote.
    ImGui::SetCursorScreenPos(ImVec2(d.x + marge, d.y));
    ImGui::TextUnformatted(nom);

    const float l_nom = ImGui::CalcTextSize(nom).x;
    ImGui::SetCursorScreenPos(ImVec2(d.x + marge + l_nom + 12.0f, d.y));
    char xyz[64];
    std::snprintf(xyz, sizeof(xyz), "(%.1f, %.1f, %.1f)", x, y, z);
    ImGui::TextColored(texte_faible(), "%s", xyz);

    // Bouton a droite, toujours au meme endroit quelle que soit la longueur du
    // nom : aligne, on lit une colonne de boutons au lieu d'un texte a saute.
    // LE BOUTON PREND LA HAUTEUR DE LA LIGNE.
    //
    // Il faisait la taille du texte plus deux pixels : au milieu d'une ligne de
    // 24 px, un bouton de 20 px paraissait Petit, et c'etait le seul element
    // de la ligne qui ne touchait ni le haut ni le bas. Un rectangle qui ne
    // remplit pas sa ligne se lit comme un titre, pas comme une action.
    const ImVec2 t_btn = ImGui::CalcTextSize(action);
    const float pad = 12.0f;
    const ImVec2 p0(d.x + ImGui::GetContentRegionAvail().x - t_btn.x - pad * 2.0f,
                     d.y);
    const ImVec2 q(p0.x + t_btn.x + pad * 2.0f, d.y + h);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    const bool survole = ImGui::IsMouseHoveringRect(p0, q, true);
    if (survole) {
        dl->AddRectFilled(p0, q, coul(accent()), 5.0f);
    } else {
        dl->AddRectFilled(p0, q, coul(panneau()), 5.0f);
        dl->AddRect(p0, q, coul(bordure()), 5.0f, 0, 1.0f);
    }
    ImGui::SetCursorScreenPos(
        ImVec2(p0.x + pad, p0.y + (h - ImGui::GetTextLineHeight()) * 0.5f));
    ImGui::TextColored(survole ? fond() : texte(), "%s", action);

    ImGui::SetCursorScreenPos(p0);
    ImGui::InvisibleButton("##act", ImVec2(q.x - p0.x, q.y - p0.y));
    const bool clic = ImGui::IsItemClicked();

    // UNE SEULE ligne reservee.
    ImGui::SetCursorScreenPos(d);
    ImGui::Dummy(ImVec2(0.0f, h));

    ImGui::PopID();
    return clic;
}

// Une case a cocher qui ressemble a une case a cocher : cadre sombre, coche
// blanche quand elle est pleine, cadre qui s'allume a l'accent au survol, et le
// libelle qui s'atténue quand elle est décochée.
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