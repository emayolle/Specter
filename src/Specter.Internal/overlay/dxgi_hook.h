// Specter.Internal — DXGI swapchain hook (D3D12 overlay entry point).
//
// The game renders through D3D12 (vkd3d-proton) and its DXGI swapchains live
// in dxgi.dll. Every swapchain of a given module shares the same vtable code,
// so we create one *probe* swapchain (own device + hidden window), read the
// vtable addresses of Present (index 8), Present1 (index 22) and ResizeBuffers
// (index 13), then detour those code addresses. The detours then intercept the
// game's own swapchain too.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace specter::overlay {

// Install the Present/ResizeBuffers detours. Call ONCE from a hidden worker
// thread (never CreateThread). Returns true when at least Present is hooked.
bool dxgi_install();

// Hidden worker entry, spawned by specter::start via nt::spawn_hidden.
unsigned long WINAPI overlay_worker(void* arg);

}  // namespace specter::overlay