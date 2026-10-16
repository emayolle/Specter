__int64 sub_180001420()
{
  __int64 result; // rax
  void *v1; // rcx
  _QWORD v2[3]; // [rsp+20h] [rbp-68h] BYREF
  unsigned __int64 v3; // [rsp+38h] [rbp-50h]
  _QWORD v4[9]; // [rsp+40h] [rbp-48h] BYREF

  v4[0] = off_1800CDB40;
  v4[1] = sub_18002CB40;
  v4[7] = v4;
  HIDWORD(v2[1]) = 0;
  v2[2] = 12;
  v3 = 15;
  strcpy((char *)v2, "Lua Executor");
  result = sub_180003EE0(&unk_18010C48C, v2, v4, 60);
  if ( v3 > 0xF )
  {
    v1 = (void *)v2[0];
    if ( v3 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v2[0] - *(_QWORD *)(v2[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v1 = *(void **)(v2[0] - 8LL);
    }
    return sub_1800931A0(v1);
  }
  return result;
}
