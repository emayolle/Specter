void sub_180027990()
{
  __int64 v0; // rdi
  int v1; // ebx
  __int64 v2; // rax
  __int64 v3; // rdx
  __int64 v4; // rcx
  __int64 v5; // rsi
  __int64 v6; // rdi
  __int64 v7; // rax
  __int64 v8; // rax
  void *v9; // rcx
  void *v10; // rcx
  _BYTE *v11; // rax
  __int64 v12; // rcx
  _BYTE *v13; // rax
  __int64 v14; // rcx
  __int128 v15; // [rsp+20h] [rbp-E0h] BYREF
  size_t v16; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v17; // [rsp+38h] [rbp-C8h]
  __int128 v18; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v19; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v20; // [rsp+58h] [rbp-A8h]
  _BYTE v21[64]; // [rsp+60h] [rbp-A0h] BYREF
  _BYTE v22[64]; // [rsp+A0h] [rbp-60h] BYREF
  char v23[176]; // [rsp+E0h] [rbp-20h] BYREF
  char v24; // [rsp+1A0h] [rbp+A0h] BYREF
  char v25; // [rsp+1A8h] [rbp+A8h] BYREF
  int v26; // [rsp+1B0h] [rbp+B0h]
  void *v27; // [rsp+1B8h] [rbp+B8h]

  v26 = 0;
  byte_1800FAC2C = byte_1800FAC2C == 0;
  if ( byte_1800FAC2C )
  {
    v0 = sub_180027C70(&v24, v22);
    v1 = 1;
  }
  else
  {
    v0 = sub_1800280E0(&v25, v21);
    v1 = 2;
  }
  v26 = v1;
  v15 = 0;
  v16 = 0;
  v17 = 0;
  v2 = sub_1800B9730(v0);
  sub_180015BF0(&v15, v0, v2);
  if ( v16 )
  {
    v27 = &unk_18010B660;
    if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
      sub_18008EE80(5);
    if ( dword_18010B6AC == 0x7FFFFFFF )
    {
      dword_18010B6AC = 2147483646;
      sub_18008EE80(6);
    }
    v3 = qword_18010C530;
    v4 = qword_18010C520;
    if ( qword_18010C520 <= (unsigned __int64)(qword_18010C530 + 1) )
    {
      sub_18002DD60(&qword_18010C510);
      v3 = qword_18010C530;
      v4 = qword_18010C520;
    }
    qword_18010C528 &= v4 - 1;
    v5 = qword_18010C528 + v3;
    v6 = (qword_18010C528 + v3) & (v4 - 1);
    v7 = qword_18010C518;
    if ( !*(_QWORD *)(qword_18010C518 + 8 * v6) )
    {
      *(_QWORD *)(qword_18010C518 + 8 * v6) = sub_180093150(32);
      v4 = qword_18010C520;
      v7 = qword_18010C518;
    }
    sub_180015AE0(*(_QWORD *)(v7 + 8 * (v5 & (v4 - 1))), &v15);
    dword_18010C5B8 = ++qword_18010C530;
    sub_18008E9E0(&unk_18010B660);
    sub_1800229B0(v23, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", v16);
    v18 = 0;
    v19 = 0;
    v20 = 0;
    v8 = sub_1800B9730(v23);
    sub_180015BF0(&v18, v23, v8);
    sub_1800291C0(&v18);
    if ( v20 > 0xF )
    {
      v9 = (void *)v18;
      if ( v20 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v18 - *(_QWORD *)(v18 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v9 = *(void **)(v18 - 8);
      }
      sub_1800931A0(v9);
    }
    sub_180029000(v23);
  }
  if ( v17 > 0xF )
  {
    v10 = (void *)v15;
    if ( v17 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v15 - *(_QWORD *)(v15 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v10 = *(void **)(v15 - 8);
    }
    sub_1800931A0(v10);
  }
  if ( (v1 & 2) != 0 )
  {
    LOBYTE(v1) = v1 & 0xFD;
    if ( v21[63] )
    {
      v11 = v21;
      v12 = 63;
      do
      {
        *v11++ = 0;
        --v12;
      }
      while ( v12 );
    }
  }
  if ( (v1 & 1) != 0 && v22[62] )
  {
    v13 = v22;
    v14 = 62;
    do
    {
      *v13++ = 0;
      --v14;
    }
    while ( v14 );
  }
}
