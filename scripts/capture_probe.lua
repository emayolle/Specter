-- capture_probe.lua -- LE test qui decide si la capture est scriptable.
--
--   tools/lua.sh -f scripts/capture_probe.lua     arme  -> lance une balle
--   tools/lua.sh -f scripts/capture_probe.lua     lit le resultat
--
-- LA QUESTION
--
-- Toute la chaine de capture est forgeable SAUF un chiffre : le
-- captureSessionId, que le serveur seul Possede. On l'a donc utilise tel quel,
-- sur une vraie session, et on annonce un touchement sur une entite que la
-- balle ne touche pas -- la plus loin de la carte.
--
--   code == 0   le serveur se fie au rapport client -> scriptable
--   code ~= 0   il verifie la collision -> on s'arrete la
--
-- CE QUE LE CLIENT DECLARE (RpcCSArgDict:894)
--
--   RPC_CS_BallHitEntity(string captureSessionId, string hitEntityId,
--                         boolean fromBehind)
--
-- On renvoie la VRAIE signature. RpcSendValidator ne regarde que le nombre et
-- le type des arguments, donc notre appel passe le controle client.
--
-- LA FORGE EST ENVOYEE APRÈS LE RETOUR DE L'HANDLER DU JEU
--
-- Le message entrant est d'abord traite normalement, puis seulement ensuite on
-- envoie. Envoyer depuis l'interieur du dispatch, c'est de la reentrance sur
-- le chemin reseau -- aucune raison de la risquer.

local sp = specter

local R = sp.store.probe
if not R then R = {} sp.store.probe = R end

-- ---------------------------------------------------------------- lire

if R.etat == 'repondu' or R.etat == 'expire' then
  print('')
  print(string.rep('=', 66))
  print('  CAPTURE PROBE -- resultat')
  print(string.rep('=', 66))
  print(string.format('  session reelle   : %s', tostring(R.session)))
  print(string.format('  cible forgee     : %s', tostring(R.cible)))
  print(string.format('  distance reelle  : %s u', R.distance and string.format('%.0f', R.distance) or '?'))
  print('')
  if R.code ~= nil then
    print(string.format('  >>> code = %s', tostring(R.code)))
    if R.code == 0 then
      print('  >>> LE SERVEUR ACCEPTE UN TOUCHEMENT INVENTE')
    else
      print('  >>> REFUSE : le serveur verifie la collision')
    end
  else
    print('  pas de reponse du rappel (delai depasse, ou session close)')
  end
  if R.note then print('  note : ' .. R.note) end
  print(string.rep('=', 66))
  return
end

-- ---------------------------------------------------------------- armer

-- Une cible REELLE mais lointaine : on veut isoler la verification de
-- distance, pas celle de l'existence de l'entite.
local me = pg.me
local p0 = me:getPosition()
local cible, loin = nil, -1
for _, en in pairs(pg.getEntities() or {}) do
  local ok, q = pcall(function() return en:getPosition() end)
  if ok and q and en.id then
    local dx = q[1] - p0[1]
    local dy = q[2] - p0[2]
    local dz = q[3] - p0[3]
    local d = (dx * dx + dy * dy + dz * dz) ^ 0.5
    if d > loin then loin, cible = d, en.id end
  end
end

R.etat = 'arme'
R.cible = cible
R.distance = loin
R.code = nil
R.session = nil
R.note = nil

local vGH = getmetatable(require('Core.Client.GateClientRpcHandler')).__index
local orig = rawget(vGH, 'entityMessageV2')

if type(orig) ~= 'function' then
  print('capture_probe : entityMessageV2 introuvable -- abandon')
  return
end

local RpcIndex = require('Core.Common.RpcIndex')

vGH.entityMessageV2 = function(self, entityId, raw, index, context, ...)
  local nom = RpcIndex.INDEX2RPC[index] or RpcIndex.RPC_INDEX2NAME[index]
  local sessionId = (nom == 'RPC_SC_OnFireBall') and (select(1, ...)) or nil

  -- 1. le jeu traite le message comme d'habitude
  local r = orig(self, entityId, raw, index, context, ...)

  -- 2. ensuite seulement, on forge
  if sessionId and R.etat == 'arme' then
    R.etat = 'envoye'
    R.session = sessionId
    local ok, err = pcall(function()
      pg.me:serverMsg('RPC_CS_BallHitEntity', sessionId, R.cible, false, function(code)
        R.etat = 'repondu'
        R.code = code
      end)
    end)
    if not ok then
      R.note = 'l envoi a leve : ' .. tostring(err)
    end
  end

  return r
end

R.orig = orig

print(string.format('capture_probe : ARME, cible = %s a %.0f u', tostring(cible), loin))
print('                lance une balle, puis relance ce script pour lire.')
print('                (la forge part toute seule des que la session arrive)')