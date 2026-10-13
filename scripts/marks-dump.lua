-- marks-dump.lua — positions des marques d'une famille.
--
-- Choisit une famille connue (ou un filtre libre) et imprime une ligne par
-- marque, triée par scène puis x. C'est le script "récupérer" générique.
--
-- Réglages :
local FAMILY = 'coffres'      -- coffres | cristaux | floraisons | ambre | eco
                              -- pierre | grottes | nomade | tout
local MARK_CONFIG = nil       -- prioritaire sur FAMILY si non nil (ex. 10506)
local MARK_TYPE   = nil       -- prioritaire sur FAMILY si non nil (ex. 26)
local SCENES = {3000, 3003}
local MAX_ROWS = 800          -- 0 = illimité (attention au buffer de 48 Ko)

-- Usage : tools/lua.sh -f scripts/marks-dump.lua
--
-- Sortie : M <scene> <cfg> <x> <y> <z> <nom>

local FAMILIES = {
  coffres    = { cfg = 10506, name = 'Coffre' },
  cristaux   = { cfg = 10406, name = 'Teleportation Array' },
  floraisons = { type = 26,   name = 'Floraison' },
  ambre      = { cfg = 10505, name = 'Ambre lumin' },
  eco        = { cfg = 10405, name = 'Point écologique clé' },
  pierre     = { cfg = 10401, name = 'Pierre gelée' },
  grottes    = { cfg = 10600, name = 'Entrée de la grotte' },
  nomade     = { cfg = 10510, name = 'Défi de Nomade' },
  tout       = {},
}

if not MARK_CONFIG and not MARK_TYPE then
  local f = FAMILIES[FAMILY]
  if not f then
    print('! famille inconnue: ' .. tostring(FAMILY))
    return
  end
  MARK_CONFIG, MARK_TYPE = f.cfg, f.type
end

local label = FAMILY
if MARK_CONFIG then label = label .. ' cfg=' .. MARK_CONFIG end
if MARK_TYPE then label = label .. ' type=' .. MARK_TYPE end

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

local matched, rows = 0, {}
for _, sid in ipairs(SCENES) do
  local ok, pts = pcall(SU.getSceneMarkPointData, sid)
  if ok and type(pts) == 'table' then
    for _, p in pairs(pts) do
      if (not MARK_CONFIG or p.markConfigId == MARK_CONFIG) and
         (not MARK_TYPE or p.markType == MARK_TYPE) and p.markPosition then
        matched = matched + 1
        local mp = p.markPosition
        rows[#rows + 1] = {
          sid, p.markConfigId, mp[1], mp[2], mp[3], localize(p.infoTitle) or '',
        }
      end
    end
  end
end

table.sort(rows, function(a, b)
  if a[1] ~= b[1] then return a[1] < b[1] end
  if a[3] ~= b[3] then return a[3] < b[3] end
  return a[4] < b[4]
end)

print('# ' .. label .. ' : ' .. matched .. ' marque(s)')
for i, r in ipairs(rows) do
  if MAX_ROWS > 0 and i > MAX_ROWS then
    print(string.format('... (%d de plus, relève MAX_ROWS)', #rows - MAX_ROWS))
    break
  end
  print(string.format('M %d %s %.2f %.2f %.2f %s',
    r[1], tostring(r[2]), r[3], r[4], r[5], r[6]))
end
print('TOTAL=' .. matched)
