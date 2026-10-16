// sub_18003A270 size=698
bool __fastcall sub_18003A270(unsigned int a1)
{
  __int64 v1; // r10
  unsigned int v2; // edi
  __int64 v3; // rbx
  __int64 v4; // rsi
  int v5; // eax
  unsigned int v6; // eax
  __int64 v7; // r8
  unsigned int v8; // eax
  __int64 v9; // r9
  int v10; // eax
  int v11; // r9d
  int v12; // eax
  float v13; // xmm3_4
  int v14; // edx
  unsigned __int64 *v15; // r8
  int v16; // edx
  unsigned int v17; // edx
  __int64 v18; // rax
  unsigned __int64 v20; // [rsp+20h] [rbp-18h] BYREF
  char v21; // [rsp+28h] [rbp-10h] BYREF

  v1 = qword_18010C470;
  v2 = a1;
  v3 = qword_18010C470;
  v4 = *(_QWORD *)(qword_18010C470 + 5216);
  if ( (a1 & 0xFFFC005F) != 0 )
  {
    sub_180049A30("Invalid flags for IsItemHovered()!");
    v1 = qword_18010C470;
  }
  if ( *(_BYTE *)(v3 + 8113) && *(_BYTE *)(v3 + 8112) && (v2 & 0x800) == 0 )
  {
    v5 = *(_DWORD *)(v1 + 8116);
    if ( v5 == *(_DWORD *)(v1 + 7744) && v5 && ((*(_DWORD *)(v3 + 7748) & 0x400) == 0 || (v2 & 0x400) != 0) )
    {
      if ( (v2 & 0x1000) != 0 )
      {
        v6 = *(_DWORD *)(v3 + 4384) & 0xFFFE3FFF;
        if ( (v2 & 0x1C000) == 0 )
          v6 = *(_DWORD *)(v3 + 4384);
        v2 |= v6;
      }
      goto LABEL_38;
    }
  }
  else
  {
    v7 = *(unsigned int *)(v3 + 7752);
    if ( (v7 & 1) != 0 )
    {
      if ( (v2 & 0x1000) != 0 )
      {
        v8 = *(_DWORD *)(v3 + 4380) & 0xFFFE3FFF;
        if ( (v2 & 0x1C000) == 0 )
          v8 = *(_DWORD *)(v3 + 4380);
        v2 |= v8;
      }
      if ( *(_QWORD *)(v3 + 5224) == v4 || (v7 = v2 & 0x200 | *(_DWORD *)(v3 + 7752) & 0x80, (_DWORD)v7) )
      {
        v9 = *(unsigned int *)(v3 + 7744);
        if ( ((v2 & 0x80u) != 0
           || (v10 = *(_DWORD *)(v3 + 5332)) == 0
           || v10 == (_DWORD)v9
           || *(_BYTE *)(v3 + 5345)
           || v10 == *(_DWORD *)(v4 + 140) && (!(_DWORD)v9 || *(_DWORD *)(v3 + 5352) == (_DWORD)v9))
          && ((unsigned __int8)sub_18003A200(v4, v2, v7, v9) || (*(_DWORD *)(v3 + 7748) & 0x2000) != 0) )
        {
          v12 = *(_DWORD *)(v3 + 7748);
          if ( ((v12 & 0x400) == 0 || (v2 & 0x400) != 0)
            && (v11 != *(_DWORD *)(v4 + 140) || !*(_BYTE *)(v4 + 206))
            && ((v12 & 0x4000) == 0 || !v11 || (v2 & 0x100) != 0 || *(_DWORD *)(v3 + 5312) == v11) )
          {
LABEL_38:
            if ( (v2 & 0x10000) != 0 )
            {
              v13 = *(float *)(v1 + 4376);
            }
            else
            {
              if ( (v2 & 0x8000) == 0 )
              {
                v13 = 0.0;
                goto LABEL_45;
              }
              v13 = *(float *)(v1 + 4372);
            }
            if ( v13 > 0.0 )
            {
LABEL_46:
              v14 = *(_DWORD *)(v3 + 7744);
              if ( !v14 )
              {
                v15 = &v20;
                v16 = *(_DWORD *)(*(_QWORD *)(v4 + 272) + 4LL * *(int *)(v4 + 264) - 4);
                v20 = _mm_sub_ps((__m128)*(unsigned __int64 *)(v3 + 7756), (__m128)*(unsigned __int64 *)(v4 + 296)).m128_u64[0];
                v17 = ~v16;
                do
                {
                  v18 = *(unsigned __int8 *)v15;
                  v15 = (unsigned __int64 *)((char *)v15 + 1);
                  v17 = dword_1800D56B0[v18 ^ (unsigned __int8)v17] ^ (v17 >> 8);
                }
                while ( v15 < (unsigned __int64 *)&v21 );
                v14 = ~v17;
              }
              if ( (v2 & 0x20000) != 0 && *(_DWORD *)(v3 + 9220) != v14 )
                *(_DWORD *)(v3 + 9224) = 0;
              *(_DWORD *)(v3 + 9216) = v14;
              if ( (v2 & 0x2000) == 0 || *(_DWORD *)(v3 + 9232) == v14 )
                return v13 <= *(float *)(v3 + 9224);
              return 0;
            }
LABEL_45:
            if ( (v2 & 0x2000) == 0 )
              return 1;
            goto LABEL_46;
          }
        }
      }
    }
  }
  return 0;
}
