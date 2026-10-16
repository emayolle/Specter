-- =====================================================================
-- init.lua — exécuté au début de CHAQUE nouveau lua_State.
--
-- Lancé par Specter au moment où l'état Lua est détecté, une fois par
-- reconnexion. Le script est embarqué dans la DLL : il n'y a pas de fichier à
-- lire, donc rien ne peut manquer entre la compilation et l'exécution.
--
-- Tout ce qui est ici s'exécute DANS le bac à sable : même environnement que
-- l'onglet « Lua Editor » de l'overlay. Donc :
--
--     specter.store       -- notre store, survit d'un Execute à l'autre
--     specter.var.x       -- les variables exposées par le pont (C++)
--     specter.log(...)    -- écrit dans la sortie de l'overlay
--
-- Et rien de tout ça ne touche les globales du jeu. Un nom neuf écrit ici
-- (`SPECTER_INIT`, ou `CATCH_AURA`…) part dans notre store, pas dans `_G`.
--
-- C'est l'endroit pour tout ce que tu préfères écrire en Lua plutôt qu'en
-- C++ : chaque reconnexion rejoue ce fichier, donc un hook posé ici survit
-- au relog sans qu'on ait à le réarmer en C++.
--
-- L'ordre compte :
--   * ce fichier s'exécute AVEC le bac à sable déjà créé (c'est lui qui le
--     crée, en fait) et avec `specter.var.*` disponible ;
--   * mais il s'exécute AVANT la première interaction du joueur. Ne suppose
--     pas que `pg.me` est déjà là : teste-le, ou attends le premier tick.
--
-- ⚠ Un point d'attention mesuré plus tard : appeler certaines API du jeu
--   qui changent le contexte de capture (throwItemFromBag) SUPPRIME les timers
--   répétés du TimerManager du jeu. Donc : n'utilisez pas ce fichier pour
--   piloter quelque chose qui_DOIT tourner en boucle, tant que le tick
--   d'autofarm n'est pas sur notre propre pompe.
-- =====================================================================

-- Ce qu'on a à faire ici, et ce que ça a coûté de le faire en C++ :
--   - le patch de stamina était un chunk C++ en constante, 应submit sur un
--     canal, avec un drapeau en double (un bool C++ ET un champ Lua sur la
--     classe du jeu). Ici il n'y a qu'un source de vérité.

print('[init] état Lua nouveau')

-- ── 1. stamina infinie ────────────────────────────────────────────
-- Pose le wrapper sur la CLASSE, donc toutes les instances sont couvertes
-- et une reconnexion ne le perd pas — ce fichier rejoue, point.
do
    local ok, AC = pcall(require, 'Common.Ability.Attribute.ActorCombatAttribute')
    if not ok or type(AC) ~= 'table' then
        print('[init] stamina : ActorCombatAttribute indisponible, passe')
    elseif type(rawget(AC, 'changeStamina')) ~= 'function' then
        print('[init] stamina : changeStamina absent, passe')
    else
        -- NOS marqueurs vivent dans NOTRE store, indexés par la classe. Pas sur
        -- AC : ce sont des noms à nous dans une table du jeu.
        SPECTER_STAMINA = SPECTER_STAMINA or {}
        if SPECTER_STAMINA[AC] == nil then
            local orig = rawget(AC, 'changeStamina')
            local w
            w = function(self, delta)
                local d = tonumber(delta)
                -- La porte est lue ici, à chaque appel, et vient du C++ :
                -- une seule vérité, pas de chunk à basculer.
                if d and d < 0 and specter.var.stamina then
                    local e = self and self.entity
                    if e == pg.me or e == pg.pawn or (e and e.isMainPlayer == true) then
                        return true
                    end
                end
                return orig(self, delta)
            end
            AC.changeStamina = w
            SPECTER_STAMINA[AC] = orig
            print('[init] stamina : patch posé sur la classe')
        else
            print('[init] stamina : déjà patché, rien à faire')
        end
    end
end

