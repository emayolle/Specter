local E=require("Const.EventConst")
local p=pg.me:getCurPetEntity()
if p then
    p.eventEmitter:emit(
        E.TOPLOGO_PLAYER_CHAT_BUBBLE,
        false,
        ""
    )
end