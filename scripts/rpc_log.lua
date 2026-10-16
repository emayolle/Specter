-- rpc_log.lua -- journal des appels serveur, dans les DEUX sens.
--
--   tools/lua.sh -f scripts/rpc_log.lua      installe, puis affiche
--   tools/lua.sh -f scripts/rpc_log.lua      affiche encore
--
-- Relance le script aussi souvent que tu veux : poser n'est fait qu'une fois,
-- l'affichage est reconstruit a chaque passage.
--
-- Pendant que ca tourne, dans le jeu :
--   specter.rpclog.suivre('RPC_CS_')   ne garder que ce prefixe
--   specter.rpclog.suivre()            tout garder
--   specter.rpclog.clear()             tout effacer
--   specter.rpclog.off() / .on()       arreter / reprendre
--
--
-- CE QUE C'EST
--
-- Les methodes d'instance d'une classe vivent dans `vtbl`, pas dans l'objet
-- classe. class.Class() renvoie un `classType` dont le METATABLE porte
-- __index = vtbl (Class.lua:399), et dont le __newindex leve une erreur sur un
-- attribut repete. Donc :
--
--     WRONG   GateClientRpcHandler.entityMessageV2 = maFonction
--     JUSTE   getmetatable(GateClientRpcHandler).__index.entityMessageV2 = ...
--
-- Mesure en jeu (probe-rpc-hook.lua) : les trois vtbl sont bien des tables, et
-- les quatre methodes vises y sont presentes.
--
-- LES QUATRE POINTES DE CAPTURE
--
--   ClientEntity.serverMsg          la sortie normale de tout le monde
--   ClientAoiComponent.serverMsg    sort par __callAoiFunc, donc elle NE PASSE
--                                   PAS par ClientEntity -- il faut les deux
--   entityMessageV2 / entityMessage l'arrivee, avec resolution index -> nom
--
-- ClientAoiComponent.serverMsg se termine parfois par un appel direct a
-- ClientEntity.serverMsg. Le drapeau enAoi evite de compter deux fois.
--
--
-- LE PIEGE : UN PRINT NE SURVIT PAS A UN EXECUTE
--
-- Mesure : une closure creee par un Execute precedent s'execute encore (ok=true)
-- mais son `print` n'atteint plus la sortie -- le tampon de reponse de cet
-- Execute-la n'existe plus. Les RECEVEURS, eux, continuent de tourner, parce
-- qu'ils n'impriment rien : ils ecrivent seulement dans R.
--
-- D'ou la separation ci-dessous : les enveloppes ne doivent JAMAIS imprimer,
-- et la console (dump, on, off, suivre) est REFAITE a chaque passage du
-- script, pour que son print soit vivant.
--
--
-- GARDE-FOUS
--
--   - on appelle TOUJOURS l'original, hors de tout pcall : une erreur du
--     logger est avalee, une erreur de l'original reste celle du jeu
--   - on n'indexe AUCUN champ des tables recues. Un argument table est note
--     '<table>', point
--   - les enveloppes restent en place pour toute la session
--   - rien dans _G : tout passe par specter.store et specter.rpclog

local sp = specter
local unpack_ = table.unpack or unpack

-- ---------------------------------------------------------------- etat

local store = sp.store
local R = store.rpc

if not R then
  R = {}
  store.rpc = R
end

-- L'etat survit d'un passage a l'autre, donc il peut dater d'une version
-- anterieure du script. On complete plutot que d'ecraser : sinon un champ
-- manquant part en nil et casse un string.format bien plus loin.
R.sortie = R.sortie or {}
R.entree = R.entree or {}
R.lignes = R.lignes or {}
R.tete = R.tete or 0
R.nsortie = R.nsortie or 0
R.nentree = R.nentree or 0
R.vue = R.vue or 0
R.poses = R.poses or 0
if R.actif == nil then R.actif = true end

local LIGNES_MAX = 300
local enAoi = false            -- reentrance AoiComponent -> ClientEntity

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

-- ---------------------------------------------------------------- pose

