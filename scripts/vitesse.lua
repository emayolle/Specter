-- vitesse.lua — multiplicateurs de vitesse, pour le joueur et ses pets.
--
-- EMBARQUE dans la DLL, joue une fois par nouveau lua_State. Il pose le patch et
-- le REPOSE : un patch qui survit au redemarrage mais pas a une reconnexion est
-- un patch qui disparait sans qu'on sache pourquoi.
--
--
-- 1. LE LEVIER
--
-- La vitesse n'est pas un champ, ce sont des METHODES.
-- `pg.me.actorCombatAttribute` porte :
--
--     getWalkSpeedRatio    getRunSpeedRatio   getSprintSpeedRatio
--     getDashSpeedRatio    getGlideSpeedRatio getSwimSpeedRatio
--     getSwimFastSpeedRatio                   getStaminaCostRatio
--
-- Toutes valent 1 a l'etat normal. On ne les ECRIT pas : on les ENTOURE.
--
-- 2. CLASSE OU INSTANCE ? LES DEUX ECHOUENT, POUR DEUX RAISONS
--
-- POSE SUR LA CLASSE : le joueur a bien ete accelerates (constate), mais
-- l'effet s'est etendu a 32 autres entites -- PNJ, ClientPuppet -- mesurees a la
-- meme valeur. Accelerer ce qui te poursuit n'est pas un bonus.
--
-- POSE SUR L'INSTANCE : plus personne n'accelere. Ni joueur, ni pet. La vitesse
-- du pet ne changeait que parce qu'un script de test l'avait appliquee a la main
-- sur l'instance du pet -- et le joueur, lui, n'a jamais bouge. Un champ pose
-- sur l'instance n'est pas la que le jeu va le chercher.
--
-- 3. LE PATCH QUI MARCHE POUR LES DEUX : LA CLASSE, CONDITIONNELLE
--
-- On installe sur la classe -- c'est la que le jeu resout la methode -- mais le
-- multiplicateur n'est applique que si l'instance appelante est celle du joueur
-- ou d'un de ses pets. Pour tout le reste, la valeur d'origine passe inchangee.
--
--     Joueur  x N      <- ce qu'on veut
--     Pets    x N      <- ce qu'on veut
--     PNJ     x 1      <- mesure : 32 entites restees a 1
--
-- 4. L'APPARTENANCE EST UN ENSEMBLE, PAS UNE RECHERCHE
--
-- Savoir si `self` est le joueur ou un pet ne se cherche pas a chaque appel :
-- `pg.getEntities()` est un balayage de scene, et l'appel peut venir des
-- dizaines d'entites. On tient donc un ENSEMBLE des attributs vises, rafraichi
-- toutes les demi-secondes par le pilote, et l'appel ne fait qu'une lecture de
-- table. Le rafraichi est necessaire parce que le jeu peut recreer
-- `actorCombatAttribute` -- et un patch devenu inerte sans raison est le pire
-- des pannes.
--
-- 5. LES MULTIPLICATEURS SONT LUS EN DIRECT
--
-- Lus dans `specter.var` a l'appel, jamais captures : un curseur bouge agit
-- immediatement, sans rejouer ce script.

local TM = require('Core.Timer.TimerManager')

