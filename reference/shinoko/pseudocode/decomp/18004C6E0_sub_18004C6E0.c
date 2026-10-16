// sub_18004C6E0 size=134
bool __fastcall sub_18004C6E0(int a1)
{
  __int64 v1; // rax
  bool v2; // bl
  unsigned __int8 v4[32]; // [rsp+20h] [rbp-28h] BYREF

  v1 = *(int *)(qword_18010C470 + 8064);
  if ( *(_DWORD *)(qword_18010C470 + 8048) > (int)v1 && *(_DWORD *)(56 * v1 + *(_QWORD *)(qword_18010C470 + 8056)) == a1 )
  {
    sub_180035ED0(v4, 20, "##Popup_%08x", a1);
    v2 = sub_180040700(v4, 0, 67109185);
    if ( !v2 )
      sub_18004C770();
    return v2;
  }
  else
  {
    *(_DWORD *)(qword_18010C470 + 7824) = 0;
    return 0;
  }
}
