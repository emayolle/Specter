// sub_18003B710 size=5067
__int64 sub_18003B710()
{
  __int64 v0; // rdi
  __int64 v1; // rbp
  int v2; // esi
  __int64 v3; // rbx
  __int64 v4; // rcx
  __int64 v5; // rax
  __int64 v6; // rsi
  int v7; // eax
  __int64 (__fastcall *v8)(); // rax
  void *v9; // rax
  const CHAR *v10; // rcx
  __int64 v11; // rax
  __int64 v12; // rbx
  unsigned int v13; // esi
  int v14; // eax
  __int64 v15; // r15
  __int64 v16; // rax
  void *v17; // rsi
  float v18; // xmm0_4
  float v19; // xmm0_4
  const CHAR *v20; // rcx
  double v21; // xmm0_8
  int v22; // ecx
  __int64 v23; // rdx
  int v24; // ecx
  float v25; // xmm6_4
  __int64 v26; // rax
  float v27; // xmm1_4
  float v28; // xmm2_4
  int v29; // eax
  int v30; // ecx
  float v31; // xmm1_4
  int v32; // ecx
  __int64 v33; // rdx
  int v34; // ecx
  __int64 v35; // rdx
  __int64 v36; // rcx
  __int64 *v37; // rcx
  __int64 v38; // rax
  __int64 *v39; // rdx
  __int64 v40; // rax
  __m128 v41; // xmm4
  __m128 v42; // xmm3
  __m128 v43; // xmm0
  float v44; // xmm1_4
  __int64 *v45; // rcx
  __int64 v46; // rax
  __int64 *v47; // rdx
  __int64 v48; // rax
  int v49; // eax
  __int64 v50; // rcx
  char v51; // al
  int v52; // eax
  float v53; // xmm2_4
  int v54; // eax
  int v55; // eax
  int v56; // ecx
  __int64 v57; // rcx
  __int64 v58; // rax
  float v59; // xmm0_4
  float v60; // xmm1_4
  float v61; // xmm0_4
  __int64 *v62; // rdi
  __int64 v63; // rax
  __int64 *v64; // rsi
  __int64 v65; // rbx
  char v66; // cl
  __int16 v67; // ax
  __int64 v68; // rcx
  void *v69; // rcx
  void *v70; // rcx
  void *v71; // rcx
  void *v72; // rcx
  __int64 v73; // r9
  __int64 v74; // rcx
  int v75; // eax
  __int64 v76; // rcx
  __int64 v77; // r9
  __int64 v78; // rcx
  int v79; // eax
  int v80; // edx
  __int64 v81; // rax
  float v82; // xmm1_4
  __int128 v83; // xmm0
  int v84; // eax
  int i; // edi
  float v86; // xmm0_4
  __int64 v87; // rsi
  __int64 v88; // rbx
  void *v89; // rcx
  void *v90; // rcx
  int v91; // edx
  __int64 v92; // rax
  __int64 v93; // rax
  __int64 v94; // rbx
  __int64 v95; // rdi
  float v96; // xmm0_4
  __int64 v97; // rbx
  void *v98; // rcx
  void *v99; // rcx
  void *v100; // rcx
  _QWORD *v101; // rsi
  __int64 v102; // rax
  _QWORD *v103; // r14
  __int64 v104; // rdi
  __int64 v105; // rbx
  __int64 v106; // rax
  __int64 v107; // rdx
  __int64 v108; // rcx
  int v109; // ecx
  __int64 v110; // rdx
  int v111; // ecx
  int *v112; // rbx
  int v113; // ecx
  __int64 v114; // rdx
  int v115; // ecx
  __int64 v116; // rcx
  __int64 v117; // r14
  int v118; // ebx
  int v119; // edi
  __int64 v120; // rcx
  __int64 v121; // rbx
  int v122; // eax
  __int64 v123; // rax
  int v124; // edi
  int v125; // ecx
  __int64 v126; // rdx
  int v127; // ecx
  __int64 v128; // rcx
  __int64 v129; // rax
  __int64 v130; // rax
  __int64 v131; // rcx
  __int64 v132; // rax
  __int64 v133; // rbx
  __int64 v134; // rdi
  int v135; // esi
  int v136; // edx
  int v137; // ecx
  int v138; // r8d
  float v139; // xmm0_4
  __int64 v140; // rax
  char v141; // al
  char v142; // al
  char v143; // al
  char v144; // al
  __int64 v145; // rdx
  int v146; // ecx
  __int64 v147; // rbx
  __int64 result; // rax
  __int64 v149; // rdi
  _QWORD v150[4]; // [rsp+30h] [rbp-68h]
  unsigned __int64 v151; // [rsp+A0h] [rbp+8h] BYREF

  v0 = qword_18010C470;
  v1 = qword_18010C470;
  v2 = *(_DWORD *)(qword_18010C470 + 9976) - 1;
  if ( v2 < 0 )
  {
    v3 = *(_QWORD *)(qword_18010C470 + 9984);
  }
  else
  {
    do
    {
      v3 = *(_QWORD *)(v0 + 9984);
      v4 = v3 + 32LL * (unsigned int)v2;
      if ( *(_DWORD *)(v4 + 4) == 7 )
      {
        sub_1800B8BD0(v4, v4 + 32, 32 * (*(int *)(v0 + 9976) - (unsigned __int64)(unsigned int)v2) - 32);
        --*(_DWORD *)(v0 + 9976);
        v3 = *(_QWORD *)(v0 + 9984);
      }
      --v2;
    }
    while ( v2 >= 0 );
  }
  v5 = 32LL * *(int *)(v0 + 9976);
  v6 = v5 + v3;
  if ( v5 )
  {
    do
    {
      if ( !*(_DWORD *)(v3 + 4) )
        (*(void (__fastcall **)(__int64, __int64))(v3 + 16))(v1, v3);
      v3 += 32;
    }
    while ( v3 != v6 );
    v0 = qword_18010C470;
  }
  v7 = *(_DWORD *)(v0 + 8);
  if ( (v7 & 4) != 0 )
  {
    v7 &= ~4u;
    *(_BYTE *)(v0 + 82) = 1;
    *(_DWORD *)(v0 + 8) = v7;
  }
  if ( (v7 & 8) != 0 )
  {
    *(_BYTE *)(v0 + 83) = 0;
    *(_DWORD *)(v0 + 8) = v7 & 0xFFFFFFF7;
  }
  if ( *(_QWORD *)(v0 + 3016) )
  {
    v8 = *(__int64 (__fastcall **)())(v0 + 3040);
    if ( !v8 || v8 == sub_180052B00 )
      *(_QWORD *)(v0 + 3040) = sub_180049390;
  }
  if ( *(_QWORD *)(v0 + 3024) )
  {
    v9 = *(void **)(v0 + 3048);
    if ( !v9 || v9 == &sub_180052C30 )
      *(_QWORD *)(v0 + 3048) = sub_1800493B0;
  }
  if ( !*(_BYTE *)(v0 + 9904) )
  {
    v10 = *(const CHAR **)(v0 + 40);
    if ( v10 )
    {
      v11 = sub_1800361A0(v10, "rb");
      v12 = v11;
      if ( v11 )
      {
        v13 = sub_18009D6A0(v11);
        if ( v13 == -1
          || (unsigned int)sub_18009D9BC(v12, 0, 2)
          || (v14 = sub_18009D6A0(v12), v15 = v14, v14 == -1)
          || (unsigned int)sub_18009D9BC(v12, v13, 0)
          || v15 == -1
          || (v16 = sub_18003A810(v15), (v17 = (void *)v16) == nullptr) )
        {
          sub_18009CAC0(v12);
        }
        else if ( sub_18009E484(v16, 1, v15, v12) == v15 )
        {
          sub_18009CAC0(v12);
          if ( (_DWORD)v15 )
            sub_180051E30(v17, v15);
          sub_18003A8D0(v17);
        }
        else
        {
          sub_18009CAC0(v12);
          sub_18003A8D0(v17);
        }
      }
    }
    *(_BYTE *)(v0 + 9904) = 1;
  }
  v18 = *(float *)(v0 + 9908);
  if ( v18 > 0.0 )
  {
    v19 = v18 - *(float *)(v0 + 32);
    *(float *)(v0 + 9908) = v19;
    if ( v19 <= 0.0 )
    {
      v20 = *(const CHAR **)(v0 + 40);
      if ( v20 )
        sub_180052070(v20);
      else
        *(_BYTE *)(v0 + 180) = 1;
      *(_DWORD *)(v0 + 9908) = 0;
    }
  }
  ++*(_DWORD *)(v1 + 5032);
  v21 = *(float *)(v1 + 32);
  *(_WORD *)(v1 + 9698) = 0;
  *(_DWORD *)(v1 + 5200) = 0;
  *(double *)(v1 + 5024) = v21 + *(double *)(v1 + 5024);
  v22 = *(_DWORD *)(v1 + 9732);
  if ( v22 < 0 )
  {
    v23 = 0;
    v24 = v22 / 2 + v22;
    if ( v24 > 0 )
      v23 = (unsigned int)v24;
    sub_180054C90(v1 + 9728, v23);
  }
  v25 = 3.4028235e38;
  *(_DWORD *)(v1 + 9728) = 0;
  v26 = *(int *)(v1 + 10724);
  v27 = *(float *)(v1 + 32);
  *(float *)(v1 + 10732) = (float)(v27 - *(float *)(v1 + 4 * v26 + 10484)) + *(float *)(v1 + 10732);
  *(float *)(v1 + 4 * v26 + 10484) = v27;
  v28 = *(float *)(v1 + 10732);
  v29 = *(_DWORD *)(v1 + 10728) + 1;
  *(_DWORD *)(v1 + 10724) = (*(_DWORD *)(v1 + 10724) + 1) % 60;
  v30 = 60;
  if ( v29 < 60 )
    v30 = v29;
  *(_DWORD *)(v1 + 10728) = v30;
  if ( v28 <= 0.0 )
    v31 = 3.4028235e38;
  else
    v31 = 1.0 / (float)(v28 / (float)v30);
  *(float *)(v1 + 184) = v31;
  v32 = *(_DWORD *)(v1 + 5100);
  if ( v32 < 0 )
  {
    v33 = 0;
    v34 = v32 / 2 + v32;
    if ( v34 > 0 )
      v33 = (unsigned int)v34;
    sub_180054B50(v1 + 5096, v33);
  }
  *(_DWORD *)(v1 + 5096) = 0;
  sub_180048440(*(unsigned __int8 *)(v1 + 90));
  v35 = qword_18010C470;
  v36 = **(_QWORD **)(qword_18010C470 + 8104);
  *(_QWORD *)(v36 + 4) = 5;
  *(_DWORD *)(v36 + 12) = 0;
  *(_QWORD *)(v36 + 16) = *(_QWORD *)(v35 + 16);
  *(_QWORD *)(v36 + 24) = *(_QWORD *)(v35 + 24);
  v37 = *(__int64 **)(v35 + 8104);
  v38 = *(int *)(v35 + 8096);
  v39 = &v37[v38];
  if ( v38 * 8 )
  {
    do
    {
      v40 = *v37++;
      v41 = (__m128)*(unsigned __int64 *)(v40 + 216);
      v42 = (__m128)*(unsigned __int64 *)(v40 + 208);
      *(_QWORD *)(v40 + 192) = v42.m128_u64[0];
      v43 = (__m128)*(unsigned __int64 *)(v40 + 8);
      *(_QWORD *)(v40 + 216) = 0;
      *(_QWORD *)(v40 + 208) = 0;
      *(_QWORD *)(v40 + 200) = v41.m128_u64[0];
      *(_QWORD *)(v40 + 32) = _mm_add_ps(v42, v43).m128_u64[0];
      v44 = *(float *)(v40 + 16);
      *(float *)(v40 + 44) = fmaxf(
                               0.0,
                               (float)(*(float *)(v40 + 20) - _mm_shuffle_ps(v42, v42, 85).m128_f32[0])
                             - _mm_shuffle_ps(v41, v41, 85).m128_f32[0]);
      *(float *)(v40 + 40) = fmaxf(0.0, (float)(v44 - v42.m128_f32[0]) - v41.m128_f32[0]);
    }
    while ( v37 != v39 );
  }
  sub_180045A90(v37, v39);
  sub_18003B4F0();
  sub_180045F80();
  *(_BYTE *)(v1 + 5048) = 1;
  v45 = *(__int64 **)(v1 + 8104);
  v46 = *(int *)(v1 + 8096);
  v47 = &v45[v46];
  if ( v46 * 8 )
  {
    do
    {
      v48 = *v45++;
      *(_BYTE *)(v48 + 88) = 0;
    }
    while ( v45 != v47 );
  }
  if ( *(_BYTE *)(v1 + 8656) )
  {
    v49 = *(_DWORD *)(v1 + 8684);
    if ( v49 == *(_DWORD *)(v1 + 5332) )
    {
      v50 = qword_18010C470;
      if ( *(_DWORD *)(qword_18010C470 + 5332) == v49 )
        *(_DWORD *)(qword_18010C470 + 5336) = v49;
      if ( *(_DWORD *)(v50 + 5384) == v49 )
        *(_BYTE *)(v50 + 5393) = 1;
    }
  }
  v51 = *(_BYTE *)(v1 + 129);
  if ( v51 && *(_BYTE *)(v1 + 252) || (*(_DWORD *)(v1 + 5300) = 0, v51) )
  {
    if ( *(int *)(v1 + 5316) > 1 )
      *(_DWORD *)(v1 + 5300) = *(_DWORD *)(v1 + 5312);
  }
  v52 = *(_DWORD *)(v1 + 5308);
  if ( *(_DWORD *)(v1 + 5312) )
  {
    if ( !v52 )
    {
LABEL_81:
      v53 = *(float *)(v1 + 32);
      goto LABEL_82;
    }
    if ( *(_DWORD *)(v1 + 5332) != v52 )
      goto LABEL_79;
  }
  else
  {
    *(_DWORD *)(v1 + 5320) = 0;
  }
  *(_DWORD *)(v1 + 5324) = 0;
  if ( !v52 )
    goto LABEL_81;
LABEL_79:
  *(float *)(v1 + 5320) = *(float *)(v1 + 32) + *(float *)(v1 + 5320);
  v53 = *(float *)(v1 + 32);
  if ( *(_DWORD *)(v1 + 5332) != v52 )
    *(float *)(v1 + 5324) = v53 + *(float *)(v1 + 5324);
LABEL_82:
  *(_DWORD *)(v1 + 5312) = v52;
  v54 = *(_DWORD *)(v1 + 5332);
  *(_DWORD *)(v1 + 5316) = 0;
  *(_DWORD *)(v1 + 5308) = 0;
  *(_WORD *)(v1 + 5328) = 0;
  if ( v54 && *(_DWORD *)(v1 + 5336) != v54 && *(_DWORD *)(v1 + 5380) == v54 )
  {
    if ( (*(_BYTE *)(v1 + 10228) & 2) != 0 )
      sub_180052F00("NewFrame(): ClearActiveID() because it isn't marked alive anymore!\n", v47);
    sub_180039FD0(0, 0);
    v53 = *(float *)(v1 + 32);
  }
  v55 = *(_DWORD *)(v1 + 5332);
  if ( v55 )
    *(float *)(v1 + 5340) = v53 + *(float *)(v1 + 5340);
  v56 = *(_DWORD *)(v1 + 9540);
  *(_DWORD *)(v1 + 5380) = v55;
  *(_DWORD *)(v1 + 5336) = 0;
  *(_BYTE *)(v1 + 5349) = 0;
  *(_BYTE *)(v1 + 5344) = 0;
  *(float *)(v1 + 5408) = v53 + *(float *)(v1 + 5408);
  if ( v56 && v55 != v56 )
    *(_DWORD *)(v1 + 9540) = 0;
  if ( !v55 )
  {
    *(_DWORD *)(v1 + 7664) = 0;
    *(_BYTE *)(v1 + 7668) = 0;
  }
  if ( *(_DWORD *)(v1 + 5388) < *(_DWORD *)(v1 + 5032) )
    *(_DWORD *)(v1 + 5384) = 0;
  v57 = *(unsigned int *)(v1 + 9216);
  *(_BYTE *)(v1 + 5393) = 0;
  if ( (_DWORD)v57 )
  {
    if ( *(float *)(v1 + 9244) >= *(float *)(v1 + 4368) )
      *(_DWORD *)(v1 + 9232) = v57;
  }
  else
  {
    *(_DWORD *)(v1 + 9232) = 0;
  }
  v58 = *(_QWORD *)(v1 + 5224);
  if ( v58 )
  {
    if ( *(float *)(v1 + 9244) >= *(float *)(v1 + 4368) )
      *(_DWORD *)(v1 + 9236) = *(_DWORD *)(v58 + 16);
  }
  else
  {
    *(_DWORD *)(v1 + 9236) = 0;
  }
  v59 = *(float *)(v1 + 9224);
  *(_DWORD *)(v1 + 9220) = v57;
  if ( (_DWORD)v57 )
  {
    *(_DWORD *)(v1 + 9228) = 0;
    *(_DWORD *)(v1 + 9216) = 0;
    *(float *)(v1 + 9224) = v53 + v59;
  }
  else if ( v59 > 0.0 )
  {
    v60 = v53 + *(float *)(v1 + 9228);
    *(float *)(v1 + 9228) = v60;
    if ( v60 >= fmaxf(0.25, v53 + v53) )
      *(_QWORD *)(v1 + 9224) = 0;
  }
  *(_DWORD *)(v1 + 8788) = *(_DWORD *)(v1 + 8784);
  *(_QWORD *)(v1 + 8780) = 2139095039;
  *(_WORD *)(v1 + 8657) = 0;
  *(_DWORD *)(v1 + 8796) = 0;
  *(_QWORD *)(v1 + 9704) = 0;
  sub_180047280(v57, v47);
  sub_18004E8F0();
  sub_1800476E0();
  if ( !*(_BYTE *)(v1 + 5050) )
  {
    v61 = *(float *)(v1 + 100);
    if ( v61 >= 0.0 )
      v25 = (float)*(double *)(v1 + 5024) - v61;
  }
  v62 = *(__int64 **)(v1 + 5128);
  v63 = *(int *)(v1 + 5120);
  v64 = &v62[v63];
  if ( v63 * 8 )
  {
    do
    {
      v65 = *v62;
      v66 = *(_BYTE *)(*v62 + 204);
      v67 = *(_WORD *)(*v62 + 218);
      *(_BYTE *)(v65 + 205) = v66;
      *(_BYTE *)(v65 + 204) = 0;
      *(_BYTE *)(v65 + 206) = 0;
      *(_WORD *)(v65 + 220) = v67;
      *(_WORD *)(v65 + 218) = 0;
      if ( !v66 && !*(_BYTE *)(v65 + 1076) && v25 > *(float *)(v65 + 652) )
      {
        v68 = *(_QWORD *)(v65 + 712);
        *(_BYTE *)(v65 + 1076) = 1;
        *(_DWORD *)(v65 + 1068) = *(_DWORD *)(v68 + 20);
        *(_DWORD *)(v65 + 1072) = *(_DWORD *)(v68 + 36);
        v69 = *(void **)(v65 + 272);
        if ( v69 )
        {
          *(_QWORD *)(v65 + 264) = 0;
          sub_18003A8D0(v69);
          *(_QWORD *)(v65 + 272) = 0;
        }
        sub_18005A290(*(_QWORD *)(v65 + 712));
        v70 = *(void **)(v65 + 440);
        if ( v70 )
        {
          *(_QWORD *)(v65 + 432) = 0;
          sub_18003A8D0(v70);
          *(_QWORD *)(v65 + 440) = 0;
        }
        v71 = *(void **)(v65 + 504);
        if ( v71 )
        {
          *(_QWORD *)(v65 + 496) = 0;
          sub_18003A8D0(v71);
          *(_QWORD *)(v65 + 504) = 0;
        }
        v72 = *(void **)(v65 + 520);
        if ( v72 )
        {
          *(_QWORD *)(v65 + 512) = 0;
          sub_18003A8D0(v72);
          *(_QWORD *)(v65 + 520) = 0;
        }
      }
      ++v62;
    }
    while ( v62 != v64 );
  }
  sub_18003B090(v1 + 224);
  v73 = qword_18010C470;
  v74 = *(_QWORD *)(qword_18010C470 + 5248);
  if ( v74 )
  {
    v75 = *(_DWORD *)(qword_18010C470 + 5332);
    *(_DWORD *)(qword_18010C470 + 5336) = v75;
    if ( *(_DWORD *)(v73 + 5384) == v75 )
      *(_BYTE *)(v73 + 5393) = 1;
    if ( *(_BYTE *)(v73 + 232) && *(float *)(v73 + 224) >= -256000.0 && *(float *)(v73 + 228) >= -256000.0 )
    {
      v76 = *(_QWORD *)(v74 + 960);
      v151 = _mm_sub_ps((__m128)*(unsigned __int64 *)(v73 + 224), (__m128)*(unsigned __int64 *)(v73 + 5360)).m128_u64[0];
      sub_1800454B0(v76, &v151, 1);
      sub_18004D450(*(_QWORD *)(v77 + 5248), 0);
      goto LABEL_140;
    }
    *(_QWORD *)(v73 + 5248) = 0;
    goto LABEL_139;
  }
  v78 = *(_QWORD *)(qword_18010C470 + 5368);
  if ( v78 )
  {
    v79 = *(_DWORD *)(qword_18010C470 + 5332);
    if ( *(_DWORD *)(v78 + 140) == v79 )
    {
      *(_DWORD *)(qword_18010C470 + 5336) = v79;
      if ( *(_DWORD *)(v73 + 5384) == v79 )
        *(_BYTE *)(v73 + 5393) = 1;
      if ( !*(_BYTE *)(v73 + 232) )
LABEL_139:
        sub_180039FD0(0, 0);
    }
  }
LABEL_140:
  v80 = *(_DWORD *)(qword_18010C470 + 8048) - 1;
  if ( v80 >= 0 )
  {
    do
    {
      v81 = *(_QWORD *)(*(_QWORD *)(qword_18010C470 + 8056) + 56LL * (unsigned int)v80 + 8);
      if ( v81 )
      {
        if ( (*(_DWORD *)(v81 + 20) & 0x8000000) != 0 )
          goto LABEL_146;
      }
    }
    while ( --v80 >= 0 );
  }
  if ( *(_QWORD *)(v1 + 8592) && *(float *)(v1 + 8620) > 0.0 )
  {
LABEL_146:
    v82 = fminf((float)(*(float *)(v1 + 32) * 6.0) + *(float *)(v1 + 8652), 1.0);
    goto LABEL_148;
  }
  v82 = fmaxf(*(float *)(v1 + 8652) - (float)(*(float *)(v1 + 32) * 10.0), 0.0);
LABEL_148:
  v83 = *(_OWORD *)(v1 + 9848);
  v84 = *(_DWORD *)(v1 + 9864);
  *(float *)(v1 + 8652) = v82;
  *(_OWORD *)(v1 + 9868) = v83;
  *(_DWORD *)(v1 + 9884) = v84;
  *(_DWORD *)(v1 + 9240) = 0;
  *(_QWORD *)(v1 + 10740) = -1;
  *(_DWORD *)(v1 + 10736) = -1;
  *(_WORD *)(v1 + 9848) = 0;
  sub_180047AB0();
  for ( i = 0; i < *(_DWORD *)(v1 + 8928); ++i )
  {
    v86 = *(float *)(*(_QWORD *)(v1 + 8936) + 4LL * i);
    if ( v86 >= 0.0 && v25 > v86 )
    {
      v87 = qword_18010C470;
      v88 = *(_QWORD *)(v1 + 8896) + 592LL * i;
      *(_QWORD *)(v88 + 496) = 0;
      v89 = *(void **)(v88 + 488);
      if ( v89 )
      {
        *(_QWORD *)(v88 + 480) = 0;
        sub_18003A8D0(v89);
        *(_QWORD *)(v88 + 488) = 0;
      }
      *(_BYTE *)(v88 + 570) = 1;
      v90 = *(void **)(v88 + 408);
      if ( v90 )
      {
        *(_QWORD *)(v88 + 400) = 0;
        sub_18003A8D0(v90);
        *(_QWORD *)(v88 + 408) = 0;
      }
      v91 = 0;
      for ( *(_BYTE *)(v88 + 585) = 1; v91 < *(_DWORD *)(v88 + 108); *(_WORD *)(*(_QWORD *)(v88 + 24) + 116 * v92 + 84) = -1 )
        v92 = v91++;
      *(_DWORD *)(*(_QWORD *)(v87 + 8936) + 4LL * (int)((v88 - *(_QWORD *)(v87 + 8896)) / 592)) = -1082130432;
    }
  }
  v93 = *(int *)(v1 + 8872);
  v94 = *(_QWORD *)(v1 + 8880);
  v95 = 136 * v93 + v94;
  if ( 136 * v93 )
  {
    do
    {
      v96 = *(float *)(v94 + 4);
      if ( v96 >= 0.0 && v25 > v96 )
      {
        sub_18005D1E0(v94 + 40);
        *(_DWORD *)(v94 + 4) = -1082130432;
      }
      v94 += 136;
    }
    while ( v94 != v95 );
  }
  if ( *(_BYTE *)(v1 + 5050) )
  {
    v97 = qword_18010C470;
    v98 = *(void **)(qword_18010C470 + 8024);
    if ( v98 )
    {
      *(_QWORD *)(qword_18010C470 + 8016) = 0;
      sub_18003A8D0(v98);
      *(_QWORD *)(v97 + 8024) = 0;
    }
    v99 = *(void **)(v97 + 8040);
    if ( v99 )
    {
      *(_QWORD *)(v97 + 8032) = 0;
      sub_18003A8D0(v99);
      *(_QWORD *)(v97 + 8040) = 0;
    }
    v100 = *(void **)(v97 + 9392);
    if ( v100 )
    {
      *(_QWORD *)(v97 + 9384) = 0;
      sub_18003A8D0(v100);
      *(_QWORD *)(v97 + 9392) = 0;
    }
    *(_DWORD *)(v97 + 9400) = 0;
    *(_DWORD *)(v97 + 9152) = 0;
    sub_180053750(v97 + 9160);
    sub_18006E0A0();
    v101 = *(_QWORD **)(v97 + 4408);
    v102 = *(int *)(v97 + 4400);
    v103 = &v101[v102];
    if ( v102 * 8 )
    {
      do
      {
        v104 = *v101;
        v105 = *(_QWORD *)(*v101 + 688LL);
        sub_180060330(*v101, 1);
        sub_180061120(&v151, v104);
        if ( *(_DWORD *)(v105 + 156) || v151 != *(_QWORD *)(*(_QWORD *)(v104 + 56) + 28LL) )
          sub_1800607D0(v104, v151, HIDWORD(v151));
        ++v101;
      }
      while ( v101 != v103 );
    }
  }
  v106 = *(_QWORD *)(v1 + 8120);
  *(_BYTE *)(v1 + 5050) = 0;
  if ( v106 && !*(_BYTE *)(v106 + 205) )
  {
    v107 = (unsigned int)(*(_DWORD *)(qword_18010C470 + 5136) - 1);
    if ( (int)v107 < 0 )
    {
LABEL_183:
      v108 = 0;
    }
    else
    {
      while ( 1 )
      {
        v108 = *(_QWORD *)(*(_QWORD *)(qword_18010C470 + 5144) + 8 * v107);
        if ( v108 )
        {
          if ( *(_BYTE *)(v108 + 205) && (*(_DWORD *)(v108 + 20) & 0x10200) != 0x10200 )
            break;
        }
        v107 = (unsigned int)(v107 - 1);
        if ( (int)v107 < 0 )
          goto LABEL_183;
      }
    }
    sub_18004D450(v108, 1);
  }
  sub_180053F70(v1 + 5168, 0);
  v109 = *(_DWORD *)(v1 + 8068);
  if ( v109 < 0 )
  {
    v110 = 0;
    v111 = v109 / 2 + v109;
    if ( v111 > 0 )
      v110 = (unsigned int)v111;
    sub_180054AF0(v1 + 8064, v110);
  }
  *(_DWORD *)(v1 + 8064) = 0;
  v112 = (int *)(v1 + 8016);
  v113 = *(_DWORD *)(v1 + 8020);
  if ( v113 < 0 )
  {
    v114 = 0;
    v115 = v113 / 2 + v113;
    if ( v115 > 0 )
      v114 = (unsigned int)v115;
    sub_180054C90(v1 + 8016, v114);
  }
  *v112 = 0;
  if ( !*(_DWORD *)(v1 + 8020) )
    sub_180054C90(v1 + 8016, 8);
  *(_DWORD *)(*(_QWORD *)(v1 + 8024) + 4LL * *v112) = 16;
  v116 = *v112;
  *v112 = v116 + 1;
  *(_DWORD *)(v1 + 7680) = *(_DWORD *)(*(_QWORD *)(v1 + 8024) + 4 * v116);
  sub_180053E00(v1 + 8032, 0);
  v117 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 10292) = 0;
  if ( *(_BYTE *)(v117 + 10289) )
  {
    v118 = *(_DWORD *)(v117 + 5312);
    *(_DWORD *)(v117 + 9240) = 7;
    if ( (unsigned __int8)sub_180046DB0(526, 1, 0) )
      *(_BYTE *)(v117 + 10289) = 0;
    v119 = *(_DWORD *)(v117 + 256);
    if ( v119 == 12288 )
    {
      if ( (unsigned __int8)sub_180046FF0(0, 0, 0) )
        *(_BYTE *)(v117 + 10290) = 0;
      if ( (unsigned __int8)sub_180046FF0(1, 0, 0) )
        *(_BYTE *)(v117 + 10290) = 1;
      if ( (unsigned __int8)sub_180046FF0(2, 0, 0) )
        *(_BYTE *)(v117 + 10290) = 2;
    }
    else if ( (unsigned __int8)sub_180046FF0(*(unsigned __int8 *)(v117 + 10290), 0, 0) && v118 )
    {
      *(_DWORD *)(v117 + 10292) = v118;
      *(_BYTE *)(v117 + 10289) = 0;
    }
    *(_DWORD *)(v117 + 7824) |= 0x40u;
    *(_DWORD *)(v117 + 7928) = 1060320051;
    if ( (unsigned __int8)sub_18004BB50(0) )
    {
      sub_18006F370((__int64)"HoveredId: 0x%08X", v118);
      sub_18006F370((__int64)"Press ESC to abort picking.");
      v150[0] = "Left";
      v150[1] = "Right";
      v150[2] = "Middle";
      if ( v119 == 12288 )
      {
        sub_18006F370((__int64)"Remap w/ Ctrl+Shift: click anywhere to select new mouse button.");
      }
      else
      {
        v120 = 3424;
        if ( !v118 )
          v120 = 3440;
        sub_18006F3E0(
          qword_18010C470 + v120,
          "Click %s Button to break in debugger! (remap w/ Ctrl+Shift)",
          v150[*(unsigned __int8 *)(v117 + 10290)]);
      }
      sub_180044DF0();
    }
    v117 = qword_18010C470;
  }
  *(_DWORD *)(v117 + 5304) = 0;
  v121 = v117;
  v122 = *(_DWORD *)(v117 + 10352) + 1;
  *(_BYTE *)(v117 + 10384) = 0;
  if ( *(_DWORD *)(v117 + 5032) != v122 )
    goto LABEL_239;
  v123 = 5312;
  if ( !*(_DWORD *)(v117 + 5312) )
    v123 = 5332;
  v124 = *(_DWORD *)(v117 + v123);
  if ( *(_DWORD *)(v117 + 10360) != v124 )
  {
    *(_DWORD *)(v117 + 10360) = v124;
    *(_DWORD *)(v117 + 10356) = -1;
    v125 = *(_DWORD *)(v117 + 10372);
    if ( v125 < 0 )
    {
      v126 = 0;
      v127 = v125 / 2 + v125;
      if ( v127 > 0 )
        v126 = (unsigned int)v127;
      sub_180054BB0(v117 + 10368, v126);
    }
    *(_DWORD *)(v117 + 10368) = 0;
    if ( *(int *)(v117 + 10392) > 0 )
      **(_BYTE **)(v117 + 10400) = 0;
    LOBYTE(v151) = 0;
    sub_1800544A0(v117 + 10392, 0, &v151);
    v117 = qword_18010C470;
  }
  if ( !v124 )
    goto LABEL_239;
  v128 = *(int *)(v121 + 10356);
  if ( (int)v128 >= 0 )
  {
    if ( (int)v128 >= *(_DWORD *)(v121 + 10368) )
      goto LABEL_239;
    v129 = *(_QWORD *)(v121 + 10376);
    if ( !*(_BYTE *)(v129 + 12 * v128 + 5) && *(char *)(v129 + 12 * v128 + 4) <= 2 )
      goto LABEL_236;
    LODWORD(v128) = v128 + 1;
    *(_DWORD *)(v121 + 10356) = v128;
  }
  if ( (_DWORD)v128 == -1 )
  {
    *(_DWORD *)(v121 + 5304) = v124;
LABEL_238:
    *(_BYTE *)(v121 + 10384) = 1;
    goto LABEL_239;
  }
  if ( (int)v128 >= 0 )
  {
LABEL_236:
    if ( (int)v128 < *(_DWORD *)(v121 + 10368) )
    {
      v130 = (int)v128;
      v131 = *(_QWORD *)(v121 + 10376);
      *(_DWORD *)(v121 + 5304) = *(_DWORD *)(v131 + 12 * v130);
      ++*(_BYTE *)(v131 + 12 * v130 + 4);
      goto LABEL_238;
    }
  }
