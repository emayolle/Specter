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

// XSRGlobalManager::GetPerfDistance(int perfLevel) -> int
//
// Le NIVEAU DE PORTEE / DETAIL du streaming. PAS un rayon, et pas convertible
// en metres : le consommateur, XSRBlockTile::CalcThisTileLodLevel, fait
//
//     d = max(|tile.X - agent.X|, |tile.Z - agent.Z|)   // en TUILES
//     if (d > 12) return 12;                             // plafond du moteur
//
// et la valeur sert a choisir jusqu'a quel niveau on charge. Decompile ici :
//
//     if ( perfLevel <= 10 ) return 3;
//     if ( perfLevel <= 30 ) return 4;
//     if ( perfLevel <= 50 ) return 5;
//     result = 6;
//     if ( perfLevel >  70 ) return 12;
//     return result;
//
// perfLevel vient de SetPerformanceLevel : un int statique clampe dans [0, 100].
//
// 12 EST LE MAXIMUM, ET C'EST LE MOTEUR QUI L'IMPOSE. Le jeu ne produit que
// 3, 4, 5, 6 ou 12 ; au-dela, CalcThisTileLodLevel ecrase. Un curseur qui
// irait plus loin serait du theatre.
//
// CE QUE CA CHARGE : des blocs de terrain et leur niveau de detail. Les
// ENTITES viennent du serveur -- donc plus de valeur ne garantit aucun coffre
// de plus, ca coute des FPS. C'est une variable et pas une constante, pour
// que la question se tranche en comptant.
constexpr std::uintptr_t kGetPerfDistanceRva = 0x184D5F0;

// XSRBlockTile::CalcThisTileLodLevel(int agentTileX, int agentTileZ) -> int
//
// Le second plafond, et le plus dur : celui qui borne la distance elle-meme.
//
//   0x...7db  mov  ecx, 0Ch      <- l'immediat "12"
//   0x...7e5  cmp  eax, ecx
//   0x...7e7  cmovg eax, ecx
//   0x...7ea  retn
//
// L'octet du plafond est donc a RVA 0x18457DC, soit fonction + 0x2C. C'est le
// SEUL endroit a ecrire pour lever la limite, et un octet se remet en ecrivant
// 0x0C.
//
// On patche l'octet plutot que de reecrire la fonction : on garde le code du
// jeu, donc on ne peut pas se tromper sur le max(|dx|,|dz|) ni sur les branches
// cmovs, et le retour a l'original est immediat.
constexpr std::uintptr_t kCalcThisTileLodLevelRva = 0x18457B0;
constexpr std::uintptr_t kLodCapOffset = 0x2C;
constexpr uint8_t kLodCapOriginal = 12;

}  // namespace specter::target