// sub_18000E740 size=1734
void __fastcall sub_18000E740(char a1, float a2, float a3)
{
  __int64 v4; // rbx
  __int64 v5; // rax
  __int64 v6; // r14
  __int64 v7; // rbx
  __int64 v8; // rax
  __int64 v9; // rdi
  __int64 v10; // rbx
  __int64 v11; // rax
  const char *v12; // rbx
  __int64 v13; // rax
  __int64 v14; // rbx
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  __int64 v20; // rax
  void *v21; // rcx
  void *v22; // rcx
  void *v23; // rcx
  void *v24; // rcx
  void *v25; // rcx
  void *v26; // rcx
  _BYTE *v27; // rax
  __int64 v28; // rcx
  void *v29; // rcx
  void *v30; // rcx
  _BYTE *v31; // rax
  __int64 v32; // rcx
  void *v33; // rcx
  void *v34; // rcx
  _BYTE *v35; // rax
  __int64 v36; // rcx
  void *v37; // rcx
  void *v38; // rcx
  _BYTE *v39; // rax
  __int64 v40; // rcx
  void *v41; // rcx
  __int128 v42; // [rsp+28h] [rbp-E0h] BYREF
  __int64 v43; // [rsp+38h] [rbp-D0h]
  unsigned __int64 v44; // [rsp+40h] [rbp-C8h]
  __int128 v45; // [rsp+48h] [rbp-C0h] BYREF
  __int64 v46; // [rsp+58h] [rbp-B0h]
  unsigned __int64 v47; // [rsp+60h] [rbp-A8h]
  __int128 v48; // [rsp+68h] [rbp-A0h] BYREF
  __int64 v49; // [rsp+78h] [rbp-90h]
  unsigned __int64 v50; // [rsp+80h] [rbp-88h]
  __int128 v51; // [rsp+88h] [rbp-80h] BYREF
  __int64 v52; // [rsp+98h] [rbp-70h]
  unsigned __int64 v53; // [rsp+A0h] [rbp-68h]
  __int128 v54; // [rsp+A8h] [rbp-60h] BYREF
  __int64 v55; // [rsp+B8h] [rbp-50h]
  unsigned __int64 v56; // [rsp+C0h] [rbp-48h]
  _QWORD v57[3]; // [rsp+C8h] [rbp-40h] BYREF
  unsigned __int64 v58; // [rsp+E0h] [rbp-28h]
  _QWORD v59[3]; // [rsp+E8h] [rbp-20h] BYREF
  unsigned __int64 v60; // [rsp+100h] [rbp-8h]
  _QWORD v61[3]; // [rsp+108h] [rbp+0h] BYREF
  unsigned __int64 v62; // [rsp+120h] [rbp+18h]
  _QWORD v63[3]; // [rsp+128h] [rbp+20h] BYREF
  unsigned __int64 v64; // [rsp+140h] [rbp+38h]
  _QWORD v65[3]; // [rsp+148h] [rbp+40h] BYREF
  unsigned __int64 v66; // [rsp+160h] [rbp+58h]
  _QWORD v67[3]; // [rsp+168h] [rbp+60h] BYREF
  unsigned __int64 v68; // [rsp+180h] [rbp+78h]
  _QWORD v69[3]; // [rsp+188h] [rbp+80h] BYREF
  unsigned __int64 v70; // [rsp+1A0h] [rbp+98h]
  _QWORD v71[3]; // [rsp+1A8h] [rbp+A0h] BYREF
  unsigned __int64 v72; // [rsp+1C0h] [rbp+B8h]
  _BYTE v73[32]; // [rsp+1C8h] [rbp+C0h] BYREF
  _BYTE v74[32]; // [rsp+1E8h] [rbp+E0h] BYREF
  _BYTE v75[400]; // [rsp+208h] [rbp+100h] BYREF
  _BYTE v76[2840]; // [rsp+398h] [rbp+290h] BYREF
  char v77; // [rsp+F18h] [rbp+E10h] BYREF
  char v78; // [rsp+F20h] [rbp+E18h] BYREF
  char v79; // [rsp+F28h] [rbp+E20h] BYREF
  char v80; // [rsp+F30h] [rbp+E28h] BYREF

  byte_1800FABFC = a1;
  dword_1800FAC00 = LODWORD(a2);
  dword_1800FAC04 = LODWORD(a3);
  v4 = sub_18000FB60(&v77, v76);
  v54 = 0;
  v55 = 0;
  v56 = 0;
  v5 = sub_1800B9730(v4);
  sub_180015BF0(&v54, v4, v5);
  v6 = sub_180002E20(v69);
  v7 = sub_18000F6F0(&v78, v74);
  v51 = 0;
  v52 = 0;
  v53 = 0;
  v8 = sub_1800B9730(v7);
  sub_180015BF0(&v51, v7, v8);
  v9 = sub_180002E20(v67);
  v10 = sub_18000F280(&v79, v73);
  v48 = 0;
  v49 = 0;
  v50 = 0;
  v11 = sub_1800B9730(v10);
  sub_180015BF0(&v48, v10, v11);
  v12 = "false";
  if ( a1 )
    v12 = "true";
  v45 = 0;
  v46 = 0;
  v47 = 0;
  v13 = sub_1800B9730(v12);
  sub_180015BF0(&v45, v12, v13);
  v14 = sub_18000EE10(&v80, v75);
  v42 = 0;
  v43 = 0;
  v44 = 0;
  v15 = sub_1800B9730(v14);
  sub_180015BF0(&v42, v14, v15);
  v16 = sub_180015300(v65, &v42, &v45);
  v17 = sub_180015300(v63, v16, &v48);
  v18 = sub_180015300(v61, v17, v9);
  v19 = sub_180015300(v59, v18, &v51);
  v20 = sub_180015300(v57, v19, v6);
  sub_180015300(v71, v20, &v54);
  if ( v58 > 0xF )
  {
    v21 = (void *)v57[0];
    if ( v58 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v57[0] - *(_QWORD *)(v57[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v21 = *(void **)(v57[0] - 8LL);
    }
    sub_1800931A0(v21);
  }
  v57[2] = 0;
  v58 = 15;
  LOBYTE(v57[0]) = 0;
  if ( v60 > 0xF )
  {
    v22 = (void *)v59[0];
    if ( v60 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v59[0] - *(_QWORD *)(v59[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v22 = *(void **)(v59[0] - 8LL);
    }
    sub_1800931A0(v22);
  }
  v59[2] = 0;
  v60 = 15;
  LOBYTE(v59[0]) = 0;
  if ( v62 > 0xF )
  {
    v23 = (void *)v61[0];
    if ( v62 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v61[0] - *(_QWORD *)(v61[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v23 = *(void **)(v61[0] - 8LL);
    }
    sub_1800931A0(v23);
  }
  v61[2] = 0;
  v62 = 15;
  LOBYTE(v61[0]) = 0;
  if ( v64 > 0xF )
  {
    v24 = (void *)v63[0];
    if ( v64 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v63[0] - *(_QWORD *)(v63[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v24 = *(void **)(v63[0] - 8LL);
    }
    sub_1800931A0(v24);
  }
  v63[2] = 0;
  v64 = 15;
  LOBYTE(v63[0]) = 0;
  if ( v66 > 0xF )
  {
    v25 = (void *)v65[0];
    if ( v66 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v65[0] - *(_QWORD *)(v65[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v25 = *(void **)(v65[0] - 8LL);
    }
    sub_1800931A0(v25);
  }
  v65[2] = 0;
  v66 = 15;
  LOBYTE(v65[0]) = 0;
  if ( v44 > 0xF )
  {
    v26 = (void *)v42;
    if ( v44 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v42 - *(_QWORD *)(v42 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v26 = *(void **)(v42 - 8);
    }
    sub_1800931A0(v26);
  }
  if ( v75[385] )
  {
    v27 = v75;
    v28 = 385;
    do
    {
      *v27++ = 0;
      --v28;
    }
    while ( v28 );
  }
  if ( v47 > 0xF )
  {
    v29 = (void *)v45;
    if ( v47 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v45 - *(_QWORD *)(v45 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v29 = *(void **)(v45 - 8);
    }
    sub_1800931A0(v29);
  }
  if ( v50 > 0xF )
  {
    v30 = (void *)v48;
    if ( v50 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v48 - *(_QWORD *)(v48 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v30 = *(void **)(v48 - 8);
    }
    sub_1800931A0(v30);
  }
  if ( v73[21] )
  {
    v31 = v73;
    v32 = 21;
    do
    {
      *v31++ = 0;
      --v32;
    }
    while ( v32 );
  }
  if ( v68 > 0xF )
  {
    v33 = (void *)v67[0];
    if ( v68 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v67[0] - *(_QWORD *)(v67[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v33 = *(void **)(v67[0] - 8LL);
    }
    sub_1800931A0(v33);
  }
  v67[2] = 0;
  v68 = 15;
  LOBYTE(v67[0]) = 0;
  if ( v53 > 0xF )
  {
    v34 = (void *)v51;
    if ( v53 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v51 - *(_QWORD *)(v51 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v34 = *(void **)(v51 - 8);
    }
    sub_1800931A0(v34);
  }
  if ( v74[23] )
  {
    v35 = v74;
    v36 = 23;
    do
    {
      *v35++ = 0;
      --v36;
    }
    while ( v36 );
  }
  if ( v70 > 0xF )
  {
    v37 = (void *)v69[0];
    if ( v70 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v69[0] - *(_QWORD *)(v69[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v37 = *(void **)(v69[0] - 8LL);
    }
    sub_1800931A0(v37);
  }
  v69[2] = 0;
  v70 = 15;
  LOBYTE(v69[0]) = 0;
  if ( v56 > 0xF )
  {
    v38 = (void *)v54;
    if ( v56 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v54 - *(_QWORD *)(v54 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v38 = *(void **)(v54 - 8);
    }
    sub_1800931A0(v38);
  }
  if ( v76[2834] )
  {
    v39 = v76;
    v40 = 2834;
    do
    {
      *v39++ = 0;
      --v40;
    }
    while ( v40 );
  }
  sub_18002C7A0((__int64)v71);
  if ( v72 > 0xF )
  {
    v41 = (void *)v71[0];
    if ( v72 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v71[0] - *(_QWORD *)(v71[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v41 = *(void **)(v71[0] - 8LL);
    }
    sub_1800931A0(v41);
  }
}
