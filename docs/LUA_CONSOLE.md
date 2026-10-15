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
- le wrapper renvoie `(texte, ok, étape, env)` — quatre résultats lus par le C.

Une boucle infinie gèle toujours le jeu : il n'y a pas de garde-fou temporel.
C'est un outil de dev, et le bac à sable ci-dessous est une isolation
**d'espace de noms**, pas de temps.

### Le bac à sable, et ce qu'il a été mesuré de lui

L'environnement (`__newindex` / `__index`) est construit **en Lua**, dans la
fabrique, et ancré dans le registre sous une clé dérivée du `lua_State*`.
L'environnement est donc **réutilisé d'un Execute à l'autre** : c'est ce qui fait
survivre le store.

Trois règles, mesurées en jeu :

| écriture | destination |
|---|---|
| nom **déjà présent** dans le `_G` du jeu | le **vrai** global du jeu |
| nom **neuf** | notre store, invisible depuis `_G` |
| aucune | le nom n'est écrit nulle part |

```
N1 nom neuf      store : A  | _G : nil
N2 nom existant  _G   : B  | store : nil
N3 restaure      _G   : Lua 5.1
E1 _G contient env/store/specter : 0 0 0
E2 souvenir  store : 777  | _G : nil
```

`E1` est le test de fuite : on balaie les ~236 globals du jeu et on cherche si
l'un d'eux **est** notre env, notre store, ou la table `specter`. Zéro.

### Pourquoi il n'y a pas de `specter.rawset` / `specter.rawget`

Il y en a eu, en C. Ils ont été retirés parce qu'ils tuaient le jeu, et la
question revenue depuis est : est-ce qu'on les réimporte ?

**Non, et c'est mesuré.** Ce build ne livre pas le `rawset` standard : celui de
`_G` est un wrapper (`Common/Functions.lua:84`) qui appelle `raw_rawset`. Il
refuse une table en **argument 1** :

```
bad argument #1 to 'raw_rawset' (table expected, got function)
```

C'est ce qui a forcé la porte de stamina à vivre sur la classe `AC` et pas sur
la fonction enveloppée. Mais l'**argument 3** — la valeur — accepte n'importe
quoi, une fonction comprise :

```
specter.store.f1 = function() return 42 end   -> function
f2 = function() return 43 end                 -> function
```

Il n'y a donc **aucun trou** : le `__newindex` appelle `rawset(__store, k, v)`
avec une table en argument 1, et cela marche. `specter.rawget` non plus n'apporte
rien : le store n'a pas de métatable, donc `specter.store.absent` est déjà `nil`
sans rien chercher dans `_G`.

Deux classes de crash distinctes ont coexisté ici, et il ne faut pas les
confondre :

1. `lua_rawseti` sur un `nil` dans `build_specter` — un index écrit à la main,
   `-3` qui tombait sur le `nil` au lieu de l'env ;
2. un `p_settop` de fin de fonction **sauté** par le `longjmp` de LuaJIT quand
   `__newindex` levait — la pile Lua restait sale au milieu du traitement.

La deuxième est celle qui a tué les fonctions C. La première est celle qui tuait
le jeu au **deuxième** Execute de chaque session.

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

## Canal shell (`tools/lua.sh`) — **ouvert par défaut**, la case le ferme

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

### Ouverture par défaut

Le canal est **ouvert au chargement**. La case « Autoriser le shell » ne sert
plus qu'à le **fermer** — c'est tout.

C'est l'inverse de ce qui était prévu. Le canal était livré fermé, ouvert par
une case à cocher, pour que rien ne puisse exécuter du Lua sans qu'une personne
l'ait demandé. La case a été demandée retirée, puis remise, puis ouverte par
défaut : sur une machine qui est la nôtre, où le module est injecté à la main,
une case à re-cocher à chaque session est une case que personne ne lit.

Ce que ça coûte, dit franchement : tant que le module est chargé, **tout ce qui
peut écrire `/tmp/specter-cli/req.lua` peut exécuter du Lua dans le jeu**. Pas
d'injection, pas d'UI, pas d'intention. C'était vrai de la case aussi — il
fallait juste dix secondes de ne pas y toucher.

Ce qui reste comme garde : chaque exécution est **journalisée** dans
`specter.log`. Le filet n'est pas « personne ne peut s'en servir », c'est
« rien ne passe sans trace ».

Le timeout automatique reste dans le code (`kCliWindowTicks = 0`) pour que le
compromis soit visible plutôt qu'oublié.

