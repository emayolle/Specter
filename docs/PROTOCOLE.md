# Le protocole serveur

Date : 2026-10-16. Source : les scripts Lua du jeu
(`~/Downloads/ScriptAniimo/source/xfs/luascripts/`), pas le binaire.

Ce document répond à deux questions :

1. Comment un appel serveur circule, du clic du joueur au paquet sur le réseau.
2. Pourquoi on ne peut pas obtenir plus d'objets en changeant un réglage
   local — la suite de `docs/STREAMING.md`.

## L'échelle en quatre marches

```
1. Lua          entity:serverMsg("RPC_CS_StartInteract", type, id, id, params)
     |
2. ServerProxy  validation locale + nom -> entier
     |          self.stub:dispatchRpc("sendEntityMessageV2", "", "", index, 0, ctx, ...)
     |
3. C# stub      serialisation protobuf, n° de séquence, chiffrement, socket
     |
4. serveur      revalide TOUT, puis repond en RPC_SC_*
```

### 1. Le point de sortie

`ServerProxy.lua` — 1065 appels à `:serverMsg(` dans les scripts du jeu.

```lua
function ServerProxy:serverMsg(name, ...)
    if not RpcSendValidator.validate(name, ...) then return end
    local index = RpcIndex.sendRpcIndex(name)
    self.stub:dispatchRpc("sendEntityMessageV2", "", "", index, 0, "", ...)
end
```

`self.stub` est un objet **C#** (`ClientRepo`). C'est là que Lua s'arrête et où
le natif commence.

Un vrai appel, pour un coffre :

```lua
-- ClientInteractComponent.lua:46
execEntity:serverMsg("RPC_CS_StartInteract", interactType, entityId, interactId, interactParams or {})
```

`entityId` vide = « l'entité qui exécutera est la cible ». Sinon le serveur
route vers l'entité nommée.

### 2. Les noms ne voyagent pas — seulement des entiers

C'est la seule chose qui ressemble à de l'obfuscation dans tout le protocole.

```lua
-- RpcIndex.lua
local RPC_SALT = "x"

function RpcIndex.calculateRpcIndex(salt, name)
    local a, b, c, d = md5.digest(salt .. name)
    return bit.lshift(bit.band(byte(a), 127), 24)
         + bit.lshift(byte(b), 16)
         + bit.lshift(byte(c), 8)
         + byte(d)
end
```

Un MD5 du nom, le premier octet masqué à 127 pour rester positif, recombiné en
entier 31 bits. Sur le réseau :

| nom | entier |
|---|---|
| `RPC_SC_OnInteractStart` | 1 941 661 249 |
| `RPC_SC_OnInteractSuccess` | 679 744 883 |
| `RPC_SC_OnInteractInterrupt` | 1 545 048 150 |

**Ce n'est pas un secret.** Le sel est `"x"`, en clair dans le client. C'est un
index, pas un chiffrement : ça évite que le nom traîne en clair dans le paquet,
et c'est tout. Nous pouvons calculer n'importe quel index.

**Mesuré** : 566 noms dans `RpcIndexDict.lua`, **0 collision**. L'espace fait
~2^31, donc 0 collision est attendu — et c'est bien le résultat. Sans surprise.

### 3. La réception est le miroir exact

```lua
-- GateClientRpcHandler.lua:383
function GateClientRpcHandler:entityMessageV2(entityId, raw, index, context, ...)
    local methodName = RpcIndex.INDEX2RPC[index]        -- table 1
    if methodName == nil then
        methodName = RpcIndex.RPC_INDEX2NAME[index]    -- table 2, Config
        if pg.isBot and BotIgnoreRpc[methodName] then return end
    end
    local targetEntity = (entityId ~= "") and ownEntity:getRealOwner(entityId) or ownEntity
    local method = targetEntity[methodName]
    if method == nil or not class.isInstanceOf(method, RpcMethod) then return end
    method(Const.ACCESSOR_SERVER, targetEntity, ...)
end
```

Deux tables de traduction, remplies par deux chemins :

