// sub_180072E10 size=2174
char __fastcall sub_180072E10(__int64 a1, __int64 a2, int a3)
{
  __int64 v3; // rsi
  __int64 v4; // r15
  int v5; // r13d
  unsigned int v6; // eax
  int v7; // r9d
  unsigned int v8; // r14d
  float v9; // xmm6_4
  float v10; // xmm2_4
  float v11; // xmm3_4
  float v12; // xmm1_4
  float v13; // xmm4_4
  float v14; // xmm0_4
  char v15; // al
  char v16; // al
  char *v17; // rdx
  unsigned int v18; // ebx
  char v19; // r10
  unsigned __int8 v20; // r8
  __int64 v21; // rax
  unsigned int v22; // ebx
  __int64 v23; // rax
  bool v24; // di
  float v25; // xmm7_4
  __int64 v26; // rcx
  float v27; // xmm1_4
  unsigned int v28; // eax
  unsigned int v29; // r12d
  int v30; // eax
  int v31; // r10d
  __int64 v32; // r14
  float v33; // xmm4_4
  float v34; // xmm0_4
  float v35; // xmm4_4
  float v36; // xmm5_4
  float v37; // xmm3_4
  __m128 v38; // xmm1
  __m128 v39; // xmm0
  __int64 v40; // rdi
  __int64 v41; // rax
  int v42; // edx
  float v43; // xmm4_4
  float v44; // xmm0_4
  unsigned __int64 v45; // rdx
  unsigned __int8 v46; // al
  unsigned __int8 *v47; // r8
  unsigned int i; // ecx
  __int64 v49; // rax
  __int64 v50; // rbx
  __int64 v51; // rcx
  __int32 v52; // edx
  float v53; // xmm7_4
  float v54; // xmm9_4
  float v55; // xmm6_4
  float v56; // xmm5_4
  float v57; // xmm12_4
  float v58; // xmm13_4
  int v59; // ecx
  float v60; // xmm10_4
  float v61; // xmm11_4
  __int32 v62; // eax
  float v63; // xmm1_4
  float v64; // xmm2_4
  __int64 v65; // rax
  bool v66; // bl
  __m128 si128; // [rsp+38h] [rbp-A9h] BYREF
  __m128 v69; // [rsp+48h] [rbp-99h] BYREF
  __int64 v70; // [rsp+58h] [rbp-89h] BYREF
  __int64 v71; // [rsp+60h] [rbp-81h] BYREF
  unsigned __int8 v72; // [rsp+68h] [rbp-79h] BYREF
  char v73; // [rsp+69h] [rbp-78h] BYREF
  __int64 v74; // [rsp+148h] [rbp+67h] BYREF
  __int64 v75; // [rsp+150h] [rbp+6Fh] BYREF
  int v76; // [rsp+158h] [rbp+77h] BYREF
  unsigned __int64 v77; // [rsp+160h] [rbp+7Fh] BYREF

  v76 = a3;
  v75 = a2;
  v74 = a1;
  v3 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v4 = *(_QWORD *)(v3 + 5216);
  v5 = *(_DWORD *)(v3 + 7824);
  *(_DWORD *)(v3 + 7824) = 0;
  if ( *(_BYTE *)(v4 + 209) )
    return 0;
  v6 = sub_1800465E0(v4, "##v");
  LOBYTE(v7) = 1;
  v8 = v6;
  v9 = (float)(*(float *)(qword_18010C470 + 3216) + *(float *)(qword_18010C470 + 3216))
     + *(float *)(qword_18010C470 + 4432);
  sub_18003DF30((unsigned int)&v74, (unsigned int)"##v", 0, v7, -1082130432);
  v10 = *(float *)(v4 + 280);
  v11 = v10 + v9;
  v12 = (float)((float)(*(float *)(v3 + 3216) + *(float *)(v3 + 3216)) + *((float *)&v74 + 1)) + *(float *)(v4 + 284);
  *(float *)&v70 = v10;
  v13 = *(float *)(v4 + 284);
  *((float *)&v70 + 1) = v13;
  *(float *)&v71 = v10 + v9;
  *((float *)&v71 + 1) = v12;
  v14 = *(float *)&v74 <= 0.0 ? 0.0 : *(float *)&v74 + *(float *)(v3 + 3236);
  v69.m128_u64[0] = __PAIR64__(LODWORD(v13), LODWORD(v10));
  v69.m128_f32[3] = v12 + 0.0;
  v69.m128_f32[2] = v14 + v11;
  *((float *)&v77 + 1) = (float)(v12 + 0.0) - v13;
  *(float *)&v77 = (float)(v14 + v11) - v10;
  sub_18004AAD0(&v77);
  sub_18004A070(&v69, v8, &v70, 0);
  if ( !v15 )
    return 0;
  v16 = sub_18006F740((unsigned int)&v70, v8, (unsigned int)&v76, (unsigned int)&v75, 0);
  v17 = "#ComboPopup";
  v18 = ~v8;
  v19 = v16;
  v20 = 35;
  do
  {
    if ( v20 == 35 && *v17 == 35 && v17[1] == 35 )
      v18 = ~v8;
    v21 = v20;
    v20 = *v17++;
    v18 = dword_1800D56B0[v21 ^ (unsigned __int8)v18] ^ (v18 >> 8);
  }
  while ( v20 );
  v22 = ~v18;
  v23 = *(int *)(qword_18010C470 + 8064);
  v24 = *(_DWORD *)(qword_18010C470 + 8048) > (int)v23
     && *(_DWORD *)(56 * v23 + *(_QWORD *)(qword_18010C470 + 8056)) == v22;
  if ( v19 )
  {
    if ( !v24 )
    {
      sub_18004BEE0(v22, 0);
      v24 = 1;
    }
    v25 = fmaxf(*(float *)&v70, *(float *)&v71 - v9);
    sub_180038770(&v70, v8, 0);
    goto LABEL_22;
  }
  v25 = fmaxf(*(float *)&v70, *(float *)&v71 - v9);
  sub_180038770(&v70, v8, 0);
  if ( v24 || (v26 = 624, (_BYTE)v76) )
LABEL_22:
    v26 = 640;
  v27 = *(float *)(qword_18010C470 + 3148);
  si128 = *(__m128 *)(v26 + qword_18010C470 + 3136);
  si128.m128_f32[3] = _mm_shuffle_ps(si128, si128, 255).m128_f32[0] * v27;
  v69 = *(__m128 *)(qword_18010C470 + 3424);
  v69.m128_f32[3] = _mm_shuffle_ps(v69, v69, 255).m128_f32[0] * v27;
  sub_180036620(&v69);
  v29 = v28;
  v77 = __PAIR64__(HIDWORD(v70), LODWORD(v25));
  sub_180036620(&si128);
  sub_18005C870(*(_QWORD *)(v4 + 712), (unsigned int)&v77, (unsigned int)&v71, v30, *(_DWORD *)(v3 + 3220), v31);
  if ( *(float *)&v71 >= (float)((float)(v9 + v25) - *(float *)(v3 + 3212)) )
  {
    v32 = *(_QWORD *)(v4 + 712);
    v33 = *(float *)(*(_QWORD *)(v32 + 56) + 32LL);
    v34 = v33 * 0.5;
    v35 = v33 * 0.40000001;
    v36 = (float)(*(float *)(v3 + 3216) + *((float *)&v70 + 1)) + v34;
    v37 = (float)(*(float *)(v3 + 3216) + v25) + v34;
    v69.m128_f32[0] = v37 + (float)(v35 * 0.866);
    v69.m128_f32[1] = v36 + (float)(v35 * -0.75);
    si128.m128_f32[1] = v69.m128_f32[1];
    si128.m128_f32[0] = v37 + (float)(v35 * -0.866);
    *((float *)&v77 + 1) = v36 + (float)(v35 * 0.75);
    *(float *)&v77 = (float)(v35 * 0.0) + v37;
    if ( (v29 & 0xFF000000) != 0 )
    {
      sub_1800345B0(v32, &v77);
      sub_1800345B0(v32, &si128);
      sub_1800345B0(v32, &v69);
      sub_180034630(v32, v29);
    }
  }
  sub_180038630(v70, v71);
  if ( *(float *)&v74 > 0.0 )
  {
    v38 = (__m128)(unsigned int)v71;
    v39 = (__m128)HIDWORD(v70);
    v38.m128_f32[0] = *(float *)&v71 + *(float *)(v3 + 3236);
    v39.m128_f32[0] = *((float *)&v70 + 1) + *(float *)(v3 + 3216);
    sub_180037440(_mm_unpacklo_ps(v38, v39).m128_i64[0], "##v", nullptr, 1);
  }
  if ( !v24 )
    return 0;
  v40 = qword_18010C470;
  *(_DWORD *)(v3 + 7824) = v5;
  v41 = *(int *)(v40 + 8064);
  if ( *(_DWORD *)(v40 + 8048) <= (int)v41 || *(_DWORD *)(56 * v41 + *(_QWORD *)(v40 + 8056)) != v22 )
  {
    *(_DWORD *)(v40 + 7824) = 0;
    return 0;
  }
  v42 = *(_DWORD *)(v40 + 7824);
  if ( (v42 & 0x10) != 0 )
  {
    *(float *)(v40 + 7892) = fmaxf(*(float *)(v40 + 7892), *(float *)&v71 - *(float *)&v70);
  }
  else
  {
    if ( ((v42 & 2) == 0 || (v43 = 0.0, *(float *)(v40 + 7856) <= 0.0))
      && (v43 = *(float *)&v71 - *(float *)&v70, (v42 & 2) == 0)
      || (v44 = 3.4028235e38, *(float *)(v40 + 7860) <= 0.0) )
    {
      v44 = sub_180072DC0(0xFFFFFFFFLL);
    }
    *(_DWORD *)(v40 + 7824) = v42 | 0x10;
    *(float *)(v40 + 7892) = v43;
    *(_DWORD *)(v40 + 7896) = 0;
    *(_DWORD *)(v40 + 7900) = 2139095039;
    *(float *)(v40 + 7904) = v44;
    *(_QWORD *)(v40 + 7912) = 0;
    *(_QWORD *)(v40 + 7920) = 0;
  }
  sub_180035ED0(&v72, 16, "##Combo_%02d", *(_DWORD *)(v40 + 9556));
  v46 = v72;
  v47 = (unsigned __int8 *)&v73;
  for ( i = -1; v46; i = dword_1800D56B0[v45] ^ (i >> 8) )
  {
    if ( v46 == 35 && *v47 == 35 && v47[1] == 35 )
      i = -1;
    v45 = v46 ^ (unsigned __int64)(unsigned __int8)i;
    v46 = *v47++;
  }
  v49 = sub_18003EA40(~i, v45, v47, 0xFFFFFFFFLL);
  v50 = v49;
  if ( !v49 || !*(_BYTE *)(v49 + 205) )
    goto LABEL_67;
  v77 = 0;
  sub_18003EEC0(v49, &v69, &v77);
  sub_18003EFE0(&v69, v51, &v77);
  sub_18003ECF0(&v77, v50, &v69);
  *(_DWORD *)(v50 + 232) = 3;
  sub_18004CB70(&v69);
  v52 = *(_DWORD *)(v50 + 232);
  v53 = *((float *)&v77 + 1);
  v54 = *(float *)&v77;
  v55 = *((float *)&v71 + 1);
  v56 = *(float *)&v70;
  v57 = v69.m128_f32[3];
  v58 = v69.m128_f32[2];
  v59 = -(v52 != -1);
  v60 = v69.m128_f32[1];
  v61 = v69.m128_f32[0];
  si128 = (__m128)_mm_load_si128((const __m128i *)&xmmword_1800E6880);
  while ( v59 != -1 )
  {
    v62 = si128.m128_i32[v59];
    if ( v62 != v52 )
      goto LABEL_51;
LABEL_64:
    if ( ++v59 >= 4 )
    {
      *(_DWORD *)(v50 + 232) = -1;
      v64 = fmaxf(fminf(v55 + v53, v57) - v53, v60);
      v63 = fmaxf(fminf(v54 + v56, v58) - v54, v61);
      goto LABEL_66;
    }
  }
  v62 = v52;
LABEL_51:
  if ( v62 != 3 )
  {
    if ( v62 == 1 )
    {
      v63 = *(float *)&v70;
    }
    else
    {
      if ( !v62 )
      {
        v64 = *((float *)&v71 + 1);
        v63 = *(float *)&v71 - *(float *)&v77;
        goto LABEL_60;
      }
      v63 = 0.0;
      v64 = 0.0;
      if ( v62 != 2 )
        goto LABEL_60;
      v63 = *(float *)&v71 - *(float *)&v77;
    }
    v64 = *((float *)&v70 + 1) - *((float *)&v77 + 1);
    goto LABEL_60;
  }
  v63 = *(float *)&v70;
  v64 = *((float *)&v71 + 1);
LABEL_60:
  if ( v63 < v69.m128_f32[0]
    || v64 < v69.m128_f32[1]
    || v69.m128_f32[2] < (float)(v63 + *(float *)&v77)
    || v69.m128_f32[3] < (float)(v64 + *((float *)&v77 + 1)) )
  {
    goto LABEL_64;
  }
  *(_DWORD *)(v50 + 232) = v62;
LABEL_66:
  v65 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 7824) |= 1u;
  *(float *)(v65 + 7840) = v63;
  *(float *)(v65 + 7844) = v64;
  *(_QWORD *)(v65 + 7848) = 0;
  *(_DWORD *)(v65 + 7828) = 1;
LABEL_67:
  sub_180037070(2, *(float *)(v40 + 3212));
  v66 = sub_180040700(&v72, 0, 67109191);
  sub_1800371B0(1);
  if ( !v66 )
  {
    sub_18004C770();
    return 0;
  }
  ++*(_DWORD *)(v40 + 9556);
  return 1;
}
