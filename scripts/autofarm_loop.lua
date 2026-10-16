-- autofarm_loop.lua — la boucle d'auto-farm, TOURNANT EN PERMANENCE.
--
-- EMBARQUE dans la DLL, execute une fois par nouveau lua_State juste apres
-- scripts/init.lua. Il ne fait rien tant que `specter.var.autofarm` est faux :
-- la case a cocher du menu est la seule chose qui decide.
--
-- CE QUE LA MESURE A IMPOSE
--
-- 1. UNE CIBLE SANS UNITE NE S'OUVRE PAS, ET IL NE FAUT PAS LE PRETENDRE.
--    Un Ambre lumin a une unite qui vit ~0.3 s, puis le contact le consomme.
--    On ne note "ouvert" QUE si l'entite a DISPARU apres l'appel. Un cache
--    qui pretend avoir ouvert ce qu'il n'a pas ouvert est PIRE que pas de
--    cache : il donne raison au script alors qu'il n'a rien fait.
--
-- 2. LA BOUCLE NE S'ARRETE JAMAIS. Une version finissait sur `NP` quand il ne
--    restait rien, ce qui laissait running = true sans aucun timer : une chaine
--    morte qui se dit vivante, et que rien ne peut relancer. Ici, "plus rien a
--    faire" veut dire "attendre et reessayer".
--
-- 3. LE COUT PAR CYCLE, ET SA CORRECTION.
--    cfgDeLEtat() parcourait les 2323 marques pour CHAQUE entite, et
--    collection() reclasse tout a chaque cycle -- dix fois par seconde avec
--    BREATH = 0.1. Deux corrections :
--      - GRILLE SPATIALE sur les marques, cellule de 24 u : on ne regarde que
--        les 27 cellules voisines, quelques marques au lieu de 2323 ;
--      - CACHE DE CLASSIFICATION par id d'entite, invalide au changement de
--        scene. La nature d'une entite ne change pas.
--    Ce qui n'a PAS ete optimise : la recherche de l'entite et la verification
--    de vie, qui balayent pg.getEntities(). Mesure : 116 entites, 20 balayages
--    = 0 ms. Optimiser ca serait du bruit.
--
-- 4. LES POTS NE SONT PAS ICI. `isChest` n'est pose que par ClientChest et
--    ClientArkChest ; ClientBreakableEntity ne l'a pas et renvoie nil de
--    getInteractionListData(). On ne se teleporte donc jamais sur un pot.

local SU  = require('Common.Utils.SceneUtils')
local CTU = require('Utils.ClientTextUtils')
local TM  = require('Core.Timer.TimerManager')

-- ------------------------------------------------------------------ reglages
local BREATH         = 0.5   -- s, pause apres une ouverture confirmee
local TRY_SECONDS    = 3     -- s, pour que le TP arrive
local GRACE_UNITE    = 1.2   -- s, a l'arrivee, pour que l'unite apparaisse
local CONFIRM_TICKS  = 1.5   -- s, pour voir DISPARAITRE la cible
local INTERACT_TYPE  = 1     -- ENT_FUNC
local ARRIVED_D      = 2.5   -- u : arrive en dessous
local MARQUE_ASSOC_D = 3     -- u : en dessous, c'est SA marque
local CFG_COFFRE     = 10506 -- markConfigId du vrai coffre
local CELL           = 24    -- u, cellule de la grille des marques
local RETRY_S        = 2     -- s, quand il n'y a plus rien a faire
local MAX_TRACE      = 40

-- Nom localise ET template : le template survit au changement de langue, le nom
-- non. Les deux, parce que le filtre doit rester lisible.
local EXCLURE_NOMS      = { 'Ambre lumin' }
local EXCLURE_TEMPLATES = { 11042 }

-- ------------------------------------------------------------------- etat
local E = specter.store.autofarm
if type(E) ~= 'table' then
    E = {}
    specter.store.autofarm = E
end
E.running = false
E.cancel  = false
E.cibles  = 0
E.ecartees = 0
E.trace   = {}

