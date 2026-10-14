# Plan — ré-architecture de `Specter.Internal`

> ✅ **EXÉCUTÉ** (branche `rebuild-from-2572297`). Le plan est ci-dessous pour ce
> qu'il explique ; l'état réel est dans `docs/ARCHITECTURE.md`.
>
> | Phase | Commit |
> |---|---|
> | 1 — déplacement en couches | `d8af0ed` |
> | 2 — namespaces par rôle | `e0771e0` |
> | 3 — pompe + mailbox, Execute seul chemin d'exécution | `d4e5b4f` |
> | 4 — seam feature (registre) | `d66f669` |
> | 5 — constantes RE dans `il2cpp/target.h` | `ebf59cb` |
> | 5 — garde SEH mutualisée | `eb70b06` |

> **Base** : `2572297` (13 oct. 11:04).
> **Objet** : réorganiser le code en couches, sans changement de comportement.
> **Règle unique côté Lua** : on n'écrit rien dans l'état Lua du jeu. Ni `_G`, ni
> clé nommée au registre, ni `lua_atpanic`. Le mode texte de `2572297`
> (`submit` / `take_result`) est conservé tel quel.

---

## 1. Le problème

Le code est propre *à l'intérieur* de ses modules ; c'est le **rangement** qui ne
suit aucune règle. On ne peut pas dire « qui est la base » sans ouvrir les
fichiers.

1. **La racine mélange quatre rôles.** `entry.cpp` / `specter.cpp` (cycle de vie),
   `runtime.*` / `il2cpp-api.*` (seam VM), `log.*` / `nt.*` (primitives),
   `hostch-rva.h` (généré) : quatre responsabilités côte à côte.
2. **Les dossiers sont nommés d'après un occupant, pas un rôle.** `overlay/`
   contient `detour.*`, un **moteur de hook générique** aussi utilisé par
   `game_input` — rien de « overlay ».
3. **`lua_console.{h,cpp}` (808 lignes) fait trois métiers** : le detour
   `CommonUpdate` (de l'infra), le transport inter-thread, et la console (une
   feature). Il est dans `features/`, alors que deux des trois sont de l'infra.
4. **La couche `features` n'a pas de seam.** `d3d12_overlay.cpp` **inclut** chaque
   feature, et `specter.cpp` les câble en dur. Ajouter une feature touche 3–4
   fichiers.
5. **Les constantes RE sont dispersées** (offsets `0x18`/`0x10`, RVA
   `0x172ADC0`, indices de vtable) au fond des modules.
6. **`lua_console.cpp` a un `ensure_lock()` qui n'est pas thread-safe** :
   `if (!g_lock_ready) { InitializeCriticalSection(...); g_lock_ready = true; }` —
   deux threads peuvent passer le test avant l'initialisation.

Le but : **en lisant seulement l'arbre, comprendre l'architecture.**

---

## 2. Le principe

> L'arbre est un **empilement de couches**. Les dépendances vont **vers le bas**.
> Un dossier est nommé pour son **rôle**, jamais pour un de ses occupants.

```
  app/          cycle de vie : DllMain + start()/stop()   (composition root)
   │
   ├── render/    front-end : overlay D3D12, fenêtre, input, UI
   └── features/  les fonctionnalités, une par dossier
        │
   lua/  il2cpp/  infra : pompe Lua, seam VM
        │
   platform/      primitives réutilisables : log, threads cachés, hook engine
```

| Couche | Peut inclure | Ne peut **pas** inclure |
|---|---|---|
| `app/` | `render/`, `features/`, `lua/`, `il2cpp/`, `platform/` | — |
| `render/` | `features/` (via le **registre** seulement), `lua/`, `il2cpp/`, `platform/` | `app/`, un `.h` de feature précis |
| `features/` | `lua/`, `il2cpp/`, `platform/` | `app/`, `render/` |
| `lua/` | `platform/` | tout le reste |
| `il2cpp/` | `platform/` | tout le reste |
| `platform/` | *(rien en interne)* | tout le reste |

Trois invariants — ils marchent aujourd'hui, on ne les casse pas :

