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
#include "features/lua_dump/lua_dump.h"

namespace specter::features {
namespace {

// Aggregate-initialised from constants, so these are constant-initialised: no
// dynamic initialiser runs at load time (the image is manually mapped).
const Feature kConsole{
    "console", "Lua Editor", &console::install, &console::draw_ui,
};

// A tool, not a gameplay feature: it installs and runs in the background, but it
// has no tab of its own, so the menu does not grow for it.
const Feature kLuaDump{"lua_dump", nullptr, &lua_dump::install, nullptr};

// The list, in menu order.
const Feature* const kFeatures[] = {&kConsole, &kLuaDump};

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