-- =====================================================================
-- test-workers.lua — escalade progressive des workers, un palier a la fois.
--
--   tools/lua.sh -f scripts/test-workers.lua     (repete la commande)
--
-- Le palier monte tout seul a chaque execution : le bac a sable n'a pas de
-- parametres (son chunk n'est pas une fonction vararg, donc `...` y est
-- illegal), alors le compte est tenu dans notre store. Apres un crash, le
-- store repart a zero avec la session -- comportement voulu.
--
-- A CHAQUE EXECUTION :
--   1. on arrete le palier PRECEDENT et on imprime son etat final
--   2. on lance le palier suivant
-- La partie jeu ne peut PAS attendre -- la bloquer figerait le jeu, ce qui
-- est justement ce qu'on essaie de mesurer. D'ou les deux temps.
--
-- LES WORKERS SE LOGUENT TOUT SEULS, c'est le but :
--
--   tail -f specter.log | grep '\[worker'
--
-- ...et en particulier, apres l'arret :
--
--   [worker N] fermeture : N bloc(s) / N o encore vivant(s)
--
-- Ce nombre doit etre 0. S'il ne l'est pas, l'etat de ce worker a garde
-- des blocs apres lua_close, et on a une vraie fuite a regarder.
--
-- !!! ATTENTION, API COTE JEU
--
-- specter.log, specter.sleep et specter.thread.id n'existent QUE dans le
-- monde du worker. Cote bac a sable, il n'y a que specter.store,
-- specter.var.*, specter.thread.* et les globales du jeu. Appeler
-- specter.sleep depuis ce fichier donne :
--
--     attempt to call field 'sleep' (a nil value)
-- =====================================================================

local S = specter.store

local function etat(h)
  local e = specter.thread.error(h)
  return string.format('handle %d : %-9s%s', h, specter.thread.status(h),
                       e ~= '' and ('  | ' .. e) or '')
end

-- --- 1. arreter TOUT ce qui tourne ----------------------------------------
-- Pas seulement le palier precedent : un worker lance par une version du
-- script qui a plante AVANT d'enregistrer son handle traine jusqu'a la
-- fermeture du jeu et fausse le compte. Au palier 2 on voyait "3 worker(s) en
-- vie" pour 2 workers lances. On balaie donc les six emplacements.
local orphans = {}
for h = 0, 5 do
  local st = specter.thread.status(h)
  if st == 'running' or st == 'kill asked' or st == 'starting' then
    orphans[#orphans + 1] = h
  end
end

if #orphans > 0 then
  print('=== arret de ' .. #orphans .. ' worker(s) en cours ===')
  for _, h in ipairs(orphans) do
    print(string.format('  kill  %d -> %s', h, tostring(specter.thread.kill(h))))
  end
  for _, h in ipairs(orphans) do
    print(string.format('  join  %d -> %s', h, tostring(specter.thread.join(h, 8000))))
  end
  for _, h in ipairs(orphans) do
    print('  final ' .. etat(h))
  end
  print('  alive apres arret : ' .. tostring(specter.thread.alive()))
  print("  -> va voir le log : grep '\\[worker' specter.log")
end
S.workers = nil

-- --- 2. lancer le palier suivant -------------------------------------------
S.palier = (S.palier or 0) + 1
local PALIER = S.palier
print('=== palier ' .. PALIER .. ' ===')

-- Boucle forever qui travaille et se logue : c'est elle qui met les workers
-- en concurrence reelle. sleep(10) les garde killables ET les laisse respirer.
local CORPS = [[
  local n = 0
  local t = {}
  specter.log('worker', specter.thread.id(), 'pret')
  while true do
    n = n + 1
    for i = 1, 40 do t[i % 40] = i * n end
    if n % 2000 == 0 then specter.log('worker', specter.thread.id(), 'vif, n =', n) end
    specter.sleep(10)
  end
]]

S.workers = {}
for i = 1, PALIER do
  local ok, h = pcall(specter.thread.spawn, CORPS)
  if not ok then
    print(string.format('  spawn %d REFUSE : %s', i, tostring(h)))
  else
    S.workers[#S.workers + 1] = h
    print(string.format('  spawn %d -> %s', i, etat(h)))
  end
end
print(string.format('  %d worker(s) en vie, max 6', specter.thread.alive()))
print('=== laisse tourner, puis relance la meme commande ===')