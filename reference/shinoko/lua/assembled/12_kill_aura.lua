-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Kill Aura — tue les ennemis dans le rayon, toutes les INTERVAL secondes
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18000D580, 18000D9F0, 18000DE60, 18000E2D0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    _G.pg = pg
    local Const = require("Common.Const.Const")
    local Utils = require("Common.Utils.Utils")
    local TimerManager = require("Core.Timer.TimerManager")

    local ENABLED = 1  -- INSERTION runtime: état Kill Aura (1=ON, 0=OFF)

    local RADIUS = 15  -- INSERTION runtime: rayon de l'aura (slider menu)

    local INTERVAL = 1.0  -- INSERTION runtime: intervalle en secondes (slider menu)


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
