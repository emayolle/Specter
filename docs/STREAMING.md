# Streaming — résultat négatif

Date : 2026-10-16. Statut : **mesuré, sans effet, retiré du produit.**

Ce document existe pour que personne ne recommence. Le code a été écrit, testé,
mesuré, puis retiré parce qu'il ne faisait rien.

## La question

> « je ne sais pas si c'est le script de auto farm ou pas » … puis, plus tard :
> « on peux pas forcer pour avoir tout les objet de la map ? ou agrandir la zone
> de chargement »

L'auto-farm vide la zone autour du joueur et n'a plus rien à faire. Est-ce une
limite de notre script, ou une limite du jeu ?

## Réponse : ce n'est pas nous, et ce n'est pas le streaming non plus

**Ce n'est pas nous.** Aucune limite de distance dans le script : la cible la
plus lointaine visitée était à **99,6 u** et il l'a téléportée. Aucune limite de
nombre non plus — la boucle tourne tant que la case est cochée. Ce qui manque,
c'est ce que le jeu a **chargé** : `pg.getEntities()` ne renvoie que les entités
en mémoire, et il n'en restait que 2 à un moment, dans un rayon de 93 u.

Le téléport **ouvre la suite** : en se déplaçant, la boucle streame d'autres
zones, donc d'autres coffres. C'est auto-alimentant.

## Le premier chemin, et pourquoi il était mort

`Common/Const/AoiLodConst.lua` avait l'air de commander la zone :

```lua
lod_level_ranges     = {6000, 6000, 9000, 12800, 25600, 51200, 102400}
normal_aoi_max_level = 3
Chest                = {2, 2, 3, 5}
```

Écrire **×8** sur tous les rayons, `normal_aoi_max_level = 7`, puis forcer le
recalcul en déplaçant le joueur de 25 u toutes les secondes :

```
AVANT : 56 entités
t+1s 56   t+2s 56   t+3s 55   t+4s 55   t+5s 56   t+6s 56   t+7s 56
```

**Zéro**, dans les deux sens. Et ces noms n'apparaissent nulle part dans
`GameAssembly.dll` (recherche par octets, avec contrôle positif : `CS_SetWorkSpaceW`
sort, `AoiLodConst` non). **Ce sont des constantes mortes.**

Les trois occurrences d'« AOI » dans le binaire sont un concept d'**interface** :
`XGUI::UWidget::EnableListenNonAOI`, `OnNonAOIRegionClicked` — des widgets qui
restent cliquables **hors** de la région AOI.

## Le vrai système, trouvé par décompile

Il s'appelle **XS / XSR** — les logs du jeu écrivent `@fjs XS.`. Tout est en C++.

```
StreamManager::CheckNeedLoad(pos)
  -> XSRGlobalManager::TeleportCheckNeedLoad(pos)
    -> TeleportCheckNeedLoadByCollider(pos, bool&, bool&)
```

Et le rayon :

```cpp
XSRGlobalManager::GetPerfDistance(int perfLevel)
    perfLevel <= 10 -> 3
    perfLevel <= 30 -> 4
    perfLevel <= 50 -> 5
    perfLevel <= 70 -> 6
    perfLevel >  70 -> 12
```

`perfLevel` vient de `SetPerformanceLevel` — un int statique **clampé dans
[0, 100]**.

## Deux plafonds, et ils ne se passent pas de la même façon

**(a) `GetPerfDistance`** — un detour. Le jeu ne produit que 3, 4, 5, 6 ou 12,
rien en aval ne l'écrase. Un curseur 0..12 passe.

**(b) `CalcThisTileLodLevel`** — dans le **code du moteur** :

```cpp
d = max(|tile.X - agent.X|, |tile.Z - agent.Z|);   // en TUILES
if (d > 12) return 12;                               // plafond DUR
```

Un detour sur (a) **ne passe pas** (b). Pour (b), il a fallu écrire dans
l'immédiat du `mov ecx, 0Ch` — **un octet**, à RVA 0x18457DC.

## Ce qui a été fait, et le résultat

Un detour sur `GetPerfDistance` (RVA 0x184D5F0), un curseur, et le patch d'un
octet pour (b), le tout gardé dans `target.h` avec les RVA et la table.

Puis la mesure :

```
streaming: plafond du moteur porte de 12 a 29 / 31 / 32 / 33 / 34
streaming: plafond du moteur porte de 12 a 18

TOTAL entites chargees : 117   (avant)
TOTAL entites chargees :  94   (apres)
```

**La garde a passé, l'octet est écrit, le journal le confirme — et rien ne
bouge.** Ni à 3, ni à 34. La différence 117 → 94 vient des déplacements du
joueur, pas du réglage.

## Pourquoi

**Les entités viennent du serveur.** Le streaming charge des **blocs de
terrain** et leur niveau de détail. Charger plus de terrain ne fait apparaître
aucun coffre de plus.

C'est écrit dans l'avertissement de l'en-tête, **avant** l'expérience :

> Charger quatre fois plus de terrain ne garantit donc aucun coffre de plus —
> ça coûte des images par seconde, c'est tout.

On a fait pareil. L'avertissement était juste.

L'autre sortie possible : (b) n'est pas appelé sur le chemin qui compte. Son
seul xref entrant est une **table de pointeurs de méthode** dans `.data`
(RVA 0x63C89A0), donc l'appel est indirect, et `IFix`
(`WrappersManagerImpl::IsPatched`, 4188 fonctions) peut rediriger l'appel vers
son propre corps — auquel cas les octets modifiés ne sont jamais exécutés.
Impossible de trancher entre les deux, et cela ne change rien au résultat.

## Pourquoi c'est retiré plutôt que désactivé

Un réglage qui ne fait rien coûte des FPS pour rien — et ce jour-là on passait
déjà de 170 à 59. **La base de code n'a pas à garder un curseur qui ment sur son
effet.**

Le résultat négatif est ici, et la base IDA (`generated/input/GameAssembly.dll.i64`)
porte les commentaires aux deux adresses.

## Ce qui reste, et qui marche

Rien de tout cela n'a servi à l'auto-farm, mais la même lecture a produit deux
choses utiles :

**La zone de téléportation.** `TeleportCheckNeedLoad` :

```cpp
dist2 = dx*dx + dz*dz;
if (dist2 <  5000)  log "TeleMinRangeDebug info"     (~70.7 u)
if (dist2 <= 1225)  log "TeleMinRangeDebug skip" -> return 0
```

**1225 = 35²** : en dessous de **35 u**, le jeu ne charge rien. C'est pourquoi un
TP sur une cible déjà proche ne déclenche aucun streaming — et pourquoi
l'auto-farm se déplace au lieu de valider sur place.

**Deux granularités qui ne se mélangent pas.** `TeleportCheckNeedLoadByCollider`
raisonne en **chunks de 256 u** (`0.00390625 = 1/256`) et exige
`|chunkAgent − chunkPos| <= 1` sur x **et** z. `XSRBlockTile` raisonne en
**tuiles**, de taille inconnue. Confondre les deux a produit une annotation
fausse, corrigée depuis.

## Ce qui reste à faire, si quelqu'un veut vraiment plus d'objets

La seule piste sérieuse serait le **protocole serveur** : ce qui décide quelles
entités existent autour du joueur. Voir `docs/PROTOCOLE.md`.