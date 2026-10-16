// sub_180088BF0 size=704
__int64 __fastcall sub_180088BF0(__int64 a1)
{
  __int64 v1; // rbp
  __int64 v3; // r14
  __m128 v4; // xmm8
  __m128 v5; // xmm9
  int v6; // xmm13_4
  int v7; // xmm14_4
  __int64 v8; // rdx
  int v9; // xmm11_4
  int v10; // xmm12_4
  unsigned __int64 v11; // xmm6_8
  float v12; // xmm7_4
  unsigned __int8 v13; // al
  int v14; // ebx
  unsigned __int8 v15; // si
  __int64 v16; // rdx
  int v17; // ecx
  __int64 v18; // r10
  int v19; // r8d
  int v20; // r9d
  __int64 v21; // r11
  unsigned int v22; // edx
  int v24; // r8d
  int v25; // eax
  __m128 v26; // [rsp+20h] [rbp-C8h] BYREF

  v1 = qword_18010C470;
  v3 = *(_QWORD *)(qword_18010C470 + 5216);
  v4 = (__m128)*(unsigned int *)(qword_18010C470 + 3216);
  v5 = (__m128)*(unsigned int *)(qword_18010C470 + 4432);
  v5.m128_f32[0] = v5.m128_f32[0] - 2.0;
  v4.m128_f32[0] = (float)(v4.m128_f32[0] + v4.m128_f32[0]) + *(float *)(qword_18010C470 + 4432);
  v6 = *(_DWORD *)(v3 + 280);
  v7 = *(_DWORD *)(v3 + 284);
  v26 = *(__m128 *)(qword_18010C470 + 3424);
  v26.m128_f32[3] = _mm_shuffle_ps(v26, v26, 255).m128_f32[0] * 0.5;
  sub_180036E50(0, &v26);
  v26 = 0;
  sub_180036E50(21, &v26);
  LOBYTE(v8) = 1;
  sub_180045260(10, v8);
  v9 = *(_DWORD *)(v1 + 116);
  v10 = *(_DWORD *)(v1 + 120);
  *(_DWORD *)(v1 + 116) = 1048576000;
  *(_DWORD *)(v1 + 120) = 1045220557;
  v11 = _mm_unpacklo_ps(v5, v4).m128_u64[0];
  v12 = fmaxf(*(float *)(a1 + 52), *(float *)(a1 + 60) - (float)(v5.m128_f32[0] + v5.m128_f32[0]));
  *(_DWORD *)(v3 + 284) = *(_DWORD *)(a1 + 56);
  *(float *)(v3 + 280) = v12;
  v13 = sub_180070570("##<", 0, v11);
  v14 = 1;
  *(_DWORD *)(v3 + 284) = *(_DWORD *)(a1 + 56);
  v15 = v13;
  *(float *)(v3 + 280) = v12 + v5.m128_f32[0];
  if ( !(unsigned __int8)sub_180070570("##>", 1, v11) )
    v14 = (v15 ^ 1) - 1;
  v16 = qword_18010C470;
  v17 = *(_DWORD *)(qword_18010C470 + 8016);
  if ( v17 > 1 )
  {
    *(_DWORD *)(qword_18010C470 + 8016) = v17 - 1;
    *(_DWORD *)(v16 + 7680) = *(_DWORD *)(*(_QWORD *)(v16 + 8024) + 4LL * (v17 - 2));
  }
  else
  {
    sub_180049A30("Calling PopItemFlag() too many times!");
  }
  sub_180036F60(2);
  v18 = 0;
  *(_DWORD *)(v1 + 120) = v10;
  *(_DWORD *)(v1 + 116) = v9;
  if ( v14 )
  {
    v19 = *(_DWORD *)(a1 + 32);
    if ( v19 )
    {
      v20 = *(_DWORD *)(a1 + 8);
      if ( v20 > 0 )
      {
        v21 = *(_QWORD *)(a1 + 16);
        v22 = 0;
        while ( *(_DWORD *)(44LL * v22 + v21) != v19 )
        {
          if ( (int)++v22 >= v20 )
            goto LABEL_12;
        }
        v24 = v22 + v14;
        while ( 1 )
        {
          if ( v24 < 0 || (v25 = v24, v24 >= v20) )
            v25 = v22;
          v18 = v21 + 44LL * v25;
          if ( (*(_DWORD *)(v18 + 4) & 0x200000) == 0 )
            break;
          v24 += v14;
          if ( v24 < 0 || v24 >= v20 )
            break;
          v22 += v14;
        }
      }
    }
  }
LABEL_12:
  *(_DWORD *)(v3 + 280) = v6;
  *(_DWORD *)(v3 + 284) = v7;
  *(float *)(a1 + 60) = *(float *)(a1 + 60) - (float)((float)(v5.m128_f32[0] + v5.m128_f32[0]) + 1.0);
  return v18;
}
