# Steam overlay hook engine (`GameOverlayRenderer64.dll`)

> **Note** : l'arborescence décrite ici est celle de la base `2572297`.
> Le code vit maintenant dans `platform/hook/detour.*` — voir `docs/ARCHITECTURE.md` §2.


Specter **ported** Steam's inline-detour engine instead of shipping its own.
Steam injects `GameOverlayRenderer64.dll` into the game process (also under
Proton/Wine), and that DLL contains a complete, well-tested x86-64 detour
engine: a table-driven length decoder, a ±2 GB trampoline allocator and a
relocation pass. We reused its design (and its 188-entry decode table verbatim)
in `overlay/detour.*`; see "Outcome" below for why calling it by RVA did not
work.

Analysis document for the original design. Reused table:
`src/Specter.Internal/overlay/detour_ld_table.h` (generated).

## Target image

| | |
|---|---|
| Module | `GameOverlayRenderer64.dll` |
| MD5 | `3b89b24723a8f7b82490da1346c31c6b` |
| Image base (file) | `0x180000000` |
| Runtime base | wherever Wine mapped it (`GetModuleHandleW`) |

At runtime `address = module_base + rva`.

## Public entry points (what we call)

| Function | RVA | Signature |
|---|---|---|
| `HookFunc` | `0x8DAB0` | `bool(void* target, void* hook, void** out_orig, int follow_jmps, const char* name)` |
| `UnhookFunc` | `0x8E2F0` | `void(void* target, int verbose)` |
| `IsHooked` | `0x8E980` | `bool(void* target)` |

`out_orig` receives a **trampoline**: the original prologue relocated into fresh
memory (within ±2 GB) followed by a jump back into the function. Calling it runs
the untampered code. `follow_jmps` asks the engine to follow that many leading
`E9`/`EB`/`FF25` jumps before it starts decoding (Steam's own call sites pass
`1`; for a plain fresh hook we pass `0`).

Prologue fingerprints used to validate the build (first 16 bytes at each RVA):

```
HookFunc   48 89 5C 24 08 57 48 83 EC 30 33 C0 48 89 44 24
UnhookFunc 48 8B C4 53 55 56 57 41 54 41 56 41 57 48 81 EC
IsHooked   40 53 55 56 57 48 83 EC 58 48 8B EA 48 8B D9 48
```

If any differs we refuse to hook (a Steam update moved the RVAs) instead of
jumping into garbage.

## Internal engine (for reference)

| Piece | RVA |
|---|---|
| core install routine | `0x8CF00` |
| trampoline allocator | `0x8C610` |
| near (±2 GB) slot allocator | `0x8CE40` |
| page size | `0x8CE00` |
| length decoder | `0x93770` |
| decoder table | `0x11F5B0` |

Decoder table: **188 entries × 16 bytes**. Layout:

```
[0..3]  match prefix bytes
[4]     instruction length (bytes to consume)
[8..11] prefix length to compare
[12..15] relocation kind:
          0 = none
          1 = 4-byte rel32 at instruction offset 1
          2 = 4-byte rel32 at instruction offset 2
          3 = 4-byte rel32 at instruction offset 3
          4 = EB rel8 (needs expansion to E9 rel32)
```

Kind counts: `0`×173, `1`×2, `2`×3, `3`×9, `4`×1.

Algorithm (as recovered):

1. Unwrap any leading jump chain (respecting `follow_jmps`).
2. Refuse if the target is already inside an executable page it cannot own.
3. Decode whole instructions until ≥ 5 bytes are covered.
4. Allocate a trampoline within ±2 GB and copy the decoded bytes.
5. Second pass: relocate each relative field — `new_rel = orig_base + rel_old −
   tramp_base` (the instruction offset cancels). `EB rel8` is expanded to
   `E9 rel32` (field set to `rel8 − 3`, then relocated).
6. Append a jump back to `target + decoded_len` (`E9` if the rel32 fits,
   otherwise `FF 25` + an 8-byte absolute address).
