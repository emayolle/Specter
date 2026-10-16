-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Échelle du pet (valeur personnalisée)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 1800069D0, 180006E50
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local C=require("Const.ClientConst")
local p=pg.me:getCurPetEntity()
if p then
    p:setModelScale(C.MODEL_SCALE_KEY.DEFAULT, 1.5  -- INSERTION runtime: échelle du modèle (slider menu)
)
end