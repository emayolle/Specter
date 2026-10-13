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
  (rubber-band) ; le max qui tient en jeu est ~5,5 u (défaut 5,5 u) ;
- **Speed** = nombre de pas par seconde. Le timer du jeu ne se déclenche
  qu'~60 fois/s max (mesuré), donc au-delà de ~60 le slider ne change rien ;
  défaut 120 (sature). Le readout affiche la vitesse **réelle** :
  `step × min(speed, fps)`.

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

## Points de TP : onglet Waypoints (Floraisons + cristaux)

L'onglet **Waypoints** du menu (SUPPR) regroupe toutes les cibles de TP nommées
du monde, **classées par zone** :

- les **Floraisons** (*Leyline Flower*), une par zone ;
- les **cristaux** (« Teleportation Array »), plusieurs par zone.

Chaque ligne a un bouton **Teleport** qui réutilise le lerp décrit plus haut.

### Floraisons (fleurs de veine)

Chaque **zone** (grande aire) possède une « Floraison » — la *Leyline Flower*,
fleur de veine qui sert de point d'information / téléport régional (icône
`$UI_Img_Map_Preview_Leylinesflower.png`, à faire bourgeonner avec
l'**Enrichissement**). Une fois bourgeonnée elle attire un groupe d'Aniimo et
fait grossir le « fruit de veine » en son centre.

Source de vérité : les *mark points* de scène du jeu,
`SceneUtils.getSceneMarkPointData(sceneId)` ; les Floraisons y portent
`markType == 26` et exposent `markPosition` = `{x, y, z}` ainsi que
`largeAreaId` = la zone. Elles sortent sous la forme :

```
F <zone> <x> <y> <z>
```

### Cristaux (Teleportation Array)

Les **cristaux** sont les points qui révèlent la carte et servent de TP,
plusieurs par zone. Ils ne forment pas un `markType` à part — ils partagent
`markType 0` avec d'autres marques — mais portent `markConfigId == 10406`
(`infoImage $UI_Img_Map_Preview_TeleportationArray.png`,
`POIIcon $UI_Icon_POI_Explore_Transmit.png`) et un `infoTitle` localisé. Le nom
(dernier champ, il peut contenir des espaces) est résolu via
`Utils.ClientTextUtils.getLocalizationText(infoTitle)` :

```
W <zone> <x> <y> <z> <nom>
```

### Le scan

Les deux familles viennent d'**un seul chunk** du canal TP : il balaie chaque
scène une fois, imprime les lignes `F …` puis `W …`, et termine par
`MARKS_DONE` :

```lua
local SU=require('Common.Utils.SceneUtils')
local CTU=require('Utils.ClientTextUtils')
for sid in pairs(set) do
  local ok,pts=pcall(SU.getSceneMarkPointData,sid)
  if ok and type(pts)=='table' then
    for id,p in pairs(pts) do
      if seen[id] then
      elseif p.markType==26 then
        local mp=p.markPosition
        if mp then print(string.format('F %d %.2f %.2f %.2f',p.largeAreaId or 0,mp[1],mp[2],mp[3])) end
      elseif p.markConfigId==10406 then
        local mp=p.markPosition
        local o,t=pcall(CTU.getLocalizationText,p.infoTitle)
        print(string.format('W %d %.2f %.2f %.2f %s',p.largeAreaId or 0,mp[1],mp[2],mp[3],o and t or ''))
      end
    end
  end
end
print('MARKS_DONE')
```

Un **seul** chunk volontairement : le canal TP ne garde qu'un buffer de résultat,
deux scans demandés coup sur coup s'écraseraient. `set` regroupe la scène
courante, la scène principale, et `3000`, `3003` (les scènes de monde ouvert
connues). Balayer **toutes** les scènes est proscrit : `getSceneMarkPointData`
coûte ~0,7 ms même pour une scène inexistante, soit ~14 s sur toute la plage —
le scan est donc borné à ces quelques scènes (≈ ms).

État du jeu actuel : **15 Floraisons** (14 en scène `3000`, zones `20200`–`21500`
+ 1 en scène `3003`, zone `21600`) et **29 cristaux** (27 en scène `3000` +
2 en scène `3003`), répartis sur 15 zones.

### Persistance

Les deux listes sont persistées séparément, une ligne par point : les Floraisons
dans `/tmp/specter-floraisons.json` (`<zone> <x> <y> <z>`), les cristaux dans
`/tmp/specter-waypoints.json` (`<zone> <x> <y> <z> <nom>`). Elles sont relues au
démarrage ; si l'une manque (ex. `/tmp` vidé au reboot), le menu déclenche **une**
récupération automatique à l'ouverture de l'onglet. Le bouton **Refresh from
game** relit tout à la demande (un seul scan) et réécrit les deux fichiers. Un
scan qui ne rapporte rien (scène sans marque) ne remplace pas la liste en cache.

## Limites connues

- Le TP est **côté client** (pas de RPC serveur). Le lerp fait accepter le
  déplacement, mais une cible **dans une autre scène** ne chargera pas la scène :
  le TP reste intra-scène.
- Un TP ne fonctionne qu'**en jeu** (la pompe n'existe que si
  `LuaManager.CommonUpdate` tourne). Hors monde, la position affiche
  « position unknown ».
- Le TP dure le temps du trajet (~1 s pour 150 u), pas instantané.
- Les **Floraisons** sont identifiées par l'`id` de zone (grande aire) : le jeu
  n'expose pas de nom lisible côté client (`getSceneName` renvoie l'id, les
  entrées d'aire sont des placeholders `区域_<id>`). Le scan ne couvre que les
  scènes de monde ouvert connues (`3000`, `3003`) : une scène de monde ouverte
  ajoutée par un patch nécessiterait d'étendre `kFloraScenes` (feature `tp.cpp`).
