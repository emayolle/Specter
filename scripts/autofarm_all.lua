-- autofarm_all.lua — DEMARRE l'auto-farm, ou l'arrete.
--
-- Ce fichier ne contient plus la boucle. Il y en a UNE, et elle vit dans
-- scripts/autofarm_loop.lua, embarquee dans la DLL et rejouee a chaque nouvel
-- etat Lua. Dupliquer la logique ici aurait donne deux implementations qui
-- divergent -- et c'est exactement ce qui s'est produit toute la journee : un
-- fichier corrige, l'autre non.
--
-- Usage :
--   tools/lua.sh -f scripts/autofarm_all.lua          demarre
--   tools/lua.sh -e 'specter.var.autofarm = false'     arrete
--
-- Ou, mieux : la case a cocher de l'onglet Auto-farm, qui lit et ecrit le
-- meme octet que ce chunk.
--
-- CE QUE LA BOUCLE FAIT, ET CE QU'ELLE NE FAIT PAS
--
-- Elle ramasse tout ce qui porte une unite d'interaction, SAUF :
--   - les coffres (marque 10506 confirmee sur LA marque de l'entite, a moins
--     de 3 u) ;
--   - les objets a contact (template 11042, "Ambre lumin"), dont l'unite vit
--     0.3 s avant que le contact ne les consomme.
--
-- Elle ne casse rien : ClientBreakableEntity n'a pas isChest et renvoie nil de
-- getInteractionListData(). Les pots ne sont jamais dans la liste.
--
-- Elle ne s'arrete jamais : quand il n'y a plus rien a faire, elle attend et
-- reessaie. Une cible n'est comptee qu'APRES la disparition de son entite.

if type(specter.var) ~= 'table' or specter.var.autofarm == nil then
  print('ERROR: specter.var.autofarm absent.')
  print('       La boucle est dans scripts/autofarm_loop.lua, joue a chaque')
  print('       nouvel etat Lua. Si elle manque, le bootstrap ne s\'est pas')
  print('       execute : regarde le log pour un [init] en echec.')
  return
end

local E = specter.store.autofarm
local etait = specter.var.autofarm

specter.var.autofarm = true

print(string.format('[autofarm] demande : %s -> true', tostring(etait)))
if E then
  print(string.format('  cibles connues : %s   ecartees : %s   ouverts : %s',
        tostring(E.cibles), tostring(E.ecartees), tostring(E.ouverts or 0)))
end
print('  arreter : specter.var.autofarm = false, ou decocher la case')