LABEL_239:
  if ( *(float *)(v117 + 10296) > 0.0 )
  {
    v132 = 16LL * *(int *)(v117 + 7948);
    v133 = v117 + v132 + 3432;
    v134 = v117 + v132 + 3428;
    v135 = v132 + 3424;
    sub_1800B4640();
    sub_180036790(v137, v136, v138, v135 + v117, v134, v133);
    *(_DWORD *)(v117 + 16LL * *(int *)(v117 + 7948) + 3436) = 1065353216;
    v139 = *(float *)(v117 + 10296) - *(float *)(v117 + 32);
    *(float *)(v117 + 10296) = v139;
    if ( v139 <= 0.0 )
    {
      v140 = *(int *)(v117 + 7948);
      if ( (_DWORD)v140 != 59 )
        *(_OWORD *)(v117 + 16 * (v140 + 214)) = *(_OWORD *)(v117 + 10300);
      *(_DWORD *)(v117 + 7948) = 59;
    }
  }
  v141 = *(_BYTE *)(v1 + 10281);
  if ( v141 )
  {
    v142 = v141 - 1;
    *(_BYTE *)(v1 + 10281) = v142;
    if ( !v142 )
    {
      *(_DWORD *)(v1 + 7684) = 0;
      *(_BYTE *)(v1 + 10282) = 0;
    }
  }
  v143 = *(_BYTE *)(v1 + 10280);
  if ( v143 )
  {
    v144 = v143 - 1;
    *(_BYTE *)(v1 + 10280) = v144;
    if ( !v144 )
    {
      sub_180052F00("(Debug Log: Auto-disabled some ImGuiDebugLogFlags after 2 frames)\n");
      v117 = qword_18010C470;
      *(_DWORD *)(v1 + 10228) &= ~*(_DWORD *)(v1 + 10276);
      *(_DWORD *)(v1 + 10276) = 0;
    }
  }
  *(_BYTE *)(v1 + 5049) = 1;
  *(_DWORD *)(v117 + 7824) |= 2u;
  *(_DWORD *)(v117 + 7856) = 1137180672;
  *(_DWORD *)(v117 + 7860) = 1137180672;
  *(_DWORD *)(v117 + 7832) = 4;
  sub_180040700("Debug##Default", 0, 0);
  v145 = qword_18010C470;
  *(_DWORD *)(v1 + 10188) = 0;
  *(_WORD *)(v1 + 10192) = *(_WORD *)(v145 + 5168);
  *(_WORD *)(v1 + 10194) = *(_WORD *)(*(_QWORD *)(v145 + 5216) + 264LL);
  *(_WORD *)(v1 + 10196) = *(_WORD *)(*(_QWORD *)(v145 + 5216) + 416LL);
  *(_WORD *)(v1 + 10198) = *(_WORD *)(v145 + 7952);
  *(_WORD *)(v1 + 10200) = *(_WORD *)(v145 + 7968);
  *(_WORD *)(v1 + 10202) = *(_WORD *)(v145 + 7984);
  *(_WORD *)(v1 + 10204) = *(_WORD *)(v145 + 8000);
  *(_WORD *)(v1 + 10206) = *(_WORD *)(v145 + 8032);
  *(_WORD *)(v1 + 10208) = *(_WORD *)(v145 + 8016);
  *(_WORD *)(v1 + 10210) = *(_WORD *)(v145 + 8064);
  *(_WORD *)(v1 + 10212) = *(_WORD *)(v145 + 9696);
  if ( *(_BYTE *)(v1 + 132) )
  {
    if ( *(_BYTE *)(v1 + 10288) == 0xFF )
      LOBYTE(v146) = 0;
    else
      v146 = (*(char *)(v1 + 10288) + (*(_DWORD *)(v1 + 5032) % 4 == 0)) % 10;
  }
  else
  {
    LOBYTE(v146) = -1;
  }
  *(_BYTE *)(v1 + 10288) = v146;
  v147 = *(_QWORD *)(v1 + 9984);
  result = 32LL * *(int *)(v1 + 9976);
  v149 = result + v147;
  if ( result )
  {
    do
    {
      if ( *(_DWORD *)(v147 + 4) == 1 )
        result = (*(__int64 (__fastcall **)(__int64, __int64))(v147 + 16))(v1, v147);
      v147 += 32;
    }
    while ( v147 != v149 );
  }
  return result;
}
