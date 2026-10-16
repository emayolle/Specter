// Specter.Internal — case « IA des Aniimoe ».
//
// UNE CASE, UN BOOLEAN, UN EMPLACEMENT. Exactement le meme contrat que
// autofarm, et pour les memes raisons (voir features/autofarm/autofarm.h) :
// `specter.var.ani_ia` et la case doivent etre LE MEME octet, sinon on a deux
// copies dont une peut diverger au relog.
//
// PAS DE LUA ICI.
//
// Le pilote est dans scripts/ani_ai.lua, joue une fois par nouveau lua_State. Il
// lit `specter.var.ani_ia` et ecrit Common.Const.AiConst.GLOBAL_OPEN_TICK. Donc
// nullptr install : il n'y a rien a crocheter au demarrage, seulement une case
// et le booleen qu'elle ecrit.
//
// CE QUE LA CASE FAIT
//
//   decochee -> GLOBAL_OPEN_TICK = false : les Aniimoe ne font plus rien
//   cochee   -> GLOBAL_OPEN_TICK = true  : leur IA reprend
//
// Mesure au moment de l'ecriture de ce fichier : GLOBAL_OPEN_TICK valait DEJA
// false dans le build. La case est donc un retour a l'etat normal autant qu'un
// mode a activer -- et l'affichage le dit, plutot que de promettre « desactive »
// sur un jeu ou l'IA tourne deja.
//
// CE QUE LA CASE NE FAIT PAS
//
// Elle n'ecrit dans aucune table du jeu. Une affectation de table toutes les
// 250 ms ne coute rien et elle n'a pas d'alternative : c'est le seul endroit ou
// le jeu lit son propre etat d'IA.

#pragma once

namespace specter::features {
namespace aniai {

// L'adresse du booleen, pour que `specter.var.ani_ia` et la case soient le
// meme stockage. Un getter et un setter re-creeraient deux copies.
bool* flag();

// Ce que le script a reellement applique, et si AiConst a ete trouve.
// Ecrit par Lua, lu par la case. 0 = introuvable, sinon 1 = IA activee,
// 2 = IA desactivee.
int* etat();
const char* etat_label(int valeur);

void draw_ui();

}  // namespace aniai
}  // namespace features