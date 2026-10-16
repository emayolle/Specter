__int64 sub_180001100()
{
  __int64 result; // rax
  void *v1; // rcx
  __int128 v2; // [rsp+20h] [rbp-68h] BYREF
  __int64 v3; // [rsp+30h] [rbp-58h]
  unsigned __int64 v4; // [rsp+38h] [rbp-50h]
  _QWORD v5[9]; // [rsp+40h] [rbp-48h] BYREF

  v5[0] = off_1800CDB40;
  v5[1] = sub_180017E80;
  v5[7] = v5;
  v2 = 0;
  v3 = 4;
  v4 = 15;
  strcpy((char *)&v2, "Misc");
  result = sub_180003EE0(&unk_18010C489, &v2, v5, 80);
  if ( v4 > 0xF )
  {
    v1 = (void *)v2;
    if ( v4 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v2 - *(_QWORD *)(v2 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v1 = *(void **)(v2 - 8);
    }
    return sub_1800931A0(v1);
  }
  return result;
}
