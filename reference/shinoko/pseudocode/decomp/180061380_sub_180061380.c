// sub_180061380 size=1928
__int64 __fastcall sub_180061380(__int64 a1)
{
  __int64 *v2; // rcx
  _QWORD *v3; // rdi
  __int64 v4; // rax
  _QWORD *v5; // rsi
  void (__fastcall *v6)(__int64); // rax
  __int64 v7; // r14
  __int64 v8; // rax
  __int64 v9; // rbp
  __int64 v10; // rdi
  __int64 i; // rsi
  __int64 v12; // rax
  void (__fastcall *v13)(__int64); // r8
  __int64 *v14; // r14
  __int64 v15; // rax
  __int64 *v16; // r15
  __int64 v17; // rsi
  _QWORD *v18; // rdi
  _QWORD *j; // rbp
  __int64 v20; // rax
  int v21; // edx
  int v22; // eax
  _QWORD *v23; // rax
  _QWORD *v24; // rdi
  __int64 v25; // rax
  void (__fastcall *v26)(__int64); // rdx
  __int64 v27; // rcx
  __int64 v28; // rax
  __int64 v29; // rdx
  __int64 v30; // rax
  __int64 v31; // r14
  __int64 v32; // rdi
  int v33; // ecx
  int v34; // esi
  int v35; // eax
  int v36; // ebp
  __int64 v37; // rax
  __int64 v38; // rdx
  __int64 v39; // r15
  signed int v40; // r10d
  unsigned __int64 v41; // r9
  signed int v42; // r8d
  int v43; // ebp
  int v44; // r11d
  __m128i v45; // xmm4
  __m128i si128; // xmm5
  __m128i v47; // xmm1
  double v48; // xmm3_8
  __m128i v49; // xmm0
  __int64 v50; // rcx
  __m128i v51; // xmm2
  __m128i v52; // xmm0
  __m128i v53; // xmm2
  unsigned int v54; // eax
  __m128i v55; // xmm0
  __m128i v56; // xmm0
  __m128i v57; // xmm2
  __m128i v58; // xmm2
  __int64 v59; // rax
  __int64 *v60; // r14
  __int64 v61; // rax
  __int64 *v62; // r15
  __int64 v63; // rdi
  int v64; // ecx
  int v65; // esi
  __int64 v66; // rax
  __int64 v67; // rdx
  __int64 v68; // rbp
  __int64 v69; // rsi
  __int64 v70; // rcx
  __int64 v71; // r14
  __int64 v72; // rbp
  int v73; // ecx
  int v74; // r8d
  int v75; // r8d
  int v76; // eax
  __int64 result; // rax
  __int64 v78; // rcx
  __int64 v79; // rdx
  _QWORD *v80; // rcx
  __m128i v81; // [rsp+20h] [rbp-68h] BYREF
  __m128i v82; // [rsp+30h] [rbp-58h] BYREF
  __m128i v83; // [rsp+40h] [rbp-48h] BYREF
  __m128i v84; // [rsp+50h] [rbp-38h] BYREF

  if ( *(_QWORD *)(a1 + 696) )
    goto LABEL_27;
  qword_18010CB88 = 0;
  qword_18010CB50 = (__int64)"stb_truetype";
  qword_18010CB68 = (__int64)sub_180062E40;
  qword_18010CB70 = (__int64)sub_1800635E0;
  qword_18010CB78 = (__int64)sub_180063620;
  qword_18010CB80 = (__int64)sub_180063640;
  qword_18010CB90 = (__int64)sub_180063700;
  v2 = *(__int64 **)(a1 + 696);
  if ( v2 == &qword_18010CB50 )
    goto LABEL_27;
  v3 = *(_QWORD **)(a1 + 112);
  v4 = *(int *)(a1 + 104);
  v5 = &v3[v4];
  if ( v4 * 8 )
  {
    do
      sub_18005F9F0(a1, *v3++);
    while ( v3 != v5 );
    v2 = *(__int64 **)(a1 + 696);
  }
  if ( *(_QWORD *)(a1 + 688) )
  {
    if ( !v2 || (v6 = (void (__fastcall *)(__int64))v2[2]) == nullptr )
    {
      *(_QWORD *)(a1 + 696) = &qword_18010CB50;
      *(_QWORD *)(a1 + 704) = qword_18010CB50;
      goto LABEL_12;
    }
    v6(a1);
    *(_QWORD *)(a1 + 696) = &qword_18010CB50;
    *(_QWORD *)(a1 + 704) = qword_18010CB50;
    if ( *(_QWORD *)(a1 + 688) )
    {
LABEL_12:
      if ( qword_18010CB58 )
        qword_18010CB58(a1);
    }
  }
  else
  {
    *(_QWORD *)(a1 + 696) = &qword_18010CB50;
    *(_QWORD *)(a1 + 704) = qword_18010CB50;
  }
  v7 = *(_QWORD *)(a1 + 112);
  v8 = 8LL * *(int *)(a1 + 104);
  v9 = v8 + v7;
  if ( v8 )
  {
    do
    {
      v10 = *(_QWORD *)(*(_QWORD *)v7 + 40LL);
      for ( i = v10 + 8LL * *(int *)(*(_QWORD *)v7 + 32LL); v10 != i; v10 += 8 )
      {
        v12 = *(_QWORD *)(*(_QWORD *)v10 + 128LL);
        if ( !v12 )
          v12 = *(_QWORD *)(a1 + 696);
        v13 = *(void (__fastcall **)(__int64))(v12 + 24);
        if ( v13 )
          v13(a1);
      }
      v7 += 8;
    }
    while ( v7 != v9 );
  }
  v14 = *(__int64 **)(a1 + 112);
  v15 = *(int *)(a1 + 104);
  v16 = &v14[v15];
  if ( v15 * 8 )
  {
    do
    {
      v17 = *v14;
      v18 = *(_QWORD **)(*v14 + 40);
      for ( j = &v18[*(int *)(*v14 + 32)]; v18 != j; ++v18 )
        sub_18005FA90(a1, v17, *v18);
      ++v14;
    }
    while ( v14 != v16 );
  }
LABEL_27:
  v20 = *(_QWORD *)(a1 + 56);
  if ( !v20 || !*(_QWORD *)(v20 + 40) )
  {
    v21 = (*(_DWORD *)(a1 + 16) - 1)
        | ((*(_DWORD *)(a1 + 16) - 1) >> 1)
        | (((*(_DWORD *)(a1 + 16) - 1) | ((*(_DWORD *)(a1 + 16) - 1) >> 1)) >> 2)
        | (((*(_DWORD *)(a1 + 16) - 1)
          | ((*(_DWORD *)(a1 + 16) - 1) >> 1)
          | (((*(_DWORD *)(a1 + 16) - 1) | ((*(_DWORD *)(a1 + 16) - 1) >> 1)) >> 2)) >> 4)
        | (((*(_DWORD *)(a1 + 16) - 1)
          | ((*(_DWORD *)(a1 + 16) - 1) >> 1)
          | (((*(_DWORD *)(a1 + 16) - 1) | ((*(_DWORD *)(a1 + 16) - 1) >> 1)) >> 2)
          | (((*(_DWORD *)(a1 + 16) - 1)
            | ((*(_DWORD *)(a1 + 16) - 1) >> 1)
            | (((*(_DWORD *)(a1 + 16) - 1) | ((*(_DWORD *)(a1 + 16) - 1) >> 1)) >> 2)) >> 4)) >> 8);
    v22 = (*(_DWORD *)(a1 + 12) - 1)
        | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
        | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)
        | (((*(_DWORD *)(a1 + 12) - 1)
          | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
          | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)) >> 4)
        | (((*(_DWORD *)(a1 + 12) - 1)
          | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
          | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)
          | (((*(_DWORD *)(a1 + 12) - 1)
            | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
            | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)) >> 4)) >> 8);
    sub_180060520(a1, (v22 | (unsigned int)(v22 >> 16)) + 1, (v21 | (unsigned int)(v21 >> 16)) + 1);
  }
  v23 = (_QWORD *)sub_18003A810(248);
  v24 = v23;
  if ( v23 )
  {
    v23[10] = 0;
    v23[11] = 0;
    v23[12] = 0;
    v23[13] = 0;
    v23[14] = 0;
    v23[15] = 0;
    v23[16] = 0;
    v23[17] = 0;
    v23[21] = 0;
    v23[22] = 0;
    v23[24] = 0;
    v23[25] = 0;
    v23[26] = 0;
    v23[27] = 0;
    v23[28] = 0;
    sub_1800B9280(v23, 0, 248);
    *((_DWORD *)v24 + 41) = -1;
    *((_DWORD *)v24 + 36) = -1;
    *(_QWORD *)((char *)v24 + 236) = -1;
  }
  else
  {
    v24 = nullptr;
  }
  v25 = *(_QWORD *)(a1 + 696);
  *(_QWORD *)(a1 + 688) = v24;
  v26 = *(void (__fastcall **)(__int64))(v25 + 8);
  if ( v26 )
    v26(a1);
  v27 = *(_QWORD *)(a1 + 680);
  v28 = 8LL * *(int *)(a1 + 672);
  v29 = v28 + v27;
  if ( v28 )
  {
    while ( 1 )
    {
      v30 = *(_QWORD *)(*(_QWORD *)v27 + 104LL);
      if ( v30 )
        break;
      v27 += 8;
      if ( v27 == v29 )
        goto LABEL_40;
    }
    *(_BYTE *)(a1 + 81) = (*(_DWORD *)(v30 + 12) & 0x10) != 0;
  }
