// sub_18000BCB0 size=1200
__int64 __fastcall sub_18000BCB0(char a1, char a2)
{
  __int64 v4; // rbx
  __int64 v5; // rax
  const char *v6; // rsi
  const char *v7; // rbx
  __int64 v8; // rax
  __int64 v9; // rbx
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rbx
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  void *v17; // rcx
  void *v18; // rcx
  void *v19; // rcx
  void *v20; // rcx
  _BYTE *v21; // rax
  __int64 v22; // rcx
  void *v23; // rcx
  void *v24; // rcx
  _BYTE *v25; // rax
  __int64 v26; // rcx
  void *v27; // rcx
  void *v28; // rcx
  _BYTE *v29; // rax
  __int64 v30; // rcx
  __int64 result; // rax
  void *v32; // rcx
  __int128 v33; // [rsp+20h] [rbp-E0h] BYREF
  __int64 v34; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v35; // [rsp+38h] [rbp-C8h]
  __int128 v36; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v37; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v38; // [rsp+58h] [rbp-A8h]
  __int128 v39; // [rsp+60h] [rbp-A0h] BYREF
  __int64 v40; // [rsp+70h] [rbp-90h]
  unsigned __int64 v41; // [rsp+78h] [rbp-88h]
  __int128 v42; // [rsp+80h] [rbp-80h] BYREF
  __int64 v43; // [rsp+90h] [rbp-70h]
  unsigned __int64 v44; // [rsp+98h] [rbp-68h]
  __int128 v45; // [rsp+A0h] [rbp-60h] BYREF
  __int64 v46; // [rsp+B0h] [rbp-50h]
  unsigned __int64 v47; // [rsp+B8h] [rbp-48h]
  _QWORD v48[3]; // [rsp+C0h] [rbp-40h] BYREF
  unsigned __int64 v49; // [rsp+D8h] [rbp-28h]
  _QWORD v50[3]; // [rsp+E0h] [rbp-20h] BYREF
  unsigned __int64 v51; // [rsp+F8h] [rbp-8h]
  _QWORD v52[3]; // [rsp+100h] [rbp+0h] BYREF
  unsigned __int64 v53; // [rsp+118h] [rbp+18h]
  _QWORD v54[3]; // [rsp+120h] [rbp+20h] BYREF
  unsigned __int64 v55; // [rsp+138h] [rbp+38h]
  _BYTE v56[32]; // [rsp+140h] [rbp+40h] BYREF
  _BYTE v57[112]; // [rsp+160h] [rbp+60h] BYREF
  _BYTE v58[3216]; // [rsp+1D0h] [rbp+D0h] BYREF
  char v59; // [rsp+E70h] [rbp+D70h] BYREF
  char v60; // [rsp+E78h] [rbp+D78h] BYREF
  char v61; // [rsp+E80h] [rbp+D80h] BYREF

  v4 = sub_18000CA30(&v59, v57);
  v45 = 0;
  v46 = 0;
  v47 = 0;
  v5 = sub_1800B9730(v4);
  sub_180015BF0(&v45, v4, v5);
  v6 = "false";
  v7 = "false";
  if ( a2 )
    v7 = "true";
  v42 = 0;
  v43 = 0;
  v44 = 0;
  v8 = sub_1800B9730(v7);
  sub_180015BF0(&v42, v7, v8);
  v9 = sub_18000C5D0(&v60, v56);
  v39 = 0;
  v40 = 0;
  v41 = 0;
  v10 = sub_1800B9730(v9);
  sub_180015BF0(&v39, v9, v10);
  if ( a1 )
    v6 = "true";
  v36 = 0;
  v37 = 0;
  v38 = 0;
  v11 = sub_1800B9730(v6);
  sub_180015BF0(&v36, v6, v11);
  v12 = sub_18000C160(&v61, v58);
  v33 = 0;
  v34 = 0;
  v35 = 0;
  v13 = sub_1800B9730(v12);
  sub_180015BF0(&v33, v12, v13);
  v14 = sub_180015300(v52, &v33, &v36);
  v15 = sub_180015300(v50, v14, &v39);
  v16 = sub_180015300(v48, v15, &v42);
  sub_180015300(v54, v16, &v45);
  if ( v49 > 0xF )
  {
    v17 = (void *)v48[0];
    if ( v49 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v48[0] - *(_QWORD *)(v48[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v17 = *(void **)(v48[0] - 8LL);
    }
    sub_1800931A0(v17);
  }
  v48[2] = 0;
  v49 = 15;
  LOBYTE(v48[0]) = 0;
  if ( v51 > 0xF )
  {
    v18 = (void *)v50[0];
    if ( v51 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v50[0] - *(_QWORD *)(v50[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v18 = *(void **)(v50[0] - 8LL);
    }
    sub_1800931A0(v18);
  }
  v50[2] = 0;
  v51 = 15;
  LOBYTE(v50[0]) = 0;
  if ( v53 > 0xF )
  {
    v19 = (void *)v52[0];
    if ( v53 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v52[0] - *(_QWORD *)(v52[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v19 = *(void **)(v52[0] - 8LL);
    }
    sub_1800931A0(v19);
  }
  v52[2] = 0;
  v53 = 15;
  LOBYTE(v52[0]) = 0;
  if ( v35 > 0xF )
  {
    v20 = (void *)v33;
    if ( v35 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v33 - *(_QWORD *)(v33 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v20 = *(void **)(v33 - 8);
    }
    sub_1800931A0(v20);
  }
  if ( v58[3162] )
  {
    v21 = v58;
    v22 = 3162;
    do
    {
      *v21++ = 0;
      --v22;
    }
    while ( v22 );
  }
  if ( v38 > 0xF )
  {
    v23 = (void *)v36;
    if ( v38 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v36 - *(_QWORD *)(v36 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v23 = *(void **)(v36 - 8);
    }
    sub_1800931A0(v23);
  }
  if ( v41 > 0xF )
  {
    v24 = (void *)v39;
    if ( v41 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v39 - *(_QWORD *)(v39 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v24 = *(void **)(v39 - 8);
    }
    sub_1800931A0(v24);
  }
  if ( v56[25] )
  {
    v25 = v56;
    v26 = 25;
    do
    {
      *v25++ = 0;
      --v26;
    }
    while ( v26 );
  }
  if ( v44 > 0xF )
  {
    v27 = (void *)v42;
    if ( v44 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v42 - *(_QWORD *)(v42 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v27 = *(void **)(v42 - 8);
    }
    sub_1800931A0(v27);
  }
  if ( v47 > 0xF )
  {
    v28 = (void *)v45;
    if ( v47 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v45 - *(_QWORD *)(v45 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v28 = *(void **)(v45 - 8);
    }
    sub_1800931A0(v28);
  }
  if ( v57[108] )
  {
    v29 = v57;
    v30 = 108;
    do
    {
      *v29++ = 0;
      --v30;
    }
    while ( v30 );
  }
  sub_18002C7A0((__int64)v54);
  result = v55;
  if ( v55 > 0xF )
  {
    v32 = (void *)v54[0];
    if ( v55 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v54[0] - *(_QWORD *)(v54[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v32 = *(void **)(v54[0] - 8LL);
    }
    return sub_1800931A0(v32);
  }
  return result;
}
