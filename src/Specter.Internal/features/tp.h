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
//   * `ent:setPosition({x, y, z})` -> moves the character (validated in-game)
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

}  // namespace tp
}  // namespace specter::features
