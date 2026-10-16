

    local state = rawget(_G, "__DX12_MULTI_HIT")
    if state == nil then
        state = {
            enabled = ENABLED,
            hitTimes = HIT_TIMES,
            patched = setmetatable({}, { __mode = "k" }),
            hitRpcs = {
                RPC_CS_DoActOnSweepTargetsActions = true,
                RPC_CS_DoActOnActorActions = true,
                RPC_CS_OnCSProjectileHit = true,
                RPC_CS_ProjectileHitTarget = true,
                RPC_CS_ChainPropagation = true,
                RPC_CS_ReboundDashHitActor = true,
                RPC_CS_OnAbilityCollisionHitTarget = true,
                RPC_CS_OnTriggerAbilityCollisionHit = true,
            }
        }
        rawset(_G, "__DX12_MULTI_HIT", state)
    else
        state.hitTimes = HIT_TIMES
        state.enabled = ENABLED
    end

    local function isLocalAttacker(ent)
        local me = pg and pg.me
        if ent == nil or me == nil then return false end
        return ent == me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
    end

    local function ensurePatched(ent)
        if ent == nil or state.patched[ent] or not isLocalAttacker(ent) then return end
        local send = ent.serverMsgNoGC
        if type(send) ~= "function" then return end

        state.patched[ent] = true
        ent.serverMsgNoGC = function(self, name, ...)
            if not state.enabled or not state.hitRpcs[name] then
                return send(self, name, ...)
            end
            local result
            for _ = 1, state.hitTimes do
                result = send(self, name, ...)
            end
            return result
        end

        local checkHitTargetSet = ent.checkHitTargetSet
        if type(checkHitTargetSet) == "function" then
            ent.checkHitTargetSet = function(self, actorId, abilityId, actionData)
                if state.enabled then return true end
                return checkHitTargetSet(self, actorId, abilityId, actionData)
            end
        end

        local checkHitTargetCd = ent.checkHitTargetCd
        if type(checkHitTargetCd) == "function" then
            ent.checkHitTargetCd = function(self, actorId, abilityId, actionData, overrideTime)
                if state.enabled then return true end
                return checkHitTargetCd(self, actorId, abilityId, actionData, overrideTime)
            end
        end
    end

    state.ensurePatched = ensurePatched

    if not rawget(_G, "__DX12_HOOKS_INSTALLED") then
        local doAction = ClientCombatAction.doAction
        ClientCombatAction.doAction = function(self, actionData, combatContext)
            if combatContext ~= nil then
                state.ensurePatched(CombatActionTool.getOwnerEntity(combatContext))
            end
            return doAction(self, actionData, combatContext)
        end

        local projectileHitRPC = ClientProjectile.onProjectileHitRPC
        ClientProjectile.onProjectileHitRPC = function(self, srcEntity, combatHitResult, nextReboundActorId)
            state.ensurePatched(srcEntity)
            return projectileHitRPC(self, srcEntity, combatHitResult, nextReboundActorId)
        end

        rawset(_G, "__DX12_HOOKS_INSTALLED", true)
    end

    if pg and pg.me then state.ensurePatched(pg.me) end
    if pg and pg.pawn then state.ensurePatched(pg.pawn) end

    print("[MULTI HIT]", state.enabled and ("ON x" .. tostring(state.hitTimes)) or "OFF")
end
