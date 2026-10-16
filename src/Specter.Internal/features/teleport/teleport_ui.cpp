// Specter.Internal — teleport UI.
//
// Split out of the overlay so the render layer does not have to know what a
// teleport tab contains. The overlay now draws whatever tabs the feature registry
// hands it; this file is the two tabs' content, plus the per-frame work that
// feeds them (draining the Lua channel, polling the player position).
//
// The feature is not an island: its Lua still travels on the console module's
// teleport channel, which is the only machinery that runs a chunk.

#include "pch-il2cpp.h"

#include <cstring>

#include "features/console/console.h"
#include "features/teleport/teleport.h"
#include "features/teleport/teleport_ui.h"
#include "imgui.h"
#include "render/ui_widgets.h"

namespace specter::features {
namespace teleport {
namespace {

// ---- UI state (render thread only) -----------------------------------------

int g_tp_refresh = 0;     // frames between two position probes
bool g_tp_loaded = false; // init() runs once
char g_tp_name[64] = "";  // name of the slot being saved
bool g_wp_auto = false;   // one-shot waypoints fetch, tried once

}  // namespace

// ---- per-frame work --------------------------------------------------------

void on_frame()
{
    // Load the persisted slots once.
    if (!g_tp_loaded) {
        g_tp_loaded = true;
        features::teleport::init();
    }

    // No drain any more. The Lua side used to print "P x y z" and "F <zone>..."
    // and this used to read those lines back out of the channel's single result
    // buffer, on the render thread, to fill in what the UI displays. Now
    // scripts/init.lua calls specter.set_position() and specter.add_mark()
    // directly, so the numbers are already in the variables the UI reads and
    // there is nothing to collect here.
}

// ---- the two tabs -----------------------------------------------------------

void draw_ui()
{
                // Poll the player's position while the tab is visible (~0.75 s
                // at 60 fps). The chunks run on the game's Lua thread.
                if (++g_tp_refresh >= 45) {
                    g_tp_refresh = 0;
                    if (features::console::ready()) {
                        features::teleport::request_position();
                    }
                }

                float cx = 0.0f, cy = 0.0f, cz = 0.0f;
                int csp = 0;
                if (features::teleport::have_position()) {
                    features::teleport::position(&cx, &cy, &cz, &csp);
                    ImGui::Text("Position: (%.2f, %.2f, %.2f)  space %d", cx, cy,
                                cz, csp);
                } else {
                    ImGui::TextColored(render::texte_faible(), 
                        "position unknown - wait until you are in-world");
                }

                ImGui::SetNextItemWidth(180.0f);
                ImGui::InputText("Name", g_tp_name, sizeof(g_tp_name));
                ImGui::SameLine();
                if (ImGui::Button("Save current position")) {
                    if (!features::teleport::save_current(g_tp_name)) {
                        console::note(
                            "! tp: nothing saved (need a live position or a "
                            "non-empty name)\n");
                    }
                }

                ImGui::Separator();
                ImGui::TextUnformatted("Lerp tuning");
                ImGui::SameLine();
                ImGui::TextColored(render::texte_faible(), 
                    "(a teleport walks to the target in small steps)");
                float stepv = features::teleport::lerp_step();
                ImGui::SetNextItemWidth(240.0f);
                if (ImGui::SliderFloat("Step size (u)", &stepv, 0.25f, 20.0f,
                                       "%.2f u/step")) {
                    features::teleport::set_lerp_step(stepv);
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "Distance moved per small TP. Too big and the server "
                        "rejects it (rubber-band).");
                }
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    features::teleport::persist();
                }
                float spdv = features::teleport::lerp_speed();
                ImGui::SetNextItemWidth(240.0f);
                if (ImGui::SliderFloat("Speed (steps/s)", &spdv, 5.0f, 120.0f,
                                       "%.0f steps/s")) {
                    features::teleport::set_lerp_speed(spdv);
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "How many steps are applied per second (capped by the "
                        "game frame rate).");
                }
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    features::teleport::persist();
                }
                const float fps = ImGui::GetIO().Framerate;
                const float cap = fps > 1.0f ? fps : 60.0f;
                const float sps = features::teleport::lerp_speed();
                const float eff_speed = sps < cap ? sps : cap;
                ImGui::TextColored(render::texte_faible(), 
                    "=> ~%.0f u/s  (step x min(speed, %.0f fps))",
                    features::teleport::lerp_step() * eff_speed, cap);

                ImGui::Separator();
                ImGui::BeginChild("##tp_slots", ImVec2(-1.0f, -1.0f), true);
                if (features::teleport::count() == 0) {
                    ImGui::TextColored(render::texte_faible(), "no saved positions yet");
                }
                for (int i = 0; i < features::teleport::count(); ++i) {
                    char nm[36] = {};
                    float sx = 0.0f, sy = 0.0f, sz = 0.0f;
                    features::teleport::get_slot(i, nm, sizeof(nm), &sx, &sy, &sz);
                    ImGui::PushID(i);
                    ImGui::TextUnformatted(nm);
                    ImGui::SameLine();
                    ImGui::TextColored(render::texte_faible(), "(%.2f, %.2f, %.2f)", sx, sy, sz);
                    ImGui::SameLine();
                    if (ImGui::SmallButton("Teleport")) {
                        if (!features::teleport::teleport_to(i)) {
                            console::note("! tp: bridge not ready\n");
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::SmallButton("Delete")) {
                        features::teleport::remove_at(i);
                        --i;  // slots shifted left; re-check this index
                    }
                    ImGui::PopID();
                }
                ImGui::EndChild();
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "Teleports lerp the player toward the target so the "
                        "server accepts the move; slots persist in "
                        "/tmp/specter-tp.json.");
                }
}