local opened    = type(E.opened)    == 'table' and E.opened    or {}
local inertes   = type(E.inertes)   == 'table' and E.inertes   or {}
local sansEffet = type(E.sansEffet) == 'table' and E.sansEffet or {}
E.opened, E.inertes, E.sansEffet = opened, inertes, sansEffet

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
    return (ok and t) or '?'
end

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

-- ------------------------------------------------- grille des marques (le gros)
local grille = nil
local grilleScene = nil
local cfgCache = {}

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
            -- SceneUtils.lua:340 fait Vector3.Clone(point.markPosition).
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

    -- Les caches sont purges AVEC LA SCENE.
    --
    -- Ils ne poussaient jamais : sans borne, ils accumulent des ids d'entites
    -- qui ne reviendront pas -- une entite d'une zone qu'on quitte ne revient
    -- pas avec le meme id. La scene qui part, ses ids partent avec.
    --
    -- Mesure avant correction, sur une session courte : ouverts=0, inertes=46,
    -- sansEffet=80. Sur plusieurs heures c'est la seule croissance non bornee du
    -- processus, et elle ne coute rien a supprimer.
    --
    -- Pas de purge sur minuterie : une scene qui ne change pas est un etat
    -- stable, et purger dessus ne ferait que refaire le meme travail.
    for k in pairs(cfgCache) do cfgCache[k] = nil end
    for k in pairs(opened) do opened[k] = nil end
    for k in pairs(inertes) do inertes[k] = nil end
    for k in pairs(sansEffet) do sansEffet[k] = nil end
    print('[autofarm] changement de scene ' .. tostring(sid) ..
          ' -- caches purges (marques, ouverts, inertes, sansEffet)')

    return g
end

-- markConfigId de l'entite, ou nil si on n'a pas etabli que la marque la plus
-- proche est la sienne. `false` dans cfgCache = "on a cherche, on ne sait pas".
local function cfgDeLEtat(x, y, z)
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
local function collection()
    local pnow = position()
    if not pnow then return {} end

    local cibles, ecartees = {}, 0
    for _, en in pairs(pg.getEntities() or {}) do
        if en.isChest and en.chestValid then
            local id = identifiant(en)
            local tpl = en.templateId
            local nom = nomDe(en)

            local exclu = false
            for _, n in ipairs(EXCLURE_NOMS) do
                if nom == n then exclu = true end
            end
            for _, t in ipairs(EXCLURE_TEMPLATES) do
                if tpl == t then exclu = true end
            end

            if exclu then
                inertes[id] = true
            elseif inertes[id] or sansEffet[id] then
                -- Deja vue sans unite, ou appel sans effet : inutile d'y
                -- retourner, et surtout inutile de le re-mesurer.
            else
                local okp, p = pcall(function() return en:getPosition() end)
                if okp and p then
                    local cfg = cfgCache[id]
                    if cfg == nil then
                        cfg = cfgDeLEtat(p[1], p[2], p[3]) or false
                        cfgCache[id] = cfg
                    end
                    if cfg == CFG_COFFRE then
                        ecartees = ecartees + 1
                    elseif not opened[id] then
                        cibles[#cibles + 1] = {
                            id = id, x = p[1], y = p[2], z = p[3],
                            d = distance(pnow, p[1], p[2], p[3]), nom = nom,
                        }
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
    curTarget = nil
    E.running = false
end

