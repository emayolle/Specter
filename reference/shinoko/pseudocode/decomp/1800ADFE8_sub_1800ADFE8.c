// sub_1800ADFE8 size=4735
__int64 __fastcall sub_1800ADFE8(__int64 a1, int a2, int a3, __int64 a4, __int64 a5, __int64 a6)
{
  unsigned int v9; // r15d
  int v10; // eax
  const char *v11; // r8
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  unsigned int v16; // r12d
  double v17; // xmm0_8
  unsigned __int64 v18; // rdi
  unsigned int v19; // edx
  __int64 v20; // r8
  unsigned int v21; // r11d
  unsigned int v22; // r8d
  bool v23; // zf
  int v24; // ecx
  int v25; // ecx
  unsigned int v26; // r14d
  __int64 v27; // r9
  __int64 v28; // rax
  __int64 v29; // rcx
  int v30; // r10d
  int v31; // edx
  __int64 v32; // rcx
  rsize_t v33; // r9
  unsigned int v34; // r11d
  unsigned int v35; // r8d
  int v36; // ecx
  int v37; // ecx
  __int64 v38; // r10
  __int64 v39; // rax
  __int64 v40; // rcx
  int v41; // r9d
  int v42; // edx
  __int64 v43; // rcx
  __int64 v44; // r8
  int v45; // eax
  int v46; // eax
  unsigned int v47; // eax
  __int64 v48; // r10
  __int64 v49; // r8
  int v50; // r9d
  unsigned int v51; // ecx
  __int64 v52; // rdi
  int v53; // eax
  int v54; // eax
  unsigned int v55; // ecx
  unsigned __int64 v56; // r8
  unsigned int v57; // r12d
  unsigned int v58; // eax
  int v59; // ecx
  __int64 v60; // rax
  __int64 v61; // rcx
  __int64 v62; // rsi
  __int64 v63; // rdi
  __int64 v64; // rbx
  unsigned int v65; // r9d
  unsigned int v66; // eax
  __int64 v67; // r10
  __int64 v68; // r8
  int v69; // r9d
  unsigned int v70; // ecx
  __int64 v71; // r10
  __int64 v72; // r9
  unsigned __int64 v73; // rcx
  char v74; // al
  __int64 v75; // rbx
  __int64 v76; // rdx
  __int64 v77; // rcx
  __int64 v78; // r8
  __int64 v79; // r9
  unsigned __int64 v80; // rcx
  unsigned int v81; // ebx
  unsigned int *v82; // rcx
  unsigned int *v83; // rdx
  __int64 v84; // r10
  __int64 v85; // rsi
  unsigned __int64 v86; // r11
  __int64 v87; // rbx
  __int64 v88; // rax
  unsigned __int64 v89; // rdx
  __int64 v90; // rdx
  unsigned __int64 v91; // rcx
  __int64 v92; // rdx
  __int64 v93; // rcx
  __int64 v94; // r8
  unsigned int v95; // ecx
  unsigned int v96; // eax
  __int64 v97; // r9
  unsigned __int64 v98; // rcx
  unsigned int v99; // ecx
  unsigned int v100; // eax
  int v101; // ecx
  __int64 v102; // rax
  __int64 v103; // rcx
  __int64 v104; // rsi
  __int64 v105; // rdi
  __int64 v106; // rbx
  unsigned int v107; // r9d
  __int64 v108; // r10
  __int64 v109; // r9
  unsigned __int64 v110; // rcx
  char v111; // al
  __int64 v112; // rbx
  __int64 v113; // rdx
  __int64 v114; // rcx
  __int64 v115; // r8
  __int64 v116; // r9
  unsigned __int64 v117; // rcx
  unsigned int v118; // ebx
  unsigned int *p_Source; // rcx
  unsigned int *v120; // rdx
  __int64 v121; // r10
  __int64 v122; // rsi
  unsigned __int64 v123; // r11
  __int64 v124; // rbx
  __int64 v125; // rax
  unsigned __int64 v126; // rdx
  __int64 v127; // rdx
  unsigned __int64 v128; // rcx
  __int64 v129; // rdx
  __int64 v130; // rcx
  __int64 v131; // r8
  unsigned int v132; // ecx
  unsigned int v133; // eax
  __int64 v134; // r9
  unsigned __int64 v135; // rcx
  _BYTE *v136; // rsi
  _BYTE *v137; // rbx
  __int64 v138; // r9
  unsigned __int64 v139; // r8
  int v140; // eax
  int v141; // r10d
  unsigned __int64 v142; // r8
  __int64 v143; // r9
  unsigned __int64 v144; // r8
  unsigned int v145; // eax
  __int64 v146; // rdi
  _BYTE *v147; // rdi
  char v148; // si
  unsigned int v149; // r9d
  unsigned __int64 v150; // r8
  __int64 v151; // r10
  unsigned __int64 v152; // rcx
  unsigned int v153; // r8d
  unsigned int i; // r9d
  char v155; // cl
  __int64 v156; // rax
  unsigned int v158; // [rsp+38h] [rbp-D0h]
  unsigned int v159; // [rsp+38h] [rbp-D0h]
  unsigned int v160; // [rsp+3Ch] [rbp-CCh]
  unsigned int v161; // [rsp+40h] [rbp-C8h]
  unsigned int v162; // [rsp+44h] [rbp-C4h] BYREF
  unsigned int *v163; // [rsp+48h] [rbp-C0h]
  int v164; // [rsp+50h] [rbp-B8h]
  int v165; // [rsp+54h] [rbp-B4h] BYREF
  int v166; // [rsp+58h] [rbp-B0h] BYREF
  unsigned int v167; // [rsp+60h] [rbp-A8h] BYREF
  unsigned int v168; // [rsp+64h] [rbp-A4h]
  unsigned int *v169; // [rsp+68h] [rbp-A0h]
  fenv_t Env; // [rsp+70h] [rbp-98h] BYREF
  __int64 v171; // [rsp+78h] [rbp-90h]
  unsigned int *v172; // [rsp+80h] [rbp-88h]
  __int64 v173; // [rsp+88h] [rbp-80h]
  __int64 v174; // [rsp+90h] [rbp-78h]
  unsigned int v175; // [rsp+98h] [rbp-70h] BYREF
  _DWORD Destination[115]; // [rsp+9Ch] [rbp-6Ch] BYREF
  unsigned int v177; // [rsp+268h] [rbp+160h] BYREF
  _DWORD v178[115]; // [rsp+26Ch] [rbp+164h] BYREF
  unsigned int v179; // [rsp+438h] [rbp+330h]
  unsigned int Source; // [rsp+43Ch] [rbp+334h] BYREF
  int v181; // [rsp+440h] [rbp+338h]
  unsigned int v182; // [rsp+608h] [rbp+500h]
  _DWORD v183[115]; // [rsp+60Ch] [rbp+504h] BYREF

  v173 = a5;
  v174 = a4;
  v165 = a3;
  fegetenv(&Env);
  v9 = 1;
  if ( (Env._Fe_ctl & 0x1F) == 0x1F )
  {
    LOBYTE(v171) = 0;
  }
  else
  {
    sub_1800B1D80(&Env);
    LOBYTE(v171) = 1;
  }
  *(_QWORD *)(a4 + 8) = a5;
  v10 = 32;
  if ( a1 < 0 )
    v10 = 45;
  v166 = 0;
  *(_DWORD *)a4 = v10;
  sub_1800B1C80(&v166, 0, 0);
  if ( (((unsigned __int64)a1 >> 52) & 0x7FF) != 0 )
  {
    if ( (((unsigned __int64)a1 >> 52) & 0x7FF) != 0x7FF )
      goto LABEL_28;
    if ( (a1 & 0xFFFFFFFFFFFFFLL) != 0 )
    {
      if ( a1 < 0 && (a1 & 0xFFFFFFFFFFFFFLL) == 0x8000000000000LL )
        v12 = 4;
      else
        v12 = ((((unsigned __int64)a1 >> 51) & 1) == 0) | 2;
    }
    else
    {
      v12 = 1;
    }
    *(_DWORD *)(a4 + 4) = 1;
    v13 = v12 - 1;
    if ( !v13 )
    {
      if ( !(unsigned int)sub_1800A5550(a5, a6, "1#INF") )
      {
        v9 = 0;
        goto LABEL_306;
      }
      goto LABEL_309;
    }
    v14 = v13 - 1;
    if ( v14 )
    {
      v15 = v14 - 1;
      if ( v15 )
      {
        if ( v15 != 1 )
          goto LABEL_28;
        v11 = "1#IND";
      }
      else
      {
        v11 = "1#SNAN";
      }
    }
    else
    {
      v11 = "1#QNAN";
    }
LABEL_22:
    if ( !(unsigned int)sub_1800A5550(a5, a6, v11) )
      goto LABEL_306;
LABEL_309:
    sub_1800A5C54(0, 0, 0, 0, 0);
    JUMPOUT(0x1800AF266LL);
  }
  if ( (a1 & 0xFFFFFFFFFFFFFLL) == 0 || (v166 & 0x1000000) != 0 )
  {
    *(_DWORD *)(a4 + 4) = 0;
    v11 = "0";
    goto LABEL_22;
  }
LABEL_28:
  v162 = 0;
  v168 = 524319;
  sub_1800B1C80(&v167, 0, 0);
  sub_1800B1C80(&v162, 524319, v168);
  v162 = a2 + 1;
  v16 = (((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF) + 2 - ((((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF) != 0);
  sub_1800B1EB0(-(__int64)(((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF));
  v17 = sub_1800B1DE0();
  Destination[0] = a1;
  v18 = ((a1 & 0xFFFFFFFFFFFFFLL)
       + (-(__int64)((((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF) != 0) & 0x10000000000000uLL)) >> 32;
  Destination[1] = v18;
  v160 = (((int)v17 - 0x7FFFFFFF) & 0xFFFFFFFE) != 0 ? (int)v17 : 0;
  v19 = ((_DWORD)v18 != 0) + 1;
  v175 = v19;
  if ( v16 < 0x434 )
  {
    if ( v16 != 54 )
    {
      v181 = 0x100000;
      Source = 0;
      v179 = 2;
      if ( (_DWORD)v18 )
      {
        v44 = 0;
        while ( *(&Source + v44) == Destination[v44] )
        {
          v44 = (unsigned int)(v44 + 1);
          if ( (_DWORD)v44 == 2 )
          {
            LODWORD(v163) = 0;
            v23 = !_BitScanReverse((unsigned int *)&v45, v18);
            if ( v23 )
              v46 = 0;
            else
              v46 = v45 + 1;
            v26 = v19 + ((unsigned int)(32 - v46) < 2);
            if ( v26 <= 0x73 )
            {
              v47 = v26 - 1;
              if ( v26 )
              {
                while ( 1 )
                {
                  v48 = v47;
                  v49 = v47 - 1;
                  v50 = v47 >= v19 ? 0 : Destination[v47];
                  v51 = (unsigned int)v49 >= v19 ? 0 : Destination[v49];
                  --v47;
                  Destination[v48] = (4 * v50) | (v51 >> 30);
                  if ( (_DWORD)v49 == -1 )
                    break;
                  v19 = v175;
                }
              }
              v175 = v26;
            }
            else
            {
              v179 = 0;
              v175 = 0;
              memcpy_s(Destination, 0x1CCu, &Source, 0);
              v26 = v175;
            }
            v52 = (1078 - v16) >> 5;
            sub_1800B9280(&Source, 0, 4 * v52);
            *(&Source + v52) = 1 << ((54
                                    - (((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52)
                                     + 2
                                     - ((((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF) != 0)))
                                   & 0x1F);
            goto LABEL_101;
          }
        }
      }
    }
    LODWORD(v163) = 0;
    v23 = !_BitScanReverse((unsigned int *)&v53, *(_DWORD *)((char *)Destination + ((_DWORD)v18 != 0 ? 4 : 0)));
    if ( v23 )
      v54 = 0;
    else
      v54 = v53 + 1;
    v26 = v19 + (v54 == 32);
    if ( v26 <= 0x73 )
    {
      v66 = v26 - 1;
      if ( v26 )
      {
        while ( 1 )
        {
          v67 = v66;
          v68 = v66 - 1;
          v69 = v66 >= v19 ? 0 : Destination[v66];
          v70 = (unsigned int)v68 >= v19 ? 0 : Destination[v68];
          --v66;
          Destination[v67] = (2 * v69) | (v70 >> 31);
          if ( (_DWORD)v68 == -1 )
            break;
          v19 = v175;
        }
      }
    }
    else
    {
      v26 = 0;
    }
    v175 = v26;
    v52 = (1077 - v16) >> 5;
    sub_1800B9280(&Source, 0, 4 * v52);
    *(&Source + v52) = 1 << ((53
                            - (((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52)
                             + 2
                             - ((((a1 & 0x7FFFFFFFFFFFFFFFuLL) >> 52) & 0x7FF) != 0)))
                           & 0x1F);
LABEL_101:
    v33 = 4LL * (unsigned int)(v52 + 1);
    v177 = v52 + 1;
    v179 = v52 + 1;
  }
  else
  {
    v181 = 0x100000;
    Source = 0;
    v179 = 2;
    if ( (_DWORD)v18 )
    {
      v20 = 0;
      while ( *(&Source + v20) == Destination[v20] )
      {
        v20 = (unsigned int)(v20 + 1);
        if ( (_DWORD)v20 == 2 )
        {
          LODWORD(v163) = 0;
          v21 = (v16 - 1074) & 0x1F;
          v22 = (v16 - 1074) >> 5;
          v23 = !_BitScanReverse((unsigned int *)&v24, Destination[(_DWORD)v18 != 0]);
          if ( v23 )
            v25 = 0;
          else
            v25 = v24 + 1;
          if ( v19 + v22 > 0x73 || (v26 = v22 + v19 + (v21 > 32 - v25), v26 > 0x73) )
          {
            v179 = 0;
            v175 = 0;
            memcpy_s(Destination, 0x1CCu, &Source, 0);
            v26 = v175;
          }
          else
          {
            v27 = v26 - 1;
            if ( (_DWORD)v27 != v22 - 1 )
            {
              while ( 1 )
              {
                v28 = (unsigned int)v27 - v22;
                v29 = (unsigned int)(v28 - 1);
                v30 = (unsigned int)v28 >= v19 ? 0 : Destination[v28];
                v31 = (unsigned int)v29 >= v19 ? 0 : Destination[v29];
                Destination[v27] = ((((unsigned int)(1LL << (32 - ((v16 - 50) & 0x1F))) - 1) & v30) << v21)
                                 | ((~((unsigned int)(1LL << (32 - ((v16 - 50) & 0x1F))) - 1) & v31) >> (32 - v21));
                v27 = (unsigned int)(v27 - 1);
                if ( (_DWORD)v27 == v22 - 1 )
                  break;
                v19 = v175;
              }
              v9 = 1;
            }
            v32 = 0;
            if ( v22 )
            {
              do
              {
                Destination[v32] = 0;
                v32 = (unsigned int)(v32 + 1);
              }
              while ( (_DWORD)v32 != v22 );
            }
            v175 = v26;
          }
          Source = 4;
          goto LABEL_53;
        }
      }
    }
    LODWORD(v163) = 0;
    v34 = (v16 - 1075) & 0x1F;
    v35 = (v16 - 1075) >> 5;
    v23 = !_BitScanReverse((unsigned int *)&v36, Destination[(_DWORD)v18 != 0]);
    if ( v23 )
      v37 = 0;
    else
      v37 = v36 + 1;
    if ( v19 + v35 > 0x73 || (v26 = v35 + v19 + (v34 > 32 - v37), v26 > 0x73) )
    {
      v179 = 0;
      v175 = 0;
      memcpy_s(Destination, 0x1CCu, &Source, 0);
      v26 = v175;
    }
    else
    {
      v38 = v26 - 1;
      if ( (_DWORD)v38 != v35 - 1 )
      {
        while ( 1 )
        {
          v39 = (unsigned int)v38 - v35;
          v40 = (unsigned int)(v39 - 1);
          v41 = (unsigned int)v39 >= v19 ? 0 : Destination[v39];
          v42 = (unsigned int)v40 >= v19 ? 0 : Destination[v40];
          Destination[v38] = ((((unsigned int)(1LL << (32 - ((v16 - 51) & 0x1F))) - 1) & v41) << v34)
                           | ((~((unsigned int)(1LL << (32 - ((v16 - 51) & 0x1F))) - 1) & v42) >> (32 - v34));
          v38 = (unsigned int)(v38 - 1);
          if ( (_DWORD)v38 == v35 - 1 )
            break;
          v19 = v175;
        }
        v9 = 1;
      }
      v43 = 0;
      if ( v35 )
      {
        do
        {
          Destination[v43] = 0;
          v43 = (unsigned int)(v43 + 1);
        }
        while ( (_DWORD)v43 != v35 );
      }
      v175 = v26;
    }
    Source = 2;
LABEL_53:
    v181 = 0;
    v33 = 4;
    v179 = 1;
    v177 = 1;
  }
  memcpy_s(v178, 0x1CCu, &Source, v33);
  v55 = (((int)v17 - 0x7FFFFFFF) & 0xFFFFFFFE) != 0 ? (int)v17 : 0;
  v56 = 0x180000000uLL;
  if ( (v160 & 0x80000000) != 0 )
  {
    v99 = -v160;
    LODWORD(v163) = -v160;
    v100 = -v160 / 0xA;
    v161 = v100;
    if ( !v100 )
    {
LABEL_247:
      v132 = v99 % 0xA;
      if ( !v132 )
        goto LABEL_259;
      v133 = dword_1800C1848[v132 - 1];
      if ( !v133 )
        goto LABEL_257;
      if ( v133 == 1 || !v26 )
        goto LABEL_259;
      LODWORD(v56) = 0;
      v134 = 0;
      do
      {
        v135 = (unsigned int)v56 + v133 * (unsigned __int64)(unsigned int)Destination[v134];
        Destination[v134] = v135;
        v56 = HIDWORD(v135);
        v134 = (unsigned int)(v134 + 1);
      }
      while ( (_DWORD)v134 != v26 );
      if ( !HIDWORD(v135) )
      {
        v26 = v175;
        goto LABEL_259;
      }
      if ( v175 >= 0x73 )
        goto LABEL_257;
      Destination[v175] = HIDWORD(v135);
      v26 = v175 + 1;
      goto LABEL_258;
    }
    while ( 1 )
    {
      v101 = v100;
      if ( v100 > 0x26 )
        v101 = 38;
      v164 = v101;
      v102 = (unsigned int)(v101 - 1);
      v103 = (unsigned __int8)byte_1800C17B2[4 * v102];
      v104 = (unsigned __int8)byte_1800C17B3[4 * v102];
      v105 = (unsigned int)v102;
      v106 = 4 * v103;
      v179 = v104 + v103;
      sub_1800B9280(&Source, 0, 4 * v103);
      sub_1800B8BD0(
        (char *)&Source + v106,
        (char *)&unk_1800C0EA0 + 4 * (unsigned __int16)word_1800C17B0[2 * v105],
        4 * v104);
      v107 = v179;
      if ( v179 > 1 )
      {
        if ( v26 > 1 )
        {
          v118 = v26;
          p_Source = &Source;
          if ( v179 < v26 )
            v118 = v179;
          else
            p_Source = Destination;
          v172 = p_Source;
          v159 = v118;
          v120 = Destination;
          if ( v179 >= v26 )
            v120 = &Source;
          v169 = v120;
          if ( v179 < v26 )
            v107 = v26;
          v26 = 0;
          v121 = 0;
          v182 = 0;
          do
          {
            v122 = p_Source[v121];
            if ( (_DWORD)v122 )
            {
              LODWORD(v123) = 0;
              v56 = (unsigned int)v121;
              if ( v107 )
              {
                while ( (_DWORD)v56 != 115 )
                {
                  v124 = (unsigned int)v56;
                  if ( (_DWORD)v56 == v26 )
                  {
                    v183[(unsigned int)v56] = 0;
                    v182 = v56 + 1;
                  }
                  v125 = (unsigned int)(v56 - v121);
                  v56 = (unsigned int)(v56 + 1);
                  v126 = (unsigned int)v183[v124] + (unsigned int)v123 + v122 * v120[v125];
                  v183[v124] = v126;
                  v26 = v182;
                  v123 = HIDWORD(v126);
                  if ( (_DWORD)v56 - (_DWORD)v121 == v107 )
                    break;
                  v120 = v169;
                }
                if ( (_DWORD)v123 )
                {
                  while ( (_DWORD)v56 != 115 )
                  {
                    v127 = (unsigned int)v56;
                    if ( (_DWORD)v56 == v26 )
                    {
                      v183[(unsigned int)v56] = 0;
                      v182 = v56 + 1;
                    }
                    v56 = (unsigned int)(v56 + 1);
                    v128 = (unsigned int)v123 + (unsigned __int64)(unsigned int)v183[v127];
                    v183[v127] = v128;
                    v26 = v182;
                    LODWORD(v123) = HIDWORD(v128);
                    if ( !HIDWORD(v128) )
                      goto LABEL_234;
                  }
LABEL_257:
                  v26 = 0;
LABEL_258:
                  v175 = v26;
                  goto LABEL_259;
                }
LABEL_234:
                v118 = v159;
              }
              if ( (_DWORD)v56 == 115 )
                goto LABEL_257;
              p_Source = v172;
              v120 = v169;
            }
            else if ( (_DWORD)v121 == v26 )
            {
              v183[v121] = 0;
              v26 = v121 + 1;
              v182 = v121 + 1;
            }
            v121 = (unsigned int)(v121 + 1);
          }
          while ( (_DWORD)v121 != v118 );
          v56 = 4LL * v26;
          v175 = v26;
          if ( v56 )
          {
            if ( v56 > 0x1CC )
            {
              sub_1800B9280(Destination, 0, 460);
              *(_DWORD *)sub_1800A5DDC(v130, v129, v131) = 34;
              invalid_parameter_noinfo();
            }
            else
            {
              sub_1800B8BD0(Destination, v183, v56);
            }
LABEL_242:
            v26 = v175;
          }
          goto LABEL_243;
        }
        v112 = Destination[0];
        v56 = 4LL * v179;
        v26 = v179;
        v175 = v179;
        if ( v56 )
        {
          if ( v56 > 0x1CC )
          {
            sub_1800B9280(Destination, 0, 460);
            *(_DWORD *)sub_1800A5DDC(v114, v113, v115) = 34;
            invalid_parameter_noinfo();
          }
          else
          {
            sub_1800B8BD0(Destination, &Source, v56);
          }
          v26 = v175;
        }
        if ( !(_DWORD)v112 )
        {
LABEL_190:
          v26 = 0;
          goto LABEL_191;
        }
        if ( (_DWORD)v112 == 1 || !v26 )
          goto LABEL_243;
        LODWORD(v56) = 0;
        v116 = 0;
        do
        {
          v117 = (unsigned int)v56 + v112 * (unsigned int)Destination[v116];
          Destination[v116] = v117;
          v56 = HIDWORD(v117);
          v116 = (unsigned int)(v116 + 1);
        }
        while ( (_DWORD)v116 != v26 );
      }
      else
      {
        if ( !Source )
          goto LABEL_190;
        if ( Source == 1 || !v26 )
          goto LABEL_243;
        LODWORD(v56) = 0;
        v108 = Source;
        v109 = 0;
        do
        {
          v110 = (unsigned int)v56 + v108 * (unsigned int)Destination[v109];
          Destination[v109] = v110;
          v56 = HIDWORD(v110);
          v109 = (unsigned int)(v109 + 1);
        }
        while ( (_DWORD)v109 != v26 );
      }
      if ( !(_DWORD)v56 )
        goto LABEL_242;
      if ( v175 < 0x73 )
      {
        Destination[v175] = v56;
        v26 = v175 + 1;
LABEL_191:
        v175 = v26;
LABEL_243:
        v111 = 1;
        goto LABEL_244;
      }
      v26 = 0;
      v175 = 0;
      v111 = 0;
LABEL_244:
      if ( !v111 )
        goto LABEL_257;
      v56 = 0x180000000uLL;
      v23 = v161 == v164;
      v100 = v161 - v164;
      v161 -= v164;
      if ( v23 )
      {
        v99 = (unsigned int)v163;
        goto LABEL_247;
      }
    }
  }
  v57 = v177;
  v58 = v160 / 0xA;
  v158 = v160 / 0xA;
  if ( !(v160 / 0xA) )
    goto LABEL_174;
  do
  {
    v59 = v58;
    if ( v58 > 0x26 )
      v59 = 38;
    v164 = v59;
    v60 = (unsigned int)(v59 - 1);
    v61 = (unsigned __int8)byte_1800C17B2[4 * v60];
    v62 = (unsigned __int8)byte_1800C17B3[4 * v60];
    v63 = (unsigned int)v60;
    v64 = 4 * v61;
    v179 = v62 + v61;
    sub_1800B9280(&Source, 0, 4 * v61);
    sub_1800B8BD0(
      (char *)&Source + v64,
      (char *)&unk_1800C0EA0 + 4 * (unsigned __int16)word_1800C17B0[2 * v63],
      4 * v62);
    v65 = v179;
    if ( v179 > 1 )
    {
      if ( v57 > 1 )
      {
        v81 = v57;
        v82 = &Source;
        if ( v179 < v57 )
          v81 = v179;
        else
          v82 = v178;
        v169 = v82;
        v161 = v81;
        v83 = v178;
        if ( v179 >= v57 )
          v83 = &Source;
        v163 = v83;
        if ( v179 < v57 )
          v65 = v57;
        v57 = 0;
        v84 = 0;
        v182 = 0;
        do
        {
          v85 = v82[v84];
          if ( (_DWORD)v85 )
          {
            LODWORD(v86) = 0;
            v56 = (unsigned int)v84;
            if ( v65 )
            {
              while ( (_DWORD)v56 != 115 )
              {
                v87 = (unsigned int)v56;
                if ( (_DWORD)v56 == v57 )
                {
                  v183[(unsigned int)v56] = 0;
                  v182 = v56 + 1;
                }
                v88 = (unsigned int)(v56 - v84);
                v56 = (unsigned int)(v56 + 1);
                v89 = (unsigned int)v86 + (unsigned int)v183[v87] + v85 * v83[v88];
                v183[v87] = v89;
                v57 = v182;
                v86 = HIDWORD(v89);
                if ( (_DWORD)v56 - (_DWORD)v84 == v65 )
                  break;
                v83 = v163;
              }
              if ( (_DWORD)v86 )
              {
                while ( (_DWORD)v56 != 115 )
                {
                  v90 = (unsigned int)v56;
                  if ( (_DWORD)v56 == v57 )
                  {
                    v183[(unsigned int)v56] = 0;
                    v182 = v56 + 1;
                  }
                  v56 = (unsigned int)(v56 + 1);
                  v91 = (unsigned int)v86 + (unsigned __int64)(unsigned int)v183[v90];
                  v183[v90] = v91;
                  v57 = v182;
                  LODWORD(v86) = HIDWORD(v91);
                  if ( !HIDWORD(v91) )
                    goto LABEL_161;
                }
                goto LABEL_183;
              }
LABEL_161:
              v81 = v161;
            }
            if ( (_DWORD)v56 == 115 )
              goto LABEL_183;
            v82 = v169;
            v83 = v163;
          }
          else if ( (_DWORD)v84 == v57 )
          {
            v183[v84] = 0;
            v57 = v84 + 1;
            v182 = v84 + 1;
          }
          v84 = (unsigned int)(v84 + 1);
        }
        while ( (_DWORD)v84 != v81 );
        v56 = 4LL * v57;
        v177 = v57;
        if ( !v56 )
          goto LABEL_170;
        if ( v56 > 0x1CC )
        {
          sub_1800B9280(v178, 0, 460);
          *(_DWORD *)sub_1800A5DDC(v93, v92, v94) = 34;
          invalid_parameter_noinfo();
        }
        else
        {
          sub_1800B8BD0(v178, v183, v56);
        }
LABEL_169:
        v57 = v177;
        goto LABEL_170;
      }
      v75 = v178[0];
      v56 = 4LL * v179;
      v57 = v179;
      v177 = v179;
      if ( v56 )
      {
        if ( v56 > 0x1CC )
        {
          sub_1800B9280(v178, 0, 460);
          *(_DWORD *)sub_1800A5DDC(v77, v76, v78) = 34;
          invalid_parameter_noinfo();
        }
        else
        {
          sub_1800B8BD0(v178, &Source, v56);
        }
        v57 = v177;
      }
      if ( !(_DWORD)v75 )
      {
LABEL_108:
        v57 = 0;
        goto LABEL_109;
      }
      if ( (_DWORD)v75 == 1 || !v57 )
        goto LABEL_170;
      LODWORD(v56) = 0;
      v79 = 0;
      do
      {
        v80 = (unsigned int)v56 + v75 * (unsigned int)v178[v79];
        v178[v79] = v80;
        v56 = HIDWORD(v80);
        v79 = (unsigned int)(v79 + 1);
      }
      while ( (_DWORD)v79 != v57 );
    }
    else
    {
      if ( !Source )
        goto LABEL_108;
      if ( Source == 1 || !v57 )
        goto LABEL_170;
      LODWORD(v56) = 0;
      v71 = Source;
      v72 = 0;
      do
      {
        v73 = (unsigned int)v56 + v71 * (unsigned int)v178[v72];
        v178[v72] = v73;
        v56 = HIDWORD(v73);
        v72 = (unsigned int)(v72 + 1);
      }
      while ( (_DWORD)v72 != v57 );
    }
    if ( !(_DWORD)v56 )
      goto LABEL_169;
    if ( v177 >= 0x73 )
    {
      v57 = 0;
      v177 = 0;
      v74 = 0;
      goto LABEL_171;
    }
    v178[v177] = v56;
    v57 = v177 + 1;
LABEL_109:
    v177 = v57;
LABEL_170:
    v74 = 1;
LABEL_171:
    if ( !v74 )
      goto LABEL_183;
    v23 = v158 == v164;
    v58 = v158 - v164;
    v158 -= v164;
  }
  while ( !v23 );
  v55 = (((int)v17 - 0x7FFFFFFF) & 0xFFFFFFFE) != 0 ? (int)v17 : 0;
  v56 = 0x180000000uLL;
LABEL_174:
  v95 = v55 % 0xA;
  if ( v95 )
  {
    v96 = dword_1800C1848[v95 - 1];
    if ( !v96 )
      goto LABEL_183;
    if ( v96 != 1 && v57 )
    {
      LODWORD(v56) = 0;
      v97 = 0;
      do
      {
        v98 = (unsigned int)v56 + v96 * (unsigned __int64)(unsigned int)v178[v97];
        v178[v97] = v98;
        v56 = HIDWORD(v98);
        v97 = (unsigned int)(v97 + 1);
      }
      while ( (_DWORD)v97 != v57 );
      if ( HIDWORD(v98) )
      {
        if ( v177 < 0x73 )
        {
          v178[v177] = HIDWORD(v98);
          v57 = v177 + 1;
          goto LABEL_184;
        }
LABEL_183:
        v57 = 0;
LABEL_184:
        v177 = v57;
        goto LABEL_260;
      }
LABEL_259:
      v57 = v177;
    }
  }
LABEL_260:
  v136 = (_BYTE *)v173;
  v137 = (_BYTE *)v173;
  if ( v26 )
  {
    LODWORD(v56) = 0;
    v138 = 0;
    do
    {
      v139 = (unsigned int)v56 + 10LL * (unsigned int)Destination[v138];
      Destination[v138] = v139;
      v138 = (unsigned int)(v138 + 1);
      v56 = HIDWORD(v139);
    }
    while ( (_DWORD)v138 != v26 );
    if ( (_DWORD)v56 )
    {
      if ( v175 >= 0x73 )
        v175 = 0;
      else
        Destination[v175++] = v56;
    }
  }
  v140 = sub_1800A2740(&v175, &v177, v56);
  v141 = (((int)v17 - 0x7FFFFFFF) & 0xFFFFFFFE) != 0 ? (int)v17 : 0;
  if ( v140 == 10 )
  {
    v141 = v160 + 1;
    *v136 = 49;
    v137 = v136 + 1;
    if ( v57 )
    {
      LODWORD(v142) = 0;
      v143 = 0;
      do
      {
        v144 = (unsigned int)v142 + 10LL * (unsigned int)v178[v143];
        v178[v143] = v144;
        v143 = (unsigned int)(v143 + 1);
        v142 = HIDWORD(v144);
      }
      while ( (_DWORD)v143 != v57 );
      if ( (_DWORD)v142 )
      {
        if ( v177 >= 0x73 )
          v177 = 0;
        else
          v178[v177++] = v142;
      }
    }
  }
  else if ( v140 )
  {
    v137 = v136 + 1;
    *v136 = v140 + 48;
  }
  else
  {
    v141 = v160 - 1;
  }
  *(_DWORD *)(v174 + 4) = v141;
  v145 = v162;
  if ( v141 >= 0 && v162 <= 0x7FFFFFFF && !v165 )
    v145 = v141 + v162;
  v146 = v145;
  if ( a6 - 1 < (unsigned __int64)v145 )
    v146 = a6 - 1;
  v147 = &v136[v146];
  v148 = 0;
  if ( v137 == v147 )
  {
LABEL_301:
    v149 = v175;
  }
  else
  {
    while ( 1 )
    {
      v149 = v175;
      if ( !v175 )
        break;
      LODWORD(v150) = 0;
      v151 = 0;
      do
      {
        v152 = (unsigned int)v150 + 1000000000LL * (unsigned int)Destination[v151];
        Destination[v151] = v152;
        v150 = HIDWORD(v152);
        v151 = (unsigned int)(v151 + 1);
      }
      while ( (_DWORD)v151 != v149 );
      if ( HIDWORD(v152) )
      {
        if ( v175 >= 0x73 )
          v175 = 0;
        else
          Destination[v175++] = HIDWORD(v152);
      }
      v153 = sub_1800A2740(&v175, &v177, v150);
      for ( i = 8; i != -1; --i )
      {
        v155 = v153 % 0xA + 48;
        v153 /= 0xAu;
        if ( (int)v147 - (int)v137 > i )
        {
          v137[i] = v155;
        }
        else if ( v155 != 48 )
        {
          v148 = 1;
        }
      }
      v156 = v147 - v137;
      if ( v147 - v137 > 9 )
        v156 = 9;
      v137 += v156;
      if ( v137 == v147 )
        goto LABEL_301;
    }
  }
  *v137 = 0;
  if ( v149 || v148 )
    v9 = 0;
  v165 = 0;
  sub_1800B1C80(&v165, v167, v168);
LABEL_306:
  if ( (_BYTE)v171 )
    sub_1800B1D10(&Env);
  return v9;
}
