# Téléportation — positions sauvegardées + TP

L'onglet **Teleport** du menu (SUPPR) permet de sauvegarder la position du
joueur et d'y revenir en un clic. Tout passe par le pont Lua : le panneau
(thread de rendu) ne touche jamais au `lua_State` lui-même.

## Levier Lua

L'entité joueur est `pg.me` (repli : la première entrée de
`pg.global.actorMgr.uid2Ent`). Elle expose :

- `ent:getPosition()` → table `{x, y, z, space}` (le 4ᵉ champ est l'espace/scène) ;
- `ent:forceSetPos({x,y,z}, true)` → déplace le personnage (`setPosition` en repli).

Un saut **unique** vers la cible est rejeté par le serveur (mouvement
autoritaire) : le personnage est ramené à sa position d'origine (rubber-band).
Le TP se fait donc en **lerp** : on interpole position courante → cible et on
applique de petits pas à chaque tick du jeu. Le serveur accepte ces petits
deltas et la position tient.

Le module `features/tp.{h,cpp}` construit deux chunks :

```lua
-- lecture (affiche "P x y z space")
local e=pg.me
...
local p=e:getPosition()
if p then print(string.format('P %.2f %.2f %.2f %d', p[1],p[2],p[3],p[4] or 0)) end

-- écriture : lerp piloté par le timer du jeu
local e=pg.me
...
local TM=require('Core.Timer.TimerManager')
local tid
tid=TM.addRepeatTimer(0.01,function()
  if not s.active then return end
  s.i=s.i+1
  local a=s.i/s.n; if a>1 then a=1 end
  local v=V.ForceNew(s.x0+(s.x1-s.x0)*a, ...)
  if e.forceSetPos then e:forceSetPos(v,true) else e:setPosition(v) end
  if s.i>=s.n then s.active=false pcall(function() TM.removeTimer(tid) end) end
end)
```

Le pas et la cadence sont **réglables depuis l'onglet Teleport** (sliders
« Step size (u) » et « Speed (steps/s) ») et persistés avec les slots :

- **Step size** = distance d'un petit TP. Trop grand → le serveur refuse
  (rubber-band) ; défaut 2 u ;
- **Speed** = nombre de pas par seconde (borné par la cadence d'image) ;
  défaut 60 pas/s.

La vitesse effective (affichée « => X u/s ») est `step × speed`. La boucle est
**auto-limitée** (flag `active`) et un nouveau TP annule le précédent : rien ne
réassène une ancienne position.

## Canal dédié (pourquoi pas la console)

Le sondage de position tourne en arrière-plan (toutes les ~0,75 s tant que
l'onglet est visible) : le faire passer par le canal de la console polluerait le
journal Lua et surtout `out.txt` / le compteur `#seq=`, ce qui casserait
`tools/lua.sh`.

`features/lua_console` expose donc un **second canal** :

| Fonction | Thread | Rôle |
|---|---|---|
| `tp_submit(code, len)` | thread de rendu | met une chunk en attente |
| `tp_take_result(out, cap, ok)` | thread de rendu | récupère le dernier résultat du canal TP |

La pompe exécute la chunk TP (`run_chunk_to(... , store_tp_result)`) : le
résultat part dans un **tampon séparé** et n'est mirroré que sur le pipe de logs.
La console, `out.txt` et le compteur `#seq=` restent intacts.

## Persistance

Les slots sont écrits dans `/tmp/specter-tp.json` (vu comme
`Z:\tmp\specter-tp.json` sous Wine), au même endroit que le remplissage de log et
le canal CLI — **jamais** dans le dossier du jeu ni le préfixe Wine. Format, une
ligne par slot :

```
<nom> <x> <y> <z> <space>
```

Les noms sont filtrés (`[A-Za-z0-9_-]`, le reste devient `_`) car le format est
séparé par des espaces. Le fichier est relu au démarrage de l'overlay, donc les
positions survivent à un changement de scène, un relog **et** un redémarrage du
jeu (la DLL est ré-injectée à chaque lancement).

## Limites connues

- Le TP est **côté client** (pas de RPC serveur). Le lerp fait accepter le
  déplacement, mais une cible **dans une autre scène** ne chargera pas la scène :
  le TP reste intra-scène.
- Un TP ne fonctionne qu'**en jeu** (la pompe n'existe que si
  `LuaManager.CommonUpdate` tourne). Hors monde, la position affiche
  « position unknown ».
- Le TP dure le temps du trajet (~1 s pour 150 u), pas instantané.
