// sub_18004E8F0 size=2593
char __fastcall sub_18004E8F0(__int64 a1, __int64 a2, __int64 a3, __m128i *p_si128)
{
  __int64 v4; // rbx
  unsigned int v5; // ebp
  bool v6; // zf
  char v7; // di
  __int64 v8; // r9
  char v9; // r15
  __int64 v10; // r9
  __int64 v11; // rdx
  __int64 v12; // rax
  __int64 v13; // rax
  char v14; // al
  char v15; // al
  bool v16; // r13
  int v17; // r12d
  __int64 v18; // rcx
  __int64 v19; // rax
  __int64 v20; // rax
  __int64 v21; // rax
  int *v22; // rdi
  char v23; // al
  int v24; // esi
  __int64 v25; // rax
  __int64 v26; // rdi
  unsigned int v27; // r14d
  int v28; // r9d
  _BYTE *v29; // rbp
  unsigned int v30; // r8d
  unsigned int v31; // r8d
  char v32; // r15
  char v33; // r14
  char v34; // bp
  char v35; // cl
  int v36; // eax
  __int64 v37; // rax
  float v38; // xmm0_4
  float v39; // xmm1_4
  int v40; // eax
  __int64 v41; // rdi
  __int64 v42; // rsi
  char v43; // al
  int *v44; // rax
  __int64 v45; // rcx
  float v46; // xmm2_4
  float v47; // xmm3_4
  int v48; // edx
  float v49; // xmm1_4
  float v50; // xmm0_4
  char v51; // dl
  float v52; // xmm0_4
  float v53; // xmm1_4
  int v54; // xmm0_4
  int v55; // xmm1_4
  __m128i si128; // [rsp+20h] [rbp-88h] BYREF
  __int64 v58; // [rsp+30h] [rbp-78h]
  int v59; // [rsp+38h] [rbp-70h]
  char v60; // [rsp+3Ch] [rbp-6Ch] BYREF
  _OWORD v61[2]; // [rsp+40h] [rbp-68h] BYREF
  __int128 v62; // [rsp+60h] [rbp-48h] BYREF
  char v63; // [rsp+B0h] [rbp+8h] BYREF
  char v64; // [rsp+B8h] [rbp+10h]

  v4 = qword_18010C470;
  v5 = 3;
  v6 = (*(_BYTE *)(qword_18010C470 + 8) & 2) == 0;
  *(_BYTE *)(qword_18010C470 + 179) = 0;
  if ( v6 || (*(_BYTE *)(v4 + 12) & 1) == 0 )
  {
    v7 = 0;
    v63 = 0;
  }
  else
  {
    p_si128 = (__m128i *)v61;
    v7 = 1;
    v61[0] = _mm_load_si128((const __m128i *)&xmmword_1800E6900);
    v63 = 1;
    v61[1] = _mm_load_si128((const __m128i *)&xmmword_1800E6910);
    do
    {
      if ( (unsigned __int8)sub_180046CF0(p_si128->m128i_u32[0]) )
        *(_DWORD *)(v4 + 8184) = 3;
      p_si128 = (__m128i *)(v8 + 4);
    }
    while ( p_si128 != (__m128i *)&v62 );
  }
  v9 = *(_BYTE *)(v4 + 8) & 1;
  v64 = v9;
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E68D0);
  v58 = 0x20300000201LL;
  v59 = 516;
  if ( v9 )
  {
    p_si128 = &si128;
    do
    {
      if ( (unsigned __int8)sub_180046CF0(p_si128->m128i_u32[0]) )
        *(_DWORD *)(v4 + 8184) = 2;
      p_si128 = (__m128i *)(v10 + 4);
    }
    while ( p_si128 != (__m128i *)&v60 );
  }
  v11 = *(unsigned int *)(v4 + 8216);
  *(_QWORD *)(v4 + 8560) = 0;
  *(_DWORD *)(v4 + 8568) = 0;
  if ( (_DWORD)v11 )
  {
    p_si128 = *(__m128i **)(v4 + 8120);
    if ( p_si128 )
    {
      if ( *(_DWORD *)(v4 + 8116) != (_DWORD)v11 )
      {
        *(_DWORD *)(v4 + 8560) = *(_DWORD *)(v4 + 8128);
        *(_DWORD *)(v4 + 8564) = v11;
        *(_DWORD *)(v4 + 8568) = *(_DWORD *)(v4 + 8220);
        *(_DWORD *)(v4 + 8572) = 0;
        *(_BYTE *)(v4 + 8576) = 0;
        *(_BYTE *)(v4 + 8577) = (*(_DWORD *)(v4 + 8240) & 0x200000) != 0;
      }
      if ( (*(_BYTE *)(v4 + 10228) & 0x10) != 0 )
        sub_180052F00(
          "[nav] NavInitRequest: ApplyResult: NavID 0x%08X in Layer %d Window \"%s\"\n",
          v11,
          *(_DWORD *)(v4 + 8132),
          (const char *)p_si128->m128i_i64[1]);
      sub_18004DA70(*(unsigned int *)(v4 + 8216), *(unsigned int *)(v4 + 8132), *(unsigned int *)(v4 + 8220), v4 + 8224);
      *(_BYTE *)(v4 + 8115) = 1;
      v12 = *(_QWORD *)(v4 + 8256);
      if ( v12 != -1 )
        *(_QWORD *)(v4 + 0x2000) = v12;
      if ( *(_BYTE *)(v4 + 8203) )
      {
        v13 = qword_18010C470;
        if ( *(_BYTE *)(qword_18010C470 + 86) )
          *(_BYTE *)(qword_18010C470 + 8112) = 1;
        *(_WORD *)(v13 + 8113) = 257;
      }
    }
  }
  *(_WORD *)(v4 + 8202) = 0;
  *(_DWORD *)(v4 + 8216) = 0;
  if ( *(_BYTE *)(v4 + 8264) )
    sub_18004FA90(a1, v11, a3, p_si128, si128.m128i_i64[0], si128.m128i_i64[1], v58, v59);
  v14 = *(_BYTE *)(v4 + 8200);
  *(_DWORD *)(v4 + 8332) = 0;
  *(_WORD *)(v4 + 8264) = 0;
  if ( v14 > 0 )
  {
    v15 = v14 - 1;
    *(_BYTE *)(v4 + 8200) = v15;
    if ( !v15 )
      *(_BYTE *)(v4 + 8112) = 1;
  }
  v16 = 0;
  v17 = 1;
  if ( *(_BYTE *)(v4 + 8114) && *(_BYTE *)(v4 + 8115) && *(_BYTE *)(v4 + 8112) && *(_BYTE *)(v4 + 8113) )
    v16 = *(_QWORD *)(v4 + 8120) != 0;
  v18 = *(_QWORD *)(v4 + 8120);
  *(_BYTE *)(v4 + 8114) = 0;
  if ( v18 )
  {
    v19 = v18;
    while ( *(_QWORD *)(v19 + 960) != v19 && (*(_DWORD *)(v19 + 20) & 0x14000000) == 0 )
    {
      v19 = *(_QWORD *)(v19 + 944);
      if ( !v19 )
        goto LABEL_44;
    }
    if ( v19 != v18 )
      *(_QWORD *)(v19 + 1000) = v18;
  }
