// Specter.Internal — D3DCompile forwarder (keeps d3dcompiler_XX out of the
// import table).
//
// Dear ImGui's DX12 backend compiles its two shaders at runtime with
// D3DCompile(), and the SDK's d3dcompiler.lib would resolve that by importing
// D3DCOMPILER_47.dll at LOAD time. Our module is manually mapped: every import
// must already be resident in the guest before mapping, and Aniimo does not load
// d3dcompiler_47.dll -> the hard import makes `map --pe` fail.
//
// D3DCompile is declared WITHOUT __declspec(dllimport) in <d3dcompiler.h>, so a
// local definition satisfies the backend's call sites and the import library is
// never pulled in. We resolve the real implementation lazily, on first use, from
// whichever d3dcompiler_XX.dll exists - the same two calls that the backend
// makes, from our own code path.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3dcompiler.h>

#include "log.h"

namespace {

using D3DCompileFn = pD3DCompile;

D3DCompileFn g_compile = nullptr;
bool g_resolved = false;

// Called from the render thread only (ImGui_ImplDX12_CreateDeviceObjects), so a
// plain flag is enough and we avoid a function-local static with dynamic init
// (unsafe in a manually-mapped module).
D3DCompileFn resolve_compile()
{
    if (g_resolved) {
        return g_compile;
    }
    g_resolved = true;

    static const char* const kCandidates[] = {
        "d3dcompiler_47.dll", "d3dcompiler_46.dll",
        "d3dcompiler_45.dll", "d3dcompiler_43.dll",
        "d3dcompiler.dll",
    };
    for (const char* name : kCandidates) {
        HMODULE mod = LoadLibraryA(name);
        if (!mod) {
            continue;
        }
        g_compile = reinterpret_cast<D3DCompileFn>(
            reinterpret_cast<void*>(GetProcAddress(mod, "D3DCompile")));
        if (g_compile) {
            specter::log::info("overlay: shader compiler resolved from %s",
                               name);
            return g_compile;
        }
    }

    specter::log::error("overlay: no d3dcompiler_XX.dll providing D3DCompile");
    return nullptr;
}

}  // namespace

// Not dllimport -> this definition is what the DX12 backend calls.
extern "C" HRESULT WINAPI D3DCompile(
    const void* pSrcData, SIZE_T SrcDataSize, const char* pSourceName,
    const D3D_SHADER_MACRO* pDefines, ID3DInclude* pInclude,
    const char* pEntrypoint, const char* pTarget, UINT Flags1, UINT Flags2,
    ID3DBlob** ppCode, ID3DBlob** ppErrorMsgs)
{
    D3DCompileFn fn = resolve_compile();
    if (!fn) {
        return E_FAIL;
    }
    return fn(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
              pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
}
