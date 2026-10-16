__int64 sub_180003B60(__int64 a1, int a2, int a3, int a4, const char *a5, ...)
{
  char v9; // si
  __int64 v10; // rax
  __int64 v11; // rdi
  __int64 v12; // r8
  __int128 *v13; // rcx
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  void *v18; // rcx
  __int128 *v19; // rcx
  unsigned __int8 v20; // bl
  void *v21; // rcx
  void *v22; // rcx
  int v24; // [rsp+40h] [rbp-71h] BYREF
  __int128 v25; // [rsp+48h] [rbp-69h] BYREF
  __int128 v26; // [rsp+58h] [rbp-59h]
  __int128 v27; // [rsp+68h] [rbp-49h] BYREF
  __int64 v28; // [rsp+78h] [rbp-39h]
  unsigned __int64 v29; // [rsp+80h] [rbp-31h]
  __int128 v30; // [rsp+88h] [rbp-29h] BYREF
  __int64 v31; // [rsp+98h] [rbp-19h]
  unsigned __int64 v32; // [rsp+A0h] [rbp-11h]
  __int64 v33; // [rsp+128h] [rbp+77h] BYREF
  va_list va; // [rsp+128h] [rbp+77h]
  __int64 v35; // [rsp+130h] [rbp+7Fh]
  va_list va1; // [rsp+138h] [rbp+87h] BYREF

  va_start(va1, a5);
  va_start(va, a5);
  HIDWORD(v33) = va_arg(va1, _QWORD) >> 32;
  v35 = va_arg(va1, _QWORD);
  v9 = 0;
  LODWORD(v33) = 0;
  v10 = sub_180094FC0(a1, "##");
  v11 = v10;
  v28 = 0;
  v29 = 0;
  v27 = 0;
  if ( v10 )
  {
    if ( a1 == v10 )
    {
      v28 = 0;
      v29 = 15;
      LOBYTE(v27) = 0;
      goto LABEL_7;
    }
    v12 = v10 - a1;
  }
  else
  {
    v12 = sub_1800B9730(a1);
  }
  sub_180015BF0(&v27, a1, v12);
LABEL_7:
  if ( v28 )
  {
    v13 = &v27;
    if ( v29 > 0xF )
      v13 = (__int128 *)v27;
    sub_18006EB90(v13, 0, 1);
  }
  v14 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
  *(_DWORD *)(v14 + 7712) = -1082130432;
  if ( v11 )
  {
    v25 = 0;
    v26 = 0u;
    v15 = sub_1800B9730(v11);
    sub_180015BF0(&v25, v11, v15);
  }
  else
  {
    v30 = 0;
    v31 = 5;
    v32 = 15;
    strcpy((char *)&v30, "##si_");
    LODWORD(v33) = 1;
    v16 = sub_1800B9730(a1);
    v17 = sub_180015CF0(&v30, a1, v16);
    v25 = 0;
    v26 = 0u;
    v25 = *(_OWORD *)v17;
    v26 = *(_OWORD *)(v17 + 16);
    *(_QWORD *)(v17 + 16) = 0;
    *(_QWORD *)(v17 + 24) = 15;
    *(_BYTE *)v17 = 0;
    v9 = 3;
  }
  if ( (v9 & 1) != 0 )
  {
    if ( v32 > 0xF )
    {
      v18 = (void *)v30;
      if ( v32 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v30 - *(_QWORD *)(v30 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v18 = *(void **)(v30 - 8);
      }
      sub_1800931A0(v18);
    }
    v31 = 0;
    v32 = 15;
    LOBYTE(v30) = 0;
  }
  v19 = &v25;
  if ( *((_QWORD *)&v26 + 1) > 0xFu )
    LODWORD(v19) = v25;
  LODWORD(v33) = a4;
  v24 = a3;
  v20 = sub_180074E80((_DWORD)v19, 4, a2, (unsigned int)&v24, (__int64)va, (__int64)a5);
  if ( v35 )
    sub_180003720(v35);
  if ( *((_QWORD *)&v26 + 1) > 0xFu )
  {
    v21 = (void *)v25;
    if ( (unsigned __int64)(*((_QWORD *)&v26 + 1) + 1LL) >= 0x1000 )
    {
      if ( (unsigned __int64)(v25 - *(_QWORD *)(v25 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v21 = *(void **)(v25 - 8);
    }
    sub_1800931A0(v21);
  }
  *(_QWORD *)&v26 = 0;
  *((_QWORD *)&v26 + 1) = 15;
  LOBYTE(v25) = 0;
  if ( v29 > 0xF )
  {
    v22 = (void *)v27;
    if ( v29 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v27 - *(_QWORD *)(v27 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v22 = *(void **)(v27 - 8);
    }
    sub_1800931A0(v22);
  }
  return v20;
}
