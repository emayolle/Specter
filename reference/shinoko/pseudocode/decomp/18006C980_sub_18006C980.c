// sub_18006C980 size=2163
__int64 __fastcall sub_18006C980(__int64 a1)
{
  bool v1; // zf
  __int64 v3; // rdi
  __int64 v4; // r13
  __int64 v5; // r15
  const char *v6; // r14
  const char *v7; // rdi
  _BYTE *v8; // rsi
  _BYTE *v9; // r13
  __int64 v10; // r12
  __int64 v11; // rax
  int v12; // eax
  __int64 v13; // rax
  const char *v14; // rsi
  __int64 v15; // rax
  int v16; // edx
  __int64 v17; // r9
  float v18; // xmm10_4
  float v19; // xmm9_4
  __int64 result; // rax
  __int64 v21; // r12
  __int64 v22; // rcx
  float v23; // xmm0_4
  int v24; // esi
  int v25; // eax
  int v26; // edi
  unsigned int v27; // r15d
  __int16 v28; // r14
  _DWORD *v29; // rcx
  int v30; // xmm0_4
  int v31; // xmm1_4
  int v32; // xmm2_4
  float v33; // xmm6_4
  float v34; // xmm7_4
  float v35; // xmm0_4
  unsigned __int64 v36; // rdi
  unsigned __int64 i; // rsi
  float v38; // xmm2_4
  __int64 v39; // rcx
  float v40; // xmm3_4
  float v41; // xmm1_4
  float v42; // xmm0_4
  float v43; // xmm0_4
  unsigned int v44; // xmm1_4
  __int64 v45; // rcx
  int v46; // edi
  int v47; // xmm1_4
  int v48; // r9d
  __int64 v49; // rcx
  int j; // r8d
  __int64 v51; // rax
  __int64 v52; // rdx
  float v53; // xmm1_4
  float v54; // xmm0_4
  int v55; // r8d
  __int16 v56; // ax
  float v57; // xmm1_4
  float v58; // xmm0_4
  float v59; // xmm1_4
  __int64 v60; // rcx
  __int64 v61; // rax
  __int64 v62; // rdx
  _DWORD *v63; // rax
  int v64; // xmm1_4
  int v65; // xmm2_4
  int v66; // xmm3_4
  int v67; // xmm4_4
  __int128 v68; // xmm0
  _DWORD *v69; // rax
  __int64 v70; // rax
  __int64 v71; // rcx
  __int64 v72; // rax
  __int64 v73; // rcx
  __m128 v74; // [rsp+38h] [rbp-59h] BYREF
  __int64 v75; // [rsp+F8h] [rbp+67h] BYREF
  __int64 v76; // [rsp+100h] [rbp+6Fh]
  int v77; // [rsp+108h] [rbp+77h]
  int v78; // [rsp+110h] [rbp+7Fh] BYREF
  float v79; // [rsp+114h] [rbp+83h]

  v1 = *(_DWORD *)(a1 + 116) == -1;
  v3 = qword_18010C470;
  v4 = *(_QWORD *)(qword_18010C470 + 5216);
  v75 = v4;
  v76 = qword_18010C470;
  if ( !v1 )
  {
    sub_18006D200();
    *(_DWORD *)(a1 + 116) = -1;
  }
  if ( *(_BYTE *)(v3 + 10080) )
  {
    v5 = qword_18010C470;
    v6 = "|";
    v7 = "|";
    v8 = *(_BYTE **)(qword_18010C470 + 10120);
    v9 = *(_BYTE **)(qword_18010C470 + 10128);
    v10 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    for ( *(_QWORD *)(v5 + 10120) = 0; v7 != (const char *)-1LL; ++v7 )
    {
      if ( !*v7 || *v7 == 35 && v7[1] == 35 )
        break;
    }
    if ( v8 )
    {
      v11 = sub_1800B9730(v8);
      sub_180051A10(0, v8, &v8[v11]);
    }
    v12 = *(_DWORD *)(v10 + 416);
    if ( *(_DWORD *)(v5 + 10144) > v12 )
      *(_DWORD *)(v5 + 10144) = v12;
    while ( 1 )
    {
      v13 = sub_1800B8A30(v6, 10, v7 - v6);
      v14 = v7;
      if ( v13 )
        v14 = (const char *)v13;
      if ( v6 == v14 && v14 == v7 )
        break;
      sub_180051790("%*s%.*s");
      *(_BYTE *)(v5 + 10140) = 0;
      if ( *v14 == 10 )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v5 + 10140) = 1;
      }
      if ( v14 == v7 )
        break;
      v6 = v14 + 1;
    }
    if ( v9 )
    {
      v15 = sub_1800B9730(v9);
      sub_180051A10(0, v9, &v9[v15]);
    }
    v3 = v76;
    v4 = v75;
  }
  *(_DWORD *)(v4 + 284) = *(_DWORD *)(a1 + 128);
  v16 = *(_DWORD *)(a1 + 112);
  v17 = (unsigned int)*(__int16 *)(a1 + 552);
  v18 = *(float *)(a1 + 124);
  v19 = *(float *)(a1 + 128);
  LODWORD(v76) = *(__int16 *)(a1 + 552);
  LODWORD(v75) = v16 + 1;
  v77 = *(__int16 *)(a1 + 550);
  result = (unsigned int)*(__int16 *)(a1 + 120);
  if ( *(_WORD *)(a1 + 120) )
  {
    v22 = 3LL * ((int)result - 1);
    result = *(_QWORD *)(a1 + 456);
    v21 = result + 8 * v22;
  }
  else
  {
    v21 = a1 + 424;
  }
  if ( (*(_BYTE *)(a1 + 148) & 1) != 0 && (!v16 || (*(_DWORD *)(a1 + 148) & 0x10000) != 0) )
    *(float *)(v21 + 8) = (float)(v19 - v18) + *(float *)(v21 + 8);
  if ( v19 < *(float *)(a1 + 292) || *(float *)(a1 + 300) < v18 )
  {
    v46 = v75;
  }
  else
  {
    if ( *(_WORD *)(a1 + 522) != 0xFFFF )
    {
      v23 = *(float *)(v3 + 228);
      if ( v23 >= v18 && v19 > v23 && *(int *)(v21 + 20) < 0 )
        *(_DWORD *)(v21 + 20) = *(_DWORD *)(a1 + 112);
    }
    v24 = *(_DWORD *)(a1 + 156);
    if ( v24 == 0x1000000 )
    {
      v24 = 0;
      if ( (*(_BYTE *)(a1 + 4) & 0x40) != 0 )
      {
        v74 = *(__m128 *)(qword_18010C470 + 16 * ((*(_DWORD *)(a1 + 152) & 1 | 0x30LL) + 18) + 3136);
        v74.m128_f32[3] = _mm_shuffle_ps(v74, v74, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
        sub_180036620(&v74);
        v24 = v25;
      }
    }
    v26 = *(_DWORD *)(a1 + 160);
    if ( v26 == 0x1000000 )
      v26 = 0;
    v27 = 0;
    if ( *(int *)(a1 + 112) > 0 && *(char *)(a1 + 4) < 0 )
    {
      if ( (*(_DWORD *)(a1 + 148) & 0x10000) != 0 )
        v27 = *(_DWORD *)(a1 + 164);
      else
        v27 = *(_DWORD *)(a1 + 168);
    }
    v28 = *(_WORD *)(a1 + 558) >> 15;
    result = v24 | v26 | v27;
    if ( v24 | v26 | v27 || (_DWORD)v75 == (_DWORD)v17 || *(__int16 *)(a1 + 558) >= 0 )
    {
      if ( (*(_DWORD *)(a1 + 4) & 0x100000) == 0 )
      {
        v29 = *(_DWORD **)(v4 + 712);
        v30 = *(_DWORD *)(a1 + 324);
        v31 = *(_DWORD *)(a1 + 328);
        v32 = *(_DWORD *)(a1 + 332);
        v29[24] = *(_DWORD *)(a1 + 320);
        v29[25] = v30;
        v29[26] = v31;
        v29[27] = v32;
      }
      result = sub_18005D640(*(_QWORD *)(a1 + 416), *(_QWORD *)(v4 + 712), 0, v17);
    }
    if ( v24 || v26 )
    {
      v33 = fmaxf(v18, *(float *)(a1 + 308));
      v34 = fminf(v19, *(float *)(a1 + 316));
      v74.m128_u64[0] = __PAIR64__(LODWORD(v33), COERCE_UNSIGNED_INT(fmaxf(*(float *)(a1 + 272), *(float *)(a1 + 304))));
      v35 = *(float *)(a1 + 280);
      v74.m128_f32[3] = v34;
      v74.m128_i32[2] = fminf(v35, *(float *)(a1 + 312));
      if ( v24 && v34 > v33 )
        result = sub_18005C870(*(_QWORD *)(v4 + 712), (unsigned int)&v74, (unsigned int)&v74.m128_u32[2], v24, 0, 0);
      if ( v26 && v34 > v33 )
        result = sub_18005C870(*(_QWORD *)(v4 + 712), (unsigned int)&v74, (unsigned int)&v74.m128_u32[2], v26, 0, 0);
    }
    if ( !(_BYTE)v28 )
    {
      v36 = *(_QWORD *)(a1 + 56);
      result = *(__int16 *)(a1 + 558);
      for ( i = v36 + 8 * result; v36 <= i; v36 += 8LL )
      {
        v38 = fminf(*(float *)(a1 + 128), *(float *)(a1 + 316));
        v39 = 116LL * *(__int16 *)(v36 + 4);
        result = *(_QWORD *)(a1 + 24);
        v40 = *(float *)(result + v39 + 12);
        v41 = fminf(v40, *(float *)(a1 + 280));
        v42 = fmaxf(*(float *)(result + v39 + 8), *(float *)(a1 + 272));
        v74.m128_i32[1] = fmaxf(*(float *)(a1 + 124), *(float *)(a1 + 308));
        v74.m128_f32[3] = v38;
        v43 = fmaxf(fmaxf(v42, *(float *)(a1 + 304)), *(float *)(result + v39 + 36));
        v74.m128_i32[2] = fminf(fminf(v41, *(float *)(a1 + 312)), v40);
        v74.m128_f32[0] = v43;
        if ( v38 > v74.m128_f32[1] )
          result = sub_18005C870(
                     *(_QWORD *)(v4 + 712),
                     (unsigned int)&v74,
                     (unsigned int)&v74.m128_u32[2],
                     *(_DWORD *)v36,
                     0,
                     0);
      }
    }
    if ( v27 && v18 >= *(float *)(a1 + 308) && *(float *)(a1 + 316) > v18 )
    {
      v44 = *(_DWORD *)(a1 + 172);
      v45 = *(_QWORD *)(v4 + 712);
      v78 = *(_DWORD *)(a1 + 176);
      v74.m128_u64[0] = __PAIR64__(LODWORD(v18), v44);
      v79 = v18;
      result = sub_18005C320(v45, (unsigned int)&v74, (unsigned int)&v78, v27, 1065353216);
    }
    v46 = v75;
    v17 = (unsigned int)v76;
    if ( (_DWORD)v75 == (_DWORD)v76 && v19 >= *(float *)(a1 + 308) && *(float *)(a1 + 316) > v19 )
    {
      v47 = *(_DWORD *)(a1 + 172);
      v48 = *(_DWORD *)(a1 + 164);
      v49 = *(_QWORD *)(v4 + 712);
      LODWORD(v75) = *(_DWORD *)(a1 + 176);
      v78 = v47;
      *((float *)&v75 + 1) = v19;
      v79 = v19;
      result = sub_18005C320(v49, (unsigned int)&v78, (unsigned int)&v75, v48, 1065353216);
      v17 = (unsigned int)v76;
    }
  }
  if ( v46 == v77 )
  {
    for ( j = 0; j < *(_DWORD *)(a1 + 108); *(_BYTE *)(*(_QWORD *)(a1 + 24) + v52 + 110) = result )
    {
      v51 = j++;
      v52 = 116 * v51;
      result = *(unsigned __int8 *)(a1 + 566);
    }
    v53 = fmaxf(*(float *)(a1 + 128) + 1.0, *(float *)(a1 + 292));
    *(float *)(v21 + 12) = v53 - *(float *)(a1 + 244);
    if ( v46 == (_DWORD)v17 )
    {
      v54 = *(float *)(a1 + 300);
      v55 = 0;
      v56 = *(_WORD *)(a1 + 564);
      v57 = fminf(v53, v54);
      *(float *)(a1 + 348) = v54;
      *(float *)(a1 + 316) = v54;
      *(_BYTE *)(a1 + 579) = 1;
      *(_WORD *)(a1 + 562) = v56;
      *(float *)(a1 + 340) = v57;
      *(float *)(a1 + 308) = v57;
      v58 = *(float *)(a1 + 128) - *(float *)(a1 + 124);
      v59 = (float)(*(float *)(a1 + 128) + *(float *)(a1 + 276)) - *(float *)(a1 + 244);
      *(float *)(v4 + 284) = v59;
      *(float *)(a1 + 128) = v59;
      for ( *(float *)(a1 + 124) = v59 - v58;
            v55 < *(_DWORD *)(a1 + 108);
            *(_DWORD *)(v60 + v62 + 40) = *(_DWORD *)(a1 + 340) )
      {
        v60 = *(_QWORD *)(a1 + 24);
        v61 = v55++;
        v62 = 116 * v61;
        *(_WORD *)(v60 + v62 + 96) = *(_WORD *)(v60 + 116 * v61 + 100);
      }
      v63 = *(_DWORD **)(a1 + 24);
      v64 = v63[9];
      v65 = v63[10];
      v66 = v63[11];
      v67 = v63[12];
      v68 = *(_OWORD *)(v63 + 9);
      v69 = *(_DWORD **)(v4 + 712);
      *(_OWORD *)(v4 + 608) = v68;
      v69[24] = v64;
      v69[25] = v65;
      v69[26] = v66;
      v69[27] = v67;
      v70 = *(_QWORD *)(v4 + 712);
      v71 = *(int *)(v70 + 160);
      v72 = *(_QWORD *)(v70 + 168);
      v73 = 2 * (v71 - 1);
      *(_DWORD *)(v72 + 8 * v73) = v64;
      *(_DWORD *)(v72 + 8 * v73 + 4) = v65;
      *(_DWORD *)(v72 + 8 * v73 + 8) = v66;
      *(_DWORD *)(v72 + 8 * v73 + 12) = v67;
      result = sub_18005D640(
                 *(_QWORD *)(a1 + 416),
                 *(_QWORD *)(v4 + 712),
                 *(unsigned __int16 *)(*(_QWORD *)(a1 + 24) + 96LL),
                 v17);
    }
  }
  v1 = (*(_BYTE *)(a1 + 148) & 1) == 0;
  *(_BYTE *)(a1 + 568) = 0;
  if ( v1 )
    ++*(_DWORD *)(a1 + 152);
  return result;
}
