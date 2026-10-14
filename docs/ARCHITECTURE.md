# Architecture — Specter

> Le produit est **une seule DLL interne** (`Specter.Internal`), injectée dans
> `Aniimo.exe` par manual-map. Il n'y a pas de lecteur externe.
>
> Base du code : **`2572297`** (13 oct. 11:04), le dernier état jamais signalé.
> Ré-architecturé en couches — voir `docs/PLAN.md` pour le plan et sa
> justification. Ce document décrit **l'état réel**, pas un cible.

---

## 1. Le principe : un dossier = un rôle

L'arbre est un **empilement de couches**, et les dépendances vont **vers le bas**.
Un dossier porte le nom de son **rôle**, jamais celui d'un de ses occupants.

```
  app/          cycle de vie : DllMain + start()/stop()   (composition root)
   │
   ├── render/    front-end : overlay D3D12, fenêtre, input
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

La table est vérifiable à l'œil : `render/d3d12_overlay.cpp` n'inclut plus
**aucun** `.h` de feature, seulement `features/feature.h`. `lua/pump.cpp`
n'inclut rien de `features/`. C'est l'intérêt de la règle : une violation se
voit en lisant les includes, sans rien exécuter.

Les `#include` sont **root-relative** — `src/Specter.Internal` est le seul `-I` :

```cpp
#include "platform/log.h"          // et non "log.h"
#include "platform/hook/detour.h"  // et non "overlay/detour.h"
#include "il2cpp/api.h"            // et non "il2cpp-api.h"
```

Le **namespace** dit le rôle du module, le dossier porte la couche :
`specter::hook` (moteur de detour générique), `specter::render`, `specter::dxgi`,
`specter::input`, `specter::il2cpp`, `specter::lua::pump`, et sous `features`
`specter::features::console`, `::teleport`, `::lua_dump`.

---

## 2. L'arbre

```
src/Specter.Internal/
├── app/
│   ├── entry.cpp                    DllMain + bootstrap
│   └── specter.{h,cpp}              start()/stop() — composition root
├── render/
│   ├── dxgi_hook.{h,cpp}            hook vtable DXGI (Present/ResizeBuffers/Execute)
│   ├── d3d12_overlay.{h,cpp}        pont ImGui ↔ D3D12 ; itère le registre
│   ├── d3dcompiler_shim.cpp         D3DCompile paresseux (import-safe)
│   └── input.{h,cpp}                gate input + curseur (7 hooks user32)
├── features/
│   ├── feature.h                    l'interface d'une feature
│   ├── registry.cpp                 LE registre — une ligne par feature
│   ├── console/                     console Lua (le seul chemin d'exécution)
│   │   └── console.{h,cpp}
│   ├── lua_dump/                    dumper de chunks Lua (outil de RE)
│   │   └── lua_dump.{h,cpp}
│   ├── teleport/                    MIS EN COMMENTAIRE, hors build
│   │   └── teleport.{h,cpp}
│   └── inf_stamina/                 MIS EN COMMENTAIRE, hors build
│       └── inf_stamina.cpp
├── lua/
│   ├── pump.{h,cpp}                 detour CommonUpdate + tick(L)
│   └── mailbox.h                    transport inter-thread
├── il2cpp/
│   ├── runtime.{h,cpp}              localise GameAssembly + self_check
│   ├── api.{h,cpp}                  résolution des fonctions VM
│   └── target.h                     offsets et RVAs du jeu
└── platform/
    ├── log.{h,cpp}                  journalisation (pipe hôte)
    ├── nt.{h,cpp}                   spawn_hidden (thread is_system)
    ├── seh.h                        garde-fou SEH
    ├── hostch-rva.h                 GÉNÉRÉ
    └── hook/
        ├── detour.{h,cpp}           moteur de detour inline x86-64
        └── detour_ld_table.h        table du décodeur
```

---

## 3. Le seam « feature »

`features/feature.h` est l'interface ; `features/registry.cpp` en est la seule
liste. C'est **le seul endroit du dépôt qui nomme une feature**.

```cpp
struct Feature {
    const char* id;
    const char* tab;        // nullptr = feature sans UI
    bool (*install)();      // une fois, depuis app::start
    void (*draw_ui)();      // par frame, dans son onglet
};
```

`app/specter.cpp` itère le registre pour installer, `render/d3d12_overlay.cpp`
l'itere pour dessiner un onglet par feature. Ajouter une feature coûte **un
dossier + une ligne**.

La liste est explicite, jamais un auto-enregistrement par constructeur statique :
la DLL est manual-mappée, le guard CRT des statiques n'est pas initialisé, donc
un tel constructeur ne tournerait pas et la feature disparaîtrait **en silence**.

---

## 4. Le chemin Lua

Tout l'accès au Lua du jeu passe par trois modules, et il n'y a qu'un seul
endroit où du code est exécuté.

```
render/d3d12_overlay.cpp
        │ (le bouton Execute)
        ▼
features/console::submit()          file le chunk dans une Mailbox
        │
        ▼
lua::pump  ─ detour LuaManager.CommonUpdate, sur le thread Lua du jeu
        │  └─ console::on_lua_tick()  draine la mailbox
        ▼
lua::pump::run()                    le seul appel de lua_pcall du dépôt
```

