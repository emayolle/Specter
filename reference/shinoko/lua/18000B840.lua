
    local state = rawget(_G, "__INF_ENERGY")
    if not state then
        state = {
            enabled = ENABLED,
            originalGetEp = ActorCombatAttribute.getEp,
            originalGetSp = ActorCombatAttribute.getSp
        }
        rawset(_G, "__INF_ENERGY", state)

        local function isMyEntity(ent)
            local me = pg and pg.me
            if ent == nil or me == nil then return false end
            return ent == me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
        end

        ActorCombatAttribute.getEp = function(self)
            if state.enabled and isMyEntity(self.entity) then
                return self:getMaxEp()
            end
            return state.originalGetEp(self)
        end

        ActorCombatAttribute.getSp = function(self)
            if state.enabled and isMyEntity(self.entity) then
                return self:getMaxSp()
            end
            return state.originalGetSp(self)
        end
    else
        state.enabled = ENABLED
    end
    print("[Infinite Energy] EP + SP", state.enabled and "ON" or "OFF")
end
