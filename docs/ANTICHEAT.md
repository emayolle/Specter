# Aniimo / NetEase Protect (NEP2) — anatomie de l'anti-cheat

Analyse statique locale (2026-10-12) des artefacts du depot Steam
`~/.local/share/Steam/steamapps/common/Aniimo/`. Objectif : savoir
**concrètement** ce que l'anti-cheat fait dans NOTRE environnement
(Proton/Wine + Specter), pas croire les rumeurs.

## Inventaire des composants

| Artefact | Taille | Rôle |
|---|---|---|
| `NEP2.dll` (racine) | 39,5 Mo | **Host anti-cheat usermode** chargé par `Aniimo.exe` (l'importe par ordinal 1). 1 seul export : `NEP_Unknown` |
| `NEPKernel.sys` | 3,97 Mo | **Pilote kernel Ring-0** (minifilter FLTMGR + payload packé `.upx0`). Sur disque ET embarqué dans `.rsrc` de NEP2.dll — md5 identiques (`92c356f2...`) |
| `NEPCleaner.exe` | 216 Ko | Désinstalleur (DeleteService / RegDeleteTreeW) — révèle qu'un service est normalement créé |
| `KernelDumpAnalyzer.exe` | — | Analyse de dumps kernel |
| `md5list.txt` | 2,6 Mo | Manifeste d'intégrité : 21 914 fichiers (`md5,taille,chemin`) |
| `CrashSightLog/`, `wesight/`, `CrashSight64.dll` | — | Crash-reporting NetEase (Wetest) — PAS de l'AC |
| `Aniimo_Data/Plugins/x86_64/*` | — | SDK acteurs : AkUnitySound, avcodec, FPX/FPXGame, GMESDK, PixVideo, pxauth… |

Le payload `.rsrc` de NEP2.dll (26 Mo) est en fait **presque entièrement de
l'infrastructure de crash** : 4× `dbghelp`/WER analyzer (ids 105-109),
`necrashpad_*` (NetEase Crashpad, id 115), uploader WINHTTP (id 116), petit
helper (DWM, id 119). **Le seul composant AC embarqué est le DRIVER
(id 103 = NEPKernel.sys).**

## Ce que prouve `NEP2.dll` par ses imports (vérité terrain)

- **Processus/modules** : Toolhelp (`Process32First/Next`), PSAPI
  (`K32EnumProcesses`, `K32GetModuleInformation`, `K32GetModuleFileNameEx`),
  `K32QueryWorkingSetEx` (scan des pages du working set).
- **Threads** : `SuspendThread`/`ResumeThread`/`GetThreadContext`/
  `SetThreadContext`/`CreateThread` — il peut suspendre les threads du jeu et
  inspecter/poser leurs contextes.
- **Anti-debug** : `IsDebuggerPresent` (+ probable résolution dynamique de
  `NtQueryInformationProcess` — 6 imports `ntdll` seulement en dur).
- **Signatures** : `WinVerifyTrust` (WINTRUST) — vérifie la signature des
  modules.
- **ETW** : `tdh.dll` (TdhGet*EventInformation) — consomme les providers ETW
  du kernel (process/thread/image/registry) sous Windows.
- **Fichiers** : `ReadDirectoryChangesW` (surveille les changements dans les
  dossiers), + hachage disque via `bcrypt` (cf. `md5list.txt`).
- **Réseau → module** : `GetOwnerModuleFromTcpEntry` (qui possède chaque
  socket TCP), `WS2_32` (38 fns) pour la télémétrie.
- **Matériel** : `SetupDi*` (SetupAPI) — inventaire du device tree
  (caméra, GPU, disques…) = empreinte matérielle.
- **Privilège** : `AdjustTokenPrivileges` → SeDebugPrivilege (ouvrir/scanner
  d'autres processus).
- **Registre** : `RegOpenKeyEx/Enum/Query` (historique, télémétrie).

Les symbols C++ **non strippés** exposent le design interne : namespace
`kernel::nep`, sérialisation **msgpack**, `com_call_helper::rpc_call` — un
**canal RPC driver→usermode** (tuples d'événements horodatés `K`). Sous Wine
ce canal est mort (pas de pilote).

## États observés dans le prefix Proton (compatdata/4126040)

- `HKCU\Software\Netease\NEP\normalUser = "qvTMdaKaw63rQ6fNQ7…"` — token
  d'identité écrit au 1er lancement.
- `drive_c/windows/NEPDriver.info` (13 octets, écrit au 1er lancement le
  2026-09-16) : `uint64 + uint32(0x527=1319)` — résultat de l'init driver.
- **Aucun service** dans `CurrentControlSet\Services` → **NEPKernel.sys
  n'est jamais installé sous Wine** (Wine ne sait pas charger un pilote
  kernel). Le minifilter et toutes les protections Ring-0 sont **dormants**
  dans notre environnement.

## `md5list.txt` est périmé

Tailles disque actuelles ≠ tailles listées (GameAssembly 115 180 928 vs
115 170 304 ; UnityPlayer 26 884 992 vs 26 874 368 ; NEP2 39 528 320 vs
40 866 296) et le chemin `worldx_Data/Plugins/x86_64/NEP2.dll` n'existe pas.
Le manifeste du depot ne correspond pas aux binaires livrés (depot mélangé /
manifeste d'une branche antérieure).

## Conséquences pour Specter — règles de stealth

| Vecteur NEP | Sous Wine | Notre posture |
|---|---|---|
| Pilote kernel (mémoire, minifilter) | **Absent** | N/A |
| Scan modules (Toolhelp/PSAPI) | Actif | Manual-map hostch : hors Ldr → invisible |
| Scan threads + contextes | Actif | Worker `is_system` (serveur) : aucune handle utilisateur |
| `WinVerifyTrust` | Actif | Aucun fichier de notre DLL dans le prefix → rien à vérifier |
| ETW kernel | Dégradé (pas de providers Wine) | invisible |
| TCP → module | Actif | Nous n'ouvrons aucun socket |
| Hachage disque (`md5list`) | Actif mais manifeste périmé | On ne touche JAMAIS aux fichiers du jeu |
| Working-set scan (pages exécutables hors modules) | Théorique | Risque résiduel faible (non observé sur 1h18) |
| Télémétrie réseau | Actif | Compte du joueur légitime ; ne pas exfiltrer |

**Hooks : O.K. sous Wine si** — patch mémoire **dans** les modules
légitimes du jeu (GameAssembly.dll : méthodes managées / MethodInfo
methodPointer swaps, VTables), trampolines dans notre propre mapping, worker
caché, log via pipe Linux, aucun objet nommé façon Windows (events/mutex),
aucun socket, aucun fichier dans le prefix.

**Sur Windows natif, tout change** : NEPKernel se charge (minifilter +
scan mémoire kernel + ETW réels). Ne pas y jouer avec Specter tel quel.

## Légende vs rumeurs (réponse à la synthèse "Google AI")

- ✅ Confirmé : pilote kernel Ring-0 nommé NEP (NEPKernel.sys), multi-couche
  (minifilter + usermode), blocage des injections DLL (mais par le kernel —
  absent sous Wine !).
- ⚠️ "Pas actif au 1er lancement, seulement au 2e" : sous Wine, il écrit
  `NEPDriver.info` dès le 1er run et le service n'apparaît JAMAIS. Sur
  Windows, NEP2 extrait le driver de ses ressources et l'installe (d'où
  l'effet "au tour suivant").
- ⚠️ "Scan des icônes du bureau" : non corroboré. L'inventaire SetupDi couvre
  le device tree (caméra incluse) — c'est de l'empreinte matérielle, pas du
  scan de fichiers usagers. Rumeur probable.