// Specter.Internal — deux groupes de controles. Pas des widgets.
//
// CE QUE CE FICHIER NE FAIT PAS
//
// Il ne reecrit aucun widget d'ImGui. Ni case, ni curseur, ni bouton, ni
// panneau dessine au draw list. Ces neuf wrappers ont existe ici, ils ont ete
// retires, et le menu est revenu a ImGui::Checkbox / SliderFloat / Button.
//
// Ce qui suit n'est que de l'IMGUI NATIF mis en forme deux fois.
//
//   Group      BeginChild(ImGuiChildFlags_Borders) + un titre. RAII.
//   SliderRow  BeginTable a deux colonnes : libelle, puis SliderFloat.
//
// Ce ne sont pas des widgets parce qu'ils ne redessinent rien : ils appellent
// ce qu'ImGui appelle. BeginChild a besoin d'un EndChild, et une table a besoin
// de ses TableNextRow — en C++ sans RAII, chaque fin de fonction oublie un End.
// C'est la seule raison d'etre de ces deux classes.
//
// CE QU'ELLES RESOLVENT
//
// Les deuxReferences lues avant d'ecrire ces lignes (deux menus de triche
//Imgui publies, lus en image) se recoupent sur deux points :
//
//   1. Les controles sont GROUPES par cadre. Un titre, une boite, les options
//      dedans. C'est ce qui fait qu'une page de dix options se lit en
//     .categories au lieu de se lire en liste.
//
//   2. Le libelle d'un curseur est a GAUCHE, la piste au centre, la valeur a
//      droite. SliderFloat fait l'inverse : il ecrit le libelle APRES la piste.
//      Un curseur se reconnait a son nom, donc le nom est a gauche.
//
// ET CE QUE LE MENU N'A PAS, PARCE QUE C'ETAIT LE PROBLEME SIGNE
//
// Un menu qui explique tout, a l'ecran, n'est pas un menu informatif : c'est un
// menu illisible. Mesure : « Auto-ouverture (SEULEMENT les coffres, rien
// d'autre) » et « desactive -- les vitesses originales sont restaurees » et
// « position inconnue - entre dans le monde », tout sur la meme page.
//
// Donc : a l'ecran, le nom court et le nombre. Le POURQUOI reste au survol.
// Une mesure reste dans l'infobulle -- elle ne coute rien, elle ne s'affiche
// que si on la cherche, et c'est la que l'information se lit vraiment.
//
// RIEN ICI NE DEPEND DU C++ DU MENU
//
// Aucune feature, aucun registre. Si une feature a besoin de dessiner 200
// reperes ou un graphe, qu'elle prenne ImGui::GetWindowDrawList() sur place,
// dans son .cpp : un wrapper partage n'ameliore rien.

#pragma once

#include "imgui.h"

