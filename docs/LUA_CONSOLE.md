# La console Lua — module, interface et canal CLI

Tout le gameplay d'Aniimo (attributs, stamina, capacités, état UI) vit en **Lua**,
pas en C#. Le C# ne fait que *relayer* : `CharacterControllerComponent.CheckStamina`
résout un `LuaFunction` et l'appelle. Pour agir sur le jeu, il faut donc exécuter
du Lua **dans l'état Lua du jeu**.

Le module `features/lua_console.{h,cpp}` est la seule interface vers cet état.
Elle expose trois choses : un **pont** (exécuter un chunk), une **pompe**
(le thread sur lequel le faire) et un **canal CLI**.

---

## Contrainte centrale : le thread

LuaJIT n'est pas thread-safe. Le `lua_State` ne peut être touché que par le
thread qui exécute déjà du Lua — le **thread principal du jeu**. On ne peut donc
pas exécuter depuis le thread de rendu de l'overlay (celui de `Present`).

La solution est une **pompe** : on détourne `LuaManager.CommonUpdate`
(RVA `0x172ADC0`, appelée une fois par frame par le gestionnaire de managers via
`ManagerInfo.CommonUpdate`, sur le thread principal) avec notre propre moteur
d'inline-detour (`overlay/detour.*`). Notre hook s'exécute **avant** le tick Lua
du jeu, draine ce qui est en attente, puis appelle le trampoline (le code
d'origine).

Le prologue (`48 8b c4` / `48 89 58 08`, 7 octets) est décodable par la table de
longueur ; le hook s'installe donc sans toucher au reste.

## Contrainte centrale : l'accès à l'état

L'API C de LuaJIT est **exportée par `xlua.dll`** (`luaL_loadbuffer`, `lua_pcall`,
`lua_gettop`, `lua_settop`, `lua_tolstring`, `lua_toboolean`, …). On ne
linke pas : on les résout par nom (`GetProcAddress`).

Le `lua_State*` s'obtient de la façon documentée par xLua, sans appeler de code
managé :

```
LuaManager.luaenv (@0x18)  ->  LuaEnv.rawL (@0x10)  ->  lua_State*
```

`LuaManager*` est justement le `this` que la pompe reçoit en premier argument.

## Exécution d'un chunk

Le chunk de l'utilisateur est enveloppé puis compilé/PCall afin que :

- `print(...)` soit capturé ligne par ligne (le `print` global est toujours
  restauré, même en cas d'erreur) ;
- les erreurs de compilation **et** d'exécution soient attrapées et rapportées ;
- les valeurs de `return` du chunk soient ajoutées à la sortie ;
- le wrapper renvoie `(texte, ok)` — deux résultats lus par le C.

Aucun bac à sable : une boucle infinie gèle le jeu. C'est un outil de dev.

---

## Interface du module

| Fonction | Thread appelant | Rôle |
|---|---|---|
| `install()` | worker caché | résout `xlua.dll`, installe le détour `CommonUpdate`, crée le dossier CLI |
| `submit(code, len)` | thread de rendu | met un chunk de l'UI en attente (le dernier écrase le précédent) |
| `take_result(out, cap, ok)` | thread de rendu | récupère le dernier résultat pour l'UI |
| `ready()` / `status()` / `ticks()` | thread de rendu | état du pont pour l'UI |

La passation render → Lua passe par une `CRITICAL_SECTION` et deux tampons
fixes : jamais de STL dans le chemin chaud.

## Sorties visibles

Chaque chunk exécuté (UI **ou** CLI) est mirroré sur le **pipe de logs**
(`/tmp/specter.pipe`, donc `specter.log`) ligne par ligne sous la forme
`[specter] lua| …` (200 lignes max), et publié dans
`/tmp/specter-lua/out.txt` :

```
#seq=<n> ok=<0|1>
<texte>
```

## Canal CLI (`tools/lua.sh`)

```
tools/lua.sh 'print(1+1)'      # chunk en argument
tools/lua.sh -f script.lua     # depuis un fichier
echo '…' | tools/lua.sh        # depuis stdin
tools/lua.sh --no-wait '…'     # sans attendre le résultat
```

Protocole (fichiers uniquement, **dans `/tmp`** — jamais le dossier du jeu ni le
prefixe Wine) :

1. le script publie le chunk de façon **atomique** (`cmd.tmp` → `cmd.lua`) ;
2. la pompe le **réclame** de façon atomique (`cmd.lua` → `cmd.run`), l'exécute,
   supprime `cmd.run` — le rename garantit qu'on ne lit jamais un fichier
   partiel ;
3. le script attend que `#seq` change dans `out.txt` et affiche le résultat.

Le sondage est limité à une fois toutes les 200 ms.

> Le module ne s'active qu'**en jeu** : la pompe n'existe que si
> `LuaManager.CommonUpdate` est appelée. Un chunk déposé avant l'entrée en jeu
> reste en attente.

## Notes pratique (entrée texte dans l'overlay)

L'overlay doit pouvoir recevoir du texte pour l'éditeur. La sous-classe de
fenêtre (`overlay/game_input.cpp`) qui avale déjà les messages du jeu les
**transmet à ImGui** (`keyboard_sink`), et la gate est levée le temps de l'appel
pour que les modificateurs (Maj/Ctrl) soient lus correctement. Comme SUPPR sert
de touche de bascule du menu, elle est laissée à ImGui quand un champ de texte a
le focus (le menu se ferme alors par le bouton **Fermer le menu**).

---

## Stamina de déplacement infinie (toggle)

L'épuisement de stamina est piloté côté Lua : les composants de mouvement
(sprint, dash, glide, climb) passent tous par `ClientStaminaComponent` →
`actorCombatAttribute:changeStamina(-coût)` (`Common.Ability.Attribute.
ActorCombatAttribute`), avec lecture via `getAttribValue(AttributeConst.
stamina_cur)`.

### Mécanisme : hook `changeStamina` par instance

Le toggle « Stamina de déplacement infinie » du panneau installe une fois un
**remplacement de `changeStamina` sur l'instance du joueur** (shadow de la
méthode du metatable pour cet objet uniquement) :

