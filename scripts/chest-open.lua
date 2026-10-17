-- chest-open.lua — la boucle d'ouverture des COFFRES, TOURNANT EN PERMANENCE.
--
-- EMBARQUE dans la DLL, execute une fois par nouveau lua_State juste apres
-- scripts/init.lua. Il ne fait rien tant que `specter.var.coffres` est faux :
-- la case a cocher du menu est la seule chose qui decide.
--
-- Sur le modele exact de scripts/autofarm_loop.lua : un pilote, un drapeau, deux
-- stockages. Meme confort, meme defaut de depart -- une case qui dit « coche »
-- sans dire si la boucle tourne.
--
--
-- 1. POURQUOI CE SCRIPT OUVRAIT TOUT, ET PAS SEULEMENT LES COFFRES
--
-- Le nom du fichier ne mentait pas par hasard. Mesure, en jeu, scene 3000 :
--
--     # coffres NON OUVERTS (source: entités vivantes) : 19
--     U atHbWnO3S5oluqug  d=  19.0  Ramasser
--     U atHa23O3S5oluo1K  d=  19.2  Aniipod
--     U atHbWnO3S5oluqut9 d=  26.0  Ramasser
--     U atHbWnO3S5oluquN  d=  29.6  Ramasser
--     U atHbWnO3S5oluquE  d=  36.2  Aniipod pro
--     ...                                    (1 seul coffre sur 19)
--
-- Sur dix-neuf cibles : UN coffre, dix-huit Aniipods, ramassages et creatures.
-- Sur les douze lignes de la toute premiere version, il y en avait UN de
-- « Coffre ». La version actuelle du fichier l'annoncait dans son en-tete, et le
-- diagnostic etait juste -- c'est le filtre qui ne l'etait pas.
--
-- LA CAUSE, MESUREE. `isChest` ne filtre rien : le jeu le pose sur les
-- ramassages, les Aniipods et les oeufs. Le filtre qui devait trancher etait
--
--     estCoffre(en) = markCfg[en.markBindStaticId] == 10506
--
-- terminé par :
--
--     if type(mbsid) == 'number' then
--         return markCfg[mbsid] == CHEST_CONFIG
--     end
--     return true   -- identité inconnue : on tente, l'interaction tranchera
--
-- Or `markBindStaticId` est nil sur les entités reelles. Mesure, collé au
-- coffre : `mbsid=nil  cfg=nil  id=atHYy3O3S5olugzX`. Donc `estCoffre(nil)`
-- rendait `true`, et TOUT entrait dans la liste.
--
-- Ce « on tente » n'etait pas de la prudence : c'etait l'erreur. Il n'y a rien a
-- tenter. Une interaction sur un Aniipod, c'est le Ramassage de l'Aniipod. La
-- ligne-commentaire disait « l'interaction tranchera » ; elle ne tranche rien,
-- elle consomme ce qu'elle trouve.
--
--
-- 2. CE QUI FAIT UN COFFRE : DEUX SIGNAUX POSITIFS, ET UN DEFAUT STRICT
--
-- Regle A — LE TEMPLATE. Mesure, toutes classes d'entités confondues, rayon 60 :
--
--       7.8  ClientChest          tpl=11134  chest=true
--      27.2  ClientChest          tpl=11042  chest=true     <- Ambre lumin
--      45.3  ClientChest          tpl=11011  chest=true
--      47.9  ClientChest          tpl=11001  chest=true
--      21.0  ClientCollectItem    tpl=14001  chest=nil
--      20.3  ClientDandelion      tpl=11     chest=nil
--      26.6  ClientPuppet         tpl=201401 chest=nil
--
-- Toutes les entités `isChest` sont des `ClientChest`, et `ClientChest` couvre
-- l'Ambre lumin (tpl 11042) comme les vrais coffres. La classe ne suffit donc
-- pas, mais le TEMPLATE, si : `Data.chest_data` est la table de config du jeu,
-- indexée par id d'objet, et chaque entité y porte le `markConfigId` de SA
-- marque. Voir parTemplate() plus bas pour la mesure complete et pour le piege
-- qui a coûté douze cibles sur vingt-cinq.
--
-- Regle B — LA MARQUE. `markConfigId == 10506` sur la marque la plus proche, à
-- moins de 3 u. C'est le filtre que porte déjà scripts/autofarm_loop.lua, mais
-- en négatif : l'autofarm écarte ces 10506, cette boucle les garde. Les deux
-- boucles se complètent, aucune ne peut attraper la cible de l'autre.
--
--     d= 28.3  Coffre        cfg a <= 3 u = 10506
--     d= 29.5  Ramasser      cfg a <= 3 u = nil
--     d= 49.2  Ramasser      cfg a <= 3 u = nil
--     d= 54.3  Ambre lumin   cfg a <= 3 u = 10505
--     d=193.5  Ambre lumin   cfg a <= 3 u = 10505
--
-- MESURE FINALE, les deux règles en place, scene 3000 :
--
--     25 entités isChest -> 9 verdicts COFFRE, 0 désaccord avec le nom du jeu
--
-- Apres correction. Avant, la regle A laissait passer 12 cibles non-coffres.
--
-- POURQUOI DEUX REGLES, ET PAS UNE.
--
--   - la règle B manque des coffres réels. Mesuré : une entité « Coffre » sans
--     marque 10506 à moins de 3 u (`U atHdxHO3S5oluzRS ... cfg=?  Coffre`) ;
--   - la règle A depend de `Data.chest_data`, qui peut ne pas être chargée au
--     premier passage. Elle est donc enclose, et son échec est visible.
--
-- L'une rattrape l'autre, et le défaut reste strict : une entité qui ne
-- correspond à AUCUNE des deux est ÉCARTÉE. Rater un coffre est un manque, que
-- le cycle suivant rattrape ; ouvrir un Aniipod est une faute qu'aucun cycle ne
-- rattrape. C'est l'inverse exact du « on tente » d'avant, et c'est la règle
-- qu'on s'est donné APRÈS l'avoir violée une fois dans ce même fichier.
--
--
-- 3. ON NE COMPTE QUE CE QUI A DISPARU
--
-- Rendre sans erreur n'est pas avoir ouvert. Un coffre met 1.2 s d'animation
-- (`Data.interact_data[59].actionTime`) plus le despawn à s'éteindre. Le
-- compteur n'augmente qu'après avoir VU l'entité s'en aller ; sinon il compte
-- des appels d'API, et une case qui affiche 40 coffres alors qu'il n'y en a eu
-- que 12 est une case qui ment.
--
--
-- 4. UN SEUL DEPLACEMENT A LA FOIS
--
-- `specter.tp.here` annule le deplacement precedent : les deux boucles ne
-- peuvent pas se teleporter en meme temps sans s'annuler l'une l'autre, et
-- aucune n'arrive jamais. Donc quand `specter.var.autofarm` est vrai, cette
-- boucle s'ecarte et le dit (phase 4). Cocher les deux cases n'ouvre pas deux
-- fois plus vite : ca ouvre les coffres quand l'auto-farm se tait.
--
--
-- PAS DE `return` AU NIVEAU PRINCIPAL.
--
-- init.lua, autofarm_loop.lua et ce fichier sont concatenes en UN chunk par
-- features/init/init.cpp. Un `return` au niveau principal arreterait le chunk
-- la ou il se trouve, et tous les scripts qui suivent ne tourneraient JAMAIS,
-- sans erreur visible. Ici, on sort d'une fonction ; on ne sort pas du chunk.
--
-- Arreter a la main :  specter.var.coffres = false

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')
local TM  = require('Core.Timer.TimerManager')

