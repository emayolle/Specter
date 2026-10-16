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
// SANS POLICE D'ICONES
//
// Le backend D3D12 n'en embarque aucune. En ajouter une pour six libelles ne
// vaut pas le cout, alors la navigation se fait au libelle, avec un trait
// d'accent a gauche pour la page courante.
//
// RIEN ICI NE DEPEND DU C++ DU MENU
//
// Widgets purs : ils knowledge le style d'ImGui et dessinent. Aucune feature,
// aucun registre. Si une feature s'en sert, c'est qu'elle veut la meme
// apparence que les autres — pas qu'elle a besoin de savoir quoi.

#pragma once

#include "imgui.h"

namespace specter::render {

// La couleur d'accent, et les quatre qui vont avec. Tout le ton du menu tient
// dans ces cinq valeurs : un violet sur un fond presque noir.
inline ImVec4 accent() { return ImVec4(0.58f, 0.36f, 0.92f, 1.00f); }
inline ImVec4 accent_doux() { return ImVec4(0.22f, 0.15f, 0.34f, 1.00f); }
inline ImVec4 fond() { return ImVec4(0.07f, 0.07f, 0.09f, 1.00f); }
inline ImVec4 panneau() { return ImVec4(0.11f, 0.11f, 0.14f, 1.00f); }
inline ImVec4 survol() { return ImVec4(0.17f, 0.16f, 0.22f, 1.00f); }
inline ImVec4 texte() { return ImVec4(0.88f, 0.88f, 0.92f, 1.00f); }
inline ImVec4 texte_faible() { return ImVec4(0.50f, 0.48f, 0.57f, 1.00f); }
inline ImVec4 bordure() { return ImVec4(0.30f, 0.28f, 0.36f, 0.65f); }

// ImGui 1.92 ne prend plus de ImVec4 dans les draw lists : c'est ImU32.
inline ImU32 coul(ImVec4 v)
{
    return ImGui::ColorConvertFloat4ToU32(v);
}

// Une case a cocher qui ressemble a une case a cocher : cadre sombre, coche
// blanche quand elle est pleine, cadre qui s'allume a l'accent au survol, et le
// libelle qui s'atténue quand elle est décochée.
//
// REND VRAI quand l'utilisateur a clique. Le libellé est multi-lignes si besoin :
// tout ce qui suit un retour a la ligne explicite passe dessous.
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

    ImGui::SameLine(0.0f, 11.0f);
    ImGui::AlignTextToFramePadding();
    if (*valeur) {
        ImGui::TextUnformatted(libelle);
    } else {
        ImGui::TextDisabled("%s", libelle);
    }

    ImGui::PopID();
    return change;
}

// Titre de section, avec le trait d'accent qui donne le ton.
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