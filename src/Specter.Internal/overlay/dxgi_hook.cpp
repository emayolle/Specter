// Specter.Internal — DXGI swapchain hook (implementation).

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>

#include "overlay/dxgi_hook.h"
#include "overlay/detour.h"
#include "overlay/d3d12_overlay.h"
#include "log.h"

// Our own image base (the module is manually mapped; see entry.cpp).
extern "C" IMAGE_DOS_HEADER __ImageBase;
// CRT per-thread initialiser for threads entered outside the loader (nt.h).
extern "C" int __cdecl _CRT_INIT(void*, unsigned long, void*);

namespace specter::overlay {
namespace {

using D3D12CreateDeviceFn =
    HRESULT(WINAPI*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);
using CreateDXGIFactory2Fn = HRESULT(WINAPI*)(UINT, REFIID, void**);

Detour g_present;
Detour g_present1;
Detour g_resize;

using PresentFn = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);
using Present1Fn = HRESULT(WINAPI*)(IDXGISwapChain1*, UINT, UINT,
                                    const DXGI_PRESENT_PARAMETERS*);
using ResizeFn = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT, UINT,
                                  const DXGI_FORMAT*);

PresentFn g_o_present = nullptr;
Present1Fn g_o_present1 = nullptr;
ResizeFn g_o_resize = nullptr;

// Unity may present through Present (vt[8]) or Present1 (vt[22]); DXVK's
// Present1 can route back through the virtual Present. The guard makes sure
// the overlay is rendered exactly once per frame no matter which path the
// game takes. Re-entrancy here is synchronous, on the render thread, so a
// plain flag is enough (and thread_local is unsafe in a manually-mapped
// module, where the loader never sets up TLS).
bool g_in_present = false;

void render_once(IDXGISwapChain* sc)
{
    if (g_in_present) {
        return;
    }
    g_in_present = true;
    d3d12_overlay::on_present(sc);
    g_in_present = false;
}

HRESULT WINAPI present_proxy(IDXGISwapChain* sc, UINT sync, UINT flags)
{
    render_once(sc);
    return g_o_present ? g_o_present(sc, sync, flags) : E_FAIL;
}

HRESULT WINAPI present1_proxy(IDXGISwapChain1* sc, UINT sync, UINT flags,
                              const DXGI_PRESENT_PARAMETERS* params)
{
    render_once(sc);
    return g_o_present1 ? g_o_present1(sc, sync, flags, params) : E_FAIL;
}

HRESULT WINAPI resize_proxy(IDXGISwapChain* sc, UINT width, UINT height,
                            UINT flags, const DXGI_FORMAT* fmt)
{
    d3d12_overlay::on_resize(sc);
    return g_o_resize ? g_o_resize(sc, width, height, flags, fmt) : E_FAIL;
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

    // Every swapchain of this module shares the vtable code.
    void** vt = *reinterpret_cast<void***>(probe);
    const uintptr_t present = reinterpret_cast<uintptr_t>(vt[8]);    // Present
    const uintptr_t resize = reinterpret_cast<uintptr_t>(vt[13]);    // ResizeBuffers
    const uintptr_t present1 = reinterpret_cast<uintptr_t>(vt[22]);  // Present1

    // Present first, so a resize can never race an unhooked Present.
    if (!detour_install(&g_present, present,
                        reinterpret_cast<uintptr_t>(present_proxy))) {
        log::error("overlay: Present detour refused");
        probe->Release();
        factory->Release();
        DestroyWindow(hwnd);
        queue->Release();
        dev->Release();
        return false;
    }
    g_o_present = reinterpret_cast<PresentFn>(g_present.trampoline);

    // Present1 is best effort: Present already covers most paths.
    if (!detour_install(&g_present1, present1,
                        reinterpret_cast<uintptr_t>(present1_proxy))) {
        log::info("overlay: Present1 detour refused (Present stays)");
    } else {
        g_o_present1 = reinterpret_cast<Present1Fn>(g_present1.trampoline);
    }

    if (!detour_install(&g_resize, resize,
                        reinterpret_cast<uintptr_t>(resize_proxy))) {
        log::info("overlay: ResizeBuffers detour refused (Present stays)");
    } else {
        g_o_resize = reinterpret_cast<ResizeFn>(g_resize.trampoline);
    }

    d3d12_overlay::set_probe_window(hwnd);

    // Detours are on shared code; the probe objects themselves are no longer
    // needed.
    probe->Release();
    factory->Release();
    queue->Release();
    dev->Release();

    log::info("overlay: swapchain hooks live (Present=%p Present1=%p "
              "ResizeBuffers=%p)",
              (void*)present, (void*)present1, (void*)resize);
    return true;
}

}  // namespace specter::overlay