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
#include "features/chests/chests.h"
#include "features/console/console.h"
#include "features/inf_stamina/inf_stamina.h"
#include "features/init/init.h"
#include "features/lua_dump/lua_dump.h"
#include "features/nofall/nofall.h"
#include "features/teleport/teleport.h"
#include "features/teleport/teleport_ui.h"
#include "features/vitesse/vitesse.h"

namespace specter::features {
namespace {

// Aggregate-initialised from constants, so these are constant-initialised: no
// dynamic initialiser runs at load time (the image is manually mapped).
const Feature kConsole{
    "console", "Outils", &console::install, &console::draw_ui, nullptr,
};

// Teleport is two tabs, so two entries over the same module: the registry
// describes tabs, not features.
const Feature kTeleport{
    "teleport", "Joueur", &teleport::init, &teleport::draw_ui,
    &teleport::on_frame,
};
const Feature kWaypoints{
    "waypoints", "Monde", &teleport::init,
    &teleport::draw_ui_waypoints, nullptr,
};

// Shares the "Movement" tab with the stamina, which is what a tab LABEL means:
// it is the ImGui ID, and two features with the same label are two entries of
// ONE tab, not two tabs that fight over one ID. See render/d3d12_overlay.cpp.
const Feature kNoFall{
    "nofall", "Joueur", nullptr, &nofall::draw_ui, nullptr,
};

const Feature kStamina{
    // nullptr install: the patch lives in scripts/init.lua, so there is nothing
    // to hook at startup. What is left is the gate and its checkbox.
    "inf_stamina", "Joueur", nullptr, &stamina::draw_ui, nullptr,
};

// Les multiplicateurs de vitesse. Onglet « Joueur » : c'est du deplacement, et
// c'est la ou l'on va les chercher. nullptr install comme la stamina -- le patch
// vit dans scripts/vitesse.lua, joue au bootstrap ; il ne reste que la case et
// les curseurs.
const Feature kVitesse{
    "vitesse", "Joueur", nullptr, &vitesse::draw_ui, nullptr,
};

// The auto-farm toggle. The LOOP lives in scripts/autofarm_loop.lua, which
// runs on every new lua_State and reads `specter.var.autofarm` -- so nullptr
// install is right: there is nothing to hook at startup, only a checkbox and
// the flag it writes.
const Feature kAutofarm{
    "autofarm", "Monde", nullptr, &autofarm::draw_ui, nullptr,
};

// L'ouverture des coffres. Meme onglet « Monde » que l'auto-farm, et c'est
// voulu : ce sont les deux moities du meme travail, posees l'une a cote de
// l'autre pour qu'on les coche et decoche en connaissance de cause. Meme libelle
// = meme page (c'est l'ID ImGui qui compte), donc c'est ici qu'on les regroupe,
// pas deux onglets qui se font concurrence.
const Feature kChests{
    "chests", "Monde", nullptr, &chests::draw_ui, nullptr,
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
    "ani_ai", "Monde", nullptr, &aniai::draw_ui, nullptr,
};

// L'ORDRE DANS LE REGISTRE EST L'ORDRE D'AFFICHAGE DANS UNE PAGE.
//
// Il n'avait aucune incidence tant que chaque feature avait son propre onglet.
// Maintenant que « Joueur » regroupe Teleport, Waypoints, stamina et chute,
// l'ordre du registre EST l'ordre dans lequel on les voit — et les deux cases
// d'abord, parce que ce sont elles qu'on cherche.
//
//   Joueur   chute, stamina, teleport
//   Monde    IA, auto-farm, coffres, reperes
const Feature* const kFeatures[] = {
    &kInit,   &kConsole, &kNoFall, &kStamina, &kVitesse,
    &kTeleport, &kAniAi,  &kAutofarm, &kChests,  &kWaypoints,
    &kLuaDump};
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