`tools/lua.sh` sort en erreur 4 après 60 s si le canal est fermé.

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

---

## La couche de liaison — `specter.var.*`

Pont C++ vers Lua, construit sur LuaBridge3 (commit `eaafdf00`, forme amalgamee
officielle). Ce qui suit est **mesure en jeu**, pas deduit.

```lua
specter.var.counter = 42      -- ecrit dans la variable C++
print(specter.var.counter)    -- 42
specter.var.x = 9
specter.reset()
```

Toutes les proprietes sont en **lecture et ecriture**. Ce n'est pas un defaut :
la forme lecture seule fait lever « attempt to write a read-only field », et cette
levee se produit dans le metamethode C++ de LuaBridge. LuaJIT implemente une
erreur Lua comme un longjmp hors du cadre C : **aucun destructeur C++ ne tourne**,
LuaBridge abandonne sa comptabilite de pile, et le processus meurt. Mesure : le
jeu a disparu sur cette seule affectation, journal arrete sans une ligne.

### Resolution, ou refus

`lua/capi.cpp` resout **46 symboles** de l'API C Lua depuis `xlua.dll`. Si un seul
manque, `resolve()` rend faux, journalise le nom de chacun, et
`bind::install()` n'enregistre rien. Enregistrer contre des pointeurs nuls
construirait des liaisons qui piegent a l'appel.

`lua/capi_shim.cpp` **definit** les fonctions globales que LuaBridge appelle,
chacune renvoyant vers son pointeur. La redirection par `#define` ne marche pas :
LuaBridge fait `using ::luaL_unref;` et une using-declaration ne peut pas nommer
une variable. Ecrire les 46 signatures a la main n'est pas le risque que c'a
l'airs : chacune est une redeclaration de `lua.h`, donc une signature fausse est
une erreur de compilation. Le compilateur en a attrape onze d'un coup, dont deux
inversees (`lua_setmetatable` renvoie `int`, `luaL_unref` renvoie `void` et prend
trois arguments ; en 5.1 `lua_gettable`/`lua_setfield` renvoient `void`).

**Un oracle hors-jeu du shim est impossible.** LuaBridge appelle l'API par nom.
Dans une DLL, `xlua.dll` resout ses propres appels dans sa propre table d'imports ;
dans une liaison statique, nos thunks s'interposeraient partout. Le jeu est le
seul banc d'essai.

### Isolation

`bind::install()` utilise `getNamespaceFromStack`, **jamais**
`getGlobalNamespace` — le seul appel qui mettrait la table dans le `_G` du jeu.
Les liaisons vivent dans `specter`, qui vit dans notre environnement ancre.

```
env :    0   |  specter :    0     -- sur les 236 globales du jeu
```

Le balayage compare des **identites**. Lire un champ dans chaque table declenche
les metamethodes du jeu : un test de fuite qui indexe n'est pas une lecture seule,
et fait echouer `BddDataMgr.lua` de facon reproductible.

### Une installation par environnement

Le preamble fait `rawset(__env,'specter',__sp)` **dans** `if __env==nil`. Aux
Executes suivants l'environnement est donc celui d'avant : `specter` reste la
table du premier Execute, et une table neuve creee a chaque fois ne sert a rien.
Enregistrer deux fois faisait mourir le jeu au deuxieme Execute.

### Pièges rencontres, tous documentes dans le code

1. **`extern "C"` obligatoire.** `luaconf.h` ne le declare pas : compile en C++,
   chaque appel sort en `_Z10lua_concatP9lua_Statei` et **rien ne resout** contre
   les exports C de `xlua.dll`. Aucun avertissement ; l'echec est a l'execution.
2. **L'index de table avant la poussee de la cle.** `lua_getfield`/`lua_setfield`
   evaluent `index2addr(L, idx)` **avant** de pousser la cle. Pousser d'abord
   fait glisser tout index negatif d'un cran : lecture dans la mauvaise table,
   ecriture une table trop haut. C'est ce qui faisait disparaitre `_G`, `pairs`,
   `string`, `math` et `require` du jeu — les seules survivantes etaient les dix
   fonctions que le preamble capture en parametres, qui ne passent jamais par ce
   chemin.
3. **`-1`, pas `-2`.** La pile fait `[chunk, store, specter]` : `-2` est le store.
   L'enregistrement paraissait reussi et la pile se reequilibrait ; seul le
   symptome etait que Lua ne trouvait rien. `install()` verifie desormais que la
   cible porte `version`.
