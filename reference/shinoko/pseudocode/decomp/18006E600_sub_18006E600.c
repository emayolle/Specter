// sub_18006E600 size=1417
__int64 sub_18006E600()
{
  __int64 v0; // r13
  __int64 v1; // rdi
  __int64 v2; // rdx
  __int64 v3; // rbx
  int v4; // ecx
  float v5; // xmm7_4
  int v6; // r12d
  char v7; // al
  float v8; // xmm7_4
  int v9; // r12d
  int v10; // esi
  unsigned int v11; // r15d
  float v12; // xmm9_4
  __int64 v13; // r14
  __int64 v14; // rdx
  float v15; // xmm6_4
  int v16; // eax
  float v17; // xmm6_4
  float v18; // xmm0_4
  unsigned int v19; // ebp
  float v20; // xmm2_4
  char v21; // al
  char v22; // al
  __int64 v23; // r8
  __int64 v24; // rdx
  unsigned int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // r8d
  __int64 v29; // rax
  __int128 v30; // xmm1
  float v31; // xmm0_4
  __int64 result; // rax
  __int64 v33; // rcx
  float v34[4]; // [rsp+30h] [rbp-D8h] BYREF
  __m128 v35; // [rsp+40h] [rbp-C8h] BYREF
  char v36; // [rsp+110h] [rbp+8h] BYREF
  char v37; // [rsp+118h] [rbp+10h] BYREF
  float v38; // [rsp+120h] [rbp+18h] BYREF
  float v39; // [rsp+124h] [rbp+1Ch]
  float v40; // [rsp+128h] [rbp+20h] BYREF
  float v41; // [rsp+12Ch] [rbp+24h]

  v0 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v1 = *(_QWORD *)(v0 + 5216);
  v2 = *(int *)(v1 + 496);
  v3 = *(_QWORD *)(v1 + 456);
  if ( (int)v2 > 0 )
  {
    v4 = *(_DWORD *)(*(_QWORD *)(v1 + 504) + 4 * v2 - 4);
    *(_DWORD *)(v1 + 496) = v2 - 1;
    *(_DWORD *)(v1 + 488) = v4;
  }
  else
  {
    sub_180049A30("Calling PopItemWidth() too many times!");
  }
  if ( *(int *)(v3 + 16) > 1 )
  {
    sub_18003CD50();
    sub_18005D2B0(v3 + 112, *(_QWORD *)(v1 + 712));
  }
  v5 = fmaxf(*(float *)(v3 + 32), *(float *)(v1 + 284));
  v6 = *(_DWORD *)(v3 + 4);
  *(float *)(v3 + 32) = v5;
  *(float *)(v1 + 284) = v5;
  if ( (v6 & 0x10) == 0 )
    *(_DWORD *)(v1 + 304) = *(_DWORD *)(v3 + 40);
  v7 = 0;
  if ( (v6 & 1) == 0 && !*(_BYTE *)(v1 + 209) && *(int *)(v3 + 16) > 1 )
  {
    v8 = fminf(v5, *(float *)(v1 + 620));
    v9 = v6 & 2;
    v10 = 1;
    v11 = -1;
    v12 = fmaxf(*(float *)(v3 + 36), *(float *)(v1 + 612));
    while ( 1 )
    {
      v13 = *(_QWORD *)(v3 + 104);
      v14 = *(_QWORD *)(*(_QWORD *)(qword_18010C470 + 5216) + 456LL);
      if ( v14 )
      {
        if ( v10 >= 0 )
          v16 = v10;
        else
          v16 = *(_DWORD *)(v14 + 12);
        v15 = (float)((float)(*(float *)(v14 + 24) - *(float *)(v14 + 20))
                    * *(float *)(*(_QWORD *)(v14 + 104) + 28LL * v16))
            + *(float *)(v14 + 20);
      }
      else
      {
        v15 = 0.0;
      }
      v17 = v15 + *(float *)(v1 + 40);
      v18 = *(float *)(v0 + 4448) * 4.0;
      v19 = v10 + *(_DWORD *)v3;
      v34[1] = v12;
      v34[3] = v8;
      v20 = (float)(int)v18;
      v34[0] = v17 - v20;
      v34[2] = v20 + v17;
      sub_18004A070(v34, v19, 0, 2);
      if ( !v21 )
        goto LABEL_30;
      v22 = 0;
      v37 = 0;
      v36 = 0;
      if ( !v9
        && ((sub_18006F740((unsigned int)v34, v19, (unsigned int)&v37, (unsigned int)&v36, 0), (v22 = v37) != 0) || v36) )
      {
        v23 = qword_18010C470;
        *(_DWORD *)(qword_18010C470 + 9240) = 4;
        if ( v36 )
        {
          v24 = 29;
          v25 = v10;
          if ( (*(_BYTE *)(v13 + 28LL * v10 + 8) & 2) != 0 )
            v25 = v11;
          v11 = v25;
          goto LABEL_29;
        }
        v22 = v37;
      }
      else
      {
        v23 = qword_18010C470;
      }
      v24 = (v22 != 0) + 27LL;
LABEL_29:
      v39 = v8;
      v41 = v12 + 1.0;
      v35 = *(__m128 *)(v23 + 16 * v24 + 3424);
      v35.m128_f32[3] = _mm_shuffle_ps(v35, v35, 255).m128_f32[0] * *(float *)(v23 + 3148);
      v38 = (float)(int)v17;
      v40 = v38;
      sub_180036620(&v35);
      sub_18005C320(*(_QWORD *)(v1 + 712), (unsigned int)&v40, (unsigned int)&v38, v26, 1065353216);
LABEL_30:
      v27 = *(_DWORD *)(v3 + 16);
      if ( ++v10 >= v27 )
      {
        if ( v11 == -1 )
        {
          v7 = 0;
        }
        else
        {
          if ( !*(_BYTE *)(v3 + 9) )
          {
            v28 = 0;
            if ( v27 + 1 > 0 )
            {
              do
              {
                v29 = v28++;
                *(_DWORD *)(*(_QWORD *)(v3 + 104) + 28 * v29 + 4) = *(_DWORD *)(*(_QWORD *)(v3 + 104) + 28 * v29);
              }
              while ( v28 < *(_DWORD *)(v3 + 16) + 1 );
            }
          }
          *(_BYTE *)(v3 + 9) = 1;
          LOBYTE(v38) = 1;
          sub_18006E380(v11);
          v7 = LOBYTE(v38);
        }
        break;
      }
    }
  }
  *(_BYTE *)(v3 + 9) = v7;
  *(_OWORD *)(v1 + 576) = *(_OWORD *)(v1 + 592);
  v30 = *(_OWORD *)(v3 + 76);
  v31 = *(float *)(v1 + 348) + *(float *)(v1 + 40);
  *(_QWORD *)(v1 + 456) = 0;
  *(_DWORD *)(v1 + 352) = 0;
  *(_OWORD *)(v1 + 592) = v30;
  result = qword_18010C470;
  *(float *)(v1 + 280) = (float)(int)(float)(v31 + 0.0);
  v33 = *(_QWORD *)(result + 5216);
  *(_BYTE *)(v33 + 376) = !*(_QWORD *)(result + 8856) && !*(_QWORD *)(v33 + 456);
  return result;
}
