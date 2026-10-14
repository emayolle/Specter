# Plan — reconstruire Specter sur la base `2572297`

> **Base** : `2572297` (13 oct. 11:04) — le dernier état jamais signalé.
> **But** : reprendre l'architecture cible (couches, namespaces, fonctions Lua
> nommées) **sans jamais réintroduire l'empreinte Lua** que cet état n'avait pas.
>
> Contraintes issues de `docs/ANALYSE-DETECTION.md`, `docs/DETECTION.md` et
> `docs/ANTICHEAT.md`. Ces trois documents sont des **contraintes de conception**,
> pas de la documentation décorative : chaque phase du plan est evaluée contre
> eux.

---

## 0. Pourquoi cette base

`ANALYSE-DETECTION.md` §5 établit le fait central : entre `2572297` et `HEAD`, **la
couche C++ est fonctionnellement identique** (mêmes hooks, caractère près), et **le
delta fonctionnel est intégralement dans la couche Lua** :

| Ajouté après `2572297` | Nature |
|---|---|
| `lua/native.cpp` (pont LuaBridge) | confort de dev |
| `lua/bridge.cpp`, `lua/api.cpp`, `lua/thunks.cpp` (142 thunks) | confort de dev |
| `specter_init.lua` | le layer Lua |
| 3 écritures dans l'état Lua du jeu (§6 de l'analyse) | **l'écart suspecté** |

Ce qu'écrit le build dans l'état Lua du jeu, et qui n'a **aucune** raison
d'exister :

1. `_G.SPECTER` — global étranger, écrit en raw ;
2. `registry["__specter_ns"]` — clé nommée dans le registre ;
3. `lua_atpanic` **remplacé** — c'était du diagnostic.

> La reconstruction doit obtenir l'architecture cible **par un autre chemin** que
> ces trois écritures. C'est la seule vraie difficulté du plan, et elle est
> traitée au §4.

---

## 1. Invariants — les règles qui ne se négocient pas

### A. Discrétion (inchangé, vient de `2572297`)

1. **Jamais de commande « GM »**, ni d'entrée qui en borrow. Aucune feature dérivée
   de Shinoko, définitivement. C'est la cause racine du premier avertissement.
2. **Aucun import réseau** — vérifié à 0 sur le binaire produit (`dxgi`, `IMM32`,
   `KERNEL32`, `SHELL32`, `USER32`).
3. **Aucun fichier écrit dans le dossier du jeu ni dans le prefix** — tout sort par
   le pipe ou `Z:\tmp\...` (= racine Linux hors prefix).
4. Manual-map hostch, worker `is_system`, aucun objet nommé, aucun socket.

### B. Empreinte sur l'état Lua du jeu — **nouveau, c'est le cœur du plan**

5. **On n'écrit rien** dans l'état Lua du jeu. Ni `_G`, ni clé nommée au registre,
   ni remplacement de `lua_atpanic`. Pas d'exception.
6. Le seul artefact autorisé est une **référence de registre anonyme**
   (`luaL_ref(L, LUA_REGISTRYINDEX)`), créée **uniquement pendant que la couche est
   armée**, et relâchée à `disarm()`.
7. **Désarmé par défaut.** Injecter n'exécute aucune ligne de Lua. L'armement est un
   acte explicite de l'utilisateur.
8. **Aucune exécution automatique à l'injection** : pas d'installation de layer, pas
   de tick de réconciliation, pas d'exécution déclenchée par le système de fichiers
   (`poll_cli` — voir §5.4, à **supprimer**).

### C. Ingénierie

9. Jamais de `CreateThread` : uniquement `nt::spawn_hidden()`.
10. Jamais de constructeur global ni de « magic static » — la DLL est manual-mappée,
    le guard CRT des statiques n'est pas initialisé. Les objets d'espace de noms
    doivent être des POD à initialisation nulle ; tout enregistrement est explicite.
11. Une seule source de vérité par état.

> Les invariants B sont **vérifiables statiquement**. Ils deviennent un contrôle
> automatique en phase 0 (§5.0) — sinon ils ne tiendront pas.

---

## 2. L'architecture cible

Le principe est inchangé : **un dossier = un rôle**, et les dépendances pointent
**vers le bas**.

```
src/Specter.Internal/
├── app/                 cycle de vie : DllMain + start()/stop()  (composition root)
│   ├── entry.cpp
│   └── specter.{h,cpp}
├── render/              front-end : overlay D3D12, fenêtre, input
│   ├── dxgi_hook.{h,cpp}
│   ├── d3d12_overlay.{h,cpp}
│   ├── d3dcompiler_shim.cpp
│   └── input.{h,cpp}
├── features/            une feature par dossier
│   ├── feature.h        l'interface + le registre
│   ├── registry.cpp     LA ligne qui câble chaque feature
│   ├── teleport/        slots + marks + lerp
│   └── lua_dump/        outil de RE (recherche, pas une feature de jeu)
├── lua/                 infra du pont Lua
│   ├── pump.{h,cpp}     detour CommonUpdate + tick(L)
│   ├── mailbox.h        transport inter-thread
│   ├── call.{h,cpp}     seam C++ → Lua (§4)
│   └── layer.{h,cpp}    chargement du chunk de layer + refs anonymes
├── il2cpp/              seam VM
│   ├── runtime.{h,cpp}
│   ├── api.{h,cpp}
│   └── target.h         constantes RE regroupées
└── platform/            primitives réutilisables
    ├── log.{h,cpp}
    ├── nt.{h,cpp}
    ├── seh.h            garde-fou SEH
    └── hook/detour.{h,cpp}
```

