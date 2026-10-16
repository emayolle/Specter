// sub_18004F320 size=1902
__int64 sub_18004F320()
{
  __int64 v0; // rbx
  int v1; // esi
  __int64 v2; // rdi
  bool v3; // bp
  char v4; // si
  int v5; // r14d
  double v6; // xmm0_8
  float v7; // xmm8_4
  float v8; // xmm9_4
  __m128 v9; // xmm2
  __int64 v10; // rcx
  __int64 result; // rax
  const char *v12; // rdx
  int v13; // ebp
  float v14; // xmm0_4
  int v15; // esi
  float v16; // xmm13_4
  float v17; // xmm15_4
  float v18; // xmm6_4
  float v19; // xmm7_4
  float v20; // xmm11_4
  float v21; // xmm10_4
  float v22; // xmm15_4
  float v23; // xmm11_4
  float v24; // xmm12_4
  int v25; // ebp
  float v26; // xmm10_4
  float v27; // xmm3_4
  float v28; // xmm2_4
  float v29; // xmm1_4
  __int64 v30; // rdx
  float v31; // xmm2_4
  float v32; // xmm4_4
  float v33; // xmm3_4
  float v34; // xmm1_4
  float v35; // xmm0_4
  float v36; // xmm2_4
  float v37; // xmm4_4
  float v38; // xmm8_4
  float v39; // xmm3_4
  float v40; // xmm5_4
  unsigned int v41; // r9d
  __int64 v42; // r8
  __int64 v43; // rcx
  float v44; // xmm1_4
  float v45; // xmm6_4
  float v46; // xmm0_4
  float v47; // xmm0_4
  float v48; // [rsp+20h] [rbp-D8h] BYREF
  float v49; // [rsp+24h] [rbp-D4h]
  float v50; // [rsp+28h] [rbp-D0h]
  float v51; // [rsp+2Ch] [rbp-CCh]
  float v52; // [rsp+100h] [rbp+8h]
  char v53; // [rsp+108h] [rbp+10h] BYREF

  v0 = qword_18010C470;
  v1 = *(_DWORD *)(qword_18010C470 + 8);
  v2 = *(_QWORD *)(qword_18010C470 + 8120);
  v3 = (v1 & 2) != 0 && (*(_BYTE *)(qword_18010C470 + 12) & 1) != 0;
  v4 = v1 & 1;
  if ( *(_BYTE *)(qword_18010C470 + 8266) && v2 )
  {
    if ( (*(_BYTE *)(qword_18010C470 + 10228) & 0x10) != 0 )
    {
      sub_180052F00("[nav] NavMoveRequestForward %d\n", *(_DWORD *)(qword_18010C470 + 8280));
      goto LABEL_38;
    }
  }
  else
  {
    *(_DWORD *)(qword_18010C470 + 8280) = -1;
    *(_QWORD *)(v0 + 8268) = 0;
    if ( v2 && !*(_QWORD *)(v0 + 8592) && (*(_DWORD *)(v2 + 20) & 0x10000) == 0 )
    {
      v5 = *(_DWORD *)(qword_18010C470 + 7664);
      if ( (v5 & 1) == 0
        && (v3 && (unsigned __int8)sub_180046DB0(638, 5, 0xFFFFFFFFLL)
         || v4 && (unsigned __int8)sub_180046DB0(513, 5, 0xFFFFFFFFLL)) )
      {
        *(_DWORD *)(v0 + 8280) = 0;
      }
      if ( (v5 & 2) == 0
        && (v3 && (unsigned __int8)sub_180046DB0(639, 5, 0xFFFFFFFFLL)
         || v4 && (unsigned __int8)sub_180046DB0(514, 5, 0xFFFFFFFFLL)) )
      {
        *(_DWORD *)(v0 + 8280) = 1;
      }
      if ( (v5 & 4) == 0
        && (v3 && (unsigned __int8)sub_180046DB0(640, 5, 0xFFFFFFFFLL)
         || v4 && (unsigned __int8)sub_180046DB0(515, 5, 0xFFFFFFFFLL)) )
      {
        *(_DWORD *)(v0 + 8280) = 2;
      }
      if ( (v5 & 8) == 0
        && (v3 && (unsigned __int8)sub_180046DB0(641, 5, 0xFFFFFFFFLL)
         || v4 && (unsigned __int8)sub_180046DB0(516, 5, 0xFFFFFFFFLL)) )
      {
        *(_DWORD *)(v0 + 8280) = 3;
      }
    }
    *(_DWORD *)(v0 + 8288) = *(_DWORD *)(v0 + 8280);
    *(_DWORD *)(v0 + 8308) = 2139095039;
    *(_DWORD *)(v0 + 8312) = 2139095039;
    *(_DWORD *)(v0 + 8316) = -8388609;
    *(_DWORD *)(v0 + 8320) = -8388609;
  }
  if ( !v2 )
  {
LABEL_42:
    v7 = 0.0;
    v8 = 0.0;
    goto LABEL_43;
  }
LABEL_38:
  if ( *(_DWORD *)(v0 + 8280) != -1 || !v4 )
    goto LABEL_42;
  v6 = sub_180050100();
  v7 = 0.0;
  v8 = *(float *)&v6;
  if ( *(float *)&v6 != 0.0 )
  {
    v9 = *(__m128 *)(v2 + 544);
    *(__m128 *)(v0 + 8308) = v9;
    *(float *)(v0 + 8320) = *(float *)&v6 + *(float *)(v0 + 8320);
    *(float *)(v0 + 8312) = *(float *)&v6 + _mm_shuffle_ps(v9, v9, 85).m128_f32[0];
  }
LABEL_43:
  v10 = *(unsigned int *)(v0 + 8280);
  *(_BYTE *)(v0 + 8266) = 0;
  if ( (_DWORD)v10 != -1 )
    sub_18004E030(v10, *(unsigned int *)(v0 + 8288), *(unsigned int *)(v0 + 8268), *(unsigned int *)(v0 + 8272));
  result = *(unsigned __int8 *)(v0 + 8264);
  if ( (_BYTE)result )
  {
    if ( *(_DWORD *)(v0 + 8116) )
      goto LABEL_94;
    if ( (*(_BYTE *)(v0 + 10228) & 0x10) != 0 )
    {
      if ( v2 )
        v12 = *(const char **)(v2 + 8);
      else
        v12 = "<NULL>";
      sub_180052F00("[nav] NavInitRequest: from move, window \"%s\", layer=%d\n", v12, *(_DWORD *)(v0 + 8132));
      result = *(unsigned __int8 *)(v0 + 8264);
    }
    *(_WORD *)(v0 + 8202) = 257;
    *(_DWORD *)(v0 + 8216) = 0;
    if ( *(_BYTE *)(v0 + 86) )
      *(_BYTE *)(v0 + 8112) = 1;
    if ( (_BYTE)result )
    {
LABEL_94:
      if ( *(_DWORD *)(v0 + 8184) == 3 && !*(_DWORD *)(v0 + 8132) )
      {
        if ( !v2 )
        {
LABEL_90:
          v40 = 0.0;
          v37 = 0.0;
          v39 = 0.0;
          v36 = 0.0;
          goto LABEL_91;
        }
        v13 = *(_DWORD *)(v0 + 8268);
        v14 = *(float *)(v2 + 300);
        v15 = v13 & 0xA;
        v16 = *(float *)(v2 + 544);
        v52 = *(float *)(v2 + 296);
        v17 = (float)(*(float *)(v2 + 548) - 1.0) - v14;
        v18 = (float)(*(float *)(v2 + 556) + 1.0) - v14;
        v19 = (float)(*(float *)(v2 + 552) + 1.0) - v52;
        result = sub_18004B450(&v53, v2);
        v20 = *(float *)(result + 4) - *(float *)(v2 + 156);
        v21 = *(float *)result - *(float *)(v2 + 152);
        v22 = v17 + v20;
        v23 = v20 + v18;
        v24 = v21 + v19;
        v25 = v13 & 5;
        if ( !v25 || !v15 )
        {
          v26 = v21 + (float)((float)(v16 - 1.0) - v52);
          if ( *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1016) < v26
            || *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1020) < v22
            || v24 < *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1024)
            || v23 < *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1028) )
          {
            if ( (*(_BYTE *)(v0 + 10228) & 0x10) != 0 )
              sub_180052F00("[nav] NavMoveRequest: clamp NavRectRel for gamepad move\n");
            v27 = *(float *)(v2 + 704) * 0.5;
            if ( v25 )
            {
              v48 = -3.4028235e38;
              v50 = 3.4028235e38;
            }
            else
            {
              v28 = fminf(v24 - v26, v27);
              v48 = v26 + v28;
              v50 = v24 - v28;
            }
            if ( v15 )
            {
              v49 = -3.4028235e38;
              v51 = 3.4028235e38;
            }
            else
            {
              v29 = fminf(v23 - v22, v27);
              v51 = v23 - v29;
              v49 = v29 + v22;
            }
            sub_180034C80(v2 + 16LL * *(int *)(v0 + 8132) + 1016, &v48);
            *(_DWORD *)(v0 + 8116) = 0;
          }
          goto LABEL_74;
        }
      }
    }
  }
  if ( !v2 )
    goto LABEL_90;
