// Specter.Internal — injected DLL entry point.
//
// We own DllMain instead of consuming the generated framework/dllmain.cpp.
//
//   - wine-hostch starts a *hidden* canonical Wine thread (server-side
//     is_system) and calls our PE entry (DllMainCRTStartup) on it with
//     (hinstDLL = base, DLL_PROCESS_ATTACH, NULL);
//   - a plain CreateThread here would create a *guest-visible* thread whose
//     start address lands in manually-mapped (zero-Ldr) memory -> a classic
//     anti-cheat signal, undoing the injector's stealth.
//
// So DllMain does the minimum: it hands the bring-up to a *hidden* worker
// thread created through our own fork entry (nt::spawn_hidden ->
// HostchSpawnThread, is_system server-side). That is the sanctioned way to
// create a thread from the DLL. See docs/ARCHITECTURE.md,
// "Injection, threads et discrétion".

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "il2cpp-init.h"  // init_il2cpp() — generated scaffold bindings
#include "log.h"          // specter::log::init / error
#include "nt.h"           // specter::nt::spawn_hidden
#include "specter.h"

// Log file used by the generated helper `il2cppi_log_write` (see helpers.cpp).
// Only used when the host pipe is gone (fallback). It must never land in the
// game directory or the wine prefix: under Wine/Proton the Z: drive maps to
// the Linux root, so this ends up at /tmp/specter-fallback.log on the host.
extern const LPCWSTR LOG_FILE = L"Z:\\tmp\\specter-fallback.log";

// Our own image base (the module is manually mapped, so it is not in the Ldr
// list and cannot be found by GetModuleHandle). Declared per the usual idiom;
// winnt.h may already declare it, in which case this is an identical redecl.
extern "C" IMAGE_DOS_HEADER __ImageBase;

// CRT per-thread initialiser. Not declared in the public CRT headers (it is
// guarded by _CRTBLD there), so the manual-map idiom is to declare it. The
// symbol lives in the CRT startup object that is statically linked into every
// module (vcruntime.lib under /MD, libcmt under /MT).
extern "C" int __cdecl _CRT_INIT(void* hDllHandle, unsigned long dwReason, void* lpreserved);

namespace {

// Bring the runtime up on our hidden worker thread.
//
// The thread is created with NtCreateThreadEx (not _beginthreadex), so it is
// entered outside the loader and receives no CRT thread-attach: set the
// per-thread CRT state up first (see nt.h).
DWORD WINAPI worker_main(LPVOID)
{
    _CRT_INIT(reinterpret_cast<HMODULE>(&__ImageBase), DLL_THREAD_ATTACH, nullptr);

    init_il2cpp();
    specter::start();
    return 0;
}

}  // namespace

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (reason) {
    case DLL_PROCESS_ATTACH:
        // Bring the log sink up first, so that a failed spawn is visible on
        // the pipe (not only in the fallback file log).
        specter::log::init();

        // Start the work on a hidden (is_system) worker thread. If the fork
        // entry is unavailable (unpatched ntdll / RVA not baked), log it and
        // fall back to running inline on the injector's hidden thread.
        if (!specter::nt::spawn_hidden(worker_main, nullptr)) {
            specter::log::error(
                "spawn_hidden failed (HostchSpawnThread unresolved) - "
                "running init inline on the injector thread");
            worker_main(nullptr);
        }
        break;
    case DLL_PROCESS_DETACH:
        specter::stop();
        break;
    default:
        break;
    }

    return TRUE;
}
