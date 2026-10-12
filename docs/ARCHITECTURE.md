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
consommé **tel quel** : c'est le point d'extension prévu par Il2CppInspector, et
il attend exactement deux symboles de notre côté — `Run()` et `LOG_FILE`
(fournis par `src/Specter.Internal/entry.cpp`). On ne duplique donc pas le
scaffold : on remplit le slot `user/` qu'il réserve, avec notre propre module.

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
| `main.h` | déclare `Run()` (nom exigé par `framework/dllmain.cpp`) | seam avec le scaffold |
| `entry.cpp` | définit `Run()` + `LOG_FILE`, délègue à `specter::start()` | adaptateur (fin, sans logique) |
| `specter.{h,cpp}` | l'interface du produit | module profond |
| `runtime.{h,cpp}` | localise `GameAssembly.dll`, résout l'API IL2CPP | seam interne |
| `log.{h,cpp}` | journalisation | adaptateur sur le helper du SDK |

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

generated/                 entrée — produite par dump.sh, jamais éditée
  sdk/appdata/               SDK C++ (types + offsets de méthodes)
  sdk/framework/             scaffold d'injection (dllmain, init, helpers, pch)
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
