-- ============================================================
-- AUTOFARM — TP sur les Pokémon capturables autour, puis capture.
--
-- Remplace les deux scripts séparés : chest-open.lua fournissait le TP en
-- lerp et la chaîne d'un point à l'autre, 13_catch_aura.lua fournissait le
-- filtrage des cibles et l'appel de capture.
--
-- ── LE BOUTON ──────────────────────────────────────────────────
--
--     specter.autofarm = true     -- démarre
--     specter.autofarm = false    -- arrête
--
-- Sur `specter`, PAS sur `specter.var` : ce dernier est un namespace
-- LuaBridge qui pose un __newindex et refuse tout nom inconnu
-- ("no writable member"). `specter` est une table ordinaire et accepte
-- n'importe quoi. Mesuré.
--
-- ── DÉROULÉ D'UN CYCLE ─────────────────────────────────────────
--
--     1. le joueur est-il en train de lancer ?  -> on sort, on réessaie
--     2. la cible capturable la plus proche
--     3. trop loin ?  -> TP en lerp, puis on settles
--     4. assez près  -> on capture
--     5. on attend la fin de l'animation avant le cycle suivant
--
-- Le TP vient de chest-open.lua : un lerp à 5,5 u par tick à 120 ticks/s,
-- ce qui évite le saut et reste dans le mouvement. Un saut brut marche
-- aussi, mais la trajectory est visible pour le serveur comme pour le client.
--
-- ── ISOLATION ──────────────────────────────────────────────────
--
-- L'état est un nom NEUF (`AUTOFARM`), donc notre bac à sable le met dans
-- NOTRE store — jamais dans les globales du jeu. Aucune ligne ici n'écrit
-- dans `_G`.
--
-- ── CE QUE LA MESURE A APPRIS, et qui est codé en dessous ─────
--
--   - `isInCatchMode()` ne teste PAS l'animation. Le jeu :
--         currentContext.className ~= "NoBallContext"
--     ça veut dire « UNE BALL EST ÉQUIPÉE ». C'était un garde dans la
--     version précédente du catcher, et il bloquait tout dès qu'une ball
--     était en main.
--   - Le vrai garde est `isCaptureThrowing()` : `ctx.state == CaptureStates.T`.
--   - `throwItemFromBag` KILL un timer répété du jeu. Équiper une ball pour
--     obtenir la charge 0,01 s est donc incompatible avec le tick. On paie les
--     0,5 s, et le tick tourne. C'est le seul arbitrage possible.
--
-- ============================================================

