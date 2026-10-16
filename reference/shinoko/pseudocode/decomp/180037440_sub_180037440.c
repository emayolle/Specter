// sub_180037440 size=753
void __fastcall sub_180037440(__int64 a1, _BYTE *a2, _BYTE *a3, char a4)
{
  _BYTE *v4; // rsi
  unsigned __int64 v5; // rcx
  _BYTE *i; // rbx
  __int64 v7; // rbp
  __int64 v8; // rdi
  int v9; // r8d
  int v10; // r9d
  __m128 *v11; // rdx
  __int64 v12; // rcx
  __int64 v13; // rdi
  __int64 v14; // r14
  __int64 v15; // r15
  float v16; // xmm1_4
  float v17; // xmm0_4
  __int64 v18; // rax
  int v19; // eax
  __int64 v20; // rax
  _BYTE *v21; // rdi
  __int64 v22; // rax
  __int64 v23; // [rsp+50h] [rbp-38h] BYREF
  __m128 v24; // [rsp+58h] [rbp-30h] BYREF

  v23 = a1;
  v4 = a2;
  if ( a4 )
  {
    v5 = -1;
    i = a2;
    if ( a3 )
      v5 = (unsigned __int64)a3;
    if ( (unsigned __int64)a2 < v5 )
    {
      do
      {
        if ( !*i || *i == 35 && i[1] == 35 )
          break;
        ++i;
      }
      while ( (unsigned __int64)i < v5 );
    }
  }
  else
  {
    if ( !a3 )
      a3 = &a2[sub_1800B9730(a2)];
    i = a3;
  }
  if ( v4 != i )
  {
    v7 = qword_18010C470;
    v8 = qword_18010C470;
    v24 = *(__m128 *)(qword_18010C470 + 3424);
    v24.m128_f32[3] = _mm_shuffle_ps(v24, v24, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    v10 = sub_180036620(&v24);
    if ( (v10 & 0xFF000000) != 0 && *v4 )
    {
      v11 = *(__m128 **)(*(_QWORD *)(v7 + 5216) + 712LL);
      v12 = *(_QWORD *)(v7 + 4416);
      if ( !v12 )
        v12 = *(_QWORD *)(v11[3].m128_u64[1] + 24);
      v24 = v11[6];
      sub_180067670(v12, (_DWORD)v11, v9, (unsigned int)&v23, v10, (__int64)&v24, (__int64)v4, (__int64)i, 0, 0);
      v7 = qword_18010C470;
    }
    if ( *(_BYTE *)(v8 + 10080) )
    {
      v13 = *(_QWORD *)(v7 + 10120);
      v14 = *(_QWORD *)(v7 + 5216);
      v15 = *(_QWORD *)(v7 + 10128);
      *(_QWORD *)(v7 + 10128) = 0;
      *(_QWORD *)(v7 + 10120) = 0;
      if ( !i )
      {
        for ( i = v4; i != (_BYTE *)-1LL; ++i )
        {
          if ( !*i || *i == 35 && i[1] == 35 )
            break;
        }
      }
      v16 = *((float *)&v23 + 1);
      v17 = *(float *)(v7 + 10136) + *(float *)(v7 + 3216);
      *(_DWORD *)(v7 + 10136) = HIDWORD(v23);
      if ( v16 > (float)(v17 + 1.0) )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v7 + 10140) = 1;
      }
      if ( v13 )
      {
        v18 = sub_1800B9730(v13);
        sub_180051A10(&v23, v13, v18 + v13);
      }
      v19 = *(_DWORD *)(v14 + 416);
      if ( *(_DWORD *)(v7 + 10144) > v19 )
        *(_DWORD *)(v7 + 10144) = v19;
      while ( 1 )
      {
        v20 = sub_1800B8A30(v4, 10, i - v4);
        v21 = i;
        if ( v20 )
          v21 = (_BYTE *)v20;
        if ( v4 == v21 && v21 == i )
          break;
        sub_180051790("%*s%.*s");
        *(_BYTE *)(v7 + 10140) = 0;
        if ( *v21 == 10 )
        {
          sub_180051790("\r\n");
          *(_BYTE *)(v7 + 10140) = 1;
        }
        if ( v21 == i )
          break;
        v4 = v21 + 1;
      }
      if ( v15 )
      {
        v22 = sub_1800B9730(v15);
        sub_180051A10(&v23, v15, v22 + v15);
      }
    }
  }
}
