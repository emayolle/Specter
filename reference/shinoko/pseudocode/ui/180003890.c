__int64 sub_180003890(__int64 a1, int a2, float a3, float a4, const char *a5, ...)
{
  char v7; // si
  __int64 v8; // rax
  __int64 v9; // rdi
  __int64 v10; // r8
  __int128 *v11; // rcx
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  void *v16; // rcx
  __int128 *v17; // rcx
  unsigned __int8 v18; // bl
  void *v19; // rcx
  void *v20; // rcx
  float v22; // [rsp+48h] [rbp-81h] BYREF
  __int128 v23; // [rsp+50h] [rbp-79h] BYREF
  __int128 v24; // [rsp+60h] [rbp-69h]
  __int128 v25; // [rsp+70h] [rbp-59h] BYREF
  __int64 v26; // [rsp+80h] [rbp-49h]
  unsigned __int64 v27; // [rsp+88h] [rbp-41h]
  __int128 v28; // [rsp+90h] [rbp-39h] BYREF
  __int64 v29; // [rsp+A0h] [rbp-29h]
  unsigned __int64 v30; // [rsp+A8h] [rbp-21h]
  __int64 v31; // [rsp+140h] [rbp+77h] BYREF
  va_list va; // [rsp+140h] [rbp+77h]
  __int64 v33; // [rsp+148h] [rbp+7Fh]
  va_list va1; // [rsp+150h] [rbp+87h] BYREF

  va_start(va1, a5);
  va_start(va, a5);
  HIDWORD(v31) = va_arg(va1, _QWORD) >> 32;
  v33 = va_arg(va1, _QWORD);
  v7 = 0;
  LODWORD(v31) = 0;
  v8 = sub_180094FC0(a1, "##");
  v9 = v8;
  v26 = 0;
  v27 = 0;
  v25 = 0;
  if ( v8 )
  {
    if ( a1 == v8 )
    {
      v26 = 0;
      v27 = 15;
      LOBYTE(v25) = 0;
      goto LABEL_7;
    }
    v10 = v8 - a1;
  }
  else
  {
    v10 = sub_1800B9730(a1);
  }
  sub_180015BF0(&v25, a1, v10);
LABEL_7:
  if ( v26 )
  {
    v11 = &v25;
    if ( v27 > 0xF )
      v11 = (__int128 *)v25;
    sub_18006EB90(v11, 0, 1);
  }
  v12 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
  *(_DWORD *)(v12 + 7712) = -1082130432;
  if ( v9 )
  {
    v23 = 0;
    v24 = 0u;
    v13 = sub_1800B9730(v9);
    sub_180015BF0(&v23, v9, v13);
  }
  else
  {
    v28 = 0;
    v29 = 5;
    v30 = 15;
    strcpy((char *)&v28, "##sf_");
    LODWORD(v31) = 1;
    v14 = sub_1800B9730(a1);
    v15 = sub_180015CF0(&v28, a1, v14);
    v23 = 0;
    v24 = 0u;
    v23 = *(_OWORD *)v15;
    v24 = *(_OWORD *)(v15 + 16);
    *(_QWORD *)(v15 + 16) = 0;
    *(_QWORD *)(v15 + 24) = 15;
    *(_BYTE *)v15 = 0;
    v7 = 3;
  }
  if ( (v7 & 1) != 0 )
  {
    if ( v30 > 0xF )
    {
      v16 = (void *)v28;
      if ( v30 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v28 - *(_QWORD *)(v28 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v16 = *(void **)(v28 - 8);
      }
      sub_1800931A0(v16);
    }
    v29 = 0;
    v30 = 15;
    LOBYTE(v28) = 0;
  }
  v17 = &v23;
  if ( *((_QWORD *)&v24 + 1) > 0xFu )
    LODWORD(v17) = v23;
  *(float *)&v31 = a4;
  v22 = a3;
  v18 = sub_180074E80((_DWORD)v17, 8, a2, (unsigned int)&v22, (__int64)va, (__int64)a5);
  if ( v33 )
    sub_180003720(v33);
  if ( *((_QWORD *)&v24 + 1) > 0xFu )
  {
    v19 = (void *)v23;
    if ( (unsigned __int64)(*((_QWORD *)&v24 + 1) + 1LL) >= 0x1000 )
    {
      if ( (unsigned __int64)(v23 - *(_QWORD *)(v23 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v19 = *(void **)(v23 - 8);
    }
    sub_1800931A0(v19);
  }
  *(_QWORD *)&v24 = 0;
  *((_QWORD *)&v24 + 1) = 15;
  LOBYTE(v23) = 0;
  if ( v27 > 0xF )
  {
    v20 = (void *)v25;
    if ( v27 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v25 - *(_QWORD *)(v25 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v20 = *(void **)(v25 - 8);
    }
    sub_1800931A0(v20);
  }
  return v18;
}