if not R.arme then
  local pose = 0
  local RpcIndex = require('Core.Common.RpcIndex')

  -- Le jeu fait deja cette conversion dans entityMessageV2. On la refait pour
  -- mettre un NOM dans le journal plutot qu'un entier de 2 milliards.
  local function nomDe(index)
    local n = RpcIndex.INDEX2RPC[index]
    if n == nil then n = RpcIndex.RPC_INDEX2NAME[index] end
    return n or ('#' .. tostring(index))
  end

  local function enveloppe(vtbl, cle, avant)
    local orig = rawget(vtbl, cle)
    if type(orig) ~= 'function' then
      print(string.format('rpc_log : %s introuvable (%s) -- passe', cle, type(orig)))
      return
    end
    R.orig = R.orig or {}
    R.orig[#R.orig + 1] = {vtbl = vtbl, cle = cle, orig = orig}
    vtbl[cle] = avant(orig)
    pose = pose + 1
  end

  local CE = require('Core.Client.ClientEntity')
  local vCE = getmetatable(CE).__index

  enveloppe(vCE, 'serverMsg', function(orig)
    return function(self, name, ...)
      if not enAoi then
        local n = select('#', ...)
        local t = {n = n}
        for k = 1, n do t[k] = (select(k, ...)) end
        note('>', name or '?', t, n)
      end
      return orig(self, name, ...)
    end
  end)

  local AC = require('Entities.SpaceEntities.CommonComponent.ClientAoiComponent')
  local vAC = getmetatable(AC).__index

  enveloppe(vAC, 'serverMsg', function(orig)
    return function(self, name, ...)
      if not enAoi then
        local n = select('#', ...)
        local t = {n = n}
        for k = 1, n do t[k] = (select(k, ...)) end
        note('>', name or '?', t, n)
        enAoi = true
      end
      local r = orig(self, name, ...)
      enAoi = false
      return r
    end
  end)

  local GH = require('Core.Client.GateClientRpcHandler')
  local vGH = getmetatable(GH).__index

  enveloppe(vGH, 'entityMessageV2', function(orig)
    return function(self, entityId, raw, index, context, ...)
      local n = select('#', ...)
      local t = {n = n + 1}
      t[1] = entityId
      for k = 1, n do t[k + 1] = (select(k, ...)) end
      note('<', nomDe(index), t, n + 1)
      return orig(self, entityId, raw, index, context, ...)
    end
  end)

  enveloppe(vGH, 'entityMessage', function(orig)
    return function(self, entityId, raw, index, parameters, context)
      note('<', nomDe(index), {entityId, parameters}, 2)
      return orig(self, entityId, raw, index, parameters, context)
    end
  end)

  R.arme = true
  R.poses = pose
  print(string.format('rpc_log : %d/4 points poses', pose))
end

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

-- Remet le jeu exactement dans son etat initial. Les originaux sont memorises
-- a la pose, donc c'est un retour vrai, pas une approximation.
function sp.rpclog.retirer()
  local n = 0
  for _, o in ipairs(R.orig or {}) do
    o.vtbl[o.cle] = o.orig
    n = n + 1
  end
  R.orig, R.arme = nil, false
  print(string.format('rpc_log : %d/4 enveloppes retirees -- le jeu est intact', n))
end

function sp.rpclog.dump(n)
  n = n or 15
  print('')
  print(string.rep('=', 68))
  print(string.format('  points poses %d/4      appeles vus %d', R.poses or 0, R.vue))
  print(string.format('  SORTIE %-6d            ENTREE %d', R.nsortie, R.nentree))
  if R.suivre then print(string.format('  filtre : %s', R.suivre)) end
  if not R.actif then print('  enregistrement EN PAUSE') end
  print(string.rep('=', 68))

  local so, se = trie(R.sortie), trie(R.entree)
  print('')
  print(string.format('--- SORTIE : ce que le jeu demande au serveur (%d noms) ---', #so))
  if #so == 0 then
    print('  (rien)  -- bouge ton personnage, ouvre un coffre, puis relance')
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

if R.tete == 0 then
  print(string.format('rpc_log : pret, %d/4 points poses -- fais une action en jeu,',
        R.poses or 0))
  print('           puis relance ce script pour lire.')
else
  sp.rpclog.dump()
end