-- ------------------------------------------------------------------ reglages
local BREATH         = 1.2   -- s, pause apres une ouverture confirmee
local TRY_SECONDS    = 4     -- s, pour que le TP arrive
local GRACE_UNITE    = 1.5   -- s, a l'arrivee, pour que l'unite apparaisse
local CONFIRM_TICKS  = 4     -- s, pour voir DISPARAITRE la cible (anim 1.2 s)
local INTERACT_TYPE  = 1     -- ENT_FUNC
local ARRIVED_D      = 2.5   -- u : arrive en dessous
local MARQUE_ASSOC_D = 3     -- u : en dessous, c'est SA marque
local CFG_COFFRE     = 10506 -- markConfigId du vrai coffre
local CELL           = 24    -- u, cellule de la grille des marques
local RETRY_S        = 3     -- s, quand il n'y a plus rien a faire
local PILOTE_S       = 0.5   -- s, lecture de la case
local MAX_TRACE      = 20

-- ------------------------------------------------------------------- etat
--
-- Notre store, pas un champ sur pg.me : un nom a nous sur une table du jeu se
-- voit, et disparait au relog.
-- La phase « joueur mort ». DISTINTE de « attend », parce que les deux se
-- ressemblent a l'ecran -- une boucle immobile -- et que l'un demande d'attendre
-- et l'autre de ressusciter.
local PHASE_MORT = 5

local E = specter.store.chests
if type(E) ~= 'table' then
    E = {}
    specter.store.chests = E
end
E.running  = false
E.cancel   = false
E.phase    = 0
E.ouverts  = 0
E.tpEchecs = 0
E.cibles   = 0
E.ecartees = 0
E.trace    = {}

-- Le decompte des verdicts, par regle. DOIT exister avant le premier appel a
-- estCoffre() : estCoffre y ecrit `R.template`, et un `R` nil leve « attempt to
-- index a nil value ».
--
-- Ce n'est pas une hypothese. C'est exactement ce qui s'est produit : la case
-- etait cochee, la boucle demarrait, chaque tick de son pilote echouait sur ce
-- nil, le pcall appelait arreter(), et la boucle se remettait a zero 20 fois par
-- seconde sans jamais rien dire. La case affichait « desactive »... non :
-- « cherche des coffres », avec 0 ouvert et 0 echec, forever.
E.regles   = { template = 0, marqueSeule = 0, aucune = 0 }
E.gagnes   = 0

local ouverts   = type(E.ouvertsCache) == 'table' and E.ouvertsCache or {}
local sansEffet = type(E.sansEffet)     == 'table' and E.sansEffet     or {}
-- Les coffres qui ont COUTE DES PV. Meme nature que `sansEffet`, meme purge
-- avec la scene, meme usage : on ne les retente pas pendant la scene. Ecarter
-- sur une absence d'information serait faux -- on n'ecarte que sur une preuve.
local dangereux = type(E.dangereux)     == 'table' and E.dangereux     or {}
E.ouvertsCache, E.sansEffet, E.dangereux = ouverts, sansEffet, dangereux

