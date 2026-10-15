// Specter.Internal — the ONE place the Lua headers are included.
//
// Everything else includes this file, never lua.h directly. There are two
// reasons, and the first one is a trap that only shows up in the game.
//
// 1. extern "C" is not optional.
//
//    LuaJIT's luaconf.h declares the public API with LUA_API, which handles
//    __declspec and visibility — and nothing else. There is no extern "C"
//    block anywhere in lua.h. So when these headers are compiled as C++, every
//    lua_* call gets C++ linkage, and the symbol comes out mangled:
//
//        _Z10lua_concatP9lua_Statei     instead of     lua_concat
//
//    Not one of those resolves against xlua.dll's C exports. Nothing warns, the
//    link is fine on our side because nothing defines them, and the failure
//    appears at RUNTIME, in the game, on the first call — as a jump through a
//    null pointer.
//
//    Measured, on the exact registration paths Specter uses: with the wrapper,
//    42 symbols are emitted as plain C names. Without it, 42 mangled names, 0
//    resolvable. The reference project gets this right by wrapping the headers
//    itself; see third_party/luabridge for the note.
//
// 2. One include point means one place to check, and the typedefs in pump.cpp
//    used to be written by hand against a `using lua_State = void`. A signature
//    written by hand is a signature that can be wrong without the compiler
//    noticing. Three of this project's deaths came from that class.
//
// LuaBridge.h enforces the order itself — Config.h raises "#error Lua headers
// must be included prior to LuaBridge ones" — which is why lua.h comes first
// inside the wrapper.
#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

// LuaBridge.h is NOT included here, on purpose.
//
// LuaBridge calls the C API by name, and the names have to be redirected to the
// pointers this module resolves. That redirection is `#define lua_gettop
// capi::p_lua_gettop`, and it has to be in effect BEFORE LuaBridge's headers are
// read — so the two includes cannot live in one file.
//
// lua/bridge.h is the translation unit's way in: it pulls this file in, defines
// the redirects, then includes LuaBridge.h. Nobody includes LuaBridge.h without
// going through it.

namespace specter::lua::capi {

// Every symbol LuaBridge3 can reach on the 5.1 ABI.
//
// MEASURED, not guessed: the list is `nm -u` over an object that instantiates
// exactly the registration paths Specter uses (see tests/lua_binding). Adding a
// LuaBridge feature that reaches one more function makes THAT one fail to link
// in capi.cpp — a build error, visible now, rather than a null pointer called
// in the game.
//
// The pointers are declared HERE and defined in capi.cpp: bridge.h's redirect
// macros name them from another translation unit.
//
// NOT extern "C". That would give them the C name `lua_gettop`, which is the
// name of the real function xlua.dll exports — two symbols with one name, and
// the linker picks one without saying which. Plain C++ linkage keeps them
// distinct.
// Full names, `lua_call` and `luaL_checkstack` alike: a macro that adds the
// prefix cannot serve both families without inventing `lua_L_checkstack`.
//
// `lua_getglobal` is deliberately NOT here: it is not a function but a macro in
// lua.h, so it has no address to take. The macro expands to lua_getfield with
// LUA_GLOBALSINDEX, and the shim provides that one.
#define CAPI_SYMBOLS(X)                                                        \
    X(lua_call) X(lua_checkstack) X(lua_concat) X(lua_createtable)            \
    X(lua_error)                                                                     \
    X(lua_getinfo) X(lua_getmetatable) X(lua_getstack) X(lua_gettop)          \
    X(lua_gettable) X(lua_settable) X(lua_getfield) X(lua_setfield)          \
    X(lua_insert) X(lua_iscfunction) X(lua_isnumber) X(lua_isuserdata)        \
    X(lua_newuserdata) X(lua_objlen) X(lua_pushboolean) X(lua_pushcclosure)   \
    X(lua_pushfstring) X(lua_pushinteger) X(lua_pushlightuserdata)            \
    X(lua_pushlstring) X(lua_pushnil) X(lua_pushnumber) X(lua_pushstring)     \
    X(lua_pushvfstring) X(lua_pushvalue) X(lua_rawget) X(lua_rawgeti)         \
    X(lua_rawset) X(lua_remove) X(lua_replace) X(lua_setmetatable)           \
    X(lua_settop) X(lua_toboolean) X(lua_tointeger) X(lua_tolstring)          \
    X(lua_tonumber) X(lua_topointer) X(lua_touserdata) X(lua_type)            \
    X(luaL_checkstack) X(luaL_unref)

#define CAPI_DECLARE(name) extern decltype(&::name) p_##name;
CAPI_SYMBOLS(CAPI_DECLARE)
#undef CAPI_DECLARE

// The exported name, for GetProcAddress and for the log.
#define CAPI_NAME_(name) #name
#define CAPI_NAME(name) CAPI_NAME_(name)

// Bind the whole Lua C API from `lua_module` (an HMODULE for xlua.dll), or
// refuse.
//
// `pump_ready` is a predicate the caller supplies for ITS OWN symbols: the
// binding layer runs inside the sandbox pump.cpp builds, so it is only usable
// when pump.cpp's resolution succeeded too. Ask rather than assume.
//
// LuaBridge3 reaches 42 functions. Refusing is the point: a half-resolved
// binding layer does not fail at the call, it jumps through a null pointer at
// the call, in the game, while the player is moving. So resolve() returns false,
// logs every symbol it could not find, and leaves ready() false — and nothing
// downstream turns the layer on.
//
// Called once per lua_State, before any registration.
bool resolve(void* lua_module, bool (*pump_ready)());

// True when every symbol LuaBridge3 can reach is bound. Everything that
// registers must refuse to run when this is false.
bool ready();

// How many symbols are bound, and a comma-separated list of the ones that are
// not (or "none"). Both exist so the log can state the position instead of
// leaving the caller to guess why the layer did nothing.
int bound_count();
int required_count();
const char* missing_summary();

}  // namespace specter::lua::capi