// Specter.Internal — ImGui/D3D12 overlay bridge (implementation).
//
// Frame flow (see third_party/imgui/examples/example_win32_directx12):
//   ImGui_ImplDX12_NewFrame -> ImGui_ImplWin32_NewFrame -> ImGui::NewFrame
//   -> ImGui::Render -> record our command list (barrier, RT, draw data)
//   -> execute on the GAME's command queue -> signal our fence. The Present
//   hook wrapper then calls the original Present, which presents the frame
//   with the overlay.
//
// We deliberately submit on the game's own command queue (learned from the
// ExecuteCommandLists hook). vkd3d-proton enqueues the real present callbacks
// on the swapchain's queue and blits from the app back buffer assuming same
// queue ordering; a private queue would be a cross-queue hazard and can make
// present fail.
//
// Input is fed manually (GetAsyncKeyState) because the game window does not
// dispatch to us; VK_DELETE toggles the menu. No window class hooks, no file
// writes (io.IniFilename = nullptr), nothing on disk inside the prefix.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>  // IDXGISwapChain3, IDXGIFactory4

#include <atomic>
#include <cstdio>
#include <cstring>
#include <string>

#include "render/d3d12_overlay.h"
#include "render/input.h"
#include "features/feature.h"
#include "il2cpp/api.h"
#include "platform/log.h"
#include "platform/perf.h"

#include "imgui.h"
#include "render/ui_widgets.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