-- NOM LISIBLE -> METHODE DU JEU. C'est aussi le contrat avec le C++ : il lit
-- `vit_<nom>` de cette liste pour construire ses curseurs. Une methode renommee
-- par une mise a jour casse le lien de maniere visible, plutot que de decaler
-- silencieusement les curseurs d'une ligne.
-- NOM LISIBLE -> METHODE DU JEU. C'est aussi le contrat avec le C++ : il lit
-- `vit_<nom>` de cette liste pour construire ses curseurs. Une methode renommee
-- par une mise a jour casse le lien de maniere visible, plutot que de decaler
-- silencieusement les curseurs d'une ligne.
--
-- `marche` n'y est PLUS : mesure, le jeu n'appelle jamais
-- `getWalkSpeedRatio` (0 appel sur une session entiere). Le curseur a ete retire
-- plutot que grise -- un reglage qui ne peut rien faire est pire que pas de
-- reglage, parce qu'il donne l'illusion qu'on peut regler quelque chose.
--
-- Ce qui suit, c'est la classification reelle, lue dans le SOURCE du jeu
-- (AIControllerUtils.lua) et confirmee par des compteurs d'appels :
--
--     sprint         886 appels   config x getSprintSpeedRatio()   -> agit
--     dash           485 appels   idem                             -> agit
--     course         114 appels   getRunSpeed(), valeur ABSOLUE    -> peu d'effet
--     cout_stamina   208 appels   config x getStaminaCostRatio()   -> agit
--     vol             45 appels   config x getGlideSpeedRatio()    -> agit
--     nage_rapide      6 appels   config x getSwimFastSpeedRatio() -> agit
--     nage              6 appels   config x getSwimSpeedRatio()     -> agit
--
-- Et ce qui n'y est pas, parce que ca n'existe pas cote client :
--
--     GRIMPER. Source : `getClimbSpeed` = climbSpeedLevels[canClimb], sans
--     aucun ratio. Et `SetAISpeed` n'a QU'UN appelant dans tout le jeu --
--     AIControllerUtils. L'escalade du pet que TU controles ne passe pas par ce
--     canal-la. Quatre tentatives mesurees (champ aiClimbSpeed ecrit puis ecrase
--     au rafraichissement, puis fonction getClimbSpeed interceptee) : l'ecriture
--     tient, la valeur demandee est bien 15, et l'escalade reste identique.
local RATIOS = {
    { nom = 'course',       methode = 'getRunSpeedRatio' },
    { nom = 'sprint',       methode = 'getSprintSpeedRatio' },
    { nom = 'dash',         methode = 'getDashSpeedRatio' },
    { nom = 'vol',          methode = 'getGlideSpeedRatio' },
    { nom = 'nage',         methode = 'getSwimSpeedRatio' },
    { nom = 'nage_rapide',  methode = 'getSwimFastSpeedRatio' },
    { nom = 'cout_stamina', methode = 'getStaminaCostRatio' },
}

local MARQUE_ORIG = '_specterOrigRatio_'
local REAPPLY_S   = 0.5

local E = specter.store.vitesse
if type(E) ~= 'table' then
    E = {}
    specter.store.vitesse = E
end

-- L'ensemble des attributs ou le multiplicateur s'applique. Cle = la table
-- elle-meme : les tables sont des cles valides en Lua, et la lecture est O(1).
--
-- On met des vraies cles (les objets), pas tostring() de l'objet : une cle
-- textuelle exigerait un tostring PAR APPEL, ce qui est de la comparaison de
-- pointeurs deguisee en chaine.
E.vises = E.vises or {}

local function classeDe(en)
    if type(en) ~= 'table' then return nil end
    local mt = getmetatable(en)
    local i = mt and mt.__index
    return i and (i.className or i.__cname) or nil
end

local function attrDe(en)
    if not en then return nil end
    local a = rawget(en, 'actorCombatAttribute')
    if type(a) ~= 'table' then return nil end
    local mt = getmetatable(a)
    local idx = (type(mt) == 'table') and rawget(mt, '__index') or nil
    if type(idx) ~= 'table' then return nil end
    for _, r in ipairs(RATIOS) do
        if type(rawget(idx, r.methode)) == 'function' then return a, idx end
    end
    return nil
end

-- Le multiplicateur demande au jeu. LU A L'APPEL, jamais capture : c'est ce qui
-- rend les curseurs instantanes.
--
-- Une valeur absente vaut 1. « On ne sait pas » n'est jamais « zero » : sinon
-- un binding manquant figerait le jeu a l'arret.
local function multDe(methode)
    for _, r in ipairs(RATIOS) do
        if r.methode == methode then
            local v = specter.var['vit_' .. r.nom]
            if type(v) == 'number' then return v end
            return 1
        end
    end
    return 1
end

-- Pose le patch de CLASSE, conditionne a l'appartenance.
--
-- L'original est memorise UNE FOIS par methode. Le poser a chaque balayage
-- empilerait les wrappers : trois rechargements et la vitesse serait cubique.
local function poserClasse(idx)
    local poses = 0
    for _, r in ipairs(RATIOS) do
        local orig = rawget(idx, r.methode)
        if type(orig) == 'function' and rawget(idx, MARQUE_ORIG .. r.methode) == nil then
            rawset(idx, MARQUE_ORIG .. r.methode, orig)
            local methode = r.methode
            rawset(idx, methode, function(self, ...)
                local rep = { pcall(orig, self, ...) }
                if not rep[1] then error(rep[2], 0) end
                if type(rep[2]) == 'number' and E.vises[self] then
                    return rep[2] * multDe(methode)
                end
                return unpack(rep, 2)
            end)
            poses = poses + 1
        end
    end
    return poses
