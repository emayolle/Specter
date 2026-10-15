// Specter.Internal — implementation of the injected runtime.

#include "pch-il2cpp.h"

#include "app/specter.h"
#include "features/feature.h"
#include "features/lua_dump/lua_dump.h"
#include "lua/pump.h"
#include "lua/worker.h"
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

    // Install every feature, from the registry. Adding one used to mean
    // editing this function; now it means one line in features/registry.cpp.
    // The pump goes in LAST: it is what makes the Lua thread reachable, so
    // anything that wants a hook on that thread has to be wired before it —
    // otherwise the detour starts firing into a half-built list.
    for (int i = 0; i < features::registry_count(); ++i) {
        const features::Feature* f = features::registry()[i];
        if (!f->install) {
            continue;
        }
        if (!f->install()) {
            log::error("start: feature '%s' failed to install", f->id);
        }
    }

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
    // Before anything else, and while our code is still mapped. A worker thread
    // still inside lua_pcall when the image goes away jumps into memory that is
    // no longer there, so the workers are stopped FIRST and the log line last.
    lua::worker::shutdown();

    log::info("detached");
}

}  // namespace specter
