// Specter.Internal — the feature interface and its registry.
//
// WHY: before this, the overlay #included each feature and the startup
// sequence called each one by name. Adding a feature meant touching the UI, the
// startup path and the build file. Worse, it meant the render layer knew every
// feature in the product, which is the wrong direction for a dependency.
//
// A Feature is the whole of that contract: an id, a tab title, and two hooks.
// The overlay iterates registry() to draw tabs; app::start() iterates the same
// list to install. Neither mentions a feature by name afterwards.
//
// Adding a feature is therefore: create features/<nom>/, and add ONE line to
// registry.cpp.

#pragma once

namespace specter::features {

struct Feature {
    // Stable, unique. Doubles as the name of the feature in the log.
    const char* id;

    // Title of its menu section, or nullptr for a feature with no UI at all
    // (a background tool still installs; it just gets no tab).
    const char* tab;

    // Run once from specter::start(), on the hidden worker thread. Returns
    // false if the feature could not come up; that is logged, not fatal.
    bool (*install)();

    // Run every frame, on the render thread, already inside the feature's tab.
    // May be nullptr for a feature with no UI.
    void (*draw_ui)();
};

// The registry: the one and only place a feature is wired.
//
// An explicit list, on purpose. A self-registering static initialiser would be
// tidier to write, but the DLL is manually mapped, so the CRT guard that would
// run it is not initialised and the constructor would never fire — the feature
// would simply be missing, silently.
const Feature* const* registry();

// How many entries registry() has.
int registry_count();

}  // namespace specter::features