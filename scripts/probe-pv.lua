-- probe-pv.lua — ou sont les PV du joueur, et comment les lire sans se tromper ?
--
-- Usage : tools/lua.sh -f scripts/probe-pv.lua
--
-- Trois questions, dans l'ordre d'importance :
--   1. QUEL CHAMP porte les PV ? `isChest` a appris qu'un nom de champ peut
--      mentir (il vaut true sur des ramassages) ; on ne choisit pas un champ au
--      hasard en se fiant a son nom.
--   2. Est-ce que le champ a l'air d'etre ENCORE des PV ? Un nombre entre 0 et
--      100000 n'est pas un nombre de PV.
--   3. Y a-t-il un MAXIMUM ? Sans lui, on ne peut rien dire d'utile dans le
--      menu, et surtout on confondrait « PV bas » et « PV perdus ».
--
-- Le test qui tranche : FAIRE BOUGER LE JOUEUR. On note les valeurs, on attend,
-- et on relit. Un champ de PV ne bouge pas quand on court ; un champ de
-- position, si. Et si un PV change tout seul pendant qu'on ne prend aucun
-- coup, alors le jeu les regenere -- ce qui veut dire qu'un delai seul ne
-- distingue pas une perte de PV d'une regen.

local e = pg.me
if not e then print('ERREUR: pas de joueur'); return end

local mt = getmetatable(e)
local idx = mt and mt.__index

-- On regarde les champs dont le nom PARLE de vie, de sang, ou de soin. On les
-- liste tous, on ne trie rien : le tri est une opinion, et c'est la mesure qui
-- tranche.
local suspects = {}
local function ajoute(ou, k, v)
  local nom = string.lower(tostring(k))
  if nom:find('hp') or nom:find('health') or nom:find('life')
     or nom:find('blood') or nom:find('hurt') or nom:find('wound')
     or nom:find('heal') or nom:find('regen') or nom:find('dead')
     or nom:find('die') or nom:find('alive') then
    suspects[#suspects + 1] = { ou = ou, k = k, v = v }
  end
end
for k, v in pairs(e) do ajoute('entite', k, v) end
if idx then for k, v in pairs(idx) do ajoute('index', k, v) end end

table.sort(suspects, function(a, b) return tostring(a.k) < tostring(b.k) end)

print(string.format('=== %d champ(s) dont le nom parle de vie ===', #suspects))
print(string.format('%-8s %-28s %-9s %s', 'ou', 'cle', 'type', 'valeur'))
for _, s in ipairs(suspects) do
  local val = s.v
  if type(val) == 'table' or type(val) == 'userdata' then
    print(string.format('%-8s %-28s %-9s %s', s.ou, tostring(s.k), type(val), '<' .. type(val) .. '>'))
  else
    print(string.format('%-8s %-28s %-9s %s', s.ou, tostring(s.k), type(val), tostring(val)))
  end
end

-- Les FONCTIONS de soin / de degat : elles revelent le modele (un serveur
-- envoie des deltas ? le client applique un total ?).
print('=== fonctions de vie ===')
local n = 0
for k, v in pairs(idx or {}) do
  if type(v) == 'function' then
    local nom = string.lower(tostring(k))
    if nom:find('hp') or nom:find('heal') or nom:find('hurt')
       or nom:find('damage') or nom:find('dead') or nom:find('revive') then
      n = n + 1
      print('  ' .. tostring(k))
    end
  end
end
if n == 0 then print('  (aucune)') end

-- ETAT INITIAL, pour comparer plus tard.
local S = specter.store.pv
if type(S) ~= 'table' then S = {}; specter.store.pv = S end
S.avant = {}
for _, s in ipairs(suspects) do
  local val = s.v
  if type(val) == 'number' then S.avant[tostring(s.k)] = val end
end
local p = e:getPosition()
S.pos = { p[1], p[2], p[3] }
local nbre = 0
for _ in pairs(S.avant) do nbre = nbre + 1 end
print(string.format('=== %d valeur(s) numerique(s) memorisee(s) ===', nbre))
print('relance dans quelques secondes pour comparer.')