local function surOuverture()
    -- ARRETER LE POLL, ICI, AVANT DE COMPTER.
    --
    -- Sans ce nettoyer(), le timer de poll survit a l'ouverture. `interagi`
    -- reste vrai, l'entite a disparu, donc surOuverture() est rappelee a CHAQUE
    -- tick -- 0.15 s plus tard -- jusqu'a ce que la respiration se déclenche. Mesure
    -- : 225 "ouvertures" affichees la ou il y en avait 75. Trois fois trop, et
    -- autant de timers de respiration empiles.
    --
    -- Le meme piege que pour le TMP lent : un truc qui survit a ce qu'il a
    -- fini de faire, il le repete.
    nettoyer()

    -- Le cache des ouverts. Sans cette ligne, la seule protection contre une
    -- cible qui traine apres avoir ete consommee disparait -- et le despawn du
    -- jeu est lent. C'est aussi ce qui permet de ne pas recounts une entite
    -- encore chargee mais deja vide.
    opened[curTarget.id] = true

    E.ouverts = (E.ouverts or 0) + 1
    if type(specter.var.autofarm_ouverts) == 'number' then
        pcall(function() specter.var.autofarm_ouverts = E.ouverts end)
    end
    -- Trace bornee : elle sert a dire QUOI on ouvre, pas a tout garder. 40
    -- entrees suffisent, et ca borne la memoire sur une session de plusieurs
    -- heures -- une boucle sans fin ne doit pas grossir sans arret.
    local tr = E.trace
    tr[#tr + 1] = string.format('ouvert %s', tostring(curTarget and curTarget.nom))
    while #tr > MAX_TRACE do table.remove(tr, 1) end
    E.lastId = curTarget and curTarget.id
    -- Pause, puis on recommence. PAS de limite d'ouverture : c'est une boucle,
    -- pas un script. Le cooldown evite de marteler le meme spot.
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
            if d > ARRIVED_D then
                tries = tries + 1
                -- UN TP LENT SAUTE UNE CIBLE, IL N'ARRETE PAS LA BOUCLE.
                if tries * 0.15 > TRY_SECONDS then startCycle() end
                return
            end
            tries = 0

            -- VERIFICATION : l'entite a-t-elle REELLEMENT disparu ? Rendre sans
            -- erreur n'est pas avoir consomme : 3 cibles sur 50 etaient toujours
            -- la une minute apres un doUnitInteractive "reussi".
            if interagi then
                if not entiteVivante(marker) then
                    surOuverture()
                else
                    verifie = verifie + 1
                    if verifie * 0.15 > CONFIRM_TICKS then
                        E.sansEffetTotal = (E.sansEffetTotal or 0) + 1
                        sansEffet[marker] = true
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
                -- Pas d'unite = rien ouvert. On note "inerte", qui est un AUTRE
                -- fait, et `opened` n'est pas touche.
                sansUnite = sansUnite + 1
                if sansUnite * 0.15 > GRACE_UNITE then
                    inertes[marker] = true
                    startCycle()
                end
                return
            end

            -- PAS de nettoyerTimers() ici : ce timer EST la verification.
            local okr = pcall(function() return it:doUnitInteractive(unit) end)
            if okr then
                interagi = true
                verifie = 0
            else
                sansEffet[marker] = true
                startCycle()
            end
        end)

        if not ok then
            E.erreurs = (E.erreurs or 0) + 1
            arreter()
        end
    end)
end

startCycle = function()
    if E.cancel then arreter() return end

    local cibles = collection()
    if #cibles == 0 then
        -- Plus rien a faire : on attend, on ne meurt pas. C'est la difference
        -- avec la version qui finissait sur NP en laissant le verrou actif.
        E.enAttente = true
        nettoyer()
        timers[#timers + 1] = TM.addRepeatTimer(RETRY_S, function()
            nettoyer()
            if not E.cancel then startCycle() end
        end)
        return
    end

    E.enAttente = false
    local t = cibles[1]
    curTarget = t
    E.lastId = t.id

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
-- Il ne fait rien d'autre, et il ne peut pas se desynchroniser de la case a
-- cocher : il n'a pas de booleen propre.
E.pilote = TM.addRepeatTimer(0.5, function()
    local ok = pcall(function()
        local voulue = (specter.var.autofarm == true)
        if voulue and not E.running then
            E.running = true
            E.cancel = false
            startCycle()
        elseif (not voulue) and E.running then
            E.cancel = true
            arreter()
        end
    end)
    if not ok then
        pcall(arreter)
    end
end)

print('[autofarm] boucle en place -- case a cocher dans le menu pour l activer')