- `INDEX2RPC` — `EntityFactory.lua:152`. Les RPC sont découverts **par
  réflexion** sur les classes d'entités, au chargement :
  ```lua
  cls[originKey] = func                       -- la vraie fonction Lua
  EntityFactory._recordRpcMethod(name, k)
  RpcIndex.registerRpc(k)
  cls[k] = RpcMethod(methodType, v, k, cls, originKey, data.Switch)
  ```
  Chaque RPC devient un objet `RpcMethod` **appelable** (`meta.__call`). On
  appelle donc `entity:RPC_SC_OnInteractSuccess(...)` comme une fonction.

- `RPC_INDEX2NAME` — le fallback, `Config/RpcIndexDict.lua`, chargé par
  `RpcIndex.Init()`.

Et un filtre anti-bot, textuel, dans le client :
`if pg.isBot and BotIgnoreRpc[methodName] then return end`.

## Les deux garde-fous du client — et pourquoi ils ne valent rien

**`RpcSendValidator`** — vérifie le nombre et le type des arguments contre
`Config/RpcCSArgDict.lua`, **913 RPC_CS** documentés avec leur signature
complète. Extensible : `select("#", ...) ~= entry.argNum` → refus. Coupable par
`CommonSwitch.RpcSendValidate`.

**`RpcMethod:call`** — contrôle l'accesseur (`ACCESSOR_SERVER` /
`ACCESSOR_CHANNEL` / `ACCESSOR_ENGINE`), le `Switch` fonctionnel, le mode
observation, et un contournement en mode debug :

```lua
if _G_IsDebugMode and rawget(getfenv(2), "isInTelnetConsole") then
    return self.entity[self.originFuncName](callerAccessor, obj, ...)  -- appel direct
end
```

**Les deux sont du Lua client.** On les lit, on les contourne, on les
désactive d'une ligne. Ce ne sont pas des mesures de sécurité, ce sont des
vérifications de développement qui évitent les crashes.

**Le seul verrou est l'étage 4.** Le serveur revérifie tout : propriété de
l'objet, distance, délai, droit, quota. Un client qui envoie n'importe quoi
obtient des erreurs, pas des coffres.

## Ce que ça dit sur les entités — la suite de STREAMING.md

Deux afirmaciones à tenir séparées :

**Ce qui est mesuré.** Charger plus de terrain ne fait apparaître aucune
entité de plus (`docs/STREAMING.md`). Les entités arrivent par le réseau, pas
par le streaming.

**Ce qu'on ne sait pas.** Si le client **déclare** sa zone d'intérêt au
serveur, alors cette déclaration est un levier, et c'est le seul qui reste.

Deux candidats, tous deux à **deux entiers** :

```lua
-- Config/RpcCSArgDict.lua:1000
RPC_CS_SetPlayerAoiLevel = { "int", "int" }
```

```lua
-- ClientAoiComponent.lua:262
function ClientAoiComponent:setSyncFps(range)
    self:__callAoiFunc("setSyncFpsRange", range, range)   -- range, range
end
```

`refreshSyncFpsRange()` choisit la valeur :

| situation | `syncFps` |
|---|---|
| joueur principal, multi-joueur | 30 |
| joueur principal, solo, ou en piège | 10 |
| les autres entités | 0,2 |

Deuxdetails qui font douter :

- le nom dit **fps**, donc une cadence, pas une distance ;
- `0,2` est envoyé dans un champ déclaré `int` ;
- `setSyncFpsRange` est une méthode **C#** (`self.aoi`), pas un RPC — le lien
  entre les deux n'est pas tracé.

Non vérifié. C'est la piste la plus sérieuse qui reste, et elle est **gratuite
à tester** : un appel, un comptage d'entités.

## Ce qu'on ne fera pas

Le catalogue est complet et lisible : `RPC_CS_DirectCollect`,
`RPC_CS_TakeItemFromPlayer`, `RPC_CS_SellItemByGenId`, `RPC_CS_UseItemById`…
On pourrait tous les appeler.

L'étage 4 les refuse. Un client qui triche sur ces appels ne gagne rien : il se
fait bannir, et le test de triche est fait côté serveur, sur des données que le
client n'a pas (`RPC_CS_SpecialDamage`, la validation de dégâts de chute — voir
le point ouvert sur `nofall`).

**Ce qu'on cherche n'est pas un accès gratuit, c'est la déclaration de zone.**
Une variable que le serveur écoute et qui élargit ce qu'il nous envoie. Ça se
teste en une mesure.