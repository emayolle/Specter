// Specter.Internal — self-contained x86-64 inline-detour engine.
//
// WHY WE PORTED IT: Steam's overlay ships a complete inline-detour engine in
// GameOverlayRenderer64.dll, and the first attempt called it in-process by RVA.
// That fails in this game: Steam manual-maps the DLL but never runs its C++
// initialisers, so its hook map / trampoline set stay null and the first engine
// call faults inside a CRITICAL_SECTION (the freeze we diagnosed). See
// docs/STEAM_HOOK.md. So we ship the same design ourselves, in-process:
//
//   * a table-driven x86-64 instruction-length decoder. The 188-entry table is
//     embedded verbatim from the Steam DLL (platform/hook/detour_ld_table.h).
//   * a +/-2GB trampoline allocator (VirtualQuery scan near the target).
//   * a rel32/rel8 relocation pass; a rel8 `EB` branch is promoted to `E9`.
//   * an E9 patch at the target. The target always jumps to a *stub* inside the
//     trampoline (guaranteed within +/-2GB), and the stub reaches the hook with
//     an E9 or an FF25 absolute jump — so a far-away hook still works.
//
// install() overwrites five bytes at `target` and hands back `*out_orig`: a
// trampoline that runs the relocated prologue and jumps back into the function.
// Call it to reach the original code.
//
// Threading: install()/remove() take an internal lock. Patching a function other
// threads may be executing is inherently racy (Steam's engine has the same
// limitation); prefer installing while the target is quiescent.

#pragma once

namespace specter::overlay {
namespace detour {

// Inline-detour `target` to `hook`. On success `*out_orig` is a trampoline you
// call to run the original code. `name` is for logging only. Idempotent for the
// same target. Returns false (and logs why) on failure.
bool install(void* target, void* hook, void** out_orig, const char* name);

// Restore the original bytes of a function previously detoured by install().
bool remove(void* target);

// True when `target` is currently detoured by us.
bool is_installed(void* target);

}  // namespace detour
}  // namespace specter::overlay
