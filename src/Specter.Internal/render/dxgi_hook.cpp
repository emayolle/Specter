// Specter.Internal — DXGI/D3D12 vtable hook (implementation).
//
// The game renders through D3D12 (vkd3d-proton under Wine). Swapchains and
// command queues are COM objects whose methods live in one shared, immutable
// vtable array per class (in .rdata of dxgi.dll / d3d12core.dll). We probe the
// real classes with throwaway objects, read the class vtable, then swap the
// slots we care about for our proxies — the saved pointer is the "original".
//
// Why vtable patching instead of inline detours: an inline trampoline has to
// relocate the target's first whole instructions. DXVK's Present prologue is
//     mov rcx,[rcx+10] / mov rax,[rcx] / mov rax,[rax+40] / mov r10d,edx
// whose instruction boundaries do not line up with a fixed patch length, so a
// naive 12-byte copy splits `mov r10d,edx` and corrupts the trampoline. Vtable
// patching needs no relocation and covers every instance of the class.
//
// We also hook `ID3D12CommandQueue::ExecuteCommandLists` to learn the game's
// own command queue. vkd3d-proton enqueues the actual vkQueuePresentKHR on the
// swapchain's own queue (see libs/vkd3d/swapchain.c) and blits from the app's
// back buffer assuming same-queue ordering; rendering the overlay on a foreign
// queue is a cross-queue hazard. Using the game's queue keeps us correct.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>

#include "render/dxgi_hook.h"
#include "render/d3d12_overlay.h"
#include "platform/log.h"

// Our own image base (the module is manually mapped; see entry.cpp).
extern "C" IMAGE_DOS_HEADER __ImageBase;
// CRT per-thread initialiser for threads entered outside the loader (nt.h).
extern "C" int __cdecl _CRT_INIT(void*, unsigned long, void*);

namespace specter::dxgi {
namespace {

using D3D12CreateDeviceFn =
    HRESULT(WINAPI*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);
using CreateDXGIFactory2Fn = HRESULT(WINAPI*)(UINT, REFIID, void**);

// COM vtable slot indices (IUnknown layout included).
constexpr int kSlotPresent = 8;               // IDXGISwapChain::Present
constexpr int kSlotResizeBuffers = 13;        // IDXGISwapChain::ResizeBuffers
constexpr int kSlotPresent1 = 22;             // IDXGISwapChain1::Present1
constexpr int kSlotResizeBuffers1 = 30;       // IDXGISwapChain3::ResizeBuffers1
constexpr int kSlotExecuteCommandLists = 10;  // ID3D12CommandQueue

using PresentFn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
using Present1Fn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, UINT, UINT,
                                               const DXGI_PRESENT_PARAMETERS*);
using ResizeFn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, UINT,
                                             const DXGI_FORMAT*);
using Resize1Fn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain3*, UINT, UINT, UINT,
                                              DXGI_FORMAT, UINT, const UINT*,
                                              IUnknown* const*);
using ExecuteFn = void(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT,
                                           ID3D12CommandList* const*);

PresentFn g_o_present = nullptr;
Present1Fn g_o_present1 = nullptr;
ResizeFn g_o_resize = nullptr;
Resize1Fn g_o_resize1 = nullptr;
ExecuteFn g_o_execute = nullptr;

// Unity presents through Present (vt[8]) or Present1 (vt[22]); Present1 may
// route back through the virtual Present. The guard renders exactly once per
// frame regardless. Re-entrancy here is synchronous, on the render thread, so a
// plain flag is enough (thread_local is unsafe in a manually-mapped module,
// where the loader never sets up TLS).
bool g_in_present = false;

bool patch_slot(void** vt, int idx, void* fn)
{
    DWORD oldProtect = 0;
    void** slot = &vt[idx];
    if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE,
                        &oldProtect)) {
        return false;
    }
    *slot = fn;
    DWORD tmp = 0;
    VirtualProtect(slot, sizeof(void*), oldProtect, &tmp);
    return true;
}

void render_once(IDXGISwapChain* sc)
{
    if (g_in_present) {
        return;
    }
    g_in_present = true;
    render::on_present(sc);
    g_in_present = false;
}

