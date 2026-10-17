-- erreurs-coffres.lua — pourquoi la boucle de coffres ne fait-elle rien ?
--
-- Usage : tools/lua.sh -f scripts/erreurs-coffres.lua
--
-- Répond à la seule question qui compte quand la case est cochée et que rien
-- ne s'ouvre : EST-CE QUE LA BOUCLE TOURNE, et sinon où est-ce qu'elle casse ?
--
-- Le contrôle `regles` est celui qui compte. `E.regles` est le décompte des
-- verdicts du filtre, et il est incrémenté à CHAQUE entité examinée. S'il
-- reste `{ template = 0, marque = 0, aucune = 0 }` alors que la case est
-- cochée, la boucle n'est pas arrivée jusqu'à la collecte — et la ligne
-- `erreursPilote` dit pourquoi.

local E = specter.store.chests
if type(E) ~= 'table' then
  print('ERREUR: specter.store.chests absent.')
  print('       Le bootstrap n a pas joue pour cet etat Lua.')
  print('       Relance : tools/specter-tap.sh puis specter-inject.sh')
  return
end

print('=== la case ===')
print(string.format('  specter.var.coffres = %s', tostring(specter.var.coffres)))

print('=== etat de la boucle ===')
print(string.format('  running   = %s', tostring(E.running)))
print(string.format('  phase     = %s   (0 inactif, 1 cherche, 2 ouvre, 3 attend, 4 auto-farm)',
      tostring(E.phase)))
print(string.format('  enAttente = %s', tostring(E.enAttente)))

print('=== compteurs ===')
print(string.format('  ouverts   = %s', tostring(E.ouverts)))
print(string.format('  tpEchecs  = %s', tostring(E.tpEchecs)))
print(string.format('  sansEffet = %s', tostring(E.sansEffetTotal)))
print(string.format('  GAGNES    = %s  (coffres qui ont coute des PV)', tostring(E.gagnes)))
local nd = 0
for _ in pairs(E.dangereux or {}) do nd = nd + 1 end
print(string.format('  ecartees (dangereux) = %d pour cette scene', nd))
local me = pg.me
if me then
  print(string.format('  PV maintenant : %s/%s   lastHurtTime=%s   dead=%s',
        tostring(me.curHp), tostring(me.maxHp), tostring(me.lastHurtTime),
        tostring(me._topLogoDeadState)))
if (tonumber(me.curHp) or 1) <= 0 then
  print('  >> JOUEUR MORT : la boucle doit etre a l arret (phase 5).')
  print('     Un mort ne se deplace pas -- chaque TP echoue legitement.')
end
end

print('=== le filtre ===')
if type(E.regles) == 'table' then
  print(string.format('  verdicts  : regle A (template)      = %s   <- la seule qui accepte', tostring(E.regles.template)))
  print(string.format('               regle B (marque) seule = %s   <- diagnostique, n accepte rien', tostring(E.regles.marqueSeule)))
  print(string.format('               aucune regle          = %s', tostring(E.regles.aucune)))
  if (E.regles.template or 0) + (E.regles.aucune or 0) == 0 then
    print('  >> AUCUN verdict : la boucle n arrive pas a la collecte.')
  end
else
  print('  E.regles ABSENT -- le script charge est une version plus ancienne,')
  print('  ou la boucle n a jamais demarre.')
end
print(string.format('  cibles    = %s   ecartees = %s', tostring(E.cibles), tostring(E.ecartees)))
print(string.format('  chestData resolu = %s', tostring(E.chestData)))

print('=== erreurs ===')
print(string.format('  erreursPilote = %s', tostring(E.erreursPilote)))
if E.derniereErreurPilote then
  print(string.format('  derniere      = %s', tostring(E.derniereErreurPilote)))
end
print(string.format('  verrous        = %s', tostring(E.dernierEchec and E.dernierEchec.raison or 'aucun')))
if E.dernierEchec then
  print(string.format('  dernier echec : id=%s d=%.1f meilleur=%.1f (%s)',
        tostring(E.dernierEchec.id), E.dernierEchec.d or -1,
        E.dernierEchec.meilleur or -1, tostring(E.dernierEchec.raison)))
end

print('=== forme ===')
print(string.format('  forme = %s   (classe visee : %s)', tostring(E.forme), tostring(E.formeClasse)))
if E.forme == 'pet' then
  print('  >> TRANSFORME : le TP vise le pet de combat, pas le joueur.')
  print('     Mesure : en pet, pg.me est une coquille passive (active=false,')
  print('     isTransparent=true) et sa position est recalculee. Le joueur suit')
  print('     le pet en X/Z ; le Y reste au sol, donc pas de passage au travers.')
end

print('=== ce que voit la case ===')
print(string.format('  coffres_ouverts = %s   phase = %s   tpEchecs = %s   erreurs = %s',
      tostring(specter.var.coffres_ouverts), tostring(specter.var.coffres_phase),
      tostring(specter.var.coffres_tp_echecs), tostring(specter.var.coffres_erreurs)))

print('=== trace (20 dernieres) ===')
local tr = E.trace or {}
if #tr == 0 then
  print('  (vide)')
else
  for i = math.max(1, #tr - 19), #tr do
    print('  ' .. tostring(tr[i]))
  end
end