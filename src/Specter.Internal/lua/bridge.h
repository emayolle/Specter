// Specter.Internal — the ONE way to include LuaBridge.h.
//
// A translation unit that wants LuaBridge includes THIS file, never
// <LuaBridge.h>. The include path for both vendored trees must already be set
// (tools/build-dll.sh adds them).
//
// There is deliberately NOTHING clever here. The first version redirected the
// C API with #define before including LuaBridge:
//
//     #define lua_gettop capi::p_lua_gettop
//
// It does not compile, and the reason is worth remembering:
// LuaBridge.h:1047 does `using ::luaL_unref;`, and a using-declaration cannot
// name a variable — so every redirect turns that line into a hard error.
//
// The redirection happens one level down instead: capi_shim.cpp DEFINES the
// global functions LuaBridge calls, forwarding to pointers capi.cpp bound from
// xlua.dll. LuaBridge then sees an ordinary API and its `using` stays valid.
//
// This file exists so that the include order stays obvious, and so that nobody
// reintroduces the macros by accident.
#pragma once

#include "lua/capi.h"

#include <LuaBridge.h>