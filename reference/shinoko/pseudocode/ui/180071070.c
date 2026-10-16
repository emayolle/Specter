char __fastcall sub_180071070(__int64 a1, char *a2)
{
  __int64 v2; // rbx
  int v4; // edi
  __int64 v5; // r13
  unsigned int v6; // eax
  int v7; // r9d
  unsigned int v8; // esi
  __m128 v9; // xmm0
  __m128 v10; // xmm10
  float v11; // xmm14_4
  __m128 v12; // xmm7
  float v13; // xmm2_4
  float v14; // xmm8_4
  float v15; // xmm1_4
  int v16; // ecx
  char v17; // al
  char v18; // di
  __int64 v19; // rcx
  char v20; // dl
  __int64 v21; // rdx
  __int64 v22; // r8
  char v23; // al
  __int64 v24; // r9
  char v25; // r12
  int v26; // edi
  __m128 v27; // xmm6
  __m128 v28; // xmm9
  int v29; // xmm11_4
  __int64 v30; // rax
  int v31; // eax
  int v32; // r9d
  unsigned int v33; // eax
  __m128 v34; // xmm2
  __int64 v35; // rcx
  __m128 v36; // xmm2
  bool v37; // zf
  float v38; // xmm7_4
  const char *v39; // rsi
  __int64 v40; // r14
  const char *v41; // rbx
  __int64 v42; // rdi
  __int64 v43; // r12
  __int64 v44; // r13
  float v45; // xmm1_4
  float v46; // xmm0_4
  __int64 v47; // rax
  int v48; // eax
  __int64 v49; // rax
  const char *v50; // rdi
  __int64 v51; // rax
  const char *v53; // [rsp+28h] [rbp-A9h]
  int v54; // [rsp+28h] [rbp-A9h]
  char v55; // [rsp+38h] [rbp-99h] BYREF
  char v56; // [rsp+39h] [rbp-98h] BYREF
  char v57; // [rsp+3Ah] [rbp-97h]
  __int64 v58; // [rsp+40h] [rbp-91h] BYREF
  float v59[2]; // [rsp+48h] [rbp-89h] BYREF
  __m128 v60; // [rsp+50h] [rbp-81h] BYREF
  float v61; // [rsp+60h] [rbp-71h] BYREF
  float v62; // [rsp+64h] [rbp-6Dh]
  float v63; // [rsp+68h] [rbp-69h]
  float v64; // [rsp+6Ch] [rbp-65h]
  float v66; // [rsp+148h] [rbp+77h] BYREF
  float v67; // [rsp+14Ch] [rbp+7Bh]
  char v68; // [rsp+150h] [rbp+7Fh] BYREF

  v2 = qword_18010C470;
  v4 = a1;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v5 = *(_QWORD *)(v2 + 5216);
  if ( *(_BYTE *)(v5 + 209) )
    return 0;
  v6 = sub_1800465E0(*(_QWORD *)(v2 + 5216), a1);
  LOBYTE(v7) = 1;
  v8 = v6;
  sub_18003DF30((unsigned int)&v66, v4, 0, v7, -1082130432);
  v9 = (__m128)*(unsigned __int64 *)(v5 + 280);
  v10 = v9;
  v11 = v66;
  v12 = _mm_shuffle_ps(v9, v9, 85);
  v13 = (float)(*(float *)(v2 + 3216) + *(float *)(v2 + 3216)) + v67;
  v14 = (float)(*(float *)(qword_18010C470 + 3216) + *(float *)(qword_18010C470 + 3216))
      + *(float *)(qword_18010C470 + 4432);
  if ( v66 <= 0.0 )
    v15 = 0.0;
  else
    v15 = v66 + *(float *)(v2 + 3236);
  LODWORD(v61) = *(_QWORD *)(v5 + 280);
  v62 = v12.m128_f32[0];
  v64 = v13 + v12.m128_f32[0];
  v63 = v9.m128_f32[0] + (float)(v15 + v14);
  v67 = (float)(v13 + v12.m128_f32[0]) - v12.m128_f32[0];
  v66 = v63 - v9.m128_f32[0];
  sub_18004AAD0(&v66);
  sub_18004A070(&v61, v8, 0, 0);
  v16 = *(_DWORD *)(v2 + 7748) & 0x400000;
  v57 = v17;
  if ( !v17 )
  {
    if ( v16
      && *(_BYTE *)(v2 + 9088)
      && *(float *)(v2 + 9104) > v62
      && v64 > *(float *)(v2 + 9096)
      && *(float *)(v2 + 9100) > v61
      && v63 > *(float *)(v2 + 9092) )
    {
      v18 = *a2;
      LOBYTE(v66) = *a2;
      goto LABEL_14;
    }
    return 0;
  }
  v18 = *a2;
  LOBYTE(v66) = *a2;
  if ( !v16 )
  {
    LOBYTE(v66) = sub_18006F740((unsigned int)&v61, v8, (unsigned int)&v68, (unsigned int)&v55, 0);
    v25 = LOBYTE(v66);
    if ( LOBYTE(v66) )
      v18 = v18 == 0;
    goto LABEL_35;
  }
LABEL_14:
  v19 = *(_QWORD *)(qword_18010C470 + 9144);
  if ( *(_BYTE *)(v19 + 90) )
  {
    v20 = *(_BYTE *)(v19 + 88);
    if ( v20 != -1 )
      v18 = v20 == 1;
    if ( *(_BYTE *)(v19 + 91) )
    {
      v21 = *(_QWORD *)(v19 + 40);
      v22 = *(_QWORD *)(qword_18010C470 + 7704);
      if ( *(_BYTE *)(v19 + 94) || *(_DWORD *)(qword_18010C470 + 8564) != v8 )
      {
        v23 = 0;
      }
      else
      {
        *(_BYTE *)(v19 + 94) = 1;
        if ( *(_QWORD *)(v21 + 24) == -1 )
        {
          *(_QWORD *)(v21 + 24) = v22;
          *(_BYTE *)(v21 + 20) = v18 != 0;
        }
        v23 = 1;
      }
      if ( *(_QWORD *)(v21 + 24) == v22 || v23 || *(_BYTE *)(v19 + 93) != *(_BYTE *)(v19 + 94) )
      {
        v18 = *(_BYTE *)(v21 + 20) != 0;
      }
      else if ( (*(_DWORD *)(v19 + 84) & 0x1000) == 0 && (*(_BYTE *)(v19 + 52) & 0x10) == 0 )
      {
        v18 = 0;
      }
    }
    LOBYTE(v66) = v18;
  }
  v56 = sub_18006F740((unsigned int)&v61, v8, (unsigned int)&v68, (unsigned int)&v55, 0);
  sub_180086280(v8, &v66, &v56);
  v25 = v56;
  v18 = LOBYTE(v66);
  LOBYTE(v66) = v56;
LABEL_35:
  if ( *a2 != v18 )
  {
    v25 = 1;
    *a2 = v18;
    LOBYTE(v66) = 1;
    sub_18003A1B0(v8);
  }
  v27 = v10;
  v26 = *(_DWORD *)(v2 + 7748) & 0x1000;
  v27.m128_f32[0] = v10.m128_f32[0] + v14;
  v28 = v12;
  v28.m128_f32[0] = v12.m128_f32[0] + v14;
  if ( v57 )
  {
    sub_180038770(&v61, v8, 0);
    v29 = *(_DWORD *)(v2 + 3220);
    if ( v55 && v68 )
      v30 = 9;
    else
      v30 = (v68 != 0) + 7LL;
    v60 = *(__m128 *)(qword_18010C470 + 16 * (v30 + 18) + 3136);
    v60.m128_f32[3] = _mm_shuffle_ps(v60, v60, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    v31 = sub_180036620(&v60);
    LOBYTE(v32) = 1;
    sub_180038470(_mm_unpacklo_ps(v10, v12).m128_u32[0], _mm_unpacklo_ps(v27, v28).m128_u32[0], v31, v32, v29);
    v60 = *(__m128 *)(qword_18010C470 + 3712);
    v60.m128_f32[3] = _mm_shuffle_ps(v60, v60, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    v33 = sub_180036620(&v60);
    if ( v26 )
    {
      v34 = (__m128)0x3F800000u;
      v35 = *(_QWORD *)(v5 + 712);
      v34.m128_f32[0] = fmaxf(1.0, (float)(int)(float)(v14 / 3.5999999));
      v54 = *(_DWORD *)(v2 + 3220);
      v59[0] = v27.m128_f32[0] - v34.m128_f32[0];
      v59[1] = v28.m128_f32[0] - v34.m128_f32[0];
      v60.m128_u64[0] = _mm_add_ps(_mm_shuffle_ps(v34, v34, 0), v10).m128_u64[0];
      sub_18005C870(v35, (unsigned int)&v60, (unsigned int)v59, v33, v54, 0);
    }
    else if ( *a2 )
    {
      v36 = (__m128)0x3F800000u;
      v36.m128_f32[0] = fmaxf(1.0, (float)(int)(float)(v14 / 6.0));
      sub_180068080(*(_QWORD *)(v5 + 712), _mm_add_ps(_mm_shuffle_ps(v36, v36, 0), v10).m128_u64[0], v33);
    }
  }
  v37 = *(_BYTE *)(v2 + 10080) == 0;
  v38 = v12.m128_f32[0] + *(float *)(v2 + 3216);
  *(float *)&v58 = v27.m128_f32[0] + *(float *)(v2 + 3236);
  *((float *)&v58 + 1) = v38;
  if ( !v37 )
  {
    if ( v26 )
    {
      v39 = "[~]";
    }
    else
    {
      v39 = "[ ]";
      if ( *a2 )
        v39 = "[x]";
    }
    v40 = qword_18010C470;
    v41 = v39;
    v42 = *(_QWORD *)(qword_18010C470 + 10120);
    v43 = *(_QWORD *)(qword_18010C470 + 10128);
    v44 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    for ( *(_QWORD *)(v40 + 10120) = 0; v41 != (const char *)-1LL; ++v41 )
    {
      if ( !*v41 || *v41 == 35 && v41[1] == 35 )
        break;
    }
    v45 = *((float *)&v58 + 1);
    v46 = *(float *)(v40 + 3216) + *(float *)(v40 + 10136);
    *(_DWORD *)(v40 + 10136) = HIDWORD(v58);
    if ( v45 > (float)(v46 + 1.0) )
    {
      sub_180051790("\r\n");
      *(_BYTE *)(v40 + 10140) = 1;
    }
    if ( v42 )
    {
      v47 = sub_1800B9730(v42);
      sub_180051A10(&v58, v42, v47 + v42);
    }
    v48 = *(_DWORD *)(v44 + 416);
    if ( *(_DWORD *)(v40 + 10144) > v48 )
      *(_DWORD *)(v40 + 10144) = v48;
    while ( 1 )
    {
      v49 = sub_1800B8A30(v39, 10, v41 - v39);
      v50 = v41;
      if ( v49 )
        v50 = (const char *)v49;
      if ( v39 == v50 && v50 == v41 )
        break;
      v53 = v39;
      sub_180051790("%*s%.*s");
      *(_BYTE *)(v40 + 10140) = 0;
      if ( *v50 == 10 )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v40 + 10140) = 1;
      }
      if ( v50 == v41 )
        break;
      v39 = v50 + 1;
    }
    if ( v43 )
    {
      v51 = sub_1800B9730(v43);
      sub_180051A10(&v58, v43, v51 + v43);
    }
    v25 = LOBYTE(v66);
  }
  if ( v57 )
  {
    if ( v11 > 0.0 )
    {
      LOBYTE(v24) = 1;
      sub_180037440(v58, a1, 0, v24, v53);
    }
  }
  return v25;
}
