__int64 __fastcall StartAddress(LPVOID lpThreadParameter)
{
  HMODULE ModuleHandleA; // rax
  const CHAR *v2; // rax
  HMODULE v3; // rax
  __int64 v4; // rbx
  __int128 *v5; // rcx
  __int64 v6; // rdx
  HMODULE v8; // rax
  const CHAR *v9; // rax
  __int128 *v10; // rcx
  __int64 v11; // rbx
  HANDLE v12; // rax
  int v13; // edi
  void *v14; // rcx
  const CHAR *v15; // rbx
  const CHAR *v16; // rax
  HWND Window; // rsi
  _BYTE *v18; // rcx
  __int64 v19; // rdx
  __int128 *v20; // rax
  __int64 v21; // rcx
  HRESULT (__stdcall *Present)(IDXGISwapChain *, UINT, UINT); // rbx
  HRESULT (__stdcall *ResizeBuffers)(IDXGISwapChain *, UINT, UINT, UINT, DXGI_FORMAT, UINT); // rdi
  HANDLE CurrentThread; // rax
  HANDLE v25; // rax
  __int128 v26; // [rsp+60h] [rbp-A0h] BYREF
  __int64 v27; // [rsp+70h] [rbp-90h]
  unsigned __int64 v28; // [rsp+78h] [rbp-88h]
  IDXGISwapChain *ppSwapChain; // [rsp+80h] [rbp-80h] BYREF
  ID3D11Device *ppDevice; // [rsp+88h] [rbp-78h] BYREF
  _BYTE v31[16]; // [rsp+90h] [rbp-70h] BYREF
  DXGI_SWAP_CHAIN_DESC pSwapChainDesc; // [rsp+A0h] [rbp-60h] BYREF
  __int64 v33; // [rsp+168h] [rbp+68h] BYREF
  __int64 v34; // [rsp+170h] [rbp+70h] BYREF
  D3D_FEATURE_LEVEL pFeatureLevel; // [rsp+178h] [rbp+78h] BYREF

  sub_180029000("--- DLL Injected: MainThread started ---");
  while ( !GetModuleHandleA("GameAssembly.dll") )
    Sleep(0x1F4u);
  ModuleHandleA = GetModuleHandleA("GameAssembly.dll");
  sub_180029000("GameAssembly.dll detected at 0x%p", ModuleHandleA);
  Sleep(0xBB8u);
  sub_180029000("Calling SetupGameHooks()...");
  v2 = (const CHAR *)sub_180033E50(&v33, &v26);
  v3 = GetModuleHandleA(v2);
  v4 = 17;
  if ( BYTE1(v27) )
  {
    v5 = &v26;
    v6 = 17;
    do
    {
      *(_BYTE *)v5 = 0;
      v5 = (__int128 *)((char *)v5 + 1);
      --v6;
    }
    while ( v6 );
  }
  if ( v3 )
  {
    qword_18010C460 = (__int64)v3;
    sub_180029000("[LUA] LuaExecutor::Start called");
    sub_18002A1C0();
    if ( byte_18010C58D && qword_18010C5B0 )
      goto LABEL_24;
    v8 = (HMODULE)qword_18010C460;
    if ( !qword_18010C460 )
    {
      v9 = (const CHAR *)sub_18002C340(&v33, &v26);
      v8 = GetModuleHandleA(v9);
      if ( BYTE1(v27) )
      {
        v10 = &v26;
        do
        {
          *(_BYTE *)v10 = 0;
          v10 = (__int128 *)((char *)v10 + 1);
          --v4;
        }
        while ( v4 );
      }
      if ( !v8 )
      {
LABEL_24:
        sub_180029000("SetupGameHooks() succeeded.");
        sub_180029000("Calling SetupRenderHooks()...");
        v15 = (const CHAR *)sub_1800339D0(&v33, &v26);
        v16 = (const CHAR *)sub_180033570(&v34, v31);
        Window = CreateWindowExA(0, v16, v15, 0xCF0000u, 0, 0, 100, 100, nullptr, nullptr, nullptr, nullptr);
        if ( v31[7] )
        {
          v18 = v31;
          v19 = 7;
          do
          {
            *v18++ = 0;
            --v19;
          }
          while ( v19 );
        }
        if ( BYTE9(v26) )
        {
          v20 = &v26;
          v21 = 9;
          do
          {
            *(_BYTE *)v20 = 0;
            v20 = (__int128 *)((char *)v20 + 1);
            --v21;
          }
          while ( v21 );
        }
        if ( Window )
        {
          *(_QWORD *)&pSwapChainDesc.BufferDesc.Width = 0;
          pSwapChainDesc.BufferDesc.RefreshRate = 0;
          *(_QWORD *)&pSwapChainDesc.BufferDesc.ScanlineOrdering = 0;
          pSwapChainDesc.SampleDesc.Quality = 0;
          *(_QWORD *)&pSwapChainDesc.BufferCount = 1;
          *(_QWORD *)&pSwapChainDesc.Flags = 0;
          pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
          pSwapChainDesc.BufferUsage = 32;
          pSwapChainDesc.OutputWindow = Window;
          pSwapChainDesc.SampleDesc.Count = 1;
          *(_QWORD *)&pSwapChainDesc.Windowed = 1;
          ppDevice = nullptr;
          ppSwapChain = nullptr;
          if ( D3D11CreateDeviceAndSwapChain(
                 nullptr,
                 D3D_DRIVER_TYPE_HARDWARE,
                 nullptr,
                 0,
                 nullptr,
                 0,
                 7u,
                 &pSwapChainDesc,
                 &ppSwapChain,
                 &ppDevice,
                 &pFeatureLevel,
                 nullptr) >= 0 )
          {
            Present = ppSwapChain->lpVtbl->Present;
            ResizeBuffers = ppSwapChain->lpVtbl->ResizeBuffers;
            ((void (__fastcall *)(IDXGISwapChain *))ppSwapChain->lpVtbl->Release)(ppSwapChain);
            ((void (__fastcall *)(ID3D11Device *))ppDevice->lpVtbl->Release)(ppDevice);
            DestroyWindow(Window);
            qword_18010C8F8 = (__int64)Present;
            qword_18010C8E8 = (__int64)ResizeBuffers;
            sub_180091250();
            CurrentThread = GetCurrentThread();
            sub_180091770(CurrentThread);
            sub_180090800(&qword_18010C8F8, sub_1800314D0);
            if ( qword_18010C8E8 )
              sub_180090800(&qword_18010C8E8, sub_1800334B0);
            _report_rangecheckfailure();
          }
          DestroyWindow(Window);
        }
        sub_180029000("SetupRenderHooks() completed.");
        while ( !byte_18010C450 )
        {
          if ( (GetAsyncKeyState(35) & 1) != 0 )
            byte_18010C450 = 1;
          Sleep(0x64u);
        }
        sub_180029000("Unloading DLL: TeardownAllHooks()...");
        sub_180091250();
        v25 = GetCurrentThread();
        sub_180091770(v25);
        if ( byte_18010C50F && qword_18010C5A8 )
        {
          sub_180090EB0(&qword_18010C5A8, sub_180029960);
          byte_18010C50F = 0;
          qword_18010C5A8 = 0;
        }
        if ( byte_18010C58D && qword_18010C5B0 )
        {
          sub_180090EB0(&qword_18010C5B0, sub_180029AB0);
          byte_18010C58D = 0;
          qword_18010C5B0 = 0;
        }
        _report_rangecheckfailure();
      }
      qword_18010C460 = (__int64)v8;
    }
    v11 = (__int64)(v8 + 6056448);
    if ( v8 != (HMODULE)-24225792LL )
    {
      sub_180029000("[HOOK] Found GameManager::CommonUpdate at 0x%p. Attaching Detour...", v8 + 6056448);
      qword_18010C5B0 = v11;
      sub_180091250();
      v12 = GetCurrentThread();
      sub_180091770(v12);
      v13 = sub_180090800(&qword_18010C5B0, sub_180029AB0);
      if ( !v13 )
        _report_rangecheckfailure();
      sub_180091100();
      qword_18010C5B0 = 0;
      sub_180029000("[ERROR] DetourAttach failed for GameManager::CommonUpdate: %ld", v13);
      v26 = 0;
      *(_QWORD *)&v26 = sub_180093150(64);
      v27 = 57;
      v28 = 63;
      strcpy((char *)v26, "[ERROR] DetourAttach failed for GameManager::CommonUpdate");
      sub_1800291C0(&v26);
      if ( v28 > 0xF )
      {
        v14 = (void *)v26;
        if ( v28 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v26 - *(_QWORD *)(v26 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v14 = *(void **)(v26 - 8);
        }
        sub_1800931A0(v14);
      }
    }
    goto LABEL_24;
  }
  sub_180029000("[ERROR] SetupGameHooks() returned false!");
  return 1;
}
