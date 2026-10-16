#pragma once

namespace specter::features {
namespace teleport {

// --- called BY LUA, through the binding layer --------------------------------
//
// These replace a text protocol. The Lua side used to PRINT "P x y z", "F zone
// x y z", "W zone x y z nom" and "MARKS_DONE", and the C++ side parsed those
// lines back out of the result buffer with sscanf.
//
// That was a workaround for a time when there was nothing else: there was no
// binding layer, so values had to travel as text. There is now, and printing a
// line to hand a number to a function in the same process is absurd.
//
// So: Lua CALLS these. No serialisation, no sscanf, no parse_position, no
// handle_result, no letter tags, and no "(no output)" to wonder about.
//
// Names carry the unit, so a caller cannot pass them in the wrong order: a
// signature of five doubles is a bug waiting to happen.

void set_position(double x, double y, double z, double space);

// kind: 0 = Leyline Flower (Floraison), 1 = Teleportation Array crystal.
void add_mark(int kind, double zone, double x, double y, double z,
              const char* name);

// The scan is over. Called even if it found nothing -- that is the point: the
// finaliser keeps the cached lists when a scene had no marks in it.
void marks_done();

// The lerp step and rate, as ADDRESSES, for the binding layer to hand to Lua.
//
// Named _addr and not lerp_step(), because there is already a float lerp_step()
// getter above: two functions differing only by return type do not overload.
//
// The same reason `stamina::flag()` exists: the checkbox writes a C++ float the
// player tunes in the overlay, and scripts/init.lua reads it through
// `specter.var.tp_step`. A getter plus a setter would put two copies of one
// truth on two sides, which is the problem this whole design is avoiding.
//
// They are NOT arguments of specter.tp.here(x, y, z) on purpose: those three
// are the target. The step and the rate are settings the player changes, so
// formatting them into the chunk on every click would be the very thing the
// migration removes.
float* lerp_step_addr();
float* lerp_speed_addr();

// Install: load the saved slots and the cached mark lists. Called once from
// specter::start(), through the feature registry. Safe to call again.
bool init();

// Queue a chunk that reads the player's current position. The answer arrives
// asynchronously; scripts/init.lua reports what it found straight into the
// variables above, through the binding layer.
void request_position();

// True once at least one position result has been parsed.
bool have_position();

// Latest parsed position (any out pointer may be null).
void position(float* x, float* y, float* z, int* space);

// Consume one drained teleport-channel result (parses "P x y z space").

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
// request_marks() scans the open-world scenes once and add_mark() collects
// the answer. The two lists are also loaded at init(), from
// /tmp/specter-floraisons.json and /tmp/specter-waypoints.json.

// Queue a chunk that lists both families in one scan. The answer arrives
// asynchronously as "F <zone> <x> <y> <z>" lines (Floraisons) and
// one specter.add_mark() call per crystal. No lines, no buffer, no parser.
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
