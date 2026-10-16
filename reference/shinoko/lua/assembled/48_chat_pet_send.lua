-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Toplogo — bulle de chat du pet
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 1800207E0, 180020C50
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local UI=require("Const.UIConst")
local E=require("Const.EventConst")
local p=pg.me:getCurPetEntity()
if p then
    p:ensureToplogoComponent(UI.TOPLOGO_COMPONENT.PLAYER_CHAT)
    p.eventEmitter:emit(
        E.TOPLOGO_PLAYER_CHAT_BUBBLE,
        true,
        "Message",
        false,
        nil
    )
end