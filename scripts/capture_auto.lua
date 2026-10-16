-- capture_auto.lua -- capture automatique, sans caméra et sans rotation.
--
--   tools/lua.sh -f scripts/capture_auto.lua     bilan
--   specter.capture.on()    demarre
--   specter.capture.off()   arrete
--   specter.capture.lancer()   un lancer, a la main
--
-- LA RECETTE, MESUREE
--
-- Quatre etapes, dans cet ordre exact. L'ordre est le sujet : le RPC doit
-- partir APRES la synchronisation d'etat, sinon le serveur acquitte et ignore.
--
--   1. pg.me:throwItemFromBag(itemId)   entre en mode capture
--        -> 57 × RPC_CS_CharacterStateChange
--   2. attendre 0.5 s que le contexte existe
--   3. ctx:throw()                       le FSM, ForceChangeToUpperState(THROWRELEASE)
--   4. attendre 0.15 s, puis ctx:throwWithRpc()
--
-- Ce que ca donne, mesure :
--
--     > FireBall x2   CaptureHoldBall x2   CharacterStateChange x57
--     > SendBallMsg x5   BallHitEntity x1   NotifyCaptureAnim* x2
--     < OnFireBall x2   OnCaptureSuccess x1   SyncCatchBallDestroyed x1
--
-- NI CAMERA NI ROTATION
--
-- ThrowBallContext:doSwitch() est la seule methode qui touche au pilotage
-- (setSteering, CAPTURE_STEERING_TIME) et elle ne sert qu'a changer d'objet.
-- On ne l'appelle pas. Aucune fonction d'orientation n'est utilisee.
--
-- CE QUE CELA NE FAIT PAS
--
-- La balle part devant soi. Aucune cible n'est choisie : on ne tourne pas, donc
-- ce qui est devant est ce qui est touche. Pour viser quelqu'un d'autre il
-- faudrait s'orienter — ce que tu as refuse, et a raison.

local sp = specter
local TM = require('Core.Timer.TimerManager')
local CCU = require('Utils.ClientCaptureUtils')
local RpcIndex = require('Core.Common.RpcIndex')

-- ---------------------------------------------------------------- etat

local S = sp.store.capture
if not S then S = {} sp.store.capture = S end
S.lancers = S.lancers or 0
S.succes = S.succes or 0
S.refus = S.refus or 0
S.code = nil
S.phase = 'inactif'
S.delai = S.delai or 3
S.attente = S.attente or 0.5
S.decalage = S.decalage or 0.15
S.enCours = false
sp.capture = S

-- ---------------------------------------------------------------- recompenses
-- On compte les succes en observant l'entree. Pose une seule fois.

if not S.Observe then
  local vGH = getmetatable(require('Core.Client.GateClientRpcHandler')).__index
  local orig = rawget(vGH, 'entityMessageV2')
  if type(orig) == 'function' then
    vGH.entityMessageV2 = function(self, entityId, raw, index, context, ...)
      local nom = RpcIndex.INDEX2RPC[index] or RpcIndex.RPC_INDEX2NAME[index]
      if nom == 'RPC_SC_OnCaptureSuccess' then S.succes = S.succes + 1 end
      return orig(self, entityId, raw, index, context, ...)
    end
    S.Observe = true
  end
end

-- ---------------------------------------------------------------- un lancer

local function lancer()
  if S.enCours then return false end
  S.enCours = true
  S.phase = 'choix de la balle'

  -- une balle reelle que le joueur possede : le controle du jeu, pas le notre
  local itemId = CCU.getFirstUsableNormalBallItemId()
  if not itemId then
    S.phase = 'aucune balle utilisable'
    S.enCours = false
    return false
  end

  -- 1. la bonne entree. toggleCatchMode() ne fait que currentContext:exit(),
  --    c'est un appel vide.
  local ok1, e1 = pcall(function() pg.me:throwItemFromBag(itemId) end)
  if not ok1 then
    S.phase = 'throwItemFromBag a leve : ' .. tostring(e1)
    S.enCours = false
    return false
  end

  -- 2. le contexte, puis le FSM, puis le RPC decale
  TM.addTimer(S.attente, function()
    local ctx = pg.me.currentContext
    if type(ctx) ~= 'table' or type(ctx.throwWithRpc) ~= 'function' then
      S.phase = 'contexte = ' .. tostring(ctx and ctx.className)
      S.enCours = false
      return
    end

    local ok2, e2 = pcall(function() ctx:throw() end)
    if not ok2 then
      S.phase = 'throw a leve : ' .. tostring(e2)
      S.enCours = false
      return
    end

    -- 3. LE DECALAGE. C'est lui qui fait la difference entre un lancer
    --    accepte et un message ignore. 0.15 s a ete mesure comme suffisant ;
    --    S.decalage permet de chercher autour.
    TM.addTimer(S.decalage, function()
      local ok3, e3 = pcall(function()
        ctx:throwWithRpc(
          function() S.code = 0 end,
          function(code) S.code = code; S.refus = S.refus + 1 end,
          function() S.phase = 'delai depasse' end)
      end)
      if ok3 then
        S.lancers = S.lancers + 1
        S.phase = 'lance'
      else
        S.phase = 'throwWithRpc a leve : ' .. tostring(e3)
      end
      S.enCours = false
    end)
  end)
  return true
end

-- ---------------------------------------------------------------- boucle
--
-- TM.addRepeatTimer, comme autofarm_loop.lua. J'avais d'abord ecrit une
-- recursion sur addTimer -- qui ne se rearme pas : au moment du rappel, `timer`
-- porte encore le minuteur qui vient de tirer, donc armer() sort
-- immediatement et la boucle meurt apres UN passage. Mesure : 45 s a delai
-- 4 s, zero session. Le repeat timer est la bonne API, voila tout.

local timer = nil

local function arreter()
  if timer then pcall(function() TM.removeTimer(timer) end) end
  timer = nil
end

-- ---------------------------------------------------------------- commande

function S.lancer() return lancer() end

function S.on()
  arreter()
  S.auto = true
  S.phase = 'auto'
  -- le delai est fige a cet instant : changer S.delai apres n'a pas d'effet
  -- tant qu'on n'a pas fait off() puis on()
  timer = TM.addRepeatTimer(S.delai, function()
    if S.auto then pcall(lancer) end
  end)
end

function S.off()
  S.auto = false
  arreter()
  S.phase = 'arrete'
end

-- Refaite a chaque passage du script : une closure d'un Execute precedent
-- s'execute mais son print n'atteint plus la sortie.
S.bilan = function()
  local taux = (S.lancers > 0) and math.floor(S.succes * 100 / S.lancers) or 0
  print('')
  print(string.rep('=', 62))
  print(string.format('  lancers %d      succes %d (%d %%)      refus %d',
        S.lancers, S.succes, taux, S.refus))
  print(string.format('  phase %s      code %s', tostring(S.phase), tostring(S.code)))
  print(string.format('  delai %s s   attente %s s   decalage %s s',
        S.delai, S.attente, S.decalage))
  print(string.rep('=', 62))
end

-- relancer le script ne doit pas empiler les boucle
arreter()
S.auto = false
S.phase = 'inactif'
S.bilan()