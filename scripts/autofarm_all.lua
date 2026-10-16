-- autofarm_all.lua — COPIE de chest-open.lua, telle qu'elle behaves AUJOURD'HUI.
--
-- CE QUE CE SCRIPT FAIT REELLEMENT, MESURE EN JEU
--
-- Il n'ouvre PAS que des coffres. Il ouvre tout ce qui a une unite
-- d'interaction. Un run reel, scene 3000 :
--
--     # coffres NON OUVERTS ... : 12   [cache deja ouverts: 22]
--     U atHYy3O3S5olugzX  d=   0.7  Coffre
--     U atHYy3O3S5olugzc  d=  22.5  Aniipod
--     U atHYwnO3S5oluguv  d=  26.9  Aniipod
--     U atHYwnO3S5oluguj  d=  50.6  Aniipod pro
--     U atHY0XO3S5olug39  d=  51.8  Aniipod pro
--     U atHYwnO3S5olugu1  d=  61.6  Aniipod pro
--     U atHYy3O3S5olugzJ  d=  64.6  Oeuf Alpha
--     U atHYwnO3S5oluguQ  d=  70.8  Aniipod pro
--     U atHYwnO3S5oluguy  d=  72.0  Ramasser
--     U atHYwnO3S5oluguY  d=  82.2  Ramasser
--     U atHYwnO3S5olugum  d=  96.9  Aniipod
--     U atHYy3O3S5olugzV  d=  99.7  Ramasser
--     TOTAL_UNLOCKED=12
--     CHAIN_OPENS=10
--
-- UN SEUL "Coffre" sur douze. Les onze autres ont ete consommes aussi.
--
-- CE QUI A CHANGE DEPUIS : LES COFFRES SONT MAINTENANT ECARTES
--
-- On ne pouvait pas les distinguer -- markBindStaticId vaut nil SUR LES
-- COFFRES REELS AUSSI, et ent.id ne dit pas 10506 de 10505. Ce qui marche,
-- c'est la distance a la marque de registre : quand la marque la plus proche
-- est a moins de 3 u, c'est la sienne, et son markConfigId tranche.
--
--     nom          d(u)   cfgMarque   dMarque
--     Coffre        28.3      10506      0.5   -> ecarte
--     Ramasser      29.5      10506      2.6   -> ecarte
--     Ambre lumin   54.3      10505      0.0   -> garde
--
-- Un "Ramasser" peut donc etre un coffre : son nom d'affichage est le verbe
-- generique, pas sa nature. Filtrer sur le nom aurait laisse passer des coffres.
--
-- Regle : on ecarte quand SA marque, et seulement la sienne, porte 10506.
-- Pas de nom, pas de chaine, pas d'heuristique. Cout : 3 ms pour 2323 marques.
--
-- CE QUE CA DONNE A UTILISER
--
--   - de l'auto-farm d'Aniipods dans la nature : c'est exactement ca.
--   - ouvrir des coffres SANS toucher aux Aniipods : chest-open.lua. Ne pas
--     l'appeler en croyant qu'il est restrictif -- il ne l'est pas.
--
-- L'ETAT EST PARTAGE AVEC chest-open.lua
--
-- Les deux scripts lisent et ecrivent le meme `specter.store.chests` : meme
-- cache d'ouverts, meme verrou `running`. Lancer l'un alors que l'autre
-- tourne donne 'ERROR: une chaine est deja en cours.' C'est voulu ici -- cette
-- copie est une copie, pas une variante. Pour les faire tourner cote a cote,
-- il faut un nom de store distinct, et c'est un changement de comportement.
--
-- Pour arreter une chaine deja lancee, depuis un autre chunk :
--     specter.store.chests.cancel = true
--
-- Réglages :
local CHAIN_OPENS  = 10      -- nb de coffres à ouvrir par exécution (0 = tout)
local BREATH       = 0.5     -- s, pause entre deux ouvertures
local WAIT_AFTER_TP = 0.5    -- s, à attendre APRÈS le TP avant d'interagir
local TRY_SECONDS  = 5       -- fenêtre pour trouver l'entité + son unité
local INTERACT_TYPE = 1      -- interactionType du coffre (actif / ENT_FUNC)
local MAX_LIST     = 40      -- lignes imprimées au plus
local ARRIVED_D    = 2.5     -- u : on considère arrivé en dessous
local OPEN_ENABLED = true    -- false = TP seulement (vers le plus proche)
-- Utiliser le registre des marques quand AUCUNE entité n'est chargée autour.
-- OFF par defaut, et mesure a l'appui : en scene 3000, 194 marques
-- deverrouillees pour 4 coffres reellement charges, et AUCUNE marque ne
-- correspondait a une entite. Le registre sert a savoir QUOI il y a dans la
-- scene, pas a ou aller maintenant.
local USE_REGISTRY = false

