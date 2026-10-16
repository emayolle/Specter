",
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