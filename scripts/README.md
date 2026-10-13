# `scripts/` — scripts d'analyse Aniimo

Petits chunks Lua **auto-contenus**, exécutés *dans* l'instance Aniimo en cours
via le canal de commande fichier de Specter (`tools/lua.sh`). **Lecture seule** :
aucun write dans le jeu ni dans le préfixe.

Ils servent à cartographier le monde (marques, collectibles, entités) et à
répondre vite à une question pendant le dev du cheat.

## Lancer

```bash
tools/lua.sh -f scripts/chests.lua       # direct
scripts/run.sh chests.lua                # même chose, en court
scripts/run.sh -e 'print(pg.me.sceneId)' # code inline
```

Le pont Lua ne répond **qu'en jeu** (pas au menu). Chaque script est un chunk
unique : pas de `require` entre fichiers, tout doit tenir dans le fichier (la
plupart des scripts ont leurs réglages dans des constantes en tête de fichier).

## Inventaire

| script | question |
|---|---|
| `position.lua` | où suis-je ? (scène, position, rotation, espace) |
| `marks-summary.lua` | **combien de chaque type** (marques par `markConfigId`, par scène) |
| `marks-dump.lua` | positions d'une famille (coffres, cristaux, floraisons, ambre, éco…) |
| `chests.lua` | les coffres : marques monde + entités vivantes, corrélées |
| `chest-tp.lua` | coffres **non ouverts** (liste) **+ TP lerp vers le plus proche** — filtre le cache local |
| `chest-open.lua` | coffre **non ouvert** le plus proche : TP lerp **puis ouverture automatique** — marque l'id « ouvert » dans le cache dès que l'interaction aboutit |
| `entities-classes.lua` | **combien de chaque type** (entités vivantes par classe) |
| `entities-near.lua` | qu'y a-t-il autour de moi (rayon réglable) |
| `entity-dump.lua` | tous les champs d'une entité (joueur / plus proche / par classe) |

## Conventions de sortie

Une ligne = un objet, préfixes stables (parsable au `grep`) :

```
M <scene> <cfg> <x> <y> <z> <nom>     marque quelconque
C <scene> <x> <y> <z>                 coffre (marque monde)
LIVE ...                              entité vivante
TOTAL=<n> / TOTAL_MARKS=<n> / TOTAL_LIVE=<n>
```

## Repères du jeu (ce qui a été vérifié en live)

### Accès

