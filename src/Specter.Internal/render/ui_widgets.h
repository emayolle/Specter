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
// BeginChild avec ImGuiChildFlags_AutoResizeY, donc la carte se mesure sur son
// contenu. C'est du stock, et c'est important : la version d'avant mesurait la
// hauteur a la main avec GetContentRegionAvail, qui RETRECIT a chaque ligne
// ajoutee — la hauteur du cadre dependait donc de l'ordre de dessin, et le
// cadre etait trop court des que son contenu grandissait.
class Group {
public:
    explicit Group(const char* titre) : titre_(titre)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 8.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        ImGui::BeginChild(titre, ImVec2(0.0f, 0.0f),
                          ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);
        if (titre_ && *titre_) {
            // TextDisabled, pas SeparatorText : le separateur avec son trait
            // etait demande a disparaitre. Le titre en gris fait le groupement
            // sans trait.
            ImGui::TextDisabled("%s", titre_);
        }
    }

    ~Group()
    {
        ImGui::EndChild();
        ImGui::PopStyleVar(3);
    }

    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;

private:
    const char* titre_;
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
    ImGui::BeginTable("##s", 2,
                      ImGuiTableFlags_SizingStretchProp |
                          ImGuiTableFlags_NoSavedSettings);
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
