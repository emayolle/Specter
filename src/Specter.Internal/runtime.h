// Specter.Internal — the IL2CPP runtime seam.
//
// Aniimo's GameAssembly.dll exports no `il2cpp_*` symbols (NetEase stripped
// them), so the generated appdata/il2cpp-api-functions.h is empty and the
// runtime API cannot be linked by name. This module owns the entire problem of
// locating the runtime and resolving the few functions we need, so the rest of
// the code never worries about it.

#pragma once

#include <cstdint>

namespace specter {
namespace runtime {

// Locate GameAssembly.dll and resolve the runtime API we need.
// Returns false if the module is not mapped.
bool initialize();

// Base address of the mapped GameAssembly.dll, or 0 if not mapped yet.
uintptr_t module_base();

}  // namespace runtime
}  // namespace specter
