// sub_18007E600 size=7480
char __fastcall sub_18007E600(_BYTE *a1, __int64 a2, unsigned int a3)
{
  __m128 *v3; // r13
  __int64 v5; // r12
  _BYTE *v6; // rbx
  unsigned __int64 v7; // r14
  float v9; // xmm6_4
  float v10; // xmm6_4
  double v11; // xmm0_8
  float v12; // xmm7_4
  __int64 v13; // rdx
  int v14; // r8d
  __int32 v15; // xmm15_4
  int v16; // edi
  float v17; // xmm9_4
  int v18; // r15d
  int v19; // r14d
  __int64 v20; // r9
  char *v21; // rdx
  unsigned __int8 v22; // al
  unsigned int v23; // ebx
  unsigned __int64 v24; // rcx
  int v25; // ebx
  __int64 v26; // rdi
  __int64 v27; // rdx
  __int64 v28; // rcx
  __int64 v29; // r8
  __int64 v30; // r9
  unsigned int v31; // edi
  char v32; // al
  __int64 v33; // r10
  char *v34; // rdx
  unsigned __int8 v35; // al
  unsigned int v36; // ebx
  unsigned __int64 v37; // rcx
  int v38; // ebx
  float v39; // xmm4_4
  float v40; // xmm0_4
  float v41; // xmm3_4
  int v42; // r13d
  float v43; // xmm0_4
  float v44; // xmm2_4
  int v45; // r12d
  float v46; // xmm0_4
  int v47; // r15d
  int v48; // ebx
  float v49; // xmm1_4
  float v50; // xmm0_4
  void (__fastcall *v51)(__int64, float *); // rax
  void (__fastcall *v52)(__int64, float *); // rax
  void (__fastcall *v53)(__int64, float *); // rax
  void (__fastcall *v54)(__int64, float *); // rax
  __int64 v55; // rdx
  int v56; // ecx
  __int32 v57; // ecx
  __int64 v58; // rcx
  unsigned int v59; // esi
  int v60; // ebx
  int v61; // r9d
  float v62; // xmm11_4
  float v63; // xmm6_4
  float v64; // xmm8_4
  float v65; // xmm7_4
  float v66; // xmm0_4
  float *v67; // r9
  int v68; // eax
  float v69; // xmm0_4
  float v70; // xmm0_4
  char v71; // r12
  char v72; // r15
  bool v73; // zf
  float v74; // xmm12_4
  int v75; // xmm10_4
  float v76; // xmm1_4
  int v77; // r14d
  float v78; // xmm6_4
  const char *v79; // rdx
  float v80; // xmm9_4
  float v81; // xmm8_4
  int v82; // r9d
  float *v83; // rax
  __int64 v84; // rcx
  int v85; // r14d
  float v86; // xmm7_4
  __int64 v87; // rcx
  int v88; // r15d
  char **v89; // rdi
  char v90; // si
  int v91; // ebx
  __int64 v92; // rax
  float v93; // xmm0_4
  int v94; // xmm0_4
  unsigned __int64 v95; // rdi
  float v96; // xmm0_4
  int v97; // esi
  char **v98; // rdi
  int v99; // ebx
  __int64 v100; // rax
  float v101; // xmm0_4
  __int32 v102; // edx
  __int32 v103; // ecx
  __int32 v104; // eax
  __int32 v105; // r9d
  __int32 v106; // ecx
  __int32 v107; // eax
  __int32 v108; // r9d
  __int64 v109; // rax
  char *v110; // rcx
  __int64 v111; // rdx
  unsigned __int64 v112; // rax
  unsigned __int64 v113; // rax
  __int32 v114; // xmm1_4
  float v115; // xmm1_4
  __int64 v116; // rax
  float v117; // xmm0_4
  _BYTE *v118; // rbx
  _BYTE *v119; // r9
  __int32 v120; // xmm1_4
  __int32 v121; // eax
  __int32 v122; // xmm6_4
  __int32 v123; // xmm7_4
  __int32 v124; // xmm8_4
  __int32 v125; // eax
  __int64 v126; // r11
  char *v127; // r9
  unsigned __int8 v128; // al
  unsigned int v129; // ebx
  unsigned __int64 v130; // rcx
  int v131; // ebx
  __int64 v132; // rax
  float v133; // xmm0_4
  int v134; // r8d
  __int64 v135; // rcx
  int v136; // eax
  __int64 v137; // rsi
  int v138; // r9d
  __int64 v139; // rax
  __int64 v140; // r14
  int v141; // ebx
  __int64 v142; // r8
  float v143; // xmm1_4
  float v144; // xmm2_4
  __int64 v145; // rcx
  __int64 v146; // rax
  float v147; // xmm0_4
  __int64 v148; // rax
  float v149; // xmm0_4
  __int64 v150; // rax
  float v151; // xmm0_4
  float *v152; // rdx
  int v153; // ebx
  unsigned int v154; // ebx
  __int64 v155; // rax
  __int64 v156; // rax
  __int64 v157; // rdi
  float *m128_f32; // rdx
  __int128 *v159; // rax
  char v160; // r13
  __int128 v161; // xmm0
  __int64 v162; // rcx
  char v163; // al
  float v164; // xmm3_4
  float v165; // xmm4_4
  float v166; // xmm5_4
  float v167; // xmm2_4
  float v168; // xmm1_4
  int v169; // r12d
  _BYTE *v170; // r15
  __int64 v171; // rcx
  int v172; // eax
  int v173; // r10d
  unsigned int v174; // xmm5_4
  float v175; // xmm2_4
  float v176; // xmm3_4
  float v177; // xmm4_4
  bool v178; // cf
  __int64 v179; // rcx
  _DWORD *v180; // rax
  int v181; // xmm1_4
  unsigned int v182; // xmm0_4
  int v183; // eax
  int v184; // eax
  char v185; // al
  char v186; // cl
  __int64 v187; // rax
  __m128 *v188; // rbx
  __int64 v189; // rcx
  char v190; // al
  float v191; // xmm3_4
  float v192; // xmm4_4
  float v193; // xmm5_4
  float v194; // xmm2_4
  float v195; // xmm1_4
  __int32 v196; // r14d
  int v197; // r15d
  __int8 *v198; // rdi
  __int64 v199; // rcx
  int v200; // eax
  int v201; // r10d
  unsigned __int64 v202; // rsi
  unsigned int v203; // xmm5_4
  float v204; // xmm2_4
  float v205; // xmm3_4
  float v206; // xmm4_4
  char v207; // r12
  __int64 v208; // rcx
  _DWORD *v209; // rax
  int v210; // xmm1_4
  unsigned int v211; // xmm0_4
  int v212; // eax
  __int32 v213; // eax
  char v214; // al
  __int64 v215; // rbx
  __int64 v216; // r8
  __int64 v217; // rdx
  __int32 v218; // eax
  __int32 v219; // edx
  __int64 v220; // rcx
  int v221; // eax
  __int64 v222; // [rsp+30h] [rbp-D0h]
  int v223; // [rsp+38h] [rbp-C8h]
  __m128 v224; // [rsp+40h] [rbp-C0h] BYREF
  int v225; // [rsp+50h] [rbp-B0h]
  char v226; // [rsp+54h] [rbp-ACh]
  int v227; // [rsp+58h] [rbp-A8h]
  __m128 v228; // [rsp+60h] [rbp-A0h] BYREF
  __m128 v229; // [rsp+70h] [rbp-90h] BYREF
  _BYTE *v230; // [rsp+80h] [rbp-80h] BYREF
  __m128i v231; // [rsp+88h] [rbp-78h] BYREF
  unsigned __int64 v232; // [rsp+98h] [rbp-68h] BYREF
  __int32 v233; // [rsp+A0h] [rbp-60h]
  int v234; // [rsp+A4h] [rbp-5Ch]
  int v235; // [rsp+A8h] [rbp-58h]
  __int64 v236; // [rsp+B0h] [rbp-50h] BYREF
  __int64 v237; // [rsp+B8h] [rbp-48h] BYREF
  unsigned __int64 v238; // [rsp+C0h] [rbp-40h]
  int v239; // [rsp+C8h] [rbp-38h]
  float v240; // [rsp+CCh] [rbp-34h]
  unsigned int v241; // [rsp+D0h] [rbp-30h]
  __int32 v242; // [rsp+D4h] [rbp-2Ch]
  __int64 v243; // [rsp+D8h] [rbp-28h]
  float v244[4]; // [rsp+E0h] [rbp-20h] BYREF
  float v245[16]; // [rsp+F0h] [rbp-10h] BYREF
  char v246[64]; // [rsp+130h] [rbp+30h] BYREF
  _BYTE *v247; // [rsp+260h] [rbp+160h]
  unsigned int v249; // [rsp+270h] [rbp+170h]
  __int64 v250; // [rsp+278h] [rbp+178h] BYREF

  v247 = a1;
  v3 = (__m128 *)qword_18010C470;
  v5 = a2;
  v243 = qword_18010C470;
  v6 = a1;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v7 = v3[326].m128_u64[0];
  v232 = v7;
  if ( *(_BYTE *)(v7 + 209) )
    return 0;
  v9 = v3[201].m128_f32[0];
  v230 = a1;
  v10 = (float)(v9 + v9) + v3[277].m128_f32[0];
  v240 = v10;
  if ( a1 != (_BYTE *)-1LL )
  {
    do
    {
      if ( !*a1 || *a1 == 35 && a1[1] == 35 )
        break;
      ++a1;
    }
    while ( a1 != (_BYTE *)-1LL );
    v230 = a1;
  }
  v11 = sub_18004AE40();
  v12 = *(float *)&v11;
  v3[480].m128_u64[1] = 0;
  sub_18004AFD0();
  sub_1800466C0(v6);
  v242 = v3[597].m128_i32[3];
  if ( !v242 )
    v3[597].m128_i32[3] = *(_DWORD *)(*(_QWORD *)(v7 + 272) + 4LL * *(int *)(v7 + 264) - 4);
  v241 = a3;
  if ( (a3 & 0x20) != 0 )
    a3 = a3 & 0xFF8FFFF7 | 0x100008;
  v15 = 1065353216;
  v16 = 255;
  v17 = 0.5;
  if ( (a3 & 8) == 0 )
  {
    v18 = a3 & 0x1800000;
    v19 = a3 & 0x700000;
    if ( (a3 & 0x700000) == 0 || !v18 )
    {
      if ( *(_DWORD *)(qword_18010C470 + 8048) > *(_DWORD *)(qword_18010C470 + 8064) )
      {
        v20 = *(_QWORD *)(qword_18010C470 + 5216);
        v21 = "ontext";
        v22 = 99;
        v23 = ~*(_DWORD *)(*(_QWORD *)(v20 + 272) + 4LL * *(int *)(v20 + 264) - 4);
        do
        {
          if ( v22 == 35 && *v21 == 35 && v21[1] == 35 )
            v23 = ~*(_DWORD *)(*(_QWORD *)(v20 + 272) + 4LL * *(int *)(v20 + 264) - 4);
          v24 = v22 ^ (unsigned __int64)(unsigned __int8)v23;
          v22 = *v21++;
          v23 = dword_1800D56B0[v24] ^ (v23 >> 8);
        }
        while ( v22 );
        v25 = ~v23;
        if ( *(_DWORD *)(*(_QWORD *)v20 + 5304LL) == v25 )
          sub_180053310(v25, 11, "context");
        if ( sub_18004C6E0(v25) )
        {
          v26 = qword_18010C470;
          LOBYTE(v13) = 1;
          v237 = qword_18010C470;
          sub_180045260(0x10000, v13);
          v31 = *(_DWORD *)(v26 + 9560);
          if ( !v19 )
          {
            if ( sub_1800717F0("RGB", (v31 & 0x100000) != 0) )
              v31 = v31 & 0xFF8FFFFF | 0x100000;
            if ( sub_1800717F0("HSV", (v31 & 0x200000) != 0) )
              v31 = v31 & 0xFF8FFFFF | 0x200000;
            if ( sub_1800717F0("Hex", (v31 & 0x400000) != 0) )
              v31 = v31 & 0xFF8FFFFF | 0x400000;
          }
          if ( !v18 )
          {
            if ( !v19 )
              sub_180071F50(v28, v27, v29, v30);
            if ( sub_1800717F0("0..255", (v31 & 0x800000) != 0) )
              v31 = v31 & 0xFE7FFFFF | 0x800000;
            if ( sub_1800717F0("0.00..1.00", HIBYTE(v31) & 1) )
              v31 = v31 & 0xFE7FFFFF | 0x1000000;
          }
          if ( !v19 || !v18 )
            sub_180071F50(v28, v27, v29, v30);
          v250 = 3212836864LL;
          sub_18006FED0((__int64)"Copy as..", &v250);
          if ( v32 )
            sub_18004BE60("Copy");
          if ( *(_DWORD *)(qword_18010C470 + 8048) > *(_DWORD *)(qword_18010C470 + 8064) )
          {
            v33 = *(_QWORD *)(qword_18010C470 + 5216);
            v34 = "opy";
            v35 = 67;
            v36 = ~*(_DWORD *)(*(_QWORD *)(v33 + 272) + 4LL * *(int *)(v33 + 264) - 4);
            do
            {
              if ( v35 == 35 && *v34 == 35 && v34[1] == 35 )
                v36 = ~*(_DWORD *)(*(_QWORD *)(v33 + 272) + 4LL * *(int *)(v33 + 264) - 4);
              v37 = v35 ^ (unsigned __int64)(unsigned __int8)v36;
              v35 = *v34++;
              v36 = dword_1800D56B0[v37] ^ (v36 >> 8);
            }
            while ( v35 );
            v38 = ~v36;
            if ( *(_DWORD *)(*(_QWORD *)v33 + 5304LL) == v38 )
              sub_180053310(v38, 11, "Copy");
            if ( sub_18004C6E0(v38) )
            {
              v39 = *(float *)v5;
              if ( *(float *)v5 >= 0.0 )
                v40 = fminf(1.0, v39);
              else
                v40 = 0.0;
              v41 = *(float *)(v5 + 4);
              v42 = (int)(float)((float)(v40 * 255.0) + 0.5);
              if ( v41 >= 0.0 )
                v43 = fminf(1.0, v41);
              else
                v43 = 0.0;
              v44 = *(float *)(a2 + 8);
              v45 = (int)(float)((float)(v43 * 255.0) + 0.5);
              if ( v44 >= 0.0 )
                v46 = fminf(1.0, v44);
              else
                v46 = 0.0;
              v47 = (int)(float)((float)(v46 * 255.0) + 0.5);
              if ( (a3 & 2) != 0 )
              {
                v48 = 255;
                v49 = 1.0;
              }
              else
              {
                v49 = *(float *)(a2 + 12);
                if ( v49 >= 0.0 )
                  v50 = fminf(1.0, v49);
                else
                  v50 = 0.0;
                v48 = (int)(float)((float)(v50 * 255.0) + 0.5);
              }
              sub_180035ED0(v245, 64, "(%.3ff, %.3ff, %.3ff, %.3ff)", v39, v41, v44, v49);
              v250 = 0;
              if ( (unsigned __int8)sub_180084D20(v245, 0, 0, &v250) )
              {
                v51 = *(void (__fastcall **)(__int64, float *))(qword_18010C470 + 3048);
                if ( v51 )
                  v51(qword_18010C470, v245);
              }
              sub_180035ED0(v245, 64, "(%d,%d,%d,%d)", v42, v45, v47, v48);
              v250 = 0;
              if ( (unsigned __int8)sub_180084D20(v245, 0, 0, &v250) )
              {
                v52 = *(void (__fastcall **)(__int64, float *))(qword_18010C470 + 3048);
                if ( v52 )
                  v52(qword_18010C470, v245);
              }
              sub_180035ED0(v245, 64, "#%02X%02X%02X", v42, v45, v47);
              v250 = 0;
              if ( (unsigned __int8)sub_180084D20(v245, 0, 0, &v250) )
              {
                v53 = *(void (__fastcall **)(__int64, float *))(qword_18010C470 + 3048);
                if ( v53 )
                  v53(qword_18010C470, v245);
              }
              if ( (a3 & 2) == 0 )
              {
                sub_180035ED0(v245, 64, "#%02X%02X%02X%02X", v42, v45, v47, v48);
                v250 = 0;
                if ( (unsigned __int8)sub_180084D20(v245, 0, 0, &v250) )
                {
                  v54 = *(void (__fastcall **)(__int64, float *))(qword_18010C470 + 3048);
                  if ( v54 )
                    v54(qword_18010C470, v245);
                }
              }
              sub_18004C770();
              v3 = (__m128 *)v243;
              v5 = a2;
            }
          }
          else
          {
            *(_DWORD *)(qword_18010C470 + 7824) = 0;
          }
          v55 = qword_18010C470;
          *(_DWORD *)(v237 + 9560) = v31;
          v56 = *(_DWORD *)(v55 + 8016);
          if ( v56 > 1 )
          {
            *(_DWORD *)(v55 + 8016) = v56 - 1;
            *(_DWORD *)(v55 + 7680) = *(_DWORD *)(*(_QWORD *)(v55 + 8024) + 4LL * (v56 - 2));
          }
          else
          {
            sub_180049A30("Calling PopItemFlag() too many times!");
          }
          sub_18004C770();
          v16 = 255;
        }
      }
      else
      {
        *(_DWORD *)(qword_18010C470 + 7824) = 0;
      }
    }
    v7 = v232;
  }
  if ( (a3 & 0x700000) == 0 )
    a3 |= v3[597].m128_i32[2] & 0x700000;
  v57 = v3[597].m128_i32[2];
  if ( (a3 & 0x1800000) == 0 )
    a3 |= v57 & 0x1800000;
  if ( (a3 & 0x6000000) == 0 )
    a3 |= v57 & 0x6000000;
  if ( (a3 & 0x18000000) == 0 )
    a3 |= v57 & 0x18000000;
  v58 = v57 & 0xE00FFFFF;
  v59 = v58 | a3;
  v249 = v59;
  v60 = v59 & 2;
  v235 = v60;
  v61 = 4 - (v60 != 0);
  v227 = v61;
  LODWORD(v237) = v59 & 0x10;
  if ( (v59 & 0x10) != 0 )
    v62 = 0.0;
  else
    v62 = v10 + v3[202].m128_f32[1];
  v63 = *(float *)v5;
  v64 = *(float *)(v5 + 8);
  v224.m128_i32[0] = *(_DWORD *)v5;
  *(float *)&v225 = fmaxf(v12 - v62, 1.0);
  v65 = *(float *)(v5 + 4);
  *(unsigned __int64 *)((char *)v224.m128_u64 + 4) = __PAIR64__(LODWORD(v64), LODWORD(v65));
  if ( (v59 & 2) != 0 )
    v224.m128_i32[3] = 1065353216;
  else
    v224.m128_i32[3] = *(_DWORD *)(v5 + 12);
  v239 = v59 & 0x10000000;
  if ( (v59 & 0x10000000) != 0 && (v59 & 0x100000) != 0 )
  {
    sub_180036790(v58, v13, v14, (unsigned int)&v224, (__int64)v224.m128_i64 + 4, (__int64)&v224.m128_i64[1]);
    goto LABEL_108;
  }
  if ( (v59 & 0x8200000) == 0x8200000 )
  {
    sub_1800366E0(v58, v13, v14, (unsigned int)&v224, (__int64)v224.m128_i64 + 4, (__int64)&v224.m128_i64[1]);
    if ( *(_DWORD *)(qword_18010C470 + 9568) == *(_DWORD *)(qword_18010C470 + 9564) )
    {
      v228.m128_u64[0] = __PAIR64__(LODWORD(v65), LODWORD(v63));
      v228.m128_u64[1] = LODWORD(v64);
      sub_180036620(&v228);
      if ( *((_DWORD *)v67 + 2395) == v68 )
      {
        v65 = v224.m128_f32[1];
        if ( v224.m128_f32[1] == 0.0 || (v63 = v224.m128_f32[0], v224.m128_f32[0] == 0.0) && v67[2393] == 1.0 )
        {
          v63 = v67[2393];
          v224.m128_f32[0] = v63;
        }
        v64 = v224.m128_f32[2];
        if ( v224.m128_f32[2] == 0.0 )
        {
          v65 = v67[2394];
          v224.m128_f32[1] = v65;
        }
        goto LABEL_109;
      }
    }
LABEL_108:
    v63 = v224.m128_f32[0];
    v65 = v224.m128_f32[1];
    v64 = v224.m128_f32[2];
LABEL_109:
    v61 = v227;
  }
  if ( v63 < 0.0 )
    v66 = -0.5;
  else
    v66 = 0.5;
  v231.m128i_i32[0] = (int)(float)((float)(v63 * 255.0) + v66);
  if ( v65 < 0.0 )
    v69 = -0.5;
  else
    v69 = 0.5;
  v231.m128i_i32[1] = (int)(float)((float)(v65 * 255.0) + v69);
  if ( v64 < 0.0 )
    v70 = -0.5;
  else
    v70 = 0.5;
  v231.m128i_i32[2] = (int)(float)((float)(v64 * 255.0) + v70);
  if ( v224.m128_f32[3] < 0.0 )
    v17 = -0.5;
  v71 = 0;
  v72 = 0;
  v73 = v3[209].m128_i32[2] == 0;
  LOBYTE(v250) = 0;
  v231.m128i_i32[3] = (int)(float)((float)(v224.m128_f32[3] * 255.0) + v17);
  v74 = *(float *)(v7 + 280);
  v75 = *(_DWORD *)(v7 + 284);
  if ( v73 )
    v76 = v62;
  else
    v76 = 0.0;
  *(float *)(v7 + 280) = v74 + v76;
  v77 = v59 & 0x20;
  LODWORD(v238) = v77;
  if ( (v59 & 0x300000) == 0 || (v59 & 0x20) != 0 )
  {
    if ( (v59 & 0x400000) == 0 || (v59 & 0x20) != 0 )
    {
LABEL_153:
      v78 = *(float *)&v225;
      goto LABEL_154;
    }
    if ( (v59 & 2) != 0 )
    {
      v106 = v231.m128i_i32[2];
      if ( v231.m128i_i32[2] >= 0 )
      {
        if ( v231.m128i_i32[2] > 255 )
          v106 = 255;
      }
      else
      {
        v106 = 0;
      }
      v107 = v231.m128i_i32[1];
      if ( v231.m128i_i32[1] >= 0 )
      {
        if ( v231.m128i_i32[1] > 255 )
          v107 = 255;
      }
      else
      {
        v107 = 0;
      }
      v108 = v231.m128i_i32[0];
      if ( v231.m128i_i32[0] >= 0 )
      {
        if ( v231.m128i_i32[0] > 255 )
          v108 = 255;
      }
      else
      {
        v108 = 0;
      }
      sub_180035ED0(v246, 64, "#%02X%02X%02X", v108, v107, v106);
    }
    else
    {
      v102 = v231.m128i_i32[3];
      if ( v231.m128i_i32[3] >= 0 )
      {
        if ( v231.m128i_i32[3] > 255 )
          v102 = 255;
      }
      else
      {
        v102 = 0;
      }
      v103 = v231.m128i_i32[2];
      if ( v231.m128i_i32[2] >= 0 )
      {
        if ( v231.m128i_i32[2] > 255 )
          v103 = 255;
      }
      else
      {
        v103 = 0;
      }
      v104 = v231.m128i_i32[1];
      if ( v231.m128i_i32[1] >= 0 )
      {
        if ( v231.m128i_i32[1] > 255 )
          v104 = 255;
      }
      else
      {
        v104 = 0;
      }
      v105 = v231.m128i_i32[0];
      if ( v231.m128i_i32[0] >= 0 )
      {
        if ( v231.m128i_i32[0] > 255 )
          v105 = 255;
      }
      else
      {
        v105 = 0;
      }
      sub_180035ED0(v246, 64, "#%02X%02X%02X%02X", v105, v104, v103, v102);
    }
    v109 = qword_18010C470;
    v78 = *(float *)&v225;
    v236 = 0;
    *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
    *(float *)(v109 + 7712) = v78;
    if ( sub_180079E10("##Text", nullptr, v246, 64, &v236, 8, 0, 0) )
    {
      v71 = 1;
      v110 = v246;
      LOBYTE(v250) = 1;
      v111 = 0x900000200LL;
      while ( 1 )
      {
        v112 = *v110;
        if ( (unsigned __int8)v112 > 0x23u || !_bittest64(&v111, v112) )
          break;
        ++v110;
      }
      v231.m128i_i32[3] = 255;
      *(__int64 *)((char *)v231.m128i_i64 + 4) = 0;
      v231.m128i_i32[0] = 0;
      if ( (v59 & 2) != 0 )
        sub_180034BF0(
          v110,
          "%02X%02X%02X",
          (unsigned int)&v231,
          (unsigned int)&v231.m128i_u32[1],
          (unsigned int)&v231.m128i_u32[2]);
      else
        sub_180034BF0(
          v110,
          "%02X%02X%02X%02X",
          (unsigned int)&v231,
          (unsigned int)&v231.m128i_u32[1],
          (unsigned int)&v231.m128i_u32[2],
          (unsigned int)&v231.m128i_u32[3]);
    }
    if ( (v59 & 8) == 0 )
      sub_18004C810();
  }
  else
  {
    v78 = *(float *)&v225;
    v79 = "M:000";
    v80 = (float)v61;
    if ( (v59 & 0x1000000) != 0 )
      v79 = "M:0.000";
    v81 = *(float *)&v225 - (float)((float)(3 - (v60 != 0)) * v3[202].m128_f32[1]);
    sub_18003DF30((unsigned int)&v229, (_DWORD)v79, 0, 0, -1082130432);
    if ( *v83 < (float)(int)(float)(v81 / v80) )
      v84 = ((v59 & 0x200000) != 0) + 1LL;
    else
      v84 = 0;
    LODWORD(v13) = 0;
    v85 = v59 & 0x80000;
    v86 = 0.0;
    if ( (v59 & 0x80000) != 0 )
      v16 = 0;
    v87 = 4 * v84;
    v88 = v59 & 8;
    LODWORD(v250) = v16;
    if ( (v59 & 0x1000000) != 0 )
    {
      v89 = &off_1800DAC30[v87];
      v90 = 0;
      do
      {
        if ( (_DWORD)v13 )
          ((void (*)(void))sub_18004AC40)();
        v91 = v13 + 1;
        v92 = qword_18010C470;
        *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
        v93 = (float)(int)(float)((float)((float)(v13 + 1) * v81) / v80) - v86;
        v86 = (float)(int)(float)((float)((float)(v13 + 1) * v81) / v80);
        *(float *)(v92 + 7712) = fmaxf(v93, 1.0);
        if ( v85 )
          v94 = 0;
        else
          v94 = 1065353216;
        v222 = (__int64)v89[(unsigned int)v13];
        LODWORD(v250) = v94;
        LODWORD(v236) = 0;
        v71 |= sub_180073AF0(
                 (unsigned int)off_1800DABB0[(unsigned int)v13],
                 8,
                 (unsigned int)&v224.m128_u32[v13],
                 v82,
                 (__int64)&v236,
                 (__int64)&v250,
                 v222,
                 v223);
        v90 |= v71;
        if ( !v88 )
          sub_18004C810();
        v13 = (unsigned int)v91;
      }
      while ( v91 < v227 );
      v77 = v238;
      v226 = v90;
      v72 = v90;
      v59 = v249;
      LOBYTE(v250) = v71;
      goto LABEL_153;
    }
    v97 = v250;
    v98 = &off_1800DABD0[v87];
    do
    {
      if ( (int)v13 > 0 )
        ((void (*)(void))sub_18004AC40)();
      v99 = v13 + 1;
      LODWORD(v250) = v97;
      LODWORD(v236) = 0;
      v100 = qword_18010C470;
      *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
      v101 = (float)(int)(float)((float)((float)(v13 + 1) * v81) / v80) - v86;
      v86 = (float)(int)(float)((float)((float)(v13 + 1) * v81) / v80);
      *(float *)(v100 + 7712) = fmaxf(v101, 1.0);
      v71 |= sub_180073AF0(
               (unsigned int)off_1800DABB0[(int)v13],
               4,
               (unsigned int)&v231 + 4 * v13,
               v82,
               (__int64)&v236,
               (__int64)&v250,
               (__int64)v98[(int)v13],
               v223);
      if ( !v88 )
        sub_18004C810();
      v13 = (unsigned int)v99;
    }
    while ( v99 < v227 );
    v59 = v249;
    v72 = 0;
    v77 = v238;
    LOBYTE(v250) = v71;
  }
LABEL_154:
  v95 = 0;
  v238 = 0;
  v225 = 1;
  if ( (_DWORD)v237 )
  {
LABEL_218:
    v118 = v230;
    goto LABEL_219;
  }
  if ( v77 || !v3[209].m128_i32[2] )
    v96 = 0.0;
  else
    v96 = v78 + v3[202].m128_f32[1];
  v113 = v232;
  *(_DWORD *)(v232 + 284) = v75;
  *(float *)(v113 + 280) = v96 + v74;
  if ( !v235 )
    v15 = *(_DWORD *)(a2 + 12);
  v114 = *(_DWORD *)(a2 + 4);
  v228.m128_i32[0] = *(_DWORD *)a2;
  v228.m128_i32[2] = *(_DWORD *)(a2 + 8);
  v228.m128_i32[1] = v114;
  v228.m128_i32[3] = v15;
  v237 = 0;
  if ( (unsigned __int8)sub_180083B30("##ColorButton", &v228, v59, &v237) && (v59 & 4) == 0 )
  {
    v3[599] = v228;
    sub_18004BE60("picker");
    v115 = v3[484].m128_f32[3] + 0.0;
    v116 = qword_18010C470;
    v117 = v3[485].m128_f32[2] + v3[202].m128_f32[0];
    *(_DWORD *)(qword_18010C470 + 7824) |= 1u;
    *(float *)(v116 + 7840) = v115;
    *(_QWORD *)(v116 + 7848) = 0;
    *(float *)(v116 + 7844) = v117;
    *(_DWORD *)(v116 + 7828) = 1;
  }
  if ( (v59 & 8) == 0 )
    sub_18004C810();
  v58 = qword_18010C470;
  if ( *(_DWORD *)(qword_18010C470 + 8048) <= *(_DWORD *)(qword_18010C470 + 8064) )
  {
    *(_DWORD *)(qword_18010C470 + 7824) = 0;
    goto LABEL_218;
  }
  v126 = *(_QWORD *)(qword_18010C470 + 5216);
  v127 = "icker";
  v128 = 112;
  v129 = ~*(_DWORD *)(*(_QWORD *)(v126 + 272) + 4LL * *(int *)(v126 + 264) - 4);
  do
  {
    if ( v128 == 35 && *v127 == 35 && v127[1] == 35 )
      v129 = ~*(_DWORD *)(*(_QWORD *)(v126 + 272) + 4LL * *(int *)(v126 + 264) - 4);
    v130 = v128 ^ (unsigned __int64)(unsigned __int8)v129;
    v128 = *v127++;
    v129 = dword_1800D56B0[v130] ^ (v129 >> 8);
  }
  while ( v128 );
  v131 = ~v129;
  v71 = v250;
  if ( *(_DWORD *)(*(_QWORD *)v126 + 5304LL) == v131 )
    sub_180053310(v131, 11, "picker", v127);
  if ( !sub_18004C6E0(v131) )
    goto LABEL_218;
  v118 = v230;
  if ( *(_WORD *)(v3[326].m128_u64[0] + 218) == 1 )
  {
    v95 = v3[326].m128_u64[0];
    v238 = v95;
    if ( v247 != v230 )
    {
      sub_18006EB90(v247, v230, 0);
      sub_180071E90();
    }
    v132 = qword_18010C470;
    v133 = v240 * 12.0;
    v134 = v241 & 0x1F890002;
    *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
    *(float *)(v132 + 7712) = v133;
    v71 |= sub_180080710("##picker", a2, v134 | 0x702080u, &v3[599]);
    LOBYTE(v250) = v71;
  }
  sub_18004C770();
LABEL_219:
  if ( v247 != v118 && (v59 & 0x80u) == 0 )
  {
    sub_18004AC40(v58, v13);
    if ( !v77 )
      v62 = (float)(v78 + v62) + v3[202].m128_f32[1];
    *(float *)(v232 + 280) = v62 + v74;
    sub_18006EB90(v119, v118, 0);
  }
  if ( v71 && !v95 )
  {
    if ( !v72 )
      v224 = _mm_div_ps(_mm_cvtepi32_ps(_mm_loadu_si128(&v231)), (__m128)xmmword_1800E6B40);
    if ( (v59 & 0x8200000) == 0x8200000 )
    {
      v120 = v224.m128_i32[1];
      v3[598].m128_i32[1] = v224.m128_i32[0];
      v3[598].m128_i32[2] = v120;
      sub_180036790(v58, v13, v14, (unsigned int)&v224, (__int64)v224.m128_i64 + 4, (__int64)&v224.m128_i64[1]);
      v121 = v3[597].m128_i32[3];
      v122 = v224.m128_i32[0];
      v123 = v224.m128_i32[1];
      v124 = v224.m128_i32[2];
      v232 = v224.m128_u64[0];
      v233 = v224.m128_i32[2];
      v3[598].m128_i32[0] = v121;
      v234 = 0;
      sub_180036620(&v232);
      v3[598].m128_i32[3] = v125;
    }
    else
    {
      v124 = v224.m128_i32[2];
      v123 = v224.m128_i32[1];
      v122 = v224.m128_i32[0];
    }
    if ( (v59 & 0x100000) != 0 && v239 )
    {
      sub_1800366E0(v58, v13, v14, (unsigned int)&v224, (__int64)v224.m128_i64 + 4, (__int64)&v224.m128_i64[1]);
      v124 = v224.m128_i32[2];
      v123 = v224.m128_i32[1];
      v122 = v224.m128_i32[0];
    }
    v73 = v235 == 0;
    *(_DWORD *)a2 = v122;
    *(_DWORD *)(a2 + 4) = v123;
    *(_DWORD *)(a2 + 8) = v124;
    if ( v73 )
      *(_DWORD *)(a2 + 12) = v224.m128_i32[3];
  }
  if ( !v242 )
    v3[597].m128_i32[3] = 0;
  v135 = *(_QWORD *)(qword_18010C470 + 5216);
  v136 = *(_DWORD *)(v135 + 264);
  if ( v136 > 1 )
    *(_DWORD *)(v135 + 264) = v136 - 1;
  else
    sub_180049A30("Calling PopID() too many times!");
  sub_18004B190();
  if ( (v3[484].m128_i8[8] & 1) != 0 && !(v59 & 0x200 | v3[484].m128_i32[1] & 0x800) )
  {
    v137 = qword_18010C470;
    if ( *(_BYTE *)(qword_18010C470 + 8656) )
    {
      v138 = *(_DWORD *)(qword_18010C470 + 7752);
      if ( (v138 & 1) != 0 )
      {
        v139 = *(_QWORD *)(qword_18010C470 + 5232);
        if ( v139 )
        {
          v140 = *(_QWORD *)(qword_18010C470 + 5216);
          if ( *(_QWORD *)(v140 + 960) == *(_QWORD *)(v139 + 960) && !*(_BYTE *)(v140 + 209) )
          {
            v141 = *(_DWORD *)(qword_18010C470 + 7744);
            v142 = 7788;
            if ( (v138 & 2) == 0 )
              v142 = 7756;
            if ( !v141 )
            {
              v143 = *(float *)(v140 + 296);
              v144 = *(float *)(v140 + 300);
              v145 = *(int *)(v140 + 264);
              v146 = 7792;
              if ( (v138 & 2) == 0 )
                v146 = 7760;
              v244[0] = *(float *)(qword_18010C470 + v142) - v143;
              v147 = *(float *)(qword_18010C470 + v146);
              v148 = 7796;
              if ( (v138 & 2) == 0 )
                v148 = 7764;
              v244[1] = v147 - v144;
              v149 = *(float *)(qword_18010C470 + v148);
              v150 = 7800;
              v151 = v149 - v143;
              if ( (v138 & 2) == 0 )
                v150 = 7768;
              v152 = v244;
              v244[2] = v151;
              v153 = *(_DWORD *)(*(_QWORD *)(v140 + 272) + 4 * v145 - 4);
              v244[3] = *(float *)(qword_18010C470 + v150) - v144;
              v154 = ~v153;
              do
              {
                v155 = *(unsigned __int8 *)v152;
                v152 = (float *)((char *)v152 + 1);
                v154 = dword_1800D56B0[v155 ^ (unsigned __int8)v154] ^ (v154 >> 8);
              }
              while ( v152 < v245 );
              v156 = qword_18010C470;
              v141 = ~v154;
              v71 = v250;
              if ( *(_DWORD *)(qword_18010C470 + 5332) == v141 )
                *(_DWORD *)(qword_18010C470 + 5336) = v141;
              if ( *(_DWORD *)(v156 + 5384) == v141 )
                *(_BYTE *)(v156 + 5393) = 1;
            }
            if ( *(_DWORD *)(v137 + 8684) != v141 )
            {
              v157 = qword_18010C470;
              m128_f32 = (float *)(v140 + 608);
              v159 = (__int128 *)(v137 + 7804);
              if ( (v138 & 0x200) == 0 )
                v159 = (__int128 *)(v140 + 608);
              v160 = 0;
              *(_OWORD *)(v137 + 8736) = *(_OWORD *)(v137 + v142);
              v161 = *v159;
              *(_DWORD *)(v137 + 8768) = v141;
              *(_BYTE *)(v137 + 8658) = 1;
              *(_OWORD *)(v137 + 8752) = v161;
              if ( *(_DWORD *)(v157 + 8692) != -1 )
              {
                v162 = 0;
                v142 = (__int64)"_COL3F";
                do
                {
                  v163 = aCol3f[v162++];
                  if ( v163 != *(_BYTE *)(v157 + v162 + 8695) )
                    goto LABEL_308;
                }
                while ( v162 != 7 );
                v164 = *(float *)(v137 + 8744);
                v165 = *(float *)(v137 + 8748);
                v166 = *(float *)(v137 + 8736);
                v167 = *(float *)(v137 + 8740);
                v168 = (float)(v165 - v167) * (float)(v164 - v166);
                if ( v168 > *(float *)(v157 + 8780) )
                  goto LABEL_308;
                v169 = *(_DWORD *)(v157 + 8788);
                *(float *)(v157 + 8780) = v168;
                *(_DWORD *)(v157 + 8776) = 0;
                *(_DWORD *)(v157 + 8784) = v141;
                *(_BYTE *)(v157 + 8729) = v169 == v141;
                if ( v169 != v141 || (v170 = (_BYTE *)(v157 + 8660), (*(_DWORD *)(v157 + 8660) & 0x800) != 0) )
                {
                  v170 = (_BYTE *)(v157 + 8660);
                }
                else if ( *(_DWORD *)(v157 + 8772) )
                {
                  v229 = *(__m128 *)(v137 + 8736);
                  v171 = **(_QWORD **)(qword_18010C470 + 8104);
                  v229.m128_f32[0] = v229.m128_f32[0] + 3.5;
                  v229.m128_f32[2] = v229.m128_f32[2] + -3.5;
                  v229.m128_f32[1] = v229.m128_f32[1] + 3.5;
                  v229.m128_f32[3] = v229.m128_f32[3] + -3.5;
                  sub_18003AA50(v171);
                  v228 = *(__m128 *)(qword_18010C470 + 4272);
                  v228.m128_f32[3] = _mm_shuffle_ps(v228, v228, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
                  sub_180036620(&v228);
                  sub_18005C460(v173, (unsigned int)&v229, (unsigned int)&v229.m128_u32[2], v172, 0);
                }
                else
                {
                  *(float *)&v174 = fmaxf(v166, *(float *)(v137 + 8752)) - 3.5;
                  v175 = fmaxf(v167, *(float *)(v157 + 8756)) - 3.5;
                  v176 = fminf(v164, *(float *)(v157 + 8760)) + 3.5;
                  v177 = fminf(v165, *(float *)(v157 + 8764)) + 3.5;
                  v178 = *(float *)&v174 < *m128_f32;
                  v228.m128_u64[0] = __PAIR64__(LODWORD(v175), v174);
                  v228.m128_u64[1] = __PAIR64__(LODWORD(v177), LODWORD(v176));
                  if ( v178
                    || v175 < *(float *)(v140 + 612)
                    || *(float *)(v140 + 616) < v176
                    || *(float *)(v140 + 620) < v177 )
                  {
                    v179 = *(_QWORD *)(v140 + 712);
                    v160 = 1;
                    v180 = *(_DWORD **)(v179 + 56);
                    v181 = v180[17];
                    LODWORD(v232) = v180[16];
                    v182 = v180[14];
                    HIDWORD(v232) = v181;
                    v230 = (_BYTE *)__PAIR64__(v180[15], v182);
                    sub_18005A5E0(v179, &v230, &v232, 0);
                  }
                  v229 = *(__m128 *)(qword_18010C470 + 4272);
                  v229.m128_f32[3] = _mm_shuffle_ps(v229, v229, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
                  sub_180036620(&v229);
                  sub_18005C460(*(_QWORD *)(v140 + 712), (unsigned int)&v228, (unsigned int)&v228.m128_u32[2], v183, 0);
                  if ( v160 )
                    sub_18005A7D0(*(_QWORD *)(v140 + 712));
                  v160 = 0;
                }
                v73 = (*v170 & 0x10) == 0;
                v184 = *(_DWORD *)(v157 + 5032);
                *(_DWORD *)(v157 + 8792) = v184;
                if ( v73 || *(_DWORD *)(v157 + 8668) != -1 )
                {
                  if ( v169 != v141 || (unsigned __int8)sub_180046F40(*(unsigned int *)(v157 + 8668)) )
                    goto LABEL_302;
                }
                else if ( v169 != v141 || *(_DWORD *)(v157 + 8664) >= v184 )
                {
LABEL_302:
                  v185 = 0;
                  v186 = 0;
                  goto LABEL_303;
                }
                v185 = 1;
                v186 = 1;
LABEL_303:
                *(_BYTE *)(v157 + 8730) = v186;
                if ( v185 )
                {
                  if ( (*(_BYTE *)(v157 + 10228) & 2) != 0 )
                    sub_180052F00(
                      "[dragdrop] AcceptDragDropPayload(): 0x%08X: payload delivery\n",
                      *(_DWORD *)(v137 + 8768));
                  if ( v157 != -8672 )
                  {
                    v187 = *(_QWORD *)(v157 + 8672);
                    v160 = 1;
                    LOBYTE(v250) = 1;
                    *(_QWORD *)a2 = *(_QWORD *)v187;
                    *(_DWORD *)(a2 + 8) = *(_DWORD *)(v187 + 8);
                  }
                }
              }
LABEL_308:
              v188 = (__m128 *)qword_18010C470;
              if ( *(_DWORD *)(qword_18010C470 + 8692) != -1 )
              {
                v189 = 0;
                m128_f32 = (float *)"_COL4F";
                do
                {
                  v190 = aCol4f[v189++];
                  if ( v190 != *(_BYTE *)(qword_18010C470 + v189 + 8695) )
                    goto LABEL_345;
                }
                while ( v189 != 7 );
                v191 = *(float *)(qword_18010C470 + 8744);
                v192 = *(float *)(qword_18010C470 + 8748);
                v193 = *(float *)(qword_18010C470 + 8736);
                v194 = *(float *)(qword_18010C470 + 8740);
                v195 = (float)(v192 - v194) * (float)(v191 - v193);
                if ( v195 > *(float *)(qword_18010C470 + 8780) )
                  goto LABEL_345;
                v196 = *(_DWORD *)(qword_18010C470 + 8768);
                v197 = *(_DWORD *)(qword_18010C470 + 8788);
                *(float *)(qword_18010C470 + 8780) = v195;
                v188[548].m128_i32[2] = 0;
                v188[549].m128_i32[0] = v196;
                v188[545].m128_i8[9] = v197 == v196;
                if ( v197 != v196 || (v198 = &v188[541].m128_i8[4], (v188[541].m128_i32[1] & 0x800) != 0) )
                {
                  v198 = &v188[541].m128_i8[4];
                }
                else if ( v188[548].m128_i32[1] )
                {
                  v229 = v188[546];
                  v199 = **(_QWORD **)(qword_18010C470 + 8104);
                  v229.m128_f32[0] = v229.m128_f32[0] + 3.5;
                  v229.m128_f32[2] = v229.m128_f32[2] + -3.5;
                  v229.m128_f32[1] = v229.m128_f32[1] + 3.5;
                  v229.m128_f32[3] = v229.m128_f32[3] + -3.5;
                  sub_18003AA50(v199);
                  v228 = *(__m128 *)(qword_18010C470 + 4272);
                  v228.m128_f32[3] = _mm_shuffle_ps(v228, v228, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
                  sub_180036620(&v228);
                  sub_18005C460(v201, (unsigned int)&v229, (unsigned int)&v229.m128_u32[2], v200, 0);
                }
                else
                {
                  v202 = v188[326].m128_u64[0];
                  *(float *)&v203 = fmaxf(v193, v188[547].m128_f32[0]) - 3.5;
                  v204 = fmaxf(v194, v188[547].m128_f32[1]) - 3.5;
                  v205 = fminf(v191, v188[547].m128_f32[2]) + 3.5;
                  v206 = fminf(v192, v188[547].m128_f32[3]) + 3.5;
                  v178 = *(float *)&v203 < *(float *)(v202 + 608);
                  v228.m128_u64[0] = __PAIR64__(LODWORD(v204), v203);
                  v228.m128_u64[1] = __PAIR64__(LODWORD(v206), LODWORD(v205));
                  if ( v178
                    || v204 < *(float *)(v202 + 612)
                    || *(float *)(v202 + 616) < v205
                    || *(float *)(v202 + 620) < v206 )
                  {
                    v208 = *(_QWORD *)(v202 + 712);
                    v207 = 1;
                    v209 = *(_DWORD **)(v208 + 56);
                    v210 = v209[17];
                    LODWORD(v232) = v209[16];
                    v211 = v209[14];
                    HIDWORD(v232) = v210;
                    v230 = (_BYTE *)__PAIR64__(v209[15], v211);
                    sub_18005A5E0(v208, &v230, &v232, 0);
                  }
                  else
                  {
                    v207 = 0;
                  }
                  v229 = *(__m128 *)(qword_18010C470 + 4272);
                  v229.m128_f32[3] = _mm_shuffle_ps(v229, v229, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
                  sub_180036620(&v229);
                  sub_18005C460(*(_QWORD *)(v202 + 712), (unsigned int)&v228, (unsigned int)&v228.m128_u32[2], v212, 0);
                  if ( v207 )
                    sub_18005A7D0(*(_QWORD *)(v202 + 712));
                }
                v73 = (*v198 & 0x10) == 0;
                v213 = v188[314].m128_i32[2];
                v188[549].m128_i32[2] = v213;
                if ( v73 || v188[541].m128_i32[3] != -1 )
                {
                  if ( v197 == v196 && !(unsigned __int8)sub_180046F40(v188[541].m128_u32[3]) )
                  {
                    v225 = 1;
                    v214 = 1;
                    goto LABEL_338;
                  }
                }
                else if ( v197 == v196 && v188[541].m128_i32[2] < v213 )
                {
                  v214 = 1;
LABEL_338:
                  v73 = (_BYTE)v225 == 0;
                  v188[545].m128_i8[10] = v214;
                  if ( !v73 )
                  {
                    if ( (v188[639].m128_i8[4] & 2) != 0 )
                      sub_180052F00(
                        "[dragdrop] AcceptDragDropPayload(): 0x%08X: payload delivery\n",
                        v188[548].m128_i32[0]);
                    m128_f32 = v188[542].m128_f32;
                    if ( v188 != (__m128 *)-8672LL )
                    {
                      v215 = a2;
                      v216 = 12;
                      v217 = *(_QWORD *)m128_f32;
                      if ( !v235 )
                        v216 = 16;
                      sub_1800B8BD0(a2, v217, v216);
                      v71 = 1;
                      goto LABEL_347;
                    }
                  }
                  goto LABEL_345;
                }
                v214 = 0;
                *(float *)&v225 = 0.0;
                goto LABEL_338;
              }
LABEL_345:
              v71 = v250;
              if ( v160 )
              {
                v215 = a2;
LABEL_347:
                if ( v239 )
                  sub_1800366E0(v215 + 8, (_DWORD)m128_f32, v142, v215, v215 + 4, v215 + 8);
              }
              v73 = *(_BYTE *)(qword_18010C470 + 8730) == 0;
              *(_BYTE *)(qword_18010C470 + 8658) = 0;
              if ( !v73 )
                sub_1800516C0();
              v3 = (__m128 *)v243;
            }
          }
        }
      }
    }
  }
  if ( v238 )
  {
    v218 = v3[333].m128_i32[1];
    if ( v218 )
    {
      if ( v3[335].m128_u64[1] == v238 )
        v3[484].m128_i32[0] = v218;
    }
  }
  if ( v71 )
  {
    v219 = v3[484].m128_i32[0];
    if ( v219 )
    {
      v220 = qword_18010C470;
      if ( (*(_DWORD *)(qword_18010C470 + 7748) & 0x10000) == 0 )
      {
        v221 = *(_DWORD *)(qword_18010C470 + 5332);
        if ( v221 == v219 || !v221 )
        {
          *(_WORD *)(qword_18010C470 + 5348) = 257;
          if ( *(_DWORD *)(v220 + 5384) == v219 )
            *(_BYTE *)(v220 + 5392) = 1;
        }
        *(_DWORD *)(v220 + 7752) |= 4u;
      }
    }
  }
  return v71;
}
