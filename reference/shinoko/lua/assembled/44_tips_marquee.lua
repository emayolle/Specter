-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : UI Tips — texte défilant
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18001E030, 18001E4A0, 18001E900
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

pg.global.ui.tips:showMarqueeText("TEXTE", 3.0  -- INSERTION runtime: durée en secondes (slider menu)
, nil)