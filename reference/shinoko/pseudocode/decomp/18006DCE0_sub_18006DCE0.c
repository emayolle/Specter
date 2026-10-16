// sub_18006DCE0 size=959
__int64 __fastcall sub_18006DCE0(__int64 a1, const char **a2, int *a3)
{
  __int64 result; // rax
  __int64 v4; // r13
  const char **v5; // r12
  __int64 v7; // rdx
  int v8; // ebp
  unsigned __int8 v9; // r14
  int v10; // r15d
  int v11; // ebp
  int v12; // esi
  int v13; // esi
  __int64 v14; // rax
  __int64 v15; // rdx
  __int64 v16; // rdi
  float v17; // xmm0_4
  int v18; // r12d
  __int64 v19; // rdi
  int v20; // esi
  int v21; // r8d
  __int64 v22; // r9
  int v23; // r15d
  int v24; // eax
  int v25; // ebp
  int v26; // esi
  __int64 v27; // rax
  __int64 v28; // rdx
  __int64 v29; // r14
  __int64 v30; // rcx
  int v31; // ebp
  int v32; // eax
  int v33; // esi
  int v34; // edi
  __int64 v35; // rax
  __int64 v36; // rdx
  __int64 v37; // r14
  __int64 v38; // r8
  bool v39; // zf
  int v40; // [rsp+30h] [rbp-58h]
  int v41; // [rsp+34h] [rbp-54h]
  int v42; // [rsp+38h] [rbp-50h]
  unsigned __int8 v45; // [rsp+A8h] [rbp+20h]

  result = *(_QWORD *)(a1 + 9968);
  v4 = 0;
  v5 = a2;
  v7 = a1;
  if ( result )
    v4 = result + 4;
  while ( v4 )
  {
    if ( *(_DWORD *)v4 )
    {
      v8 = *(_DWORD *)(v4 + 4);
      v9 = v8 & 1;
      v45 = v8 & 1;
      v10 = v8 & 4;
      v40 = v8 & 2;
      v11 = v8 & 8;
      v42 = *(_DWORD *)(v4 + 4) & 4;
      v41 = v11;
      v12 = 50 * *(__int16 *)(v4 + 12) + *a3 - 1;
      if ( !*a3 )
        v12 = 50 * *(__int16 *)(v4 + 12);
      v13 = v12 + 30;
      if ( v13 > a3[1] )
      {
        v14 = sub_18003A810(v13);
        v15 = *((_QWORD *)a3 + 1);
        v16 = v14;
        if ( v15 )
        {
          sub_1800B8BD0(v14, v15, *a3);
          sub_18003A8D0(*((LPVOID *)a3 + 1));
        }
        *((_QWORD *)a3 + 1) = v16;
        a3[1] = v13;
      }
      sub_180036D40(a3, "[%s][0x%08X,%d]\n", *v5, *(_DWORD *)v4, *(__int16 *)(v4 + 12));
      v17 = *(float *)(v4 + 8);
      if ( v17 != 0.0 )
        sub_180036D40(a3, "RefScale=%g\n", v17);
      v18 = 0;
      v19 = v4 + 20;
      if ( *(__int16 *)(v4 + 12) > 0 )
      {
        v20 = v40;
        do
        {
          if ( v20 | v10 | *(_DWORD *)(v19 + 4) | v9 || v11 && *(_WORD *)(v19 + 12) != 0xFFFF )
          {
            sub_180036D40(a3, "Column %-2d", v18);
            v21 = *(_DWORD *)(v19 + 4);
            if ( v21 )
              sub_180036D40(a3, " UserID=%08X", v21);
            if ( v9 )
            {
              if ( (*(_BYTE *)(v19 + 14) & 0x10) == 0
                || (sub_180036D40(a3, " Weight=%.4f", *(float *)v19), (*(_BYTE *)(v19 + 14) & 0x10) == 0) )
              {
                sub_180036D40(a3, " Width=%d", (int)*(float *)v19);
              }
            }
            if ( v10 )
              sub_180036D40(a3, " Visible=%d", (char)(16 * *(_BYTE *)(v19 + 14)) >> 6);
            if ( v20 )
              sub_180036D40(a3, " Order=%d", *(__int16 *)(v19 + 10));
            if ( v11 && *(_WORD *)(v19 + 12) != 0xFFFF )
            {
              v22 = 94;
              if ( (*(_BYTE *)(v19 + 14) & 3) == 1 )
                v22 = 118;
              sub_180036D40(a3, " Sort=%d%c", (unsigned int)*(__int16 *)(v19 + 12), v22);
            }
            v23 = 1;
            if ( *a3 )
              v23 = *a3;
            v24 = a3[1];
            v25 = v23 + 1;
            if ( v23 + 1 >= v24 )
            {
              v26 = 2 * v24;
              if ( v25 > 2 * v24 )
                v26 = v23 + 1;
              if ( v26 > v24 )
              {
                v27 = sub_18003A810(v26);
                v28 = *((_QWORD *)a3 + 1);
                v29 = v27;
                if ( v28 )
                {
                  sub_1800B8BD0(v27, v28, *a3);
                  sub_18003A8D0(*((LPVOID *)a3 + 1));
                }
                *((_QWORD *)a3 + 1) = v29;
                v9 = v45;
                a3[1] = v26;
              }
              v20 = v40;
            }
            sub_1800542F0(a3, (unsigned int)v25);
            v11 = v41;
            v30 = v23;
            v10 = v42;
            *(_BYTE *)(*((_QWORD *)a3 + 1) + v30 - 1) = 10;
            *(_BYTE *)(v30 + *((_QWORD *)a3 + 1)) = 0;
          }
          ++v18;
          v19 += 16;
        }
        while ( v18 < *(__int16 *)(v4 + 12) );
      }
      v31 = 1;
      if ( *a3 )
        v31 = *a3;
      v32 = a3[1];
      v33 = v31 + 1;
      if ( v31 + 1 >= v32 )
      {
        v34 = 2 * v32;
        if ( v33 > 2 * v32 )
          v34 = v31 + 1;
        if ( v34 > v32 )
        {
          v35 = sub_18003A810(v34);
          v36 = *((_QWORD *)a3 + 1);
          v37 = v35;
          if ( v36 )
          {
            sub_1800B8BD0(v35, v36, *a3);
            sub_18003A8D0(*((LPVOID *)a3 + 1));
          }
          *((_QWORD *)a3 + 1) = v37;
          a3[1] = v34;
        }
      }
      sub_1800542F0(a3, (unsigned int)v33);
      v7 = a1;
      v5 = a2;
      *(_BYTE *)(*((_QWORD *)a3 + 1) + v31 - 1LL) = 10;
      result = *((_QWORD *)a3 + 1);
      *(_BYTE *)(v31 + result) = 0;
    }
    v38 = v4 + *(int *)(v4 - 4);
    v4 = 0;
    v39 = v38 == *(int *)(v7 + 9960) + *(_QWORD *)(v7 + 9968) + 4LL;
    v7 = a1;
    if ( !v39 )
      v4 = v38;
  }
  return result;
}
