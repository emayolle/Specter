// sub_18002C070 size=716
char sub_18002C070()
{
  HMODULE ModuleHandleA; // rax
  const CHAR *v1; // rax
  __int128 *v2; // rcx
  __int64 v3; // rdx
  __int64 v4; // rbx
  HANDLE CurrentThread; // rax
  int v6; // edi
  void *v7; // rcx
  __int128 v9; // [rsp+20h] [rbp-69h] BYREF
  __int64 v10; // [rsp+30h] [rbp-59h]
  unsigned __int64 v11; // [rsp+38h] [rbp-51h]
  char v12; // [rsp+F0h] [rbp+67h] BYREF

  if ( !byte_18010C58D || !qword_18010C5B0 )
  {
    ModuleHandleA = (HMODULE)qword_18010C460;
    if ( !qword_18010C460 )
    {
      v1 = (const CHAR *)sub_18002C340(&v12, &v9);
      ModuleHandleA = GetModuleHandleA(v1);
      if ( BYTE1(v10) )
      {
        v2 = &v9;
        v3 = 17;
        do
        {
          *(_BYTE *)v2 = 0;
          v2 = (__int128 *)((char *)v2 + 1);
          --v3;
        }
        while ( v3 );
      }
      if ( !ModuleHandleA )
        return 0;
      qword_18010C460 = (__int64)ModuleHandleA;
    }
    v4 = (__int64)(ModuleHandleA + 6056448);
    if ( ModuleHandleA != (HMODULE)-24225792LL )
    {
      sub_180029000("[HOOK] Found GameManager::CommonUpdate at 0x%p. Attaching Detour...", ModuleHandleA + 6056448);
      qword_18010C5B0 = v4;
      sub_180091250();
      CurrentThread = GetCurrentThread();
      sub_180091770(CurrentThread);
      v6 = sub_180090800(&qword_18010C5B0, sub_180029AB0);
      if ( !v6 )
        _report_rangecheckfailure();
      sub_180091100();
      qword_18010C5B0 = 0;
      sub_180029000("[ERROR] DetourAttach failed for GameManager::CommonUpdate: %ld", v6);
      v9 = 0;
      *(_QWORD *)&v9 = sub_180093150(64);
      v10 = 57;
      v11 = 63;
      strcpy((char *)v9, "[ERROR] DetourAttach failed for GameManager::CommonUpdate");
      sub_1800291C0(&v9);
      if ( v11 > 0xF )
      {
        v7 = (void *)v9;
        if ( v11 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v9 - *(_QWORD *)(v9 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v7 = *(void **)(v9 - 8);
        }
        sub_1800931A0(v7);
      }
    }
    return 0;
  }
  return 1;
}
