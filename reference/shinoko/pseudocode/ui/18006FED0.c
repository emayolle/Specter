void __fastcall sub_18006FED0(__int64 a1, _QWORD *a2)
{
  __int64 v2; // rbx
  int v4; // esi
  __int64 v5; // rdi
  unsigned int v6; // eax
  int v7; // r9d
  unsigned int v8; // r14d
  float v9; // xmm6_4
  float v10; // xmm8_4
  char v11; // al
  __int64 v12; // rax
  int v13; // eax
  int v14; // r9d
  __int64 v15; // rax
  float v16; // xmm3_4
  float v17; // xmm2_4
  float v18; // [rsp+40h] [rbp-19h] BYREF
  float v19; // [rsp+44h] [rbp-15h]
  int v20; // [rsp+48h] [rbp-11h] BYREF
  __m128 v21; // [rsp+50h] [rbp-9h] BYREF
  float v22; // [rsp+60h] [rbp+7h] BYREF
  float v23; // [rsp+64h] [rbp+Bh]
  float v24; // [rsp+68h] [rbp+Fh]
  float v25; // [rsp+6Ch] [rbp+13h]
  char v26; // [rsp+D0h] [rbp+77h] BYREF
  char v27; // [rsp+D8h] [rbp+7Fh] BYREF

  v2 = qword_18010C470;
  v4 = a1;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v5 = *(_QWORD *)(v2 + 5216);
  if ( !*(_BYTE *)(v5 + 209) )
  {
    v6 = sub_1800465E0(v5, a1);
    LOBYTE(v7) = 1;
    v8 = v6;
    sub_18003DF30((unsigned int)&v20, v4, 0, v7, -1082130432);
    v9 = *(float *)(v5 + 280);
    v10 = *(float *)(v5 + 284);
    sub_18004AEC0(&v18, *a2);
    v22 = v9;
    v23 = v10;
    v24 = v9 + v18;
    v25 = v10 + v19;
    sub_18004AAD0(&v18);
    sub_18004A070(&v22, v8, 0, 0);
    if ( v11 )
    {
      sub_18006F740((unsigned int)&v22, v8, (unsigned int)&v26, (unsigned int)&v27, 0);
      if ( v27 && v26 )
        v12 = 23;
      else
        v12 = (v26 != 0) + 21LL;
      v21 = *(__m128 *)(qword_18010C470 + 16 * (v12 + 18) + 3136);
      v21.m128_f32[3] = _mm_shuffle_ps(v21, v21, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      sub_180038770(&v22, v8, 0);
      v13 = sub_180036620(&v21);
      LOBYTE(v14) = 1;
      sub_180038470(LODWORD(v22), LODWORD(v24), v13, v14, *(_DWORD *)(v2 + 3220));
      if ( *(_BYTE *)(v2 + 10080) )
      {
        v15 = qword_18010C470;
        *(_QWORD *)(qword_18010C470 + 10120) = "[";
        *(_QWORD *)(v15 + 10128) = "]";
      }
      v16 = *(float *)(v2 + 3212);
      v17 = *(float *)(v2 + 3216);
      v18 = v24 - v16;
      v21.m128_f32[0] = v16 + v22;
      v19 = v25 - v17;
      v21.m128_f32[1] = v17 + v23;
      sub_180037980((unsigned int)&v21, (unsigned int)&v18, v4, 0, (__int64)&v20, v2 + 3356, (__int64)&v22);
    }
  }
}
