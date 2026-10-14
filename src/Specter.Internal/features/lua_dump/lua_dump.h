// Specter.Internal — runtime dumper for the game's Lua chunks.
//
// WHY: the shipped scripts are not source. `Aniimo_Data/cvs/res/lua/LuaScripts.xdf`
// is a stored (uncompressed) zip whose members are *LuaJIT 2.1 bytecode*, not
// text: every file starts with the LuaJIT header `1B 4C 4A` + version + flags +
// the original Perforce chunkname (`@C:\dev\jkroot\ws\workspace\XWinPublish\...`).
// That is readable with `luajit -bl`, but only if you already have the pack --
// and it says nothing about chunks delivered by XPatch at runtime, nor about
// anything that changes without a Steam update.
//
// So we tap the entry point the game itself uses. The IL2CPP P/Invoke wrapper
// `XLua::LuaDLL::Lua::xluaL_loadbuffer(IntPtr L, Byte[] buff, int size, String
// name)` (GameAssembly RVA 0x879010) does no transformation of its own: it
// marshals `name`, then calls `xluaL_loadbuffer(L, buff->vector, size, name)`.
// xlua.dll exports that symbol (515 exports, `luaJIT_version_2_1_0_beta3`), so we
// can detour it directly -- no export-table walking needed.
//
// The bytes we capture are therefore byte-identical to what LuaJIT compiles:
// exactly what `luajit -bl` wants, and exactly what a LuaJIT decompiler wants.
//
// OUTPUT: `Z:\tmp\specter-lua-dump\` -- i.e. /tmp/specter-lua-dump on the host.
// Deliberately *outside* the game directory and the wine prefix, per the same
// rule the log pipe and the CLI channel already follow (entry.cpp): under
// Wine/Proton Z: is the Linux root, and anything written into the prefix or the
// install dir is a file an integrity check could see.
//
// ARMING: install() always puts the detour in place (early, so nothing loaded
// before we attach is missed), but dumping is gated by set_enabled(). Writing
// ~8.6k files during boot is a lot of I/O on the game's Lua thread for something
// that is a research tool, not a gameplay feature.

#pragma once

namespace specter::features {
namespace lua_dump {

// Resolve xlua.dll and detour xluaL_loadbuffer. Idempotent. Returns false only
// if the detour itself failed; a missing xlua.dll is not fatal here because the
// Lua bridge retries from tick().
bool install();

// Retry install() until it succeeds. Called from the CommonUpdate pump, for the
// same reason resolve_xlua() is: xlua.dll may not be mapped yet when we attach.
void tick();

// Arm / disarm the actual file writes. Default: disarmed.
void set_enabled(bool on);
bool enabled();

// Number of chunks written since attach (statistics for the UI / log).
unsigned long long dumped();

// Suppress dumping for chunks that *we* inject. The console pushes a chunk
// through luaL_loadbuffer too; that one is ours, not the game's, and must not
// land in the dump.
//
// The Lua pump consults this through set_chunk_filter() rather than calling in
// here, so the dependency stays feature -> lua and `lua/` never has to know that
// a feature exists. Matching is by chunk name.
bool filter(const char* chunk_name);

// RAII scope for the counter, for a caller that is not the pump.
void push_suppress();
void pop_suppress();

struct Suppress {
    Suppress() { push_suppress(); }
    ~Suppress() { pop_suppress(); }
    Suppress(const Suppress&) = delete;
    Suppress& operator=(const Suppress&) = delete;
};

}  // namespace lua_dump
}  // namespace specter::features