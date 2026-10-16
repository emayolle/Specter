local ClientDyingComponent = require("Entities.SpaceEntities.CommonComponent.ClientDyingComponent")
if _G.OriginalFallDamage then
    ClientDyingComponent.receiveFallToGroundDamage = _G.OriginalFallDamage
    _G.OriginalFallDamage = nil
    print("[NO FALL DAMAGE] OFF")
else
    print("[NO FALL DAMAGE] original function not saved")
end