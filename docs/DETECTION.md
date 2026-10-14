# Aniimo — facteurs de détection (intel terrain)

Synthèse des **facteurs de détection** observés côté jeu, croisée avec notre
propre expérience. Elle complète `docs/ANTICHEAT.md` (qui décrit l'**anatomie de
l'anti-cheat client**, NEP2) : ici on s'intéresse à ce qui, concrètement, nous a
valu des avertissements.

## Sources

| Source | Nature |
|---|---|
| Thread UC `772345` — `[Release] Shinoko-Aniimo [Aniimo Chetoo]`, **408 posts / 21 pages**, du 16 sept. au 10 oct. 2026 (fermé par un modérateur) | Témoignages directs des utilisateurs de Shinoko, **la même voie que nous avions empruntée** |
| Thread UC `772290` (`Aniimo Dumper`), `772391` (internal), `4580902` (LUA tool), downloads `57860`/`52879` | Annexe technique (dump/Unity-xLua) |
| PSA Steam `app/4126040/discussions/0/563668168527073570` | Rappel de l'AC kernel NEP2 |
| `fearlessrevolution.com` topic `40799` | Avertissements serveur-side |
| Notre propre historique d'injection + avertissements de compte | Corrélation décisive (voir « Notre cas ») |

L'archive brute du thread est dans `reference/unknowncheats/`
(`thread-772345-all-posts.md`). Les renvois `#N` ci-dessous sont les numéros de
post.

## Verdict court

> La détection qui nous a touchés est **serveur + comportementale**, pas kernel.
> Le vecteur principal est l'usage des **commandes Lua « GM »** du jeu, que les
> serveurs **journalisent et flaggent**. L'AC kernel NEP2 est vraisemblablement
> **dormant sous Wine** (`docs/ANTICHEAT.md`) et n'est pas ce qui nous a fait
> sanctionner.

Corollaire : **l'injection seule** s'est avérée suffisante dans plusieurs cas
pour déclencher un avertissement, mais le comportement anormal (commandes GM,
volume/rythme) est le facteur dominant.

## Facteur n°1 — commandes Lua « GM » (cause racine)

Post **#401** (sushi404, 10 oct.) :

> « Shinoko relies more on **GM script commands** that were vulnerable to exploit
> which are now **all server logged and flagged**. […] the message "Shinoko is
> freeee!!!" […] is a script for your client that also uses a **gm command**,
> which now the use of these scripts is easily flagged and that instantly detects
> you're using a cheeto. »

Ce que ça veut dire concrètement :

- Le cheat n'agissait pas (seulement) par patch mémoire profond, mais **exécutait
  du Lua dans l'état du jeu** en appelant des points d'entrée « GM »
  (`Utils.GmToolUtils`, RPC de combat/interaction, etc.).
- Le serveur **n'a pas de raison légitime** de voir ces commandes venir d'un
  client joueur (elles sont réservées aux outils internes) → signature triviale
  à logger puis flagger.
- C'est exactement ce que faisait **notre portage Shinoko**
  (`features/specter_init.lua`, features `god_mode`, `one_hit`, `multi_hit`,
  `kill_aura`, `catch_aura`, `auto_loot`, `unlimited_dash`, `rate_limit_bypass`,
  `ob_camera`…). → **retiré** (voir « Décision »).

## Facteur n°2 — l'injection en elle-même

Plusieurs utilisateurs ont été sanctionnés **sans avoir activé la moindre
feature** :

| Post | Situation rapportée |
|---|---|
| #322 | « all I did was inject […] got a 2hr ban » |
| #387 | injection de Jon's menu, **sans activer** → 2 h |
| #394 | inject + logout → flag |
| #299 | login + idle quelques minutes → 2 h |
| #396 | « monitoring/flagging that » |

→ Même une DLL inerte a marqué. Notre posture stealth existante (manual-map
`hostch`, worker `is_system`, aucun objet nommé, pas de socket — cf.
`docs/ANTICHEAT.md`) reste **nécessaire**, mais ne suffit pas à elle seule.

## Facteur n°3 — comportement / télémétrie gameplay

Le serveur voit des **écarts statistiques** :

- **Rythme et volume de farm** : le farm de la scène **3007** (1 Prisma + étincelle)
  a été **patché côté serveur le 7 oct.** (#247–#274). Preuve que le serveur
  observe les scènes fréquentées — « the devs log who goes there » (#196, #2857).
- **Multi-Hit** (#285) et **Catch Aura** (#286) cités nommément comme flaggés.
  God Mode + Multi-Hit ensemble aussi (#290, #293).
- **Ressources anormales** : les grosses sommes « 3007 » font « lever un flag »
  à coup sûr (#2212, #2218).
- SCENE IDs : les membres ont dumpé 201 scènes (#186/#192) ; téléporter le joueur
  vers une scène de farm est donc **loggé**.

## Facteur n°4 — temporalité des bans

| Date | Événement |
|---|---|
| 16 sept. – 6 oct. | Le cheat fonctionne ; farm 3007 en masse ; premiers bans perma signalés (#118, 28 sept.) |
| **7 oct. (~18 h)** | Scène **3007 patchée** côté serveur ; les TP vers d'autres scènes cessent de marcher (#247–#274) |
| **8 oct. (~16 h)** | **Vague de suspensions 2 h + mail d'avertissement** (#280–#350), quasi simultanée au retrait (DMCA) du thread concurrent « Jon » |
| 9–10 oct. | Toujours détecté ; 2 h → ban long/permanent (#362, #397) ; **thread fermé** (#408) |

## Politique de sanction observée

- **1ʳᵉ offense** : suspension **2 h** + **mail d'avertissement** in-game (parfois
  simple kick « network error », #315).
- **Récidive** : ban **permanent / 10 ans** (#294, #3795) ; remise du compte à
  zéro signalée (#2564).
- **Serveurs CN/Asie** : 10 ans d'emblée, sans avertissement (#294).

> Notre compte a reçu exactement le palier « 2 h + mail » : c'est le **premier
> avertissement**, pas encore la sanction lourde. D'où l'urgence de retirer la
> cause.

## Ce que l'AC client (NEP2) fait — et ne fait pas

Rappel (détail dans `docs/ANTICHEAT.md`) : `NEP2.dll` + `NEPKernel.sys` forment
une protection kernel multi-couches, mais **sous Wine/Proton le pilote Ring-0
n'est jamais installé** (aucun service créé) → minifilter et scans kernel
**dormants**. Sur le thread, NEP2 est d'ailleurs décrit comme « dead code » par
plusieurs utilisateurs (#196, #205, #2850).

Conclusion : sur **notre** environnement, l'AC kernel ne nous attrape pas — mais
le **serveur** nous voit via les commandes GM et le comportement (facteurs 1 et
3). Les deux plans sont indépendants.

## Notre cas (corrélation)

Observation directe :

- **Avant** le portage Shinoko : notre **Infinite Stamina C++**
  (`lua_console.cpp :: kStaminaInstall`, hook `changeStamina` sur l'instance du
  joueur) et nos **scripts maison de TP coffres** (`scripts/chest-*.lua`) —
  **aucun avertissement**.
- **Depuis** le portage des features Shinoko (`specter_init.lua` v1) : apparition
  des **avertissements** du même type que ceux du thread.

Cohérent avec #401 : nos scripts maison tapent des RPC d'interaction que le
serveur attend d'un joueur normal ; le port Shinoko, lui, emprunte les **GM
commands** flaggées.

## Facteurs de détection — récapitulatif

| # | Facteur | Côté | Statut chez Specter |
|---|---|---|---|
| 1 | Commandes Lua « GM » (`GmToolUtils`, RPC internes) | Serveur | **Supprimé** (features Shinoko retirées) |
| 2 | Injection visible (Ldr, threads user, handles) | Client | Manual-map + worker `is_system` |
| 3 | Comportement anormal (rythme de farm, scènes, montants) | Serveur | Règle de jeu : rester plausible |
| 4 | Multi-Hit / Catch Aura / auras automatiques | Serveur | **Supprimé** |
| 5 | Scene-teleport vers les scènes de farm (3007…) | Serveur | Ne pas cibler ces scènes |
| 6 | `Packet Rate Limit Bypass` (trafic anormal) | Serveur | **Supprimé** |
| 7 | NEP2 kernel (minifilter, scan mémoire) | Client | Dormant sous Wine ; **actif sur Windows natif** |

## Décision et règles

- **Décision** : les 15 features Lua portées de Shinoko sont **retirées**
  (`specter_init.lua` = coque seule ; `features/cheats.cpp` n'expose plus que
  `inf_stamina`, C++ maison). Voir `docs/LUA_CONSOLE.md`.
- **Règles pour la suite** :
  1. Ne pas ré-exposer une feature qui parle aux **GM commands** du jeu.
  2. Préférer les **hooks mémoire profonds** (MethodInfo/`getVtbl` swaps) et les
     scripts qui n'usurpent pas des chemins serveur internes.
  3. Rester **plausible** : pas de montants/rythmes aberrants, pas de farm sur des
     scènes signalées (3007…).
  4. Garder l'injection **furtive** (facteur 2).
  5. Ne pas ajouter de **trafic réseau** ni exfiltrer (la télémétrie NEP observe
     les sockets, cf. `docs/ANTICHEAT.md`).
- **À surveiller** : le passage à la version 1.1, annoncé comme pouvant apporter
  une nouvelle vague (#2516), et tout nouveau `mail` d'avertissement.

> **Analyse du 14 octobre 2026** : voir `docs/ANALYSE-DETECTION.md` pour le
> delta vérifié entre les deux builds, le balayage des 8 541 scripts Lua du jeu,
> et l'inventaire des écritures dans l'état Lua. En résumé : aucune détection
> côté Lua dans le jeu, aucun import réseau dans notre DLL, et le delta
> fonctionnel entre la version jamais signalée et la version signalée est
> intégralement dans la couche Lua.

## Questions ouvertes

- Le flag est-il **unitaire** (une seule commande GM suffit) ou **agrégé** (seuil
  sur une fenêtre) ? Les bans du 8 oct. groupés à ~16 h suggèrent un **batch
  serveur** plus qu'un déclenchement temps réel.
- Le « restart toutes les 15 min » (#392 : « the anti-cheat is slow and
  restarting makes it reboot ») contourne-t-il un **accumulateur client** ? À
  vérifier si l'on veut un jour un mode « propre ».
