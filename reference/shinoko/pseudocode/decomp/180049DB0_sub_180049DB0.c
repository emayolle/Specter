// sub_180049DB0 size=699
_BOOL8 sub_180049DB0()
{
  __int64 v0; // rdi
  char *v1; // r8
  unsigned int v2; // ecx
  unsigned __int8 v3; // al
  unsigned __int64 v4; // rdx
  __int64 v5; // rax
  bool v6; // bl
  __m128 v7; // xmm1
  __int64 v8; // rax
  __int64 v9; // xmm0_8
  bool v10; // bp
  __int64 v11; // rbx
  __int64 v12; // rsi
  __int64 v13; // rdx
  __int64 v14; // r10
  __int64 v15; // rcx
  __int64 v16; // rcx
  __int64 v17; // r9
  __int64 v18; // r11
  __int64 v19; // r10
  int v20; // r8d
  int i; // r9d
  __int64 v22; // rdx
  __int64 v23; // rcx
  __int64 v24; // rax
  int v25; // xmm0_4
  float v27; // [rsp+20h] [rbp-18h] BYREF
  unsigned __int64 v28; // [rsp+24h] [rbp-14h]
  float v29; // [rsp+2Ch] [rbp-Ch]

  v0 = qword_18010C470;
  v1 = "#Tooltip_Error";
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
  v5 = sub_18003EA40(~v2, v4, v1, 0xFFFFFFFFLL);
  v6 = *(_BYTE *)(v0 + 252) && v5 && *(_BYTE *)(v5 + 205);
  v7 = (__m128)*(unsigned __int64 *)(v0 + 3492);
  v27 = (float)((float)(1.0 - *(float *)(v0 + 3488)) * 0.15000001) + *(float *)(v0 + 3488);
  v28 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps((__m128)0LL, v7), (__m128)xmmword_1800E6930), v7).m128_u64[0];
  v29 = (float)((float)(1.0 - *(float *)(v0 + 3500)) * 0.15000001) + *(float *)(v0 + 3500);
  sub_180036E50(4, &v27);
  if ( v6 )
  {
    v8 = qword_18010C470;
    *(_DWORD *)(qword_18010C470 + 7824) |= 1u;
    v9 = *(_QWORD *)(v0 + 10176);
    *(_QWORD *)(v8 + 7848) = 0;
    *(_QWORD *)(v8 + 7840) = v9;
    *(_DWORD *)(v8 + 7828) = 1;
  }
  v10 = sub_180040700("##Tooltip_Error", 0, 33554799);
  sub_180036F60(1);
  if ( !v10 )
  {
    sub_180044DF0();
    return v10;
  }
  if ( *(_WORD *)(*(_QWORD *)(v0 + 5216) + 218LL) != 1 )
    return v10;
  sub_180072500("MESSAGE FROM DEAR IMGUI");
  v11 = qword_18010C470;
  v12 = *(_QWORD *)(v0 + 5216);
  v13 = *(int *)(qword_18010C470 + 5120);
  v14 = *(_QWORD *)(qword_18010C470 + 5128);
  v15 = *(_QWORD *)(v14 + 8 * v13 - 8);
  if ( v15 != v12 && *(_QWORD *)(v15 + 960) != v12 )
  {
    v16 = (unsigned int)(v13 - 2);
    if ( (int)v16 >= 0 )
    {
      while ( *(_QWORD *)(v14 + 8 * v16) != v12 )
      {
        v16 = (unsigned int)(v16 - 1);
        if ( (int)v16 < 0 )
          goto LABEL_23;
      }
      sub_1800B8BD0(v14 + 8 * v16, v14 + 8LL * ((int)v16 + 1), 8LL * ((int)v13 + ~(_DWORD)v16));
      *(_QWORD *)(*(_QWORD *)(v11 + 5128) + 8LL * *(int *)(v11 + 5120) - 8) = v12;
    }
  }
LABEL_23:
  v17 = *(int *)(v11 + 5136);
  v18 = v17;
  v19 = *(_QWORD *)(v0 + 5216);
  if ( *(_QWORD *)(*(_QWORD *)(v11 + 5144) + 8 * v17 - 8) != v19 )
  {
    v20 = *(__int16 *)(v19 + 226);
    for ( i = v17 - 1; v20 < i; --*(_WORD *)(v23 + 226) )
    {
      v22 = v20++;
      *(_QWORD *)(*(_QWORD *)(v11 + 5144) + 8 * v22) = *(_QWORD *)(*(_QWORD *)(v11 + 5144) + 8 * v22 + 8);
      v23 = *(_QWORD *)(*(_QWORD *)(v11 + 5144) + 8 * v22);
    }
    *(_QWORD *)(*(_QWORD *)(v11 + 5144) + 8 * v18 - 8) = v19;
    *(_WORD *)(v19 + 226) = i;
  }
  v24 = *(_QWORD *)(v11 + 5216);
  v25 = *(_DWORD *)(v24 + 44);
  *(_DWORD *)(v0 + 10176) = *(_DWORD *)(v24 + 40);
  *(_DWORD *)(v0 + 10180) = v25;
  return v10;
}
