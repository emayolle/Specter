// sub_1800847B0 size=1381
__int64 sub_1800847B0()
{
  __int64 v0; // r8
  __int64 v1; // rbx
  __int64 v2; // rdi
  float *v3; // rax
  float v4; // xmm0_4
  int v5; // r14d
  __int64 v6; // rax
  __int64 v7; // rbp
  __int64 v8; // rsi
  __int64 v9; // r9
  __int64 v10; // rcx
  int v11; // eax
  unsigned int v12; // edx
  __m128 v13; // xmm3
  unsigned __int64 v14; // xmm2_8
  bool v15; // al
  float v16; // xmm8_4
  __int64 v17; // r15
  float v18; // xmm6_4
  float v19; // xmm7_4
  __int64 v20; // rax
  float v21; // xmm2_4
  float v22; // xmm1_4
  float v23; // xmm6_4
  __int64 v24; // rax
  __int64 v25; // r9
  __int64 v26; // rdx
  __int64 v27; // r8
  _DWORD *v28; // rax
  int v29; // xmm1_4
  int v30; // xmm2_4
  int v31; // xmm3_4
  int v32; // xmm4_4
  __int64 v33; // rax
  __int64 v34; // rcx
  __int64 v35; // rax
  __int64 v36; // rcx
  float v37; // xmm0_4
  int v38; // eax
  __int64 v39; // rcx
  __int64 v40; // rax
  __int64 v41; // rdx
  __int64 v42; // r9
  __int64 v43; // r10
  _DWORD *v44; // rax
  int v45; // xmm1_4
  int v46; // xmm2_4
  int v47; // xmm3_4
  int v48; // xmm4_4
  __int64 v49; // rax
  __int64 v50; // r8
  __int64 v51; // rax
  __int64 v52; // r8
  __int64 v53; // rcx
  int v54; // eax
  __int64 result; // rax
  __m128 v56; // [rsp+30h] [rbp-68h] BYREF
  float v57; // [rsp+A0h] [rbp+8h] BYREF
  float v58; // [rsp+A4h] [rbp+Ch]
  float v59; // [rsp+A8h] [rbp+10h] BYREF
  float v60; // [rsp+ACh] [rbp+14h]

  v0 = qword_18010C470;
  v1 = qword_18010C470;
  v2 = *(_QWORD *)(qword_18010C470 + 5216);
  *(_BYTE *)(v2 + 206) = 1;
  v3 = *(float **)(v0 + 5216);
  v4 = v3[87] - *(float *)(v0 + 3260);
  v3[87] = v4;
  v3[70] = (float)(v4 + v3[10]) + v3[88];
  v5 = 1 << --*(_DWORD *)(v2 + 416);
  if ( (v5 & *(_DWORD *)(v2 + 420)) != 0 )
  {
    v6 = *(int *)(v0 + 8080);
    v7 = *(_QWORD *)(v0 + 8088);
    v8 = 5 * v6;
    if ( (*(_DWORD *)(v7 + 40 * v6 - 36) & 0x20000) != 0 )
    {
      if ( *(_BYTE *)(v0 + 8115) )
      {
        if ( !*(_DWORD *)(v0 + 8280) )
        {
          v9 = *(_QWORD *)(v0 + 8120);
          if ( v9 == v2 && *(_BYTE *)(v0 + 8265) && !*(_DWORD *)(v0 + 8344) && !*(_DWORD *)(v0 + 8456) )
          {
            v10 = *(_QWORD *)(v0 + 5216);
            *(_BYTE *)(v0 + 8265) = 0;
            v11 = *(_DWORD *)(v7 + 40 * v6 - 40);
            *(_DWORD *)(v0 + 7744) = v11;
            v12 = *(_DWORD *)(v7 + 8 * v8 - 32) & 0xFFDFFFFF;
            *(_DWORD *)(v0 + 7748) = v12;
            *(_OWORD *)(v0 + 7772) = *(_OWORD *)(v7 + 8 * v8 - 28);
            *(_QWORD *)(v0 + 8336) = v10;
            *(_DWORD *)(v0 + 8344) = v11;
            *(_DWORD *)(v0 + 8348) = *(_DWORD *)(v0 + 7676);
            *(_DWORD *)(v0 + 8368) = v12;
            v13 = (__m128)*(unsigned __int64 *)(v10 + 296);
            v14 = _mm_sub_ps((__m128)*(unsigned __int64 *)(v0 + 7780), v13).m128_u64[0];
            *(_QWORD *)(v0 + 8352) = _mm_sub_ps((__m128)*(unsigned __int64 *)(v0 + 7772), v13).m128_u64[0];
            *(_QWORD *)(v0 + 8360) = v14;
            *(_DWORD *)(*(_QWORD *)(v9 + 984) + 8LL * *(int *)(v0 + 8132) + 1052) = 2139095039;
            v15 = *(_BYTE *)(v0 + 8265) || *(_BYTE *)(v0 + 8202);
            *(_BYTE *)(v0 + 8201) = v15;
          }
        }
      }
    }
    v16 = *(float *)(v7 + 8 * v8 - 12);
    if ( v16 != 3.4028235e38 && *(float *)(v2 + 284) >= *(float *)(v2 + 612) )
    {
      v17 = *(_QWORD *)(v0 + 5216);
      v18 = *(float *)(v7 + 8 * v8 - 8);
      v19 = fmaxf(*(float *)(v7 + 8 * v8 - 16), *(float *)(v17 + 612));
      if ( (*(_DWORD *)(v7 + 8 * v8 - 36) & 0x80000) != 0 )
      {
        v20 = *(_QWORD *)(v0 + 8856);
        v21 = v20 ? fmaxf(*(float *)(v20 + 128), *(float *)(v17 + 284)) : *(float *)(v17 + 284);
        v22 = *(float *)(v0 + 3232);
        if ( (float)(int)(float)((float)(v21 - v22) - (float)(*(float *)(v0 + 4432) * 0.5)) > (float)((float)(v22 + *(float *)(v0 + 3348)) + v18) )
          v18 = (float)(int)(float)((float)(v21 - v22) - (float)(*(float *)(v0 + 4432) * 0.5));
      }
      v23 = fminf(v18, *(float *)(v17 + 620));
      if ( v19 < v23 )
      {
        v24 = *(__int16 *)(v7 + 8 * v8 - 4);
        if ( (_WORD)v24 != 0xFFFF )
        {
          v25 = *(_QWORD *)(v0 + 8856);
          if ( (*(_DWORD *)(v25 + 4) & 0x100000) == 0 )
          {
            v26 = *(_QWORD *)(v25 + 24);
            v27 = 116 * v24;
            v28 = *(_DWORD **)(v17 + 712);
            v29 = *(_DWORD *)(v27 + v26 + 36);
            v30 = *(_DWORD *)(v27 + v26 + 40);
            v31 = *(_DWORD *)(v27 + v26 + 44);
            v32 = *(_DWORD *)(v27 + v26 + 48);
            *(_OWORD *)(v17 + 608) = *(_OWORD *)(v27 + v26 + 36);
            v28[24] = v29;
            v28[25] = v30;
            v28[26] = v31;
            v28[27] = v32;
            v33 = *(_QWORD *)(v17 + 712);
            v34 = *(int *)(v33 + 160);
            v35 = *(_QWORD *)(v33 + 168);
            v36 = 2 * (v34 - 1);
            *(_DWORD *)(v35 + 8 * v36) = v29;
            *(_DWORD *)(v35 + 8 * v36 + 4) = v30;
            *(_DWORD *)(v35 + 8 * v36 + 8) = v31;
            *(_DWORD *)(v35 + 8 * v36 + 12) = v32;
            sub_18005D640(*(_QWORD *)(v25 + 416), *(_QWORD *)(v17 + 712), *(unsigned __int16 *)(v27 + v26 + 96), v25);
            v0 = qword_18010C470;
          }
        }
        v56 = *(__m128 *)(v0 + 4256);
        v37 = _mm_shuffle_ps(v56, v56, 255).m128_f32[0] * *(float *)(v0 + 3148);
        v58 = v23;
        v60 = v19;
        v56.m128_f32[3] = v37;
        v57 = (float)(int)v16;
        v59 = v57;
        sub_180036620(&v56);
        sub_18005C320(*(_QWORD *)(v17 + 712), (unsigned int)&v59, (unsigned int)&v57, v38, *(_DWORD *)(v1 + 3344));
        v0 = qword_18010C470;
        if ( *(_WORD *)(v7 + 8 * v8 - 4) != 0xFFFF )
        {
          v39 = *(_QWORD *)(qword_18010C470 + 8856);
          if ( (*(_DWORD *)(v39 + 4) & 0x100000) == 0 )
          {
            v40 = *(int *)(v39 + 116);
            if ( (_DWORD)v40 != -1 )
            {
              v41 = *(_QWORD *)(qword_18010C470 + 5216);
              v42 = *(_QWORD *)(v39 + 24);
              v43 = 116 * v40;
              v44 = *(_DWORD **)(v41 + 712);
              v45 = *(_DWORD *)(v43 + v42 + 36);
              v46 = *(_DWORD *)(v43 + v42 + 40);
              v47 = *(_DWORD *)(v43 + v42 + 44);
              v48 = *(_DWORD *)(v43 + v42 + 48);
              *(_OWORD *)(v41 + 608) = *(_OWORD *)(v43 + v42 + 36);
              v44[24] = v45;
              v44[25] = v46;
              v44[26] = v47;
              v44[27] = v48;
              v49 = *(_QWORD *)(v41 + 712);
              v50 = *(int *)(v49 + 160);
              v51 = *(_QWORD *)(v49 + 168);
              v52 = 2 * (v50 - 1);
              *(_DWORD *)(v51 + 8 * v52) = v45;
              *(_DWORD *)(v51 + 8 * v52 + 4) = v46;
              *(_DWORD *)(v51 + 8 * v52 + 8) = v47;
              *(_DWORD *)(v51 + 8 * v52 + 12) = v48;
              sub_18005D640(*(_QWORD *)(v39 + 416), *(_QWORD *)(v41 + 712), *(unsigned __int16 *)(v43 + v42 + 96), v42);
              v0 = qword_18010C470;
            }
          }
        }
      }
    }
    --*(_DWORD *)(v1 + 8080);
    *(_QWORD *)(v2 + 420) &= _mm_shuffle_epi32(_mm_cvtsi32_si128(~v5), 0).m128i_u64[0];
  }
  v53 = *(_QWORD *)(v0 + 5216);
  v54 = *(_DWORD *)(v53 + 264);
  if ( v54 <= 1 )
    return sub_180049A30("Calling PopID() too many times!");
  result = (unsigned int)(v54 - 1);
  *(_DWORD *)(v53 + 264) = result;
  return result;
}
