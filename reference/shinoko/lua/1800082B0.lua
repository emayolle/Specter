do
    local AiConst = package.loaded["Common.Const.AiConst"]
    if type(AiConst) ~= "table" then
        AiConst = require("Common.Const.AiConst")
    end
    if type(AiConst) == "table" then
        AiConst.GLOBAL_OPEN_TICK = false
        print("[AI TICK] OFF / Dumb Enemy ON")
    end
end