1. **jamais de `CreateThread`** : uniquement via `platform/nt::spawn_hidden()` ;
2. **jamais de constructeur global / « magic static »** : la DLL est manual-mappée,
   le guard CRT des statiques n'est pas initialisé. Les objets d'espace de noms
   sont des POD à initialisation nulle, et tout enregistrement est **explicite** ;
3. **provisoirement** : pas d'écriture dans l'état Lua du jeu — ni global
   (`_G.…`, `lua_setglobal`, `LUA_GLOBALSINDEX`), ni clé nommée au registre, ni
   remplacement de `lua_atpanic`. On **exécute** des chunks et on lit des
   valeurs ; on ne **dépose rien**.

> ⚠️ **L'invariant 3 n'est pas figé.** La question « faut-il des globals ? »
> sera tranchée plus tard, et elle a des conséquences dans les deux sens : le mode
> texte est moche, un namespace publié est plus propre à lire. **Tant que la
> décision n'est pas prise, on ne verrouille rien mécaniquement** — un contrôle de
> build qui interdit les globals prendrait la décision à la place du lecteur, et
> il faudrait l'abolir le jour où elle s'inverse.
>
> Les invariants 1 et 2, eux, sont acquis et peuvent être contrôlés dès
> maintenant.

---

## 3. Arbre cible

```
src/Specter.Internal/
├── app/
│   ├── entry.cpp                    DllMain + bootstrap
│   └── specter.{h,cpp}              start()/stop() — composition root
│
├── render/
│   ├── dxgi_hook.{h,cpp}            hook vtable DXGI (Present/ResizeBuffers/Execute)
│   ├── d3d12_overlay.{h,cpp}        pont ImGui ↔ D3D12 + l'UI
│   ├── d3dcompiler_shim.cpp         D3DCompile paresseux (import-safe)
│   └── input.{h,cpp}                (ex game_input) gate input + curseur
│
├── features/
│   ├── feature.h                    l'interface d'une feature + le registre
│   ├── registry.cpp                 LA ligne unique qui câble chaque feature
│   ├── teleport/                    (ex tp) slots + marks + lerp
│   │   └── teleport.{h,cpp}
│   ├── console/                     console Lua (UI + résultat)
│   │   └── console.{h,cpp}
│   └── lua_dump/                    dumper de chunks (outil de RE)
│       └── lua_dump.{h,cpp}
│
├── lua/
│   ├── pump.{h,cpp}                 detour CommonUpdate + tick(L)   ← extrait
│   └── mailbox.h                    transport inter-thread          ← nouveau
│
├── il2cpp/
│   ├── runtime.{h,cpp}              localise GameAssembly + init
│   ├── api.{h,cpp}                  (ex il2cpp-api) résolution mono_*
│   └── target.h                     constantes RE regroupées       ← nouveau
│
└── platform/
    ├── log.{h,cpp}                  journalisation (pipe / fichier)
    ├── nt.{h,cpp}                   spawn_hidden (thread is_system)
    ├── seh.h                        garde-fou SEH du pump           ← nouveau
    ├── hostch-rva.h                 GÉNÉRÉ (bannière AUTO-GENERATED)
    └── hook/
        ├── detour.{h,cpp}           moteur de detour inline générique
        └── detour_ld_table.h        table du décodeur x86-64
```

### Correspondance (état actuel → cible)

| Aujourd'hui | Cible | Nature |
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
| `features/tp.{h,cpp}` | `features/teleport/*` | déplacement + renommage |
| `features/lua_dump.{h,cpp}` | `features/lua_dump/*` | déplacement |
| `features/lua_console.{h,cpp}` | **éclaté** : `lua/pump.*` + `lua/mailbox.h` + `features/console/*` | refactor |

Style d'include résultant (tout relatif à la racine `src/Specter.Internal`,
qui reste le seul `-I`) :

```cpp
#include "app/specter.h"            // et non "specter.h"
#include "platform/log.h"           // et non "log.h"
#include "platform/hook/detour.h"   // et non "overlay/detour.h"
#include "il2cpp/api.h"             // et non "il2cpp-api.h"
#include "lua/pump.h"
#include "features/feature.h"
```

---

## 4. Les seams à introduire

