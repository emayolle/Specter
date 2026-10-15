// Specter.Internal — the worker descriptor format, and its parser.
//
// WHY IT IS ITS OWN FILE
//
// This is the code that broke the game, and it broke it twice: once because a
// skipped 'S' directive left its payload in the stream, once because 'S' was
// read one byte off (the header's newline in, the last byte out). Both were
// found by reasoning, and both were found too late — the game had already died
// by the time anyone was sure.
//
// So it lives here, with nothing else in it, and tools/test-worker-meta.sh runs
// it on the host against the system LuaJIT. No game, no DLL, no Wine, one
// second. A change that breaks the descriptor format now fails there.
//
// WHAT THE FORMAT IS
//
// A worker is started with a chunk (source OR LuaJIT bytecode) plus a flat
// buffer of descriptors saying how to bind that chunk's upvalues and what to
// pass it. One directive per line:
//
//     <role> <kind> <index> [payload]
//
// role:  U = upvalue slot to fill        A = call argument to push
// kind:  L <name>  the worker's own global <name>
//        N <num>    number
//        S <len>    string; <len> bytes follow on their OWN line
//        B <0|1>    boolean
//        Z          nil
//
// A 'S' payload lives on the lines after the header's newline and may contain
// ANYTHING, newlines included. That is why both the take and the skip paths go
// through take_desc(): one function that always consumes the whole directive.
//
// THE BUFFER IS NUL-TERMINATED. strtod and strtol are pointed straight at it
// and have no length of their own to stop at.
//
// NO lua_error IN HERE. apply_meta() reports a bad descriptor by RETURNING, and
// the caller decides. A raise here would longjmp with no pcall around it -- the
// worker thread has none yet at that point -- and a worker that longjmps into
// nothing takes the game down with it. That is not hypothetical: it is what the
// first version did.

#pragma once

#include "lua/capi.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace specter::lua::meta {

using namespace capi;

//
// What cannot cross is anything the worker's world does not also have: a game
// function, a game table, a game userdata. Those are refused by NAME, in the
// game world, before anything is spawned — so the error names the variable
// instead of surfacing later as a nil deep inside the body. The same rule
// applies to the ARGUMENTS of the call, which cross by the same road.
//
// Wire format, one directive per line, parsed by a pointer walk. The role letter
// says what the value is FOR, so the same encodings serve both upvalues and
// call arguments:
//
//     <role> <kind> <index> [payload]
//
// role: U = upvalue slot, A = call argument
// kind: L <name>  the worker's global <name>
//       N <num>    number
//       S <len>    string; <len> bytes follow on their own line
//       B <0|1>    boolean
//       Z          nil
// ---------------------------------------------------------------------------

// Standard Lua 5.1 names. Only these may be rebound; anything else that is not
// a primitive is refused.
const char* const kStdlibNames[] = {
    "assert", "collectgarbage", "coroutine", "debug", "error", "getfenv",
    "getmetatable", "io", "ipairs", "loadstring", "math", "module", "next",
    "os", "pairs", "pcall", "print", "rawequal", "rawget", "rawlen", "rawset",
    "require", "select", "setfenv", "setmetatable", "string", "table",
    "tonumber", "tostring", "type", "unpack", "xpcall", "_G",
};

bool is_stdlib_name(const char* n)
{
    for (const char* s : kStdlibNames) {
        if (std::strcmp(s, n) == 0) {
            return true;
        }
    }
    return false;
}

// Consume one descriptor, optionally pushing its value.
//
// `payload` is the text after the index, `nl` the newline that ends the header
// line. A 'S' payload lives on the lines AFTER that newline and can contain
// anything, including newlines -- so BOTH paths have to skip it, which is the
// whole point of having one function instead of two.
//
// `p` is advanced past the whole directive, payload included, either way.
// Errors go through `why`: a Lua error longjmps out of here and skips every
// destructor between.
bool take_desc(lua_State* L, char kind, const char* payload, const char* nl,
               const char* end, bool want, const char*& p, char* why,
               std::size_t why_cap)
{
    switch (kind) {
    case 'Z':
        if (want) {
            p_lua_pushnil(L);
        }
        p = nl + 1;
        return true;

    case 'N': {
        if (want) {
            p_lua_pushnumber(L, std::strtod(payload, nullptr));
        }
        p = nl + 1;
        return true;
    }

    case 'B':
        if (want) {
            p_lua_pushboolean(L, payload[0] == '1');
        }
        p = nl + 1;
        return true;

    case 'L': {
        const std::string nm(payload, static_cast<std::size_t>(nl - payload));
        if (!want) {
            p = nl + 1;
            return true;
        }
        p_lua_getfield(L, LUA_GLOBALSINDEX, nm.c_str());
        if (p_lua_type(L, -1) == LUA_TNIL) {
            std::snprintf(why, why_cap, "le worker n'a pas le global '%s'",
                          nm.c_str());
            return false;
        }
        p = nl + 1;
        return true;
    }

    case 'S': {
        // `payload` here is the LENGTH, not the text: the bytes live on the
        // lines after nl. Reading them from `payload` instead would be off by
        // one -- the header's own newline in, the last byte out.
        const long slen = std::strtol(payload, nullptr, 10);
        const char* bytes = nl + 1;
        if (slen < 0 || bytes + slen > end) {
            std::snprintf(why, why_cap, "chaine tronquee dans les descripteurs");
            return false;
        }
        if (want) {
            p_lua_pushlstring(L, bytes, static_cast<std::size_t>(slen));
        }
        p = bytes + slen;
        if (p < end && *p == '\n') {
            ++p;
        }
        return true;
    }

    default:
        std::snprintf(why, why_cap, "descripteur inconnu '%c'", kind);
        return false;
    }
}

