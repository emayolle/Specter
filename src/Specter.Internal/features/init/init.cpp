// Specter.Internal — runs scripts/init.lua at the start of every new lua_State.
//
// See init.h for why this exists and what it replaces.

#include "pch-il2cpp.h"

#include "features/console/console.h"
#include "features/init/init.h"
#include "lua/pump.h"
#include "platform/log.h"

#include <cstring>

#include "lua_init.h"   // generated/lua_init.h, from scripts/init.lua

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
    const char* code = lua::init::kInitScript;
    const int len = static_cast<int>(std::strlen(code));
    if (len <= 0) {
        return;
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
