// sub_1800B3CC0 size=540
// local variable allocation has failed, the output may be wrong!
double __fastcall sub_1800B3CC0(double result)
{
  __m128i v1; // xmm5
  __int64 v2; // rcx
  __int64 v3; // rdx
  __m128 v4; // xmm3
  __m128i v5; // xmm4
  float v6; // xmm6_4
  __m128d v7; // xmm0
  float v8; // eax
  __m128d v9; // xmm2

  v1 = 0;
  v2 = (unsigned int)_mm_cvtsi128_si32(*(__m128i *)&result);
  v3 = (unsigned __int8)((unsigned int)v2 >> 23);
  if ( ((unsigned int)v2 & 0x7FFFFFFF) <= 0x7F800000 )
  {
    if ( (unsigned int)v3 >= 0x65 )
    {
      if ( (unsigned int)v3 < 0x7F )
      {
        v4 = *(__m128 *)&result;
        if ( (int)v2 < 0 )
          v4 = _mm_xor_ps(*(__m128 *)&result, (__m128)xmmword_1800E6B90);
        if ( (unsigned int)v3 < 0x7E )
        {
          *(float *)v5.m128i_i32 = v4.m128_f32[0] * v4.m128_f32[0];
        }
        else
        {
          v5 = (__m128i)0x3F800000u;
          *(float *)v5.m128i_i32 = (float)(1.0 - v4.m128_f32[0]) * 0.5;
          v1 = v5;
          *(float *)v1.m128i_i32 = fsqrt(*(float *)v5.m128i_i32);
          v4 = (__m128)v1;
        }
        v6 = (float)((float)((float)((float)((float)((float)(-0.013381929
                                                           - (float)(*(float *)v5.m128i_i32 * 0.0039613745))
                                                   * *(float *)v5.m128i_i32)
                                           - 0.056529868)
                                   * *(float *)v5.m128i_i32)
                           + 0.1841616)
                   * *(float *)v5.m128i_i32)
           / (float)(1.1049696 - (float)(*(float *)v5.m128i_i32 * 0.8364113));
        if ( (unsigned int)v3 < 0x7E )
        {
          v9 = (__m128d)0x3FF921FB54442D18uLL;
          v9.m128d_f64[0] = 1.570796326794897
                          - (*(float *)&result
                           - (6.123233995736766e-17
                            - (float)(v6 * *(float *)&result)));
          *(__m128 *)&result = _mm_cvtpd_ps(v9);
        }
        else if ( (int)v2 >= 0 )
        {
          LODWORD(v8) = _mm_cvtsi128_si32(v1) & 0xFFFF0000;
          v4.m128_f32[0] = (float)((float)((float)(v4.m128_f32[0] + v4.m128_f32[0]) * v6)
                                 + (float)((float)((float)(*(float *)v5.m128i_i32 - (float)(v8 * v8))
                                                 / (float)(v8 + *(float *)v1.m128i_i32))
                                         + (float)((float)(*(float *)v5.m128i_i32 - (float)(v8 * v8))
                                                 / (float)(v8 + *(float *)v1.m128i_i32))))
                         + (float)(v8 + v8);
          *(__m128 *)&result = v4;
        }
        else
        {
          v7 = (__m128d)0x400921FB54442D18uLL;
          v7.m128d_f64[0] = 3.141592653589793
                          - ((float)(v4.m128_f32[0] * v6)
                           - 6.123233995736766e-17
                           + *(float *)v1.m128i_i32
                           + (float)(v4.m128_f32[0] * v6)
                           - 6.123233995736766e-17
                           + *(float *)v1.m128i_i32);
          *(__m128 *)&result = _mm_cvtpd_ps(v7);
        }
      }
      else if ( *(float *)&result == 1.0 )
      {
        *(_OWORD *)&result = 0;
      }
      else if ( *(float *)&result == -1.0 )
      {
        sub_1800B34C0(32);
        *(_OWORD *)&result = 0x40490FDBu;
      }
      else
      {
        sub_1800B2F60((unsigned int)"acosf", 13, -4194304, 1, 8, 33, LODWORD(result), 0, 1);
      }
    }
    else
    {
      sub_1800B34C0(32);
      *(_OWORD *)&result = 0x3FC90FDBu;
    }
  }
  else
  {
    sub_1800B30C0(v2, v3);
  }
  return result;
}