HRESULT STDMETHODCALLTYPE present_proxy(IDXGISwapChain* sc, UINT sync,
                                        UINT flags)
{
    render_once(sc);
    return g_o_present ? g_o_present(sc, sync, flags) : E_FAIL;
}

HRESULT STDMETHODCALLTYPE present1_proxy(IDXGISwapChain1* sc, UINT sync,
                                         UINT flags,
                                         const DXGI_PRESENT_PARAMETERS* params)
{
    render_once(reinterpret_cast<IDXGISwapChain*>(sc));
    return g_o_present1 ? g_o_present1(sc, sync, flags, params) : E_FAIL;
}

HRESULT STDMETHODCALLTYPE resize_proxy(IDXGISwapChain* sc, UINT width,
                                       UINT height, UINT flags,
                                       const DXGI_FORMAT* fmt)
{
    render::on_resize(sc);
    return g_o_resize ? g_o_resize(sc, width, height, flags, fmt) : E_FAIL;
}

HRESULT STDMETHODCALLTYPE resize1_proxy(IDXGISwapChain3* sc, UINT count,
                                        UINT width, UINT height,
                                        DXGI_FORMAT fmt, UINT flags,
                                        const UINT* node_mask,
                                        IUnknown* const* present_queue)
{
    render::on_resize(reinterpret_cast<IDXGISwapChain*>(sc));
    return g_o_resize1
               ? g_o_resize1(sc, count, width, height, fmt, flags, node_mask,
                             present_queue)
               : E_FAIL;
}

void STDMETHODCALLTYPE execute_proxy(ID3D12CommandQueue* queue, UINT count,
                                     ID3D12CommandList* const* lists)
{
    render::on_command_queue(queue);
    if (g_o_execute) {
        g_o_execute(queue, count, lists);
    }
}

// Hidden window that backs the probe swapchain. Kept alive for the session:
// it is also the fallback hwnd for ImGui's platform backend when the game's
// swapchain does not report one.
HWND create_probe_window()
{
    static constexpr wchar_t kClass[] = L"SpecterOverlayProbe";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kClass;
    if (!RegisterClassW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        return nullptr;
    }
    return CreateWindowExW(0, kClass, L"", WS_POPUP, 0, 0, 16, 16, nullptr,
                           nullptr, wc.hInstance, nullptr);
}

}  // namespace

unsigned long WINAPI overlay_worker(void*)
{
    _CRT_INIT(reinterpret_cast<void*>(&__ImageBase), DLL_THREAD_ATTACH, nullptr);
    if (!dxgi_install()) {
        log::error("overlay: swapchain hooks not installed - no overlay");
    }
    return 0;
}