// Apply every descriptor in `meta`.
//
// want_upvalues true  -> 'U' directives are bound on the chunk at chunk_idx
//                        with debug.setupvalue, and nothing is left on the stack.
// want_upvalues false -> 'A' directives are pushed, left for lua_pcall, and
//                        their count is returned.
//
// `meta` MUST be NUL-terminated: strtod/strtol are pointed straight at it and
// have no length to stop at. spawn() allocates one byte more for exactly this.
//
// Errors propagate as ordinary Lua errors, so a bad descriptor lands in the
// worker's `error` like anything else.
// Returns the number of values taken (or bound), or -1 on a bad descriptor,
// with `why` filled in. NEVER raises: see the note at the top of this file.
int apply_meta(lua_State* L, int chunk_idx, const char* meta, int len,
               bool want_upvalues, char* why, std::size_t why_cap)
{
    why[0] = '\0';
    const int base = p_lua_gettop(L);
    int fn_idx = 0;
    if (want_upvalues) {
        p_lua_getfield(L, LUA_GLOBALSINDEX, "debug");
        p_lua_getfield(L, -1, "setupvalue");  // [ .., debug, setupvalue ]
        if (p_lua_type(L, -1) != LUA_TFUNCTION) {
            p_lua_settop(L, base);
            std::snprintf(why, why_cap,
                          "le worker n'a pas debug.setupvalue");
            return -1;
        }
        fn_idx = p_lua_gettop(L);
    }

    int taken = 0;
    const char* p = meta;
    const char* end = meta + len;

    while (p < end) {
        const char* nl = static_cast<const char*>(
            std::memchr(p, '\n', static_cast<std::size_t>(end - p)));
        if (!nl) {
            break;
        }
        const char role = *p++;
        while (p < nl && *p == ' ') {
            ++p;
        }
        const char kind = *p++;
        while (p < nl && *p == ' ') {
            ++p;
        }
        char* after = nullptr;
        const long idx = std::strtol(p, &after, 10);
        while (after < nl && *after == ' ') {
            ++after;
        }

        const bool is_up = (role == 'U');
        const bool want = (is_up == want_upvalues);
        if (!take_desc(L, kind, after, nl, end, want, p, why, why_cap)) {
            p_lua_settop(L, base);
            return -1;
        }
        if (!want) {
            continue;
        }
        if (is_up) {
            // The value take_desc just pushed. Everything below restores the
            // stack to value_at, never to base -- an earlier version popped the
            // value before using it and then called a nil.
            const int value_at = p_lua_gettop(L);

            // 1. The function must ACTUALLY HAVE this upvalue. setupvalue on a
            // function with none returns nil and changes nothing: a silent
            // no-op that looks exactly like success, with the body then running
            // against an uninitialised slot. Ask first.
            p_lua_getfield(L, LUA_GLOBALSINDEX, "debug");
            p_lua_getfield(L, -1, "getupvalue");
            p_lua_pushvalue(L, chunk_idx);
            p_lua_pushinteger(L, idx);
            if (p_lua_pcall(L, 2, 1, 0) != 0) {
                char m[128] = "";
                const char* t = p_lua_tolstring(L, -1, nullptr);
                if (t) {
                    std::snprintf(m, sizeof(m), "%s", t);
                }
                p_lua_settop(L, base);
                std::snprintf(why, why_cap, "debug.getupvalue a echoue : %s", m);
                return -1;
            }
            if (p_lua_type(L, -1) == LUA_TNIL) {
                p_lua_settop(L, base);
                std::snprintf(why, why_cap,
                              "la fonction n'a pas d'upvalue numero %ld", idx);
                return -1;
            }
            p_lua_settop(L, value_at);

            // 2. Bind, through pcall, with THREE arguments.
            //
            // Both of those were learned the expensive way.
            //
            // The arity of debug.setupvalue belongs to the LIBRARY, not to the
            // headers we compiled against. xlua.dll's LuaJIT is built with
            // LUA52COMPAT, so it wants setupvalue(f, n, v) -- the 5.2 form,
            // three arguments -- while the 5.1 headers describe two. With two:
            //
            //     pcall(debug.setupvalue, bb, 1) -> bad argument #3 to '?'
            //
            // And it used to be called UNPROTECTED. The worker thread has no
            // pcall around this point, so the raise longjmped into nothing,
            // LuaJIT printed PANIC, and the game died with it. Twice.
            //
            // So: three arguments, and a pcall. A worker that cannot bind an
            // upvalue is a worker in error, with a message -- not a crash.
            p_lua_getfield(L, LUA_GLOBALSINDEX, "debug");
            p_lua_getfield(L, -1, "setupvalue");
            const int su = p_lua_gettop(L);
            p_lua_pushvalue(L, su);         // la fonction a appeler
            p_lua_pushvalue(L, chunk_idx);  // le chunk
            p_lua_pushinteger(L, idx);      // quel emplacement
            p_lua_pushvalue(L, value_at);   // quoi y mettre
            if (p_lua_pcall(L, 3, 1, 0) != 0) {
                char m[128] = "";
                const char* t = p_lua_tolstring(L, -1, nullptr);
                if (t) {
                    std::snprintf(m, sizeof(m), "%s", t);
                }
                p_lua_settop(L, base);
                std::snprintf(why, why_cap,
                              "debug.setupvalue a refuse l'upvalue %ld : %s",
                              idx, m);
                return -1;
            }
            p_lua_settop(L, base);
        } else {
            ++taken;
        }
    }

    if (want_upvalues) {
        p_lua_settop(L, base);
    }
    return taken;
}

// ---------------------------------------------------------------------------
}  // namespace specter::lua::meta
