// sub_180062E40 size=1945
char __fastcall sub_180062E40(__int64 a1, __int64 a2)
{
  __int64 v3; // rax
  char *v4; // rbx
  __int64 v5; // rdi
  int v6; // edx
  char v7; // al
  unsigned int v8; // esi
  __int64 v9; // r13
  int v10; // eax
  int v11; // r14d
  int v12; // eax
  int v13; // r12d
  unsigned int v15; // eax
  __int128 v16; // xmm2
  int v17; // ecx
  __int64 v18; // rax
  int v19; // r8d
  unsigned __int8 v20; // dl
  __int128 v21; // xmm1
  int v22; // r12d
  int v23; // r14d
  int v24; // ecx
  __int64 v25; // rdx
  bool v26; // zf
  int v27; // ecx
  __int64 v28; // r12
  _OWORD *v29; // rax
  int v30; // eax
  __int64 v31; // rcx
  unsigned int v32; // eax
  int v33; // edx
  int v34; // r8d
  int v35; // eax
  int v36; // r9d
  __int64 v37; // rdx
  int v38; // ecx
  __int64 v39; // rax
  float v40; // xmm3_4
  __int64 v41; // r9
  __m128i v42; // xmm0
  float v43; // xmm1_4
  float v44; // xmm0_4
  int v45; // [rsp+20h] [rbp-39h] BYREF
  _DWORD v46[3]; // [rsp+24h] [rbp-35h] BYREF
  __int128 v47; // [rsp+30h] [rbp-29h] BYREF
  __int128 v48; // [rsp+40h] [rbp-19h] BYREF
  __int128 v49; // [rsp+50h] [rbp-9h] BYREF
  __int128 v50; // [rsp+60h] [rbp+7h] BYREF
  __int128 v51; // [rsp+70h] [rbp+17h] BYREF
  int v52; // [rsp+C8h] [rbp+6Fh] BYREF
  int v53; // [rsp+D0h] [rbp+77h] BYREF
  int v54; // [rsp+D8h] [rbp+7Fh] BYREF

  v3 = sub_18003A810(168);
  v4 = *(char **)(a2 + 40);
  v5 = v3;
  v6 = *(_DWORD *)(a2 + 100);
  v7 = *v4;
  if ( *v4 == 49 )
  {
    if ( v4[1] || v4[2] )
      goto LABEL_99;
    if ( !v4[3] )
      goto LABEL_21;
  }
  if ( v7 == 116 )
  {
    if ( v4[1] != 121 )
      goto LABEL_18;
    if ( v4[2] != 112 )
    {
LABEL_99:
      if ( v5 )
        sub_18003A8D0((LPVOID)v5);
      sub_180049A30("stbtt_GetFontOffsetForIndex(): FontData is incorrect, or FontNo cannot be found.");
      return 0;
    }
    if ( v4[3] == 49 )
    {
LABEL_21:
      v8 = -(v6 != 0);
      goto LABEL_28;
    }
  }
  if ( v7 == 79 )
  {
    if ( v4[1] != 84 || v4[2] != 84 )
      goto LABEL_99;
    if ( v4[3] == 79 )
      goto LABEL_21;
  }
  if ( !v7 )
  {
    if ( v4[1] != 1 || v4[2] )
      goto LABEL_99;
    if ( !v4[3] )
      goto LABEL_21;
  }
  if ( v7 != 116 )
    goto LABEL_99;
LABEL_18:
  if ( v4[1] == 114 && v4[2] == 117 && v4[3] == 101 )
    goto LABEL_21;
  if ( v4[1] != 116
    || v4[2] != 99
    || v4[3] != 102
    || ((_byteswap_ulong(*((_DWORD *)v4 + 1)) - 0x10000) & 0xFFFEFFFF) != 0
    || v6 >= ((unsigned __int8)v4[11]
            | (((unsigned __int8)v4[10] | (((unsigned __int8)v4[9] | ((unsigned __int8)v4[8] << 8)) << 8)) << 8)) )
  {
    goto LABEL_99;
  }
  v8 = _byteswap_ulong(*(_DWORD *)&v4[4 * v6 + 12]);
LABEL_28:
  if ( (v8 & 0x80000000) != 0 )
    goto LABEL_99;
  *(_QWORD *)(v5 + 8) = v4;
  *(_DWORD *)(v5 + 16) = v8;
  *(_QWORD *)(v5 + 64) = 0;
  *(_QWORD *)(v5 + 72) = 0;
  v9 = (unsigned int)sub_180055450(v4, v8, "cmap");
  v54 = sub_180055450(v4, v8, "loca");
  *(_DWORD *)(v5 + 24) = v54;
  v10 = sub_180055450(v4, v8, "head");
  *(_DWORD *)(v5 + 28) = v10;
  v11 = v10;
  v53 = sub_180055450(v4, v8, "glyf");
  *(_DWORD *)(v5 + 32) = v53;
  v12 = sub_180055450(v4, v8, "hhea");
  *(_DWORD *)(v5 + 36) = v12;
  v13 = v12;
  v52 = sub_180055450(v4, v8, "hmtx");
  *(_DWORD *)(v5 + 40) = v52;
  *(_DWORD *)(v5 + 44) = sub_180055450(v4, v8, "kern");
  *(_DWORD *)(v5 + 48) = sub_180055450(v4, v8, "GPOS");
  if ( !(_DWORD)v9 || !v11 || !v13 || !v52 )
  {
LABEL_35:
    if ( v5 )
      sub_18003A8D0((LPVOID)v5);
    sub_180049A30("stbtt_InitFont(): failed to parse FontData. It is correct and complete? Check FontDataSize.");
    return 0;
  }
  if ( v53 )
  {
    if ( !v54 )
      goto LABEL_35;
  }
  else
  {
    v53 = 2;
    v54 = 0;
    v45 = 0;
    v46[0] = 0;
    v15 = sub_180055450(v4, v8, "CFF ");
    if ( !v15 )
      goto LABEL_35;
    *(_QWORD *)(v5 + 128) = 0;
    *(_QWORD *)(v5 + 136) = 0;
    *(_QWORD *)(v5 + 144) = 0;
    *(_QWORD *)(v5 + 152) = 0;
    *(_QWORD *)(v5 + 64) = &v4[v15];
    *(_DWORD *)(v5 + 76) = 0x20000000;
    v16 = *(_OWORD *)(v5 + 64);
    v17 = *(_DWORD *)(v5 + 72) + 2;
    v18 = HIDWORD(*(_QWORD *)(v5 + 72));
    v19 = *(_DWORD *)(v5 + 76);
    v48 = v16;
    if ( v17 > (int)v18 || v17 < 0 || v17 >= v19 )
      v20 = 0;
    else
      v20 = *(_BYTE *)(v17 + (_QWORD)v16);
    if ( v20 <= v19 )
      v19 = v20;
    DWORD2(v48) = v19;
    sub_180054E40(&v51, &v48);
    v50 = *(_OWORD *)sub_180054E40(&v51, &v48);
    v47 = *(_OWORD *)sub_180055320(&v51, &v50, 0);
    sub_180054E40(&v51, &v48);
    *(_OWORD *)(v5 + 96) = *(_OWORD *)sub_180054E40(&v51, &v48);
    sub_180054F50(&v47, 17, 1, &v54);
    sub_180054F50(&v47, 262, 1, &v53);
    sub_180054F50(&v47, 292, 1, &v45);
    sub_180054F50(&v47, 293, 1, v46);
    v21 = v48;
    v51 = v47;
    v50 = v48;
    v52 = 0;
    *(_QWORD *)&v47 = 0;
    sub_180054F50(&v51, 18, 2, &v47);
    v22 = DWORD1(v47);
    v23 = HIDWORD(v21);
    if ( !DWORD1(v47) )
      goto LABEL_59;
    v24 = v47;
    if ( !(_DWORD)v47 )
      goto LABEL_59;
    if ( SDWORD1(v47) < 0 || (int)v47 < 0 || SDWORD1(v47) > SHIDWORD(v21) || (int)v47 > HIDWORD(v21) - DWORD1(v47) )
    {
      v24 = 0;
      v25 = 0;
    }
    else
    {
      v25 = SDWORD1(v47) + (_QWORD)v21;
    }
    *(_QWORD *)&v47 = v25;
    HIDWORD(v47) = v24;
    DWORD2(v47) = 0;
    sub_180054F50(&v47, 19, 1, &v52);
    if ( v52 )
    {
      if ( v22 + v52 > SHIDWORD(v21) || (DWORD2(v50) = v22 + v52, v22 + v52 < 0) )
        DWORD2(v50) = HIDWORD(v21);
      sub_180054E40(&v49, &v50);
    }
    else
    {
LABEL_59:
      v49 = 0u;
    }
    v26 = v53 == 2;
    *(_OWORD *)(v5 + 112) = v49;
    if ( !v26 )
      goto LABEL_35;
    v27 = v54;
    v52 = v54;
    if ( !v54 )
      goto LABEL_35;
    if ( v45 )
    {
      v28 = v46[0];
      if ( !v46[0] )
        goto LABEL_35;
      if ( v45 > SHIDWORD(v21) || (DWORD2(v48) = v45, v45 < 0) )
        DWORD2(v48) = HIDWORD(v21);
      v29 = (_OWORD *)sub_180054E40(&v51, &v48);
      v23 = HIDWORD(v48);
      *(_OWORD *)(v5 + 128) = *v29;
      if ( (int)v28 < 0 || (v30 = v23 - v28, v23 - (int)v28 < 0) || (int)v28 > v23 )
      {
        v30 = 0;
        v31 = 0;
      }
      else
      {
        v31 = v48 + v28;
      }
      *(_QWORD *)(v5 + 144) = v31;
      *(_DWORD *)(v5 + 152) = 0;
      *(_DWORD *)(v5 + 156) = v30;
      v27 = v52;
    }
    if ( v27 > v23 || (DWORD2(v48) = v27, v27 < 0) )
      DWORD2(v48) = v23;
    *(_OWORD *)(v5 + 80) = *(_OWORD *)sub_180054E40(&v51, &v48);
  }
  v32 = sub_180055450(v4, v8, "maxp");
  if ( v32 )
    v33 = ((unsigned __int8)v4[v32 + 4] << 8) | (unsigned __int8)v4[v32 + 5];
  else
    v33 = 0xFFFF;
  *(_DWORD *)(v5 + 20) = v33;
  v34 = 0;
  *(_DWORD *)(v5 + 52) = -1;
  v35 = (unsigned __int8)v4[v9 + 3];
  v26 = (v35 | ((unsigned __int8)v4[v9 + 2] << 8)) == 0;
  v36 = v35 | ((unsigned __int8)v4[v9 + 2] << 8);
  *(_DWORD *)(v5 + 56) = 0;
  if ( !v26 )
  {
    do
    {
      v37 = (unsigned int)(v9 + 4 + 8 * v34);
      v38 = (unsigned __int8)v4[v37 + 1] | ((unsigned __int8)v4[v37] << 8);
      if ( !v38
        || v38 == 3
        && (((unsigned __int8)v4[v37 + 3] | ((unsigned __int8)v4[v37 + 2] << 8)) == 1
         || ((unsigned __int8)v4[v37 + 3] | ((unsigned __int8)v4[v37 + 2] << 8)) == 0xA) )
      {
        *(_DWORD *)(v5 + 56) = v9 + _byteswap_ulong(*(_DWORD *)&v4[v37 + 4]);
      }
      ++v34;
    }
    while ( v34 < v36 );
  }
  if ( !*(_DWORD *)(v5 + 56) )
    goto LABEL_35;
  *(_DWORD *)(v5 + 60) = (unsigned __int8)v4[*(int *)(v5 + 28) + 51]
                       | ((unsigned __int8)v4[*(int *)(v5 + 28) + 50] << 8);
  v26 = *(_BYTE *)(a2 + 53) == 0;
  v39 = *(_QWORD *)(a2 + 120);
  *(_QWORD *)(a2 + 136) = v5;
  v40 = *(float *)(**(_QWORD **)(v39 + 40) + 60LL);
  if ( !v26 && *(float *)(a2 + 60) == 0.0 )
    *(float *)(a2 + 60) = v40;
  v41 = *(_QWORD *)(v5 + 8);
  if ( *(float *)(a2 + 60) < 0.0 )
    v42 = _mm_cvtsi32_si128(
            *(unsigned __int8 *)(*(int *)(v5 + 28) + v41 + 19)
          | (*(unsigned __int8 *)(*(int *)(v5 + 28) + v41 + 18) << 8));
  else
    v42 = _mm_cvtsi32_si128(
            (__int16)_byteswap_ushort(*(_WORD *)(v41 + *(int *)(v5 + 36) + 4))
          - (__int16)_byteswap_ushort(*(_WORD *)(v41 + *(int *)(v5 + 36) + 6)));
  v43 = 1.0 / _mm_cvtepi32_ps(v42).m128_f32[0];
  *(float *)(v5 + 160) = v43;
  if ( *(_BYTE *)(a2 + 53) )
  {
    v44 = *(float *)(a2 + 60);
    if ( v44 != 0.0 && v40 != 0.0 )
      *(float *)(v5 + 160) = (float)(v44 / v40) * v43;
  }
  return 1;
}
