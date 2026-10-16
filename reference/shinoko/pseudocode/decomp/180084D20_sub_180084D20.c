// sub_180084D20 size=2686
char __fastcall sub_180084D20(_BYTE *a1, char a2, int a3, float *a4)
{
  __int64 v4; // rbx
  char v7; // r13
  int v8; // r14d
  __int64 v9; // rdi
  unsigned int v10; // eax
  int v11; // r9d
  unsigned int v12; // r12d
  float v13; // xmm11_4
  float v14; // xmm10_4
  float v15; // xmm1_4
  float v16; // xmm5_4
  __int64 v17; // rax
  float v18; // xmm6_4
  float v19; // xmm4_4
  float v20; // xmm2_4
  float v21; // xmm3_4
  __int64 v22; // r9
  int v23; // xmm6_4
  int v24; // xmm7_4
  char v25; // al
  __int64 v26; // r9
  int v27; // esi
  int v28; // eax
  __int64 v29; // rcx
  __int64 v30; // rdx
  _DWORD *v31; // rax
  int v32; // xmm1_4
  int v33; // xmm2_4
  int v34; // xmm3_4
  int v35; // xmm4_4
  __int64 v36; // rax
  __int64 v37; // r8
  __int64 v38; // rax
  __int64 v39; // r8
  int v40; // edx
  int v41; // ecx
  int v42; // edx
  int v43; // ecx
  bool v44; // r8
  __int64 v45; // r10
  __int64 v46; // rdx
  char v47; // al
  __int64 v48; // r9
  __int64 v49; // rsi
  __int64 v50; // rax
  unsigned int v51; // ecx
  char v52; // r11
  __int64 v53; // r9
  char v54; // r14
  char v55; // si
  __int64 v56; // rdx
  float v57; // xmm2_4
  float v58; // xmm3_4
  __int64 v59; // r8
  char v60; // cl
  __int64 v61; // rax
  int v62; // edx
  __int64 v63; // r10
  int v64; // eax
  __int64 v65; // r8
  __int64 v66; // rcx
  __int64 v67; // rdx
  _DWORD *v68; // rax
  int v69; // xmm1_4
  int v70; // xmm2_4
  int v71; // xmm3_4
  int v72; // xmm4_4
  __int64 v73; // rax
  __int64 v74; // r8
  __int64 v75; // rax
  __int64 v76; // r8
  float v77; // xmm10_4
  __int64 v78; // rdi
  int v79; // r9d
  int v80; // ebx
  __int64 v81; // r8
  __int64 v82; // rcx
  __int64 v83; // rax
  __int64 v84; // rax
  __int64 v85; // rax
  unsigned __int8 v87; // [rsp+48h] [rbp-C0h] BYREF
  char v88; // [rsp+49h] [rbp-BFh]
  char v89; // [rsp+4Ah] [rbp-BEh] BYREF
  char v90; // [rsp+4Bh] [rbp-BDh] BYREF
  int v91; // [rsp+4Ch] [rbp-BCh]
  unsigned __int64 v92; // [rsp+50h] [rbp-B8h] BYREF
  __int64 v93; // [rsp+58h] [rbp-B0h]
  unsigned __int64 v94; // [rsp+60h] [rbp-A8h] BYREF
  int v95; // [rsp+68h] [rbp-A0h]
  unsigned __int64 v96; // [rsp+70h] [rbp-98h] BYREF
  float v97; // [rsp+78h] [rbp-90h]
  float v98; // [rsp+7Ch] [rbp-8Ch]
  _DWORD v99[2]; // [rsp+80h] [rbp-88h] BYREF
  __int64 v100; // [rsp+88h] [rbp-80h] BYREF
  int v101; // [rsp+90h] [rbp-78h]
  int v102; // [rsp+94h] [rbp-74h]
  __int64 v103; // [rsp+98h] [rbp-70h] BYREF
  __m128 v104; // [rsp+A0h] [rbp-68h] BYREF
  char v106; // [rsp+170h] [rbp+68h] BYREF

  v106 = a2;
  v4 = qword_18010C470;
  v7 = a2;
  v8 = (int)a1;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v9 = *(_QWORD *)(v4 + 5216);
  if ( *(_BYTE *)(v9 + 209) )
    return 0;
  v10 = sub_1800465E0(v9, a1);
  LOBYTE(v11) = 1;
  v12 = v10;
  sub_18003DF30((unsigned int)&v100, v8, 0, v11, -1082130432);
  v13 = a4[1];
  if ( v13 == 0.0 )
    v13 = *((float *)&v100 + 1);
  v14 = *a4;
  if ( *a4 == 0.0 )
    v14 = *(float *)&v100;
  v94 = *(_QWORD *)(v9 + 280);
  v15 = _mm_shuffle_ps((__m128)v94, (__m128)v94, 85).m128_f32[0] + *(float *)(v9 + 336);
  *(float *)v99 = v14;
  *(float *)&v99[1] = v13;
  *((float *)&v94 + 1) = v15;
  sub_18004AAD0(v99);
  v102 = a3 & 2;
  if ( (a3 & 2) != 0 )
    v16 = *(float *)(v9 + 592);
  else
    LODWORD(v16) = v94;
  v17 = 600;
  if ( (a3 & 2) == 0 )
    v17 = 584;
  if ( *a4 == 0.0 || (a3 & 0x1000000) != 0 )
    v14 = fmaxf(*(float *)&v100, *(float *)(v17 + v9) - v16);
  v92 = __PAIR64__(HIDWORD(v94), LODWORD(v16));
  *(float *)&v93 = v14 + v16;
  *((float *)&v93 + 1) = v13 + *((float *)&v94 + 1);
  if ( (a3 & 0x4000000) == 0 )
  {
    if ( (a3 & 2) != 0 )
      v18 = 0.0;
    else
      v18 = *(float *)(v4 + 3228);
    v19 = *(float *)(v4 + 3232);
    v20 = (float)(int)(float)(v18 * 0.5);
    v21 = (float)(int)(float)(v19 * 0.5);
    *(float *)&v92 = v16 - v20;
    *(float *)&v93 = (float)(v18 - v20) + (float)(v14 + v16);
    *((float *)&v92 + 1) = *((float *)&v94 + 1) - v21;
    *((float *)&v93 + 1) = (float)(v19 - v21) + (float)(v13 + *((float *)&v94 + 1));
  }
  v95 = a3 & 8;
  v22 = v95 != 0 ? 0x400 : 0;
  if ( (a3 & 2) != 0 )
  {
    v23 = *(_DWORD *)(v9 + 608);
    v24 = *(_DWORD *)(v9 + 616);
    *(_DWORD *)(v9 + 608) = *(_DWORD *)(v9 + 592);
    *(_DWORD *)(v9 + 616) = *(_DWORD *)(v9 + 600);
    sub_18004A070(&v92, v12, 0, v22);
    *(_DWORD *)(v9 + 608) = v23;
    *(_DWORD *)(v9 + 616) = v24;
  }
  else
  {
    sub_18004A070(&v92, v12, 0, v22);
  }
  v27 = *(_DWORD *)(v4 + 7748) & 0x400000;
  v88 = v25;
  v101 = v27;
  if ( !v25
    && (!v27
     || !*(_BYTE *)(v4 + 9088)
     || *(float *)(v4 + 9104) <= *((float *)&v92 + 1)
     || *((float *)&v93 + 1) <= *(float *)(v4 + 9096)
     || *(float *)(v4 + 9100) <= *(float *)&v92
     || *(float *)&v93 <= *(float *)(v4 + 9092)) )
  {
    return 0;
  }
  v28 = *(_DWORD *)(v4 + 7680) & 0x400;
  v99[0] = v28;
  if ( v95 && !v28 )
    sub_180045380();
  if ( (a3 & 2) != 0 )
  {
    if ( *(_QWORD *)(v4 + 8856) )
    {
      v29 = *(_QWORD *)(qword_18010C470 + 8856);
      v30 = *(_QWORD *)(qword_18010C470 + 5216);
      *(_OWORD *)(v29 + 368) = *(_OWORD *)(v30 + 608);
      v31 = *(_DWORD **)(v30 + 712);
      v32 = *(_DWORD *)(v29 + 336);
      v33 = *(_DWORD *)(v29 + 340);
      v34 = *(_DWORD *)(v29 + 344);
      v35 = *(_DWORD *)(v29 + 348);
      *(_OWORD *)(v30 + 608) = *(_OWORD *)(v29 + 336);
      v31[24] = v32;
      v31[25] = v33;
      v31[26] = v34;
      v31[27] = v35;
      v36 = *(_QWORD *)(v30 + 712);
      v37 = *(int *)(v36 + 160);
      v38 = *(_QWORD *)(v36 + 168);
      v39 = 2 * (v37 - 1);
      *(_DWORD *)(v38 + 8 * v39) = v32;
      *(_DWORD *)(v38 + 8 * v39 + 4) = v33;
      *(_DWORD *)(v38 + 8 * v39 + 8) = v34;
      *(_DWORD *)(v38 + 8 * v39 + 12) = v35;
      sub_18005D640(*(_QWORD *)(v29 + 416), *(_QWORD *)(v30 + 712), *(unsigned __int16 *)(v29 + 562), v26);
    }
    else if ( *(_QWORD *)(v9 + 456) )
    {
      sub_18006E490();
    }
    *(_DWORD *)(v4 + 7752) |= 0x200u;
    *(_OWORD *)(v4 + 7804) = *(_OWORD *)(v9 + 608);
  }
  v40 = (a3 & 0x100000) != 0 ? 0x20000 : 0;
  if ( (a3 & 0x8000000) != 0 )
  {
    v40 = 1179648;
    if ( (a3 & 0x100000) == 0 )
      v40 = 0x100000;
  }
  v41 = v40 | 0x10;
  if ( (a3 & 0x400000) == 0 )
    v41 = v40;
  v42 = v41 | 0x80;
  if ( (a3 & 0x800000) == 0 )
    v42 = v41;
  v43 = v42 | 0x120;
  if ( (a3 & 4) == 0 )
    v43 = v42;
  if ( (a3 & 0x10) != 0 || (*(_DWORD *)(v4 + 7748) & 0x4000) != 0 )
    v43 |= 0x1000u;
  LOBYTE(v91) = v7;
  v44 = v7;
  if ( v27 )
  {
    v45 = qword_18010C470;
    v46 = *(_QWORD *)(qword_18010C470 + 9144);
    if ( !*(_BYTE *)(v46 + 90) )
    {
LABEL_61:
      if ( v44 && (*(_DWORD *)(v45 + 5332) != v12 || !*(_BYTE *)(v45 + 5347)) || (*(_DWORD *)(v46 + 52) & 0x4000) != 0 )
        v51 = v43 | 0x80020;
      else
        v51 = v43 & 0xFFF7FFCF | 0x80010;
      v89 = sub_18006F740((unsigned int)&v92, v12, (unsigned int)&v87, (unsigned int)&v90, v51);
      sub_180086280(v12, &v106, &v89);
      v7 = v106;
      v54 = v89;
LABEL_76:
      v55 = 0;
      if ( !v54 && (!v87 || (a3 & 0x2000000) == 0) )
        goto LABEL_86;
      goto LABEL_79;
    }
    v47 = *(_BYTE *)(v46 + 88);
    if ( v47 != -1 )
      v44 = v47 == 1;
    if ( !*(_BYTE *)(v46 + 91) )
    {
LABEL_60:
      v106 = v44;
      goto LABEL_61;
    }
    v48 = *(_QWORD *)(v46 + 40);
    v49 = *(_QWORD *)(qword_18010C470 + 7704);
    if ( *(_BYTE *)(v46 + 94) || *(_DWORD *)(qword_18010C470 + 8564) != v12 )
    {
      v50 = *(_QWORD *)(v48 + 24);
      v52 = 0;
    }
    else
    {
      *(_BYTE *)(v46 + 94) = 1;
      v50 = *(_QWORD *)(v48 + 24);
      if ( v50 == -1 )
      {
        *(_QWORD *)(v48 + 24) = v49;
        *(_BYTE *)(v48 + 20) = v44;
LABEL_59:
        v44 = *(_BYTE *)(v48 + 20) != 0;
        goto LABEL_60;
      }
      v52 = 1;
    }
    if ( v50 != v49 && !v52 && *(_BYTE *)(v46 + 93) == *(_BYTE *)(v46 + 94) )
    {
      if ( (*(_DWORD *)(v46 + 84) & 0x1000) == 0 && (*(_BYTE *)(v46 + 52) & 0x10) == 0 )
        v44 = 0;
      goto LABEL_60;
    }
    goto LABEL_59;
  }
  v54 = sub_18006F740((unsigned int)&v92, v12, (unsigned int)&v87, (unsigned int)&v90, v43);
  if ( (a3 & 0x40) == 0 )
    goto LABEL_76;
  v62 = *(_DWORD *)(v4 + 8564);
  if ( !v62 || *(_DWORD *)(v4 + 8568) != *(_DWORD *)(v4 + 7676) || v62 != v12 || (*(_DWORD *)(v4 + 8572) & 0x1000) != 0 )
    goto LABEL_76;
  v55 = 1;
  v54 = 1;
  v7 = 1;
LABEL_79:
  if ( !*(_BYTE *)(v4 + 8113) && *(_QWORD *)(v4 + 8120) == v9 )
  {
    v56 = *(unsigned int *)(v9 + 368);
    if ( *(_DWORD *)(v4 + 8132) == (_DWORD)v56 )
    {
      v57 = *(float *)(v9 + 296);
      v58 = *(float *)(v9 + 300);
      v59 = *(unsigned int *)(v4 + 7676);
      *(float *)&v96 = *(float *)&v92 - v57;
      *((float *)&v96 + 1) = *((float *)&v92 + 1) - v58;
      v97 = *(float *)&v93 - v57;
      v98 = *((float *)&v93 + 1) - v58;
      sub_18004DA70(v12, v56, v59, &v96);
      if ( *(_BYTE *)(v4 + 86) )
        *(_BYTE *)(v4 + 8112) = 0;
    }
  }
  if ( v54 )
    sub_18003A1B0(v12);
LABEL_86:
  if ( v7 != (_BYTE)v91 )
    *(_DWORD *)(v4 + 7752) |= 8u;
  if ( !v88 )
    goto LABEL_107;
  if ( a3 & 0x20 | v87 )
  {
    v60 = 1;
    v61 = 25;
    goto LABEL_99;
  }
  v60 = 0;
  v61 = 24;
  if ( v7 )
  {
LABEL_99:
    if ( v90 && v60 )
      v61 = 26;
    v104 = *(__m128 *)(qword_18010C470 + 16 * (v61 + 18) + 3136);
    v104.m128_f32[3] = _mm_shuffle_ps(v104, v104, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    v103 = v93;
    v96 = v92;
    sub_180036620(&v104);
    sub_18005C870(*(_QWORD *)(*(_QWORD *)(v63 + 5216) + 712LL), (unsigned int)&v96, (unsigned int)&v103, v64, 0, 0);
  }
  if ( *(_DWORD *)(v4 + 8116) == v12 )
  {
    v65 = 14;
    if ( !v101 )
      v65 = 10;
    sub_180038770(&v92, v12, v65);
  }
LABEL_107:
  if ( v102 )
  {
    if ( *(_QWORD *)(v4 + 8856) )
    {
      v66 = *(_QWORD *)(qword_18010C470 + 8856);
      v67 = *(_QWORD *)(qword_18010C470 + 5216);
      v68 = *(_DWORD **)(v67 + 712);
      v69 = *(_DWORD *)(v66 + 368);
      v70 = *(_DWORD *)(v66 + 372);
      v71 = *(_DWORD *)(v66 + 376);
      v72 = *(_DWORD *)(v66 + 380);
      *(_OWORD *)(v67 + 608) = *(_OWORD *)(v66 + 368);
      v68[24] = v69;
      v68[25] = v70;
      v68[26] = v71;
      v68[27] = v72;
      v73 = *(_QWORD *)(v67 + 712);
      v74 = *(int *)(v73 + 160);
      v75 = *(_QWORD *)(v73 + 168);
      v76 = 2 * (v74 - 1);
      *(_DWORD *)(v75 + 8 * v76) = v69;
      *(_DWORD *)(v75 + 8 * v76 + 4) = v70;
      *(_DWORD *)(v75 + 8 * v76 + 8) = v71;
      *(_DWORD *)(v75 + 8 * v76 + 12) = v72;
      sub_18005D640(
        *(_QWORD *)(v66 + 416),
        *(_QWORD *)(v67 + 712),
        *(unsigned __int16 *)(116LL * *(int *)(v66 + 116) + *(_QWORD *)(v66 + 24) + 96),
        v53);
    }
    else if ( *(_QWORD *)(v9 + 456) )
    {
      sub_18006E550();
    }
  }
  if ( v88 )
  {
    v77 = fminf(v14 + *(float *)&v94, *(float *)(v9 + 584));
    *((float *)&v96 + 1) = v13 + *((float *)&v94 + 1);
    *(float *)&v96 = v77;
    sub_180037980((float *)&v94, (float *)&v96, a1, 0, &v100, (float *)(v4 + 3364), (float *)&v92);
  }
  if ( v54 )
  {
    if ( !v55 && (*(_DWORD *)(v9 + 20) & 0x4000000) != 0 && (a3 & 1) == 0 && (*(_BYTE *)(v4 + 7748) & 0x10) != 0 )
    {
      v78 = qword_18010C470;
      v79 = *(_DWORD *)(qword_18010C470 + 8064) - 1;
      v80 = v79;
      if ( v79 >= 0 && v79 < *(_DWORD *)(qword_18010C470 + 8048) )
      {
        v81 = *(_QWORD *)(qword_18010C470 + 8056);
        if ( *(_DWORD *)(56LL * v79 + *(_QWORD *)(qword_18010C470 + 8072)) == *(_DWORD *)(56LL * v79 + v81) )
        {
          if ( v79 > 0 )
          {
            do
            {
              v82 = 56LL * (unsigned int)v80;
              v83 = *(_QWORD *)(v81 + v82 + 8);
              if ( !v83 )
                break;
              if ( (*(_DWORD *)(v83 + 20) & 0x10000000) == 0 )
                break;
              v84 = *(_QWORD *)(v81 + v82 - 48);
              if ( !v84 )
                break;
              if ( (*(_DWORD *)(v84 + 20) & 0x400) != 0 )
                break;
              --v80;
            }
            while ( v80 > 0 );
          }
          if ( (*(_BYTE *)(qword_18010C470 + 10228) & 8) != 0 )
            sub_180052F00("[popup] CloseCurrentPopup %d -> %d\n", v79, v80);
          sub_18004C4C0(v80, 1u);
          v85 = *(_QWORD *)(v78 + 8120);
          if ( v85 )
            *(_BYTE *)(v85 + 377) = 1;
        }
      }
    }
  }
  if ( v95 )
  {
    if ( !v99[0] )
      sub_1800453E0();
  }
  return v54;
}