LABEL_44:
  v20 = *(_QWORD *)(v4 + 8120);
  if ( v20 && *(_QWORD *)(v20 + 1000) && !*(_DWORD *)(v4 + 8132) )
    *(_QWORD *)(v20 + 1000) = 0;
  sub_180050760();
  if ( (v9 || v7) && (v21 = *(_QWORD *)(v4 + 8120)) != 0 && (*(_DWORD *)(v21 + 20) & 0x10000) == 0 )
  {
    v22 = (int *)(v4 + 8116);
    *(_BYTE *)(v4 + 181) = 1;
    if ( *(_DWORD *)(v4 + 8116) && *(_BYTE *)(v4 + 8112) )
      goto LABEL_54;
  }
  else
  {
    *(_BYTE *)(v4 + 181) = 0;
    v22 = (int *)(v4 + 8116);
  }
  if ( !*(_QWORD *)(v4 + 8592) )
  {
    v23 = 0;
    goto LABEL_55;
  }
LABEL_54:
  v23 = 1;
  v22 = (int *)(v4 + 8116);
LABEL_55:
  *(_BYTE *)(v4 + 182) = v23;
  sub_18004FED0();
  v24 = *v22;
  *(_QWORD *)(v4 + 8140) = 0;
  *(_DWORD *)(v4 + 8136) = 0;
  *(_DWORD *)(v4 + 8148) = 0;
  if ( v24 )
  {
    if ( *(_BYTE *)(v4 + 8112) )
    {
      if ( !*(_QWORD *)(v4 + 8592) )
      {
        v25 = *(_QWORD *)(v4 + 8120);
        if ( v25 )
        {
          if ( (*(_DWORD *)(v25 + 20) & 0x10000) == 0 )
          {
            v26 = qword_18010C470;
            v27 = 637;
            v28 = 635;
            if ( v9
              && *(_BYTE *)(qword_18010C470 + 452)
              && (!*(_BYTE *)(qword_18010C470 + 7668) || *(_DWORD *)(qword_18010C470 + 5332) == -1)
              && *(_DWORD *)(qword_18010C470 + 5604) == -1 )
            {
              v29 = (_BYTE *)(v4 + 81);
            }
            else
            {
              if ( !v63 )
                goto LABEL_82;
              v29 = (_BYTE *)(v4 + 81);
              v30 = 637;
              if ( *(_BYTE *)(v4 + 81) )
                v30 = 635;
              if ( !*(_BYTE *)sub_180034F60(v30) || !(unsigned __int8)sub_180048B00(v31, 0xFFFFFFFFLL) )
              {
LABEL_82:
                v32 = 0;
                goto LABEL_83;
              }
            }
            v32 = 1;
            if ( v64 )
            {
              if ( (unsigned __int8)sub_180046DB0(524, 0, 0xFFFFFFFFLL) )
              {
LABEL_81:
                v33 = 1;
                goto LABEL_84;
              }
              v28 = 635;
            }
            if ( v63 )
            {
              if ( *v29 )
                v27 = v28;
              if ( (unsigned __int8)sub_180046DB0(v27, 0, 0xFFFFFFFFLL) )
                goto LABEL_81;
            }
LABEL_83:
            v33 = 0;
LABEL_84:
            if ( v64
              && (*(_BYTE *)(v26 + 468)
               && (!*(_BYTE *)(v26 + 7668) || *(_DWORD *)(v26 + 5332) == -1)
               && *(_DWORD *)(v26 + 5616) == -1
               || *(_BYTE *)(v26 + 2100)
               && (!*(_BYTE *)(v26 + 7668) || *(_DWORD *)(v26 + 5332) == -1)
               && *(_DWORD *)(v26 + 6840) == -1)
              || v63 && *(_BYTE *)(v26 + 2244) && *(_DWORD *)(v26 + 6948) == -1 )
            {
              v34 = 1;
              if ( v64
                && ((unsigned __int8)sub_180046DB0(525, 0, 0xFFFFFFFFLL)
                 || (unsigned __int8)sub_180046DB0(627, 0, 0xFFFFFFFFLL))
                || v63 && (unsigned __int8)sub_180046DB0(636, 0, 0xFFFFFFFFLL) )
              {
                v35 = 1;
                goto LABEL_104;
              }
            }
            else
            {
              v34 = 0;
            }
            v35 = 0;
LABEL_104:
            v36 = *(_DWORD *)(v4 + 5332);
            if ( v36 )
            {
              if ( v36 != v24 )
              {
LABEL_120:
                v9 = v64;
                v5 = 3;
                goto LABEL_121;
              }
            }
            else if ( v33 )
            {
              *(_DWORD *)(v4 + 8136) = v24;
              *(_DWORD *)(v4 + 8148) = 2;
            }
            if ( v35 )
            {
              *(_DWORD *)(v4 + 8136) = v24;
              *(_DWORD *)(v4 + 8148) = 1;
            }
            if ( !v36 || v36 == v24 )
            {
              if ( v32 || v34 )
                *(_DWORD *)(v4 + 8140) = v24;
              if ( (!v36 || v36 == v24) && (v33 || v35) )
              {
                *(_DWORD *)(v4 + 8144) = v24;
                *(_DWORD *)(v26 + 8168) = v24;
                *(_DWORD *)(v26 + 8172) = 1036831949;
              }
            }
            goto LABEL_120;
          }
        }
      }
    }
  }
