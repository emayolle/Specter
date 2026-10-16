# Restructuration de `Specter.Internal` — cible et plan de migration

> **Statut : en cours.** Le plan est validé et s'exécute phase par phase ; chaque
> phase atterrie est commitée, et le contenu définitif est absorbé dans
> `docs/ARCHITECTURE.md` (qui décrit, lui, l'état *réel*). Phases atterries :
> **1** (arbre en couches), **2** (généré hors `src/`), plus le balayage des
> namespaces. Prochaine : **phase 3** (pompe Lua + mailbox + couche Lua + appels
> nommés).

---

## 1. Le problème

Le code est propre *à l'intérieur* des modules ; c'est le **rangement** qui ne
suit aucune règle, donc l'arbre est illisible : on ne peut pas dire « qui est la
base », ni dans quel sens vont les dépendances, sans ouvrir les fichiers.

Constat précis :

1. **La racine mélange quatre rôles.** `entry.cpp` / `specter.cpp` (cycle de
   vie), `runtime.*` / `il2cpp-api.*` (seam VM), `log.*` / `nt.*` (primitives),
   `hostch-rva.h` (généré) : quatre responsabilités côte à côte, sans hiérarchie.
2. **Les dossiers sont nommés d'après un occupant, pas un rôle.** `overlay/`
   contient `detour.*`, un **moteur de hook générique** également utilisé par
   `game_input` — rien de « overlay ». `features/lua_console` contient la
   **pompe du thread Lua**, qui est de l'infra, pas une feature.
3. **La couche `features` n'a pas de seam.** Chaque feature est câblée à la main
   dans `overlay/d3d12_overlay.cpp` (qui **inclut** `features/cheats.h`,
   `features/lua_console.h`, `features/tp.h`), dans `specter.cpp::start()`, dans
   le registre `features/cheats.cpp` et dans `specter_init.lua`. Le rendu
   connaît toute l'application → **inversion de couche**, et ajouter une feature
   touche 4 à 5 fichiers.
4. **L'API Lua est résolue deux fois** : `features/lua_console.cpp` (17 pointeurs)
   et `lua/lua_api.cpp` + `xlua_thunks.cpp` (142 thunks).
5. **Du code généré vit sous `src/`** : `lua/xlua_thunks.cpp` (généré par
   `tools/gen_lua_thunks.py`) et `hostch-rva.h` — ce qui brouille le seam
   `generated/` vs `src/`.
6. **Les constantes RE sont dispersées** (offsets `0x18`/`0x10`, RVA
   `0x172ADC0`, indices de vtable) au fond des modules.

Le but de cette restructuration : **en lisant seulement l'arbre, comprendre
l'architecture.**

---

## 2. Le principe de rangement (un seul)

> L'arbre est un **empilement de couches**. Les dépendances vont **toujours vers
> le bas**, jamais vers le haut. Un dossier est nommé pour son **rôle**, jamais
> pour un de ses occupants.

Cinq couches, du haut vers le bas :

```
  app/          cycle de vie : DllMain + start()/stop()  (composition root)
   │
   ├── render/    front-end : overlay D3D12, fenêtre, input, UI
   └── features/  les fonctionnalités, une par dossier
        │
   lua/  il2cpp/  infra : pont Lua, seam VM
        │
   platform/      primitives réutilisables : log, threads cachés, hook engine
```

Règle de dépendance (qui a le droit d'inclure qui) :

| Couche | Peut inclure | Ne peut **pas** inclure |
|---|---|---|
| `app/` | `render/`, `features/`, `lua/`, `il2cpp/`, `platform/` | — |
| `render/` | `features/` (via le **registre** seulement), `lua/`, `il2cpp/`, `platform/` | `app/`, un fichier de feature précis |
| `features/` | `lua/`, `il2cpp/`, `platform/` | `app/`, `render/` |
| `lua/` | `platform/` | tout le reste |
| `il2cpp/` | `platform/` | tout le reste |
| `platform/` | *(rien en interne)* | tout le reste |

Deux invariants **conservés** (ils marchent aujourd'hui, on ne les casse pas) :

- **jamais de `CreateThread`** : on crée un thread uniquement via
  `platform/nt::spawn_hidden()` ;
- **jamais de constructeur global / « magic static »** : la DLL est
  manual-mappée, le guard CRT des statiques n'est pas initialisé. Conséquence :
  l'enregistrement des features est **explicite** (pas d'auto-enregistrement par
  static initializer).

Trois racines, et rien d'autre :

| Racine | Écrit à la main | Versionné | Rôle |
|---|---|---|---|
| `src/` | oui | oui | le produit |
| `generated/` | non | non | repars de `tools/dump.sh` + générateurs |
| `third_party/` | non | oui (vendoré) | imgui, luajit, luabridge |

---

## 3. Arbre cible

```
src/Specter.Internal/
├── app/
│   ├── entry.cpp                    DllMain + LOG_FILE (adaptateur d'entrée)
│   └── specter.{h,cpp}              start()/stop() — composition root
│
├── render/
│   ├── dxgi_hook.{h,cpp}            hook vtable DXGI (Present/Present1/Resize/ECL)
│   ├── d3d12_overlay.{h,cpp}        pont ImGui ↔ D3D12 + l'UI (itère le registre)
│   ├── d3dcompiler_shim.cpp         D3DCompile paresseux (import-safe)
│   └── input.{h,cpp}                (ex game_input) gate input + curseur
│
├── features/
│   ├── feature.h                    l'interface d'une feature + le registre
│   ├── registry.cpp                 LA ligne unique qui câble chaque feature
│   ├── layer/                       la couche Lua : fonctions de jeu nommées
│   │   ├── layer.{h,cpp}            install_layer()
│   │   └── specter_init.lua         script embarqué → publie SPECTER.*
│   ├── console/                     canal console (UI + résultat)
│   │   └── console.{h,cpp}
│   ├── cheats/                      panneau toggles/options
│   │   └── cheats.{h,cpp}
│   └── teleport/                    (ex tp) slots + marks + lerp
│       └── teleport.{h,cpp}
│
├── lua/
│   ├── api.{h,cpp}                  (ex lua_api) résolution xlua.dll
│   ├── thunks.cpp                   GÉNÉRÉ (bannière AUTO-GENERATED)
│   ├── bridge.{h,cpp}               file de tâches du thread Lua
│   ├── native.{h,cpp}               pont LuaBridge typé (Lua → C++)
│   ├── call.{h,cpp}                 seam C++ → Lua (getfield/pcall/tonumber)
│   ├── mailbox.h                    transport inter-thread (POD)
│   ├── bind/                        (phase 5) un fichier de binding par domaine
│   └── pump.{h,cpp}                 detour CommonUpdate + tick(L) (extrait)
│
├── il2cpp/
│   ├── runtime.{h,cpp}              localise GameAssembly + init
│   ├── api.{h,cpp}                  (ex il2cpp-api) résolution mono_*
│   └── target.h                     constantes RE : offsets, RVA, idx vtable
│
└── platform/
    ├── log.{h,cpp}                  journalisation (pipe / fichier)
    ├── nt.{h,cpp}                   spawn_hidden (thread is_system)
    ├── hostch-rva.h                 GÉNÉRÉ (bannière AUTO-GENERATED)
    └── hook/
        ├── detour.{h,cpp}           moteur de detour inline générique
        └── detour_ld_table.h        table du décodeur x86-64
```

### Table de correspondance (état actuel → cible)

| Aujourd'hui | Cible | Nature du changement |
|---|---|---|
| `entry.cpp` | `app/entry.cpp` | déplacement |
| `specter.{h,cpp}` | `app/specter.{h,cpp}` | déplacement |
| `runtime.{h,cpp}` | `il2cpp/runtime.{h,cpp}` | déplacement |
| `il2cpp-api.{h,cpp}` | `il2cpp/api.{h,cpp}` | déplacement + renommage |
| `log.{h,cpp}` | `platform/log.{h,cpp}` | déplacement |
| `nt.{h,cpp}` | `platform/nt.{h,cpp}` | déplacement |
| `hostch-rva.h` | `platform/hostch-rva.h` | déplacement (généré) |
| `overlay/dxgi_hook.{h,cpp}` | `render/dxgi_hook.{h,cpp}` | déplacement |
| `overlay/d3d12_overlay.{h,cpp}` | `render/d3d12_overlay.{h,cpp}` | déplacement |
| `overlay/d3dcompiler_shim.cpp` | `render/d3dcompiler_shim.cpp` | déplacement |
| `overlay/game_input.{h,cpp}` | `render/input.{h,cpp}` | déplacement + renommage |
| `overlay/detour.{h,cpp}` | `platform/hook/detour.{h,cpp}` | déplacement (générique) |
| `overlay/detour_ld_table.h` | `platform/hook/detour_ld_table.h` | déplacement |
| `lua/lua_api.{h,cpp}` | `lua/api.{h,cpp}` | déplacement + renommage |
| `lua/bridge.{h,cpp}` | `lua/bridge.{h,cpp}` | inchangé |
| `lua/native.{h,cpp}` | `lua/native.{h,cpp}` | inchangé |
| `lua/xlua_thunks.cpp` | `lua/thunks.cpp` | renommage (bannière générée) |
| `features/lua_console.{h,cpp}` | **éclaté** : `lua/pump.*` + `lua/mailbox.h` + `features/layer/*` + `features/console/*` + `lua/call/*` | refactor |
| `features/cheats.{h,cpp}` | `features/cheats/*` | déplacement |
| `features/tp.{h,cpp}` | `features/teleport/*` | déplacement + renommage |
| `features/specter_init.lua` | `features/layer/specter_init.lua` | déplacement (publie `SPECTER.*`) |

Style d'`#include` résultant (tout est relatif à la racine `src/Specter.Internal`,
qui reste le seul `-I`) :

```cpp
#include "app/specter.h"        // pas "specter.h"
#include "platform/log.h"       // pas "log.h"
#include "il2cpp/api.h"         // pas "il2cpp-api.h"
#include "platform/hook/detour.h"   // pas "overlay/detour.h"
#include "lua/bridge.h"
#include "features/feature.h"
```

---

## 4. Les seams à introduire

Le déplacement seul (section 3) rend l'arbre lisible. Mais il ne corrige pas
l'inversion de couche : c'est l'objet des seams ci-dessous.

### 4.1 Seam « feature » (corrige le problème n°3)

Aujourd'hui l'UI (`render/d3d12_overlay.cpp`) **inclut chaque feature**. On
introduit une interface minuscule ; l'UI ne connaît plus que le registre.

```cpp
// features/feature.h
namespace specter::features {

struct Feature {
    const char* id;            // stable, unique (== nom du flag Lua)
    const char* tab;           // section de menu
    bool (*install)();         // une fois, depuis app::start (worker caché)
    void (*draw_ui)();         // à chaque frame, thread de rendu, menu ouvert
};

// Le registre. C'est LE seul endroit où une feature est câblée.
const Feature* const* registry();
int registry_count();

}  // namespace specter::features
```

- `features/registry.cpp` liste les features, **une ligne chacune** (explicite :
  pas de static initializer, cf. invariant CRT).
- `render/d3d12_overlay.cpp` itère `registry()` et appelle `draw_ui()` — il
  n'inclut plus `cheats.h`, `console.h`, `teleport.h`.
- `app/specter.cpp` itère `registry()` pour `install()` (au lieu de la liste
  d'appels en dur actuelle).

**Coût d'ajout d'une feature, après ce seam** : créer `features/<nom>/` +
**une ligne** dans `registry.cpp`. C'est le gain central.

### 4.2 Extraire la pompe Lua (corrige le problème n°2)

`features/lua_console.cpp` (1223 lignes) fait quatre métiers. On les sépare :

- `lua/pump.{h,cpp}` — **infra** : detour de `LuaManager.CommonUpdate`, suivi du
  `lua_State`, appel de `lua::bridge::tick(L, new_state)`. Le seam est
  `pump::install()` (une fois) et un point d'extension par tick.
- `features/console/*` — **feature** : file de chunks + `/tmp` out.txt + résultat.
- `features/teleport/*` — **feature** : utilise le même primitif de chunk
  (aujourd'hui `tp_submit`/`tp_take_result` vivent dans `lua_console`).
- l'**infinite stamina** ne devient **pas** un module C++ : son hook passe dans la
  layer Lua (§4.6) et le C++ ne garde que le booléen — que `features/cheats.cpp`
  publie **déjà** (`publish_all` → `publish_flag`). Il n'y a donc rien à extraire.

**Décision figée — transport réutilisable, pas de canal unique.** Le `pump` ne
connaît aucun canal : il détecte le `lua_State`, garde la section critique
(`seh::Guard`, en laissant passer l'exception LuaJIT `0xE24C4A00`) et, à chaque
tick, draine pour le compte de qui s'y est enregistré (`on_new_state(L)` /
`on_tick(L)`). Le transport inter-thread est un `lua::Mailbox` **réutilisable**
(POD, zéro-init, verrou créé paresseusement), pas un tampon unique :

- `Mailbox<1, Repl>` — console : une requête en attente, la nouvelle **remplace**
  l'ancienne (on veut toujours la dernière soumise) ;
- `Mailbox<8, Drop>` — téléport : plusieurs requêtes, on **abandonne** au-delà.

Chaque feature possède sa mailbox et **la draine dans son propre `on_tick`**. Le
pump transporte donc des requêtes typées, pas du code Lua (cf. §4.5). Au passage,
le verrou paresseux de `Mailbox` remplace le `ensure_lock()` de
`lua_console.cpp`, qui n'est pas thread-safe.

### 4.3 Unifier l'API Lua (corrige le problème n°4)

`features/console` cesse de résoudre ses propres `lua_*` : il utilise
`lua/api.h` + `lua/thunks.cpp` (déjà 142 fonctions). Une seule vérité pour l'ABI
LuaJIT.

### 4.4 Regrouper les constantes RE (corrige le problème n°6)

`il2cpp/target.h` rassemble les valeurs propres à la cible Aniimo : offsets de
champs (`LuaManager.luaenv 0x18`, `LuaEnv.rawL 0x10`), RVA
(`CommonUpdate 0x172ADC0`), indices de vtable DXGI. Un seul endroit à mettre à
jour lors d'une maj du jeu.

### 4.5 Seam d'appel C++ → Lua : les fonctions nommées

**Principe : le C++ ne contient aucun code Lua.** Les opérations de jeu fixes
(téléport, stamina, …) sont des **fonctions Lua nommées**, chargées au démarrage
dans `SPECTER.*`, et c'est le C++ qui les appelle. Le C++ ne construit plus de
chaîne de code : fini le canal `tp_submit` / `tp_take_result`, qui s'échangeait
du texte Lua. La boucle complète :

1. `features/layer/specter_init.lua` **définit et publie** les fonctions
   (`SPECTER.teleport.to(x, y, z)`, `SPECTER.teleport.pos()`, …), chargé une fois
   par `install_layer()`.
2. Le C++ appelle `SPECTER.<fn>(args)` via un **mécanisme partagé** (`lua/call`)
   qui, sur le thread Lua : résout `SPECTER.<domaine>.<fn>`, pousse les args,
   `lua_pcall`, relit les retours typés, restaure le sommet de pile.
3. La traversée de thread (clic render → thread Lua) est portée par la
   `Mailbox` : le render dépose « appelle `teleport.to` avec x, y, z », le pump
   l'exécute à son tick.

**Deux sens, deux outils** (chacun déjà présent ou tranché) :

| Sens | Outil | Pourquoi |
|---|---|---|
| Lua → C++ (publier une fonction C++ appelable depuis Lua) | **LuaBridge** — `getNamespaceFromStack(L).addFunction(...)`, déjà en place dans `lua/native.cpp` | c'est fait pour ça |
| C++ → Lua (appeler `SPECTER.<fn>`) | **C API brute** — `lua_getfield` + `lua_pcall` + `lua_tonumber` | `LuaRef` / `TableItem` a crashé le process de façon **incatchable** au premier write scalaire (`lua/native.cpp`, `lua/native.h`) |

**Forme du mécanisme : un seul mécanisme, des adaptateurs par domaine.** Un
`lua::call` *générique et unique* qui accepterait « n'importe quels » args et
retours est un faux ami : Lua renvoie un nombre **variable** de valeurs
hétérogènes (jusqu'à des tables) que C++ ne peut pas typer génériquement. On
partage donc une **seule mécanique**, et on type par domaine :

- `lua/call.{h,cpp}` — le mécanisme : résolution via le handle registre
  `__specter_ns` (déjà utilisé par `push_namespace()`), `pcall`, lecture
  `tonumber`/`tointeger`, restauration systématique du sommet ; plus un template
  `call<Rets...>(L, path, args...)` pour les cas **scalaires** ;
- `lua/call/<domaine>.{h,cpp}` — **un adaptateur typé par fonction**
  (`teleport::to(L, x, y, z)`, `teleport::pos(L, &x, &y, &z, &space)`). Les
  retours « liste » (marks) restent du **texte**, comme aujourd'hui.

Tout s'exécute **sur le thread Lua**, jamais au clic : c'est la `Mailbox` qui
franchit la frontière de thread.

**Preuve dans la référence** : `nova-gmod` fait exactement ce geste — résoudre un
nom (`GetField`), pousser les args, appeler, relire le retour typé
(`GetNumber` / `IsType`) — dans `CreateMoveHook.cpp` (`ents.GetByIndex`,
`GetViewPunchP`) et `hook_logger.cpp` (`nova.hook.Call`). Il ne l'a jamais
branché sur un **bouton** ; c'est le pas que Specter ajoute.

### 4.6 L'infinite stamina : hook de **classe** gate-in (vérifié en jeu)

L'infinite stamina today = deux chunks (`kStaminaInstall` / `kStaminaDisable`)
envoyés depuis le C++, qui patchent `changeStamina` sur **l'instance** du joueur,
plus une passe de maintenance toutes les ~10 s qui re-pose le patch (une entité
recréée après un relog n'a plus le patch).

**Le modèle retenu** — patch de **classe**, gate sur le booléen C++ :

- **Action** (téléport) → un **appel nommé** `SPECTER.teleport.to(x, y, z)`.
- **État persistant** (stamina) → un **booléen** `SPECTER.inf_stamina` publié
  par le C++ (LuaBridge), lu au moment de l'appel.

Le wrapper est posé **une fois** sur la classe ; le booléen décide, à chaque
appel, entre « nop » et « on appelle l'original ». Donc : plus de chunk
install/restore, plus de maintenance périodique, plus de cas particulier relog.

**Pourquoi un patch de classe et pas d'instance.** Vérifié en jeu (build
courant, via le canal `tools/lua.sh`) :

| Fait vérifié | Conséquence |
|---|---|
| `require("Common.Ability.Attribute.ActorCombatAttribute")` renvoie **exactement** le metatable partagé des instances (`AC == getmetatable(aca)` et `mt.__index == mt`) | patcher `AC.changeStamina` = patcher la classe |
| Un patch de classe **intercepte réellement** les appels (compteur `neg` qui progresse en jeu) | le patch entre dans le chemin d'appel, pas dans une copie cachée |
| `self.entity == pg.me == pg.pawn` (même objet), `isMainPlayer == true` | filtre joueur **gratuit** et exact |
| Restauration : remettre `orig` rend le drainage normal | **réversible**, aucun résidu |

En jeu, gate **OFF** → la stamina drain normalement (100 → 14.6) ; gate **ON**
→ elle reste à **100/100** et les deltas négatifs sont comptés « avalés »
(`swallowed = 3`).

```lua
local AC = require("Common.Ability.Attribute.ActorCombatAttribute")
local orig = AC.changeStamina
AC.changeStamina = function(self, delta)
    local d = tonumber(delta)
    if d and d < 0 and M.inf_stamina then          -- gate : booléen C++
        local e = self.entity
        if e and (e == pg.me or e == pg.pawn) then -- filtre joueur
            return true
        end
    end
    return orig(self, delta)
end
```

**Aucun changement C++ côté flag.** `features/cheats.cpp` déclare déjà le toggle
`inf_stamina`, et `publish_all(L)` republicie `SPECTER.inf_stamina` sur **chaque**
nouveau `lua_State`. Le réconcilieur `M.tick()` de la layer voit donc l'edge et
ré-applique le patch tout seul après un relog — sans code de relog, sans timer.

Le hook s'installe via `def("inf_stamina", { enable = … })`. Deux précautions :

- `enable` doit être **idempotent et rendre `true`** même s'il n'a pas encore pu
  patcher (le module peut ne pas être chargé à la première tentative) ; c'est un
  `on_tick` qui **retente** tant que ce n'est pas fait. Sinon `_apply` mémorise
  `_last_want` et le feature resterait off jusqu'au prochain basculement du toggle ;
- une fois posé, le wrapper **reste** (gate off = il appelle `orig`). C'est le
  compromis assumé : activation instantanée, et jamais de jeu laissé dans un
  état intermédiaire.

**Le piège du sandbox (à ne pas oublier).** Les chunks sont exécutés dans un env
sandbox **par chunk** : un `rawset(_G, k, v)` écrit dans l'env du chunk et
**disparaît au chunk suivant** (constaté : le flag de test relu valait `nil`).
En revanche `install_layer` fait `pcall` sur le chunk qui **retourne `M`**, et
C++ publie ensuite `M` dans le registre (`__specter_ns`) **et** en `_G.SPECTER`
en raw. Donc `M` est une vraie table persistante, et le wrapper la capture en
**upvalue** : il lit `M.inf_stamina` sans jamais toucher `_G`.

> **Règle** : un état posé depuis un chunk ne vit jamais dans le `_G` du chunk,
> mais sur une **table partagée** (`M`, ou une table de classe). C'est aussi ce
> qui rend un hook résilient à un rechargement du layer.

---

## 5. Plan de migration

Chaque phase est **indépendante et build-intact** (sauf mention) : la DLL reste
injectable et le comportement identique, on vérifie, on commit, on avance.

### Phase 0 — base de référence
- **But** : pouvoir comparer. Commiter/taguer l'état actuel qui compile et
  s'injecte.
- **Vérif** : `tools/build-dll.sh` puis `tools/specter-up.sh` → log `attached`.

### Phase 1 — déplacement + renommage (mécanique)
- **Contenu** : la table de correspondance de la section 3, **hors** éclatement
  de `lua_console` (reporté en phase 3). Uniquement `git mv` + réécriture des
  `#include` + mise à jour des fichiers projet.
- **Fichiers à mettre à jour** : `Specter.Internal.vcxproj`,
  `Specter.Internal.vcxproj.filters` (déjà désynchronisé — à réparer au
  passage), `tools/build-dll.sh` (chemins `$SRC/...`), `tools/gen-compile-commands.sh`
  (auto : il `find` sous `src/`), `.gitignore`.
- **Ne change pas** : aucun `.cpp` autre que les `#include`.
- **Vérif** : build + injection + logs ; relancer `tools/gen-compile-commands.sh`
  pour IntelliSense.

### Phase 2 — sortir le généré de `src/`
- **Contenu** : décision « généré versionné » (voir §7) appliquée à
  `xlua_thunks.cpp` (→ `lua/thunks.cpp`) et `hostch-rva.h` (→
  `platform/hostch-rva.h`), bannière `AUTO-GENERATED` en tête.
- **Fichiers à mettre à jour** : `tools/gen_lua_thunks.py` (chemin `OUT`),
  `tools/build-dll.sh`, projet VS.
- **Vérif** : `python3 tools/gen_lua_thunks.py` puis build → binaire identique
  attendu.

### Phase 3 — pompe Lua, mailbox, couche Lua et appels nommés
- **Contenu** :
  - `lua/pump.{h,cpp}` — detour `LuaManager.CommonUpdate` + suivi du `lua_State`
    (`LuaManager.luaenv(0x18)` → `LuaEnv.rawL(0x10)`), `seh::Guard`, registre
    `on_new_state` / `on_tick`, `install` / `ready` / `status` / `ticks`.
    Extrait de `features/lua_console.cpp`.
  - `lua/mailbox.h` — `lua::Mailbox<Slots, Policy>` (POD, zéro-init, verrou
    paresseux) : `submit` / `take_pending` / `publish` / `take_result`. Remplace
    l'`ensure_lock()` non thread-safe de `lua_console.cpp`.
  - `features/layer/` — `specter_init.lua` + `install_layer()` : les fonctions
    de jeu nommées publiées sous `SPECTER.*`.
  - `lua/call.{h,cpp}` (+ `lua/call/<domaine>`) — le seam C++ → Lua (§4.5).
  - `features/console/*` — file de chunks + `/tmp/out.txt` + résultat ;
    `features/teleport/*` — migré de `tp_submit` / `tp_take_result` vers
    `SPECTER.teleport.to` ; l'**infinite stamina** — `kStaminaInstall` /
    `kStaminaDisable` et `set_infinite_stamina()` **supprimés**, remplacés par le
    hook de classe gate-in de la layer (§4.6). Le toggle ne bouge pas : il reste
    dans `features/cheats.cpp`, qui publie déjà `SPECTER.inf_stamina`.
- **Fichiers à mettre à jour** : `tools/embed_lua.py` (chemins `LUA`/`CPP`),
  projet VS, `app/specter.cpp` (ordre d'install : **le pump en dernier**).
- **Vérif** : console (soumettre un chunk), téléport (sauver/aller, lerp actif),
  `inf_stamina`.

### Phase 3bis — embed Lua en `.gen.h`
- **Contenu** : remplacer l'embed actuel (chaîne brute dans un `.cpp`) par un
  en-tête **généré** `AUTO-GENERATED` (comme `nova-gmod` :
  `_lua_InitScript.gen.h`), produit par `tools/embed_lua.py`.
- **Vérif** : binaire identique ; `SPECTER.*` publié.

### Phase 4 — seam « feature » (registre)
- **Contenu** : ajouter `features/feature.h` + `features/registry.cpp` ;
  `render/d3d12_overlay.cpp` itère le registre et **perd** ses `#include` de
  features ; `app/specter.cpp` itère le registre.
- **Vérif** : chaque onglet/feature s'affiche et se pilote comme avant.

### Phase 5 — unifier l'API Lua et éclater les bindings
- **Contenu** :
  - `features/console` cesse de résoudre ses propres `lua_*` : il passe par
    `lua/api.h` + `lua/thunks.cpp` (une seule vérité pour l'ABI LuaJIT).
    Attention aux cas particuliers déjà commentés (panique, pseudo-index globals).
  - Éclater `lua/native.{h,cpp}` en `lua/bind/*` — **un fichier de binding par
    domaine** (LuaBridge, sens Lua → C++), à la manière de pokemon-gode
    (`lua_bind_*.cpp`). C'est la correction de l'anti-pattern `luaexec.cpp` de
    nova-gmod (2571 lignes monolithiques).
- **Vérif** : `SPECTER` publié, toggles/options fonctionnels, reload de scène.

### Phase 6 — `il2cpp/target.h`
- **Contenu** : extraire offsets/RVA/indices de vtable dispersés.
- **Vérif** : self_check + features.

### Phase 7 — documentation & (option) tests
- **Contenu** : réécrire `docs/ARCHITECTURE.md` pour décrire l'arbre réel ;
  mettre à jour `README.md` (arborescence) et ce doc → absorbé.
- **Option** : harnais de test *host-side* pour la logique pure sans jeu
  (`platform/hook/detour` décodeur, `lua/bridge` file, parsing `owners`,
  parsing `teleport`).

---

## 6. Ce que la restructuration ne change **pas**

- Les commandes : `tools/dump.sh`, `tools/build-dll.sh`, `tools/specter-up.sh`.
- La sortie : `generated/bin/Release/Specter.Internal.dll`, imports
  `KERNEL32`/`USER32` uniquement.
- Les règles de discrétion (manual-map, threads cachés, pas d'`il2cpp_*`).
- Le comportement observé du mod.

---

## 7. Décisions ouvertes (à trancher avant/pendant)

> Les quatre points ci-dessous sont désormais **tranchés** (arbitrage de la phase
> de cadrage) ; on les garde listés pour mémoire.

1. **Noms de dossiers** — **Tranché** : ceux du §3 (`platform/`, `render/`,
   `features/teleport/`, `input`, `api`, `teleport`, `thunks`).
2. **Fichiers générés** — **Tranché** : versionnés sous `src/`, avec une bannière
   `AUTO-GENERATED` en tête et un emplacement dédié (le « clone puis build »
   reste possible sans wine-hostch).
3. **Enregistrement des features** — **Tranché** : liste **explicite** dans
   `registry.cpp` (pas d'auto-enregistrement par static initializer : la DLL est
   manual-mappée, le guard CRT n'est pas initialisé).
4. **`specter_init.lua`** — **Tranché** : `features/layer/specter_init.lua` (c'est
   une *feature* — elle publie `SPECTER.*` — pas la console, et pas l'infra
   `lua/`).

---

## 8. Récapitulatif des fichiers d'outillage à toucher

| Fichier | Pourquoi |
|---|---|
| `src/Specter.Internal/Specter.Internal.vcxproj` | liste des sources/en-têtes |
| `src/Specter.Internal/Specter.Internal.vcxproj.filters` | filtres (déjà obsolètes) |
| `tools/build-dll.sh` | chemins `$SRC/...` par TU |
| `tools/gen_lua_thunks.py` | chemin de sortie `xlua_thunks.cpp` |
| `tools/embed_lua.py` | chemins de `specter_init.lua` et du `.cpp` hôte |
| `tools/gen-compile-commands.sh` | auto (fait `find` sous `src/`) — à revérifier |
| `.gitignore` | si le généré change d'emplacement |
| `README.md`, `docs/ARCHITECTURE.md` | description de l'arborescence |
