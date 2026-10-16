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
-- LE VISAGE
--
-- « vise alors » — d'accord. On utilise la fonction du jeu pour se tourner,
-- faceToTarget(), et le calcul de probabilite du jeu pour choisir la cible,
-- CatchProbContext. Aucune de nososinventions.
--
-- Mesure : 32 ClientPuppet dans la zone, probabilites 0.6160 et 0.9240, et
-- 30 evaluations de probabilite en 1.0 ms. Le cout est negligeable.
--
-- Le choix se fait sur la PROBABILITE, pas sur la distance : c'est elle qui
-- decide du rendement, et la portee de la balle est un probleme different.
--
-- La sequence s'allonge d'un cran : apres throwItemFromBag (qui reconstruit le
-- contexte), on se tourne, on laisse le modele se poser, puis on lance.

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
S.orientation = S.orientation or 0.1
S.enCours = false
-- LE VISAGE EST DESACTIVE PAR DEFAUT, et c'est mesure :
--   19 cibles visees, 38 sessions, ZERO contact.
--
-- faceToTarget() fait bien tourner le modele -- rotation y : 0.898 juste apres
-- l'appel -- mais le controleur de locomotion l'ECRASE en 150 ms :
--
--   t000_immediat  y= 0.898
--   t015           y= 0.122
--   t200           y=-0.232
--
-- La balle part ou le personnage regarde, donc elle part ou le controleur
-- decide, et on vise dans le vide. OnHandleMoveDirection (la voie des sorts)
-- ne tient pas non plus.
--
-- Pour viser reelement il faudrait-feeding du locomotion input -- le personnage
-- fait un pas. C'est visible, et c'est une decision du joueur, pas une
-- possibilite que je constate. Le code est la, actif sur demande :
--     specter.capture.viser = true
S.portee = S.portee or 25        -- au-dela, la balle ne porte pas
S.vises = S.vises or 0
S.cible = nil
sp.capture = S

-- ---------------------------------------------------------------- recompenses
-- On compte les succes en observant l'entree. Pose une seule fois.

