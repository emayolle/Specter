// sub_180037980 size=1119
void __fastcall sub_180037980(float *a1, float *a2, _BYTE *a3, unsigned __int64 a4, __int64 *a5, float *a6, float *a7)
{
  _BYTE *i; // rbx
  _BYTE *v8; // rsi
  unsigned __int64 v9; // r8
  float *v11; // r11
  __m128 *v12; // r14
  __int64 v13; // r13
  __int64 v14; // xmm6_8
  __int64 v15; // rax
  __m128 *v16; // rdi
  float *v17; // rax
  float v18; // xmm3_4
  float v19; // xmm4_4
  float *v20; // r9
  float *v21; // r10
  char v22; // cl
  bool v23; // al
  float v24; // xmm2_4
  int v25; // eax
  int v26; // r8d
  float *v27; // r9
  float *v28; // r10
  float *v29; // r11
  unsigned int v30; // xmm1_4
  int v31; // eax
  int v32; // r8d
  unsigned __int64 v33; // rdi
  unsigned __int64 v34; // r15
  unsigned __int64 v35; // r12
  float v36; // xmm1_4
  float v37; // xmm0_4
  __int64 v38; // rax
  float *v39; // r13
  __int32 v40; // eax
  __int64 v41; // rax
  _BYTE *v42; // rdi
  __int64 v43; // rax
  __int64 v44; // [rsp+50h] [rbp-31h] BYREF
  __m128 v45; // [rsp+58h] [rbp-29h] BYREF
  __int64 v47; // [rsp+E0h] [rbp+5Fh] BYREF
  char v48; // [rsp+E8h] [rbp+67h] BYREF

  i = a3;
  v8 = a3;
  v9 = -1;
  v11 = a1;
  if ( a4 )
    v9 = a4;
  for ( ; (unsigned __int64)i < v9; ++i )
  {
    if ( !*i || *i == 35 && i[1] == 35 )
      break;
  }
  if ( (_DWORD)i != (_DWORD)v8 )
  {
    v12 = (__m128 *)qword_18010C470;
    v13 = qword_18010C470;
    v14 = *(_QWORD *)a1;
    v15 = *(_QWORD *)(qword_18010C470 + 5216);
    v47 = *(_QWORD *)a1;
    v16 = *(__m128 **)(v15 + 712);
    if ( a5 )
    {
      v17 = (float *)&v44;
      v44 = *a5;
    }
    else
    {
      sub_18003DF30((unsigned int)&v48, (_DWORD)v8, (_DWORD)i, 0, 0);
      v11 = a1;
      v12 = (__m128 *)qword_18010C470;
    }
    v18 = *v17;
    v19 = v17[1];
    v20 = a7;
    if ( !a7 )
      v20 = v11;
    v21 = a7 + 2;
    if ( !a7 )
      v21 = a2;
    v22 = (float)(v18 + *(float *)&v14) >= *v21 || (float)(v19 + *((float *)&v47 + 1)) >= v21[1];
    if ( a7 )
    {
      v23 = *v20 > *(float *)&v14 || v20[1] > *((float *)&v47 + 1);
      v22 |= v23;
    }
    if ( *a6 > 0.0 )
      LODWORD(v47) = fmaxf(*(float *)&v14, (float)((float)((float)(*a2 - *(float *)&v14) - v18) * *a6) + *(float *)&v14);
    v24 = a6[1];
    if ( v24 > 0.0 )
      HIDWORD(v47) = fmaxf(
                       *((float *)&v47 + 1),
                       (float)((float)((float)(a2[1] - *((float *)&v47 + 1)) - v19) * v24) + *((float *)&v47 + 1));
    v45 = v12[214];
    v45.m128_f32[3] = _mm_shuffle_ps(v45, v45, 255).m128_f32[0] * v12[196].m128_f32[3];
    if ( v22 )
    {
      v25 = sub_180036620(&v45);
      if ( (v25 & 0xFF000000) != 0 && v8 != i && *v8 )
      {
        v45 = v16[6];
        *(float *)&v30 = fminf(v45.m128_f32[2], *v28);
        v45.m128_i32[0] = fmaxf(v45.m128_f32[0], *v27);
        *(unsigned __int64 *)((char *)v45.m128_u64 + 4) = __PAIR64__(
                                                            v30,
                                                            COERCE_UNSIGNED_INT(fmaxf(v45.m128_f32[1], v27[1])));
        v45.m128_i32[3] = fminf(v45.m128_f32[3], v28[1]);
        sub_180067670(
          *(_QWORD *)(v16[3].m128_u64[1] + 24),
          (_DWORD)v16,
          v26,
          (unsigned int)&v47,
          v25,
          (__int64)&v45,
          (__int64)v8,
          (__int64)i,
          0,
          1);
LABEL_39:
        v29 = a1;
        v12 = (__m128 *)qword_18010C470;
      }
    }
    else
    {
      v31 = sub_180036620(&v45);
      if ( (v31 & 0xFF000000) != 0 && v8 != i && *v8 )
      {
        v45 = v16[6];
        sub_180067670(
          *(_QWORD *)(v16[3].m128_u64[1] + 24),
          (_DWORD)v16,
          v32,
          (unsigned int)&v47,
          v31,
          (__int64)&v45,
          (__int64)v8,
          (__int64)i,
          0,
          0);
        goto LABEL_39;
      }
    }
    if ( *(_BYTE *)(v13 + 10080) )
    {
      v33 = v12[632].m128_u64[1];
      v34 = v12[326].m128_u64[0];
      v35 = v12[633].m128_u64[0];
      v12[633].m128_u64[0] = 0;
      v12[632].m128_u64[1] = 0;
      if ( !i )
      {
        for ( i = v8; i != (_BYTE *)-1LL; ++i )
        {
          if ( !*i || *i == 35 && i[1] == 35 )
            break;
        }
      }
      v36 = v12[201].m128_f32[0] + v12[633].m128_f32[2];
      v37 = v29[1];
      v12[633].m128_f32[2] = v37;
      if ( v37 > (float)(v36 + 1.0) )
      {
        sub_180051790("\r\n");
        v12[633].m128_i8[12] = 1;
      }
      if ( v33 )
      {
        v38 = sub_1800B9730(v33);
        v39 = a1;
        sub_180051A10(a1, v33, v38 + v33);
      }
      else
      {
        v39 = a1;
      }
      v40 = *(_DWORD *)(v34 + 416);
      if ( v12[634].m128_i32[0] > v40 )
        v12[634].m128_i32[0] = v40;
      while ( 1 )
      {
        v41 = sub_1800B8A30(v8, 10, i - v8);
        v42 = i;
        if ( v41 )
          v42 = (_BYTE *)v41;
        if ( v8 == v42 && v42 == i )
          break;
        sub_180051790("%*s%.*s");
        v12[633].m128_i8[12] = 0;
        if ( *v42 == 10 )
        {
          sub_180051790("\r\n");
          v12[633].m128_i8[12] = 1;
        }
        if ( v42 == i )
          break;
        v8 = v42 + 1;
      }
      if ( v35 )
      {
        v43 = sub_1800B9730(v35);
        sub_180051A10(v39, v35, v43 + v35);
      }
    }
  }
}
