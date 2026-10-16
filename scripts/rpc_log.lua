-- rpc_log.lua -- journal des appels serveur, dans les DEUX sens.
--
--   tools/lua.sh -f scripts/rpc_log.lua      installe, puis affiche
--   tools/lua.sh -f scripts/rpc_log.lua      affiche encore
--
-- Relance le script aussi souvent que tu veux : la pose est refaite a chaque
-- passage (elle commence toujours par retirer ce qu'il y avait).
--
-- Pendant que ca tourne, dans le jeu :
--   specter.rpclog.suivre('RPC_CS_')   ne garder que ce prefixe
--   specter.rpclog.suivre()            tout garder
--   specter.rpclog.clear()             tout effacer
--   specter.rpclog.off() / .on()       arreter / reprendre
--   specter.rpclog.retirer()           tout demonter
--
--
-- LE PIEGE DES METHODES DUPLIQUEES -- mesure, pas intuition
--
-- J'ai d'abord pose une enveloppe sur
--     getmetatable(require('Core.Client.ClientEntity')).__index.serverMsg
-- et sur celle de ClientAoiComponent. Resultat : SORTIE a 0 pendant que le
-- joueur lançait des balles. Zero.
--
-- Mesure : EntityFactory._entities contient 149 classes d'entites, et 38
-- d'entre elles ont serverMsg dans LEUR PROPRE vtbl. La methode est COPIEE
-- dans chaque classe au moment du parse de la config, pas heritee. Donc :
--
--     WRONG   patcher la vtbl de ClientEntity
--     JUSTE   patcher les 38 vtbl qui ont serverMsg
--
-- Et pg.me (ClientMainPlayer) resout bien le sien : debug.getinfo donne
-- ClientAoiComponent.lua comme source, mais la table qui le contient est la
-- sienne.
--
-- Donc on enveloppe tout, et on remet les originaux a chaque passage -- sinon
-- on emballe nos propres enveloppes.
--
--
-- CE QUE C'EST PAR AILLEURS
--
-- Les methodes d'instance vivent dans `vtbl`, pas dans l'objet classe.
-- class.Class() renvoie un classType dont le METATABLE porte __index = vtbl
-- (Class.lua:399), et dont le __newindex leve une erreur sur un attribut
-- repete. D'ou :
--
--     getmetatable(CLS).__index.methode = ...
--
-- et jamais CLS.methode = ...
--
--
-- LE PIEGE DU PRINT QUI SURVIT PAS -- mesure, lui aussi
--
-- Une closure creee par un Execute precedent s'execute encore (pcall ->
-- ok=true) mais son print n'atteint plus rien : le tampon de reponse de cet
-- Execute-la n'existe plus. Les ENVELOPPES, elles, continuent, parce qu'elles
-- n'impriment jamais -- elles ecrivent seulement dans R. D'ou la separation.
--
--
-- GARDE-FOUS
--
--   - on appelle TOUJOURS l'original, hors de tout pcall
--   - on n'indexe AUCUN champ des tables recues : un argument table est note
--     '<table>', point
--   - rien dans _G : tout passe par specter.store et specter.rpclog

local sp = specter

-- ---------------------------------------------------------------- etat

local store = sp.store
local R = store.rpc

if not R then R = {} store.rpc = R end

-- L'etat survit d'un passage a l'autre et peut dater d'une version anterieure
-- du script : on complete plutot que d'ecraser. Un champ manquant part en nil
-- et casse un string.format deux cents lignes plus loin.
R.sortie = R.sortie or {}
R.entree = R.entree or {}
R.lignes = R.lignes or {}
R.tete = R.tete or 0
R.nsortie = R.nsortie or 0
R.nentree = R.nentree or 0
R.vue = R.vue or 0
R.poses = R.poses or 0
R.orig = R.orig or {}
if R.actif == nil then R.actif = true end

local LIGNES_MAX = 300
local enInterne = false          -- reentrance AoiComponent -> ClientEntity

-- ---------------------------------------------------------------- formes

