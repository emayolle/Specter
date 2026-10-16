// Specter.Internal — runs scripts/init.lua at the start of every new lua_State.
//
// See init.h for why this exists and what it replaces.

#include "pch-il2cpp.h"

#include "features/console/console.h"
#include "features/init/init.h"
#include "lua/pump.h"
#include "platform/log.h"

#include <cstring>

#include "lua_init.h"       // generated/lua_init.h,      from scripts/init.lua
#include "lua_autofarm.h"   // generated/lua_autofarm.h, from scripts/autofarm_loop.lua

namespace specter::features {
namespace init {
namespace {

// One-shot per state: the pump calls state hooks once when it notices a
// lua_State it has not seen. A reconnect makes a new one, and the script has
// to run again — that is the whole point of the mechanism.
void on_new_lua_state(void* L)
{
    if (L == nullptr) {
        return;
    }
    // UN SEUL CHUNK, DANS L'ORDRE.
    //
    // La file d'attente du canal init est de profondeur 1 et REMPLACE : deux
    // submit successifs, et le premier peut disparaitre avant d'etre draine. Donc
    // pas deux envois -- on concatene, et l'ordre est garanti par construction.
    // L'autofarm lit `specter.var.autofarm` et pose son pilote, donc il doit
    // passer APRES init.lua, qui pose les bindings.
    // `sizeof(kInitScript)` vaut 8 : c'est un `const char*`, pas le tableau.
    // La premiere version dimensionnait donc le tampon a 16 octets, la garde
    // declenchait, et le bootstrap ne partait JAMAIS -- avec un build vert et
    // aucun avertissement. La taille se deduit de la longueur, pas du type.
    static const int kInitLen =
        static_cast<int>(std::strlen(lua::init::kInitScript));
    static const int kAutoLen =
        static_cast<int>(std::strlen(lua::init::kAutofarmLoop));
    static char code[kInitLen + kAutoLen + 2];
    static bool sized = false;
    if (!sized) {
        static_assert(sizeof(code) > sizeof(lua::init::kInitScript) + 16,
                      "le tampon doit suivre la LONGUEUR des scripts, pas sizeof "
                      "d'un pointeur");
        sized = true;
    }

    const int l1 = kInitLen;
    const int l2 = kAutoLen;
    int len = 0;
    if (l1 <= 0 || l2 <= 0) {
        return;
    }
    std::memcpy(code, lua::init::kInitScript, static_cast<std::size_t>(l1));
    code[l1] = '\n';
    std::memcpy(code + l1 + 1, lua::init::kAutofarmLoop, static_cast<std::size_t>(l2));
    len = l1 + 1 + l2;
    // Through the console's queue rather than a direct pump::run(): the state
    // hook runs from inside the pump, and the queue is how every other feature
    // gets its Lua onto the Lua thread on a tick instead of re-entering the
    // pump from within itself.
    if (!console::submit(console::kChannelInit, code, len)) {
        log::error("init: file d'attente refusee -- scripts/init.lua ne "
                   "s'executera pas pour cet etat");
    }
}

}  // namespace

bool install()
{
    return lua::pump::add_state_hook(&on_new_lua_state);
}

}  // namespace init
}  // namespace specter
