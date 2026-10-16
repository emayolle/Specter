// Specter.Internal — auto-farm (case a cocher).
//
// UNE CASE, UN BOOLEAN, UN EMPLACEMENT.
//
// La demande etait : « integrer dans le menu une checkbox autofarm, et mettre
// la boucle en boucle sans s'arreter avec un if qui utilise le booleen cpp
// passe par bridge ». Le `if` et le booleen existent deja, cote C++. Il ne
// restait que la case.
//
// CE QUI EST ICI, ET RIEN D'AUTRE
//
//   flag()        l'adresse du bool, pour que `specter.var.autofarm` et la
//                 case soient LE MEME stockage -- pas deux copies, dont une
//                 qui peut se desynchroniser a un relog
//   draw_ui()     la case, et le compteur d'ouvertures pour qu'elle dise
//                 si elle fait quelque chose
//   init()        rien a installer
//
// PAS DE LUA ICI. Toute la boucle est dans scripts/autofarm_loop.lua, embarque
// et joue une fois par nouveau lua_State. C'est le meme choix que
// inf_stamina : une chose qui doit survivre a un relog appartient a un fichier
// qu'on rejoue, pas a un chunk qu'une DLL doit se rappeler d'envoyer.
//
// LE PILOTE EST DANS LE SCRIPT, PAS ICI
//
// Une fois par demi-seconde, scripts/autofarm_loop.lua lit `specter.var.autofarm`
// et demarre ou arrete. Il n'a pas de booleen propre : il n'y a donc rien qui
// puisse diverger de la case. Le C++ n'a pas a pousser vers Lua, et Lua n'a pas
// a interroger le C++ autrement qu'en lisant le flag -- une ecriture, une
// lecture, pas de canal, pas de thread.
//
// POURQUOI UNE CASE PLUTOT QU'UN SCRIPT A LANCER
//
// Le lancement manuel avait un cout qu'on ne voyait pas : le joueur devait
// declencher la chaine, attendre, relancer. Et surtout le gel de 1.4 s au
// changement de zone (mesure : `pump 1408.634 ms`) ne se voit QUE si on teleporte
// beaucoup. Une case qu'on laisse cochee rend ce cout regulier et visible au
// lieu de le laisser Hair au hasard d'une session.

#pragma once

namespace specter::features {
namespace autofarm {

// Le booleen, comme ADRESSE : `specter.var.autofarm` doit lire et ecrire le
// meme octet que la case. Un getter et un setter re-creeraient le probleme des
// deux copies que ce module supprime.
bool* flag();

// Ce que le script a ouvert depuis le dernier demarrage. Ecrit par Lua a
// travers `specter.var.autofarm_ouverts`, lu par la case pour l'afficher.
int* ouverts();

void set_enabled(bool on);
bool enabled();

// Le cycle courant et l'etat de la boucle, pour l'affichage. Ecrits par le
// script, lus par la case. 0 = inactif, 1 = cherche, 2 = ouvre, 3 = attend.
int* phase();
const char* phase_label(int valeur);

void draw_ui();

}  // namespace autofarm
}  // namespace features