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

print('[init] prêt')