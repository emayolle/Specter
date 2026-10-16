-- quest-waypoints.lua — waypoints de missions (quêtes), avec leur position monde.
--
-- Trois sources, même format de sortie :
--
--   tracked    les marques que le jeu affiche actuellement sur la carte / la HUD
--              (pg.game.map.tempMarkPointData) : 20 chez nous, ce sont les
--              quetes suivies. Position deja resolue par le jeu.
--
--   accepted   TOUTES les quetes en cours du joueur, avec la position resolue
--              par le jeu lui-meme (QuestUtils.getQuestTargetInfo). 231 quetes
--              acceptees chez nous, 34 waypoints.
--
--   catalogue  les quetes du jeu listees dans Data.quest_main. MESURE : vide.
--              118 quetes en memoire, mais 0 avec `objectives` rempli — la
--              table de config ne materialize les objectifs que pour les quetes
--              acceptees (getQuestConfig d'une quete non acceptee -> nil). Le
--              mode reste la pour tracer le probleme, pas pour produire des
--              positions. La cle de position existe pourtant :
--              SU.getSceneTargetPositionData(scene)[posConfigId].position
--              (c'est par elle qu'on resout GOTO_POSITION, cf. plus bas).
--
-- Reglages :
local MODE      = 'accepted'  -- tracked | accepted | catalogue | coord
local SCENES    = {3000, 3003}-- escenas ou chercher les positions du catalogue
local MAX_ROWS  = 800         -- 0 = illimite (attention au buffer de 48 Ko)
local WITH_NAME = true        -- nom localise de la quete (text id -> texte)

-- Mode 'coord' : le point a retrouver, tel que le jeu le met dans le
-- presse-papier quand on epingle un point sur la carte (MapCtrl.onPinBtnClick
-- ecrit `MAPCOORDINATE_%s_%s`). -411 / 763 -> MAPCOORDINATE_-0411_0763.
local TARGET    = 'MAPCOORDINATE_-0411_0763'

-- Usage : tools/lua.sh -f scripts/quest-waypoints.lua
--
-- Sortie : W <source> <scene> <questId> <objId> <x> <y> <z> <coordId> <nom>
--          TOTAL_<SOURCE>=<n>

-- Les waypoints de mission ne sont PAS des marques monde : dans la scene 3000,
-- getSceneMarkPointData() renvoie 2323 marques (coffres 10506, floraisons 10410,
-- etc.) et aucune en 100 / 109, alors que les marques de quete utilisent ces
-- cfg-la. Ils viennent de QuestUtils, d'ou les trois entrees ci-dessous.
local QU  = require('GameApp.Quest.QuestUtils')
local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local rows, counts = {}, {}

local function localize(textId)
  if not WITH_NAME or not textId then return '' end
  local ok, s = pcall(CTU.getLocalizationText, textId)
  if ok and s and s ~= '' then return s end
  return ''
end

-- Un vecteur du jeu se lit par indice : [1]=x [2]=y [3]=z.
local function v3(p)
  if type(p) ~= 'userdata' and type(p) ~= 'table' then return nil end
  local a, b, c = p[1], p[2], p[3]
  if a == nil or b == nil or c == nil then return nil end
  return a, b, c
end

-- Le jeu formate les coordonnees de carte « -%04d » / « %04d » (MapCtrl :
-- `%04d`, `abs`, `-%04d`, `format`) puis les colle en MAPCOORDINATE_<x>_<z>.
local function coordId(x, z)
  local function fmt(v)
    v = math.floor(v)
    if v < 0 then return string.format('-%04d', math.abs(v)) end
    return string.format('%04d', v)
  end
  return string.format('MAPCOORDINATE_%s_%s', fmt(x), fmt(z))
end

local function add(source, scene, questId, objId, p, name)
  local x, y, z = v3(p)
  if not x then return end
  counts[source] = (counts[source] or 0) + 1
  rows[#rows + 1] = string.format('W %s %s %s %s %.2f %.2f %.2f %s %s',
    source, tostring(scene), tostring(questId), tostring(objId),
    x, y, z, coordId(x, z), name or '')
end

--------------------------------------------------------------------------
-- tracked : les marques vivantes du client
--------------------------------------------------------------------------
local function mode_tracked()
  local t = pg.game.map.tempMarkPointData
  if type(t) ~= 'table' then
    print('! tempMarkPointData indisponible: ' .. type(t))
    return
  end
  for markId in pairs(t) do
    local m = t[markId]
    if m then
      local cfg = QU.getQuestConfig(m.questId)
      add('tracked', m.sceneId or pg.me.sceneId, m.questId, m.objId,
          m.markPosition, cfg and localize(cfg.name) or localize(m.infoTitle))
    end
  end
end

--------------------------------------------------------------------------
-- accepted : les quetes en cours, position resolue par le jeu
--------------------------------------------------------------------------
local function mode_accepted()
  local accepted = QU.getAllAcceptedQuestsData()
  if type(accepted) ~= 'table' then
    print('! getAllAcceptedQuestsData indisponible: ' .. type(accepted))
    return
  end
  for questId, questData in pairs(accepted) do
    local cfg = QU.getQuestConfig(questId)
    local name = cfg and localize(cfg.name) or ''
    local objIds = (questData and questData.objectives) or {}
    for objId in pairs(objIds) do
      local ok, info = pcall(QU.getQuestTargetInfo, questData, objId)
      if ok and info and info.posInfo then
        for i = 1, 64 do
          local pi = info.posInfo[i]
          if not pi then break end
          -- pos est la position d'arrivee ; posConfig.position la meme.
          add('accepted', pg.me.sceneId, questId, pi.objId or objId,
              pi.pos or (pi.posConfig and pi.posConfig.position), name)
        end
      end
    end
  end
end

--------------------------------------------------------------------------
-- catalogue : toutes les quetes chargees, position via la config du scene
--------------------------------------------------------------------------
local function mode_catalogue()
  local main = require('Data.quest_main')
  local cache = {}   -- posConfigId -> { scene, position }
  local function position(id)
    if not id or cache[id] then return cache[id] end
    for _, scene in ipairs(SCENES) do
      local ok, table_ = pcall(function()
        return SU.getSceneTargetPositionData(scene, id)
      end)
      if ok and table_ then
        local ok2, row = pcall(function() return table_[id] end)
        if ok2 and row and row.position then
          cache[id] = { scene = scene, pos = row.position }
          return cache[id]
        end
      end
    end
    cache[id] = false
    return false
  end

  for sectionId, section in pairs(main) do
    for questId, cfg in pairs(section) do
      local name = localize(cfg.name)
      local objectives = cfg.objectives
      if objectives then
        for objId, obj in pairs(objectives) do
          local pv = obj.paramVals
          if pv then
            -- paramVals est une liste plate : cle, valeur, cle, valeur...
            for i = 1, 64, 2 do
              if tostring(pv[i]) == 'GOTO_POSITION' then
                local hit = position(pv[i + 1])
                if hit then
                  add('catalogue', hit.scene, questId, objId, hit.pos, name)
                end
                break
              end
            end
          end
        end
      end
    end
    local _ = sectionId
  end
end

--------------------------------------------------------------------------
-- coord : le point epingle sur la carte, retrouve par son identifiant
--
-- MAPCOORDINATE_<x>_<z> est ce que le jeu ecrit dans le presse-papier quand on
-- clique sur l'epingle d'une marque (MapCtrl.onPinBtnClick). On le relit, et on
-- dit ce qu'il y a la : marque de quete, marque monde, ou les deux.
--------------------------------------------------------------------------
local function mode_coord()
  local sx, sz = TARGET:match('^MAPCOORDINATE_(-?%d+)_(-?%d+)$')
  if not (sx and sz) then
    print('! TARGET illisible: ' .. tostring(TARGET))
    return
  end
  local tx, tz = tonumber(sx), tonumber(sz)

  -- 1. les marques de quete
  local t = pg.game.map.tempMarkPointData
  if type(t) == 'table' then
    for markId, m in pairs(t) do
      if m and m.markPosition and coordId(m.markPosition[1], m.markPosition[3]) == TARGET then
        local cfg = QU.getQuestConfig(m.questId)
        add('questmark', m.sceneId, m.questId, m.objId, m.markPosition,
            cfg and localize(cfg.name) or localize(m.infoTitle))
        print(string.format('  (marque de quete n°%s, cfg%s, icône %s)',
          tostring(markId), tostring(m.markConfigId), tostring(m.icon)))
      end
    end
  end

  -- 2. les objectifs des quetes en cours
  local accepted = QU.getAllAcceptedQuestsData()
  if type(accepted) == 'table' then
    for questId, questData in pairs(accepted) do
      for objId in pairs((questData and questData.objectives) or {}) do
        local ok, info = pcall(QU.getQuestTargetInfo, questData, objId)
        if ok and info and info.posInfo then
          for i = 1, 64 do
            local pi = info.posInfo[i]
            if not pi then break end
            local p = pi.pos or (pi.posConfig and pi.posConfig.position)
            if p and coordId(p[1], p[3]) == TARGET then
              local cfg = QU.getQuestConfig(questId)
              local desc = ''
              if cfg and cfg.objectives then
                local o = cfg.objectives[pi.objId or objId]
                if o then desc = localize(o.desc) end
              end
              add('objective', pg.me.sceneId, questId, pi.objId or objId, p, desc)
            end
          end
        end
      end
    end
  end

  -- 3. les marques monde, au meme point (les deux peuvent designer la meme
  --    chose : un point de quete pose sur un evenement du monde).
  for _, scene in ipairs(SCENES) do
    local marks = SU.getSceneMarkPointData(scene)
    for _, p in pairs(marks) do
      local mp = p.markPosition
      if mp and coordId(mp[1], mp[3]) == TARGET then
        counts.worldmark = (counts.worldmark or 0) + 1
        rows[#rows + 1] = string.format(
          'W worldmark %s cfg%s type%s - - %.2f %.2f %.2f %s %s',
          tostring(scene), tostring(p.markConfigId), tostring(p.markType),
          mp[1], mp[2], mp[3], TARGET, localize(p.infoTitle))
      end
    end
  end

  local _ = tx, tz
end

local MODES = {
  tracked = mode_tracked,
  accepted = mode_accepted,
  catalogue = mode_catalogue,
  coord = mode_coord,
}

local run = MODES[MODE]
if not run then
  print('! MODE inconnu: ' .. tostring(MODE))
  return
end
run()

table.sort(rows)
local total = 0
for _, n in pairs(counts) do total = total + n end
print('# ' .. MODE .. ' : ' .. total .. ' waypoint(s)')
for i, r in ipairs(rows) do
  if MAX_ROWS > 0 and i > MAX_ROWS then
    print(string.format('... (%d de plus, releve MAX_ROWS)', #rows - MAX_ROWS))
    break
  end
  print(r)
end
for source, n in pairs(counts) do
  print(string.format('TOTAL_%s=%d', source:upper(), n))
end