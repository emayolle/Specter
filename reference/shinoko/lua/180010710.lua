

    local state = rawget(_G, "__ONE_HIT")
    if not state then
        state = {
            enabled = ENABLED,
            origCalcResult = ClientCombatAction.calcResult
        }
        rawset(_G, "__ONE_HIT", state)

        local function isMyEntity(ent)
            if ent == nil or pg == nil or pg.me == nil then return false end
            return ent == pg.me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
        end

        local function isEnemy(caster, target)
            if caster == nil or target == nil or caster == target then return false end
            local ok, result = pcall(Utils.checkRelation, caster, target, Const.WORLD_PAIRS_CAMP_ENEMY)
            return ok and result == true
        end

        ClientCombatAction.calcResult = function(self, actionData, combatContext)
            if state.enabled and actionData ~= nil and combatContext ~= nil and actionData.attackData ~= nil then
                local target = nil
                local caster = nil

                if actionData.target ~= nil then
                    local ok, actorId = pcall(CombatActionTool.parseActorId, combatContext, actionData.target)
                    if ok and actorId ~= nil then
                        target = pg.getEntityByActorId(actorId)
                    end
                end

                local casterType = actionData.overrideCaster or AbilityConst.COMBAT_TARGET_TYPE_CASTER
                local okCaster, casterActorId = pcall(CombatActionTool.parseActorId, combatContext, casterType)
                if okCaster and casterActorId ~= nil then
                    caster = pg.getEntityByActorId(casterActorId)
                end

                if target ~= nil and caster ~= nil and isMyEntity(caster) and isEnemy(caster, target) then
                    if target.authority == Const.AUTHORITY_MASTER then
                        local ok, err = pcall(target.serverMsg, target, "RPC_CS_SpecialDamage", 1, Const.LIFE_DEAD_BY_COMBAT)
                        if ok then
                            print("[ONE HIT]", tostring(target.id), tostring(target.actorId))
                        else
                            print("[ONE HIT ERROR]", tostring(err))
                        end
                    else
                        print("[ONE HIT] target is not MASTER authority:", tostring(target.id))
                    end
                end
            end

            return state.origCalcResult(self, actionData, combatContext)
        end
    else
        state.enabled = ENABLED
    end

    print("[ONE HIT]", state.enabled and "ON" or "OFF")
end
