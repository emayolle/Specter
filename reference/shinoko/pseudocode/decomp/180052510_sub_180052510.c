// sub_180052510 size=228
char __fastcall sub_180052510(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  int v6; // eax
  __int16 v7; // cx
  __int16 v8; // cx
  _WORD v10[2]; // [rsp+20h] [rbp-18h] BYREF
  _DWORD v11[5]; // [rsp+24h] [rbp-14h] BYREF
  __int16 v12; // [rsp+50h] [rbp+18h] BYREF

  if ( (unsigned int)sub_180034BF0(a4, "Pos=%i,%i", (unsigned int)&v12, (unsigned int)v10) == 2 )
  {
    LOBYTE(v6) = v12;
    v7 = v10[0];
    *(_WORD *)(a3 + 4) = v12;
    *(_WORD *)(a3 + 6) = v7;
  }
  else if ( (unsigned int)sub_180034BF0(a4, "Size=%i,%i", (unsigned int)&v12, (unsigned int)v10) == 2 )
  {
    LOBYTE(v6) = v12;
    v8 = v10[0];
    *(_WORD *)(a3 + 8) = v12;
    *(_WORD *)(a3 + 10) = v8;
  }
  else if ( (unsigned int)sub_180034BF0(a4, "Collapsed=%d", (unsigned int)v11) == 1 )
  {
    LOBYTE(v6) = v11[0] != 0;
    *(_BYTE *)(a3 + 12) = v11[0] != 0;
  }
  else
  {
    v6 = sub_180034BF0(a4, "IsChild=%d", (unsigned int)v11);
    if ( v6 == 1 )
    {
      LOBYTE(v6) = v11[0] != 0;
      *(_BYTE *)(a3 + 13) = v11[0] != 0;
    }
  }
  return v6;
}
