local ClientDyingComponent = require("Entities.SpaceEntities.CommonComponent.ClientDyingComponent")
if not _G.OriginalFallDamage then
    _G.OriginalFallDamage = ClientDyingComponent.receiveFallToGroundDamage
end
ClientDyingComponent.receiveFallToGroundDamage = function(self, height)
    print("Fall damage blocked! height:", tostring(height))
    return
end
print("[NO FALL DAMAGE] ON")