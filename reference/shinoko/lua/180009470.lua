
    end

    if pg and pg.me then
        pcall(function()
            pg.me:doGmCmd("modifyStateSelf", 1, state.enabled and 1 or 0)
        end)
    end
    print("[GOD MODE]", state.enabled and "ON" or "OFF")
end
