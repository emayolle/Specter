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
#include "lua_chests.h"     // generated/lua_chests.h,   from scripts/chest-open.lua
#include "lua_vitesse.h"    // generated/lua_vitesse.h,  from scripts/vitesse.lua

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
    //
    // L'ordre est une dependance, pas un hasard : init.lua pose les bindings,
    // autofarm_loop.lua lit `specter.var.autofarm`, chest-open.lua lit
    // `specter.var.coffres`, ani_ai.lua lit `specter.var.ani_ia`. Les trois
    // derniers echoueraient silencieusement sur un binding qui n'existe pas
    // encore.
    //
    // `sizeof(kInitScript)` vaut 8 : c'est un `const char*`, pas le tableau.
    // La premiere version dimensionnait donc le tampon a 16 octets, la garde
    // declenchait, et le bootstrap ne partait JAMAIS -- avec un build vert et
    // aucun avertissement. La taille se deduit de la LONGUEUR des scripts.
    //
    // LE TABLEAU EST EN DUR ET C'EST VOLONTAIRE. Un `for` sur une liste compilee
    // ici obligerait a ajouter une ligne dans ce fichier ET dans embed-lua.sh,
    // et il n'y a aucun test qui relie les deux : le build resterait vert avec
    // un script embarque et jamais joue. La liste est donc visible ici, et
    // l'ordre se lit d'un coup d'oeil.
    static const char* const kParts[] = {
        lua::init::kInitScript,     // 1. bindings, patchs, specter.tp
        lua::init::kAutofarmLoop,   // 2. ramasse tout SAUF les coffres
        lua::init::kChestsLoop,     // 3. ouvre les coffres, rien d'autre
        lua::init::kVitesseLoop,    // 4. multiplicateurs de vitesse
        lua::init::kAniAiLoop,      // 5. IA des Aniimoe
    };
    constexpr int kNParts =
        static_cast<int>(sizeof(kParts) / sizeof(kParts[0]));

    // LE PLAFOND, ET IL EST CELUI DU CANAL.
    //
    // C'est la meme constante que `kMaxCode` dans features/console/console.cpp,
    // recopiee parce qu'elle n'est pas exportee. Une recopie est un second
    // endroit a maintenir, donc embed-lua.sh LIT celle de console.cpp et
    // refuse le build si la somme des scripts la depasse : le pire qui puisse
    // arriver ici est donc un build casse, jamais un chunk tronque en silence.
    //
    // Depasser le plafond ne corrompt pas le jeu, ca CORROMPT le chunk : la
    // troncature tombe au milieu d'une ligne et l'erreur qui en sort accuse un
    // fichier interne du jeu plutot que le script. Mesure :
    //
    //     SpecterManager.lua:492: unexpected symbol near ')'
    //
    // 64 Ko, comme le `static char src[...]` de lua/pump.cpp : un tampon
    // unique, pose une fois.
    constexpr int kMaxBootstrap = 128 * 1024;
    static char tampon[kMaxBootstrap];

    int total = 0;
    for (int i = 0; i < kNParts; ++i) {
        const int n = static_cast<int>(std::strlen(kParts[i]));
        if (n <= 0) {
            log::error("init: le script %d est vide -- bootstrap refuse", i + 1);
            return;
        }
        total += n;
    }
    // Un separateur entre chaque : deux scripts colles sans rien entre eux
    // peuvent se trouver fusionnes en un seul mot si le premier finit sur un
    // caractere et que le second commence sur celui qui le complete.
    if (total + kNParts >= static_cast<int>(sizeof(tampon))) {
        log::error("init: le bootstrap fait %d octets, le tampon en accepte %d "
                   "-- scripts trop gros, RIEN n'est execute", total,
                   static_cast<int>(sizeof(tampon)));
        return;
    }

    int len = 0;
    for (int i = 0; i < kNParts; ++i) {
        const int n = static_cast<int>(std::strlen(kParts[i]));
        if (len > 0) {
            tampon[len++] = '\n';
        }
        std::memcpy(tampon + len, kParts[i], static_cast<std::size_t>(n));
        len += n;
    }
    tampon[len] = '\0';

    // Through the console's queue rather than a direct pump::run(): the state
    // hook runs from inside the pump, and the queue is how every other feature
    // gets its Lua onto the Lua thread on a tick instead of re-entering the
    // pump from within itself.
    if (!console::submit(console::kChannelInit, tampon, len)) {
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
