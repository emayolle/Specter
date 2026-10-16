// sub_18002A1C0 size=1112
char sub_18002A1C0()
{
  const CHAR *v0; // rax
  HMODULE ModuleHandleA; // rax
  HMODULE v2; // rdi
  _BYTE *v3; // rcx
  __int64 v4; // rdx
  const CHAR *v5; // rax
  FARPROC ProcAddress; // rax
  FARPROC v7; // rsi
  _BYTE *v8; // rcx
  __int64 v9; // rdx
  const CHAR *v10; // rax
  __int64 v11; // rbx
  __int128 *v12; // rax
  __int64 v13; // rcx
  const CHAR *v14; // rax
  __int128 *v15; // rax
  const CHAR *v16; // rax
  __int128 *v17; // rax
  __int64 v18; // rcx
  const CHAR *v19; // rax
  __int128 *v20; // rax
  __int64 v21; // rcx
  HANDLE CurrentThread; // rax
  int v23; // ebx
  void *v24; // rcx
  __int128 v26; // [rsp+20h] [rbp-99h] BYREF
  __int64 v27; // [rsp+30h] [rbp-89h]
  unsigned __int64 v28; // [rsp+38h] [rbp-81h]
  _BYTE v29[16]; // [rsp+40h] [rbp-79h] BYREF
  _BYTE v30[32]; // [rsp+50h] [rbp-69h] BYREF
  char v31; // [rsp+120h] [rbp+67h] BYREF
  char v32; // [rsp+128h] [rbp+6Fh] BYREF
  char v33; // [rsp+130h] [rbp+77h] BYREF

  if ( byte_18010C50F && qword_18010C5A8 )
    return 1;
  v0 = (const CHAR *)sub_18002A620(&v31, v29);
  ModuleHandleA = GetModuleHandleA(v0);
  v2 = ModuleHandleA;
  if ( v29[9] )
  {
    v3 = v29;
    v4 = 9;
    do
    {
      *v3++ = 0;
      --v4;
    }
    while ( v4 );
  }
  if ( ModuleHandleA )
  {
    v5 = (const CHAR *)sub_18002AA80(&v32, v30);
    ProcAddress = GetProcAddress(v2, v5);
    v7 = ProcAddress;
    if ( v30[17] )
    {
      v8 = v30;
      v9 = 17;
      do
      {
        *v8++ = 0;
        --v9;
      }
      while ( v9 );
    }
    if ( ProcAddress )
    {
      v10 = (const CHAR *)sub_18002AEE0(&v33, &v26);
      GetProcAddress(v2, v10);
      v11 = 11;
      if ( BYTE11(v26) )
      {
        v12 = &v26;
        v13 = 11;
        do
        {
          *(_BYTE *)v12 = 0;
          v12 = (__int128 *)((char *)v12 + 1);
          --v13;
        }
        while ( v13 );
      }
      v14 = (const CHAR *)sub_18002B340(&v33, &v26);
      qword_18010C5C8 = (__int64 (__fastcall *)(_QWORD, _QWORD))GetProcAddress(v2, v14);
      if ( BYTE11(v26) )
      {
        v15 = &v26;
        do
        {
          *(_BYTE *)v15 = 0;
          v15 = (__int128 *)((char *)v15 + 1);
          --v11;
        }
        while ( v11 );
      }
      v16 = (const CHAR *)sub_18002B7A0(&v33, &v26);
      qword_18010C5C0 = (__int64 (__fastcall *)(_QWORD, _QWORD, _QWORD, _QWORD))GetProcAddress(v2, v16);
      if ( BYTE10(v26) )
      {
        v17 = &v26;
        v18 = 10;
        do
        {
          *(_BYTE *)v17 = 0;
          v17 = (__int128 *)((char *)v17 + 1);
          --v18;
        }
        while ( v18 );
      }
      v19 = (const CHAR *)sub_18002BC00(&v33, &v26);
      qword_18010C5D0 = (__int64 (__fastcall *)(_QWORD, _QWORD, _QWORD))GetProcAddress(v2, v19);
      if ( BYTE14(v26) )
      {
        v20 = &v26;
        v21 = 14;
        do
        {
          *(_BYTE *)v20 = 0;
          v20 = (__int128 *)((char *)v20 + 1);
          --v21;
        }
        while ( v21 );
      }
      sub_180029000("[HOOK] Found xlua.dll!xluaL_loadbuffer at 0x%p. Attaching Detour...", v7);
      qword_18010C5A8 = (__int64 (__fastcall *)(_QWORD, _QWORD, _QWORD, _QWORD))v7;
      sub_180091250();
      CurrentThread = GetCurrentThread();
      sub_180091770(CurrentThread);
      v23 = sub_180090800(&qword_18010C5A8, sub_180029960);
      if ( !v23 )
        _report_rangecheckfailure();
      sub_180091100();
      qword_18010C5A8 = nullptr;
      sub_180029000("[ERROR] DetourAttach failed for xluaL_loadbuffer: %ld", v23);
      v26 = 0;
      *(_QWORD *)&v26 = sub_180093150(64);
      v27 = 48;
      v28 = 63;
      strcpy((char *)v26, "[ERROR] DetourAttach failed for xluaL_loadbuffer");
      sub_1800291C0(&v26);
    }
    else
    {
      sub_180029000("[ERROR] GetProcAddress(xluaL_loadbuffer) returned null");
      v26 = 0;
      *(_QWORD *)&v26 = sub_180093150(48);
      v27 = 47;
      v28 = 47;
      strcpy((char *)v26, "[ERROR] GetProcAddress(xluaL_loadbuffer) failed");
      sub_1800291C0(&v26);
    }
    if ( v28 > 0xF )
    {
      v24 = (void *)v26;
      if ( v28 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v26 - *(_QWORD *)(v26 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v24 = *(void **)(v26 - 8);
      }
      sub_1800931A0(v24);
    }
  }
  return 0;
}
