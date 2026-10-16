-- probe-rpc-hook.lua -- ou sont vraiment les methodes qu'on peut envelopper.
--
-- class.Class() renvoie un objet `classType` dont le metatable porte
-- __index = vtbl (Class.lua:399). Les methodes d'instance vivent dans vtbl,
-- PAS dans classType lui-meme -- et classType a un __newindex qui leve une
-- erreur sur un attribut repete. Il faut donc ecrire DANS vtbl.

local noms = {
  {nom = 'ClientEntity',        mod = 'Core.Client.ClientEntity'},
  {nom = 'ClientAoiComponent',  mod = 'Entities.SpaceEntities.CommonComponent.ClientAoiComponent'},
  {nom = 'GateClientRpcHandler', mod = 'Core.Client.GateClientRpcHandler'},
  {nom = 'RpcIndex',            mod = 'Core.Common.RpcIndex'},
}

for _, e in ipairs(noms) do
  local ok, C = pcall(require, e.mod)
  if not ok then
    print(string.format('%-20s require ECHEC : %s', e.nom, tostring(C):sub(1, 70)))
  else
    local mt = getmetatable(C)
    local vtbl = mt and mt.__index
    print(string.format('%-20s type=%s  metatable=%s  __index=%s',
          e.nom, type(C), type(mt), type(vtbl)))
    if type(vtbl) == 'table' then
      for _, m in ipairs({'serverMsg', 'entityMessageV2', 'entityMessage',
                          'sendRpcIndex', 'INDEX2RPC', 'RPC_INDEX2NAME'}) do
        if rawget(vtbl, m) ~= nil then
          print(string.format('      vtbl.%s = %s', m, type(rawget(vtbl, m))))
        end
      end
    end
    if type(C) == 'table' then
      for _, m in ipairs({'serverMsg', 'entityMessageV2', 'entityMessage',
                          'INDEX2RPC', 'RPC_INDEX2NAME'}) do
        if rawget(C, m) ~= nil then
          print(string.format('      C[%s] = %s (champ direct)', m, type(rawget(C, m))))
        end
      end
    end
  end
end

print('')
print('--- l instance du handler est-elle joignable ? ---')
local ok2, R = pcall(require, 'Core.Client.ClientRepo')
if ok2 and type(R) == 'table' then
  local n = 0
  for k, v in pairs(R) do n = n + 1 end
  print('ClientRepo : ' .. n .. ' champs')
  for k, v in pairs(R) do
    local t = type(v)
    if t == 'table' or t == 'userdata' then
      print(string.format('   %-22s %s', tostring(k), t))
    end
  end
else
  print('ClientRepo : indisponible (' .. tostring(R):sub(1, 60) .. ')')
end

print('')
print('--- pg.me : sa classe et sa vtbl ---')
if pg and pg.me then
  print('pg.me existe, className = ' .. tostring(pg.me.className))
  local mtme = getmetatable(pg.me)
  print('metatable(pg.me).__index = ' .. type(mtme and mtme.__index))
end