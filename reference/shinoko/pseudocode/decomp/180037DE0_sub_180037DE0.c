// sub_180037DE0 size=1667
__int64 __fastcall sub_180037DE0(__int64 a1, float *a2, float *a3, __int64 a4, __int64 *a5, __int64 *a6, __int64 *a7)
{
  __int64 *i; // rbx
  __int64 *v9; // rsi
  unsigned __int64 *v12; // rax
  unsigned __int64 v13; // xmm10_8
  float v14; // xmm0_4
  __int64 v15; // r15
  int v16; // r8d
  int v17; // r9d
  __int64 v18; // r14
  __int64 v19; // rax
  float *v20; // r14
  int v21; // r8d
  __int64 v22; // r9
  float j; // xmm7_4
  char v24; // al
  float v25; // xmm8_4
  int v26; // eax
  int v27; // r8d
  __int64 v28; // r9
  int v29; // eax
  int v30; // r8d
  __int64 v31; // r9
  unsigned int v32; // xmm1_4
  float v33; // xmm2_4
  float v34; // xmm3_4
  int v35; // xmm1_4
  __m128 v36; // xmm0
  int v37; // eax
  int v38; // r8d
  __int64 result; // rax
  __int64 v40; // r14
  __int64 v41; // r15
  __int64 v42; // r12
  __int64 v43; // r13
  float v44; // xmm1_4
  float v45; // xmm0_4
  __int64 v46; // rax
  int v47; // eax
  __int64 *v48; // rdi
  __int64 v49; // rax
  __m128 v50; // [rsp+68h] [rbp-71h] BYREF
  __int64 v51; // [rsp+78h] [rbp-61h] BYREF
  __int128 v52; // [rsp+80h] [rbp-59h] BYREF
  __int128 v53; // [rsp+90h] [rbp-49h]
  float *v55; // [rsp+138h] [rbp+5Fh] BYREF

  v55 = a3;
  i = a6;
  v9 = a5;
  *(_QWORD *)&v53 = qword_18010C470;
  if ( !a6 )
  {
    for ( i = a5; i != (__int64 *)-1LL; i = (__int64 *)((char *)i + 1) )
    {
      if ( !*(_BYTE *)i || *(_BYTE *)i == 35 && *((_BYTE *)i + 1) == 35 )
        break;
    }
  }
  if ( a7 )
  {
    v12 = (unsigned __int64 *)&v51;
    v51 = *a7;
  }
  else
  {
    sub_18003DF30((unsigned int)&a6, (_DWORD)a5, (_DWORD)i, 0, 0);
  }
  v13 = *v12;
  v14 = *a3 - *a2;
  v50.m128_u64[0] = v13;
  if ( *(float *)&v13 <= v14 )
  {
    v55 = nullptr;
    sub_180037740(a1, (_DWORD)a2, (_DWORD)a3, (_DWORD)v9, (__int64)i, (__int64)&v50, (__int64)&v55, 0);
  }
  else
  {
    v15 = *(_QWORD *)(*(_QWORD *)(a1 + 56) + 24LL);
    a7 = nullptr;
    v18 = sub_180066070(v15);
    v19 = *(unsigned __int16 *)(v15 + 48);
    if ( (int)v19 >= *(_DWORD *)v18 || *(float *)(*(_QWORD *)(v18 + 8) + 4 * v19) < 0.0 )
    {
      if ( *(float *)(v18 + 20) >= 128.0 || (*(_DWORD *)(v18 + 76) & 0x10000000) != 0 )
      {
        LODWORD(a6) = 0;
        sub_180062410(v18, (unsigned __int16)v19, &a6);
      }
      else
      {
        sub_180062410(v18, (unsigned __int16)v19, 0);
      }
    }
    v20 = v55;
    sub_180066D80((unsigned int)&a6, v15, v16, v17, 0, (__int64)v9, (__int64)i, (__int64)i, (__int64)&a7, 0, 0);
    v22 = (__int64)a7;
    for ( j = *(float *)&a6; a7 > v9; j = j - *(float *)&v52 )
    {
      v24 = *(_BYTE *)(v22 - 1);
      if ( v24 != 32 && v24 != 9 )
        break;
      a7 = (__int64 *)(v22 - 1);
      sub_180066D80((unsigned int)&v52, v15, v21, v22, 0, v22 - 1, v22, v22, 0, 0, 0);
      v22 = (__int64)a7;
    }
    v25 = v20[1];
    v55 = *(float **)a2;
    if ( (float)(*(float *)&v55 + *(float *)&v13) >= *v20 || (float)(v50.m128_f32[1] + *((float *)&v55 + 1)) >= v25 )
    {
      v50 = *(__m128 *)(qword_18010C470 + 3424);
      v50.m128_f32[3] = _mm_shuffle_ps(v50, v50, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      v29 = ((__int64 (__fastcall *)(__m128 *))sub_180036620)(&v50);
      if ( (v29 & 0xFF000000) != 0 && v9 != (__int64 *)v31 && *(_BYTE *)v9 )
      {
        v52 = *(_OWORD *)(a1 + 96);
        *(float *)&v32 = fminf(*((float *)&v52 + 2), *v20);
        LODWORD(v52) = fmaxf(*(float *)&v52, *a2);
        *(_QWORD *)((char *)&v52 + 4) = __PAIR64__(v32, COERCE_UNSIGNED_INT(fmaxf(*((float *)&v52 + 1), a2[1])));
        HIDWORD(v52) = fminf(*((float *)&v52 + 3), v25);
        sub_180067670(
          *(_QWORD *)(*(_QWORD *)(a1 + 56) + 24LL),
          a1,
          v30,
          (unsigned int)&v55,
          v29,
          (__int64)&v52,
          (__int64)v9,
          v31,
          0,
          1);
      }
    }
    else
    {
      v50 = *(__m128 *)(qword_18010C470 + 3424);
      v50.m128_f32[3] = _mm_shuffle_ps(v50, v50, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      v26 = ((__int64 (__fastcall *)(__m128 *))sub_180036620)(&v50);
      if ( (v26 & 0xFF000000) != 0 && v9 != (__int64 *)v28 && *(_BYTE *)v9 )
      {
        v52 = *(_OWORD *)(a1 + 96);
        sub_180067670(
          *(_QWORD *)(*(_QWORD *)(a1 + 56) + 24LL),
          a1,
          v27,
          (unsigned int)&v55,
          v26,
          (__int64)&v52,
          (__int64)v9,
          v28,
          0,
          0);
      }
    }
    v33 = *a2;
    v34 = a2[1];
    v35 = *((_DWORD *)v20 + 1);
    *((float *)&v52 + 2) = *v20;
    HIDWORD(v52) = v35;
    *(_QWORD *)&v52 = __PAIR64__(LODWORD(v34), LODWORD(v33));
    *(float *)&v55 = (float)(int)(float)(v33 + j);
    v36 = *(__m128 *)(qword_18010C470 + 3424);
    *((float *)&v55 + 1) = (float)(int)v34;
    v50 = v36;
    v50.m128_f32[3] = _mm_shuffle_ps(v36, v36, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    sub_180036620(&v50);
    sub_180067360(v15, a1, v38, (unsigned int)&v55, v37, *(_WORD *)(v15 + 48), (__int64)&v52);
  }
  result = v53;
  if ( *(_BYTE *)(v53 + 10080) )
  {
    v40 = qword_18010C470;
    v41 = *(_QWORD *)(qword_18010C470 + 10120);
    v42 = *(_QWORD *)(qword_18010C470 + 10128);
    v43 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    *(_QWORD *)(v40 + 10120) = 0;
    if ( !i )
    {
      for ( i = v9; i != (__int64 *)-1LL; i = (__int64 *)((char *)i + 1) )
      {
        if ( !*(_BYTE *)i || *(_BYTE *)i == 35 && *((_BYTE *)i + 1) == 35 )
          break;
      }
    }
    v44 = *(float *)(v40 + 3216) + *(float *)(v40 + 10136);
    v45 = a2[1];
    *(float *)(v40 + 10136) = v45;
    if ( v45 > (float)(v44 + 1.0) )
    {
      sub_180051790("\r\n");
      *(_BYTE *)(v40 + 10140) = 1;
    }
    if ( v41 )
    {
      v46 = sub_1800B9730(v41);
      sub_180051A10(a2, v41, v46 + v41);
    }
    v47 = *(_DWORD *)(v43 + 416);
    if ( *(_DWORD *)(v40 + 10144) > v47 )
      *(_DWORD *)(v40 + 10144) = v47;
    while ( 1 )
    {
      result = sub_1800B8A30(v9, 10, (char *)i - (char *)v9);
      v48 = i;
      if ( result )
        v48 = (__int64 *)result;
      if ( v9 == v48 && v48 == i )
        break;
      result = sub_180051790("%*s%.*s");
      *(_BYTE *)(v40 + 10140) = 0;
      if ( *(_BYTE *)v48 == 10 )
      {
        result = sub_180051790("\r\n");
        *(_BYTE *)(v40 + 10140) = 1;
      }
      if ( v48 == i )
        break;
      v9 = (__int64 *)((char *)v48 + 1);
    }
    if ( v42 )
    {
      v49 = sub_1800B9730(v42);
      return sub_180051A10(a2, v42, v49 + v42);
    }
  }
  return result;
}
