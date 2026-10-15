// Specter.Internal — the shim that makes runtime resolution possible.
//
// LuaBridge3 calls the Lua C API by NAME. We only have those functions at run
// time, out of xlua.dll. So the names have to exist in OUR binary, and forward
// to a pointer we bound.
//
// WHY THUNKS AND NOT #define REDIRECTS.
//
// The obvious alternative — `#define lua_gettop capi::p_lua_gettop` before
// including LuaBridge — does not work, and the reason is worth keeping:
// LuaBridge does `using ::luaL_unref;` (LuaBridge.h:1047), and a
// using-declaration cannot name a variable. The macro rewrite turns that into a
// hard compile error. Thunks define the global function LuaBridge expects, so
// that line stays valid.
//
// WHY HAND-WRITING 42 SIGNATURES IS NOT THE RISK IT LOOKS LIKE.
//
// Every function below is a REDECLARATION of what lua.h already declares. A
// signature that does not match is a compile error, not a silent mismatch at run
// time. That is the one property this project lacks everywhere else — the
// hand-written typedefs in pump.cpp, and the hand-written stack offsets that
// cost three crashes. Here the compiler is the check.
//
// The list is exactly the set `nm -u` reported for the registration paths
// Specter uses. If LuaBridge ever reaches one more, the LINK fails and names it.
// That is the intended alarm: a build error now, not a null pointer in the game.

#include "pch-il2cpp.h"

#include "lua/capi.h"

#include <cstdarg>
#include <cstdio>

#include "platform/log.h"

namespace specter::lua::capi {
namespace {

// Reached only if a caller ignored ready(). There is deliberately no silent
// fallback: a stub returning 0 for lua_gettop leaves the stack off by one, and
// the crash lands ten lines later in somebody else's code. Naming the symbol
// here is the difference between a one-line log and a mystery.
[[noreturn]] void unbound(const char* name)
{
    static bool reported = false;
    if (!reported) {
        reported = true;
        log::error("lua: SHIM -- '%s' appele alors que le symbole n'est pas lie.",
                   name);
        log::error("lua: la couche de binding aurait du ete refusee ; "
                   "voir la ligne 'REFUSEE' plus haut.");
    }
    __builtin_trap();
    __builtin_unreachable();
}

}  // namespace
}  // namespace specter::lua::capi

using namespace specter::lua::capi;

