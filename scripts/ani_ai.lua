-- ani_ai.lua -- case a cocher « IA des Aniimoe », appliquee au jeu.
--
-- La case vit dans le menu (features/aniai/). Elle ecrit un booleen C++,
-- expose ici comme `specter.var.ani_ia`. CE SCRIPT EST LE SEUL a l'ecrire
-- dans AiConst -- comme pour l'autofarm, une seule ecriture, un seul lecteur,
-- aucune copie qui peut diverger.
--
-- Ce qu'on ecrit :
--
--     Common.Const.AiConst.GLOBAL_OPEN_TICK = <le flag>
--
-- false : les Aniimoe ne font rien (ils ne poursivent pas, n attacked... en
-- francais : « Dumb Enemy »)
-- true  : leur IA reprend
--
--
-- UN SEUL PILOTE, IL NE MEURT PAS
--
-- Comme autofarm_loop : une minuterie repetitive, posee une fois par nouvel
-- etat Lua, sans condition d'arret. Elle survit a un relog parce qu'elle est
-- rejouee avec le reste du bootstrap.
--
--
-- ON REECRIT A CHAQUE PASSAGE, ET NON SEULEMENT AU CHANGEMENT
--
-- Le premier reflexes est « ecris si la valeur differe ». C'est faux ici : le
-- jeu peut remettre GLOBAL_OPEN_TICK a sa valeur entre deux passages, et on
-- ne le remarke pas -- la case dirait activee alors que l'IA tourne. Une
-- affectation de table toutes les 0.25 s ne coute rien, et le dernier ecrivain
-- gagne toujours.
--
-- 0.25 s et pas moins : le jeu lit cette constante a chaque tick d'IA, et on
-- veut que l'arret soit pris en compte vite. En dessous, on ecrit plus vite que
-- le jeu ne lit, pour rien.
--
--
-- CE QUI EST ECRIT ET OU
--
-- Tout passe par specter.store et le timer du jeu (Core.Timer.TimerManager).
-- Rien dans _G. Une table du jeu est lue et une ecrite -- c'est exactement ce
-- que la case doit faire, et rien d'autre n'est touche.

local sp = specter
local store = sp.store
local TM = require('Core.Timer.TimerManager')

local function resoudreAiConst()
    local A = package.loaded['Common.Const.AiConst']
    if type(A) ~= 'table' then
        local ok, m = pcall(require, 'Common.Const.AiConst')
        A = ok and m or nil
    end
    if type(A) ~= 'table' then return nil end
    return A
end

local AiConst = resoudreAiConst()

-- Une seule fois, au demarrage : resoudre le module a chaque tick serait du
-- travail repete pour un resultat qui ne change pas.
if AiConst == nil then
    -- Il peut ne pas etre charge au premier passage. On retente plus tard.
    TM.addRepeatTimer(2, function()
        AiConst = resoudreAiConst()
        if AiConst ~= nil then
            store.ani_ai_disponible = true
            appliquer()
        end
    end)
else
    store.ani_ai_disponible = true
end

local function appliquer()
    local A = resoudreAiConst()
    if A == nil then
        -- La case affiche ce nombre : 0 introuvable, 1 activee, 2 desactivee.
        -- Sans cette ecriture, la case dirait « introuvable » indefiniment
        -- alors que tout fonctionne.
        specter.var.ani_ia_etat = 0
        return
    end

    local veut = specter.var.ani_ia and true or false

    -- Ecriture inconditionnelle : le jeu peut remettre sa valeur entre deux
    -- passages, et une ecriture conditionnelle ne le verrait pas.
    A.GLOBAL_OPEN_TICK = veut

    specter.var.ani_ia_etat = veut and 1 or 2
end

appliquer()
TM.addRepeatTimer(0.25, appliquer)