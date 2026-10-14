// Specter.Internal — implementation of the injected runtime.

#include "pch-il2cpp.h"

#include "app/specter.h"
#include "features/console/console.h"
#include "lua/pump.h"
#include "features/lua_dump/lua_dump.h"
#include "platform/log.h"
#include "il2cpp/runtime.h"
#include "platform/nt.h"
#include "render/dxgi_hook.h"

namespace specter {

bool start()
{
    log::init();

    if (!il2cpp::initialize()) {
        log::error("start failed: GameAssembly.dll is not mapped");
        return false;
    }

    // First feature: prove the resolved VM API from inside the process.
    il2cpp::self_check();

    // Order matters here, and it is the opposite of the obvious one: every hook
    // is registered BEFORE the pump's detour goes in. The detour starts firing
    // on the very next CommonUpdate, so anything that must be drained on the Lua
    // thread has to be wired before that, not after.

    // Runtime Lua chunk dumper: taps xluaL_loadbuffer in xlua.dll so the
    // shipped LuaJIT bytecode (and anything XPatch drops at runtime) can be
    // captured. Installed here so it is in place before the game loads its
    // startup pack; xlua.dll may not be mapped yet, in which case its own tick
    // hook retries. The detour goes in regardless of the enabled flag -- that
    // only gates the file writes -- so toggling it later still captures
    // everything from the game's first chunk onwards.
    features::lua_dump::install();
    features::lua_dump::set_enabled(true);
    lua::pump::set_chunk_filter(&features::lua_dump::filter);

    // The console is the one and only path that runs Lua: its Execute button.
    // It only registers a drain hook; it runs nothing by itself.
    if (!features::console::install()) {
        log::error("start: Lua console could not register its drain hook");
    }

    // Pump last: installs the CommonUpdate detour, which is what makes the Lua
    // thread reachable in the first place.
    if (!lua::pump::install()) {
        log::error("start: Lua pump unavailable - the console will not run");
    }

    // D3D12 overlay: hook IDXGISwapChain::Present and render ImGui. Runs on
    // its own hidden thread so it never depends on the loader thread and never
    // uses CreateThread.
    if (!nt::spawn_hidden(dxgi::overlay_worker, nullptr)) {
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
