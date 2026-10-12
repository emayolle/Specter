// Specter.Internal — implementation of the injected runtime.

#include "pch-il2cpp.h"

#include "specter.h"
#include "log.h"
#include "runtime.h"

namespace specter {

bool start()
{
    log::init();

    if (!runtime::initialize()) {
        log::error("start failed: GameAssembly.dll is not mapped");
        return false;
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
