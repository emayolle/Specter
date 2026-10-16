// sub_18003AA50 size=942
int *__fastcall sub_18003AA50(__int64 a1)
{
  __int64 v2; // rsi
  int *v3; // rbx
  int v4; // ebp
  __int64 v5; // r8
  int **v6; // r9
  int **v7; // rcx
  unsigned __int64 v8; // rdx
  int v9; // ecx
  int v10; // r8d
  int v11; // r8d
  int v12; // eax
  int v13; // ecx
  int v14; // ecx
  __int64 v15; // rdx
  int v16; // ecx
  int v17; // ecx
  __int64 v18; // rdx
  int v19; // ecx
  int v20; // ecx
  __int64 v21; // rdx
  int v22; // ecx
  int v23; // ecx
  __int64 v24; // rdx
  int v25; // r8d
  int v26; // ecx
  __int64 v27; // rcx
  __int64 v28; // rax
  __int128 v30; // [rsp+20h] [rbp-58h] BYREF
  char v31; // [rsp+80h] [rbp+8h] BYREF
  int *v32; // [rsp+88h] [rbp+10h] BYREF
  char *v33; // [rsp+90h] [rbp+18h]
  int *v34; // [rsp+98h] [rbp+20h]

  v2 = qword_18010C470;
  v3 = *(int **)(a1 + 80);
  v4 = 8;
  if ( !v3 )
  {
    v3 = (int *)sub_18003A810(224);
    v32 = v3;
    v33 = &v31;
    v34 = v3;
    if ( v3 )
    {
      *(_QWORD *)v3 = 0;
      *((_QWORD *)v3 + 1) = 0;
      *((_QWORD *)v3 + 2) = 0;
      *((_QWORD *)v3 + 3) = 0;
      *((_QWORD *)v3 + 4) = 0;
      *((_QWORD *)v3 + 5) = 0;
      *((_QWORD *)v3 + 10) = 0;
      *((_QWORD *)v3 + 11) = 0;
      *((_QWORD *)v3 + 12) = 0;
      *((_QWORD *)v3 + 13) = 0;
      *((_QWORD *)v3 + 14) = 0;
      *((_QWORD *)v3 + 15) = 0;
      *(_OWORD *)(v3 + 34) = 0;
      *((_QWORD *)v3 + 19) = 0;
      *((_QWORD *)v3 + 20) = 0;
      *((_QWORD *)v3 + 21) = 0;
      *((_QWORD *)v3 + 22) = 0;
      *((_QWORD *)v3 + 23) = 0;
      *((_QWORD *)v3 + 24) = 0;
      *((_QWORD *)v3 + 25) = 0;
      sub_1800B9280(v3, 0, 224);
      v5 = *((_QWORD *)v3 + 7);
      if ( v5 )
      {
        v6 = *(int ***)(v5 + 96);
        v7 = v6;
        v8 = (unsigned __int64)&v6[*(int *)(v5 + 88)];
        if ( (unsigned __int64)v6 < v8 )
        {
          while ( *v7 != v3 )
          {
            if ( (unsigned __int64)++v7 >= v8 )
              goto LABEL_11;
          }
          if ( (unsigned __int64)v7 < v8 - 8 )
            *(int **)((char *)v6 + (((char *)v7 - (char *)v6) & 0xFFFFFFFFFFFFFFF8uLL)) = *(int **)(v8 - 8);
          --*(_DWORD *)(v5 + 88);
        }
      }
LABEL_11:
      *((_QWORD *)v3 + 7) = v2 + 4456;
      if ( v2 != -4456 )
      {
        v9 = *(_DWORD *)(v2 + 4548);
        v10 = *(_DWORD *)(v2 + 4544);
        if ( v10 == v9 )
        {
          v11 = v10 + 1;
          if ( v9 )
            v12 = v9 + v9 / 2;
          else
            v12 = 8;
          if ( v12 > v11 )
            v11 = v12;
          sub_180054080(v2 + 4544, (unsigned int)v11);
        }
        *(_QWORD *)(*(_QWORD *)(v2 + 4552) + 8LL * (int)(*(_DWORD *)(v2 + 4544))++) = v3;
      }
    }
    else
    {
      v3 = nullptr;
    }
    *((_QWORD *)v3 + 27) = "##Foreground";
    *(_QWORD *)(a1 + 80) = v3;
  }
  if ( *(_DWORD *)(a1 + 68) != *(_DWORD *)(v2 + 5032) )
  {
    if ( v3[35] > 1 )
      sub_18005D2B0(v3 + 34, v3);
    sub_180069260(v3, 0);
    v13 = v3[5];
    if ( v13 < 0 )
    {
      v14 = v13 / 2 + v13;
      v15 = 0;
      if ( v14 > 0 )
        v15 = (unsigned int)v14;
      sub_180054650(v3 + 4, v15);
    }
    v3[4] = 0;
    sub_180069130(v3 + 8, 0);
    v3[12] = *(_DWORD *)(*((_QWORD *)v3 + 7) + 52LL);
    *((_OWORD *)v3 + 6) = 0;
    *((_OWORD *)v3 + 7) = 0;
    *((_QWORD *)v3 + 16) = 0;
    v3[13] = 0;
    *((_QWORD *)v3 + 8) = 0;
    *((_QWORD *)v3 + 9) = 0;
    v16 = v3[41];
    if ( v16 < 0 )
    {
      v17 = v16 / 2 + v16;
      v18 = 0;
      if ( v17 > 0 )
        v18 = (unsigned int)v17;
      sub_180054C20(v3 + 40, v18);
    }
    v3[40] = 0;
    v19 = v3[45];
    if ( v19 < 0 )
    {
      v20 = v19 / 2 + v19;
      v21 = 0;
      if ( v20 > 0 )
        v21 = (unsigned int)v20;
      sub_180054C20(v3 + 44, v21);
    }
    v3[44] = 0;
    sub_1800542F0(v3 + 48, 0);
    v22 = v3[21];
    if ( v22 < 0 )
    {
      v23 = v22 / 2 + v22;
      v24 = 0;
      if ( v23 > 0 )
        v24 = (unsigned int)v23;
      sub_180054080(v3 + 20, v24);
    }
    v3[20] = 0;
    v3[34] = 0;
    v3[35] = 1;
    v25 = v3[1];
    if ( *v3 == v25 )
    {
      v26 = *v3 + 1;
      if ( v25 )
        v4 = v25 + v25 / 2;
      if ( v4 > v26 )
        v26 = v4;
      sub_180054DD0(v3, (unsigned int)v26);
    }
    v27 = 9LL * *v3;
    v28 = *((_QWORD *)v3 + 1);
    *(_OWORD *)(v28 + 8 * v27) = 0;
    *(_OWORD *)(v28 + 8 * v27 + 16) = 0;
    *(_OWORD *)(v28 + 8 * v27 + 32) = 0;
    *(_OWORD *)(v28 + 8 * v27 + 48) = 0;
    *(_QWORD *)(v28 + 8 * v27 + 64) = 0;
    ++*v3;
    v3[52] = *(_DWORD *)(*((_QWORD *)v3 + 7) + 48LL);
    v30 = *(_OWORD *)(*(_QWORD *)(v2 + 64) + 40LL);
    sub_18005A8C0(v3, &v30);
    *(float *)&v32 = *(float *)(a1 + 16) + *(float *)(a1 + 8);
    *((float *)&v32 + 1) = *(float *)(a1 + 20) + *(float *)(a1 + 12);
    sub_18005A5E0(v3, a1 + 8, &v32, 0);
    *(_DWORD *)(a1 + 68) = *(_DWORD *)(v2 + 5032);
  }
  return v3;
}
