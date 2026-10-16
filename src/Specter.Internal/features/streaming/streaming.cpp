// Specter.Internal — rayon de streaming de la carte. See streaming.h.

#include "pch-il2cpp.h"

#include <cstdint>

#include "features/streaming/streaming.h"
#include "imgui.h"
#include "il2cpp/runtime.h"
#include "il2cpp/target.h"
#include "platform/hook/detour.h"
#include "platform/log.h"

namespace specter::features {
namespace streaming {
namespace {

// LA valeur. Lue et ecrite par la case et par `specter.var.stream_distance`,
// donc un seul endroit, comme partout ailleurs dans ce projet.
//
// 0 = on ne touche a rien. C'est le defaut : un patch qui s'active tout seul
// et coute des FPS sans que personne l'ait demande, c'est un patch qu'on
// retire dans une semaine.
int g_chunks = 0;

// Ce que le jeu aurait repondu, pour l'afficher. 0 tant qu'on n'a rien vu.
int g_game_value = 0;

// Signature : instance method, `this` en rcx, puis l'argument, puis le
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
    switch (g_chunks) {
    case 0: return "jeu decide";
    case 3: return "3 chunks (~768 u)";
    case 4: return "4 chunks (~1024 u)";
    case 5: return "5 chunks (~1280 u)";
    case 6: return "6 chunks (~1536 u)";
    case 12: return "12 chunks (~3072 u)";
    default: return "force";
    }
}

void draw_ui()
{
    if (!installed()) {
        ImGui::TextDisabled("detour absent -- reinjecter la DLL");
        return;
    }

    // Le neutre d'abord : c'est l'etat par defaut, et il doit etre obvious.
    int v = g_chunks;
    const char* items[] = {"Jeu decide", "3", "4", "5", "6", "12"};
    const int valeurs[] = {0, 3, 4, 5, 6, 12};
    int idx = 0;
    for (int i = 0; i < 6; ++i) {
        if (valeurs[i] == v) {
            idx = i;
        }
    }
    if (ImGui::Combo("Rayon de streaming", &idx, items, 6)) {
        set_value(valeurs[idx]);
    }

    ImGui::SameLine();
    if (g_game_value > 0) {
        ImGui::TextDisabled("le jeu veut %d", g_game_value);
    }

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(
            "GetPerfDistance traduit le niveau de performance du jeu en rayon "
            "de chargement, en chunks de 256 u.\n\n"
            "ATTENTION : ce sont des BLOCS DE TERRAIN, pas des entites. Les "
            "coffres viennent du serveur, donc charger plus loin ne garantit "
            "pas un objet de plus -- ca coute des FPS. C'est une mesure a faire, "
            "pas un gain acquis.");
    }
}

}  // namespace streaming
}  // namespace specter::features