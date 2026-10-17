-- probe-pv-suite.lua — est-ce que `lastHurtTime` bouge quand on encaisse ?
--
-- Usage : tools/lua.sh -f scripts/probe-pv-suite.lua   (deux fois, ~10 s d'ecart)
--
-- La question n'est pas « quels champs existent » (repondu par probe-pv.lua),
-- c'est : lequel se lit SANS se tromper.
--
-- Un diff de `curHp` a un defaut qu'on ne voit qu'en jeu : la REGENERATION. Si
-- le joueur reprend des PV tout seul, `curHp` monte pendant un cycle, et une
-- perte de 1 suivie d'une regen de 1 passe inapercue.
--
-- `lastHurtTime` est un INSTANT, pas un total : il ne bouge que sur un coup.
-- S'il avance pendant un intervalle sans coup, soit il mesure autre chose, soit
-- on encaisse vraiment. Le test se fait en deux releves espaces, sans rien
-- provoquer : c'est la seule maniere de distinguer « avance sur coup » de
-- « avance tout le temps », qui rendrait le champ inutile.

local e = pg.me
if not e then print('ERREUR: pas de joueur'); return end

local S = specter.store.pv
if type(S) ~= 'table' then S = {}; specter.store.pv = S end

local function lire()
  return {
    curHp = e.curHp, maxHp = e.maxHp, life = e.life,
    lastHurtTime = e.lastHurtTime,
    dead = e._topLogoDeadState,
  }
end

local a = lire()
print('=== PRELEVEMENT ' .. tostring(S.n or 1) .. ' ===')
print(string.format('  curHp=%s/%s  life=%s  lastHurtTime=%s  dead=%s',
      tostring(a.curHp), tostring(a.maxHp), tostring(a.life),
      tostring(a.lastHurtTime), tostring(a.dead)))

if S.avant then
  local d = (tonumber(a.lastHurtTime) or 0) - (tonumber(S.avant.lastHurtTime) or 0)
  local dh = (tonumber(a.curHp) or 0) - (tonumber(S.avant.curHp) or 0)
  print('=== COMPARAISON ===')
  print(string.format('  ecart de temps : %.3f s', tonumber(a.lastHurtTime) and d or -1))
  print(string.format('  curHp          : %s -> %s  (%+d)',
        tostring(S.avant.curHp), tostring(a.curHp), dh))
  if d > 0.001 then
    print('  >> lastHurtTime A AVANCE : le champ se lit, on peut s y fier.')
  elseif math.abs(dh) > 0 then
    print('  >> curHp a bouge SANS que lastHurtTime bouge.')
    print('     Donc soit il y a eu un coup trop rapide pour etre horodate,')
    print('     soit la regeneration est ce qui bouge. A trancher en jeu.')
  else
    print('  >> rien n a bouge : intervalle sans coup (attendu).')
  end
end

S.avant = a
S.n = (S.n or 0) + 1
print('relance dans ~10 s.')