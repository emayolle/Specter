// sub_180085C00 size=1654
__int64 sub_180085C00()
{
  __int64 v0; // rsi
  __int64 v1; // rbx
  float *v2; // r14
  __int64 v3; // rdi
  float v4; // xmm9_4
  float v5; // xmm10_4
  float v6; // xmm7_4
  float v7; // xmm8_4
  int v8; // r12d
  int v9; // eax
  __int64 v10; // rdi
  __int64 v11; // r13
  float v12; // xmm1_4
  float v13; // xmm0_4
  float v14; // xmm2_4
  float v15; // xmm1_4
  float v16; // xmm1_4
  __m128 *v17; // rax
  __int128 v18; // xmm0
  int v19; // eax
  int v20; // eax
  float v21; // xmm0_4
  float v22; // xmm5_4
  float v23; // xmm3_4
  float v24; // xmm4_4
  float v25; // xmm2_4
  float v26; // xmm0_4
  float v27; // xmm2_4
  float v28; // xmm1_4
  int v29; // eax
  _DWORD *v30; // rdi
  __int64 v31; // rcx
  __m128d v32; // xmm0
  int v33; // ecx
  __int64 v34; // rax
  float v35; // xmm0_4
  __int64 v36; // r8
  __int64 v37; // rcx
  float v38; // xmm1_4
  __int64 v39; // rcx
  int v40; // eax
  float v42; // [rsp+48h] [rbp-39h] BYREF
  float v43; // [rsp+4Ch] [rbp-35h]
  float v44; // [rsp+50h] [rbp-31h] BYREF
  float v45; // [rsp+54h] [rbp-2Dh]
  __m128 v46; // [rsp+58h] [rbp-29h] BYREF

  v0 = qword_18010C470;
  v1 = *(_QWORD *)(qword_18010C470 + 9144);
  v2 = *(float **)(qword_18010C470 + 5216);
  v3 = *(_QWORD *)(v1 + 40);
  if ( *(_DWORD *)(v1 + 48) != *(_DWORD *)(qword_18010C470 + 7676) )
    sub_180049A30("EndMultiSelect() FocusScope mismatch!");
  sub_180085B30(&v42, v1, v2);
  v4 = v45;
  v5 = v44;
  v6 = v43;
  v7 = v42;
  if ( *(_BYTE *)(v1 + 90) )
  {
    if ( *(_BYTE *)(v1 + 33) || !*(_BYTE *)(v1 + 93) && *(_QWORD *)(v1 + 16) != -1 )
    {
      if ( (*(_BYTE *)(v0 + 10228) & 0x40) != 0 )
        sub_180052F00("[selection] EndMultiSelect: Reset RangeSrcItem.\n");
      *(_QWORD *)(v3 + 24) = -1;
    }
    if ( !*(_BYTE *)(v1 + 92) && *(_QWORD *)(v3 + 32) != -1 )
    {
      if ( (*(_BYTE *)(v0 + 10228) & 0x40) != 0 )
        sub_180052F00("[selection] EndMultiSelect: Reset NavIdItem.\n");
      *(_QWORD *)(v3 + 32) = -1;
      *(_BYTE *)(v3 + 21) = -1;
    }
    v8 = *(_DWORD *)(v1 + 52);
    if ( (v8 & 0xC0) != 0 )
    {
      v9 = *(_DWORD *)(v1 + 80);
      if ( v9 )
      {
        v10 = qword_18010C470;
        if ( *(_DWORD *)(qword_18010C470 + 9040) == v9 )
        {
          if ( *(_BYTE *)(qword_18010C470 + 9044) )
          {
            v11 = *(_QWORD *)(qword_18010C470 + 5216);
            *(_BYTE *)(qword_18010C470 + 9088) = 0;
            v12 = *(float *)(v10 + 228);
            v13 = v6 <= v12 ? fminf(v4, v12) : v6;
            v14 = *(float *)(v10 + 224);
            v15 = v7 <= v14 ? fminf(v5, v14) : v7;
            v16 = v15 - *(float *)(v11 + 296);
            v17 = (__m128 *)qword_18010C470;
            *(float *)(v10 + 9068) = v13 - *(float *)(v11 + 300);
            v18 = *(_OWORD *)(v10 + 9124);
            *(float *)(v10 + 9064) = v16;
            v46 = v17[242];
            v42 = fmaxf(*(float *)&v18, v7);
            v45 = fminf(*((float *)&v18 + 3), v4);
            v43 = fmaxf(*((float *)&v18 + 1), v6);
            v44 = fminf(*((float *)&v18 + 2), v5);
            v46.m128_f32[3] = _mm_shuffle_ps(v46, v46, 255).m128_f32[0] * (float)(v17[196].m128_f32[3] * 0.30000001);
            sub_180036620(&v46);
            sub_18005C870(*(_QWORD *)(v11 + 712), (unsigned int)&v42, (unsigned int)&v44, v19, 0, 0);
            v46 = *(__m128 *)(qword_18010C470 + 4304);
            v46.m128_f32[3] = _mm_shuffle_ps(v46, v46, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
            sub_180036620(&v46);
            sub_18005C460(*(_QWORD *)(v11 + 712), (unsigned int)&v42, (unsigned int)&v44, v20, 0);
            if ( (v8 & 0x900) == 0x800 )
            {
              v21 = -*(float *)(v10 + 4432);
              v22 = *(float *)(v10 + 224);
              v23 = v6 - v21;
              v24 = v5 - *(float *)(v10 + 4432);
              v25 = v4 - *(float *)(v10 + 4432);
              v42 = v7 - v21;
              v43 = v6 - v21;
              v44 = v5 + v21;
              v45 = v4 + v21;
              if ( v22 < (float)(v7 - v21) || (v26 = *(float *)(v10 + 228), v26 < v23) || v24 <= v22 || v25 <= v26 )
                sub_1800857A0(v10 + 9040, v11, &v42);
            }
          }
        }
      }
    }
  }
  if ( !*(_BYTE *)(v1 + 89) )
    sub_18008A670(v1);
  if ( (unsigned __int8)sub_180045450()
    && (v27 = *(float *)(v0 + 224), v27 >= v2[136])
    && (v28 = *(float *)(v0 + 228), v28 >= v2[137])
    && v2[138] > v27
    && v2[139] > v28 )
  {
    v29 = *(_DWORD *)(v1 + 52);
    v30 = (_DWORD *)(v1 + 52);
    if ( ((v29 & 0x1000) == 0 || v27 >= v7 && v28 >= v6 && v5 > v27 && v4 > v28)
      && !*(_DWORD *)(v0 + 5308)
      && !*(_DWORD *)(v0 + 5332) )
    {
      if ( (v29 & 0xC0) != 0 && !*(_BYTE *)(v0 + 9044) && !*(_BYTE *)(v0 + 9045) && *(_WORD *)(v0 + 2842) == 1 )
      {
        v31 = qword_18010C470;
        *(_DWORD *)(qword_18010C470 + 9040) = *(_DWORD *)(v1 + 80);
        *(_WORD *)(v31 + 9045) = 257;
        *(_BYTE *)(v31 + 9047) = 1;
        *(_WORD *)(v31 + 9052) = *(_WORD *)(v31 + 256);
        v32 = (__m128d)_mm_sub_ps(
                         (__m128)*(unsigned __int64 *)(v31 + 224),
                         (__m128)*(unsigned __int64 *)(*(_QWORD *)(v31 + 5216) + 296LL));
        *(_QWORD *)(v31 + 9072) = 0;
        *(__m128d *)(v31 + 9056) = _mm_unpacklo_pd(v32, v32);
        sub_18004D450((__int64)v2, 2u);
        v33 = *(_DWORD *)(v1 + 80);
        v34 = qword_18010C470;
        *(_DWORD *)(qword_18010C470 + 5308) = v33;
        *(_BYTE *)(v34 + 5328) = 0;
        if ( v33 && *(_DWORD *)(v34 + 5312) != v33 )
          *(_QWORD *)(v34 + 5320) = 0;
        if ( (*v30 & 0x1000) != 0 )
        {
          v35 = *(float *)(v0 + 228);
          v36 = *(unsigned int *)(v1 + 48);
          v42 = *(float *)(v0 + 224);
          v43 = v35;
          v44 = v42;
          v45 = v35;
          sub_18004DA70(0, 0, v36, &v42);
        }
      }
      if ( (*v30 & 0x400) != 0
        && *(_BYTE *)(qword_18010C470 + 2862)
        && !*(_BYTE *)(qword_18010C470 + 7196)
        && *(float *)(qword_18010C470 + 2964) < (float)(*(float *)(qword_18010C470 + 112)
                                                      * *(float *)(qword_18010C470 + 112))
        && !*(_DWORD *)(v0 + 256) )
      {
        sub_180086A80(v1);
      }
    }
  }
  else
  {
    v30 = (_DWORD *)(v1 + 52);
  }
  if ( (*v30 & 0x10000) != 0 )
  {
    v37 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( *(_QWORD *)(v37 + 8120) == *(_QWORD *)(v37 + 5216) && *(_BYTE *)(v37 + 8265) && !*(_DWORD *)(v37 + 8132) )
    {
      *(_DWORD *)(v37 + 8268) &= 0xFFFFFFF4;
      *(_DWORD *)(v37 + 8268) |= 4u;
    }
  }
  v38 = fmaxf(*(float *)(v1 + 68), v2[77]);
  v2[76] = fmaxf(*(float *)(v1 + 64), v2[76]);
  v2[77] = v38;
  sub_1800455F0();
  if ( (*(_BYTE *)(v0 + 10228) & 0x40) != 0 )
    sub_180085A40(v39, (int *)v1);
  *v30 = 0;
  *(_DWORD *)(v1 + 48) = 0;
  v40 = *(_DWORD *)(v0 + 9152);
  *(_DWORD *)(v0 + 9152) = v40 - 1;
  if ( v40 - 1 <= 0 )
    *(_QWORD *)(v0 + 9144) = 0;
  else
    *(_QWORD *)(v0 + 9144) = *(_QWORD *)(v0 + 9168) + 96LL * (v40 - 2);
  return v1;
}
