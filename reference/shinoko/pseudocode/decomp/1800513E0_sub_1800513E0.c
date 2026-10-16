// sub_1800513E0 size=724
void sub_1800513E0()
{
  __int64 v0; // rsi
  char *v1; // r8
  unsigned int v2; // ecx
  unsigned __int8 v3; // al
  unsigned __int64 v4; // rdx
  __int64 v5; // rcx
  int v6; // edx
  unsigned __int64 v7; // xmm0_8
  __m128 v8; // xmm0
  __m128 v9; // xmm2
  int v10; // xmm1_4
  __m128 v11; // xmm6
  __int64 v12; // rdx
  __int64 i; // rdi
  __int64 v14; // rbx
  const char *v15; // r10
  const char *v16; // rax
  int v17; // eax
  bool v18; // zf
  _DWORD v19[4]; // [rsp+20h] [rbp-28h] BYREF
  __int64 v20; // [rsp+50h] [rbp+8h] BYREF

  v0 = qword_18010C470;
  if ( *(float *)(qword_18010C470 + 8616) >= 0.15000001 )
  {
    if ( !*(_QWORD *)(qword_18010C470 + 8608) )
    {
      v1 = "#NavWindowingOverlay";
      v2 = -1;
      v3 = 35;
      do
      {
        if ( v3 == 35 && *v1 == 35 && v1[1] == 35 )
          v2 = -1;
        v4 = v3 ^ (unsigned __int64)(unsigned __int8)v2;
        v3 = *v1++;
        v2 = dword_1800D56B0[v4] ^ (v2 >> 8);
      }
      while ( v3 );
      *(_QWORD *)(v0 + 8608) = sub_18003EA40(~v2, v4, v1, 0xFFFFFFFFLL);
    }
    v5 = **(_QWORD **)(v0 + 8104);
    v6 = *(_DWORD *)(v0 + 7824) | 0x11;
    v7 = _mm_mul_ps((__m128)*(unsigned __int64 *)(v5 + 16), (__m128)xmmword_1800E6940).m128_u64[0];
    *(_DWORD *)(v0 + 7824) |= 0x10u;
    *(_QWORD *)(v0 + 7892) = v7;
    *(_DWORD *)(v0 + 7900) = 2139095039;
    *(_DWORD *)(v0 + 7904) = 2139095039;
    *(_QWORD *)(v0 + 7912) = 0;
    *(_QWORD *)(v0 + 7920) = 0;
    v8 = (__m128)*(unsigned __int64 *)(v5 + 8);
    v9 = (__m128)*(unsigned __int64 *)(v5 + 16);
    *(_DWORD *)(v0 + 7824) = v6;
    *(_DWORD *)(v0 + 7848) = 1056964608;
    *(_DWORD *)(v0 + 7852) = 1056964608;
    *(_DWORD *)(v0 + 7828) = 1;
    v19[0] = 2;
    *(_QWORD *)(v0 + 7840) = _mm_add_ps(_mm_mul_ps(v9, (__m128)xmmword_1800E6960), v8).m128_u64[0];
    v10 = *(_DWORD *)(v0 + 3160);
    v11 = (__m128)*(unsigned __int64 *)(v0 + 3156);
    v19[1] = *(_DWORD *)(v0 + 3156);
    v19[2] = v10;
    sub_180053EB0(v0 + 7968, v19);
    *(_QWORD *)(v0 + 3156) = _mm_add_ps(v11, v11).m128_u64[0];
    sub_180040700("##NavWindowingOverlay", 0, 201543);
    if ( *(_BYTE *)(v0 + 5064) )
      sub_180072500(v0 + 5064);
    for ( i = (unsigned int)(*(_DWORD *)(v0 + 5136) - 1); (int)i >= 0; i = (unsigned int)(i - 1) )
    {
      v14 = *(_QWORD *)(*(_QWORD *)(v0 + 5144) + 8 * i);
      if ( *(_BYTE *)(v14 + 205) && v14 == *(_QWORD *)(v14 + 960) && (*(_DWORD *)(v14 + 20) & 0x20000) == 0 )
      {
        v15 = *(const char **)(v14 + 8);
        v16 = v15;
        if ( v15 == (const char *)-1LL )
          goto LABEL_22;
        do
        {
          if ( !*v16 || *v16 == 35 && v16[1] == 35 )
            break;
          ++v16;
        }
        while ( v16 != (const char *)-1LL );
        if ( v15 == v16 )
        {
LABEL_22:
          v17 = *(_DWORD *)(v14 + 20);
          if ( (v17 & 0x4000000) != 0 )
          {
            v15 = "*Missing Text*";
            if ( *(_QWORD *)(qword_18010C470 + 10048) )
              v15 = *(const char **)(qword_18010C470 + 10048);
          }
          else if ( (v17 & 0x400) == 0 || (unsigned int)sub_1800B9620(*(_QWORD *)(v14 + 8), "##MainMenuBar") )
          {
            v15 = "*Missing Text*";
            v12 = *(_QWORD *)(qword_18010C470 + 10056);
            if ( v12 )
              v15 = *(const char **)(qword_18010C470 + 10056);
          }
          else
          {
            v15 = "*Missing Text*";
            if ( *(_QWORD *)(qword_18010C470 + 10040) )
              v15 = *(const char **)(qword_18010C470 + 10040);
          }
        }
        v18 = *(_QWORD *)(v0 + 8592) == v14;
        v20 = 0;
        LOBYTE(v12) = v18;
        sub_180084D20(v15, v12, 0, &v20);
      }
    }
    sub_180044DF0();
    sub_1800371B0(1);
  }
}
