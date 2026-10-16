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
#include "lua_aniai.h"      // generated/lua_aniai.h,    from scripts/ani_ai.lua

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
    // Les trois scripts, dans l'ordre, concatenes en UN chunk.
    //
    // L'ordre est une dependance, pas un hasard : init.lua pose les bindings,
    // autofarm_loop.lua lit `specter.var.autofarm`, ani_ai.lua lit
    // `specter.var.ani_ia`. Les deux derniers echoueraient silencieusement sur
    // un binding qui n'existe pas encore.
    //
    // La file du canal init est de profondeur 1 et REMPLACE : deux submit
    // successifs, et le premier peut disparaitre avant d'etre draine. Donc pas
    // trois envois -- on concatene, et l'ordre est garanti par construction.
    //
    // `sizeof(kInitScript)` vaut 8 : c'est un `const char*`, pas le tableau.
    // La premiere version dimensionnait donc le tampon a 16 octets, la garde
    // declenchait, et le bootstrap ne partait JAMAIS -- avec un build vert et
    // aucun avertissement. La taille se deduit de la LONGUEUR des scripts.
    static const int kInitLen =
        static_cast<int>(std::strlen(lua::init::kInitScript));
    static const int kAutoLen =
        static_cast<int>(std::strlen(lua::init::kAutofarmLoop));
    static const int kAiLen =
        static_cast<int>(std::strlen(lua::init::kAniAiLoop));

    static char code[kInitLen + kAutoLen + kAiLen + 3];
    static bool sized = false;
    if (!sized) {
        static_assert(sizeof(code) > sizeof(lua::init::kInitScript) + 16,
                      "le tampon doit suivre la LONGUEUR des scripts, pas sizeof "
                      "d'un pointeur");
        sized = true;
    }

    if (kInitLen <= 0 || kAutoLen <= 0 || kAiLen <= 0) {
        return;
    }

    int len = 0;
    const int lens[3] = {kInitLen, kAutoLen, kAiLen};
    const char* parts[3] = {lua::init::kInitScript, lua::init::kAutofarmLoop,
                            lua::init::kAniAiLoop};
    for (int i = 0; i < 3; ++i) {
        if (len > 0) {
            code[len++] = '\n';
        }
        std::memcpy(code + len, parts[i], static_cast<std::size_t>(lens[i]));
        len += lens[i];
    }

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
