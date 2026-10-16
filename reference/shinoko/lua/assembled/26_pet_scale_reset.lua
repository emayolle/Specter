-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Échelle du pet — reset (1.0)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180007540
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local C=require("Const.ClientConst")
local p=pg.me:getCurPetEntity()
if p then
    p:setModelScale(C.MODEL_SCALE_KEY.DEFAULT, 1)
end