// imgui_impl_win32.h deliberately hides this in a '#if 0' (to avoid forcing
// <windows.h> on includers); we already have <windows.h>, so declare it here.
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace specter {
namespace render {
namespace {

constexpr UINT kSrvHeapSize = 128;  // power of two: the bump allocator wraps
constexpr UINT kRtvHeapSize = 8;
constexpr UINT kFlight = 3;
constexpr DWORD kFenceTimeoutMs = 2000;  // never block the render thread for good

enum class State { Idle, Ready, Failed };
enum class InitResult { Ok, Defer, Fail };

std::atomic<bool> g_ui_enabled{true};

// Le menu s'ouvre une fois sur « Joueur ». See build_ui() et le drapeau
// ImGuiTabItemFlags_SetSelected : sans lui, ImGui ouvre le PREMIER onglet du
// registre, c'est-a-dire « Outils », qui est la console Lua.
bool g_onglet_defaut_pose = false;

State g_state = State::Idle;
bool g_err_logged = false;
bool g_queue_wait_logged = false;

HWND g_probe_hwnd = nullptr;
HWND g_hwnd = nullptr;

ID3D12Device* g_dev = nullptr;
IDXGISwapChain3* g_sc3 = nullptr;
UINT g_buffer_count = 2;
DXGI_FORMAT g_format = DXGI_FORMAT_R8G8B8A8_UNORM;
UINT g_width = 0;
UINT g_height = 0;

ID3D12CommandQueue* g_queue = nullptr;
ID3D12DescriptorHeap* g_srv = nullptr;
ID3D12DescriptorHeap* g_rtv = nullptr;
UINT g_srv_stride = 0;
UINT g_rtv_stride = 0;
std::size_t g_srv_cpu = 0;
std::size_t g_srv_gpu = 0;
UINT g_srv_used = 0;

// Command queues seen submitting work (ExecuteCommandLists). The swapchain's
// queue is the one whose device matches the swapchain's device. Bounded and
// lock-free: a duplicate is harmless and cross-thread adds are rare.
constexpr int kMaxQueues = 8;
std::atomic<ID3D12CommandQueue*> g_queues[kMaxQueues] = {};
std::atomic<int> g_queue_count{0};

struct Frame
{
    ID3D12CommandAllocator* alloc = nullptr;
    UINT64 fence = 0;
};
Frame g_frames[kFlight];
ID3D12GraphicsCommandList* g_cmd = nullptr;
ID3D12Fence* g_fence = nullptr;
HANDLE g_fence_event = nullptr;
UINT64 g_fence_value = 0;
UINT g_frame_index = 0;

ID3D12Resource* g_buffers[kRtvHeapSize] = {};
D3D12_CPU_DESCRIPTOR_HANDLE g_rtv_handles[kRtvHeapSize] = {};

bool g_resize_dirty = true;
bool g_demo = false;
char g_snapshot[512] = {};
// 
// // ---- Lua console state (touch()d only on the render thread) ----------------
// 

// ---- Teleport tab state (render thread only) -------------------------------

bool g_tp_loaded = false;        // slot file loaded once, lazily
int g_tp_refresh = 0;            // frame counter: throttle position polling
bool g_wp_auto = false;  // tried the one-shot fast-travel auto-fetch
char g_tp_name[32] = "spot";

// Keyboard sink: the window subclass forwards swallowed key/char messages here
// so ImGui's Win32 backend sees them (the console needs text input).
bool keyboard_sink(void* hwnd, unsigned msg, uintptr_t wparam, intptr_t lparam)
{
    return ImGui_ImplWin32_WndProcHandler(static_cast<HWND>(hwnd), msg,
                                          static_cast<WPARAM>(wparam),
                                          static_cast<LPARAM>(lparam)) != 0;
}

// La molette. Le gate avale WM_MOUSEWHEEL pour que la camera ne zoome pas, ce
// qui supprime le seul evenement qui portait le defilement : la molette n'a pas
// d'etat, donc rien ne peut la rattraper apres coup.
//
// On reconstruit un vrai message plutot que d'appeler AddMouseWheelEvent en
// direct, pour que le backend fasse le travail lui-meme : c'est lui qui
// convertit WHEEL_DELTA en unites ImGui et qui applique IMGUI_DISABLE_MOUSE_WHEEL.
// On passe aussi WM_MOUSEHWHEEL, donc les molettes horizontales (et les
// trackpads) passent aussi.
//
// HI_RESOLUTE est indispensable : sans lui, une molette a haute resolution est
// arrondie au cran, et les petits defilements disparaissent.
void mouse_sink(int x, int y, int wheel)
{
    (void)x;
    (void)y;
    if (wheel == 0) {
        return;
    }
    // DIAGNOSTIC : la suite des crans recus, signe compris. C'est la seule
    // information qui manque. On sait que la roue arrive ; on sait que le
    // symptome est « un cran perdu par changement de direction ».
    //
    // Si la suite montre un signe MANQUANT, la perte est avant ImGui, et elle
    // est a notre cote. Si la suite est complete, la perte est apres, et c'est
    // ImGui qui ecarte — auquel cas le verrou de molette est innocent et c'est
    // TestKeyOwner qu'il faut regarder.
    //
    // Les deux sont distinguables uniquement par la sequence, donc on journalise
    // la sequence et pas un compteur.
    static int n = 0;
    if (++n <= 24) {
        log::info("overlay: cran recu %+d",
                  static_cast<int>(static_cast<float>(wheel) /
                                   static_cast<float>(WHEEL_DELTA)));
    }

    // `wheel` est en UNITES DE WHEEL_DELTA : 120 pour un cran, -120 vers le
    // bas. On convertit en crans, ce qu'ImGui attend (1.0 = un cran).
    //
    // AddMouseWheelEvent et non le handler Win32 : ce handler s'attend a un
    // WM_MOUSEWHEEL qu'on ne recoit jamais — fenetre fantome de 1x1 qui garde le
    // focus (voir render/input.cpp).
    ImGui::GetIO().AddMouseWheelEvent(
        0.0f, static_cast<float>(wheel) / static_cast<float>(WHEEL_DELTA));
}


void log_once(const char* what)
{
    if (!g_err_logged) {
        g_err_logged = true;
        log::error("overlay: %s", what);
    }
}

void fetch_desc(IDXGISwapChain* sc)
{
    DXGI_SWAP_CHAIN_DESC d = {};
    if (sc && SUCCEEDED(sc->GetDesc(&d))) {
        g_buffer_count = d.BufferCount > 0 ? d.BufferCount : 2;
        g_format = d.BufferDesc.Format;
        g_width = d.BufferDesc.Width;
        g_height = d.BufferDesc.Height;
        if (d.OutputWindow) {
            g_hwnd = d.OutputWindow;
        }
    }
    if (g_width == 0) {
        g_width = 1280;
    }
    if (g_height == 0) {
        g_height = 720;
    }
    if (!g_hwnd) {
        g_hwnd = g_probe_hwnd;
    }
}

void release_buffers()
{
    for (auto& b : g_buffers) {
        if (b) {
            b->Release();
            b = nullptr;
        }
    }
}

void create_rtvs()
{
    if (!g_dev || !g_sc3 || !g_rtv) {
        return;
    }
    release_buffers();
    const UINT n = g_buffer_count < kRtvHeapSize ? g_buffer_count : kRtvHeapSize;
    D3D12_CPU_DESCRIPTOR_HANDLE h = g_rtv->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < n; ++i) {
        ID3D12Resource* buf = nullptr;
        if (FAILED(g_sc3->GetBuffer(i, __uuidof(ID3D12Resource),
                                    (void**)&buf)) ||
            !buf) {
            break;
        }
        g_buffers[i] = buf;
        g_dev->CreateRenderTargetView(buf, nullptr, h);
        g_rtv_handles[i] = h;
        h.ptr += g_rtv_stride;
    }
}

// Wait until everything we have submitted so far has completed. Bounded: on
// timeout we log once and carry on rather than freezing the render thread.
void flush_queue()
{
    if (!g_queue || !g_fence || !g_fence_event) {
        return;
    }
    const UINT64 v = ++g_fence_value;
    if (FAILED(g_queue->Signal(g_fence, v))) {
        return;
    }
    if (g_fence->GetCompletedValue() >= v) {
        return;
    }
    g_fence->SetEventOnCompletion(v, g_fence_event);
    if (WaitForSingleObject(g_fence_event, kFenceTimeoutMs) != WAIT_OBJECT_0) {
        log_once("GPU fence wait timed out (queue stalled?)");
    }
}

// The queue whose device is the swapchain's device.
ID3D12CommandQueue* pick_queue(ID3D12Device* dev)
{
    const int n = g_queue_count.load(std::memory_order_acquire);
    for (int i = 0; i < n; ++i) {
        ID3D12CommandQueue* q = g_queues[i].load(std::memory_order_relaxed);
        if (!q) {
            continue;
        }
        ID3D12Device* d = nullptr;
        if (SUCCEEDED(q->GetDevice(__uuidof(ID3D12Device), (void**)&d)) && d) {
            const bool match = (d == dev);
            d->Release();
            if (match) {
                return q;
            }
        }
    }
    return nullptr;
}

void srv_alloc(ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* cpu,
               D3D12_GPU_DESCRIPTOR_HANDLE* gpu)
{
    const UINT idx = (g_srv_used++) & (kSrvHeapSize - 1);
    cpu->ptr = g_srv_cpu + static_cast<std::size_t>(idx) * g_srv_stride;
    gpu->ptr = g_srv_gpu + static_cast<std::size_t>(idx) * g_srv_stride;
}

void srv_free(ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE,
              D3D12_GPU_DESCRIPTOR_HANDLE)
{
    // Bump allocator: nothing to reclaim in-place.
}

void build_snapshot()
{
    using namespace specter::il2cpp;
    auto& t = table();
    const int bound = resolve();
    const bool ok = ready();
    const char* first_asm = "-";
    unsigned methods = 0;
    unsigned fields = 0;
    Il2CppDomain* dom = nullptr;

    if (ok) {
        dom = t.get_root_domain();
        if (dom) {
            void* it = nullptr;
            int count = 0;
            for (Il2CppAssembly* asm_;
                 (asm_ = t.domain_get_assemblies_iter(dom, &it)) != nullptr;) {
                if (count == 0 && asm_->image) {
                    const char* n = t.image_get_name(asm_->image);
                    if (n) {
                        first_asm = n;
                    }
                }
                ++count;
                if (count > 256) {
                    break;
                }
            }
        }
        if (app::AppFacade__TypeInfo && *app::AppFacade__TypeInfo) {
            Il2CppClass* klass =
                reinterpret_cast<Il2CppClass*>(*app::AppFacade__TypeInfo);
            methods = t.class_num_methods(klass);
            fields = t.class_num_fields(klass);
        }
    }

    std::snprintf(g_snapshot, sizeof(g_snapshot),
                  "Specter.Internal - D3D12 overlay\n"
                  "api: %d exports (ready=%s)\n"
                  "root domain: %p\n"
                  "first assembly: %s\n"
                  "AppFacade: %u methods / %u fields",
                  bound, ok ? "yes" : "no", (void*)dom, first_asm, methods,
                  fields);
}

InitResult init_once(IDXGISwapChain* sc)
{
    // Game device + swapchain3 (cached across deferred attempts).
    if (!g_dev) {
        HRESULT hr = sc ? sc->GetDevice(__uuidof(ID3D12Device), (void**)&g_dev)
                        : E_POINTER;
        if (FAILED(hr) || !g_dev) {
            // Transient, not terminal. The game creates and destroys swapchains
            // while it boots, and the one we hooked can already be gone by the
            // time its first Present reaches us. The next Present offers a live
            // one. Treating this as a failure killed the overlay for the whole
            // session, over a swapchain that happened to die on us.
            g_dev = nullptr;
            // NOT log_once: a repeated defer means the hook fires but the object
            // is never a usable swapchain, which is a different bug entirely and
            // needs to be visible. Five lines is enough to tell them apart.
            static int tries = 0;
            if (tries < 5) {
                ++tries;
                log::error("overlay: swapchain %p sans device (hr=0x%08lx), "
                           "essai %d/5", (void*)sc, (unsigned long)hr, tries);
            } else if (tries == 5) {
                ++tries;
                log::error("overlay: toujours pas de device -- plus de traces");
            }
            return InitResult::Defer;
        }
    }
    if (!g_sc3 &&
        FAILED(sc->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&g_sc3))) {
        g_sc3 = nullptr;
    }

    // We must render on the game's own queue. If we have not seen it submit
    // yet, defer instead of counting a failure.
    if (!g_queue) {
        g_queue = pick_queue(g_dev);
        if (!g_queue) {
            if (!g_queue_wait_logged) {
                g_queue_wait_logged = true;
                log::info("overlay: waiting for the game's command queue "
                          "(device=%p candidates=%d)",
                          (void*)g_dev, g_queue_count.load());
            }
            return InitResult::Defer;
        }
        g_queue->AddRef();
    }

    fetch_desc(sc);

    // Arm the input gate + cursor control as soon as we know the game window.
    //
    // LES SINKS D'ABORD. Cet ordre n'est pas cosmetique.
    //
    // install() sous-classe la fenetre tout de suite : a partir de la, chaque
    // message passe par notre wnd_proc. Si le sink est encore null a ce moment,
    // le message est traite par le gate qui l'AVALE — et un avale definitif.
    //
    // Pour la molette, c'est fatal : elle n'existe que pendant son message, donc
    // il n'y a aucun etat a relire ensuite. Un message perdu est perdu. C'etait
    // exactement ce qui se passait : install() ligne 378, set_mouse_sink()
    // ligne 471 — quatre-vingt-treize lignes trop tard, et le defilement ne
    // pouvait jamais fonctionner.
    //
    // Le clavier echappait au sort par chance : les touches sont relues par
    // GetAsyncKeyState a chaque frame, donc un message rate est rattrape au
    // frame suivant. La molette, non.
    input::set_keyboard_sink(&keyboard_sink);
    input::set_mouse_sink(&mouse_sink);
    input::install(g_hwnd ? g_hwnd : g_probe_hwnd);

    // Shader-visible SRV heap (fonts/textures) with a wrapping bump allocator.
    {
        D3D12_DESCRIPTOR_HEAP_DESC hd = {};
        hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        hd.NumDescriptors = kSrvHeapSize;
        hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        if (FAILED(g_dev->CreateDescriptorHeap(
                &hd, __uuidof(ID3D12DescriptorHeap), (void**)&g_srv)) ||
            !g_srv) {
            return InitResult::Fail;
        }
        g_srv_stride = g_dev->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        g_srv_cpu = g_srv->GetCPUDescriptorHandleForHeapStart().ptr;
        g_srv_gpu = g_srv->GetGPUDescriptorHandleForHeapStart().ptr;
    }

    // RTV heap, one descriptor per back buffer.
    {
        D3D12_DESCRIPTOR_HEAP_DESC hd = {};
        hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        hd.NumDescriptors = kRtvHeapSize;
        hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(g_dev->CreateDescriptorHeap(
                &hd, __uuidof(ID3D12DescriptorHeap), (void**)&g_rtv)) ||
            !g_rtv) {
            return InitResult::Fail;
        }
        g_rtv_stride = g_dev->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    for (auto& f : g_frames) {
        if (FAILED(g_dev->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator),
                (void**)&f.alloc)) ||
            !f.alloc) {
            return InitResult::Fail;
        }
    }
    if (FAILED(g_dev->CreateCommandList(
            0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frames[0].alloc, nullptr,
            __uuidof(ID3D12GraphicsCommandList), (void**)&g_cmd)) ||
        !g_cmd) {
        return InitResult::Fail;
    }
    g_cmd->Close();
    if (FAILED(g_dev->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                  __uuidof(ID3D12Fence), (void**)&g_fence)) ||
        !g_fence) {
        return InitResult::Fail;
    }
    g_fence_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_fence_event) {
        return InitResult::Fail;
    }

    create_rtvs();
    g_resize_dirty = false;

    build_snapshot();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;   // never write imgui.ini into the game prefix
    io.LogFilename = nullptr;
    // PAS DE CURSEUR IMGUI.
    //
    // io.MouseDrawCursor dessinait la fleche d'ImGui, pour remplacer le curseur
    // de l'OS que notre gate rendait invisible. Les deux causes ont disparu : le
    // gate ne touche plus au curseur (voir render/input.cpp), donc le curseur du
    // jeu reste cache en jeu, ce qui est coherent -- et le menu dessine sa
    // PASTILLE a la position souris, sur la draw list d'avant-plan. Voir
    // dessiner_pastille().
    io.MouseDrawCursor = false;
    ImGui::StyleColorsDark();

    // LE MENU S'OUVRE SUR « Player », UNE FOIS PAR SESSION.
    //
    // g_onglet_defaut_pose est un static local de build_ui(), donc il survit a
    // la destruction du contexte ImGui : sans cette remise a zero, le premier
    // menu de la session poserait l'onglet, et tous les suivants s'ouvriraient
    // sur « Outils » — c'est-a-dire la console, parce que SetSelected n'a jamais
    // ete redemande.
    g_onglet_defaut_pose = false;

    ImGui_ImplWin32_Init(g_hwnd ? g_hwnd : g_probe_hwnd);

    // Les sinks sont poses plus haut, AVANT input::install() — voir le commentaire
    // la : la sous-classe s'arme la et tout message trouve un sink null si on
    // attend. On ne les repose donc pas ici.

    ImGui_ImplDX12_InitInfo info = {};
    info.Device = g_dev;
    info.CommandQueue = g_queue;  // the game's queue, not ours
    info.NumFramesInFlight = static_cast<int>(
        g_buffer_count < kFlight ? g_buffer_count : kFlight);
    info.RTVFormat = g_format;
    info.DSVFormat = DXGI_FORMAT_UNKNOWN;
    info.SrvDescriptorHeap = g_srv;
    info.SrvDescriptorAllocFn = srv_alloc;
    info.SrvDescriptorFreeFn = srv_free;
    if (!ImGui_ImplDX12_Init(&info)) {
        return InitResult::Fail;
    }

    log::info("overlay: D3D12 ImGui ready (buffers=%u fmt=%d %ux%u hwnd=%p "
              "queue=%p)",
              g_buffer_count, static_cast<int>(g_format), g_width, g_height,
              (void*)g_hwnd, (void*)g_queue);
    return InitResult::Ok;
}

