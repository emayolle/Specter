-- entity-dump.lua — tous les champs d'une entité.
--
-- Très utile pour découvrir une API : on choisit une cible, on liste ses champs
-- avec leur type et leur valeur courante.
--
-- Réglages :
local TARGET = 'me'          -- 'me' | 'nearest' | 'class:<NomDeClasse>'
local MAX_VALUE_LEN = 60     -- tronque les valeurs longues

-- Usage :
--   tools/lua.sh -f scripts/entity-dump.lua
-- (éditer TARGET en tête du fichier pour cibler une autre entité)

local function class_of(e)
  local mt = getmetatable(e)
  local idx = mt and mt.__index
  return (idx and (idx.className or idx.__cname)) or '?'
end

local function pick()
  if TARGET == 'me' then return pg.me end
  local wanted = TARGET:match('^class:(.+)$')
  local me = pg.me
  local mp = me and me:getPosition()
  local best, bestd
  for _, e in pairs(pg.getEntities() or {}) do
    if wanted then
      if class_of(e) == wanted then return e end
    else -- 'nearest'
      local p
      pcall(function() p = e:getPosition() end)
      if p and mp and e ~= me then
        local d = (p[1] - mp[1]) ^ 2 + (p[2] - mp[2]) ^ 2 + (p[3] - mp[3]) ^ 2
        if not bestd or d < bestd then bestd, best = d, e end
      end
    end
  end
  return best
end

local e = pick()
if not e then print('! entité introuvable (' .. TARGET .. ')'); return end

print('cible=' .. TARGET .. '  classe=' .. class_of(e) ..
      '  tpl=' .. tostring(e.templateId) .. '  scene=' .. tostring(e.sceneId))
local p
pcall(function() p = e:getPosition() end)
if p then print(string.format('pos=%.2f %.2f %.2f', p[1], p[2], p[3])) end

local fields = {}
for k, v in pairs(e) do fields[#fields + 1] = { tostring(k), type(v), tostring(v) } end
table.sort(fields, function(a, b) return a[1] < b[1] end)

for _, f in ipairs(fields) do
  local val = f[3]:gsub('[%c]', ' ')
  if #val > MAX_VALUE_LEN then val = val:sub(1, MAX_VALUE_LEN - 3) .. '...' end
  print(string.format('  %-42s %-8s %s', f[1], f[2], val))
end
print('champs=' .. #fields)
