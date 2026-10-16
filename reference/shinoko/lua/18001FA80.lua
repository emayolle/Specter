local UI=require("Const.UIConst")
local E=require("Const.EventConst")
pg.me:ensureToplogoComponent(UI.TOPLOGO_COMPONENT.PLAYER_CHAT)
pg.me.eventEmitter:emit(
    E.TOPLOGO_PLAYER_CHAT_BUBBLE,
    true,
    "