-- chests.lua — les coffres.
--
-- Deux vues complémentaires, plus leur corrélation :
--   * MARQUES MONDE : les coffres sont des marques de scène `cfg=10506`
--     ("Coffre"), présentes dans toutes les zones (chargées ou pas) ;
--   * ENTITÉS VIVANTES : les `ClientChest` réellement instanciés dans la scène
--     courante (`isChest == true`).
--   * LIEN : `markBindStaticId` d'une entité == `id` de sa marque monde.
--
-- Réglages :
local SCENES = {3000, 3003}
local MARK_CONFIG = 10506
local SHOW_MARKS = true
local SHOW_LIVE  = true
local LIVE_RADIUS = 0        -- 0 = toutes ; sinon, limiter au rayon (unités)

-- Usage : tools/lua.sh -f scripts/chests.lua

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

-- ---------------------------------------------------------------- marques monde
local mark_by_id = {}
if SHOW_MARKS then
  local rows = {}
  for _, sid in ipairs(SCENES) do
    local ok, pts = pcall(SU.getSceneMarkPointData, sid)
    if ok and type(pts) == 'table' then
      for id, p in pairs(pts) do
        if p.markConfigId == MARK_CONFIG and p.markPosition then
          local mp = p.markPosition
          rows[#rows + 1] = { sid, mp[1], mp[2], mp[3], id }
          mark_by_id[id] = { sid = sid, x = mp[1], y = mp[2], z = mp[3],
                             name = localize(p.infoTitle) }
        end
      end
    end
  end
  table.sort(rows, function(a, b)
    if a[1] ~= b[1] then return a[1] < b[1] end
    if a[2] ~= b[2] then return a[2] < b[2] end
    return a[3] < b[3]
  end)
  print('# marques monde cfg=' .. MARK_CONFIG .. ' : ' .. #rows)
  for _, r in ipairs(rows) do
    print(string.format('C %d %.2f %.2f %.2f', r[1], r[2], r[3], r[4]))
  end
  print('TOTAL_MARKS=' .. #rows)
end

-- ------------------------------------------------------------- entités vivantes
if SHOW_LIVE then
  print('# entités vivantes (isChest) ...')
  local me = pg.me
  local mp = me and me:getPosition()
  local rows, seen = {}, 0
  for _, e in pairs(pg.getEntities() or {}) do
    if e.isChest then
      seen = seen + 1
      local p
      pcall(function() p = e:getPosition() end)
      local d = (p and mp) and
        math.sqrt((p[1] - mp[1]) ^ 2 + (p[2] - mp[2]) ^ 2 + (p[3] - mp[3]) ^ 2)
        or -1
      if LIVE_RADIUS == 0 or d <= LIVE_RADIUS then
        local mk = e.markBindStaticId and mark_by_id[e.markBindStaticId]
        rows[#rows + 1] = {
          d, e.templateId, e.chestType, localize(e.configName),
          e.markBindStaticId, p and p[1], p and p[2], p and p[3],
          mk and mk.sid,
        }
      end
    end
  end
  table.sort(rows, function(a, b) return a[1] < b[1] end)
  for _, r in ipairs(rows) do
    print(string.format(
      'LIVE d=%6.1f tpl=%-8s type=%-2s mark=%-10s scene=%-5s name=%s pos=%.1f %.1f %.1f',
      r[1], tostring(r[2]), tostring(r[3]), tostring(r[5]),
      tostring(r[9] or '-'), tostring(r[4]), r[6] or 0, r[7] or 0, r[8] or 0))
  end
  print('TOTAL_LIVE=' .. seen)
end
