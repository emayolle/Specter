// Specter.Internal — the Lua thread pump (implementation).
//
// See pump.h for why this module exists. Nothing here knows about a feature:
// the detour, the state discovery, the C API resolution, the chunk runner and
// the hook dispatch are the whole of it.

#include "pch-il2cpp.h"

#include "lua/bind.h"
#include "lua/capi.h"
#include "lua/pump.h"

#include <Windows.h>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "il2cpp/runtime.h"
#include "il2cpp/target.h"
#include "platform/hook/detour.h"
#include "platform/log.h"
#include "platform/perf.h"
#include "platform/seh.h"

namespace specter::lua {
namespace pump {
namespace {

// ---- Lua C API (xlua.dll, LuaJIT 5.1 ABI) ----------------------------------
//
// `lua_State` comes from capi.h now, which includes the vendored LuaJIT headers
// inside extern "C". It used to be `using lua_State = void;` here, written by
// hand because this file had no headers — and that is how two DIFFERENT types
// ended up sharing one name across the DLL. One declaration, from the header,
// everywhere.

using luaL_loadbuffer_fn = int(__cdecl*)(lua_State*, const char*, size_t,
                                         const char*);
using lua_pcall_fn = int(__cdecl*)(lua_State*, int, int, int);
using lua_gettop_fn = int(__cdecl*)(lua_State*);
using lua_settop_fn = void(__cdecl*)(lua_State*, int);
using lua_getglobal_fn = void(__cdecl*)(lua_State*, const char*);
using lua_type_fn = int(__cdecl*)(lua_State*, int);
using lua_tolstring_fn = const char*(__cdecl*)(lua_State*, int, size_t*);
using lua_toboolean_fn = int(__cdecl*)(lua_State*, int);
using lua_createtable_fn = void(__cdecl*)(lua_State*, int, int);
using lua_rawgeti_fn = void(__cdecl*)(lua_State*, int, int);
using lua_rawseti_fn = void(__cdecl*)(lua_State*, int, int);
using lua_pushlstring_fn = void(__cdecl*)(lua_State*, const char*, unsigned long long);
using lua_setfield_fn = void(__cdecl*)(lua_State*, int, const char*);
using lua_pushcclosure_fn = void(__cdecl*)(lua_State*, int(__cdecl*)(lua_State*), int);
using lua_pushstring_fn = void(__cdecl*)(lua_State*, const char*);
using lua_pushvalue_fn = void(__cdecl*)(lua_State*, int);
using lua_gettable_fn = void(__cdecl*)(lua_State*, int);
using lua_settable_fn = void(__cdecl*)(lua_State*, int);
using lua_setfenv_fn = int(__cdecl*)(lua_State*, int);
using lua_setmetatable_fn = int(__cdecl*)(lua_State*, int);

luaL_loadbuffer_fn p_loadbuffer = nullptr;
lua_pcall_fn p_pcall = nullptr;
lua_gettop_fn p_gettop = nullptr;
lua_settop_fn p_settop = nullptr;
lua_getglobal_fn p_getglobal = nullptr;
lua_type_fn p_type = nullptr;
lua_tolstring_fn p_tolstring = nullptr;
lua_toboolean_fn p_toboolean = nullptr;
lua_createtable_fn p_createtable = nullptr;
// Back for the registry anchors. They cost two exports and they are the only
// way the C API offers to say "keep this object alive" -- see the sandbox
// environment note above.
lua_rawgeti_fn p_rawgeti = nullptr;
lua_rawseti_fn p_rawseti = nullptr;
// lua_pushnil is a MACRO in Lua 5.1 (pushlstring of length 0), so there is no
// such export to look up.
lua_pushlstring_fn p_pushlstring = nullptr;
lua_setfield_fn p_setfield = nullptr;
lua_pushcclosure_fn p_pushcclosure = nullptr;
lua_pushstring_fn p_pushstring = nullptr;
lua_pushvalue_fn p_pushvalue = nullptr;
lua_gettable_fn p_gettable = nullptr;
lua_settable_fn p_settable = nullptr;
lua_setfenv_fn p_setfenv = nullptr;
lua_setmetatable_fn p_setmetatable = nullptr;

// The Lua registry is NOT used anywhere in this file, and that is a deliberate
// decision rather than an omission.
//
// LUA_REGISTRYINDEX is not a constant across the versions this code could meet:
// Lua 5.0 and 5.1 spell it -10000, Lua 5.2 and later spell it 0xFFF. Hardcoding
// the wrong one is not a compile error and not a runtime error -- it is an
// ordinary stack index that lands far out of bounds. Measured on this build:
// lua_rawgeti(L, -10000, key) does not return the registry, and the matching
// lua_rawseti wrote through a pointer computed from that out-of-range index.
//
// That is a wild write. It happened before any chunk ran, so no amount of
// editing the Lua preamble could have changed the symptom, and the symptom was
// an incoherent error that ignored every fix.
//
// The sandbox store is therefore a plain table, rebuilt per Execute, held on
// the Lua stack for the duration of the call. Nothing here guesses an index.

// ---- state ------------------------------------------------------------------

std::atomic<bool> g_api_ready{false};
std::atomic<bool> g_hook_installed{false};
std::atomic<bool> g_seen_state{false};
std::atomic<void*> g_lua_state{nullptr};
std::atomic<unsigned long long> g_ticks{0};

// The Lua registry index, found by probe on the first Execute; 0 when none of
// the documented candidates answered. With 0 there is nowhere to anchor the
// sandbox, so the store simply does not survive between Executes -- a
// limitation, not a failure. Constant-initialised like everything else here:
// no constructor runs at load.
std::atomic<int> g_registry_index{0};
std::atomic<void*> g_last_state{nullptr};  // last state we fired hooks for

// ---- detour ----------------------------------------------------------------

using common_update_fn = void (*)(void* self, void* method);
common_update_fn g_orig_common_update = nullptr;

// ---- hook tables ------------------------------------------------------------
//
// Fixed capacity and zero-initialised on purpose: the DLL is manually mapped,
// so a container with a constructor would run before the CRT guard is set up.
// Registration is explicit and happens from app::start(), before the pump can
// ever fire.

constexpr int kMaxHooks = 8;
state_fn g_state_hooks[kMaxHooks];
tick_fn g_tick_hooks[kMaxHooks];

// Set by a feature that wants to filter our own chunks out of its capture
// (see features/lua_dump). A filter keeps `lua/` from having to know that a
// feature exists — the dependency stays feature -> lua.
using chunk_filter_fn = bool (*)(const char* chunk_name);
chunk_filter_fn g_chunk_filter = nullptr;

// ---- xlua resolution -------------------------------------------------------

template <typename T>
void bind(HMODULE m, const char* name, T& out)
{
    out = reinterpret_cast<T>(::GetProcAddress(m, name));
}

// One answer to "are the pump's own symbols bound?", so the binding layer's
// check and the pump's check cannot drift apart.
bool pump_api_ready()
{
    return p_loadbuffer && p_pcall && p_gettop && p_settop && p_tolstring &&
           p_toboolean && p_getglobal && p_type && p_createtable &&
           p_setfield && p_pushcclosure && p_pushstring && p_pushvalue &&
           p_gettable && p_settable && p_setfenv && p_setmetatable;
}

bool resolve_xlua()
{
    if (g_api_ready.load(std::memory_order_relaxed)) {
        return true;
    }
    HMODULE m = ::GetModuleHandleW(L"xlua.dll");
    if (!m) {
        m = ::GetModuleHandleW(L"XLua.dll");
    }
    if (!m) {
        return false;
    }
    bind(m, "luaL_loadbuffer", p_loadbuffer);
    bind(m, "lua_pcall", p_pcall);
    bind(m, "lua_gettop", p_gettop);
    bind(m, "lua_settop", p_settop);
    bind(m, "lua_getglobal", p_getglobal);
    bind(m, "lua_type", p_type);
    bind(m, "lua_tolstring", p_tolstring);
    bind(m, "lua_toboolean", p_toboolean);
    bind(m, "lua_createtable", p_createtable);
    bind(m, "lua_rawgeti", p_rawgeti);
    bind(m, "lua_rawseti", p_rawseti);
    bind(m, "lua_pushlstring", p_pushlstring);
    bind(m, "lua_setfield", p_setfield);
    bind(m, "lua_pushcclosure", p_pushcclosure);
    bind(m, "lua_pushstring", p_pushstring);
    bind(m, "lua_pushvalue", p_pushvalue);
    bind(m, "lua_gettable", p_gettable);
    bind(m, "lua_settable", p_settable);
    bind(m, "lua_setfenv", p_setfenv);
    bind(m, "lua_setmetatable", p_setmetatable);
    if (!p_loadbuffer || !p_pcall || !p_gettop || !p_settop || !p_tolstring ||
        !p_toboolean || !p_getglobal || !p_type ||
        !p_createtable || !p_setfield || !p_pushcclosure ||
        !p_pushstring || !p_pushvalue || !p_gettable || !p_settable || !p_setfenv || !p_setmetatable) {
        log::error("lua: xlua.dll found but some Lua C API exports are missing");
        return false;
    }
    g_api_ready.store(true, std::memory_order_relaxed);
    log::info("lua: LuaJIT C API resolved from xlua.dll (%p)", (void*)m);

    // The binding layer runs INSIDE the sandbox this module builds, so it is
    // only usable if the pump's own resolution succeeded — which, at this point
    // in the function, it has. Asking keeps the two answers in one place: if
    // either table is ever short a symbol, the binding layer refuses instead of
    // registering trampolines onto null pointers.
    capi::resolve(m, &pump_api_ready);
    return true;
}

// ---- chunk execution (runs on the Lua thread) ------------------------------

constexpr int kMaxCode = 32 * 1024;

// The chunk is a FACTORY. C hands it everything it needs, by value: the
// specter table, the real globals, and the standard library functions. The
// preamble resolves no name from its own environment, because that
// environment is whatever luaL_loadbuffer gave the chunk and is not
// necessarily the game's _G.
//
// The factory NEVER raises. Everything the preamble does is wrapped in a
// pcall, so when it dies we still get a normal return -- carrying the stage
// it reached. C reads that third result and logs it. The preamble used to
// throw straight through, and an error raised inside a C function carries no
// position, which is why four fixes in a row guessed wrong.
//
//   read  k      -> our store first, then the game's real _G  (full access)
//   write k = v  -> the game already owns k, write the GAME's global
//   write k = v  -> otherwise keep it in our store
//
// `print` is a LOCAL, so the game's print is never touched.
//
// And why not setfenv(0, env), the idiomatic 5.1 form? Because LuaJIT does not
// implement it: measured, setfenv(0, t) leaves the environment untouched while
// setfenv(f, t) works. So the factory names itself and passes that name.
// NOUVEAU LECTEUR, LIS CE COMMENTAIRE.
//
// LE BAC A SABLE N'EXPOSE PAS LES VALEURS DE RETOUR DU CHUNK. Ce qui apparait
// dans le resultat, c'est ce que print a ecrit, plus les erreurs. Mesure :
//
//     return "X"                 -> sortie vide
//     local x = 1 return x, "Y"  -> sortie vide
//     print("X")                 -> "X"
//
// J'ai cru l'inverse en migrating une sonde de print vers return, et la
// position du joueur a cesse de s'afficher -- le C++ ne recevait rien, et
// n'avait rien a le dire. Une sonde qui echoue en silence est pire qu'une
// sonde qui echoue bruyamment.
//
// Si un jour le retour doit fonctionner, c'est __u qu'il faut lire dans la
// collection, pas ce qui sort de __b -- qui renvoie `true`. Mais ne change pas
// le prefixe sans raison : il tient tout l'isolement, et il l'a deja casse
// quatre fois.
constexpr char kPrefix[] =
    "local __f;\n"
    "__f=function(__store,__sp,__g,__env,pcall,setfenv,setmetatable,rawset,\n"
    "rawget,table,tostring,select,type,getfenv)\n"
    "local __o={}\n"
    "local __st='00 avant'\n"
    "local __t={pcall(function()\n"
    "local __b;__b=function()\n"
    "__st='10 store';\n"
    "__st='11 diag';__sp.__diag=tostring(getfenv(__f)==__g)\n"
    "local print=function(...)local t={}for i=1,select('#',...)do\n"
    "  t[#t+1]=tostring((select(i,...)))end\n"
    "  __o[#__o+1]=table.concat(t,'\\t')end\n"
    "__st='13 env'\n"
    "if __env==nil then\n"
    "  __env=setmetatable({},{\n"
    "    __index=function(_,k)local v=rawget(__store,k)\n"
    "      if v~=nil then return v end return __g[k] end,\n"
    "    __newindex=function(_,k,v)if rawget(__g,k)~=nil then\n"
    "      rawset(__g,k,v) else rawset(__store,k,v) end end})\n"
    "  rawset(__env,'specter',__sp)\n"
    "  rawset(__env,'env',function() return __g end)\n"
    "  rawset(__env,'__global',__g)\n"
    "end\n"
    "__st='14 setfenv'\n"
    "rawset(__sp,'__global',__g)\n"
    "setfenv(__f,__env)\n"
    "setfenv(__b,__env)\n"
    "__st='15 code'\n"
    "local __u={pcall(function()\n";

constexpr char kSuffix[] =
    "\nend)}"
    "__st='16 collecte';\n"
    "local __ok=table.remove(__u,1);"
    "if not __ok then __o[#__o+1]='ERROR: '..tostring(__u[1])"
    "else if #__u>0 then local t={}for i=1,#__u do t[i]=tostring(__u[i])end"
    "  __o[#__o+1]=table.concat(t,'\\t')end end\n"
    "return true\n"
    "end\n"
    "__st='20 appel du corps'\n"
    "local __r={pcall(__b)}\n"
    "if not __r[1] then\n"
    "  __o[#__o+1]='PREAMBLE: '..tostring(__r[2])\n"
    "  return table.concat(__o,'\\n'),false,__st\n"
    "end\n"
    "__st='30 fini'\n"
    "return table.concat(__o,'\\n'),true,__st,__env\n"
    "end)}\n"
    "local __fin=__st\n"
    "if not __t[1] then\n"
    "  return 'PREAMBLE: '..tostring(__t[2]),false,__fin,__env\n"
    "end\n"
    "return __t[2],__t[3],__t[4],__env\n"
    "end\nreturn __f\n";

// ---- diagnostics ------------------------------------------------------------
//
// Every name the sandbox preamble uses is read out of the game's globals, and
// the preamble CALLS several of them (getfenv, setmetatable, rawset, setfenv,
// pcall, table.*, tostring, select). A game is free to shadow any of those, and
// when one of them is not a function the preamble dies with a bare
// "attempt to call a table value" -- no position, because the raise happens
// inside a C function.
//
// Guessing has already cost two wrong fixes. So: ask. This reads each name the
// preamble depends on, reports its type once per state, and names the offenders.
// The whole cost is one log line, paid once.
const char* type_name(int t)
{
    switch (t) {
    case 0: return "nil";
    case 1: return "boolean";
    case 2: return "lightuserdata";
    case 3: return "number";
    case 4: return "string";
    case 5: return "table";       // <-- the one that breaks a call
    case 6: return "function";
    case 7: return "userdata";
    case 8: return "thread";
    default: return "?";
    }
}

void probe_globals(lua_State* L)
{
    static const char* kNeed[] = {
        "getfenv", "setfenv", "setmetatable", "rawset", "rawget",
        "pcall",   "table",   "tostring",     "select", "print",
    };
    char buf[512];
    int n = 0;
    n += std::snprintf(buf + n, sizeof(buf) - n, "globals requis :");
    for (const char* name : kNeed) {
        p_getglobal(L, name);
        const int t = p_type(L, -1);
        // Flag anything that is not a function: the preamble calls all of them
        // -- except the table library, which is a table we index into.
        const bool want_fn = (std::strcmp(name, "table") != 0);
        n += std::snprintf(buf + n, sizeof(buf) - n, " %s=%s%s",
                           name, type_name(t),
                           (want_fn && t != 6) ? " <<< PAS UNE FONCTION" : "");
        p_settop(L, -2);
    }
    log::info("lua: %s", buf);

    // The library is a table, so its FIELDS are what actually get called. A
    // framework that replaces `table` can leave remove/concat as anything, and
    // that is invisible to a type check on the table itself.
    static const char* kFields[] = {"remove", "concat", "insert"};
    for (const char* f : kFields) {
        p_getglobal(L, "table");
        p_pushstring(L, f);
        p_gettable(L, -2);
        const int t = p_type(L, -1);
        log::info("lua:   table.%s = %s%s", f, type_name(t),
                  t == 6 ? "" : " <<< PAS UNE FONCTION");
        p_settop(L, -3);
    }
}

// The standard library the preamble calls, pushed by C and taken by the factory
// as parameters. Same order as kPrefix's parameter list.
constexpr const char* kPreambleFns[] = {
    "pcall", "setfenv", "setmetatable", "rawset", "rawget",
    "table", "tostring", "select", "type", "getfenv",
};

// The user's own code, echoed on failure. Three fixes in a row have missed,
// every time because the failure was reported without the input that caused
// it. The code is short, and it is the one thing the log was missing.
void log_chunk(const char* code, int len)
{
    char buf[768];
    int n = 0;
    n += std::snprintf(buf + n, sizeof(buf) - n, "chunk (%d o) : ", len);
    for (int i = 0; i < len && n < static_cast<int>(sizeof(buf)) - 8; ++i) {
        const unsigned char c = static_cast<unsigned char>(code[i]);
        // Keep it on one log line: newlines become \n, quotes are escaped.
        if (c == '\n') {
            buf[n++] = '\\'; buf[n++] = 'n';
        } else if (c == '\r') {
            // dropped
        } else if (c == '"' || c == '\\') {
            buf[n++] = '\\'; buf[n++] = static_cast<char>(c);
        } else if (c >= 0x20 && c < 0x7f) {
            buf[n++] = static_cast<char>(c);
        } else {
            n += std::snprintf(buf + n, sizeof(buf) - n, "\\x%02x", c);
        }
    }
    buf[n] = '\0';
    log::info("lua: %s", buf);
}

// ---- the `specter` namespace ------------------------------------------------
//
// Built per run and injected into the sandbox env, NEVER into the game's _G.
// That is what makes it ours alone: a game script resolving `specter` goes
// through the real globals and finds nothing, while our own chunks resolve it in
// the environment we handed them. No global is created, so there is nothing to
// collide with and nothing to enumerate out of _G.

// ---- finding the registry, without guessing --------------------------------
//
// The env has to be anchored somewhere the GC will keep, and the registry is
// the only such place reachable from the C API. So the registry index has to be
// identified — and it is not a constant across versions:
//
//     -10000    Lua 5.0 / 5.1      0xFFF    Lua 5.2+
//
// Hardcoding the wrong one is not a compile error and not a runtime error: it is
// an ordinary out-of-range stack index. Writing through it wrote through a
// pointer computed from an invalid index -- a wild write, before any chunk ran.
//
// Two obvious verifications are both WRONG, and the offline harness said so
// before they ever shipped:
//   * "the registry contains print"    -- it does not
//   * "the registry contains _LOADED"  -- it does, but so does _G in 5.1, so it
//                                         does not tell the two apart
//
// What is left is a read-only probe over the documented candidates. READ ONLY:
// a probe that writes is the very bug it is looking for. It never tries an
// arbitrary index — only the two the manuals name — and it reports what it
// finds so the choice is visible in the log rather than assumed.
//
// Candidates are the two registry constants, never the globals ones (-10002 /
// 2): those are different indices, so finding _LOADED at a candidate means the
// candidate IS the registry, not the globals.
int find_registry_index(lua_State* L)
{
    static const int kCandidates[] = {-10000, 0xFFF};
    char buf[640];
    int n = 0;
    for (int idx : kCandidates) {
        // Two keys, and the second is the decisive one. "FILE*" is the registry's
        // own file-handle list: nothing else holds it, and the globals never do.
        // "_LOADED" alone would not do -- it is a global in 5.1 too.
        int found = 0;
        p_pushstring(L, "_LOADED");
        p_gettable(L, idx);
        const bool loaded = p_type(L, -1) == 5;
        p_settop(L, -2);

        p_pushstring(L, "FILE*");
        p_gettable(L, idx);
        const bool files = p_type(L, -1) == 5;
        p_settop(L, -2);

        if (loaded && files) {
            found = 1;
        }
        n += std::snprintf(buf + n, sizeof(buf) - n, " %d[_LOADED=%d,FILE*=%d]",
                           idx, loaded ? 1 : 0, files ? 1 : 0);
        if (found) {
            log::info("lua: sonde registre : %s", buf);
            log::info("lua: registre trouve a l'index %d", idx);
            return idx;
        }
    }
    log::error("lua: sonde registre : %s", buf);
    log::error("lua: aucun index de registre reconnu -- le store restera par "
               "Execute, rien ne casse");
    return 0;
}

int specter_log(lua_State* L)
{
    const int top = p_gettop(L);
    if (top < 2) {  // index 1 is the function itself, not an argument
        return 0;
    }
    char buf[1024];
    int n = 0;
    for (int i = 2; i <= top; ++i) {
        std::size_t len = 0;
        const char* s = p_tolstring(L, i, &len);
        if (!s || len == 0) {
            continue;
        }
        if (n < static_cast<int>(sizeof(buf)) - 2) {
            buf[n++] = ' ';
        }
        const int room = static_cast<int>(sizeof(buf)) - n - 1;
        const int c = len < static_cast<std::size_t>(room)
                          ? static_cast<int>(len)
                          : room;
        std::memcpy(buf + n, s, static_cast<std::size_t>(c));
        n += c;
    }
    buf[n] = '\0';
    log::info("specter| %s", buf);
    return 0;
}

// ---- the sandbox environment, built once per Lua state ---------------------
//
// WHY IT EXISTS AT ALL: a Lua table only survives while something the garbage
// collector can see still points at it. A void* in this module is not such a
// thing -- the collector does not know the module exists -- so a table kept
// only on our side is collected and the pointer dangles. There is no userdata
// that fixes this: a userdata holds a pointer, not a reference.
//
// That leaves the registry as the only anchor the C API offers. Which is why
// this file used to have no anchor at all, and why a variable set by one
// Execute died before the next: guessing the registry index was writing through
// a wild pointer, so the store was dropped instead. That was a retreat, not a
// solution.
//
// The index is now FOUND rather than assumed. See find_registry_index().
//
// WHAT THIS COSTS, stated rather than discovered: the environment is now in the
// registry, so a script with debug.getregistry() can walk to it. Nova anchors
// its table there too and hides it behind a debug.getregistry hook; we do not
// hook it, because hiding our tables from the game's scripts is concealment,
// not isolation. What we do instead is not sign our own work: the key is
// derived from the state rather than being a labelled constant, and the store
// hangs off the environment at an integer key rather than a field called
// __store.

// ---- ANCHORS ----------------------------------------------------------------
//
// kEnableAnchors gates the two registry WRITES. Flipping it to false puts the
// sandbox back exactly as it was before anchoring existed: the environment is
// built per Execute and the store does not survive between them. Nothing else
// changes, and the probe still runs — it is read-only.
//
// It exists because the anchored path crashed the game ONCE. It did not
// reproduce: with the anchors off, run() still reads g_registry_index, so it
// still reads the env and still writes it -- on the first Execute the two
// settings are the same code path, and three Executes ran clean. So the write
// is not the culprit, and the crash was not deterministic.
//
// Which is worse than a known bug, so the switch stays: it is the cheapest way
// to isolate anything that comes back.
constexpr bool kEnableAnchors = true;

// The two anchor keys. Derived from the state pointer, not labelled constants:
// a key spelled "SPECTER" in a table the game can walk is a signature, and this
// whole file exists because guessing is how we got here.
int env_key(const void* L)
{
    return static_cast<int>(0x53505245u ^
           (static_cast<unsigned long long>(reinterpret_cast<unsigned long long>(L)) >> 4));
}
int store_key()
{
    return 0x53505254;  // 'SPRT', an integer field on the environment
}

// What build_specter() leaves on the stack: [store, specter]. Both are
// arguments to the factory, so this number belongs to BOTH the contract check
// and the call's argument count -- kStackArgs is derived from it below.
//
// It is one constant because those two used to be written out separately, and
// they disagreed twice in a row: the check expected one value, the call expected
// two, and each version of the guard refused work that was fine.
constexpr int kSpecValues = 2;

void build_specter(lua_State* L, int reg)
{
    if (!kEnableAnchors) {
        reg = 0;
    }
    // The store must be the SAME table the environment's __index/__newindex close
    // over, or `specter.store` would name a table nothing actually uses. So it
    // hangs off the environment at an integer key, and only the environment is
    // anchored in the registry.
    // Did we just create the environment, or is it the one a previous Execute
    // anchored? Decided HERE, once, and the binding layer keys off it.
    bool env_is_new = true;

    if (reg != 0) {
        p_rawgeti(L, reg, env_key(L));     // [env]
        if (p_type(L, -1) == 5) {
            env_is_new = false;
            p_rawgeti(L, -1, store_key());  // [env, store | nil]
            if (p_type(L, -1) != 5) {
                // Drop the nil BEFORE creating the new store. It used to stay
                // on the stack, which put the env two slots down instead of
                // three -- so lua_rawseti was handed the NIL and wrote through
                // hvalue(nil). That is a wild write, and it killed the game on
                // the second Execute of every session: the first one builds the
                // environment, the second one is the first to take this branch.
                p_settop(L, -2);             // [env]
                p_createtable(L, 0, 8);     // [env, store]
                p_pushvalue(L, -1);         // [env, store, store]
                p_rawseti(L, -3, store_key());
            }
            // The env is SCRATCH here: it is re-pushed from the registry in
            // run(). Leaving it on the stack would put one value more than the
            // argument count, and the call would land on it instead of the
            // factory. Same class of bug as the store/specter offset before.
            p_settop(L, -2);                // [store]
        } else {
            p_settop(L, -2);
            p_createtable(L, 0, 8);         // [store]
        }
    } else {
        p_createtable(L, 0, 8);             // [store]
    }
    // [store]

    p_createtable(L, 0, 4);  // [store, specter]

    p_pushstring(L, "1.0");
    p_setfield(L, -2, "version");

    p_pushvalue(L, -2);   // [store, specter, store]
    p_setfield(L, -2, "store");

    p_pushcclosure(L, &specter_log, 0);
    p_setfield(L, -2, "log");


    // NOTE: there is no `env` here any more, and there was a bug in it.
    //
    // It was a C closure that did lua_gettable(L, 1) to fetch specter.__global.
    // Index 1 inside a C function is the FUNCTION, not the first argument -- so
    // specter.env() read `func.__global`, which is nil, always. It only appeared
    // to work because specter.env(specter) passed the table explicitly.
    //
    // The offline harness could not have caught that: it stood a Lua closure in
    // for the C one, so it tested a different program than the one that ships.
    //
    // The factory builds `env` in Lua instead, where it closes over __g and
    // there is no index to get wrong.

    // Hand the store to the preamble under the internal name it reads.
    p_pushvalue(L, -2);   // [store, specter, store]
    p_setfield(L, -2, "__store");
    // [store, specter]  -- TWO values, and the contract says two.

    // Install the binding layer INTO `specter`, which is at -2. Never into _G:
    // getGlobalNamespace is the one LuaBridge call that would put it there, and
    // the leak sweep over the game's globals (0, 0, 0) is what we would lose.
    // install() leaves the stack untouched, so the kSpecValues check in run()
    // still means what it says.
    // -1, NOT -2. The stack here is [chunk, store, specter]: p_loadbuffer left
    // the chunk, build_specter added two values. So -2 is the STORE and -1 is
    // specter. Passing -2 registered every binding into the store, where Lua
    // never looks for them — `specter.reset` was nil while `specter.store.reset`
    // was a function. install() now verifies the target for itself.
    //
    // ONLY WHEN THE ENVIRONMENT IS NEW.
    //
    // The preamble does `rawset(__env,'specter',__sp)` inside `if __env==nil`,
    // so on a later Execute the environment keeps the specter table from the
    // FIRST one — while this specter is a brand new table nobody will ever look
    // at. Registering into it is work thrown away, and it is what made the game
    // die on the second Execute: the second registration ran while Lua was about
    // to use the first table's metatable.
    //
    // One registration per environment. The bindings live in the anchored table,
    // which is exactly the thing persistence relies on.
    if (env_is_new) {
        bind::install(L, -1);
    }
}


// ---- the pump itself -------------------------------------------------------

void pump_impl(void* self)
{
    // Notre part du temps de frame sur le thread Lua. Les return multiples
    // plus bas sont tous couverts par le garde : c'est le cout de NOTRE
    // passage, pas celui du jeu. Voir perf.h.
    const long long perf_t0 = perf::now_ns();
    struct PerfGuard {
        long long t0;
        ~PerfGuard() { perf::add(perf::kPump, perf::now_ns() - t0); }
    } perf_guard{perf_t0};

    g_ticks.fetch_add(1, std::memory_order_relaxed);

    if (!resolve_xlua()) {
        return;
    }

    char* env = *reinterpret_cast<char**>(reinterpret_cast<char*>(self) +
                                          target::kLuaManager_luaenv);
    char* L = env ? *reinterpret_cast<char**>(env + target::kLuaEnv_rawL) : nullptr;
    if (!L) {
        return;
    }
    g_seen_state.store(true, std::memory_order_relaxed);
    g_lua_state.store(L, std::memory_order_relaxed);

    // The game recreates the state on scene reload / re-login, so per-state
    // hooks fire again for a brand new pointer. Keyed on the pointer, never on a
    // boolean: a state can come back different after a disconnect.
    if (g_last_state.load(std::memory_order_relaxed) != L) {
        g_last_state.store(L, std::memory_order_relaxed);
        for (int i = 0; i < kMaxHooks; ++i) {
            if (g_state_hooks[i]) {
                g_state_hooks[i](L);
            }
        }
    }

    for (int i = 0; i < kMaxHooks; ++i) {
        if (g_tick_hooks[i]) {
            g_tick_hooks[i](L);
        }
    }
}

// A bug in our Lua work must never take the whole game down. platform/seh.h
// explains why SEH and not a C++ try/catch.
void pump(void* self)
{
    SPECTER_SEH_BEGIN
    pump_impl(self);
    SPECTER_SEH_END("lua: work skipped for this frame")
}

void common_update_hook(void* self, void* method)
{
    pump(self);
    if (g_orig_common_update) {
        g_orig_common_update(self, method);
    }
}

}  // namespace

// ---- public API ------------------------------------------------------------

void run(lua_State* L, const char* code, int len, result_sink sink)
{
    if (!L || !code || len <= 0 || !sink) {
        return;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    static char src[kMaxCode + sizeof(kPrefix) + sizeof(kSuffix)];
    const int plen = static_cast<int>(sizeof(kPrefix) - 1);
    const int slen = static_cast<int>(sizeof(kSuffix) - 1);
    std::memcpy(src, kPrefix, static_cast<std::size_t>(plen));
    std::memcpy(src + plen, code, static_cast<std::size_t>(len));
    std::memcpy(src + plen + len, kSuffix, static_cast<std::size_t>(slen));

    // The name our chunks carry. Lua's '@' prefix means "this is a file name",
    // so errors read `specter\client\...\:12:` instead of `[string "..."]:12:`,
    // and debug.getinfo reports a source rather than an opaque marker.
    //
    // It is shaped like the game's own script paths — drive, client, LuaScripts,
    // Core — so that anything reading a chunk name sees the same KIND of string
    // it sees all day. It is not one of the game's paths, and it does not claim
    // to be: the first segment says specter, and it stays there whatever else we
    // do. Borrowing a real script's path would be camouflage, and it would not
    // survive contact with a dumper anyway: the source text is ours, and the
    // factory's shape (12 parameters, vararg-free) is not any game script's.
    // The first segment is the honest part, so it is the part we keep.
    constexpr char kChunkName[] =
        "@specter\\client\\LuaScripts\\Core\\Timer\\SpecterManager.lua";
    const bool suppressed =
        g_chunk_filter != nullptr && g_chunk_filter(kChunkName);

    // Once per process: report what the game's globals actually are, since a
    // shadowed name there is silent until it kills a chunk. And establish
    // whether there is a registry index we can anchor the env in — without one,
    // the sandbox store simply does not survive between Executes, which is a
    // limitation, not a failure.
    static bool probed = false;
    if (!probed) {
        probed = true;
        probe_globals(L);
        const int reg = find_registry_index(L);
        g_registry_index.store(reg, std::memory_order_relaxed);
    }

    const int top = p_gettop(L);
    // 0 when the probe found no registry: there is nowhere to anchor anything,
    // so the environment is rebuilt per Execute and the store does not survive.
    const int reg = g_registry_index.load(std::memory_order_relaxed);
    if (!suppressed &&
        p_loadbuffer(L, src, static_cast<size_t>(plen + len + slen),
                     kChunkName) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua load error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (suppressed) {
        sink(true, "", 0);
        p_settop(L, top);
        return;
    }

    // Call 1: the chunk returns its factory closure.
    if (p_pcall(L, 0, 1, 0) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        sink(false, e ? e : "(lua load error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }
    if (p_type(L, -1) != 6) {  // LUA_TFUNCTION
        sink(false, "chunk did not return a function", 29);
        p_settop(L, top);
        return;
    }

    // Call 2: hand it everything the preamble needs, by value.
    //
    // The order below is the factory's parameter order, and it is the ONLY
    // thing tying the two together. Read the names here, not in the chunk: the
    // environment luaL_loadbuffer gives a chunk is not necessarily the game's
    // _G, and resolving them in Lua tied the preamble to whatever that is.
    const int before_specter = p_gettop(L);
    build_specter(L, reg);
    // build_specter's contract, checked HERE at the boundary where a violation is
    // still cheap: the guard further down runs too late for anything that
    // crashes inside build_specter itself, and that is where the deaths were.
    //
    // TWO values, not one: [store, specter]. Both are arguments to the factory.
    // The number lives in kSpecValues because kStackArgs is built from it --
    // one constant, so the check and the call can never disagree again. The two
    // previous versions of this guard disagreed with the code (once by measuring
    // from `top`, which predates the chunk, and once by expecting one) and both
    // refused good calls.
    const int left = p_gettop(L) - before_specter;
    if (left != kSpecValues) {
        log::error("lua: build_specter a laisse %d valeur(s) au lieu de %d -- "
                   "appel annule", left, kSpecValues);
        sink(false, "(internal) build_specter broke the stack contract", 45);
        p_settop(L, top);
        return;
    }
    p_getglobal(L, "_G");  // the real globals, via the path the probe verified
    // The environment from a previous run, or nil so the factory builds one.
    if (reg != 0) {
        p_rawgeti(L, reg, env_key(L));
    } else {
        p_pushlstring(L, nullptr, 0);  // pushnil is a macro in 5.1
    }
    for (const char* fn : kPreambleFns) {
        p_getglobal(L, fn);
    }
    // build_specter leaves [store, specter] (kSpecValues), then _G and env, plus
    // the ten library functions. The argument count must include the store AND
    // specter, or the call lands on `store` instead of the factory.
    constexpr int kNFn =
        static_cast<int>(sizeof(kPreambleFns) / sizeof(*kPreambleFns));
    // kSpecValues + _G + env + the functions.
    constexpr int kStackArgs = kSpecValues + 2 + kNFn;
    // Verify what we are about to hand over, EVERY call, not once. Offsets are
    // DERIVED, never written down -- counting by hand caused this bug, and then
    // caused a wrong "fix" to this probe itself.
    //
    // This used to be gated behind a `probed` flag. That was the second time
    // the same class of bug got past it: a helper that leaves one value more on
    // the first call than on the later ones shifts the callee by one, and the
    // only run whose depth was ever checked was the one that was fine.
    //
    // So: check every time, and if the depth is not what the argument count
    // says it must be, DO NOT CALL. A loud refusal beats a silent mis-call.
    {
        const int depth = p_gettop(L) - top;
        if (depth != kStackArgs + 1) {
            log::error("lua: profondeur %d, callee attendu a -%d -- appel "
                       "annule, la pile ne tient pas son contrat",
                       depth, kStackArgs + 1);
            sink(false, "(internal) stack depth mismatch before the call", 46);
            p_settop(L, top);
            return;
        }
        // The callee must be a function. Everything else must not be callable.
        if (p_type(L, -kStackArgs - 1) != 6) {
            log::error("lua: l'appelee n'est pas une fonction (type %d) a -%d",
                       p_type(L, -kStackArgs - 1), kStackArgs + 1);
            sink(false, "(internal) callee is not a function", 34);
            p_settop(L, top);
            return;
        }
        // Types of the ten dependencies, every call: cheap, and the only thing
        // that has ever caught a shifted stack in this file.
        //
        // Nine are functions; `table` is the library, a TABLE, and what the
        // preamble calls is its `remove`/`concat` fields. A uniform "must be a
        // function" test rejects it -- which is what the first version of this
        // check did, and the guard then refused a perfectly good call.
        for (int i = 0; i < kNFn; ++i) {
            const bool is_lib = std::strcmp(kPreambleFns[i], "table") == 0;
            const int want = is_lib ? 5 : 6;  // LUA_TTABLE / LUA_TFUNCTION
            const int got = p_type(L, -(kNFn - i));
            if (got != want) {
                log::error("lua: %s devrait etre de type %d, est de type %d, "
                           "a -%d -- appel annule", kPreambleFns[i], want, got,
                           kNFn - i);
                sink(false, "(internal) a dependency has the wrong type", 44);
                p_settop(L, top);
                return;
            }
        }
    }
    if (p_pcall(L, kStackArgs, 4, 0) != 0) {
        std::size_t n = 0;
        const char* e = p_tolstring(L, -1, &n);
        log_chunk(code, len);
        sink(false, e ? e : "(lua runtime error)", static_cast<int>(n));
        p_settop(L, top);
        return;
    }

    // Stack: [text, ok, step, env]. The factory catches its own failures, so
    // reaching here means it returned normally; `step` is simply where it got
    // to, and `env` is the environment it used -- built on this run, or reused
    // from a previous one.
    std::size_t n = 0;
    const char* text = p_tolstring(L, -4, &n);
    const bool ok = p_toboolean(L, -3) != 0;
    std::size_t sn = 0;
    const char* step = p_tolstring(L, -2, &sn);
    if (reg != 0 && p_type(L, -1) == 5) {
        // Anchor it. Idempotent: on later runs this re-anchors the same table,
        // so there is no "first run" special case to get wrong.
        p_rawseti(L, reg, env_key(L));
    }
    if (!ok) {
        log::info("lua: le bac a sable a echoue a l'etape '%.*s'",
                  static_cast<int>(sn), step ? step : "?");
    }
    sink(ok, text ? text : "", static_cast<int>(n));
    p_settop(L, top);
}


bool install()
{
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        const std::uintptr_t base = il2cpp::module_base();
        if (base == 0) {
            log::error("lua: GameAssembly.dll not mapped - no Lua bridge");
            return false;
        }
        // Not named `target`: that would shadow the target namespace right
        // where we need to qualify the RVA.
        void* site = reinterpret_cast<void*>(base + target::kCommonUpdateRva);
        if (specter::hook::install(
                site, reinterpret_cast<void*>(&common_update_hook),
                reinterpret_cast<void**>(&g_orig_common_update),
                "LuaManager.CommonUpdate")) {
            g_hook_installed.store(true, std::memory_order_relaxed);
        } else {
            log::error("lua: CommonUpdate hook failed - Lua disabled");
            return false;
        }
    }

    if (!resolve_xlua()) {
        log::info("lua: xlua.dll not loaded yet - will retry from the pump");
    }
    return g_hook_installed.load(std::memory_order_relaxed);
}

bool ready()
{
    return g_hook_installed.load(std::memory_order_relaxed) &&
           g_seen_state.load(std::memory_order_relaxed);
}

unsigned long long ticks()
{
    return g_ticks.load(std::memory_order_relaxed);
}

void* state()
{
    return g_lua_state.load(std::memory_order_relaxed);
}

bool add_state_hook(state_fn fn)
{
    if (!fn) {
        return false;
    }
    for (int i = 0; i < kMaxHooks; ++i) {
        if (!g_state_hooks[i]) {
            g_state_hooks[i] = fn;
            return true;
        }
    }
    return false;
}

bool add_tick_hook(tick_fn fn)
{
    if (!fn) {
        return false;
    }
    for (int i = 0; i < kMaxHooks; ++i) {
        if (!g_tick_hooks[i]) {
            g_tick_hooks[i] = fn;
            return true;
        }
    }
    return false;
}

void set_chunk_filter(chunk_filter_fn fn)
{
    g_chunk_filter = fn;
}

const char* status()
{
    static char buf[160];
    if (!g_hook_installed.load(std::memory_order_relaxed)) {
        return "hook not installed";
    }
    if (!g_api_ready.load(std::memory_order_relaxed)) {
        return "waiting for xlua.dll";
    }
    if (!g_seen_state.load(std::memory_order_relaxed)) {
        return "waiting for LuaManager.CommonUpdate";
    }
    std::snprintf(buf, sizeof(buf), "ready - L=%p, %llu ticks",
                  g_lua_state.load(std::memory_order_relaxed),
                  static_cast<unsigned long long>(
                      g_ticks.load(std::memory_order_relaxed)));
    return buf;
}

}  // namespace pump
}  // namespace specter::lua