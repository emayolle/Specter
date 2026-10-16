
do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    _G.pg = pg
    local Const = require("Common.Const.Const")
    local Utils = require("Common.Utils.Utils")
    local TimerManager = require("Core.Timer.TimerManager")

    local ENABLED = 