end

-- Remet les originaux sur la classe.
--
-- Indispensable : sans ca, decocher la case ne changerait RIEN de visible, et le
-- seul moyen de revenir a une vitesse normale serait de relancer le jeu.
local function restaurerClasse(idx)
    local n = 0
    for _, r in ipairs(RATIOS) do
        local orig = rawget(idx, MARQUE_ORIG .. r.methode)
        if orig ~= nil then
            rawset(idx, r.methode, orig)
            rawset(idx, MARQUE_ORIG .. r.methode, nil)
            n = n + 1
        end
    end
    return n
end

-- Un balayage : on rafraichit l'ensemble des vises, et on pose ou on retire le
-- patch de classe selon l'interrupteur.
local function balayer()
    local actif = (specter.var.vit_actif == true)
    local poses, restaures = 0, 0

    -- 1. rafraichir l'ensemble. On ne le fait que si la feature est activee :
    --    sinon on vide, ce qui suffit a neutraliser les wrappers.
    for k in pairs(E.vises) do E.vises[k] = nil end
    if actif then
        local me = pg.me
        local a = attrDe(me)
        if a then E.vises[a] = true end
        -- Les pets : tous ceux qui portent l'attribut. Un pet peut changer en
        -- cours de session, et « mon pet » n'a pas d'identifiant connu du joueur
        -- -- on prend la classe, et la presence de l'attribut fait le reste. Les
        -- betes sauvages n'ont pas les memes methodes.
        for _, en in pairs(pg.getEntities() or {}) do
            if classeDe(en) == 'ClientPet' then
                local pa = attrDe(en)
                if pa then E.vises[pa] = true end
            end
        end
    end

    -- 2. poser ou retirer.
    local me = pg.me
    local _, idx = attrDe(me)
    if idx then
        if actif then
            poses = poserClasse(idx)
        else
            restaures = restaurerClasse(idx)
        end
    end

    E.patches = (E.patches or 0) + poses
    E.restores = (E.restores or 0) + restaures
    E.actif = actif
    local n = 0
    for _ in pairs(E.vises) do n = n + 1 end
    E.nbVises = n
    return poses, restaures
end

-- ----------------------------------------------------------------- pilote
--
-- UN SEUL timer, comme autofarm, coffres et le reste : il lit le booleen C++ et
-- fait ce qu'il faut. Il n'a pas de booleen propre, donc il ne peut pas diverger
-- de la case a cocher.
E.pilote = TM.addRepeatTimer(REAPPLY_S, function()
    local ok, err = pcall(balayer)
    if not ok then
        E.erreurs = (E.erreurs or 0) + 1
        E.derniereErreur = tostring(err)
        if E.erreurs <= 1 then print('[vitesse] ERREUR : ' .. tostring(err)) end
    end
end)

balayer()

print('[vitesse] patch de classe conditionnel en place -- case et curseurs dans le menu')

-- L'ETAT, pour le diagnostic.
--
-- Un seul appel dit ce qui est reellement patche et combien d'entites sont
-- concernees -- et non ce qu'on croit avoir patche. C'est la seule distinction
-- qui compte si le jeu recree `actorCombatAttribute`, ou si le curseur a bouge
-- sans que rien ne change.
specter.vitesse = specter.vitesse or {}
specter.vitesse.etat = function()
    local me = pg.me
    local _, idx = attrDe(me)
    local ratios = {}
    if idx then
        for _, r in ipairs(RATIOS) do
            ratios[r.nom] = {
                patche = (rawget(idx, MARQUE_ORIG .. r.methode) ~= nil),
                curseur = specter.var['vit_' .. r.nom],
            }
        end
    end
    return {
        actif = (specter.var.vit_actif == true),
        classePatched = (idx ~= nil
            and rawget(idx, MARQUE_ORIG .. RATIOS[1].methode) ~= nil),
        entitesVises = E.nbVises or 0,
        ratios = ratios,
        erreurs = E.erreurs or 0,
    }
end