// sub_1800717F0 size=1681
char __fastcall sub_1800717F0(_BYTE *a1, char a2)
{
  __int64 v2; // rdi
  __int64 v5; // rsi
  unsigned int v6; // eax
  int v7; // r9d
  unsigned int v8; // ebx
  float v9; // xmm15_4
  float v10; // xmm9_4
  float v11; // xmm7_4
  float v12; // xmm1_4
  float v13; // xmm6_4
  float v14; // xmm0_4
  char v15; // al
  float v16; // xmm8_4
  float v17; // xmm12_4
  float v18; // xmm13_4
  __int64 v19; // rbx
  int v20; // r12d
  __int64 v21; // rax
  int v22; // eax
  int v23; // r8d
  int v24; // r8d
  unsigned int v25; // eax
  unsigned int v26; // r14d
  float v27; // xmm1_4
  __int64 v28; // rbx
  float v29; // xmm6_4
  __m128 v30; // xmm0
  int v31; // eax
  int v32; // r8d
  int v33; // eax
  int v34; // r8d
  bool v35; // zf
  float v36; // xmm7_4
  __int64 v37; // r14
  const char *v38; // rsi
  _BYTE *v39; // rdi
  const char *v40; // rbx
  _BYTE *v41; // r12
  __int64 v42; // r15
  float v43; // xmm1_4
  float v44; // xmm0_4
  __int64 v45; // rax
  int v46; // eax
  __int64 v47; // rax
  const char *v48; // rdi
  __int64 v49; // rax
  char v51; // [rsp+38h] [rbp-D0h]
  __int64 v52; // [rsp+40h] [rbp-C8h] BYREF
  float v53; // [rsp+48h] [rbp-C0h] BYREF
  float v54; // [rsp+4Ch] [rbp-BCh]
  __m128 v55; // [rsp+50h] [rbp-B8h] BYREF
  _DWORD v56[2]; // [rsp+60h] [rbp-A8h] BYREF
  float v57; // [rsp+68h] [rbp-A0h]
  float v58; // [rsp+6Ch] [rbp-9Ch]
  __m128 v59[3]; // [rsp+70h] [rbp-98h] BYREF
  char v60; // [rsp+178h] [rbp+70h] BYREF
  char v61; // [rsp+180h] [rbp+78h] BYREF

  v2 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v5 = *(_QWORD *)(v2 + 5216);
  if ( *(_BYTE *)(v5 + 209) )
    return 0;
  v6 = sub_1800465E0(*(_QWORD *)(v2 + 5216), a1);
  LOBYTE(v7) = 1;
  v8 = v6;
  sub_18003DF30((unsigned int)&v53, (_DWORD)a1, 0, v7, -1082130432);
  v9 = v53;
  v10 = *(float *)(v5 + 280);
  v11 = *(float *)(v5 + 284);
  v12 = (float)(*(float *)(v2 + 3216) + *(float *)(v2 + 3216)) + v54;
  v13 = (float)(*(float *)(qword_18010C470 + 3216) + *(float *)(qword_18010C470 + 3216))
      + *(float *)(qword_18010C470 + 4432);
  v14 = v53 <= 0.0 ? 0.0 : v53 + *(float *)(v2 + 3236);
  v56[0] = *(_DWORD *)(v5 + 280);
  *(float *)&v56[1] = v11;
  v58 = v12 + v11;
  v54 = (float)(v12 + v11) - v11;
  v57 = (float)(v14 + v13) + v10;
  v53 = v57 - v10;
  sub_18004AAD0(&v53);
  sub_18004A070(v56, v8, 0, 0);
  if ( !v15 )
    return 0;
  v16 = v10 + v13;
  v17 = (float)(int)(float)((float)((float)((float)(v10 + v13) + v10) * 0.5) + 0.5);
  v53 = v17;
  v18 = (float)(int)(float)((float)((float)((float)(v11 + v13) + v11) * 0.5) + 0.5);
  v54 = v18;
  v51 = sub_18006F740((unsigned int)v56, v8, (unsigned int)&v60, (unsigned int)&v61, 0);
  if ( v51 )
    sub_18003A1B0(v8);
  sub_180038770(v56, v8, 0);
  v19 = *(_QWORD *)(v5 + 712);
  v20 = sub_18005A550(v19);
  if ( v61 && v60 )
    v21 = 9;
  else
    v21 = (v60 != 0) + 7LL;
  v55 = *(__m128 *)(qword_18010C470 + 16 * (v21 + 18) + 3136);
  v55.m128_f32[3] = _mm_shuffle_ps(v55, v55, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
  sub_180036620(&v55);
  sub_18005CF60(v19, (unsigned int)&v53, v23, v22, v20);
  if ( a2 )
  {
    v55 = *(__m128 *)(qword_18010C470 + 3712);
    v55.m128_f32[3] = _mm_shuffle_ps(v55, v55, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    sub_180036620(&v55);
    v26 = v25;
    v27 = fmaxf(1.0, (float)(int)(float)(v13 / 6.0));
    if ( (v25 & 0xFF000000) != 0 && (float)((float)((float)(v13 - 1.0) * 0.5) - v27) >= 0.5 )
    {
      v28 = *(_QWORD *)(v5 + 712);
      sub_18005BB80(v28, (unsigned int)&v53, v24, 0, 48);
      --*(_DWORD *)(v28 + 80);
      sub_180034630(v28, v26);
    }
  }
  v29 = *(float *)(v2 + 3224);
  if ( v29 > 0.0 )
  {
    v30 = *(__m128 *)(qword_18010C470 + 3520);
    v55.m128_f32[0] = v17 + 1.0;
    v59[0] = v30;
    v30.m128_f32[0] = _mm_shuffle_ps(v30, v30, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    v55.m128_f32[1] = v18 + 1.0;
    v59[0].m128_i32[3] = v30.m128_i32[0];
    sub_180036620(v59);
    sub_18005CE80(*(_QWORD *)(v5 + 712), (unsigned int)&v55, v32, v31, v20, LODWORD(v29));
    v59[0] = *(__m128 *)(qword_18010C470 + 3504);
    v59[0].m128_f32[3] = _mm_shuffle_ps(v59[0], v59[0], 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    sub_180036620(v59);
    sub_18005CE80(*(_QWORD *)(v5 + 712), (unsigned int)&v53, v34, v33, v20, *(_DWORD *)(v2 + 3224));
  }
  v35 = *(_BYTE *)(v2 + 10080) == 0;
  v36 = v11 + *(float *)(v2 + 3216);
  *(float *)&v52 = v16 + *(float *)(v2 + 3236);
  *((float *)&v52 + 1) = v36;
  if ( !v35 )
  {
    v37 = qword_18010C470;
    v38 = "( )";
    if ( a2 )
      v38 = "(x)";
    v39 = *(_BYTE **)(qword_18010C470 + 10120);
    v40 = v38;
    v41 = *(_BYTE **)(qword_18010C470 + 10128);
    v42 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    for ( *(_QWORD *)(v37 + 10120) = 0; v40 != (const char *)-1LL; ++v40 )
    {
      if ( !*v40 || *v40 == 35 && v40[1] == 35 )
        break;
    }
    v43 = *((float *)&v52 + 1);
    v44 = *(float *)(v37 + 3216) + *(float *)(v37 + 10136);
    *(_DWORD *)(v37 + 10136) = HIDWORD(v52);
    if ( v43 > (float)(v44 + 1.0) )
    {
      sub_180051790("\r\n");
      *(_BYTE *)(v37 + 10140) = 1;
    }
    if ( v39 )
    {
      v45 = sub_1800B9730(v39);
      sub_180051A10((__int64)&v52, v39, &v39[v45]);
    }
    v46 = *(_DWORD *)(v42 + 416);
    if ( *(_DWORD *)(v37 + 10144) > v46 )
      *(_DWORD *)(v37 + 10144) = v46;
    while ( 1 )
    {
      v47 = sub_1800B8A30(v38, 10, v40 - v38);
      v48 = v40;
      if ( v47 )
        v48 = (const char *)v47;
      if ( v38 == v48 && v48 == v40 )
        break;
      sub_180051790("%*s%.*s");
      *(_BYTE *)(v37 + 10140) = 0;
      if ( *v48 == 10 )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v37 + 10140) = 1;
      }
      if ( v48 == v40 )
        break;
      v38 = v48 + 1;
    }
    if ( v41 )
    {
      v49 = sub_1800B9730(v41);
      sub_180051A10((__int64)&v52, v41, &v41[v49]);
    }
  }
  if ( v9 > 0.0 )
    sub_180037440(v52, a1, nullptr, 1);
  return v51;
}