-- Usage : tools/lua.sh -f scripts/chest-open.lua   (En jeu uniquement)
--
-- Pour arrêter une chaîne déjà lancée, depuis un autre chunk :
--     specter.store.chests.cancel = true

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')
local TM  = require('Core.Timer.TimerManager')

-- ---------------------------------------------------------- garde : le TP existe
if type(specter.tp) ~= 'table' or type(specter.tp.here) ~= 'function' then
  print('ERROR: specter.tp.here absent. scripts/init.lua ne tourne pas ?')
  return
end

local function tpHere(x, y, z)
  -- Le pas et la vitesse viennent de l'onglet Teleport (specter.var.tp_step /
  -- tp_speed), pas de constantes ici : c'est le meme déplacement que celui du
  -- menu, donc les memes réglages.
  specter.tp.here(x, y, z)
end

local function tpStop()
  if specter.tp and type(specter.tp.stop) == 'function' then
    pcall(specter.tp.stop)
  end
end

local function localize(id)
  if not id then return nil end
  local ok, t = pcall(CTU.getLocalizationText, id)
  if ok and t and t ~= '' then return t end
  return nil
end

local e = pg.me
if not e or not e.getPosition then
  print('ERROR: pas de joueur')
  return
end

local function maPosition()
  local ok, p = pcall(function() return e:getPosition() end)
  if ok and p then return p end
  return nil
end

local function distance(p, x, y, z)
  return ((p[1] - x) ^ 2 + (p[2] - y) ^ 2 + (p[3] - z) ^ 2) ^ 0.5
end

-- ------------------------------------------------------------------ notre état
local ETAT = specter.store.chests
if type(ETAT) ~= 'table' then
  ETAT = {}
  specter.store.chests = ETAT
end

-- Un run precedent peut avoir laisse des timers si le jeu a crashé ou si le
-- joueur s'est déconnecté. On les récupère avant tout, sinon `running'
-- resterait vrai indéfiniment et personne ne pourrait plus relancer.
local function nettoyerTimers()
  for _, nom in ipairs({ 'poll', 'breath' }) do
    local t = ETAT[nom]
    if t then
      pcall(function() TM.removeTimer(t) end)
      ETAT[nom] = nil
    end
  end
end
nettoyerTimers()

-- Un run peut mourir SANS laisser le verrou : le jeu a crashé, le joueur s'est
-- deconnecté, une erreur a tue un timer. Dans ce cas il ne reste aucun timer
-- vivant, et refuser indefiniment serait la seule facon de ne jamais relancer.
-- On recycle donc un verrou sans timer plutot que de coincer le script.
if ETAT.running and not ETAT.poll and not ETAT.breath then
  print('ETAT: chaine orpheline sans timer, on repart')
  ETAT.running = false
end

if ETAT.running then
  print('ERROR: une chaine est deja en cours.')
  print('       Pour l arreter :  specter.store.chests.cancel = true')
  return
end

ETAT.running = true
ETAT.cancel = false
ETAT.done = 0
local opened = type(ETAT.opened) == 'table' and ETAT.opened or {}
ETAT.opened = opened

-- markConfigId du vrai coffre. Sert au registre (priorite 2) ; pour les
-- entites vivantes, c'est CFG_COFFRE plus bas qui fait le travail.
local CHEST_CONFIG = 10506