**Le thread.** L'état Lua appartient au thread Lua du jeu, piloté par
`LuaManager.CommonUpdate`, que la pompe detour. C'est le seul moment où l'on est
sur ce thread, donc le seul où l'on peut appeler l'API Lua. Appeler depuis le
thread de rendu ferait traverser `longjmp` à des frames sans rapport.

Le state est trouvé par le chemin xLua documenté :
`LuaManager::luaenv` → `LuaEnv::rawL` (les deux offsets sont dans
`il2cpp/target.h`).

**Le transport.** `lua/mailbox.h` est un POD borné : une file de slots et un
slot de résultat, sous une `CRITICAL_SECTION` créée par `InitOnceExecuteOnce`.
Le verrou est paresseux parce que la DLL est manual-mappée — mais paresseux
**et** correct : le motif `if (!ready) { InitializeCriticalSection; ready = true; }`
qui existait auparavant était une course, deux threads pouvant franchir le test.

**La pompe ne connaît aucun canal.** Elle draine pour le compte de qui s'est
enregistré (`add_state_hook`, `add_tick_hook`). Une feature possède son
transport et se draine elle-même.

### Une seule exécution

```
lua::pump::run()  <-  1 appelant : features/console.cpp
console::submit() <-  1 appelant : le bouton « Execute »
```

C'est vérifiable en trois lignes de grep, et c'est vérifié à chaque build.
Il n'y a **ni** polling, **ni** timer, **ni** maintenance, **ni** canal CLI.

---

## 5. Ce qui est désactivé, et pourquoi

| Module | État | Raison |
|---|---|---|
| `features/teleport/` | commenté, hors build | déplacer le joueur exige d'exécuter du Lua sans que l'utilisateur ait demandé |
| `features/inf_stamina/` | commenté, hors build | idem : le toggle soumet un chunk, et la pompe le rejoue toutes les ~10 s |
| `poll_cli` | **supprimé** | exécutait `Z:\tmp\specter-lua\cmd.lua` : déclenché par le système de fichiers, sans UI, sans authentification |

Le code est conservé pour pouvoir revenir, avec en tête de chaque fichier ce
qu'il faut savoir pour le réactiver — dont, pour la stamina, la version qui a
été **vérifiée en jeu** : patcher la *classe*
(`ActorCombatAttribute.changeStamina`), pas l'instance, et lire le drapeau à
l'appel. Cela supprime d'un coup la maintenance périodique et le cas du relog.

---

## 6. Les invariants

Ce ne sont pas des recommandations ; deux sont vérifiables mécaniquement.

1. **Jamais de `CreateThread`** — uniquement `platform/nt::spawn_hidden()`, un
   worker `is_system` invisible aux handles utilisateur.
2. **Jamais de constructeur global ni de « magic static »** — la DLL est
   manual-mappée, le guard CRT des statiques n'est pas initialisé. Les objets
   d'espace de noms sont des POD à initialisation nulle ; les tables de
   dispatch (`g_state_hooks`, `g_tick_hooks`, le registre) sont des tableaux
   fixes remplis explicitement.
3. **Pas d'écriture dans l'état Lua du jeu** — ni global, ni clé nommée au
   registre, ni remplacement de `lua_atpanic`. *Point non tranché* : la question
   « faut-il des globals ? » reste ouverte, et c'est volontairement **non
   verrouillé** par un contrôle de build, pour pouvoir être revisitée dans les
   deux sens. Voir `docs/PLAN.md` §2.
4. **Aucun import réseau.** Le binaire produit n'importe que `KERNEL32`,
   `USER32`, `dxgi`, `SHELL32`, `IMM32`. Ce que le serveur reçoit est du
   trafic de jeu normal.
5. **Rien dans le dossier du jeu ni dans le prefix** — toute sortie part par le
   pipe hôte ou `Z:\tmp\...` (= racine Linux).

---

## 7. Le seam `generated/` vs `src/`

| | `generated/` | `src/` |
|---|---|---|
| Origine | `tools/dump.sh` (Il2CppInspectorRedux) | écrite à la main |
| Versionnée | non | oui |
| Rôle | **entrée** (bindings IL2CPP) | **le produit** |

Règle mécanique : sous `generated/`, on ne touche pas ; sous `src/`, c'est à
nous. Une seule exception : `platform/hostch-rva.h` est **généré et versionné**, parce
qu'un « clone puis build » doit rester possible sans wine-hostch.

---

## 8. Ce que ce document ne prétend pas

Rien ici ne rend le mod non détectable. `docs/ANALYSE-DETECTION.md` pose une
contradiction non résolue entre « `2572297` n'a jamais été signalé » et « un
build **désarmé**, qui n'exécute rien, l'a été quand même », et l'hypothèse la
plus cohérente avec les deux reste un contrôle **natif** capable d'inspecter le
registre — que Lua ne voit pas. Ce document décrit l'architecture, pas une
garantie.