// Specter.Internal — implementation of the IL2CPP runtime seam.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "runtime.h"
#include "log.h"

namespace specter {
namespace runtime {

uintptr_t module_base()
{
    return reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));
}

bool initialize()
{
    if (module_base() == 0) {
        return false;
    }

    // The IL2CPP API (il2cpp_*) is not exported. The functions exist internally,
    // so they have to be recovered by signature/motif scanning before they can
    // be called (see docs/ARCHITECTURE.md, "Limitation: no exported API").
    //
    // Per-method pointers from appdata/il2cpp-functions.h are offsets relative
    // to module_base() and need no resolution.
    log::info("runtime: GameAssembly.dll mapped");
    return true;
}

}  // namespace runtime
}  // namespace specter
