// sub_18002DF80 size=585
__int64 sub_18002DF80()
{
  __int64 *v0; // rdi
  __int64 v2; // rcx
  __int64 v3; // rdx
  __int64 v4; // rcx
  unsigned __int64 v5; // rbx
  __int64 v6; // rsi
  _QWORD *v7; // rcx
  __int64 v8; // rcx
  char *v9; // rdx
  __int64 v10; // r9
  unsigned __int8 v11; // al
  unsigned int v12; // ebx
  unsigned __int64 v13; // rcx
  unsigned int v14; // ebx
  __int64 v15; // rdx
  unsigned __int64 v16; // rcx
  __int64 v17; // rbx
  __int64 i; // rdi
  __int64 v19; // rcx
  __int64 v20; // [rsp+40h] [rbp+8h] BYREF

  v0 = (__int64 *)sub_180003E20();
  if ( *v0 == v0[1] )
  {
    sub_18006F470("No modules registered.");
    return 1;
  }
  else
  {
    sub_18004AFD0();
    sub_180036FE0(13);
    HIDWORD(v20) = -2139095040;
    v2 = *(_QWORD *)(qword_18010C470 + 5216);
    *(float *)&v20 = *(float *)(v2 + 48) / 5.0;
    if ( (unsigned __int8)sub_180086B50(v2, &v20) )
    {
      v4 = *v0;
      if ( (v0[1] - *v0) >> 6 )
      {
        v5 = 0;
        do
        {
          v6 = (unsigned int)dword_18010C5BC;
          v7 = (_QWORD *)((v5 << 6) + v4);
          v20 = 0;
          if ( v7[3] > 0xFu )
            v7 = (_QWORD *)*v7;
          LOBYTE(v3) = v5 == dword_18010C5BC;
          if ( (unsigned __int8)sub_180084D20(v7, v3, 0, &v20) )
            dword_18010C5BC = v5;
          if ( v5 == v6 )
            sub_180045950();
          v4 = *v0;
          ++v5;
        }
        while ( v5 < (v0[1] - *v0) >> 6 );
      }
      sub_18003E7F0();
      sub_18004B190();
    }
    sub_1800371B0(1);
    sub_18004B190();
    sub_18004AC40();
    sub_18004AFD0();
    v8 = qword_18010C470;
    v9 = "#MainChild";
    v20 = 0;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v10 = *(_QWORD *)(v8 + 5216);
    v11 = 35;
    v12 = ~*(_DWORD *)(*(_QWORD *)(v10 + 272) + 4LL * *(int *)(v10 + 264) - 4);
    do
    {
      if ( v11 == 35 && *v9 == 35 && v9[1] == 35 )
        v12 = ~*(_DWORD *)(*(_QWORD *)(v10 + 272) + 4LL * *(int *)(v10 + 264) - 4);
      v13 = v11 ^ (unsigned __int64)(unsigned __int8)v12;
      v11 = *v9++;
      v12 = dword_1800D56B0[v13] ^ (v12 >> 8);
    }
    while ( v11 );
    v14 = ~v12;
    if ( *(_DWORD *)(*(_QWORD *)v10 + 5304LL) == v14 )
      sub_180053310(v14, 11, "##MainChild");
    sub_18003E470((unsigned int)"##MainChild", v14, (unsigned int)&v20, 1, 0);
    v15 = *v0;
    if ( (unsigned int)dword_18010C5BC < (unsigned __int64)((v0[1] - *v0) >> 6) )
    {
      v16 = (unsigned __int64)(unsigned int)dword_18010C5BC << 6;
      v17 = *(_QWORD *)(v16 + v15 + 40);
      for ( i = *(_QWORD *)(v16 + v15 + 48); v17 != i; v17 += 64 )
      {
        v19 = *(_QWORD *)(v17 + 56);
        if ( v19 )
          (*(void (__fastcall **)(__int64))(*(_QWORD *)v19 + 16LL))(v19);
      }
    }
    sub_18003E7F0();
    sub_18004B190();
    return 1;
  }
}