bool is_vk_down(int vk)
{
    // Real key state even while the menu gate is active (our own toggle and
    // ImGui input must not be blocked by our own hooks).
    return (input::real_async_key_state(vk) & 0x8000) != 0;
}

void feed_input()
{
    ImGuiIO& io = ImGui::GetIO();

    // LA POSITION D'ABORD, LES BOUTONS ENSUITE. L'ORDRE EST LE CORRECTIF.
    //
    // ImGui traite Evenements() dans l'ordre, et MouseClickEvent s'applique a
    // la position CONNUE AU MOMENT ou il est traite. Boutons d'abord, position
    // ensuite : le clic de ce frame se retrouve donc applique a la position
    // d'il y a UN FRAME. Un clic Registerait la ou la souris etait, pas la ou
    // elle est — le widget passe a cote, et ca resemble a un clic manque.
    //
    // Ce n'etait visible qu'en bougeant la souris pendant le clic, parce que
    // souris immobile : les deux positions sont la meme, et le retard de un
    // frame ne se voit pas. C'est un bug de course, pas de clic.
    //
    // AddMousePosEvent, PAS io.MousePos = ... : MousePos est un etat, on ne
    // peut que le SURCHARGER, et ImGui 1.92 ecarte toute ecriture directe entre
    // NewFrame et Render. L'API Evenement est l'unique voie.
    //
    // Le jeu garde sa souris verrouillee, donc le curseur de l'OS ne bouge pas :
    // c'est celle qu'input::accumuler_delta a construite, a partir des deltas
    // bruts (voir render/input.cpp).
    int cx = 0, cy = 0;
    if (input::curseur_pos(&cx, &cy)) {
        io.AddMousePosEvent(static_cast<float>(cx), static_cast<float>(cy));
    }

    // Mouse buttons on edges only, so ImGui sees clean down/up pairs.
    static const int kButtons[3] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON};
    static bool prev[3] = {};
    for (int i = 0; i < 3; ++i) {
        const bool down = is_vk_down(kButtons[i]);
        if (down != prev[i]) {
            io.AddMouseButtonEvent(i, down);
            prev[i] = down;
        }
    }
}

