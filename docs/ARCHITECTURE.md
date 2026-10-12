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
| `entry.cpp` | possède `DllMain` + `LOG_FILE`, lance le worker caché via `nt::spawn_hidden()` | adaptateur (point d'entrée, sans logique) |
| `specter.{h,cpp}` | l'interface du produit | module profond |
| `runtime.{h,cpp}` | localise `GameAssembly.dll`, orchestre l'init + `self_check()` | seam interne |
| `il2cpp-api.{h,cpp}` | résout l'API du VM : noms `mono_*` vérifiés corps à corps | seam interne |
| `nt.{h,cpp}` | pont NT/hostch : `spawn_hidden()` → `HostchSpawnThread` | adaptateur (fork) |
| `hostch-rva.h` | RVA bakée du point d'entrée `HostchSpawnThread` | généré par le build |
| `log.{h,cpp}` | journalisation : pipe hôte, repli fichier | seam interne (2 adaptateurs) |
| `overlay/dxgi_hook.{h,cpp}` | objets sonde → patch des vtables COM `Present`/`Present1`/`ResizeBuffers`/`ExecuteCommandLists` | seam interne |
| `overlay/d3d12_overlay.{h,cpp}` | pont ImGui ↔ D3D12 : rendu de l'UI sur la queue du jeu, dans le `Present` | seam interne |

### Pourquoi `runtime` est un vrai seam (et pas de l'indirection)

Un seam se justifie quand **au moins deux adaptateurs** existent de part et
d'autre. Ici, « comment obtenir l'API IL2CPP » varie réellement :

1. **résolution par exports** (`mono_*` vérifiés corps à corps via
   `GetProcAddress`) — la voie actuelle, voir `il2cpp-api.{h,cpp}` ;
2. **scan de motifs** (signature/motif scanning dans `GameAssembly.dll`) — la
   voie de repli pour une fonction du VM qui ne serait pas exportée ;
3. **table d'offsets statique** dérivée du SDK ;
4. (à terme) un **faux** en test, où l'API est fournie en mémoire.

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

Conséquence concrète : notre `DllMain` (`entry.cpp`) ne fait qu'**une chose** —
lancer la mise en route sur un thread caché via `nt::spawn_hidden()`, puis rendre
la main. Le bring-up (`init_il2cpp()` + `specter::start()`, donc le **log
d'init**) s'exécute sur ce worker `is_system`, pas sur le thread de l'injecteur.
C'est pourquoi le `framework/dllmain.cpp` généré (qui fait un `CreateThread`)
n'est pas compilé.

### `nt::spawn_hidden()` — le seul moyen de créer un thread

`DllMain` s'en sert déjà pour le worker d'init, et tout worker persistant futur
(boucle, dispatcher de hooks) doit passer par là. Plutôt que de solliciter
l'hôte à chaque thread, on a **étendu notre fork**.
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

## Contrainte structurante : pas d'`il2cpp_*` exporté

`GameAssembly.dll` exporte 390 fonctions, **zéro** en `il2cpp_*` (renommées par
NetEase Protect 2). Ce que c'est vraiment, une fois la table d'export lue :

- `118` noms `mono_*` — la couche de compat Mono du VM (une partie de l'API) ;
- `245` noms obfusqués `i…` — le reste de l'API il2cpp, renommé ;
- le reste (~27) : Brotli et divers symboles tiers ;
- les **noms de symboles** `il2cpp_*` ont été retirés du binaire (0 hit en
  strings), et les exports `mono_*` qui concernent l'API ne sont **pas** la
  liste canonique : certains nomments sont **aliasés** arbitrairement.

Conséquences sur l'architecture :

- `generated/sdk/appdata/il2cpp-api-functions.h` est **vide** ;
- aucune résolution par nom `il2cpp_*` (GetProcAddress / import) n'est possible ;
- la résolution de l'API est **concentrée** dans `api/` (`il2cpp-api.{h,cpp}`)
  + `runtime`, pour que le reste du code n'ait jamais à s'en soucier.

### Résolution de l'API : export `mono_*` vérifiés corps à corps

Pas de scan de motifs : les fonctions du VM existent, elles sont simplement
exportées autrement. On résout donc les noms `mono_*` par `GetProcAddress`, en
ne retenant QUE des fonctions dont le **corps a été décompilé et vérifié** sur
le vrai binaire (IDA, base `0x180000000`). Ce que la vérification a établi :

- **Vrais accesseurs** (corps distincts, offsets cohérents avec les structs) :
  `mono_string_length` lit `Il2CppString.length` @+16, `mono_string_chars`
  renvoie @+20, `mono_image_get_name` lit `Il2CppImage.name` @+0,
  `mono_image_get_assembly` @+16, `mono_method_get_name` @+24 (MethodInfo),
  `mono_method_get_class` @+32 (MethodInfo.klass).
- **Pièges — clusters d'alias vers des stubs inertes** : plusieurs noms
  partagent le même corps, parfois **vide** (`mono_field_set_value`,
  `mono_arch_*` → corps vide) ou **`return 0`** (`mono_array_length`,
  `mono_jit_info_get_method`, …). **Ne jamais appeler** un nom du cluster sans
  vérifier son corps.
- **Piège — noms trompeurs** : `mono_class_get_flags` lit un `uint32` à +88
  (layout runtime ≠ layout SDK) ; ne pas déduire la sémantique du nom seul.
- **Refactor Unity 2023.2** : `Il2CppClass` a déplacé `name`/`namespace`/
  `methods` dans un bloc opaque pointé à `class+80`. Le layout SDK généré ne
  correspond **pas** au layout runtime pour cette structure : ne jamais
  parcourir les champs d'`Il2CppClass` directement ici, passer par les
  accesseurs `mono_*` vérifiés.

Ajouter une fonction à l'API = 1) décompiler son corps, 2) confirmer que ce
n'est ni un stub du cluster, ni un accesseur au mauvais offset, 3) l'ajouter à
`il2cpp-api.h` (names + `Table`) et au `bind` de `il2cpp-api.cpp`.

`runtime::initialize()` appelle `api::resolve()` ; `runtime::self_check()`
(première fonctionnalité) prouve l'API depuis l'intérieur du process : round
trip de string managée, énumération des assemblies, introspection de classe.

---

## Overlay D3D12 (ImGui)

Le jeu rend en **D3D12** (vkd3d-proton) à travers `dxgi.dll`. Le sous-système
`overlay/` pose un overlay ImGui sans toucher au renderer du jeu :

1. `dxgi_hook` crée des objets **sonde** (device + queue + swapchain + fenêtre
   cachée à nous) et lit les **vtables COM partagées** de `DxgiSwapChain` et
   `ID3D12CommandQueue`. Une classe n'a qu'**une** vtable (en `.rdata`), donc
   remplacer une entrée intercepte aussi les objets du jeu : `Present` (vt[8]),
   `Present1` (vt[22]), `ResizeBuffers` (vt[13]) et `ExecuteCommandLists`
   (queue vt[10]). Le pointeur d'origine sauvegardé est l'« original » ; une
   garde de ré-entrance garantit **un seul** rendu par frame.
   *Pourquoi la vtable et pas un détour inline* : un trampoline doit recopier
   des **instructions entières** ; le prologue DXVK de `Present`
   (`mov rcx,[rcx+10]` / `mov rax,[rcx]` / `mov rax,[rax+40]` / `mov r10d,edx`)
   coupe `mov r10d,edx` à 12 octets et corrompt le trampoline (registres/args
   bidons → `Present` renvoie une erreur et le jeu se fige). La vtable ne
   demande aucune relocalisation.
2. Le hook `ExecuteCommandLists` apprend **la queue du jeu** (celle dont le
   device est celui de la swapchain). `d3d12_overlay` s'initialise paresseusement,
   au premier `Present`, sur le **device du jeu** et **cette queue** : il bascule
   le backbuffer `PRESENT → RENDER_TARGET`, dessine, rebascule, exécute, puis
   laisse le `Present` original présenter la frame. Utiliser la queue du jeu est
   nécessaire : vkd3d-proton enfile le vrai `vkQueuePresentKHR` sur la queue de
   la swapchain et blitte depuis le backbuffer en supposant un ordre sur cette
   **même** queue (rendre sur une queue privée est une hazard cross-queue).
3. `ResizeBuffers` libère nos références aux anciens backbuffers **avant**
   l'appel original : DXGI refuse de redimensionner tant qu'un backbuffer est
   encore référencé (sinon le `ResizeBuffers` du jeu échoue).

Discrétion : patchs en vtable (mémoire `.rdata` de `dxgi.dll`/`d3d12core.dll`),
jamais de fichier écrit (`io.IniFilename = nullptr`), fenêtre sonde cachée,
aucun `CreateThread` (le worker vient de `nt::spawn_hidden`). Les attentes de
fence sont **bornées** : le thread de rendu ne peut jamais geler. La touche
**SUPPR** ouvre/ferme le menu.

`overlay/d3dcompiler_shim.cpp` : le backend ImGui DX12 compile ses shaders via
`D3DCompile`, et `d3dcompiler.lib` créerait un **import au chargement** sur
`D3DCOMPILER_47.dll` — que le jeu ne charge pas, donc `map --pe` échouerait
(tous les imports doivent être résidents avant le mapping). Comme `D3DCompile`
n'est pas `__declspec(dllimport)`, on fournit notre propre `D3DCompile` qui
résout la vraie implémentation à la première utilisation (chargement paresseux de
`d3dcompiler_XX.dll`). La table d'imports du module ne contient plus que des
modules déjà résidents dans le guest.

Le seul contrat partagé est `overlay/d3d12_overlay.h` (4 fonctions) ;
`dxgi_hook` est un détail d'implémentation caché derrière `dxgi_install()`.

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
2. soit ouvrir `src/Specter.Internal/Specter.sln` (Visual Studio, **x64**),
   configurer `Release|x64`, compiler ; soit, sur Linux, `tools/build-dll.sh` ;
3. sortie : `generated/bin/Release/Specter.Internal.dll`.

### `tools/build-dll.sh` (cross-build Linux)

Compile avec `clang-cl` + le CRT/MSVC et le SDK Windows récupérés par `xwin`,
sans Visual Studio. Le build est **incrémental** et éclate le code stable en
bibliothèques statiques mises en cache :

| Cache | Contenu | Reconstruction |
|---|---|---|
| `generated/build/specter_sdk.lib` | SDK généré (`helpers`, `il2cpp-init`, PCH) | seulement si le SDK change |
| `generated/build/specter_imgui.lib` | ImGui + backends | seulement si `third_party/imgui` change |
| `generated/build/obj/*.obj` | un objet par TU | si la source, un header suivi ou le PCH est plus récent |

Travailler sous `src/Specter.Internal/` ne reconstruit donc **ni** le SDK généré
**ni** ImGui : seuls les TUs modifiés sont recompilés, puis reliés aux deux
`.lib`. `tools/build-dll.sh --clean` vide le cache.

L'injection de la DLL et les hooks relèvent de l'expérimentation locale
uniquement (process possédé, hors ligne).