do
  local vGH = getmetatable(require('Core.Client.GateClientRpcHandler')).__index

  -- On remet l'original avant de poser la notre. Sans ca, chaque rechargement
  -- empile une couche de plus sur une fonction tres chaude : mesuree a 9.
  sp.store.hooks = sp.store.hooks or {}
  for i = #sp.store.hooks, 1, -1 do
    local h = sp.store.hooks[i]
    pcall(function() h.vtbl[h.cle] = h.orig end)
  end
  sp.store.hooks = {}

  local orig = rawget(vGH, 'entityMessageV2')
  sp.store.hooks[#sp.store.hooks + 1] = {vtbl = vGH, cle = 'entityMessageV2', orig = orig}

  if type(orig) == 'function' then
    vGH.entityMessageV2 = function(self, entityId, raw, index, context, ...)
      local nom = RpcIndex.INDEX2RPC[index] or RpcIndex.RPC_INDEX2NAME[index]
      if nom == 'RPC_SC_OnCaptureSuccess' then S.succes = S.succes + 1 end
      return orig(self, entityId, raw, index, context, ...)
    end
  end
end

-- ---------------------------------------------------------------- un lancer

-- Deux etapes, parce que le visage doit se faire ENTRE la creation du
-- contexte et le lancer : throwItemFromBag reconstruit le contexte, donc se
-- tourner avant ne servirait a rien.
--
-- declencher est declare ici et defini plus bas -- en Lua, un appel a un
-- local defini plus bas dans le fichier est un global, donc nil a l'execution.
-- Les deux fonctions d'en dessous sont appelees par lancer() et definies plus
-- bas. En Lua, un identifiant qualifie local qui n'est pas encore declare
-- devient un GLOBAL -- donc nil a l'execution, et un pcall qui rend false en
-- silence. C'est exactement ce qui est arrive : vises restait a 0 et le
-- script visaient personne, sans lever la moindre erreur.
-- ATTENTION : `local function choisirCible` creerait un NOUVEAU local qui masque
-- celui d ici. Il faut une affectation, pour que le nom designe bien le local
-- annonce plus haut. C'est la raison du `vises = 0` sans aucune erreur.
local declencher
local choisirCible

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

  -- 2. attendre que le contexte existe
  TM.addTimer(S.attente, function()
    local ctx = pg.me.currentContext
    if type(ctx) ~= 'table' or type(ctx.throwWithRpc) ~= 'function' then
      S.phase = 'contexte = ' .. tostring(ctx and ctx.className)
      S.enCours = false
      return
    end

    -- 3. viser. faceToTarget va sur faceToRotation -> setAgentRotation(..., true),
    --    qui est instantane ; le petit delai laisse seulement le modele se poser.
    S.cible, S.cibleProb, S.cibleDist = nil, nil, nil
    if S.viser then
      local okv, cible, prob, dist = pcall(choisirCible, itemId)
      if okv and cible then
        S.cible, S.cibleProb, S.cibleDist = cible.id, prob, dist
        S.vises = S.vises + 1
        -- ensemble des cibles qu'on a visees, pour verifier apres si la balle
        -- touche vraiment CE QUE NOUS VISONS
        S.choisi = S.choisi or {}
        S.choisi[cible.id] = true
        pcall(function() pg.me:faceToTarget(cible) end)
        TM.addTimer(S.orientation, function() declencher(ctx) end)
      else
        S.phase = 'aucune cible dans ' .. S.portee .. ' u'
        declencher(ctx)
      end
    else
      declencher(ctx)
    end
  end)
  return true
end

-- le FSM, puis le RPC decale. C'est le decalage qui fait la difference entre
-- un lancer accepte et un message ignore.
function declencher(ctx)
  local ok2, e2 = pcall(function() ctx:throw() end)
  if not ok2 then
    S.phase = 'throw a leve : ' .. tostring(e2)
    S.enCours = false
    return
  end

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
end

-- ---------------------------------------------------------------- cible
--
-- On demande au jeu, pour chaque ClientPuppet, sa probabilite de capture. Ce
-- n'est pas nous qui deciders si elle est capturable : c'est CatchProbContext,
-- le meme calcul que le HUD affiche.

function choisirCible(itemId)
  local moi = pg.me
  local p0 = moi:getPosition()
  if not p0 then return nil end

  local meilleure, meilProb, meilDist = nil, 0, nil

  for _, en in pairs(pg.getEntities() or {}) do
    local mt = getmetatable(en)
    local idx = mt and mt.__index
    if idx and idx.__CLASS_NAME__ == 'ClientPuppet' then
      local ok, q = pcall(function() return en:getPosition() end)
      if ok and q then
        local dx, dy, dz = q[1] - p0[1], q[2] - p0[2], q[3] - p0[3]
        local d = (dx * dx + dy * dy + dz * dz) ^ 0.5
        if d <= S.portee then
          -- getFromBehindCatchProb renvoie (prob, context)
          local okp, prob = pcall(function()
            return CCU.getFromBehindCatchProb(moi, en, itemId)
          end)
          if okp and type(prob) == 'number' and prob > 0 then
            -- probabilite d'abord, distance en egalite
            if prob > meilProb or (prob == meilProb and d < meilDist) then
              meilleure, meilProb, meilDist = en, prob, d
            end
          end
        end
      end
    end
  end

  return meilleure, meilProb, meilDist
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
  print(string.format('  delai %s s   attente %s s   decalage %s s   orientation %s s',
        S.delai, S.attente, S.decalage, S.orientation))
  print(string.format('  viser %s   portee %s u   vises %d', tostring(S.viser), S.portee, S.vises))
  if S.cible then
    print(string.format('  derniere cible %s   prob %.3f   a %.1f u',
          tostring(S.cible), S.cibleProb or -1, S.cibleDist or -1))
  end
  print(string.rep('=', 62))
end

-- relancer le script ne doit pas empiler les boucle
arreter()
S.auto = false
S.phase = 'inactif'
S.bilan()