-- IDENTIFIER UNE CIBLE
--
-- `markBindStaticId` est la facon evidente, et elle ne marche pas. Mesure, en
-- jeu, colle au coffre :
--
--     unites d'interaction : type=1  globalId=atHYy3O3S5olugzX  (chaine)
--     coffre a 1.4 u       : mbsid=nil  cfg=nil  id=atHYy3O3S5olugzX
--
-- markBindStaticId est NIL sur le coffre qui est LA. Donc isCoffre(nil)
-- renvoyait faux, et le coffre n'entrait JAMAIS dans la liste de cibles :
-- la chaine partait, le TP partait vers ce qu'elle avait retenu ailleurs, et
-- zero coffre n'etait jamais ouvert.
--
-- Ce qui n'est jamais nul, c'est `ent.id` -- et c'est exactement la valeur que
-- l'unite d'interaction porte dans `globalId`. C'est donc par LA que le jeu
-- reconnait une cible, et c'est par la que nous le faisons.
--
-- markBindStaticId reste utile quand il existe : il identifie le coffre dans le
-- registre et permet de le retrouver apres un despawn. On s'en sert comme CLE
-- DE CACHE quand il est present, et on retombe sur ent.id sinon.
local function identifiant(en)
  if en.markBindStaticId ~= nil then
    return en.markBindStaticId
  end
  return en.id
end

-- ---------------------------------------------------------- CLASSER UNE CIBLE
--
-- On ne veut PAS de coffres ici : on veut les Aniipods, les Ambre, les
-- ramassages. Il faut donc distinguer 10506 (coffre) du reste -- et
-- markBindStaticId, qui le faisait, vaut nil partout.
--
-- CE QUI RESTE, MESURE EN JEU, SCENE 3000
--
--     entite            1re marque   cfg      2e marque
--     Coffre               0.5 u   10506      27.7 u
--     Ramasser (coffre)    2.6 u   10506      19.6 u
--     Ambre lumin          0.0 u   10505      15.3 u
--     Ambre lumin          0.0 u   10505      17.1 u
--     Ambre lumin          0.0 u   10505      37.6 u
--     Ambre lumin          0.0 u   10505      38.1 u
--     Aniipod             13.9 u   10505      30.3 u
--     Oeuf d'elite         7.4 u   10506      10.6 u
--     Aniipod pro         24.5 u    102      28.0 u
--
-- Trois choses tombent du tableau.
--
-- 1. Quand la 1re marque est a moins de 3 u et la 2e a plus de 15, l'entite et
--    la marque c'est la meme objet : c'est SA marque. Le critere est donc
--    `dMarque <= 3`, et au-dela on ne classe pas.
--
-- 2. Un "Ramasser" PEUT ETRE UN COFFRE. Celui a 2.6 u porte cfg 10506 : son
--    nom d'affichage est le verbe generique, sa nature est celle d'un coffre.
--    Filtrer sur le nom affiche aurait donc laisse passer des coffres.
--
-- 3. cfg 10506 n'est PAS "coffre" au sens de ce qu'on veut ramasser : un
--    "Oeuf d'elite" en porte aussi. Il est a 7.4 u de sa marque, donc il n'est
--    PAS classe, donc il est garde. C'est le bon choix ici -- un oeuf n'est pas
--    un coffre.
--
-- TAILLE D'ECHANTILLON : DEUX COFFRES. 0.5 u et 2.6 u. Le seuil de 3 u les
--    couvre tous les deux, avec 0.4 u de marge sur le pire. Ce n'est pas une
--    loi du jeu, c'est deux observations -- si un troisieme coffre sortait avec
--    sa marque a 4 u, il passerait au travers. Le compteur
--    "# coffres ECARTES" sert a le voir.
--
-- LIMITES, DITES TELLES QU'ELLES SONT
--
--   - une entite dont la marque n'est pas chargee n'est pas classee, et elle est
--     donc GARDEE. Un coffre non classe peut etre ramasse. C'est le choix
--     inverse de chest-open.lua, et c'est le bon ici : un Aniipod rate coute
--     une ressource, un coffre pris par erreur ne coute qu'un coffre.
--   - l'inverse existe aussi : une entite a moins de 3 u de la marque d'un
--     VOISIN sera ecartee a tort. Rare -- la 2e marque est presque toujours a
--     plus de 15 u.
--   - cout : 3 ms pour 2323 marques, une fois par collecte.
local MARQUE_ASSOC_D = 3     -- u : en dessous, c'est SA marque
local CFG_COFFRE    = 10506  -- markConfigId du vrai coffre

local marques = nil
local marquesScene = nil   -- les marques sont par scene : on ne les recycle pas

