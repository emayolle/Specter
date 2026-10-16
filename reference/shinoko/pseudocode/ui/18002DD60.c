__int64 __fastcall sub_18002DD60(_QWORD *a1)
{
  unsigned __int64 v2; // rbx
  unsigned __int64 v3; // rcx
  unsigned __int64 v4; // r15
  unsigned __int64 v5; // rcx
  unsigned __int64 v6; // r14
  __int64 v7; // rax
  unsigned __int64 v8; // rcx
  __int64 i; // rsi
  __int64 v10; // rax
  unsigned __int64 v11; // rbx
  __int64 v12; // rdi
  __int64 v13; // rdx
  unsigned __int64 v14; // rdi
  unsigned __int64 v15; // rcx
  __int64 result; // rax
  __int64 v17; // rcx
  void *v18; // rax

  v2 = 1;
  v3 = a1[2];
  if ( v3 )
    v2 = v3;
  while ( v2 == v3 || v2 < 8 )
  {
    if ( 0x7FFFFFFFFFFFFFFLL - v2 < v2 )
      std::vector<void *>::_Xlen();
    v2 *= 2LL;
  }
  v4 = a1[3];
  if ( v2 > 0x1FFFFFFFFFFFFFFFLL )
    goto LABEL_27;
  v5 = 8 * v2;
  if ( !(8 * v2) )
  {
    v6 = 0;
    goto LABEL_15;
  }
  if ( v5 < 0x1000 )
  {
    v6 = sub_180093150(v5);
    goto LABEL_15;
  }
  if ( v5 + 39 < v5 )
LABEL_27:
    Concurrency::cancel_current_task();
  v7 = sub_180093150(v5 + 39);
  if ( !v7 )
    goto LABEL_23;
  v6 = (v7 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
  *(_QWORD *)(v6 - 8) = v7;
LABEL_15:
  v8 = v2 >> 1;
  for ( i = 8 * v4; v2 <= v8; v2 *= 2LL )
    ;
  v10 = a1[2];
  v11 = v2 - v10;
  v12 = 8 * (v10 - v4);
  sub_1800B8BD0(i + v6, i + a1[1], v12);
  v13 = a1[1];
  v14 = 8 * v4 + v6 + v12;
  if ( v4 > v11 )
  {
    i = 8 * v11;
    sub_1800B8BD0(v14, v13, 8 * v11);
    sub_1800B8BD0(v6, 8 * v11 + a1[1], 8 * (v4 - v11));
    v15 = v6 + 8 * (v4 - v11);
  }
  else
  {
    sub_1800B8BD0(v14, v13, 8 * v4);
    sub_1800B9280(v14 + i, 0, 8 * (v11 - v4));
    v15 = v6;
  }
  result = sub_1800B9280(v15, 0, i);
  v17 = a1[1];
  if ( v17 )
  {
    if ( (unsigned __int64)(8LL * a1[2]) < 0x1000 )
    {
      v18 = (void *)a1[1];
    }
    else
    {
      v18 = *(void **)(v17 - 8);
      if ( (unsigned __int64)(v17 - (_QWORD)v18 - 8) > 0x1F )
LABEL_23:
        __fastfail(5u);
    }
    result = sub_1800931A0(v18);
  }
  a1[2] += v11;
  a1[1] = v6;
  return result;
}
