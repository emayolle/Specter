-- =====================================================================
-- test-workers.lua — escalade progressive des workers, un palier a la fois.
--
--   tools/lua.sh -f scripts/test-workers.lua
--
-- Le palier monte tout seul a chaque execution : le bac a sable n'a pas de
-- parametres (son chunk n'est pas une fonction vararg, donc `...` y est
-- illegal), alors le compte est tenu dans notre store. Une execution = un
-- palier de plus. Apres un crash, le store repart a zero avec la session, ce
-- qui est le comportement voulu.
--
-- Le dernier crash est mort SANS RAISON ECRITE : le log s'arretait sur
-- « worker N demarre » et rien ne disait pourquoi. Ca ne doit plus
-- arriver -- chaque worker est sous un pcall, donc son erreur est lisible
-- dans specter.thread.error(h).
--
-- L'echelle est montee d'un coup la derniere fois (6 workers d'un coup) et
-- le jeu est mort. Donc on monte par paliers : si un palier casse, on a
-- le seuil, pas une supposition.
--
-- APRES CHAQUE PALIER, REGARDE LE LOG :
--
--   tail -f specter.log | grep '\[worker'
--
-- ...et en particulier :
--
--   [worker N] fermeture : N bloc(s) / N o encore vivant(s)
--
-- Ce nombre doit etre 0. S'il ne l'est pas, l'etat de ce worker a garde
-- des blocs apres lua_close, et on a une vraie fuite a regarder.
-- =====================================================================

local S = specter.store
S.palier = (S.palier or 0) + 1
local PALIER = S.palier
local CORPS  = [[
  local n = 0
  local t = {}
  while true do
    n = n + 1
    for i = 1, 40 do t[i % 40] = i * n end
    specter.sleep(10)               -- 10 ms : vivant, et killable
  end
]]

local function etat(h)
  return string.format('handle %d : %-9s alive %d%s', h,
                       specter.thread.status(h), specter.thread.alive(),
                       specter.thread.error(h) ~= ''
                         and ('  | ' .. specter.thread.error(h)) or '')
end

print(('=== palier %d ==='):format(PALIER))

-- --- un seul worker : la base ------------------------------------------
if PALIER >= 1 then
  local n = PALIER
  local hs = {}
  for i = 1, n do
    local ok, h = pcall(specter.thread.spawn, CORPS)
    if not ok then
      print(string.format('  spawn %d REFUSE : %s', i, tostring(h)))
    else
      hs[#hs + 1] = h
      print(string.format('  spawn %d -> %s', i, etat(h)))
    end
  end
  print(('  %d worker(s) en vie, max 6'):format(specter.thread.alive()))

  -- laisse-les tourner, pour que le log montre leur vie
  for _ = 1, 60 do
    specter.sleep(0)
  end
  print('  --- 60 ticks plus tard ---')
  for _, h in ipairs(hs) do print('  ' .. etat(h)) end

  -- arret cooperative
  print('  --- arret ---')
  for _, h in ipairs(hs) do
    print(string.format('  kill %d -> %s', h, tostring(specter.thread.kill(h))))
  end
  for _, h in ipairs(hs) do
    print(string.format('  join %d -> %s', h, tostring(specter.thread.join(h, 5000))))
  end
  for _, h in ipairs(hs) do print('  final ' .. etat(h)) end
  print(('  alive apres arret : %d'):format(specter.thread.alive()))
end

print('=== fin du palier ===')