-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Rate-Limit Bypass — contourne la limite de taux client (ClientSwitch)
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180016E20, 1800172A0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local ok, ClientSwitch = pcall(require, "Common.ClientSwitch")
    if ok and ClientSwitch then
        local ENABLED = 1  -- INSERTION runtime: état (1=ON, 0=OFF)


        local state = rawget(_G, "__RATE_LIMIT_BYPASS")
        if not state then
            state = {
                origEnable = ClientSwitch.ClientMsCallRateLimitEnable,
                origBurst = ClientSwitch.ClientMsCallRateLimitBurstCapacity,
                origMax = ClientSwitch.ClientMsCallRateLimitMaxCount
            }
            rawset(_G, "__RATE_LIMIT_BYPASS", state)
        end

        if ENABLED then
            ClientSwitch.ClientMsCallRateLimitEnable = false
            ClientSwitch.ClientMsCallRateLimitBurstCapacity = 999999
            ClientSwitch.ClientMsCallRateLimitMaxCount = 999999
            print("[Mod] Packet Rate Limit: DISABLED")
        else
            ClientSwitch.ClientMsCallRateLimitEnable = state.origEnable
            ClientSwitch.ClientMsCallRateLimitBurstCapacity = state.origBurst
            ClientSwitch.ClientMsCallRateLimitMaxCount = state.origMax
            print("[Mod] Packet Rate Limit: RESTORED")
        end
    else
        print("[Mod] Error: ClientSwitch not found")
    end
end
