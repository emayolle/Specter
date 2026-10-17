// Specter.Internal — ouverture automatique des coffres (case a cocher).
//
// UNE CASE, UN BOOLEAN, UN EMPLACEMENT.
//
// Le pendant exact de features/autofarm, pour l'autre moitie du travail : ce que
// l'auto-farm ecarte, cette boucle le garde. Le filtre est le meme dans les
// deux sens — une entite `isChest` dont la config de jeu dit « coffre », ou dont
// la marque la plus proche a moins de 3 u porte markConfigId 10506 — donc les
// deux boucles ne peuvent pas viser la meme cible.
//
// CE QUI EST ICI, ET RIEN D'AUTRE
//
//   flag()        l'adresse du bool, pour que `specter.var.coffres` et la case
//                 soient LE MEME stockage -- pas deux copies, dont une qui se
//                 desynchronise a un relog
//   ouverts()     ce que le script a reellement ouvert, pour que la case dise
//                 si elle fait quelque chose
//   draw_ui()     la case, le compteur, et la phase courante
//   init()        rien a installer
//
// PAS DE LUA ICI. Toute la boucle est dans scripts/chest-open.lua, embarque et
// joue une fois par nouveau lua_State. C'est le meme choix que l'autofarm : une
// chose qui doit survivre a un relog appartient a un fichier qu'on rejoue, pas a
// un chunk qu'une DLL doit se rappeler d'envoyer.
//
// LE PILOTE EST DANS LE SCRIPT, PAS ICI
//
// Une fois par demi-seconde, scripts/chest-open.lua lit `specter.var.coffres` et
// demarre ou arrete. Il n'a pas de booleen propre : il n'y a donc rien qui
// puisse diverger de la case. Le C++ n'a pas a pousser vers Lua, et Lua n'a pas a
// interroger le C++ autrement qu'en lisant le flag -- une ecriture, une lecture,
// pas de canal, pas de thread.
//
// UNE SEULE BOUCLE SE DEPLACE A LA FOIS
//
// `specter.tp.here` annule le deplacement precedent : deux boucles qui se
// teleportent en meme temps s'annulent, et aucune n'arrive. Le script s'ecarte
// donc quand `specter.var.autofarm` est vrai, et la case le dit — sinon
// l'utilisateur coche les deux et comprend que rien ne se passe.

#pragma once

namespace specter::features {
namespace chests {

// Le booleen, comme ADRESSE : `specter.var.coffres` doit lire et ecrire le meme
// octet que la case. Un getter et un setter re-creeraient le probleme des deux
// copies que ce module supprime.
bool* flag();

// Ce que le script a ouvert depuis le dernier changement de scene. Ecrit par
// Lua a travers `specter.var.coffres_ouverts`, lu par la case pour l'afficher.
//
// Ecrit SEULEMENT apres avoir vu l'entite disparaitre. Un compteur qui
// compterait les appels d'API serait le mensonge qu'on a deja retire une fois de
// l'autofarm : rendre sans erreur n'est pas avoir ouvert.
int* ouverts();

// Les teleports qui n'ont pas amene. Ecrit par Lua quand un coffre n'a pas ete
// atteint dans le delai, lu par la case.
//
// SON EXISTENCE EST LE POINT. Sans lui, une boucle incapable de se deplacer est
// silencieuse : elle cherche, elle rate, elle passe au suivant, et la case
// affiche « cherche des coffres » sans jamais rien ouvrir. C'est exactement ce
// qui s'est produit quand le TP a cesse de fonctionner pendant une session
// entiere : rien ne l'a dit. Un compteur qui reste a zero quand la case dit
// « cherche » est un diagnostic ; son absence n'en est pas un.
int* echecs();

// Les erreurs du pilote Lua, et la derniere. LE PILOTE EST UN pcall, ET UN
// pcall QUI AVALE EST UNE PANNE MUETTE.
//
// C'est mesure : la case etait cochee, la boucle demarrait, et chaque tick de son
// pilote echouait sur un `E.regles` nil. Le pcall appelait arreter(), la boucle
// se remettait a zero, le pilote recommençait -- vingt fois par seconde, sans
// jamais rien dire. Le menu affichait « cherche des coffres », 0 ouvert, 0 echec
// de TP. Un menu qui ment parce qu'il n'a pas de ligne d'erreur est un menu
// qu'on peut croire pendant des heures.
int* erreurs();

// Les coffres qui ont COUTE DES PV. Ecrit par Lua a la fin d'un cycle
// d'ouverture ou le joueur a perdu un coeur, lu par la case.
//
// L'ouverture COMPTE malgre tout : le coffre est bien ouvert. Les deux faits
// sont vrais, et c'est le second qu'on ne voyait pas -- une boucle qui enchaîne
// les coffres dans une zone d'Aniipods enayarne six, le compteur monte, et rien
// ne dit pourquoi la vie descend.
int* gagnes();

// Le cycle courant, pour l'affichage. Ecrit par le script, lu par la case.
// 0 = inactif, 1 = cherche, 2 = ouvre, 3 = attend, 4 = laisse la place a
// l'auto-farm.
int* phase();
const char* phase_label(int valeur);

void draw_ui();

}  // namespace chests
}  // namespace features