| Couche | Peut inclure | Ne peut pas inclure |
|---|---|---|
| `app/` | `render/`, `features/`, `lua/`, `il2cpp/`, `platform/` | — |
| `render/` | `features/` (via le registre), `lua/`, `il2cpp/`, `platform/` | `app/`, un `.h` de feature précis |
| `features/` | `lua/`, `il2cpp/`, `platform/` | `app/`, `render/` |
| `lua/` | `platform/` | tout le reste |
| `il2cpp/` | `platform/` | tout le reste |
| `platform/` | *(rien)* | tout le reste |

---

## 3. Correspondance `2572297` → cible

| Aujourd'hui (`2572297`) | Cible | Nature |
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
| `features/lua_console.{h,cpp}` | **éclaté** : `lua/pump.*` + `lua/mailbox.h` + `lua/call.*` + `lua/layer.*` + `features/console/*` | refactor |
| `features/lua_dump.{h,cpp}` | `features/lua_dump/*` | déplacement |
| `features/tp.{h,cpp}` | `features/teleport/*` | déplacement + renommage |

Style d'include résultant (tout relatif à la racine `src/Specter.Internal`) :

```cpp
#include "platform/log.h"          // et non "log.h"
#include "platform/hook/detour.h"  // et non "overlay/detour.h"
#include "lua/pump.h"
```

---

## 4. Le point difficile — le seam C++ → Lua sans écrire dans l'environnement

On veut des **fonctions Lua nommées** appelées par le C++ (`SPECTER.teleport.to(x,y,z)`)
— mais l'invariant 5 interdit d'écrire dans l'état du jeu.

### La solution : le chunk **retourne** ses fonctions, C++ les prend par référence anonyme

```
1. C++ charge le chunk de layer et l'appelle UNE fois, armé.
     → le chunk retourne une table { teleport = { to = fn, pos = fn }, … }
2. C++ la pop, et pour chaque fonction fait :
     luaL_ref(L, LUA_REGISTRYINDEX)   →  un INT anonyme dans le registre
   Rien n'est écrit sous un nom. La table n'existe plus après le pop.
3. C++ appelle : push args, lua_pcall, lit les résultats, pop.
4. disarm() → luaL_unref sur chaque référence.
```

Conséquences :

- **aucune clé nommée** dans `_G` ou le registre — donc rien que le code du jeu
  puisse découvrir par nom ;
- les fonctions meurent avec l'état Lua, comme tout le reste ;
- rien à nettoyer en cas de rechargement de scène : les refs sont ré-indexées par
  `pump::on_new_state`.

### Les flags dans l'autre sens (Lua lit l'état du C++)

L'infinite stamina a besoin que le wrapper Lua lise un booléen détenu par le C++
(menu = source de vérité). On **passe la table en argument du chunk** :

```lua
local flags = ...        -- upvalue, capturé à la compilation du chunk
return { teleport = { to = fn, pos = fn } }
```

