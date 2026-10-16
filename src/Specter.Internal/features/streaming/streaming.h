// Specter.Internal — rayon de streaming de la carte.
//
// CE QUE C'EST
//
// Une variable entiere qui remplace la valeur de
// `FunPlus::WorldX::Stream::Runtime::XSRGlobalManager::GetPerfDistance`, la
// fonction qui traduit le niveau de performance du jeu en rayon de chargement.
// Decompile dans generated/input/GameAssembly.dll.i64 :
//
//     perfLevel <= 10  -> 3
//     perfLevel <= 30  -> 4
//     perfLevel <= 50  -> 5
//     perfLevel <= 70  -> 6
//     perfLevel >  70  -> 12
//
// Le rayon est en CHUNKS de 256 u (TeleportCheckNeedLoadByCollider utilise
// 0.00390625 == 1/256). Donc 3 chunks ~ 768 u, et 12 chunks ~ 3072 u.
//
// CE QUE CA NE FAIT PAS, ET C'EST LE POINT
//
// Ca ne fait PAS apparaître plus d'entités. Le streaming charge des BLOCS de
// terrain ; les coffres, les Aniipods et les PNJ viennent du SERVEUR. Charger
// quatre fois plus de terrain ne garantit donc pas un seul coffre de plus --
// ça coûte des images par seconde, c'est tout.
//
// C'est pour ça que la valeur est une variable lisible et modifiable, et pas
// une constante forcée : la question « est-ce que ça donne plus d'objets » se
// tranche en changeant le chiffre et en comptant, pas en le supposant.
//
// ET LE CHEMIN N'EST PAS CELUI QU'ON CROYAIT
//
// Les constantes `AoiLodConst` de Common/Const/AoiLodConst.lua (lod_level_ranges,
// normal_aoi_max_level, Chest) semblaient commander la zone de chargement.
// Mesure : ecrire x8 sur tous les rayons et mettre normal_aoi_max_level a 7
// n'a change AUCUNE entite chargee (56 avant, 56 apres, sur 7 s de
// deplacement force). Elles ne sont lues par aucun code Lua, et leur nom
// n'apparait nulle part dans GameAssembly.dll : ce sont des constantes mortes.
//
// Le vrai systeme s'appelle XS / XSR (le "@fjs XS." des logs du jeu), il est
// en C++, et c'est celui-la qu'on detourne.
//
// L'ASTUCE UTILE, TROUVEE AU PASSAGE
//
// TeleportCheckNeedLoad pose dist2 = (dx)^2 + (dz)^2, puis :
//
//     if ( dist2 <  5000 )  log "TeleMinRangeDebug info"     (~70.7 u)
//     if ( dist2 <= 1225 )  log "TeleMinRangeDebug skip"  -> return 0
//
// 1225 == 35^2 : en dessous de 35 u, le jeu ne charge RIEN. C'est pour ca que
// le TP sur une cible deja proche ne declenche aucun streaming.

#pragma once

namespace specter::features {
namespace streaming {

// La valeur forcee, comme ADRESSE : `specter.var.stream_distance` doit lire et
// ecrire le meme int que la case.
//
//   0    -> on ne touche a rien, le jeu decide (comportement normal)
//   1..12-> le nombre de chunks a charger autour du joueur
constexpr int kMin = 0;
constexpr int kMax = 12;

int* value();
void set_value(int chunks);
int value_now();

bool install();
bool installed();

// Le nom lisible du mode courant, pour la case. nullptr si on n'a pas force.
const char* current_label();

void draw_ui();

}  // namespace streaming
}  // namespace specter::features