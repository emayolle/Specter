-- mesure-ouverture.lua -- COMBIEN DE TEMPS faut-il pour qu'un coffre disparaisse ?
--
-- Usage : tools/lua.sh -f scripts/mesure-ouverture.lua   (puis relire)
--
-- La boucle marque un coffre « sans effet » si l'entite n'a pas disparu en
-- CONFIRM_TICKS secondes, et ne le retente plus de la scene. C'est une peine
-- DESTRUCTIVE, et elle repose sur une constante devinee. Mesure-la.
--
-- Le protocole reprend le chemin reel de la boucle : meme filtre (regle A),
-- meme teleport, meme interaction, meme verification de disparition. On ne
-- mesure que le delai.
--
-- On echantillonne dans le STORE, pas avec print : le canal CLI perd tout ce
-- qui est imprime apres le retour du chunk, et c'est precisement la fenetre
-- qu'on cherche a mesurer.

local SU  = require('Common.Utils.SceneUtils')
local TM  = require('Core.Timer.TimerManager')
local CFG_COFFRE = 10506
local ARRIVED_D   = 2.5

local function position()
  local e = pg.me
  if not e then return nil end
  local ok, p = pcall(function() return e:getPosition() end)
  if ok and p then return p end
  return nil
end

local function identifiant(en)
  if en.markBindStaticId ~= nil then return en.markBindStaticId end
  return en.id
end

local function estCoffre(en)
  local C = package.loaded['Data.chest_data']
  if type(C) ~= 'table' or en.templateId == nil then return false end
  local oke, e2 = pcall(function() return C[en.templateId] end)
  if not oke or e2 == nil then return false end
  local okc, cfg = pcall(function() return e2.markConfigId end)
  if not okc or cfg == nil then return false end
  return cfg == CFG_COFFRE
end

local function entiteVivante(marker)
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and (en.id == marker or identifiant(en) == marker) then
      return true
    end
  end
  return false
end

local S = specter.store.mesure
if type(S) ~= 'table' then S = {}; specter.store.mesure = S end

-- PHASE 2 : lire le resultat
if S.trace and #S.trace > 0 then
  print('=== premiere disparition apres ' .. tostring(S.trouve or '?') .. ' s ===')
  local vu = false
  for _, l in ipairs(S.trace) do
    print('  ' .. l)
    if l:find('DISPARUE') then vu = true end
  end
  print('---')
  if vu then
    print(string.format('CONFIRM_TICKS devrait depasser %.1f s', tonumber(S.trouve) or 0))
  else
    print('l entite n a PAS disparu en ' .. tostring(S.duree or 0) .. ' s')
  end
  return
end

-- PHASE 1 : viser et ouvrir
local pnow = position()
if not pnow then print('ERREUR: pas de position'); return end

local cible
for _, en in pairs(pg.getEntities() or {}) do
  if en.isChest and en.chestValid and estCoffre(en) then
    local okp, p = pcall(function() return en:getPosition() end)
    if okp and p then
      local d = math.sqrt((p[1]-pnow[1])^2 + (p[2]-pnow[2])^2 + (p[3]-pnow[3])^2)
      if not cible or d < cible.d then
        cible = { d = d, x = p[1], y = p[2], z = p[3], id = identifiant(en), entId = en.id }
      end
    end
  end
end

if not cible then print('aucun coffre (regle A) autour'); return end
print(string.format('cible : id=%s  a %.2f u', tostring(cible.id), cible.d))

S.trace, S.t, S.interagi = {}, 0, false
S.duree = 20

specter.tp.here(cible.x, cible.y, cible.z)
print('TP lance -- observation jusqu a 20 s')

local h
h = TM.addRepeatTimer(0.25, function()
  S.t = S.t + 0.25
  local alive = entiteVivante(cible.id)

  -- l arrivee se juge sur l UNITE du jeu, comme dans la boucle
  local unite = false
  local it = pg.game and pg.game.interaction
  if it and it.unitMap then
    for _, u in pairs(it.unitMap[1] or {}) do
      if type(u) == 'table' and u.globalId == cible.entId then unite = true break end
    end
  end

  local d = -1
  local p = position()
  if p then d = math.sqrt((p[1]-cible.x)^2 + (p[2]-cible.y)^2 + (p[3]-cible.z)^2) end

  S.trace[#S.trace + 1] = string.format('%6.2f s  d=%6.2f  unite=%-5s entite=%s',
      S.t, d, tostring(unite), tostring(alive))

  if not S.interagi and unite then
    S.interagi = true
    if it then
      for _, u in pairs(it.unitMap[1] or {}) do
        if type(u) == 'table' and u.globalId == cible.entId then
          local okr, res = pcall(function() return it:doUnitInteractive(u) end)
          S.interactOk = tostring(okr) .. ' / ' .. tostring(res)
          S.trace[#S.trace + 1] = '        >> doUnitInteractive : ' .. S.interactOk
          break
        end
      end
    end
  end

  if S.interagi and not alive then
    S.trouve = S.t
    S.trace[#S.trace + 1] = '        >> DISPARUE a ' .. tostring(S.t) .. ' s'
    pcall(function() TM.removeTimer(h) end)
  elseif S.t >= S.duree then
    S.trouve = false
    pcall(function() TM.removeTimer(h) end)
  end
end)