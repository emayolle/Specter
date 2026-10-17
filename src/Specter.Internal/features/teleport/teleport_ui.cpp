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

// std::max, pour la borne de la liste de reperes ; std::snprintf, pour les
// coordonnees formatees. Ces deux-lui venaient par effet de bord de
// <algorithm> dans ui_widgets.h : relies ici, ils dependent de ce qu'elles
// utilisent, pas de l'ordre des includes ailleurs.
#include <algorithm>
#include <cstdio>
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
    // On lit la position du joueur tant que l'onglet est visible (~0.75 s a
    // 60 images). Les chunks tournent sur le thread Lua du jeu.
    if (++g_tp_refresh >= 45) {
        g_tp_refresh = 0;
        if (features::console::ready()) {
            features::teleport::request_position();
        }
    }

    // SECTION PAR SECTION, avec un separateur entre les deux. Avant, c'etait un
    // panneau encadre : BeginChild qui se mesure, plus sa bordure, plus son
    // fond. SeparatorText fait la meme separation en UN item, sans la gestion
    // de la hauteur — et une hauteur mal calculee, c'est le contenu qui sort de
    // l'ecran, ce qui s'est produit.
    { render::Group g("Position", 76.0f);
    float cx = 0.0f, cy = 0.0f, cz = 0.0f;
    int csp = 0;
    if (features::teleport::have_position()) {
        features::teleport::position(&cx, &cy, &cz, &csp);
        char buf[96];
        std::snprintf(buf, sizeof(buf), "%.0f   %.0f   %.0f", cx, cy, cz);
        ImGui::Text("%s", buf);
        ImGui::TextDisabled("x  y  z   scene %d", csp);
    } else {
        ImGui::TextDisabled("unknown - get in-game");
    }

    }  { render::Group g("Save here", 54.0f);
    ImGui::SetNextItemWidth(-1.0f - 200.0f);
    ImGui::InputText("##nom", g_tp_name, sizeof(g_tp_name));
    ImGui::SameLine();
    if (ImGui::Button("Save here", ImVec2(180.0f, 0.0f))) {
        if (!features::teleport::save_current(g_tp_name)) {
            console::note("! tp: rien enregistre (position ou nom manquant)\n");
        }
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Saves the current position under this name.");
    }

    }  { render::Group g("Teleport", 150.0f);
    ImGui::TextDisabled("walks to the target in small steps");
    float stepv = features::teleport::lerp_step();
    if (render::slider_row("Step size", &stepv, 0.25f, 20.0f, "%.2f u", 110.0f)) {
        features::teleport::set_lerp_step(stepv);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Distance moved per small TP. Too big and the server rejects it\n"
            "(rubber-band).");
    }
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        features::teleport::persist();
    }

    float spdv = features::teleport::lerp_speed();
    if (render::slider_row("Speed", &spdv, 5.0f, 120.0f, "%.0f st/s", 110.0f)) {
        features::teleport::set_lerp_speed(spdv);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "Steps applied per second, capped by the game frame rate.");
    }
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        features::teleport::persist();
    }

    const float fps = ImGui::GetIO().Framerate;
    const float cap = fps > 1.0f ? fps : 60.0f;
    const float sps = features::teleport::lerp_speed();
    const float eff_speed = sps < cap ? sps : cap;
    ImGui::TextDisabled("~%.0f u/s   steps x min(speed, %.0f fps)",
                       features::teleport::lerp_step() * eff_speed, cap);

    }  {
      // AutoResizeY : autorise ici parce que la carte n'est PAS imbriquee dans
      // un enfant qui defile — elle est dans la page. Elle se mesure donc sur son
      // contenu, et l'espace du dessous disparait. Les cartes de ZONE, elles, sont
      // dans la liste defilante : c'est la qu'AutoResizeY plantait.
      render::Group g("Saved positions");

    if (features::teleport::count() == 0) {
        ImGui::TextDisabled("none yet - save one above");
    }
    for (int i = 0; i < features::teleport::count(); ++i) {
        char nm[36] = {};
        float sx = 0.0f, sy = 0.0f, sz = 0.0f;
        features::teleport::get_slot(i, nm, sizeof(nm), &sx, &sy, &sz);

        ImGui::PushID(i);
        char xyz[64];
        std::snprintf(xyz, sizeof(xyz), "(%.0f, %.0f, %.0f)", sx, sy, sz);

        // Nom + coordonnees a gauche, Aller et Effacer a droite.
        //
        // Le tableau ci-dessous remplace le bouton pose en ABSOLU
        // (bouton_a_x, x = d.x + largeur_disponible - 168). Ce bouton-la se
        // positionnait lui-meme au draw list et reposait un InvisibleButton :
        // deux systemes de coordonnees, et le curseur qu'il laissait derriere
        // lui. Un tableau, c'est UN item par colonne, et ImGui aligne tout seul.
        // BeginTable / EndTable : LES DEUX OU AUCUN.
        //
        // imgui.h, ligne 907 : « only call EndTable() if BeginTable() returns
        // true! » — l'INVERSE de BeginChild, qui doit toujours etre apparie.
        // Melanger les deux regles, c'est laisser g.CurrentTable a nul.
        //
        // Ici la forme est « early return » : le PopID est fait explicitement,
        // et le continue saute le contenu de la ligne. Aucun EndTable ne peut
        // etre oublie, parce qu'il n'y en a pas a appeler dans ce chemin.
        if (!ImGui::BeginTable("##pos", 3,
                               ImGuiTableFlags_SizingStretchSame |
                                   ImGuiTableFlags_NoSavedSettings)) {
            ImGui::PopID();
            continue;
        }
        // Les libelles de colonnes sont des ID, pas du texte : ils restent en
        // francais ici parce que personne ne les lit. NE JAMAIS appeler
        // TableHeadersRow() — sur la capture, on lisait « nom  aller  effacer »
        // en tete du tableau, alors que les boutons disaient « Go  Delete ».
        // Le titre d'une colonne n'est pas une etiquette : c'est un identifiant.
        ImGui::TableSetupColumn("nom", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("go", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("del", ImGuiTableColumnFlags_WidthFixed, 100.0f);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        // UNE SEULE LIGNE PAR POSITION. Nom et coordonnees sur la meme ligne.
        //
        // En deux lignes, la ligne des coordonnees tombait ENTRE deux lignes de
        // tableau : chaque coordonnee se lisait a hauteur du bouton de la
        // position SUIVANTE. C'est ce que montrait la capture — cinq coordonnees
        // decalees d'un cran par rapport a leur « Teleport ».
        //
        // Une ligne de tableau fait UNE ligne de texte. Tout ce qui deborde sort
        // de la ligne et recouvre la suivante.
        ImGui::TextUnformatted(nm);
        ImGui::SameLine();
        ImGui::TextDisabled("%s", xyz);

        ImGui::TableNextColumn();
        if (ImGui::Button("Go", ImVec2(-1.0f, 0.0f))) {
            if (!features::teleport::teleport_to(i)) {
                console::note("! tp: bridge not ready\n");
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Teleports there.");
        }

        ImGui::TableNextColumn();
        if (ImGui::Button("Delete", ImVec2(-1.0f, 0.0f))) {
            features::teleport::remove_at(i);
            --i;   // les slots ont recule d'un cran
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Removes this position.");
        }

        ImGui::EndTable();
        ImGui::PopID();
    }
    }  // group
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
                    ImGui::TextDisabled("scanning...");
                } else {
                    ImGui::TextDisabled("%d zones   %d flowers   %d waypoints", nz, nflora, nwp);
                }
                ImGui::SameLine();
                if (ImGui::Button("Refresh")) {
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

                // LA LISTE PREND TOUT CE QUI RESTE.
                //
                // Elle passe apres les deux cases dans le registre : elle est
                // donc en dernier, et ce qui reste de la page est exactement sa
                // hauteur. Avant, elle prenait la page entiere - les deux cases
                // se retrouvaient sous le bord.
                const float h = std::max(ImGui::GetContentRegionAvail().y - 14.0f,
                                         140.0f);
                ImGui::BeginChild("##wp_list", ImVec2(0.0f, h));

                if (nz == 0) {
                    ImGui::TextDisabled("nothing yet - press Refresh in-game");
                }

                for (int zi = 0; zi < nz; ++zi) {
                    const int zone = zones[zi];
                    char titre[32];
                    std::snprintf(titre, sizeof(titre), "Zone %d", zone);

                    if (zi > 0) {
                        ImGui::Separator();
                    }
                    ImGui::TextDisabled("%s", titre);

                    // BeginTable / EndTable : LES DEUX OU AUCUN.
                    //
                    // imgui.h, ligne 907 : « only call EndTable() if BeginTable()
                    // returns true! » — c'est l'INVERSE de BeginChild, qui doit
                    // toujours etre apparie. Ne pas melanger les deux regles :
                    // c'est exactement la confusion qui laisse un CurrentTable
                    // nul, et l'assertion mesuree venait de la.
                    //
                    // Le bloc encapsule tout, donc aucun `continue` ne peut
                    // sauter le EndTable.
                    if (ImGui::BeginTable("##zp", 2,
                                          ImGuiTableFlags_SizingStretchSame |
                                              ImGuiTableFlags_NoSavedSettings)) {
                    ImGui::TableSetupColumn("quoi",
                                            ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("tp", ImGuiTableColumnFlags_WidthFixed,
                                            100.0f);

                    for (int i = 0; i < nflora; ++i) {
                        int z = 0;
                        float fx = 0.0f, fy = 0.0f, fz = 0.0f;
                        features::teleport::get_floraison(i, &z, &fx, &fy, &fz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(100000 + i);
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        // UNE LIGNE. Voir la table ##pos : deux lignes font
                        // deborder les coordonnees sur la ligne du dessous.
                        ImGui::TextUnformatted("Floraison");
                        ImGui::SameLine();
                        ImGui::TextDisabled("(%.0f, %.0f, %.0f)", fx, fy, fz);
                        ImGui::TableNextColumn();
                        if (ImGui::Button("Teleport", ImVec2(-1.0f, 0.0f))) {
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
                        features::teleport::get_waypoint(i, &z, nm, sizeof(nm),
                                                        &wx, &wy, &wz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(200000 + i);
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        // LE NOM, ET LA FAUTE QUI L'EFFACAIT.
                        //
                        // TextUnformatted("%s", nom) est le MAUVAIS appel, et il
                        // rend RIEN — silencieusement.
                        //
                        // TextUnformatted n'est pas un printf. Sa signature est
                        //
                        //     TextUnformatted(const char* text, const char* text_end)
                        //
                        // Le second parametre n'est pas une vararg : c'est la FIN
                        // de la plage d'octets a rendre. En passant `nom`, on
                        // rendait la plage « "%s" a nom », soit DEUX octets, dont
                        // un '%' — qu'ImGui lit comme un debut de commande de
                        // texte, donc a vide.
                        //
                        // Le nom etait la, correct, en memoire : le marqueur de
                        // diagnostic affichait « len=22 Coll », longueur et
                        // premiers caracteres exacts. TextColored est un VRAI
                        // printf, donc lui fonctionnait. C'est ce qui a designe
                        // la panne : donnees correctes, rendu faux, meme ligne,
                        // meme police, meme couleur.
                        //
                        // La forme correcte : TextEx fait le formatage, donc
                        // Text("%s", ...) et non TextUnformatted.
                        ImGui::Text("%s", nm[0] ? nm : "(unnamed)");
                        ImGui::SameLine();
                        ImGui::TextDisabled("(%.0f, %.0f, %.0f)", wx, wy, wz);
                        ImGui::TableNextColumn();
                        if (ImGui::Button("Teleport", ImVec2(-1.0f, 0.0f))) {
                            if (!features::teleport::teleport_to_waypoint(i)) {
                                console::note("! tp: bridge not ready\n");
                            }
                        }
                        ImGui::PopID();
                    }

                    ImGui::EndTable();
                    }  // BeginTable (les deux ou aucun)
                }  // zone

                ImGui::EndChild();
}

}  // namespace teleport
}  // namespace specter::features