local function indexerMarques()
  local sid = e.sceneId
  if marques and marquesScene == sid then return marques end
  local ok, pts = pcall(SU.getSceneMarkPointData, sid)
  local out = {}
  if ok and type(pts) == 'table' then
    for _, mp in pairs(pts) do
      -- `markPosition` est un userdata VECTEUR : markPosition[1..3], pas
      -- .x/.y/.z. SceneUtils.lua:340 fait Vector3.Clone(point.markPosition).
      local P = mp.markPosition
      if P and P[1] then
        out[#out + 1] = { x = P[1], y = P[2], z = P[3], cfg = mp.markConfigId }
      end
    end
  end
  marques, marquesScene = out, sid
  return out
end

-- Retourne le markConfigId de l'entite, ou nil si on n'est pas sur de l'avoir
-- identifiee. nil se distingue de 10505 : "je sais ce que c'est" / "je ne sais pas".
local function cfgDeLEtat(x, y, z)
  local mk = marques or indexerMarques()
  local bd, bc
  for i = 1, #mk do
    local M = mk[i]
    local d = ((M.x - x) ^ 2 + (M.y - y) ^ 2 + (M.z - z) ^ 2) ^ 0.5
    if not bd or d < bd then bd, bc = d, M.cfg end
  end
  if bd and bd <= MARQUE_ASSOC_D then return bc end
  return nil
end

-- ----------------------------------------------------------- collecte cible
local function collectTargets()
  local pnow = maPosition()
  if not pnow then return {}, {} end

  -- Priorité 1 : entités ClientChest VIVANTES donc disponibles (ouvertes par
  -- construction). Un coffre déjà ouvert par nous est caché par `opened`
  -- ci-dessous, même si son entité traîne encore (despawn lent).
  local byLive, ecartees = {}, 0
  for _, en in pairs(pg.getEntities() or {}) do
    if en.isChest and en.chestValid then
      local okp, p = pcall(function() return en:getPosition() end)
      if okp and p then
        local cfg = cfgDeLEtat(p[1], p[2], p[3])
        if cfg == CFG_COFFRE then
          -- Coffre confirme par SA marque : on ne le prend pas.
          ecartees = ecartees + 1
        else
          byLive[#byLive + 1] = {
            id = identifiant(en),
            entId = en.id,
            x = p[1], y = p[2], z = p[3],
            d = distance(pnow, p[1], p[2], p[3]),
            name = localize(en.configName) or 'Ramassage',
            cfg = cfg,          -- nil = on n'a pas su le classer
          }
        end
      end
    end
  end
  table.sort(byLive, function(a, b) return a.d < b.d end)
  ETAT.coffresEcartes = ecartees

  -- Priorité 2 : marques Coffre (cfg 10506) déverrouillées (registre).
  local unlocked = {}
  local mu = pg.game and pg.game.map and pg.game.map.markUnlocker
  if mu and mu.unlockChunkMap then
    for _, cv in pairs(mu.unlockChunkMap) do
      for _, id in pairs(cv or {}) do
        if type(id) == 'number' then
          unlocked[id] = true
        end
      end
    end
  end

  local rows = {}
  local ok, pts = pcall(SU.getSceneMarkPointData, e.sceneId)
  if ok and type(pts) == 'table' then
    for id, p in pairs(pts) do
      if p.markConfigId == CHEST_CONFIG and p.markPosition and unlocked[id] then
        local mp = p.markPosition
        rows[#rows + 1] = {
          id = id,
          x = mp[1], y = mp[2], z = mp[3],
          d = distance(pnow, mp[1], mp[2], mp[3]),
          name = localize(p.infoTitle) or '',
        }
      end
    end
  end

  -- Filtre cache : les ids déjà ouverts ne réapparaissent jamais par la seule
  -- présence d'une entité (despawn lent) — c'est la source de vérité.
  local function dropCached(listIn)
    local out = {}
    for _, r in ipairs(listIn) do
      if not opened[r.id] then
        out[#out + 1] = r
      end
    end
    return out
  end

  return dropCached(byLive), dropCached(rows)
end

-- ------------------------------------------------------------------ machine
local curTarget
local chainActive = true

local function finish(reason)
  chainActive = false
  nettoyerTimers()
  tpStop()
  ETAT.running = false
  ETAT.finish = reason
  ETAT.done = ETAT.done or 0
  print('FIN ' .. tostring(reason) .. ' ouverts=' .. tostring(ETAT.done))
end

-- Choisit la cible, lance le TP si besoin, puis le polling d'interaction.
local startCycle

local function onOpened()
  ETAT.done = (ETAT.done or 0) + 1
  opened[curTarget.id] = true
  ETAT.lastId = curTarget.id
  local n = ETAT.done
  ETAT.breath = TM.addRepeatTimer(BREATH, function()
    nettoyerTimers()
    if chainActive then
      startCycle()
    end
  end)
  print(string.format('CHAIN %d ok id=%s', n, tostring(curTarget.id)))
end

local function startPoll()
  nettoyerTimers()
  local tries = 0
  local waited = 0
  local target = curTarget
  local marker, mx, my, mz = target.id, target.x, target.y, target.z
  local waitTicks = math.max(0, math.floor(WAIT_AFTER_TP / 0.15))

  ETAT.poll = TM.addRepeatTimer(0.15, function()
    -- Toute la logique est sous pcall. Une erreur ici laisserait le timer
    -- alive et `running' a true, et la seule facon de s'enULES sortir serait
    -- de relancer le jeu : un script doit toujours pouvoir s'arreter lui-meme.
    local ok, err = pcall(function()
      if not chainActive or ETAT.cancel then
      finish(ETAT.cancel and 'CANCEL' or 'STOP')
      return
    end

    -- Attente de l'arrivée. C'est une MESURE DE DISTANCE, pas un drapeau de
    -- lerp : le déplacement appartient à specter.tp.here, et ce script n'a
    -- rien à savoir de son état interne.
    local pnow = maPosition()
    if not pnow then
      tries = tries + 1
      if tries * 0.15 > TRY_SECONDS then finish('NOPOS') end
      return
    end
    local d = distance(pnow, mx, my, mz)
    if d > ARRIVED_D then
      tries = tries + 1
      if tries * 0.15 > TRY_SECONDS then finish('TP_TIMEOUT') end
      return
    end

    -- Fenêtre configurée après le TP avant d'interagir.
    if waited < waitTicks then
      waited = waited + 1
      return
    end

    -- 1) l'entité liée à la cible.
    --
    -- On la retrouve par le meme identifiant que celui de la liste, et par son
    -- `ent.id` : c'est la valeur que l'unité d'interaction porte dans
    -- `globalId`, donc c'est celle qui apparait dans unitMap quand on est à
    -- portée.
    local ent
    for _, en in pairs(pg.getEntities() or {}) do
      if en.isChest and (identifiant(en) == marker or en.id == marker) then
        ent = en
        break
      end
    end

    -- 2) son unité d'interaction
    local it = pg.game and pg.game.interaction
    local unit
    if ent and it and it.unitMap then
      local byType = it.unitMap[INTERACT_TYPE]
      if type(byType) == 'table' then
        for _, u in pairs(byType) do
          if type(u) == 'table' and u.globalId == ent.id then
            unit = u
            break
          end
        end
      end
    end

    if not unit then
      tries = tries + 1
      if tries * 0.15 > TRY_SECONDS then
        -- Entité morte ou absente. Si on est collé au point, c'est un coffre
        -- du registre déjà ouvert (désync) : on le marque et on enchaîne.
        if d <= 3 then
          opened[marker] = true
        end
        startCycle()
      end
      return
    end

    nettoyerTimers()
    local okr, res = pcall(function() return it:doUnitInteractive(unit) end)
    print('OPEN_INTERACT ok=' .. tostring(okr) .. ' id=' .. tostring(marker))
    ETAT.lastInteractOk = okr
    if okr then
      onOpened()
    else
      -- Un echec d'interaction ne prouve pas que le coffre est ouvert : ca
      -- peut etre un ramassage (10505) que le filtre n'a pas su ecarter parce
      -- que markBindStaticId manquait. On passe au suivant plutot que de
      -- finir -- sinon une cible erronee arrete toute la chaine.
      ETAT.lastInteractOk = false
      startCycle()
    end
    end)

    if not ok then
      print('ERREUR dans le cycle : ' .. tostring(err))
      finish('ERROR')
    end
  end)
end

startCycle = function()
  if not chainActive then return end
  if ETAT.cancel then finish('CANCEL') return end
  if CHAIN_OPENS > 0 and (ETAT.done or 0) >= CHAIN_OPENS then
    finish('OK')
    return
  end

  local byLive, rows = collectTargets()
  -- JAMAIS de repli aveugle sur le registre. Mesure, en jeu :
  --
  --   scene 3000
  --   entites ClientChest chargees ... 10   (dont 4 reellement 10506)
  --   marques Coffre deverrouillees ..... 194
  --   dont avec une entite vivante ....... 0
  --   distance mediane jusqu a une marque : 397 u
  --
  -- Une marque du registre n'a pas d'entite tant qu'on n'est pas alle la
  -- charger. Se téléporter dessus, c'est se téléporter dans le vide -- et c'est
  -- exactement la question "je me TP a des chests invisible ?".
  --
  -- Donc : entites vivantes, ou rien.
  local list = byLive
  if USE_REGISTRY and #byLive == 0 then
    list = rows
    print('REGISTRE: ' .. #rows .. ' marque(s) -- many ont AUCUNE entite, le TP '
          .. 'peut atterrir dans le vide')
  end
  if #list == 0 then
    finish('NP')
    return
  end

  local t = list[1]
  local pnow = maPosition()
  if not pnow then finish('NOPOS') return end
  local dist = distance(pnow, t.x, t.y, t.z)

  curTarget = t
  if (ETAT.done or 0) > 0 then
    print(string.format('CHAIN %d -> id=%s d=%6.1f',
                        ETAT.done + 1, tostring(t.id), dist))
  end

  if dist >= ARRIVED_D then
    tpStop()                       -- annule un éventuel déplacement en cours
    tpHere(t.x, t.y, t.z)
    print(string.format('TP_TO id=%s d=%6.1f', tostring(t.id), dist))
  end

  startPoll()
end

-- ---------------------------------------------------------- affichage initial
local nCache = 0
for _ in pairs(opened) do nCache = nCache + 1 end

local byLive0, rows0 = collectTargets()
local list0 = byLive0
local source0 = 'entités vivantes'
if USE_REGISTRY and #byLive0 == 0 then
  list0 = rows0
  source0 = 'registre (RISQUE : marques sans entité)'
end

-- On affiche aussi ce qu'on ECarte, et pourquoi. Un compteur de "ignorés" sans
-- raison n'apprend rien ; avec la raison, on sait si le filtre fait son travail.
print(string.format('# cibles NON OUVERTES (scene %s, source: %s) : %d  [cache déjà ouverts: %d]',
                     tostring(e.sceneId), source0, #list0, nCache))
-- Les coffres qu'on a laisse Deliberement tranquilles. C'est LA mesure qui dit
-- si le filtre marche : sans ce nombre, "0 cible" est indistinguable de
-- "0 cible parce que j'ai tout ecarte".
print(string.format('# coffres ECARTES (marque 10506 confirmee a <= %d u) : %d',
                    MARQUE_ASSOC_D, ETAT.coffresEcartes or 0))
print(string.format('# marques au registre IGNOREES (aucune entité = TP dans le vide) : %d',
                     #rows0))
for i, r in ipairs(list0) do
  if i > MAX_LIST then
    print(string.format('... (%d de plus)', #list0 - MAX_LIST))
    break
  end
  -- cfg nil = on n'a pas su classer cette cible : elle est gardee, et on le dit.
  print(string.format('U %s %.2f %.2f %.2f d=%7.1f cfg=%-5s %s',
                     tostring(r.id), r.x, r.y, r.z, r.d, tostring(r.cfg or '?'), r.name))
end
print('TOTAL_UNLOCKED=' .. #list0)

if #list0 == 0 then
  finish('NP')
  return
end

if not OPEN_ENABLED then
  -- Mode TP seulement : on se pose sur le plus proche, sans ouvrir.
  local t = list0[1]
  local pnow = maPosition()
  if pnow and distance(pnow, t.x, t.y, t.z) < ARRIVED_D then
    print('ALREADY_HERE id=' .. tostring(t.id))
    finish('OK')
    return
  end
  tpHere(t.x, t.y, t.z)
  print(string.format('TP_ONLY id=%s', tostring(t.id)))
  finish('OK')
  return
end

if CHAIN_OPENS > 0 then
  print('CHAIN_OPENS=' .. CHAIN_OPENS)
end
print('ANNULER :  specter.store.chests.cancel = true')
startCycle()