LABEL_40:
  v31 = *(_QWORD *)(a1 + 56);
  v32 = *(_QWORD *)(a1 + 688);
  v33 = *(_DWORD *)(v32 + 84);
  v34 = *(_DWORD *)(v31 + 28) / 2;
  if ( v34 > v33 )
  {
    if ( v33 )
      v35 = v33 + v33 / 2;
    else
      v35 = 8;
    v36 = *(_DWORD *)(v31 + 28) / 2;
    if ( v35 > v34 )
      v36 = v35;
    if ( v36 > v33 )
    {
      v37 = sub_18003A810(16LL * v36);
      v38 = *(_QWORD *)(v32 + 88);
      v39 = v37;
      if ( v38 )
      {
        sub_1800B8BD0(v37, v38, 16LL * *(int *)(v32 + 80));
        sub_18003A8D0(*(LPVOID *)(v32 + 88));
      }
      *(_QWORD *)(v32 + 88) = v39;
      *(_DWORD *)(v32 + 84) = v36;
    }
  }
  *(_DWORD *)(v32 + 80) = v34;
  v40 = v34 - 1;
  v41 = *(_QWORD *)(v32 + 88);
  v42 = 0;
  v43 = *(_DWORD *)(v31 + 32);
  v44 = *(_DWORD *)(v31 + 28);
  v45 = _mm_unpacklo_epi64((__m128i)v41, (__m128i)v41);
  if ( v34 - 1 > 0 )
  {
    if ( (unsigned int)v40 < 8 )
      goto LABEL_82;
    if ( dword_1800FA030 < 2 )
      goto LABEL_82;
    si128 = _mm_load_si128((const __m128i *)&xmmword_1800E68A0);
    do
    {
      v47.m128i_i64[1] = _mm_load_si128(&v81).m128i_i64[1];
      v48 = *(double *)_mm_move_epi64(si128).m128i_i64;
      *(double *)v47.m128i_i64 = v48;
      v81 = v47;
      v49 = _mm_move_epi64(_mm_add_epi32(v47, _mm_shuffle_epi32(_mm_cvtsi32_si128(v42 + 1), 0)));
      v50 = 2LL * v42;
      v47.m128i_i64[1] = _mm_load_si128(&v82).m128i_i64[1];
      *(double *)v47.m128i_i64 = v48;
      v51 = _mm_add_epi64(_mm_slli_epi64(_mm_cvtepi32_epi64(v49), 4u), v45);
      v82 = v47;
      *(_QWORD *)(v41 + 8 * v50 + 8) = v51.m128i_i64[0];
      *(_QWORD *)(v41 + 8 * v50 + 24) = _mm_srli_si128(v51, 8).m128i_u64[0];
      v52 = _mm_move_epi64(_mm_add_epi32(v47, _mm_shuffle_epi32(_mm_cvtsi32_si128(v42 + 3), 0)));
      v47.m128i_i64[1] = _mm_load_si128(&v83).m128i_i64[1];
      *(double *)v47.m128i_i64 = v48;
      v53 = _mm_add_epi64(_mm_slli_epi64(_mm_cvtepi32_epi64(v52), 4u), v45);
      v83 = v47;
      *(_QWORD *)(v41 + 8 * v50 + 40) = v53.m128i_i64[0];
      *(_QWORD *)(v41 + 8 * v50 + 56) = _mm_srli_si128(v53, 8).m128i_u64[0];
      v54 = v42 + 7;
      v55 = _mm_shuffle_epi32(_mm_cvtsi32_si128(v42 + 5), 0);
      v42 += 8;
      v56 = _mm_move_epi64(_mm_add_epi32(v47, v55));
      v47.m128i_i64[1] = _mm_load_si128(&v84).m128i_i64[1];
      *(double *)v47.m128i_i64 = v48;
      v84 = v47;
      v57 = _mm_add_epi64(_mm_slli_epi64(_mm_cvtepi32_epi64(v56), 4u), v45);
      *(_QWORD *)(v41 + 8 * v50 + 72) = v57.m128i_i64[0];
      *(_QWORD *)(v41 + 8 * v50 + 88) = _mm_srli_si128(v57, 8).m128i_u64[0];
      v58 = _mm_add_epi64(
              _mm_slli_epi64(
                _mm_cvtepi32_epi64(_mm_move_epi64(_mm_add_epi32(v47, _mm_shuffle_epi32(_mm_cvtsi32_si128(v54), 0)))),
                4u),
              v45);
      *(_QWORD *)(v41 + 8 * v50 + 104) = v58.m128i_i64[0];
      *(_QWORD *)(v41 + 8 * v50 + 120) = _mm_srli_si128(v58, 8).m128i_u64[0];
    }
    while ( v42 < v40 - v40 % 8 );
    if ( v42 < v40 )
    {
LABEL_82:
      do
      {
        v59 = 2LL * v42++;
        *(_QWORD *)(v41 + 8 * v59 + 8) = v41 + 16LL * v42;
      }
      while ( v42 < v40 );
    }
  }
  *(_QWORD *)(v41 + 16LL * v42 + 8) = 0;
  *(_QWORD *)(v32 + 24) = v32 + 40;
  *(_QWORD *)(v32 + 12) = 1;
  *(_QWORD *)(v32 + 32) = v41;
  *(_DWORD *)v32 = v44;
  *(_DWORD *)(v32 + 4) = v43;
  *(_DWORD *)(v32 + 20) = v34;
  *(_DWORD *)(v32 + 8) = (v34 + v44 - 1) / v34;
  *(_DWORD *)(v32 + 40) = 0;
  *(_QWORD *)(v32 + 48) = v32 + 56;
  *(_DWORD *)(v32 + 56) = v44;
  *(_DWORD *)(v32 + 44) = 0;
  *(_DWORD *)(v32 + 60) = 0x40000000;
  *(_QWORD *)(v32 + 64) = 0;
  *(_QWORD *)(v32 + 148) = 0;
  *(_QWORD *)(v32 + 168) = 0;
  *(_QWORD *)(v32 + 176) = 0;
  sub_18005F600(a1);
  sub_18005F180(a1);
  v60 = *(__int64 **)(a1 + 112);
  v61 = *(int *)(a1 + 104);
  v62 = &v60[v61];
  if ( v61 * 8 )
  {
    do
    {
      v63 = *v60;
      v64 = *(_DWORD *)(*v60 + 36);
      if ( v64 < 0 )
      {
        v65 = 0;
        if ( v64 + ((v64 + 1) >> 1) > 0 )
          v65 = v64 + ((v64 + 1) >> 1);
        if ( v65 > v64 )
        {
          v66 = sub_18003A810(8LL * v65);
          v67 = *(_QWORD *)(v63 + 40);
          v68 = v66;
          if ( v67 )
          {
            sub_1800B8BD0(v66, v67, 8LL * *(int *)(v63 + 32));
            sub_18003A8D0(*(LPVOID *)(v63 + 40));
          }
          *(_QWORD *)(v63 + 40) = v68;
          *(_DWORD *)(v63 + 36) = v65;
        }
      }
      ++v60;
      *(_DWORD *)(v63 + 32) = 0;
    }
    while ( v60 != v62 );
  }
  v69 = *(_QWORD *)(a1 + 128);
  v70 = 144LL * *(int *)(a1 + 120);
  v71 = v70 + v69;
  if ( v70 )
  {
    do
    {
      v72 = *(_QWORD *)(v69 + 120);
      v73 = *(_DWORD *)(v72 + 36);
      v74 = *(_DWORD *)(v72 + 32);
      if ( v74 == v73 )
      {
        v75 = v74 + 1;
        if ( v73 )
          v76 = v73 + v73 / 2;
        else
          v76 = 8;
        if ( v76 > v75 )
          v75 = v76;
        sub_180054080(v72 + 32, (unsigned int)v75);
      }
      *(_QWORD *)(*(_QWORD *)(v72 + 40) + 8LL * *(int *)(v72 + 32)) = v69;
      v69 += 144;
      ++*(_DWORD *)(v72 + 32);
    }
    while ( v69 != v71 );
  }
  result = *(int *)(a1 + 672);
  v78 = 8 * result;
  if ( 8 * result )
  {
    result = *(_QWORD *)(a1 + 680);
    v79 = v78 + result;
    do
    {
      v80 = *(_QWORD **)result;
      if ( *(_QWORD *)(*(_QWORD *)result + 16LL) == a1 )
      {
        *v80 = *(_QWORD *)(a1 + 92);
        v80[1] = a1 + 136;
      }
      result += 8;
    }
    while ( result != v79 );
  }
  return result;
}
