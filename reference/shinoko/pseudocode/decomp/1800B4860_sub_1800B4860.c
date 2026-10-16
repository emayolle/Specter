// sub_1800B4860 size=856
__int64 __fastcall sub_1800B4860(float a1, float a2)
{
  __int64 result; // rax
  double v4; // r9
  unsigned __int64 v5; // rcx
  double v6; // r10
  unsigned __int64 v7; // rdx
  double v8; // xmm2_8
  double v9; // xmm3_8
  unsigned int v10; // r9d
  int v11; // r8d
  int v12; // edx
  int v13; // r8d
  unsigned int v14; // eax
  __int64 v15; // rcx
  double v16; // xmm1_8
  double v17; // xmm3_8
  double v18; // xmm2_8
  double v19; // xmm1_8
  double v20; // xmm3_8
  double v21; // xmm2_8
  double v22; // xmm1_8
  double v23; // xmm3_8
  double v24; // xmm2_8
  double v25; // xmm1_8
  double v26; // xmm3_8
  double v27; // xmm2_8
  double v28; // xmm1_8
  double v29; // xmm3_8
  double v30; // xmm2_8
  double v31; // xmm1_8
  double v32; // xmm3_8
  double v33; // xmm2_8
  double v34; // xmm1_8
  double v35; // xmm3_8
  double v36; // xmm2_8
  double v37; // xmm1_8
  __int64 v38; // rcx
  double v39; // xmm1_8
  __m128i v40; // xmm1
  __m128i v41; // xmm1

  result = 0x7FFFFFFFFFFFFFFFLL;
  v4 = fabs(a1);
  v5 = (COERCE_UNSIGNED_INT64(a1) >> 52) & 0x7FF;
  v6 = fabs(a2);
  v7 = (COERCE_UNSIGNED_INT64(a2) >> 52) & 0x7FF;
  if ( ((COERCE_UNSIGNED_INT64(a1) >> 52) & 0x7FF) != 0 )
  {
    if ( ((COERCE_UNSIGNED_INT64(a1) >> 52) & 0x7FF) == 0x7FF )
      goto LABEL_16;
    result = (unsigned int)(v7 - 1);
    if ( (unsigned int)result <= 0x7FD )
    {
      if ( *(_QWORD *)&v4 == *(_QWORD *)&v6 )
        return 0x8000000000000000uLL;
      v8 = v4;
      v9 = v6;
      if ( *(_QWORD *)&v4 >= *(_QWORD *)&v6 )
      {
        v10 = _mm_getcsr();
        if ( (int)v5 > (int)v7 )
        {
          v11 = (unsigned __int64)(715827883LL * ((int)v5 - (int)v7)) >> 32;
          v12 = 0;
          v13 = ((unsigned int)v11 >> 31) + (v11 >> 2);
          v9 = v6 * COERCE_DOUBLE((__int64)(24 * v13 + 1023) << 52);
          if ( v13 >= 8 )
          {
            v14 = ((unsigned int)(v13 - 8) >> 3) + 1;
            v15 = v14;
            v12 = 8 * v14;
            do
            {
              v16 = (double)(int)(v8 / v9) * v9;
              v17 = v9 * 0.00000005960464477539062;
              v18 = v8 - v16;
              v19 = (double)(int)(v18 / v17) * v17;
              v20 = v17 * 0.00000005960464477539062;
              v21 = v18 - v19;
              v22 = (double)(int)(v21 / v20) * v20;
              v23 = v20 * 0.00000005960464477539062;
              v24 = v21 - v22;
              v25 = (double)(int)(v24 / v23) * v23;
              v26 = v23 * 0.00000005960464477539062;
              v27 = v24 - v25;
              v28 = (double)(int)(v27 / v26) * v26;
              v29 = v26 * 0.00000005960464477539062;
              v30 = v27 - v28;
              v31 = (double)(int)(v30 / v29) * v29;
              v32 = v29 * 0.00000005960464477539062;
              v33 = v30 - v31;
              v34 = (double)(int)(v33 / v32) * v32;
              v35 = v32 * 0.00000005960464477539062;
              v36 = v33 - v34;
              v37 = (double)(int)(v36 / v35) * v35;
              v9 = v35 * 0.00000005960464477539062;
              v8 = v36 - v37;
              --v15;
            }
            while ( v15 );
          }
          if ( v12 < v13 )
          {
            v38 = (unsigned int)(v13 - v12);
            do
            {
              v39 = (double)(int)(v8 / v9) * v9;
              v9 = v9 * 0.00000005960464477539062;
              v8 = v8 - v39;
              --v38;
            }
            while ( v38 );
          }
        }
        _mm_setcsr(v10);
        return (unsigned int)(int)(v8 / v9);
      }
      return result;
    }
  }
  if ( ((COERCE_UNSIGNED_INT64(a1) >> 52) & 0x7FF) == 0x7FF )
  {
LABEL_16:
    if ( (COERCE_UNSIGNED_INT64(a1) & 0xFFFFFFFFFFFFFLL) != 0 )
    {
      v40 = 0;
      *(float *)v40.m128i_i32 = a1;
      return sub_1800B30C0((unsigned int)_mm_cvtsi128_si32(v40), v7);
    }
    return sub_1800B2F60((unsigned int)"fmodf", 22, -4194304, 1, 8, 33, LODWORD(a1), LODWORD(a2), 2);
  }
  if ( ((COERCE_UNSIGNED_INT64(a2) >> 52) & 0x7FF) != 0x7FF )
  {
    if ( ((COERCE_UNSIGNED_INT64(a1) >> 52) & 0x7FF) == 0 && ((COERCE_UNSIGNED_INT64(a2) >> 52) & 0x7FF) != 0 )
      return result;
    return sub_1800B2F60((unsigned int)"fmodf", 22, -4194304, 1, 8, 33, LODWORD(a1), LODWORD(a2), 2);
  }
  result = 0xFFFFFFFFFFFFFLL;
  if ( (COERCE_UNSIGNED_INT64(a2) & 0xFFFFFFFFFFFFFLL) != 0 )
  {
    v41 = 0;
    *(float *)v41.m128i_i32 = a2;
    return sub_1800B30C0((unsigned int)_mm_cvtsi128_si32(v41), v7);
  }
  return result;
}