7. Patch the target with an `E9 rel32` (or `FF 25` fallback) via
   `VirtualProtect` (page-straddle aware) + `WriteProcessMemory` +
   `FlushInstructionCache`.
8. Record the hook in a `std::map` (`qword_1801671D8`); trampolines live in a
   list at `xmmword_180167228`.

## Caveat: Steam's own hooks

Steam's overlay **already detours** the user32 input/cursor functions it needs
(`GetRawInputData`, `GetRawInputBuffer`, `GetAsyncKeyState`, `GetKeyState`,
`GetKeyboardState`, `ClipCursor`, `GetClipCursor`, `ShowCursor`, `SetCursor`,
`SetCursorPos`, `GetCursorPos`, `GetCursor`, `DispatchMessageA/W`,
`GetMessageA/W`, `PeekMessageA/W`, `SetCapture`, `ReleaseCapture`,
`RegisterDeviceNotification`, …) to save/restore the cursor, clip region and
raw-input registrations, and it hooks D3D9 device functions.

`HookFunc` calls `UnhookFunc(target)` on the same address **before** installing,
so hooking a target Steam already owns **replaces** Steam's hook — it does not
chain. Because both sides use the *same* registry map, the first installer wins.

## Outcome: we do NOT call Steam's engine at runtime (it is dormant)

The plan of calling the resident engine by RVA was tried and **abandoned**: Steam
manual-maps `GameOverlayRenderer64.dll` but never calls its exported
`DllEntryPoint`, so the C++ initialisers that build the hook map
(`base+0x1671D8`, set by `sub_180039F70`) and the trampoline set
(`base+0x167258`, set by `sub_180039F30`) never run. We confirmed this live with
`/proc/<pid>/mem`: both heads stay `0` and the engine's `CRITICAL_SECTION`
(`base+0x1671F8`) is all-zero for the whole session. The first engine call
therefore dereferenced a null map head inside a held `CRITICAL_SECTION`, faulted,
and wedged the calling thread — the game freeze we diagnosed. The overlay can
still be *shown* with Shift+Tab (Steam initialises it lazily for its own UI), but
we cannot rely on that for our gate.

## Specter usage: we ported the engine

* `overlay/detour.*` — our own inline-detour engine, a faithful port of the Steam
  design: the table-driven length decoder (the 188-entry table is embedded
  verbatim in `overlay/detour_ld_table.h`, extracted from the DLL at RVA
  `0x11F5B0`), a ±2 GB trampoline allocator, the rel32/rel8 relocation pass
  (`EB` → `E9` promotion) and the `E9`-with-`FF25`-fallback patch. The target
  always jumps to a *stub* inside the in-range trampoline, and the stub reaches a
  far-away hook with an absolute `FF25` jump.
* `overlay/game_input.*` — hooks seven user32 exports so the ImGui menu can free
  the OS cursor and starve the game of input. Our own overlay code reads the real
  key state through `game_input::real_async_key_state()` (the trampoline) so the
  toggle keeps working while the gate is armed.
* The imported DLL set is unchanged by all of this — we resolve `user32`
  exports with `GetProcAddress`, so no new IAT entry appears (see `ANTICHEAT.md`).

### Why the port decodes Wine's user32

Wine exports user32 functions as *universal thunks*, which is why the Steam table
covers them unchanged:

| target (prologue)                  | decoder entry | preamble | reloc |
|------------------------------------|---------------|----------|-------|
| `GetRawInputData`/`Buffer` `FF 25` | #177          | 6        | rel32@2 |
| `GetAsyncKeyState`/`GetKeyState`/`ClipCursor`/`ShowCursor`/`SetCursor`/`GetKeyboardState`/`SetCursorPos` `48 8D A4 24 …` | #96 | 8 | none |
| `GetCursorPos` `48 FF 25 …`        | #?            | 8        | – |
| `GetPhysicalCursorPos` `E9 rel32`  | #166          | 5        | rel32@1 |

(Verified by reading the prologues out of the on-disk `user32.dll` and running
the exact Steam decode loop over them.)

