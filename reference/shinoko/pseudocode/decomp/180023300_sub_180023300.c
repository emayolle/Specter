// sub_180023300 size=4857
void sub_180023300()
{
  char *v0; // rbx
  char *v1; // rdi
  __int64 v2; // rax
  __int64 v3; // rax
  __int64 v4; // r15
  unsigned int v5; // ebx
  __int64 v6; // rax
  __int64 v7; // rdi
  unsigned int i; // r12d
  __int64 v9; // rax
  __int64 v10; // r14
  int v11; // xmm8_4
  __m128 v12; // xmm9
  __m128 v13; // xmm7
  float v14; // xmm2_4
  float v15; // xmm6_4
  double v16; // xmm0_8
  int v17; // ebx
  bool v18; // si
  bool v19; // di
  char v20; // al
  int v21; // ecx
  int v22; // ecx
  __int64 v23; // rsi
  unsigned __int64 v24; // rdi
  __int64 v25; // rax
  __int64 v26; // rax
  __m128i v27; // xmm1
  void *v28; // rcx
  __int64 v29; // rax
  __int64 v30; // rbx
  void *v31; // rcx
  __m128i v32; // xmm1
  void *v33; // rcx
  __int64 v34; // rax
  __int64 v35; // rbx
  void *v36; // rcx
  __m128i v37; // xmm1
  void *v38; // rcx
  LPVOID *v39; // rcx
  LPVOID *v40; // rbx
  LPVOID *v41; // rcx
  __int64 v42; // rbx
  void *v43; // rcx
  __int64 v44; // rcx
  unsigned __int64 v45; // rdx
  __int64 v46; // rdi
  unsigned __int64 v47; // rsi
  __int64 v48; // rax
  __int64 v49; // rax
  __m128i v50; // xmm1
  void *v51; // rcx
  __int64 v52; // rax
  __int64 v53; // rbx
  void *v54; // rcx
  __m128i v55; // xmm1
  void *v56; // rcx
  __int128 *v57; // rcx
  LPVOID *v58; // rcx
  LPVOID *v59; // rcx
  __int64 v60; // rbx
  void *v61; // rcx
  float v62; // xmm0_4
  __int64 v63; // rsi
  unsigned __int64 v64; // rdi
  __int64 v65; // rax
  __int64 v66; // rax
  __m128i v67; // xmm1
  void *v68; // rcx
  __int64 v69; // rax
  __int64 v70; // rbx
  void *v71; // rcx
  __m128i v72; // xmm1
  void *v73; // rcx
  __int64 v74; // rax
  __int64 v75; // rbx
  void *v76; // rcx
  __m128i v77; // xmm1
  void *v78; // rcx
  __int128 *v79; // rcx
  LPVOID *v80; // rcx
  __int64 v81; // rbx
  void *v82; // rcx
  float v83; // xmm0_4
  __int64 v84; // rax
  __int64 v85; // rdi
  __int64 v86; // rax
  __int64 v87; // rax
  __m128i v88; // xmm1
  void *v89; // rcx
  __int64 v90; // rax
  __int64 v91; // rbx
  void *v92; // rcx
  __m128i v93; // xmm1
  void *v94; // rcx
  __int128 *v95; // rcx
  LPVOID *v96; // rcx
  LPVOID *v97; // rcx
  __int64 v98; // rbx
  void *v99; // rcx
  float v100; // xmm0_4
  __int64 v101; // rax
  __int64 v102; // rbx
  void *v103; // rcx
  unsigned __int64 v104; // [rsp+28h] [rbp-E0h] BYREF
  __int64 v105; // [rsp+30h] [rbp-D8h]
  _QWORD v106[3]; // [rsp+38h] [rbp-D0h] BYREF
  unsigned __int64 v107; // [rsp+50h] [rbp-B8h]
  __int64 v108; // [rsp+58h] [rbp-B0h] BYREF
  __int128 v109; // [rsp+60h] [rbp-A8h] BYREF
  __int64 v110; // [rsp+70h] [rbp-98h]
  unsigned __int64 v111; // [rsp+78h] [rbp-90h]
  unsigned __int64 v112; // [rsp+80h] [rbp-88h]
  int v113; // [rsp+88h] [rbp-80h]
  float v114; // [rsp+8Ch] [rbp-7Ch]
  int v115; // [rsp+90h] [rbp-78h]
  float v116; // [rsp+94h] [rbp-74h]
  int v117; // [rsp+98h] [rbp-70h]
  __int64 v118; // [rsp+9Ch] [rbp-6Ch] BYREF
  int v119; // [rsp+A4h] [rbp-64h]
  char v120; // [rsp+A8h] [rbp-60h]
  LPVOID lpMem[2]; // [rsp+B8h] [rbp-50h] BYREF
  __m128i v122; // [rsp+C8h] [rbp-40h]
  __int128 v123; // [rsp+D8h] [rbp-30h] BYREF
  __m128i v124; // [rsp+E8h] [rbp-20h]
  __int128 v125; // [rsp+F8h] [rbp-10h] BYREF
  __m128i v126; // [rsp+108h] [rbp+0h]
  __int128 v127; // [rsp+118h] [rbp+10h] BYREF
  __m128i v128; // [rsp+128h] [rbp+20h]
  int v129; // [rsp+1E8h] [rbp+E0h] BYREF

  if ( byte_1800FAB38 && qword_18010C460 )
  {
    v1 = (char *)*(&xmmword_18010C568 + 1);
    v0 = (char *)xmmword_18010C568;
    if ( xmmword_18010C568 != *(&xmmword_18010C568 + 1) )
    {
      do
      {
        sub_180015D80(v0 + 8);
        v0 += 88;
      }
      while ( v0 != v1 );
      *(&xmmword_18010C568 + 1) = xmmword_18010C568;
    }
    qword_18010C590 = 0;
    v2 = sub_180022D10();
    if ( v2 )
    {
      v3 = sub_180022D40(v2);
      v4 = v3;
      if ( v3 )
      {
        if ( *(int *)(v3 + 24) > 0 )
        {
          v5 = 0;
          while ( 1 )
          {
            v6 = sub_1800254C0(v4, v5);
            v7 = v6;
            if ( v6 )
            {
              if ( !(unsigned __int8)sub_180022DC0(v6) && (unsigned __int8)sub_180022F60(v7) )
                break;
            }
            if ( (signed int)++v5 >= *(_DWORD *)(v4 + 24) )
              goto LABEL_17;
          }
          qword_18010C590 = v7;
          v104 = 0;
          LODWORD(v105) = 0;
          if ( (unsigned __int8)sub_1800231A0(v7, &v104) )
          {
            qword_18010C580 = v104;
            dword_18010C588 = v105;
          }
LABEL_17:
          for ( i = 0; (signed int)i < *(_DWORD *)(v4 + 24); ++i )
          {
            v9 = sub_1800254C0(v4, i);
            v10 = v9;
            if ( v9 )
            {
              if ( !(unsigned __int8)sub_180022DC0(v9) && v10 != qword_18010C590 )
              {
                v104 = 0;
                LODWORD(v105) = 0;
                if ( (unsigned __int8)sub_1800231A0(v10, &v104) )
                {
                  v11 = v105;
                  v12 = (__m128)HIDWORD(v104);
                  v13 = (__m128)(unsigned int)v104;
                  v14 = (float)((float)((float)(*((float *)&v104 + 1) - *((float *)&qword_18010C580 + 1))
                                      * (float)(*((float *)&v104 + 1) - *((float *)&qword_18010C580 + 1)))
                              + (float)((float)(*(float *)&v104 - *(float *)&qword_18010C580)
                                      * (float)(*(float *)&v104 - *(float *)&qword_18010C580)))
                      + (float)((float)(*(float *)&v105 - *(float *)&dword_18010C588)
                              * (float)(*(float *)&v105 - *(float *)&dword_18010C588));
                  if ( v14 < 0.0 )
                  {
                    v16 = sub_1800B7240();
                    v15 = *(float *)&v16;
                  }
                  else
                  {
                    v15 = fsqrt(v14);
                  }
                  if ( v15 <= *(float *)&dword_1800FAB44 )
                  {
                    v17 = sub_180022D70(v10);
                    v18 = (unsigned __int8)sub_180022EA0(v10)
                       || (unsigned __int8)sub_180022ED0(v10) && !(unsigned __int8)sub_180022F60(v10)
                       || v17 == 8;
                    v19 = (unsigned __int8)sub_180022F00(v10) || v17 == 7;
                    v20 = sub_180022F30(v10);
                    if ( v20 || v17 == 9 || v17 == 6 )
                      v20 = 1;
                    if ( v18 )
                    {
                      if ( byte_1800FAB39 )
                      {
                        v21 = 0;
                        goto LABEL_51;
                      }
                    }
                    else if ( v19 )
                    {
                      if ( byte_1800FAB3A )
                      {
                        v21 = 1;
                        goto LABEL_51;
                      }
                    }
                    else if ( v20 )
                    {
                      if ( byte_1800FAB3B )
                      {
                        v21 = 2;
LABEL_51:
                        v109 = 0;
                        v110 = 0;
                        v111 = 15;
                        LOBYTE(v109) = 0;
                        v114 = 1.8;
                        v115 = 1053609165;
                        v118 = 0;
                        v119 = 0;
                        v120 = 0;
                        v108 = v10;
                        v104 = _mm_unpacklo_ps(v13, v12).m128_u64[0];
                        v112 = v104;
                        v113 = v11;
                        v116 = v15;
                        v117 = v21;
                        if ( v21 )
                        {
                          v22 = v21 - 1;
                          if ( v22 )
                          {
                            if ( v22 != 1 )
                            {
                              *(_OWORD *)lpMem = 0;
                              v23 = 0;
                              v122.m128i_i64[0] = 0;
                              v24 = 15;
                              v122.m128i_i64[1] = 15;
                              LOBYTE(lpMem[0]) = 0;
                              v25 = sub_180022E40(v10);
                              if ( v25 )
                              {
                                v26 = sub_180022A10(v25, v106);
                                if ( lpMem != (LPVOID *)v26 )
                                {
                                  *(_OWORD *)lpMem = *(_OWORD *)v26;
                                  v122 = *(__m128i *)(v26 + 16);
                                  v27 = v122;
                                  *(_QWORD *)(v26 + 16) = 0;
                                  *(_QWORD *)(v26 + 24) = 15;
                                  *(_BYTE *)v26 = 0;
                                  v24 = _mm_srli_si128(v27, 8).m128i_u64[0];
                                  v23 = v27.m128i_i64[0];
                                }
                                if ( v107 > 0xF )
                                {
                                  v28 = (void *)v106[0];
                                  if ( v107 + 1 >= 0x1000 )
                                  {
                                    if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                      goto LABEL_291;
                                    v28 = *(void **)(v106[0] - 8LL);
                                  }
                                  sub_1800931A0(v28);
                                }
                                if ( v23 )
                                  goto LABEL_91;
                              }
                              v29 = sub_180022E10(v10);
                              if ( v29 )
                              {
                                v30 = sub_180022A10(v29, v106);
                                if ( lpMem != (LPVOID *)v30 )
                                {
                                  if ( v24 > 0xF )
                                  {
                                    v31 = lpMem[0];
                                    if ( v24 + 1 >= 0x1000 )
                                    {
                                      if ( (unsigned __int64)lpMem[0] - *((_QWORD *)lpMem[0] - 1) - 8 > 0x1F )
                                        goto LABEL_291;
                                      v31 = *((void **)lpMem[0] - 1);
                                    }
                                    sub_1800931A0(v31);
                                  }
                                  *(_OWORD *)lpMem = *(_OWORD *)v30;
                                  v122 = *(__m128i *)(v30 + 16);
                                  v32 = v122;
                                  *(_QWORD *)(v30 + 16) = 0;
                                  *(_QWORD *)(v30 + 24) = 15;
                                  *(_BYTE *)v30 = 0;
                                  v24 = _mm_srli_si128(v32, 8).m128i_u64[0];
                                  v23 = v32.m128i_i64[0];
                                }
                                if ( v107 > 0xF )
                                {
                                  v33 = (void *)v106[0];
                                  if ( v107 + 1 >= 0x1000 )
                                  {
                                    if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                      goto LABEL_291;
                                    v33 = *(void **)(v106[0] - 8LL);
                                  }
                                  sub_1800931A0(v33);
                                }
                                if ( v23 )
                                  goto LABEL_91;
                              }
                              v34 = sub_180022F90(v10);
                              if ( !v34 )
                                goto LABEL_107;
                              v35 = sub_180022A10(v34, v106);
                              if ( lpMem != (LPVOID *)v35 )
                              {
                                if ( v24 > 0xF )
                                {
                                  v36 = lpMem[0];
                                  if ( v24 + 1 >= 0x1000 )
                                  {
                                    if ( (unsigned __int64)lpMem[0] - *((_QWORD *)lpMem[0] - 1) - 8 > 0x1F )
                                      goto LABEL_291;
                                    v36 = *((void **)lpMem[0] - 1);
                                  }
                                  sub_1800931A0(v36);
                                }
                                *(_OWORD *)lpMem = *(_OWORD *)v35;
                                v122 = *(__m128i *)(v35 + 16);
                                v37 = v122;
                                *(_QWORD *)(v35 + 16) = 0;
                                *(_QWORD *)(v35 + 24) = 15;
                                *(_BYTE *)v35 = 0;
                                v24 = _mm_srli_si128(v37, 8).m128i_u64[0];
                                v23 = v37.m128i_i64[0];
                              }
                              if ( v107 > 0xF )
                              {
                                v38 = (void *)v106[0];
                                if ( v107 + 1 >= 0x1000 )
                                {
                                  if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                    goto LABEL_291;
                                  v38 = *(void **)(v106[0] - 8LL);
                                }
                                sub_1800931A0(v38);
                              }
                              if ( v23 )
                              {
LABEL_91:
                                v39 = lpMem;
                                v40 = (LPVOID *)lpMem[0];
                                if ( v24 > 0xF )
                                  v39 = (LPVOID *)lpMem[0];
                                if ( v23 != 4 || (unsigned int)sub_1800B8AD0(v39, "Loot", 4) )
                                {
                                  v41 = lpMem;
                                  if ( v24 > 0xF )
                                    v41 = v40;
                                  if ( v23 != 4 || (unsigned int)sub_1800B8AD0(v41, "loot", 4) )
                                  {
                                    v42 = sub_180025370(v106, "Loot - ", lpMem);
                                    if ( &v109 != (__int128 *)v42 )
                                    {
                                      if ( v111 > 0xF )
                                      {
                                        v43 = (void *)v109;
                                        if ( v111 + 1 >= 0x1000 )
                                        {
                                          if ( (unsigned __int64)(v109 - *(_QWORD *)(v109 - 8) - 8) > 0x1F )
LABEL_291:
                                            __fastfail(5u);
                                          v43 = *(void **)(v109 - 8);
                                        }
                                        sub_1800931A0(v43);
                                      }
                                      v110 = 0;
                                      v111 = 15;
                                      LOBYTE(v109) = 0;
                                      v109 = *(_OWORD *)v42;
                                      v110 = *(_QWORD *)(v42 + 16);
                                      v111 = *(_QWORD *)(v42 + 24);
                                      *(_QWORD *)(v42 + 16) = 0;
                                      *(_QWORD *)(v42 + 24) = 15;
                                      *(_BYTE *)v42 = 0;
                                    }
                                    sub_180015D80(v106);
                                    v24 = v122.m128i_u64[1];
                                    v40 = (LPVOID *)lpMem[0];
LABEL_109:
                                    v114 = 0.80000001;
                                    v115 = 1053609165;
                                    if ( v24 > 0xF )
                                    {
                                      v45 = v24 + 1;
                                      goto LABEL_277;
                                    }
LABEL_281:
                                    v102 = (__int64)*(&xmmword_18010C568 + 1);
                                    if ( *(&xmmword_18010C568 + 1) == (LPVOID)qword_18010C578 )
                                    {
                                      sub_180025700(v44, *(&xmmword_18010C568 + 1), &v108);
                                    }
                                    else
                                    {
                                      *(_QWORD *)*(&xmmword_18010C568 + 1) = v108;
                                      sub_180015AE0(v102 + 8, &v109);
                                      *(_QWORD *)(v102 + 40) = v112;
                                      *(_DWORD *)(v102 + 48) = v113;
                                      *(float *)(v102 + 52) = v114;
                                      *(_DWORD *)(v102 + 56) = v115;
                                      *(float *)(v102 + 60) = v116;
                                      *(_DWORD *)(v102 + 64) = v117;
                                      *(_QWORD *)(v102 + 68) = v118;
                                      *(_DWORD *)(v102 + 76) = v119;
                                      *(_BYTE *)(v102 + 80) = v120;
                                      *(&xmmword_18010C568 + 1) = (char *)*(&xmmword_18010C568 + 1) + 88;
                                    }
                                    if ( v111 > 0xF )
                                    {
                                      v103 = (void *)v109;
                                      if ( v111 + 1 >= 0x1000 )
                                      {
                                        if ( (unsigned __int64)(v109 - *(_QWORD *)(v109 - 8) - 8) > 0x1F )
                                          __fastfail(5u);
                                        v103 = *(void **)(v109 - 8);
                                      }
                                      sub_1800931A0(v103);
                                    }
                                    continue;
                                  }
                                }
                              }
                              else
                              {
LABEL_107:
                                v40 = (LPVOID *)lpMem[0];
                              }
                              sub_1800254F0(&v109, "Loot");
                              goto LABEL_109;
                            }
                            v125 = 0;
                            v46 = 0;
                            v126.m128i_i64[0] = 0;
                            v47 = 15;
                            v126.m128i_i64[1] = 15;
                            LOBYTE(v125) = 0;
                            v48 = sub_180022E10(v10);
                            if ( v48 )
                            {
                              v49 = sub_180022A10(v48, v106);
                              if ( &v125 != (__int128 *)v49 )
                              {
                                v125 = *(_OWORD *)v49;
                                v126 = *(__m128i *)(v49 + 16);
                                v50 = v126;
                                *(_QWORD *)(v49 + 16) = 0;
                                *(_QWORD *)(v49 + 24) = 15;
                                *(_BYTE *)v49 = 0;
                                v47 = _mm_srli_si128(v50, 8).m128i_u64[0];
                                v46 = v50.m128i_i64[0];
                              }
                              if ( v107 > 0xF )
                              {
                                v51 = (void *)v106[0];
                                if ( v107 + 1 >= 0x1000 )
                                {
                                  if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                    goto LABEL_292;
                                  v51 = *(void **)(v106[0] - 8LL);
                                }
                                sub_1800931A0(v51);
                              }
                              if ( v46 )
                                goto LABEL_134;
                            }
                            v52 = sub_180022E70(v10);
                            if ( !v52 )
                              goto LABEL_154;
                            v53 = sub_180022A10(v52, v106);
                            if ( &v125 != (__int128 *)v53 )
                            {
                              if ( v47 > 0xF )
                              {
                                v54 = (void *)v125;
                                if ( v47 + 1 >= 0x1000 )
                                {
                                  if ( (unsigned __int64)(v125 - *(_QWORD *)(v125 - 8) - 8) > 0x1F )
                                    goto LABEL_292;
                                  v54 = *(void **)(v125 - 8);
                                }
                                sub_1800931A0(v54);
                              }
                              v125 = *(_OWORD *)v53;
                              v126 = *(__m128i *)(v53 + 16);
                              v55 = v126;
                              *(_QWORD *)(v53 + 16) = 0;
                              *(_QWORD *)(v53 + 24) = 15;
                              *(_BYTE *)v53 = 0;
                              v47 = _mm_srli_si128(v55, 8).m128i_u64[0];
                              v46 = v55.m128i_i64[0];
                            }
                            if ( v107 > 0xF )
                            {
                              v56 = (void *)v106[0];
                              if ( v107 + 1 >= 0x1000 )
                              {
                                if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                  goto LABEL_292;
                                v56 = *(void **)(v106[0] - 8LL);
                              }
                              sub_1800931A0(v56);
                            }
                            if ( v46 )
                            {
LABEL_134:
                              v57 = &v125;
                              v40 = (LPVOID *)v125;
                              if ( v47 > 0xF )
                                v57 = (__int128 *)v125;
                              if ( v46 != 3 || (unsigned int)sub_1800B8AD0(v57, "Pet", 3) )
                              {
                                v58 = (LPVOID *)&v125;
                                if ( v47 > 0xF )
                                  v58 = v40;
                                if ( v46 != 3 || (unsigned int)sub_1800B8AD0(v58, "pet", 3) )
                                {
                                  v59 = (LPVOID *)&v125;
                                  if ( v47 > 0xF )
                                    v59 = v40;
                                  if ( v46 != 4 || (unsigned int)sub_1800B8AD0(v59, "Pets", 4) )
                                  {
                                    v60 = sub_180025370(v106, "Pets - ", &v125);
                                    if ( &v109 != (__int128 *)v60 )
                                    {
                                      if ( v111 > 0xF )
                                      {
                                        v61 = (void *)v109;
                                        if ( v111 + 1 >= 0x1000 )
                                        {
                                          if ( (unsigned __int64)(v109 - *(_QWORD *)(v109 - 8) - 8) > 0x1F )
LABEL_292:
                                            __fastfail(5u);
                                          v61 = *(void **)(v109 - 8);
                                        }
                                        sub_1800931A0(v61);
                                      }
                                      v110 = 0;
                                      v111 = 15;
                                      LOBYTE(v109) = 0;
                                      v109 = *(_OWORD *)v60;
                                      v110 = *(_QWORD *)(v60 + 16);
                                      v111 = *(_QWORD *)(v60 + 24);
                                      *(_QWORD *)(v60 + 16) = 0;
                                      *(_QWORD *)(v60 + 24) = 15;
                                      *(_BYTE *)v60 = 0;
                                    }
                                    sub_180015D80(v106);
                                    v47 = v126.m128i_u64[1];
                                    v40 = (LPVOID *)v125;
LABEL_156:
                                    v114 = sub_180022FC0(v10);
                                    v62 = sub_180023000(v10);
                                    v115 = LODWORD(v62);
                                    if ( v114 < 0.2 )
                                      v114 = 1.0;
                                    if ( v62 < 0.1 )
                                      v115 = 1051931443;
LABEL_275:
                                    if ( v47 <= 0xF )
                                      goto LABEL_281;
                                    v45 = v47 + 1;
LABEL_277:
                                    if ( v45 >= 0x1000 )
                                    {
                                      if ( (unsigned __int64)((char *)v40 - (_BYTE *)*(v40 - 1) - 8) > 0x1F )
                                        __fastfail(5u);
                                      v40 = (LPVOID *)*(v40 - 1);
                                    }
                                    sub_1800931A0(v40);
                                    goto LABEL_281;
                                  }
                                }
                              }
                            }
                            else
                            {
LABEL_154:
                              v40 = (LPVOID *)v125;
                            }
                            sub_1800254F0(&v109, "Pets");
                            goto LABEL_156;
                          }
                          v123 = 0;
                          v63 = 0;
                          v124.m128i_i64[0] = 0;
                          v64 = 15;
                          v124.m128i_i64[1] = 15;
                          LOBYTE(v123) = 0;
                          v65 = sub_180022E10(v10);
                          if ( v65 )
                          {
                            v66 = sub_180022A10(v65, v106);
                            if ( &v123 != (__int128 *)v66 )
                            {
                              v123 = *(_OWORD *)v66;
                              v124 = *(__m128i *)(v66 + 16);
                              v67 = v124;
                              *(_QWORD *)(v66 + 16) = 0;
                              *(_QWORD *)(v66 + 24) = 15;
                              *(_BYTE *)v66 = 0;
                              v64 = _mm_srli_si128(v67, 8).m128i_u64[0];
                              v63 = v67.m128i_i64[0];
                            }
                            if ( v107 > 0xF )
                            {
                              v68 = (void *)v106[0];
                              if ( v107 + 1 >= 0x1000 )
                              {
                                if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                  goto LABEL_293;
                                v68 = *(void **)(v106[0] - 8LL);
                              }
                              sub_1800931A0(v68);
                            }
                            if ( v63 )
                              goto LABEL_198;
                          }
                          v69 = sub_180022E70(v10);
                          if ( v69 )
                          {
                            v70 = sub_180022A10(v69, v106);
                            if ( &v123 != (__int128 *)v70 )
                            {
                              if ( v64 > 0xF )
                              {
                                v71 = (void *)v123;
                                if ( v64 + 1 >= 0x1000 )
                                {
                                  if ( (unsigned __int64)(v123 - *(_QWORD *)(v123 - 8) - 8) > 0x1F )
                                    goto LABEL_293;
                                  v71 = *(void **)(v123 - 8);
                                }
                                sub_1800931A0(v71);
                              }
                              v123 = *(_OWORD *)v70;
                              v124 = *(__m128i *)(v70 + 16);
                              v72 = v124;
                              *(_QWORD *)(v70 + 16) = 0;
                              *(_QWORD *)(v70 + 24) = 15;
                              *(_BYTE *)v70 = 0;
                              v64 = _mm_srli_si128(v72, 8).m128i_u64[0];
                              v63 = v72.m128i_i64[0];
                            }
                            if ( v107 > 0xF )
                            {
                              v73 = (void *)v106[0];
                              if ( v107 + 1 >= 0x1000 )
                              {
                                if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                  goto LABEL_293;
                                v73 = *(void **)(v106[0] - 8LL);
                              }
                              sub_1800931A0(v73);
                            }
                            if ( v63 )
                              goto LABEL_198;
                          }
                          v74 = sub_180022E40(v10);
                          if ( !v74 )
                            goto LABEL_214;
                          v75 = sub_180022A10(v74, v106);
                          if ( &v123 != (__int128 *)v75 )
                          {
                            if ( v64 > 0xF )
                            {
                              v76 = (void *)v123;
                              if ( v64 + 1 >= 0x1000 )
                              {
                                if ( (unsigned __int64)(v123 - *(_QWORD *)(v123 - 8) - 8) > 0x1F )
                                  goto LABEL_293;
                                v76 = *(void **)(v123 - 8);
                              }
                              sub_1800931A0(v76);
                            }
                            v123 = *(_OWORD *)v75;
                            v124 = *(__m128i *)(v75 + 16);
                            v77 = v124;
                            *(_QWORD *)(v75 + 16) = 0;
                            *(_QWORD *)(v75 + 24) = 15;
                            *(_BYTE *)v75 = 0;
                            v64 = _mm_srli_si128(v77, 8).m128i_u64[0];
                            v63 = v77.m128i_i64[0];
                          }
                          if ( v107 > 0xF )
                          {
                            v78 = (void *)v106[0];
                            if ( v107 + 1 >= 0x1000 )
                            {
                              if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                goto LABEL_293;
                              v78 = *(void **)(v106[0] - 8LL);
                            }
                            sub_1800931A0(v78);
                          }
                          if ( v63 )
                          {
LABEL_198:
                            v79 = &v123;
                            v40 = (LPVOID *)v123;
                            if ( v64 > 0xF )
                              v79 = (__int128 *)v123;
                            if ( v63 != 3 || (unsigned int)sub_1800B8AD0(v79, "NPC", 3) )
                            {
                              v80 = (LPVOID *)&v123;
                              if ( v64 > 0xF )
                                v80 = v40;
                              if ( v63 != 3 || (unsigned int)sub_1800B8AD0(v80, "npc", 3) )
                              {
                                v81 = sub_180025370(v106, "NPC - ", &v123);
                                if ( &v109 != (__int128 *)v81 )
                                {
                                  if ( v111 > 0xF )
                                  {
                                    v82 = (void *)v109;
                                    if ( v111 + 1 >= 0x1000 )
                                    {
                                      if ( (unsigned __int64)(v109 - *(_QWORD *)(v109 - 8) - 8) > 0x1F )
LABEL_293:
                                        __fastfail(5u);
                                      v82 = *(void **)(v109 - 8);
                                    }
                                    sub_1800931A0(v82);
                                  }
                                  v110 = 0;
                                  v111 = 15;
                                  LOBYTE(v109) = 0;
                                  v109 = *(_OWORD *)v81;
                                  v110 = *(_QWORD *)(v81 + 16);
                                  v111 = *(_QWORD *)(v81 + 24);
                                  *(_QWORD *)(v81 + 16) = 0;
                                  *(_QWORD *)(v81 + 24) = 15;
                                  *(_BYTE *)v81 = 0;
                                }
                                sub_180015D80(v106);
                                v64 = v124.m128i_u64[1];
                                v40 = (LPVOID *)v123;
                                goto LABEL_216;
                              }
                            }
                          }
                          else
                          {
LABEL_214:
                            v40 = (LPVOID *)v123;
                          }
                          sub_1800254F0(&v109, "NPC");
LABEL_216:
                          v114 = sub_180022FC0(v10);
                          v83 = sub_180023000(v10);
                          v115 = LODWORD(v83);
                          if ( v114 < 0.2 )
                            v114 = 1.8;
                          if ( v83 < 0.1 )
                            v115 = 1053609165;
                          v84 = sub_180022DA0(v10);
                          if ( v84 )
                          {
                            v129 = 0;
                            v120 = sub_1800230A0(v84, &v118, &v129);
                          }
                          if ( v64 <= 0xF )
                            goto LABEL_281;
                          v45 = v64 + 1;
                          goto LABEL_277;
                        }
                        v127 = 0;
                        v85 = 0;
                        v128.m128i_i64[0] = 0;
                        v47 = 15;
                        v128.m128i_i64[1] = 15;
                        LOBYTE(v127) = 0;
                        v86 = sub_180022E10(v10);
                        if ( v86 )
                        {
                          v87 = sub_180022A10(v86, v106);
                          if ( &v127 != (__int128 *)v87 )
                          {
                            v127 = *(_OWORD *)v87;
                            v128 = *(__m128i *)(v87 + 16);
                            v88 = v128;
                            *(_QWORD *)(v87 + 16) = 0;
                            *(_QWORD *)(v87 + 24) = 15;
                            *(_BYTE *)v87 = 0;
                            v47 = _mm_srli_si128(v88, 8).m128i_u64[0];
                            v85 = v88.m128i_i64[0];
                          }
                          if ( v107 > 0xF )
                          {
                            v89 = (void *)v106[0];
                            if ( v107 + 1 >= 0x1000 )
                            {
                              if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                                goto LABEL_294;
                              v89 = *(void **)(v106[0] - 8LL);
                            }
                            sub_1800931A0(v89);
                          }
                          if ( v85 )
                            goto LABEL_247;
                        }
                        v90 = sub_180022E70(v10);
                        if ( !v90 )
                          goto LABEL_267;
                        v91 = sub_180022A10(v90, v106);
                        if ( &v127 != (__int128 *)v91 )
                        {
                          if ( v47 > 0xF )
                          {
                            v92 = (void *)v127;
                            if ( v47 + 1 >= 0x1000 )
                            {
                              if ( (unsigned __int64)(v127 - *(_QWORD *)(v127 - 8) - 8) > 0x1F )
                                goto LABEL_294;
                              v92 = *(void **)(v127 - 8);
                            }
                            sub_1800931A0(v92);
                          }
                          v127 = *(_OWORD *)v91;
                          v128 = *(__m128i *)(v91 + 16);
                          v93 = v128;
                          *(_QWORD *)(v91 + 16) = 0;
                          *(_QWORD *)(v91 + 24) = 15;
                          *(_BYTE *)v91 = 0;
                          v47 = _mm_srli_si128(v93, 8).m128i_u64[0];
                          v85 = v93.m128i_i64[0];
                        }
                        if ( v107 > 0xF )
                        {
                          v94 = (void *)v106[0];
                          if ( v107 + 1 >= 0x1000 )
                          {
                            if ( (unsigned __int64)(v106[0] - *(_QWORD *)(v106[0] - 8LL) - 8LL) > 0x1F )
                              goto LABEL_294;
                            v94 = *(void **)(v106[0] - 8LL);
                          }
                          sub_1800931A0(v94);
                        }
                        if ( v85 )
                        {
LABEL_247:
                          v95 = &v127;
                          v40 = (LPVOID *)v127;
                          if ( v47 > 0xF )
                            v95 = (__int128 *)v127;
                          if ( v85 != 6 || (unsigned int)sub_1800B8AD0(v95, &dword_1800C90EC, 6) )
                          {
                            v96 = (LPVOID *)&v127;
                            if ( v47 > 0xF )
                              v96 = v40;
                            if ( v85 != 6 || (unsigned int)sub_1800B8AD0(v96, "player", 6) )
                            {
                              v97 = (LPVOID *)&v127;
                              if ( v47 > 0xF )
                                v97 = v40;
                              if ( v85 != 7 || (unsigned int)sub_1800B8AD0(v97, "Players", 7) )
                              {
                                v98 = sub_180025370(v106, "Players - ", &v127);
                                if ( &v109 != (__int128 *)v98 )
                                {
                                  if ( v111 > 0xF )
                                  {
                                    v99 = (void *)v109;
                                    if ( v111 + 1 >= 0x1000 )
                                    {
                                      if ( (unsigned __int64)(v109 - *(_QWORD *)(v109 - 8) - 8) > 0x1F )
LABEL_294:
                                        __fastfail(5u);
                                      v99 = *(void **)(v109 - 8);
                                    }
                                    sub_1800931A0(v99);
                                  }
                                  v110 = 0;
                                  v111 = 15;
                                  LOBYTE(v109) = 0;
                                  v109 = *(_OWORD *)v98;
                                  v110 = *(_QWORD *)(v98 + 16);
                                  v111 = *(_QWORD *)(v98 + 24);
                                  *(_QWORD *)(v98 + 16) = 0;
                                  *(_QWORD *)(v98 + 24) = 15;
                                  *(_BYTE *)v98 = 0;
                                }
                                sub_180015D80(v106);
                                v47 = v128.m128i_u64[1];
                                v40 = (LPVOID *)v127;
                                goto LABEL_269;
                              }
                            }
                          }
                        }
                        else
                        {
LABEL_267:
                          v40 = (LPVOID *)v127;
                        }
                        sub_1800254F0(&v109, "Players");
LABEL_269:
                        v114 = sub_180022FC0(v10);
                        v100 = sub_180023000(v10);
                        v115 = LODWORD(v100);
                        if ( v114 < 0.2 )
                          v114 = 1.8;
                        if ( v100 < 0.1 )
                          v115 = 1053609165;
                        v101 = sub_180022DA0(v10);
                        if ( v101 )
                        {
                          v129 = 0;
                          v120 = sub_1800230A0(v101, &v118, &v129);
                        }
                        goto LABEL_275;
                      }
                    }
                    else
                    {
                      v21 = 3;
                      if ( byte_1800FAB3C || byte_1800FAB3D )
                        goto LABEL_51;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
