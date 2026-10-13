-- chest-open.lua — TP lerp vers le coffre NON OUVERT le plus proche, puis
-- OUVERTURE automatique (interaction).
--
-- C'est chest-tp.lua + l'interaction. Déroulé :
--   1. coffres non ouverts = marques Coffre (cfg 10506) dont l'id est dans le
--      registre "déverrouillé" du client (pg.game.map.markUnlocker
--      .unlockChunkMap) — non ouverts = disponibles, vérifié en live ;
--   2. TP en lerp (TM.addRepeatTimer) vers le plus proche, comme tp.cpp ;
--   3. à l'arrivée, on cherche l'entité ClientChest liée (markBindStaticId)
--      puis son unité d'interaction dans pg.game.interaction.unitMap, et on
--      déclenche pg.game.interaction:doUnitInteractive(unit) — exactement le
--      chemin de la touche F. Le serveur valide, le coffre s'ouvre (l'entité
--      disparaît, la récompense tombe). Vérifié en live.
--
-- Cache local "déjà ouvert" : dès que doUnitInteractive aboutit sans erreur,
-- l'id de la marque est marqué ouvert dans pg.me.__specterChestOpened (champ
-- d'instance : persiste entre les chunks, JAMAIS réinitialisé). La liste des
-- "non ouverts" ne dépend plus du despawn/registre lent. Garde-fous : une
-- entité vivante repasse l'id en disponible (respawn) ; et seuls les VRAIS
-- coffres sont traités (marques cfg 10506 — pas les Ambre lumin / ramassages
-- / Aniipods, même si leur entité a isChest=true).
--
-- Réglages :
local LERP_STEP  = 5.5      -- unités par tick (mêmes valeurs que le menu TP)
local LERP_SPEED = 120      -- ticks par seconde (~660 u/s)
local CHEST_CONFIG = 10506  -- markConfigId "Coffre"
local MAX_LIST   = 40       -- lignes imprimées au plus
local INTERACT_TYPE = 1     -- interactionType du coffre (actif / ENT_FUNC)
local TRY_SECONDS = 5       -- fenêtre pour trouver l'entité + son unité
local OPEN_ENABLED = true   -- false = TP seulement

-- Usage : tools/lua.sh -f scripts/chest-open.lua   (En jeu uniquement)

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

local pnow = e:getPosition()

