
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