// ---------------------------------------------------------------- theme
//
// Palette et widgets.
//
// La demande etait : « c'est pas assez representatif, et c'est complique de se
// balader dedans ». Les deux problemes sont la disposition, pas la couleur : une
// barre d'onglets en haut avec six libelles oblige a lire chaque mot pour savoir
// ou cliquer. Une colonne de navigation a gauche avec une seule couleur d'accent
// se repere au coin de l'oeil.
//
// Aucune police d'icones : le backend D3D12 n'en embarque aucune, et en ajouter
// une pour six entrees ne vaut pas le cout. Les libelles sont la navigation.

using namespace specter::render;

// LA PASTILLE : ou est la souris, sans toucher au curseur du jeu.
//
// Un jeu a la premiere personne cache son curseur -- il appelle SetCursor(NULL)
// lui-meme -- donc en jeu il n'y a rien a afficher. Mais quand le menu est
// ouvert, il faut savoir ou on pointe. Donc on dessine un point, et on ne
// touche a rien d'autre.
//
// LA DRAW LIST D'AVANT-PLAN, ET POURQUOI PAS UNE AUTRE.
//
// GetForegroundDrawList() est dessinee AU-DESSUS de la fenetre et de tout le
// reste, et son contenu n'est pas ecrete par la fenetre du menu. Une pastille
// dessinee dans la fenetre, elle, disparaitrait des que le curseur sortirait
// du cadre du menu -- et disparaitrait visuellement alors que la souris est
// encore dessus.
//
// ET PAS DANS LE FLUX NORMAL, pour une raison qui compte.
//
// Un ImGui::CircleFilled() entre deux widgets avance le curseur, donc la
// pastille mangerait la place d'un controle et decalerait la mise en page. On
// la dessine donc sur la draw list, hors du flux : aucun item, aucun effet sur
// ce qui suit.
//
// UNE PASTILLE, ET SON ANNEAU. L'anneau sombre de 4 px se voit sur fond clair
// comme sur fond sombre, et le point blanc de 2 px reste visible sur les deux.
// Un disque plein, lui, disparaitrait sur un fond clair.
void dessiner_pastille()
{
    if (!g_ui_enabled.load(std::memory_order_relaxed)) {
        return;   // menu ferme : on ne dessine rien, le jeu garde son curseur
    }

    const ImVec2 p = ImGui::GetIO().MousePos;
    // Avant la premiere frame, MousePos vaut -FLT_MAX. Un cercle dessine la-bas
    // ne coute rien mais n'a aucun sens.
    if (p.x < -1000.0f || p.y < -1000.0f) {
        return;
    }

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    dl->AddCircleFilled(p, 4.0f, IM_COL32(20, 20, 20, 200));
    dl->AddCircleFilled(p, 2.0f, IM_COL32(255, 255, 255, 235));
}

