// sub_18001D760 size=1117
__int64 __fastcall sub_18001D760(__int64 a1, __int64 a2)
{
  unsigned __int64 v3; // rax
  int v4; // r8d
  _BYTE *v5; // rax
  __int128 *v6; // rcx
  __int64 v7; // rdx
  __int128 v8; // xmm0
  __int128 v9; // xmm1
  __int128 v10; // xmm0
  __int128 v11; // xmm1
  __int128 v12; // xmm0
  __int128 v13; // xmm1
  __int128 v14; // xmm0
  __int128 v15; // xmm1
  int v16; // esi
  unsigned __int64 v17; // rax
  __int64 v18; // r10
  unsigned __int64 v19; // rax
  unsigned int v20; // r9d
  char v21; // r11
  unsigned __int64 v22; // rax
  int i; // eax
  int v24; // ecx
  char v25; // dl
  __int64 v26; // rax
  unsigned __int64 v27; // rax
  int v29; // eax
  int v30; // eax
  unsigned __int64 v31; // [rsp+18h] [rbp-280h]
  _BYTE v32[512]; // [rsp+80h] [rbp-218h] BYREF
  int v33; // [rsp+2A0h] [rbp+8h]
  char v34; // [rsp+2A0h] [rbp+8h]
  char v35; // [rsp+2A0h] [rbp+8h]
  int v36; // [rsp+2A0h] [rbp+8h]
  int v37; // [rsp+2A0h] [rbp+8h]

  *(_DWORD *)a2 = 0;
  *(_WORD *)(a2 + 4) = 256;
  v3 = __rdtsc();
  v4 = 0;
  v33 = 0;
  if ( ((unsigned int)v3 | 0xCAFEBABE) - ((unsigned int)v3 & ((unsigned int)v3 ^ 0xCAFEBABE)) == -889275714 )
  {
    v5 = v32;
    v6 = (__int128 *)&unk_1800DBE40;
    v7 = 4;
    do
    {
      v5 += 128;
      v8 = *v6;
      v9 = v6[1];
      v6 += 8;
      *((_OWORD *)v5 - 8) = v8;
      v10 = *(v6 - 6);
      *((_OWORD *)v5 - 7) = v9;
      v11 = *(v6 - 5);
      *((_OWORD *)v5 - 6) = v10;
      v12 = *(v6 - 4);
      *((_OWORD *)v5 - 5) = v11;
      v13 = *(v6 - 3);
      *((_OWORD *)v5 - 4) = v12;
      v14 = *(v6 - 2);
      *((_OWORD *)v5 - 3) = v13;
      v15 = *(v6 - 1);
      *((_OWORD *)v5 - 2) = v14;
      *((_OWORD *)v5 - 1) = v15;
      --v7;
    }
    while ( v7 );
    v16 = 79288853;
    v31 = __rdtsc();
    v34 = __rdtsc();
    v17 = __rdtsc();
    if ( (unsigned __int64)((v34 * v34) & 3) - 2 > 1 && (((_BYTE)v17 * ((_BYTE)v17 - 1)) & 1) == 0 )
    {
      v18 = 0;
      __rdtsc();
      while ( 1 )
      {
        v35 = __rdtsc();
        if ( (unsigned __int64)((v35 * v35) & 3) - 2 <= 1 )
        {
          v31 ^= 0xDEADBEEF;
        }
        else
        {
          v19 = __rdtsc();
          if ( (((_BYTE)v19 * ((_BYTE)v19 - 1)) & 1) == 0 )
          {
            v20 = BYTE2(v16);
            v16 = 1664525 * v16 + 1013904223;
            v21 = _mm_cvtsi128_si32((__m128i)_mm_xor_ps(
                                               (__m128)_mm_cvtsi32_si128(v20),
                                               (__m128)_mm_cvtsi32_si128((unsigned __int8)aI[v18])));
            v22 = __rdtsc();
            v36 = 0;
            if ( ((unsigned int)v22 | 0xCAFEBABE) - ((unsigned int)v22 & ((unsigned int)v22 ^ 0xCAFEBABE)) == -889275714 )
            {
              *(_BYTE *)(v18 + a2) = v32[(unsigned __int8)_mm_cvtsi128_si32(
                                                            _mm_sub_epi8(
                                                              _mm_cvtsi32_si128((unsigned __int8)__ROR1__(v21, v20 & 7)),
                                                              _mm_cvtsi32_si128((unsigned __int8)v18 ^ 0xAAu)))
                                       + 256];
            }
            else
            {
              for ( i = 0; i < 10; ++i )
              {
                v24 = i ^ v36;
                v36 = v24;
              }
            }
          }
        }
        v25 = __rdtsc();
        if ( ((v25 * v25) & 3) == 2 )
          break;
        v26 = v18++;
        if ( v26 - 4 >= 0 )
          goto LABEL_19;
      }
      __rdtsc();
    }
LABEL_19:
    v27 = __rdtsc();
    if ( ((unsigned int)v27 | 0xCAFEBABE) - ((unsigned int)v27 & ((unsigned int)v27 ^ 0xCAFEBABE)) == -889275714 )
    {
      *(_BYTE *)(a2 + 4) = 0;
      return a2;
    }
    else
    {
      v37 = 0;
      do
      {
        v29 = v4++ ^ v37;
        v37 = v29;
      }
      while ( v4 < 10 );
      return a2;
    }
  }
  else
  {
    do
    {
      v30 = v4++ ^ v33;
      v33 = v30;
    }
    while ( v4 < 10 );
    return a2;
  }
}
