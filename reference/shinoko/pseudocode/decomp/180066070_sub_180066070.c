// sub_180066070 size=2685
__int64 __fastcall sub_180066070(__int64 *a1, float a2, float a3)
{
  float v3; // xmm8_4
  __int64 v5; // rdx
  float v6; // xmm6_4
  __int64 v8; // r15
  __int64 v9; // r8
  unsigned int v10; // ebp
  unsigned __int8 *v11; // rdx
  unsigned int v12; // ebp
  __int64 v13; // r10
  __int64 v14; // r9
  __int64 v15; // r11
  unsigned __int64 v16; // rdx
  __int64 v17; // r8
  __int64 v18; // rax
  __int64 v19; // rbx
  __int64 v20; // r14
  int v21; // r10d
  int v22; // esi
  __int64 v23; // r8
  unsigned int v24; // r9d
  __int64 v25; // r11
  __int64 v26; // rax
  __int64 v27; // rdx
  float v28; // xmm1_4
  __int64 v29; // rax
  __int64 v30; // rcx
  __int64 v31; // rdx
  float v32; // xmm1_4
  __int64 v33; // rax
  __int64 v34; // rcx
  __int64 v35; // rdx
  float v36; // xmm1_4
  __int64 v37; // rax
  __int64 v38; // rcx
  __int64 v39; // rdx
  float v40; // xmm1_4
  __int64 v41; // rax
  __int64 v42; // rdx
  float v43; // xmm1_4
  __int64 v44; // r8
  __int64 v45; // rdi
  int v46; // r12d
  int v47; // eax
  signed int v48; // r15d
  int v49; // ebx
  int v50; // ebp
  int v51; // ecx
  int v52; // eax
  int v53; // esi
  __int64 v54; // rax
  __int64 v55; // r14
  __int64 v56; // rdx
  __int64 v57; // r10
  int v58; // r9d
  __int64 v59; // rdx
  __int64 v60; // rcx
  __int16 v61; // cx
  void *v62; // xmm0_8
  int v63; // r9d
  __int64 v64; // rdx
  __int64 v65; // rcx
  __int16 v66; // cx
  void *v67; // xmm0_8
  int v68; // r10d
  __int64 v69; // rdx
  __int64 v70; // rcx
  __int16 v71; // cx
  void *v72; // xmm7_8
  int v73; // r10d
  __int64 v74; // rdx
  __int64 v75; // rcx
  __int16 v76; // cx
  __int64 v77; // r8
  __int64 v78; // rcx
  __int64 v79; // rax
  __int64 v80; // r9
  __int64 v81; // rdx
  __int64 v82; // rbp
  _QWORD *v83; // rsi
  __int64 v84; // rax
  _QWORD *v85; // r14
  __int64 v86; // rdi
  void (__fastcall *v87)(__int64, _QWORD, __int64, __int64, __int64, _DWORD); // rax
  __int64 v88; // rcx
  __int64 v89; // rdi
  __int64 v90; // rcx
  __int64 v91; // rax
  __int64 v92; // [rsp+20h] [rbp-138h] BYREF
  float v93; // [rsp+28h] [rbp-130h]
  char v94; // [rsp+2Ch] [rbp-12Ch] BYREF
  __int64 v95; // [rsp+30h] [rbp-128h]
  __int64 v96; // [rsp+38h] [rbp-120h]
  unsigned int v97; // [rsp+40h] [rbp-118h] BYREF
  __int64 v98; // [rsp+48h] [rbp-110h]
  _DWORD v99[2]; // [rsp+50h] [rbp-108h] BYREF
  __int128 v100; // [rsp+58h] [rbp-100h]
  __int128 v101; // [rsp+68h] [rbp-F0h]
  int v102; // [rsp+78h] [rbp-E0h]
  __int128 v103; // [rsp+80h] [rbp-D8h]
  __int128 v104; // [rsp+90h] [rbp-C8h]
  __int128 v105; // [rsp+A0h] [rbp-B8h]
  __int128 v106; // [rsp+B0h] [rbp-A8h]
  __int128 v107; // [rsp+C0h] [rbp-98h]
  __int128 v108; // [rsp+D0h] [rbp-88h]
  __int64 v109; // [rsp+E0h] [rbp-78h]
  __int64 v110; // [rsp+160h] [rbp+8h]
  unsigned int v111; // [rsp+168h] [rbp+10h]

  v3 = a3;
  v5 = *a1;
  v6 = (float)(int)(float)(a2 + 0.5);
  if ( a3 < 0.0 )
    v3 = *((float *)a1 + 5);
  if ( v5 && *(float *)(v5 + 20) == v6 && *(float *)(v5 + 24) == v3 )
    return *a1;
  v8 = a1[1];
  v95 = v8;
  v9 = *(_QWORD *)(v8 + 688);
  v96 = v9;
  LODWORD(v92) = *((_DWORD *)a1 + 6);
  *((float *)&v92 + 1) = (float)(int)(float)(a2 + 0.5);
  v93 = v3;
  v10 = -1;
  v11 = (unsigned __int8 *)&v92;
  do
    v10 = dword_1800D56B0[*v11++ ^ (unsigned __int64)(unsigned __int8)v10] ^ (v10 >> 8);
  while ( v11 < (unsigned __int8 *)&v94 );
  v12 = ~v10;
  v111 = v12;
  v13 = v9 + 216;
  v14 = *(_QWORD *)(v9 + 224);
  v15 = v14;
  v110 = v14;
  v16 = *(int *)(v9 + 216);
  v17 = 2 * v16;
  if ( (_DWORD)v16 )
  {
    do
    {
      v18 = 16 * (v16 >> 1);
      if ( *(_DWORD *)(v18 + v15) >= v12 )
      {
        v16 >>= 1;
      }
      else
      {
        v15 += v18 + 16;
        v16 += -1LL - (v16 >> 1);
      }
    }
    while ( v16 );
    v110 = v15;
  }
  if ( v15 == v14 + 8 * v17 || *(_DWORD *)v15 != v12 )
  {
    v97 = v12;
    v98 = 0;
    v15 = sub_1800543A0(v13, v15, &v97);
    v110 = v15;
  }
  v19 = *(_QWORD *)(v15 + 8);
  if ( v19 )
    goto LABEL_170;
  if ( (a1[2] & 8) == 0 && !*(_BYTE *)(v8 + 80) )
  {
LABEL_99:
    v44 = qword_18010C470;
    if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
    {
      sub_180052F00("[font] Created baked %.2fpx\n", v6);
      v44 = qword_18010C470;
    }
    v45 = *(_QWORD *)(v8 + 688);
    v103 = 0;
    v104 = 0;
    v105 = 0;
    v106 = 0;
    v107 = 0;
    v108 = 0;
    v109 = 0;
    LODWORD(v107) = -1;
    v46 = *(_DWORD *)(v45 + 192);
    v47 = *(_DWORD *)(v45 + 196);
    if ( v46 == v47 )
    {
      v48 = (v47 + 63) & 0xFFFFFFE0;
      v49 = v47 / 32;
      v50 = v48 / 32;
      if ( v48 / 32 > v47 / 32 )
      {
        v51 = *(_DWORD *)(v45 + 204);
        if ( v48 / 32 > v51 )
        {
          if ( v51 )
            v52 = v51 + v51 / 2;
          else
            v52 = 8;
          v53 = v48 / 32;
          if ( v52 > v50 )
            v53 = v52;
          if ( v53 > v51 )
          {
            v54 = sub_18003A810(8LL * v53);
            v55 = v54;
            v56 = *(_QWORD *)(v45 + 208);
            if ( v56 )
            {
              sub_1800B8BD0(v54, v56, 8LL * *(int *)(v45 + 200));
              sub_18003A8D0(*(LPVOID *)(v45 + 208));
            }
            *(_QWORD *)(v45 + 208) = v55;
            *(_DWORD *)(v45 + 204) = v53;
          }
        }
        *(_DWORD *)(v45 + 200) = v50;
        do
        {
          v57 = sub_1800A39E0(3328);
          v44 = qword_18010C470;
          if ( qword_18010C470 )
          {
            v58 = *(_DWORD *)(qword_18010C470 + 5032);
            v59 = *(__int16 *)(qword_18010C470 + 10432);
            v60 = 8 * v59;
            if ( *(_DWORD *)(8 * v59 + qword_18010C470 + 10436) != v58 )
            {
              v61 = ((int)v59 + 1) % 6;
              *(_WORD *)(qword_18010C470 + 10432) = v61;
              v60 = 8LL * v61;
              *(_DWORD *)(v60 + v44 + 10436) = v58;
              *(_DWORD *)(v60 + v44 + 10440) = 0;
            }
            ++*(_WORD *)(v60 + v44 + 10440);
            ++*(_DWORD *)(v44 + 10424);
          }
          *(_QWORD *)(*(_QWORD *)(v45 + 208) + 8LL * v49++) = v57;
        }
        while ( v49 < v50 );
        *(_DWORD *)(v45 + 196) = v48;
      }
      v8 = v95;
      v12 = v111;
    }
    v19 = *(_QWORD *)(*(_QWORD *)(v45 + 208) + 8LL * (v46 / 32)) + 104LL * (v46 % 32);
    *(_OWORD *)v19 = 0;
    *(_OWORD *)(v19 + 16) = 0;
    *(_OWORD *)(v19 + 32) = 0;
    *(_OWORD *)(v19 + 48) = 0;
    *(_OWORD *)(v19 + 64) = v107;
    *(_OWORD *)(v19 + 80) = 0;
    *(_QWORD *)(v19 + 96) = 0;
    ++*(_DWORD *)(v45 + 192);
    v62 = (void *)_mm_srli_si128((__m128i)0LL, 8).m128i_u64[0];
    if ( v62 )
    {
      if ( v44 )
      {
        v63 = *(_DWORD *)(v44 + 5032);
        v64 = *(__int16 *)(v44 + 10432);
        v65 = 8 * v64;
        if ( *(_DWORD *)(8 * v64 + v44 + 10436) != v63 )
        {
          v66 = ((int)v64 + 1) % 6;
          *(_WORD *)(v44 + 10432) = v66;
          v65 = 8LL * v66;
          *(_DWORD *)(v65 + v44 + 10436) = v63;
          *(_DWORD *)(v65 + v44 + 10440) = 0;
        }
        ++*(_WORD *)(v65 + v44 + 10442);
        ++*(_DWORD *)(v44 + 10428);
      }
      sub_18009E210(v62);
      v44 = qword_18010C470;
    }
    v67 = (void *)_mm_srli_si128((__m128i)0LL, 8).m128i_u64[0];
    if ( v67 )
    {
      if ( v44 )
      {
        v68 = *(_DWORD *)(v44 + 5032);
        v69 = *(__int16 *)(v44 + 10432);
        v70 = 8 * v69;
        if ( *(_DWORD *)(8 * v69 + v44 + 10436) != v68 )
        {
          v71 = ((int)v69 + 1) % 6;
          *(_WORD *)(v44 + 10432) = v71;
          v70 = 8LL * v71;
          *(_DWORD *)(v70 + v44 + 10436) = v68;
          *(_DWORD *)(v70 + v44 + 10440) = 0;
        }
        ++*(_WORD *)(v70 + v44 + 10442);
        ++*(_DWORD *)(v44 + 10428);
      }
      sub_18009E210(v67);
      v44 = qword_18010C470;
    }
    v72 = (void *)_mm_srli_si128((__m128i)0LL, 8).m128i_u64[0];
    if ( v72 )
    {
      if ( v44 )
      {
        v73 = *(_DWORD *)(v44 + 5032);
        v74 = *(__int16 *)(v44 + 10432);
        v75 = 8 * v74;
        if ( *(_DWORD *)(8 * v74 + v44 + 10436) != v73 )
        {
          v76 = ((int)v74 + 1) % 6;
          *(_WORD *)(v44 + 10432) = v76;
          v75 = 8LL * v76;
          *(_DWORD *)(v75 + v44 + 10436) = v73;
          *(_DWORD *)(v75 + v44 + 10440) = 0;
        }
        ++*(_WORD *)(v75 + v44 + 10442);
        ++*(_DWORD *)(v44 + 10428);
      }
      sub_18009E210(v72);
    }
    *(float *)(v19 + 20) = v6;
    *(float *)(v19 + 24) = v3;
    *(_DWORD *)(v19 + 84) = v12;
    *(_QWORD *)(v19 + 88) = a1;
    *(_DWORD *)(v19 + 80) = *(_DWORD *)(*(_QWORD *)(v8 + 688) + 164LL);
    v77 = 0;
    v78 = a1[5];
    v79 = 8LL * *((int *)a1 + 8);
    v80 = v79 + v78;
    if ( !v79 )
      goto LABEL_146;
    do
    {
      v81 = *(_QWORD *)(*(_QWORD *)v78 + 128LL);
      if ( !v81 )
        v81 = *(_QWORD *)(v8 + 696);
      v77 += *(_QWORD *)(v81 + 72);
      v78 += 8;
    }
    while ( v78 != v80 );
    if ( v77 )
      v82 = sub_18003A810(v77);
    else
LABEL_146:
      v82 = 0;
    *(_QWORD *)(v19 + 96) = v82;
    v83 = (_QWORD *)a1[5];
    v84 = *((int *)a1 + 8);
    v85 = &v83[v84];
    if ( v84 * 8 )
    {
      do
      {
        v86 = *(_QWORD *)(*v83 + 128LL);
        if ( !v86 )
          v86 = *(_QWORD *)(v8 + 696);
        v87 = *(void (__fastcall **)(__int64, _QWORD, __int64, __int64, __int64, _DWORD))(v86 + 48);
        if ( v87 )
          v87(v8, *v83, v19, v82, v92, LODWORD(v93));
        v82 += *(_QWORD *)(v86 + 72);
        ++v83;
      }
      while ( v83 != v85 );
    }
    if ( *(_DWORD *)(v19 + 32) <= 0x20u )
      goto LABEL_158;
    v88 = *(unsigned __int16 *)(*(_QWORD *)(v19 + 40) + 64LL);
    if ( (_WORD)v88 == 0xFFFE )
    {
      v89 = 0;
LABEL_161:
      if ( *(_DWORD *)(v19 + 32) <= 9u )
        goto LABEL_165;
      v90 = *(unsigned __int16 *)(*(_QWORD *)(v19 + 40) + 18LL);
      if ( (_WORD)v90 == 0xFFFE )
        goto LABEL_167;
      if ( (_WORD)v90 == 0xFFFF )
      {
LABEL_165:
        *(_DWORD *)(v19 + 76) |= 0x8000000u;
        v91 = sub_180062410(v19, 9, 0);
        *(_DWORD *)(v19 + 76) &= ~0x8000000u;
      }
      else
      {
        v91 = *(_QWORD *)(v19 + 56) + 44 * v90;
      }
      if ( v91 )
      {
LABEL_169:
        *(_QWORD *)(v110 + 8) = v19;
LABEL_170:
        *(_DWORD *)(v19 + 80) = *(_DWORD *)(v96 + 164);
        *a1 = v19;
        return v19;
      }
LABEL_167:
      if ( v89 )
      {
        v100 = 0;
        v101 = 0;
        v102 = -1;
        v99[0] = 576;
        *(float *)&v99[1] = *(float *)(v89 + 4) * 4.0;
        sub_180065AE0(v8, v19, 0, v99);
      }
      goto LABEL_169;
    }
    if ( (_WORD)v88 == 0xFFFF )
    {
LABEL_158:
      *(_DWORD *)(v19 + 76) |= 0x8000000u;
      v89 = sub_180062410(v19, 32, 0);
      *(_DWORD *)(v19 + 76) &= ~0x8000000u;
    }
    else
    {
      v89 = *(_QWORD *)(v19 + 56) + 44 * v88;
    }
    if ( v89 )
      *(_DWORD *)v89 &= ~2u;
    goto LABEL_161;
  }
  v20 = *(_QWORD *)(v8 + 688);
  v21 = 0;
  v22 = *(_DWORD *)(v20 + 192);
  do
  {
    v19 = 0;
    v23 = 0;
    v24 = 0;
    if ( v22 >= 4 )
    {
      v25 = *(_QWORD *)(v20 + 208);
      do
      {
        v26 = v24 & 0x1F;
        v27 = 104 * v26 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
        if ( *(__int64 **)(v27 + 88) == a1
          && (*(_DWORD *)(v27 + 76) & 0x4000000) == 0
          && (v21 || *(float *)(v27 + 24) == v3) )
        {
          v28 = *(float *)(v27 + 20);
          if ( v28 > v6 && (!v19 || *(float *)(v19 + 20) > v28) )
            v19 = 104 * v26 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
          if ( v6 > v28 && (!v23 || v28 > *(float *)(v23 + 20)) )
            v23 = 104 * v26 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
        }
        v29 = (v24 + 1) >> 5;
        v30 = 104LL * ((v24 + 1) & 0x1F);
        v31 = v30 + *(_QWORD *)(v25 + 8 * v29);
        if ( *(__int64 **)(v31 + 88) == a1
          && (*(_DWORD *)(v31 + 76) & 0x4000000) == 0
          && (v21 || *(float *)(v31 + 24) == v3) )
        {
          v32 = *(float *)(v31 + 20);
          if ( v32 > v6 && (!v19 || *(float *)(v19 + 20) > v32) )
            v19 = v30 + *(_QWORD *)(v25 + 8 * v29);
          if ( v6 > v32 && (!v23 || v32 > *(float *)(v23 + 20)) )
            v23 = v30 + *(_QWORD *)(v25 + 8 * v29);
        }
        v33 = (v24 + 2) >> 5;
        v34 = 104LL * ((v24 + 2) & 0x1F);
        v35 = v34 + *(_QWORD *)(v25 + 8 * v33);
        if ( *(__int64 **)(v35 + 88) == a1
          && (*(_DWORD *)(v35 + 76) & 0x4000000) == 0
          && (v21 || *(float *)(v35 + 24) == v3) )
        {
          v36 = *(float *)(v35 + 20);
          if ( v36 > v6 && (!v19 || *(float *)(v19 + 20) > v36) )
            v19 = v34 + *(_QWORD *)(v25 + 8 * v33);
          if ( v6 > v36 && (!v23 || v36 > *(float *)(v23 + 20)) )
            v23 = v34 + *(_QWORD *)(v25 + 8 * v33);
        }
        v37 = (v24 + 3) >> 5;
        v38 = 104LL * ((v24 + 3) & 0x1F);
        v39 = v38 + *(_QWORD *)(v25 + 8 * v37);
        if ( *(__int64 **)(v39 + 88) == a1
          && (*(_DWORD *)(v39 + 76) & 0x4000000) == 0
          && (v21 || *(float *)(v39 + 24) == v3) )
        {
          v40 = *(float *)(v39 + 20);
          if ( v40 > v6 && (!v19 || *(float *)(v19 + 20) > v40) )
            v19 = v38 + *(_QWORD *)(v25 + 8 * v37);
          if ( v6 > v40 && (!v23 || v40 > *(float *)(v23 + 20)) )
            v23 = v38 + *(_QWORD *)(v25 + 8 * v37);
        }
        v24 += 4;
      }
      while ( (int)v24 < v22 - 3 );
      goto LABEL_89;
    }
    if ( v22 > 0 )
    {
      v25 = *(_QWORD *)(v20 + 208);
      do
      {
        v41 = v24 & 0x1F;
        v42 = 104 * v41 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
        if ( *(__int64 **)(v42 + 88) == a1
          && (*(_DWORD *)(v42 + 76) & 0x4000000) == 0
          && (v21 || *(float *)(v42 + 24) == v3) )
        {
          v43 = *(float *)(v42 + 20);
          if ( v43 > v6 && (!v19 || *(float *)(v19 + 20) > v43) )
            v19 = 104 * v41 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
          if ( v6 > v43 && (!v23 || v43 > *(float *)(v23 + 20)) )
            v23 = 104 * v41 + *(_QWORD *)(v25 + 8LL * (v24 >> 5));
        }
        ++v24;
LABEL_89:
        ;
      }
      while ( (int)v24 < v22 );
      if ( v19 )
      {
        if ( !v23 )
          goto LABEL_170;
        if ( *(float *)(v19 + 20) < (float)(v6 + v6) )
        {
LABEL_98:
          v19 = v23;
          goto LABEL_170;
        }
        if ( *(float *)(v23 + 20) > (float)(v6 * 0.5) )
          goto LABEL_170;
      }
      if ( v23 )
        goto LABEL_98;
    }
    ++v21;
  }
  while ( v21 < 2 );
  if ( !*(_BYTE *)(v8 + 80) )
    goto LABEL_99;
  return 0;
}
