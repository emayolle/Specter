# Specter — DLL interne IL2CPP (cible : Aniimo)

Projet **Specter** : reverse engineering du jeu Unity **IL2CPP** *Aniimo*
(FunPlus / WorldX) et production du scaffold d'une **DLL interne** injectée dans
le jeu, via **Il2CppInspectorRedux**.

> Une seule cible : `Specter.Internal.dll`. Pas de lecteur externe.

## Cible

| | |
|---|---|
| Jeu | Aniimo (installé via Steam) |
| Chemin | `~/.local/share/Steam/steamapps/common/Aniimo/` |
| Moteur | Unity **2022.3.62f1**, backend **IL2CPP** |
| Binaire | `GameAssembly.dll` — PE32+, x64, ~115 Mo |
| Metadata | `Aniimo_Data/il2cpp_data/Metadata/global-metadata.dat` (~28,9 Mo) |
| Version metadata | **31** (le header en clair affiche une version bidon = taille du fichier) |
| Protection | **NetEase Protect 2** (`NEP2.dll`, `NEPKernel.sys`) → metadata **chiffrée** (entropie ~7,93) |

## Point clé

`global-metadata.dat` est **chiffrée** (seul le magic Unity `FAB11BAF` reste en
clair). Il2CppInspectorRedux ne peut pas la lire telle quelle — il faut d'abord
la déchiffrer.

La protection (NEProtect2) est contournée avec le déchiffreur public
[`YuroGod/metadata_decrypt`](https://github.com/YuroGod/metadata_decrypt) (schéma
validé sur AFK Journey), avec une correction : le script écrit une version
metadata `29`, or Aniimo est en **v31** (les `Il2CppMethodDefinition` font 36
octets, pas 32). `tools/dump.sh` corrige ça automatiquement.

## Arborescence

```
Specter/
├── tools/                       # pipeline RE (Python + bash) — versionné
│   ├── metadata_decrypt.py        déchiffreur NEProtect2
│   ├── dump.sh                    pipeline complet (déchiffre + dump)
│   ├── specter-tap.sh             affiche les logs de la DLL (pipe vers Linux)
│   └── Il2CppInspector            binaire linux-x64 (non versionné, ~80 Mo)
├── src/                         # LE PRODUIT — versionné
│   └── Specter.Internal/          la DLL interne (module profond)
│       ├── entry.cpp              DllMain + LOG_FILE (point d'entrée ; aucun thread)
│       ├── specter.{h,cpp}        interface : start() / stop()
│       ├── runtime.{h,cpp}        seam IL2CPP (localise + résout l'API)
│       ├── log.{h,cpp}            journalisation (pipe hôte / fichier)
│       └── Specter.sln / .vcxproj projet Visual Studio (x64)
├── generated/                   # reproduit par tools/dump.sh — NON versionné
│   ├── sdk/appdata/               SDK C++ (types, offsets de méthodes, TypeInfo)
│   ├── sdk/framework/             scaffold d'injection (dllmain, init, helpers, pch)
│   ├── dump/                      dump.cs, il2cpp.py (IDA), metadata.json
│   ├── shims/                     assemblies .NET (ILSpy/dnSpy)
│   ├── input/                     liens vers le jeu + metadata déchiffrée (v31)
│   └── bin/                       sortie de compilation de la DLL
├── docs/ARCHITECTURE.md         # design (seams, modules, limites)
└── README.md
```

