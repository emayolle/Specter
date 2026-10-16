do
    local AiConst = package.loaded["Common.Const.AiConst"]
    if type(AiConst) ~= "table" then
        AiConst = require("Common.Const.AiConst")
    end
    if type(AiConst) == "table" then
        AiConst.GLOBAL_OPEN_TICK = true
        print("[AI TICK] ON / Dumb Enemy OFF")
    end
end