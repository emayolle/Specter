// sub_18006DA50 size=646
char __fastcall sub_18006DA50(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  double v4; // xmm2_8
  int v7; // eax
  _BYTE *i; // rsi
  __int64 v9; // r14
  _BYTE *j; // rbx
  __m128i v11; // xmm0
  int v12; // xmm0_4
  int v14; // [rsp+30h] [rbp-10h] BYREF
  unsigned int v15; // [rsp+34h] [rbp-Ch] BYREF
  int v16; // [rsp+38h] [rbp-8h]
  int v17; // [rsp+3Ch] [rbp-4h] BYREF
  char v18; // [rsp+70h] [rbp+30h] BYREF

  v16 = 0;
  v17 = 0;
  v14 = 0;
  v15 = 0;
  v7 = sub_180034BF0(a4, "RefScale=%f", v4);
  if ( v7 == 1 )
  {
    *(_DWORD *)(a3 + 8) = v16;
  }
  else
  {
    v7 = sub_180034BF0(a4, "Column %d%n", (unsigned int)&v17, &v14);
    if ( v7 == 1 && v17 >= 0 )
    {
      v7 = *(__int16 *)(a3 + 12);
      if ( v17 < v7 )
      {
        for ( i = (_BYTE *)(a4 + v14); *i == 32 || *i == 9; ++i )
          ;
        v18 = 0;
        v9 = 16LL * v17;
        *(_WORD *)(v9 + a3 + 28) = v17;
        if ( (unsigned int)sub_180034BF0(i, "UserID=0x%08X%n", (unsigned int)&v15, &v14) == 1 )
        {
          for ( j = &i[v14]; *j == 32 || *j == 9; ++j )
            ;
          *(_DWORD *)(v9 + a3 + 24) = v15;
        }
        else
        {
          j = i;
        }
        if ( (unsigned int)sub_180034BF0(j, "Width=%d%n", (unsigned int)&v15, &v14) == 1 )
        {
          for ( j += v14; *j == 32 || *j == 9; ++j )
            ;
          v11 = _mm_cvtsi32_si128(v15);
          *(_BYTE *)(v9 + a3 + 34) &= ~0x10u;
          *(_DWORD *)(v9 + a3 + 20) = _mm_cvtepi32_ps(v11).m128_u32[0];
          *(_DWORD *)(a3 + 4) |= 1u;
        }
        if ( (unsigned int)sub_180034BF0(j, "Weight=%f%n", v4, &v14) == 1 )
        {
          for ( j += v14; *j == 32 || *j == 9; ++j )
            ;
          v12 = v16;
          *(_BYTE *)(v9 + a3 + 34) |= 0x10u;
          *(_DWORD *)(v9 + a3 + 20) = v12;
          *(_DWORD *)(a3 + 4) |= 1u;
        }
        if ( (unsigned int)sub_180034BF0(j, "Visible=%d%n", (unsigned int)&v15, &v14) == 1 )
        {
          for ( j += v14; *j == 32 || *j == 9; ++j )
            ;
          *(_BYTE *)(v9 + a3 + 34) = *(_BYTE *)(v9 + a3 + 34) & 0xF3 | (4 * (v15 & 3));
          *(_DWORD *)(a3 + 4) |= 4u;
        }
        if ( (unsigned int)sub_180034BF0(j, "Order=%d%n", (unsigned int)&v15, &v14) == 1 )
        {
          for ( j += v14; *j == 32 || *j == 9; ++j )
            ;
          *(_WORD *)(v9 + a3 + 30) = v15;
          *(_DWORD *)(a3 + 4) |= 2u;
        }
        v7 = sub_180034BF0(j, "Sort=%d%c%n", (unsigned int)&v15, &v18, &v14);
        if ( v7 == 2 )
        {
          *(_WORD *)(v9 + a3 + 32) = v15;
          LOBYTE(v7) = *(_BYTE *)(v9 + a3 + 34) & 0xFC;
          *(_BYTE *)(v9 + a3 + 34) = v7 | ((v18 == 94) + 1);
          *(_DWORD *)(a3 + 4) |= 8u;
        }
      }
    }
  }
  return v7;
}
