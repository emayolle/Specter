// sub_180083B30 size=3196
char __fastcall sub_180083B30(_BYTE *a1, float *a2, unsigned int a3, float *a4)
{
  __int64 v4; // rdi
  __int64 v9; // rbx
  unsigned int v10; // eax
  float v11; // xmm6_4
  unsigned int v12; // r13d
  float v13; // xmm9_4
  float v14; // xmm2_4
  char v15; // al
  char v16; // al
  int v17; // edx
  int v18; // ecx
  int v19; // r8d
  __int128 v20; // xmm0
  unsigned int v21; // r14d
  float v22; // xmm12_4
  __m128 v23; // xmm10
  __m128 v24; // xmm14
  __m128 v25; // xmm11
  __m128 v26; // xmm13
  float v27; // xmm9_4
  float v28; // xmm12_4
  __m128 v29; // xmm15
  float v30; // xmm0_4
  float v31; // xmm0_4
  __m128 v32; // xmm6
  __int64 v33; // rcx
  int v34; // eax
  int v35; // eax
  int v36; // xmm6_4
  int v37; // xmm9_4
  __int32 v38; // xmm10_4
  int v39; // eax
  unsigned int *v40; // rax
  unsigned int v41; // xmm1_4
  char *v42; // rax
  unsigned int v43; // xmm2_4
  __int32 *v44; // rax
  __int32 v45; // xmm3_4
  float *v46; // rax
  float v47; // xmm0_4
  int v48; // eax
  int v49; // eax
  int v50; // eax
  __int64 v51; // rdi
  int v52; // ebx
  int v53; // r15d
  __int64 v54; // rax
  int v55; // r13d
  bool v56; // cl
  bool v57; // zf
  __int64 v58; // rbx
  _BYTE *v59; // rax
  __int64 v60; // rbx
  int v61; // xmm0_4
  __int64 v62; // rdx
  __int64 v63; // rcx
  __int64 v64; // rbx
  __int64 v65; // rbx
  _BYTE *i; // rdx
  __int64 v67; // rdx
  __int64 v68; // rcx
  __int64 v69; // r8
  __int64 v70; // r9
  __int32 v71; // xmm3_4
  float v72; // xmm1_4
  float v73; // xmm2_4
  float v74; // xmm10_4
  float v75; // xmm9_4
  float v76; // xmm6_4
  int v77; // edi
  float v78; // xmm0_4
  float v79; // xmm8_4
  __int64 v80; // rdx
  __int64 v81; // rcx
  double v82; // xmm3_8
  double v83; // xmm2_8
  double v84; // xmm1_8
  float v85; // xmm10_4
  float v86; // xmm9_4
  float v87; // xmm6_4
  int v88; // edx
  int v89; // r8d
  int v90; // r9d
  char v92; // [rsp+78h] [rbp-90h] BYREF
  char v93; // [rsp+79h] [rbp-8Fh]
  __m128 v94; // [rsp+80h] [rbp-88h] BYREF
  unsigned __int64 v95; // [rsp+90h] [rbp-78h] BYREF
  int v96; // [rsp+98h] [rbp-70h]
  float v97; // [rsp+9Ch] [rbp-6Ch]
  char v98; // [rsp+A0h] [rbp-68h] BYREF
  unsigned __int64 v99; // [rsp+A4h] [rbp-64h]
  __int32 v100; // [rsp+ACh] [rbp-5Ch]
  __int128 v101; // [rsp+B0h] [rbp-58h] BYREF
  unsigned __int64 v102; // [rsp+C0h] [rbp-48h] BYREF
  unsigned __int64 v103; // [rsp+C8h] [rbp-40h] BYREF
  unsigned __int64 v104; // [rsp+D0h] [rbp-38h] BYREF
  unsigned __int64 v105; // [rsp+D8h] [rbp-30h] BYREF
  float v106[2]; // [rsp+E0h] [rbp-28h] BYREF
  float v107; // [rsp+E8h] [rbp-20h]
  __int64 v108; // [rsp+F0h] [rbp-18h] BYREF
  int v109; // [rsp+F8h] [rbp-10h] BYREF
  int v110; // [rsp+FCh] [rbp-Ch] BYREF

  v4 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v9 = *(_QWORD *)(v4 + 5216);
  if ( *(_BYTE *)(v9 + 209) )
    return 0;
  v10 = sub_1800465E0(*(_QWORD *)(v4 + 5216), a1);
  v11 = a4[1];
  v12 = v10;
  if ( v11 == 0.0 )
    v11 = (float)(*(float *)(qword_18010C470 + 3216) + *(float *)(qword_18010C470 + 3216))
        + *(float *)(qword_18010C470 + 4432);
  v13 = *a4;
  if ( *a4 == 0.0 )
    v13 = (float)(*(float *)(qword_18010C470 + 3216) + *(float *)(qword_18010C470 + 3216))
        + *(float *)(qword_18010C470 + 4432);
  v14 = v11 + *(float *)(v9 + 284);
  v102 = *(_QWORD *)(v9 + 280);
  *((float *)&v103 + 1) = v14;
  *(float *)&v103 = *(float *)&v102 + v13;
  v106[0] = (float)(*(float *)&v102 + v13) - *(float *)&v102;
  v106[1] = v14 - *((float *)&v102 + 1);
  sub_18004AAD0(v106);
  sub_18004A070(&v102, v12, 0, 0);
  if ( !v15 )
    return 0;
  v16 = sub_18006F740((unsigned int)&v102, v12, (unsigned int)&v92, (unsigned int)&v98, 0);
  v20 = *(_OWORD *)a2;
  v93 = v16;
  v21 = a3 & 0xFFFFCFFF;
  v101 = v20;
  if ( (a3 & 0x802) == 0 )
    v21 = a3;
  LODWORD(v106[0]) = v21 & 0x10000000;
  if ( (v21 & 0x10000000) != 0 )
    sub_180036790(v18, v17, v19, (unsigned int)&v101, (__int64)&v101 + 4, (__int64)&v101 + 8);
  v22 = *(float *)(v4 + 3220);
  v23 = (__m128)(unsigned int)v102;
  v24 = (__m128)HIDWORD(v102);
  v25 = (__m128)(unsigned int)v103;
  v26 = (__m128)HIDWORD(v103);
  v99 = v101;
  v108 = v101;
  v100 = DWORD2(v101);
  v109 = DWORD2(v101);
  v104 = v102;
  v105 = v103;
  v110 = 1065353216;
  v27 = fminf(v13, v11) / 2.99;
  v28 = fminf(v22, v27 * 0.5);
  if ( (v21 & 0x400) != 0 )
  {
    v29 = 0;
  }
  else
  {
    v29 = (__m128)0xBF400000;
    v23.m128_f32[0] = *(float *)&v102 - -0.75;
    v24.m128_f32[0] = *((float *)&v102 + 1) - -0.75;
    v25.m128_f32[0] = *(float *)&v103 - 0.75;
    v26.m128_f32[0] = *((float *)&v103 + 1) - 0.75;
    v104 = __PAIR64__(*((float *)&v102 + 1) - -0.75, *(float *)&v102 - -0.75);
    v105 = __PAIR64__(*((float *)&v103 + 1) - 0.75, *(float *)&v103 - 0.75);
  }
  if ( (v21 & 0x2000) != 0 && *((float *)&v101 + 3) < 1.0 )
  {
    v30 = v25.m128_f32[0] + v23.m128_f32[0];
    v23.m128_f32[0] = v23.m128_f32[0] + v27;
    v107 = (float)(int)(float)((float)(v30 * 0.5) + 0.5);
    v31 = *((float *)&v101 + 3) * *(float *)(qword_18010C470 + 3148);
    if ( (v21 & 0x1000) != 0 )
    {
      v94.m128_u64[0] = v101;
      v94.m128_u64[1] = __PAIR64__(LODWORD(v31), DWORD2(v101));
      v95 = __PAIR64__(v24.m128_u32[0], v23.m128_u32[0]);
      sub_180036620(&v94);
      sub_18005C870(*(_QWORD *)(v9 + 712), (unsigned int)&v95, (unsigned int)&v105, v35, LODWORD(v28), 160);
    }
    else
    {
      v32 = v29;
      v95 = v101;
      v32.m128_f32[0] = v29.m128_f32[0] - v27;
      v96 = DWORD2(v101);
      v97 = v31;
      sub_180036620(&v95);
      v33 = *(_QWORD *)(v9 + 712);
      v105 = _mm_unpacklo_ps(v25, v26).m128_u64[0];
      sub_180068380(
        v33,
        _mm_unpacklo_ps(v23, v24).m128_u32[0],
        v105,
        v34,
        LODWORD(v27),
        _mm_unpacklo_ps(v32, v29).m128_i64[0],
        LODWORD(v28),
        160);
    }
    v36 = v99;
    v37 = HIDWORD(v99);
    v38 = v100;
    v94.m128_i32[3] = *(_DWORD *)(qword_18010C470 + 3148);
    v94.m128_u64[0] = v99;
    v94.m128_i32[2] = v100;
    v95 = __PAIR64__(v26.m128_u32[0], LODWORD(v107));
    sub_180036620(&v94);
    sub_18005C870(*(_QWORD *)(v9 + 712), (unsigned int)&v104, (unsigned int)&v95, v39, LODWORD(v28), 80);
  }
  else
  {
    v40 = (unsigned int *)&v108;
    if ( (v21 & 0x800) == 0 )
      v40 = (unsigned int *)&v101;
    v41 = *v40;
    v42 = (char *)&v108 + 4;
    if ( (v21 & 0x800) == 0 )
      v42 = (char *)&v101 + 4;
    v43 = *(_DWORD *)v42;
    v44 = &v109;
    if ( (v21 & 0x800) == 0 )
      v44 = (__int32 *)&v101 + 2;
    v45 = *v44;
    v46 = (float *)&v110;
    if ( (v21 & 0x800) == 0 )
      v46 = (float *)&v101 + 3;
    v47 = *v46;
    if ( *v46 >= 1.0 || (v21 & 0x1000) != 0 )
    {
      v94.m128_u64[0] = __PAIR64__(v43, v41);
      v94.m128_i32[2] = v45;
      v94.m128_f32[3] = v47 * *(float *)(qword_18010C470 + 3148);
      sub_180036620(&v94);
      sub_18005C870(*(_QWORD *)(v9 + 712), (unsigned int)&v104, (unsigned int)&v105, v49, LODWORD(v28), 0);
    }
    else
    {
      v94.m128_u64[0] = __PAIR64__(v43, v41);
      v94.m128_i32[2] = v45;
      v94.m128_f32[3] = v47 * *(float *)(qword_18010C470 + 3148);
      sub_180036620(&v94);
      sub_180068380(
        *(_QWORD *)(v9 + 712),
        _mm_unpacklo_ps(v23, v24).m128_u32[0],
        _mm_unpacklo_ps(v25, v26).m128_u32[0],
        v48,
        LODWORD(v27),
        _mm_unpacklo_ps(v29, v29).m128_i64[0],
        LODWORD(v28),
        0);
    }
    v38 = v100;
    v37 = HIDWORD(v99);
    v36 = v99;
  }
  sub_180038770(&v102, v12, 0);
  if ( (v21 & 0x400) == 0 )
  {
    if ( *(float *)(v4 + 3224) <= 0.0 )
    {
      v94 = *(__m128 *)(qword_18010C470 + 3536);
      v94.m128_f32[3] = _mm_shuffle_ps(v94, v94, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      sub_180036620(&v94);
      sub_18005C460(*(_QWORD *)(v9 + 712), (unsigned int)&v102, (unsigned int)&v103, v50, LODWORD(v28));
    }
    else
    {
      sub_180038630(v102, v103);
    }
  }
  if ( *(_DWORD *)(v4 + 5332) == v12 && (v21 & 0x200) == 0 )
  {
    v51 = qword_18010C470;
    v52 = *(_DWORD *)(qword_18010C470 + 7744);
    if ( v52 )
    {
      if ( *(_DWORD *)(qword_18010C470 + 5332) == v52 )
      {
        v53 = *(char *)(qword_18010C470 + 5356);
        if ( *(_BYTE *)(qword_18010C470 + 5356) == 0xFF )
          v53 = 0;
        if ( *(_BYTE *)(v53 + qword_18010C470 + 232) )
        {
          v54 = *(_QWORD *)(qword_18010C470 + 5216);
          if ( !*(_BYTE *)(v54 + 209) )
          {
            *(_BYTE *)(qword_18010C470 + 5345) = 0;
            v55 = *(_DWORD *)(*(_QWORD *)(v54 + 272) + 4LL * *(int *)(v54 + 264) - 4);
            v56 = *(_BYTE *)(v53 + v51 + 232)
               && *(float *)(v51 + 4LL * v53 + 2964) >= (float)(*(float *)(v51 + 112) * *(float *)(v51 + 112));
            v57 = *(_BYTE *)(v51 + 8202) == 0;
            *(_DWORD *)(v51 + 7664) = 15;
            *(_BYTE *)(v51 + 7668) = 1;
            *(_BYTE *)(v51 + 8201) = !v57;
            *(_WORD *)(v51 + 8264) = 0;
            if ( v56 )
            {
              if ( !*(_BYTE *)(v51 + 8656) )
              {
                sub_1800516C0();
                if ( (*(_BYTE *)(v51 + 10228) & 2) != 0 )
                  sub_180052F00(
                    "[dragdrop] BeginDragDropSource() DragDropActive = true, source_id = 0x%08X%s\n",
                    v52,
                    byte_1800D411C);
                *(_DWORD *)(v51 + 8684) = v52;
                *(_DWORD *)(v51 + 8688) = v55;
                *(_BYTE *)(v51 + 8656) = 1;
                *(_DWORD *)(v51 + 8660) = 0;
                *(_DWORD *)(v51 + 8668) = v53;
                if ( v52 == *(_DWORD *)(v51 + 5332) )
                  *(_BYTE *)(v51 + 5346) = 1;
              }
              v57 = *(_DWORD *)(v51 + 8788) == 0;
              *(_DWORD *)(v51 + 8664) = *(_DWORD *)(v51 + 5032);
              *(_BYTE *)(v51 + 8657) = 1;
              if ( v57 || (*(_DWORD *)(v51 + 8776) & 0x1000) == 0 )
              {
                sub_18004BB50(0);
              }
              else
              {
                v58 = qword_18010C470;
                sub_180040700("##Tooltip_Hidden", 0, 33751879);
                v59 = *(_BYTE **)(v58 + 5216);
                v59[209] = 1;
                v59[212] = 1;
                v59[236] = 1;
              }
              *(_DWORD *)(v51 + 7752) &= ~1u;
              v60 = qword_18010C470;
              if ( (v21 & 2) != 0 )
              {
                if ( *(_DWORD *)(qword_18010C470 + 8692) == -1 )
                {
                  sub_1800B97F0(qword_18010C470 + 8696, "_COL3F", 32);
                  *(_BYTE *)(v60 + 8728) = 0;
                  sub_1800542F0(v60 + 8800, 0);
                  *(_DWORD *)(v60 + 8828) = 0;
                  *(_QWORD *)(v60 + 8672) = v60 + 8816;
                  *(_DWORD *)(v60 + 8816) = v36;
                  *(_DWORD *)(v60 + 8820) = v37;
                  *(_DWORD *)(v60 + 8824) = v38;
                  *(_DWORD *)(v60 + 8680) = 12;
                }
              }
              else if ( *(_DWORD *)(qword_18010C470 + 8692) == -1 )
              {
                sub_1800B97F0(qword_18010C470 + 8696, "_COL4F", 32);
                *(_BYTE *)(v60 + 8728) = 0;
                sub_1800542F0(v60 + 8800, 0);
                v61 = HIDWORD(v101);
                *(_QWORD *)(v60 + 8672) = v60 + 8816;
                *(_DWORD *)(v60 + 8816) = v36;
                *(_DWORD *)(v60 + 8820) = v37;
                *(_DWORD *)(v60 + 8824) = v38;
                *(_DWORD *)(v60 + 8828) = v61;
                *(_DWORD *)(v60 + 8680) = 16;
              }
              *(_DWORD *)(v60 + 8692) = *(_DWORD *)(v60 + 5032);
              v95 = 0;
              sub_180083B30(a1, a2, v21, &v95);
              sub_18004AC40(v63, v62);
              sub_18006EB90("Color", nullptr, 0);
              v64 = qword_18010C470;
              if ( (*(_BYTE *)(qword_18010C470 + 8660) & 1) == 0 )
                sub_180044DF0();
              if ( *(_DWORD *)(v64 + 8692) == -1 )
                sub_1800516C0();
              *(_BYTE *)(v64 + 8657) = 0;
            }
          }
        }
      }
    }
  }
  if ( (v21 & 0x40) == 0 )
  {
    if ( v92 )
    {
      if ( sub_18003A270(0x1000u) )
      {
        v65 = qword_18010C470;
        if ( sub_18004BB50(2) )
        {
          if ( a1 )
          {
            for ( i = a1; i != (_BYTE *)-1LL; ++i )
            {
              if ( !*i || *i == 35 && i[1] == 35 )
                break;
            }
            if ( i > a1 )
            {
              sub_18006EB90(a1, i, 0);
              sub_180071F50(v68, v67, v69, v70);
            }
          }
          *(float *)&v95 = (float)(*(float *)(v65 + 4432) * 3.0)
                         + (float)(*(float *)(v65 + 3216) + *(float *)(v65 + 3216));
          HIDWORD(v95) = v95;
          if ( (v21 & 2) != 0 )
            v71 = 1065353216;
          else
            v71 = *((_DWORD *)a2 + 3);
          v72 = a2[1];
          v73 = a2[2];
          v94.m128_f32[0] = *a2;
          *(unsigned __int64 *)((char *)v94.m128_u64 + 4) = __PAIR64__(LODWORD(v73), LODWORD(v72));
          v94.m128_i32[3] = v71;
          if ( v94.m128_f32[0] >= 0.0 )
            v74 = fminf(1.0, v94.m128_f32[0]);
          else
            v74 = 0.0;
          if ( v72 >= 0.0 )
            v75 = fminf(1.0, v72);
          else
            v75 = 0.0;
          if ( v73 >= 0.0 )
            v76 = fminf(1.0, v73);
          else
            v76 = 0.0;
          if ( (v21 & 2) != 0 )
          {
            v77 = 255;
          }
          else
          {
            v78 = a2[3];
            if ( v78 >= 0.0 )
              v79 = fminf(1.0, v78);
            else
              v79 = 0.0;
            v77 = (int)(float)((float)(v79 * 255.0) + 0.5);
          }
          sub_180083B30("##preview", &v94, v21 & 0x18003802 | 0x40, &v95);
          sub_18004AC40(v81, v80);
          if ( (v21 & 0x8000000) != 0 || (v21 & 0x18000000) == 0 )
          {
            v85 = (float)(v74 * 255.0) + 0.5;
            v86 = (float)(v75 * 255.0) + 0.5;
            v87 = (float)(v76 * 255.0) + 0.5;
            v88 = (int)v85;
            v89 = (int)v86;
            v90 = (int)v87;
            if ( (v21 & 2) != 0 )
              sub_18006F370(
                (__int64)"#%02X%02X%02X\nR: %d, G: %d, B: %d\n(%.3f, %.3f, %.3f)",
                v88,
                v89,
                v90,
                (int)v85,
                (int)v86,
                (int)v87,
                *a2,
                a2[1],
                a2[2]);
            else
              sub_18006F370(
                (__int64)"#%02X%02X%02X%02X\nR:%d, G:%d, B:%d, A:%d\n(%.3f, %.3f, %.3f, %.3f)",
                v88,
                v89,
                v90,
                v77,
                (int)v85,
                (int)v86,
                (int)v87,
                v77,
                *a2,
                a2[1],
                a2[2],
                a2[3]);
          }
          else if ( LODWORD(v106[0]) )
          {
            v82 = a2[2];
            v83 = a2[1];
            v84 = *a2;
            if ( (v21 & 2) != 0 )
              sub_18006F370((__int64)"H: %.3f, S: %.3f, V: %.3f", v84, v83, v82);
            else
              sub_18006F370((__int64)"H: %.3f, S: %.3f, V: %.3f, A: %.3f", v84, v83, v82, a2[3]);
          }
          sub_180044DF0();
        }
      }
    }
  }
  return v93;
}