void draw_ui_waypoints()
{
                const int nflora = features::teleport::floraison_count();
                const int nwp = features::teleport::waypoint_count();
                // One-shot fetch if a cached list is missing (e.g. /tmp was
                // wiped by a reboot). Both lists come from the same scan.
                if (!g_wp_auto && (nflora == 0 || nwp == 0) &&
                    features::console::ready()) {
                    g_wp_auto = true;
                    features::teleport::request_marks();
                }

                // Merge the Floraisons and the crystals, grouped by zone.
                int zones[128];
                int nz = 0;
                auto add_zone = [&](int z) {
                    for (int k = 0; k < nz; ++k) {
                        if (zones[k] == z) {
                            return;
                        }
                    }
                    if (nz < static_cast<int>(sizeof(zones) /
                                              sizeof(zones[0]))) {
                        zones[nz++] = z;
                    }
                };
                for (int i = 0; i < nflora; ++i) {
                    int z = 0;
                    features::teleport::get_floraison(i, &z, nullptr, nullptr,
                                                nullptr);
                    add_zone(z);
                }
                for (int i = 0; i < nwp; ++i) {
                    int z = 0;
                    features::teleport::get_waypoint(i, &z, nullptr, 0, nullptr,
                                               nullptr, nullptr);
                    add_zone(z);
                }
                for (int i = 1; i < nz; ++i) {  // insertion sort, ascending
                    const int k = zones[i];
                    int j = i;
                    while (j > 0 && zones[j - 1] > k) {
                        zones[j] = zones[j - 1];
                        --j;
                    }
                    zones[j] = k;
                }

                if (features::teleport::marks_pending()) {
                    ImGui::TextColored(render::texte_faible(), "scanning the game...");
                } else {
                    ImGui::TextColored(render::texte_faible(), 
                        "%d zone(s): %d Floraison(s), %d waypoint(s)", nz,
                        nflora, nwp);
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Refresh from game")) {
                    if (features::console::ready()) {
                        features::teleport::request_marks();
                    } else {
                        console::note("! tp: bridge not ready\n");
                    }
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "Re-reads every zone's Leyline Flower (Floraison) and "
                        "every Teleportation Array crystal from the game's "
                        "scene data. Cached in /tmp/specter-floraisons.json "
                        "and /tmp/specter-waypoints.json.");
                }
                ImGui::Separator();
                ImGui::BeginChild("##wp_list", ImVec2(-1.0f, -1.0f), true);
                if (nz == 0) {
                    ImGui::TextColored(render::texte_faible(), 
                        "nothing yet - press Refresh once in-world");
                }
                for (int zi = 0; zi < nz; ++zi) {
                    const int zone = zones[zi];
                    ImGui::Separator();
                    ImGui::TextColored(render::texte_faible(), "Zone %d", zone);
                    for (int i = 0; i < nflora; ++i) {
                        int z = 0;
                        float fx = 0.0f, fy = 0.0f, fz = 0.0f;
                        features::teleport::get_floraison(i, &z, &fx, &fy, &fz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(100000 + i);
                        ImGui::TextUnformatted("Floraison");
                        ImGui::SameLine();
                        ImGui::TextColored(render::texte_faible(), "(%.1f, %.1f, %.1f)", fx, fy, fz);
                        ImGui::SameLine();
                        if (ImGui::SmallButton("Teleport")) {
                            if (!features::teleport::teleport_to_floraison(i)) {
                                console::note("! tp: bridge not ready\n");
                            }
                        }
                        ImGui::PopID();
                    }
                    for (int i = 0; i < nwp; ++i) {
                        int z = 0;
                        char nm[64] = {};
                        float wx = 0.0f, wy = 0.0f, wz = 0.0f;
                        features::teleport::get_waypoint(i, &z, nm, sizeof(nm), &wx,
                                                   &wy, &wz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(200000 + i);
                        ImGui::TextUnformatted(nm[0] ? nm : "(unnamed)");
                        ImGui::SameLine();
                        ImGui::TextColored(render::texte_faible(), "(%.1f, %.1f, %.1f)", wx, wy, wz);
                        ImGui::SameLine();
                        if (ImGui::SmallButton("Teleport")) {
                            if (!features::teleport::teleport_to_waypoint(i)) {
                                console::note("! tp: bridge not ready\n");
                            }
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndChild();
}

}  // namespace teleport
}  // namespace specter::features
