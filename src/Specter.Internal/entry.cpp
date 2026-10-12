// Specter.Internal — injected DLL entry point.
//
// We own DllMain instead of consuming the generated framework/dllmain.cpp, so
// the injection entry does exactly one thing and, crucially, does NOT spawn a
// thread:
//
//   - wine-hostch starts a *hidden* canonical Wine thread (server-side
//     is_system) and invokes our DllMain on it;
//   - a plain CreateThread here would create a *guest-visible* thread whose
//     start address lands in manually-mapped (zero-Ldr) memory -> a classic
//     anti-cheat signal, undoing the injector's stealth.
//
// Current scope is logging only, which is short and loader-lock-safe, so it
// runs inline on that hidden thread. No logic lives here on purpose.
//
// FUTURE WORKERS (loops, hooks): do NOT start them with CreateThread here.
// A persistent worker must be created hidden (server-side is_system) from the
// host side via the hostch channel. See docs/ARCHITECTURE.md,
// "Injection, threads et discrétion".

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "il2cpp-init.h"  // init_il2cpp() — generated scaffold bindings
#include "specter.h"

// Log file used by the generated helper `il2cppi_log_write` (see helpers.cpp).
extern const LPCWSTR LOG_FILE = L"specter-log.txt";

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (reason) {
    case DLL_PROCESS_ATTACH:
        // Runs on the injector's hidden thread: keep it inline, spawn nothing.
        init_il2cpp();
        specter::start();
        break;
    case DLL_PROCESS_DETACH:
        specter::stop();
        break;
    default:
        break;
    }

    return TRUE;
}