Les deux dossiers qui comptent : **`generated/`** = entrée régénérable qu'on
n'édite jamais, **`src/`** = ce qu'on écrit. Détails dans
[`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md).

## Régénérer le SDK

```bash
tools/dump.sh                 # déchiffre + corrige la version + dump complet
GAME_DIR=/autre/chemin/Aniimo tools/dump.sh
```

Produit `generated/sdk/appdata/` (`il2cpp-types.h` 114 Mo,
`il2cpp-functions.h` 450 k lignes, …), `generated/dump/` et `generated/shims/`.

## Compiler la DLL interne

Deux chemins, **même sortie** : `generated/bin/Release/Specter.Internal.dll`
(Release | x64, CRT **statique** `/MT`).

### A. Windows / Visual Studio (MSVC)

1. `tools/dump.sh` (crée `generated/`, indispensable avant de compiler) ;
2. ouvrir `src/Specter.Internal/Specter.sln` dans **Visual Studio**, viser
   **Release | x64**, compiler ;
3. sortie : `generated/bin/Release/Specter.Internal.dll`.

### B. Linux, sans Windows (clang-cl + xwin)

Cross-compile avec l'**ABI MSVC** : `clang-cl` + les en-têtes/bibliothèques du
CRT MSVC et du SDK Windows récupérés une fois par
[`xwin`](https://github.com/Jake-Shadle/xwin).

```bash
# une seule fois : CRT + SDK Windows (~640 Mo) dans ~/.xwin
xwin --accept-license --arch x86_64 splat --output ~/.xwin

# à chaque build
tools/dump.sh          # si generated/ est absent
tools/build-dll.sh     # -> generated/bin/Release/Specter.Internal.dll
```

Le script reproduit le projet MSVC (mêmes defines, PCH `pch-il2cpp.h`) et lie en
`/MT`. Imports attendus du binaire : `KERNEL32.dll`, `USER32.dll` uniquement.

Écris ton code dans `src/Specter.Internal/` : le point d'entrée est
`specter::start()` (`specter.cpp`). Toutes les méthodes du jeu sont accessibles
par offset image via `generated/sdk/appdata/il2cpp-functions.h`.

## Injecter (wine-hostch)

Le DLL est **manual-mappé** (zéro PEB/Ldr) et son `DllMain` s'exécute sur un
thread **caché** (`is_system`), via [`wine-hostch`](../wine-hostch) :

```
hostch.py map --pe generated/bin/Release/Specter.Internal.dll --dllmain --hide-system
```

**Règle : ne jamais appeler `CreateThread` depuis la DLL.** Un tel thread serait
**visible** et son adresse de départ tomberait dans la mémoire manual-mappée —
signal d'anti-cheat classique. Le `framework/dllmain.cpp` généré (qui fait un
`CreateThread`) n'est donc **pas compilé** : on fournit notre propre `DllMain`
dans `entry.cpp`, qui ne fait que lancer la mise en route sur un thread caché
(`nt::spawn_hidden()`) et rendre la main.

Pour un worker persistant (boucle, hooks), on utilise `nt::spawn_hidden()`
(`src/Specter.Internal/nt.cpp`) : il appelle l'entrée dédiée non exportée
`HostchSpawnThread` du fork (`wine-hostch/patches/hostch-spawnthread.patch`), qui
crée un thread **caché** (`is_system`). La RVA de cette entrée est bakée par
`wine-hostch/emit-hostch-rva.sh` dans `src/Specter.Internal/hostch-rva.h` (à
régénérer après chaque rebuild du fork). Détails :
[`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md), « Injection, threads et discrétion ».

## Logs (pipe vers Linux)

Les logs de la DLL sortent par un **pipe** vers l'hôte Linux, sans écrire de
fichier dans le préfixe du jeu. Sous Wine/Proton le disque `Z:` pointe vers la
racine Linux, donc la DLL écrit dans une FIFO :

| | |
|---|---|
| Côté Windows (DLL) | `Z:\tmp\specter.pipe` |
| Côté Linux (hôte) | `/tmp/specter.pipe` |

Lance l'écouteur **avant** de charger la DLL :

```bash
tools/specter-tap.sh                 # affiche les logs sur stdout
tools/specter-tap.sh specter.log     # affiche ET enregistre
```

Si la FIFO est absente, `log::init()` retombe automatiquement sur un fichier
(`il2cppi_log_write`). Sur le chemin `pipe` aucune trace disque n'est laissée
dans le préfixe — seulement un handle. Chemin du pipe surchargeable via la
variable Windows `SPECTER_PIPE`.

## Explorer

* **IDA** : `File > Script file…` → `generated/dump/il2cpp.py` (garder
  `generated/sdk/appdata/il2cpp-types.h` et `generated/dump/metadata.json` à
  côté). Lancer le script **juste après** le chargement du binaire.
* **C#** : `generated/dump/dump.cs` (27 Mo) se lit/`grep` directement.
* **Assemblies** : `generated/shims/*.dll` dans ILSpy/dnSpy.

## Limites / à savoir

* **Aucun export `il2cpp_*`** dans `GameAssembly.dll` (390 exports, 0 en
  `il2cpp_`) : NetEase les a retirés. `generated/sdk/appdata/il2cpp-api-functions.h`
  est donc vide et les appels type `il2cpp_thread_attach()` ne se résolvent pas
  par nom. Toute la résolution est isolée dans `src/Specter.Internal/runtime.cpp`
  (scan de motifs à implémenter). Les offsets de méthodes, eux, sont présents.
* Le déchiffreur `metadata_decrypt.py` est **spécifique NEProtect2/AFK Journey** :
  il fonctionne ici mais pourrait casser à une maj du jeu.
* La metadata déchiffrée est une **copie locale** : ne remplace jamais l'original
  dans le jeu. Le pipeline lit toujours l'original.

## Outil utilisé

* [Il2CppInspectorRedux](https://github.com/LukeFZ/Il2CppInspectorRedux) `2026.2`
  — commit `335c3797`
  (build `dotnet publish Il2CppInspector.CLI -c Release -r linux-x64 --self-contained`).
* Version Unity auto-détectée pour les en-têtes API : `2023.2.0+`
  (types `2022.3.33+`), cohérente avec la metadata v31.

> Résultat du run : `CodeRegistration @ 0x184E73630`,
> `MetadataRegistration @ 0x185921F40`, `196 460` définitions de méthodes,
> `23 698` `TypeInfo`.
