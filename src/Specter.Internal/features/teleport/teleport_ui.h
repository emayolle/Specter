// Specter.Internal — teleport UI (declarations).
//
// The overlay draws whatever tabs the feature registry hands it; these are the
// contents of teleport's two tabs, and the per-frame work that feeds them.
// Kept apart from teleport.cpp so the feature's logic (slots, lerp, persistence)
// does not have to carry ImGui calls.

#pragma once

namespace specter::features {
namespace teleport {

// Per frame, render thread: load the slots once, then drain the teleport
// channel so parsed positions and mark lists reach the feature.
void on_frame();

// The "Teleport" tab.
void draw_ui();

// The "Waypoints" tab.
void draw_ui_waypoints();

}  // namespace teleport
}  // namespace specter::features