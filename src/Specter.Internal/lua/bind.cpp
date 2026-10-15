// Specter.Internal — what Lua is allowed to see of ours (implementation).
//
// See bind.h for the isolation rule this file exists to enforce.

#include "pch-il2cpp.h"

#include "lua/bind.h"
#include "lua/bridge.h"

#include "platform/log.h"

namespace specter::lua::bind {
namespace {

// The variables the layer exposes. Plain globals in this namespace, on purpose:
// the whole point of addProperty is handing Lua an address to read and write,
// and a member pointer would only add indirection.
//
// Read-only by default. A feature that wants Lua to WRITE one of these has to
// say so here, where the decision is visible, rather than inferring it from the
// caller's mood. That is the difference between an API and a hole.
bool g_enabled_flag = false;
int g_counter = 0;
float g_speed = 0.0f;
double g_position[3] = {0.0, 0.0, 0.0};

int api_reset()
{
    g_counter = 0;
    return 0;
}

}  // namespace

// OFF. Do not flip this on without reading the note below.
//
// 2026-10-15, in game: with the layer ON, the sandbox lost most of the game's
// globals. `specter` survived, `specter.version` survived, `table`/`tostring`/
// `rawget`/`setmetatable`/`getfenv` survived -- and `_G`, `pairs`, `ipairs`,
// `string`, `math` and `require` were all nil. `require` being gone takes the
// stamina toggle with it.
//
// The survivors are exactly the ten library functions the sandbox preamble
// captures as parameters, so those never needed the globals table. Everything
// else resolved through the env's __index and found nothing. That says the
// globals table became unreachable or empty from the sandbox's side; it does NOT
// say why.
//
// What was RULED OUT, both measured in a second rather than argued:
//
//   - the registration itself. Run offline with real LuaJIT, the identical
//     chain leaves pairs/string/math/require/_G intact AND specter.var works.
//   - the shim. The offline shim test crashed in luaL_newstate(), before our
//     code runs: defining lua_gettop globally INTERPOSES the library's symbol,
//     so p_lua_gettop points at our own shim and recurses forever. The DLL does
//     not have that defect -- it resolves through GetProcAddress on xlua.dll,
//     where the name finds the real function -- but it means the offline harness
//     cannot be the oracle for this class of question.
//   - lua_Debug. 120 bytes in the vendored headers and in the system ones.
//
// What was NOT ruled out, and is where to look: whatever LuaBridge calls while
// registering that touches the globals table, or the stack, through our shim --
// luaL_unref and the backtrace helpers (lua_getstack/lua_getinfo) are the
// obvious suspects, because the first frees registry references and the other
// two take a lua_Debug* from the game's LuaJIT.
//
// The switch exists so the answer can be found with a rebuild instead of a
// bisect over launches.
constexpr bool kEnableBinding = false;

bool install(lua_State* L, int specter_idx)
{
    if (!kEnableBinding) {
        return false;
    }
    // REFUSE FIRST. Registering with unbound pointers means every binding is a
    // trap waiting for a call, and the failure would be a crash in the game with
    // no log line pointing here.
    if (!capi::ready()) {
        log::info("lua: couche de binding absente -- rien n'est enregistre");
        return false;
    }

    // The stack must come back EXACTLY as it was found. build_specter's contract
    // is "leaves two values", and run() checks that immediately afterwards with
    // a depth comparison — a binding layer that leaked one value would shift
    // every index above it, and the symptom would be the factory being called
    // with the wrong argument rather than anything to do with bindings.
    // Validity the way Lua defines it. The previous test was `specter_idx <= 0`,
    // which rejects every NEGATIVE index — and negative indices are exactly the
    // ones a caller with values on the stack hands over. There is no index 0 at
    // all, so the test rejected the only form that works and accepted nothing.
    // It fired on every single run and nothing was ever registered.
    const int top = lua_gettop(L);
    if (specter_idx == 0 || specter_idx > top || specter_idx < -top) {
        log::error("lua: bind -- index %d hors pile (profondeur %d)",
                   specter_idx, top);
        return false;
    }
    const int depth_before = top;

    // getNamespaceFromStack, NEVER getGlobalNamespace.
    //
    // This one call is the whole isolation story. getGlobalNamespace puts the
    // table in the game's _G, where the E1 leak sweep finds it — measured, 236
    // globals, one of them ours. getNamespaceFromStack seeds from the table on
    // top of the stack, so the bindings live in `specter`, which lives in our
    // sandbox environment, which nothing in the game points at.
    lua_pushvalue(L, specter_idx);  // the table getNamespaceFromStack reads
    if (lua_type(L, -1) != LUA_TTABLE) {
        lua_pop(L, 1);
        log::error("lua: bind -- ce n'est pas une table, rien n'est enregistre");
        return false;
    }

    // No beginNamespace() around it: the table we are registering into IS
    // `specter`, so adding a namespace would make it `specter.specter.*`. The
    // members land directly on it:
    //
    //     specter.var.counter = 7
    //     specter.reset()
    luabridge::getNamespaceFromStack(L)
        .beginNamespace("var")
            // Read only: Lua can see these, cannot change them. The documented
            // two-argument form. Writing raises 'x' is read-only.
            .addProperty("enabled", &g_enabled_flag)
            .addProperty("position", &g_position)
            // Read AND write: the SAME address as getter and setter, which is
            // what the three-argument form means. The two-argument form does
            // NOT give you this, and the difference is silent until you write.
            .addProperty("counter", &g_counter, &g_counter)
            .addProperty("speed", &g_speed, &g_speed)
        .endNamespace()
        .addFunction("reset", &api_reset);

    lua_pop(L, 1);  // our copy of the table; the bindings live inside it

    const int depth_after = lua_gettop(L);
    if (depth_after != depth_before) {
        log::error("lua: bind -- la pile a bouge (%d -> %d). La couche est "
                   "desactivee pour ce run.", depth_before, depth_after);
        lua_settop(L, depth_before);
        return false;
    }

    log::info("lua: couche de binding installee dans specter "
              "(%d/%d symboles)", capi::bound_count(), capi::required_count());
    return true;
}

}  // namespace specter::lua::bind