Le déplacement seul rend l'arbre lisible, mais ne corrige pas l'inversion de
couche. C'est l'objet des trois seams ci-dessous.

### 4.1 Seam « feature » (corrige le n°4)

Aujourd'hui l'UI **inclut** chaque feature. On introduit une interface minuscule ;
l'UI ne connaît plus que le registre.

```cpp
// features/feature.h
namespace specter::features {

struct Feature {
    const char* id;            // stable, unique
    const char* tab;           // section de menu
    bool (*install)();         // une fois, depuis app::start
    void (*draw_ui)();         // à chaque frame, thread de rendu
    void (*on_tick)();         // à chaque tick de la pompe
};

// Le registre : le SEUL endroit où une feature est câblée.
const Feature* const* registry();
int registry_count();

}  // namespace specter::features
```

- `registry.cpp` liste les features, **une ligne chacune** (explicite : pas de
  static initializer, cf. invariant CRT).
- `render/d3d12_overlay.cpp` itère `registry()` — il n'inclut plus `teleport.h`,
  `console.h`, `lua_dump.h`.
- `app/specter.cpp` itère le même registre pour `install()`.

**Gain** : le coût d'ajout d'une feature tombe à « un dossier + une ligne ».

### 4.2 Extraire la pompe Lua (corrige le n°3)

`lua_console.cpp` (808 lignes) fait trois métiers. On les sépare :

- `lua/pump.{h,cpp}` — **infra** : detour de `LuaManager.CommonUpdate`, suivi du
  `lua_State` (`LuaManager.luaenv(0x18)` → `LuaEnv.rawL(0x10)`), garde SEH, et
  un point d'extension par tick. Seams : `pump::install()`, `pump::ready()`,
  `pump::ticks()`.
- `lua/mailbox.h` — **transport inter-thread** : `Mailbox<Slots, Policy>`,
  POD à initialisation nulle, verrou créé paresseusement. C'est ce qui remplace
  l'`ensure_lock()` du n°6, **non thread-safe**.
- `features/console/*` — **feature** : file de chunks + résultat + canal TP.

Décision figée : le pump ne connaît **aucun canal**. Il draine pour le compte de
qui s'est enregistré (`on_new_state` / `on_tick`), et chaque feature possède son
propre transport.

```cpp
// lua/mailbox.h — exemple d'usage
lua::Mailbox<1, Replace>  console_q;   // 1 requête : la dernière gagne
lua::Mailbox<4, Drop>     tp_q;        // quelques requêtes, on abandonne au-delà
```

### 4.3 Regrouper les constantes RE (corrige le n°5)

`il2cpp/target.h` rassemble les valeurs propres à la cible : offsets de champs
(`LuaManager.luaenv 0x18`, `LuaEnv.rawL 0x10`), RVA (`CommonUpdate 0x172ADC0`),
idx de vtable DXGI, RVA `xluaL_loadbuffer`. Un seul endroit à mettre à jour lors
d'une maj du jeu.

---

## 5. Le plan de migration

Chaque phase est **build-intact** : la DLL reste injectable, le comportement
identique, on vérifie, on commit, on avance.

### Phase 0 — outillage
- **But** : que les violations acquises se voient. Créer
  `tools/check-invariants.sh` qui **échoue** si on trouve `CreateThread`, un
  `#include` réseau, ou un constructeur global, et le brancher sur
  `tools/build-dll.sh`.
- **Hors périmètre pour l'instant** : ne **pas** contrôler les écritures dans
  l'état Lua du jeu. La question des globals n'est pas tranchée (§2, invariant 3) ;
  la contrôler maintenant reviendrait à trancher à la place du lecteur.
- Créer `tools/gen-compile-commands.sh` + `.clangd` pour l'IntelliSense.
- **Critère** : le contrôle passe sur `2572297` tel quel.

### Phase 1 — déplacement + renommage (mécanique)
- **Contenu** : la table de correspondance du §3. Uniquement `git mv` +
  réécriture des `#include` + mise à jour des fichiers projet.
- **Fichiers à mettre à jour** : `Specter.Internal.vcxproj`,
  `Specter.Internal.vcxproj.filters` (à réparer au passage), `tools/build-dll.sh`.
