-- probe-coffres.lua — VERIFICATION DU FILTRE A COFFRES.
--
-- Read-only. Pour chaque entite `isChest` de la scene, affiche ce que les deux
-- regles du filtre voient, le verdict, et -- le point important -- si le nom
-- localise dit « Coffre », afin de verifier que le filtre et le nom DU JEU sont
-- d'accord.
--
-- C'est la mesure qui tranche : si une ligne porte verdict=COFFRE et un nom
-- qui n'est pas « Coffre », le filtre mange autre chose que des coffres.

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')

local CFG_COFFRE     = 10506
local MARQUE_ASSOC_D = 3
local CELL           = 24

local function position()
  local e = pg.me
  if not e then return nil end
  local ok, p = pcall(function() return e:getPosition() end)
  if ok and p then return p end
  return nil
end

local function nomDe(en)
  local ok, t = pcall(CTU.getLocalizationText, en.configName)
  return (ok and t and t ~= '') and t or '?'
end

local function classOf(e)
  local mt = getmetatable(e)
  local idx = mt and mt.__index
  return (idx and (idx.className or idx.__cname)) or '?'
end

-- Regle A : la config du jeu
local CD = package.loaded['Data.chest_data']
if type(CD) ~= 'table' then
  local ok, m = pcall(require, 'Data.chest_data')
  CD = ok and m or nil
end
print('A) Data.chest_data : ' .. tostring(type(CD)))

-- Regle B : la grille des marques
local pnow = position()
if not pnow then print('ERREUR: pas de position joueur'); return end
local sid = pg.me.sceneId
local pts = nil
local okm, m = pcall(SU.getSceneMarkPointData, sid)
if okm then pts = m end
print('B) scene ' .. tostring(sid) .. '  marques=' .. tostring(pts and 'oui' or 'non'))

local function cfgProche(x, y, z)
  if type(pts) ~= 'table' then return nil end
  local bd, bc
  for _, mp in pairs(pts) do
    local P = mp.markPosition
    if P and P[1] then
      local dx, dy, dz = P[1] - x, P[2] - y, P[3] - z
      local d = math.sqrt(dx * dx + dy * dy + dz * dz)
      if d < 1e9 and (not bd or d < bd) then bd, bc = d, mp.markConfigId end
    end
  end
  if bd and bd <= MARQUE_ASSOC_D then return bc, bd end
  return nil, bd
end

-- L'entite
local rows = {}
for _, en in pairs(pg.getEntities() or {}) do
  if en.isChest then
    local okp, p = pcall(function() return en:getPosition() end)
    if okp and p then
      local d = math.sqrt((p[1]-pnow[1])^2 + (p[2]-pnow[2])^2 + (p[3]-pnow[3])^2)
      local tpl = en.templateId

      -- CORRECTIF : une lecture qui ECHOUE vaut NON, jamais OUI.
      -- C'etait le bug : les entrees de chest_data qui n'ont pas de
      -- markConfigId (les ramassages) sortaient par un `return true`, et le
      -- filtre laissait passer 12 cibles non-coffres sur 25.
      local a, aCfg
      if type(CD) == 'table' and tpl ~= nil then
        local oke, e = pcall(function() return CD[tpl] end)
        if oke and e ~= nil then
          local okc, c = pcall(function() return e.markConfigId end)
          aCfg = (okc and c ~= nil) and tostring(c) or 'illisible'
          a = (okc and c ~= nil) and (c == CFG_COFFRE) or false
        else
          a, aCfg = false, 'absent'
        end
      end

      local b, bD = cfgProche(p[1], p[2], p[3])

      local verdict, why
      if a then verdict, why = 'COFFRE', 'A'
      elseif b == CFG_COFFRE then verdict, why = 'COFFRE', 'B'
      else verdict, why = 'ecarte', '-' end

      rows[#rows + 1] = {
        d = d, cls = classOf(en), tpl = tpl, nom = nomDe(en),
        aCfg = aCfg, b = b, bD = bD, v = verdict, why = why,
      }
    end
  end
end

table.sort(rows, function(x, y) return x.d < y.d end)

print(string.format('entites isChest = %d', #rows))
print(string.format('%-4s %-9s %-8s %-16s %-9s %-6s %-7s %s',
      'd(u)', 'classe', 'tpl', 'nom', 'chestDat', 'marque', 'dMarque', 'verdict'))

local nCoffre, nDisagree, nA, nB, nDisA, nDisB = 0, 0, 0, 0, 0, 0
for _, r in ipairs(rows) do
  print(string.format('%-4.0f %-9s %-8s %-16s %-9s %-6s %-7s %s [%s]',
        r.d, tostring(r.cls), tostring(r.tpl), tostring(r.nom),
        tostring(r.aCfg), tostring(r.b),
        r.bD and string.format('%.1f', r.bD) or '-',
        r.v, r.why))
  if r.v == 'COFFRE' then
    nCoffre = nCoffre + 1
    if r.why == 'A' then nA = nA + 1 else nB = nB + 1 end
    -- LE CONTROLE QUI VAUT : le filtre et le NOM DU JEU.
    -- 'Ramasser' n'est PAS un coffre, quelle que soit la regle qui l'a accepte.
    if r.nom ~= 'Coffre' then
      nDisagree = nDisagree + 1
      if r.why == 'A' then nDisA = nDisA + 1 else nDisB = nDisB + 1 end
    end
  end
end

print('---')
print(string.format('verdicts COFFRE : %d   (regle A : %d, regle B : %d)', nCoffre, nA, nB))
print(string.format('DESACCORDS     : %d   (regle A : %d, regle B : %d)', nDisagree, nDisA, nDisB))
print('---')
print(string.format('regle A seule  : %d verdict(s), %d desaccord(s)', nA, nDisA))
print(string.format('regle B seule  : %d verdict(s), %d desaccord(s)', nB, nDisB))
print('---')
if nDisB > 0 then
  print('VERDICT : LA REGLE B EST COUPABLE -- elle accepte des non-coffres.')
  print('         A la retirer, ou a exiger une corroboration par A.')
elseif nDisagree == 0 then
  print('VERDICT : le filtre ne mange que des coffres.')
else
  print('VERDICT : la regle A est coupable.')
end