__int64 sub_18002E1D0()
{
  __int64 v0; // rcx
  __int64 v1; // rax
  __int64 v2; // rbx
  DWORD TickCount; // eax
  _DWORD *v4; // rax

  sub_180023300();
  if ( byte_1800FABBD )
  {
    if ( !byte_18010C48E )
    {
      dword_1800FAC3C = sub_180004880();
      if ( *(float *)&dword_1800FAC3C <= 0.0 )
        dword_1800FAC3C = 1065353216;
      byte_18010C48E = 1;
    }
    sub_1800048C0();
  }
  else if ( byte_18010C48E )
  {
    sub_1800048C0();
    byte_18010C48E = 0;
  }
  if ( byte_1800FABC4 || byte_18010C48D )
  {
    v1 = sub_1800047E0();
    v2 = v1;
    if ( byte_1800FABC4 && v1 )
    {
      if ( !byte_18010C48D )
      {
        dword_1800FAC40 = sub_180004810(v1);
        if ( *(float *)&dword_1800FAC40 <= 0.0 )
          dword_1800FAC40 = 1114636288;
        byte_18010C48D = 1;
      }
      sub_180004850(v2);
    }
    else if ( byte_18010C48D && v1 )
    {
      sub_180004850(v1);
      byte_18010C48D = 0;
    }
  }
  if ( byte_1800FABDD )
  {
    TickCount = GetTickCount();
    v0 = TickCount - dword_18010C958;
    if ( (unsigned int)v0 >= 0x15E )
    {
      dword_18010C958 = TickCount;
      sub_1800048E0();
    }
  }
  if ( qword_18010C5A0 && !byte_18010C934 )
  {
    byte_18010C934 = 1;
    if ( byte_1800FABF2 )
    {
      LOBYTE(v0) = 1;
      sub_18000CEA0(v0);
    }
    if ( byte_1800FABFC )
    {
      LOBYTE(v0) = 1;
      sub_18000E740(v0);
    }
    if ( byte_1800FAC08 )
    {
      LOBYTE(v0) = 1;
      sub_180011730(v0);
    }
    if ( byte_1800FAC14 )
    {
      LOBYTE(v0) = 1;
      sub_18000FFD0(v0);
    }
    if ( byte_1800FAC15 )
    {
      LOBYTE(v0) = 1;
      sub_180010B80(v0);
    }
  }
  if ( !byte_18010C50F )
    sub_18002A1C0();
  if ( !byte_18010C58D )
    sub_18002C070();
  sub_180017710();
  if ( !qword_18010C598 && (!qword_18010C470 || !*(_BYTE *)(qword_18010C470 + 178)) )
  {
    if ( vKey && (GetAsyncKeyState(vKey) & 1) != 0 )
      sub_180025D80();
    if ( dword_1800FAC20 && (GetAsyncKeyState(dword_1800FAC20) & 1) != 0 )
      sub_180026490();
    if ( dword_1800FAC24 && (GetAsyncKeyState(dword_1800FAC24) & 1) != 0 )
      sub_180026B90();
    if ( dword_1800FAC28 && (GetAsyncKeyState(dword_1800FAC28) & 1) != 0 )
      sub_180027290();
    if ( dword_1800FAC30 && (GetAsyncKeyState(dword_1800FAC30) & 1) != 0 )
      sub_180027990();
  }
  sub_180024610();
  if ( byte_1800FAB30 )
  {
    if ( qword_18010C458 )
      sub_180046440();
    v4 = (_DWORD *)qword_18010C470;
    *(_DWORD *)(qword_18010C470 + 7824) |= 2u;
    v4[1964] = 1145569280;
    v4[1965] = 1134559232;
    v4[1958] = 4;
    sub_180040700("Shinoko-Aniimo", 0, 32);
    sub_18002DF80();
    sub_180044DF0();
    if ( qword_18010C458 )
      sub_180046580();
  }
  return 1;
}
