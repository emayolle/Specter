// sub_180051A10 size=462
__int64 __fastcall sub_180051A10(__int64 a1, _BYTE *a2, _BYTE *i)
{
  __int64 v6; // rsi
  __int64 v7; // rdi
  _BYTE *v8; // r15
  __int64 v9; // r14
  bool v10; // dl
  __int64 v11; // rax
  int v12; // eax
  __int64 result; // rax
  _BYTE *v14; // rdi

  while ( 1 )
  {
    v6 = qword_18010C470;
    v7 = *(_QWORD *)(qword_18010C470 + 10120);
    v8 = *(_BYTE **)(qword_18010C470 + 10128);
    v9 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    *(_QWORD *)(v6 + 10120) = 0;
    if ( !i )
    {
      for ( i = a2; i != (_BYTE *)-1LL; ++i )
      {
        if ( !*i || *i == 35 && i[1] == 35 )
          break;
      }
    }
    if ( a1 )
    {
      v10 = *(float *)(a1 + 4) > (float)((float)(*(float *)(v6 + 10136) + *(float *)(v6 + 3216)) + 1.0);
      *(_DWORD *)(v6 + 10136) = *(_DWORD *)(a1 + 4);
      if ( v10 )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v6 + 10140) = 1;
      }
    }
    if ( v7 )
    {
      v11 = sub_1800B9730(v7);
      sub_180051A10(a1, v7, v11 + v7);
    }
    v12 = *(_DWORD *)(v9 + 416);
    if ( *(_DWORD *)(v6 + 10144) > v12 )
      *(_DWORD *)(v6 + 10144) = v12;
    while ( 1 )
    {
      result = sub_1800B8A30(a2, 10, i - a2);
      v14 = i;
      if ( result )
        v14 = (_BYTE *)result;
      if ( a2 == v14 && v14 == i )
        break;
      result = sub_180051790("%*s%.*s");
      *(_BYTE *)(v6 + 10140) = 0;
      if ( *v14 == 10 )
      {
        result = sub_180051790("\r\n");
        *(_BYTE *)(v6 + 10140) = 1;
      }
      if ( v14 == i )
        break;
      a2 = v14 + 1;
    }
    if ( !v8 )
      break;
    a2 = v8;
    i = &v8[sub_1800B9730(v8)];
  }
  return result;
}
