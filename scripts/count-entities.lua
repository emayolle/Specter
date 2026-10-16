-- count-entities.lua — combien d'objets le jeu a charges autour de toi.
--
-- C'est LA mesure qui tranche pour le streaming : on compte avant, on change le
-- plafond, on recompte. Sans nombre, "ca a l'air d'avoir aide" ne veut rien
-- dire.
--
-- Usage : tools/lua.sh -f scripts/count-entities.lua

local me = pg.me
if not me then print('! pas de joueur'); return end
local p0 = me:getPosition()

local parClasse = {}
local total = 0
local chests, chestSansMarque = 0, 0

for _, en in pairs(pg.getEntities() or {}) do
  total = total + 1
  local mt = getmetatable(en)
  local idx = mt and mt.__index
  local c = (idx and (idx.className or idx.__cname)) or '?'
  parClasse[c] = (parClasse[c] or 0) + 1
  if en.isChest then
    chests = chests + 1
    if en.markBindStaticId == nil then chestSansMarque = chestSansMarque + 1 end
  end
end

print(string.format('TOTAL entites chargees : %d', total))
print(string.format('  dont isChest          : %d', chests))
print(string.format('  dont sans markBindStaticId : %d', chestSansMarque))

-- Le streaming ne charge que des BLOCS de terrain. Les coffres viennent du
-- serveur. Donc le chiffre a regarder en premier, c'est "total" : s'il ne bouge
-- pas, le plafond ne sert a rien pour l'auto-farm.
local t = {}
for c, n in pairs(parClasse) do t[#t + 1] = { c, n } end
table.sort(t, function(a, b) return a[2] > b[2] end)
print('')
print('par classe :')
for i = 1, math.min(#t, 14) do
  print(string.format('  %-26s %5d', t[i][1], t[i][2]))
end

-- Et la distance aux coffres, parce que c'est ce que l'auto-farm vise.
local d = {}
for _, en in pairs(pg.getEntities() or {}) do
  if en.isChest then
    local ok, q = pcall(function() return en:getPosition() end)
    if ok and q then
      d[#d + 1] = ((q[1] - p0[1]) ^ 2 + (q[2] - p0[2]) ^ 2 + (q[3] - p0[3]) ^ 2) ^ 0.5
    end
  end
end
table.sort(d)
if #d > 0 then
  print('')
  print(string.format('coffres charges : %d   plus proche %.1f u   plus loin %.1f u   mediane %.1f u',
        #d, d[1], d[#d], d[math.floor(#d / 2) + 1]))
else
  print('')
  print('aucun coffre charge')
end