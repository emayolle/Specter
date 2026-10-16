

    local state = rawget(_G, "__CATCH_AURA")
    if not state then
        state = {
            enabled = ENABLED,
            radius = RADIUS,
            interval = INTERVAL,
            timerId = nil,
            lastInterval = INTERVAL
        }
        rawset(_G, "__CATCH_AURA", state)
    else
        state.enabled = ENABLED
        state.radius = RADIUS
        state.interval = INTERVAL
    end

    local function canCatchTarget(ent)
        if ent == nil or ent.destroyed then
            return false
        end
        if not Utils.isWildPuppet(ent) then
            return false
        end
        if ent.lastQuickCaptureTime ~= nil and Time.realSecondCache - ent.lastQuickCaptureTime < 5 then
            return false
        end
        local ok, ctx = pcall(CatchProbContext.clientGet, ent)
        return ok and ctx ~= nil and ctx.canCatch == true
    end

    local function findCatchTarget()
        if pg == nil or pg.me == nil then return nil end
        return Utils.getNearestPuppet(pg.me, state.radius, canCatchTarget)
    end

    local function catchAuraTick()
        if not state.enabled then return end
        if pg == nil or pg.me == nil or pg.game == nil or pg.game.controller == nil then
            return
        end
        if pg.me.isCaptureThrowing ~= nil and pg.me:isCaptureThrowing() then
            return
        end
        if pg.me.isInCatchMode ~= nil and pg.me:isInCatchMode() then
            return
        end
        local target = findCatchTarget()
        if target == nil then return end
        local ok, result = pcall(pg.game.controller.onHandleQuickCapture, pg.game.controller, target.id)
        if ok and result then
            print("[CATCH AURA]", "target=", tostring(target.id), "actor=", tostring(target.actorId))
        end
    end

    state.tickFunc = catchAuraTick

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
            print("[CATCH AURA] ON | radius=", state.radius, "| timerId=", tostring(state.timerId))
        else
            print("[CATCH AURA] ON | radius=", state.radius)
        end
    else
        if state.timerId ~= nil then
            removeTimer(state.timerId)
            state.timerId = nil
        end
        print("[CATCH AURA] OFF")
    end
end
