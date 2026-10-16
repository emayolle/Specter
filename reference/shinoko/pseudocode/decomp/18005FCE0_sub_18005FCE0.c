// sub_18005FCE0 size=534
__int64 __fastcall sub_18005FCE0(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v4; // r13
  const char *v7; // r8
  __int64 v8; // rax
  __int64 v9; // rdi
  __int64 v10; // rsi
  _QWORD *v11; // rsi
  __int64 v12; // r14
  __int64 v13; // rax
  _QWORD *v14; // r15
  __int64 v15; // rdi
  void (__fastcall *v16)(__int64, _QWORD, __int64, __int64); // rax
  void *v17; // r9
  __int64 v18; // r8
  __int64 v19; // rdx
  int v20; // r10d
  __int64 v21; // rcx
  __int16 v22; // cx
  __int64 result; // rax
  void *v24; // rcx
  void *v25; // rcx
  void *v26; // rcx

  v4 = *(_QWORD *)(a1 + 688);
  if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
  {
    if ( *(_DWORD *)(a2 + 32) )
      v7 = **(const char ***)(a2 + 40);
    else
      v7 = "<unknown>";
    sub_180052F00("[font] Discard baked %.2f for \"%s\"\n", *(float *)(a3 + 20), v7);
  }
  v8 = *(int *)(a3 + 48);
  v9 = *(_QWORD *)(a3 + 56);
  v10 = 44 * v8 + v9;
  if ( 44 * v8 )
  {
    do
    {
      if ( *(_DWORD *)(v9 + 40) != -1 )
        sub_180061C10(a1);
      v9 += 44;
    }
    while ( v9 != v10 );
  }
  v11 = *(_QWORD **)(a2 + 40);
  v12 = *(_QWORD *)(a3 + 96);
  v13 = *(int *)(a2 + 32);
  v14 = &v11[v13];
  if ( v13 * 8 )
  {
    do
    {
      v15 = *(_QWORD *)(*v11 + 128LL);
      if ( !v15 )
        v15 = *(_QWORD *)(a1 + 696);
      v16 = *(void (__fastcall **)(__int64, _QWORD, __int64, __int64))(v15 + 56);
      if ( v16 )
        v16(a1, *v11, a3, v12);
      v12 += *(_QWORD *)(v15 + 72);
      ++v11;
    }
    while ( v11 != v14 );
  }
  v17 = *(void **)(a3 + 96);
  if ( v17 )
  {
    v18 = qword_18010C470;
    if ( qword_18010C470 )
    {
      v19 = *(__int16 *)(qword_18010C470 + 10432);
      v20 = *(_DWORD *)(qword_18010C470 + 5032);
      v21 = 8 * v19;
      if ( *(_DWORD *)(8 * v19 + qword_18010C470 + 10436) != v20 )
      {
        v22 = ((int)v19 + 1) % 6;
        *(_WORD *)(qword_18010C470 + 10432) = v22;
        v21 = 8LL * v22;
        *(_DWORD *)(v21 + v18 + 10436) = v20;
        *(_DWORD *)(v21 + v18 + 10440) = 0;
      }
      ++*(_WORD *)(v21 + v18 + 10442);
      ++*(_DWORD *)(v18 + 10428);
    }
    sub_18009E210(v17);
    *(_QWORD *)(a3 + 96) = 0;
  }
  result = sub_1800369D0(v4 + 216, *(unsigned int *)(a3 + 84), 0);
  ++*(_DWORD *)(v4 + 232);
  *(_DWORD *)(a3 + 16) = 0;
  v24 = *(void **)(a3 + 56);
  if ( v24 )
  {
    *(_QWORD *)(a3 + 48) = 0;
    result = sub_18003A8D0(v24);
    *(_QWORD *)(a3 + 56) = 0;
  }
  v25 = *(void **)(a3 + 8);
  if ( v25 )
  {
    *(_QWORD *)a3 = 0;
    result = sub_18003A8D0(v25);
    *(_QWORD *)(a3 + 8) = 0;
  }
  v26 = *(void **)(a3 + 40);
  if ( v26 )
  {
    *(_QWORD *)(a3 + 32) = 0;
    result = sub_18003A8D0(v26);
    *(_QWORD *)(a3 + 40) = 0;
  }
  *(_DWORD *)(a3 + 76) &= 0xFC000000;
  *(_DWORD *)(a3 + 76) |= 0x4000000u;
  *(_DWORD *)(a3 + 64) = -1;
  *(_QWORD *)(a3 + 68) = 0;
  *(_QWORD *)a2 = 0;
  return result;
}
