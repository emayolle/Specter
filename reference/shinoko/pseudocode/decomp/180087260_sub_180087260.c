// sub_180087260 size=1490
char __fastcall sub_180087260(_BYTE *a1, unsigned __int64 a2, _BYTE *a3, char a4, char a5)
{
  __int64 v5; // rdi
  __int64 v9; // rbx
  __m128 v11; // xmm10
  __m128 v12; // xmm11
  __int64 v13; // rax
  __int64 v14; // rdx
  int v15; // r8d
  int v16; // r9d
  unsigned int v17; // xmm9_4
  float v18; // xmm7_4
  __int64 v19; // rdx
  char v20; // r15
  int v21; // edx
  int v22; // r8d
  int v23; // r9d
  __m128 v24; // xmm8
  float v25; // xmm1_4
  __m128 v26; // xmm6
  char v27; // r12
  float *v28; // rax
  float v29; // xmm8_4
  float v30; // xmm0_4
  __int64 v31; // rcx
  __int64 v32; // rax
  float v33; // xmm7_4
  float v34; // xmm7_4
  __m128 v35; // xmm1
  float v36; // xmm9_4
  __m128 v37; // xmm7
  __int64 v38; // rax
  __m128 v39; // xmm0
  float v40; // xmm7_4
  __m128 v41; // xmm6
  int v42; // eax
  __m128 v43; // xmm8
  unsigned int v44; // eax
  __int64 v45; // rdx
  __int16 v46; // ax
  int v47; // ecx
  bool v48; // zf
  int v49; // r8d
  __int64 v50; // rcx
  int v51; // eax
  __int64 v52; // rdx
  int v53; // ecx
  __m128 v54; // [rsp+40h] [rbp-98h] BYREF
  unsigned __int64 v55; // [rsp+E8h] [rbp+10h] BYREF

  v55 = a2;
  v5 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v9 = *(_QWORD *)(v5 + 5216);
  if ( *(_BYTE *)(v9 + 209) )
    return 0;
  v11 = (__m128)*(unsigned int *)(v9 + 280);
  v12 = (__m128)*(unsigned int *)(v9 + 284);
  v13 = sub_180037410(a1, 0);
  v17 = *(_DWORD *)(v5 + 4432);
  if ( a1 == (_BYTE *)v13 )
  {
    v18 = 0.0;
  }
  else
  {
    sub_180067070(*(_QWORD *)(v5 + 4416), (unsigned int)&v55, v15, v16, -1082130432, (__int64)a1, v13, v14);
    v17 = HIDWORD(v55);
    v18 = (float)(int)(float)(*(float *)&v55 + 0.99998999);
  }
  v20 = sub_1800871D0();
  if ( v20 )
  {
    LOBYTE(v19) = 1;
    sub_180045260(0x2000, v19);
  }
  sub_1800466C0(a1);
  if ( !a5 )
    sub_180045380();
  if ( *(_DWORD *)(v9 + 468) )
  {
    if ( a3 && *a3 )
    {
      sub_18003DF30((unsigned int)&v55, (_DWORD)a3, 0, 0, -1082130432);
      v29 = *v28;
    }
    else
    {
      v29 = 0.0;
    }
    v30 = (float)(int)(float)(*(float *)(v5 + 4432) * 1.2);
    sub_180086EA0(v9 + 388, v21, v22, v23, LODWORD(v30));
    v31 = *(_QWORD *)(qword_18010C470 + 5216);
    if ( *(_QWORD *)(v31 + 456) || (v32 = 632, *(_QWORD *)(qword_18010C470 + 8856)) )
      v32 = 584;
    v33 = *(float *)(v32 + v31) - *(float *)(v31 + 280);
    v55 = __PAIR64__(v17, LODWORD(v30));
    v34 = v33 - v30;
    v27 = sub_180084D20(byte_1800D411C, 0, 192937984, (float *)&v55);
    if ( (*(_DWORD *)(v5 + 7752) & 0x100) != 0 )
    {
      v35 = v11;
      v36 = fmaxf(0.0, v34);
      v37 = v12;
      v37.m128_f32[0] = v12.m128_f32[0] + 0.0;
      v35.m128_f32[0] = v11.m128_f32[0] + (float)*(unsigned __int16 *)(v9 + 400);
      sub_180037440(_mm_unpacklo_ps(v35, v37).m128_i64[0], a1, nullptr, 1);
      if ( v29 > 0.0 )
      {
        sub_180036E50(0, v5 + 3440);
        v38 = qword_18010C470;
        *(_QWORD *)(qword_18010C470 + 10120) = "(";
        *(_QWORD *)(v38 + 10128) = ")";
        v39 = (__m128)COERCE_UNSIGNED_INT((float)*(unsigned __int16 *)(v9 + 402));
        v39.m128_f32[0] = (float)(v39.m128_f32[0] + v36) + v11.m128_f32[0];
        sub_180037440(_mm_unpacklo_ps(v39, v37).m128_i64[0], a3, nullptr, 0);
        sub_180036F60(1);
      }
      if ( a4 )
      {
        v40 = *(float *)(v5 + 4432);
        v41 = (__m128)LODWORD(v40);
        v54 = *(__m128 *)(qword_18010C470 + 3424);
        v41.m128_f32[0] = (float)((float)(v40 * 0.134) * 0.5) + v12.m128_f32[0];
        v42 = *(unsigned __int16 *)(v9 + 404);
        v54.m128_f32[3] = _mm_shuffle_ps(v54, v54, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
        v43 = (__m128)COERCE_UNSIGNED_INT((float)v42);
        v43.m128_f32[0] = (float)((float)(v43.m128_f32[0] + v36) + (float)(v40 * 0.40000001)) + v11.m128_f32[0];
        sub_180036620(&v54);
        sub_180068080(*(_QWORD *)(v9 + 712), _mm_unpacklo_ps(v43, v41).m128_u64[0], v44);
      }
    }
  }
  else
  {
    v24 = (__m128)*(unsigned int *)(v9 + 336);
    v24.m128_f32[0] = v24.m128_f32[0] + *(float *)(v9 + 284);
    v25 = (float)(int)(float)(*(float *)(v5 + 3228) * 0.5) + *(float *)(v9 + 280);
    *(float *)(v9 + 280) = v25;
    v26 = (__m128)COERCE_UNSIGNED_INT((float)*(unsigned __int16 *)(v9 + 400));
    v26.m128_f32[0] = v26.m128_f32[0] + v25;
    sub_180037070(14, *(float *)(v5 + 3228) + *(float *)(v5 + 3228));
    v55 = LODWORD(v18);
    v27 = sub_180084D20(byte_1800D411C, a4, 176160768, (float *)&v55);
    sub_1800371B0(1);
    if ( (*(_DWORD *)(v5 + 7752) & 0x100) != 0 )
      sub_180037440(_mm_unpacklo_ps(v26, v24).m128_i64[0], a1, nullptr, 1);
    *(float *)(v9 + 280) = *(float *)(v9 + 280) - (float)(int)(float)(*(float *)(v5 + 3228) * 0.5);
  }
  if ( !a5 )
  {
    v45 = qword_18010C470;
    v46 = *(_WORD *)(qword_18010C470 + 9696);
    if ( v46 > 0 )
    {
      v47 = *(_DWORD *)(qword_18010C470 + 8016);
      v48 = (*(_DWORD *)(qword_18010C470 + 7680) & 0x400) == 0;
      *(_WORD *)(qword_18010C470 + 9696) = v46 - 1;
      *(_DWORD *)(v45 + 8016) = v47 - 1;
      v49 = *(_DWORD *)(*(_QWORD *)(v45 + 8024) + 4LL * (v47 - 2));
      *(_DWORD *)(v45 + 7680) = v49;
      if ( !v48 && (v49 & 0x400) == 0 )
        *(_DWORD *)(v45 + 3148) = *(_DWORD *)(v45 + 9692);
    }
    else
    {
      sub_180049A30("Calling EndDisabled() too many times!");
    }
  }
  v50 = *(_QWORD *)(qword_18010C470 + 5216);
  v51 = *(_DWORD *)(v50 + 264);
  if ( v51 > 1 )
    *(_DWORD *)(v50 + 264) = v51 - 1;
  else
    sub_180049A30("Calling PopID() too many times!");
  if ( v20 )
  {
    v52 = qword_18010C470;
    v53 = *(_DWORD *)(qword_18010C470 + 8016);
    if ( v53 > 1 )
    {
      *(_DWORD *)(qword_18010C470 + 8016) = v53 - 1;
      *(_DWORD *)(v52 + 7680) = *(_DWORD *)(*(_QWORD *)(v52 + 8024) + 4LL * (v53 - 2));
    }
    else
    {
      sub_180049A30("Calling PopItemFlag() too many times!");
    }
  }
  return v27;
}