local curTarget = nil
local timers    = {}

-- ------------------------------------------------------------------ outils
local function position()
    local e = pg.me
    if not e then return nil end
    local ok, p = pcall(function() return e:getPosition() end)
    if ok and p then return p end
    return nil
end

local function distance(p, x, y, z)
    local dx, dy, dz = p[1] - x, p[2] - y, p[3] - z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

local function nomDe(en)
    local ok, t = pcall(CTU.getLocalizationText, en.configName)
    return (ok and t and t ~= '') and t or '?'
end

-- ------------------------------------------------------------------ les PV
--
-- Mesure, en jeu, sur `pg.me` :
--
--     curHp = 6    maxHp = 6      les PV sont en COEURS, pas en pourcentage
--     life  = 1
--     lastHurtTime = 101319.471  l INSTANT du dernier coup recu
--
-- Un diff de `curHp` seul ne suffit pas : la REGENERATION fait remonter `curHp`
-- pendant un cycle, et une perte d'un coeur suivie d'une regen passerait
-- inapercue. `lastHurtTime` est un instant, pas un total -- il ne bouge que sur
-- un coup.
--
-- Donc on prend les DEUX, et « l'un OU l'autre » :
--   - `lastHurtTime` couvre le coup suivi d'une regen immediate ;
--   - `curHp` couvre un coup dont l'horodatage n'aurait pas bouge.
-- Aucun des deux n'a de faux positif que l'autre ne couvre.
-- ETAT DE FORME : joueur, ou pet de substitution ?
--
-- `specter.tp.etat()` vient d'init.lua, qui resout l'entite reellement deplacee
-- (mesure : transforme, `pg.me` est une coquille passive et le pet de combat est
-- vise a la place). On ne decide rien ici : on REPART ce que la resolution sait
-- deja, plutot que de refaire une detection qui divergerait.
--
-- Ca ne change pas ce qu'on vise -- un coffre reste un coffre, et le filtre ne
-- depend pas du joueur. Ca change ce que la case DIT. Une boucle qui vise un pet
-- doit le dire, sinon ses echecs de teleportation paraitront etre des
-- difficultes de placement alors que c'est une decision de conception.
local function formeDuJoueur()
    local st = nil
    if type(specter.tp) == 'table' and type(specter.tp.etat) == 'function' then
        pcall(function() st = specter.tp.etat() end)
    end
    return st
end

-- EST-CE QUE LE JOUEUR EST MORT ?
--
-- Mesure, en jeu, la boucle tournant sur un joueur sans vie :
--
--     curHp = 0    maxHp = 6    _topLogoDeadState = true    life = 3
--
-- et la trace qui disait, en meme temps :
--
--     TP ECHEC (lent) id=91350283 d=5.0 meilleur=0.3 unite=vue
--     ...   x5, le meme coffre
--
-- UN MORT NE SE DEPLACE PAS. Le teleport echouait donc legitimement, cinq fois
-- de suite, sur le meme coffre, et la case affichait « cherche des coffres ».
-- Aucun des garde-fous ajoutes ne pouvait le voir : le TP EchOUAIT bien, et
-- l'echec etait correctement compte. Ce qui manquait, c'est la question
-- « pourquoi ca echoue-t-il encore », et la reponse tenant en un mot.
--
-- On ne s'arrete PAS sur une absence d'information : nil = on ne sait pas, la
-- boucle continue. C'est `curHp <= 0` ou le drapeau du jeu qui arretent.
local function estMort()
    local me = pg.me
    if not me then return nil end
    local ok, hp = pcall(function() return me.curHp end)
    if not ok or hp == nil then return nil end
    if me._topLogoDeadState == true then return true end
    return hp <= 0
end

local function lirePv()
    -- Un acces direct qui leve (le champ disparait dans une version du jeu) ne
    -- doit pas casser le script : il doit dire « inconnu ».
    local me = pg.me
    if not me then return nil end
    local ok, hp, mhp, hurt = pcall(function()
        return me.curHp, me.maxHp, me.lastHurtTime
    end)
    if not ok then return nil end
    return { hp = hp, max = mhp, t = hurt }
end

-- Le joueur a-t-il perdu des PV depuis le debut du cycle ? nil = on ne sait pas
-- (champ absent, joueur pas encore la). Et « on ne sait pas » n'est JAMAIS
-- « oui » : on n'ecarte pas un coffre sur une absence d'information -- c'est le
-- meme defaut par defaut qu'on s'est interdit pour le filtre a coffres.
local function aPerduDesPv(t)
    local avant = t and t.pv
    local now = lirePv()
    if not avant or not now then return nil end
    local dh, dt = 0, 0
    if type(avant.hp) == 'number' and type(now.hp) == 'number' then
        dh = avant.hp - now.hp
    end
    if type(avant.t) == 'number' and type(now.t) == 'number' then
        dt = now.t - avant.t
    end
    if dh > 0 or dt > 0.0005 then
        return true, dh, now
    end
    return false, 0, now
end

