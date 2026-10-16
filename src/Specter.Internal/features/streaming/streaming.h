// Specter.Internal — rayon de streaming de la carte.
//
// CE QUE C'EST, CORRIGE
//
// Une variable entiere qui remplace la valeur de
// `FunPlus::WorldX::Stream::Runtime::XSRGlobalManager::GetPerfDistance`.
//
// PREMIERE VERSION, FAUSSE : j'ai ecrit que c'etait un rayon en chunks. Le
// consommateur dit le contraire -- XSRBlockTile::CalcThisTileLodLevel :
//
//     dx = |tile.GlobalTileX - agentTileX|
//     dz = |tile.GlobalTileZ - agentTileZ|
//     d  = max(dx, dz)        // distance de Chebyshev, EN TUILES
//     if (d > 12) return 12;  // PLAFOND DUR DU MOTEUR
//
// C'est donc un NIVEAU DE PORTEE / DETAIL, en tuiles, et pas une distance
// convertible.
//
// DEUX CONSEQUENCES, DEFINITIVES
//
// 1. On ne peut PAS afficher de metres. La taille d'une tuile en unites monde
//    n'est exposee nulle part de facon fiable : AoiLodConst.SPACE_TILE_SIZE = 64
//    vient de la table de constantes MORTE (voir plus bas).
//
// 2. 12 est le maximum, et il est impose par le moteur, pas par nous.
//    GetPerfDistance ne produit que 3, 4, 5, 6 ou 12. Un curseur qui irait plus
//    haut serait du theatre : notre hook accepterait la valeur, puis le clamp de
//    CalcThisTileLodLevel l'ecraserait. Le curseur s'arrete donc a 12.
//
// DEUX PLAFONDS, ET ILS NE SE REGENT PAS DE LA MEME FACON
//
// (a) GetPerfDistance : le jeu ne produit que 3, 4, 5, 6 ou 12. C'est un
//     detour, on peut renvoyer ce qu'on veut, et rien en aval ne l'ecrase.
//     D'ou le curseur 0..12 de draw_ui().
//
// (b) CalcThisTileLodLevel : le moteur ecrase la distance elle-meme a 12, dans
//     SON PROPRE CODE. Un detour sur (a) ne peut pas passer ce plafond-la : la
//     valeur trop grande serait ramenee a 12 en aval. C'etait le point que le
//     curseur (a) ne pouvait pas regler, et il fallait un deuxieme levier.
//
// (b) se leve en UN OCTET : l'immediat du `mov ecx, 12`, a RVA 0x18457DC. On
//     garde le code du jeu -- donc on ne peut pas se tromper sur le
//     max(|dx|,|dz|) ni sur les cmovs -- et on revient a l'original en ecrivant
//     0x0C.
//
// LE RISQUE, DIT TEL QU'IL EST
//
// Le consommateur du resultat n'a PAS ete trace : le seul xref entrant est une
// entree de table de pointeurs de methode dans .data, donc l'appel est indirect.
// Impossible de dire statiquement si le systeme de tuiles possede 13 niveaux de
// LOD ou davantage. Si c'est 13, une valeur > 12 demande un niveau qui
// n'existe pas -- et le comportement est alors INCONNU.
//
// C'est pourquoi c'est une variable reglee a la valeur d'origine par defaut, et
// non un patch force : la question se tranche en changeant le chiffre et en
// regardant le jeu, pas en supposant que plus grand veut dire mieux.
//
// CE QUE CA NE FAIT PAS, ET C'EST L'ESSENTIEL
//
// Des BLOCS DE TERRAIN et leur niveau de detail. Pas des entites : celles-ci
// viennent du SERVEUR. Charger plus de detail ne garantit donc aucun coffre de
// plus -- ca coute des FPS, c'est tout.
//
// C'est pour ca que la valeur est une variable lisible et modifiable, et pas
// une constante forcee : la question « est-ce que ca donne plus d'objets » se
// tranche en changeant le chiffre et en comptant, pas en le supposant.
//
// ET LE CHEMIN N'EST PAS CELUI QU'ON CROYAIT
//
// Les constantes `AoiLodConst` (lod_level_ranges, normal_aoi_max_level, Chest)
// semblaient commander la zone de chargement. Mesure : ecrire x8 sur tous les
// rayons et mettre normal_aoi_max_level a 7 n'a change AUCUNE entite chargee
// (56 avant, 56 apres, sur 7 s de deplacement force). Elles ne sont lues par
// aucun code Lua, et leur nom n'apparait nulle part dans GameAssembly.dll : ce
// sont des constantes mortes.
//
// Le vrai systeme s'appelle XS / XSR (les logs du jeu ecrivent "@fjs XS."), il
// est en C++, et c'est celui-la qu'on detourne.
//
// L'ASTUCE UTILE, TROUVEE AU PASSAGE
//
// TeleportCheckNeedLoad pose dist2 = (dx)^2 + (dz)^2, puis :
//
//     if ( dist2 <  5000 )  log "TeleMinRangeDebug info"     (~70.7 u)
//     if ( dist2 <= 1225 )  log "TeleMinRangeDebug skip" -> return 0
//
// 1225 == 35^2 : en dessous de 35 u, le jeu ne charge RIEN. C'est pourquoi le
// TP sur une cible deja proche ne declenche aucun streaming.
//
// ET ATTENTION, DEUX GRANULARITES NE SE MELANGENT PAS
//
// TeleportCheckNeedLoadByCollider raisonne en CHUNKS de 256 u (1/256).
// XSRBlockTile raisonne en TUILES, de taille inconnue. La teleportation exige
// |chunkAgent - chunkPos| <= 1 sur x ET z ; le niveau de portee, lui, est en
// tuiles et plafonne a 12.

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

// Le second plafond, celui du moteur. Valeur d'origine = 12. On ecrit UN
// octet. `false` si la garde a refuse (le jeu a change sous nos pieds).
int* lod_cap();
bool set_lod_cap(int valeur);
int lod_cap_now();

bool install();
bool installed();

// Le nom lisible du mode courant, pour la case. nullptr si on n'a pas force.
const char* current_label();

void draw_ui();

}  // namespace streaming
}  // namespace specter::features