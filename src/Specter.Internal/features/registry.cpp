// Specter.Internal — the feature registry.
//
// This is the file to touch when adding a feature: one line, right here.
//
// Nothing else in the tree names a feature. The overlay draws whatever tabs it
// finds; app::start() installs whatever it finds. Adding a feature used to mean
// editing the UI, the startup sequence and the build file.

#include "pch-il2cpp.h"

#include "features/feature.h"

#include "features/console/console.h"
#include "features/inf_stamina/inf_stamina.h"
#include "features/lua_dump/lua_dump.h"
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

const Feature kStamina{
    "inf_stamina", "Movement", &stamina::install, &stamina::draw_ui, nullptr,
};

// A tool, not a gameplay feature: it installs and runs in the background, but it
// has no tab of its own, so the menu does not grow for it.
const Feature kLuaDump{"lua_dump", nullptr, &lua_dump::install, nullptr,
                          nullptr};

// The list, in menu order.
const Feature* const kFeatures[] = {&kConsole, &kTeleport, &kWaypoints,
                                     &kStamina, &kLuaDump};

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