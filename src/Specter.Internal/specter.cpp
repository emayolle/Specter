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

    return true;
}

void stop()
{
    log::info("detached");
}

}  // namespace specter
