-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Auto Loot — ramasse le butin dans le rayon, toutes les INTERVAL secondes
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180011E10, 180012280, 1800126F0, 180012B60
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
    local Time = require("Core.Common.Time")

    local ENABLED = 1  -- INSERTION runtime: état Auto Loot (1=ON, 0=OFF)

    local RADIUS = 15  -- INSERTION runtime: rayon de ramassage (slider menu)

    local INTERVAL = 1.0  -- INSERTION runtime: intervalle en secondes (slider menu)

    local RETRY_DELAY = 1.0

    local state = rawget(_G, "__AUTO_LOOT")
    if not state then
        state = {
            enabled = ENABLED,
            radius = RADIUS,
            interval = INTERVAL,
            timerId = nil,
            lastInterval = INTERVAL,
            lastRequest = {}
        }
        rawset(_G, "__AUTO_LOOT", state)
    else
        state.enabled = ENABLED
        state.radius = RADIUS
        state.interval = INTERVAL
    end

    local function canSend(id)
        local now = Time.realtimeSinceStartup
        local last = state.lastRequest[id]
        if last ~= nil and now - last < RETRY_DELAY then
            return false
        end
        state.lastRequest[id] = now
        return true
    end

    local function networkInteract(entity, interactType)
        if entity == nil or entity.id == nil or entity.actionPrototypeId == nil then
            return
        end
        if not canSend(entity.id) then
            return
        end
        local entityId = entity.id
        local interactId = entity.actionPrototypeId

        -- START
        pg.me:serverMsg("RPC_CS_StartInteract", interactType, entityId, interactId, {})

        -- ACTUAL INTERACT
        pg.me:serverMsg("RPC_CS_Interact", interactType, entityId, interactId, {}, function(ret, args)
            print("[AUTO LOOT]", tostring(entityId), "ret=", tostring(ret))
        end)
    end

    local function autoLootTick()
        if not state.enabled then return end
        if pg == nil or pg.me == nil then return end

        local actorIds = pg.me:entitiesInRange(state.radius, Const.SEARCH_USR_TYPE_INTERACTOR, 0)
        if actorIds == nil then return end

        for _, actorId in ipairs(actorIds) do
            local ent = pg.getEntityByActorId(actorId)
            if ent ~= nil then
                -- DROPPED ITEMS / COLLECT ITEMS
                if Utils.isCollectItem(ent)
                    and (ent.isCollectItemOpened == nil or not ent:isCollectItemOpened())
                    and Utils.isCollectItemVisible(pg.me, ent)
                then
                    networkInteract(ent, Const.IACT_IP_COLLECT_ITEM)

                -- CHESTS
                elseif Utils.isChest(ent) and Utils.isChestVisible(pg.me, ent) then
                    networkInteract(ent, Const.IACT_TP_CHEST)

                -- RESOURCE BOX
                elseif Utils.isResourceBox(ent) and ent.id ~= nil then
                    if canSend(ent.id) then
                        pg.me:serverMsg("RPC_CS_OpenResourceBoxWithQTE", ent.id, 100)
                        print("[AUTO RESOURCE BOX]", tostring(ent.id))
                    end
                end
            end
        end
    end

    state.tickFunc = autoLootTick

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
            print("[NETWORK AUTO LOOT] ON | radius=", state.radius, "| timerId=", tostring(state.timerId))
        else
            print("[NETWORK AUTO LOOT] ON | radius=", state.radius)
        end
    else
        if state.timerId ~= nil then
            removeTimer(state.timerId)
            state.timerId = nil
        end
        print("[NETWORK AUTO LOOT] OFF")
    end
end
