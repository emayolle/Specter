-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : ⚠ INCOMPLET — définition de `target` (téléport cible ?) — se termine `getForward()*`, suite introuvable
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180004EC0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local pg=require("Pg")
local U=require("Common.Utils.Utils")
local me=pg.me
local target=me:getPosition()+me:getForward()*