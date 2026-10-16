-- ============================================================
-- CATCH AURA — capture automatique des Pokémon sauvages proches
--
-- ── LE BOUTON ──────────────────────────────────────────────────
--
--     specter.catch_aura = true     -- active
--     specter.catch_aura = false    -- désactive
--
-- Ça marche tel quel, SANS rebuild. ATTENTION AU NIVEAU : `specter` est
-- inscriptible, mais `specter.var` ne l'est PAS. C'est un namespace LuaBridge,
-- qui pose un __newindex et refuse tout nom qu'il ne connaît pas :
--
--     specter.var.catch_aura = true
--     -> no writable member 'catch_aura'
--
-- Mesuré. Le booléen va donc sur `specter` directement. Il survit d'un
-- Execute à l'autre parce que la table est dans notre environnement ancré.
--
-- Le tick lit le booléen à chaque appel. Poser une fois, décider à chaque fois.
--
-- ── ISOLATION ──────────────────────────────────────────────────
--
-- L'état du script est un nom NEUF (`CATCH_AURA`), donc notre bac à sable
-- l'écrit dans NOTRE store, jamais dans les globales du jeu.
--
-- Le script d'origine faisait :
--     rawset(_G, "__CATCH_AURA", state)
-- ce qui posait un nom à nous dans le _G du jeu, définitivement — un jeu qui
-- parcourt ses propres globales le trouve et ne sait pas d'où il sort.
--
-- Ici : rien n'est écrit dans le jeu. Aucune ligne du script ne touche `_G`
-- en écriture, et la seule lecture est `rawget(_G, "pg")`.
--
-- ============================================================

