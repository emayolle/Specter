-- tp-test-original.lua -- reproduction EXACTE du lerp d'origine (commit e72ca4f).
--
-- Pourquoi on teste une version qui existe deja dans l'historique : parce que la
-- version actuelle ne deplace pas le joueur, et que celle-la est ecrite
-- « validated in-game, a 150 u move holds ».
--
-- Ce qui a change depuis, et qui est le seul candidat :
--
--     pas         2.0 u      ->  5.5 u
--     intervalle  0.01 s     ->  1/120 s = 0.0083 s   (equivalent)
--     methode     forceSetPos(v, true)               (INCHANGE)
--
-- Le pas est donc la seule variable serieuse. Le commit dit « ~2 units/step
-- holds », donc le seuil est entre 2 et 5.5.
--
-- La trace est ecrite dans specter.store, PAS dans print : le canal CLI perd
-- tout ce qui est imprime apres le retour du chunk, et c'est precisement la
-- fenetre qui compte ici.

local TM = require('Core.Timer.TimerManager')

-- Parametres via le store : le CLI ne passe pas d'arguments a un fichier, et
-- `ARG_PAS` n'existe pas. On lit donc ce qu'un appel precedent a pose.
local P = specter.store.tpparams
if type(P) ~= 'table' then P = {}; specter.store.tpparams = P end

local PAS        = tonumber(P.pas) or 2.0  -- u
local INTERVALLE = tonumber(P.intervalle) or 0.01  -- s, comme l original
local DIST       = tonumber(P.dist) or 150.0       -- u

local e = pg.me
if not e then
  for _k, _v in pairs(pg.global.actorMgr.uid2Ent) do e = _v break end
end
if not e or not e.getPosition then print('ERREUR: pas de joueur'); return end

local S = specter.store.tptest
if type(S) ~= 'table' then S = {}; specter.store.tptest = S end
S.trace, S.n, S.fini = {}, 0, false
S.pas, S.dist = PAS, DIST

local function lire()
  local p = e:getPosition()
  return p[1], p[2], p[3]
end

local x0, y0, z0 = lire()

-- Cible a DIST sur X, en gardant y et z : on ne veut pas tester la gravite.
local x1, y1, z1 = x0 + DIST, y0, z0

print(string.format('pas=%.2f u  intervalle=%.3f s  distance=%.1f u', PAS, INTERVALLE, DIST))
print(string.format('depart (%.2f %.2f %.2f)', x0, y0, z0))
print(string.format('cible  (%.2f %.2f %.2f)', x1, y1, z1))

-- Un run precedent peut laisser un timer : on l annule, sinon deux lerps se
-- disputent la meme position.
local prev = specter.store.tpMove
if prev and prev.tid then pcall(function() TM.removeTimer(prev.tid) end) end
if prev then prev.active = false end

local dx, dy, dz = x1 - x0, y1 - y0, z1 - z0
local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
local n = math.ceil(dist / PAS)
if n < 1 then n = 1 end
local st = { active = true, i = 0, s = PAS, n = n,
             x0 = x0, y0 = y0, z0 = z0, x1 = x1, y1 = y1, z1 = z1 }
print(string.format('pas de depart : n = %d', n))

local s = st
st.tid = TM.addRepeatTimer(INTERVALLE, function()
  if not s.active then return end
  s.i = s.i + 1
  local a = s.i / s.n
  if a > 1 then a = 1 end
  local v = Vector3.ForceNew(s.x0 + (s.x1 - s.x0) * a,
                             s.y0 + (s.y1 - s.y0) * a,
                             s.z0 + (s.z1 - s.z0) * a)
  if e.forceSetPos then e:forceSetPos(v, true) else e:setPosition(v) end
  if s.i >= s.n then
    s.active = false
    pcall(function() TM.removeTimer(s.tid) end)
  end
end)
specter.store.tpMove = st

-- Sonde INDEPENDANTE : elle mesure l'entite, pas l'ecriture. C'est le point de
-- tout le test -- une mesure faite juste apres une ecriture ne prouve rien.
local t = 0
local h
h = TM.addRepeatTimer(0.1, function()
  t = t + 1
  local px, py, pz = lire()
  local attendu = x0 + (x1 - x0) * math.min(1, st.i / st.n)
  S.n = t
  S.trace[#S.trace + 1] = string.format('%.1f i=%d attendu=%.2f reel=%.2f ecart=%.2f',
      t * 0.1, st.i, attendu, px, px - attendu)
  if t >= 40 then
    pcall(function() TM.removeTimer(h) end)
    S.fini = true
  end
end)
print('sonde armee : 40 echantillons a 0.1 s')