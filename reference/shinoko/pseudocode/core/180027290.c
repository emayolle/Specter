void sub_180027290()
{
  __int64 v0; // rbx
  __int64 v1; // rax
  __int64 v2; // rdx
  __int64 v3; // rcx
  __int64 v4; // rdi
  __int64 v5; // rbx
  __int64 v6; // rax
  __int64 v7; // rax
  void *v8; // rcx
  void *v9; // rcx
  _BYTE *v10; // rax
  __int64 v11; // rcx
  __int128 v12; // [rsp+20h] [rbp-E0h] BYREF
  size_t v13; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v14; // [rsp+38h] [rbp-C8h]
  __int128 v15; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v16; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v17; // [rsp+58h] [rbp-A8h]
  _BYTE v18[48]; // [rsp+60h] [rbp-A0h] BYREF
  char v19[128]; // [rsp+90h] [rbp-70h] BYREF
  char v20; // [rsp+130h] [rbp+30h] BYREF
  void *v21; // [rsp+138h] [rbp+38h]

  v0 = sub_180027520(&v20, v18);
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v1 = sub_1800B9730(v0);
  sub_180015BF0(&v12, v0, v1);
  if ( v13 )
  {
    v21 = &unk_18010B660;
    if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
      sub_18008EE80(5);
    if ( dword_18010B6AC == 0x7FFFFFFF )
    {
      dword_18010B6AC = 2147483646;
      sub_18008EE80(6);
    }
    v2 = qword_18010C530;
    v3 = qword_18010C520;
    if ( qword_18010C520 <= (unsigned __int64)(qword_18010C530 + 1) )
    {
      sub_18002DD60(&qword_18010C510);
      v2 = qword_18010C530;
      v3 = qword_18010C520;
    }
    qword_18010C528 &= v3 - 1;
    v4 = qword_18010C528 + v2;
    v5 = (qword_18010C528 + v2) & (v3 - 1);
    v6 = qword_18010C518;
    if ( !*(_QWORD *)(qword_18010C518 + 8 * v5) )
    {
      *(_QWORD *)(qword_18010C518 + 8 * v5) = sub_180093150(32);
      v3 = qword_18010C520;
      v6 = qword_18010C518;
    }
    sub_180015AE0(*(_QWORD *)(v6 + 8 * (v4 & (v3 - 1))), &v12);
    dword_18010C5B8 = ++qword_18010C530;
    sub_18008E9E0(&unk_18010B660);
    sub_1800229B0(v19, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", v13);
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v7 = sub_1800B9730(v19);
    sub_180015BF0(&v15, v19, v7);
    sub_1800291C0(&v15);
    if ( v17 > 0xF )
    {
      v8 = (void *)v15;
      if ( v17 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v15 - *(_QWORD *)(v15 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v8 = *(void **)(v15 - 8);
      }
      sub_1800931A0(v8);
    }
    sub_180029000(v19);
  }
  if ( v14 > 0xF )
  {
    v9 = (void *)v12;
    if ( v14 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v12 - *(_QWORD *)(v12 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v9 = *(void **)(v12 - 8);
    }
    sub_1800931A0(v9);
  }
  if ( v18[43] )
  {
    v10 = v18;
    v11 = 43;
    do
    {
      *v10++ = 0;
      --v11;
    }
    while ( v11 );
  }
}
