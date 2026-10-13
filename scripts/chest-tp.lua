-- chest-tp.lua — coffres NON OUVERTS : liste + TP lerp vers le plus proche.
--
-- Un "coffre non ouvert" est un coffre encore disponible au ramassage. L'état
-- n'est pas dans les marques (toutes ont activeState=2) mais dans le registre
-- du client : pg.game.map.markUnlocker.unlockChunkMap contient l'ensemble des
-- ids de marques "déverrouillées" (= présentes, pas encore ouvertes) pour les
-- chunks chargés autour du joueur. Vérifié en live : les 749 marques Coffre de
-- la scène 3000, 40 déverrouillées, et les N coffres vivants (ClientChest) y
-- sont tous.
--
-- Le TP reprend exactement lerp de tp.cpp : TM.addRepeatTimer qui déplace le
-- joueur par petits pas (forceSetPos), auto-annulé en fin de course, et
-- remplace un éventuel TP en cours.
--
-- Réglages :
local LERP_STEP  = 5.5     -- unités par tick (mêmes valeurs que le menu TP)
local LERP_SPEED = 120     -- ticks par seconde (~660 u/s)
local CHEST_CONFIG = 10506 -- markConfigId "Coffre"
local MAX_LIST   = 40      -- lignes imprimées au plus
local TP_ENABLED = true    -- false = liste seulement

-- Usage : tools/lua.sh -f scripts/chest-tp.lua   (En jeu uniquement)

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

-- -------------------------------------------------------------- recueil coffres
local e = pg.me
if not e or not e.getPosition then
  print('ERROR: pas de joueur')
  return
end

-- Ensemble des marques déverrouillées (non ouvertes) pour les chunks chargés.
local unlocked = {}
local mu = pg.game and pg.game.map and pg.game.map.markUnlocker
if mu and mu.unlockChunkMap then
  for _, cv in pairs(mu.unlockChunkMap) do
    for _, id in pairs(cv or {}) do
      if type(id) == 'number' then
        unlocked[id] = true
      end
    end
  end
end

local pnow = e:getPosition()
local rows = {}

local ok, pts = pcall(SU.getSceneMarkPointData, e.sceneId)
if ok and type(pts) == 'table' then
  for id, p in pairs(pts) do
    if p.markConfigId == CHEST_CONFIG and p.markPosition and unlocked[id] then
      local mp = p.markPosition
      local dx, dy, dz = mp[1] - pnow[1], mp[2] - pnow[2], mp[3] - pnow[3]
      rows[#rows + 1] = {
        id = id,
        x = mp[1], y = mp[2], z = mp[3],
        d = (dx * dx + dy * dy + dz * dz) ^ 0.5,
        name = localize(p.infoTitle) or '',
      }
    end
  end
end

-- Repli : si le registre n'est pas chargé, on se rabat sur les ClientChest
-- vivants (par construction non ouverts).
if #rows == 0 then
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.markBindStaticId then
      local okp, p = pcall(function() return en:getPosition() end)
      if okp and p then
        local dx, dy, dz = p[1] - pnow[1], p[2] - pnow[2], p[3] - pnow[3]
        rows[#rows + 1] = {
          id = en.markBindStaticId,
          x = p[1], y = p[2], z = p[3],
          d = (dx * dx + dy * dy + dz * dz) ^ 0.5,
          name = en.chestValid and 'Coffre' or '',
        }
      end
    end
  end
end

table.sort(rows, function(a, b) return a.d < b.d end)

print('# coffres NON OUVERTS (scene ' .. tostring(e.sceneId) .. ') : ' .. #rows)
for i, r in ipairs(rows) do
  if i > MAX_LIST then
    print(string.format('... (%d de plus)', #rows - MAX_LIST))
    break
  end
  print(string.format('U %s %.2f %.2f %.2f d=%7.1f %s',
                       tostring(r.id), r.x, r.y, r.z, r.d, r.name))
end
print('TOTAL_UNLOCKED=' .. #rows)

-- ------------------------------------------------------------------- TP lerp
if not TP_ENABLED then
  return
end
if #rows == 0 then
  print('NP: aucun coffre non ouvert trouvé')
  return
end

local target = rows[1]
if target.d < 2.0 then
  print('ALREADY_HERE d=' .. string.format('%.1f', target.d) ..
        ' id=' .. tostring(target.id))
  return
end

local V = Vector3
local TM = require('Core.Timer.TimerManager')

-- Annule un éventuel lerp précédent (rendu/TP en cours).
local prev = e.__specter_tp
if prev and prev.tid then
  pcall(function() TM.removeTimer(prev.tid) end)
end
if prev then
  prev.active = false
end

local s = {
  active = true, i = 0, step = LERP_STEP,
  x0 = pnow[1], y0 = pnow[2], z0 = pnow[3],
  x1 = target.x, y1 = target.y, z1 = target.z,
}
e.__specter_tp = s

local dx, dy, dz = target.x - pnow[1], target.y - pnow[2], target.z - pnow[3]
local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
local n = math.ceil(dist / s.step)
if n < 1 then n = 1 end
if n > 20000 then n = 20000 end
s.n = n

local st = s
local tid
tid = TM.addRepeatTimer(1 / LERP_SPEED, function()
  if not st.active then
    return
  end
  st.i = st.i + 1
  local a = st.i / st.n
  if a > 1 then a = 1 end
  local v = V.ForceNew(st.x0 + (st.x1 - st.x0) * a,
                       st.y0 + (st.y1 - st.y0) * a,
                       st.z0 + (st.z1 - st.z0) * a)
  if e.forceSetPos then
    e:forceSetPos(v, true)
  else
    e:setPosition(v)
  end
  if st.i >= st.n then
    st.active = false
    pcall(function() TM.removeTimer(tid) end)
  end
end)
st.tid = tid

print(string.format('TP_TO id=%s d=%6.1f (~%.0f u/s)', tostring(target.id),
                     dist, LERP_STEP * LERP_SPEED))