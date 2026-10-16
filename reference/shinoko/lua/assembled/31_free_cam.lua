-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Free Cam / Camera
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180017A10
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local pg = rawget(_G, "pg") or package.loaded["Pg"] or require("Pg")
    if pg and pg.global and pg.global.ui and pg.global.ui.tips and pg.global.ui.tips.showConfirm then
        pg.global.ui.tips:showConfirm(
            "Shinoko ITS FREEEEEEEEE!!!!!!!!",
            "If you bought Shinoko, you were scammed!!",
            function()
                print("[NOTICE] OK clicked")
            end,
            false,
            function()
                print("[NOTICE] Cancel clicked")
            end
        )
    end
end
