-- chest-open.lua — ouvre les coffres NON OUVERTS, ENCHAÎNÉ.
--
-- Déroulé par cycle :
--   1. coffres non ouverts = marques Coffre (cfg 10506) du registre
--      "déverrouillé" (pg.game.map.markUnlocker.unlockChunkMap) + entités
--      vivantes ClientChest (préférées quand présentes) ;
--   2. TP vers le plus proche, via `specter.tp.here` — PAS un lerp local ;
--   3. à l'arrivée, on cherche l'entité puis son unité d'interaction dans
--      pg.game.interaction.unitMap[1] et on déclenche
--      pg.game.interaction:doUnitInteractive(unit) (chemin de la touche F) ;
--   4. dès que l'interaction aboutit, l'id est marqué "ouvert" dans le cache
--      et on enchaîne immédiatement — SANS attendre l'animation de despawn ni
--      la purge du registre (l'un et l'autre sont lents ; le cache est la
--      source de vérité).
--
-- LE TP EST CELUI DE L'OVERLAY.
--
-- Cette version utilisait son propre lerp, écrit DEUX fois dans le fichier,
-- 5.5/120 en dur — donc les réglages de l'onglet Teleport ne lui
-- parlaient pas. Et son état de déplacement était sur `e.__specter_tp`, ce qui
-- ne cohabite pas avec `specter.store.tpMove` que `specter.tp.here` utilise :
-- deux timers indépendants pouvait déplacer le joueur en même temps.
--
-- Maintenant : `specter.tp.here(x, y, z)`, et l'arrivée se detecte par la
-- distance — ce que le script faisait déjà pour désynchroniser.
--
-- AUCUN NOM À NOUS SUR UNE TABLE DU JEU.
--
-- Le cache des coffres ouverts et l'état de la chaîne vivent dans
-- `specter.store.chests`. Ils étaient sur `pg.me.__specterChestOpened`,
-- `pg.me.__specterOpenState` et `pg.me.__specterLastOpen` : visibles par
-- quiconque parcourt l'entité, et disparus au relog.
--
-- Réglages :
local CHAIN_OPENS  = 10      -- nb de coffres à ouvrir par exécution (0 = tout)
local BREATH       = 1.6     -- s, pause entre deux ouvertures
local WAIT_AFTER_TP = 0.8    -- s, à attendre APRÈS le TP avant d'interagir
local TRY_SECONDS  = 5       -- fenêtre pour trouver l'entité + son unité
local INTERACT_TYPE = 1      -- interactionType du coffre (actif / ENT_FUNC)
local MAX_LIST     = 40      -- lignes imprimées au plus
local ARRIVED_D    = 2.5     -- u : on considère arrivé en dessous
local OPEN_ENABLED = true    -- false = TP seulement (vers le plus proche)
-- Utiliser le registre des marques quand AUCUNE entité n'est chargée autour.
-- OFF par defaut, et mesure a l'appui : en scene 3000, 194 marques
-- deverrouillees pour 4 coffres reellement charges, et AUCUNE marque ne
-- correspondait a une entite. Le registre sert a savoir QUOI il y a dans la
-- scene, pas a ou aller maintenant.
local USE_REGISTRY = false

-- Usage : tools/lua.sh -f scripts/chest-open.lua   (En jeu uniquement)
--
-- Pour arrêter une chaîne déjà lancée, depuis un autre chunk :
--     specter.store.chests.cancel = true

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')
local TM  = require('Core.Timer.TimerManager')

-- ---------------------------------------------------------- garde : le TP existe
if type(specter.tp) ~= 'table' or type(specter.tp.here) ~= 'function' then
  print('ERROR: specter.tp.here absent. scripts/init.lua ne tourne pas ?')
  return
end

local function tpHere(x, y, z)
  -- Le pas et la vitesse viennent de l'onglet Teleport (specter.var.tp_step /
  -- tp_speed), pas de constantes ici : c'est le meme déplacement que celui du
  -- menu, donc les memes réglages.
  specter.tp.here(x, y, z)
end

local function tpStop()
  if specter.tp and type(specter.tp.stop) == 'function' then
    pcall(specter.tp.stop)
  end
end

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

local function maPosition()
  local ok, p = pcall(function() return e:getPosition() end)
  if ok and p then return p end
  return nil
end

local function distance(p, x, y, z)
  return ((p[1] - x) ^ 2 + (p[2] - y) ^ 2 + (p[3] - z) ^ 2) ^ 0.5
end

-- ------------------------------------------------------------------ notre état
local ETAT = specter.store.chests
if type(ETAT) ~= 'table' then
  ETAT = {}
  specter.store.chests = ETAT
end