namespace specter {
namespace render {

// UNE CARTE : un titre, un cadre, les controles dedans.
//
// PAS DE AutoResizeY. IMBRIQUE, C'EST UN CRASH — et ImGui le dit lui-meme.
//
// La premiere version porta AutoResizeY, pour que la carte se mesure sur son
// contenu. C'etait l'intention, et l'onglet « World » plantait a l'ouverture.
//
// La cause est dans imgui.cpp, sur le chemin AutoResizeY :
//
//     [EXPERIMENTAL] Breaks on nested Begin/End pairs.
//
// Un BeginChild en AutoResizeY doit mesurer son contenu ET borner son parent
// dans la MEME frame. Embole dans un BeginChild scrollable — c'est exactement
// le cas « World », dont la liste des reperes est un BeginChild qui defile, et
// qui contient UNE carte par zone — la mesure se mord la queue : chaque
// mesure du parent change la place disponible pour l'enfant, qui change sa
// propre taille, qui change celle du parent. La boucle ne sort pas.
//
// Ce n'est donc PAS une height de 0, ni un dereferencement nul : c'est une
// boucle de mesure, et elle est fatale dans la frame ou elle se serre.
//
// On garde le cadre, on retire le flag. Une carte a donc une taille fixe —
// celle de son contenu a la premiere frame. C'est le compromis : ImGui ne sait
// pas faire les deux, et « savoir les deux » vaut mieux qu'un onglet qui
// plante.
class Group {
public:
    // `hauteur` a 0 = toute la place disponible de la page. C'est le defaut,
    // et c'est ce qu'il faut pour une carte de controles : elle a un nombre de
    // lignes connu, donc une hauteur qui colle au contenu est un detail, et le
    // prix a payer est un espace vide en bas de la carte.
    // `hauteur` a 0 = se mesurer sur son contenu (AutoResizeY).
    //
    // RESERVEE AUX CARTES NON IMBRIQUEES. AutoResizeY mesure la carte ET borne
    // son parent dans la MEME frame : dans un parent qui defile, la mesure se
    // mord la queue. C'est experimentale et ImGui le dit — voir le gros
    // commentaire plus haut.
    //
    // Hors de ce cas-la, donner une hauteur. C'est moins joli, mais c'est la
    // seule facon honnete : la hauteur d'une BeginChild doit etre CONNUE avant
    // le rendu, donc devinee, donc un jour fausse. Une fausse par defaut, ca
    // fait un vide sous le contenu — un tableau, lui, se mesure pour de vrai.
    explicit Group(const char* titre, float hauteur = 0.0f) : titre_(titre)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 8.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        // LA HAUTEUR EST DONNEE PAR L'APPELANT. JAMAIS MESUREE.
    //
    // Le defaut anterior — GetContentRegionAvail().y — etait FAUX, et c'est lui
    // qui gelait l'application a l'injection, meme sans ouvrir le menu.
    //
    // Il y a deux manieres de se tromper, et la premiere ne se voit pas :
    //
    //   1. AutoResizeY (retire) : la carte se mesure ELLE-MEME. Embole dans un
    //      BeginChild qui defile, la mesure se mord la queue — boucle, gel.
    //
    //   2. La place DISPONIBLE : la carte est plus petite que son contenu. Un
    //      SliderFloat qui deborde fait alors defiler l'interieur de l'enfant,
    //      dans un parent qui defile deja. Deux niveaux de defilement emboites,
    //      et ImGui recalcule la visibilite a chaque item.
    //
    // Le second est plus sournois parce qu'il ne demande aucun imbrication :
    // il suffisait d'une carte avec 7 curseurs dans la page par defaut. Et il
    // gele, pas ne plante — parce que la boucle de mesure ne rend jamais la
    // main, au lieu de sortir en erreur.
    //
    // Donc : la hauteur vient de l'appelant, qui COMPTE ses lignes. Compter
    // d'abord, construire ensuite — l'inverse d'AutoResizeY, donc pas de boucle
    // possible. Et le defaut n'est PAS la place disponible : c'est AsIs, qui
    // laisse la carte se contenir elle-meme.
    const float h = hauteur;
    // BeginChild PEUT RETOURNER FALSE, et c'est NORMAL.
    //
    // Il rend false quand la fenetre est sautee — hors de l'ecran, ou trop
    // haute pour ce qui reste. Dans ce cas ImGui pose SkipItems : tout item
    // suivant est ignore. BeginTable est appele quand meme, il rend lui aussi
    // false, et g.CurrentTable reste NUL.
    //
    // La suite hurle alors : TableSetupColumn et TableHeadersRow verifient
    // qu'elles sont dans un BeginTable, et echouent sur :
    //
    //     Call should only be done while in BeginTable() scope!
    //
    // Ce n'etait pas une hypothese : /tmp/specter-imgui-assert.txt contenait
    // exactement ces quatre lignes, et le jeu crashait une frame apres
    // l'affichage.
    //
    // Le correctif N'EST PAS ici : Begin/End doivent toujours etre apparies —
    // EndChild reste obligatoire meme quand BeginChild rend false. Ce qu'on
    // peut, c'est que BeginTable et ses appelants respectent le false.
    // Donc Group expose `ouvert()`, et BeginTable le teste.
    ouvert_ = ImGui::BeginChild(titre, ImVec2(0.0f, h),
                                ImGuiChildFlags_Borders,
                                ImGuiWindowFlags_NoScrollbar);
    if (ouvert_ && titre_ && *titre_) {
        ImGui::TextDisabled("%s", titre_);
    }
    }

