-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Infini Stamina / Endurance
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18000AAD0, 18000AF50
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local ActorCombatAttribute = require("Common.Ability.Attribute.ActorCombatAttribute")
    local ENABLED = 1  -- INSERTION runtime: état Inf Stamina (1=ON, 0=OFF)

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
