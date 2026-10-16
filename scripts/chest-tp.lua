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
-- Le TP est celui de `specter.tp.here` -- celui de l'onglet Teleport, avec
-- ses réglages. Ce script avait son propre lerp, écrit ici, avec un état sur
-- le joueur qui ne cohabitait pas avec lui.
-- remplace un éventuel TP en cours.
--
-- Cache local "déjà ouvert" : on garde sur pg.me.__specterChestOpened la liste
-- des coffres que nous avons déjà ouverts, re-chargée (jamais réinitialisée) à
-- chaque exécution. Un id mis en cache disparaît de la liste pour de bon
-- (source de vérité : l'entité d'un coffre déjà ouvert peut encore traîner un
-- moment avec chestValid=true — on n'attend pas le despawn). Reset si besoin :
-- pg.me.__specterChestOpened = nil. Le registre unlockChunkMap, lui, ne se
-- purge pas en temps réel après une ouverture.
--
-- Réglages :
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

-- ------------------------------------------------ cache local "déjà ouverts"
-- DANS NOTRE STORE, pas sur le joueur.
--
-- Il était sur `pg.me.__specterChestOpened` : un nom à nous dans une table du
-- jeu, visible par quiconque parcourt l'entité.
--
-- Il est aussi PARTAGE avec chest-open.lua, volontairement : les deux scripts
-- parlent des mêmes coffres, et deux caches divergeraient — l'un croirait un
-- coffre ouvert que l'autre juge disponible, et la chaîne le rouvrirait.
local ETAT = specter.store.chests
if type(ETAT) ~= 'table' then
  ETAT = {}
  specter.store.chests = ETAT
end
local opened = type(ETAT.opened) == 'table' and ETAT.opened or {}
ETAT.opened = opened

local SEED_RADIUS = 4   -- u : coffre du registre très proche sans entité
                        -- vivante => considéré comme déjà ouvert

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
  -- Autoritatif : un id du cache ne réapparaît pas dans la liste, même si une
  -- entité du coffre ouvert traîne encore (despawn lent).
  local out = {}
  for _, r in ipairs(rowsIn) do
    if not opened[r.id] then
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

-- Que les VRAIS coffres (markConfigId 10506) : l'indicateur isChest couvre
-- aussi ramassages / Ambre lumin / Aniipods — le registre déverrouillé, lui,
-- ne liste que des Coffre (cfg 10506) ; on aligne le repli "entités vivantes".
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

local nCache = 0
for _ in pairs(opened) do nCache = nCache + 1 end

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

-- Les ClientChest VIVANTS d'abord. Ils sont, par construction, des coffres non
-- ouverts, et ils sont RÉELS : on peut se téléporter dessus sans atterrir dans
-- le vide.
--
-- L'ordre inverse était le défaut, et il mesurait :
--
--     scene 3000
--     marques Coffre deverrouillees ..... 194
--     dont avec une entite vivante ....... 0
--     distance mediane jusqu a une marque : 397 u
--
-- Aucune marque du registre n'a d'entité tant qu'on n'est pas allé la charger.
-- Se téléporter dessus, c'est se téléporter dans le vide.
local live = {}
for _, en in pairs(pg.getEntities() or {}) do
  if en.isChest and isCoffre(en.markBindStaticId) then
    local okp, p = pcall(function() return en:getPosition() end)
    if okp and p then
      local dx, dy, dz = p[1] - pnow[1], p[2] - pnow[2], p[3] - pnow[3]
      live[#live + 1] = {
        id = en.markBindStaticId,
        x = p[1], y = p[2], z = p[3],
        d = (dx * dx + dy * dy + dz * dz) ^ 0.5,
        name = en.chestValid and 'Coffre' or '',
      }
    end
  end
end
if #live > 0 then
  print(string.format('# marques au registre IGNOREES (aucune entite = TP dans le vide) : %d',
                       #rows))
  rows = live
end

if #rows == 0 then
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and isCoffre(en.markBindStaticId) then
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

-- Réconciliation : tout coffre du registre quasi-collé au joueur et sans
-- entité vivante est déjà ouvert (le registre n'est pas purgé en temps réel).
seedNear(rows)
rows = sieve(rows)

table.sort(rows, function(a, b) return a.d < b.d end)

print('# coffres NON OUVERTS (scene ' .. tostring(e.sceneId) .. ') : ' .. #rows
      .. '  [cache déjà ouverts: ' .. nCache .. ']')
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

-- Le deplacement appartient a specter.tp.here, comme pour l'onglet Teleport.
--
-- Ce script avait SON PROPRE lerp -- 5.5/120 en dur, donc les reglages du menu
-- ne lui parlaient pas -- et son etat sur `e.__specter_tp`, qui ne cohabite
-- pas avec `specter.store.tpMove`. Deux timers independants pouvaient
-- deplacer le joueur en meme temps.
if type(specter.tp) ~= 'table' or type(specter.tp.here) ~= 'function' then
  print('ERROR: specter.tp.here absent. scripts/init.lua ne tourne pas ?')
  return
end

if type(specter.tp.stop) == 'function' then
  pcall(specter.tp.stop)   -- annule un eventuel deplacement en cours
end
specter.tp.here(target.x, target.y, target.z)

print(string.format('TP_TO id=%s d=%6.1f', tostring(target.id), dist))