- les **deltas négatifs** (une dépense de stamina : sprint/dash/glide/climb)
  sont avalés (`return true`) — la stamina ne descend jamais ;
- les **deltas positifs** (régénération naturelle, objets…) passent tels quels à
  la méthode d'origine.

L'endurance est remise à fond **une seule fois** à l'installation (via
`setAttribute` — l'API du jeu, donc les notifications d'attribut et le HUD
fonctionnent). On ne re-pinne **pas** à chaque drain : chaque `setAttribute`
déclenche le pipeline complet de changement d'attribut du jeu et causerait un
mini-freeze à chaque utilisation.

### Pourquoi un hook par instance plutôt qu'un tick par frame

Découverte de terrain : les chunks de ce pont s'exécutent dans l'environnement
Lua **sandboxé** du jeu. Les *lectures* des globals existants passent au vrai
`_G`, mais les *écritures* de globals (même `_G.x = …`) partent dans une table
d'ombre et n'atteignent jamais le vrai `_G`. La première implémentation — une
chunk d'installation définissant `__SpecterStaminaTick`, puis la pompe en
`lua_getglobal` + `lua_pcall` par frame — ne voyait donc jamais la fonction
(`getglobal` lit le vrai `_G`) : le toggle « ne faisait rien » en silence.

Les écritures sur **champs d'objets réels** (l'instance `actorCombatAttribute`)
persistent, elles : le hook est immune au sandbox. Avantage supplémentaire :
avaler la dépense **à la source** n'entre pas en course avec le drain du jeu
par frame (un refill avant l'update aurait été annulé par la dépense ensuite).

### Implémentation

- `set_infinite_stamina(bool)` (thread de rendu) : bascule l'atomique
  `g_inf_stamina` et soumet une chunk **silencieuse** (installation ou
  restauration) qui est consommée par la pompe.
- L'installateur est **idempotent** (marqueur `aca.__SpecterHooked`) ; la pompe
  le ré-émet silencieusement toutes les ~10 s tant que le toggle est actif, ce
  qui re-hook automatiquement une entité/`actorCombatAttribute` neuve après un
  changement de scène ou un relog.
- Le chemin **silencieux** (`run_silent`/`submit_silent`) n'écrit ni dans
  `out.txt`, ni dans le compteur `#seq=` : la maintenance n'entre jamais en
  conflit avec une commande `tools/lua.sh` en vol. La vérification de
  résistance du hook : `tools/lua.sh 'local e; for k,v in pairs(pg.global.actorMgr.uid2Ent) do e=v break end
  print(getmetatable(e.actorCombatAttribute).changeStamina == e.actorCombatAttribute.changeStamina)'
  ` (false = hook actif).
- champ d'application **joueur uniquement** : `gmMode == Const.NO_COST_MODE`
  reste désactivé (il couperait aussi les coûts de compétences et d'eau).
