// sub_18003D9E0 size=1345
__int64 sub_18003D9E0()
{
  __int64 v0; // r15
  __int64 result; // rax
  __int64 v2; // rbx
  __int64 v3; // rax
  __int64 v4; // rdi
  __int64 *v5; // rsi
  __int64 v6; // rax
  __int64 *v7; // rbp
  __int64 v8; // rdi
  __int64 v9; // rbx
  __int64 v10; // rcx
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rsi
  __int64 v16; // rdi
  __int64 *v17; // rbx
  __int64 v18; // rax
  __int64 *v19; // rbp
  __int64 v20; // rcx
  unsigned int v21; // edx
  __int64 *v22; // r14
  __int64 v23; // rax
  __int64 *v24; // rbp
  __int64 v25; // rsi
  int *v26; // rcx
  __int64 v27; // rdi
  int *v28; // rbx
  __int64 v29; // rax
  int v30; // ecx
  __int64 v31; // rdx
  int v32; // eax
  int *v33; // rax
  int **v34; // r9
  int **i; // r10
  int *v36; // r8
  int j; // ecx
  __int64 v38; // rax
  __int64 v39; // rsi
  __int64 v40; // rax
  __int64 v41; // rbp
  __int64 v42; // rbx
  __int64 k; // rdi
  _DWORD *v44; // rdx
  int v45; // eax
  __int64 v46; // rbx
  __int64 v47; // rdi

  v0 = qword_18010C470;
  if ( *(_DWORD *)(qword_18010C470 + 5036) != *(_DWORD *)(qword_18010C470 + 5032) )
    sub_18003D360();
  result = *(unsigned int *)(v0 + 5032);
  if ( *(_DWORD *)(v0 + 5040) != (_DWORD)result )
  {
    *(_DWORD *)(v0 + 5040) = result;
    *(_DWORD *)(v0 + 196) = 0;
    v2 = *(_QWORD *)(v0 + 9984);
    v3 = 32LL * *(int *)(v0 + 9976);
    v4 = v3 + v2;
    if ( v3 )
    {
      do
      {
        if ( *(_DWORD *)(v2 + 4) == 4 )
          (*(void (__fastcall **)(__int64, __int64))(v2 + 16))(v0, v2);
        v2 += 32;
      }
      while ( v2 != v4 );
    }
    v5 = *(__int64 **)(v0 + 8104);
    v6 = *(int *)(v0 + 8096);
    v7 = &v5[v6];
    if ( v6 * 8 )
    {
      do
      {
        v8 = *v5;
        v9 = qword_18010C470;
        v10 = *v5 + 104;
        v11 = *v5 + 176;
        *(_QWORD *)(v8 + 160) = v10;
        *(_QWORD *)(v8 + 168) = v11;
        sub_180054240(v10, 0);
        sub_180054240(*(_QWORD *)(v8 + 168), 0);
        v12 = qword_18010C470;
        *(_BYTE *)(v8 + 88) = 1;
        *(_QWORD *)(v8 + 92) = 0;
        *(_DWORD *)(v8 + 100) = 0;
        *(_OWORD *)(v8 + 120) = *(_OWORD *)(v8 + 8);
        *(_QWORD *)(v8 + 136) = *(_QWORD *)(v9 + 24);
        *(_QWORD *)(v8 + 144) = v8;
        *(_QWORD *)(v8 + 152) = v12 + 3120;
        if ( *(_QWORD *)(v8 + 72) )
        {
          v13 = sub_18003A960(v8, 0, "##Background");
          sub_18005D720(v8 + 88, *(_QWORD *)(v8 + 160), v13);
        }
        ++v5;
      }
      while ( v5 != v7 );
    }
    sub_18003CFF0();
    v14 = *(_QWORD *)(v0 + 8592);
    if ( !v14 || (*(_DWORD *)(v14 + 20) & 0x2000) != 0 )
    {
      v15 = 0;
      if ( v14 )
        v16 = *(_QWORD *)(v0 + 8608);
      else
        v16 = 0;
    }
    else
    {
      v15 = *(_QWORD *)(v14 + 960);
      v16 = *(_QWORD *)(v0 + 8608);
    }
    v17 = *(__int64 **)(v0 + 5128);
    v18 = *(int *)(v0 + 5120);
    v19 = &v17[v18];
    if ( v18 * 8 )
    {
      do
      {
        v20 = *v17;
        if ( *(_BYTE *)(*v17 + 204) )
        {
          if ( !*(_BYTE *)(v20 + 212) )
          {
            v21 = *(_DWORD *)(v20 + 20);
            if ( (v21 & 0x1000000) == 0 && v20 != v15 && v20 != v16 )
              sub_18003CC00(v20, (v21 >> 25) & 1);
          }
        }
        ++v17;
      }
      while ( v17 != v19 );
    }
    if ( v15 && *(_BYTE *)(v15 + 204) && !*(_BYTE *)(v15 + 212) )
      sub_18003CC00(v15, (*(_DWORD *)(v15 + 20) >> 25) & 1);
    if ( v16 && *(_BYTE *)(v16 + 204) && !*(_BYTE *)(v16 + 212) )
      sub_18003CC00(v16, (*(_DWORD *)(v16 + 20) >> 25) & 1);
    if ( *(_BYTE *)(v0 + 88) && *(_DWORD *)(v0 + 9240) != -1 )
      sub_1800389B0(*(_QWORD *)(v0 + 224));
    *(_QWORD *)(v0 + 188) = 0;
    v22 = *(__int64 **)(v0 + 8104);
    v23 = *(int *)(v0 + 8096);
    v24 = &v22[v23];
    if ( v23 * 8 )
    {
      do
      {
        v25 = *v22;
        v26 = *(int **)(*v22 + 160);
        v27 = *v26;
        sub_180054240(v26, (unsigned int)(v27 + **(_DWORD **)(*v22 + 168)));
        v28 = *(int **)(v25 + 168);
        v29 = *v28;
        if ( (_DWORD)v29 )
        {
          sub_1800B8BD0(*(_QWORD *)(*(_QWORD *)(v25 + 160) + 8LL) + 8 * v27, *((_QWORD *)v28 + 1), 8 * v29);
          v30 = v28[1];
          if ( v30 < 0 )
          {
            v31 = 0;
            v32 = v30 + ((v30 + 1) >> 1);
            if ( v32 > 0 )
              v31 = (unsigned int)v32;
            sub_180054080(v28, v31);
          }
          *v28 = 0;
        }
        if ( *(_QWORD *)(v25 + 80) )
        {
          v33 = sub_18003AA50(v25);
          sub_18005D720(v25 + 88, *(_QWORD *)(v25 + 160), v33);
        }
        v34 = *(int ***)(v25 + 112);
        for ( i = &v34[*(int *)(v25 + 104)]; v34 != i; ++v34 )
        {
          v36 = *v34;
          for ( j = **v34; j > 0; *v36 = --j )
          {
            v38 = *((_QWORD *)v36 + 1);
            if ( *(_DWORD *)(v38 + 72LL * (unsigned int)j - 32) )
              break;
            if ( *(_QWORD *)(v38 + 72LL * (unsigned int)j - 24) )
              break;
          }
        }
        ++v22;
        *(_DWORD *)(v0 + 188) += *(_DWORD *)(v25 + 100);
        *(_DWORD *)(v0 + 192) += *(_DWORD *)(v25 + 96);
      }
      while ( v22 != v24 );
    }
    if ( (*(_BYTE *)(v0 + 12) & 0x10) != 0 )
    {
      v39 = *(_QWORD *)(v0 + 4408);
      v40 = 8LL * *(int *)(v0 + 4400);
      v41 = v40 + v39;
      if ( v40 )
      {
        do
        {
          v42 = *(_QWORD *)(*(_QWORD *)v39 + 72LL);
          for ( k = v42 + 8LL * *(int *)(*(_QWORD *)v39 + 64LL); v42 != k; v42 += 8 )
          {
            v44 = *(_DWORD **)v42;
            v45 = *(_DWORD *)(*(_QWORD *)v42 + 4LL);
            if ( v45 == 2 )
            {
              if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
                sub_180052F00("[font] Texture #%03d: create %dx%d\n", *v44, v44[7], v44[8]);
            }
            else if ( v45 == 4 )
            {
              if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
                sub_180052F00(
                  "[font] Texture #%03d: destroy %dx%d, texid=0x%I64X, backend_data=%p\n",
                  *v44,
                  v44[7],
                  v44[8],
                  *((_QWORD *)v44 + 2),
                  *((const void **)v44 + 1));
            }
            else if ( v45 == 3 && qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
            {
              sub_180052F00(
                "[font] Texture #%03d: update %d regions, texid=0x%I64X, backend_data=0x%I64X\n",
                *v44,
                v44[16],
                *((_QWORD *)v44 + 2),
                *((_QWORD *)v44 + 1));
            }
          }
          v39 += 8;
        }
        while ( v39 != v41 );
      }
    }
    v46 = *(_QWORD *)(v0 + 9984);
    result = 32LL * *(int *)(v0 + 9976);
    v47 = result + v46;
    if ( result )
    {
      do
      {
        if ( *(_DWORD *)(v46 + 4) == 5 )
          result = (*(__int64 (__fastcall **)(__int64, __int64))(v46 + 16))(v0, v46);
        v46 += 32;
      }
      while ( v46 != v47 );
    }
  }
  return result;
}