bool dxgi_install()
{
    // The game already runs the D3D12 backend, so these are loaded; this is
    // just taking our own reference.
    HMODULE d3d12 = LoadLibraryW(L"d3d12.dll");
    HMODULE dxgi = LoadLibraryW(L"dxgi.dll");
    if (!d3d12 || !dxgi) {
        log::error("overlay: d3d12.dll/dxgi.dll not loadable");
        return false;
    }

    auto pCreateDevice = reinterpret_cast<D3D12CreateDeviceFn>(
        GetProcAddress(d3d12, "D3D12CreateDevice"));
    auto pCreateFactory = reinterpret_cast<CreateDXGIFactory2Fn>(
        GetProcAddress(dxgi, "CreateDXGIFactory2"));
    if (!pCreateDevice || !pCreateFactory) {
        log::error("overlay: D3D12CreateDevice / CreateDXGIFactory2 unresolved");
        return false;
    }

    // Probe device + queue. A second D3D12 device is cheap; it never renders.
    ID3D12Device* dev = nullptr;
    if (FAILED(pCreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0,
                             __uuidof(ID3D12Device), (void**)&dev)) ||
        !dev) {
        log::error("overlay: D3D12CreateDevice failed (vulkan dx12 missing?)");
        return false;
    }
    ID3D12CommandQueue* queue = nullptr;
    {
        D3D12_COMMAND_QUEUE_DESC qd = {};
        qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        if (FAILED(dev->CreateCommandQueue(&qd, __uuidof(ID3D12CommandQueue),
                                           (void**)&queue)) ||
            !queue) {
            log::error("overlay: probe CreateCommandQueue failed");
            dev->Release();
            return false;
        }
    }

    HWND hwnd = create_probe_window();
    if (!hwnd) {
        log::error("overlay: probe window creation failed");
        queue->Release();
        dev->Release();
        return false;
    }

    IDXGIFactory4* factory = nullptr;
    if (FAILED(pCreateFactory(0, __uuidof(IDXGIFactory4), (void**)&factory)) ||
        !factory) {
        log::error("overlay: CreateDXGIFactory2 failed");
        DestroyWindow(hwnd);
        queue->Release();
        dev->Release();
        return false;
    }

    DXGI_SWAP_CHAIN_DESC1 sd1 = {};
    sd1.Width = 16;
    sd1.Height = 16;
    sd1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd1.BufferCount = 2;
    sd1.SampleDesc.Count = 1;
    sd1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd1.Scaling = DXGI_SCALING_STRETCH;
    IDXGISwapChain1* probe = nullptr;
    if (FAILED(factory->CreateSwapChainForHwnd(queue, hwnd, &sd1, nullptr,
                                               nullptr, &probe)) ||
        !probe) {
        log::error("overlay: probe CreateSwapChain failed");
        factory->Release();
        DestroyWindow(hwnd);
        queue->Release();
        dev->Release();
        return false;
    }

    // Every instance of a class shares the vtable, so the probe tells us the
    // exact slots the game's own objects dispatch through.
    void** sc_vt = *reinterpret_cast<void***>(probe);
    void** q_vt = *reinterpret_cast<void***>(queue);

    g_o_execute = reinterpret_cast<ExecuteFn>(q_vt[kSlotExecuteCommandLists]);
    if (!patch_slot(q_vt, kSlotExecuteCommandLists,
                    reinterpret_cast<void*>(execute_proxy))) {
        log::error("overlay: ExecuteCommandLists vtable patch failed");
    }

    g_o_present = reinterpret_cast<PresentFn>(sc_vt[kSlotPresent]);
    g_o_present1 = reinterpret_cast<Present1Fn>(sc_vt[kSlotPresent1]);
    g_o_resize = reinterpret_cast<ResizeFn>(sc_vt[kSlotResizeBuffers]);
    g_o_resize1 = reinterpret_cast<Resize1Fn>(sc_vt[kSlotResizeBuffers1]);

    if (!patch_slot(sc_vt, kSlotPresent,
                    reinterpret_cast<void*>(present_proxy))) {
        log::error("overlay: Present vtable patch failed");
        g_o_present = nullptr;
    }
    // Present1/ResizeBuffers are best effort: Present already covers most
    // paths, and the resize hooks just free our back-buffer references early.
    if (!patch_slot(sc_vt, kSlotPresent1,
                    reinterpret_cast<void*>(present1_proxy))) {
        log::info("overlay: Present1 vtable patch failed (Present stays)");
        g_o_present1 = nullptr;
    }
    if (!patch_slot(sc_vt, kSlotResizeBuffers,
                    reinterpret_cast<void*>(resize_proxy))) {
        log::info("overlay: ResizeBuffers vtable patch failed");
        g_o_resize = nullptr;
    }
    if (!patch_slot(sc_vt, kSlotResizeBuffers1,
                    reinterpret_cast<void*>(resize1_proxy))) {
        log::info("overlay: ResizeBuffers1 vtable patch failed");
        g_o_resize1 = nullptr;
    }

    render::set_probe_window(hwnd);

    // The probe objects themselves are no longer needed; the patches live on
    // the shared class vtable.
    probe->Release();
    factory->Release();
    queue->Release();
    dev->Release();

    log::info("overlay: swapchain vtable hooked (Present=%p Present1=%p "
              "ResizeBuffers=%p ResizeBuffers1=%p Execute=%p)",
              (void*)g_o_present, (void*)g_o_present1, (void*)g_o_resize,
              (void*)g_o_resize1, (void*)g_o_execute);
    return true;
}

}  // namespace specter::dxgi
