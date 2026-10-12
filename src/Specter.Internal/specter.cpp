// Specter.Internal — implementation of the injected runtime.

#include "pch-il2cpp.h"

#include "specter.h"
#include "features/lua_console.h"
#include "log.h"
#include "runtime.h"
#include "nt.h"
#include "overlay/dxgi_hook.h"

namespace specter {

bool start()
{
    log::init();

    if (!runtime::initialize()) {
        log::error("start failed: GameAssembly.dll is not mapped");
        return false;
    }

    // First feature: prove the resolved VM API from inside the process.
    runtime::self_check();

    // Lua console bridge: detour LuaManager.CommonUpdate so queued chunks run
    // on the game's own Lua thread (see features/lua_console.*).
    if (!features::lua::install()) {
        log::error("start: Lua bridge unavailable - the console will not run");
    }

    // D3D12 overlay: hook IDXGISwapChain::Present and render ImGui. Runs on
    // its own hidden thread so it never depends on the loader thread and never
    // uses CreateThread.
    if (!nt::spawn_hidden(overlay::overlay_worker, nullptr)) {
        log::error("start: overlay worker not spawned - no overlay");
    }

    log::info("attached");

    // TODO: install hooks and register features.
    //   - features live under src/Specter.Internal/features/ (see docs/ARCHITECTURE.md)
    //   - hooks use the offsets in generated/sdk/appdata/il2cpp-functions.h
    //
    // STEALTH (see docs/ARCHITECTURE.md, "Injection, threads et discrétion"):
    //   start() runs on the hidden (is_system) worker thread that DllMain
    //   created with nt::spawn_hidden. Starting *further* persistent workers
    //   (loops, hook dispatchers) must also go through nt::spawn_hidden --
    //   never CreateThread, which yields a guest-visible thread whose start
    //   address lands in manually-mapped memory.

    return true;
}

void stop()
{
    log::info("detached");
}

}  // namespace specter
