// sub_180086B50 size=833
char __fastcall sub_180086B50(__int64 a1, _QWORD *a2)
{
  __int64 v2; // rbx
  __int64 v4; // rdi
  int v6; // eax
  int v7; // r9d
  int v8; // ebp
  float *v9; // rax
  __int64 v10; // r9
  float v11; // xmm11_4
  float v12; // xmm12_4
  __m128 v13; // xmm10
  float v14; // xmm9_4
  __m128 v15; // xmm8
  float v16; // xmm9_4
  float v17; // xmm0_4
  float *v18; // rax
  float v19; // xmm1_4
  float v20; // xmm2_4
  float v21; // xmm0_4
  __m128 v22; // xmm7
  __m128 v23; // xmm6
  float v24; // xmm1_4
  _DWORD v25[4]; // [rsp+30h] [rbp-A8h] BYREF
  _DWORD v26[4]; // [rsp+40h] [rbp-98h] BYREF
  __int64 v27; // [rsp+E0h] [rbp+8h] BYREF
  char v28; // [rsp+F0h] [rbp+18h] BYREF

  v27 = a1;
  v2 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v4 = *(_QWORD *)(v2 + 5216);
  if ( *(_BYTE *)(v4 + 209) )
    return 0;
  v6 = sub_1800468E0();
  LOBYTE(v7) = 1;
  v8 = v6;
  sub_18003DF30((unsigned int)&v27, (unsigned int)"##MainListbox", 0, v7, -1082130432);
  sub_18004AE40();
  v9 = (float *)sub_18004AEC0(&v28, *a2);
  v11 = *(float *)(v4 + 280);
  v12 = *(float *)&v27;
  v15 = (__m128)LODWORD(v11);
  v13 = (__m128)*(unsigned int *)(v4 + 284);
  v14 = (float)(int)v9[1];
  v15.m128_f32[0] = v11 + (float)(int)*v9;
  *(float *)v25 = v11;
  v25[1] = v13.m128_i32[0];
  v25[2] = v15.m128_i32[0];
  v16 = fmaxf(v14, *((float *)&v27 + 1)) + *(float *)(v4 + 284);
  *(float *)&v25[3] = v16;
  if ( *(float *)&v27 <= 0.0 )
    v17 = 0.0;
  else
    v17 = *(float *)&v27 + *(float *)(v2 + 3236);
  *(float *)v26 = v11;
  *(_QWORD *)(v2 + 7688) = 0;
  v18 = *(float **)(v10 + 5216);
  v19 = v15.m128_f32[0] + v17;
  v26[1] = v13.m128_i32[0];
  v20 = v16 + 0.0;
  v21 = v18[155];
  *(float *)&v26[2] = v19;
  *(float *)&v26[3] = v16 + 0.0;
  if ( v21 <= v13.m128_f32[0] || v20 <= v18[153] || v18[154] <= v11 || v19 <= v18[152] )
  {
    *(float *)&v27 = v19 - v11;
    *((float *)&v27 + 1) = v20 - v13.m128_f32[0];
    sub_18004AAD0(&v27);
    sub_18004A070(v26, 0, v25, 0);
    *(_DWORD *)(v2 + 7824) = 0;
    return 0;
  }
  else
  {
    sub_18004AFD0();
    if ( v12 > 0.0 )
    {
      v22 = v15;
      v22.m128_f32[0] = v15.m128_f32[0] + *(float *)(v2 + 3236);
      v23 = v13;
      v23.m128_f32[0] = v13.m128_f32[0] + *(float *)(v2 + 3216);
      sub_180037440(_mm_unpacklo_ps(v22, v23).m128_i64[0], "##MainListbox", nullptr, 1);
      v24 = fmaxf(*(float *)(v4 + 308), v23.m128_f32[0] + *((float *)&v27 + 1));
      *(float *)(v4 + 304) = fmaxf(*(float *)(v4 + 304), v22.m128_f32[0] + v12);
      *(float *)(v4 + 308) = v24;
      sub_180071EE0();
    }
    *(float *)&v27 = v15.m128_f32[0] - v11;
    *((float *)&v27 + 1) = v16 - v13.m128_f32[0];
    sub_18003E470(nullptr, v8, &v27, 128, 0);
    return 1;
  }
}
