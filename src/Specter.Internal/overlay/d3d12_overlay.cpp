// Specter.Internal — ImGui/D3D12 overlay bridge (implementation).
//
// Frame flow (see third_party/imgui/examples/example_win32_directx12):
//   ImGui_ImplDX12_NewFrame -> ImGui_ImplWin32_NewFrame -> ImGui::NewFrame
//   -> ImGui::Render -> record our command list (barrier, RT, draw data)
//   -> execute on OUR queue -> signal fence. The Present detour wrapper then
//   calls the original Present, which presents the frame with the overlay.
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

#include "overlay/d3d12_overlay.h"
#include "il2cpp-api.h"
#include "log.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

namespace specter::overlay {
namespace d3d12_overlay {
namespace {

constexpr UINT kSrvHeapSize = 128;  // power of two: the bump allocator wraps
constexpr UINT kRtvHeapSize = 8;
constexpr UINT kFlight = 3;

enum class State { Idle, Ready, Failed };

std::atomic<bool> g_ui_enabled{true};
State g_state = State::Idle;
int g_init_tries = 0;
bool g_err_logged = false;

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

bool init_once(IDXGISwapChain* sc)
{
    // Game device + swapchain3.
    if (FAILED(sc->GetDevice(__uuidof(ID3D12Device), (void**)&g_dev)) ||
        !g_dev) {
        return false;
    }
    if (FAILED(sc->QueryInterface(__uuidof(IDXGISwapChain3),
                                 (void**)&g_sc3))) {
        g_sc3 = nullptr;
    }
    fetch_desc(sc);

    // Our own command queue on the game's device.
    {
        D3D12_COMMAND_QUEUE_DESC qd = {};
        qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        qd.NodeMask = 1;
        if (FAILED(g_dev->CreateCommandQueue(&qd, __uuidof(ID3D12CommandQueue),
                                             (void**)&g_queue)) ||
            !g_queue) {
            return false;
        }
    }

    // Shader-visible SRV heap (fonts/textures) with a wrapping bump allocator.
    {
        D3D12_DESCRIPTOR_HEAP_DESC hd = {};
        hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        hd.NumDescriptors = kSrvHeapSize;
        hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        hd.NodeMask = 1;
        if (FAILED(g_dev->CreateDescriptorHeap(
                &hd, __uuidof(ID3D12DescriptorHeap), (void**)&g_srv)) ||
            !g_srv) {
            return false;
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
        hd.NodeMask = 1;
        if (FAILED(g_dev->CreateDescriptorHeap(
                &hd, __uuidof(ID3D12DescriptorHeap), (void**)&g_rtv)) ||
            !g_rtv) {
            return false;
        }
        g_rtv_stride = g_dev->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    for (auto& f : g_frames) {
        if (FAILED(g_dev->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator),
                (void**)&f.alloc)) ||
            !f.alloc) {
            return false;
        }
    }
    if (FAILED(g_dev->CreateCommandList(
            0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frames[0].alloc, nullptr,
            __uuidof(ID3D12GraphicsCommandList), (void**)&g_cmd)) ||
        !g_cmd) {
        return false;
    }
    g_cmd->Close();
    if (FAILED(g_dev->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                  __uuidof(ID3D12Fence), (void**)&g_fence)) ||
        !g_fence) {
        return false;
    }
    g_fence_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_fence_event) {
        return false;
    }

    create_rtvs();
    g_resize_dirty = false;

    build_snapshot();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;   // never write imgui.ini into the game prefix
    io.LogFilename = nullptr;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(g_hwnd ? g_hwnd : g_probe_hwnd);

    ImGui_ImplDX12_InitInfo info = {};
    info.Device = g_dev;
    info.CommandQueue = g_queue;
    info.NumFramesInFlight = static_cast<int>(
        g_buffer_count < kFlight ? g_buffer_count : kFlight);
    info.RTVFormat = g_format;
    info.DSVFormat = DXGI_FORMAT_UNKNOWN;
    info.SrvDescriptorHeap = g_srv;
    info.SrvDescriptorAllocFn = srv_alloc;
    info.SrvDescriptorFreeFn = srv_free;
    if (!ImGui_ImplDX12_Init(&info)) {
        return false;
    }

    log::info("overlay: D3D12 ImGui ready (buffers=%u fmt=%d %ux%u hwnd=%p)",
              g_buffer_count, static_cast<int>(g_format), g_width, g_height,
              (void*)g_hwnd);
    return true;
}

bool is_vk_down(int vk)
{
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
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
    ImGui::SetNextWindowPos(ImVec2(24.0f, 24.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Specter")) {
        ImGui::TextUnformatted(g_snapshot);
        ImGui::Separator();
        ImGui::Checkbox("ImGui demo window", &g_demo);
        ImGui::TextUnformatted("menu: SUPPR pour ouvrir/fermer");
        ImGui::Text("FPS %.1f (%.2f ms)", io.Framerate,
                    1000.0f / (io.Framerate > 0.1f ? io.Framerate : 1.0f));
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
        WaitForSingleObject(g_fence_event, INFINITE);
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

void on_resize(IDXGISwapChain* sc)
{
    (void)sc;
    g_resize_dirty = true;
}

void on_present(IDXGISwapChain* sc)
{
    if (!sc) {
        return;
    }

    // Toggle is independent of state: SUPPR opens/closes the menu.
    static bool prev_del = false;
    const bool del = is_vk_down(VK_DELETE);
    if (del && !prev_del) {
        g_ui_enabled = !g_ui_enabled.load(std::memory_order_relaxed);
        log::info("overlay: menu %s (SUPPR)",
                  g_ui_enabled.load(std::memory_order_relaxed) ? "ouvert"
                                                               : "ferme");
    }
    prev_del = del;

    if (!g_ui_enabled.load(std::memory_order_relaxed)) {
        return;
    }

    if (g_state == State::Idle) {
        if (++g_init_tries > 3) {
            g_state = State::Failed;
            log_once("D3D12 init failed after 3 attempts");
            return;
        }
        try {
            if (init_once(sc)) {
                g_state = State::Ready;
                log::info("overlay: frame pipeline armed");
            } else {
                log_once("D3D12 init failed (will retry)");
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

    if (g_resize_dirty) {
        fetch_desc(sc);
        create_rtvs();
        g_resize_dirty = false;
    }

    try {
        feed_input();
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
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