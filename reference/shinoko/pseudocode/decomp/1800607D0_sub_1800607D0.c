// sub_1800607D0 size=2103
__int64 __fastcall sub_1800607D0(__int64 a1, unsigned int a2, unsigned int a3)
{
  __int64 v5; // r15
  __int64 v6; // r13
  __int64 v7; // rax
  __int64 v8; // rsi
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v12; // r8d
  int v13; // ebp
  int v14; // r8d
  int v15; // eax
  int v16; // r14d
  void *v17; // rcx
  int v18; // ecx
  int v19; // eax
  __int64 v20; // rax
  __int64 v21; // r8
  __int64 v22; // r14
  int v23; // r12d
  int v24; // ecx
  int v25; // eax
  __int64 v26; // rax
  __int64 v27; // rbp
  __int64 v28; // rdx
  unsigned __int64 v29; // r9
  __m128i v30; // xmm4
  int v31; // ebp
  int v32; // r11d
  signed int v33; // r8d
  signed int v34; // r10d
  __m128i si128; // xmm5
  double v36; // xmm3_8
  __m128i v37; // xmm1
  __m128i v38; // xmm2
  __int64 v39; // rcx
  __m128i v40; // xmm2
  __m128i v41; // xmm2
  __m128i v42; // xmm2
  _DWORD *v43; // r14
  _DWORD *v44; // r12
  __int64 v45; // rax
  __int64 v46; // rcx
  __int64 v47; // rbp
  int v48; // eax
  __int64 v49; // r8
  __int64 v50; // rdx
  __int64 v51; // rax
  int v52; // edx
  int v53; // eax
  __int64 v54; // rdx
  __int64 v55; // rcx
  __int64 v56; // r10
  __int64 i; // r11
  int v58; // ecx
  __int64 v59; // rdx
  __int64 v60; // r9
  __int64 v61; // r8
  __int64 result; // rax
  __int64 v63; // rcx
  __int64 v64; // rdx
  _QWORD *v65; // rcx
  _DWORD *v66; // rax
  __m128i v67; // [rsp+40h] [rbp-88h] BYREF
  __m128i v68; // [rsp+50h] [rbp-78h] BYREF
  __m128i v69; // [rsp+60h] [rbp-68h] BYREF
  __m128i v70[5]; // [rsp+70h] [rbp-58h] BYREF
  int v71; // [rsp+D0h] [rbp+8h]
  __int32 v72; // [rsp+D0h] [rbp+8h]
  __int64 v75; // [rsp+E8h] [rbp+20h]
  __int32 v76; // [rsp+E8h] [rbp+20h]

  v5 = *(_QWORD *)(a1 + 688);
  *(_BYTE *)(v5 + 184) = 1;
  v6 = *(_QWORD *)(a1 + 56);
  v7 = sub_18003A810(88);
  v8 = v7;
  v9 = 0;
  if ( v7 )
  {
    *(_QWORD *)(v7 + 64) = 0;
    *(_QWORD *)(v7 + 72) = 0;
    *(_OWORD *)v7 = 0;
    *(_OWORD *)(v7 + 16) = 0;
    *(_OWORD *)(v7 + 32) = 0;
    *(_OWORD *)(v7 + 48) = 0;
    *(_OWORD *)(v7 + 64) = 0;
    *(_QWORD *)(v7 + 80) = 0;
    *(_DWORD *)(v7 + 4) = 1;
    *(_QWORD *)(v7 + 16) = 0;
  }
  else
  {
    v8 = 0;
  }
  v10 = *(_DWORD *)(a1 + 664);
  *(_DWORD *)(a1 + 664) = v10 + 1;
  *(_DWORD *)v8 = v10;
  v11 = *(_DWORD *)(a1 + 68);
  v12 = *(_DWORD *)(a1 + 64);
  v13 = 8;
  if ( v12 == v11 )
  {
    v14 = v12 + 1;
    if ( v11 )
      v15 = v11 + v11 / 2;
    else
      v15 = 8;
    if ( v15 > v14 )
      v14 = v15;
    sub_180054080(a1 + 64, (unsigned int)v14);
  }
  *(_QWORD *)(*(_QWORD *)(a1 + 72) + 8LL * (int)(*(_DWORD *)(a1 + 64))++) = v8;
  if ( v6 )
    *(_BYTE *)(v6 + 87) = 1;
  v16 = *(_DWORD *)(a1 + 4);
  v17 = *(void **)(v8 + 40);
  if ( v17 )
    sub_18003A8D0(v17);
  *(_QWORD *)(v8 + 40) = 0;
  *(_DWORD *)(v8 + 24) = v16;
  *(_DWORD *)(v8 + 4) = 2;
  *(_DWORD *)(v8 + 28) = a2;
  *(_DWORD *)(v8 + 32) = a3;
  if ( v16 )
  {
    if ( v16 == 1 )
    {
      v18 = 1;
      v19 = a2;
    }
    else
    {
      v18 = 0;
      v19 = 0;
    }
  }
  else
  {
    v18 = 4;
    v19 = 4 * a2;
  }
  *(_DWORD *)(v8 + 36) = v18;
  *(_BYTE *)(v8 + 86) = 0;
  v20 = sub_18003A810((int)(a3 * v19));
  *(_QWORD *)(v8 + 40) = v20;
  sub_1800B9280(v20, 0, *(_DWORD *)(v8 + 28) * *(_DWORD *)(v8 + 32) * *(_DWORD *)(v8 + 36));
  *(_QWORD *)(v8 + 48) = 0;
  *(_DWORD *)(v8 + 56) = -1;
  *(_DWORD *)(v8 + 60) = 0;
  *(_BYTE *)(a1 + 82) = 0;
  sub_1800603D0(a1, v8);
  *(_BYTE *)(v8 + 86) = *(_BYTE *)(v6 + 86);
  if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
    sub_180052F00(
      "[font] Texture #%03d: resize+repack %dx%d => Texture #%03d: %dx%d\n",
      *(_DWORD *)v6,
      *(_DWORD *)(v6 + 28),
      *(_DWORD *)(v6 + 32),
      *(_DWORD *)v8,
      *(_DWORD *)(v8 + 28),
      *(_DWORD *)(v8 + 32));
  v21 = *(_QWORD *)(a1 + 56);
  v75 = v21;
  v22 = *(_QWORD *)(a1 + 688);
  v23 = *(_DWORD *)(v21 + 28) / 2;
  v24 = *(_DWORD *)(v22 + 84);
  if ( v23 > v24 )
  {
    if ( v24 )
      v13 = v24 + v24 / 2;
    v25 = *(_DWORD *)(v21 + 28) / 2;
    if ( v13 > v23 )
      v25 = v13;
    v71 = v25;
    if ( v25 > v24 )
    {
      v26 = sub_18003A810(16LL * v25);
      v27 = v26;
      v28 = *(_QWORD *)(v22 + 88);
      if ( v28 )
      {
        sub_1800B8BD0(v26, v28, 16LL * *(int *)(v22 + 80));
        sub_18003A8D0(*(LPVOID *)(v22 + 88));
      }
      *(_QWORD *)(v22 + 88) = v27;
      *(_DWORD *)(v22 + 84) = v71;
      v21 = v75;
    }
  }
  *(_DWORD *)(v22 + 80) = v23;
  v29 = *(_QWORD *)(v22 + 88);
  v30 = _mm_unpacklo_epi64((__m128i)v29, (__m128i)v29);
  v31 = *(_DWORD *)(v21 + 32);
  v32 = *(_DWORD *)(v21 + 28);
  v33 = 0;
  v34 = v23 - 1;
  if ( v23 - 1 > 0 )
  {
    if ( (unsigned int)v34 < 8 )
      goto LABEL_69;
    if ( dword_1800FA030 < 2 )
      goto LABEL_69;
    si128 = _mm_load_si128((const __m128i *)&xmmword_1800E68A0);
    do
    {
      v36 = *(double *)_mm_move_epi64(si128).m128i_i64;
      v37.m128i_i64[1] = _mm_load_si128(&v69).m128i_i64[1];
      *(double *)v37.m128i_i64 = v36;
      v69 = v37;
      v38 = _mm_add_epi64(
              _mm_slli_epi64(
                _mm_cvtepi32_epi64(_mm_move_epi64(_mm_add_epi32(v37, _mm_shuffle_epi32(_mm_cvtsi32_si128(v33 + 1), 0)))),
                4u),
              v30);
      v39 = 2LL * v33;
      *(_QWORD *)(v29 + 8 * v39 + 8) = v38.m128i_i64[0];
      *(_QWORD *)(v29 + 8 * v39 + 24) = _mm_srli_si128(v38, 8).m128i_u64[0];
      v37.m128i_i64[1] = _mm_load_si128(&v68).m128i_i64[1];
      *(double *)v37.m128i_i64 = v36;
      v68 = v37;
      v40 = _mm_add_epi64(
              _mm_slli_epi64(
                _mm_cvtepi32_epi64(_mm_move_epi64(_mm_add_epi32(v37, _mm_shuffle_epi32(_mm_cvtsi32_si128(v33 + 3), 0)))),
                4u),
              v30);
      *(_QWORD *)(v29 + 8 * v39 + 40) = v40.m128i_i64[0];
      *(_QWORD *)(v29 + 8 * v39 + 56) = _mm_srli_si128(v40, 8).m128i_u64[0];
      v37.m128i_i64[1] = _mm_load_si128(&v67).m128i_i64[1];
      *(double *)v37.m128i_i64 = v36;
      v67 = v37;
      v41 = _mm_add_epi64(
              _mm_slli_epi64(
                _mm_cvtepi32_epi64(_mm_move_epi64(_mm_add_epi32(v37, _mm_shuffle_epi32(_mm_cvtsi32_si128(v33 + 5), 0)))),
                4u),
              v30);
      *(_QWORD *)(v29 + 8 * v39 + 72) = v41.m128i_i64[0];
      *(_QWORD *)(v29 + 8 * v39 + 88) = _mm_srli_si128(v41, 8).m128i_u64[0];
      v37.m128i_i64[1] = _mm_load_si128(v70).m128i_i64[1];
      *(double *)v37.m128i_i64 = v36;
      v70[0] = v37;
      v42 = _mm_add_epi64(
              _mm_slli_epi64(
                _mm_cvtepi32_epi64(_mm_move_epi64(_mm_add_epi32(v37, _mm_shuffle_epi32(_mm_cvtsi32_si128(v33 + 7), 0)))),
                4u),
              v30);
      *(_QWORD *)(v29 + 8 * v39 + 104) = v42.m128i_i64[0];
      *(_QWORD *)(v29 + 8 * v39 + 120) = _mm_srli_si128(v42, 8).m128i_u64[0];
      v33 += 8;
    }
    while ( v33 < v34 - v34 % 8 );
    if ( v33 < v34 )
    {
LABEL_69:
      do
      {
        *(_QWORD *)(v29 + 16LL * v33 + 8) = v29 + 16LL * (v33 + 1);
        ++v33;
      }
      while ( v33 < v34 );
    }
  }
  *(_QWORD *)(v29 + 16LL * v33 + 8) = 0;
  *(_QWORD *)(v22 + 12) = 1;
  *(_QWORD *)(v22 + 32) = v29;
  *(_QWORD *)(v22 + 24) = v22 + 40;
  *(_DWORD *)v22 = v32;
  *(_DWORD *)(v22 + 4) = v31;
  *(_DWORD *)(v22 + 20) = v23;
  *(_DWORD *)(v22 + 8) = (v32 + v23 - 1) / v23;
  *(_DWORD *)(v22 + 40) = 0;
  *(_DWORD *)(v22 + 44) = 0;
  *(_QWORD *)(v22 + 48) = v22 + 56;
  *(_DWORD *)(v22 + 56) = v32;
  *(_DWORD *)(v22 + 60) = 0x40000000;
  *(_QWORD *)(v22 + 64) = 0;
  *(_QWORD *)(v22 + 148) = 0;
  *(_QWORD *)(v22 + 168) = 0;
  *(_QWORD *)(v22 + 176) = 0;
  v68 = 0u;
  v69 = 0u;
  sub_180068F50(&v69, v5 + 112);
  v72 = *(_DWORD *)(v5 + 96);
  *(_DWORD *)(v5 + 96) = 0;
  v68.m128i_i32[0] = v72;
  v76 = *(_DWORD *)(v5 + 100);
  *(_DWORD *)(v5 + 100) = 0;
  v68.m128i_i32[1] = v76;
  v43 = *(_DWORD **)(v5 + 104);
  *(_QWORD *)(v5 + 104) = 0;
  v68.m128i_i64[1] = (__int64)v43;
  v44 = *(_DWORD **)(v5 + 120);
  v45 = *(int *)(v5 + 112);
  v46 = (__int64)&v44[v45];
  v67.m128i_i64[0] = (__int64)&v44[v45];
  if ( !(v45 * 4) )
  {
LABEL_45:
    *(_QWORD *)(v5 + 156) = 0;
    if ( *(int *)(v5 + 192) > 0 )
    {
      do
      {
        v52 = v9 & 0x1F;
        v53 = v9;
        if ( v9 < 0 )
        {
          v53 = v9 + 31;
          v52 -= 32;
        }
        v54 = 104LL * v52;
        v55 = *(_QWORD *)(*(_QWORD *)(v5 + 208) + 8LL * (v53 >> 5));
        v56 = *(_QWORD *)(v54 + v55 + 56);
        for ( i = v56 + 44LL * *(int *)(v54 + v55 + 48); v56 != i; v56 += 44 )
        {
          v58 = *(_DWORD *)(v56 + 40);
          if ( v58 != -1 )
          {
            v59 = *(_QWORD *)(a1 + 688);
            v60 = (__int64)(int)(*(_DWORD *)(*(_QWORD *)(v59 + 120) + 4LL * (v58 & 0x7FFFF)) << 12) >> 12;
            v61 = *(_QWORD *)(v59 + 104);
            *(float *)(v56 + 24) = (float)*(unsigned __int16 *)(v61 + 8 * v60) * *(float *)(a1 + 84);
            *(float *)(v56 + 28) = (float)*(unsigned __int16 *)(v61 + 8 * v60 + 2) * *(float *)(a1 + 88);
            *(float *)(v56 + 32) = (float)(*(unsigned __int16 *)(v61 + 8 * v60)
                                         + *(unsigned __int16 *)(v61 + 8 * v60 + 4))
                                 * *(float *)(a1 + 84);
            *(float *)(v56 + 36) = (float)(*(unsigned __int16 *)(v61 + 8 * v60 + 2)
                                         + *(unsigned __int16 *)(v61 + 8 * v60 + 6))
                                 * *(float *)(a1 + 88);
          }
        }
        ++v9;
      }
      while ( v9 < *(_DWORD *)(v5 + 192) );
    }
    sub_18005F600(a1);
    sub_18005F180(a1);
    *(_BYTE *)(v5 + 184) = 0;
    result = *(int *)(a1 + 672);
    v63 = 8 * result;
    if ( 8 * result )
    {
      result = *(_QWORD *)(a1 + 680);
      v64 = v63 + result;
      do
      {
        v65 = *(_QWORD **)result;
        if ( *(_QWORD *)(*(_QWORD *)result + 16LL) == a1 )
        {
          *v65 = *(_QWORD *)(a1 + 92);
          v65[1] = a1 + 136;
        }
        result += 8;
      }
      while ( result != v64 );
    }
    goto LABEL_58;
  }
  while ( 1 )
  {
    if ( (*v44 & 0x40000000) == 0 )
      goto LABEL_44;
    v47 = (__int64)(int)(*v44 << 12) >> 12;
    if ( !v43[2 * v47 + 1] )
      goto LABEL_44;
    v48 = sub_180061CF0(a1, LOWORD(v43[2 * v47 + 1]), HIWORD(v43[2 * v47 + 1]), v44);
    if ( v48 == -1 )
      break;
    v49 = *(_QWORD *)(a1 + 688);
    v50 = (__int64)(int)(*(_DWORD *)(*(_QWORD *)(v49 + 120) + 4LL * (v48 & 0x7FFFF)) << 12) >> 12;
    v51 = *(_QWORD *)(v49 + 104);
    sub_18005DFE0(
      v6,
      LOWORD(v43[2 * v47]),
      HIWORD(v43[2 * v47]),
      v8,
      *(unsigned __int16 *)(v51 + 8 * v50),
      *(unsigned __int16 *)(v51 + 8 * v50 + 2),
      *(unsigned __int16 *)(v51 + 8 * v50 + 4),
      *(unsigned __int16 *)(v51 + 8 * v50 + 6));
    v46 = v67.m128i_i64[0];
LABEL_44:
    if ( ++v44 == (_DWORD *)v46 )
      goto LABEL_45;
  }
  if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
    sub_180052F00("[font] Texture #%03d: resize failed. Will grow.\n", *(_DWORD *)v8);
  *(_BYTE *)(v8 + 87) = 1;
  v68.m128i_i32[0] = *(_DWORD *)(v5 + 96);
  *(_DWORD *)(v5 + 96) = v72;
  v68.m128i_i32[1] = *(_DWORD *)(v5 + 100);
  *(_DWORD *)(v5 + 100) = v76;
  v66 = v43;
  v43 = *(_DWORD **)(v5 + 104);
  v68.m128i_i64[1] = (__int64)v43;
  *(_QWORD *)(v5 + 104) = v66;
  sub_180068F50(v5 + 112, &v69);
  sub_1800603D0(a1, v6);
  result = sub_180061010(a1, a2, a3);
LABEL_58:
  if ( v69.m128i_i64[1] )
    result = sub_18003A8D0((LPVOID)v69.m128i_i64[1]);
  if ( v43 )
    return sub_18003A8D0(v43);
  return result;
}