void build_ui()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(24.0f, 24.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(780.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Specter")) {
        ImGui::TextUnformatted(g_snapshot);
        ImGui::Separator();

        // Feed every feature first, visible tab or not.
        for (int i = 0; i < features::registry_count(); ++i) {
            const features::Feature* f = features::registry()[i];
            if (f->on_frame) {
                f->on_frame();
            }
        }

        if (ImGui::BeginTabBar("##main_tabs")) {
            // ONE TAB PER DISTINCT LABEL, not one per feature.
            //
            // The overlay no longer knows what a console is, or that a teleport
            // tab used to exist. But the tab LABEL is the ImGui ID, so two
            // features carrying the same label produce two tabs with the same
            // ID: selecting one selects both, and the second is unreachable --
            // with no error, and no symptom anyone would look for.
            //
            // So the label is the grouping key, not the feature. "Movement"
            // holds the stamina checkbox and the fall-damage one. Teleport and
            // Waypoints each keep their own. Nothing here knows or cares which
            // feature lives in which tab.
            //
            // The first version tracked the labels it had OPENED, which is the
            // wrong set. BeginTabItem returns false for every tab that is not
            // the selected one, so an unselected label never got recorded and
            // the NEXT feature with that label called BeginTabItem again --
            // two tabs, one ID, and ImGui saying so:
            //
            //     Programmer error: 2 visible items with conflicting ID!
            //
            // So what is tracked is every label PASSED to BeginTabItem, along
            // with whether that call ended up open. One call per distinct
            // label, always; drawing only for the ones that are open.
            //
            // A small fixed array rather than a std::vector: this runs every
            // frame, and the image is manually mapped, so the fewer dynamic
            // things a render frame touches, the better.
            struct TabVu {
                const char* label;
                bool open;
            };
            TabVu vus[16];
            int nvus = 0;

            for (int i = 0; i < features::registry_count(); ++i) {
                const features::Feature* f = features::registry()[i];
                if (!f->tab || !f->draw_ui) {
                    continue;
                }

                int dejaVu = -1;
                for (int j = 0; j < nvus; ++j) {
                    if (std::strcmp(vus[j].label, f->tab) == 0) {
                        dejaVu = j;
                        break;
                    }
                }

                if (dejaVu >= 0) {
                    // Already inside that tab: draw, do not open it again.
                    if (vus[dejaVu].open) {
                        f->draw_ui();
                    }
                    continue;
                }

                if (nvus >= 16) {
                    continue;  // more distinct labels than the array holds
                }

                // L'ONGLET PAR DEFAUT, et pourquoi il faut le demander.
                //
                // BeginTabItem ouvre le PREMIER onglet qu'on lui passe si aucun
                // n'est selectionne — et le premier du registre est « Outils »,
                // c'est-a-dire la console Lua. Mesure sur la capture : le menu
                // s'ouvrait donc sur un champ de saisie vide, ce qui est la
                // page la moins parlante comme premiere impression.
                //
                // Et ce n'est PAS un choix qu'ImGui retient : io.IniFilename est
                // nul (le jeu ecrit dans son prefixe, on n'y touche pas), donc
                // il n'y a aucun imgui.ini. Sans SetSelected, c'est « Outils »
                // a CHAQUE ouverture, indefiniment.
                //
                // SetSelected ne doit etre demande qu'une fois, sur la premiere frame ou le
                // menu est dessine : ImGui bascule l'onglet, puis le deselectionne
                // tout seul. Le demander en boucle vole la selection a
                // l'utilisateur a chaque clic sur une autre page.
                //
                // CE N'EST PAS g_frame_index == 0. g_frame_index est un compteur
                // circulaire d'images D3D, qui tourne en permanence et n'est
                // jamais nul apres le premier rendu -- et il compte les images
                // presentees, pas les frames de menu dessinees. Un flag dedie
                // dit ce qu'il veut dire.
                ImGuiTabItemFlags drapeaux = ImGuiTabItemFlags_None;
                if (!g_onglet_defaut_pose &&
                    std::strcmp(f->tab, "Player") == 0) {
                    drapeaux = ImGuiTabItemFlags_SetSelected;
                    g_onglet_defaut_pose = true;
                }
                // Le 2e parametre est bool* p_open, PAS les drapeaux : les
                // drapeaux sont le 3e. Passer les drapeaux en 2e ne compile
                // meme pas, et c'est le seul endroit du fichier ou l'ordre
                // compte.
                const bool open = ImGui::BeginTabItem(f->tab, nullptr, drapeaux);
                vus[nvus].label = f->tab;
                vus[nvus].open = open;
                ++nvus;
                if (open) {
                    f->draw_ui();
                    ImGui::EndTabItem();
                }
            }

            if (ImGui::BeginTabItem("Misc")) {

                ImGui::Separator();
                ImGui::Checkbox("ImGui demo window", &g_demo);
                ImGui::Separator();
                ImGui::Text("FPS %.1f (%.2f ms)", io.Framerate,
                            1000.0f / (io.Framerate > 0.1f ? io.Framerate : 1.0f));
                if (ImGui::Button("Close menu  (DELETE)", ImVec2(-1.0f, 0.0f))) {
                    g_ui_enabled = false;
                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    if (g_demo) {
        ImGui::ShowDemoWindow(&g_demo);
    }
}

void render_frame()
{
    // Notre part du temps de frame. C'est LE chiffre qui dit si la chute de fps
    // est chez nous : tout le reste est la mesure en trop. Voir perf.h.
    const long long perf_t0 = perf::now_ns();
    struct PerfGuard {
        long long t0;
        ~PerfGuard() {
            perf::add(perf::kOverlay, perf::now_ns() - t0);
            perf::frame();
            perf::report();
        }
    } perf_guard{perf_t0};

    Frame& f = g_frames[g_frame_index % kFlight];
    if (f.fence && g_fence->GetCompletedValue() < f.fence) {
        g_fence->SetEventOnCompletion(f.fence, g_fence_event);
        if (WaitForSingleObject(g_fence_event, kFenceTimeoutMs) !=
            WAIT_OBJECT_0) {
            // Never block the render thread for good; skip this frame.
            log_once("GPU fence wait timed out during render");
            return;
        }
    }
    if (FAILED(f.alloc->Reset())) {
        return;
    }

    UINT idx = 0;
    if (g_sc3) {
        idx = g_sc3->GetCurrentBackBufferIndex();
    }
    if (idx >= g_buffer_count) {
        idx = g_frame_index % g_buffer_count;  // fallback
    }
    ID3D12Resource* back = g_buffers[idx];
    if (!back) {
        return;
    }

    ID3D12GraphicsCommandList* cl = g_cmd;
    if (FAILED(cl->Reset(f.alloc, nullptr))) {
        return;
    }

    D3D12_RESOURCE_BARRIER bar = {};
    bar.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    bar.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    bar.Transition.pResource = back;
    bar.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    bar.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    bar.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    cl->ResourceBarrier(1, &bar);

    cl->OMSetRenderTargets(1, &g_rtv_handles[idx], FALSE, nullptr);
    ID3D12DescriptorHeap* heaps[] = {g_srv};
    cl->SetDescriptorHeaps(1, heaps);

    D3D12_VIEWPORT vp = {0.0f, 0.0f, static_cast<float>(g_width),
                         static_cast<float>(g_height), 0.0f, 1.0f};
    D3D12_RECT sr = {0, 0, static_cast<LONG>(g_width),
                     static_cast<LONG>(g_height)};
    cl->RSSetViewports(1, &vp);
    cl->RSSetScissorRects(1, &sr);

    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cl);

    bar.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    bar.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    cl->ResourceBarrier(1, &bar);
    if (FAILED(cl->Close())) {
        return;
    }

    ID3D12CommandList* lists[] = {cl};
    g_queue->ExecuteCommandLists(1, lists);
    f.fence = ++g_fence_value;
    g_queue->Signal(g_fence, f.fence);
    ++g_frame_index;
}

}  // namespace

void set_probe_window(void* hwnd)
{
    g_probe_hwnd = static_cast<HWND>(hwnd);
    if (!g_hwnd) {
        g_hwnd = g_probe_hwnd;
    }
}

void on_command_queue(ID3D12CommandQueue* queue)
{
    if (!queue) {
        return;
    }
    const int n = g_queue_count.load(std::memory_order_acquire);
    for (int i = 0; i < n; ++i) {
        if (g_queues[i].load(std::memory_order_relaxed) == queue) {
            return;
        }
    }
    if (n < kMaxQueues) {
        g_queues[n].store(queue, std::memory_order_relaxed);
        g_queue_count.store(n + 1, std::memory_order_release);
        queue->AddRef();
    }
}

void on_resize(IDXGISwapChain* sc)
{
    (void)sc;
    // DXGI refuses to resize a swapchain while any of its back buffers are
    // referenced. Wait for our own in-flight work, then drop our references
    // before the original ResizeBuffers runs. RTVs are rebuilt next present.
    if (g_state == State::Ready) {
        flush_queue();
        release_buffers();
    }
    g_resize_dirty = true;
}

void on_present(IDXGISwapChain* sc)
{
    if (!sc) {
        return;
    }

    // Toggle is independent of state: SUPPR opens/closes the menu. While a text
    // field has focus (the Lua console) SUPPR is left to ImGui — there it is
    // "delete forward" — so the menu is then closed with the button instead.
    static bool prev_del = false;
    const bool del = is_vk_down(VK_DELETE);
    const bool want_text =
        ImGui::GetCurrentContext() != nullptr && ImGui::GetIO().WantTextInput;
    if (del && !prev_del && !want_text) {
        g_ui_enabled = !g_ui_enabled.load(std::memory_order_relaxed);
        log::info("overlay: menu %s (SUPPR)",
                  g_ui_enabled.load(std::memory_order_relaxed) ? "open"
                                                               : "closed");
    }
    prev_del = del;

    // Match the input gate + OS cursor to the menu state (block the game and
    // free the cursor while the menu is open). Only meaningful once the render
    // pipeline is live.
    input::set_menu_open(g_ui_enabled.load(std::memory_order_relaxed) &&
                              g_state == State::Ready);

    if (!g_ui_enabled.load(std::memory_order_relaxed)) {
        return;
    }

    if (g_state == State::Idle) {
        try {
            const InitResult r = init_once(sc);
            if (r == InitResult::Ok) {
                g_state = State::Ready;
                log::info("overlay: frame pipeline armed");
            } else if (r == InitResult::Fail) {
                // A deferral (waiting for the game's queue) is expected and
                // retried indefinitely; a hard failure is terminal so we never
                // re-run partial initialisation.
                g_state = State::Failed;
                log_once("D3D12 init failed");
            }
        } catch (...) {
            g_state = State::Failed;
            log_once("D3D12 init threw");
        }
        return;  // render starts next frame
    }
    if (g_state != State::Ready) {
        return;
    }

    // The input gate is armed by input::install() inside init_once(); if it
    // failed there (e.g. a prologue our decoder cannot handle) keep retrying
    // (throttled) in case the situation changes.
    if (!input::armed()) {
        static int retry = 0;
        if ((retry++ % 120) == 0) {
            input::install(g_hwnd ? g_hwnd : g_probe_hwnd);
        }
    }

    if (g_resize_dirty) {
        fetch_desc(sc);
        create_rtvs();
        g_resize_dirty = false;
    }

    try {
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        // feed_input() DOIT etre ICI, entre le NewFrame du backend et celui
        // d'ImGui -- et c'est l'ORDRE qui compte, pas la place dans le bloc.
        //
        // ImGui_ImplWin32_NewFrame() fait ceci, pour son repli :
        //
        //     if (!io.WantSetMousePos && bd->MouseTrackedArea == 0)
        //         io.AddMousePosEvent(pos.x, pos.y);   // GetCursorPos
        //
        // MouseTrackedArea vaut 0 parce que le backend ne voit JAMAIS
        // WM_MOUSEMOVE : c'est NOTRE sous-classe qui la recoit, et on ne le
        // transmet pas. Le backend croit donc la souris hors de la fenetre et
        // applique son repli — la position du curseur de l'OS.
        //
        // Or cette position est celle du JEU, donc VERROUILLEE au centre.
        //
        //feed_input etait appele AVANT : le backend ecrivait sa position apres
        // la notre, et la derniere ecriture gagne. Le curseur virtuel se
        // deplacait bien (mesure : 121 deltas, position 941,636 puis 493,594),
        // et la pastille restait collee au centre -- exactement ce que donnait
        // le symptome. La chaine fonctionnait; on etait ecrase juste apres.
        //
        // Apres, notre evenement est le dernier de la file, donc c'est lui qui
        // est lu. Les evenements ImGui sont traites dans l'ordre : dernier
        // ecrit, dernier lu.
        feed_input();
        // The Win32 backend sizes the display from the window's client area;
        // pin it to the swapchain so the UI always maps 1:1 to what we draw.
        ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(g_width),
                                             static_cast<float>(g_height));
        ImGui::NewFrame();
        build_ui();
        dessiner_pastille();
        ImGui::Render();
        render_frame();
    } catch (...) {
        g_state = State::Failed;
        log_once("frame threw - overlay disarmed");
    }
}

}  // namespace d3d12_overlay
}  // namespace specter::dxgi
