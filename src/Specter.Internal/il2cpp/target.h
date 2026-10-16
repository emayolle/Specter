// Specter.Internal — everything specific to this build of Aniimo.
//
// WHY this file exists: a patch of code is only as good as the number it reads.
// Those numbers were scattered across modules — the field offsets in lua/pump,
// an RVA in a comment in features/lua_dump — so a game update meant finding
// them by grep and hoping nobody missed one.
//
// They all live here now. One file to re-check when the game updates, and one
// place to look when a patch stops working.
//
// WHAT BELONGS HERE: a value that encodes a fact about the game binary —
// a field offset, a method RVA, a field index, a vtable slot.
//
// WHAT DOES NOT: anything about how we patch (that is platform/hook/detour's
// algorithm) or anything about the game's behaviour. A mask or a granularity
// is ours, not the game's, and belongs where it is used.
//
// All offsets are for the IL2CPP metadata of the shipped build and were taken
// from generated/dump + generated/sdk/appdata. Re-verify them with
// tools/dump.sh after a game update.

#pragma once

#include <cstddef>
#include <cstdint>

namespace specter::target {

// ---- IL2CPP field offsets --------------------------------------------------
//
// How the game's lua_State is reached, the documented xLua way: the IL2CPP
// LuaManager holds a LuaEnv, and that LuaEnv holds the raw lua_State*.

// LuaManager::luaenv
constexpr std::size_t kLuaManager_luaenv = 0x18;

// LuaEnv::rawL
constexpr std::size_t kLuaEnv_rawL = 0x10;

// ---- method RVAs (from GameAssembly.dll's base) ----------------------------

// LuaManager.CommonUpdate — per-frame, on the main thread. The one method the
// pump detours to get onto the game's Lua thread.
constexpr std::uintptr_t kCommonUpdateRva = 0x172ADC0;

// XLua::LuaDLL::Lua::xluaL_loadbuffer — the IL2CPP P/Invoke wrapper the game
// uses to hand a chunk to LuaJIT. Hooked by features/lua_dump to capture the
// shipped bytecode. It marshals `name` and then calls the xlua.dll export.
constexpr std::uintptr_t kXluaLoadBufferRva = 0x879010;

}  // namespace specter::target
