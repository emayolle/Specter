
    local state = rawget(_G, "__INF_STAMINA")
    if not state then
        state = {
            enabled = ENABLED,
            originalChangeStamina = ActorCombatAttribute.changeStamina
        }
        rawset(_G, "__INF_STAMINA", state)

        local function isProtectedEntity(ent)
            local me = pg and pg.me
            if ent == nil or me == nil then return false end
            return ent == me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
        end

        ActorCombatAttribute.changeStamina = function(self, value)
            if state.enabled and value ~= nil and value < 0 and isProtectedEntity(self.entity) then
                print("[Infinite Stamina] blocked:", tostring(value))
                return
            end
            return state.originalChangeStamina(self, value)
        end
    else
        state.enabled = ENABLED
    end
    print("[Infinite Stamina]", state.enabled and "ON" or "OFF")
end
