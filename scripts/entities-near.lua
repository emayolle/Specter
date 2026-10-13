-- entities-near.lua — ce qu'il y a autour du joueur.
--
-- Réglages :
local RADIUS = 60            -- rayon en unités monde
local CLASS_FILTER = nil     -- ex. 'Chest' : ne garder que les classes contenant ça
local MAX_ROWS = 60          -- 0 = illimité

-- Usage : tools/lua.sh -f scripts/entities-near.lua

local me = pg.me
if not me then print('! pas de joueur'); return end
local mp = me:getPosition()

local function class_of(e)
  local mt = getmetatable(e)
  local idx = mt and mt.__index
  return (idx and (idx.className or idx.__cname)) or '?'
end

local rows = {}
for _, e in pairs(pg.getEntities() or {}) do
  local c = class_of(e)
  if not CLASS_FILTER or c:find(CLASS_FILTER, 1, true) then
    local p
    pcall(function() p = e:getPosition() end)
    if p then
      local d = math.sqrt((p[1] - mp[1]) ^ 2 + (p[2] - mp[2]) ^ 2 +
                          (p[3] - mp[3]) ^ 2)
      if d <= RADIUS and e ~= me then
        rows[#rows + 1] = { d, c, e.templateId, e.isChest, p[1], p[2], p[3] }
      end
    end
  end
end
table.sort(rows, function(a, b) return a[1] < b[1] end)

print(string.format('scene=%s  pos=%.1f %.1f %.1f  rayon=%.0f  n=%d',
  tostring(me.sceneId), mp[1], mp[2], mp[3], RADIUS, #rows))
for i, r in ipairs(rows) do
  if MAX_ROWS > 0 and i > MAX_ROWS then
    print(string.format('... (%d de plus)', #rows - MAX_ROWS))
    break
  end
  print(string.format('%7.1f  %-20s tpl=%-8s chest=%-5s pos=%.1f %.1f %.1f',
    r[1], r[2], tostring(r[3]), tostring(r[4]), r[5], r[6], r[7]))
end
