// Specter.Internal — le menu est ImGui, et rien d'autre.
//
// IMGUI BRUT. AUCUNE RETOUCHE.
//
// Ce fichier a ete vide de widgets pendant des mois, puis il en avait neuf, puis
// il en a un. L'etat actuel est le bon : il n'y a RIEN a ajouter.
//
//   Ancien etat (des widgets maison)          Etat actuel
//   ------------------------------------      --------------------------------
//   Panneau, case_a_cocher, curseur,          rien : ImGui::Checkbox,
//   bouton, bouton_ligne, bouton_a_x,                     ImGui::SliderFloat,
//   ligne_repere, titre_section,                          ImGui::Button,
//   entree_nav                                            ImGui::BeginTable,
//                                                        ImGui::SeparatorText
//
// Chaque widget maison etait une reconstruction d'un widget qu'ImGui fournit
// deja, et chacun a paye : voir d3d12_overlay.cpp, ou BeginTabItem et la
// gestion des ID sont commentes en detail.
//
// Ce qu'ImGui ne fournit pas, c'est la COULEUR et la POLICE. Les deuxetaient
//posees ici — sept ImVec4, une police Inter, une police Lucide, des arrondis,
// des marges. Ce sont ces retouches-la que « ImGui nu » veut dire qu'on retire.
//
// POURQUOI C'EST MIEUX, ET PAS SEULEMENT PLUS SIMPLE
//
// 1. ImGui 1.92 a 14 style-vars et 60 couleurs. Les retoucher a la main, c'est
//    se tromper sur ce qui est couvert par defaut. StyleColorsDark() couvre tout
//    d'un coup, et reste juste quand ImGui change.
//
// 2. Un style fige casse les entrees au clavier. ImGui dessine le focus avec
//    TabHighlightAlpha ; une couleur posee a la main le remplace par du gris
//    fixe, et on ne sait plus ou on est.
//
// 3. ProggyClean — la police par defaut — n'est pas un oubli, c'est ce que
//    « ImGui tel quel » veut dire. Les libelles se lisent. Ce qui ne se lit pas,
//    c'est ce qu'on ecrit : c'est une question de contenu, pas de rendu.
//
// RIEN ICI NE DEPEND DU C++ DU MENU
//
// Aucune feature, aucun registre. Ce fichier ne contient que des couleurs, et
// meme plus.
//
// Si un jour une feature a BESOIN deDessiner — une liste de 200 reperes, un
// graphe —, qu'elle utilise ImGui::GetWindowDrawList() sur place, dans le .cpp
// de la feature. Un wrapper partage n'ameliore rien : il recree exactement le
// probleme qu'on vient de resoudre.

#pragma once

#include "imgui.h"