-- La CLE de cache. `markBindStaticId` est l'identifiant STATIQUE de l'objet : il
-- survit a un rechargement de scene, la ou `ent.id` (le globalId que porte
-- l'unite d'interaction) est recree. On prend le statique quand il existe, et
-- l'autre sinon.
local function identifiant(en)
    if en.markBindStaticId ~= nil then return en.markBindStaticId end
    return en.id
end

local function entiteVivante(marker)
    for _, en in pairs(pg.getEntities() or {}) do
        if en.isChest and (en.id == marker or identifiant(en) == marker) then
            return true
        end
    end
    return false
end

local function nettoyer()
    for i = #timers, 1, -1 do
        if timers[i] then pcall(function() TM.removeTimer(timers[i]) end) end
        timers[i] = nil
    end
end

local function journal(fmt, ...)
    local tr = E.trace
    tr[#tr + 1] = string.format(fmt, ...)
    while #tr > MAX_TRACE do table.remove(tr, 1) end
end

local function ecrirePhase(v)
    E.phase = v
    if type(specter.var.coffres_phase) == 'number' then
        pcall(function() specter.var.coffres_phase = v end)
    end
end

-- ------------------------------------------- REGLE A : la config du jeu
--
-- `Data.chest_data` est la definition du jeu : 373 entrees indexees par id de
-- coffre, chacune avec `markConfigId = 10506`. C'est la seule source qui dit
-- « cet objet est un coffre » sans passer par la position ni par la langue.
--
-- Elle peut ne pas etre chargee au premier passage -- init.lua s'execute AVANT
-- que le joueur soit fully loaded, c'est dit dans son en-tete. On retente donc
-- depuis le pilote, comme ani_ai.lua le fait pour AiConst.
local chestData = nil

local function resoudreChestData()
    if chestData then return chestData end
    local C = package.loaded['Data.chest_data']
    if type(C) ~= 'table' then
        local ok, m = pcall(require, 'Data.chest_data')
        C = ok and m or nil
    end
    -- On exige une table INDEXABLE. Un userdata se comporte comme une table
    -- pour les lectures, et le jeu expose certaines de ses configs ainsi ; si
    -- c'est un userdata, `type` ment et on ne peut pas l'indexer en Lua.
    if type(C) ~= 'table' then return nil end
    chestData = C
    E.chestData = true
    print('[coffres] Data.chest_data resolu -- regle A (template) active')
    return chestData
end

-- Une entite est-elle un coffre PAR SA CONFIG ? true / false / nil (inconnu).
--
-- MESURE, scene 3000, 25 entites `isChest` de la classe ClientChest, apres
-- correction (colonne `chestDat` = le markConfigId de l'entree de
-- Data.chest_data ; « illisible » = l'entree existe mais n'a pas le champ) :
--
--     d(u) tpl      nom          chestDat    marque a <= 3 u
--       3 13020   Coffre        10506       10506 (0.0 u)
--      12 11135   Ramasser      illisible   nil
--      21 13010   Coffre        10506       10506 (0.0 u)
--      36 11042   Ambre lumin   10505       10505 (0.0 u)
--     ...                                (9 coffres, 16 non-coffres)
--     desaccords (verdict COFFRE avec un nom qui n'est pas « Coffre ») : 0
--
-- `Data.chest_data` NE CONTIENT PAS QUE DES COFFRES : les templates 11092 a
-- 11136 y sont aussi, avec `markConfigId` ABSENT de l'entree. Une premiere
-- version faisait `return true` quand le champ etait illisible -- et laissait
-- passer 12 cibles sur 25, dont la moitie des ramassages. C'etait l'ERREUR,
-- recopiee mot pour mot depuis l'ancien filtre : « identite inconnue, on
-- tente ». Il n'y a rien a tenter ; une interaction sur un ramassage, c'est le
-- ramassage.
--
-- DONC : une lecture qui echoue vaut NON. Jamais OUI.
local function parTemplate(en)
    local C = chestData
    if not C then return nil end
    local tpl = en.templateId
    if tpl == nil then return nil end
    local ok, entree = pcall(function() return C[tpl] end)
    if not ok or entree == nil then return false end
    local okc, cfg = pcall(function() return entree.markConfigId end)
    if not okc or cfg == nil then return false end
    return cfg == CFG_COFFRE
end

-- ------------------------------------------------------ grille des marques
--
-- La meme que celle d'autofarm_loop.lua, et pour la meme raison : 2323 marques
-- par scene, et le balayage complet coutait 2323 iterations par entite et par
-- cycle. Cellule de 24 u, on ne regarde que les 27 voisines. Chaque fichier est
-- auto-contenu (pas de require entre nos scripts), donc la grille n'est pas
-- partagee -- c'est 0,7 ms une fois par scene, deux fois plutot qu'une.
local grille      = nil
local grilleScene = nil

local function celler(cx, cy, cz)
    return cx .. ':' .. cy .. ':' .. cz
end

local function indexerMarques()
    local e = pg.me
    if not e then return nil end
    local sid = e.sceneId
    if grille and grilleScene == sid then return grille end

    local ok, pts = pcall(SU.getSceneMarkPointData, sid)
    local g = {}
    if ok and type(pts) == 'table' then
        for _, mp in pairs(pts) do
            -- markPosition est un userdata VECTEUR : markPosition[1..3].
            local P = mp.markPosition
            if P and P[1] then
                local k = celler(math.floor(P[1] / CELL), math.floor(P[2] / CELL),
                                 math.floor(P[3] / CELL))
                local c = g[k]
                if not c then c = {}; g[k] = c end
                c[#c + 1] = { x = P[1], y = P[2], z = P[3], cfg = mp.markConfigId }
            end
        end
    end
    grille, grilleScene = g, sid

    -- Les caches partent AVEC la scene. Sans borne ils accumulent des ids
    -- d'entites d'une zone qu'on quitte, et une zone qui part ne revient pas
    -- avec les memes ids : c'est la seule croissance non bornee du processus,
    -- et elle ne coute rien a supprimer.
    for k in pairs(ouverts) do ouverts[k] = nil end
    for k in pairs(sansEffet) do sansEffet[k] = nil end
    for k in pairs(dangereux) do dangereux[k] = nil end
    print('[coffres] changement de scene ' .. tostring(sid) ..
          ' -- caches purges (ouverts, sansEffet)')

    return g
end

-- REGLE B : markConfigId de la marque la plus proche, si elle est a moins de
-- MARQUE_ASSOC_D. nil = « aucune marque associable », ce qui vaut ECART.
local function parMarque(x, y, z)
    local g = indexerMarques()
    if not g then return nil end
    local cx, cy, cz = math.floor(x / CELL), math.floor(y / CELL), math.floor(z / CELL)
    local bd, bc
    for i = -1, 1 do
        for j = -1, 1 do
            for k = -1, 1 do
                local c = g[celler(cx + i, cy + j, cz + k)]
                if c then
                    for n = 1, #c do
                        local M = c[n]
                        local dx, dy, dz = M.x - x, M.y - y, M.z - z
                        local d = math.sqrt(dx * dx + dy * dy + dz * dz)
                        if not bd or d < bd then bd, bc = d, M.cfg end
                    end
                end
            end
        end
    end
    if bd and bd <= MARQUE_ASSOC_D then return bc end
    return nil
end

-- ------------------------------------------------------- collecte des cibles
--
-- LE VERDICT. UNE SEULE REGLE DECIDE.
--
-- La regle B (marque 10506 a moins de 3 u) est toujours lue et comptee, mais
-- elle n'accepte plus rien.
--
-- Mesure, scene 3000, deux releves :
--
--     regle A (template) : 12 coffres acceptes sur 12, 0 desaccord
--     regle B (marque)   : 0 verdict quand elle est seule, et 1 VERITABLE
--                          faux positif -- un « Ramasser » pose a moins de 3 u
--                          d'une marque 10506, OUVERT par la boucle
--
-- Le raisonnement qui rendait B necessaire : « un vrai coffre peut etre a plus
-- de 3 u de sa marque ». Mais sur 12 coffres reels observes, A les a tous
-- acceptes sans jamais avoir besoin de B. B n'a donc jamais ete necessaire, et
-- elle a deja ouvert un ramassage. Une regle qui n'a jamais rendu service et qui
-- a coute une fois ne reste pas, meme « en secours » : c'est exactement le meme
-- « on tente » qu'on s'etait interdit plus haut dans ce fichier.
local function estCoffre(en, x, y, z)
    local R = E.regles
    -- B est TOUJOURS lue : elle reste un diagnostic gratuit (« la marque la
    -- plus proche dit 10506 et pourtant ce n'est pas un coffre »), et c'est ce
    -- diagnostic qui a designe la regle A comme la seule fiable.
    local b = parMarque(x, y, z)
    local a = parTemplate(en)
    if a then
        R.template = (R.template or 0) + 1
    else
        R.aucune = (R.aucune or 0) + 1
        if b == CFG_COFFRE then R.marqueSeule = (R.marqueSeule or 0) + 1 end
    end
    return a == true   -- LE DEFAUT STRICT, et la seule porte d'entree
end

local function collection()
    local pnow = position()
    if not pnow then return {} end

    local cibles, ecartees = {}, 0
    for _, en in pairs(pg.getEntities() or {}) do
        if en.isChest and en.chestValid then
            local id = identifiant(en)

            if sansEffet[id] or dangereux[id] then
                -- Deja tente sans effet, ou deja ouvert en encaissant :
                -- inutile d'y retourner, et surtout inutile de le re-mesurer.
            else
                local okp, p = pcall(function() return en:getPosition() end)
                if okp and p then
                    if estCoffre(en, p[1], p[2], p[3]) then
                        if not ouverts[id] then
                            cibles[#cibles + 1] = {
                                id = id,
                                -- Le globalId de l'entite, que PORTE l'unite
                                -- d'interaction. On le garde ici pour pouvoir
                                -- interroger le JEU pendant le trajet, sans
                                -- rebalayer pg.getEntities() a chaque tick.
                                entId = en.id,
                                x = p[1], y = p[2], z = p[3],
                                d = distance(pnow, p[1], p[2], p[3]),
                                nom = nomDe(en),
                            }
                        end
                    else
                        -- Tout le reste passe a l'autofarm, qui le Ramassera :
                        -- c'est le complement, pas une perte.
                        ecartees = ecartees + 1
                    end
                end
            end
        end
    end

    table.sort(cibles, function(a, b) return a.d < b.d end)
    E.cibles, E.ecartees = #cibles, ecartees
    return cibles
end

-- ---------------------------------------------------------------- la chaine
local startCycle

local function arreter()
    nettoyer()
    if type(specter.tp) == 'table' and specter.tp.stop then
        pcall(specter.tp.stop)
    end
    curTarget = nil
    E.running = false
    ecrirePhase(0)
end

local function surOuverture()
    -- A LA FIN DU CYCLE : le coffre a ete ouvert, ET on l'a paye ?
    --
    -- On verifie AVANT de compter l'ouverture, et le coffre est marque
    -- « dangereux » meme si l'ouverture compte. Ce n'est pas contradictoire :
    -- le coffre EST ouvert, et il nous a coute des PV. Les deux faits sont
    -- vrais, et on veut savoir le deuxieme.
    --
    -- On ecarte pour la SCENE, comme `sansEffet`. Un coffre qui fait mal ne
    -- devient pas bon au bout de dix minutes.
    local touche, dh, now = aPerduDesPv(curTarget)
    if touche then
        E.gagnes = (E.gagnes or 0) + 1
        dangereux[curTarget.id] = true
        if type(specter.var.coffres_gagnes) == 'number' then
            pcall(function() specter.var.coffres_gagnes = E.gagnes end)
        end
        journal('DEGATS sur %s (id=%s) : %d coeur(s), reste %s/%s -- coffre ecarte',
                tostring(curTarget.nom), tostring(curTarget.id), dh,
                tostring(now and now.hp), tostring(now and now.max))
        -- MORT n'est pas « des degats », c'est la fin du cycle : on ne reprend
        -- pas la boucle. Un coffre qui tue est ecarte comme les autres, mais
        -- surtout on cesse de TP un corpse, qui ne peut aboutir a rien.
        if estMort() then
            journal('JOUEUR MORT pendant le cycle -- boucle arretee')
            ecrirePhase(PHASE_MORT)
            E.cancel = true
            arreter()
            ecrirePhase(PHASE_MORT)   -- arreter() remet a 0 : on reecrit apres
            return
        end
    end

    -- ARRETER LE POLL, ICI, AVANT DE COMPTER.
    --
    -- Sans ce nettoyer(), le timer de poll survit a l'ouverture : `interagi`
    -- reste vrai, l'entite a disparu, et surOuverture() est rappelee a CHAQUE
    -- tick jusqu'a ce que la respiration se declenche. Mesure sur l'autofarm :
    -- 225 « ouvertures » affichees la ou il y en avait 75, et autant de timers
    -- de respiration empiles. Un truc qui survit a ce qu'il a fini de faire, il
    -- le repete.
    nettoyer()

    ouverts[curTarget.id] = true
    E.ouverts = (E.ouverts or 0) + 1
    if type(specter.var.coffres_ouverts) == 'number' then
        pcall(function() specter.var.coffres_ouverts = E.ouverts end)
    end
    journal('ouvert %s (id=%s)', tostring(curTarget.nom), tostring(curTarget.id))

    -- Pause, puis on recommence. Pas de limite : c'est une boucle, pas un
    -- script. Le cooldown evite de marteler le meme spot.
    E.breath = TM.addRepeatTimer(BREATH, function()
        nettoyer()
        if not E.cancel then startCycle() end
    end)
    timers[#timers + 1] = E.breath
end

local function startPoll()
    nettoyer()
    local tries, sansUnite, verifie = 0, 0, 0
    local interagi = false
    local t = curTarget
    local marker, mx, my, mz = t.id, t.x, t.y, t.z

    -- Le plus petit ecart vu pendant le trajet, et l'a-t-on VUE l'unite.
    --
    -- `distance()` se contente de lire la position du joueur, et cette position
    -- peut etre celle que NOUS venons d'ecrire : le lerp de `specter.tp.here`
    -- ecrit, et le tick suivant relit. Un `d` petit prouve alors seulement
    -- qu'on sait ecrire, pas qu'on est arrive. C'est exactement le piege qui a
    -- fait croire a un TP casse pendant des heures.
    --
    -- Deux contre-mesures :
    --   - le plus petit ecart est MEMORISE, pour distinguer « on a frôle la
    --     cible » de « on n'a jamais bougé » ;
    --   - et surtout l'UNITE D'INTERACTION, qui est un signal du JEU : elle
    --     n'existe que si le jeu estime le joueur a portee. On ne peut pas la
    --     fabriquer en ecrivant une position, donc c'est le seul temoin fiable.
    local meilleurD = 1e9
    local uniteVue = false

    -- Publier le compteur d'erreurs du pilote. Appele a chaque tick du pilote,
-- donc une erreur qui se repete ne reste pas invisible.
    local function publierErreurs()
        if type(specter.var.coffres_erreurs) == 'number' then
            pcall(function()
                specter.var.coffres_erreurs = E.erreursPilote or 0
            end)
        end
    end
    E.publierErreurs = publierErreurs

    local function noteEchec(raison, d)
        E.tpEchecs = (E.tpEchecs or 0) + 1
        E.dernierEchec = {
            id = marker, nom = t.nom,
            d = d or -1, meilleur = meilleurD, raison = raison,
        }
        if type(specter.var.coffres_tp_echecs) == 'number' then
            pcall(function() specter.var.coffres_tp_echecs = E.tpEchecs end)
        end
        journal('TP ECHEC (%s) id=%s d=%.1f meilleur=%.1f unite=%s',
                raison, tostring(marker), d or -1, meilleurD,
                uniteVue and 'vue' or 'jamais')
    end

    timers[#timers + 1] = TM.addRepeatTimer(0.15, function()
        local ok, err = pcall(function()
            if E.cancel then arreter() return end

            local pnow = position()
            if not pnow then
                tries = tries + 1
                if tries * 0.15 > TRY_SECONDS then arreter() end
                return
            end
            local d = distance(pnow, mx, my, mz)
            if d < meilleurD then meilleurD = d end

            -- L'unite est notee AVANT le test d'arrivee : c'est elle le temoin,
            -- et elle doit pouvoir etre vue meme quand la distance ment.
            local it0 = pg.game and pg.game.interaction
            if it0 and it0.unitMap then
                local byType = it0.unitMap[INTERACT_TYPE]
                if type(byType) == 'table' then
                    for _, u in pairs(byType) do
                        if type(u) == 'table' and u.globalId == t.entId then
                            uniteVue = true
                            break
                        end
                    end
                end
            end

            -- L'ARRIVEE, C'EST LE JEU QUI LA DECIDE.
            --
            -- Mesure, en jeu : `unite=vue` sur un joueur a 5,0 u du coffre
            -- vise. Le jeu le declare a portee -- son unite d'interaction est
            -- la, c'est sa propre regle -- et notre lecture de distance dit
            -- 5 u. Les deux ne peuvent pas avoir raison : notre position est
            -- celle que le lerp vient d'ecrire, pas ou le joueur est.
            --
            -- Alors l'arrivee c'est `uniteVue`, et la distance ne sert plus qu'a
            -- DIAGNOSTIQUER : a savoir jusqu'ou on est alle reellement. C'est
            -- le contre-weigh de garde-fou qu'on s'etait donne, et il vient de
            -- montrer que c'etait lui qui avait raison -- sans lui, cette boucle
            -- n'aurait jamais rien ouvert, et elle aurait eu l'air de chercher.
            if d > ARRIVED_D and not uniteVue then
                tries = tries + 1
                -- UN TP QUI N'ARRIVE PAS SAUTE UNE CIBLE, IL N'ARRETE PAS LA
                -- BOUCLE. Mais il COMPTE : sinon une boucle incapable de se
                -- deplacer tourne en silence, et la case affiche « cherche des
                -- coffres » sans jamais rien ouvrir.
                if tries * 0.15 > TRY_SECONDS then
                    -- « bloque » = on n'a meme pas commence a approcher.
                    -- C'est le symptome d'un joueur ancre par le jeu.
                    noteEchec(meilleurD > ARRIVED_D * 4 and 'bloque' or 'lent', d)
                    startCycle()
                end
                return
            end
            tries = 0

            -- VERIFICATION : l'entite a-t-elle REELLEMENT disparu ?
            if interagi then
                if not entiteVivante(marker) then
                    surOuverture()
                else
                    verifie = verifie + 1
                    if verifie * 0.15 > CONFIRM_TICKS then
                        E.sansEffetTotal = (E.sansEffetTotal or 0) + 1
                        sansEffet[marker] = true
                        journal('sans effet id=%s (tjrs vivant)', tostring(marker))
                        startCycle()
                    end
                end
                return
            end

            local ent
            for _, en in pairs(pg.getEntities() or {}) do
                if en.isChest and (identifiant(en) == marker or en.id == marker) then
                    ent = en
                    break
                end
            end

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
                -- Pas d'unite = rien ouvert. On note « inerte », qui est un AUTRE
                -- fait : `ouverts` n'est pas touche.
                sansUnite = sansUnite + 1
                if sansUnite * 0.15 > GRACE_UNITE then
                    journal('pas d unite id=%s', tostring(marker))
                    startCycle()
                end
                return
            end

            -- DERNIERE VERIFICATION, ET CELLE QUI COMPTE LE PLUS.
            --
            -- La cible a ete classee a distance, avec la regle du template OU
            -- celle de la marque. On repose la question AU MOMENT D'INTERAGIR,
            -- en direct, sur l'entite qu'on va toucher. C'est une grille de 27
            -- cellules, ca ne coute rien, et ca ferme le seul scenario qui
            -- ferait du mal : une cible classee avant un changement de scene,
            -- ou un deplacement de 3 u entre la classification et l'appel.
            --
            -- Si la reponse change, on ne touche a rien et on passe a la
            -- suivante. Ne pas ouvir vaut mieux qu'ouvrir la mauvaise chose.
            if not estCoffre(ent, mx, my, mz) then
                journal('classee coffre, refusee a l arrivee id=%s', tostring(marker))
                E.refus = (E.refus or 0) + 1
                startCycle()
                return
            end

            -- PAS de nettoyer() ici : ce timer EST la verification.
            local okr = pcall(function() return it:doUnitInteractive(unit) end)
            if okr then
                interagi = true
                verifie = 0
                ecrirePhase(2)
            else
                sansEffet[marker] = true
                journal('echec interaction id=%s', tostring(marker))
                startCycle()
            end
        end)

        if not ok then
            E.erreurs = (E.erreurs or 0) + 1
            journal('ERREUR ' .. tostring(err))
            arreter()
        end
    end)
end

startCycle = function()
    if E.cancel then arreter() return end

    local cibles = collection()
    if #cibles == 0 then
        -- Plus rien a faire : on attend, on ne meurt pas. Une chaine finie sur
        -- « NP » en laissant le verrou actif est une chaine morte qui se dit
        -- vivante, et que rien ne peut relancer.
        E.enAttente = true
        ecrirePhase(3)
        nettoyer()
        timers[#timers + 1] = TM.addRepeatTimer(RETRY_S, function()
            nettoyer()
            if not E.cancel then startCycle() end
        end)
        return
    end

    E.enAttente = false
    ecrirePhase(1)

    local t = cibles[1]
    curTarget = t
    E.lastId = t.id
    -- Les PV AVANT le TP. C'est la reference du cycle : sans elle, on ne pourrait
    -- comparer qu'a un instant anterieur inconnu, et « a perdu des PV » ne
    -- signifierait rien. Prise ICI, parce que c'est le dernier moment ou l'on
    -- n'a pas encore commute la position -- et qu'une chute en chemin (le TP
    -- traverse des falaises, c'est mesure) compterait alors pour le coffre.
    t.pv = lirePv()
    -- La forme, relevee A CHAQUE cycle et pas une fois au demarrage : le joueur
    -- peut se transformer ou se de-transformer en cours de session, et une
    -- valeur figee au bootstrap serait fausse au bout de dix minutes.
    --
    -- Elle ne change rien au ciblage -- on vise toujours un coffre. Elle explique
    -- les echecs de teleportation : viser un pet de substitution est un CHOIX,
    -- pas une difficulte, et le dire evite de chercher pourquoi.
    local forme = formeDuJoueur()
    E.forme = forme and (forme.transforme and 'pet' or 'joueur') or '?'
    E.formeClasse = forme and tostring(forme.classe) or '?'

    local pnow = position()
    local d = pnow and distance(pnow, t.x, t.y, t.z) or 999
    if d >= ARRIVED_D and type(specter.tp) == 'table' and specter.tp.here then
        pcall(function() specter.tp.here(t.x, t.y, t.z) end)
    end

    startPoll()
end

-- ----------------------------------------------------------------- pilote
--
-- UN SEUL timer, lu toute la vie. Il lit le booleen C++ et demarre ou arrete.
-- Il n'a pas de booleen propre : il ne peut donc pas se desynchroniser de la
-- case a cocher.
E.pilote = TM.addRepeatTimer(PILOTE_S, function()
    local ok, err = pcall(function()
        -- La regle A a besoin de sa table de config. On la reprend tant qu'elle
        -- n'est pas la : gratuit, et la boucle tourne de toute facon.
        if not chestData then resoudreChestData() end

        local voulue = (specter.var.coffres == true)

        -- UN MORT N'ARRIVE PAS. On coupe, et on le dit -- sinon la case affiche
        -- « cherche des coffres » et compte des TP ratés pendant que le
        -- personnage est au sol, ce qui est exactement ce qui s'est produit.
        if estMort() then
            if E.running then
                E.cancel = true
                arreter()
            end
            ecrirePhase(PHASE_MORT)
            return
        end

        if not voulue then
            if E.running then
                E.cancel = true
                arreter()
            end
            return
        end

        -- UN SEUL DEPLACEMENT A LA FOIS. `specter.tp.here` annule le
        -- deplacement precedent : si les deux boucles se teleportaient en meme
        -- temps, chacune annulerait celle de l'autre et aucune n'arriverait.
        -- L'auto-farm garde la main tant que sa case est cochee ; celle-ci
        -- reprend la main des qu'on la decoche.
        if specter.var.autofarm == true then
            if E.running then
                E.cancel = true
                arreter()
            end
            ecrirePhase(4)
            return
        end

        if not E.running then
            E.running = true
            E.cancel = false
            startCycle()
        end
    end)
    -- UN pcall QUI AVALE N'EST PAS UNE PROTECTION : c'est une panne muette.
    --
    -- La premiere version faisait `if not ok then pcall(arreter) end` et rien
    -- d'autre. Une erreur dans le pilote etait donc invisible : la boucle se
    -- remettait a zero, le pilote recommençait, et rien ne le disait. C'est
    -- exactement ce qui est arrive avec le `E.regles` nil -- la case etait
    -- cochee, rien ne s'ouvrait, et le menu disait « cherche des coffres ».
    --
    -- Alors on garde l'erreur. Un compteur d'erreurs, et la derniere ecrite
    -- dans le store : la case peut les lire, et `tools/lua.sh` aussi.
    if not ok then
        E.erreursPilote = (E.erreursPilote or 0) + 1
        E.derniereErreurPilote = tostring(err)
        journal('PILOTE ERREUR : %s', tostring(err))
        pcall(arreter)
    end
    if E.publierErreurs then E.publierErreurs() end
end)

resoudreChestData()

print('[coffres] boucle en place -- case a cocher dans le menu pour l activer')