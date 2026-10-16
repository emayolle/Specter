-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : One Hit — les attaques du joueur tuent en un coup
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 1800102A0, 180010710
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    _G.pg = pg
    local AbilityConst = require("Common.Const.AbilityConst")
    local Const = require("Common.Const.Const")
    local CombatActionTool = require("Common.Ability.CombatActionTool")
    local Utils = require("Common.Utils.Utils")
    local ClientCombatAction = require("GameApp.Ability.ClientCombatAction")

    local ENABLED = 1  -- INSERTION runtime: état One Hit (1=ON, 0=OFF)


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
