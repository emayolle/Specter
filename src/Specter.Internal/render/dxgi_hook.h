// Specter.Internal — DXGI swapchain hook (D3D12 overlay entry point).
//
// The game renders through D3D12 (vkd3d-proton) and its DXGI swapchains live
// in dxgi.dll. Every instance of a class shares one immutable vtable, so we
// create one *probe* swapchain (own device + hidden window) and one probe
// command queue, then swap the vtable slots for Present (8), Present1 (22),
// ResizeBuffers (13) and ExecuteCommandLists (10) with our proxies. The saved
// slot pointers are the originals; the patches then cover the game's own
// objects too.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace specter::dxgi {

// Install the vtable hooks. Call ONCE from a hidden worker thread (never
// CreateThread). Returns true when at least Present is hooked.
bool dxgi_install();

// Hidden worker entry, spawned by specter::start via nt::spawn_hidden.
unsigned long WINAPI overlay_worker(void* arg);

}  // namespace specter::dxgi