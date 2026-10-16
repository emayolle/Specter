-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Toplogo — effacer la bulle du joueur
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180020360
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local E=require("Const.EventConst")
pg.me.eventEmitter:emit(
    E.TOPLOGO_PLAYER_CHAT_BUBBLE,
    false,
    ""
)