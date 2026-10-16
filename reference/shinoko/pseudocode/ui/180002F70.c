__int64 __fastcall sub_180002F70(__int64 a1, float *a2)
{
  __int64 v4; // rdx
  float v5; // xmm2_4
  float v6; // xmm7_4
  __int64 v7; // rax
  __int64 v8; // rcx
  __int64 v9; // rax
  __int64 v10; // rax
  float v11; // xmm0_4
  __int64 v12; // rcx
  __int64 v13; // rax
  float v14; // xmm0_4
  int v15; // xmm9_4
  int v16; // xmm10_4
  int v17; // xmm11_4
  int v18; // xmm12_4
  int v19; // r8d
  int v20; // ebx
  int v21; // eax
  __int64 v22; // rax
  __int64 v23; // rdi
  __int64 v24; // rcx
  float v25; // xmm7_4
  __int64 v26; // rax
  __int64 v27; // rax
  float v28; // xmm0_4
  float *v29; // rax
  float v30; // xmm0_4
  float v32; // [rsp+28h] [rbp-39h] BYREF
  float v33; // [rsp+2Ch] [rbp-35h]
  float v34; // [rsp+30h] [rbp-31h]
  float v35; // [rsp+34h] [rbp-2Dh]
  __int64 v36; // [rsp+D0h] [rbp+6Fh] BYREF

  sub_18004AFD0();
  v4 = qword_18010C470;
  v5 = *a2;
  v6 = *(float *)(qword_18010C470 + 3232);
  if ( *a2 < 0.0 )
  {
    v7 = *(_QWORD *)(qword_18010C470 + 5216);
    if ( *(_QWORD *)(v7 + 456) || (v8 = 632, *(_QWORD *)(qword_18010C470 + 8856)) )
      v8 = 584;
    v5 = *(float *)(v8 + v7) - *(float *)(v7 + 280);
  }
  v9 = *(_QWORD *)(qword_18010C470 + 5216);
  v36 = LODWORD(v5);
  *(_BYTE *)(v9 + 206) = 1;
  v10 = *(_QWORD *)(v4 + 5216);
  if ( !*(_BYTE *)(v10 + 209) )
  {
    v11 = *(float *)(v10 + 284);
    v32 = *(float *)(v10 + 280);
    v33 = v11;
    v34 = v32 + v5;
    v35 = v11 + 0.0;
    sub_18004AAD0(&v36);
    sub_18004A070(&v32, 0, 0, 0);
  }
  v36 = 0;
  sub_180037110(11, &v36);
  v36 = 0;
  sub_180037110(14, &v36);
  v12 = qword_18010C470;
  v36 = 1094713344;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v13 = *(_QWORD *)(v12 + 5216);
  if ( !*(_BYTE *)(v13 + 209) )
  {
    v14 = *(float *)(v13 + 284);
    v32 = *(float *)(v13 + 280);
    v33 = v14;
    v34 = v32 + 12.0;
    v35 = v14 + 0.0;
    sub_18004AAD0(&v36);
    sub_18004A070(&v32, 0, 0, 0);
  }
  sub_18004AC40();
  sub_18006EB90(a1, 0, 1);
  v15 = *(_DWORD *)(qword_18010C470 + 7756);
  v16 = *(_DWORD *)(qword_18010C470 + 7760);
  v17 = *(_DWORD *)(qword_18010C470 + 7764);
  v18 = *(_DWORD *)(qword_18010C470 + 7768);
  sub_1800371B0(2);
  v19 = dword_18010C490;
  if ( dword_18010C490 != dword_18010C494 )
    goto LABEL_20;
  v20 = dword_18010C490 + 1;
  if ( dword_18010C494 )
    v21 = dword_18010C494 + dword_18010C494 / 2;
  else
    v21 = 8;
  if ( v21 > v20 )
    v20 = v21;
  if ( v20 > dword_18010C494 )
  {
    v22 = sub_18003A810(16LL * v20);
    v23 = v22;
    if ( qword_18010C498 )
    {
      sub_1800B8BD0(v22, qword_18010C498, 16LL * dword_18010C490);
      sub_18003A8D0((LPVOID)qword_18010C498);
    }
    v19 = dword_18010C490;
    qword_18010C498 = v23;
    dword_18010C494 = v20;
  }
  else
  {
LABEL_20:
    v23 = qword_18010C498;
  }
  v24 = qword_18010C470;
  v25 = v6 + 4.0;
  v26 = 2LL * v19;
  LODWORD(v36) = 0;
  *((float *)&v36 + 1) = v25;
  *(_DWORD *)(v23 + 8 * v26) = v15;
  *(_DWORD *)(v23 + 8 * v26 + 4) = v16;
  *(_DWORD *)(v23 + 8 * v26 + 8) = v17;
  *(_DWORD *)(v23 + 8 * v26 + 12) = v18;
  ++dword_18010C490;
  *(_BYTE *)(*(_QWORD *)(v24 + 5216) + 206LL) = 1;
  v27 = *(_QWORD *)(v24 + 5216);
  if ( !*(_BYTE *)(v27 + 209) )
  {
    v28 = *(float *)(v27 + 284);
    v32 = *(float *)(v27 + 280);
    v33 = v28;
    v35 = v25 + v28;
    v34 = v32 + 0.0;
    sub_18004AAD0(&v36);
    sub_18004A070(&v32, 0, 0, 0);
    v24 = qword_18010C470;
  }
  *(_BYTE *)(*(_QWORD *)(v24 + 5216) + 206LL) = 1;
  v29 = *(float **)(v24 + 5216);
  v30 = v29[87] + 10.0;
  v29[87] = v30;
  v29[70] = (float)(v30 + v29[10]) + v29[88];
  sub_18004ACF0();
  return sub_18004AFD0();
}
