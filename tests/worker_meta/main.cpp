// Specter.Internal — offline test for the worker descriptor format.
//
// Links the SAME worker_meta.h the DLL compiles, against the system LuaJIT.
// The capi pointers are bound to the real library functions, so apply_meta() and
// take_desc() run here exactly as they run in the worker — same code, same Lua,
// no game, no DLL, no Wine.
//
// This exists because that code broke the game twice and both times the reason
// was obvious only AFTER a restart. Here it fails in a second.
//
// ONE TRAP WORTH NAMING: lua_tolstring CONVERTS THE SLOT IN PLACE. Calling a
// reader twice over the same stack therefore sees a number as a string the
// second time. Every read below happens exactly once, into a variable.

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "lua/capi.h"

// worker_meta.h includes capi.h, which declares p_<name> as
// `extern decltype(&::name) p_name` inside extern "C". We satisfy them here by
// assigning the real library functions. That is the one thing the DLL cannot
// do offline: it resolves them through GetProcAddress on xlua.dll.
//
// Note we do NOT compile capi_shim.cpp here. The shim DEFINES the global lua_*
// functions, and in a static link that interposes the library's own symbols --
// the defect documented in bind.h. worker_meta.h calls p_* directly, so it does
// not need the shim and does not suffer from it.
namespace specter::lua::capi {
#define BIND(name) decltype(&::name) p_##name = &::name;
CAPI_SYMBOLS(BIND)
#undef BIND
}  // namespace specter::lua::capi

#include "lua/worker_meta.h"

namespace {

int g_ok = 0;
int g_ko = 0;

void verifie(const char* nom, bool condition, const std::string& detail = "")
{
    if (condition) {
        ++g_ok;
        std::printf("  ok    %-44s %s\n", nom, detail.c_str());
    } else {
        ++g_ko;
        std::printf("  ECHEC %-44s %s\n", nom, detail.c_str());
    }
}

// One descriptor per value, exactly as describe_args / describe_upvalues build
// them. `vals` holds the wire form directly, so a test can state "a string with
// newlines in it" as readably as "a number".
std::string decrire(const std::vector<std::string>& vals, char role)
{
    std::string m;
    char buf[64];
    for (size_t i = 0; i < vals.size(); ++i) {
        const std::string& v = vals[i];
        const size_t n = i + 1;
        switch (v[0]) {
        case 'z':
            std::snprintf(buf, sizeof(buf), "%c Z %zu\n", role, n);
            m += buf;
            break;
        case 'b':
            std::snprintf(buf, sizeof(buf), "%c B %zu %c\n", role, n, v[1]);
            m += buf;
            break;
        case 'n':
            std::snprintf(buf, sizeof(buf), "%c N %zu %s\n", role, n,
                          v.c_str() + 1);
            m += buf;
            break;
        case 'L': {
            // "L:<nom>" : rebrancher sur un global du worker PAR SON NOM.
            // C'est le seul kind qui depend du nom plutot que de la valeur,
            // et le seul qui puisse reussir ou echouer selon la bibliotheque
            // du worker.
            const std::string nom = v.substr(2);
            std::snprintf(buf, sizeof(buf), "%c L %zu %s\n", role, n,
                          nom.c_str());
            m += buf;
            break;
        }
        case 's': {
            // "s<taille>:<texte>" : on coupe au ':', PAS a l'octet 2. Avec
            // "s7:bonjour", substr(2) donnait ":bonjour" -- un octet de trop
            // dans le texte et une taille qui collait par hasard.
            const std::string body = v.substr(v.find(':') + 1);
            std::snprintf(buf, sizeof(buf), "%c S %zu %zu\n", role, n,
                          body.size());
            m += buf;
            m += body;
            m += '\n';
            break;
        }
        }
    }
    // worker.cpp alloue un octet de plus et y met un zero. strtod/strtol sont
    // pointes droit dessus et n'ont pas de longueur a eux.
    m.push_back('\0');
    m.pop_back();
    return m;
}

std::string arg_n(const char* v) { return std::string("n") + v; }
std::string arg_b(bool v) { return std::string("b") + (v ? '1' : '0'); }
std::string arg_z() { return "z"; }
// kind 'L' : rebrancher sur un global du worker PAR SON NOM. arg_spousseait une
// chaine, ce qui nexercise pas du tout le cas "ce global n'existe pas".
std::string arg_l(const std::string& nom) { return "L:" + nom; }
std::string arg_s(const std::string& v) {
    char b[32];
    std::snprintf(b, sizeof(b), "s%zu:", v.size());
    return std::string(b) + v;
}

// Describe the values apply_meta pushed, in order. ONE pass: lua_tolstring
// rewrites the slot, so a second pass would read a number as a string.
std::string lire(lua_State* L, int first, int count)
{
    std::string out;
    char buf[256];
    for (int i = 0; i < count; ++i) {
        const int idx = first + i;
        switch (lua_type(L, idx)) {
        case LUA_TNIL:
            out += "nil";
            break;
        case LUA_TBOOLEAN:
            out += lua_toboolean(L, idx) ? "true" : "false";
            break;
        case LUA_TNUMBER:
            std::snprintf(buf, sizeof(buf), "%.17g", lua_tonumber(L, idx));
            out += buf;
            break;
        case LUA_TSTRING: {
            std::size_t n = 0;
            const char* s = lua_tolstring(L, idx, &n);
            out += "[";
            out.append(s ? s : "?", s ? n : 0);
            out += "]";
            break;
        }
        default:
            out += "?";
            break;
        }
        if (i + 1 < count) {
            out += " ";
        }
    }
    return out;
}

}  // namespace

