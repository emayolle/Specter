
do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    _G.pg = pg
    local AbilityConst = require("Common.Const.AbilityConst")
    local Const = require("Common.Const.Const")
    local CombatActionTool = require("Common.Ability.CombatActionTool")
    local Utils = require("Common.Utils.Utils")
    local ClientCombatAction = require("GameApp.Ability.ClientCombatAction")

    local ENABLED = 