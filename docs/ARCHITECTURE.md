# Architecture — Specter

Ce document décrit l'architecture du projet avec un vocabulaire volontairement
partagé et restreint (skill **codebase-design**) : **module**, **interface**,
**implémentation**, **seam**, **adaptateur**, **profondeur**.

> Le produit est **une seule DLL interne** (`Specter.Internal`), injectée dans
> `Aniimo.exe`. Il n'y a pas de lecteur externe.

---

## Le seam principal : `generated/` vs `src/`

Tout le projet tient sur une seule frontière, et c'est la plus importante :

| | `generated/` | `src/` |
|---|---|---|
| Origine | produite par `tools/dump.sh` | écrite à la main |
| Versionnée | non | oui |
| Autorité | l'outil (Il2CppInspectorRedux) | l'auteur |
| Rôle | **entrée** (bindings IL2CPP) | **le produit** (la DLL) |
| Modification | à chaque régénération | jamais par l'outil |

C'est ce qui remplace le mélange d'origine : les en-têtes de 200 Mo du SDK ne
sont **jamais** édités, et le code métier ne se retrouve **jamais** écrasé par
une régénération. La règle est mécanique : si c'est sous `generated/`, on ne le
touche pas ; si c'est sous `src/`, c'est à nous.

`generated/sdk/framework/` (le scaffold d'injection produit par l'outil) est
consommé presque **tel quel** : `il2cpp-init`, `helpers` et `pch` sont utilisés
sans modification. **Une seule pièce est reprise à notre compte** : le
`dllmain.cpp` généré n'est **pas compilé** — nous fournissons notre propre
`DllMain` (`src/Specter.Internal/entry.cpp`) pour maîtriser le comportement
d'entrée (voir « Injection, threads et discrétion »). On ne modifie donc rien
sous `generated/` : on cesse simplement de dépendre de son point d'entrée.

---

## Le module produit : `Specter.Internal`

C'est un **module profond** : une interface minuscule
(`specter::start()` / `specter::stop()`) derrière laquelle se trouve une grosse
implémentation (localiser le runtime IL2CPP, résoudre son API, poser des hooks,
enregistrer des fonctionnalités).

```
        ┌──────────────────────────────────────────────┐
        │  interface   specter::start() / stop()        │  ← 2 appels
        ├──────────────────────────────────────────────┤
        │  runtime  ·  log  ·  (hooks)  ·  (features)   │
        │  + offsets issus de generated/sdk/appdata      │  ← implémentation
        └──────────────────────────────────────────────┘
```

