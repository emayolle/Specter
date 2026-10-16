-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Téléportation de scène
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180014A30, 180014EA0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local pg=require("Pg");pg.me:tryTeleportToScene(1001  -- INSERTION runtime: ID de scène (liste déroulante menu)
, 0, true)