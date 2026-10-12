# Journal (jalons)

## 2026-10-12 — Premiere injection reelle en jeu (Aniimo, appid 4126040)

Lancement depuis Steam (GE-Proton11-7-hostch), jeu joue 1h18 avec la DLL
injectee. Tap Linux :

    [specter] runtime: GameAssembly.dll mapped
    [specter] attached

Ce que cette session valide bout en bout :

- wine-hostch `map --pe Specter.Internal.dll --dllmain --hide-system` marche
  dans le vrai jeu (client hote + ntdll patche + RVA hostch).
- Le spawn de thread cache fonctionne : tout le flux de log vient du worker
  cree par `nt::spawn_hidden` -> HostchSpawnThread (is_system cote serveur),
  jamais de CreateThread visible.
- La pipe Z:\tmp\specter.pipe est un transport log propre : visible Linux,
  aucune trace dans le prefixe du jeu, pendant 1h18 sans crash ni reaction
  de NEP.
- `runtime::initialize()` detecte GameAssembly.dll mappe (GetModuleHandleW).

Reste a faire (prochain jalon) :
- Motif scanning dans `runtime::initialize()` : GameAssembly.dll n'exporte
  AUCUN `il2cpp_*` (il2cpp-api-functions.h vide) -> resolution des fonctions
  API par signatures (prologues) avant de pouvoir appeler l'API.
