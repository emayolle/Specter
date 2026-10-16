-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Mob Vacuum — pousse les mobs vers la cible (global `target`, défini par 99_incomplete_teleport_target)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180005340
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


local count=0
for _,e in pairs(pg.global.entityMgr.getAllEntities()) do
    if e and e~=me and not e.isDestroyed then
        local ok,isMob=pcall(function()
            return U.isWildPuppet(e)
                and U.isEnemy(me,e)
                and not U.isNpc(e)
                and not (e.isDead and e:isDead())
        end)
        if ok and isMob then
            pcall(function()
                e:forceSetPos(target,true)
                count=count+1
            end)
        end
    end
end
print("[MOB VACUUM] MOBS PULLED:", count)