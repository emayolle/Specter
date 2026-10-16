// sub_1800B7240 size=155
float __fastcall sub_1800B7240(float a1)
{
  __m128i v2; // xmm0
  __int64 v3; // rdx

  v2 = 0;
  *(float *)v2.m128i_i32 = a1;
  v3 = (unsigned int)_mm_cvtsi128_si32(v2);
  if ( (v3 & 0x7F800000) != 0x7F800000 )
    goto LABEL_6;
  if ( (v3 & 0x7FFFFF) == 0 )
  {
    if ( (int)v3 < 0 )
    {
LABEL_5:
      sub_1800B2F60((unsigned int)"sqrtf", 5, -4194304, 1, 8, 33, LODWORD(a1), 0, 1);
      v2.m128i_i32[0] = 0;
      return *(float *)v2.m128i_i32;
    }
LABEL_6:
    if ( (v3 & 0x7FFFFFFF) == 0 || (int)v3 >= 0 )
    {
      *(float *)v2.m128i_i32 = fsqrt(a1);
      return *(float *)v2.m128i_i32;
    }
    goto LABEL_5;
  }
  sub_1800B30C0((unsigned int)v3, v3);
  return *(float *)v2.m128i_i32;
}
