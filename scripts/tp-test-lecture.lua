-- tp-test-original.lua — LECTURE de la trace du test de TP.
--
-- Usage : tools/lua.sh -f scripts/tp-test-original.lua
--
-- Affiche t / pas du lerp / position attendue / position reelle / ecart.
-- L'ECART EST LA SEULE MESURE QUI COMPTE : la position reelle est lue par la
-- sonde, qui ne touche pas au lerp. Un ecart qui reste sous 1 u apres la fin du
-- parcours veut dire que le joueur a suivi.

local S = specter.store.tptest
if type(S) ~= 'table' or not S.trace or #S.trace == 0 then
  print('pas de trace : lance d\'abord le test')
  return
end

print(string.format('pas=%.2f u  distance visee=%.1f u  echantillons=%d fini=%s',
      S.pas or -1, S.dist or -1, S.n or 0, tostring(S.fini)))
print(string.format('%-7s %-8s %-11s %-11s %s', 't', 'i', 'attendu', 'reel', 'ecart'))
for _, l in ipairs(S.trace) do
  print(l)
end

-- Le resume : la derniere ligne suffit.
local dernier = S.trace[#S.trace]
local reel, ecart = tostring(dernier):match('reel=([%d%.%-]+) ecart=([%d%.%-]+)')
print('---')
if reel and ecart then
  local e = math.abs(tonumber(ecart))
  print(string.format('ecart final : %.2f u', e))
  print(e < 1.0 and 'RESULTAT : le joueur a suivi -- CE PAS MARCHE'
                    or 'RESULTAT : le joueur n a PAS suivi')
else
  print('trace illisible')
end