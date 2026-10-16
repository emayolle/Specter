-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Toplogo — bulle de chat du joueur
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18001FA80, 18001FEF0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local UI=require("Const.UIConst")
local E=require("Const.EventConst")
pg.me:ensureToplogoComponent(UI.TOPLOGO_COMPONENT.PLAYER_CHAT)
pg.me.eventEmitter:emit(
    E.TOPLOGO_PLAYER_CHAT_BUBBLE,
    true,
    "Message",
    false,
    nil
)