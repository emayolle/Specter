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
    //   start() runs on the injector's hidden thread. Any *persistent worker*
    //   (loop, hook dispatcher) must NOT be spawned with CreateThread here --
    //   that yields a guest-visible thread whose start address lands in
    //   manually-mapped memory. Workers are created hidden from the host side
    //   (hostch), not from inside the DLL.

    return true;
}

void stop()
{
    log::info("detached");
}

}  // namespace specter
