// sub_18008DA80 size=431
char __fastcall sub_18008DA80(__int64 a1)
{
  __int64 v1; // rbx
  __int64 v3; // rdi
  __int64 v4; // rbx
  HKL KeyboardLayout; // rax
  __int64 v6; // rbx
  __int64 v7; // rax
  __int64 v8; // rdx
  HMODULE LibraryA; // rax
  HMODULE v10; // rsi
  LPCSTR lpLibFileName[5]; // [rsp+28h] [rbp-40h]
  LARGE_INTEGER Frequency; // [rsp+80h] [rbp+18h] BYREF
  LARGE_INTEGER PerformanceCount; // [rsp+88h] [rbp+20h] BYREF

  v1 = qword_18010C470;
  if ( !QueryPerformanceFrequency(&Frequency) || !QueryPerformanceCounter(&PerformanceCount) )
    return 0;
  v3 = sub_18003A810(88);
  if ( v3 )
  {
    *(_OWORD *)v3 = 0;
    *(_OWORD *)(v3 + 16) = 0;
    *(_OWORD *)(v3 + 32) = 0;
    *(_OWORD *)(v3 + 48) = 0;
    *(_OWORD *)(v3 + 64) = 0;
    *(_QWORD *)(v3 + 80) = 0;
  }
  else
  {
    v3 = 0;
  }
  *(_DWORD *)(v1 + 12) |= 6u;
  *(_QWORD *)(v1 + 136) = "imgui_impl_win32";
  *(_QWORD *)(v1 + 152) = v3;
  *(_QWORD *)v3 = a1;
  *(LARGE_INTEGER *)(v3 + 32) = Frequency;
  *(LARGE_INTEGER *)(v3 + 24) = PerformanceCount;
  *(_DWORD *)(v3 + 40) = 11;
  v4 = *(_QWORD *)(v1 + 152);
  KeyboardLayout = GetKeyboardLayout(0);
  if ( !GetLocaleInfoA(WORD1(KeyboardLayout), 0x20001004u, (LPSTR)(v4 + 44), 4) )
    *(_DWORD *)(v4 + 44) = 0;
  v6 = 0;
  v7 = *(_QWORD *)v3;
  v8 = **(_QWORD **)(qword_18010C470 + 8104);
  *(_QWORD *)(v8 + 56) = *(_QWORD *)v3;
  *(_QWORD *)(v8 + 48) = v7;
  lpLibFileName[0] = "xinput1_4.dll";
  lpLibFileName[1] = "xinput1_3.dll";
  lpLibFileName[2] = "xinput9_1_0.dll";
  lpLibFileName[3] = "xinput1_2.dll";
  lpLibFileName[4] = "xinput1_1.dll";
  *(_BYTE *)(v3 + 49) = 1;
  while ( 1 )
  {
    LibraryA = LoadLibraryA(lpLibFileName[v6]);
    v10 = LibraryA;
    if ( LibraryA )
      break;
    v6 = (unsigned int)(v6 + 1);
    if ( (int)v6 >= 5 )
      return 1;
  }
  *(_QWORD *)(v3 + 56) = LibraryA;
  *(_QWORD *)(v3 + 64) = GetProcAddress(LibraryA, "XInputGetCapabilities");
  *(_QWORD *)(v3 + 72) = GetProcAddress(v10, "XInputGetState");
  return 1;
}