-- ------------------------------------------------ cache local "déjà ouverts"
-- (v. commentaire d'en-tête) — champ d'instance, JAMAIS réinitialisé s'il
-- existe déjà (sinon on perdrait la liste d'une exécution à l'autre).
local CACHE_KEY = '__specterChestOpened'
local SEED_RADIUS = 4
local opened = pg.me[CACHE_KEY]
if type(opened) ~= 'table' then
  opened = {}
  pg.me[CACHE_KEY] = opened
end

local function liveChestIds()
  local s = {}
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.markBindStaticId then
      s[en.markBindStaticId] = true
    end
  end
  return s
end

local function sieve(rowsIn)
  local liveNow = liveChestIds()
  local out = {}
  for _, r in ipairs(rowsIn) do
    if opened[r.id] and not liveNow[r.id] then
      -- en cache => déjà ouvert, on saute
    else
      if opened[r.id] then
        opened[r.id] = nil -- entité vivante => disponible à nouveau
      end
      out[#out + 1] = r
    end
  end
  return out
end

local function seedNear(rowsIn)
  local liveNow = liveChestIds()
  for _, r in ipairs(rowsIn) do
    if not opened[r.id] and r.d <= SEED_RADIUS and not liveNow[r.id] then
      opened[r.id] = true
      print(string.format('SEED_OPEN id=%s d=%.1f', tostring(r.id), r.d))
    end
  end
end

local nCache = 0
for _ in pairs(opened) do nCache = nCache + 1 end

-- Que les VRAIS coffres : on restreint aux marques de cfg Coffre (10506) —
-- les entités "isChest" couvrent aussi ramassages / Ambre lumin / Aniipods.
local markCfg = {}
local okm, mpts = pcall(SU.getSceneMarkPointData, e.sceneId)
if okm and type(mpts) == 'table' then
  for mid, mp in pairs(mpts) do
    markCfg[mid] = mp.markConfigId
  end
end
local function isCoffre(id)
  return type(id) == 'number' and markCfg[id] == CHEST_CONFIG
end

-- Priorité 1 : entités ClientChest VIVANTES (par construction non ouvertes, et
-- surtout le registre unlockChunkMap n'oublie pas les coffres déjà ouverts —
-- une entité absente est le seul signal fiable à distance de TOUCHER).
local byLive = {}
for _, en in pairs(pg.getEntities() or {}) do
  if en.isChest and en.chestValid and isCoffre(en.markBindStaticId) then
    local okp, p = pcall(function() return en:getPosition() end)
    if okp and p then
      local dx, dy, dz = p[1] - pnow[1], p[2] - pnow[2], p[3] - pnow[3]
      byLive[#byLive + 1] = {
        id = en.markBindStaticId,
        x = p[1], y = p[2], z = p[3],
        d = (dx * dx + dy * dy + dz * dz) ^ 0.5,
        name = localize(en.configName) or 'Coffre',
      }
    end
  end
end
table.sort(byLive, function(a, b) return a.d < b.d end)
byLive = sieve(byLive)

-- Priorité 2 : marques Coffre (cfg 10506) déverrouillées (registre).
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
seedNear(rows)
rows = sieve(rows)
table.sort(rows, function(a, b) return a.d < b.d end)

local list = #byLive > 0 and byLive or rows
local source = #byLive > 0 and 'entités vivantes' or 'registre déverrouillé'

print('# coffres NON OUVERTS (scene ' .. tostring(e.sceneId) .. ', source: '
      .. source .. ') : ' .. #list
      .. '  [cache déjà ouverts: ' .. nCache .. ']')
for i, r in ipairs(list) do
  if i > MAX_LIST then
    print(string.format('... (%d de plus)', #list - MAX_LIST))
    break
  end
  print(string.format('U %s %.2f %.2f %.2f d=%7.1f %s',
                       tostring(r.id), r.x, r.y, r.z, r.d, r.name))
end
print('TOTAL_UNLOCKED=' .. #list)

if #list == 0 then
  print('NP: aucun coffre non ouvert trouvé')
  return
end

local target = list[1]
local arrived = target.d < 2.0

if not arrived then
  -- TP lerp (annule un éventuel lerp en cours).
  local TM = require('Core.Timer.TimerManager')
  local V = Vector3
  local prev = e.__specter_tp
  if prev and prev.tid then
    pcall(function() TM.removeTimer(prev.tid) end)
  end
  if prev then
    prev.active = false
  end
  local st = {
    active = true, i = 0, step = LERP_STEP,
    x0 = pnow[1], y0 = pnow[2], z0 = pnow[3],
    x1 = target.x, y1 = target.y, z1 = target.z,
  }
  e.__specter_tp = st
  local dx, dy, dz = target.x - pnow[1], target.y - pnow[2],
                     target.z - pnow[3]
  local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
  local n = math.ceil(dist / st.step)
  if n < 1 then n = 1 end
  if n > 20000 then n = 20000 end
  st.n = n
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
end

-- ------------------------------------------------------ ouverture automatique
if not OPEN_ENABLED then
  print('ARRIVED=' .. tostring(arrived))
  return
end

-- On attend l'arrivée puis on cherche l'entité du coffre puis son unité
-- d'interaction, et on déclenche l'interaction (équivalent F).
local it = pg.game and pg.game.interaction
if not it then
  print('NO_INTERACTION_SYSTEM')
  return
end

local tries = 0
local TM = require('Core.Timer.TimerManager')
local marker = target.id
local markx, marky, markz = target.x, target.y, target.z
local poll

poll = TM.addRepeatTimer(0.15, function()
  -- pas encore arrivé ?
  if not arrived and e.__specter_tp and e.__specter_tp.active then
    return
  end
  -- 1) l'entité ClientChest liée à la marque
  local ent
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.markBindStaticId == marker then
      ent = en
      break
    end
  end
  -- 2) son unité d'interaction (unitMap[type] -> liste d'unités)
  local unit
  if ent then
    local byType = it.unitMap and it.unitMap[INTERACT_TYPE]
    if type(byType) == 'table' then
      for _, u in pairs(byType) do
        if type(u) == 'table' and u.globalId == ent.id then
          unit = u
          break
        end
      end
    end
  end
  if not unit then
    tries = tries + 1
    if tries * 0.15 > TRY_SECONDS then
      -- Plus d'entité ni d'unité : si on est collé au point visé, c'est un
      -- coffre du registre dont l'entité est morte/absent (désync) => on le
      -- marque ouvert pour ne plus retenter.
      local okp, p = pcall(function() return e:getPosition() end)
      local d0 = okp and p and
        ((p[1]-markx)^2 + (p[2]-marky)^2 + (p[3]-markz)^2) ^ 0.5
      if d0 and d0 <= 3 then
        opened[marker] = true
        print('OPEN_NO_UNIT -> marqué ouvert (ent=' .. tostring(ent ~= nil)
              .. ')')
      end
      pcall(function() TM.removeTimer(poll) end)
    end
    return
  end
  pcall(function() TM.removeTimer(poll) end)
  local okr, res = pcall(function() return it:doUnitInteractive(unit) end)
  if okr then
    -- Succès (appel exécuté) : on passe l'id en "ouvert" tout de suite, sans
    -- attendre le despawn/la purge du registre.
    opened[marker] = true
    pg.me.__specterLastOpen = { id = marker, t = (os and os.time and os.time()) or 0 }
  end
  print('OPEN_INTERACT ok=' .. tostring(okr) .. ' res=' .. tostring(res))
end)