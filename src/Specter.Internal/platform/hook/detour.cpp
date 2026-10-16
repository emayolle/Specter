// Specter.Internal — self-contained inline-detour engine (implementation).
//
// Ported from Steam's overlay engine: same table-driven length decoder, same
// relocation rules, same E9-with-FF25-fallback strategy. See platform/hook/detour.h
// for context and docs/STEAM_HOOK.md for the original analysis.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "platform/hook/detour.h"
#include "platform/hook/detour_ld_table.h"
#include "platform/log.h"

namespace specter {
namespace hook {
namespace {

// The E9 we write needs a 5-byte window, so the prologue we relocate must be at
// least that long. We cap it so a pathological stream cannot run away.
constexpr std::uint32_t kMinPreamble = 5;
constexpr std::uint32_t kMaxPreamble = 48;
constexpr int kMaxInsns = 16;
constexpr int kMaxHooks = 32;

// ---- length decoder ------------------------------------------------------

// Exactly the algorithm of the Steam routine at RVA 0x93770: first entry whose
// 1..4-byte prefix matches wins; it reports the instruction length and the
// relocation kind (0 none, 1 rel32@1, 2 rel32@2, 3 rel32@3, 4 rel8 EB->E9).
// Longueur d'une instruction ModRM/SIB/disp, regles x86-64.
//
// `imm8` / `imm32` disent ce qui suit le operande. On ne devine JAMAIS : un
// appel qui ne sait pas rendre une longueur refuse, parce qu'une longueur
// fausse dans un trampoline, c'est un saut au milieu d'une instruction.
bool modrm_len(const std::uint8_t* p, bool imm8, bool imm32, std::uint32_t* out)
{
    const std::uint8_t modrm = p[1];
    const std::uint8_t mod = static_cast<std::uint8_t>(modrm >> 6);
    const std::uint8_t rm = static_cast<std::uint8_t>(modrm & 7);
    std::uint32_t n = 2;  // opcode + ModRM
    if (mod != 3 && rm == 4) {
        n += 1;  // SIB
    }
    if (mod == 0 && rm == 5) {
        n += 4;  // disp32
    } else if (mod == 1) {
        n += 1;  // disp8
    } else if (mod == 2) {
        n += 4;  // disp32
    }
    if (imm8) {
        n += 1;
    }
    if (imm32) {
        n += 4;
    }
    *out = n;
    return true;
}

// Le repli, pour ce que la table de Steam ne couvre pas.
//
// La table est un jeu de PREFIXES, pas un decodeur ModRM general : elle a une
// seule entree 0x83, `83 64 24 00` (cmp dword [rsp+0x24], imm8). Le
// compilateur de CE jeu ouvre une fonction par `83 f9 <imm8>` -- cmp ecx,
// imm8 -- et la table ne le sait pas. Resultat mesure :
//
//     detour: XSRGlobalManager::GetPerfDistance opcode @+0 (byte 83)
//             not in decoder table - refusing
//
// Ajouter l'entree qui manque ici ne ferait que deplacer le probleme a la
// fonction suivante. Donc on decode vraiment le ModRM, pour les familles dont
// la longueur est sans ambiguite, et on REFUSE tout le reste.
//
// Aucun de ces cas ne contient d immediat relatif : out_reloc reste 0, donc le
// trampoline les recopie telles quelles.
bool ld_decode_fallback(const std::uint8_t* op, std::uint32_t* out_len,
                      std::uint32_t* out_reloc)
{
    *out_reloc = 0;
    const std::uint8_t opc = op[0];
    std::uint32_t n = 0;
    switch (opc) {
    // ALU op r/m,r et r,r/m : pas d immediat
    case 0x00: case 0x01: case 0x02: case 0x03:
    case 0x08: case 0x09: case 0x0a: case 0x0b:
    case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x18: case 0x19: case 0x1a: case 0x1b:
    case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x28: case 0x29: case 0x2a: case 0x2b:
    case 0x30: case 0x31: case 0x32: case 0x33:
    case 0x38: case 0x39: case 0x3a: case 0x3b:
    // MOV, TEST, XCHG, LEA, POP r/m
    case 0x63: case 0x84: case 0x85: case 0x86: case 0x87:
    case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8d: case 0x8f:
    // NOP r/m, Prefetch
    case 0x0f:
        return false;  // deux octets : la table s'en charge
    // shifts par 1 et par CL
    case 0xd0: case 0xd1: case 0xd2: case 0xd3:
    // group 4 et 5
    case 0xfe: case 0xff:
        modrm_len(op, false, false, &n);
        *out_len = n;
        return true;
    // Jcc rel8 : 2 octets, et le trampoline les reecrit en forme longue. Le
    // second octet est un decalage, pas un ModRM : c'est pour ca que ca passe
    // par le repli et pas par modrm_len.
    case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
    case 0x76: case 0x77: case 0x78: case 0x79: case 0x7a: case 0x7b:
    case 0x7c: case 0x7d: case 0x7e: case 0x7f: {
        if (out_reloc == nullptr) {
            return false;
        }
        *out_len = 2;
        *out_reloc = 5;
        return true;
    }
    // immediat 8 bits
    case 0x6b: case 0x80: case 0x83: case 0xc0: case 0xc1:
        modrm_len(op, true, false, &n);
        *out_len = n;
        return true;
    // immediat 32 bits
    case 0x69: case 0x81: case 0xc7:
        modrm_len(op, false, true, &n);
        *out_len = n;
        return true;
    // group 3 : l'immediat n'existe que pour /0 et /1 (TEST)
    case 0xf6: case 0xf7: {
        const std::uint8_t reg = static_cast<std::uint8_t>((op[1] >> 3) & 7);
        const bool imm = (reg <= 1);
        const bool wide = (opc == 0xf7);
        modrm_len(op, imm && !wide, imm && wide, &n);
        *out_len = n;
        return true;
    }
    default:
        return false;
    }
}

bool ld_decode(const std::uint8_t* p, std::uint32_t* out_len,
               std::uint32_t* out_reloc)
{
    for (int e = 0; e < kLdCount; ++e) {
        const LdEntry& t = kLdTable[e];
        if (p[0] != t.prefix[0]) {
            continue;
        }
        if (t.complen >= 2 && p[1] != t.prefix[1]) {
            continue;
        }
        if (t.complen >= 3 && p[2] != t.prefix[2]) {
            continue;
        }
        if (t.complen >= 4 && p[3] != t.prefix[3]) {
            continue;
        }
        *out_len = t.len;
        *out_reloc = t.reloc;
        return true;
    }
    std::uint32_t n = 0;
    std::uint32_t reloc = 0;
    if (ld_decode_fallback(p, &n, &reloc) && n != 0) {
        *out_len = n;
        *out_reloc = reloc;
        return true;
    }
    return false;
}

// ---- jump emission -------------------------------------------------------

// Write at `dst` a branch to `to`. Returns the number of bytes written (5 for
// E9 rel32, 14 for FF25 + imm64). `dst` must have at least 14 spare bytes.
std::uint32_t emit_jump(std::uint8_t* dst, std::int64_t to)
{
    const std::int64_t rel = to - static_cast<std::int64_t>(
                                      reinterpret_cast<std::uintptr_t>(dst)) -
                             5;
    if (rel >= INT32_MIN && rel <= INT32_MAX) {
        dst[0] = 0xE9;
        const std::int32_t r = static_cast<std::int32_t>(rel);
        std::memcpy(dst + 1, &r, 4);
        return 5;
    }
    // FF 25 00 00 00 00 <imm64> : jmp qword ptr [rip+0]
    dst[0] = 0xFF;
    dst[1] = 0x25;
    const std::int32_t zero = 0;
    std::memcpy(dst + 2, &zero, 4);
    std::memcpy(dst + 6, &to, 8);
    return 14;
}

// ---- trampoline allocation ----------------------------------------------

// Allocate executable memory within +/-2GB of `target` (so the target's E9 can
// reach it). Tries a plain allocation first, then scans outward from the target
// for a free region.
void* alloc_near(void* target, std::size_t size)
{
    const std::uintptr_t t = reinterpret_cast<std::uintptr_t>(target);
    const std::int64_t limit = 0x7FF00000;  // stay safely inside +/-2GB
    const std::uintptr_t gran = 0x10000;

    {
        void* p = ::VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT,
                                 PAGE_EXECUTE_READWRITE);
        if (p) {
            const std::int64_t d =
                static_cast<std::int64_t>(
                    reinterpret_cast<std::uintptr_t>(p)) -
                static_cast<std::int64_t>(t);
            if (d > -limit && d < limit) {
                return p;
            }
            ::VirtualFree(p, 0, MEM_RELEASE);
        }
    }

