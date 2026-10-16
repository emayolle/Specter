local E=require("Const.EventConst")
pg.me.eventEmitter:emit(
    E.TOPLOGO_PLAYER_CHAT_BUBBLE,
    false,
    ""
)