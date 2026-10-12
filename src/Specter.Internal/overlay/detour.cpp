// Specter.Internal — minimal x64 inline detour (implementation).

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstring>

#include "overlay/detour.h"
#include "log.h"

namespace specter::overlay {
namespace {

constexpr std::size_t kRelayLen = 12;  // mov rax, imm64; jmp rax

// True when a byte looks like a RIP-relative ModRM (mod=00, rm=101). These
// encodings embed a displacement relative to the ORIGINAL address and would
// need relocation — which this engine does not do.
inline bool rip_relative_modrm(std::uint8_t b)
{
    return (b & 0xC7) == 0x05 && b != 0x05;  // 0x05 alone is add eax, imm32
}

// True if the first `len` bytes cannot be relocated to a trampoline.
bool unsafe_prologue(const std::uint8_t* p, std::size_t len)
{
    for (std::size_t i = 0; i < len; ++i) {
        const std::uint8_t b = p[i];
        if (b == 0xE8 || b == 0xE9) {          // call/jmp rel32
            return true;
        }
        if (b == 0x0F) {                       // two-byte opcode class (may carry modrm)
            return true;
        }
        if (rip_relative_modrm(b)) {
            // The ModRM byte directly follows the opcode byte for one-byte
            // opcodes. If it is RIP-relative, refuse.
            return true;
        }
        // REX prefix bytes are fine; plain registers/memory (mod=01/10) are fine.
    }
    return false;
}

void write_relay(std::uint8_t* dst, uintptr_t where)
{
    dst[0] = 0x48; dst[1] = 0xB8;              // mov rax, imm64
    std::memcpy(dst + 2, &where, sizeof(where));
    dst[10] = 0xFF; dst[11] = 0xE0;            // jmp rax
}

}  // namespace

bool detour_install(Detour* d, uintptr_t target, uintptr_t detour)
{
    if (!d || !target || !detour) {
        return false;
    }

    MEMORY_BASIC_INFORMATION mbi = {};
    if (VirtualQuery(reinterpret_cast<LPCVOID>(target), &mbi, sizeof(mbi)) == 0) {
        log::error("detour: VirtualQuery(%p) failed", (void*)target);
        return false;
    }
    const std::uint8_t* p = reinterpret_cast<const std::uint8_t*>(target);
    const bool executable =
        mbi.State == MEM_COMMIT &&
        (mbi.Protect &
         (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE |
          PAGE_EXECUTE_WRITECOPY)) != 0;
    if (!executable) {
        log::error("detour: target %p is not executable", (void*)target);
        return false;
    }
    // Make sure 12 bytes are readable without crossing into another region.
    const std::size_t room =
        mbi.RegionSize - (std::size_t)(target - (uintptr_t)mbi.BaseAddress);
    if (room < kRelayLen) {
        log::error("detour: %p is within %zu bytes of a region end",
                   (void*)target, room);
        return false;
    }

    if (unsafe_prologue(p, kRelayLen)) {
        log::error(
            "detour: %p prologue not relocatable (relative branch/RIP) - not hooked",
            (void*)target);
        return false;
    }

    // Trampoline: displaced bytes + relay back to target+len.
    std::uint8_t* tramp = static_cast<std::uint8_t*>(
        VirtualAlloc(nullptr, kRelayLen + kRelayLen, MEM_COMMIT | MEM_RESERVE,
                     PAGE_EXECUTE_READWRITE));
    if (!tramp) {
        log::error("detour: VirtualAlloc(trampoline) failed");
        return false;
    }
    std::memcpy(tramp, p, kRelayLen);
    write_relay(tramp + kRelayLen, target + kRelayLen);

    DWORD oldProtect = 0;
    if (!VirtualProtect(reinterpret_cast<LPVOID>(target), kRelayLen,
                        PAGE_EXECUTE_READWRITE, &oldProtect)) {
        VirtualFree(tramp, 0, MEM_RELEASE);
        log::error("detour: VirtualProtect(%p) failed", (void*)target);
        return false;
    }
    std::memcpy(d->original, p, kRelayLen);
    write_relay(const_cast<std::uint8_t*>(p), detour);
    VirtualProtect(reinterpret_cast<LPVOID>(target), kRelayLen, oldProtect,
                   &oldProtect);

    d->target = target;
    d->trampoline = reinterpret_cast<uintptr_t>(tramp);
    d->length = kRelayLen;
    d->active = true;
    return true;
}

void detour_remove(Detour* d)
{
    if (!d || !d->active) {
        return;
    }
    DWORD oldProtect = 0;
    if (VirtualProtect(reinterpret_cast<LPVOID>(d->target), d->length,
                       PAGE_EXECUTE_READWRITE, &oldProtect)) {
        std::memcpy(reinterpret_cast<void*>(d->target), d->original,
                    d->length);
        VirtualProtect(reinterpret_cast<LPVOID>(d->target), d->length,
                       oldProtect, &oldProtect);
    }
    if (d->trampoline) {
        VirtualFree(reinterpret_cast<LPVOID>(d->trampoline), 0, MEM_RELEASE);
    }
    d->active = false;
    d->trampoline = 0;
}

}  // namespace specter::overlay