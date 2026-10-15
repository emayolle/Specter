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

## Canal shell (`tools/lua.sh`) — **armé, et fermé par défaut**

```
tools/lua.sh 'print(1+1)'      # chunk en argument
tools/lua.sh -f script.lua     # depuis un fichier
echo '…' | tools/lua.sh        # depuis stdin
```

Protocole (fichiers uniquement, **dans `/tmp`** — jamais le dossier du jeu ni le
prefixe Wine) :

1. le script publie le chunk de façon **atomique** (`req.tmp` → `req.lua`) ;
2. la pompe le **réclame** de façon atomique (`req.lua` → `claimed.lua`), donc
   elle ne lit jamais un fichier à moitié écrit, puis l'exécute et écrit
   `res.txt` ;
3. le script attend que `res.txt` change et affiche le résultat.

### Pourquoi il y a une case à cocher

Un canal d'exécution déclenché par le système de fichiers est un canal que
**quiconque peut écrire dans ce dossier** peut utiliser : pas d'UI, pas
d'intention, pas de trace d'une personne ayant demandé. C'est ce qui avait fait
retirer le canal à l'origine.

Le canal est donc revenu **derrière une précondition humaine** :

- la case « Autoriser le shell » de l'onglet Lua Editor ouvre une fenêtre ;
- la fenêtre dure ~10 s et **expire d'elle-même** ;
- hors fenêtre, la DLL ne regarde **pas** le fichier — le chemin n'existe pas ;
- à chaque injection, la fenêtre est fermée ;
- chaque exécution est **journalisée** dans `specter.log` (`cli: requete
  traitee`), armé ou non. Une fenêtre qui exécuterait du code dont personne ne
  peut rendre compte serait pire que pas de fenêtre du tout.

`tools/lua.sh` sort en erreur 4 avec le rappel si la fenêtre est fermée.

### Identité des chunks

Nos chunks portent le nom `@specter\client\LuaScripts\Core\Timer\SpecterManager.lua` :
la forme d'un chemin de script du jeu, avec `specter` en premier segment. Ce
n'est pas un chemin du jeu et ça ne prétend pas l'être — c'est un choix assumé.
 Emprunter le chemin d'un vrai script serait du camouflage, et cela ne tiendrait
pas face à un dumper : le **texte source** est le nôtre, et la fabrique a
12 paramètres là où un script du jeu en a un.

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