LABEL_121:
  v37 = *(_QWORD *)(v4 + 8120);
  if ( v37 && (*(_DWORD *)(v37 + 20) & 0x10000) != 0 )
  {
    *(_BYTE *)(v4 + 8112) = 0;
  }
  else if ( *(_BYTE *)(v4 + 87) && !*(_BYTE *)(v4 + 8200) )
  {
    *(_BYTE *)(v4 + 8112) = 1;
  }
  v38 = *(float *)(v4 + 8172);
  if ( v38 <= 0.0 )
  {
    v39 = *(float *)(v4 + 8172);
  }
  else
  {
    v39 = fmaxf(0.0, v38 - *(float *)(v4 + 32));
    *(float *)(v4 + 8172) = v39;
  }
  if ( v39 == 0.0 )
    *(_DWORD *)(v4 + 8168) = 0;
  v40 = *(_DWORD *)(v4 + 8176);
  if ( v40 )
  {
    *(_DWORD *)(v4 + 8144) = v40;
    *(_DWORD *)(v4 + 8140) = v40;
    *(_DWORD *)(v4 + 8136) = v40;
    *(_DWORD *)(v4 + 8148) = *(_DWORD *)(v4 + 8180);
  }
  *(_DWORD *)(v4 + 8176) = 0;
  sub_18004F320();
  v41 = qword_18010C470;
  if ( *(_DWORD *)(v4 + 8280) == -1 )
  {
    v42 = *(_QWORD *)(qword_18010C470 + 8120);
    if ( v42 )
    {
      if ( !*(_QWORD *)(qword_18010C470 + 8592)
        && (*(_DWORD *)(v42 + 20) & 0x10000) == 0
        && (unsigned __int8)sub_180046DB0(512, 1, 0xFFFFFFFFLL)
        && !*(_BYTE *)(v41 + 252)
        && !*(_BYTE *)(v41 + 254) )
      {
        v43 = *(_BYTE *)(v41 + 253);
        if ( (*(_BYTE *)(v41 + 8) & 1) != 0 )
        {
          if ( v43 )
          {
            v17 = -1;
          }
          else if ( !*(_BYTE *)(v41 + 8112) && !*(_DWORD *)(v41 + 5332) )
          {
            v17 = 0;
          }
        }
        else if ( v43 )
        {
          v17 = -1;
        }
        else
        {
          v17 = *(_DWORD *)(v41 + 5332) != 0;
        }
        *(_DWORD *)(v41 + 8328) = v17;
        if ( *(_BYTE *)(v42 + 211) )
          v5 = 33;
        sub_18004E030(0xFFFFFFFFLL, (unsigned int)((v17 >> 31) + 3), 5120, v5);
        *(_DWORD *)(v41 + 8332) = -1;
      }
    }
  }
  LOBYTE(v44) = *(_BYTE *)(v41 + 8265) || *(_BYTE *)(v41 + 8202);
  *(_BYTE *)(v41 + 8201) = (_BYTE)v44;
  v45 = *(_QWORD *)(v4 + 8120);
  *(_BYTE *)(v4 + 8115) = 0;
  if ( !v45 || (*(_DWORD *)(v45 + 20) & 0x10000) != 0 || *(_QWORD *)(v4 + 8592) )
  {
    v51 = v63;
    goto LABEL_185;
  }
  v46 = 1.0;
  LODWORD(v44) = (int)(float)((float)((float)(*(float *)(v45 + 704) * 100.0) * *(float *)(v4 + 32)) + 0.5);
  v47 = (float)(int)v44;
  if ( *(_WORD *)(v45 + 372) )
    goto LABEL_172;
  if ( !*(_BYTE *)(v45 + 378) )
    goto LABEL_172;
  v48 = *(_DWORD *)(v4 + 8280);
  if ( v48 == -1 )
    goto LABEL_172;
  v49 = -1.0;
  if ( !v48 )
  {
    v50 = -1.0;
    goto LABEL_167;
  }
  if ( v48 == 1 )
  {
    v50 = 1.0;
LABEL_167:
    *(_DWORD *)(v45 + 176) = 0;
    *(_DWORD *)(v45 + 184) = 0;
    LODWORD(v44) = (int)(float)((float)(v50 * v47) + *(float *)(v45 + 152));
    *(float *)(v45 + 168) = (float)(int)v44;
  }
  if ( v48 != 2 )
  {
    if ( v48 != 3 )
      goto LABEL_172;
    v49 = 1.0;
  }
  *(_DWORD *)(v45 + 180) = 0;
  *(_DWORD *)(v45 + 188) = 0;
  LODWORD(v44) = (int)(float)((float)(v49 * v47) + *(float *)(v45 + 156));
  *(float *)(v45 + 172) = (float)(int)v44;
