# Shinoko-Aniimo.dll — Reverse-Engineering Report

Annotated IDA database: **`/tmp/opencode/shinoko-re/Shinoko-Aniimo.dll.i64`** (saved).
Raw working copy: `/tmp/opencode/shinoko-re/Shinoko-Aniimo.dll`.
Original (untouched): `/home/cozlex/Downloads/Global/Shinoko-Aniimo.dll[.i64]`.

## 1. Binary metadata

| | |
|---|---|
| File | `Shinoko-Aniimo.dll` |
| Type | PE64 (AMD64), DLL |
| Image base | `0x180000000` |
| Segments | 9 (`.text`, `.rdata`, `.data`, `.pdata`, `.detourc`, `.detourd`, `.detour`, `.fptable`, …) |
| Functions | 1 728 |
| MD5 | `f48bfb09debe87275b6bd307ef525535` |
| SHA-256 | `964623462dcb872341375851428c2030b3005e7365ac74b037f6bd0d7b63c47e` |
| Game target | *Aniimo* 1.0.3535596.0 (non-Steam, DirectX 11) |
| Mod | "Shinoko" v0.1.0 — ImGui 1.92.4 overlay |

Only 6 static imports; everything else (`D3D11CreateDeviceAndSwapChain`, `GetProcAddress`, `LoadLibraryA`, CRT, …) is resolved at runtime.

## 2. High-level architecture

```
DllMain ──> CreateThread(MainThread)
MainThread:
    wait for GameAssembly.dll
    SetupGameHooks()   -> hook xlua.dll!xluaL_loadbuffer     -> Hooked_xluaL_loadbuffer
                       -> hook GameAssembly+0x5C6A80
                          (GameManager::CommonUpdate)        -> Hooked_GameManager_CommonUpdate
    SetupRenderHooks() -> hidden window + D3D11 device
                       -> hook IDXGISwapChain::Present       -> Hooked_IDXGISwapChain_Present
    wait VK_END -> teardown / unload
```

`Hooked_IDXGISwapChain_Present` initialises the ImGui D3D11/Win32 backends and, each frame, calls
`OnFrameTick` (DS `0x18002E1D0`) which does gameplay work, then draws the module list + the selected
module UI.

### The core trick: a Lua bridge
The mod does **not** patch game code for most features. Instead it:

1. Captures the game's xLua state in `Hooked_xluaL_loadbuffer` → `g_pLuaState`.
2. Builds a **Lua script** in C++ and pushes it with `EnqueueLuaScript`.
3. On every `GameManager::CommonUpdate`, `Hooked_GameManager_CommonUpdate` drains the queue and runs
   each script inside the game VM.

So every "cheat" is a Lua script that calls the game's own Lua API
(`pg`, `Utils.checkRelation`, `pg.global.entityMgr`, `ActorCombatAttribute`, `CombatActionTool`,
`Common.ClientSwitch`, `Utils.GmToolUtils`, …). This is why there is almost no game-offset math in the DLL.

## 3. String obfuscation (fully reversed)

All Lua scripts and API name strings are stored encrypted. Each decryptor:

* copies a 512-byte substitution table from `.rdata`,
* seeds a 32-bit LCG (seed `mov esi, imm`),
* per byte: `k = (state>>16)&0xFF`; `state = state*1664525+1013904223`;
  `idx = (ror8(k ^ key[i], k&7) - (i^0xAA)) & 0xFF`; `out[i] = table[256+idx]`.

Opaque predicates built on `__rdtsc()` (`0xCAFEBABE`, `0xDEADBEEF`, `0xDEADC0DE`, `0x56292D37`) are
always constant. I reimplemented the cipher and **decrypted all 93 encrypted strings** — the complete
Lua cheat logic. Raw output: `decoded_lua_bundle.txt` and `lua/<ea>.lua`.

## 4. Module system

`ModuleRegistry_Register(prefix, name, feature-list, order)` builds a `ModuleEntry` (0x40 bytes) and
inserts it into `std::vector<ModuleEntry>`. `RenderModuleList` draws the tab bar and, for the selected
module, walks a nested list of feature objects and calls their virtual `render` (vtable+16).

| Order | Module | Register fn | UI render fn |
|---|---|---|---|
| 100 | Player | `0x180001020` | `PlayerModule_Render` `0x180012FD0` |
| 90 | ESP | `0x1800011E0` | `ESPModule_Render` `0x180024E80` |
| 80 | Misc | `0x180001100` | `MiscModule_Render` `0x180017E80` |
| 70 | GM | `0x1800012D0` | `GMModule_Render` `0x180028550` |
| 60 | Lua Executor | `0x180001420` | `LuaModule_Render` `0x18002CB40` |

Structs created in the IDB: `ModuleEntry` (0x40) and `FeatureItem` (0x40).

## 5. Features → config globals → Lua template

