# Shinoko-Aniimo.dll — RE d'un mod tiers (menu Aniimo)

Reverse-engineering **complet** du mod tiers **Shinoko** (`Shinoko-Aniimo.dll`,
v0.1.0) pour *Aniimo* 1.0.3535596.0 — base IDA entièrement annotée + logique Lua
déchiffrée. Sert de **référence** pour Specter (mêmes Lua-API de jeu, mêmes
familles de features).

## Provenance

| | |
|---|---|
| Artefact | `Shinoko-Aniimo.dll` (PE64 AMD64, overlay ImGui 1.92.4 / D3D11) |
| Jeu cible | Aniimo 1.0.3535596.0 (DirectX 11, **non-Steam**) |
| Mod | Shinoko v0.1.0 ("Launch with DirectX 11") |
| MD5 | `f48bfb09debe87275b6bd307ef525535` |
| SHA-256 | `964623462dcb872341375851428c2030b3005e7365ac74b037f6bd0d7b63c47e` |
| Image base | `0x180000000` — 1728 fonctions, 9 segments |

> Fichier d'origine : `~/Downloads/Global/Shinoko-Aniimo.dll[.i64]` (jamais modifié).
> La copie de travail ci-dessous a été annotée puis sauvegardée.

## Arborescence

```
reference/shinoko/
├── README.md                  ce fichier
├── REPORT.md                  rapport d'analyse complet (archi, features, offsets)
├── lua/                       93 fragments Lua déchiffrés (briques) — voir `lua/README.md` + `lua/assembled/` (scripts reconstitués)
├── maps/                      tables texte produites pendant l'analyse
│   ├── strings.txt / functions.txt / func_strings.txt / func_index.txt
│   ├── final_names.txt          toutes les fonctions renommées dans l'IDB
│   ├── label_global.txt         libellé UI -> globale de config
│   ├── enqueuers.txt            qui enfile quel script Lua
│   ├── decryptors.txt/2/3       inventaire des 93 déchiffreurs de chaînes
│   ├── decoded_summary.txt/2    résumé des chaînes déchiffrées
│   ├── decoded_lua_bundle.txt   les 93 scripts concaténés en un seul fichier
│   └── strings.txt              toutes les chaînes
├── pseudocode/                pseudocode Hex-Rays (lisable sans IDA)
│   ├── decomp/ (166)  core/ (30)  ui/ (19)
│   └── decrypt_e2d0.c / decrypt_d580.c   le déchiffreur de chaînes
├── binary/                    [NON versionné] Shinoko-Aniimo.dll + .i64 annoté
└── assemble_scripts.py         générateur des scripts reconstitués (`lua/assembled/`)
```

## Résumé des découvertes

* **Pont Lua** : le mod ne patche quasi pas la mémoire du jeu ; il capture l'état
  xLua (`xluaL_loadbuffer`) et fait exécuter, à chaque `GameManager::CommonUpdate`,
  des scripts Lua qu'il a lui-même assemblés → toutes les features sont du Lua
  appelant l'API du jeu (`pg`, `Utils.checkRelation`, `entityMgr`,
  `ActorCombatAttribute`, `CombatActionTool`, `Common.ClientSwitch`, `GmToolUtils`).
* **Obfuscation de chaînes cassée** : table de substitution 512 o + LCG seedé ;
  les **93 chaînes** (= scripts Lua + noms d'API) sont déchiffrées dans `lua/`.
* **Modules** : Player(100), ESP(90), Misc(80), GM(70), Lua Executor(60) —
  registre `std::vector<ModuleEntry>`.
* **Features** : Kill/Catch Aura, One Hit, Multi-Hit, No Cooldown, Inf
  Stamina/Energy, Auto Loot, Dumb Enemy, No Fall Damage, Mob Vacuum, Rate-Limit
  Bypass, Global Speed/FOV, Free Cam, model scale, tips UI custom, ESP, GM Tools,
  éditeur Lua.

Détails (offsets, globales de config, schéma de déchiffrement) → [`REPORT.md`](REPORT.md).

## Ouvrir la base annotée

1. `binary/` n'est pas versionné : récupère la copie de travail (ou refais une
   copie de l'original dans `~/Downloads/Global/`).
2. Ouvrir `reference/shinoko/binary/Shinoko-Aniimo.dll.i64` dans **IDA**
   (image base conservée `0x180000000`).
3. Les noms annotés (`Apply*`, `Hooked_*`, `*Module_Render`, `LuaStr_*`, `g_*`),
   les 2 structs (`ModuleEntry`, `FeatureItem`) et les commentaires y sont persistés.

> `functions.txt` figeait l'état **avant** renommage ; `final_names.txt` reflète
> l'état **après** (`sub_*` → noms parlants).
