-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : No Fall Damage — ACTIVER
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 1800079D0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

local ClientDyingComponent = require("Entities.SpaceEntities.CommonComponent.ClientDyingComponent")
if not _G.OriginalFallDamage then
    _G.OriginalFallDamage = ClientDyingComponent.receiveFallToGroundDamage
end
ClientDyingComponent.receiveFallToGroundDamage = function(self, height)
    print("Fall damage blocked! height:", tostring(height))
    return
end
print("[NO FALL DAMAGE] ON")