// Specter.Internal — rayon de streaming de la carte. See streaming.h.

#include "pch-il2cpp.h"

#include <cstdint>
#include <cstdio>

#include "features/streaming/streaming.h"
#include "il2cpp/runtime.h"
#include "il2cpp/target.h"
#include "imgui.h"
#include "platform/hook/detour.h"
#include "platform/log.h"

namespace specter::features {
namespace streaming {
namespace {

// LA valeur. Lue et ecrite par le curseur et par `specter.var.stream_distance`,
// donc un seul endroit.
//
// 0 = on ne touche a rien. C'est le defaut : un patch qui s'active tout seul et
// coute des FPS sans que personne l'ait demande, c'est un patch qu'on retire
// dans une semaine.
int g_chunks = 0;

// Ce que le jeu aurait repondu, pour l'afficher a cote. 0 tant qu'on n'a rien
// observe.
int g_game_value = 0;

// Signature : methode d'instance, `this` en rcx, puis l'argument, puis le
// MethodInfo* que l'IL2CPP passe toujours en dernier.
using PerfDistanceFn = int32_t(__fastcall*)(void*, int32_t, void*);
PerfDistanceFn g_orig = nullptr;

int32_t __fastcall hooked(void* self, int32_t perfLevel, void* method)
{
    if (g_orig != nullptr) {
        g_game_value = g_orig(self, perfLevel, method);
    }
    const int want = g_chunks;
    if (want >= kMin && want <= kMax) {
        return static_cast<int32_t>(want);
    }
    return g_game_value;
}

const char* label_for(int v)
{
    static char buf[48];
    if (v == 0) {
        return "neutre";
    }
    if (v >= kMax) {
        return "maximum du moteur";
    }
    std::snprintf(buf, sizeof(buf), "%d tuile%s", v, v > 1 ? "s" : "");
    return buf;
}

}  // namespace

int* value()
{
    return &g_chunks;
}

void set_value(int chunks)
{
    if (chunks < kMin) {
        chunks = kMin;
    }
    if (chunks > kMax) {
        chunks = kMax;
    }
    g_chunks = chunks;
}

int value_now()
{
    return g_game_value;
}

bool install()
{
    const std::uintptr_t base = il2cpp::module_base();
    if (base == 0) {
        log::error("streaming: GameAssembly.dll absent -- le patch est inactif");
        return false;
    }
    void* fn = reinterpret_cast<void*>(base + target::kGetPerfDistanceRva);
    if (fn == nullptr) {
        log::error("streaming: RVA %llx introuvable -- le patch est inactif",
                   static_cast<unsigned long long>(target::kGetPerfDistanceRva));
        return false;
    }
    if (hook::is_installed(fn)) {
        return true;
    }
    void* orig = nullptr;
    if (!hook::install(fn, reinterpret_cast<void*>(&hooked), &orig,
                       "XSRGlobalManager::GetPerfDistance")) {
        log::error("streaming: detour echoue -- le patch est inactif");
        return false;
    }
    g_orig = reinterpret_cast<PerfDistanceFn>(orig);
    log::info("streaming: GetPerfDistance detoure (RVA %llx) -- 0 = neutre",
              static_cast<unsigned long long>(target::kGetPerfDistanceRva));
    return true;
}

bool installed()
{
    return g_orig != nullptr;
}

const char* current_label()
{
    return label_for(g_chunks);
}

void draw_ui()
{
    if (!installed()) {
        ImGui::TextDisabled("detour absent -- reinjecter la DLL");
        return;
    }

    // Le neutre est un BOUTON, pas une position du curseur.
    //
    // Repasser par zero en arriere ne dit pas "je desactive", ca dit "je n'ai
    // pas decide". C'est deux intentions differentes, donc deux gestes
    // differents -- et ca evite surtout qu'un retour arriere par megamarche
    // laisse le jeu en surcharge sans que personne l'ait voulu.
    if (ImGui::Button("Jeu decide (neutre)")) {
        set_value(0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Maximum")) {
        set_value(kMax);
    }

    int v = g_chunks;
    if (ImGui::SliderInt("Portee du streaming", &v, kMin, kMax, "%d")) {
        set_value(v);
    }
    ImGui::SameLine();
    ImGui::TextDisabled("%s", label_for(g_chunks));

    if (g_game_value > 0) {
        ImGui::TextDisabled("le jeu demande %d", g_game_value);
    }

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "XSRGlobalManager::GetPerfDistance, remplace par ce detour.\n\n"
            "L'UNITE N'EST PAS UNE DISTANCE. C'est un niveau de portee, en\n"
            "TUILES : XSRBlockTile::CalcThisTileLodLevel fait\n"
            "  max(|tileX-agentX|, |tileZ-agentZ|)\n"
            "plafonne a 12 PAR LE MOTEUR. La taille d'une tuile en metres\n"
            "n'est exposee nulle part de facon fiable, donc afficher des metres\n"
            "serait inventer un chiffre.\n\n"
            "Ce que ca charge : du TERRAIN et son niveau de detail. Les\n"
            "coffres viennent du serveur -- donc plus de valeur ne garantit\n"
            "aucun objet de plus, ca coute des FPS. A mesurer, pas a supposer.");
    }
}

}  // namespace streaming
}  // namespace specter::features