
do
    local ok1, PawnController = pcall(require, "GameApp.Controller.PawnController")
    local ok2, PlayerController = pcall(require, "GameApp.Controller.PlayerController")

    if not ok1 or not PawnController then
        print("[Mod] Error: PawnController not found")
        return
    end

    local InputCommand = require("GameApp.Input.InputCommand")
    local Const = require("Common.Const.Const")

    local ENABLED = 