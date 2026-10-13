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

#include "overlay/d3d12_overlay.h"
#include "overlay/game_input.h"
#include "features/lua_console.h"
#include "features/tp.h"
#include "il2cpp-api.h"
#include "log.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

// imgui_impl_win32.h deliberately hides this in a '#if 0' (to avoid forcing
// <windows.h> on includers); we already have <windows.h>, so declare it here.
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace specter::overlay {
namespace d3d12_overlay {
namespace {

constexpr UINT kSrvHeapSize = 128;  // power of two: the bump allocator wraps
constexpr UINT kRtvHeapSize = 8;
constexpr UINT kFlight = 3;
constexpr DWORD kFenceTimeoutMs = 2000;  // never block the render thread for good

enum class State { Idle, Ready, Failed };
enum class InitResult { Ok, Defer, Fail };

std::atomic<bool> g_ui_enabled{true};
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

// ---- Lua console state (touch()d only on the render thread) ----------------

char g_lua_src[16384] =
    "-- Specter Lua console - runs in the game's own lua_State, on the game's\n"
    "-- Lua thread. `print(...)` output and the chunk's return values appear\n"
    "-- below; errors are caught and reported.\n"
    "print('hello from Specter', _VERSION)";
std::string g_lua_log;

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
    using namespace specter::api;
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
        if (FAILED(sc->GetDevice(__uuidof(ID3D12Device), (void**)&g_dev)) ||
            !g_dev) {
            return InitResult::Fail;
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
    game_input::install(g_hwnd ? g_hwnd : g_probe_hwnd);

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
    // The game hides the OS cursor; draw ImGui's own so the user can see what
    // they are pointing at. The OS cursor is forced hidden while the menu is up
    // (see overlay/game_input.*).
    io.MouseDrawCursor = true;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(g_hwnd ? g_hwnd : g_probe_hwnd);

    // Once the context exists, route keyboard messages the subclass swallows to
    // ImGui, so the Lua console can receive typed text.
    game_input::set_keyboard_sink(&keyboard_sink);

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
    return (game_input::real_async_key_state(vk) & 0x8000) != 0;
}

void feed_input()
{
    ImGuiIO& io = ImGui::GetIO();

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

void build_ui()
{
    ImGuiIO& io = ImGui::GetIO();

    // Drain whatever the Lua thread produced since the last frame.
    {
        char buf[8192];
        bool ok = false;
        if (features::lua::take_result(buf, sizeof(buf), &ok)) {
            g_lua_log += ok ? "> " : "! ";
            g_lua_log += buf;
            g_lua_log += '\n';
            constexpr std::size_t kKeep = 60000;
            if (g_lua_log.size() > kKeep) {
                g_lua_log.erase(0, g_lua_log.size() - kKeep / 2);
            }
        }
    }

    // Drain the dedicated teleport channel and feed parsed position data.
    if (!g_tp_loaded) {
        g_tp_loaded = true;
        features::tp::init();
    }
    {
        char buf[256];
        bool ok = false;
        if (features::lua::tp_take_result(buf, sizeof(buf), &ok)) {
            features::tp::handle_result(buf);
        }
    }

    ImGui::SetNextWindowPos(ImVec2(24.0f, 24.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(780.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Specter")) {
        ImGui::TextUnformatted(g_snapshot);
        ImGui::Separator();

        if (ImGui::BeginTabBar("##main_tabs")) {
            if (ImGui::BeginTabItem("Lua Editor")) {
                ImGui::Text("bridge: %s", features::lua::status());
                ImGui::InputTextMultiline("##lua_src", g_lua_src,
                                          sizeof(g_lua_src),
                                          ImVec2(-1.0f, 180.0f));
                if (ImGui::Button("Execute")) {
                    const int n = static_cast<int>(std::strlen(g_lua_src));
                    if (!features::lua::submit(g_lua_src, n)) {
                        g_lua_log += "! bridge not ready\n";
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear output")) {
                    g_lua_log.clear();
                }
                ImGui::SameLine();
                ImGui::TextDisabled("(an infinite loop freezes the game)");

                ImGui::BeginChild("##lua_out", ImVec2(-1.0f, -1.0f), true);
                ImGui::TextUnformatted(g_lua_log.c_str());
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Teleport")) {
                // Poll the player's position while the tab is visible (~0.75 s
                // at 60 fps). The chunks run on the game's Lua thread.
                if (++g_tp_refresh >= 45) {
                    g_tp_refresh = 0;
                    if (features::lua::ready()) {
                        features::tp::request_position();
                    }
                }

                float cx = 0.0f, cy = 0.0f, cz = 0.0f;
                int csp = 0;
                if (features::tp::have_position()) {
                    features::tp::position(&cx, &cy, &cz, &csp);
                    ImGui::Text("Position: (%.2f, %.2f, %.2f)  space %d", cx, cy,
                                cz, csp);
                } else {
                    ImGui::TextDisabled(
                        "position unknown - wait until you are in-world");
                }

                ImGui::SetNextItemWidth(180.0f);
                ImGui::InputText("Name", g_tp_name, sizeof(g_tp_name));
                ImGui::SameLine();
                if (ImGui::Button("Save current position")) {
                    if (!features::tp::save_current(g_tp_name)) {
                        g_lua_log +=
                            "! tp: nothing saved (need a live position or a "
                            "non-empty name)\n";
                    }
                }

                ImGui::Separator();
                ImGui::TextUnformatted("Lerp tuning");
                ImGui::SameLine();
                ImGui::TextDisabled(
                    "(a teleport walks to the target in small steps)");
                float stepv = features::tp::lerp_step();
                ImGui::SetNextItemWidth(240.0f);
                if (ImGui::SliderFloat("Step size (u)", &stepv, 0.25f, 20.0f,
                                       "%.2f u/step")) {
                    features::tp::set_lerp_step(stepv);
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "Distance moved per small TP. Too big and the server "
                        "rejects it (rubber-band).");
                }
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    features::tp::persist();
                }
                float spdv = features::tp::lerp_speed();
                ImGui::SetNextItemWidth(240.0f);
                if (ImGui::SliderFloat("Speed (steps/s)", &spdv, 5.0f, 120.0f,
                                       "%.0f steps/s")) {
                    features::tp::set_lerp_speed(spdv);
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "How many steps are applied per second (capped by the "
                        "game frame rate).");
                }
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    features::tp::persist();
                }
                const float fps = ImGui::GetIO().Framerate;
                const float cap = fps > 1.0f ? fps : 60.0f;
                const float sps = features::tp::lerp_speed();
                const float eff_speed = sps < cap ? sps : cap;
                ImGui::TextDisabled(
                    "=> ~%.0f u/s  (step x min(speed, %.0f fps))",
                    features::tp::lerp_step() * eff_speed, cap);

                ImGui::Separator();
                ImGui::BeginChild("##tp_slots", ImVec2(-1.0f, -1.0f), true);
                if (features::tp::count() == 0) {
                    ImGui::TextDisabled("no saved positions yet");
                }
                for (int i = 0; i < features::tp::count(); ++i) {
                    char nm[36] = {};
                    float sx = 0.0f, sy = 0.0f, sz = 0.0f;
                    features::tp::get_slot(i, nm, sizeof(nm), &sx, &sy, &sz);
                    ImGui::PushID(i);
                    ImGui::TextUnformatted(nm);
                    ImGui::SameLine();
                    ImGui::TextDisabled("(%.2f, %.2f, %.2f)", sx, sy, sz);
                    ImGui::SameLine();
                    if (ImGui::SmallButton("Teleport")) {
                        if (!features::tp::teleport_to(i)) {
                            g_lua_log += "! tp: bridge not ready\n";
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::SmallButton("Delete")) {
                        features::tp::remove_at(i);
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
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Waypoints")) {
                const int nflora = features::tp::floraison_count();
                const int nwp = features::tp::waypoint_count();
                // One-shot fetch if a cached list is missing (e.g. /tmp was
                // wiped by a reboot). Both lists come from the same scan.
                if (!g_wp_auto && (nflora == 0 || nwp == 0) &&
                    features::lua::ready()) {
                    g_wp_auto = true;
                    features::tp::request_marks();
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
                    features::tp::get_floraison(i, &z, nullptr, nullptr,
                                                nullptr);
                    add_zone(z);
                }
                for (int i = 0; i < nwp; ++i) {
                    int z = 0;
                    features::tp::get_waypoint(i, &z, nullptr, 0, nullptr,
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

                if (features::tp::marks_pending()) {
                    ImGui::TextDisabled("scanning the game...");
                } else {
                    ImGui::TextDisabled(
                        "%d zone(s): %d Floraison(s), %d waypoint(s)", nz,
                        nflora, nwp);
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Refresh from game")) {
                    if (features::lua::ready()) {
                        features::tp::request_marks();
                    } else {
                        g_lua_log += "! tp: bridge not ready\n";
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
                    ImGui::TextDisabled(
                        "nothing yet - press Refresh once in-world");
                }
                for (int zi = 0; zi < nz; ++zi) {
                    const int zone = zones[zi];
                    ImGui::Separator();
                    ImGui::TextDisabled("Zone %d", zone);
                    for (int i = 0; i < nflora; ++i) {
                        int z = 0;
                        float fx = 0.0f, fy = 0.0f, fz = 0.0f;
                        features::tp::get_floraison(i, &z, &fx, &fy, &fz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(100000 + i);
                        ImGui::TextUnformatted("Floraison");
                        ImGui::SameLine();
                        ImGui::TextDisabled("(%.1f, %.1f, %.1f)", fx, fy, fz);
                        ImGui::SameLine();
                        if (ImGui::SmallButton("Teleport")) {
                            if (!features::tp::teleport_to_floraison(i)) {
                                g_lua_log += "! tp: bridge not ready\n";
                            }
                        }
                        ImGui::PopID();
                    }
                    for (int i = 0; i < nwp; ++i) {
                        int z = 0;
                        char nm[64] = {};
                        float wx = 0.0f, wy = 0.0f, wz = 0.0f;
                        features::tp::get_waypoint(i, &z, nm, sizeof(nm), &wx,
                                                   &wy, &wz);
                        if (z != zone) {
                            continue;
                        }
                        ImGui::PushID(200000 + i);
                        ImGui::TextUnformatted(nm[0] ? nm : "(unnamed)");
                        ImGui::SameLine();
                        ImGui::TextDisabled("(%.1f, %.1f, %.1f)", wx, wy, wz);
                        ImGui::SameLine();
                        if (ImGui::SmallButton("Teleport")) {
                            if (!features::tp::teleport_to_waypoint(i)) {
                                g_lua_log += "! tp: bridge not ready\n";
                            }
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Miscellaneous")) {
                bool inf = features::lua::infinite_stamina();
                if (ImGui::Checkbox(
                        "Infinite movement stamina (sprint/dash/glide/climb)",
                        &inf)) {
                    if (!features::lua::set_infinite_stamina(inf)) {
                        g_lua_log += "! bridge not ready - can't toggle stamina\n";
                    }
                }
                ImGui::SameLine();
                ImGui::TextDisabled("(?)");
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(
                        "Intercepts the player's stamina cost function "
                        "(changeStamina): sprint/dash/glide/climb costs are "
                        "blocked and stamina is refilled to full once at "
                        "install. Re-applies automatically after a scene "
                        "change or relog (~10 s).");
                }

                ImGui::Separator();
                ImGui::Checkbox("ImGui demo window", &g_demo);
                ImGui::Separator();
                ImGui::Text("FPS %.1f (%.2f ms)", io.Framerate,
                            1000.0f / (io.Framerate > 0.1f ? io.Framerate : 1.0f));
                if (ImGui::Button("Close menu (DELETE)", ImVec2(-1.0f, 0.0f))) {
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
    game_input::set_menu_open(g_ui_enabled.load(std::memory_order_relaxed) &&
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

    // The input gate is armed by game_input::install() inside init_once(); if it
    // failed there (e.g. a prologue our decoder cannot handle) keep retrying
    // (throttled) in case the situation changes.
    if (!game_input::armed()) {
        static int retry = 0;
        if ((retry++ % 120) == 0) {
            game_input::install(g_hwnd ? g_hwnd : g_probe_hwnd);
        }
    }

    if (g_resize_dirty) {
        fetch_desc(sc);
        create_rtvs();
        g_resize_dirty = false;
    }

    try {
        feed_input();
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        // The Win32 backend sizes the display from the window's client area;
        // pin it to the swapchain so the UI always maps 1:1 to what we draw.
        ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(g_width),
                                             static_cast<float>(g_height));
        ImGui::NewFrame();
        build_ui();
        ImGui::Render();
        render_frame();
    } catch (...) {
        g_state = State::Failed;
        log_once("frame threw - overlay disarmed");
    }
}

}  // namespace d3d12_overlay
}  // namespace specter::overlay
