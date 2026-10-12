# Journal (jalons)

## 2026-10-12 (suite) — Resolution de l'API IL2CPP (fini, sans motif scanning)

Investigations sur le vrai `GameAssembly.dll` (IDA via mcpwn, `.i64` cree a la
main dans `generated/input/`), resultat qui change la strategie prevue :

- Le jeu **n'a pas supprime** l'API il2cpp : il a **renomme** toute la surface
  d'export — 118 noms `mono_*` (couche de compat Mono du VM) + 245 noms
  obfusques `i...` — et retire les strings de symboles `il2cpp_*`.
- L'API est donc atteignable par `GetProcAddress` sur les noms `mono_*`,
  **sans scan de motifs** (qui reste le plan B pour une fonction non exportee).
- Verification corp a corp (decompilation IDA + cross-check offsets SDK) de
  chaque fonction : `mono_string_length` = `Il2CppString.length`(+16),
  `mono_string_chars` = @+20, `mono_image_get_name` = `name`(+0),
  `mono_image_get_assembly` = @+16, `mono_method_get_name` = @+24,
  `mono_method_get_class` = @+32 (MethodInfo).
- Pieges identifies : clusters d'alias vers des **stubs inertes**
  (`mono_field_set_value` corps vide, `mono_array_length` = `return 0` — a ne
  jamais appeler) ; `mono_class_get_flags` lit un champ a +88 ambigu ; et
  **Unity 2023.2 a refactorise `Il2CppClass`** (name/methods dans un bloc
  opaque a class+80, layout SDK != layout runtime) -> on ne parcourt jamais
  les champs de classe directement, on passe par les accesseurs verifies.

Code livre dans ce commit :

- `il2cpp-api.{h,cpp}` : tableau de 20 fonctions resolues par nom, toutes
  verifiees ; `api::resolve()` installe depuis `GameAssembly.dll`, log du
  compte + des noms manquants ; `api::ready()`.
- `runtime::initialize()` appelle `api::resolve()`.
- `runtime::self_check()` — premiere fonctionnalite : round-trip string
  managée, enumeration des assemblies du root domain, introspection de la
  classe `AppFacade` (TypeInfo statique, RVA du dump) + 3 premieres methodes.
- `specter::start()` branche `self_check()`.
- Docs : `ARCHITECTURE.md` (section contrainte + resolution + composants),
  `LOG.md`.
- Build : `tools/build-dll.sh` compile `il2cpp-api.cpp` ; DLL OK
  (`generated/bin/Release/Specter.Internal.dll`).

A valider en jeu (prochaine session) : `cd ~/Projects/Specter && tools/specter-up.sh`,
le tap doit montrer, apres `runtime: GameAssembly.dll mapped` :

    api: resolved 20 VM functions from GameAssembly.dll exports
    self_check: root domain ...
    self_check: string_new -> len=... first=U+....
    self_check: 2 assemblies (first: mscorlib, ...)
    self_check: class=...AppFacade methods=... fields=... image=...
    self_check:   method[0]=...

En cas d'echec : verifier la resolution (`ready()`), ne **pas** lire les champs
d'`Il2CppClass` en dur, et suivre la procedure d'ajout de `il2cpp-api.h`.

---

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