| quoi | comment |
|---|---|
| joueur | `pg.me` (`sceneId`, `id`, `uid`) |
| position / rotation | `pg.playerPos` `{x,y,z,space}`, `pg.playerRot` `{…}` ; `pg.me:getPosition()` |
| entités vivantes | `pg.getEntities()` (≈ `pg.global.actorMgr.entities`) — `uid2Ent` ne contient que le joueur |
| position d'une entité | `e:getPosition()` → vecteur `[1]=x [2]=y [3]=z` |
| classe d'une entité | `getmetatable(e).__index.className` |
| config d'une entité | `e.templateId` ; coffre : `e.isChest`, `e.chestType`, `e.markBindStaticId` |
| marques de scène | `require('Common.Utils.SceneUtils').getSceneMarkPointData(sceneId)` |
| champs d'une marque | `markConfigId`, `markType`, `markPosition` `{x,y,z}`, `largeAreaId`, `infoTitle` |
| nom localisé | `require('Utils.ClientTextUtils').getLocalizationText(textId)` |
| **coffres non ouverts** | l'état n'est *pas* dans les marques (toutes `activeState=2`) : les ids des marques disponibles sont dans `pg.game.map.markUnlocker.unlockChunkMap` (par chunk, autour du joueur). Vérifié : 749 marques Coffre en 3000, 40 déverrouillées, et tous les `ClientChest` vivants y sont. ⚠️ ce registre n'est **pas** purgé en temps réel après ouverture — l'entité vivante absente est le signal fiable. Seules les marques cfg `10506` sont traitées (pas les Ambre lumin / ramassages / Aniipods, même si leur entité a `isChest=true`). |
| **cache local « déjà ouverts »** | `pg.me.__specterChestOpened` (champ d'instance, **jamais réinitialisé** s'il existe) : ids des coffres déjà ouverts par nos scripts, posés **dès que l'interaction aboutit** — la liste des « non ouverts » n'attend plus le despawn ni la purge. Un id en cache est masqué, **sauf si une entité vivante réapparaît** (respawn) : la règle du filtre repasse l'id en disponible. Vérifié en live : 3 coffres ouverts, présents dans le registre, absents de nos listes. |
| **ouvrir un coffre** | interaction = chemin de la touche F : unité d'interaction du coffre dans `pg.game.interaction.unitMap[1]` (type 1, `actionPrototypeId` = 59, `globalId` = l'`id` de l'entité), puis `pg.game.interaction:doUnitInteractive(unit)`. Le serveur valide → le coffre s'ouvre (l'entité disparaît, la récompense tombe). Précondition lisible : `unit:canInteractive(pg.me)`. Vérifié : cochée par script TP→open ; dernier id ouvert dans `pg.me.__specterLastOpen`. |
| config interaction | `Data.interact_data[59]` : `type=1`, `interactiveDist=2`, `startAnim=Kick`, `actionTime=1.2`, `actCooldown=5` |

### `markConfigId` connus (scènes 3000 / 3003, valeurs live)

| cfg | nom | n (3000 / 3003) |
|---|---|---|
| `10506` | **Coffre** | 749 / 41 = **790** |
| `10505` | Ambre lumin | 102 / 7 |
| `10405` | Point écologique clé | 158 / 4 |
| `10406` | Cristaux (« Teleportation Array ») | 27 / 2 = **29** |
| `10410` / type `26` | **Floraison** | 14 / 1 = **15** |
| `10401` | Pierre gelée | 20 / 2 |
| `10510` | Défi de Nomade | 56 / 0 |
| `10600` | Entrée de la grotte | 14 / 0 |
| `10414` | Saut d'Échoflux | 27 / 1 |
| `102` | (sans `infoTitle`) | 693 / 43 |

Autres repères : `10301` Branche, `10304` Nutrion, `10305` Flux électrique,
`10400` Casse-tête thématique, `10402` Mémoire du Mutaspiole, `10403` Défi du
Dr Glass, `10404` Casquillon, `10407` Avant-poste, `10412` Aider l'Aniimo,
`10413` Atterrissage insulaire, `10415` Enrichir, `10511` Défi de Nomade d'élite,
`20` Transporteur, `27` Point de suivi, `121` Abondance de veine.

### Config des coffres

`require('Data.chest_data')` = 373 entrées indexées par id de coffre
(`userdata` ; champs lisibles via `pairs`/index : `chestType`, `quality`,
`name` (text id), `icon` `$UI_Icon_MarkPoint_Chest.png`, `markConfigId=10506`,
`model`, `actionPrototypeId`, `openingTime`, `unlockSound`…). C'est la **config**,
pas les positions : celles-ci viennent des marques.

## Pièges (vécus)

- **Scan borné** : balayer *toutes* les scènes est proscrit —
  `getSceneMarkPointData` coûte ~0,7 ms même pour une scène inexistante (~14 s
  pour toute la plage). On se limite aux scènes de monde ouvert connues
  (`3000`, `3003`).
- **Un seul buffer de résultat** sur le canal TP (48 Ko) : deux chunks demandés
  coup sur coup s'écrasent. Les gros dumps peuvent être tronqués → `MAX_ROWS`.
- **Ordre `pairs`** non déterministe → trier avant d'afficher.
- **Sandbox Lua** : les variables globales ne persistent pas d'un chunk à
  l'autre ; les écritures de *champs* d'instances, si — c'est le support du
  cache `pg.me.__specterChestOpened`.
- **Despawn / purge lente** : après ouverture, l'entité peut rester un moment et
  `unlockChunkMap` n'est pas purgé en temps réel → on s'appuie sur le cache
  local (ci-dessus) plutôt que sur le despawn pour savoir qu'un coffre est déjà
  ouvert. Garde-fou : une entité vivante repasse l'id en « disponible ».
- Les fichiers Lua du jeu sont du **bytecode LuaJIT** (`\x1bLJ\x02`) : on lit les
  chaînes (`strings`) et on introspecte en live, pas le source.