-- ── 2. l'espace pour le reste ────────────────────────────────────
-- Exemples de ce qui trouve sa place ici :
--   * poser un patch sur une table du jeu et le réinstaller à chaque state
--   * enregistrer des raccourcis dans SPECTER_INIT
--   * préparer une aura, une liste de cibles, un état de session
--
-- Rappel : un nom neuf écrit ici va dans notre store. Pour poser quelque
-- chose SUR une table du jeu, faites-le explicitement, et remindez qu'on
-- laisse alors un nom à nous dessus.
--
-- SPECTER_INIT = SPECTER_INIT or {}
-- SPECTER_INIT.nbEtats = (SPECTER_INIT.nbEtats or 0) + 1

-- ── 2. teleport ──────────────────────────────────────────────────
-- Ce que le C++ faisait en construisant un chunk de 40 lignes a chaque
-- clic. Ici la logique vit dans un fichier, et le C++ se contente d'appeler
--
--     specter.tp.here(x, y, z)
--
-- Trois arguments, comme demande. Le pas et la vitesse NE SONT PAS des
-- arguments : ce sont des reglages que l'utilisateur change depuis l'overlay,
-- donc ils restent cote C++ et se lisent ici par specter.var. Passer par des
-- arguments obligerait le C++ a les reformater dans le chunk a chaque clic,
-- ce qui est exactement ce qu'on supprime.
do
    local MAX_STEPS = 20000

    -- L'entite du joueur. Le jeu la met parfois a nil ; on la cherche.
    local function joueur()
        local e = pg.me
        if not e then
            for _k, _v in pairs(pg.global.actorMgr.uid2Ent) do e = _v break end
        end
        return e
    end

    specter.tp = specter.tp or {}

    -- Position du joueur.
    --
    -- Elle APPELLE specter.set_position(). Elle n'imprime rien et ne renvoie
    -- rien.
    --
    -- Elle faisait print('P x y z'), et le C++ relisait la ligne au sscanf.
    -- C'etait un contournement d'une epoque ou il n'existait aucune couche de
    -- liaison : sans pont, une valeur ne pouvait circuler qu'en passant par du
    -- texte. Le pont existe. Ecrire une ligne pour donner un nombre a une
    -- fonction du meme processus n'a plus de sens.
    --
    -- Et le bac a sable n'expose de toute facon pas les valeurs de retour, ce
    -- que la migration vers `return` a appris a mes depens : voir pump.cpp.
    --
    -- Les echecs se disent maintenant en retournant un message, parce que
    -- personne ne l'attend et qu'un echec muet est un echec qu'on ne voit pas.
    specter.tp.pos = function()
        local e = joueur()
        if not e then return 'pas d entite' end
        local p = e:getPosition()
        if not p then return 'pas de position' end
        specter.set_position(p[1], p[2], p[3], p[4] or 0)
        return
    end

    -- Un petit setPosition est rejete par le deplacement autoritaire et le
    -- joueur est rappele en arriere : on marche donc vers la cible par petits
    -- pas, dans le timer du jeu.
    --
    -- L'etat du deplacement vit dans NOTRE store, pas sur l'entite. Il etait
    -- sur e.__specter_tp : un nom a nous dans une table du jeu, visible par
    -- quiconque parcourt les champs. C'est le meme probleme que la stamina,
    -- et la meme correction.
    specter.tp.here = function(x, y, z)
        local e = joueur()
        if not e or not e.getPosition then return end

        local TM = require('Core.Timer.TimerManager')
        local store = specter.store

        -- Un deplacement precedent est annule AVANT de commencer, sinon deux
        -- timers se disputent la meme position.
        local prev = store.tpMove
        if prev and prev.tid then pcall(function() TM.removeTimer(prev.tid) end) end
        if prev then prev.active = false end

        local p = e:getPosition()
        if not p then return end

        local step = tonumber(specter.var.tp_step) or 5.5
        local speed = tonumber(specter.var.tp_speed) or 120
        if speed <= 0 then speed = 1 end

        local st = {
            active = true, i = 0, s = step,
            x0 = p[1], y0 = p[2], z0 = p[3],
            x1 = x,    y1 = y,    z1 = z,
        }

        local dx, dy, dz = st.x1 - st.x0, st.y1 - st.y0, st.z1 - st.z0
        local dist = (dx * dx + dy * dy + dz * dz) ^ 0.5
        local n = math.ceil(dist / st.s)
        if n < 1 then n = 1 end
        if n > MAX_STEPS then n = MAX_STEPS end
        st.n = n

        local s = st
        local tid
        tid = TM.addRepeatTimer(1 / speed, function()
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
                pcall(function() TM.removeTimer(tid) end)
            end
        end)
        st.tid = tid
        store.tpMove = st
        -- Pas de return ici : personne ne le lit, et le bac a sable
        -- l'ignorerait. print('deplacement en %d pas de %.2f') fonctionnerait,
        -- mais la ligne atterrirait dans le tampon du canal teleport, ou
        -- handle_result() tenterait de la lire.
    end

    -- Interrompre un deplacement en cours. Le C++ n'en a pas besoin pour
    -- l'instant, mais c'est le morceau qui manque toujours, et l'ecrire ici
    -- coute trois lignes.
    specter.tp.stop = function()
        local TM = require('Core.Timer.TimerManager')
        local st = specter.store.tpMove
        if not st then return end
        if st.tid then pcall(function() TM.removeTimer(st.tid) end) end
        st.active = false
        specter.store.tpMove = nil
    end

    -- ── reperer les floraisons et les teleporteurs ──────────────────────
    -- Un scan par appui sur le bouton, dans les scenes du monde ouvert.
    -- Les identifiants de scenes et de marque sont de la CONNAISSANCE DU
    -- JEU, pas de la logique : ils etaient en constantes C++ et le C++
    -- les formatait un par un dans le chunk. Ils sont ici, a cote du reste.
    local SCENES = { 3000, 3003 }
    local CRYSTAL_MARK_CONFIG = 10406
    local FLORAL_MARK_TYPE = 26

    -- Chaque repere est APPELLE, pas imprime.
    --
    -- kind : 0 = Floraison, 1 = cristal de teleportation. Le nom porte l' unite
    -- et le type, parce que cinq doubles a la suite, c'est une faute qui
    -- attend que quelqu'un la fasse.
    specter.tp.marks = function()
        local SU = require('Common.Utils.SceneUtils')
        local CTU = require('Utils.ClientTextUtils')

        local set = {}
        local function add(s)
            if s and s > 100 then set[s] = true end
        end

        local e = pg.me
        if e and e.sceneId then add(e.sceneId) end
        local m = pg.game and pg.game.map
        if m then add(m.sceneId); add(m.mainSceneId) end
        for _, sid in ipairs(SCENES) do add(sid) end

        local seen = {}
        for sid in pairs(set) do
            local ok, pts = pcall(SU.getSceneMarkPointData, sid)
            if ok and type(pts) == 'table' then
                for id, p in pairs(pts) do
                    if seen[id] then
                        -- deja vu
                    elseif p.markType == FLORAL_MARK_TYPE then
                        seen[id] = true
                        local mp = p.markPosition
                        if mp then
                            specter.add_mark(0, p.largeAreaId or 0,
                                             mp[1], mp[2], mp[3], '')
                        end
                    elseif p.markConfigId == CRYSTAL_MARK_CONFIG then
                        seen[id] = true
                        local mp = p.markPosition
                        if mp then
                            local nm = ''
                            if p.infoTitle then
                                local good, t = pcall(CTU.getLocalizationText, p.infoTitle)
                                if good and t then nm = tostring(t) end
                            end
                            nm = nm:gsub('%s+', ' ')
                            specter.add_mark(1, p.largeAreaId or 0,
                                             mp[1], mp[2], mp[3], nm)
                        end
                    end
                end
            end
        end

        -- Appele meme si le scan n'a rien trouve : c'est le but. Le
        -- finaliseur garde les listes en cache quand une scene n'en a pas, et
        -- une reponse partielle ne doit jamais ecraser de bonnes donnees.
        specter.marks_done()
    end
end

print('[init] prêt')