// Specter.Internal — the IL2CPP runtime seam.
//
// Aniimo's GameAssembly.dll exports no `il2cpp_*` symbols (NetEase stripped
// them), so the generated appdata/il2cpp-api-functions.h is empty and the
// runtime API cannot be linked by name. This module owns the entire problem of
// locating the runtime and resolving the few functions we need, so the rest of
// the code never worries about it.
//
// Resolution itself lives in api/ (api.{h,cpp}): the VM functions are
// exported under `mono_*` compatibility names, recovered here by export name
// after body verification on the real binary.

#pragma once

#include <cstdint>

namespace specter {
namespace runtime {

// Locate GameAssembly.dll and resolve the runtime API (api::resolve()).
// Returns false if the module is not mapped.
bool initialize();

// Base address of the mapped GameAssembly.dll, or 0 if not mapped yet.
uintptr_t module_base();

// First feature: prove the resolved API end-to-end from inside the process —
// managed string round-trip, assembly enumeration, class introspection.
// Every step is null-guarded and log-only; never raises.
void self_check();

}  // namespace runtime
}  // namespace specter