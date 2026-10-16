// sub_1800A67C8 size=481
__int64 __fastcall sub_1800A67C8(
        _BYTE *a1,
        unsigned __int64 a2,
        int a3,
        char a4,
        int a5,
        __int64 a6,
        unsigned __int8 a7,
        __int64 a8)
{
  int v8; // eax
  __int64 v9; // rbp
  unsigned __int64 v11; // r15
  __int64 v14; // r8
  _BYTE *v15; // rbx
  _BYTE *v16; // rbx
  __int64 v17; // rdx
  _BYTE *v18; // rcx
  int v19; // r8d

  v8 = 0;
  v9 = a3;
  v11 = a2;
  if ( a3 > 0 )
    v8 = a3;
  if ( a2 > v8 + 9 )
  {
    if ( a7 )
    {
      a2 = (unsigned __int64)&a1[*(_DWORD *)a6 == 45];
      if ( a3 > 0 )
      {
        v14 = -1;
        do
          ++v14;
        while ( *(_BYTE *)(a2 + v14) );
        sub_1800B8BD0(a2 + 1, a2, v14 + 1);
      }
    }
    v15 = a1;
    if ( *(_DWORD *)a6 == 45 )
    {
      *a1 = 45;
      v15 = a1 + 1;
    }
    if ( (int)v9 > 0 )
    {
      *v15 = v15[1];
      ++v15;
      if ( !*(_BYTE *)(a8 + 40) )
        sub_18009BCF0(a8, a2);
      *v15 = ***(_BYTE ***)(*(_QWORD *)(a8 + 24) + 248LL);
    }
    v16 = &v15[v9 + (a7 ^ 1LL)];
    v17 = v11 + a1 - v16;
    if ( v11 == -1 )
      v17 = -1;
    if ( (unsigned int)sub_1800A5550(v16, v17, "e+000") )
    {
      sub_1800A5C54(0, 0, 0, 0, 0);
      JUMPOUT(0x1800A69A8LL);
    }
    v18 = v16 + 2;
    if ( a4 )
      *v16 = 69;
    if ( **(_BYTE **)(a6 + 8) != 48 )
    {
      v19 = *(_DWORD *)(a6 + 4) - 1;
      if ( v19 < 0 )
      {
        v19 = 1 - *(_DWORD *)(a6 + 4);
        v16[1] = 45;
      }
      if ( v19 >= 100 )
      {
        v16[2] += v19 / 100;
        v19 %= 100;
      }
      if ( v19 >= 10 )
      {
        v16[3] += v19 / 10;
        LOBYTE(v19) = v19 % 10;
      }
      v16[4] += v19;
    }
    if ( a5 == 2 && *v18 == 48 )
      sub_1800B8BD0(v18, v16 + 3, 3);
    return 0;
  }
  else
  {
    *(_BYTE *)(a8 + 48) = 1;
    *(_DWORD *)(a8 + 44) = 34;
    sub_1800A5B7C(0, 0, 0, 0, 0, a8);
    return 34;
  }
}
