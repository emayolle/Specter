// Specter.Internal — ImGui/D3D12 overlay bridge.
//
// Runs inside the Present detour (game render thread): initialises ImGui once
// with the game's device (from the swapchain) plus our own command queue and
// descriptor heaps, then renders the UI into the current backbuffer before the
// original Present submits the frame. The render thread is the only thread
// that touches ImGui state; toggling uses a plain atomic.

#pragma once

struct IDXGISwapChain;

namespace specter::overlay {
namespace d3d12_overlay {

// Render-thread, called from the Present detour (before the original call).
void on_present(IDXGISwapChain* sc);

// Render-thread, called from the ResizeBuffers detour. Marks the swapchain
// dirty; the RTV cache is rebuilt on the next present.
void on_resize(IDXGISwapChain* sc);

// Fallback hwnd (the probe window) used when the game swapchain reports none.
void set_probe_window(void* hwnd);

}  // namespace d3d12_overlay
}  // namespace specter::overlay