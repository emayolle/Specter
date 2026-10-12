# Téléportation — positions sauvegardées + TP

L'onglet **Teleport** du menu (SUPPR) permet de sauvegarder la position du
joueur et d'y revenir en un clic. Tout passe par le pont Lua : le panneau
(thread de rendu) ne touche jamais au `lua_State` lui-même.

## Levier Lua

L'entité joueur expose déjà tout ce qu'il faut :

- `ent:getPosition()` → table `{x, y, z, space}` (le 4ᵉ champ est l'espace/scène) ;
- `ent:setPosition({x, y, z})` → déplace le personnage (validé en jeu).

Le module `features/tp.{h,cpp}` construit deux chunks :

```lua
-- lecture (affiche "P x y z space")
local ent
for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do ent=_v break end
if not ent then return end
local p=ent:getPosition()
if p then print(string.format('P %.2f %.2f %.2f %d', p[1],p[2],p[3],p[4] or 0)) end

-- écriture
ent:setPosition({x, y, z})
```

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

- Le TP utilise `setPosition` **côté client**. Sur un serveur qui revalide les
  déplacements, le personnage peut être ramené (rubber-band). Si ça arrive, la
  suite est le chemin GM du jeu (`GmToolUtils.execGmCmd` / `teleportToScene`),
  déjà identifié.
- Un TP ne fonctionne qu'**en jeu** (la pompe n'existe que si
  `LuaManager.CommonUpdate` tourne). Hors monde, la position affiche
  « position unknown ».