extern "C" {

// ---- pile ------------------------------------------------------------------

int lua_gettop(lua_State* L)
{
    // Not a ternary: `unbound` is void, and `int ? int : void` does not compile
    // however [[noreturn]] the second branch is.
    if (p_lua_gettop == nullptr) {
        unbound("lua_gettop");
    }
    return p_lua_gettop(L);
}
void lua_settop(lua_State* L, int idx) { p_lua_settop(L, idx); }
void lua_pushvalue(lua_State* L, int idx) { p_lua_pushvalue(L, idx); }
void lua_remove(lua_State* L, int idx) { p_lua_remove(L, idx); }
void lua_insert(lua_State* L, int idx) { p_lua_insert(L, idx); }
void lua_replace(lua_State* L, int idx) { p_lua_replace(L, idx); }
int lua_checkstack(lua_State* L, int sz) { return p_lua_checkstack(L, sz); }

// ---- construction et tables ------------------------------------------------

void lua_createtable(lua_State* L, int narray, int nrec) { p_lua_createtable(L, narray, nrec); }
void* lua_newuserdata(lua_State* L, std::size_t sz) { return p_lua_newuserdata(L, sz); }
size_t lua_objlen(lua_State* L, int idx) { return p_lua_objlen(L, idx); }
int lua_getmetatable(lua_State* L, int objindex) { return p_lua_getmetatable(L, objindex); }
int lua_setmetatable(lua_State* L, int objindex) { return p_lua_setmetatable(L, objindex); }
void lua_rawget(lua_State* L, int idx) { p_lua_rawget(L, idx); }
void lua_rawgeti(lua_State* L, int idx, int n) { p_lua_rawgeti(L, idx, n); }
void lua_rawset(lua_State* L, int idx) { p_lua_rawset(L, idx); }
// In Lua 5.1 these four are all `void`. They return int from 5.2 on, and
// guessing wrong is a compile error rather than a stack mistake — which is the
// only reason hand-writing them here is acceptable at all.
void lua_gettable(lua_State* L, int idx) { p_lua_gettable(L, idx); }
void lua_settable(lua_State* L, int idx) { p_lua_settable(L, idx); }
void lua_getfield(lua_State* L, int idx, const char* k)
{
    p_lua_pushstring(L, k);
    p_lua_gettable(L, idx);
}
void lua_setfield(lua_State* L, int idx, const char* k)
{
    p_lua_pushstring(L, k);
    p_lua_settable(L, idx);
}

// ---- pousse ----------------------------------------------------------------

void lua_pushnil(lua_State* L) { p_lua_pushnil(L); }
void lua_pushboolean(lua_State* L, int b) { p_lua_pushboolean(L, b); }
void lua_pushinteger(lua_State* L, lua_Integer n) { p_lua_pushinteger(L, n); }
void lua_pushnumber(lua_State* L, lua_Number n) { p_lua_pushnumber(L, n); }
void lua_pushlstring(lua_State* L, const char* s, size_t len) { p_lua_pushlstring(L, s, static_cast<unsigned long long>(len)); }
void lua_pushstring(lua_State* L, const char* s) { p_lua_pushstring(L, s); }
void lua_pushlightuserdata(lua_State* L, void* p) { p_lua_pushlightuserdata(L, p); }
void lua_pushcclosure(lua_State* L, lua_CFunction fn, int n) { p_lua_pushcclosure(L, fn, n); }

// ---- conversions -----------------------------------------------------------

int lua_type(lua_State* L, int idx) { return p_lua_type(L, idx); }
int lua_toboolean(lua_State* L, int idx) { return p_lua_toboolean(L, idx); }
lua_Integer lua_tointeger(lua_State* L, int idx) { return p_lua_tointeger(L, idx); }
lua_Number lua_tonumber(lua_State* L, int idx) { return p_lua_tonumber(L, idx); }
const char* lua_tolstring(lua_State* L, int idx, size_t* len) { return p_lua_tolstring(L, idx, len); }
void* lua_touserdata(lua_State* L, int idx) { return p_lua_touserdata(L, idx); }
const void* lua_topointer(lua_State* L, int idx) { return p_lua_topointer(L, idx); }
int lua_isnumber(lua_State* L, int idx) { return p_lua_isnumber(L, idx); }
int lua_iscfunction(lua_State* L, int idx) { return p_lua_iscfunction(L, idx); }
int lua_isuserdata(lua_State* L, int idx) { return p_lua_isuserdata(L, idx); }

// ---- execution -------------------------------------------------------------

void lua_call(lua_State* L, int nargs, int nresults) { p_lua_call(L, nargs, nresults); }
void lua_concat(lua_State* L, int n) { p_lua_concat(L, n); }
int lua_error(lua_State* L) { return p_lua_error(L); }
const char* lua_pushfstring(lua_State* L, const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n < 0) {
        n = 0;
    }
    p_lua_pushlstring(L, buf, static_cast<unsigned long long>(n));
    return p_lua_tolstring(L, -1, nullptr);
}
const char* lua_pushvfstring(lua_State* L, const char* fmt, va_list argp) {
    char buf[1024];
    int n = vsnprintf(buf, sizeof(buf), fmt, argp);
    if (n < 0) {
        n = 0;
    }
    p_lua_pushlstring(L, buf, static_cast<unsigned long long>(n));
    return p_lua_tolstring(L, -1, nullptr);
}

// ---- pile de traces --------------------------------------------------------
//
// LuaBridge walks the Lua stack to produce its error backtraces. Two symbols
// here are what make that work, and they are the reason `lua_getinfo` and
// `lua_getstack` are in the list even though nothing else calls them.

int lua_getstack(lua_State* L, int level, lua_Debug* ar) { return p_lua_getstack(L, level, ar); }
int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar) { return p_lua_getinfo(L, what, ar); }

// ---- bibliotheque auxiliaire ----------------------------------------------

void luaL_checkstack(lua_State* L, int sz, const char* msg) { p_luaL_checkstack(L, sz, msg); }
void luaL_unref(lua_State* L, int t, int ref) { p_luaL_unref(L, t, ref); }

}  // extern "C"