-- Un run precedent peut avoir laisse des timers si le jeu a crashé ou si le
-- joueur s'est déconnecté. On les récupère avant tout, sinon `running'
-- resterait vrai indéfiniment et personne ne pourrait plus relancer.
local function nettoyerTimers()
  for _, nom in ipairs({ 'poll', 'breath' }) do
    local t = ETAT[nom]
    if t then
      pcall(function() TM.removeTimer(t) end)
      ETAT[nom] = nil
    end
  end
end
nettoyerTimers()

-- Un run peut mourir SANS laisser le verrou : le jeu a crashé, le joueur s'est
-- deconnecté, une erreur a tue un timer. Dans ce cas il ne reste aucun timer
-- vivant, et refuser indefiniment serait la seule facon de ne jamais relancer.
-- On recycle donc un verrou sans timer plutot que de coincer le script.
if ETAT.running and not ETAT.poll and not ETAT.breath then
  print('ETAT: chaine orpheline sans timer, on repart')
  ETAT.running = false
end

if ETAT.running then
  print('ERROR: une chaine est deja en cours.')
  print('       Pour l arreter :  specter.store.chests.cancel = true')
  return
end

ETAT.running = true
ETAT.cancel = false
ETAT.done = 0
local opened = type(ETAT.opened) == 'table' and ETAT.opened or {}
ETAT.opened = opened

