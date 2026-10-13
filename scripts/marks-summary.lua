-- marks-summary.lua — COMBIEN DE CHAQUE TYPE.
--
-- Le script d'inventaire : pour chaque scène balayée, il compte les marques par
-- `markConfigId` et affiche un nom d'exemple (résolu via la table de
-- localisation). C'est la vue "n de chaque type" du monde.
--
-- Réglages :
local SCENES = {3000, 3003}   -- scènes du monde ouvert connues
--
-- Usage : tools/lua.sh -f scripts/marks-summary.lua
--
-- Sortie :
--   === scene 3000 ===
--    749  cfg=10506  type=5   Coffre
--   === total (2 scenes) ===
--    790  cfg=10506  type=5   Coffre

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

-- by[scene][cfg] = { n, markType, name }
local by = {}
local total = {}

for _, sid in ipairs(SCENES) do
  by[sid] = {}
  local ok, pts = pcall(SU.getSceneMarkPointData, sid)
  if ok and type(pts) == 'table' then
    for _, p in pairs(pts) do
      local c = p.markConfigId
      local e = by[sid][c]
      if not e then
        e = { n = 0, markType = p.markType, name = nil }
        by[sid][c] = e
      end
      e.n = e.n + 1
      if not e.name then e.name = localize(p.infoTitle) end
    end
  end
end

-- total global (mêmes configs cumulées sur toutes les scènes)
for _, sid in ipairs(SCENES) do
  for c, e in pairs(by[sid]) do
    local t = total[c]
    if not t then
      t = { n = 0, markType = e.markType, name = e.name }
      total[c] = t
    end
    t.n = t.n + e.n
    if not t.name then t.name = e.name end
  end
end

local function report(title, map)
  print('=== ' .. title .. ' ===')
  local rows = {}
  for c, e in pairs(map) do rows[#rows + 1] = { e.n, c, e.markType, e.name } end
  table.sort(rows, function(a, b)
    if a[1] ~= b[1] then return a[1] > b[1] end
    return a[2] < b[2]
  end)
  for _, r in ipairs(rows) do
    print(string.format('%6d  cfg=%-6s type=%-4s %s',
      r[1], tostring(r[2]), tostring(r[3]), r[4] or ''))
  end
end

for _, sid in ipairs(SCENES) do
  report('scene ' .. sid, by[sid])
end
report('total (' .. #SCENES .. ' scenes)', total)
