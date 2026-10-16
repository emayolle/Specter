// sub_18004BEE0 size=1275
void __fastcall sub_18004BEE0(unsigned int a1, char a2)
{
  __int64 v2; // rbx
  __int64 v5; // r14
  __int64 v6; // rax
  __int64 v7; // rdx
  int v8; // r12d
  int v9; // ecx
  int v10; // eax
  bool v11; // cl
  int v12; // r8d
  bool v13; // cl
  float v14; // xmm6_4
  float v15; // xmm9_4
  float v16; // xmm8_4
  float v17; // xmm7_4
  __int64 v18; // rdx
  float v19; // xmm1_4
  float v20; // xmm0_4
  __int64 *v21; // rax
  __int64 v22; // rcx
  float v23; // xmm0_4
  float v24; // xmm2_4
  float v25; // xmm7_4
  float v26; // xmm1_4
  float v27; // xmm2_4
  float v28; // xmm0_4
  float *v29; // rax
  bool v30; // cl
  __int64 v31; // rax
  float v32; // xmm2_4
  __int64 v33; // rax
  _DWORD *v34; // rax
  float *v35; // rcx
  _DWORD *v36; // rcx
  bool v37; // zf
  int *v38; // rdi
  int v39; // esi
  int v40; // ecx
  int v41; // esi
  int v42; // eax
  __int64 v43; // rax
  __int64 v44; // rdx
  __int64 v45; // r14
  __int64 v46; // rdx
  __int64 v47; // rcx
  int v48; // ecx
  int v49; // r8d
  int v50; // eax
  __int64 v51; // rcx
  __int64 v52; // rax
  __int128 v53; // xmm0
  __int64 v54; // xmm1_8
  __int128 v55; // [rsp+30h] [rbp-49h]
  _BYTE v56[24]; // [rsp+40h] [rbp-39h] BYREF
  float v57; // [rsp+F0h] [rbp+77h] BYREF
  float v58; // [rsp+F4h] [rbp+7Bh]

  v2 = qword_18010C470;
  v5 = *(int *)(qword_18010C470 + 8064);
  if ( a2 < 0 && *(_DWORD *)(qword_18010C470 + 8048) > (int)v5 )
    return;
  v6 = *(_QWORD *)(qword_18010C470 + 5216);
  v7 = *(_QWORD *)(qword_18010C470 + 8120);
  *(_QWORD *)&v56[12] = 0;
  *(_DWORD *)&v56[20] = 0;
  v8 = *(_DWORD *)(qword_18010C470 + 5032);
  v9 = *(_DWORD *)(*(_QWORD *)(v6 + 272) + 4LL * *(int *)(v6 + 264) - 4);
  v10 = *(_DWORD *)(qword_18010C470 + 5332);
  DWORD2(v55) = -1;
  *(_QWORD *)&v55 = v7;
  HIDWORD(v55) = v8;
  *(_DWORD *)v56 = v9;
  v11 = v10 && *(_BYTE *)(qword_18010C470 + 5350) && v10 == *(_DWORD *)(qword_18010C470 + 7744);
  if ( *(_BYTE *)(qword_18010C470 + 8112) && *(_BYTE *)(qword_18010C470 + 8113) && v7 || (v12 = 1, v11) )
    v12 = 2;
  v13 = v10 && *(_BYTE *)(qword_18010C470 + 5350) && v10 == *(_DWORD *)(qword_18010C470 + 7744);
  if ( v12 == 1 || !(v7 | v13) )
  {
    v29 = (float *)(qword_18010C470 + 224);
    if ( qword_18010C470 == -224 )
      v29 = nullptr;
    v30 = *v29 >= -256000.0 && v29[1] >= -256000.0;
    v31 = 224;
    if ( !v30 )
      v31 = 9248;
    v32 = *(float *)(v31 + qword_18010C470);
    v33 = 228;
    v27 = v32 + 1.0;
    if ( !v30 )
      v33 = 9252;
    v28 = *(float *)(v33 + qword_18010C470);
    goto LABEL_45;
  }
  if ( v13 )
  {
    v14 = *(float *)(qword_18010C470 + 7772);
    v15 = *(float *)(qword_18010C470 + 7776);
    v16 = *(float *)(qword_18010C470 + 7780);
    v17 = *(float *)(qword_18010C470 + 7784);
    if ( v7 )
      goto LABEL_25;
  }
  else
  {
    v14 = 0.0;
    v15 = 0.0;
    v16 = 0.0;
    v17 = 0.0;
    if ( v7 )
    {
      v14 = *(float *)(v7 + 296) + *(float *)(v7 + 16LL * *(int *)(qword_18010C470 + 8132) + 1016);
      v15 = *(float *)(v7 + 300) + *(float *)(v7 + 16LL * *(int *)(qword_18010C470 + 8132) + 1020);
      v16 = *(float *)(v7 + 296) + *(float *)(v7 + 16LL * *(int *)(qword_18010C470 + 8132) + 1024);
      v17 = *(float *)(v7 + 300) + *(float *)(v7 + 16LL * *(int *)(qword_18010C470 + 8132) + 1028);
LABEL_25:
      if ( *(_DWORD *)(v7 + 648) != v8 && (*(float *)(v7 + 168) != 3.4028235e38 || *(float *)(v7 + 172) != 3.4028235e38) )
      {
        sub_18004B450(&v57, v7);
        v19 = *(float *)(v18 + 152) - v57;
        v20 = *(float *)(v18 + 156) - v58;
        v14 = v14 + v19;
        v16 = v16 + v19;
        v15 = v15 + v20;
        v17 = v17 + v20;
      }
    }
  }
  v21 = *(__int64 **)(v2 + 8104);
  v22 = *v21;
  v23 = *(float *)(*v21 + 8);
  v24 = fminf(*(float *)(v2 + 3212) * 4.0, v16 - v14) + v14;
  v25 = v17 - fminf(*(float *)(v2 + 3216), v17 - v15);
  v26 = *(float *)(*v21 + 12);
  if ( v26 <= v25 )
    v26 = fminf(v26 + *(float *)(v22 + 20), v25);
  if ( v23 <= v24 )
    v23 = fminf(v23 + *(float *)(v22 + 16), v24);
  v27 = (float)(int)v23;
  v28 = (float)(int)v26;
LABEL_45:
  v34 = (_DWORD *)(v2 + 224);
  *(float *)&v56[4] = v27;
  *(float *)&v56[8] = v28;
  v35 = (float *)(v2 + 224);
  if ( v2 == -224 )
    v35 = nullptr;
  if ( *v35 < -256000.0 || v35[1] < -256000.0 )
  {
    v34 = &v56[4];
    v36 = &v56[8];
  }
  else
  {
    v36 = (_DWORD *)(v2 + 228);
  }
  v37 = (*(_BYTE *)(v2 + 10228) & 8) == 0;
  *(_DWORD *)&v56[12] = *v34;
  *(_DWORD *)&v56[16] = *v36;
  if ( !v37 )
    sub_180052F00("[popup] OpenPopupEx(0x%08X)\n", a1);
  v38 = (int *)(v2 + 8048);
  v39 = *(_DWORD *)(v2 + 8048);
  if ( v39 >= (int)v5 + 1 )
  {
    v46 = *(_QWORD *)(v2 + 8056);
    v47 = 56 * v5;
    if ( *(_DWORD *)(56 * v5 + v46) == a1
      && (*(_DWORD *)(v47 + v46 + 28) == *(_DWORD *)(v2 + 5032) - 1 || (a2 & 0x20) != 0) )
    {
      *(_DWORD *)(v47 + v46 + 28) = v8;
      return;
    }
    LOBYTE(v46) = 1;
    sub_18004C4C0((unsigned int)v5, v46);
    v48 = *(_DWORD *)(v2 + 8052);
    if ( *v38 == v48 )
    {
      v49 = *v38 + 1;
      if ( v48 )
        v50 = v48 + v48 / 2;
      else
        v50 = 8;
      if ( v50 > v49 )
        v49 = v50;
      sub_180054AF0(v2 + 8048, (unsigned int)v49);
    }
  }
  else
  {
    v40 = *(_DWORD *)(v2 + 8052);
    if ( v39 == v40 )
    {
      v41 = v39 + 1;
      if ( v40 )
        v42 = v40 + v40 / 2;
      else
        v42 = 8;
      if ( v42 > v41 )
        v41 = v42;
      if ( v41 > v40 )
      {
        v43 = sub_18003A810(56LL * v41);
        v44 = *(_QWORD *)(v2 + 8056);
        v45 = v43;
        if ( v44 )
        {
          sub_1800B8BD0(v43, v44, 56LL * *v38);
          sub_18003A8D0(*(LPVOID *)(v2 + 8056));
        }
        *(_QWORD *)(v2 + 8056) = v45;
        *(_DWORD *)(v2 + 8052) = v41;
      }
    }
  }
  v51 = 56LL * *v38;
  v52 = *(_QWORD *)(v2 + 8056);
  *(_OWORD *)(v51 + v52) = a1;
  v53 = *(_OWORD *)v56;
  *(_OWORD *)(v51 + v52 + 16) = v55;
  v54 = *(_QWORD *)&v56[16];
  *(_OWORD *)(v51 + v52 + 32) = v53;
  *(_QWORD *)(v51 + v52 + 48) = v54;
  ++*v38;
}