int main()
{
    // stdout is buffered, and terminate() does not flush. Without this, a crash
    // eats every line the test just produced and you are left guessing where.
    setvbuf(stdout, nullptr, _IONBF, 0);

    using namespace specter::lua;

    lua_State* L = luaL_newstate();
    if (!L) {
        std::printf("impossible de creer un etat\n");
        return 2;
    }
    luaL_openlibs(L);

    // --- sonde : debug.setupvalue SOUS pcall, pour lire le message ---------
    {
        std::printf("diag : sonde sur debug.setupvalue\n");
        luaL_dostring(L, "aa = 1  bb = function() return aa end");
        lua_getfield(L, LUA_GLOBALSINDEX, "debug");
        std::printf("diag : debug type=%d (table=%d)\n", lua_type(L, -1), LUA_TTABLE);
        lua_getfield(L, -1, "setupvalue");
        std::printf("diag : setupvalue type=%d (function=%d)\n", lua_type(L, -1), LUA_TFUNCTION);
        lua_getfield(L, LUA_GLOBALSINDEX, "bb");
        std::printf("diag : bb type=%d\n", lua_type(L, -1));
        lua_pushinteger(L, 1);
        const int rc = lua_pcall(L, 2, 0, 0);
        std::printf("diag : rc=%d msg=%s\n", rc,
                    rc ? (lua_tostring(L, -1) ? lua_tostring(L, -1) : "?") : "ok");
        lua_settop(L, 0);
    }

    // ---------------------------------------------------------------- args
    std::printf("descripteurs : arguments\n");

    struct CasArg {
        const char* nom;
        std::vector<std::string> vals;
        const char* attendu;
        int nombre;
    };
    const CasArg cas[] = {
        {"les quatre types",
         {arg_n("42"), arg_s("bonjour"), arg_b(true), arg_z()},
         "42 [bonjour] true nil", 4},
        {"chaine avec retours a la ligne",
         {arg_n("1"), arg_s("avec\nun\nretour"), arg_n("9")},
         "1 [avec\nun\nretour] 9", 3},
        {"chaine vide puis 1 octet", {arg_s(""), arg_s("x")}, "[] [x]", 2},
        {"deux chaines consecutives", {arg_s("un"), arg_s("deux")},
         "[un] [deux]", 2},
        {"chaine de 64 octets", {arg_s(std::string(64, 'z'))},
         "[zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz]", 1},
        {"aucun argument", {}, "", 0},
    };

    for (const CasArg& c : cas) {
        const std::string m = decrire(c.vals, 'A');
        char why[192] = "";
        const int base = lua_gettop(L);
        const int n = meta::apply_meta(L, 0, m.c_str(),
                                       static_cast<int>(m.size()), false, why,
                                       sizeof(why));
        char detail[256];
        std::snprintf(detail, sizeof(detail), "%d valeur(s) : %s", n,
                      lire(L, base + 1, n).c_str());
        verifie(c.nom, n == c.nombre && lire(L, base + 1, n) == c.attendu,
                detail);
        lua_settop(L, base);
    }

    // ------------------------------------------------------- role inverse
    {
        const std::string m = decrire(
            {arg_n("1"), arg_s("abc"), arg_n("7")}, 'A');
        char why[192] = "";
        const int base = lua_gettop(L);
        const int n = meta::apply_meta(L, 0, m.c_str(),
                                       static_cast<int>(m.size()), true, why,
                                       sizeof(why));
        verifie("role U sur du A : rien pris, pile intacte",
                n == 0 && lua_gettop(L) == base);
    }

    // ---------------------------------------------------------- upvalues
    std::printf("descripteurs : upvalues\n");

    // A real closure, loaded the way the worker loads the dumped chunk, with
    // debug.setupvalue filling its slot.
    {
        char why[192] = "";
        const int base = lua_gettop(L);

        luaL_dostring(L, "local k = 999  additionneur = function(a) return a + k end");
        lua_getfield(L, LUA_GLOBALSINDEX, "additionneur");
        const int chunk = lua_gettop(L);

        const std::string m = decrire({arg_n("1")}, 'U');
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        verifie("apply_meta(U) sans erreur", rc >= 0, why);
        lua_pushnumber(L, 1);
        if (lua_pcall(L, 1, 1, 0) == 0) {
            char b[64];
            std::snprintf(b, sizeof(b), "%.0f", lua_tonumber(L, -1));
            verifie("  upvalue REMPLACE : 1 + 1 = 2", std::strcmp(b, "2") == 0,
                    b);
        } else {
            verifie("  upvalue REMPLACE : 1 + 1 = 2", false,
                    (lua_type(L, -1) == LUA_TSTRING && lua_tostring(L, -1))
                        ? lua_tostring(L, -1)
                        : "pas une chaine");
        }
        lua_settop(L, base);
    }

    // Several upvalues at once, in order, with mixed kinds.
    {
        char why[192] = "";
        const int base = lua_gettop(L);

        luaL_dostring(L,
                      "local a, b, c = '1', '2', '3'\n"
                      "triple = function(x) return a .. b .. c .. x end");
        lua_getfield(L, LUA_GLOBALSINDEX, "triple");
        const int chunk = lua_gettop(L);

        const std::string m = decrire(
            {arg_s("A"), arg_s("B"), arg_s("C")}, 'U');
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        verifie("trois upvalues-string sans erreur", rc >= 0, why);

        lua_pushstring(L, "!");
        if (lua_pcall(L, 1, 1, 0) == 0 && lua_type(L, -1) == LUA_TSTRING) {
            const char* r = lua_tostring(L, -1);
            verifie("  les trois sont lies : ABC!",
                    std::strcmp(r, "ABC!") == 0, r);
        } else {
            verifie("  les trois sont lies : ABC!", false,
                    lua_type(L, -1) == LUA_TSTRING ? lua_tostring(L, -1)
                                                   : "pas une chaine");
        }
        lua_settop(L, base);
    }

    // A standard-library upvalue, rebound to the worker's own global.
    {
        char why[192] = "";
        const int base = lua_gettop(L);

        luaL_dostring(L,
                      "local type = type\n"
                      "decideur = function(a) if type(a) == 'nil' then return 1 end return 0 end");
        lua_getfield(L, LUA_GLOBALSINDEX, "decideur");
        const int chunk = lua_gettop(L);

        // On NAIT pas dans le bac a sable ici, donc `type` n'est pas un
        // upvalue : on force la situation en l'assignant.
        luaL_dostring(L, "type = type");
        const std::string m = decrire({arg_s("type")}, 'U');
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        verifie("upvalue 'type' rebranche sans erreur", rc >= 0, why);
        lua_settop(L, base);
    }

    // A global the worker does not have must be REPORTED, never raised.
    {
        char why[192] = "";
        luaL_dostring(L,
                      "local absent_du_worker = 1\n"
                      "f3 = function() return absent_du_worker end");
        lua_getfield(L, LUA_GLOBALSINDEX, "f3");
        const int chunk = lua_gettop(L);
        const int base = chunk;  // le chunk EST la base : apply_meta doit
                                // rendre la pile exactement comme elle l'a
                                // trouvee
        const std::string m = decrire({arg_l("absent_du_worker")}, 'U');
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        char det[256];
        std::snprintf(det, sizeof(det), "rc=%d why=[%s] top=%d base=%d",
                      rc, why, lua_gettop(L), base);
        verifie("global absent -> -1, aucun raise",
                rc == -1 && why[0] != '\0', det);
        verifie("  et la pile est rendue", lua_gettop(L) == base);
    }

    // Le miroir : un global que le worker A bien doit se rebrancher.
    {
        char why[192] = "";
        luaL_dostring(L, "surcharge = 999\n"
                          "local surcharge = 0\n"
                          "f4 = function() return surcharge end");
        lua_getfield(L, LUA_GLOBALSINDEX, "f4");
        const int chunk = lua_gettop(L);
        const int base = chunk;
        const std::string m = decrire({arg_l("surcharge")}, 'U');
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        char det[256];
        std::snprintf(det, sizeof(det), "rc=%d why=[%s]", rc, why);
        verifie("global present -> rebranchement sans erreur", rc >= 0, det);

        lua_pushnumber(L, 0);
        if (lua_pcall(L, 1, 1, 0) == 0 && lua_type(L, -1) == LUA_TNUMBER) {
            char b[32];
            std::snprintf(b, sizeof(b), "%.0f", lua_tonumber(L, -1));
            verifie("  la valeur vient du global du worker : 999",
                    std::strcmp(b, "999") == 0, b);
        } else {
            verifie("  la valeur vient du global du worker : 999", false, "?");
        }
        lua_settop(L, base);
    }

    // An upvalue index past the end must be REPORTED. Without the getupvalue
    // pre-check, setupvalue returns nil, changes nothing, and the worker's body
    // then runs against a slot that was never set -- which looks, from the
    // outside, exactly like a feature that mysteriously does nothing.
    {
        char why[192] = "";
        luaL_dostring(L, "local u = 1  f5 = function() return u end");
        lua_getfield(L, LUA_GLOBALSINDEX, "f5");
        const int chunk = lua_gettop(L);
        const int base = chunk;
        // A la main : decrire() numrote 1..n, et c'est justement un index
        // hors de range qu'on veut.
        std::string m = "U N 3 7\n";
        m.push_back('\0');
        m.pop_back();
        const int rc = meta::apply_meta(L, chunk, m.c_str(),
                                        static_cast<int>(m.size()), true, why,
                                        sizeof(why));
        char det[256];
        std::snprintf(det, sizeof(det), "rc=%d why=[%s]", rc, why);
        verifie("index d'upvalue hors bornes -> signale, pas leve", rc == -1,
                det);
        verifie("  et la pile est rendue", lua_gettop(L) == base);
        lua_settop(L, 0);
    }

    // A truncated 'S' must be refused, not read past.
    {
        char why[192] = "";
        std::string m = "A S 1 999\ncourt\n";  // annonce 999 octets, en a 6
        m.push_back('\0');
        m.pop_back();
        const int base = lua_gettop(L);
        const int rc = meta::apply_meta(L, 0, m.c_str(),
                                        static_cast<int>(m.size()) - 1, false,
                                        why, sizeof(why));
        verifie("chaine annoncee trop longue -> -1", rc == -1, why);
        lua_settop(L, base);
    }

    lua_close(L);

    std::printf("\n%d ok, %d echec(s)\n", g_ok, g_ko);
    return g_ko ? 1 : 0;
}