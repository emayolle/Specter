// sub_18004D450 size=1343
void __fastcall sub_18004D450(__int64 a1, unsigned int a2)
{
  __int64 v2; // r15
  __int64 v3; // r9
  __int64 v4; // rbp
  __int64 v5; // rdi
  __int64 v6; // rax
  __int64 v7; // rdx
  __int64 v8; // rcx
  __int64 v9; // r8
  __int64 v10; // rbx
  __int64 v11; // rax
  const char *v12; // r14
  const char *v13; // rdx
  __int64 v14; // rax
  __int64 v15; // rsi
  __int64 v16; // rcx
  __int64 v17; // rsi
  _QWORD *v18; // r10
  _QWORD *v19; // r9
  unsigned __int64 v20; // rcx
  _QWORD *v21; // rdi
  __int64 v22; // r9
  __int64 v23; // rdi
  __int64 v24; // rax
  int v25; // r10d
  __int64 v26; // r9
  int v27; // esi
  __int64 v28; // r11
  int v29; // r8d
  __int64 v30; // rdx
  __int64 v31; // rax
  int v32; // r9d
  int v33; // ebx
  __int64 v34; // r10
  int v35; // r8d
  __int64 v36; // rdx
  __int64 v37; // rax
  const char *v38; // r14
  __int64 v39; // rax
  __int64 v40; // r9
  __int64 v41; // r10
  int v42; // r8d
  int i; // r9d
  __int64 v44; // rdx
  __int64 v45; // rcx
  __int64 v46; // rdx
  __int64 v47; // r10
  __int64 v48; // rcx
  __int64 v49; // rcx

  v2 = qword_18010C470;
  v3 = a2;
  v4 = qword_18010C470;
  v5 = a1;
  if ( (a2 & 2) != 0 && *(_QWORD *)(qword_18010C470 + 8120) != a1 )
  {
    v6 = *(int *)(qword_18010C470 + 8048);
    if ( (int)v6 > 0 )
    {
      v7 = *(_QWORD *)(qword_18010C470 + 8056);
      v8 = 56 * v6;
      v9 = 56 * v6 + v7;
      if ( 56 * v6 )
      {
        do
        {
          v10 = *(_QWORD *)(v7 + 8);
          if ( v10 && (*(_DWORD *)(v10 + 20) & 0x8000000) != 0 && (*(_BYTE *)(v10 + 204) || *(_BYTE *)(v10 + 205)) )
          {
            if ( !v5 )
            {
LABEL_13:
              v12 = "<NULL>";
              if ( (*(_BYTE *)(qword_18010C470 + 10228) & 4) != 0 )
              {
                if ( v5 )
                  v13 = *(const char **)(v5 + 8);
                else
                  v13 = "<NULL>";
                sub_180052F00(
                  "[focus] FocusWindow(\"%s\", UnlessBelowModal): prevented by \"%s\".\n",
                  v13,
                  *(const char **)(v10 + 8));
                v2 = qword_18010C470;
              }
              if ( v5 )
              {
                v17 = *(_QWORD *)(v5 + 960);
                if ( v5 == v17 && (*(_DWORD *)(v5 + 20) & 0x2000) == 0 )
                {
                  v18 = *(_QWORD **)(v2 + 5128);
                  v19 = v18;
                  v20 = (unsigned __int64)&v18[*(int *)(v2 + 5120)];
                  if ( (unsigned __int64)v18 < v20 )
                  {
                    do
                    {
                      if ( *v19 == v17 )
                        break;
                      ++v19;
                    }
                    while ( (unsigned __int64)v19 < v20 );
                  }
                  v21 = *(_QWORD **)(v2 + 5128);
                  v22 = v19 - v18;
                  if ( (unsigned __int64)v18 < v20 )
                  {
                    do
                    {
                      if ( *v21 == *(_QWORD *)(v10 + 960) )
                        break;
                      ++v21;
                    }
                    while ( (unsigned __int64)v21 < v20 );
                  }
                  v23 = v21 - v18;
                  if ( (int)v22 >= (int)v23 )
                  {
                    sub_1800B8BD0(&v18[(int)v23 + 1], &v18[(int)v23], 8LL * ((int)v22 - (int)v23));
                    *(_QWORD *)(*(_QWORD *)(v2 + 5128) + 8LL * (int)v23) = v17;
                  }
                  else
                  {
                    sub_1800B8BD0(&v18[(int)v22], &v18[(int)v22 + 1], 8LL * ((int)v23 - (int)v22 - 1));
                    v8 = (int)v23;
                    *(_QWORD *)(*(_QWORD *)(v2 + 5128) + 8LL * (int)v23 - 8) = v17;
                  }
                }
              }
              v24 = sub_18004BE10(v8, v7, v9, v3);
              v25 = *(_DWORD *)(v2 + 8048);
              v26 = v24;
              if ( v25 )
              {
                v27 = 0;
                if ( v24 && v25 > 0 )
                {
                  v28 = *(_QWORD *)(v2 + 8056);
                  do
                  {
                    if ( *(_QWORD *)(v28 + 56LL * (unsigned int)v27 + 8) )
                    {
                      v29 = v27;
                      while ( 1 )
                      {
                        v30 = *(_QWORD *)(v28 + 56LL * v29 + 8);
                        if ( v30 )
                          break;
LABEL_51:
                        if ( ++v29 >= v25 )
                          goto LABEL_55;
                      }
                      v31 = v26;
                      if ( *(_QWORD *)(v26 + 960) != v30 )
                      {
                        while ( v31 != v30 )
                        {
                          v31 = *(_QWORD *)(v31 + 952);
                          if ( !v31 )
                            goto LABEL_51;
                        }
                      }
                    }
                    ++v27;
                  }
                  while ( v27 < v25 );
                }
                if ( v27 < v25 )
                {
LABEL_55:
                  if ( (*(_BYTE *)(v2 + 10228) & 8) != 0 )
                  {
                    if ( v26 )
                      v12 = *(const char **)(v26 + 8);
                    sub_180052F00("[popup] ClosePopupsOverWindow(\"%s\")\n", v12);
                  }
                  sub_18004C4C0(v27, 0);
                }
              }
              return;
            }
            v11 = v5;
            if ( *(_QWORD *)(v5 + 960) != v10 )
            {
              while ( v11 != v10 )
              {
                v11 = *(_QWORD *)(v11 + 952);
                if ( !v11 )
                  goto LABEL_13;
              }
            }
          }
          v7 += 56;
        }
        while ( v7 != v9 );
      }
    }
  }
  if ( (v3 & 1) != 0 )
  {
    if ( v5 )
    {
      v14 = *(_QWORD *)(v5 + 1000);
      if ( v14 )
      {
        if ( *(_BYTE *)(v14 + 205) )
          v5 = *(_QWORD *)(v5 + 1000);
      }
    }
  }
  v15 = 0;
  if ( *(_QWORD *)(qword_18010C470 + 8120) != v5 )
  {
    sub_18004D9C0(v5);
    if ( v5 )
    {
      if ( *(_BYTE *)(v2 + 8113) )
        *(_BYTE *)(v2 + 8114) = 1;
      *(_DWORD *)(v2 + 8116) = *(_DWORD *)(v5 + 1008);
      *(_DWORD *)(v2 + 8132) = 0;
      v16 = *(unsigned int *)(v5 + 1064);
    }
    else
    {
      *(_DWORD *)(v2 + 8116) = 0;
      v16 = 0;
      *(_DWORD *)(v2 + 8132) = 0;
    }
    sub_180045650(v16);
    *(_BYTE *)(v2 + 8115) = 0;
    *(_QWORD *)(v2 + 0x2000) = -1;
    v2 = qword_18010C470;
    v32 = *(_DWORD *)(qword_18010C470 + 8048);
    if ( v32 )
    {
      v33 = 0;
      if ( v5 && v32 > 0 )
      {
        v34 = *(_QWORD *)(qword_18010C470 + 8056);
        do
        {
          if ( *(_QWORD *)(v34 + 56LL * (unsigned int)v33 + 8) )
          {
            v35 = v33;
            while ( 1 )
            {
              v36 = *(_QWORD *)(v34 + 56LL * v35 + 8);
              if ( v36 )
                break;
LABEL_71:
              if ( ++v35 >= v32 )
                goto LABEL_75;
            }
            v37 = v5;
            if ( *(_QWORD *)(v5 + 960) != v36 )
            {
              while ( v37 != v36 )
              {
                v37 = *(_QWORD *)(v37 + 952);
                if ( !v37 )
                  goto LABEL_71;
              }
            }
          }
          ++v33;
        }
        while ( v33 < v32 );
      }
      if ( v33 < v32 )
      {
LABEL_75:
        if ( (*(_BYTE *)(qword_18010C470 + 10228) & 8) != 0 )
        {
          if ( v5 )
            v38 = *(const char **)(v5 + 8);
          else
            v38 = "<NULL>";
          sub_180052F00("[popup] ClosePopupsOverWindow(\"%s\")\n", v38);
        }
        sub_18004C4C0(v33, 0);
        v2 = qword_18010C470;
      }
    }
  }
  if ( v5 )
    v15 = *(_QWORD *)(v5 + 960);
  if ( *(_DWORD *)(v4 + 5332) )
  {
    v39 = *(_QWORD *)(v4 + 5368);
    if ( v39 )
    {
      if ( *(_QWORD *)(v39 + 960) != v15 && !*(_BYTE *)(v4 + 5346) )
      {
        sub_180039FD0(0, 0);
        v2 = qword_18010C470;
      }
    }
  }
  if ( v5 )
  {
    v40 = *(int *)(v2 + 5136);
    v41 = 8 * v40 - 8;
    if ( *(_QWORD *)(v41 + *(_QWORD *)(v2 + 5144)) != v15 )
    {
      v42 = *(__int16 *)(v15 + 226);
      for ( i = v40 - 1; v42 < i; --*(_WORD *)(v45 + 226) )
      {
        v44 = v42++;
        *(_QWORD *)(*(_QWORD *)(v2 + 5144) + 8 * v44) = *(_QWORD *)(*(_QWORD *)(v2 + 5144) + 8 * v44 + 8);
        v45 = *(_QWORD *)(*(_QWORD *)(v2 + 5144) + 8 * v44);
      }
      *(_QWORD *)(v41 + *(_QWORD *)(v2 + 5144)) = v15;
      *(_WORD *)(v15 + 226) = i;
    }
    if ( ((*(_DWORD *)(v5 + 20) | *(_DWORD *)(v15 + 20)) & 0x2000) == 0 )
    {
      v46 = *(int *)(v2 + 5120);
      v47 = *(_QWORD *)(v2 + 5128);
      v48 = *(_QWORD *)(v47 + 8 * v46 - 8);
      if ( v48 != v15 && *(_QWORD *)(v48 + 960) != v15 )
      {
        v49 = (unsigned int)(v46 - 2);
        if ( (int)v49 >= 0 )
        {
          while ( *(_QWORD *)(v47 + 8 * v49) != v15 )
          {
            v49 = (unsigned int)(v49 - 1);
            if ( (int)v49 < 0 )
              return;
          }
          sub_1800B8BD0(v47 + 8 * v49, v47 + 8LL * ((int)v49 + 1), 8LL * ((int)v46 + ~(_DWORD)v49));
          *(_QWORD *)(*(_QWORD *)(v2 + 5128) + 8LL * *(int *)(v2 + 5120) - 8) = v15;
        }
      }
    }
  }
}
