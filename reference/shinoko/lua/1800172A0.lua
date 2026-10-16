

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
