// Specter.Internal — minimal x64 inline detour.
//
// Installs a 12-byte relay (`mov rax, imm64; jmp rax`) at the target and
// builds a trampoline that replays the displaced bytes then jumps back past
// the patch. Used by the D3D12 overlay to hook IDXGISwapChain::Present and
// IDXGISwapChain::ResizeBuffers (DXVK/vkd3d code in dxgi.dll).
//
// Safety: this engine does NOT relocate instructions, so it refuses
// prologues it cannot safely move — ones that are shorter than the relay,
// start with a relative call/jump, or contain RIP-relative operands. On
// refusal it logs and returns false; nothing is patched.

#pragma once

#include <cstddef>
#include <cstdint>

namespace specter::overlay {

struct Detour
{
    uintptr_t target = 0;      // hooked function
    uintptr_t trampoline = 0;  // replacement "original" entry
    std::size_t length = 0;    // bytes displaced (always 12 on success)
    std::uint8_t original[16] = {};
    bool active = false;
};

// Install the relay detour. Returns false (logged) if the prologue is not
// safely relocatable; the module is never patched on failure.
bool detour_install(Detour* d, uintptr_t target, uintptr_t detour);

// Restore the original bytes (removes the relay) and free the trampoline.
void detour_remove(Detour* d);

}  // namespace specter::overlay