    for (std::uintptr_t step = gran; step < static_cast<std::uintptr_t>(limit);
         step += gran) {
        for (int dir = 0; dir < 2; ++dir) {
            std::uintptr_t cand = dir ? (t + step) : (t - step);
            cand &= ~(gran - 1);
            if (cand < 0x10000) {
                continue;
            }
            const std::int64_t d = static_cast<std::int64_t>(cand) -
                                   static_cast<std::int64_t>(t);
            if (d <= -limit || d >= limit) {
                continue;
            }
            MEMORY_BASIC_INFORMATION mbi{};
            if (::VirtualQuery(reinterpret_cast<LPCVOID>(cand), &mbi,
                               sizeof(mbi)) == 0) {
                continue;
            }
            if (mbi.State != MEM_FREE) {
                continue;
            }
            void* p = ::VirtualAlloc(reinterpret_cast<LPVOID>(cand), size,
                                     MEM_RESERVE | MEM_COMMIT,
                                     PAGE_EXECUTE_READWRITE);
            if (p) {
                return p;
            }
        }
    }
    return nullptr;
}

// ---- trampoline build ----------------------------------------------------

struct Insn {
    std::uint32_t off;
    std::uint32_t len;
    std::uint32_t reloc;
};

// Build a trampoline for `target`. On success returns the trampoline base (the
// relocated original code, i.e. what callers use as "orig"), fills
// `*out_preamble` / `out_original` with the bytes consumed at the target and
// `*out_stub` with the address inside the trampoline the target must jump to.
std::uint8_t* build_trampoline(void* target, void* hook, const char* name,
                               std::uint32_t* out_preamble,
                               std::uint8_t* out_original, void** out_stub)
{
    const std::uint8_t* code = reinterpret_cast<const std::uint8_t*>(target);

    Insn insns[kMaxInsns];
    int n = 0;
    std::uint32_t off = 0;
    std::uint32_t copy_len = 0;
    while (off < kMinPreamble) {
        if (n >= kMaxInsns || off >= kMaxPreamble) {
            log::error("detour: %s prologue too long/odd", name);
            return nullptr;
        }
        std::uint32_t len = 0;
        std::uint32_t reloc = 0;
        if (!ld_decode(code + off, &len, &reloc) || len == 0) {
            // Les 8 octets du depart, parce que "byte 83" ne dit rien et
            // qu'il a fallu relire le desassemblage pour comprendre.
            char octets[32];
            std::snprintf(octets, sizeof(octets), "%02x %02x %02x %02x "
                                               "%02x %02x %02x %02x",
                          code[0], code[1], code[2], code[3], code[4], code[5],
                          code[6], code[7]);
            log::error("detour: %s opcode @+%u (byte %02x) not in decoder "
                       "table - refusing. depart : %s",
                       name, off, code[off], octets);
            return nullptr;
        }
        insns[n++] = {off, len, reloc};
        // reloc 4 : EB rel8 -> E9 rel32  (2 octets -> 5)
        // reloc 5 : Jcc rel8 -> 0F 8x rel32 (2 octets -> 6)
        copy_len += (reloc == 4) ? 5u : (reloc == 5 ? 6u : len);
        off += len;
    }
    const std::uint32_t preamble_len = off;

    const std::size_t tsize = copy_len + 14 + 14;
    std::uint8_t* tramp = reinterpret_cast<std::uint8_t*>(
        alloc_near(target, tsize));
    if (!tramp) {
        log::error("detour: %s no trampoline within +/-2GB", name);
        return nullptr;
    }

    // Relocate the prologue into the trampoline.
    std::uint32_t c = 0;
    for (int i = 0; i < n; ++i) {
        const Insn& in = insns[i];
        if (in.reloc == 4) {
            // EB rel8 -> E9 rel32 (the branch must keep its destination).
            const std::int8_t rel8 =
                static_cast<std::int8_t>(code[in.off + 1]);
            const std::int64_t dest = static_cast<std::int64_t>(
                                          reinterpret_cast<std::uintptr_t>(
                                              code + in.off + 2)) +
                                      rel8;
            const std::int64_t end = static_cast<std::int64_t>(
                reinterpret_cast<std::uintptr_t>(tramp + c + 5));
            const std::int64_t nr = dest - end;
            if (nr < INT32_MIN || nr > INT32_MAX) {
                ::VirtualFree(tramp, 0, MEM_RELEASE);
                log::error("detour: %s EB relocation out of range", name);
                return nullptr;
            }
            tramp[c] = 0xE9;
            const std::int32_t r = static_cast<std::int32_t>(nr);
            std::memcpy(tramp + c + 1, &r, 4);
            c += 5;
        } else if (in.reloc == 5) {
            // JCC REL8 -> FORME LONGUE.
            //
            // 7x rel8 devient 0F 8x rel32 : 2 octets remplaces par 6. Sans
            // ca, le trampoline recopierait les 2 octets et le saut porterait
            // sur l'adresse du patch, pas sur la destination d'origine.
            //
            // C'est le cas du jeu : GetPerfDistance commence par
            //     83 f9 0a   cmp ecx, 0x0a
            //     7e 27      jle +0x27
            // et la table de Steam n'a AUCUNE famille Jcc : elle a ete
            // relevee sur un overlay qui n'avait jamais rencontres ca.
            const std::uint8_t opc = code[in.off];
            const std::int8_t rel8 =
                static_cast<std::int8_t>(code[in.off + 1]);
            const std::int64_t dest = static_cast<std::int64_t>(
                                          reinterpret_cast<std::uintptr_t>(
                                              code + in.off + 2)) +
                                      rel8;
            const std::int64_t end = static_cast<std::int64_t>(
                reinterpret_cast<std::uintptr_t>(tramp + c + 6));
            const std::int64_t nr = dest - end;
            if (nr < INT32_MIN || nr > INT32_MAX) {
                ::VirtualFree(tramp, 0, MEM_RELEASE);
                log::error("detour: %s Jcc relocation out of range", name);
                return nullptr;
            }
            tramp[c] = 0x0F;
            tramp[c + 1] = static_cast<std::uint8_t>(0x80 | (opc & 0x0F));
            const std::int32_t r = static_cast<std::int32_t>(nr);
            std::memcpy(tramp + c + 2, &r, 4);
            c += 6;
        } else {
            std::memcpy(tramp + c, code + in.off, in.len);
            if (in.reloc >= 1 && in.reloc <= 3) {
                const std::uint32_t f = in.reloc;
                std::int32_t oldrel = 0;
                std::memcpy(&oldrel, tramp + c + f, 4);
                const std::int64_t dest = static_cast<std::int64_t>(
                                              reinterpret_cast<std::uintptr_t>(
                                                  code + in.off + in.len)) +
                                          oldrel;
                const std::int64_t end = static_cast<std::int64_t>(
                    reinterpret_cast<std::uintptr_t>(tramp + c + in.len));
                const std::int64_t nr = dest - end;
                if (nr < INT32_MIN || nr > INT32_MAX) {
                    ::VirtualFree(tramp, 0, MEM_RELEASE);
                    log::error("detour: %s rel32 relocation out of range",
                               name);
                    return nullptr;
                }
                const std::int32_t r = static_cast<std::int32_t>(nr);
                std::memcpy(tramp + c + f, &r, 4);
            }
            c += in.len;
        }
    }

    // Jump back to the first byte past the relocated prologue.
    c += emit_jump(tramp + c,
                   static_cast<std::int64_t>(reinterpret_cast<std::uintptr_t>(
                       code + preamble_len)));
    // Stub the target will jump to; it reaches the (possibly far) hook.
    std::uint8_t* stub = tramp + c;
    c += emit_jump(stub, static_cast<std::int64_t>(
                             reinterpret_cast<std::uintptr_t>(hook)));

    ::FlushInstructionCache(::GetCurrentProcess(), tramp, c);

    std::memcpy(out_original, code, preamble_len);
    *out_preamble = preamble_len;
    *out_stub = stub;
    return tramp;
}

bool patch_target(void* target, void* stub, std::uint32_t preamble_len,
                  const char* name)
{
    const std::int64_t rel =
        static_cast<std::int64_t>(reinterpret_cast<std::uintptr_t>(stub)) -
        (static_cast<std::int64_t>(reinterpret_cast<std::uintptr_t>(target)) +
         5);
    if (rel < INT32_MIN || rel > INT32_MAX) {
        log::error("detour: %s stub out of E9 range", name);
        return false;
    }
    std::uint8_t patch[5];
    patch[0] = 0xE9;
    const std::int32_t r = static_cast<std::int32_t>(rel);
    std::memcpy(patch + 1, &r, 4);

    DWORD old_prot = 0;
    if (!::VirtualProtect(target, preamble_len, PAGE_EXECUTE_READWRITE,
                          &old_prot)) {
        log::error("detour: %s VirtualProtect failed (%lu)", name,
                   ::GetLastError());
        return false;
    }
    std::memcpy(target, patch, 5);
    DWORD tmp = 0;
    ::VirtualProtect(target, preamble_len, old_prot, &tmp);
    ::FlushInstructionCache(::GetCurrentProcess(), target, 5);
    return true;
}

// ---- registry ------------------------------------------------------------

struct Hook {
    void* target = nullptr;
    void* tramp = nullptr;
    void* hook = nullptr;
    std::uint32_t preamble_len = 0;
    std::uint8_t original[kMaxPreamble] = {};
    bool used = false;
};

Hook g_hooks[kMaxHooks];
CRITICAL_SECTION g_lock;
bool g_lock_init = false;

void ensure_lock()
{
    if (!g_lock_init) {
        ::InitializeCriticalSection(&g_lock);
        g_lock_init = true;
    }
}

Hook* find(void* target)
{
    for (Hook& h : g_hooks) {
        if (h.used && h.target == target) {
            return &h;
        }
    }
    return nullptr;
}

}  // namespace

bool install(void* target, void* hook, void** out_orig, const char* name)
{
    if (out_orig) {
        *out_orig = nullptr;
    }
    if (!target || !hook) {
        log::error("detour: install('%s') with null %s", name ? name : "?",
                   !target ? "target" : "hook");
        return false;
    }

    ensure_lock();
    ::EnterCriticalSection(&g_lock);

    if (Hook* existing = find(target)) {
        ::LeaveCriticalSection(&g_lock);
        if (out_orig) {
            *out_orig = existing->tramp;
        }
        return true;
    }

    Hook* slot = nullptr;
    for (Hook& h : g_hooks) {
        if (!h.used) {
            slot = &h;
            break;
        }
    }
    if (!slot) {
        ::LeaveCriticalSection(&g_lock);
        log::error("detour: hook table full, cannot hook %s",
                   name ? name : "?");
        return false;
    }

    void* stub = nullptr;
    std::uint32_t preamble_len = 0;
    std::uint8_t original[kMaxPreamble];
    std::uint8_t* tramp =
        build_trampoline(target, hook, name ? name : "?", &preamble_len,
                         original, &stub);
    if (!tramp) {
        ::LeaveCriticalSection(&g_lock);
        return false;
    }

    // Publish the trampoline BEFORE patching the target: the instant
    // patch_target() succeeds the hook becomes reachable from other threads, and
    // those threads immediately read *out_orig. Publishing it afterwards would
    // leave a window where the hook calls a null trampoline.
    slot->target = target;
    slot->tramp = tramp;
    slot->hook = hook;
    slot->preamble_len = preamble_len;
    std::memcpy(slot->original, original, preamble_len);
    slot->used = true;
    if (out_orig) {
        *out_orig = tramp;
    }

    if (!patch_target(target, stub, preamble_len, name ? name : "?")) {
        slot->used = false;
        if (out_orig) {
            *out_orig = nullptr;
        }
        ::VirtualFree(tramp, 0, MEM_RELEASE);
        ::LeaveCriticalSection(&g_lock);
        return false;
    }

    ::LeaveCriticalSection(&g_lock);

    log::info("detour: %s hooked @%p -> %p (orig=%p preamble=%u)", name,
              target, hook, tramp, preamble_len);
    return true;
}

bool remove(void* target)
{
    if (!target) {
        return false;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);

    Hook* h = find(target);
    if (!h) {
        ::LeaveCriticalSection(&g_lock);
        return false;
    }

    DWORD old_prot = 0;
    if (::VirtualProtect(target, h->preamble_len, PAGE_EXECUTE_READWRITE,
                         &old_prot)) {
        std::memcpy(target, h->original, h->preamble_len);
        DWORD tmp = 0;
        ::VirtualProtect(target, h->preamble_len, old_prot, &tmp);
        ::FlushInstructionCache(::GetCurrentProcess(), target,
                                h->preamble_len);
    }
    void* tramp = h->tramp;
    h->used = false;

    ::LeaveCriticalSection(&g_lock);

    // Keep the trampoline mapped: a thread may still be inside it. It is one
    // small page leaked per unhook, which is the safe trade.
    (void)tramp;
    log::info("detour: unhooked %p", target);
    return true;
}

bool is_installed(void* target)
{
    if (!target) {
        return false;
    }
    ensure_lock();
    ::EnterCriticalSection(&g_lock);
    const bool r = find(target) != nullptr;
    ::LeaveCriticalSection(&g_lock);
    return r;
}

}  // namespace detour
}  // namespace specter::dxgi