- **Ne change pas** : aucune ligne hors `#include`.
- **Critère** : build vert, taille de binaire équivalente, contrôles verts.

### Phase 2 — namespaces par rôle
- `overlay::detour` → `specter::hook`
- `overlay::game_input` → `specter::input`
- `overlay` (dxgi) → `specter::dxgi`, et `overlay::overlay_worker` → `specter::render`
- `features::tp` → `features::teleport`
- **Critère** : build vert, aucun symbole de hook changé (les hooks sont
  identifiés par leur cible, pas par leur namespace — mais le vérifier).

### Phase 3 — pompe + mailbox
- **Contenu** : créer `lua/pump.{h,cpp}` et `lua/mailbox.h`, déplacer le detour,
  la découverte du state et la garde SEH depuis `lua_console.cpp` ; le reste
  devient `features/console/*`.
- **Fichiers à mettre à jour** : `Specter.Internal.vcxproj`, `.filters`,
  `app/specter.cpp` (ordre d'install : **le pump en dernier**).
- **Critère** : console et téléport se comportent comme avant ; le n°6 est clos
  (le verrou est désormais initialisé une seule fois, correctement).

### Phase 4 — seam « feature »
- **Contenu** : `features/feature.h` + `features/registry.cpp` ;
  `render/d3d12_overlay.cpp` itère le registre et **perd** ses `#include` de
  features ; `app/specter.cpp` itère le registre.
- **Critère** : chaque onglet s'affiche et se pilote comme avant.

### Phase 5 — constantes RE et garde SEH
- **Contenu** : `il2cpp/target.h` (offsets/RVA/idx regroupés) ; `platform/seh.h`
  (`seh::Guard`, réutilisable par le pump et par tout detour qui doit survivre à
  une exception).
- **Critère** : build vert, comportement identique.

### Phase 6 — documentation
- **Contenu** : réécrire `docs/ARCHITECTURE.md` pour l'arbre réel ; mettre à jour
  `README.md` (arborescence), `docs/LUA_CONSOLE.md`, `docs/TELEPORT.md`. Ce plan
  est absorbé dans `ARCHITECTURE.md`.
- **Option** : harnais *host-side* pour la logique pure sans jeu — le décodeur
  x86-64 de `platform/hook/detour`, le parsing de `teleport`.

---

## 6. Ce que la ré-architecture ne change pas

- Les hooks : detour `LuaManager.CommonUpdate`, vtables DXGI, 7 hooks `user32`.
- Le mode d'accès au Lua : résolution par `GetProcAddress` sur `xlua.dll`, chunks
  exécutés sur le thread Lua via la pompe.
- Le transport d'I/O : pipe hôte, `Z:\tmp\...` (hors prefix), jamais dans le
  dossier du jeu.
- Les commandes : `tools/build-dll.sh`, `tools/specter-up.sh`, `tools/dump.sh`.
- La sortie : `generated/bin/Release/Specter.Internal.dll`, imports
  `dxgi`/`IMM32`/`KERNEL32`/`SHELL32`/`USER32` uniquement.
- Les règles de discrétion (manual-map, worker `is_system`, pas d'objet nommé,
  pas de socket, pas de fichier dans le prefix).
- Le comportement observé du mod.

---

## 7. Hors périmètre

- **Pas de changement de comportement.** Aucun correctif fonctionnel n'est
  introduit par ce plan, hormis le n°6 (verrou non thread-safe), qui est une
  correction de bug.
- **Point non tranché : les écritures dans l'état Lua du jeu** (invariant n°3 du
  §2). Le mode texte de `2572297` n'en fait aucune ; mais globals ou pas reste
  **à décider**, et cette décision n'appartient pas à ce plan. Tant qu'elle n'est
  pas prise, on n'écrit rien — sans que quoi que ce soit ne l'impose
  mécaniquement, pour pouvoir la revoir dans les deux sens.
- **Pas de nouvelle feature**, et pas de feature dérivée d'un mod tiers.
- **Windows natif** : hors Wine/Proton, `NEPKernel.sys` se charge et le minifilter
  devient réel. Ne pas jouer avec Specter tel quel hors Wine/Proton.