// sub_180052F00 size=697
double sub_180052F00(const char *a1, ...)
{
  __int64 v1; // rdi
  int v2; // r8d
  int *v3; // rbx
  int v4; // r15d
  int v5; // ecx
  bool v6; // zf
  int v7; // r13d
  __int64 v8; // rcx
  _DWORD *v9; // r12
  int v10; // esi
  int v11; // r14d
  int v12; // edx
  unsigned int v13; // ebp
  __int64 v14; // rdx
  __int64 v15; // rbp
  int v16; // esi
  int v17; // eax
  int v18; // ecx
  int v19; // r14d
  const char *v20; // rcx
  char *v21; // r15
  __int64 v22; // rax
  _DWORD *v23; // rbx
  unsigned __int64 v24; // r12
  __int64 i; // rax
  __int64 v26; // rsi
  int v27; // ecx
  int v28; // r8d
  int v29; // eax
  double result; // xmm0_8
  va_list va; // [rsp+98h] [rbp+10h] BYREF

  va_start(va, a1);
  v1 = qword_18010C470;
  v2 = *(_DWORD *)(qword_18010C470 + 5032);
  v3 = (int *)(qword_18010C470 + 10232);
  v4 = (int)a1;
  v5 = *(_DWORD *)(qword_18010C470 + 10232);
  v6 = v5 == 0;
  v7 = v5 - 1;
  v8 = qword_18010C470 + 10232;
  if ( v6 )
    v7 = 0;
  if ( *(_BYTE *)(qword_18010C470 + 5064) )
    sub_180036D40(v8, "[%s] [%05d] ", (const char *)(qword_18010C470 + 5064), v2);
  else
    sub_180036D40(v8, "[%05d] ", v2);
  v9 = (_DWORD *)sub_180002960();
  v10 = sub_18009C09C(*v9 | 1u, 0, 0, v4, 0, (__int64)va);
  if ( v10 < 0 )
    v10 = -1;
  if ( v10 > 0 )
  {
    v11 = 1;
    v12 = *(_DWORD *)(v1 + 10236);
    if ( *v3 )
      v11 = *v3;
    v13 = v11 + v10;
    if ( v11 + v10 >= v12 )
    {
      v14 = (unsigned int)(2 * v12);
      if ( (int)v13 > (int)v14 )
        v14 = v13;
      sub_180054440(v1 + 10232, v14);
    }
    sub_1800542F0(v1 + 10232, v13);
    v15 = v11 + *(_QWORD *)(v1 + 10240);
    v16 = v10 + 1;
    v17 = sub_18009C09C(*v9 | 1u, (int)v15 - 1, v16, v4, 0, (__int64)va);
    if ( v17 < 0 )
      v17 = -1;
    if ( v15 != 1 )
    {
      if ( v17 == -1 || v17 >= v16 )
        v17 = v16 - 1;
      *(_BYTE *)(v17 + v15 - 1) = 0;
    }
  }
  v18 = *(_DWORD *)(v1 + 10232);
  v19 = v18 - 1;
  if ( !v18 )
    v19 = 0;
  v20 = (const char *)&unk_18010C451;
  v21 = (char *)&unk_18010C451;
  if ( *(_QWORD *)(v1 + 10240) )
    v21 = *(char **)(v1 + 10240);
  if ( v7 != v19 )
  {
    v22 = *(int *)(v1 + 10264);
    v23 = (_DWORD *)(v1 + 10248);
    if ( !(_DWORD)v22 || v21[v22 - 1] == 10 )
      sub_1800541A0(v1 + 10248, v1 + 10264);
    v24 = (unsigned __int64)&v21[v19];
    for ( i = sub_1800B8A30(&v21[v7], 10, v19 - (__int64)v7); i; i = sub_1800B8A30(v26, 10, v24 - v26) )
    {
      v26 = i + 1;
      if ( i + 1 < v24 )
      {
        v27 = *(_DWORD *)(v1 + 10252);
        if ( *v23 == v27 )
        {
          v28 = *v23 + 1;
          if ( v27 )
            v29 = v27 + v27 / 2;
          else
            v29 = 8;
          if ( v29 > v28 )
            v28 = v29;
          sub_180054C90(v1 + 10248, (unsigned int)v28);
        }
        *(_DWORD *)(*(_QWORD *)(v1 + 10256) + 4LL * (int)(*v23)++) = v26 - (_DWORD)v21;
      }
    }
    v20 = (const char *)&unk_18010C451;
    if ( *(_DWORD *)(v1 + 10264) >= v19 )
      v19 = *(_DWORD *)(v1 + 10264);
    *(_DWORD *)(v1 + 10264) = v19;
  }
  if ( (*(_DWORD *)(v1 + 10228) & 0x100000) != 0 )
  {
    if ( *(_QWORD *)(v1 + 10240) )
      v20 = *(const char **)(v1 + 10240);
    return sub_180028FB0("%s", &v20[v7]);
  }
  return result;
}
