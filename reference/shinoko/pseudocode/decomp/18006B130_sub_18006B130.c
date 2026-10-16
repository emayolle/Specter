// sub_18006B130 size=6211
char __fastcall sub_18006B130(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // r14
  unsigned int *v5; // rdi
  bool v7; // zf
  __int64 v8; // r13
  __int64 v9; // r15
  __int64 v10; // r12
  unsigned int v11; // ebx
  __int64 v12; // rax
  float v13; // xmm13_4
  float v14; // xmm0_4
  float v15; // xmm1_4
  unsigned int v16; // eax
  float v17; // xmm2_4
  __int64 v18; // rdx
  __int64 v19; // rax
  float v20; // xmm1_4
  __int64 v21; // rax
  __int64 v22; // rcx
  __int64 v23; // rax
  int v24; // xmm0_4
  int v25; // xmm1_4
  int v26; // xmm2_4
  float *v27; // rax
  __int64 v28; // rsi
  __int64 v29; // rcx
  unsigned int v30; // edx
  float v31; // xmm2_4
  __int64 v32; // rax
  float v33; // xmm6_4
  float v34; // xmm7_4
  float v35; // xmm9_4
  signed int i; // ebx
  __int64 v37; // r9
  int v38; // eax
  __int64 v39; // rdx
  __int64 v40; // r10
  __int64 v41; // rcx
  float v42; // xmm1_4
  unsigned int v43; // r8d
  float v44; // xmm0_4
  unsigned int v45; // eax
  int v46; // eax
  unsigned int v47; // eax
  unsigned int v48; // ebx
  __m128 v49; // xmm6
  float v50; // xmm6_4
  float v51; // xmm2_4
  unsigned int v52; // xmm1_4
  unsigned int v53; // r9d
  __int64 v54; // rdx
  __int64 v55; // r12
  __int16 v56; // r15
  unsigned int v57; // eax
  int v58; // eax
  int v59; // esi
  int v60; // ebx
  __m128i v61; // xmm6
  __int64 v62; // rax
  __int64 v63; // rdx
  __int64 v64; // rsi
  unsigned __int64 v65; // r8
  __m128i v66; // xmm3
  __m128i v67; // xmm2
  __m128i v68; // xmm1
  __m128i v69; // xmm2
  int j; // edx
  __int64 v71; // rcx
  __int64 v72; // rax
  signed int v73; // eax
  int v74; // r13d
  __int64 v75; // r9
  unsigned int v76; // ecx
  int v77; // eax
  __int64 v78; // r10
  int v79; // esi
  __int64 v80; // rax
  unsigned __int16 v81; // r12
  __int64 v82; // r11
  __int64 v83; // r14
  int v84; // edx
  int v85; // ecx
  __int64 v86; // rax
  float v87; // xmm0_4
  BOOL v88; // eax
  int v89; // ecx
  unsigned int v90; // eax
  __int64 v91; // rdx
  char v92; // bl
  float *v93; // r8
  float *v94; // r9
  __int64 v95; // rax
  float v96; // xmm1_4
  float v97; // xmm3_4
  float v98; // xmm4_4
  __int64 v99; // r13
  __int64 v100; // r15
  int v101; // esi
  unsigned __int64 v102; // rbx
  int v103; // ecx
  int v104; // eax
  __int64 v105; // rdx
  _OWORD *v106; // rsi
  int v107; // r10d
  signed int v108; // r15d
  char v109; // r9
  char v110; // cl
  __int64 v111; // r8
  unsigned __int64 v112; // rcx
  char v113; // dl
  int v114; // eax
  __int16 v115; // dx
  float v116; // xmm10_4
  float v117; // xmm11_4
  float v118; // xmm9_4
  float v119; // xmm8_4
  int v120; // r12d
  int k; // r15d
  unsigned __int64 v122; // r11
  int v123; // r14d
  float v124; // xmm5_4
  float v125; // xmm6_4
  float v126; // xmm4_4
  float v127; // xmm3_4
  int v128; // r9d
  int v129; // r8d
  unsigned __int64 v130; // rdx
  __int64 v131; // rcx
  unsigned __int64 v132; // r10
  __int64 v133; // rax
  __m128 v134; // xmm2
  __m128 v135; // xmm1
  __m128 v136; // xmm2
  __int64 v137; // rdx
  __int64 v138; // rax
  __int64 v139; // rdx
  int m; // edx
  __int64 v141; // r10
  unsigned int v142; // ecx
  __int64 v143; // rax
  int v144; // r9d
  __int64 v145; // r8
  __int64 v146; // rcx
  float *v147; // rax
  _OWORD *v148; // rax
  __int64 v149; // rax
  __int64 v150; // rcx
  int v151; // eax
  int n; // r8d
  int v153; // eax
  __int64 v154; // rax
  _OWORD *v155; // rcx
  __int64 v156; // rdx
  int v157; // r11d
  float v158; // xmm7_4
  float v159; // xmm6_4
  float v160; // xmm4_4
  int ii; // r10d
  int v162; // eax
  __int64 v163; // rcx
  __int64 v164; // rax
  int v165; // edx
  float v166; // xmm1_4
  float v167; // xmm2_4
  float v168; // xmm1_4
  float v169; // xmm5_4
  __int64 v170; // rcx
  float v171; // xmm5_4
  float v172; // xmm1_4
  float v173; // xmm1_4
  float v174; // xmm1_4
  __int64 v175; // rcx
  bool v176; // al
  __int64 v177; // rcx
  int v178; // eax
  __int64 v179; // rdx
  int v180; // eax
  float v181; // xmm6_4
  float v182; // xmm7_4
  __int16 v183; // bx
  unsigned __int32 v184; // xmm0_4
  unsigned int v185; // eax
  float v186; // xmm6_4
  float v187; // xmm2_4
  float v188; // xmm3_4
  float v189; // xmm3_4
  float v190; // xmm0_4
  float v191; // xmm3_4
  float v192; // xmm3_4
  float v193; // xmm7_4
  __int64 v194; // rax
  __int64 v195; // rsi
  __int64 v196; // r9
  unsigned int v197; // ecx
  __int64 v198; // r10
  char v199; // bl
  __int64 v200; // r8
  signed int v201; // r11d
  __int64 v202; // rax
  float v203; // xmm0_4
  char v204; // cl
  char v205; // dl
  unsigned int v206; // xmm0_4
  int v207; // ecx
  int *v208; // r8
  __int64 v209; // rax
  __int64 v210; // rdx
  __int64 v211; // rcx
  __int64 v212; // rdx
  __int64 v213; // rcx
  __int64 v214; // [rsp+40h] [rbp-C0h]
  __int64 v215; // [rsp+48h] [rbp-B8h]
  __m128 v216; // [rsp+50h] [rbp-B0h] BYREF
  int v217; // [rsp+60h] [rbp-A0h]
  int v218; // [rsp+64h] [rbp-9Ch]
  __int64 v219; // [rsp+68h] [rbp-98h]
  __int64 v220; // [rsp+70h] [rbp-90h]
  __int64 v221; // [rsp+78h] [rbp-88h]
  __int64 v222; // [rsp+80h] [rbp-80h]
  _DWORD *v223; // [rsp+88h] [rbp-78h]
  __int128 v224; // [rsp+90h] [rbp-70h] BYREF
  _DWORD v225[2]; // [rsp+A0h] [rbp-60h]
  __int64 v226; // [rsp+A8h] [rbp-58h] BYREF
  __int128 v227; // [rsp+B0h] [rbp-50h]
  int v228; // [rsp+C0h] [rbp-40h]
  unsigned __int64 v229; // [rsp+C8h] [rbp-38h]
  __int128 v230; // [rsp+D0h] [rbp-30h]
  int v231; // [rsp+E0h] [rbp-20h]
  __int64 v232; // [rsp+E8h] [rbp-18h]
  __int128 v233; // [rsp+F0h] [rbp-10h]
  int v234; // [rsp+100h] [rbp+0h]
  unsigned __int64 v235; // [rsp+108h] [rbp+8h]
  unsigned __int64 v236; // [rsp+110h] [rbp+10h]
  unsigned __int32 v237; // [rsp+1F0h] [rbp+F0h] BYREF
  unsigned __int32 v238; // [rsp+1F4h] [rbp+F4h]
  float v239; // [rsp+1F8h] [rbp+F8h] BYREF
  float v240; // [rsp+1FCh] [rbp+FCh]
  signed int v241; // [rsp+200h] [rbp+100h]
  int v242; // [rsp+208h] [rbp+108h]

  v4 = qword_18010C470;
  v214 = qword_18010C470;
  v5 = *(unsigned int **)(qword_18010C470 + 8856);
  if ( !v5 )
    return sub_180049A30("EndTable() call should only be done while in BeginTable() scope!");
  if ( !*((_BYTE *)v5 + 567) )
    sub_180069320((__int64)v5);
  v7 = *((_BYTE *)v5 + 568) == 0;
  v8 = *((_QWORD *)v5 + 49);
  v9 = *((_QWORD *)v5 + 48);
  v10 = *((_QWORD *)v5 + 2);
  v11 = v5[1];
  v222 = v8;
  v215 = v9;
  v220 = v10;
  if ( !v7 )
    sub_18006C980(v5);
  if ( (v11 & 0x20) != 0
    && *((_WORD *)v5 + 261) != 0xFFFF
    && !*(_DWORD *)(qword_18010C470 + 5308)
    && !*(_DWORD *)(qword_18010C470 + 5312)
    && *(_BYTE *)(qword_18010C470 + 2863)
    && !*(_BYTE *)(qword_18010C470 + 7208) )
  {
    sub_18006D3B0();
  }
  if ( *((_WORD *)v5 + 60) )
    v12 = *((_QWORD *)v5 + 57) + 24LL * (*((__int16 *)v5 + 60) - 1);
  else
    v12 = (__int64)(v5 + 106);
  *(_QWORD *)(v8 + 328) = *(_QWORD *)(v10 + 96);
  *(_QWORD *)(v8 + 320) = *(_QWORD *)(v10 + 104);
  *(_QWORD *)(v8 + 304) = *(_QWORD *)(v10 + 112);
  v13 = *((float *)v5 + 32);
  v223 = (_DWORD *)v12;
  if ( v8 == v9 )
  {
    if ( (v11 & 0x20000) == 0 )
    {
      v14 = fmaxf(*((float *)v5 + 63), v13);
      *((float *)v5 + 67) = v14;
      *((float *)v5 + 63) = v14;
    }
  }
  else
  {
    *(float *)(v8 + 308) = v13;
  }
  v15 = *((float *)v5 + 63);
  *((float *)v5 + 71) = fmaxf(*((float *)v5 + 71), v15);
  *(float *)(v12 + 4) = v15 - *((float *)v5 + 61);
  v16 = v5[1];
  if ( (v16 & 0x1000000) != 0 )
  {
    if ( (v16 & 0x400) != 0 )
      v17 = 1.0;
    else
      v17 = 0.0;
    v18 = *((_QWORD *)v5 + 49);
    v19 = *((__int16 *)v5 + 271);
    v20 = *(float *)(v18 + 304);
    if ( (_WORD)v19 != 0xFFFF )
      v20 = fmaxf(
              v20,
              (float)((float)(*(float *)(116 * v19 + *((_QWORD *)v5 + 3) + 60) + *((float *)v5 + 48))
                    + *((float *)v5 + 47))
            - v17);
    if ( *((_WORD *)v5 + 265) != 0xFFFF )
      v20 = fmaxf(v20, *((float *)v5 + 56));
    *(float *)(v18 + 304) = v20 + *(float *)(*((_QWORD *)v5 + 2) + 8LL);
  }
  if ( (v11 & 0x100000) == 0 )
    sub_18005A7D0(*(_QWORD *)(v8 + 712));
  v21 = *(_QWORD *)(v8 + 712);
  v22 = *(int *)(v21 + 160);
  v23 = *(_QWORD *)(v21 + 168);
  v22 *= 2;
  v24 = *(_DWORD *)(v23 + 8 * v22 - 12);
  v25 = *(_DWORD *)(v23 + 8 * v22 - 8);
  v26 = *(_DWORD *)(v23 + 8 * v22 - 4);
  *(_DWORD *)(v8 + 608) = *(_DWORD *)(v23 + 8 * v22 - 16);
  *(_DWORD *)(v8 + 612) = v24;
  *(_DWORD *)(v8 + 616) = v25;
  *(_DWORD *)(v8 + 620) = v26;
  if ( (v11 & 0x780) != 0 )
  {
    v27 = *((float **)v5 + 48);
    if ( v27[155] > *((float *)v5 + 61)
      && *((float *)v5 + 63) > v27[153]
      && v27[154] > *((float *)v5 + 60)
      && *((float *)v5 + 62) > v27[152] )
    {
      v28 = *(_QWORD *)(*((_QWORD *)v5 + 49) + 712LL);
      sub_18005D640(*((_QWORD *)v5 + 52), v28, 0, a4);
      sub_18005A5E0(v28, v5 + 80, v5 + 82, 0);
      if ( *((_WORD *)v5 + 60) )
        v29 = *((_QWORD *)v5 + 57) + 24LL * (*((__int16 *)v5 + 60) - 1);
      else
        v29 = (__int64)(v5 + 106);
      v30 = v5[1];
      if ( (v30 & 0x100) != 0 )
        v31 = 1.0;
      else
        v31 = 0.0;
      v32 = 65;
      v33 = *((float *)v5 + 67);
      if ( *((__int16 *)v5 + 276) < 1 )
        v32 = 69;
      v34 = fmaxf(*((float *)v5 + 65), *(float *)&v5[v32] + *((float *)v5 + 58)) + v31;
      if ( *((_BYTE *)v5 + 571) )
        v35 = fminf(v33, *(float *)&v5[v32] + *(float *)(v29 + 8));
      else
        v35 = v34;
      if ( (v30 & 0x200) != 0 )
      {
        for ( i = 0; i < (int)v5[27]; ++i )
        {
          v37 = i;
          v38 = *(_DWORD *)(*((_QWORD *)v5 + 9) + 4 * ((__int64)i >> 5));
          if ( _bittest(&v38, i & 0x1F) )
          {
            v39 = *((_QWORD *)v5 + 3);
            v40 = *(__int16 *)(*((_QWORD *)v5 + 5) + 2LL * i);
            v41 = 116 * v40;
            LOBYTE(v37) = *((_WORD *)v5 + 265) == (_WORD)v40 && *((_WORD *)v5 + 61) == *((_WORD *)v5 + 60);
            v42 = *(float *)(v39 + v41 + 12);
            if ( v42 <= *((float *)v5 + 74) || (_BYTE)v37 )
            {
              if ( *(_WORD *)(v39 + v41 + 92) != 0xFFFF
                || (*(_DWORD *)(v39 + 116 * v40) & 0x40000020) == 0
                || (v43 = v5[1], (v43 & 0xE000) == 0x4000) && (v43 & 0x10000) == 0 )
              {
                if ( *(float *)(v39 + v41 + 36) < v42 )
                {
                  if ( *((__int16 *)v5 + 278) == i + 1 )
                  {
                    v44 = v33;
                  }
                  else
                  {
                    v45 = v5[1];
                    if ( (v45 & 0x1000) != 0 && (*((_WORD *)v5 + 262) == (_WORD)v40 || (_BYTE)v37) )
                      v44 = v33;
                    else
                      v44 = (v45 & 0x1800) != 0 ? v35 : v33;
                  }
                  if ( v44 > v34 )
                  {
                    v237 = *(_DWORD *)(v39 + v41 + 12);
                    *(float *)&v238 = v44;
                    v239 = v42;
                    v240 = v34;
                    v46 = sub_18006D310(v5, (unsigned int)i, (unsigned int)v40, v37);
                    sub_18005C320(v28, (unsigned int)&v239, (unsigned int)&v237, v46, 1065353216);
                  }
                }
              }
            }
          }
        }
      }
      v47 = v5[1];
      if ( (v47 & 0x500) == 0 )
        goto LABEL_82;
      v48 = v5[41];
      v49 = *((__m128 *)v5 + 15);
      v216 = v49;
      if ( (v47 & 0x500) == 0x500 )
      {
        sub_18005C460(v28, (unsigned int)&v216, (unsigned int)&v216.m128_u32[2], v48, 0);
        goto LABEL_82;
      }
      if ( (v47 & 0x400) != 0 )
      {
        v237 = v49.m128_i32[0];
        v238 = _mm_shuffle_ps(v49, v49, 255).m128_u32[0];
        sub_18005C320(v28, (unsigned int)&v216, (unsigned int)&v237, v48, 1065353216);
        v237 = _mm_shuffle_ps(v49, v49, 170).m128_u32[0];
        v50 = _mm_shuffle_ps(v49, v49, 85).m128_f32[0];
      }
      else
      {
        if ( (v47 & 0x100) == 0 )
          goto LABEL_82;
        v237 = _mm_shuffle_ps(v49, v49, 170).m128_u32[0];
        v238 = _mm_shuffle_ps(v49, v49, 85).m128_u32[0];
        sub_18005C320(v28, (unsigned int)&v216, (unsigned int)&v237, v48, 1065353216);
        v237 = v49.m128_i32[0];
        v50 = _mm_shuffle_ps(v49, v49, 255).m128_f32[0];
      }
      *(float *)&v238 = v50;
      sub_18005C320(v28, (unsigned int)&v237, (unsigned int)&v216.m128_u32[2], v48, 1065353216);
LABEL_82:
      if ( *((char *)v5 + 4) < 0 )
      {
        v51 = *((float *)v5 + 32);
        if ( *((float *)v5 + 63) > v51 && v51 >= *((float *)v5 + 77) && *((float *)v5 + 79) > v51 )
        {
          v52 = v5[43];
          v53 = v5[42];
          v237 = v5[44];
          v239 = *(float *)&v52;
          *(float *)&v238 = v51;
          v240 = v51;
          sub_18005C320(v28, (unsigned int)&v239, (unsigned int)&v237, v53, 1065353216);
        }
      }
      sub_18005A7D0(v28);
    }
  }
  v54 = *(_QWORD *)(v8 + 712);
  v216.m128_u64[0] = *((_QWORD *)v5 + 52);
  sub_18005D640(v216.m128_u64[0], v54, 0, a4);
  if ( (v5[1] & 0x100000) == 0 )
  {
    v55 = qword_18010C470;
    v56 = *((_WORD *)v5 + 276);
    v219 = *((_QWORD *)v5 + 52);
    LOWORD(v239) = *((_WORD *)v5 + 278);
    v57 = v5[27];
    v225[0] = 0;
    v226 = 0;
    v228 = 0;
    v229 = 0;
    v58 = (int)(2 * v57 + 35) >> 5;
    v231 = 0;
    v232 = 0;
    v234 = 0;
    v235 = 0;
    v59 = 4 * v58;
    v60 = 20 * v58;
    v221 = qword_18010C470;
    LOWORD(v237) = v56;
    v224 = 0;
    v227 = 0;
    v230 = 0;
    v233 = 0;
    v218 = v58;
    v242 = 4 * v58;
    v61 = _mm_shuffle_epi32(_mm_cvtsi32_si128(4 * v58), 0);
    if ( 20 * v58 > *(_DWORD *)(qword_18010C470 + 10756) )
    {
      v62 = sub_18003A810(v60);
      v63 = *(_QWORD *)(v55 + 10760);
      v64 = v62;
      if ( v63 )
      {
        sub_1800B8BD0(v62, v63, *(int *)(v55 + 10752));
        sub_18003A8D0(*(LPVOID *)(v55 + 10760));
      }
      *(_QWORD *)(v55 + 10760) = v64;
      v59 = v242;
      *(_DWORD *)(v55 + 10756) = v60;
    }
    sub_1800B9280(*(_QWORD *)(v55 + 10760), 0, v60);
    v65 = *(_QWORD *)(v55 + 10760);
    v236 = v65;
    v66 = _mm_unpacklo_epi64((__m128i)v65, (__m128i)v65);
    if ( dword_1800FA030 < 2 )
    {
      for ( j = 0; j < 4; ++j )
      {
        v71 = v65 + j * v59;
        v72 = 32LL * j;
        *(__int64 *)((char *)&v226 + v72) = v71;
      }
    }
    else
    {
      v67 = _mm_loadl_epi64((const __m128i *)&xmmword_1800E68A0);
      v68 = _mm_add_epi64(_mm_cvtepi32_epi64(_mm_mullo_epi32(_mm_move_epi64(v61), v67)), v66);
      v226 = v68.m128i_i64[0];
      v229 = _mm_srli_si128(v68, 8).m128i_u64[0];
      v69 = _mm_add_epi64(
              _mm_cvtepi32_epi64(
                _mm_mullo_epi32(
                  _mm_move_epi64(v61),
                  _mm_add_epi32(_mm_load_si128((const __m128i *)&xmmword_1800E6890), v67))),
              v66);
      v232 = v69.m128i_i64[0];
      v235 = _mm_srli_si128(v69, 8).m128i_u64[0];
    }
    if ( (int)v5[27] > 0 )
    {
      v73 = 0;
      v74 = 0;
      v241 = 0;
      v217 = (v56 > 0) + 1;
      do
      {
        v75 = v73;
        v76 = v73 & 0x1F;
        v77 = *(_DWORD *)(*((_QWORD *)v5 + 11) + 4 * ((__int64)v73 >> 5));
        if ( _bittest(&v77, v76) )
        {
          v78 = *((_QWORD *)v5 + 3) + 116 * v75;
          v79 = 0;
          do
          {
            v80 = 98;
            if ( v79 )
              v80 = 100;
            v81 = *(_WORD *)(v78 + v80);
            v82 = 32LL * v81;
            v83 = *(_QWORD *)(v219 + 16);
            v84 = *(_DWORD *)(v82 + v83);
            if ( v84 > 0 )
            {
              v85 = v84 - 1;
              v86 = *(_QWORD *)(v82 + v83 + 8);
              if ( *(_DWORD *)(v86 + 72LL * (v84 - 1) + 40) || *(_QWORD *)(v86 + 72LL * v85 + 48) )
                v85 = *(_DWORD *)(v82 + v83);
              else
                *(_DWORD *)(v82 + v83) = v85;
              if ( v85 == 1 )
              {
                if ( (*(_DWORD *)v78 & 0x100) != 0
                  || ((__int16)v237 > 0
                    ? (v79
                     ? (v87 = *(float *)(v78 + 72))
                     : (v87 = fmaxf(*(float *)(v78 + 68), *(float *)(v78 + 76))))
                    : (v87 = fmaxf(*(float *)(v78 + 72), *(float *)(v78 + 76))),
                      v87 <= *(float *)(v78 + 44)) )
                {
                  v88 = SLOWORD(v239) <= 0 || v241 >= *((__int16 *)v5 + 278);
                  if ( (__int16)v237 <= 0 || v79 )
                    v89 = 2;
                  else
                    v89 = 0;
                  v90 = v89 | v88;
                  v91 = 8LL * v90;
                  v92 = v90;
                  if ( v225[v91] )
                  {
                    v93 = (float *)((char *)&v225[-4] + ((v91 * 4) | 8));
                    v94 = (float *)((char *)&v225[-4] + ((v91 * 4) | 0xC));
                  }
                  else
                  {
                    v225[8 * v90 - 4] = 2139095039;
                    v93 = (float *)&v225[v91 - 2];
                    v225[8 * v90 - 3] = 2139095039;
                    v94 = (float *)&v225[v91 - 1];
                    v225[v91 - 2] = -8388609;
                    v225[v91 - 1] = -8388609;
                  }
                  *(_DWORD *)(*(&v226 + 4 * v90) + 4 * ((unsigned __int64)v81 >> 5)) |= 1 << (v81 & 0x1F);
                  ++v225[8 * v90];
                  v95 = *(_QWORD *)(v82 + v83 + 8);
                  v96 = *(float *)(v95 + 4);
                  v97 = *(float *)(v95 + 8);
                  v98 = *(float *)(v95 + 12);
                  if ( *(float *)&v225[v91 - 4] > *(float *)v95 )
                    v225[v91 - 4] = *(_DWORD *)v95;
                  if ( *(float *)&v225[v91 - 3] > v96 )
                    *(float *)&v225[v91 - 3] = v96;
                  if ( v97 > *v93 )
                    *v93 = v97;
                  if ( v98 > *v94 )
                    *v94 = v98;
                  v74 |= 1 << v92;
                }
              }
            }
            ++v79;
          }
          while ( v79 < v217 );
          *(_WORD *)(v78 + 96) = -1;
        }
        v73 = v241 + 1;
        v241 = v73;
      }
      while ( v73 < (int)v5[27] );
      if ( v74 )
      {
        v99 = v219;
        v100 = v221;
        v101 = *(_DWORD *)(v219 + 4) - 2;
        v102 = v236 + 16 * v218;
        v103 = *(_DWORD *)(v221 + 8948);
        if ( v101 > v103 )
        {
          if ( v103 )
            v104 = v103 + v103 / 2;
          else
            v104 = 8;
          v105 = (unsigned int)v101;
          if ( v104 > v101 )
            v105 = (unsigned int)v104;
          sub_1800691F0(v221 + 8944, v105);
        }
        *(_DWORD *)(v100 + 8944) = v101;
        v106 = *(_OWORD **)(v100 + 8952);
        v107 = *(_DWORD *)(v99 + 4) - 1;
        if ( v107 >= 2 )
        {
          v108 = 2;
          do
          {
            v109 = v108 & 0x1F;
            v110 = v107 & 0x1F;
            if ( v107 > (v108 | 0x1F) )
              v110 = 31;
            v111 = (__int64)v108 >> 5;
            v108 = (v108 + 32) & 0xFFFFFFE0;
            *(_DWORD *)(v102 + 4 * v111) |= -(1 << v109) & ((1LL << (v110 + 1)) - 1);
          }
          while ( v108 <= v107 );
          v99 = v219;
        }
        v112 = *((unsigned __int16 *)v5 + 282);
        v113 = v112 & 0x1F;
        v112 >>= 5;
        v114 = *(_DWORD *)(v102 + 4 * v112) & ~(1 << v113);
        v115 = v237;
        *(_DWORD *)(v102 + 4 * v112) = v114;
        v116 = *((float *)v5 + 88);
        v117 = *((float *)v5 + 89);
        v118 = *((float *)v5 + 90);
        v119 = *((float *)v5 + 91);
        v120 = *(_DWORD *)(v99 + 4) - ((v115 > 0) + 2);
        for ( k = 0; k < 4; ++k )
        {
          while ( 1 )
          {
            v122 = 32LL * k;
            v123 = v225[v122 / 4];
            if ( v123 )
            {
              v124 = *(float *)&v225[8 * k - 4];
              v125 = *(float *)&v225[8 * k - 3];
              v126 = *(float *)&v225[8 * k - 2];
              v127 = *(float *)&v225[8 * k - 1];
              if ( (k & 1) == 0 || SLOWORD(v239) <= 0 )
                v124 = fminf(v124, v116);
              if ( (k & 2) == 0 || v115 <= 0 )
                v125 = fminf(v125, v117);
              if ( (k & 1) != 0 )
                v126 = fmaxf(v126, v118);
              if ( (k & 2) != 0 && (v5[1] & 0x20000) == 0 )
                v127 = fmaxf(v127, v119);
              v120 -= v123;
              v128 = v242 >> 2;
              if ( v242 >> 2 > 0 )
              {
                v129 = 0;
                if ( (unsigned int)v128 < 2 )
                  goto LABEL_308;
                v130 = *(&v226 + 4 * k);
                v131 = v128 - 1;
                v132 = v102 + 4 * v131;
                if ( v102 <= v130 + 4 * v131 && v132 >= v130 )
                  goto LABEL_308;
                if ( v102 <= (unsigned __int64)&v226 + v122 && v132 >= (unsigned __int64)&v226 + v122 )
                  goto LABEL_308;
                if ( (unsigned int)v128 < 0x10 )
                  goto LABEL_175;
                do
                {
                  v133 = v129;
                  v129 += 16;
                  v134 = (__m128)_mm_loadu_si128((const __m128i *)(v130 + 4 * v133 + 16));
                  *(__m128 *)(v102 + 4 * v133) = _mm_andnot_ps(
                                                   (__m128)_mm_loadu_si128((const __m128i *)(v130 + 4 * v133)),
                                                   (__m128)_mm_loadu_si128((const __m128i *)(v102 + 4 * v133)));
                  v135 = (__m128)_mm_loadu_si128((const __m128i *)(v130 + 4 * v133 + 32));
                  *(__m128 *)(v102 + 4 * v133 + 16) = _mm_andnot_ps(
                                                        v134,
                                                        (__m128)_mm_loadu_si128((const __m128i *)(v102 + 4 * v133 + 16)));
                  v136 = (__m128)_mm_loadu_si128((const __m128i *)(v130 + 4 * v133 + 48));
                  *(__m128 *)(v102 + 4 * v133 + 32) = _mm_andnot_ps(
                                                        v135,
                                                        (__m128)_mm_loadu_si128((const __m128i *)(v102 + 4 * v133 + 32)));
                  *(__m128 *)(v102 + 4 * v133 + 48) = _mm_andnot_ps(
                                                        v136,
                                                        (__m128)_mm_loadu_si128((const __m128i *)(v102 + 4 * v133 + 48)));
                }
                while ( v129 < v128 - v128 % 16 );
                if ( v128 % 0x10u >= 2 )
                {
LABEL_175:
                  v137 = *(&v226 + 4 * k);
                  do
                  {
                    v138 = v129;
                    v129 += 2;
                    *(_QWORD *)(v102 + 4 * v138) = _mm_andnot_ps(
                                                     (__m128)_mm_loadl_epi64((const __m128i *)(v137 + 4 * v138)),
                                                     (__m128)_mm_loadl_epi64((const __m128i *)(v102 + 4 * v138))).m128_u64[0];
                  }
                  while ( v129 < v128 - v128 % 2 );
                }
                if ( v129 < v128 )
                {
LABEL_308:
                  do
                  {
                    v139 = v129++;
                    *(_DWORD *)(v102 + 4 * v139) &= ~*(_DWORD *)(*(&v226 + 4 * k) + 4 * v139);
                  }
                  while ( v129 < v128 );
                }
              }
              for ( m = 0; m < *(_DWORD *)(v99 + 4); ++m )
              {
                if ( !v123 )
                  break;
                v141 = *(&v226 + 4 * k);
                v142 = m & 0x1F;
                v143 = (__int64)m >> 5;
                v144 = *(_DWORD *)(v141 + 4 * v143);
                if ( _bittest(&v144, v142) )
                {
                  v145 = 32LL * m;
                  *(_DWORD *)(v141 + 4 * v143) = v144 & ~(1 << v142);
                  --v123;
                  v146 = *(_QWORD *)(v99 + 16);
                  v147 = *(float **)(v145 + v146 + 8);
                  *v147 = v124;
                  v147[1] = v125;
                  v147[2] = v126;
                  v147[3] = v127;
                  v148 = v106;
                  v106 += 2;
                  *v148 = *(_OWORD *)(v145 + v146);
                  v148[1] = *(_OWORD *)(v145 + v146 + 16);
                }
              }
              v115 = v237;
            }
            if ( k != 1 )
              break;
            if ( v115 > 0 )
            {
              v149 = *(_QWORD *)(v99 + 16);
              v150 = 32LL * *((unsigned __int16 *)v5 + 282);
              *v106 = *(_OWORD *)(v149 + v150);
              v106[1] = *(_OWORD *)(v149 + v150 + 16);
              v106 += 2;
            }
            k = 2;
          }
        }
        v151 = *(_DWORD *)(v99 + 4);
        if ( v151 > 0 )
        {
          for ( n = 0; n < v151; ++n )
          {
            if ( !v120 )
              break;
            v153 = *(_DWORD *)(v102 + 4 * ((__int64)n >> 5));
            if ( _bittest(&v153, n & 0x1F) )
            {
              v154 = *(_QWORD *)(v99 + 16);
              v155 = v106;
              v156 = 32LL * n;
              v106 += 2;
              --v120;
              *v155 = *(_OWORD *)(v154 + v156);
              v155[1] = *(_OWORD *)(v154 + v156 + 16);
            }
            v151 = *(_DWORD *)(v99 + 4);
          }
        }
        sub_1800B8BD0(*(_QWORD *)(v99 + 16) + 64LL, *(_QWORD *)(v221 + 8952), 32LL * (v151 - 2));
      }
      v8 = v222;
    }
    v4 = v214;
    v9 = v215;
    v10 = v220;
  }
  sub_18005D2B0(v216.m128_u64[0], *(_QWORD *)(v8 + 712));
  v157 = v5[27];
  v158 = 0.0;
  v159 = 0.0;
  v160 = 0.0;
  if ( v157 > 0 )
  {
    for ( ii = 0; ii < v157; ++ii )
    {
      v162 = *(_DWORD *)(*((_QWORD *)v5 + 10) + 4 * ((__int64)ii >> 5));
      if ( _bittest(&v162, ii & 0x1F) )
      {
        v163 = *((_QWORD *)v5 + 3);
        v164 = 116LL * ii;
        v165 = *(_DWORD *)(v163 + v164);
        if ( (v165 & 0x10) == 0 || (v165 & 0x20) != 0 )
        {
          v167 = *(float *)(v163 + v164 + 56);
          v168 = fmaxf(*(float *)(v163 + v164 + 68), *(float *)(v163 + v164 + 72)) - v167;
          if ( (v165 & 0x2000) == 0 )
            v168 = fmaxf(v168, *(float *)(v163 + v164 + 80) - v167);
          if ( (v165 & 0x10) != 0 && *(float *)(v163 + v164 + 32) > 0.0 && ((v5[1] & 1) == 0 || (v165 & 0x20) != 0) )
            v168 = *(float *)(v163 + v164 + 32);
          v166 = fmaxf(v168, *((float *)v5 + 46));
          if ( (v165 & 0x10) != 0 )
            v158 = v158 + v166;
          else
            v159 = v159 + v166;
        }
        else
        {
          v166 = *(float *)(v163 + v164 + 16);
          v158 = v158 + v166;
        }
        if ( (v165 & 0x28) == 0x28 )
          v160 = fmaxf(v160, v166 / (float)(*(float *)(v163 + v164 + 28) / *((float *)v5 + 54)));
      }
    }
  }
  v7 = (v5[1] & 0x1000000) == 0;
  v169 = *((float *)v5 + 48) + *((float *)v5 + 48);
  *((float *)v5 + 53) = (float)((float)((float)((float)((float)(*((float *)v5 + 50) + *((float *)v5 + 49))
                                                      * (float)(*((__int16 *)v5 + 257) - 1))
                                              + (float)(*((float *)v5 + 47) + *((float *)v5 + 47)))
                                      + (float)((float)*((__int16 *)v5 + 257) * v169))
                              + v158)
                      + fmaxf(v159, v160);
  if ( !v7 || v8 == v9 )
  {
    v170 = *((__int16 *)v5 + 266);
    if ( (_WORD)v170 != 0xFFFF
      && *((_WORD *)v5 + 265) == 0xFFFF
      && *(_BYTE *)(v8 + 200)
      && *((_WORD *)v5 + 61) == *((_WORD *)v5 + 60) )
    {
      v171 = v169 + *((float *)v5 + 46);
      v172 = *(float *)(116 * v170 + *((_QWORD *)v5 + 3) + 12);
      if ( *((float *)v5 + 72) <= v172 )
      {
        if ( v172 <= *((float *)v5 + 74) )
          goto LABEL_230;
        v173 = (float)(v172 - *(float *)(v8 + 40)) + v171;
      }
      else
      {
        v173 = (float)(v172 - *(float *)(v8 + 40)) - v171;
      }
      v174 = v173 - *(float *)(v8 + 112);
      *(_DWORD *)(v8 + 184) = 0;
      *(_DWORD *)(v8 + 176) = 1065353216;
      *(float *)(v8 + 168) = (float)(int)(float)((float)(v174 - *(float *)(v8 + 128)) + *(float *)(v8 + 152));
    }
  }
  else
  {
    *(_DWORD *)(v8 + 152) = 0;
  }
LABEL_230:
  v175 = *((__int16 *)v5 + 265);
  if ( (_WORD)v175 != 0xFFFF && *((_WORD *)v5 + 60) == *((_WORD *)v5 + 61) )
    *((float *)v5 + 55) = (float)(int)(float)((float)((float)((float)((float)(*(float *)(v4 + 224)
                                                                            - *(float *)(v4 + 5360))
                                                                    + (float)(int)(float)(*(float *)(v4 + 4448) * 4.0))
                                                            - *(float *)(116 * v175 + *((_QWORD *)v5 + 3) + 8))
                                                    - *((float *)v5 + 49))
                                            - (float)(*((float *)v5 + 48) + *((float *)v5 + 48)));
  v176 = *(_DWORD *)(v4 + 5336) && !*((_BYTE *)v5 + 581);
  *((_BYTE *)v5 + 582) = v176;
  if ( *(_DWORD *)(*(_QWORD *)(v8 + 272) + 4LL * *(int *)(v8 + 264) - 4) != *v223 )
    sub_180049A30("Mismatching PushID/PopID!");
  if ( *(_DWORD *)(v9 + 496) < *(_DWORD *)(v10 + 128) )
    sub_180049A30("Too many PopItemWidth!");
  if ( *((__int16 *)v5 + 60) > 0 )
  {
    v177 = *(_QWORD *)(qword_18010C470 + 5216);
    v178 = *(_DWORD *)(v177 + 264);
    if ( v178 > 1 )
      *(_DWORD *)(v177 + 264) = v178 - 1;
    else
      sub_180049A30("Calling PopID() too many times!");
  }
  v179 = *(_QWORD *)(qword_18010C470 + 5216);
  v180 = *(_DWORD *)(v179 + 264);
  if ( v180 > 1 )
    *(_DWORD *)(v179 + 264) = v180 - 1;
  else
    sub_180049A30("Calling PopID() too many times!");
  v181 = *(float *)(v9 + 304);
  v182 = *(float *)(v9 + 308);
  *(_OWORD *)(v8 + 576) = *(_OWORD *)(v10 + 64);
  *(_OWORD *)(v8 + 592) = *(_OWORD *)(v10 + 80);
  *(_BYTE *)(v8 + 209) = *((_BYTE *)v5 + 586);
  *(_QWORD *)(v9 + 280) = *((_QWORD *)v5 + 30);
  *(_DWORD *)(v9 + 488) = *(_DWORD *)(v10 + 124);
  *(_DWORD *)(v9 + 496) = *(_DWORD *)(v10 + 128);
  *(_DWORD *)(v9 + 352) = *(_DWORD *)(v10 + 120);
  if ( v8 == v9 )
  {
    --*(_DWORD *)(*((_QWORD *)v5 + 49) + 416LL);
    *(float *)&v184 = *((float *)v5 + 62) - *((float *)v5 + 60);
    *(float *)&v238 = *((float *)v5 + 63) - *((float *)v5 + 61);
    v237 = v184;
    sub_18004AAD0(&v237);
    sub_18004A070(v5 + 60, 0, 0, 0);
  }
  else
  {
    v183 = *(_WORD *)(v8 + 372);
    *(_WORD *)(v8 + 372) = v183 | (1 << *((_BYTE *)v5 + 566));
    *(_QWORD *)(v4 + 8856) = 0;
    sub_18003E7F0();
    *(_QWORD *)(v4 + 8856) = v5;
    *(_WORD *)(v8 + 372) = v183;
  }
  v185 = v5[1];
  if ( (v185 & 0x10000) != 0 )
  {
    v186 = fmaxf(v181, *((float *)v5 + 53) + *((float *)v5 + 60));
  }
  else
  {
    v187 = *(float *)(v10 + 32);
    if ( v187 > 0.0 )
    {
      v186 = fmaxf(v181, *((float *)v5 + 62));
    }
    else
    {
      if ( (v185 & 0x2000000) != 0 )
        v188 = *(float *)(v8 + 192);
      else
        v188 = 0.0;
      v189 = (float)(v188 + *(float *)(*((_QWORD *)v5 + 2) + 8LL)) + (float)(*((float *)v5 + 53) + *((float *)v5 + 60));
      *(float *)(v9 + 312) = fmaxf(*(float *)(v9 + 312), v189 - v187);
      v186 = fmaxf(v181, fminf(*((float *)v5 + 62), v189));
    }
  }
  *(float *)(v9 + 304) = v186;
  v190 = *(float *)(v10 + 36);
  if ( v190 > 0.0 )
  {
    v193 = fmaxf(v182, *((float *)v5 + 63));
  }
  else
  {
    if ( (v5[1] & 0x1000000) != 0 )
      v191 = *(float *)(v8 + 196);
    else
      v191 = 0.0;
    v192 = v191 + v13;
    *(float *)(v9 + 316) = fmaxf(*(float *)(v9 + 316), v192 - v190);
    v193 = fmaxf(v182, fminf(*((float *)v5 + 63), v192));
  }
  *(float *)(v9 + 308) = v193;
  if ( *((_BYTE *)v5 + 575) )
  {
    v7 = (v5[1] & 0x10) == 0;
    *((_BYTE *)v5 + 575) = 0;
    if ( v7 )
    {
      v194 = (int)v5[25];
      v195 = qword_18010C470;
      if ( (_DWORD)v194 != -1 )
      {
        v196 = v194 + *(_QWORD *)(qword_18010C470 + 9968);
        if ( *(__int16 *)(v196 + 14) < (int)v5[27] )
        {
          *(_DWORD *)v196 = 0;
        }
        else if ( v196 )
        {
          goto LABEL_273;
        }
      }
      v196 = sub_18006D590(*v5, v5[27]);
      v197 = v196 - *(_DWORD *)(v195 + 9968);
      v195 = qword_18010C470;
      v5[25] = v197;
LABEL_273:
      v198 = v196 + 20;
      *(_WORD *)(v196 + 12) = *((_WORD *)v5 + 54);
      v199 = 0;
      v200 = *((_QWORD *)v5 + 3);
      v201 = 0;
      *(_DWORD *)(v196 + 4) = 0;
      if ( (int)v5[27] > 0 )
      {
        do
        {
          v202 = 28;
          if ( (*(_BYTE *)v200 & 8) == 0 )
            v202 = 16;
          v203 = *(float *)(v200 + v202);
          *(float *)v198 = v203;
          *(_WORD *)(v198 + 8) = v201;
          *(_WORD *)(v198 + 10) = *(_WORD *)(v200 + 86);
          *(_WORD *)(v198 + 12) = *(_WORD *)(v200 + 94);
          v204 = *(_BYTE *)(v198 + 14) ^ (*(_BYTE *)(v200 + 113) ^ *(_BYTE *)(v198 + 14)) & 3;
          *(_BYTE *)(v198 + 14) = v204;
          v205 = (4 * *(_BYTE *)(v200 + 103)) ^ (v204 ^ (4 * *(_BYTE *)(v200 + 103))) & 0xF3;
          *(_BYTE *)(v198 + 14) = v205;
          *(_BYTE *)(v198 + 14) = v205 ^ ((16 * (*(_DWORD *)v200 >> 3)) ^ v205) & 0x10;
          if ( (*(_BYTE *)v200 & 8) == 0 )
            v199 = 1;
          if ( v203 != *(float *)(v200 + 32) )
            *(_DWORD *)(v196 + 4) |= 1u;
          if ( *(__int16 *)(v200 + 86) != v201 )
            *(_DWORD *)(v196 + 4) |= 2u;
          if ( *(_WORD *)(v200 + 94) != 0xFFFF )
            *(_DWORD *)(v196 + 4) |= 8u;
          if ( *(_BYTE *)(v200 + 103) != (~(*(_DWORD *)v200 >> 1) & 1) )
            *(_DWORD *)(v196 + 4) |= 4u;
          ++v201;
          v200 += 116;
          v198 += 16;
        }
        while ( v201 < (int)v5[27] );
        v4 = v214;
        v9 = v215;
      }
      *(_DWORD *)(v196 + 4) &= v5[1];
      if ( v199 )
        v206 = v5[57];
      else
        v206 = 0;
      *(_DWORD *)(v196 + 8) = v206;
      if ( *(float *)(v195 + 9908) <= 0.0 )
        *(_DWORD *)(v195 + 9908) = *(_DWORD *)(v195 + 36);
      goto LABEL_294;
    }
  }
  v195 = qword_18010C470;
LABEL_294:
  *((_BYTE *)v5 + 569) = 0;
  v207 = *(_DWORD *)(v4 + 8868);
  *(_DWORD *)(v4 + 8868) = v207 - 1;
  if ( v207 - 1 > 0 && (v208 = (int *)(*(_QWORD *)(v4 + 8880) + 136LL * (v207 - 2))) != nullptr )
  {
    v209 = *v208;
    v7 = *(_QWORD *)(v4 + 8896) + 592 * v209 == 0;
    v210 = *(_QWORD *)(v4 + 8896) + 592 * v209;
    *(_QWORD *)(v4 + 8856) = v210;
    if ( !v7 )
    {
      *(_QWORD *)(v210 + 16) = v208;
      *(_QWORD *)(*(_QWORD *)(v4 + 8856) + 416LL) = v208 + 10;
    }
  }
  else
  {
    *(_QWORD *)(v4 + 8856) = 0;
  }
  v211 = *(_QWORD *)(v4 + 8856);
  if ( v211 )
    v212 = (v211 - *(_QWORD *)(v4 + 8896)) / 592;
  else
    LODWORD(v212) = -1;
  *(_DWORD *)(v9 + 464) = v212;
  v213 = *(_QWORD *)(v195 + 5216);
  if ( *(_QWORD *)(v195 + 8856) || *(_QWORD *)(v213 + 456) )
  {
    *(_BYTE *)(v213 + 376) = 0;
    return 0;
  }
  else
  {
    *(_BYTE *)(v213 + 376) = 1;
    return 1;
  }
}
