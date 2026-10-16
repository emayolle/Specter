local UI=require("Const.UIConst")
local E=require("Const.EventConst")
local p=pg.me:getCurPetEntity()
if p then
    p:ensureToplogoComponent(UI.TOPLOGO_COMPONENT.PLAYER_CHAT)
    p.eventEmitter:emit(
        E.TOPLOGO_PLAYER_CHAT_BUBBLE,
        true,
        "