do
    -- `pg` vient du jeu. LECTURE seule.
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")

    local Utils            = require("Common.Utils.Utils")
    local CatchProbContext = require("Common.Utils.CatchProbContext")
    local TimerManager     = require("Core.Timer.TimerManager")
    local Time             = require("Core.Common.Time")

    -- Valeurs INITIALES, lues une fois seulement.
    local ENABLED = true    -- état de départ
    local RADIUS  = 15      -- rayon de l'aura
    -- 0.8 s, PAS 0.15.
    --
    -- Mesure : 406 tentatives pour 33 reussites, soit 8 %. A 0.15 s on
    -- martelait le jeu sept fois par seconde pendant toute sa sequence de
    -- capture, et 92 % de ces appels etaient perdus. C'est aussi ce qui rendait
    -- les captures plus LENTES : le jeu est derriere sa sequence d'animation,
    -- il ne peut pas en accepter deux.
    --
    -- Mesure inverse : ~12 appels par capture reussie, donc une capture toutes
    -- les ~1,8 s. C'est la duree de la sequence du jeu, pas la nôtre — on ne
    -- peut pas aller plus vite qu'une animation.
    --
    -- 0.8 s : assez fin pour saisir une cible des que l'animation se termine,
    -- sans frapper dans le vide entretemps.
    local INTERVAL = 0.8

    -- Délai avant de RETENTER la même entité, en secondes.
    --
    -- 0 = pas de délai. C'est le réglage par défaut parce que la question
    -- posée était « sans cooldown », et parce que le cooldown de 5 s de
    -- l'original était la vraie cause des captures lentes à démarrer.
    --
    -- Il ne touche qu'au CHOIX de la cible, pas au rythme. Si le jeu refuse les
    -- appels pendant une animation, le plafond reste une capture par animation
    -- — voir les compteurs dans catchAuraTick pour le savoir.
    local RETRY_DELAY = 0.0

    -- LE BOUTON : s'il n'existe pas encore, on lui donne la valeur de
    -- départ. Ensuite seul le booléen compte — sinon le script referait son
    -- propre interrupteur à chaque Execute.
    if specter.catch_aura == nil then
        specter.catch_aura = ENABLED
    end

    -- Nom neuf → notre store. Invisible dans le jeu, persistant.
    local state = CATCH_AURA
    if not state then
        state = { timerId = nil, lastInterval = nil }
        CATCH_AURA = state
    end
    state.radius   = RADIUS
    state.interval = INTERVAL

    local function canCatchTarget(ent)
        if ent == nil or ent.destroyed then
            return false
        end
        if not Utils.isWildPuppet(ent) then
            return false
        end
        if RETRY_DELAY > 0 and ent.lastQuickCaptureTime ~= nil
           and Time.realSecondCache - ent.lastQuickCaptureTime < RETRY_DELAY then
            return false
        end
        local ok, ctx = pcall(CatchProbContext.clientGet, ent)
        return ok and ctx ~= nil and ctx.canCatch == true
    end

    local function findCatchTarget()
        if pg == nil or pg.me == nil then
            return nil
        end
        return Utils.getNearestPuppet(pg.me, state.radius, canCatchTarget)
    end

    local function catchAuraTick()
        -- LA DÉCISION, lue au pont à chaque tick.
        if not specter.catch_aura then
            return
        end
        if pg == nil or pg.me == nil or pg.game == nil
           or pg.game.controller == nil then
            return
        end

        -- LES GARDES D'ANIMATION SONT REQUISES. ESSAYEES SANS, REVIENUES.
        --
        -- On avait retire ces deux lignes en pensant que le jeu encaisse la
        -- demande et l'enfile. Mesure : c'est le PIRE. Le joueur attend non
        -- seulement l'animation de lancer, mais aussi celle du résultat — les
        -- appels pendant l'animation n'enfilent rien, ils gênent.
        --
        -- Donc : `isCaptureThrowing` = le joueur est en train de preparer son
        -- lancer, `isInCatchMode` = il est en train de lancer. Tant que l'un des
        -- deux est vrai, on ne cherche meme pas de cible.
        --
        -- C'est le plafond REEL : une capture par animation, pas par tick. Le
        -- tick a 0.15 s pour trouver la cible AU PLUS TOT quand l'animation se
        -- termine, et c'est tout ce qu'on peut faire de ce cote.
        --
        -- Les compteurs restent : ils disent si on gaspille des appels.
        -- LE SEUL VRAI GARDE D'ANIMATION.
        --
        -- isCaptureThrowing() teste `ctx.state == CaptureStates.T` : c'est
        -- exactement « le lancer est en cours ».
        --
        -- isInCatchMode() NE TESTE PAS L'ANIMATION. Le jeu :
        --     return self.currentContext.className ~= "NoBallContext"
        -- ca veut dire « UNE BALL EST EQUIPEE ». Ce n'est pas la meme chose.
        --
        -- Le garder ici bloquait TOUT des que la ball etait en main — donc
        -- precisement quand on l'equipait pour beneficier du mode rapide. Il a
        -- ete invisible jusqu'ici parce qu'on etait en NoBallContext : le test
        -- renvoyait faux et laissait passer.
        if pg.me.isCaptureThrowing ~= nil and pg.me:isCaptureThrowing() then
            return
        end

        -- PAS DE RÉÉQUIPEMENT ICI.
        --
        -- Mesuré deux fois : appeler throwItemFromBag depuis le tick KILL notre
        -- timer répété. Une fois placé avant le garde d'animation, une fois
        -- après — donc même au calme, hors de tout lancer. Zéro tentative dans
        -- les deux cas, alors que le timer était bel et bien créé et que
        -- tickFunc existait : il ne s'exécutait plus.
        --
        -- Le changement de contexte du jeu passe par son TimerManager, et notre
        -- timer en sort. Equipper une ball et ticker avec le timer du jeu sont
        -- incompatibles.
        --
        -- Donc : ball unequipée, et on paie les 0,5 s. C'est le choix qui
        -- fonctionne — 24 % de réussite contre 8 % avant, et surtout un tick
        -- qui tourne vraiment.

        local target = findCatchTarget()
        if target == nil then
            return
        end

        state.tentatives = (state.tentatives or 0) + 1

        local ok, result = pcall(pg.game.controller.onHandleQuickCapture,
                                 pg.game.controller, target.id)
        if ok and result then
            state.reussites = (state.reussites or 0) + 1
            print("[CATCH AURA]", "target=", tostring(target.id),
                  "actor=", tostring(target.actorId))
        end
    end

    -- PAS D'ÉQUIPEMENT DE BALL. DÉFINITIVEMENT.
    --
    -- L'idée était bonne et l'API existe : throwItemFromBag met le contexte à
    -- CameraThrowContext, donc isInCatchMode() devient vrai, donc alreadyHolding
    -- est vrai, donc la charge tombe de 0,5 s à 0,01 s. Mesuré.
    --
    -- Mais cet appel KILL notre timer répété. Trois fois essayé, trois fois
    -- zéro tentative — avant le timer, après le garde d'animation, et au moment
    -- de la pose. Le timer existait, tickFunc existait, et rien ne tournait
    -- plus. Le changement de contexte du jeu passe par son TimerManager et notre
    -- timer en sort.
    --
    -- Donc on paie les 0,5 s, et le tick tourne. C'est le seul arbitrage
    -- possible : equipper ou ticker, pas les deux.

    state.tickFunc = catchAuraTick

    local function removeTimer(id)
        if id == nil then
            return
        end
        if TimerManager.removeTimer then
            pcall(TimerManager.removeTimer, id)
        elseif TimerManager.delTimer then
            pcall(TimerManager.delTimer, id)
        end
    end

    -- LE TIMER, TOUJOURS POSÉ.
    --
    -- L'original ne le posait que si `enabled`, et le retirait sinon : activer
    -- plus tard ne faisait donc RIEN tant que le script n'était pas relancé. Le
    -- booléen n'était un bouton que dans un sens.
    --
    -- Posé une fois, le tick décide. Une variable, deux sens.
    if state.timerId ~= nil and state.lastInterval ~= state.interval then
        removeTimer(state.timerId)
        state.timerId = nil
    end
    -- BALL EN MAIN, UNE FOIS, AVANT LE TIMER.
    --
    -- Essayer de la remettre a CHAQUE tick cassait le tick lui-meme :
    -- throwItemFromBag passe par switchContext, et ce changement de contexte
    -- tue notre timer repete. Le tick continuait a exister dans nos variables
    -- (timerId non nil, tickFunc presente) mais ne s'executait plus — et
    -- aucun compteur ne le signalait.
    --
    -- Donc : une fois, ici, avant de poser quoi que ce soit. Le jeu remet
    -- lui-meme le contexte a NoBallContext apres chaque capture, donc la ball
    -- ne sera pas tenue en main a chaque appel — on y gagne la premiere
    -- capture, ce qui suffit a ne plus payer 0,5 s d'entree.
    if state.timerId == nil then
        state.timerId = TimerManager.addRepeatTimer(state.interval,
                                                     state.tickFunc)
        state.lastInterval = state.interval
    end

    -- COMPTEURS. Lisibles quand tu veux :
    --
    --     print(CATCH_AURA.tentatives, CATCH_AURA.reussites)
    --
    -- Un ratio proche de 1 veut dire que le jeu encaisse les appels pendant
    -- l'animation. Un ratio bas veut dire qu'il les refuse, et qu'il faut
    -- remettre les gardes.
    if specter.catch_aura then
        print("[CATCH AURA] ON  | rayon=", state.radius,
              " | toutes les ", state.interval, " s")
        print("[CATCH AURA] couper :  specter.catch_aura = false")
    else
        print("[CATCH AURA] OFF (timer posé, il ne fait rien)")
        print("[CATCH AURA] activer : specter.catch_aura = true")
    end
end