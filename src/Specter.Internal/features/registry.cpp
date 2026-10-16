// Specter.Internal — the feature registry.
//
// This is the file to touch when adding a feature: one line, right here.
//
// Nothing else in the tree names a feature. The overlay draws whatever tabs it
// finds; app::start() installs whatever it finds. Adding a feature used to mean
// editing the UI, the startup sequence and the build file.

#include "pch-il2cpp.h"

#include "features/feature.h"

#include "features/aniai/aniai.h"
#include "features/autofarm/autofarm.h"
#include "features/console/console.h"
#include "features/inf_stamina/inf_stamina.h"
#include "features/init/init.h"
#include "features/lua_dump/lua_dump.h"
#include "features/nofall/nofall.h"
#include "features/teleport/teleport.h"
#include "features/teleport/teleport_ui.h"

namespace specter::features {
namespace {

// Aggregate-initialised from constants, so these are constant-initialised: no
// dynamic initialiser runs at load time (the image is manually mapped).
const Feature kConsole{
    "console", "Lua Editor", &console::install, &console::draw_ui, nullptr,
};

// Teleport is two tabs, so two entries over the same module: the registry
// describes tabs, not features.
const Feature kTeleport{
    "teleport", "Teleport", &teleport::init, &teleport::draw_ui,
    &teleport::on_frame,
};
const Feature kWaypoints{
    "waypoints", "Waypoints", &teleport::init,
    &teleport::draw_ui_waypoints, nullptr,
};

// Shares the "Movement" tab with the stamina, which is what a tab LABEL means:
// it is the ImGui ID, and two features with the same label are two entries of
// ONE tab, not two tabs that fight over one ID. See render/d3d12_overlay.cpp.
const Feature kNoFall{
    "nofall", "Movement", nullptr, &nofall::draw_ui, nullptr,
};

const Feature kStamina{
    // nullptr install: the patch lives in scripts/init.lua, so there is nothing
    // to hook at startup. What is left is the gate and its checkbox.
    "inf_stamina", "Movement", nullptr, &stamina::draw_ui, nullptr,
};

// The auto-farm toggle. The LOOP lives in scripts/autofarm_loop.lua, which
// runs on every new lua_State and reads `specter.var.autofarm` -- so nullptr
// install is right: there is nothing to hook at startup, only a checkbox and
// the flag it writes.
const Feature kAutofarm{
    "autofarm", "Auto-farm", nullptr, &autofarm::draw_ui, nullptr,
};

// Runs scripts/init.lua once per new lua_State. No tab: it is a bootstrap, not
// something a person interacts with.
const Feature kInit{
    "init", nullptr, &init::install, nullptr, nullptr,
};

// A tool, not a gameplay feature: it installs and runs in the background, but it
// has no tab of its own, so the menu does not grow for it.
const Feature kLuaDump{"lua_dump", nullptr, &lua_dump::install, nullptr,
                          nullptr};

// The list, in menu order.
// kInit comes FIRST on purpose: it re-arms the per-session patches, and those
// want to be in place before anything else runs on a fresh state.
// Onglet propre : « Auto-farm » est une boucle qui ramasse, ca n'a rien a voir
// avec le fait qu'un creature pense ou non. Deux entrees de MEME libelle
// seraient un seul onglet (c'est l'ID ImGui qui compte) -- donc si on veut les
// voir separees, il faut deux libelles.
const Feature kAniAi{
    "ani_ai", "Aniimoe", nullptr, &aniai::draw_ui, nullptr,
};

const Feature* const kFeatures[] = {&kInit,      &kConsole, &kTeleport,
                                    &kWaypoints, &kStamina, &kNoFall,
                                    &kAutofarm,  &kAniAi,   &kLuaDump};
}  // namespace

const Feature* const* registry()
{
    return kFeatures;
}

int registry_count()
{
    return static_cast<int>(sizeof(kFeatures) / sizeof(kFeatures[0]));
}

}  // namespace specter::features