| Feature | Toggle global | Apply fn | Lua template |
|---|---|---|---|
| God Mode | `g_bGodMode` `0x1800FABEA` | (Lua patch CombatCore) | `LuaStr_Patch_CombatCore` `0x180009000` |
| One Hit Kill | `g_bOneHitKill` `0x1800FAC14` | `ApplyOneHitKill` `0x18000FFD0` | `LuaStr_OneHitKill` `0x180010710` |
| Kill Aura (+radius/interval) | `g_bKillAura` `0x1800FABF2` | `ApplyKillAura` `0x18000CEA0` | `LuaStr_KillAura` `0x18000E2D0` |
| Catch Aura | `g_bCatchAura` `0x1800FABFC` | `ApplyCatchAura` `0x18000E740` | `LuaStr_CatchAura` `0x18000FB60` |
| Auto Loot | `g_bAutoLoot` `0x1800FAC08` | `ApplyAutoLoot` `0x180011730` | `LuaStr_AutoLoot` `0x180012B60` |
| Unlimited Dash | `g_bUnlimitedDash` `0x1800FAC15` | `ApplyUnlimitedDash` `0x180010B80` | `LuaStr_UnlimitedDash` `0x1800112C0` |
| Multi-Hit (+mult) | `g_bMultiHit` `0x1800FABEB` | `ApplyMultiHit` `0x1800098E0` | `LuaStr_MultiHit` `0x18000A660` |
| No Fall Damage | `g_bNoFallDamage` `0x1800FABE8` | (patch) | `…NoFallDamage_Enable/Disable` |
| No Cooldown (full/player/pet) | `g_bNoCooldown`/`Player`/`Pet` | `ApplyNoCooldown` `0x18000BCB0` | `LuaStr_NoCooldown` `0x18000C160` |
| Infinite Stamina | `g_bInfiniteStamina` `0x1800FABF0` | (patch) | `LuaStr_InfStamina` `0x18000AF50` |
| Infinite Energy (EP+SP) | `g_bInfiniteEnergy` `0x1800FABF1` | (patch) | `LuaStr_InfEnergy` `0x18000B840` |
| Dumb Enemy | `g_bDumbEnemy` `0x1800FABE9` | (patch AiConst) | `…DumbEnemy_Enable/Disable` |
| Mob Vacuum | `g_bMobVacuum` `0x1800FABDC` | `MobVacuum_Pull` `0x1800048E0` | `LuaStr_FindNearestEnemies` `0x180005340` |
| Packet Rate-Limit Bypass | `g_bPacketRateLimitBypass` `0x1800FAC16` | `ApplyRateLimitBypass` `0x180016B50` | `LuaStr_RateLimitBypass_*` |
| Scene Teleport | — | — | `LuaStr_SceneTeleport_Prefix/Suffix` |
| Global Speed Multiplier | `g_bGlobalSpeedEnabled` `0x1800FABBD` | `Game_ApplySpeedMultiplier` | native |
| Camera FOV override | `g_bFovOverride` `0x1800FABC4` | `Game_SetCameraFOV` | native |
| Free Camera | `g_bFreeCamera` `0x1800FAC34` | — | `LuaStr_FreeCam_Enable/Disable` |
| Player / Aniimo model scale | `g_bPlayerModelScale` / `g_bAniimoModelScale` | `Apply*ModelScale` | `LuaStr_Set*ModelScale` |
| Custom tips (warning/input/confirm/marquee/msg/bubble/effect) | `g_bTip*` `0x18001xxxx` | — | `LuaStr_Tip_*`, `LuaStr_Effect_*` |
| ESP (players/npc/pets/loot/objects, box/lines/name/distance, colors) | `g_bEsp*` `0x1800FAB38…` | native draw `ESP_Draw` | — |
| GM Tools (Console/Hierarchy/Inspector/AI Debug/Ability Inspect) | — | `GM_*` `0x180025D80…` | `LuaStr_GmCmd_*` |
| Lua Script Editor/Executor | `g_bLuaAutoScroll` | `LuaModule_Render` | user input |

Full global list: `label_global.txt`. Full function list: `final_names.txt`.

## 6. What was annotated in the IDB

* **~180 functions renamed** (core/entry/hooks, module registry & registration, all 5 module UIs, all
  feature apply functions, GM handlers, 93 Lua-string decryptors, UI wrappers, identified ImGui APIs,
  runtime helpers: `operator_new/delete`, `memmove/memset/strlen`, `std::to_string`, `WndProc`, …).
* **~81 global variables renamed** (config flags/sliders, Lua state + queue, hook-installed flags, ImGui hash table).
* **2 structs created**: `ModuleEntry` (0x40), `FeatureItem` (0x40).
* **46 function comments** describing architecture and each feature.
* Database saved in place.

## 7. Key addresses (imagebase 0x180000000)

| Name | Address |
|---|---|
| DllMain | `0x180002920` |
| MainThread | `0x180001510` |
| OnFrameTick | `0x18002E1D0` |
| RenderModuleList | `0x18002DF80` |
| Hooked_IDXGISwapChain_Present | `0x1800314D0` |
| Hooked_xluaL_loadbuffer | `0x180029960` |
| Hooked_GameManager_CommonUpdate | `0x180029AB0` |
| EnqueueLuaScript | `0x18002C7A0` |
| ModuleRegistry_Register / GetList | `0x180003EE0` / `0x180003E20` |
| g_pLuaState | `0x18010C5A0` |
| GameManager::CommonUpdate RVA | GameAssembly + `0x5C6A80` (6056448) |

## 8. Coverage / limitations

* All application-layer code (mod logic) is named and documented; the Lua cheat bodies are recovered in full.
* The statically-linked **ImGui 1.92.4 core** (≈0x180036000–0x180090000, ~900 functions) is stock
  library code; only the functions referenced by the mod (Begin/End/Checkbox/Button/Text/InputInt/
  SliderFloat/SliderInt/PopStyleVar/CreateContext/…) plus the Win32 backend (`ImGui_ImplWin32_WndProcHandler`)
  were named. The remainder keep `sub_*` names.
* Detours/CRT helper region (0x180090000+) is only partially named (`Detour_AttachHook/Detour_DetachHook`,
  `operator_new/delete`, mem/str helpers).
* Feature semantics are derived from the decoded Lua and UI labels, not from live execution.
