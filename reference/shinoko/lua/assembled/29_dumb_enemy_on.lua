-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Dumb Enemy — IA désactivée (AiConst.GLOBAL_OPEN_TICK=false)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 1800082B0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

do
    local AiConst = package.loaded["Common.Const.AiConst"]
    if type(AiConst) ~= "table" then
        AiConst = require("Common.Const.AiConst")
    end
    if type(AiConst) == "table" then
        AiConst.GLOBAL_OPEN_TICK = false
        print("[AI TICK] OFF / Dumb Enemy ON")
    end
end