# Specter — SDK C++ IL2CPP (cible : Aniimo)

Projet **Specter** : reverse engineering du jeu Unity **IL2CPP** *Aniimo* (FunPlus / WorldX) —
déchiffrement de la metadata protégée et génération d'un **SDK C++** + `dump.cs`
+ script IDA + JSON, via **Il2CppInspectorRedux**.

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

`global-metadata.dat` est **chiffrée** (seul le magic Unity `FAB11BAF` reste en clair).
Il2CppInspectorRedux ne peut pas la lire telle quelle — il faut d'abord la déchiffrer.

La protection (NEProtect2) a été contournée avec le déchiffreur public
[`YuroGod/metadata_decrypt`](https://github.com/YuroGod/metadata_decrypt) (schéma validé sur AFK Journey).
Il fonctionne ici **tel quel**, avec une correction : le script écrit une version metadata `29`,
or Aniimo est en **v31** (les enregistrements `Il2CppMethodDefinition` font 36 octets, pas 32).

## Contenu du projet

```
Specter/
├── input/
│   ├── GameAssembly.dll                 -> lien vers le jeu
│   ├── global-metadata.encrypted.dat    -> lien vers le jeu (chiffré)
│   └── global-metadata.decrypted.dat    -> metadata déchiffrée, version=31
├── tools/
│   ├── Il2CppInspector                  -> Il2CppInspectorRedux 2026.2 (binaire linux-x64)
│   ├── metadata_decrypt.py              -> déchiffreur NEProtect2
│   └── dump.sh                          -> pipeline complet (déchiffre + dump)
├── cpp/                                 -> *** LE SDK C++ ***
│   ├── appdata/
│   │   ├── il2cpp-types.h               -> types IL2CPP + types du jeu (vraies classes/structs)
│   │   ├── il2cpp-functions.h           -> signature + offset de CHAQUE méthode (450 k lignes)
│   │   ├── il2cpp-types-ptr.h           -> offset de chaque Il2CppClass* (TypeInfo)
│   │   ├── il2cpp-api-functions*.h      -> API il2cpp_* (VIDE — voir Limites)
│   │   └── il2cpp-metadata-version.h
│   ├── framework/                       -> boilerplate injection DLL (init, helpers, pch)
│   ├── user/main.cpp                    -> point d'entrée Run() de ton code injecté
│   └── IL2CppDLL.sln / .vcxproj         -> projet Visual Studio (DLL injection)
├── dump/
│   ├── dump.cs                          -> 27 Mo : toutes les classes/méthodes C# (TypeDefIndex)
│   ├── il2cpp.py                        -> script IDA (nécessite cpp/appdata/il2cpp-types.h)
│   └── metadata.json                    -> 282 Mo : adresses de méthodes, typeInfo, strings…
├── dll/                                 -> assemblies .NET "shim" (pour ILSpy/dnSpy, 53 Mo)
└── README.md
```

## Regénérer

```bash
tools/dump.sh                 # déchiffre + corrige la version + dump complet (~1 min)
GAME_DIR=/autre/chemin/Aniimo tools/dump.sh
```

## Utilisation

* **SDK C++ / hook natif (Windows)** : ouvre `cpp/IL2CppDLL.sln` dans Visual
  Studio, écris ton code dans `cpp/user/main.cpp` (`Run()`), compile en DLL, injecte
  (Cheat Engine / injecteur DLL) dans `Aniimo.exe`. Toutes les métodes sont
  accessibles par offset image (`cpp/appdata/il2cpp-functions.h`).
  Pour clang/GCC (cross-compile) : relancer avec `--cpp-compiler GCC`.
* **Analyse dans IDA** : `File > Script file…` → `dump/il2cpp.py`
  (garder `cpp/appdata/il2cpp-types.h` et `dump/metadata.json` à côté du script).
  Lance le script **juste après** le chargement du binaire.
* **Exploration** : `dump/dump.cs` se lit directement (cherche une classe/méthode).
  `dll/*.dll` s'ouvrent dans ILSpy/dnSpy.

## Limites / à savoir

* **Aucun export `il2cpp_*`** dans `GameAssembly.dll` (390 exports, 0 en `il2cpp_`) :
  NetEase les a retirés. Conséquence : `appdata/il2cpp-api-functions.h` est vide et
  les appels type `il2cpp_thread_attach()` / `il2cpp_object_new()` du template
  `main.cpp` **ne se résoudront pas par nom**. Les pointeurs de méthodes du jeu, eux,
  sont bien présents par offset.
  → Pour retrouver les fonctions de l'API il2cpp, il faut scanner les motifs
  (les fonctions existent en interne, non exportées) ou passer par tes propres wrappers.
* Le déchiffreur `metadata_decrypt.py` est **spécifique NEProtect2/AFK Journey** : il
  fonctionne ici mais pourrait casser à une maj du jeu (clés/schéma réinitialisés).
* La metadata déchiffrée est une **modif locale** : ne la remplace pas dans le jeu.
  Le pipeline lit toujours l'original.

## Outil utilisé

* [Il2CppInspectorRedux](https://github.com/LukeFZ/Il2CppInspectorRedux) `2026.2` — commit `335c3797`
  (build `dotnet publish Il2CppInspector.CLI -c Release -r linux-x64 --self-contained`)
* Version Unity auto-détectée pour les en-têtes API : `2023.2.0+` (types `2022.3.33+`),
  cohérente avec la metadata v31.

> Résultat du run : `CodeRegistration @ 0x184E73630`, `MetadataRegistration @ 0x185921F40`,
> `196 460` définitions de méthodes, `23 698` `TypeInfo`.
