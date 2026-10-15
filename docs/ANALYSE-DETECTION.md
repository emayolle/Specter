# Analyse de détection — 14 octobre 2026

> Analyse statique du dépôt `Specter`, du binaire produit, et des scripts Lua
> publiés du jeu. Aucun test en jeu n'a été mené pour cette analyse. Aucun
> reverse du client ni de l'anti-triche n'a été effectué : les b concerned ne
> sont pas présents dans le dépôt, et l'analyse s'est donc limitée à ce qui est
> vérifiable localement.

---

## 1. Le problème, posé proprement

Trois observations terrain, de nature différente :

| # | Observation | Ce qu'elle prouve / ne prouve pas |
|---|---|---|
| O1 | Versions **antérieures** (jusqu'à `2572297`, 13 oct. 11:04) : usage prolongé, **aucun flag** | Ces versions n'universalitaient pas le vecteur — ou pas avec la même intensité |
| O2 | Versions **récentes** : avertissement à ~30 min | Le déclencheur est apparu **entre les deux** |
| O3 | Compte neuf + build actuel **désarmé** (aucune feature, aucun Lua) : avertissement quand même | **Le vecteur n'est pas la Lua exécutée** — ou alors l'injection seule suffit |

O3 est contre-intuitive : elle semble contredire O1. La question est donc
précisément : **qu'est-ce qui diffère entre `2572297` et le build actuel ?**

---

## 2. Méthode

Élimination par couches, du plus large au plus étroit :

1. Ce que **notre code** envoie sur le réseau → lecture des imports du binaire.
2. Ce que **le jeu** fait de son état Lua → balayage des scripts publiés.
3. Ce qui **change** entre les deux builds → diff complet de l'arborescence.

---

## 3. Résultat 1 — notre code n'envoie rien

Lecture des imports de `Specter.Internal.dll` produit par `tools/build-dll.sh` :

```
dxgi.dll   IMM32.dll   KERNEL32.dll   SHELL32.dll   USER32.dll
```

Aucun import réseau : ni `ws2_32`, ni `winhttp`, ni `wininet`, ni
`socket`/`send`/`connect`. Le binaire n'a **aucun moyen** d'émettre de trafic
vers un serveur.

Conséquence : ce que le serveur reçoit est du **trafic de jeu normal**. Toute
détection de ce côté est donc **comportementale** (facteur 3 de
`DETECTION.md`), pas liée à une émission de notre part.

---

## 4. Résultat 2 — aucune détection dans les scripts Lua du jeu

Corpus : `/home/cozlex/Downloads/ScriptAniimo/source/xfs/luascripts` —
**8 541 fichiers `.lua`, 320 Mo**. Recherche exhaustive sur les angles
pertinents pour détecter une环境污染 d'environnement Lua :

| Recherche | Résultat |
|---|---|
| `pairs(_G)`, `pairs(_ENV)`, `next(_G` | **2 fichiers** : `Core/Common/lume.lua:1490` (lib de sérialisation) et `Lib/luaunit.lua:2337` (tests unitaires) — deux outils de dev |
| `debug.getregistry` | **aucune occurrence** |
| `debug.sethook` / `getinfo` / `getlocal` / `setupvalue` | profilage, logging, et l'outil de hot-reload `Core/Framework/Reload.lua` |
| `scripthash` / `verifyscript` / `checkscript` | **aucune occurrence** |
| `anticheat`, `integrity`, `tamper`, `ischeat` | **aucune occurrence** |
| Fichiers nommés `*cheat*` / `*security*` / `*detect*` | uniquement de l'**IA de jeu** (`BC_*_Security_Patrol`, `*_Guard_AlertCheck`) — sans rapport |
| `io.popen`, `os.execute` | outils de debug Behaviac et profilers |

Emploi de `md5` (le seul candidat « hash ») :

- `Common/ServerErrorReporter.lua` — déduplication de rapports d'erreur, envoi de
  stack traces vers `http://10.8.45.67:8080/…` (**IP privée de dev**, 10.x) ;
- `Common/Utils/Utils.lua:6778` — hash de **version de graphe de scène** ;
- `Core/Common/RpcIndex.lua`, `Guis/Utils/AvatarShareService.lua` — caches.

**Jamais pour hasher les scripts ou l'environnement Lua.**

### Un fichier révélateur : `Core/Framework/Global.lua`

Le jeu maintient une liste blanche de ses propres globals :

```lua
local function __innerDeclareIndex(tbl, key)
    if not _GlobalNames[key] then
        error("Attempt to access an undeclared global variable : " .. key)
```

C'est une protection contre les **fuites de variables dans son propre code** :
l'erreur ne se déclenche que sur un accès *du code du jeu* à un global non
déclaré. **La présence d'une clé étrangère dans `_G` ne déclenche rien ici.**

---

## 5. Résultat 3 — le delta fonctionnel est **intégralement** côté Lua

Diff complet entre `2572297` et `HEAD`, fichier par fichier.

### 5.1 La couche C++ est fonctionnellement identique

| Fichier | Diff hors includes/namespaces |
|---|---|
| `entry.cpp` → `app/entry.cpp` | **rien** |
| `nt.cpp` → `platform/nt.cpp` | **rien** |
| `log.cpp` → `platform/log.cpp` | **rien** |
| `detour.cpp` → `platform/hook/detour.cpp` | **rien** |
| `dxgi_hook.cpp` → `render/dxgi_hook.cpp` | **rien** (namespace `overlay` → `dxgi`) |
| `game_input.cpp` → `render/input.cpp` | **rien** (namespace `overlay::game_input` → `input`) |
| `specter.cpp` → `app/specter.cpp` | **3 appels ajoutés** (voir 5.3), + 1 renommage de symbole |

Les seuls écarts sont des chemins d'include, des renommages de namespace
(`specter::overlay` → `specter::dxgi` / `specter::render` / `specter::input` /
`specter::hook`) et `overlay::overlay_worker` → `dxgi::overlay_worker`.

**Les hooks sont donc rigoureusement les mêmes** : detour inline
`LuaManager.CommonUpdate`, vtables DXGI (Present/Present1/ResizeBuffers/
ResizeBuffers1/Execute), 7 hooks `user32` (GetRawInputData,
GetRawInputBuffer, GetAsyncKeyState, GetKeyState, ClipCursor, ShowCursor,
SetCursor), manual-map, thread caché.

Puisque O1 montre que ces hooks-là ne déclenchaient rien, **ils ne sont pas le
vecteur.**

### 5.2 La couche Lua est le seul changement réel

| | ancien | actuel |
|---|---|---|
| `lua_console.cpp` | 796 lignes | **1280 lignes** (+502 lignes de diff) |
| `specter_init.lua` | inexistant | **8 010 octets** |
| `lua/native.cpp` | inexistant | pont LuaBridge |
| `lua/bridge.cpp`, `lua/api.cpp`, `lua/thunks.cpp` | inexistants | **142 thunks** |

### 5.3 Trois appels de démarrage ajoutés (`app/specter.cpp`)

```cpp
if (!lua::install()) { … }          // bind C API + detour CommonUpdate
if (!lua::install_native()) { … }   // ENREGISTRE un state hook  -> native::publish
features::cheats::install();        // ENREGISTRE un state hook  -> cheats::publish_all
```

Les deux derniers enregistrent des **hooks d'état permanents** qui s'exécutent à
**chaque nouveau `lua_State`**.

---

## 6. Ce que le build écrit dans l'état Lua du jeu

Réécrit le 15 octobre : l'ancienne version de cette section décrivait un build
qui n'existe plus. Inventaire exact du build courant, tout trouvé dans **notre**
code :

| Écriture | Emplacement | Nécessaire ? |
|---|---|---|
| `registry[<clé dérivée>] = <env>` | `lua/pump.cpp` `run()` | **oui** — c'est l'ancre GC du bac à sable |
| `<env>[0x53505254] = <store>` | `lua/pump.cpp` `build_specter()` | oui — le store doit être celui que l'env referme |
| `ActorCombatAttribute.changeStamina` (**classe**, pas instance) | chunk `kEnable` | oui — la stamina |
| rien du tout dans `_G` | — | — |

Mesuré en jeu le 15 octobre :

```
E1  un global du jeu pointe sur nous ?        NON
E2  un global du jeu voit notre store ?       NON
E3  le registre contient notre env ?          OUI — clé 1436213885
E4  notre env est un global ?                 false
```

### Ce que ça coûte, en une phrase

**Une promenade dans le registre suffit à nous trouver.** Six lignes de Lua :

```lua
local reg = debug.getregistry()
for k, v in pairs(reg) do
  if type(v) == 'table' and rawget(v, '__global') then
    -- c'est notre bac à sable
  end
end
```

La clé est un entier **dérivé de l'état**, pas une constante nommée : on ne signe
pas notre travail. Mais un entier dans un registre se remarque aussi
aisément qu'un nom, et le registre a 13 277 entrées ici — dont 497 chaînes du
genre `FunPlus.WorldX.*` : on s'y perdrait presque.

### Ce qu'on ne fait pas, délibérément

Nova (GMod) ancre son `genv` de la même façon, et **le cache** : il installe un
hook sur `debug.getregistry` (`EnsureHookAPI`) pour que la promenade ci-dessus ne
trouve rien.

On ne fait pas ça. Cacher sa présence d'une inspection est de la **dissimulation**,
pas de l'isolation — et ça ne servirait de toute façon qu'à Lua : le module mappé,
les sept crochets `user32` et le détour `dxgi` ne changent pas. Un hook posé sur
une bibliothèque du jeu serait en outre **plus** visible que la table qu'on cherche
à masquer.

Si ce document sert à décider quoi que ce soit, la décision à prendre n'est donc
pas « masquer mieux » mais « est-ce que l'ancre vaut ce qu'elle coûte ».

### Le patch de stamina est, lui, bien plus lisible

`ActorCombatAttribute.changeStamina` est remplacé sur la **classe**. Tout script
qui fait :

```lua
local e = pg.me
print(getmetatable(e.actorCombatAttribute).changeStamina == e.actorCombatAttribute.changeStamina)
```

voit `false` et sait qu'il y a un patch. C'est sans doute l'empreinte Lua la plus
directe du build — et elle est **nécessaire** : sans patch, pas de stamina infinie.

## 7. Hypothèses classées

**H0 — Notre propre ancre dans le registre est un vecteur, et nous l'avons
ajoutée nous-mêmes.** *(nouveau, 15 octobre)*
*Preuves :* mesuré en jeu — `debug.getregistry()` rend notre environnement, clé
1436213885. Six lignes de Lua suffisent (§6). La clé est un entier dérivé de
l'état, donc non signé, mais un entier foreign dans 13 277 entrées reste
remarquable.
*Statut :* **accepté en connaissance de cause.** L'ancre est ce qui fait tenir
une variable entre deux Execute ; sans elle, le store meurt à chaque run.
L'alternative — un store sur fichier — donne la même persistance **sans rien
écrire dans l'état Lua**. Elle n'a pas été retenue parce que les variables
wanted were Lua variables.
*Ce qui a été refusé :* hooker `debug.getregistry` pour la cacher, comme fait
Nova. C'est de la dissimulation, et ça ne change rien au reste de l'empreinte.

**H1 — Le vecteur est l'écriture dans l'état Lua du jeu.**
*Preuves :* delta fonctionnel isolé côté Lua (§5) ; O1 vs O2 ; O3 (aucune
Lua exécutée, mais le code qui *sait* écrire reste là — en fait non : désarmé,
il n'écrit rien. Donc **O3 weakens H1**).
*Statut : plausible mais **affaiblie par O3**.*

**H2 — Le vecteur est l'injection seule (facteur 2).**
*Preuves :* O3 ; le thread (`#322`, `#3770`, `#3962`, `#4600` — bannis en
injectant sans utiliser).
*Contre-preuves :* O1 (des mois d'usage sans flag avec la même injection).
*Statut : **contradiction non résolue** entre O1 et O3.*

**H3 — Le vecteur est comportemental, côté serveur.**
*Preuves :* le thread (`#247–#274`, scènes de farm loggées ; `#285` multi-hit) ;
facteur 3.
*Note :* le build désarmé n'utilise aucune feature, mais le **comportement de
jeu** reste celui d'un compte normal — donc H3 n'explique pas O3.

**H4 — Détection native, en C++, sur l'état Lua.**
*Preuves :* la **seule** hypothèse qui réconcilie O1, O2 et O3 : un contrôle en
C++ (capable d'inspecter le registre, que Lua ne voit pas) qui constate l'état
muté **lorsqu'il est armé** — et constatait autre chose, ou rien, avec les
anciens builds.
*Statut : **la plus cohérente avec l'ensemble des observations**.*

> O3 se réconcilie en effet avec H4 : le build désarmé n'écrit rien, mais
> l'injection, les hooks `user32`, les vtables DXGI et le manual-map sont
> présents. Un contrôle C++ voit *ça* — et c'est commun à O1. La différence
> entre O1 et O2/O3 reste alors à expliquer par le **moment** : O1 découle d'une
> longue utilisation passée, peut-être avant le durcissement côté serveur du
> 7 octobre mentionné dans `DETECTION.md`.

---

## 8. Ce qui reste indéterminé

- **Aucun test en jeu n'a été conduit** pour cette analyse : les sanctions sont
  asynchrones et par vagues (`#362`), donc l'absence de bannissement à T+1h ne
  prouve **rien** (un flag ne se périme pas).
- Les **binaires client et anti-triche ne sont pas dans le dépôt** : H4 est
  déduite, pas observée.
- Le diff C++ a été mené **fichier par fichier sur les TU** ; un changement dans
  une bibliothèque tierce (`third_party/`) ou dans `tools/embed_lua.py` n'a pas
  été instruit.

---

## 9. Pistes d'action — sur notre dépôt uniquement

Ces trois écritures (§6) sont du **confort de développement**, pas de la
fonctionnalité. Les retirer :

1. supprime `_G.SPECTER` — un registre privé suffit pour résoudre le namespace ;
2. supprime `registry["__specter_ns"]` — même raison ;
3. cesse de remplacer `lua_atpanic` — c'était du diagnostic.

Coût : faible. Effet : ramène l'empreinte Lua du build à celle de `2572297`.

> **Ce que ça ne garantit pas** : rien ne permet d'affirmer que ces écritures
> sont le vecteur. H4 reste non observée. L'action est rationnelle (retirer du
> code mort), pas une garantie.

Complément déjà en place : depuis le commit `98f5848`, le build est **désarmé
par défaut** — injecter n'exécute plus aucune ligne de Lua, et l'armement est un
acte explicite depuis le menu.

---

## 10. Résumé

- Notre DLL **n'émet rien** (0 import réseau, vérifié sur le binaire).
- Les **8 541 scripts Lua du jeu ne contiennent aucune détection** d'environnement.
- Le **delta fonctionnel** entre la version jamais signalée et la version
  signalée est **intégralement** dans la couche Lua — la couche C++ est
  identique au caractère près.
- Le build écrit **trois choses** dans l'état Lua du jeu qui n'ont aucune
  raison d'exister.
- Aucun test en jeu n'a été conduit pour cette analyse ; aucune conclusion
  causale n'est établie.