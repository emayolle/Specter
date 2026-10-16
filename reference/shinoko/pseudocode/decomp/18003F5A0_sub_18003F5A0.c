// sub_18003F5A0 size=3608
__int64 __fastcall sub_18003F5A0(__int64 a1, __int64 a2, int *a3, int *a4, int a5, _DWORD *a6, float *a7)
{
  int v8; // ecx
  unsigned int v9; // ebx
  __int64 v10; // r12
  int v11; // r13d
  float v12; // xmm6_4
  float v13; // xmm13_4
  float v14; // xmm9_4
  float v15; // xmm12_4
  float v16; // xmm7_4
  float v17; // xmm8_4
  int v18; // r9d
  __int64 v19; // rsi
  float v20; // xmm12_4
  float *v21; // r15
  float v22; // xmm3_4
  float v23; // xmm5_4
  float v24; // xmm0_4
  float v25; // xmm2_4
  float v26; // xmm4_4
  float v27; // xmm1_4
  float v28; // xmm5_4
  float v29; // xmm3_4
  float v30; // xmm4_4
  float v31; // xmm2_4
  __int64 v32; // rbx
  char v33; // dl
  char v34; // al
  __int64 *v35; // rax
  float v36; // xmm9_4
  float v37; // xmm6_4
  float v38; // xmm10_4
  float v39; // xmm5_4
  float v40; // xmm8_4
  float v41; // xmm7_4
  float v42; // xmm2_4
  float v43; // xmm1_4
  __int64 v44; // rcx
  int v45; // eax
  int v46; // ecx
  int v47; // eax
  float v48; // xmm11_4
  int v49; // r13d
  __int64 *v50; // r12
  float *v51; // rax
  int v52; // esi
  char v53; // r14
  __int64 v54; // r15
  __int64 v55; // rbx
  __int64 v56; // rcx
  int v57; // ecx
  int v58; // eax
  __int64 v59; // r8
  __int64 v60; // rcx
  __int64 v61; // rdx
  __int64 v62; // rax
  char v63; // al
  __m128 v64; // xmm0
  char v65; // dl
  float v66; // xmm5_4
  float v67; // xmm6_4
  float v68; // xmm1_4
  float *v69; // rax
  float v70; // xmm2_4
  float v71; // xmm1_4
  float v72; // xmm0_4
  float v73; // xmm1_4
  float v74; // xmm0_4
  float v75; // xmm2_4
  float v76; // xmm4_4
  __int64 v77; // rcx
  int v78; // eax
  __int64 v79; // rax
  int v80; // eax
  __m128 *v81; // rax
  float v82; // xmm3_4
  float v83; // xmm4_4
  float v84; // xmm1_4
  float v85; // xmm2_4
  float v86; // xmm1_4
  float v87; // xmm8_4
  float v88; // xmm9_4
  int v89; // eax
  __m128 v90; // xmm6
  float v91; // xmm7_4
  __int64 *v92; // rax
  float v93; // xmm1_4
  float v94; // xmm0_4
  int v95; // xmm1_4
  float v96; // xmm2_4
  float v97; // xmm5_4
  float v98; // xmm4_4
  float v99; // xmm6_4
  int v100; // xmm1_4
  float v101; // xmm1_4
  float v102; // xmm0_4
  float v103; // xmm3_4
  char v105; // [rsp+30h] [rbp-D0h] BYREF
  char v106; // [rsp+31h] [rbp-CFh] BYREF
  char v107; // [rsp+32h] [rbp-CEh] BYREF
  char v108; // [rsp+33h] [rbp-CDh]
  int v109; // [rsp+34h] [rbp-CCh]
  float v110; // [rsp+38h] [rbp-C8h]
  float v111; // [rsp+3Ch] [rbp-C4h]
  float v112; // [rsp+40h] [rbp-C0h]
  unsigned __int64 v113; // [rsp+48h] [rbp-B8h] BYREF
  __int64 v114; // [rsp+50h] [rbp-B0h] BYREF
  __int64 v115; // [rsp+58h] [rbp-A8h]
  float v116; // [rsp+60h] [rbp-A0h] BYREF
  float v117; // [rsp+64h] [rbp-9Ch]
  unsigned __int64 v118; // [rsp+68h] [rbp-98h] BYREF
  unsigned __int64 v119; // [rsp+70h] [rbp-90h] BYREF
  float v120; // [rsp+78h] [rbp-88h] BYREF
  float v121; // [rsp+7Ch] [rbp-84h]
  float v122; // [rsp+80h] [rbp-80h]
  float v123; // [rsp+84h] [rbp-7Ch]
  __m128 v124; // [rsp+88h] [rbp-78h] BYREF
  float v125; // [rsp+98h] [rbp-68h] BYREF
  float v126; // [rsp+9Ch] [rbp-64h] BYREF
  __int64 v127; // [rsp+A0h] [rbp-60h]
  float *v128; // [rsp+A8h] [rbp-58h]
  __int64 v129; // [rsp+B0h] [rbp-50h]
  float *v130; // [rsp+B8h] [rbp-48h]
  __m128 v131; // [rsp+C0h] [rbp-40h] BYREF
  float v132; // [rsp+1C0h] [rbp+C0h] BYREF
  __int64 v133; // [rsp+1C8h] [rbp+C8h]
  int *v134; // [rsp+1D0h] [rbp+D0h]
  int *v135; // [rsp+1D8h] [rbp+D8h]

  v135 = a4;
  v134 = a3;
  v133 = a2;
  v8 = *(_DWORD *)(a1 + 20);
  if ( (v8 & 2) != 0
    || *(char *)(a1 + 228) > 0
    || *(char *)(a1 + 229) > 0
    || (v8 & 0x40) != 0 && (*(_BYTE *)(a1 + 24) & 0xC) == 0
    || !*(_BYTE *)(a1 + 205) )
  {
    return 0;
  }
  v9 = 0;
  v10 = qword_18010C470;
  v11 = a5;
  v115 = qword_18010C470;
  v109 = 0;
  if ( a5 <= 0 )
    v12 = 0.0;
  else
    v12 = (float)(int)(float)((float)(int)fmaxf(
                                            *(float *)(qword_18010C470 + 4432) * 1.35,
                                            (float)(*(float *)(a1 + 96) + 1.0)
                                          + (float)(*(float *)(qword_18010C470 + 4432) * 0.2))
                            * 0.75);
  v13 = *(float *)(qword_18010C470 + 5204);
  v110 = v12;
  v14 = *a7;
  v15 = a7[2];
  v16 = a7[3];
  v17 = a7[1];
  v111 = *a7;
  v112 = v15;
  *(float *)&v113 = v16;
  if ( !*(_BYTE *)(qword_18010C470 + 95) || (v8 & 1) != 0 )
  {
    v108 = 0;
  }
  else
  {
    v17 = v17 - *(float *)(a1 + 104);
    v108 = 1;
  }
  v132 = v17;
  v116 = 3.4028235e38;
  v117 = 3.4028235e38;
  v114 = 0x7F7FFFFF7F7FFFFFLL;
  *(_DWORD *)(a1 + 368) = 1;
  sub_1800466C0("#RESIZE");
  if ( v11 > 0 )
  {
    v19 = 0;
    v20 = -v12;
    while ( 1 )
    {
      v21 = (float *)(0x180000000LL + 24 * v19 + 874064);
      v22 = (float)((float)((float)(*(float *)(a1 + 40) + *(float *)(a1 + 48)) - *(float *)(a1 + 40)) * *v21)
          + *(float *)(a1 + 40);
      v23 = *(float *)&dword_1800D5658[6 * v19];
      v24 = v23 * v13;
      v25 = (float)((float)((float)(*(float *)(a1 + 44) + *(float *)(a1 + 52)) - *(float *)(a1 + 44))
                  * *(float *)&dword_1800D5654[6 * v19])
          + *(float *)(a1 + 44);
      v26 = *(float *)&dword_1800D565C[6 * v19];
      v27 = v26 * v13;
      v28 = (float)(v23 * v12) + v22;
      v29 = v22 - v24;
      v30 = (float)(v26 * v12) + v25;
      v31 = v25 - v27;
      v122 = v28;
      v120 = v29;
      v121 = v31;
      v123 = v30;
      if ( v29 > v28 )
      {
        v120 = v28;
        v122 = v29;
      }
      if ( v31 > v30 )
      {
        v121 = v30;
        v123 = v31;
      }
      v32 = (unsigned int)sub_180046640(a1, (unsigned int)v19);
      sub_18004A070(&v120, v32, 0, 2);
      sub_18006F740((unsigned int)&v120, v32, (unsigned int)&v107, (unsigned int)&v106, 264192);
      v33 = v107;
      if ( v107 || (v34 = v106) != 0 )
      {
        *(_DWORD *)(qword_18010C470 + 9240) = ((v19 & 1) == 0) + 5;
        v34 = v106;
        if ( v106 )
        {
          if ( *(_BYTE *)(v10 + 2837) )
          {
            v35 = (__int64 *)sub_18003ECF0(&v119, a1, v133);
            v109 = 3;
            v114 = *v35;
            sub_180039FD0(0, 0);
          }
          else
          {
            v36 = *(float *)&dword_1800D5654[6 * v19];
            if ( v36 == 1.0 || v36 == 0.0 && v108 )
              v37 = v17;
            else
              v37 = -3.4028235e38;
            v38 = *v21;
            if ( *v21 == 1.0 )
              v39 = v111;
            else
              v39 = -3.4028235e38;
            if ( v36 == 0.0 )
              v40 = v16;
            else
              v40 = 3.4028235e38;
            if ( v38 == 0.0 )
              v41 = v112;
            else
              v41 = 3.4028235e38;
            v42 = (float)(*(float *)(v10 + 224) - *(float *)(v10 + 5360))
                + (float)((float)((float)((float)(v20 * *(float *)&dword_1800D5658[6 * v19])
                                        - (float)(*(float *)&dword_1800D5658[6 * v19] * v13))
                                * v38)
                        + (float)(*(float *)&dword_1800D5658[6 * v19] * v13));
            v43 = (float)(*(float *)(v10 + 228) - *(float *)(v10 + 5364))
                + (float)((float)((float)((float)(v20 * *(float *)&dword_1800D565C[6 * v19])
                                        - (float)(*(float *)&dword_1800D565C[6 * v19] * v13))
                                * v36)
                        + (float)(*(float *)&dword_1800D565C[6 * v19] * v13));
            if ( v37 <= v43 )
              v37 = fminf(v40, v43);
            if ( v39 <= v42 )
              v39 = fminf(v41, v42);
            v118 = __PAIR64__(LODWORD(v37), LODWORD(v39));
            sub_18003F280(a1, (unsigned int)&v118, (_DWORD)v21, (unsigned int)&v116, (__int64)&v114);
            v17 = v132;
            v16 = *(float *)&v113;
            v12 = v110;
          }
          v34 = v106;
          if ( v106 )
          {
            v33 = v107;
LABEL_49:
            if ( v34 )
              v44 = 32;
            else
              v44 = (v33 != 0) + 30LL;
            v124 = *(__m128 *)(qword_18010C470 + 16 * v44 + 3424);
            v124.m128_f32[3] = _mm_shuffle_ps(v124, v124, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
            sub_180036620(&v124);
            a6[v19] = v45;
            goto LABEL_53;
          }
        }
        v33 = v107;
        if ( v107 )
          goto LABEL_49;
      }
      if ( !(_DWORD)v19 && (*(_DWORD *)(a1 + 20) & 0x1000000) == 0 )
        goto LABEL_49;
LABEL_53:
      v19 = (unsigned int)(v19 + 1);
      if ( (int)v19 >= v11 )
      {
        v14 = v111;
        v15 = v112;
        v9 = v109;
        break;
      }
    }
  }
  if ( (*(_DWORD *)(a1 + 20) & 0x1000000) != 0 )
    v46 = *(_DWORD *)(a1 + 24) & 8 | (*(_DWORD *)(a1 + 24) >> 1) & 2;
  else
    v46 = *(_BYTE *)(v10 + 94) != 0 ? 0xF : 0;
  v47 = 1;
  v48 = *(float *)&v113;
  v49 = 0;
  LODWORD(v111) = 1;
  v112 = *(float *)&v46;
  do
  {
    if ( (v47 & v46) == 0 )
    {
      v109 = v9;
      goto LABEL_118;
    }
    if ( (unsigned int)v49 < 2 )
    {
      v129 = 204;
      v53 = 0;
      v128 = (float *)&v113;
      v51 = &v125;
      v118 = 224;
      v52 = 4;
      v127 = 5360;
      v54 = 0;
      v50 = &v114;
    }
    else
    {
      v129 = 208;
      v128 = (float *)&v113 + 1;
      v50 = (__int64 *)((char *)&v114 + 4);
      v51 = &v126;
      v118 = 228;
      v52 = 3;
      v127 = 5364;
      v53 = 1;
      v54 = 4;
    }
    v130 = v51;
    sub_18003F460((unsigned int)&v124, a1, v49, v18, *(_DWORD *)(v115 + 5204));
    v55 = (unsigned int)sub_180046640(a1, (unsigned int)(v49 + 4));
    sub_18004A070(&v124, v55, 0, 2);
    sub_18006F740((unsigned int)&v124, v55, (unsigned int)&v132, (unsigned int)&v105, 264192);
    v56 = v115;
    if ( !LOBYTE(v132) )
      goto LABEL_66;
    if ( *(float *)(v115 + 5320) <= 0.039999999 )
    {
      LOBYTE(v132) = 0;
LABEL_66:
      if ( !v105 )
        goto LABEL_72;
    }
    *(_DWORD *)(qword_18010C470 + 9240) = v52;
    if ( v105 )
    {
      if ( *(_BYTE *)(v56 + 2837) )
      {
        if ( ((v49 - 1) & 0xFFFFFFFD) == 0 )
        {
          v57 = *(_DWORD *)(v54 + sub_18003ECF0(&v131, a1, v133));
          v58 = v109 | (1 << v53);
          *(_DWORD *)v50 = v57;
          v109 = v58;
          v105 = 0;
          LOBYTE(v132) = 0;
        }
        sub_180039FD0(0, 0);
        goto LABEL_72;
      }
      v10 = v115;
      v18 = 28 * v49;
      v59 = *(_QWORD *)(v115 + 5256);
      if ( v59 && *(_DWORD *)(v115 + 5276) == *(_DWORD *)(v115 + 5032) )
      {
        v60 = a1;
        v61 = a1;
        do
        {
          v62 = v61;
          v61 = *(_QWORD *)(v61 + 960);
        }
        while ( v62 != v61 );
        if ( v61 != v59 )
        {
          while ( v60 != v59 )
          {
            if ( v60 != v61 )
            {
              v60 = *(_QWORD *)(v60 + 944);
              if ( v60 )
                continue;
            }
            goto LABEL_86;
          }
        }
        v63 = 1;
      }
      else
      {
LABEL_86:
        v63 = 0;
      }
      if ( *(_BYTE *)(v115 + 5344) || v63 )
      {
        v64 = v124;
        *(_BYTE *)(v115 + 9664) = 0;
        *(__m128 *)(v10 + 9648) = v64;
      }
      if ( (*(_DWORD *)(a1 + 20) & 0x1000000) != 0 && *(_OWORD *)(v10 + 9648) != *(_OWORD *)&v124 )
        *(_BYTE *)(v10 + 9664) = 1;
      v65 = 0;
      v66 = fminf(*(float *)&dword_1800D55DC[7 * v49], dword_1800D55E4[7 * v49]);
      v67 = fminf(*(float *)&dword_1800D55D8[7 * v49], *(float *)&dword_1800D55E0[7 * v49]);
      v68 = (float)(v66 * *(float *)(a1 + 52)) + *(float *)(a1 + 44);
      v69 = v128;
      v70 = (float)(*(float *)(v118 + v10) - *(float *)(v127 + v10)) + *(float *)(v10 + 5204);
      v125 = (float)(v67 * *(float *)(a1 + 48)) + *(float *)(a1 + 40);
      v113 = *(_QWORD *)(a1 + 40);
      v126 = v68;
      *v128 = v70;
      if ( *(_BYTE *)(v10 + 9664) )
      {
        v71 = *(float *)(v129 + v10);
        v72 = v71 + *v130;
        *v69 = v72;
        if ( v71 == 0.0 || v71 > 0.0 == v72 > v70 )
          v65 = 1;
      }
      if ( v49 == 3 || v49 == 2 && v108 )
        v73 = v17;
      else
        v73 = -3.4028235e38;
      if ( v49 == 1 )
      {
        v74 = v14;
        v75 = 3.4028235e38;
      }
      else
      {
        v74 = -3.4028235e38;
        if ( v49 == 2 )
        {
          v75 = v48;
        }
        else
        {
          v75 = 3.4028235e38;
          if ( !v49 )
          {
            v76 = v15;
            goto LABEL_106;
          }
        }
      }
      v76 = 3.4028235e38;
LABEL_106:
      if ( v73 <= *((float *)&v113 + 1) )
        v73 = fminf(v75, *((float *)&v113 + 1));
      if ( v74 <= *(float *)&v113 )
        v74 = fminf(v76, *(float *)&v113);
      v113 = __PAIR64__(LODWORD(v73), LODWORD(v74));
      if ( !v65 )
      {
        v119 = __PAIR64__(LODWORD(v66), LODWORD(v67));
        sub_18003F280(a1, (unsigned int)&v113, (unsigned int)&v119, (unsigned int)&v116, (__int64)&v114);
      }
      goto LABEL_73;
    }
LABEL_72:
    v10 = v115;
LABEL_73:
    if ( LOBYTE(v132) )
      *v134 = v49;
    v9 = v109;
    if ( v105 )
      *v135 = v49;
    *(float *)&v47 = v111;
    v46 = LODWORD(v112);
LABEL_118:
    *(float *)&v47 = COERCE_FLOAT(__ROL4__(v47, 1));
    ++v49;
    v111 = *(float *)&v47;
  }
  while ( v49 < 4 );
  v77 = *(_QWORD *)(qword_18010C470 + 5216);
  v78 = *(_DWORD *)(v77 + 264);
  if ( v78 > 1 )
    *(_DWORD *)(v77 + 264) = v78 - 1;
  else
    sub_180049A30("Calling PopID() too many times!");
  *(_DWORD *)(a1 + 368) = 0;
  v79 = *(_QWORD *)(v10 + 8592);
  if ( v79 && *(_QWORD *)(v79 + 960) == a1 )
  {
    v80 = *(_DWORD *)(v10 + 8184);
    if ( v80 == 2 )
    {
      if ( *(_BYTE *)(v10 + 253) )
      {
        v81 = (__m128 *)qword_18010C470;
        v82 = *(float *)(qword_18010C470 + 304) - *(float *)(qword_18010C470 + 288);
        v83 = *(float *)(qword_18010C470 + 336) - *(float *)(qword_18010C470 + 320);
LABEL_129:
        if ( v82 != 0.0 || v83 != 0.0 )
        {
          v84 = (float)(*(float *)(v10 + 32) * 600.0) * fminf(*(float *)(v10 + 24), *(float *)(v10 + 28));
          v85 = (float)(v84 * v83) + *(float *)(v10 + 8648);
          v86 = (float)(v84 * v82) + *(float *)(v10 + 8644);
          *(float *)(v10 + 8648) = v85;
          *(float *)(v10 + 8644) = v86;
          v87 = (float)(v17 - *(float *)(a1 + 44)) - *(float *)(a1 + 52);
          v88 = (float)(v14 - *(float *)(a1 + 40)) - *(float *)(a1 + 48);
          *(_BYTE *)(v10 + 8628) = 0;
          *(_BYTE *)(v10 + 8113) = 1;
          *(float *)(v10 + 8648) = fmaxf(v85, v87);
          *(float *)(v10 + 8644) = fmaxf(v86, v88);
          v131 = v81[246];
          v131.m128_f32[3] = _mm_shuffle_ps(v131, v131, 255).m128_f32[0] * v81[196].m128_f32[3];
          sub_180036620(&v131);
          *a6 = v89;
          v90 = _mm_cvtepi32_ps(_mm_cvttps_epi32((__m128)*(unsigned __int64 *)(v10 + 8644)));
          v91 = _mm_shuffle_ps(v90, v90, 85).m128_f32[0];
          if ( v90.m128_f32[0] != 0.0 || v91 != 0.0 )
          {
            v119 = _mm_add_ps((__m128)*(unsigned __int64 *)(a1 + 56), v90).m128_u64[0];
            v92 = (__int64 *)sub_18003ECF0(&v131, a1, &v119);
            v93 = *(float *)(v10 + 8644) - v90.m128_f32[0];
            v114 = *v92;
            v94 = *(float *)(v10 + 8648) - v91;
            *(float *)(v10 + 8644) = v93;
            *(float *)(v10 + 8648) = v94;
          }
        }
      }
    }
    else if ( v80 == 3 )
    {
      v81 = (__m128 *)qword_18010C470;
      v82 = *(float *)(qword_18010C470 + 2304) - *(float *)(qword_18010C470 + 2288);
      v83 = *(float *)(qword_18010C470 + 2336) - *(float *)(qword_18010C470 + 2320);
      goto LABEL_129;
    }
  }
  v95 = v114;
  v96 = *(float *)(a1 + 40);
  v97 = *(float *)(a1 + 44);
  v98 = *(float *)(a1 + 56);
  v99 = *(float *)(a1 + 60);
  if ( *(float *)&v114 != 3.4028235e38 && (*(float *)(a1 + 48) != *(float *)&v114 || v98 != *(float *)&v114) )
  {
    *(_DWORD *)(a1 + 56) = v114;
    *(_DWORD *)(a1 + 48) = v95;
  }
  v100 = HIDWORD(v114);
  if ( *((float *)&v114 + 1) != 3.4028235e38
    && (*(float *)(a1 + 52) != *((float *)&v114 + 1) || v99 != *((float *)&v114 + 1)) )
  {
    *(_DWORD *)(a1 + 60) = HIDWORD(v114);
    *(_DWORD *)(a1 + 52) = v100;
  }
  if ( v116 == 3.4028235e38 )
  {
    v101 = v96;
  }
  else
  {
    v101 = v96;
    v102 = (float)(int)v116;
    if ( v96 != v102 )
    {
      *(float *)(a1 + 40) = v102;
      v101 = v102;
    }
  }
  if ( v117 != 3.4028235e38 )
  {
    v103 = (float)(int)v117;
    if ( v97 != v103 )
      *(float *)(a1 + 44) = v103;
  }
  if ( (v96 != v101 || v97 != *(float *)(a1 + 44) || v98 != *(float *)(a1 + 56) || v99 != *(float *)(a1 + 60))
    && (*(_DWORD *)(a1 + 20) & 0x100) == 0
    && *(float *)(qword_18010C470 + 9908) <= 0.0 )
  {
    *(_DWORD *)(qword_18010C470 + 9908) = *(_DWORD *)(qword_18010C470 + 36);
  }
  if ( *v135 != -1 )
    *(_OWORD *)(v10 + 9648) = *(_OWORD *)sub_18003F460((unsigned int)&v124, a1, *v135, v18, *(_DWORD *)(v10 + 5204));
  return v9;
}
