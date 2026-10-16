local C=require("Const.ClientConst")
local p=pg.me:getCurPetEntity()
if p then
    p:setModelScale(C.MODEL_SCALE_KEY.DEFAULT, 