# Capture silencieuse — ce qui marche, ce qui casse

Date : 2026-10-16. Statut : **non atteint**, et le client se désynchronise en
essayant. Ce document existe pour ne pas refaire le chemin.

## La demande

« silent catch / catch aura » : capturer sans le geste. Sans animation, sans
caméra, sans rotation. Tout est autorisé : hooks, analyse, tests en jeu.

## Ce qui est établi

### 1. Les RPC bruts sont acceptés puis ignorés

`RPC_CS_CaptureHoldBall(envId, itemId)` et
`RPC_CS_FireBall(itemId, ballUid, catchMode, cb)` — tous leurs arguments
naissent chez nous (`genEnvId()` est local, et le journal montre que `ballUid`
vaut exactement cet `envId`). Le rappel revient avec **`code = 0`**.

Et pourtant : **aucun message en retour**, pas de `RPC_SC_OnFireBall`, pas de
session. Trois fois de suite, avec des chemins différents.

**`code = 0` n'est pas « le lancer a réussi ».** C'est « le message a été pris
en charge ». Le seul signal de vérité est `RPC_SC_OnFireBall`, et il ne vient
pas.

### 2. Le contact forgé est refusé

```
RPC_CS_BallHitEntity(session, cible, fromBehind)   →   code = 1010
```

`Common/NoticeDef.lua:835` : **`ERROR_INVALID_TARGET`**. La session avait été
acceptée ; c'est la cible qui a été refusée. Le serveur ne se fie pas au
rapport de touchement du client.

### 3. Il manque l'état, et il ne part pas de l'API

| ce qu'on fait | `CharacterStateChange` | `OnFireBall` |
|---|---|---|
| `toggleCatchMode()` + `throwWithRpc()` | **0** | non |
| joueur tenant vraiment la balle + `throwWithRpc()` | **0** | non |

`toggleCatchMode()` ne fait que `currentContext:exit()` — un appel vide.

L'état qui compte, c'est `eModel:ForceChangeToUpperState(5, THROWHOLD)`, une
méthode **native**. Appelée de hors du cycle du jeu, elle ne se synchronise pas.

### 4. La bonne entrée, et la vraie séquence

```lua
-- ClientCaptureMainComponent:66
function ClientCaptureMainComponent:throwItemFromBag(itemId)
    self:switchContext(ClientCaptureUtils.getThrowContext(self, itemId))
end
```

Là, **27 `RPC_CS_CharacterStateChange`** partent. L'état est là.

Puis `ctx:throw()` (le FSM) et, **150 ms plus tard** — pour que la synchro soit
partie — `ctx:throwWithRpc()`. Résultat : la chaîne complète, pour la première
fois.

```
RPC_CS_FireBall x2     RPC_CS_SendBallMsg x5
RPC_CS_NotifyCaptureAnimStart x1
RPC_CS_BallHitEntity x1            ← le contact part enfin
RPC_CS_NotifyCaptureAnimEnd x1
```

**Le ordering est le sujet** : le RPC doit partir *après* la synchro d'état,
pas en même temps.

## Le problème

Juste après, le client se désynchronise :

```
entites=0   entrant=0   sortie=495 → 598 → 703 → …
```

Zéro entité, zéro message reçu, et les sorties montent sans fin — le client
spammait `RequestCreateClientEntity` sans réponse. Boucle typique de désync.

**Hypothèse** : le contexte était `CameraThrowContext`, pas `ThrowBallContext`.
On a appelé `throw()` et `throwWithRpc()` sur un contexte dont la machine à
états n'était pas dans l'état de lancer — d'où un `BallHitEntity` émis avec une
session que le serveur n'a jamais ouverte.

Non vérifié : le jeu était déjà cassé, la mesure suivante n'a pas pu être prise.

## Ce qui reste à tester, dans cet ordre

1. **Le contexte correct d'abord.** Forcer
   `pg.me:throwItemFromBag(itemId)` et attendre que
   `currentContext.className == 'ThrowBallContext'`, puis seulement
   `throw()` + `throwWithRpc()` différé. C'est l'hypothèse principale du
   désync.
2. **L'offset.** 150 ms est une supposition. Mesurer : 50 / 150 / 400 ms.
3. **L'event plutôt que la minuterie.** Le jeu émet `fireBall` quand l'animation
   passe le bon point ; s'y accrocher serait plus fidèle qu'un délai fixe.

## Ce qu'on ne fera pas

- Remplacer le `prob` ou le `canCapture` que le client calcule localement.
- Contourner `MUST_SUCCESS_PROB_THRESHOLD`, `MAX_HIT_DISTANCE`,
  `MAX_BEHIND_ANGLE`.
- Signaler un contact qui n'a pas eu lieu.

`clientGet` calcule la probabilité **côté client**
(`CatchProbContext.clientGet`) et la valeur remonte au serveur. C'est
exactement le genre de donnée qu'un serveur valide. Le fait que
`ERROR_INVALID_TARGET` existe montre que la vérification est réelle ;
falsifier la probabilité serait détectable, et le prix d'un bannissement ne
vaut pas une capture.

## L'état de `scripts/capture_auto.lua`

Le script est **inutilisable en l'état** : il appelle `toggleCatchMode()`,
qui ne fait rien d'utile. Il faut le réécrire sur `throwItemFromBag` +
séquence différée, une fois le point 1 validé.