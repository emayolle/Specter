// sub_180047AB0 size=1819
void sub_180047AB0()
{
  __int64 v0; // rsi
  __int64 v1; // rdi
  float v2; // xmm3_4
  float v3; // xmm2_4
  float v4; // xmm0_4
  bool v5; // zf
  float v6; // xmm8_4
  float v7; // xmm7_4
  __int64 v8; // rbx
  __int64 v9; // rbp
  float v10; // xmm1_4
  __m128 v11; // xmm6
  float v12; // xmm0_4
  __m128 v13; // xmm0
  __m128 v14; // xmm6
  __int32 v15; // xmm4_4
  float v16; // xmm2_4
  float v17; // xmm8_4
  float v18; // xmm7_4
  __int64 v19; // rdx
  __int64 i; // rcx
  __int64 j; // rcx
  __int64 v22; // rcx
  float v23; // xmm0_4
  float v24; // xmm1_4
  bool v25; // al
  char v26; // r14
  _QWORD *v27; // rbp
  float v28; // xmm0_4
  float v29; // xmm1_4
  float v30; // xmm1_4
  float v31; // xmm0_4
  unsigned __int64 v32; // [rsp+70h] [rbp+8h] BYREF

  v0 = qword_18010C470;
  v1 = qword_18010C470;
  if ( *(_QWORD *)(qword_18010C470 + 5256) )
  {
    v2 = *(float *)(qword_18010C470 + 5280) - *(float *)(qword_18010C470 + 32);
    *(float *)(qword_18010C470 + 5280) = v2;
    v3 = *(float *)(v0 + 224);
    if ( v3 >= -256000.0 )
    {
      v4 = *(float *)(v0 + 228);
      if ( v4 >= -256000.0
        && (float)((float)((float)(v3 - *(float *)(v0 + 5264)) * (float)(v3 - *(float *)(v0 + 5264)))
                 + (float)((float)(v4 - *(float *)(v0 + 5268)) * (float)(v4 - *(float *)(v0 + 5268)))) > (float)(*(float *)(v0 + 112) * *(float *)(v0 + 112)) )
      {
        *(_DWORD *)(v0 + 5280) = 0;
        v2 = 0.0;
      }
    }
    if ( v2 <= 0.0 )
    {
      v5 = *(_BYTE *)(v0 + 10228) >= 0;
      *(_DWORD *)(v0 + 5280) = 0;
      if ( !v5 )
      {
        sub_180052F00("[io] LockWheelingWindow() \"%s\"\n", "NULL");
        v0 = qword_18010C470;
      }
      *(_QWORD *)(v1 + 5264) = *(_QWORD *)(v1 + 224);
      *(_QWORD *)(v1 + 5256) = 0;
      *(_DWORD *)(v1 + 5272) = -1;
      *(_QWORD *)(v1 + 5292) = 0;
    }
  }
  if ( *(_DWORD *)(v0 + 7248) == -1 )
    v6 = *(float *)(v1 + 244);
  else
    v6 = 0.0;
  if ( *(_DWORD *)(v0 + 7260) == -1 )
    v7 = *(float *)(v1 + 240);
  else
    v7 = 0.0;
  v8 = *(_QWORD *)(v1 + 5256);
  if ( v8 )
  {
    v9 = *(_QWORD *)(v1 + 5256);
  }
  else
  {
    v9 = *(_QWORD *)(v1 + 5224);
    if ( !v9 )
      return;
  }
  if ( *(_BYTE *)(v9 + 207) )
    return;
  if ( v7 != 0.0 )
  {
    if ( !*(_BYTE *)(v1 + 252) )
      goto LABEL_32;
    if ( *(_BYTE *)(v1 + 80) )
    {
      *(float *)(v0 + 5280) = fminf((float)(fabs(v7) * 0.69999999) + *(float *)(v0 + 5280), 0.69999999);
      if ( *(_QWORD *)(v0 + 5256) != v9 )
      {
        if ( *(char *)(v0 + 10228) < 0 )
          sub_180052F00("[io] LockWheelingWindow() \"%s\"\n", *(const char **)(v9 + 8));
        *(_QWORD *)(v0 + 5264) = *(_QWORD *)(v0 + 224);
        *(_QWORD *)(v0 + 5256) = v9;
      }
      v10 = *(float *)(v9 + 696);
      v11 = (__m128)0x3F000000u;
      v12 = (float)(*(float *)(v1 + 240) * 0.1) + v10;
      if ( v12 >= 0.5 )
      {
        v11 = (__m128)0x40200000u;
        v11.m128_f32[0] = fminf(2.5, v12);
      }
      *(_DWORD *)(v9 + 696) = v11.m128_i32[0];
      if ( v9 == *(_QWORD *)(v9 + 960) )
      {
        v13 = (__m128)0x3F800000u;
        v11.m128_f32[0] = v11.m128_f32[0] / v10;
        v13.m128_f32[0] = 1.0 - v11.m128_f32[0];
        v32 = _mm_add_ps(
                (__m128)*(unsigned __int64 *)(v9 + 40),
                _mm_div_ps(
                  _mm_mul_ps(
                    _mm_mul_ps((__m128)*(unsigned __int64 *)(v9 + 48), _mm_shuffle_ps(v13, v13, 0)),
                    _mm_sub_ps((__m128)*(unsigned __int64 *)(v1 + 224), (__m128)*(unsigned __int64 *)(v9 + 40))),
                  (__m128)*(unsigned __int64 *)(v9 + 48))).m128_u64[0];
        sub_1800454B0(v9, &v32, 0);
        v14 = _mm_shuffle_ps(v11, v11, 0);
        *(_QWORD *)(v9 + 48) = _mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_mul_ps((__m128)*(unsigned __int64 *)(v9 + 48), v14))).m128_u64[0];
        *(_QWORD *)(v9 + 56) = _mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_mul_ps((__m128)*(unsigned __int64 *)(v9 + 56), v14))).m128_u64[0];
      }
      return;
    }
  }
  if ( *(_BYTE *)(v1 + 252) )
    return;