LABEL_172:
  v51 = v63;
  if ( v63 )
  {
    v52 = *(float *)(v41 + 2464) - *(float *)(v41 + 2448);
    v53 = *(float *)(v41 + 2496) - *(float *)(v41 + 2480);
    if ( !*(_BYTE *)(v41 + 2340) || *(_BYTE *)(v41 + 7028) )
    {
      if ( *(_BYTE *)(v41 + 2356) && !*(_BYTE *)(v41 + 7040) )
        v46 = 10.0;
    }
    else
    {
      v46 = 0.1;
    }
    if ( v52 != 0.0 && *(_BYTE *)(v45 + 200) )
    {
      *(_DWORD *)(v45 + 176) = 0;
      *(_DWORD *)(v45 + 184) = 0;
      LODWORD(v44) = (int)(float)((float)((float)(v52 * v47) * v46) + *(float *)(v45 + 152));
      *(float *)(v45 + 168) = (float)(int)v44;
    }
    if ( v53 != 0.0 )
    {
      *(_DWORD *)(v45 + 180) = 0;
      *(_DWORD *)(v45 + 188) = 0;
      LODWORD(v44) = (int)(float)((float)((float)(v53 * v47) * v46) + *(float *)(v45 + 156));
      *(float *)(v45 + 172) = (float)(int)v44;
    }
  }
LABEL_185:
  if ( !v9 && !v51 )
  {
    *(_WORD *)(v4 + 8112) = 0;
    v16 = 0;
  }
  if ( v16 && *(_BYTE *)(v4 + 82) && (*(_BYTE *)(v4 + 12) & 4) != 0 )
  {
    v44 = (int *)sub_18004E470(&v63);
    v54 = *v44;
    v55 = v44[1];
    *(_DWORD *)(v41 + 2744) = *v44;
    *(_DWORD *)(v41 + 2748) = v55;
    *(_DWORD *)(v41 + 224) = v54;
    *(_DWORD *)(v41 + 228) = v55;
    *(_QWORD *)(v41 + 204) = 0;
    *(_BYTE *)(v41 + 179) = 1;
  }
  *(_DWORD *)(v4 + 8324) = 0;
  return (char)v44;
}
