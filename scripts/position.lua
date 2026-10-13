-- position.lua — où suis-je ?
--
-- Affiche la scène, la position monde, la rotation et l'espace du joueur.
-- Lecture seule.
--
-- Usage : tools/lua.sh -f scripts/position.lua

local me = pg.me
if not me then
  print('! pas de joueur (le pont Lua ne répond qu\'en jeu)')
  return
end

-- pg.playerPos / pg.playerRot sont les copies "propres" publiées par le jeu
-- ({1,2,3} = x,y,z et {4} = espace) ; on retombe sur getPosition() si besoin.
local p = pg.playerPos or me:getPosition()
local r = pg.playerRot

print(string.format('scene=%s  pos=%.2f %.2f %.2f  space=%s',
  tostring(me.sceneId), p[1], p[2], p[3], tostring(p[4])))
if r then
  print(string.format('rot=%.4f %.4f %.4f %.4f', r[1], r[2], r[3], r[4]))
end
print(string.format('id=%s  uid=%s', tostring(me.id), tostring(me.uid)))
