

    local state = rawget(_G, "__KILL_AURA")
    if not state then
        state = {
            enabled = ENABLED,
            radius = RADIUS,
            interval = INTERVAL,
            timerId = nil,
            lastInterval = INTERVAL
        }
        rawset(_G, "__KILL_AURA", state)
    else
        state.enabled = ENABLED
        state.radius = RADIUS
        state.interval = INTERVAL
    end

    local function isEnemy(ent)
        if ent == nil or pg == nil or pg.me == nil or ent == pg.me then
            return false
        end
        local ok, result = pcall(Utils.checkRelation, pg.me, ent, Const.WORLD_PAIRS_CAMP_ENEMY)
        return ok and result == true
    end

    local function getHp(ent)
        if ent == nil then return nil end
        if ent.actorCombatAttribute ~= nil and ent.actorCombatAttribute.getHp ~= nil then
            local ok, hp = pcall(ent.actorCombatAttribute.getHp, ent.actorCombatAttribute)
            if ok and hp ~= nil then return hp end
        end
        if ent.getHp ~= nil then
            local ok, hp = pcall(ent.getHp, ent)
            if ok and hp ~= nil then return hp end
        end
        return nil
    end

    local function killAuraTick()
        if not state.enabled then return end
        if pg == nil or pg.me == nil then return end

        local actorIds = pg.me:entitiesInRange(state.radius, Const.SEARCH_USR_TYPE_MONSTER)
        if actorIds == nil then return end

        for _, actorId in ipairs(actorIds) do
            local target = pg.getEntityByActorId(actorId)
            if target ~= nil and isEnemy(target) and target.authority == Const.AUTHORITY_MASTER then
                local hp = getHp(target)
                if hp ~= nil and hp > 0 then
                    local damage = math.ceil(hp)
                    local ok, err = pcall(target.serverMsg, target, "RPC_CS_SpecialDamage", damage, Const.LIFE_DEAD_BY_COMBAT)
                    if ok then
                        print("[KILL AURA]", tostring(target.id), "HP=", tostring(hp), "DMG=", tostring(damage))
                    else
                        print("[KILL AURA ERROR]", tostring(err))
                    end
                end
            end
        end
    end

    state.tickFunc = killAuraTick

    local function removeTimer(id)
        if id == nil then return end
        if TimerManager.removeTimer then
            pcall(TimerManager.removeTimer, id)
        elseif TimerManager.delTimer then
            pcall(TimerManager.delTimer, id)
        end
    end

    if state.enabled then
        if state.timerId ~= nil and state.lastInterval ~= state.interval then
            removeTimer(state.timerId)
            state.timerId = nil
        end
        if state.timerId == nil then
            state.timerId = TimerManager.addRepeatTimer(state.interval, state.tickFunc)
            state.lastInterval = state.interval
            print("[NETWORK KILL AURA] ON | radius=", state.radius, "| timerId=", tostring(state.timerId))
        else
            print("[NETWORK KILL AURA] ON | radius=", state.radius)
        end
    else
        if state.timerId ~= nil then
            removeTimer(state.timerId)
            state.timerId = nil
        end
        print("[NETWORK KILL AURA] OFF")
    end
end
