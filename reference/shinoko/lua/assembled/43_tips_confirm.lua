-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : UI Tips — confirmation Oui/Non
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 18001D300, 18001D760, 18001DBC0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

pg.global.ui.tips:showConfirm("Confirmer ?", "OUI",
    function()
        print("YES")
        pg.global.ui.tips:showTextTip("ENABLED", 3)
    end,
    false,
    function()
        print("NO")
        pg.global.ui.tips:showTextTip("CANCELLED", 3)
    end
)