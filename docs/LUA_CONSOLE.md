# La console Lua — module, interface et canal CLI

> ⚠️ **Ce document décrit un état de rue antérieur.**
>
> Le pont Lua n'a plus de canaux : ni canal téléport, ni maintenance de la
> stamina, ni canal CLI. La pompe est dans `lua/pump.*`, le transport dans
> `lua/mailbox.h`, et **la seule exécution de Lua est le bouton « Execute »** de
> l'onglet Lua Editor.
>
> Voir `docs/ARCHITECTURE.md` §4 pour l'état réel, et `docs/PLAN.md` pour la
> migration.


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

Chaque chunk exécuté est mirroré sur le **pipe de logs** (`/tmp/specter.pipe`,
donc `specter.log`) ligne par ligne sous la forme `[specter] lua| …`
(200 lignes max), et affiché dans l'onglet **Lua Editor** de l'overlay.

## Canal CLI (`tools/lua.sh`) — **retiré**

Le canal n'existe plus. `tools/lua.sh` explique pourquoi et sort en erreur.

Il déposait un chunk dans `/tmp/specter-lua/cmd.lua` et la pompe le relisait
toutes les 200 ms. C'était un **canal d'exécution de code déclenché par le
système de fichiers** : sans UI, sans authentification, et sans qu'aucune action
humaine soit nécessaire. Tout processus capable d'écrire ce fichier y entrait.

La seule voie d'exécution est maintenant le bouton **Execute** de l'onglet Lua
Editor. Chaque exécution part dans un environnement construit pour elle — voir
`docs/ARCHITECTURE.md` §4.

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

### Mécanisme : hook `changeStamina` sur la **classe**

Le coût de déplacement passe tous par
`actorCombatAttribute:changeStamina(-cost)`. Avaler les deltas négatifs, c'est
la stamina infinie **à la source** — avant que le coût ne soit appliqué — et ça
ne fait pas course avec la vidange par frame qu'un refill par frame produirait.

On patche la **classe**, pas l'instance :

```lua
local AC = require('Common.Ability.Attribute.ActorCombatAttribute')
AC.changeStamina = function(self, delta)
  if specter.store.inf_stamina and tonumber(delta) and tonumber(delta) < 0 then
    local e = self and self.entity
    if e == pg.me or e == pg.pawn then return true end
  end
  return orig(self, delta)
end
```

**Vérifié en jeu** : `require('Common.Ability.Attribute.ActorCombatAttribute')`
rend **exactement** le métatable partagé des instances
(`AC == getmetatable(aca)`, et `mt.__index == mt`). Un patch sur cette classe
intercepte donc les appels réels, et **toute instance future l'hérite**.

Trois conséquences, comparées à l'ancien patch d'instance :

| | patch d'instance (avant) | patch de classe (maintenant) |
|---|---|---|
| relog | le patch mourait, il fallait le remettre | **rien à faire** |
| maintenance | chunk rejoué toutes les ~10 s | **supprimée** |
| bascule | coût un chunk à chaque toggle | **instantanée**, le drapeau est lu à l'appel |

### Pourquoi ne pas re-pin la stamina à chaque frame

Chaque `setAttribute` déclenche tout le pipeline d'attribut du jeu (recalc +
notifications HUD + diffusion d'événements) et fait saccader la frame. Le hook
avale en `return true` — quelques nanosecondes — et la stamina n'est jamais
re-épinglée en boucle.

### Implémentation

- `features/inf_stamina/inf_stamina.{h,cpp}`. Le toggle soumet **un seul chunk**
  sur le canal `kChannelStamina` : poser le patch, ou juste retourner le
  drapeau. Le drapeau est `specter.store.inf_stamina`, donc il vit dans notre
  store et **jamais dans un global du jeu**.
- `install()` ne fait rien et ne lance aucun Lua : poser le patch à
  l'installation exécuterait du Lua que personne n'a demandé. Il est posé au
  premier toggle.
- Désactiver laisse le wrapper en place : il redevient pass-through. Il n'y a
  donc jamais de fenêtre où le jeu reste à moitié patché.
- Champ d'application **joueur uniquement** : `Const.NO_COST_MODE` reste
  désactivé (il couperait aussi les coûts de compétences et d'eau).

### Vérifier que le hook est actif

Dans l'onglet Lua Editor :

```lua
local e = pg.me
print(getmetatable(e.actorCombatAttribute).changeStamina
      == e.actorCombatAttribute.changeStamina)
```

`false` = le hook de classe est en place. `true` = il ne l'est pas.
