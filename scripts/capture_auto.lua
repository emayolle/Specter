-- capture_auto.lua -- lancer des balles sans passer par le context du jeu.
--
--   tools/lua.sh -f scripts/capture_auto.lua     demarre / arrete
--   tools/lua.sh -f scripts/capture_auto.lua     affiche le bilan
--
--   specter.capture.auto  = true / false
--   specter.capture.delai = secondes entre deux lancers
--   specter.capture.lancer()  un lancer, a la main
--   specter.capture.bilan()
--
--
-- LE PRINCIPE
--
-- On appelle exactement ce que le bouton appelle : toggleCatchMode(), puis
-- ctx:throwWithRpc(). Rien de forge.
--
-- La piste des RPC bruts a ete mesuree et elle est morte. Envoyer
-- CaptureHoldBall + FireBall a la main revient avec code = 0 -- mais AUCUN
-- message en retour, pas de RPC_SC_OnFireBall, pas de session. Le serveur
-- acquitte et ignore : aucun etat ne correspond. L'etat, c'est
-- ForceChangeToUpperState(THROWHOLD), qui part par RPC_CS_CharacterStateChange.
--
-- Ni camera ni rotation : doSwitch() est la seule methode qui touche au
-- pilotage et elle ne sert qu'a changer d'objet. La balle part devant soi.
--
-- Ce qu'on ne touche pas, c'est le resultat : le serveur a refuse notre
-- BallHitEntity forge (ERROR_INVALID_TARGET, 1010). On lance plus vite, on ne
-- reussit pas plus.

local sp = specter
local TM = require('Core.Timer.TimerManager')
local CCU = require('Utils.ClientCaptureUtils')

-- ---------------------------------------------------------------- etat

local S = sp.store.capture
if not S then S = {} sp.store.capture = S end
S.auto = S.auto or false
S.delai = S.delai or 3
S.lancers = S.lancers or 0
S.refus = S.refus or 0
S.code = nil
S.phase = S.phase or 'inactif'
S.erreurs = S.erreurs or {}

local timer = nil

-- ---------------------------------------------------------------- un lancer

-- On passe par l'API du jeu, pas par des RPC bruts : c'est la seule voie que
-- le serveur accepte. Mesure : CaptureHoldBall + FireBall envoyes a la main
-- reviennent avec code = 0 mais SANS aucun message en retour -- le serveur
-- acquitte la prise en charge et ignore la suite, parce qu'aucun etat ne
-- correspond. L'etat, c'est ForceChangeToUpperState(THROWHOLD), qui remonte
-- par RPC_CS_CharacterStateChange (585 vus dans le journal).
--
-- Donc : on appelle ce que le bouton appelle. Rien de forge, rien de force.
--
-- Et surtout : AUCUNE rotation, AUCUNE camera. ThrowBallContext:doSwitch() est
-- la seule methode qui touche au pilotage (setSteering, CAPTURE_STEERING_TIME)
-- et elle ne sert qu'a changer d'objet. Le chemin du lancer n'y passe pas.
-- On tient une balle et on lance devant soi -- exactement comme le bouton.

local function lancer()
  S.phase = 'choix de la balle'

  -- 1. une balle reelle que le joueur possede : le controle du jeu, pas le
  --    notre. Sans balle, ca ne peut pas marcher.
  local itemId = CCU.getFirstUsableNormalBallItemId()
  if not itemId then
    S.phase = 'aucune balle utilisable'
    return false
  end

  -- 2. etre en mode capture, pour que l'etat soit reel cote serveur
  if not pg.me:isInCatchMode() then
    S.phase = 'entree en mode capture'
    local ok, err = pcall(function() pg.me:toggleCatchMode() end)
    if not ok then
      S.phase = 'toggleCatchMode a leve : ' .. tostring(err)
      return false
    end
  end

  -- 3. le lancer, par le context du jeu
  local ctx = pg.me.currentContext
  if type(ctx) ~= 'table' or type(ctx.throwWithRpc) ~= 'function' then
    S.phase = 'context = ' .. tostring(ctx and ctx.className) .. ' (pas de throwWithRpc)'
    return false
  end

  S.phase = 'envoi'
  local ok, err = pcall(function()
    ctx:throwWithRpc(
      function() S.code = 0 end,
      function(code)
        S.code = code
        S.refus = S.refus + 1
        local cle = tostring(code)
        S.erreurs[cle] = (S.erreurs[cle] or 0) + 1
      end,
      function() S.phase = 'delai depasse (2 s)' end)
  end)
  if not ok then
    S.phase = 'throwWithRpc a leve : ' .. tostring(err)
    return false
  end

  S.lancers = S.lancers + 1
  S.phase = 'lance'
  return true
end

-- ---------------------------------------------------------------- boucle

local function armer()
  if timer then return end
  timer = TM.addTimer(S.delai, function()
    if S.auto then pcall(lancer) end
    armer()
  end)
end

local function arreter()
  if timer then pcall(function() TM.removeTimer(timer) end) end
  timer = nil
end

-- ---------------------------------------------------------------- commande

sp.capture = S

function S.lancer() lancer() end
function S.on()  S.auto = true;  armer();  S.phase = 'auto' end
function S.off() S.auto = false; arreter(); S.phase = 'arrete' end

function S.bilan()
  print('')
  print(string.rep('=', 60))
  print(string.format('  lancers %d      refus %d      phase %s',
        S.lancers, S.refus, tostring(S.phase)))
  print(string.format('  dernier code = %s      delai = %s s', tostring(S.code), tostring(S.delai)))
  print(string.format('  mode capture = %s      context = %s',
        tostring(pg.me:isInCatchMode()), tostring(pg.me.currentContext and pg.me.currentContext.className)))
  if next(S.erreurs) ~= nil then
    print('  codes de refus :')
    for code, n in pairs(S.erreurs) do
      print(string.format('    %-8s x%d', code, n))
    end
  end
  print(string.rep('=', 60))
end

-- relance du script = arret puis affichage, pour ne pas empiler les boucle
arreter()
S.auto = false
S.phase = 'inactif'
S.bilan()
print('  specter.capture.on() / .off() / .lancer() / .bilan()')