    // La carte a-t-elle ete dessinee ? Begin/End restent apparies dans tous
    // les cas — voir ci-dessus. C'est BeginTable, appele A L'INTERIEUR, qui doit
    // consulter ce flag.
    bool ouvert() const { return ouvert_; }

    ~Group()
    {
        ImGui::EndChild();
        ImGui::PopStyleVar(3);
    }

    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;

private:
    const char* titre_;
    bool ouvert_ = false;
};

// UN CURSEUR : libelle a gauche, piste a droite.
//
// SliderFloat met le libelle APRES la piste : le nom est donc a droite de la
// barre, ce qui n'est l'usage de personne. Un curseur se reconnait a son nom,
// donc le nom passe a gauche, dans une colonne de largeur fixe.
//
// Le tableau, et non deux textes a la main : une table aligne ses colonnes toute
// seule. C'etait l'arriere-plan de bouton_a_x et de ligne_repere, tous deux
// poses en ABSOLU avec un report de curseur a la main — deux systemes de
// coordonnees, et le piege qui va avec.
//
// `largeur_nom` est une colonne, pas une largeur de widget : tous les curseurs
// d'une carte partagent le meme x pour leur piste, donc les barres sont
// alignees meme si les noms ont des longueurs differentes.
inline bool slider_row(const char* libelle, float* valeur, float mini,
                       float maxi, const char* format,
                       float largeur_nom = 130.0f)
{
    ImGui::PushID(libelle);

    // Si la fenetre englobante est sautee (SkipItems), BeginTable rend false et
    // CurrentTable reste NUL : TableSetupColumn et TableHeadersRow verifient
    // qu'elles sont dans une table et plantent sur :
    //
    //     Call should only be done while in BeginTable() scope!
    //
    // Mesure : quatre de ces assertions, puis le jeu mort une frame apres.
    //
    // BeginChild pose SkipItems tant que la fenetre est hors ecran, et ImGui
    // ne remet pas l'etat tout seul. Sans ce test, un curseur invisible dans
    // une carte invisible fait tomber le processus. (Voir Group::ouvert et
    // l'argumentaire dans Group.)
    if (!ImGui::BeginTable("##s", 2,
                           ImGuiTableFlags_SizingStretchProp |
                               ImGuiTableFlags_NoSavedSettings)) {
        ImGui::PopID();
        return false;
    }
    ImGui::TableSetupColumn("nom", ImGuiTableColumnFlags_WidthFixed, largeur_nom);
    ImGui::TableSetupColumn("piste", ImGuiTableColumnFlags_WidthStretch);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted(libelle);
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(-1.0f);

    // "##v" : le libelle est deja ecrit dans la colonne de gauche. Sans le
    // "##", ImGui prendrait la chaine comme ID — et deux curseurs de MEME nom
    // dans deux cartes deviendraient un seul curseur.
    const bool change = ImGui::SliderFloat("##v", valeur, mini, maxi, format);

    // La bulle porte sur le CURSEUR : c'est le dernier item, et c'est lui.
    // IsItemHovered() apres le EndTable porterait sur le tableau entier.
    const bool survol = ImGui::IsItemHovered();
    ImGui::EndTable();
    ImGui::PopID();
    (void)survol;
    return change;
}

}  // namespace render
}  // namespace specter
