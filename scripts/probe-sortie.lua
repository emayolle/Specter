-- probe-sortie.lua -- ou passe REALLY l'envoi ?
--
-- On a pose deux enveloppes :
--   getmetatable(ClientEntity).__index.serverMsg
--   getmetatable(ClientAoiComponent).__index.serverMsg
-- et SORTIE reste a 0 malgre un cycle lancer/attrape complet. Donc la
-- resolution de `serverMsg` evite ces deux vtbl.
--
-- Suspect : le framework de classes copie certaines methodes SUR LES
-- INSTANCES (forceAttrRepeat, __worldxAoiMethods). Un champ present sur
-- l'instance masque le metatable.

local function vt(cls)
  local mt = getmetatable(cls)
  return mt and rawget(mt, '__index') or nil
end

local CE = require('Core.Client.ClientEntity')
local AC = require('Entities.SpaceEntities.CommonComponent.ClientAoiComponent')

print('=== 1. ou est le serverMsg REELLEMENT utilise ? ===')

local cibles = {}
if pg and pg.me then
  cibles[#cibles + 1] = {'pg.me', pg.me}
  if pg.me.aoi then
    cibles[#cibles + 1] = {'pg.me.aoi', pg.me.aoi}
  end
end

for _, c in ipairs(cibles) do
  local nom, o = c[1], c[2]
  print('')
  print(nom .. '  className=' .. tostring(o.className))

  -- champ sur l'instance ? il masque le metatable
  local surInst = rawget(o, 'serverMsg')
  print('   rawget(instance, "serverMsg") = ' .. type(surInst))

  -- valeur resolue
  local f = o.serverMsg
  print('   o.serverMsg                  = ' .. type(f))

  if type(f) == 'function' and debug and debug.getinfo then
    local i = debug.getinfo(f, 'S')
    print('   definie dans                 = ' .. tostring(i and i.short_src))
    print('   ligne                        = ' .. tostring(i and i.linedefined))
    -- est-ce NOTRE enveloppe ? elle a orig et note en upvalues
    local noms = {}
    for u = 1, 12 do
      local n = debug.getupvalue(f, u)
      if not n then break end
      noms[#noms + 1] = n
    end
    print('   upvalues                     = ' .. table.concat(noms, ','))
    local estNotre = false
    for _, n in ipairs(noms) do if n == 'note' or n == 'orig' then estNotre = true end end
    print('   >>> NOTRE enveloppe ?         = ' .. tostring(estNotre))
  end
end

print('')
print('=== 2. la chaine de classes : qui redEFINIT serverMsg ? ===')
local CEvt = vt(CE)
local ACvt = vt(AC)
print('ClientEntity        vtbl.serverMsg       = ' .. type(rawget(CEvt, 'serverMsg')))
print('ClientAoiComponent  vtbl.serverMsg       = ' .. type(rawget(ACvt, 'serverMsg')))

print('')
print('=== 3. les classes derivees quiDeclarent serverMsg ===')
local vus = {}
for nom, mod in pairs({
  ClientMainPlayer     = 'Entities.SpaceEntities.Player.ClientMainPlayer',
  ClientAoiComponent   = 'Entities.SpaceEntities.CommonComponent.ClientAoiComponent',
}) do
  local ok, C = pcall(require, mod)
  if ok and type(C) == 'table' then
    local t = vt(C)
    local f = t and rawget(t, 'serverMsg')
    vus[nom] = tostring(f)
    print(string.format('  %-22s declare serverMsg : %s', nom, tostring(f)))
  end
end

print('')
print('=== 4. le framework copie-t-il des methodes sur les instances ? ===')
local Class = require('Core.Framework.Class')
for _, k in ipairs({'__forceAttrRepeat', '__worldxAoiMethods', '__canOverrideDefaumtMethods'}) do
  local v = Class and rawget(Class, k)
  if type(v) == 'table' then
    local n = 0
    local exemples = {}
    for kk in pairs(v) do
      n = n + 1
      if #exemples < 8 then exemples[#exemples + 1] = tostring(kk) end
    end
    print(string.format('  Class.%s : %d entrees  [%s]', k, n, table.concat(exemples, ' ')))
  else
    print(string.format('  Class.%s : %s', k, type(v)))
  end
end

print('')
print('=== 5. WorldxAoi : la classe aoi reelle du joueur ===')
if pg and pg.me and pg.me.aoi then
  local a = pg.me.aoi
  print('  className = ' .. tostring(a.className))
  local mt = getmetatable(a)
  print('  metatable(a).__index = ' .. type(mt and mt.__index))
  print('  rawget(a, "serverMsg") = ' .. type(rawget(a, 'serverMsg')))
end