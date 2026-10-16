-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Infini Énergie (EP + SP)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18000B3C0, 18000B840
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local ActorCombatAttribute = require("Common.Ability.Attribute.ActorCombatAttribute")
    local ENABLED = 1  -- INSERTION runtime: état Inf Energy (1=ON, 0=OFF)

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
