// Specter.Internal — teleport feature (saved positions + teleport).
//
// The overlay is D3D12/ImGui on the render thread; reading or writing the
// player's position must happen inside the game's Lua and on the game's Lua
// thread. This module owns the SLOT registry (a small list persisted to
// /tmp/specter-tp.json) and turns UI actions into chunk traffic on the
// dedicated bridge channel (features::lua::tp_submit / tp_take_result), which
// keeps its results out of the Lua console and out.txt.
//
// The lever is the player entity's own API:
//   * `ent:getPosition()` -> {x, y, z, space}
//   * `ent:forceSetPos({x, y, z}, true)` -> moves the character (validated in-game)
//
// A single jump is reverted by the server (rubber-band), so a teleport lerps:
// it walks to the target in small per-tick steps whose size and rate are
// user-tunable (see the sliders in the Teleport tab).
//
// All functions here are render-thread only.

#pragma once

namespace specter::features {
namespace tp {

// Load saved slots from the persistence file. Call once (render thread).
void init();

// Queue a chunk that reads the player's current position. The answer arrives
// asynchronously; feed drained channel output to handle_result().
void request_position();

// True once at least one position result has been parsed.
bool have_position();

// Latest parsed position (any out pointer may be null).
void position(float* x, float* y, float* z, int* space);

// Consume one drained teleport-channel result (parses "P x y z space").
void handle_result(const char* text);

// Save the current position under `name` (replaces an existing slot). Returns
// false when no position is known yet, the name is empty, or the list is full.
bool save_current(const char* name);

// Queue a chunk that teleports to the i-th slot. False if the bridge is down.
bool teleport_to(int idx);

// Remove the i-th slot (persists immediately).
bool remove_at(int idx);

int count();

// Copy the i-th slot out (name is sanitized; coords are the saved ones).
void get_slot(int idx, char* name, int cap, float* x, float* y, float* z);

// --- Fast-travel marks (Floraisons + crystals) ------------------------------
//
// Two families of map marks are exposed as one-click teleport targets:
//
//  * Floraisons (Leyline Flowers): every zone (a "large area") has one, drawn
//    as the Nourish / Enrichissement fast-travel flower. Tagged in the game's
//    per-scene mark data as markType 26.
//  * Waypoints (Teleportation Array crystals): the in-world crystals that
//    reveal the map and act as fast-travel points. Not a distinct markType
//    (they share markType 0 with other marks) but carry markConfigId 10406
//    (infoImage $UI_Img_Map_Preview_TeleportationArray.png, POIIcon
//    $UI_Icon_POI_Explore_Transmit.png) and a localized infoTitle. Several can
//    share a zone.
//
// Both come from the game's Lua, so the read goes through the same TP channel:
// request_marks() scans the open-world scenes once and handle_result() parses
// the answer. The two lists are also loaded at init(), from
// /tmp/specter-floraisons.json and /tmp/specter-waypoints.json.

// Queue a chunk that lists both families in one scan. The answer arrives
// asynchronously as "F <zone> <x> <y> <z>" lines (Floraisons) and
// "W <zone> <x> <y> <z> <name>" lines (crystals), terminated by "MARKS_DONE".
// One scan on purpose: the TP channel keeps a single result buffer, so two
// queued probes would clobber each other.
void request_marks();

// True while a scan has been requested but not answered yet.
bool marks_pending();

int floraison_count();
// Copy the i-th Floraison (zone id + coords; any out pointer may be null).
void get_floraison(int idx, int* zone, float* x, float* y, float* z);
// One-click teleport to the i-th Floraison. False if the bridge is down.
bool teleport_to_floraison(int idx);

int waypoint_count();
// Copy the i-th waypoint (zone id, localized name, coords; out pointers may be
// null; name is truncated to cap including the terminator).
void get_waypoint(int idx, int* zone, char* name, int cap, float* x, float* y,
                  float* z);
// One-click teleport to the i-th waypoint. False if the bridge is down.
bool teleport_to_waypoint(int idx);

// --- Lerp tuning (render thread) --------------------------------------------
//
// `step` is the distance (world units) moved per step; `speed` is how many
// steps are applied per second. Effective movement = step * speed units/s.
// Both are clamped to safe ranges and persisted alongside the slots.

float lerp_step();
void set_lerp_step(float units);

float lerp_speed();
void set_lerp_speed(float steps_per_second);

// Write slots + tuning to the persistence file now.
void persist();

}  // namespace tp
}  // namespace specter::features
