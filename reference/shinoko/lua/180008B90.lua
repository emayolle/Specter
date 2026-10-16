
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
            enabled = 