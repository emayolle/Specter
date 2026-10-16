
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
