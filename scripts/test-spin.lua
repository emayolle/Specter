-- =====================================================================
-- test-spin.lua — le seul scenario de la session du crash qui n'a jamais
-- ete rejoue.
--
--   tools/lua.sh -f scripts/test-spin.lua
--   tools/lua.sh -f scripts/test-spin.lua      (2e temps)
--
-- LE SCENARIO. Ce jour-la, en meme temps que six workers normaux, tournait
-- un worker qui faisait des dizaines de millions d'iterations par seconde
-- SANS JAMAIS appeler specter.sleep(). Il etait le seul a ne pas passer par
-- le point de controle.
--
-- Ce qu'on sait deja, et qui ne suffit pas a conclure :
--
--   x 6 workers concurrents        paliers 1-2-3 : le jeu tient
--   x fuite de l'allocateur        0 bloc rendu sur tous
--   x pcall manquant               plus aucun PANIC
--   x kill non cooperatif          3 arrets propres, alive 0
--   v un worker a 100% CPU sans point de controle   <-- celui-ci
--
-- ATTENTION, DEUX CHOIX DELIBERES.
--
-- 1. LE SPINEUR EST BORNEE. Un worker sans specter.sleep() ne peut pas etre
--    arrete -- c'est la regle, ecrite dans worker.h. En laisser un libre
--    tourner jusqu'a la fermeture du jeu serait la reproduction exacte du
--    crash ET un fil a 100% CPU qu'on ne maitrise plus. Donc il travaille
--    5 secondes puis rend la main. Ce qu'on veut tester, c'est la
--    CONCURRENCE avec lui, pas sa duree.
--
-- 2. LA PARTIE JEU N'ATTEND PAS. Elle ne peut pas : la bloquer figerait le
--    jeu, ce qu'on essaie de mesurer. Donc deux temps -- relance la meme
--    commande.
--
-- CE QU'IL FAUT REGARDER, dans cet ordre :
--
--   a) [spineur N] demarre / ... / [spineur N] fini  (il a vraiment boucle)
--   b) [worker N] fin : <status> ... <N> bloc(s) / <N> o non rendu(s)
--      les deux derniers nombres doivent etre 0
--   c) les [worker] normaux continuent-ils a loguer pendant que le spineur
--      tourne ? Si oui, ils ne sont pas etouffes par lui.
-- =====================================================================

local S = specter.store

local function etat(h)
  local e = specter.thread.error(h)
  return string.format('handle %d : %-9s%s', h, specter.thread.status(h),
                       e ~= '' and ('  | ' .. e) or '')
end

-- --- 1. arret de tout ce qui tourne ---------------------------------------
local orphans = {}
for h = 0, 5 do
  local st = specter.thread.status(h)
  if st == 'running' or st == 'kill asked' or st == 'starting' then
    orphans[#orphans + 1] = h
  end
end
if #orphans > 0 then
  print('=== arret de ' .. #orphans .. ' worker(s) en cours ===')
  for _, h in ipairs(orphans) do specter.thread.kill(h) end
  for _, h in ipairs(orphans) do
    print(string.format('  join  %d -> %s', h, tostring(specter.thread.join(h, 8000))))
  end
  for _, h in ipairs(orphans) do print('  final ' .. etat(h)) end
  print('  alive apres arret : ' .. tostring(specter.thread.alive()))
  print("  -> log : grep '\\[worker\\|\\[spineur' specter.log")
end

-- --- 2. le test ------------------------------------------------------------
print('=== spineur + 3 workers normaux ===')

-- BORNIE : 5 secondes de pur CPU, puis elle rend la main toute seule.
local SPINEUR = [[
  specter.log('spineur', specter.thread.id(), 'demarre -- 100% CPU, sans sleep()')
  local x, tab, t = 0, {}, 0
  for _ = 1, 200 do
    for i = 1, 200000 do tab[i % 4096] = i; x = x + i end
    t = t + 1
  end
  specter.log('spineur', specter.thread.id(), 'fini apres', t, 'blocs de calcul, x =', x)
  return x
]]

local NORMAL = [[
  local n = 0
  local t = {}
  specter.log('worker', specter.thread.id(), 'pret')
  while true do
    n = n + 1
    for i = 1, 40 do t[i % 40] = i * n end
    if n % 1000 == 0 then specter.log('worker', specter.thread.id(), 'vif, n =', n) end
    specter.sleep(10)
  end
]]

local spin = specter.thread.spawn(SPINEUR)
print('  spineur   -> ' .. etat(spin))

local ns = {}
for i = 1, 3 do
  ns[#ns + 1] = specter.thread.spawn(NORMAL)
  print(string.format('  normal %d  -> %s', i, etat(ns[i])))
end

print('  alive : ' .. tostring(specter.thread.alive()))
print('=== attends ~15 s puis relance la meme commande ===')
print("  tu dois voir dans le log : '[spineur N] demarre', puis '[spineur N] fini',")
print("  et les 'worker N vif' continuer PENDANT que le spineur tourne.")