-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : UI Tips — warning de boss (id + 2 textes)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18001B420, 18001B890, 18001BCF0, 18001C150
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

pg.global.ui.tips:showBossCatchWarning(1  -- INSERTION runtime: ID du boss
, "BOSS", "ATTENTION")