-- Que les VRAIS coffres (markConfigId 10506) : isChest couvre aussi
-- ramassages / Ambre lumin / Aniipods.
local CHEST_CONFIG = 10506
local SEED_RADIUS = 4   -- u : coffre du registre très proche SANS entité
                        -- vivante => considéré comme déjà ouvert (désync)
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
  local pnow = maPosition()
  if not pnow then return {}, {} end

  -- Priorité 1 : entités ClientChest VIVANTES donc disponibles (ouvertes par
  -- construction). Un coffre déjà ouvert par nous est caché par `opened`
  -- ci-dessous, même si son entité traîne encore (despawn lent).
  local byLive = {}
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.chestValid and isCoffre(en.markBindStaticId) then
      local okp, p = pcall(function() return en:getPosition() end)
      if okp and p then
        byLive[#byLive + 1] = {
          id = en.markBindStaticId,
          x = p[1], y = p[2], z = p[3],
          d = distance(pnow, p[1], p[2], p[3]),
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
        rows[#rows + 1] = {
          id = id,
          x = mp[1], y = mp[2], z = mp[3],
          d = distance(pnow, mp[1], mp[2], mp[3]),
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

  -- Filtre cache : les ids déjà ouverts ne réapparaissent jamais par la seule
  -- présence d'une entité (despawn lent) — c'est la source de vérité.
  local function dropCached(listIn)
    local out = {}
    for _, r in ipairs(listIn) do
      if not opened[r.id] then
        out[#out + 1] = r
      end
    end
    return out
  end

  return dropCached(byLive), dropCached(rows)
end

-- ------------------------------------------------------------------ machine
local curTarget
local chainActive = true

local function finish(reason)
  chainActive = false
  nettoyerTimers()
  tpStop()
  ETAT.running = false
  ETAT.finish = reason
  ETAT.done = ETAT.done or 0
  print('FIN ' .. tostring(reason) .. ' ouverts=' .. tostring(ETAT.done))
end

-- Choisit la cible, lance le TP si besoin, puis le polling d'interaction.
local startCycle

local function onOpened()
  ETAT.done = (ETAT.done or 0) + 1
  opened[curTarget.id] = true
  ETAT.lastId = curTarget.id
  local n = ETAT.done
  ETAT.breath = TM.addRepeatTimer(BREATH, function()
    nettoyerTimers()
    if chainActive then
      startCycle()
    end
  end)
  print(string.format('CHAIN %d ok id=%s', n, tostring(curTarget.id)))
end

local function startPoll()
  nettoyerTimers()
  local tries = 0
  local waited = 0
  local target = curTarget
  local marker, mx, my, mz = target.id, target.x, target.y, target.z
  local waitTicks = math.max(0, math.floor(WAIT_AFTER_TP / 0.15))

  ETAT.poll = TM.addRepeatTimer(0.15, function()
    -- Toute la logique est sous pcall. Une erreur ici laisserait le timer
    -- alive et `running' a true, et la seule facon de s'enULES sortir serait
    -- de relancer le jeu : un script doit toujours pouvoir s'arreter lui-meme.
    local ok, err = pcall(function()
      if not chainActive or ETAT.cancel then
      finish(ETAT.cancel and 'CANCEL' or 'STOP')
      return
    end

    -- Attente de l'arrivée. C'est une MESURE DE DISTANCE, pas un drapeau de
    -- lerp : le déplacement appartient à specter.tp.here, et ce script n'a
    -- rien à savoir de son état interne.
    local pnow = maPosition()
    if not pnow then
      tries = tries + 1
      if tries * 0.15 > TRY_SECONDS then finish('NOPOS') end
      return
    end
    local d = distance(pnow, mx, my, mz)
    if d > ARRIVED_D then
      tries = tries + 1
      if tries * 0.15 > TRY_SECONDS then finish('TP_TIMEOUT') end
      return
    end

    -- Fenêtre configurée après le TP avant d'interagir.
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
        -- Entité morte ou absente. Si on est collé au point, c'est un coffre
        -- du registre déjà ouvert (désync) : on le marque et on enchaîne.
        if d <= 3 then
          opened[marker] = true
        end
        startCycle()
      end
      return
    end

    nettoyerTimers()
    local okr, res = pcall(function() return it:doUnitInteractive(unit) end)
    print('OPEN_INTERACT ok=' .. tostring(okr) .. ' id=' .. tostring(marker))
    ETAT.lastInteractOk = okr
    if okr then
      onOpened()
    else
      finish('OPEN_ERR')
    end
    end)

    if not ok then
      print('ERREUR dans le cycle : ' .. tostring(err))
      finish('ERROR')
    end
  end)
end

startCycle = function()
  if not chainActive then return end
  if ETAT.cancel then finish('CANCEL') return end
  if CHAIN_OPENS > 0 and (ETAT.done or 0) >= CHAIN_OPENS then
    finish('OK')
    return
  end

  local byLive, rows = collectTargets()
  -- JAMAIS de repli aveugle sur le registre. Mesure, en jeu :
  --
  --   scene 3000
  --   entites ClientChest chargees ... 10   (dont 4 reellement 10506)
  --   marques Coffre deverrouillees ..... 194
  --   dont avec une entite vivante ....... 0
  --   distance mediane jusqu a une marque : 397 u
  --
  -- Une marque du registre n'a pas d'entite tant qu'on n'est pas alle la
  -- charger. Se téléporter dessus, c'est se téléporter dans le vide -- et c'est
  -- exactement la question "je me TP a des chests invisible ?".
  --
  -- Donc : entites vivantes, ou rien.
  local list = byLive
  if USE_REGISTRY and #byLive == 0 then
    list = rows
    print('REGISTRE: ' .. #rows .. ' marque(s) -- many ont AUCUNE entite, le TP '
          .. 'peut atterrir dans le vide')
  end
  if #list == 0 then
    finish('NP')
    return
  end

  local t = list[1]
  local pnow = maPosition()
  if not pnow then finish('NOPOS') return end
  local dist = distance(pnow, t.x, t.y, t.z)

  curTarget = t
  if (ETAT.done or 0) > 0 then
    print(string.format('CHAIN %d -> id=%s d=%6.1f',
                        ETAT.done + 1, tostring(t.id), dist))
  end

  if dist >= ARRIVED_D then
    tpStop()                       -- annule un éventuel déplacement en cours
    tpHere(t.x, t.y, t.z)
    print(string.format('TP_TO id=%s d=%6.1f', tostring(t.id), dist))
  end

  startPoll()
end

-- ---------------------------------------------------------- affichage initial
local nCache = 0
for _ in pairs(opened) do nCache = nCache + 1 end

local byLive0, rows0 = collectTargets()
local list0 = byLive0
local source0 = 'entités vivantes'
if USE_REGISTRY and #byLive0 == 0 then
  list0 = rows0
  source0 = 'registre (RISQUE : marques sans entité)'
end

-- On affiche aussi ce qu'on ECarte, et pourquoi. Un compteur de "ignorés" sans
-- raison n'apprend rien ; avec la raison, on sait si le filtre fait son travail.
print(string.format('# coffres NON OUVERTS (scene %s, source: %s) : %d  [cache déjà ouverts: %d]',
                     tostring(e.sceneId), source0, #list0, nCache))
print(string.format('# marques au registre IGNOREES (aucune entité = TP dans le vide) : %d',
                     #rows0))
for i, r in ipairs(list0) do
  if i > MAX_LIST then
    print(string.format('... (%d de plus)', #list0 - MAX_LIST))
    break
  end
  print(string.format('U %s %.2f %.2f %.2f d=%7.1f %s',
                     tostring(r.id), r.x, r.y, r.z, r.d, r.name))
end
print('TOTAL_UNLOCKED=' .. #list0)

if #list0 == 0 then
  finish('NP')
  return
end

if not OPEN_ENABLED then
  -- Mode TP seulement : on se pose sur le plus proche, sans ouvrir.
  local t = list0[1]
  local pnow = maPosition()
  if pnow and distance(pnow, t.x, t.y, t.z) < ARRIVED_D then
    print('ALREADY_HERE id=' .. tostring(t.id))
    finish('OK')
    return
  end
  tpHere(t.x, t.y, t.z)
  print(string.format('TP_ONLY id=%s', tostring(t.id)))
  finish('OK')
  return
end

if CHAIN_OPENS > 0 then
  print('CHAIN_OPENS=' .. CHAIN_OPENS)
end
print('ANNULER :  specter.store.chests.cancel = true')
startCycle()