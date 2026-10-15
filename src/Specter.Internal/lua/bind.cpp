// Specter.Internal — what Lua is allowed to see of ours (implementation).
//
// See bind.h for the isolation rule this file exists to enforce.

#include "pch-il2cpp.h"

#include "lua/bind.h"
#include "lua/bridge.h"

#include "features/inf_stamina/inf_stamina.h"
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
// Three scalars, not a double[3]: LuaBridge's Stack<double[3]> has no writable
// form, and `specter.var.x` says more than `specter.var.position[1]` anyway.
double g_x = 0.0;
double g_y = 0.0;
double g_z = 0.0;

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
constexpr bool kEnableBinding = true;

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

    // Do not TRUST the caller's index. build_specter leaves [store, specter] on
    // top of a stack that already holds the chunk, so the two are one slot
    // apart and -2 names the store. Registering there looks like it worked: the
    // table still gains the functions, the stack still balances, every check
    // still passes — and Lua, which looks in `specter`, finds nothing.
    //
    // `version` is the marker build_specter sets on specter and never on the
    // store, so the target can identify itself.
    lua_getfield(L, specter_idx, "version");
    const bool bonne_cible = !lua_isnil(L, -1);
    lua_pop(L, 1);
    if (!bonne_cible) {
        log::error("lua: bind -- index %d ne porte pas 'version' : ce n'est pas "
                   "la table specter. RIEN n'est enregistre.", specter_idx);
        return false;
    }

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
    // EVERY property is read AND write, and that is a decision, not a default.
    //
    // The two-argument form (getter only) makes Lua raise "attempt to write a
    // read-only field" when the script assigns. That raise happens INSIDE
    // LuaBridge's C++ __newindex metamethod, and LuaJIT implements a Lua error as
    // a longjmp out of the C frame: no C++ destructor runs, LuaBridge abandons
    // its stack bookkeeping mid-way, and the process dies. Measured on
    // 2026-10-15 — the game was gone on that one assignment, and the log stopped
    // with no line at all.
    //
    // This is the same longjmp hazard that killed specter.rawset/rawget before
    // the shim existed; it is a property of LuaJIT plus C++ bindings, not of any
    // one function.
    //
    // So the read-only protection is deliberately given up: a binding layer that
    // kills the process on a typo is a binding layer nobody uses. What is lost is
    // small — Lua can only write the addresses we handed it. The alternative,
    // documented rather than forgotten: expose nothing writable, or accept that
    // assigning to a read-only property is fatal.
    luabridge::getNamespaceFromStack(L)
        .beginNamespace("var")
            // Same address as getter and setter — that is what the three-argument
            // form means, and it is NOT what the two-argument form gives you.
            .addProperty("enabled", &g_enabled_flag, &g_enabled_flag)
            .addProperty("x", &g_x, &g_x)
            .addProperty("y", &g_y, &g_y)
            .addProperty("z", &g_z, &g_z)
            .addProperty("counter", &g_counter, &g_counter)
            .addProperty("speed", &g_speed, &g_speed)
            // The stamina gate. The address of the C++ bool the checkbox writes,
            // so `specter.var.stamina` and the checkbox are the SAME storage.
            // This is the first thing the binding layer is actually FOR: until
            // now a Lua flag and a C++ bool had to be kept in agreement by hand.
//
// NOT to hold script-owned switches. `specter` itself accepts
// `specter.catch_aura = true` with no DLL change at all, and the __newindex
// LuaBridge puts on `specter.var` REFUSES unknown names — so a flag written
// there needs a registered property and a rebuild, for nothing.
            .addProperty("stamina", features::stamina::flag(),
                         features::stamina::flag())
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

    // THE GAME IS THE ONLY ORACLE for the shim. LuaBridge calls the C API by
    // NAME: in a DLL, xlua.dll resolves its own internal calls to itself, while
    // in a static link our thunks would interpose everywhere. So there is no
    // faithful host test -- the honest move is to ask the question here, now,
    // while the stack still looks like it did before registration.
    //
    // If these are intact HERE, the damage happens later (in the factory, in the
    // preamble, on the next Execute). If they are already gone, registration is
    // the culprit and the log says exactly which call did it.
    const char* kWatch[] = {"_G", "pairs", "string", "math", "require"};
    int perdus = 0;
    for (const char* nom : kWatch) {
        lua_getglobal(L, nom);
        if (lua_isnil(L, -1)) {
            ++perdus;
        }
        lua_pop(L, 1);
    }
    if (perdus == 0) {
        log::info("lua: binding installee -- controles d'integrite OK "
                  "(%d/%d symboles)", capi::bound_count(), capi::required_count());
    } else {
        log::error("lua: binding INSTALLEE MAIS %d/%d globales du jeu ont "
                   "DISPARU AU MOMENT DE L'ENREGISTREMENT. Le shim est "
                   "coupable ; la couche est coupee pour ce run.",
                   perdus, static_cast<int>(sizeof(kWatch) / sizeof(kWatch[0])));
        lua_settop(L, depth_before);
        return false;
    }
    return true;
}

}  // namespace specter::lua::bind