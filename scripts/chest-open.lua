-- chest-open.lua — ouvre les coffres NON OUVERTS, ENCHAÎNÉ.
--
-- Déroulé par cycle :
--   1. coffres non ouverts = marques Coffre (cfg 10506) du registre
--      "déverrouillé" (pg.game.map.markUnlocker.unlockChunkMap) + entités
--      vivantes ClientChest (préférées quand présentes) ;
--   2. TP en lerp vers le plus proche (TM.addRepeatTimer, comme tp.cpp) ;
--   3. à l'arrivée, on cherche l'entité puis son unité d'interaction dans
--      pg.game.interaction.unitMap[1] et on déclenche
--      pg.game.interaction:doUnitInteractive(unit) (chemin de la touche F) ;
--   4. dès que l'interaction aboutit, l'id est marqué "ouvert" dans le cache
--      local (pg.me.__specterChestOpened) et on enchaîne immédiatement sur le
--      coffre suivant — SANS attendre l'animation de despawn ni la purge du
--      registre (l'un et l'autre sont lents ; le cache est la source de
--      vérité, l'entité d'un coffre déjà ouvert peut encore traîner avec
--      chestValid=true, elle ne fait plus "repasser" l'id en disponible).
--
-- Réglages :
local LERP_STEP  = 5.5      -- unités par tick (mêmes valeurs que le menu TP)
local LERP_SPEED = 120      -- ticks par seconde (~660 u/s)
local CHEST_CONFIG = 10506  -- markConfigId "Coffre"
local MAX_LIST   = 40       -- lignes imprimées au plus
local INTERACT_TYPE = 1     -- interactionType du coffre (actif / ENT_FUNC)
local TRY_SECONDS = 5       -- fenêtre pour trouver l'entité + son unité
local WAIT_AFTER_TP = 0.2   -- s, à attendre APRÈS le TP avant d'interagir
local CHAIN_OPENS = 3       -- nb de coffres à ouvrir par exécution (0 = tout)
local BREATH = 0.6          -- s, pause entre deux ouvertures
local OPEN_ENABLED = true   -- false = TP seulement (vers le plus proche)

-- Usage : tools/lua.sh -f scripts/chest-open.lua   (En jeu uniquement)

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')
local TM  = require('Core.Timer.TimerManager')
local V   = Vector3

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

local e = pg.me
if not e or not e.getPosition then
  print('ERROR: pas de joueur')
  return
end

-- ------------------------------------------------- cache local "déjà ouverts"
-- Champ d'instance sur le joueur : persiste entre les chunks, JAMAIS
-- réinitialisé s'il existe déjà. Source de vérité pour la liste des non
-- ouverts. Reset si besoin : pg.me.__specterChestOpened = nil
local CACHE_KEY = '__specterChestOpened'
local SEED_RADIUS = 4   -- u : coffre du registre très proche SANS entité
                        -- vivante => considéré comme déjà ouvert (désync)
local opened = pg.me[CACHE_KEY]
if type(opened) ~= 'table' then
  opened = {}
  pg.me[CACHE_KEY] = opened
end

-- Que les VRAIS coffres (markConfigId 10506) : isChest couvre aussi
-- ramassages / Ambre lumin / Aniipods.
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

local function liveChestIds()
  local s = {}
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.markBindStaticId then
      s[en.markBindStaticId] = true
    end
  end
  return s
end

-- ----------------------------------------------------------- collecte cible
local function collectTargets()
  local pnow = e:getPosition()

  -- Priorité 1 : entités ClientChest VIVANTES donc disponibles (ouvertes par
  -- construction). Un coffre déjà ouvert par nous est caché par `opened`
  -- ci-dessous, même si son entité traîne encore (despawn lent).
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
  -- Réconciliation : un coffre du registre quasi-collé au joueur SANS entité
  -- vivante est déjà ouvert (registre pas purgé en temps réel).
  local liveNow = liveChestIds()
  for _, r in ipairs(rows) do
    if not opened[r.id] and r.d <= SEED_RADIUS and not liveNow[r.id] then
      opened[r.id] = true
    end
  end

  -- Filtre cache : les ids déjà ouverts par nous ne réapparaissent jamais par
  -- la simple présence d'une entité (despawn lent) — source de vérité.
  local function dropCached(listIn)
    local out = {}
    for _, r in ipairs(listIn) do
      if not opened[r.id] then
        out[#out + 1] = r
      end
    end
    return out
  end
  byLive = dropCached(byLive)
  rows = dropCached(rows)

  return byLive, rows
end

-- ------------------------------------------------------------------ machine
local opensDone = 0
local curTarget
local curArrived
local curTp
local curPoll
local chainActive = true

local function stopPoll()
  if curPoll then
    pcall(function() TM.removeTimer(curPoll) end)
    curPoll = nil
  end
end

local function cancelTp()
  if curTp then
    if curTp.tid then
      pcall(function() TM.removeTimer(curTp.tid) end)
    end
    curTp.active = false
    curTp = nil
  end
end

local function finish(reason)
  chainActive = false
  stopPoll()
  cancelTp()
  pg.me.__specterOpenState = {
    done = opensDone,
    lastId = pg.me.__specterLastOpen and pg.me.__specterLastOpen.id or nil,
    finish = reason,
    at = (os and os.time and os.time()) or 0,
  }
end

-- Choisit la cible, TP-lerp si besoin, puis lance le polling d'interaction.
local startCycle

local function onOpened()
  opensDone = opensDone + 1
  opened[curTarget.id] = true
  pg.me.__specterLastOpen = { id = curTarget.id, t = (os and os.time and os.time()) or 0 }
  pg.me.__specterOpenState = { done = opensDone, lastId = curTarget.id }
  -- petite pause (laisse l'ouverture se poser) puis cible suivante
  local tid
  tid = TM.addRepeatTimer(BREATH, function()
    pcall(function() TM.removeTimer(tid) end)
    if chainActive then
      startCycle()
    end
  end)
end

local function startPoll()
  stopPoll()
  local tries = 0
  local marker = curTarget.id
  local mkx, mky, mkz = curTarget.x, curTarget.y, curTarget.z
  local waitTicks = math.max(0, math.floor(WAIT_AFTER_TP / 0.15))
  local waited = 0
  curPoll = TM.addRepeatTimer(0.15, function()
    -- pas encore arrivé ?
    if not curArrived and curTp and curTp.active then
      return
    end
    -- attendre la fenêtre configurée APRÈS le TP avant d'interagir
    if waited < waitTicks then
      waited = waited + 1
      return
    end
    -- 1) l'entité liée à la marque
    local ent
    for _, en in pairs(pg.getEntities() or {}) do
      if en.isChest and en.markBindStaticId == marker then
        ent = en
        break
      end
    end
    -- 2) son unité d'interaction
    local it = pg.game and pg.game.interaction
    local unit
    if ent and it and it.unitMap then
      local byType = it.unitMap[INTERACT_TYPE]
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
        -- entité morte/absente : si on est collé au point, c'est un coffre du
        -- registre déjà ouvert (désync) => on le marque et on enchaîne
        local okp, p = pcall(function() return e:getPosition() end)
        local d0 = okp and p and
          ((p[1]-mkx)^2 + (p[2]-mky)^2 + (p[3]-mkz)^2) ^ 0.5
        if d0 and d0 <= 3 then
          opened[marker] = true
        end
        if chainActive then
          startCycle()
        end
      end
      return
    end
    stopPoll()
    local okr, res = pcall(function() return it:doUnitInteractive(unit) end)
    print('OPEN_INTERACT ok=' .. tostring(okr) .. ' id=' .. tostring(marker))
    pg.me.__specterOpenState = pg.me.__specterOpenState or {}
    pg.me.__specterOpenState.lastInteractOk = okr
    if okr then
      onOpened()
    else
      -- interaction en échec : on s'arrête (évite une boucle sur la même cible)
      finish('OPEN_ERR')
    end
  end)
end

startCycle = function()
  if not chainActive or (CHAIN_OPENS > 0 and opensDone >= CHAIN_OPENS) then
    finish('OK')
    return
  end
  local byLive, rows = collectTargets()
  local list = #byLive > 0 and byLive or rows
  if #list == 0 then
    finish('NP')
    return
  end
  local t = list[1]
  local pnow = e:getPosition()
  local dx, dy, dz = t.x - pnow[1], t.y - pnow[2], t.z - pnow[3]
  local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
  curTarget = t
  curArrived = dist < 2.0
  if opensDone > 0 then
    print(string.format('CHAIN %d -> id=%s d=%6.1f',
                        opensDone + 1, tostring(t.id), dist))
  end
  if not curArrived then
    cancelTp()
    local st = {
      active = true, i = 0, step = LERP_STEP,
      x0 = pnow[1], y0 = pnow[2], z0 = pnow[3],
      x1 = t.x, y1 = t.y, z1 = t.z,
    }
    e.__specter_tp = st
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
    curTp = st
    print(string.format('TP_TO id=%s d=%6.1f (~%.0f u/s)',
                        tostring(t.id), dist, LERP_STEP * LERP_SPEED))
  end
  startPoll()
end

-- ---------------------------------------------------------- lancement
-- Liste initiale (affichage synchrone) + démarrage de la chaîne.
local c0 = pg.me[CACHE_KEY]
local nCache = 0
if type(c0) == 'table' then
  for _ in pairs(c0) do nCache = nCache + 1 end
end

local byLive0, rows0 = collectTargets()
local list0 = #byLive0 > 0 and byLive0 or rows0
local source0 = #byLive0 > 0 and 'entités vivantes' or 'registre déverrouillé'

print('# coffres NON OUVERTS (scene ' .. tostring(e.sceneId) .. ', source: '
      .. source0 .. ') : ' .. #list0
      .. '  [cache déjà ouverts: ' .. nCache .. ']')
for i, r in ipairs(list0) do
  if i > MAX_LIST then
    print(string.format('... (%d de plus)', #list0 - MAX_LIST))
    break
  end
  print(string.format('U %s %.2f %.2f %.2f d=%7.1f %s',
                       tostring(r.id), r.x, r.y, r.z, r.d, r.name))
end
print('TOTAL_UNLOCKED=' .. #list0)

if not OPEN_ENABLED then
  -- mode TP seulement : on se pose sur le plus proche, sans ouvrir
  if #list0 == 0 then
    print('NP: aucun coffre non ouvert trouvé')
    return
  end
  local t = list0[1]
  local pnow = e:getPosition()
  local dx, dy, dz = t.x - pnow[1], t.y - pnow[2], t.z - pnow[3]
  local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
  if dist < 2.0 then
    print('ALREADY_HERE id=' .. tostring(t.id))
    return
  end
  local st = {
    active = true, i = 0, step = LERP_STEP,
    x0 = pnow[1], y0 = pnow[2], z0 = pnow[3],
    x1 = t.x, y1 = t.y, z1 = t.z,
  }
  e.__specter_tp = st
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
  print(string.format('TP_TO id=%s d=%6.1f (~%.0f u/s)',
                      tostring(t.id), dist, LERP_STEP * LERP_SPEED))
  return
end

if #list0 == 0 then
  print('NP: aucun coffre non ouvert trouvé')
  return
end

if CHAIN_OPENS > 0 then
  print('CHAIN_OPENS=' .. CHAIN_OPENS)
end
startCycle()