// Specter.Internal — ImGui/D3D12 overlay bridge.
//
// Runs inside the Present hook (game render thread): initialises ImGui once
// with the game's device (from the swapchain) and the game's own command queue
// (learned from ExecuteCommandLists), then renders the UI into the current
// back buffer before the original Present submits the frame. The render thread
// is the only thread that touches ImGui state; toggling uses a plain atomic.
//
// The game's queue is used on purpose: vkd3d-proton runs the real present on
// the swapchain's queue and blits from the app's back buffer assuming same
// queue ordering, so a private queue would race the presentation.

#pragma once

struct IDXGISwapChain;
struct ID3D12CommandQueue;

namespace specter::overlay {
namespace d3d12_overlay {

// Render-thread, called from the Present hook (before the original call).
void on_present(IDXGISwapChain* sc);

// Called from the ResizeBuffers hook, before the original call. Releases our
// references to the old back buffers (DXGI refuses to resize while any are
// outstanding) and marks the swapchain dirty; RTVs are rebuilt on the next
// present.
void on_resize(IDXGISwapChain* sc);

// Called from the ExecuteCommandLists hook on whatever thread submits work.
// Records the game's queues (deduplicated) so we can render on the one that
// belongs to the swapchain's device.
void on_command_queue(ID3D12CommandQueue* queue);

// Fallback hwnd (the probe window) used when the game swapchain reports none.
void set_probe_window(void* hwnd);

}  // namespace d3d12_overlay
}  // namespace specter::overlay