-- On ne descend dans AUCUNE table. Nombre, chaine, booleen, et voila.
local function forme(t, n)
  if n > 6 then n = 6 end
  local out = {}
  for i = 1, n do
    local ty = type(t[i])
    if ty == 'string' or ty == 'number' or ty == 'boolean' then
      out[#out + 1] = tostring(t[i])
    elseif ty == 'nil' then
      out[#out + 1] = 'nil'
    elseif ty == 'function' then
      out[#out + 1] = '<fn>'
    elseif ty == 'table' then
      out[#out + 1] = '<table>'
    else
      out[#out + 1] = '<' .. ty .. '>'
    end
  end
  return table.concat(out, ', ')
end

local function note(sens, nom, t, n)
  R.vue = R.vue + 1                -- temoin de vie, incremente TOUJOURS

  if not R.actif then return end
  if R.suivre and nom:sub(1, #R.suivre) ~= R.suivre then return end

  local c = (sens == '>' and R.sortie or R.entree)
  c[nom] = (c[nom] or 0) + 1
  if sens == '>' then R.nsortie = R.nsortie + 1 else R.nentree = R.nentree + 1 end

  R.tete = R.tete + 1
  R.lignes[R.tete % LIGNES_MAX] = string.format('%s %-34s %s', sens, nom, forme(t, n))
end

-- ---------------------------------------------------------------- retirer

for _, o in ipairs(R.orig) do o.vtbl[o.cle] = o.orig end
R.orig = {}

-- ---------------------------------------------------------------- poser

local function enveloppe(vtbl, cle, avant)
  local orig = rawget(vtbl, cle)
  if type(orig) ~= 'function' then return false end
  R.orig[#R.orig + 1] = {vtbl = vtbl, cle = cle, orig = orig}
  vtbl[cle] = avant(orig)
  return true
end

local function avantSortie(orig)
  return function(self, name, ...)
    if not enInterne then
      local n = select('#', ...)
      local t = {n = n}
      for k = 1, n do t[k] = (select(k, ...)) end
      note('>', name or '?', t, n)
      enInterne = true
    end
    local r = orig(self, name, ...)
    enInterne = false
    return r
  end
end

-- SORTIE : les 38 vtbl qui portent une copie de serverMsg, plus les deux
-- classes de base (que le registre ne contient pas : ce sont des composants).
local pose = 0
local vues = {}

local function enveloppeSi(serverMsg)
  local v = getmetatable(serverMsg) and rawget(getmetatable(serverMsg), '__index')
  if type(v) ~= 'table' or vues[v] then return end
  vues[v] = true
  if enveloppe(v, 'serverMsg', avantSortie) then pose = pose + 1 end
end

local EF = require('Core.Common.EntityFactory')
for _, cls in pairs(EF._entities or {}) do
  if type(cls) == 'table' then enveloppeSi(cls) end
end
enveloppeSi(require('Core.Client.ClientEntity'))
enveloppeSi(require('Entities.SpaceEntities.CommonComponent.ClientAoiComponent'))

-- ENTREE : une seule classe, et ca marche deja -- une seule entite distribue.
local RpcIndex = require('Core.Common.RpcIndex')

local function nomDe(index)
  local n = RpcIndex.INDEX2RPC[index]
  if n == nil then n = RpcIndex.RPC_INDEX2NAME[index] end
  return n or ('#' .. tostring(index))
end

local vGH = getmetatable(require('Core.Client.GateClientRpcHandler')).__index

if enveloppe(vGH, 'entityMessageV2', function(orig)
  return function(self, entityId, raw, index, context, ...)
    local n = select('#', ...)
    local t = {n = n + 1}
    t[1] = entityId
    for k = 1, n do t[k + 1] = (select(k, ...)) end
    note('<', nomDe(index), t, n + 1)
    return orig(self, entityId, raw, index, context, ...)
  end
end) then pose = pose + 1 end

if enveloppe(vGH, 'entityMessage', function(orig)
  return function(self, entityId, raw, index, parameters, context)
    note('<', nomDe(index), {entityId, parameters}, 2)
    return orig(self, entityId, raw, index, parameters, context)
  end
end) then pose = pose + 1 end

R.poses = pose

-- ---------------------------------------------------------------- console
-- Refaite a chaque passage : c'est ici que print doit etre vivant.

local function trie(compte)
  local t = {}
  for nom, n in pairs(compte) do t[#t + 1] = {nom, n} end
  table.sort(t, function(a, b) return a[2] > b[2] end)
  return t
end

sp.rpclog = {}

function sp.rpclog.on()
  R.actif = true
  print('rpc_log : enregistrement ACTIF')
end

function sp.rpclog.off()
  R.actif = false
  print('rpc_log : enregistrement en pause')
end

function sp.rpclog.suivre(prefixe)
  R.suivre = prefixe
  print('rpc_log : filtre = ' .. (prefixe or '(tout)'))
end

function sp.rpclog.clear()
  R.sortie, R.entree, R.lignes = {}, {}, {}
  R.tete, R.nsortie, R.nentree = 0, 0, 0
  print('rpc_log : efface')
end

-- Remet le jeu exactement dans son etat initial : les originaux sont memorises
-- a la pose, donc c'est un retour vrai, pas une approximation.
function sp.rpclog.retirer()
  local n = 0
  for _, o in ipairs(R.orig) do o.vtbl[o.cle] = o.orig; n = n + 1 end
  R.orig = {}
  print(string.format('rpc_log : %d enveloppes retirees -- le jeu est intact', n))
end

function sp.rpclog.dump(n)
  n = n or 15
  print('')
  print(string.rep('=', 68))
  print(string.format('  enveloppes posees %d      appeles vus %d', R.poses, R.vue))
  print(string.format('  SORTIE %-6d            ENTREE %d', R.nsortie, R.nentree))
  if R.suivre then print(string.format('  filtre : %s', R.suivre)) end
  if not R.actif then print('  enregistrement EN PAUSE') end
  print(string.rep('=', 68))

  local so, se = trie(R.sortie), trie(R.entree)
  print('')
  print(string.format('--- SORTIE : ce que le jeu demande au serveur (%d noms) ---', #so))
  if #so == 0 then
    print('  (rien) -- fais une action en jeu, puis relance')
  end
  for i = 1, math.min(#so, 24) do
    print(string.format('  %-36s %5d', so[i][1], so[i][2]))
  end

  print('')
  print(string.format('--- ENTREE : ce que le serveur renvoie (%d noms) ---', #se))
  if #se == 0 then print('  (rien)') end
  for i = 1, math.min(#se, 24) do
    print(string.format('  %-36s %5d', se[i][1], se[i][2]))
  end

  print('')
  print(string.format('--- %d dernieres lignes ---', n))
  local dispo = math.min(R.tete, LIGNES_MAX)
  for i = 0, dispo - 1 do
    local l = R.lignes[(R.tete - i) % LIGNES_MAX]
    if l then print('  ' .. l) end
  end
  print(string.rep('=', 68))
end

print(string.format('rpc_log : %d enveloppes posees', pose))
if R.tete == 0 then
  print('           fais une action en jeu, puis relance ce script pour lire.')
else
  sp.rpclog.dump()
end