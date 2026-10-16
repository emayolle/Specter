__int64 __fastcall sub_180029960(const void *a1, __int64 a2, unsigned int a3, __int64 a4)
{
  __int64 result; // rax
  __int64 v9; // rax
  void *v10; // rcx
  __int128 v11; // [rsp+20h] [rbp-C8h] BYREF
  __int64 v12; // [rsp+30h] [rbp-B8h]
  unsigned __int64 v13; // [rsp+38h] [rbp-B0h]
  _BYTE v14[168]; // [rsp+40h] [rbp-A8h] BYREF

  if ( byte_18010C58C )
  {
    sub_180028FB0("[LUA] RECURSION, bailing\n");
    sub_180029000("[LUA] RECURSION, bailing");
    return 1;
  }
  else
  {
    byte_18010C58C = 1;
    if ( !qword_18010C5A0 )
    {
      sub_180028FB0("[LUA] captured state %p\n", a1);
      sub_180029000("[LUA] captured state %p", a1);
      sub_1800229B0(v14, 128, "[LUA] Captured globalState = 0x%p", a1);
      v11 = 0;
      v12 = 0;
      v13 = 0;
      v9 = sub_1800B9730(v14);
      sub_180015BF0(&v11, v14, v9);
      sub_1800291C0(&v11);
      if ( v13 > 0xF )
      {
        v10 = (void *)v11;
        if ( v13 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v11 - *(_QWORD *)(v11 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v10 = *(void **)(v11 - 8);
        }
        sub_1800931A0(v10);
      }
      qword_18010C5A0 = (__int64)a1;
    }
    result = qword_18010C5A8(a1, a2, a3, a4);
    byte_18010C58C = 0;
  }
  return result;
}
