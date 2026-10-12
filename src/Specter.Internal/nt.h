// Specter.Internal — NT / hostch bridge.
//
// The proton-ge-hostch fork exposes a DEDICATED, NON-EXPORTED entry
// `HostchSpawnThread` in ntdll.dll (see wine-hostch patches/hostch-spawnthread.patch).
// It is deliberately absent from the export table, so it is resolved by RVA,
// which the build bakes into hostch-rva.h. It creates a hidden (is_system)
// thread — invisible to guest thread enumeration — so the DLL never has to
// call CreateThread.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace specter::nt {

// Run `proc(arg)` on a hidden (is_system) thread. Returns true on success.
//
// `proc` is entered OUTSIDE the loader, so per-thread CRT state is NOT set up.
// If it uses the C++ runtime (thread_local, exceptions, std::mutex, errno, ...)
// initialise it first:
//
//     _CRT_INIT((HMODULE)&__ImageBase, DLL_THREAD_ATTACH, nullptr);
bool spawn_hidden(DWORD (WINAPI *proc)(LPVOID), void *arg);

}  // namespace specter::nt
