-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : No Fall Damage — DÉSACTIVER
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180007E40
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local ClientDyingComponent = require("Entities.SpaceEntities.CommonComponent.ClientDyingComponent")
if _G.OriginalFallDamage then
    ClientDyingComponent.receiveFallToGroundDamage = _G.OriginalFallDamage
    _G.OriginalFallDamage = nil
    print("[NO FALL DAMAGE] OFF")
else
    print("[NO FALL DAMAGE] original function not saved")
end