C++ garde une **ref anonyme** sur `flags` et écrit les champs en `lua_rawset`. Le
wrapper Lua lit `flags.inf_stamina` via son upvalue. **Aucun global, aucune clé
nommée** — et le wrapper lit une variable locale, ce qui est plus rapide et
insensible au sandbox (cf. le constat mesuré : les chunks tournent dans un env par
chunk, un `rawset(_G, …)` n'y survit pas).

### Forme des échanges

| Sens | Mécanisme | Pourquoi |
|---|---|---|
| C++ → Lua | `lua_getfield` sur la ref anonyme + `lua_pcall` + `lua_tonumber` | typé, sous contrôle, pas d'exception |
| Lua → C++ | le chunk reçoit une table de callbacks en argument | pas de publication dans l'environnement |

> **LuaBridge est écarté** sur cette base. Il servait à publier dans `SPECTER`, ce
> qui est précisément ce qu'on supprime. Il n'y a plus de cas d'usage qui justifie
> de garder 218 Ko de `third_party/luabridge` et 142 thunks : la résolution de
> l'API Lua se fait par `GetProcAddress` sur `xlua.dll`, comme aujourd'hui dans
> `lua_console.cpp`.

---

## 5. Les phases

Chaque phase est **build-intact** et **n'augmente pas l'empreinte Lua**. On vérifie
le diff de footprint avant de commiter.

### Phase 0 — Les invariants deviennent exécutables
- Créer `tools/check-invariants.sh` : grep sur `src/` qui **échoue** si on trouve
  `lua_setfield(L, LUA_GLOBALSINDEX`, `lua_setglobal`, `raw_setglobal`, un nom
  `__specter`, `lua_atpanic(`, un `#include` réseau, ou un `CreateThread`.
- Le rendre bloquant dans `tools/build-dll.sh`.
- **Critère** : passe sur `2572297` tel quel.

### Phase 1 — Arbor plat → couches
- `git mv` selon la table §3, réécriture des includes, mise à jour du `.vcxproj`,
  `.filters`, `tools/build-dll.sh`.
- Aucun changement de comportement, aucune ligne touchée hors includes.
- **Critère** : build vert, binaire de taille équivalente, invariants verts.

### Phase 2 — Namespaces par rôle
- `overlay::detour` → `specter::hook`, `overlay::game_input` → `specter::input`,
  `overlay` (dxgi) → `specter::dxgi`, `overlay::overlay_worker` → `specter::render`,
  `features::tp` → `features::teleport`.
- **Critère** : build vert, aucun symbole de hook changé.

### Phase 3 — Pompe + mailbox
- Extraire `lua/pump.{h,cpp}` (le detour, la découverte du state, la garde SEH) et
  `lua/mailbox.h` (transport typé, POD, verrou paresseux — qui remplace
  l'`ensure_lock()` de `lua_console.cpp`, aujourd'hui **non thread-safe**).
- Le pump ne connaît aucun canal ; chaque feature draine dans son propre `on_tick`.
- **Critère** : console et téléport se comportent comme avant.

### Phase 4 — Suppression de `poll_cli`
- `poll_cli` exécute `Z:\tmp\specter-lua\cmd.lua` : déclenché par le système de
  fichiers, sans UI, sans authentification. C'est un canal d'exécution de code, pas
  seulement un risque de détection. **On le retire**, ainsi que `tools/lua.sh` et le
  répertoire `Z:\tmp\specter-lua\`.
- **Critère** : plus aucune référence à `cmd.lua` ; le contrôle de la console passe
  par la seule UI.

### Phase 5 — Seam « feature » (registre)
- `features/feature.h` + `features/registry.cpp` (liste **explicite** — invariant 10).
- `render/d3d12_overlay.cpp` itère le registre et **perd** ses includes de features ;
  `app/specter.cpp` itère le registre pour l'installation.
- **Critère** : le coût d'ajout d'une feature tombe à « un dossier + une ligne ».

### Phase 6 — Fonctions nommées (`lua/call` + `lua/layer`)
- Le mécanisme du §4 : chunk qui retourne ses fonctions, refs anonymes.
- Migrer `features/teleport` : `send_setpos` (qui **fabrique du texte Lua en C++**)
  devient `SPECTER.teleport.to(x, y, z)` ; `kPosProbe` devient `SPECTER.teleport.pos()`.
- Migrer l'infinite stamina : `kStaminaInstall` / `kStaminaDisable` disparaissent, la
  couche Lua installe un patch **de classe** (vérifié : la classe est le metatable
  partagé, `AC == getmetatable(aca)`) qui lit `flags.inf_stamina`.
- **Critère** : le C++ ne contient plus une seule chaîne de Lua gameplay.

### Phase 7 — `lua_dump` comme module de premier plan
- `features/lua_dump` est un **outil de recherche**, pas une feature de jeu. Le
  documenter comme tel, et trancher une question qu'il faut poser explicitement :
  `install()` pose le detour sur `xluaL_loadbuffer` **au démarrage, inconditionnellement**.
  C'est un hook de plus que `2572297` n'avait pas.
  - Option retenue : le detour part avec le reste de l'armement (§ invariant 7), ou
    bien il est retiré du chemin d'injection.
- **Critère** : la décision est écrite, pas implicite.

### Phase 8 — Documentation
- Réécrire `docs/ARCHITECTURE.md` pour l'arbre réel ; mettre à jour `README.md`,
  `docs/LUA_CONSOLE.md`, `docs/TELEPORT.md`. Ce plan est absorbé.

---

## 6. Ce que ce plan ne prétend pas

- **Aucune garantie de non-détection.** `ANALYSE-DETECTION.md` §7 pose une
  contradiction non résolue entre O1 (`2572297` jamais signalé) et O3 (build désarmé
  signalé quand même), et H4 — un contrôle **natif** capable d'inspecter le registre,
  que Lua ne voit pas — reste la seule hypothèse qui réconcilie les deux. Ce plan
  **retire** des écritures dont on n'a pas la preuve qu'elles sont le vecteur ; ce
  n'est pas une preuve de sécurité.
- Les sanctions sont **asynchrones et par vagues** (`DETECTION.md` facteur 4) :
  l'absence d'avertissement à T+1h ne prouve rien. Cette base n'a pas été validée
  par ce critère, seulement par l'usage historique.
- H2 (« l'injection seule suffit ») reste ouverte et **ne serait pas corrigée** par
  ce plan : les hooks restent identiques.

---

## 7. Out of scope

- Toute feature qui parle aux commandes GM (interdit, invariant 1).
- Le réseau, l'exfiltration (invariant 2).
- L'execution de code arbitraire hors de l'UI (invariant 8).
- Windows natif : `NEPKernel.sys` s'y charge et le minifilter devient réel
  (`ANTICHEAT.md`). Ne pas jouer avec Specter tel quel hors Wine/Proton.