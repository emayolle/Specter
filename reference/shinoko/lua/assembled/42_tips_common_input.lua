-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : UI Tips — boîte de saisie réutilisable
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18001CA20, 18001CE90
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

pg.global.ui.tips:showCommonInput("Saisie", function(text)
    print("INPUT:", text)
    pg.global.ui.tips:showTextTip(text, 5)
end)