LABEL_74:
  v30 = *(int *)(v0 + 8132);
  result = 2 * v30;
  v31 = *(float *)(v2 + 16 * v30 + 1016);
  if ( v31 > *(float *)(v2 + 16 * v30 + 1024)
    || *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1020) > *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1028) )
  {
    v31 = 0.0;
    v32 = 0.0;
    v33 = 0.0;
  }
  else
  {
    v32 = *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1024);
    v7 = *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1020);
    v33 = *(float *)(v2 + 16LL * *(int *)(v0 + 8132) + 1028);
  }
  v34 = *(float *)(v2 + 300);
  v35 = *(float *)(v2 + 296);
  v36 = v31 + v35;
  v37 = v32 + v35;
  v38 = (float)(v7 + v34) + v8;
  v39 = (float)(v33 + v34) + v8;
  v40 = v38;
  if ( *(_BYTE *)(v0 + 8264) )
  {
    v41 = *(_DWORD *)(v0 + 8280);
    v42 = *(_QWORD *)(v2 + 984);
    v43 = *(_QWORD *)(qword_18010C470 + 8120);
    v44 = *(float *)(v43 + 296);
    v45 = *(float *)(v43 + 300);
    if ( *(char *)(v0 + 8268) >= 0 )
    {
      if ( *(float *)(v42 + 8 * v30 + 1048) == 3.4028235e38 )
        *(float *)(v42 + 8 * v30 + 1048) = fminf(v36 + 1.0, v37) - v44;
      if ( *(float *)(v42 + 8 * v30 + 1052) == 3.4028235e38 )
        *(float *)(v42 + 8 * v30 + 1052) = (float)((float)(v39 + v38) * 0.5) - v45;
    }
    result = v41 - 2;
    if ( (unsigned int)result > 1 || (v46 = *(float *)(v42 + 8 * v30 + 1048), v46 == 3.4028235e38) )
    {
      if ( v41 <= 1 )
      {
        v47 = *(float *)(v42 + 8 * v30 + 1052);
        if ( v47 != 3.4028235e38 )
        {
          v40 = v47 + v45;
          v39 = v47 + v45;
        }
      }
    }
    else
    {
      v36 = v46 + v44;
      v37 = v46 + v44;
    }
  }
LABEL_91:
  *(float *)(v0 + 8292) = v36;
  *(float *)(v0 + 8296) = v40;
  *(float *)(v0 + 8300) = v37;
  *(float *)(v0 + 8304) = v39;
  return result;
}
