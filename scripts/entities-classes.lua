-- entities-classes.lua — COMBIEN DE CHAQUE TYPE (entités vivantes).
--
-- Pendant "entités" de marks-summary.lua : compte les entités réellement
-- instanciées dans la scène courante, par classe Lua.
--
-- La classe d'une entité se lit via la métatable : getmetatable(e).__index.className.
--
-- Usage : tools/lua.sh -f scripts/entities-classes.lua
--
-- Sortie :
--      12  ClientChest
--      18  ClientEnvObject
--      ...

local function class_of(e)
  local mt = getmetatable(e)
  local idx = mt and mt.__index
  return (idx and (idx.className or idx.__cname)) or '?'
end

local counts = {}
local n = 0
for _, e in pairs(pg.getEntities() or {}) do
  n = n + 1
  local c = class_of(e)
  counts[c] = (counts[c] or 0) + 1
end

local rows = {}
for c, k in pairs(counts) do rows[#rows + 1] = { k, c } end
table.sort(rows, function(a, b)
  if a[1] ~= b[1] then return a[1] > b[1] end
  return a[2] < b[2]
end)

print('scene=' .. tostring(pg.me and pg.me.sceneId) .. '  entites=' .. n)
for _, r in ipairs(rows) do
  print(string.format('%6d  %s', r[1], r[2]))
end
print('TOTAL=' .. n)
