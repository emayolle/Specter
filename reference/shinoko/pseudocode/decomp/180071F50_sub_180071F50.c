// sub_180071F50 size=1450
void __fastcall sub_180071F50(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // rbx
  __int64 v5; // rdx
  int v6; // r8d
  char v7; // cl
  int v8; // edx
  __int64 v9; // r15
  float v10; // xmm0_4
  float v11; // xmm1_4
  char v12; // al
  int v13; // eax
  float v14; // xmm6_4
  float v15; // xmm7_4
  __int64 v16; // r13
  _DWORD *v17; // rax
  int v18; // xmm1_4
  int v19; // xmm2_4
  int v20; // xmm3_4
  int v21; // xmm4_4
  __int64 v22; // rax
  __int64 v23; // rcx
  __int64 v24; // rax
  __int64 v25; // rcx
  float v26; // xmm0_4
  char v27; // al
  int v28; // eax
  __int64 v29; // rsi
  __int64 v30; // rax
  _BYTE *v31; // rdi
  __int64 v32; // r12
  const char *v33; // r14
  const char *i; // rbx
  float v35; // xmm1_4
  float v36; // xmm0_4
  __int64 v37; // rax
  int v38; // eax
  __int64 v39; // rax
  const char *v40; // rdi
  _BYTE *v41; // rbx
  __int64 v42; // rax
  __int64 v43; // rdx
  _DWORD *v44; // r9
  _DWORD *v45; // rax
  int v46; // xmm1_4
  int v47; // xmm2_4
  int v48; // xmm3_4
  int v49; // xmm4_4
  __int64 v50; // rax
  __int64 v51; // rcx
  __int64 v52; // rax
  __int64 v53; // rcx
  float v54; // [rsp+30h] [rbp-9h] BYREF
  float v55; // [rsp+34h] [rbp-5h]
  float v56; // [rsp+38h] [rbp-1h] BYREF
  float v57; // [rsp+3Ch] [rbp+3h]
  __m128 v58; // [rsp+40h] [rbp+7h] BYREF
  __int64 v59; // [rsp+A0h] [rbp+67h] BYREF

  v4 = qword_18010C470;
  v5 = *(_QWORD *)(qword_18010C470 + 5216);
  if ( !*(_BYTE *)(v5 + 209) )
  {
    v6 = *(_DWORD *)(v5 + 468);
    v7 = 2 - (v6 != 0);
    if ( *(_QWORD *)(v5 + 456) )
    {
      v8 = 4;
      v7 = 6 - (v6 != 0);
    }
    else
    {
      v8 = 0;
    }
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v9 = *(_QWORD *)(v4 + 5216);
    if ( !*(_BYTE *)(v9 + 209) )
    {
      if ( (v7 & 2) != 0 )
      {
        v10 = *(float *)(v9 + 280);
        v55 = *(float *)(v9 + 284);
        v11 = v55 + *(float *)(v9 + 324);
        v54 = v10;
        v59 = 1065353216;
        v57 = v11;
        v56 = v10 + 1.0;
        sub_18004AAD0(&v59);
        sub_18004A070(&v54, 0, 0, 0);
        if ( v12 )
        {
          v58 = *(__m128 *)(qword_18010C470 + 3856);
          v58.m128_f32[3] = _mm_shuffle_ps(v58, v58, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
          sub_180036620(&v58);
          sub_18005C870(*(_QWORD *)(v9 + 712), (unsigned int)&v54, (unsigned int)&v56, v13, 0, 0);
          if ( *(_BYTE *)(v4 + 10080) )
            sub_180051790(" |");
        }
      }
      else if ( (v7 & 1) != 0 )
      {
        v14 = *(float *)(v9 + 584);
        v15 = *(float *)(v9 + 280);
        if ( v8 )
        {
          v16 = *(_QWORD *)(v9 + 456);
          if ( v16 )
          {
            v15 = *(float *)(v9 + 40) + *(float *)(v9 + 348);
            v14 = *(float *)(v9 + 40) + *(float *)(v9 + 48);
            if ( *(_DWORD *)(v16 + 16) != 1 )
            {
              *(_OWORD *)(v16 + 60) = *(_OWORD *)(v9 + 608);
              v17 = *(_DWORD **)(v9 + 712);
              v18 = *(_DWORD *)(v16 + 44);
              v19 = *(_DWORD *)(v16 + 48);
              v20 = *(_DWORD *)(v16 + 52);
              v21 = *(_DWORD *)(v16 + 56);
              *(_OWORD *)(v9 + 608) = *(_OWORD *)(v16 + 44);
              v17[24] = v18;
              v17[25] = v19;
              v17[26] = v20;
              v17[27] = v21;
              v22 = *(_QWORD *)(v9 + 712);
              v23 = *(int *)(v22 + 160);
              v24 = *(_QWORD *)(v22 + 168);
              v25 = 2 * (v23 - 1);
              *(_DWORD *)(v24 + 8 * v25) = v18;
              *(_DWORD *)(v24 + 8 * v25 + 4) = v19;
              *(_DWORD *)(v24 + 8 * v25 + 8) = v20;
              *(_DWORD *)(v24 + 8 * v25 + 12) = v21;
              sub_18005D640(v16 + 112, *(_QWORD *)(v9 + 712), 0, a4);
            }
          }
        }
        else
        {
          v16 = 0;
        }
        v26 = *(float *)(v9 + 284);
        v54 = v15;
        v55 = v26;
        v56 = v14;
        v59 = 0;
        v57 = v26 + 1.0;
        sub_18004AAD0(&v59);
        sub_18004A070(&v54, 0, 0, 0);
        if ( v27 )
        {
          v58 = *(__m128 *)(qword_18010C470 + 3856);
          v58.m128_f32[3] = _mm_shuffle_ps(v58, v58, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
          sub_180036620(&v58);
          sub_18005C870(*(_QWORD *)(v9 + 712), (unsigned int)&v54, (unsigned int)&v56, v28, 0, 0);
          if ( *(_BYTE *)(v4 + 10080) )
          {
            v29 = qword_18010C470;
            v30 = *(_QWORD *)(qword_18010C470 + 10128);
            v31 = *(_BYTE **)(qword_18010C470 + 10120);
            v32 = *(_QWORD *)(qword_18010C470 + 5216);
            *(_QWORD *)(qword_18010C470 + 10128) = 0;
            *(_QWORD *)(v29 + 10120) = 0;
            v33 = "--------------------------------\n";
            v59 = v30;
            for ( i = "--------------------------------\n"; i != (const char *)-1LL; ++i )
            {
              if ( !*i || *i == 35 && i[1] == 35 )
                break;
            }
            v35 = v55;
            v36 = *(float *)(v29 + 3216) + *(float *)(v29 + 10136);
            *(float *)(v29 + 10136) = v55;
            if ( v35 > (float)(v36 + 1.0) )
            {
              sub_180051790("\r\n");
              *(_BYTE *)(v29 + 10140) = 1;
            }
            if ( v31 )
            {
              v37 = sub_1800B9730(v31);
              sub_180051A10((__int64)&v54, v31, &v31[v37]);
            }
            v38 = *(_DWORD *)(v32 + 416);
            if ( *(_DWORD *)(v29 + 10144) > v38 )
              *(_DWORD *)(v29 + 10144) = v38;
            while ( 1 )
            {
              v39 = sub_1800B8A30(v33, 10, i - v33);
              v40 = i;
              if ( v39 )
                v40 = (const char *)v39;
              if ( v33 == v40 && v40 == i )
                break;
              sub_180051790("%*s%.*s");
              *(_BYTE *)(v29 + 10140) = 0;
              if ( *v40 == 10 )
              {
                sub_180051790("\r\n");
                *(_BYTE *)(v29 + 10140) = 1;
              }
              if ( v40 == i )
                break;
              v33 = v40 + 1;
            }
            v41 = (_BYTE *)v59;
            if ( v59 )
            {
              v42 = sub_1800B9730(v59);
              sub_180051A10((__int64)&v54, v41, &v41[v42]);
            }
          }
        }
        if ( v16 )
        {
          v43 = *(_QWORD *)(qword_18010C470 + 5216);
          v44 = *(_DWORD **)(v43 + 456);
          if ( v44[4] != 1 )
          {
            v45 = *(_DWORD **)(v43 + 712);
            v46 = v44[15];
            v47 = v44[16];
            v48 = v44[17];
            v49 = v44[18];
            *(_OWORD *)(v43 + 608) = *(_OWORD *)(v44 + 15);
            v45[24] = v46;
            v45[25] = v47;
            v45[26] = v48;
            v45[27] = v49;
            v50 = *(_QWORD *)(v43 + 712);
            v51 = *(int *)(v50 + 160);
            v52 = *(_QWORD *)(v50 + 168);
            v53 = 2 * (v51 - 1);
            *(_DWORD *)(v52 + 8 * v53) = v46;
            *(_DWORD *)(v52 + 8 * v53 + 4) = v47;
            *(_DWORD *)(v52 + 8 * v53 + 8) = v48;
            *(_DWORD *)(v52 + 8 * v53 + 12) = v49;
            sub_18005D640(v44 + 28, *(_QWORD *)(v43 + 712), (unsigned int)(v44[3] + 1), v44);
          }
          *(_DWORD *)(v16 + 28) = *(_DWORD *)(v9 + 284);
        }
      }
    }
  }
}
