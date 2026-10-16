-- capture_succes.lua -- que contient REALLY le OnCaptureSuccess ?
--
-- On ne se fie pas au compteur : on lit la liste des captures renvoyee par le
-- serveur et on affiche les templateId. Si elle est vide, le compteur mentait.
--
--   tools/lua.sh -f scripts/capture_succes.lua     arme
--   (lance une balle)  puis relance pour lire

local sp = specter
local R = sp.store.succes
if R then
  print('')
  print(string.rep('=', 62))
  print('  OnCaptureSuccess recus : ' .. R.n)
  print(string.format('  dernier : type(infos)=%s  taille=%s  session=%s',
        tostring(R.typeInfos), tostring(R.nbInfos), tostring(R.session)))
  if R.dernier and #R.dernier > 0 then
    print('  captures du dernier succes :')
    for _, info in ipairs(R.dernier) do
      print(string.format('    templateId=%s  level=%s  nom=%s',
        tostring(info.templateId), tostring(info.level), tostring(info.name)))
    end
  elseif R.vu then
    print('  (liste vide)')
  end
  if R.erreur then print('  erreur : ' .. R.erreur) end
  print(string.rep('=', 62))
  return
end

R = {n = 0, vu = false}
sp.store.succes = R

local RpcIndex = require('Core.Common.RpcIndex')
local vGH = getmetatable(require('Core.Client.GateClientRpcHandler')).__index

-- Empiler les enveloppes : au 9e rechargement il y avait NEUF couches sur
-- entityMessageV2. Chaque couche paie select('#', ...), copie six arguments et
-- formate une chaine. On remet donc l'original AVANT de re-envelopper.
sp.store.hooks = sp.store.hooks or {}
for i = #sp.store.hooks, 1, -1 do
  local h = sp.store.hooks[i]
  pcall(function() h.vtbl[h.cle] = h.orig end)
end
sp.store.hooks = {}

local orig = rawget(vGH, 'entityMessageV2')
sp.store.hooks[#sp.store.hooks + 1] = {vtbl = vGH, cle = 'entityMessageV2', orig = orig}

vGH.entityMessageV2 = function(self, entityId, raw, index, context, ...)
  local nom = RpcIndex.INDEX2RPC[index] or RpcIndex.RPC_INDEX2NAME[index]
  if nom == 'RPC_SC_OnCaptureSuccess' then
    R.n = R.n + 1
    R.vu = true
    local infos = (select(1, ...))
    R.typeInfos = type(infos)
    R.nbInfos = (type(infos) == 'table') and #infos or -1
    R.dernier = {}
    if type(infos) == 'table' then
      -- champs declares : le handler du jeu les lit lui-meme
      for _, info in ipairs(infos) do
        if type(info) == 'table' then
          R.dernier[#R.dernier + 1] = {
            templateId = info.templateId,
            level = info.level or info.petLevel,
            name = info.name,
          }
        end
      end
    end
    R.session = (select(2, ...))
  end
  return orig(self, entityId, raw, index, context, ...)
end

print('capture_succes : arme — capture automatique a lancer, puis relis ce script')
