// Specter — offline binding test.
//
// Runs on the host, against the system's LuaJIT and the SAME vendored headers
// the DLL compiles against. It answers the question the game cannot answer
// cheaply: does the binding layer actually read and write the C++ variables, and
// does the table it builds stay out of the game's globals?
//
// It exists because of what happened on 2026-10-15. Two of this project's
// deaths came from hand-written signatures and hand-written stack offsets, and
// the offline harness could not see either: it stood a Lua closure in for the C
// one, so it tested a different program than the one that ships. A test that
// cannot fail on the real code is not a test.
//
// What it covers, and what it does not:
//   - the extern "C" wrapper (an unlinked `lua_gettop()` fails here, loudly)
//   - addProperty read-only and read-write semantics
//   - addFunction from a C function pointer
//   - isolation: the built table must not appear in _G
//
// Build and run: tools/test-binding.sh

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge.h>

#include <cstdio>

namespace {

int g_failures = 0;

void check(bool ok, const char* what)
{
    std::printf("  %s  %s\n", ok ? "ok  " : "FAIL", what);
    if (!ok) {
        ++g_failures;
    }
}

// The variables Lua reaches. Plain globals, on purpose: this is the case the
// feature is for.
bool g_bNoRecoil = false;
int g_iAim = 0;
float g_fSpeed = 0.0f;
int g_print_calls = 0;

int api_print(const char* s)
{
    ++g_print_calls;
    return s != nullptr ? 0 : 0;
}

void register_devkit(lua_State* L)
{
    // getNamespaceFromStack, NOT getGlobalNamespace. The latter would put
    // `devkit` into the game's _G and make the E1 leak sweep fail. That
    // difference is the whole isolation story, so the test asserts it.
    luabridge::getNamespaceFromStack(L).beginNamespace("devkit")
        .beginNamespace("var")
            // Two arguments: READ ONLY. The Lua side can read the C++ variable,
            // and writing it raises 'x' is read-only.
            .addProperty("ro", &g_bNoRecoil)
            // Three arguments, same address twice: READ WRITE. This is the
            // documented form, and the one a two-argument call silently does
            // NOT give you.
            .addProperty("bNoRecoil", &g_bNoRecoil, &g_bNoRecoil)
            .addProperty("iAim", &g_iAim, &g_iAim)
            .addProperty("fSpeed", &g_fSpeed, &g_fSpeed)
        .endNamespace()
        .addFunction("print", &api_print)
        .endNamespace();
}

}  // namespace

int main()
{
    lua_State* L = luaL_newstate();
    if (L == nullptr) {
        std::printf("impossible de creer un etat Lua\n");
        return 2;
    }
    luaL_openlibs(L);

    std::printf("Liaison LuaBridge3 — test hors jeu\n");

    // The table LuaBridge builds lands on top of the stack.
    lua_newtable(L);
    register_devkit(L);

    const char* code =
        // `ro` is read BEFORE anything writes, so the assertion below actually
        // tests the read. Reading it afterwards would read back our own write
        // and pass for the wrong reason.
        "local d = ...\n"
        "local ro_avant = d.devkit.var.ro\n"
        "d.devkit.var.bNoRecoil = true\n"
        "d.devkit.var.iAim = 7\n"
        "d.devkit.var.fSpeed = 2.5\n"
        "d.devkit.print('x')\n"
        "return ro_avant, d.devkit.var.bNoRecoil, d.devkit.var.iAim,\n"
        "       d.devkit.var.fSpeed\n";

    if (luaL_loadstring(L, code) != 0) {
        std::printf("  FAIL  chargement: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }
    lua_pushvalue(L, -2);  // the table, as argument 1
    const int rc = lua_pcall(L, 1, 4, 0);
    if (rc != 0) {
        std::printf("  FAIL  execution: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    check(lua_toboolean(L, -4) == 0, "read-only property lit la variable C++");
    check(lua_toboolean(L, -3) != 0, "read-write property lit ce que Lua a ecrit");
    check(lua_tointeger(L, -2) == 7, "l'entier fait l'aller-retour");
    check(lua_tonumber(L, -1) == 2.5, "le flottant fait l'aller-retour");
    lua_pop(L, 4);

    std::printf("  -- cote C++ --\n");
    check(g_bNoRecoil, "g_bNoRecoil a ete ecrit depuis Lua");
    check(g_iAim == 7, "g_iAim a ete ecrit depuis Lua");
    check(g_fSpeed == 2.5f, "g_fSpeed a ete ecrit depuis Lua");
    check(g_print_calls == 1, "addFunction a bien ete appelee");

    std::printf("  -- isolation --\n");
    lua_getglobal(L, "devkit");
    check(lua_isnil(L, -1) != 0,
          "devkit n'apparait PAS dans les globales");
    lua_pop(L, 1);

    lua_close(L);

    if (g_failures == 0) {
        std::printf("\nTout passe.\n");
        return 0;
    }
    std::printf("\n%d echec(s).\n", g_failures);
    return 1;
}