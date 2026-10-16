// sub_1800098E0 size=1179
void __fastcall sub_1800098E0(char a1, int a2)
{
  __int64 v4; // rbx
  __int64 v5; // rax
  const char *v6; // rbx
  __int64 v7; // rax
  __int64 v8; // rbx
  __int64 v9; // rax
  __int64 v10; // rdi
  __int64 v11; // rbx
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  void *v16; // rcx
  void *v17; // rcx
  void *v18; // rcx
  void *v19; // rcx
  _BYTE *v20; // rax
  __int64 v21; // rcx
  void *v22; // rcx
  void *v23; // rcx
  _BYTE *v24; // rax
  __int64 v25; // rcx
  void *v26; // rcx
  void *v27; // rcx
  _BYTE *v28; // rax
  __int64 v29; // rcx
  void *v30; // rcx
  __int128 v31; // [rsp+20h] [rbp-E0h] BYREF
  __int64 v32; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v33; // [rsp+38h] [rbp-C8h]
  __int128 v34; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v35; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v36; // [rsp+58h] [rbp-A8h]
  __int128 v37; // [rsp+60h] [rbp-A0h] BYREF
  __int64 v38; // [rsp+70h] [rbp-90h]
  unsigned __int64 v39; // [rsp+78h] [rbp-88h]
  __int128 v40; // [rsp+80h] [rbp-80h] BYREF
  __int64 v41; // [rsp+90h] [rbp-70h]
  unsigned __int64 v42; // [rsp+98h] [rbp-68h]
  _QWORD v43[3]; // [rsp+A0h] [rbp-60h] BYREF
  unsigned __int64 v44; // [rsp+B8h] [rbp-48h]
  _QWORD v45[3]; // [rsp+C0h] [rbp-40h] BYREF
  unsigned __int64 v46; // [rsp+D8h] [rbp-28h]
  _QWORD v47[3]; // [rsp+E0h] [rbp-20h] BYREF
  unsigned __int64 v48; // [rsp+F8h] [rbp-8h]
  _QWORD v49[3]; // [rsp+100h] [rbp+0h] BYREF
  unsigned __int64 v50; // [rsp+118h] [rbp+18h]
  _QWORD v51[3]; // [rsp+120h] [rbp+20h] BYREF
  unsigned __int64 v52; // [rsp+138h] [rbp+38h]
  _BYTE v53[32]; // [rsp+140h] [rbp+40h] BYREF
  _BYTE v54[256]; // [rsp+160h] [rbp+60h] BYREF
  _BYTE v55[3472]; // [rsp+260h] [rbp+160h] BYREF
  char v56; // [rsp+1000h] [rbp+F00h] BYREF
  char v57; // [rsp+1008h] [rbp+F08h] BYREF
  char v58; // [rsp+1010h] [rbp+F10h] BYREF

  byte_1800FABEB = a1;
  dword_1800FABEC = a2;
  v4 = sub_18000A660(&v56, v55);
  v40 = 0;
  v41 = 0;
  v42 = 0;
  v5 = sub_1800B9730(v4);
  sub_180015BF0(&v40, v4, v5);
  v6 = "false";
  if ( a1 )
    v6 = "true";
  v37 = 0;
  v38 = 0;
  v39 = 0;
  v7 = sub_1800B9730(v6);
  sub_180015BF0(&v37, v6, v7);
  v8 = sub_18000A1F0(&v57, v53);
  v34 = 0;
  v35 = 0;
  v36 = 0;
  v9 = sub_1800B9730(v8);
  sub_180015BF0(&v34, v8, v9);
  v10 = sub_180002BF0((__int64)v49, a2);
  v11 = sub_180009D80(&v58, v54);
  v31 = 0;
  v32 = 0;
  v33 = 0;
  v12 = sub_1800B9730(v11);
  sub_180015BF0(&v31, v11, v12);
  v13 = sub_180015300(v47, &v31, v10);
  v14 = sub_180015300(v45, v13, &v34);
  v15 = sub_180015300(v43, v14, &v37);
  sub_180015300(v51, v15, &v40);
  if ( v44 > 0xF )
  {
    v16 = (void *)v43[0];
    if ( v44 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v43[0] - *(_QWORD *)(v43[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v16 = *(void **)(v43[0] - 8LL);
    }
    sub_1800931A0(v16);
  }
  v43[2] = 0;
  v44 = 15;
  LOBYTE(v43[0]) = 0;
  if ( v46 > 0xF )
  {
    v17 = (void *)v45[0];
    if ( v46 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v45[0] - *(_QWORD *)(v45[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v17 = *(void **)(v45[0] - 8LL);
    }
    sub_1800931A0(v17);
  }
  v45[2] = 0;
  v46 = 15;
  LOBYTE(v45[0]) = 0;
  if ( v48 > 0xF )
  {
    v18 = (void *)v47[0];
    if ( v48 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v47[0] - *(_QWORD *)(v47[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v18 = *(void **)(v47[0] - 8LL);
    }
    sub_1800931A0(v18);
  }
  v47[2] = 0;
  v48 = 15;
  LOBYTE(v47[0]) = 0;
  if ( v33 > 0xF )
  {
    v19 = (void *)v31;
    if ( v33 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v31 - *(_QWORD *)(v31 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v19 = *(void **)(v31 - 8);
    }
    sub_1800931A0(v19);
  }
  if ( v54[250] )
  {
    v20 = v54;
    v21 = 250;
    do
    {
      *v20++ = 0;
      --v21;
    }
    while ( v21 );
  }
  if ( v50 > 0xF )
  {
    v22 = (void *)v49[0];
    if ( v50 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v49[0] - *(_QWORD *)(v49[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v22 = *(void **)(v49[0] - 8LL);
    }
    sub_1800931A0(v22);
  }
  v49[2] = 0;
  v50 = 15;
  LOBYTE(v49[0]) = 0;
  if ( v36 > 0xF )
  {
    v23 = (void *)v34;
    if ( v36 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v34 - *(_QWORD *)(v34 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v23 = *(void **)(v34 - 8);
    }
    sub_1800931A0(v23);
  }
  if ( v53[22] )
  {
    v24 = v53;
    v25 = 22;
    do
    {
      *v24++ = 0;
      --v25;
    }
    while ( v25 );
  }
  if ( v39 > 0xF )
  {
    v26 = (void *)v37;
    if ( v39 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v37 - *(_QWORD *)(v37 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v26 = *(void **)(v37 - 8);
    }
    sub_1800931A0(v26);
  }
  if ( v42 > 0xF )
  {
    v27 = (void *)v40;
    if ( v42 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v40 - *(_QWORD *)(v40 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v27 = *(void **)(v40 - 8);
    }
    sub_1800931A0(v27);
  }
  if ( v55[3436] )
  {
    v28 = v55;
    v29 = 3436;
    do
    {
      *v28++ = 0;
      --v29;
    }
    while ( v29 );
  }
  sub_18002C7A0((__int64)v51);
  if ( v52 > 0xF )
  {
    v30 = (void *)v51[0];
    if ( v52 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v51[0] - *(_QWORD *)(v51[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v30 = *(void **)(v51[0] - 8LL);
    }
    sub_1800931A0(v30);
  }
}