LABEL_32:
  if ( *(_BYTE *)(v1 + 2922) )
  {
    v6 = v7;
    v7 = 0.0;
  }
  v15 = _mm_load_si128((const __m128i *)&xmmword_1800E6B60).m128i_i32[0];
  v16 = *(float *)(v1 + 5296);
  *(float *)(v1 + 5292) = (float)(COERCE_FLOAT(LODWORD(v6) & v15) / 30.0)
                        + (float)(*(float *)(v1 + 5292) - (float)(*(float *)(v1 + 5292) / 30.0));
  *(float *)(v1 + 5296) = (float)(COERCE_FLOAT(LODWORD(v7) & v15) / 30.0) + (float)(v16 - (float)(v16 / 30.0));
  v17 = v6 + *(float *)(v1 + 5284);
  v18 = v7 + *(float *)(v1 + 5288);
  *(_QWORD *)(v1 + 5284) = 0;
  if ( v17 != 0.0 || v18 != 0.0 )
  {
    if ( v8 )
      goto LABEL_66;
    v19 = 0;
    v8 = 0;
    if ( v17 != 0.0 )
    {
      v19 = *(_QWORD *)(v0 + 5224);
      for ( i = v19; (*(_DWORD *)(v19 + 20) & 0x1000000) != 0; i = v19 )
      {
        if ( *(float *)(i + 160) != 0.0 && (*(_DWORD *)(i + 20) & 0x210) != 0x10 )
          break;
        v19 = *(_QWORD *)(i + 944);
      }
    }
    if ( v18 != 0.0 )
    {
      v8 = *(_QWORD *)(v0 + 5224);
      for ( j = v8; (*(_DWORD *)(v8 + 20) & 0x1000000) != 0; j = v8 )
      {
        if ( *(float *)(j + 164) != 0.0 && (*(_DWORD *)(j + 20) & 0x210) != 0x10 )
          break;
        v8 = *(_QWORD *)(j + 944);
      }
    }
    if ( !v19 )
    {
      if ( !v8 )
      {
        v8 = 0;
        goto LABEL_65;
      }
LABEL_66:
      if ( (*(_DWORD *)(v8 + 20) & 0x210) == 0 )
      {
        v25 = v17 != 0.0 && *(float *)(v8 + 160) != 0.0;
        LOBYTE(v32) = v25;
        v26 = v18 != 0.0 && *(float *)(v8 + 164) != 0.0;
        BYTE1(v32) = v26;
        if ( v25 )
        {
          if ( v26 )
          {
            *((_BYTE *)&v32 + (*(float *)(v1 + 5292) > *(float *)(v1 + 5296))) = 0;
            v26 = BYTE1(v32);
            v25 = v32;
          }
          if ( v25 )
          {
            v27 = (_QWORD *)v0;
            *(float *)(v0 + 5280) = fminf(
                                      (float)(COERCE_FLOAT(LODWORD(v17) & v15) * 0.69999999) + *(float *)(v0 + 5280),
                                      0.69999999);
            if ( *(_QWORD *)(v0 + 5256) != v8 )
            {
              if ( *(char *)(v0 + 10228) < 0 )
              {
                sub_180052F00("[io] LockWheelingWindow() \"%s\"\n", *(const char **)(v8 + 8));
                v15 = _mm_load_si128((const __m128i *)&xmmword_1800E6B60).m128i_u32[0];
                v0 = qword_18010C470;
              }
              v27[658] = v27[28];
              v27[657] = v8;
            }
            v28 = *(float *)(v8 + 552) - *(float *)(v8 + 544);
            v29 = *(float *)(v8 + 704) + *(float *)(v8 + 704);
            *(_DWORD *)(v8 + 176) = 0;
            *(_DWORD *)(v8 + 184) = 0;
            *(float *)(v8 + 168) = *(float *)(v8 + 152) - (float)((float)(int)fminf(v29, v28 * 0.67000002) * v17);
            *(_DWORD *)(v1 + 5276) = *(_DWORD *)(v1 + 5032);
          }
        }
        if ( v26 )
        {
          *(float *)(v0 + 5280) = fminf(
                                    (float)(COERCE_FLOAT(LODWORD(v18) & v15) * 0.69999999) + *(float *)(v0 + 5280),
                                    0.69999999);
          if ( *(_QWORD *)(v0 + 5256) != v8 )
          {
            if ( *(char *)(v0 + 10228) < 0 )
              sub_180052F00("[io] LockWheelingWindow() \"%s\"\n", *(const char **)(v8 + 8));
            *(_QWORD *)(v0 + 5264) = *(_QWORD *)(v0 + 224);
            *(_QWORD *)(v0 + 5256) = v8;
          }
          v30 = *(float *)(v8 + 556) - *(float *)(v8 + 548);
          v31 = *(float *)(v8 + 704) * 5.0;
          *(_DWORD *)(v8 + 180) = 0;
          *(_DWORD *)(v8 + 188) = 0;
          *(float *)(v8 + 172) = *(float *)(v8 + 156) - (float)((float)(int)fminf(v31, v30 * 0.67000002) * v18);
          *(_DWORD *)(v1 + 5276) = *(_DWORD *)(v1 + 5032);
        }
      }
      return;
    }
    if ( v19 == v8 )
    {
      if ( v8 )
        goto LABEL_66;
    }
    else if ( v8 )
    {
      if ( *(_DWORD *)(v0 + 5272) == -1 )
      {
        v22 = 5032;
        *(_DWORD *)(v0 + 5272) = *(_DWORD *)(v0 + 5032);
      }
      else
      {
        v22 = 5272;
      }
      if ( (*(_DWORD *)(v22 + v0) != *(_DWORD *)(v0 + 5032) || v17 == 0.0 || v18 == 0.0)
        && (v23 = *(float *)(v0 + 5296), v24 = *(float *)(v0 + 5292), v24 != v23) )
      {
        if ( v24 > v23 )
          v8 = v19;
      }
      else
      {
        *(float *)(v0 + 5284) = v17;
        v8 = 0;
        *(float *)(v0 + 5288) = v18;
      }
LABEL_65:
      if ( !v8 )
        return;
      goto LABEL_66;
    }
    v8 = v19;
    goto LABEL_65;
  }
}
