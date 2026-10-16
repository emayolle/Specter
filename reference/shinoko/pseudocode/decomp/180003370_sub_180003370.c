// sub_180003370 size=934
__int64 sub_180003370()
{
  __int64 v0; // rdx
  __int64 v1; // r8
  __int64 v2; // r9
  int v3; // ecx
  __int64 v4; // rax
  float *v5; // rax
  float v6; // xmm0_4
  __int64 v7; // rax
  float v8; // xmm0_4
  __int64 v9; // r9
  float v10; // xmm15_4
  float v11; // xmm14_4
  float v12; // xmm13_4
  float v13; // xmm0_4
  float v14; // xmm12_4
  float v15; // xmm6_4
  float v16; // xmm10_4
  __int64 v17; // rax
  float v18; // xmm12_4
  __int64 v19; // rdi
  int v20; // eax
  __int64 v21; // r9
  int v22; // xmm9_4
  float v23; // xmm13_4
  float v24; // xmm15_4
  int v25; // ebx
  float v26; // xmm14_4
  __int64 v27; // r9
  __int64 v28; // r9
  float v30; // [rsp+48h] [rbp-59h] BYREF
  float v31; // [rsp+4Ch] [rbp-55h]
  float v32; // [rsp+50h] [rbp-51h] BYREF
  float v33; // [rsp+54h] [rbp-4Dh]
  __int128 v34; // [rsp+58h] [rbp-49h] BYREF
  float v35; // [rsp+108h] [rbp+67h] BYREF
  float v36; // [rsp+10Ch] [rbp+6Bh]
  float v37; // [rsp+110h] [rbp+6Fh] BYREF
  float v38; // [rsp+114h] [rbp+73h]

  sub_18004B190();
  v0 = qword_18010C470;
  v1 = *(_QWORD *)(qword_18010C470 + 5216);
  v2 = *(int *)(v1 + 496);
  if ( (int)v2 > 0 )
  {
    v3 = *(_DWORD *)(*(_QWORD *)(v1 + 504) + 4 * v2 - 4);
    *(_DWORD *)(v1 + 496) = v2 - 1;
    *(_DWORD *)(v1 + 488) = v3;
  }
  else
  {
    sub_180049A30("Calling PopItemWidth() too many times!");
    v0 = qword_18010C470;
  }
  v4 = *(_QWORD *)(v0 + 5216);
  v35 = 0.0;
  v36 = 6.0;
  *(_BYTE *)(v4 + 206) = 1;
  v5 = *(float **)(v0 + 5216);
  v6 = v5[87] - 10.0;
  v5[87] = v6;
  v5[70] = (float)(v6 + v5[10]) + v5[88];
  *(_BYTE *)(*(_QWORD *)(v0 + 5216) + 206LL) = 1;
  v7 = *(_QWORD *)(v0 + 5216);
  if ( !*(_BYTE *)(v7 + 209) )
  {
    v8 = *(float *)(v7 + 284);
    v30 = *(float *)(v7 + 280);
    v31 = v8;
    v32 = v30 + 0.0;
    v33 = v8 + 6.0;
    sub_18004AAD0(&v35);
    sub_18004A070(&v30, 0, 0, 0);
  }
  sub_18004B190();
  v9 = qword_18010C470;
  v11 = *(float *)(qword_18010C470 + 7764) - 2.0;
  v12 = *(float *)(qword_18010C470 + 7768) - 1.0;
  v30 = *(float *)(qword_18010C470 + 7756) + 2.0;
  v10 = v30;
  v32 = v11;
  v13 = *(float *)(qword_18010C498 + 16LL * (dword_18010C490 - 1) + 4);
  v14 = *(float *)(qword_18010C498 + 16LL * (dword_18010C490 - 1) + 12);
  v15 = *(float *)(qword_18010C498 + 16LL * (dword_18010C490 - 1));
  v16 = *(float *)(qword_18010C498 + 16LL * --dword_18010C490 + 8);
  v17 = *(_QWORD *)(qword_18010C470 + 5216);
  v33 = v12;
  *(_BYTE *)(v17 + 206) = 1;
  v18 = (float)((float)(v14 - v13) * 0.5) + v13;
  v19 = *(_QWORD *)(*(_QWORD *)(v9 + 5216) + 712LL);
  v34 = *(_OWORD *)(v9 + 3504);
  v31 = v18;
  v20 = sub_180036620(&v34);
  v22 = *(_DWORD *)(v21 + 3220);
  v23 = v12 + 2.0;
  v24 = v10 - 2.0;
  LOBYTE(v21) = 1;
  v25 = v20;
  v35 = v15 - 4.0;
  v36 = v23;
  v37 = v24;
  v38 = v18 - 2.0;
  sub_18005A5E0(v19, &v37, &v35, v21);
  sub_18005C460(v19, (unsigned int)&v30, (unsigned int)&v32, v25, v22);
  sub_18005A7D0(v19);
  v26 = v11 + 2.0;
  v36 = v23;
  LOBYTE(v27) = 1;
  v38 = v18 - 2.0;
  v37 = v16 + 4.0;
  v35 = v26;
  sub_18005A5E0(v19, &v37, &v35, v27);
  sub_18005C460(v19, (unsigned int)&v30, (unsigned int)&v32, v25, v22);
  sub_18005A7D0(v19);
  v35 = v26;
  v36 = v23;
  LOBYTE(v28) = 1;
  v37 = v24;
  v38 = v18 + 1.0;
  sub_18005A5E0(v19, &v37, &v35, v28);
  sub_18005C460(v19, (unsigned int)&v30, (unsigned int)&v32, v25, v22);
  return sub_18005A7D0(v19);
}
