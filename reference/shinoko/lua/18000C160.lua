
do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    _G.pg = pg
    local Ability = require("CustomTypes.Ability")
    local AbilityUIUtils = require("Utils.AbilityUIUtils")
    local PetListUIComponent = require("Guis.Panels.HudV2.BaseComponent.PetListUIComponent")

    local state = rawget(_G, "__NO_CD_STATE")
    if not state then
        state = {
            playerEnabled = false,
            petEnabled = false,
            origIsInCd = Ability.isInCd,
            origStartCoolDown = Ability.startCoolDown,
            origRefreshCDState = AbilityUIUtils.refreshCDState,
            origRefreshSupportSkillCD = PetListUIComponent.refreshSupportSkillCD
        }
        rawset(_G, "__NO_CD_STATE", state)

        local function isMyEntity(ent)
            local me = pg and pg.me
            if ent == nil or me == nil then return false end
            return ent == me or ent == pg.pawn or ent.isMainPlayer == true or ent.isMainPet == true
        end

        local function isMyPlayerEntity(ent)
            local me = pg and pg.me
            if ent == nil or me == nil then return false end
            return ent == me or ent == pg.pawn or ent.isMainPlayer == true
        end

        local function isMyAbility(ability)
            if ability == nil or ability.actorId == nil then return false end
            local entity = pg.getEntityByActorId(ability.actorId)
            return isMyEntity(entity)
        end

        local function clearCd(ability)
            if ability == nil then return end
            if ability.cdEndTime ~= nil and ability.cdEndTime > 0 then
                ability.cdEndTime = 0
            end
        end

        Ability.isInCd = function(self)
            if (state.playerEnabled or state.petEnabled) and isMyAbility(self) then
                return false
            end
            return state.origIsInCd(self)
        end

        Ability.startCoolDown = function(self, cdEndTime)
            if (state.playerEnabled or state.petEnabled) and isMyAbility(self) then
                cdEndTime = 0
            end
            return state.origStartCoolDown(self, cdEndTime)
        end

        AbilityUIUtils.refreshCDState = function(btnRefInfo, skillInfo)
            if state.playerEnabled and skillInfo ~= nil then
                local pawn = skillInfo.pawn or (pg and pg.pawn)
                if pawn ~= nil and isMyPlayerEntity(pawn) and pawn.abilityMap ~= nil and skillInfo.abilityId ~= nil then
                    clearCd(pawn.abilityMap[skillInfo.abilityId])
                end
            end
            return state.origRefreshCDState(btnRefInfo, skillInfo)
        end

        PetListUIComponent.refreshSupportSkillCD = function(self, button, refreshTarget, petEntity, index, refreshBtnFunc)
            if state.petEnabled and petEntity ~= nil and petEntity.coreAbilityId ~= nil and isMyEntity(petEntity) then
                clearCd(petEntity:getAbility(petEntity.coreAbilityId))
            end
            return state.origRefreshSupportSkillCD(self, button, refreshTarget, petEntity, index, refreshBtnFunc)
        end
    end

    state.playerEnabled = 