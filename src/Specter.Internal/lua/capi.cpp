// Specter.Internal — runtime resolution of the Lua C API (implementation).
//
// See capi.h for the extern "C" story, which is the part that matters.
//
// The pointers below are declared with `decltype(&lua_x)`, so a pointer type
// cannot disagree with the header: if lua.h changes a signature, these follow
// it at compile time instead of quietly mismatching at run time. Writing the
// typedefs by hand is what pump.cpp used to do, and a hand-written signature is
// a signature that can be wrong without the compiler noticing.

#include "pch-il2cpp.h"

#include "lua/capi.h"

#include <Windows.h>

#include <cstdio>

#include "platform/log.h"

namespace specter::lua::capi {

// DEFINITIONS. capi.h only declares them (`extern`), which is what lets
// capi_shim.cpp forward to them. Without a definition here the LINKER fails and
// names every one — which is the intended alarm: a build error now, not a null
// pointer called in the game later.
//
// Every one starts null on purpose. Nothing may call the shim before
// resolve() has bound it, and bind::install refuses when ready() is false.

#define CAPI_DEFINE(name) decltype(&::name) p_##name = nullptr;
CAPI_SYMBOLS(CAPI_DEFINE)
#undef CAPI_DEFINE

namespace {

int g_bound = 0;
int g_total = 0;
bool g_ready = false;

// Names we could not bind, so the log can say WHICH ones rather than only that
// it did not work. 48 is room for the whole set plus slack.
constexpr int kMaxMissing = 48;
const char* g_missing[kMaxMissing] = {};
int g_missing_count = 0;

void note_missing(const char* name)
{
    if (g_missing_count < kMaxMissing) {
        g_missing[g_missing_count++] = name;
    }
}

char* join_missing(char* buf, std::size_t cap)
{
    std::size_t n = 0;
    for (int i = 0; i < g_missing_count; ++i) {
        const int w = std::snprintf(buf + n, cap - n, "%s%s",
                                    i ? ", " : "", g_missing[i]);
        if (w <= 0 || static_cast<std::size_t>(w) >= cap - n) {
            break;
        }
        n += static_cast<std::size_t>(w);
    }
    buf[n] = '\0';
    return buf;
}

}  // namespace

bool resolve(void* lua_module, bool (*pump_ready)())
{
    if (lua_module == nullptr) {
        log::error("lua: module Lua absent -- couche de binding desactivee");
        return false;
    }
    int missing = 0;
    g_bound = 0;
    g_total = 0;

    // The same one line for every symbol, so none can be forgotten: a name
    // added to CAPI_SYMBOLS is bound here, and the totals cannot drift from the
    // list.
#define CAPI_BIND(name)                                                        \
    ++g_total;                                                                 \
    p_##name = decltype(p_##name)(::GetProcAddress(                           \
        static_cast<HMODULE>(lua_module), CAPI_NAME(name)));                   \
    if (p_##name == nullptr) {                                                \
        note_missing(CAPI_NAME(name));                                         \
        ++missing;                                                             \
    } else {                                                                   \
        ++g_bound;                                                             \
    }
    CAPI_SYMBOLS(CAPI_BIND)
#undef CAPI_BIND

    // The binding layer is only usable if the pump's own symbols are bound too —
    // it runs inside the sandbox the pump builds. Ask rather than assume.
    //
    // NOT counted in g_total: it is not a symbol, it is a question. Counting it
    // made a healthy run report "46/47", which reads exactly like one symbol
    // missing — the worst possible way to say "everything is fine".
    if (pump_ready == nullptr || !pump_ready()) {
        note_missing("pump: au moins un symbole de base manque");
        ++missing;
    }

    g_ready = (missing == 0);
    if (!g_ready) {
        log::error("lua: couche de binding REFUSEE -- %d symbole(s) manquant(s) "
                   "sur %d. RIEN ne sera enregistre.",
                   missing, g_total);
        char buf[1024];
        log::error("lua: manquants : %s", join_missing(buf, sizeof(buf)));
    } else {
        log::info("lua: couche de binding prete -- %d/%d symboles lies depuis "
                  "xlua.dll", g_bound, g_total);
    }
    return g_ready;
}

bool ready()
{
    return g_ready;
}

int bound_count()
{
    return g_bound;
}

int required_count()
{
    return g_total;
}

const char* missing_summary()
{
    static char buf[1024];
    return join_missing(buf, sizeof(buf));
}

}  // namespace specter::lua::capi