Le test de suppression : si on supprimait `specter`, la complexité (résolution
du runtime, ordre d'initialisation, hooks) ne disparaîtrait pas — elle
réapparaîtrait dans chaque point d'entrée. Le module gagne donc sa place.

### Composants

| Fichier | Rôle | Nature |
|---|---|---|
| `entry.cpp` | possède `DllMain` + `LOG_FILE`, appelle `specter::start()` inline | adaptateur (point d'entrée, sans logique) |
| `specter.{h,cpp}` | l'interface du produit | module profond |
| `runtime.{h,cpp}` | localise `GameAssembly.dll`, résout l'API IL2CPP | seam interne |
| `nt.{h,cpp}` | pont NT/hostch : `spawn_hidden()` → `HostchSpawnThread` | adaptateur (fork) |
| `hostch-rva.h` | RVA bakée du point d'entrée `HostchSpawnThread` | généré par le build |
| `log.{h,cpp}` | journalisation : pipe hôte, repli fichier | seam interne (2 adaptateurs) |

### Pourquoi `runtime` est un vrai seam (et pas de l'indirection)

Un seam se justifie quand **au moins deux adaptateurs** existent de part et
d'autre. Ici, « comment obtenir l'API IL2CPP » varie réellement :

1. **scan de motifs** (signature/motif scanning dans `GameAssembly.dll`) — la
   seule voie pour les `il2cpp_*` non exportés ;
2. **table d'offsets statique** dérivée du SDK ;
3. (à terme) un **faux** en test, où l'API est fournie en mémoire.

Le reste du code appelle `runtime::initialize()` / `runtime::module_base()` sans
savoir laquelle est active. Les offsets **par méthode** de
`generated/sdk/appdata/il2cpp-functions.h` sont, eux, relatifs à
`module_base()` et ne nécessitent aucune résolution : ils sont donc utilisés
directement, sans passer par un seam inutile.

---

## Logs : deux adaptateurs derrière un même seam

Le module `log` expose toujours la même interface minuscule (`info` / `error`)
mais choisit son **adaptateur** au démarrage (`log::init()`) :

| Adaptateur | Où vont les octets | Trace côté Windows |
|---|---|---|
| **pipe hôte** | FIFO créée côté Linux, atteinte via le disque `Z:` de Wine | aucun fichier dans le préfixe — juste un *handle* |
| **fichier** | `il2cppi_log_write` du scaffold (repli) | un fichier `specter-log.txt` |

Deux adaptateurs réels justifient donc le seam (et non de l'indirection) : on
peut basculer pipe/fichier sans toucher aux appelants.

### Pourquoi un pipe via `Z:`

Sous Wine/Proton, le disque `Z:` pointe vers la racine Linux. La DLL ouvre donc
une simple FIFO — côté Windows `Z:\tmp\specter.pipe`, côté hôte
`/tmp/specter.pipe` — et y écrit son flux. C'est **vérifié empiriquement** sur
cette machine (Wine + binaire MinGW) :

- l'ouverture en `GENERIC_READ | GENERIC_WRITE` **ne bloque pas** l'attente d'un
  lecteur (contrairement à un `open(O_WRONLY)` Unix) ;
- un **handle persistant** ouvert une fois au démarrage livre toutes les lignes
  dans l'ordre ;
- aucune écriture disque n'est faite dans le préfixe du jeu.

Détails d'implémentation importants :

- le pipe est résolu par `SPECTER_PIPE` (variable d'environnement Windows),
  sinon `Z:\tmp\specter.pipe` ;
- si la FIFO n'existe pas / n'est pas ouvrable, on **retombe** sur le fichier ;
- l'écriture est sérialisée par une section critique (logs multi-thread) ;
- `init()` est appelé en tête de `specter::start()` — donc avant tout log.

Côté hôte, `tools/specter-tap.sh` crée la FIFO et affiche le flux
(`cat`, ou `tee` vers un fichier). Il doit tourner **avant** le chargement de la
DLL (sinon la FIFO n'existe pas et la DLL reste sur le repli fichier).

> Alternative non retenue : socket TCP loopback — plus visible côté réseau, et
> ce n'est pas un « pipe ».

---

## Injection, threads et discrétion

L'injection se fait avec **wine-hostch** :

```
hostch.py map --pe Specter.Internal.dll --dllmain --hide-system
```

- le PE est **manual-mappé** : zéro PEB/Ldr, le DLL n'apparaît dans **aucune**
  liste de modules ;
- le thread qui exécute `DllMain` est un thread Wine **canonique**, créé par le
  `NtCreateThreadEx` **du guest** (pas de ptrace), et marqué `is_system` **côté
  serveur** → **invisible** de toute énumération de threads côté jeu.

D'où une règle d'architecture :

> **Ne jamais appeler `CreateThread` depuis la DLL.**

Un `CreateThread` produirait un thread **visible** dont l'adresse de départ
pointe dans la mémoire manual-mappée — le signal d'anti-cheat typique « *thread
dont l'adresse de départ n'appartient à aucun module connu* ». Il annulerait la
discrétion que l'injecteur procure.

Conséquence concrète : notre `DllMain` (`entry.cpp`) exécute `specter::start()`
**inline**, sur le thread caché de l'injecteur, et **ne crée aucun thread** —
c'est pourquoi le `framework/dllmain.cpp` généré (qui fait un `CreateThread`)
n'est pas compilé. C'est suffisant pour le périmètre actuel (logs courts,
compatibles avec le loader lock).

### Workers persistants : `nt::spawn_hidden()`

Plutôt que de solliciter l'hôte à chaque worker, on a **étendu notre fork**.
`wine-hostch/patches/hostch-spawnthread.patch` ajoute une entrée **dédiée et non
exportée** `HostchSpawnThread` dans `ntdll.dll` : elle crée un thread `is_system`.
Notre DLL la résout par **RVA** — bakée par le build dans `hostch-rva.h` via
`wine-hostch/emit-hostch-rva.sh` — et l'appelle :

```cpp
// src/Specter.Internal/nt.cpp
uintptr_t base = (uintptr_t)GetModuleHandleW(L"ntdll.dll");
auto fn = (HostchSpawnFn)(base + SPECTER_HOSTCH_SPAWN_RVA);
fn(&h, SPECTER_HOSTCH_SPAWN_MAGIC, worker, arg);   // -> thread is_system
```

**Pourquoi non exportée :** un export nommé dans `ntdll` serait **énumérable** par
NEP2 (un *tell*). Le nom n'existe que chez nous et dans le source Wine, et un
**magic** (loquet) garantit que seul un appelant connaissant le secret peut créer
un thread caché.

**Pourquoi par RVA :** c'est le prix de la non-exportation ; le build émet la RVA
(cf. `emit-hostch-rva.sh`), à régénérer à chaque rebuild de `ntdll`.

La règle devient donc : **depuis la DLL, on ne crée un thread que via
`nt::spawn_hidden()`** — jamais `CreateThread`. Et comme le thread naît **hors
loader**, il ne reçoit pas `DLL_THREAD_ATTACH` : le worker doit initialiser son
CRT par-thread (`_CRT_INIT((HMODULE)&__ImageBase, DLL_THREAD_ATTACH, nullptr)`).

---

## Contrainte structurante : aucun `il2cpp_*` exporté

`GameAssembly.dll` exporte 390 fonctions, **zéro** en `il2cpp_*` (retirées par
NetEase Protect 2). Conséquences directes sur l'architecture :

- `generated/sdk/appdata/il2cpp-api-functions.h` est **vide** ;
- le template d'origine qui appelle `il2cpp_thread_attach(il2cpp_domain_get())`
  **ne compile pas** (symboles absents) — `entry.cpp` ne l'appelle donc pas ;
- toute la résolution de l'API est **concentrée** dans `runtime`, précisément
  pour que le reste du code n'ait jamais à s'en soucier.

C'est le principal travail à venir : implémenter le scan de motifs derrière
`runtime::initialize()`.

---

## Où vont les fonctionnalités

Une **fonctionnalité** = un module sous
`src/Specter.Internal/features/<nom>/`, avec une interface étroite
(`enable()` / `disable()`, ou un hook) et son implémentation cachée. Elle est
branchée une seule fois dans `specter::start()`.

On n'introduit pas encore de seam `features` : il n'existe pour l'instant
**aucune** fonctionnalité (un seam à un seul adaptateur n'est que de
l'indirection). Le dossier apparaît avec la première fonctionnalité.

---

## Vue d'ensemble

```
tools/                     pipeline RE (langage hôte : Python + bash)  ── module
  metadata_decrypt.py        déchiffre la metadata NEProtect2
  dump.sh                    interface : « régénère generated/ »
  specter-tap.sh             interface : « affiche les logs de la DLL »

generated/                 entrée — produite par dump.sh, jamais éditée
  sdk/appdata/               SDK C++ (types + offsets de méthodes)
  sdk/framework/             scaffold d'injection (init, helpers, pch ; dllmain non compilé)
  dump/                      dump.cs, il2cpp.py, metadata.json
  shims/                     assemblies .NET
  input/                     liens vers le jeu + metadata déchiffrée

src/Specter.Internal/      le produit — la DLL interne (voir ci-dessus)
docs/                      ce document + notes
```

---

## Compiler

1. `tools/dump.sh` (crée `generated/` — nécessaire avant toute compilation) ;
2. ouvrir `src/Specter.Internal/Specter.sln` (Visual Studio, **x64**),
   configurer `Release|x64`, compiler ;
3. sortie : `generated/bin/Release/Specter.Internal.dll`.

L'injection de la DLL et les hooks relèvent de l'expérimentation locale
uniquement (process possédé, hors ligne).
