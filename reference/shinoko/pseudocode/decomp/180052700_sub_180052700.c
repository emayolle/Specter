// sub_180052700 size=1014
__int64 __fastcall sub_180052700(__int64 a1, const char **a2, int *a3)
{
  __int64 *v3; // r9
  int *v4; // r14
  const char **v5; // rsi
  __int64 v6; // r15
  __int64 v7; // rax
  __int64 *v8; // r10
  __int64 v9; // r13
  __int64 v10; // rbp
  __int64 v11; // rax
  __int64 v12; // rbx
  __int64 v13; // rax
  __int64 v14; // rcx
  char *v15; // rsi
  char v16; // cl
  char *i; // rax
  __int64 v18; // r15
  __int64 v19; // rbx
  int v20; // edi
  __int64 v21; // r12
  __int64 v22; // rdi
  int v23; // eax
  int v24; // ecx
  int v25; // ebx
  __int64 v26; // rax
  __int64 v27; // rdx
  __int64 v28; // rdi
  __int64 result; // rax
  __int64 v30; // rbx
  int v31; // ebp
  int v32; // eax
  int v33; // esi
  int v34; // edi
  __int64 v35; // rax
  __int64 v36; // rdx
  __int64 v37; // r15
  __int64 v38; // r8
  __int64 *v39; // [rsp+20h] [rbp-58h]
  __int64 *v40; // [rsp+28h] [rbp-50h]

  v3 = *(__int64 **)(a1 + 5128);
  v4 = a3;
  v5 = a2;
  v6 = a1;
  v39 = v3;
  v7 = *(int *)(a1 + 5120);
  v8 = &v3[v7];
  v40 = &v3[v7];
  if ( v7 * 8 )
  {
    v9 = qword_18010C470;
    do
    {
      v10 = *v3;
      if ( (*(_DWORD *)(*v3 + 20) & 0x100) == 0 )
      {
        v11 = *(int *)(v10 + 708);
        if ( (_DWORD)v11 == -1 )
        {
          v13 = *(_QWORD *)(v9 + 9952);
          v12 = 0;
          if ( v13 )
            v12 = v13 + 4;
          if ( v12 )
          {
            while ( *(_DWORD *)v12 != *(_DWORD *)(v10 + 16) || *(_BYTE *)(v12 + 15) )
            {
              v14 = v12 + *(int *)(v12 - 4);
              v12 = 0;
              if ( v14 != v13 + 4 + *(int *)(v9 + 9944) )
                v12 = v14;
              if ( !v12 )
                goto LABEL_14;
            }
          }
          else
          {
LABEL_14:
            v12 = 0;
          }
        }
        else
        {
          v12 = *(_QWORD *)(v9 + 9952) + v11;
        }
        if ( !v12 )
        {
          v15 = *(char **)(v10 + 8);
          if ( !*(_BYTE *)(v9 + 134) )
          {
            v16 = *v15;
            for ( i = v15 + 1; v16; ++i )
            {
              while ( v16 == 35 && *i == 35 && i[1] == 35 )
              {
                v16 = *i;
                v15 = i++ - 1;
              }
              v16 = *i;
            }
          }
          v18 = sub_1800B9730(v15);
          v19 = *(int *)(v9 + 9944);
          v20 = (v18 + 24) & 0xFFFFFFFC;
          sub_1800542F0(v9 + 9944, (unsigned int)(v20 + v19));
          v21 = v19;
          *(_DWORD *)(v19 + *(_QWORD *)(v9 + 9952)) = v20;
          v22 = *(_QWORD *)(v9 + 9952);
          v12 = v22 + v19 + 4;
          if ( v12 )
            *(_OWORD *)v12 = 0;
          *(_DWORD *)v12 = sub_1800360F0(v15, v18, 0);
          sub_1800B8BD0(v22 + v21 + 20, v15, v18 + 1);
          v6 = a1;
          v9 = qword_18010C470;
          v3 = v39;
          v8 = v40;
          *(_DWORD *)(v10 + 708) = v12 - *(_DWORD *)(a1 + 9952);
        }
        v23 = (int)*(float *)(v10 + 40);
        *(_WORD *)(v12 + 6) = (int)*(float *)(v10 + 44);
        *(_WORD *)(v12 + 4) = v23;
        v24 = (int)*(float *)(v10 + 60);
        *(_WORD *)(v12 + 8) = (int)*(float *)(v10 + 56);
        *(_WORD *)(v12 + 10) = v24;
        *(_BYTE *)(v12 + 13) = HIBYTE(*(_DWORD *)(v10 + 20)) & 1;
        *(_BYTE *)(v12 + 12) = *(_BYTE *)(v10 + 207);
        *(_BYTE *)(v12 + 15) = 0;
      }
      v39 = ++v3;
    }
    while ( v3 != v8 );
    v4 = a3;
    v5 = a2;
  }
  v25 = *v4 + 6 * *(_DWORD *)(v6 + 9944) - 1;
  if ( !*v4 )
    v25 = 6 * *(_DWORD *)(v6 + 9944);
  if ( v25 > v4[1] )
  {
    v26 = sub_18003A810(v25);
    v27 = *((_QWORD *)v4 + 1);
    v28 = v26;
    if ( v27 )
    {
      sub_1800B8BD0(v26, v27, *v4);
      sub_18003A8D0(*((LPVOID *)v4 + 1));
    }
    *((_QWORD *)v4 + 1) = v28;
    v4[1] = v25;
  }
  result = *(_QWORD *)(v6 + 9952);
  v30 = 0;
  if ( result )
    v30 = result + 4;
  while ( v30 )
  {
    if ( !*(_BYTE *)(v30 + 15) )
    {
      sub_180036D40(v4, "[%s][%s]\n", *v5, (const char *)(v30 + 16));
      if ( *(_BYTE *)(v30 + 13) )
      {
        sub_180036D40(v4, "IsChild=1\n");
        sub_180036D40(v4, "Size=%d,%d\n", *(__int16 *)(v30 + 8), *(__int16 *)(v30 + 10));
      }
      else
      {
        sub_180036D40(v4, "Pos=%d,%d\n", *(__int16 *)(v30 + 4), *(__int16 *)(v30 + 6));
        sub_180036D40(v4, "Size=%d,%d\n", *(__int16 *)(v30 + 8), *(__int16 *)(v30 + 10));
        if ( *(_BYTE *)(v30 + 12) )
          sub_180036D40(v4, "Collapsed=1\n");
      }
      v31 = 1;
      if ( *v4 )
        v31 = *v4;
      v32 = v4[1];
      v33 = v31 + 1;
      if ( v31 + 1 >= v32 )
      {
        v34 = 2 * v32;
        if ( v33 > 2 * v32 )
          v34 = v31 + 1;
        if ( v34 > v32 )
        {
          v35 = sub_18003A810(v34);
          v36 = *((_QWORD *)v4 + 1);
          v37 = v35;
          if ( v36 )
          {
            sub_1800B8BD0(v35, v36, *v4);
            sub_18003A8D0(*((LPVOID *)v4 + 1));
          }
          *((_QWORD *)v4 + 1) = v37;
          v6 = a1;
          v4[1] = v34;
        }
      }
      sub_1800542F0(v4, (unsigned int)v33);
      *(_BYTE *)(*((_QWORD *)v4 + 1) + v31 - 1LL) = 10;
      result = *((_QWORD *)v4 + 1);
      *(_BYTE *)(v31 + result) = 0;
    }
    v38 = v30 + *(int *)(v30 - 4);
    v5 = a2;
    v30 = 0;
    if ( v38 != *(int *)(v6 + 9944) + *(_QWORD *)(v6 + 9952) + 4LL )
      v30 = v38;
  }
  return result;
}
