// sub_18000FFD0 size=709
void __fastcall sub_18000FFD0(char a1)
{
  __int64 v2; // rbx
  __int64 v3; // rax
  const char *v4; // rbx
  __int64 v5; // rax
  __int64 v6; // rbx
  __int64 v7; // rax
  __int64 v8; // rax
  void *v9; // rcx
  void *v10; // rcx
  _BYTE *v11; // rax
  __int64 v12; // rcx
  void *v13; // rcx
  void *v14; // rcx
  _BYTE *v15; // rax
  __int64 v16; // rcx
  void *v17; // rcx
  __int128 v18; // [rsp+20h] [rbp-E0h] BYREF
  __int64 v19; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v20; // [rsp+38h] [rbp-C8h]
  __int128 v21; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v22; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v23; // [rsp+58h] [rbp-A8h]
  __int128 v24; // [rsp+60h] [rbp-A0h] BYREF
  __int64 v25; // [rsp+70h] [rbp-90h]
  unsigned __int64 v26; // [rsp+78h] [rbp-88h]
  _QWORD v27[3]; // [rsp+80h] [rbp-80h] BYREF
  unsigned __int64 v28; // [rsp+98h] [rbp-68h]
  _QWORD v29[3]; // [rsp+A0h] [rbp-60h] BYREF
  unsigned __int64 v30; // [rsp+B8h] [rbp-48h]
  _BYTE v31[432]; // [rsp+C0h] [rbp-40h] BYREF
  _BYTE v32[2656]; // [rsp+270h] [rbp+170h] BYREF
  char v33; // [rsp+CE0h] [rbp+BE0h] BYREF
  char v34; // [rsp+CE8h] [rbp+BE8h] BYREF

  byte_1800FAC14 = a1;
  v2 = sub_180010710(&v33, v32);
  v24 = 0;
  v25 = 0;
  v26 = 0;
  v3 = sub_1800B9730(v2);
  sub_180015BF0(&v24, v2, v3);
  v4 = "false";
  if ( a1 )
    v4 = "true";
  v21 = 0;
  v22 = 0;
  v23 = 0;
  v5 = sub_1800B9730(v4);
  sub_180015BF0(&v21, v4, v5);
  v6 = sub_1800102A0(&v34, v31);
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v7 = sub_1800B9730(v6);
  sub_180015BF0(&v18, v6, v7);
  v8 = sub_180015300(v27, &v18, &v21);
  sub_180015300(v29, v8, &v24);
  if ( v28 > 0xF )
  {
    v9 = (void *)v27[0];
    if ( v28 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v27[0] - *(_QWORD *)(v27[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v9 = *(void **)(v27[0] - 8LL);
    }
    sub_1800931A0(v9);
  }
  v27[2] = 0;
  v28 = 15;
  LOBYTE(v27[0]) = 0;
  if ( v20 > 0xF )
  {
    v10 = (void *)v18;
    if ( v20 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v18 - *(_QWORD *)(v18 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v10 = *(void **)(v18 - 8);
    }
    sub_1800931A0(v10);
  }
  if ( v31[421] )
  {
    v11 = v31;
    v12 = 421;
    do
    {
      *v11++ = 0;
      --v12;
    }
    while ( v12 );
  }
  if ( v23 > 0xF )
  {
    v13 = (void *)v21;
    if ( v23 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v21 - *(_QWORD *)(v21 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v13 = *(void **)(v21 - 8);
    }
    sub_1800931A0(v13);
  }
  if ( v26 > 0xF )
  {
    v14 = (void *)v24;
    if ( v26 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v24 - *(_QWORD *)(v24 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v14 = *(void **)(v24 - 8);
    }
    sub_1800931A0(v14);
  }
  if ( v32[2631] )
  {
    v15 = v32;
    v16 = 2631;
    do
    {
      *v15++ = 0;
      --v16;
    }
    while ( v16 );
  }
  sub_18002C7A0((__int64)v29);
  if ( v30 > 0xF )
  {
    v17 = (void *)v29[0];
    if ( v30 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v29[0] - *(_QWORD *)(v29[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v17 = *(void **)(v29[0] - 8LL);
    }
    sub_1800931A0(v17);
  }
}
