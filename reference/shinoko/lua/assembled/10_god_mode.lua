-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : God Mode (protection combat, chutes, RPC) — 3 fragments + 2 toggles
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180008B90, 180009000, 180009470
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local AbilityConst = require("Common.Const.AbilityConst")
    local Const = require("Common.Const.Const")
    local CombatActionTool = require("Common.Ability.CombatActionTool")
    local Utils = require("Common.Utils.Utils")
    local ClientCombatAction = require("GameApp.Ability.ClientCombatAction")
    local ClientDyingComponent = require("Entities.SpaceEntities.CommonComponent.ClientDyingComponent")
    local ClientPlayer = require("Entities.SpaceEntities.ClientPlayer")
    local ClientMainPlayer = require("Entities.SpaceEntities.ClientMainPlayer")
    local ClientPet = require("Entities.SpaceEntities.ClientPet")
    local ClientPuppet = require("Entities.SpaceEntities.ClientPuppet")
    local ClientTempPlayer = require("Entities.ClientTempPlayer")
    local ClientRobSpaceEgg = require("Entities.SpaceEntities.ClientRobSpaceEgg")

    local state = rawget(_G, "__GOD_MODE")
    if not state then
        state = {
            enabled = 1  -- INSERTION runtime: état God Mode (1=ON, 0=OFF)
,
            origCheckValidTarget = Utils.checkValidTarget,
            origCalcResult = ClientCombatAction.calcResult,
            origFallDamage = ClientDyingComponent.receiveFallToGroundDamage,
            origEggFallDamage = ClientRobSpaceEgg.receiveFallToGroundDamage,
            origEggImpactDamage = ClientRobSpaceEgg.receiveImpactDamage,
            origServerMsg = ClientPlayer.getVtbl().serverMsg
        }
        rawset(_G, "__GOD_MODE", state)

        local function isProtectedEntity(ent)
            local me = pg and pg.me
            if ent == nil or me == nil then return false end
            return ent == me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
        end

        local function isProtectedEgg(egg)
            if egg == nil or egg.controller == nil then return false end
            local controller = pg.getEntity(egg.controller)
            return controller ~= nil and isProtectedEntity(controller)
        end

        Utils.checkValidTarget = function(target, owner)
            if state.enabled and isProtectedEntity(target) then
                if owner ~= nil and owner ~= target then
                    local ok, hostile = pcall(Utils.checkRelation, owner, target, Const.WORLD_PAIRS_CAMP_ENEMY)
                    if ok and hostile then return false end
                end
            end
            return state.origCheckValidTarget(target, owner)
        end

        ClientCombatAction.calcResult = function(self, actionData, combatContext)
            if state.enabled and actionData ~= nil and combatContext ~= nil then
                local okTarget, targetActorId = pcall(CombatActionTool.parseActorId, combatContext, actionData.target)
                if okTarget and targetActorId ~= nil then
                    local target = pg.getEntityByActorId(targetActorId)
                    if target ~= nil and isProtectedEntity(target) then
                        combatContext.isImmuteDamage = true
                        if combatContext.damageData ~= nil then
                            combatContext.damageData.finalDamage = 0
                            if AbilityConst.ATTACK_RESULT_IMMUNE ~= nil then
                                combatContext.damageData.attackResult = AbilityConst.ATTACK_RESULT_IMMUNE
                            end
                        end
                        print("[GOD] blocked combat damage:", tostring(targetActorId))
                        return false
                    end
                end
            end
            return state.origCalcResult(self, actionData, combatContext)
        end

        local function noFallDamage(self, height)
            if state.enabled and isProtectedEntity(self) then
                print("[GOD] fall damage blocked:", tostring(height))
                return
            end
            return state.origFallDamage(self, height)
        end

        local function noEggFallDamage(self, height)
            if state.enabled and isProtectedEgg(self) then return end
            return state.origEggFallDamage(self, height)
        end

        local function noEggImpactDamage(self, velocity)
            if state.enabled and isProtectedEgg(self) then return end
            return state.origEggImpactDamage(self, velocity)
        end

        local function godServerMsg(self, name, ...)
            if state.enabled and isProtectedEntity(self) then
                if name == "RPC_CS_SpecialDamage" then
                    local _, reason = ...
                    if reason == Const.LIFE_DEAD_BY_FALL_TO_GROUND then
                        print("[GOD] blocked SpecialDamage fall RPC")
                        return
                    end
                end
                if name == "RPC_CS_RobEggHurt" then
                    local _, __, reason = ...
                    if reason == Const.LIFE_DEAD_BY_FALL_TO_GROUND then
                        print("[GOD] blocked RobEgg fall RPC")
                        return
                    end
                end
            end
            return state.origServerMsg(self, name, ...)
        end

        ClientPlayer.getVtbl().receiveFallToGroundDamage = noFallDamage
        ClientMainPlayer.getVtbl().receiveFallToGroundDamage = noFallDamage
        ClientPet.getVtbl().receiveFallToGroundDamage = noFallDamage
        ClientPuppet.getVtbl().receiveFallToGroundDamage = noFallDamage
        ClientTempPlayer.getVtbl().receiveFallToGroundDamage = noFallDamage

        ClientRobSpaceEgg.getVtbl().receiveFallToGroundDamage = noEggFallDamage
        ClientRobSpaceEgg.getVtbl().receiveImpactDamage = noEggImpactDamage

        ClientPlayer.getVtbl().serverMsg = godServerMsg
        ClientMainPlayer.getVtbl().serverMsg = godServerMsg
        ClientPet.getVtbl().serverMsg = godServerMsg
        ClientPuppet.getVtbl().serverMsg = godServerMsg
        ClientTempPlayer.getVtbl().serverMsg = godServerMsg
    else
        state.enabled = 1  -- INSERTION runtime: état God Mode (1=ON, 0=OFF)

    end

    if pg and pg.me then
        pcall(function()
            pg.me:doGmCmd("modifyStateSelf", 1, state.enabled and 1 or 0)
        end)
    end
    print("[GOD MODE]", state.enabled and "ON" or "OFF")
end
