// sub_18006EB90 size=2011
void __fastcall sub_18006EB90(_BYTE *a1, _BYTE *a2, char a3)
{
  __int64 v3; // r14
  char v4; // r13
  __int64 v5; // rsi
  _BYTE *i; // rbx
  _BYTE *v7; // rdi
  float v8; // xmm0_4
  float v9; // xmm13_4
  float v10; // xmm11_4
  int v11; // r15d
  float v12; // xmm6_4
  float v13; // xmm14_4
  float v14; // xmm7_4
  int v15; // r12d
  int v16; // r14d
  int v17; // r13d
  __int64 v18; // rsi
  float *v19; // rax
  float v20; // xmm9_4
  float v21; // xmm10_4
  __int64 v22; // rsi
  float *v23; // rax
  int v24; // r8d
  int v25; // r9d
  _BYTE *v26; // r14
  float v27; // xmm0_4
  int v28; // r13d
  __int64 v29; // rsi
  float *v30; // rax
  float v31; // xmm6_4
  char v32; // al
  __int64 v33; // r14
  __int64 v34; // rsi
  int v35; // eax
  int v36; // r8d
  __int64 v37; // rdx
  __int64 v38; // rcx
  _BYTE *v39; // rsi
  _BYTE *v40; // r12
  __int64 v41; // r13
  float v42; // xmm1_4
  float v43; // xmm0_4
  __int64 v44; // rax
  int v45; // eax
  __int64 v46; // rax
  _BYTE *v47; // rsi
  __int64 v48; // rax
  __int64 v49; // [rsp+58h] [rbp-B0h]
  float v50; // [rsp+60h] [rbp-A8h] BYREF
  float v51; // [rsp+64h] [rbp-A4h]
  _QWORD v52[3]; // [rsp+68h] [rbp-A0h] BYREF
  __int64 v54; // [rsp+180h] [rbp+78h] BYREF

  v3 = qword_18010C470;
  v4 = a3;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v5 = *(_QWORD *)(v3 + 5216);
  if ( !*(_BYTE *)(v5 + 209) )
  {
    i = &unk_1800D411C;
    v7 = &unk_1800D411C;
    if ( a1 != a2 )
    {
      i = a2;
      v7 = a1;
    }
    if ( !i )
      i = &v7[sub_1800B9730(v7)];
    v8 = *(float *)(v5 + 492);
    v9 = *(float *)(v5 + 336) + *(float *)(v5 + 284);
    v10 = *(float *)(v5 + 280);
    *(float *)&v54 = v9;
    if ( i - v7 <= 2000 || v8 >= 0.0 )
    {
      if ( v8 < 0.0 )
      {
        v31 = 0.0;
      }
      else if ( v8 == 0.0 )
      {
        v31 = fmaxf(*(float *)(v5 + 584) - v10, 1.0);
      }
      else if ( v8 <= 0.0 )
      {
        v31 = fmaxf(v8 - v10, 1.0);
      }
      else
      {
        v31 = fmaxf((float)((float)(*(float *)(v5 + 40) - *(float *)(v5 + 152)) + v8) - v10, 1.0);
      }
      sub_18003DF30((unsigned int)&v50, (_DWORD)v7, (_DWORD)i, 0, LODWORD(v31));
      v52[1] = __PAIR64__(LODWORD(v9), LODWORD(v10));
      *((float *)&v52[2] + 1) = v51 + v9;
      *(float *)&v52[2] = v50 + v10;
      sub_18004AAD0(&v50);
      sub_18004A070(&v52[1], 0, 0, 0);
      if ( v32 )
      {
        v54 = v52[1];
        if ( !i )
          i = &v7[sub_1800B9730(v7)];
        if ( v7 != i )
        {
          v33 = qword_18010C470;
          v34 = qword_18010C470;
          *(_OWORD *)&v52[1] = *(_OWORD *)(qword_18010C470 + 3424);
          *((float *)&v52[2] + 1) = _mm_shuffle_ps(*(__m128 *)&v52[1], *(__m128 *)&v52[1], 255).m128_f32[0]
                                  * *(float *)(qword_18010C470 + 3148);
          sub_180036620(&v52[1]);
          if ( (v35 & 0xFF000000) != 0 && *v7 )
          {
            v37 = *(_QWORD *)(*(_QWORD *)(v33 + 5216) + 712LL);
            v38 = *(_QWORD *)(v33 + 4416);
            if ( !v38 )
              v38 = *(_QWORD *)(*(_QWORD *)(v37 + 56) + 24LL);
            *(_OWORD *)&v52[1] = *(_OWORD *)(v37 + 96);
            sub_180067670(
              v38,
              v37,
              v36,
              (unsigned int)&v54,
              v35,
              (__int64)&v52[1],
              (__int64)v7,
              (__int64)i,
              LODWORD(v31),
              0);
            v33 = qword_18010C470;
          }
          if ( *(_BYTE *)(v34 + 10080) )
          {
            v39 = *(_BYTE **)(v33 + 10120);
            v40 = *(_BYTE **)(v33 + 10128);
            v41 = *(_QWORD *)(v33 + 5216);
            *(_QWORD *)(v33 + 10128) = 0;
            *(_QWORD *)(v33 + 10120) = 0;
            if ( !i )
            {
              for ( i = v7; i != (_BYTE *)-1LL; ++i )
              {
                if ( !*i || *i == 35 && i[1] == 35 )
                  break;
              }
            }
            v42 = *((float *)&v54 + 1);
            v43 = *(float *)(v33 + 3216) + *(float *)(v33 + 10136);
            *(_DWORD *)(v33 + 10136) = HIDWORD(v54);
            if ( v42 > (float)(v43 + 1.0) )
            {
              sub_180051790("\r\n");
              *(_BYTE *)(v33 + 10140) = 1;
            }
            if ( v39 )
            {
              v44 = sub_1800B9730(v39);
              sub_180051A10((__int64)&v54, v39, &v39[v44]);
            }
            v45 = *(_DWORD *)(v41 + 416);
            if ( *(_DWORD *)(v33 + 10144) > v45 )
              *(_DWORD *)(v33 + 10144) = v45;
            while ( 1 )
            {
              v46 = sub_1800B8A30(v7, 10, i - v7);
              v47 = i;
              if ( v46 )
                v47 = (_BYTE *)v46;
              if ( v7 == v47 && v47 == i )
                break;
              sub_180051790("%*s%.*s");
              *(_BYTE *)(v33 + 10140) = 0;
              if ( *v47 == 10 )
              {
                sub_180051790("\r\n");
                *(_BYTE *)(v33 + 10140) = 1;
              }
              if ( v47 == i )
                break;
              v7 = v47 + 1;
            }
            if ( v40 )
            {
              v48 = sub_1800B9730(v40);
              sub_180051A10((__int64)&v54, v40, &v40[v48]);
            }
          }
        }
      }
    }
    else
    {
      v11 = 0;
      v12 = 0.0;
      v13 = *(float *)(v3 + 4432);
      v14 = v9;
      v50 = 0.0;
      v49 = __PAIR64__(LODWORD(v9), LODWORD(v10));
      if ( !*(_BYTE *)(v3 + 10080) )
      {
        *((float *)&v49 + 1) = v9;
        v15 = (int)(float)((float)(*(float *)(v5 + 612) - v9) / v13);
        if ( v15 > 0 )
        {
          v16 = 0;
          if ( v7 < i )
          {
            v17 = v4 & 1;
            do
            {
              if ( v16 >= v15 )
                break;
              v18 = sub_1800B8A30(v7, 10, i - v7);
              if ( !v18 )
                v18 = (__int64)i;
              if ( !v17 )
              {
                sub_18003DF30((unsigned int)&v52[1], (_DWORD)v7, v18, 0, -1082130432);
                v12 = fmaxf(v12, *v19);
                v50 = v12;
              }
              v7 = (_BYTE *)(v18 + 1);
              ++v16;
            }
            while ( v18 + 1 < (unsigned __int64)i );
            v4 = a3;
          }
          v14 = (float)((float)v16 * v13) + v9;
          *((float *)&v49 + 1) = v14;
        }
      }
      if ( v7 < i )
      {
        v20 = v13 + v14;
        v21 = v14;
        do
        {
          v22 = qword_18010C470;
          v23 = *(float **)(qword_18010C470 + 5216);
          if ( (v20 <= v23[153] || v23[155] <= v21 || (float)(v10 + 3.4028235e38) <= v23[152] || v23[154] <= v10)
            && !*(_BYTE *)(qword_18010C470 + 5330) )
          {
            break;
          }
          v26 = (_BYTE *)sub_1800B8A30(v7, 10, i - v7);
          if ( !v26 )
            v26 = i;
          if ( v7 == v26 )
          {
            v27 = 0.0;
          }
          else
          {
            sub_180067070(
              *(_QWORD *)(v22 + 4416),
              (unsigned int)v52,
              v24,
              v25,
              -1082130432,
              (__int64)v7,
              (__int64)v26,
              0);
            v27 = (float)(int)(float)(*(float *)v52 + 0.99998999);
            *(float *)v52 = v27;
          }
          v12 = fmaxf(v12, v27);
          v50 = v12;
          sub_180037440(v49, v7, v26, 0);
          v14 = v14 + v13;
          v7 = v26 + 1;
          v21 = v21 + v13;
          v20 = v20 + v13;
          *((float *)&v49 + 1) = v14;
        }
        while ( v26 + 1 < i );
        LODWORD(v9) = v54;
        if ( v7 < i )
        {
          v28 = v4 & 1;
          do
          {
            v29 = sub_1800B8A30(v7, 10, i - v7);
            if ( !v29 )
              v29 = (__int64)i;
            if ( !v28 )
            {
              sub_18003DF30((unsigned int)&v54, (_DWORD)v7, v29, 0, -1082130432);
              v12 = fmaxf(v12, *v30);
              v50 = v12;
            }
            v7 = (_BYTE *)(v29 + 1);
            ++v11;
          }
          while ( v29 + 1 < (unsigned __int64)i );
        }
        v14 = v14 + (float)((float)v11 * v13);
      }
      v52[1] = __PAIR64__(LODWORD(v9), LODWORD(v10));
      v51 = v14 - v9;
      *(float *)&v52[2] = v10 + v12;
      *((float *)&v52[2] + 1) = (float)(v14 - v9) + v9;
      sub_18004AAD0(&v50);
      sub_18004A070(&v52[1], 0, 0, 0);
    }
  }
}
