// Specter.Internal — injected DLL entry point (declaration).
//
// Name kept as "main.h": Il2CppInspector's generated framework/dllmain.cpp
// does `#include "main.h"` and expects `Run()` to be declared there, so this
// file is the seam between the generated scaffold and our code.

#pragma once

// Entry point executed on the dedicated thread spawned by DllMain.
// See framework/dllmain.cpp (generated) and entry.cpp (ours).
void Run();
