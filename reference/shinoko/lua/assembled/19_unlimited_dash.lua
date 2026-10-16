-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Unlimited Dash — dash sans limite
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180010E50, 1800112C0
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================


do
    local ok1, PawnController = pcall(require, "GameApp.Controller.PawnController")
    local ok2, PlayerController = pcall(require, "GameApp.Controller.PlayerController")

    if not ok1 or not PawnController then
        print("[Mod] Error: PawnController not found")
        return
    end

    local InputCommand = require("GameApp.Input.InputCommand")
    local Const = require("Common.Const.Const")

    local ENABLED = 1  -- INSERTION runtime: état Unlimited Dash (1=ON, 0=OFF)


    local state = rawget(_G, "__UNLIMITED_DASH")
    if not state then
        state = {
            enabled = ENABLED,
            origPawnDash = PawnController.onHandleDash,
            origPlayerDash = (ok2 and PlayerController) and PlayerController.onHandleDash or nil
        }
        rawset(_G, "__UNLIMITED_DASH", state)
    else
        state.enabled = ENABLED
    end

    local function customDash(self, isPress, ignoreCancelStates)
        if not state.enabled then
            if self == PawnController and state.origPawnDash then
                return state.origPawnDash(self, isPress, ignoreCancelStates)
            elseif state.origPlayerDash then
                return state.origPlayerDash(self, isPress, ignoreCancelStates)
            end
            return
        end

        if not self:checkPawn() then return end

        if isPress then
            self.dashCount = 0
            self.lastDashTime = 0

            if self.pawn.cancelAbility then
                self.pawn:cancelAbility()
            end

            self.pawn.eModel:SetInputCommand(Const.COMPONENT_INDEX_CHARACETER_CONTROLLER, InputCommand.DashMark, true)
            self.pawn.eModel:SetInputCommand(Const.COMPONENT_INDEX_CHARACETER_CONTROLLER, InputCommand.Dash, true, 1)
        else
            self.pawn.eModel:SetInputCommand(Const.COMPONENT_INDEX_CHARACETER_CONTROLLER, InputCommand.Dash, false)
        end
    end

    if state.enabled then
        PawnController.onHandleDash = customDash
        if ok2 and PlayerController then
            PlayerController.onHandleDash = customDash
        end

        if pg and pg.game and pg.game.controller and pg.game.controller.curController then
            pg.game.controller.curController.dashCount = 0
            pg.game.controller.curController.lastDashTime = 0
        end

        print("[Mod] Unlimited Dash: ENABLED (No ReadOnly Error)")
    else
        if state.origPawnDash then
            PawnController.onHandleDash = state.origPawnDash
        end
        if ok2 and PlayerController and state.origPlayerDash then
            PlayerController.onHandleDash = state.origPlayerDash
        end
        print("[Mod] Unlimited Dash: DISABLED")
    end
end