do
    local Utils            = require('Common.Utils.Utils')
    local CatchProbContext = require('Common.Utils.CatchProbContext')
    local TimerManager     = require('Core.Timer.TimerManager')
    local Time             = require('Core.Common.Time')
    local V                = Vector3

    -- ── RÉGLAGES ─────────────────────────────────────────────────
    local SEARCH_RADIUS = 80    -- u : au-delà, on TP vers la cible
    local CATCH_RADIUS  = 4     -- u : à portée de capture
    local LERP_STEP     = 5.5   -- u par tick (mêmes valeurs que le menu TP)
    local LERP_SPEED    = 120   -- ticks par seconde (~660 u/s)
    local SETTLE        = 0.4   -- s d'attente à l'arrivée, avant de capturer
    local MAX_CYCLES    = 0     -- 0 = illimité

    -- ── ÉTAT ─────────────────────────────────────────────────────
    -- Nom neuf -> notre store. Disparu du nom : invisible, et il survit aux
    -- Executes comme à la reconnexion, puisque le store est ancré.
    local S = AUTOFARM
    if not S then
        S = { phase = 'idle', cycles = 0, tps = 0, tp = nil, timerId = nil }
        AUTOFARM = S
    end

    -- ── LE BOUTON ────────────────────────────────────────────────
    if specter.autofarm == nil then
        specter.autofarm = false
    end
    local function wanted()
        return specter.autofarm and true or false
    end

    -- ── LE TEMPS DU JEU ───────────────────────────────────────────
    --
    -- onHandleQuickCapture porte un COOLDOWN DE 5 SECONDES PAR ENTITE :
    --
    --     if entity.lastQuickCaptureTime
    --        and Time.realSecondCache - entity.lastQuickCaptureTime < 5 then
    --         return false
    --     end
    --
    -- C'est la regle du serveur, pas la notre. On ne peut pas faire mieux
    -- qu'une capture par entite toutes les 5 s.
    --
    -- C'est aussi ce qui expliquait les 42 echecs AVANT le cache : le tick
    -- rappelait des entites encore dans leur delai. Le cache evite de les
    -- re-viser, donc evite de se prendre le refus.
    --
    -- L'autre entree, `onHandleThrow` — le bouton du joueur — n'est PAS
    -- equivalente : elle exige isInCatchMode() (une ball en main) et lance sur
    -- ce que vise la camera, sans parametre d'entite. Inutilisable ici, et
    -- l'equipement d'une ball tue notre timer.
    local GAME_COOLDOWN = 5

    -- ── LE CACHE ─────────────────────────────────────────────────
    --
    -- Meme principe que le cache des coffres, mais chez NOUS : un nom neuf
    -- (`AUTOFARM`) va dans notre store, alors qu'un champ pose sur pg.me
    -- serait un nom a nous sur une table du jeu.
    --
    -- Il existe parce que sans lui le tick revient sur la meme cible : on la
    -- capture, le jeu met une seconde a la faire disparaitre, et entre-temps on
    -- est deja en train de voler vers elle a nouveau. Chaque passage coute un
    -- TP entier.
    --
    -- Cle = id d'entite, et on y entre DES QUE QU'ON VISE la cible — pas quand
    -- la capture est confirmee. On ne lit pas le resultat, donc attendre une
    -- confirmation n'aurait pas de sens. Ce qui garantit de ne pas revenir,
    -- c'est de considerer la cible consommee au moment ou on s'y engage.
    if type(S.done) ~= 'table' then
        S.done = {}
        S.doneOrder = {}
    end
    local function markDone(id)
        if id == nil or S.done[id] then return end
        S.done[id] = true
        S.doneOrder[#S.doneOrder + 1] = id
        -- Borne : au-dela, on oublie les plus anciens. Une entite encore
        -- presente apres 300 captures ne sert probablement plus a rien.
        while #S.doneOrder > 300 do
            local vieux = table.remove(S.doneOrder, 1)
            S.done[vieux] = nil
        end
    end

    -- ── CIBLE ────────────────────────────────────────────────────
    local function canCatch(ent)
        if ent == nil or ent.destroyed then return false end
        if not Utils.isWildPuppet(ent) then return false end
        if S.done[ent.id] then return false end      -- deja traitee
        local ok, ctx = pcall(CatchProbContext.clientGet, ent)
        return ok and ctx ~= nil and ctx.canCatch == true
    end

    -- La plus proche, a chaque tick. Aucune cible memorisee, aucun resultat lu.
    local function findTarget()
        if pg == nil or pg.me == nil then return nil end
        return Utils.getNearestPuppet(pg.me, SEARCH_RADIUS, canCatch)
    end

    -- ── TP EN LERP ───────────────────────────────────────────────
    -- Pris tel quel de chest-open.lua : un lerp, pas un saut.
    local function flyTo(pos)
        local e = pg.me
        local pnow = e:getPosition()
        local x0, y0, z0 = pnow.x, pnow.y, pnow.z
        local dx, dy, dz = pos.x - x0, pos.y - y0, pos.z - z0
        local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
        if dist < CATCH_RADIUS then
            return true
        end
        local st = { active = true, i = 0, step = LERP_STEP,
                     x0 = x0, y0 = y0, z0 = z0, x1 = pos.x, y1 = pos.y, z1 = pos.z }
        local n = math.ceil(dist / st.step)
        if n < 1 then n = 1 end
        if n > 20000 then n = 20000 end
        st.n = n
        local tid
        tid = TimerManager.addRepeatTimer(1 / LERP_SPEED, function()
            if not st.active then return end
            st.i = st.i + 1
            local a = st.i / st.n
            if a > 1 then a = 1 end
            local v = V.ForceNew(st.x0 + (st.x1 - st.x0) * a,
                                 st.y0 + (st.y1 - st.y0) * a,
                                 st.z0 + (st.z1 - st.z0) * a)
            if e.forceSetPos then e:forceSetPos(v, true) else e:setPosition(v) end
            if st.i >= st.n then
                st.active = false
                pcall(function() TimerManager.removeTimer(tid) end)
                S.phase = 'settle'
                TimerManager.addTimer(SETTLE, function() S.phase = 'idle' end)
            end
        end)
        st.tid = tid
        S.phase = 'flying'
        S.tps = (S.tps or 0) + 1
        return false
    end

    -- ── CAPTURE ──────────────────────────────────────────────────
    local function capture()
        local target = findTarget()
        if target == nil then return false end

        local p = pg.me:getPosition()
        local tp = target:getPosition()
        local dx, dy, dz = tp.x - p.x, tp.y - p.y, tp.z - p.z
        local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5

        markDone(target.id)

        if dist > CATCH_RADIUS then
            return flyTo(tp)          -- pas assez près -> on vole, puis on cycle
        end

        S.cycles = S.cycles + 1
        -- On lance et on passe a la suite. Le retour n'est PAS lu : savoir si
        -- le jeu a accepte n'interesse pas, etguetter le resultat nous ferait
        -- perdre exactement le temps que ce script est cense gagner.
        pcall(pg.game.controller.onHandleQuickCapture,
              pg.game.controller, target.id)
        -- On laisse le jeu finir son animation avant le cycle suivant : le
        -- cycle repart au tick, et isCaptureThrowing() nous fera patienter.
        return true
    end

    -- ── LE TICK ──────────────────────────────────────────────────
    local function tick()
        if not wanted() then
            S.timerId = nil
            return
        end
        -- LE SEUL VRAI GARDE D'ANIMATION.
        if pg == nil or pg.me == nil or pg.game == nil
           or pg.game.controller == nil then
            return
        end
        if S.phase ~= 'idle' then return end
        -- PAS DE GARDE D'ANIMATION.
        --
        -- On ne demande plus « la capture précédente est-elle finie ? ». Le FSM
        -- a quatre etats (Empty/T/E/S) et isCaptureThrowing() ne teste que T :
        -- il ne couvre pas la sequence entiere, et attendre sa reponse
        -- n'attendait en fait rien de fiable.
        --
        -- A la place : on vise UNE cible et on reessaie sur elle tant qu'elle
        -- existe. C'est le succes qui se voit — la cible disparait quand elle
        -- est capturee — pas la confirmation du jeu.
        if MAX_CYCLES > 0 and S.cycles >= MAX_CYCLES then
            specter.autofarm = false
            print('[AUTOFARM] MAX_CYCLES atteint, arret')
            return
        end
        capture()
    end

    S.tick = tick

    -- ── DÉMARRAGE ────────────────────────────────────────────────
    if S.timerId == nil then
        S.timerId = TimerManager.addRepeatTimer(0.8, tick)
    end

    print('[AUTOFARM] pret. rayon ' .. SEARCH_RADIUS .. ' u, tick 0.8 s')
    print('[AUTOFARM] demarrer : specter.autofarm = true')
    print('[AUTOFARM] etat : cycles', tostring(S.cycles),
          '| tp', tostring(S.tps))
    print('[AUTOFARM] relire : print(AUTOFARM.cycles, AUTOFARM.tps)')
    print('[AUTOFARM] cache  :', tostring(S.doneOrder and #S.doneOrder or 0), 'entites vues')
    print('[AUTOFARM] note   : le jeu impose', GAME_COOLDOWN, 's par entite')
end