void __fastcall sub_18002C7A0(__int64 a1)
{
  __int64 v2; // rdx
  __int64 v3; // rcx
  unsigned __int64 v4; // rbx
  unsigned __int64 v5; // rsi
  unsigned __int64 v6; // rax
  unsigned __int64 v7; // r14
  __int64 v8; // rax
  __int64 v9; // r15
  unsigned __int64 i; // rax
  unsigned __int64 v11; // rbx
  __int64 v12; // rdi
  unsigned __int64 v13; // r12
  __int64 v14; // r8
  unsigned __int64 v15; // rcx
  __int64 v16; // rdi
  void *v17; // rcx
  __int64 v18; // rdi
  __int64 v19; // rbx
  __int64 v20; // rax
  void *v21; // rcx
  __int128 v22; // [rsp+20h] [rbp-E8h] BYREF
  __int64 v23; // [rsp+30h] [rbp-D8h]
  unsigned __int64 v24; // [rsp+38h] [rbp-D0h]
  char v25[200]; // [rsp+40h] [rbp-C8h] BYREF

  if ( !*(_QWORD *)(a1 + 16) )
    return;
  if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
    sub_18008EE80(5);
  if ( dword_18010B6AC == 0x7FFFFFFF )
  {
    dword_18010B6AC = 2147483646;
    sub_18008EE80(6);
  }
  v2 = qword_18010C530;
  v3 = qword_18010C520;
  if ( qword_18010C520 > (unsigned __int64)(qword_18010C530 + 1) )
  {
    v7 = qword_18010C518;
    goto LABEL_33;
  }
  v4 = 1;
  if ( qword_18010C520 )
    v4 = qword_18010C520;
  while ( v4 == qword_18010C520 || v4 < 8 )
  {
    if ( 0x7FFFFFFFFFFFFFFLL - v4 < v4 )
      std::vector<void *>::_Xlen(qword_18010C520, 0x7FFFFFFFFFFFFFFLL);
    v4 *= 2LL;
  }
  v5 = qword_18010C528;
  if ( v4 > 0x1FFFFFFFFFFFFFFFLL )
    goto LABEL_46;
  v6 = 8 * v4;
  if ( !(8 * v4) )
  {
    v7 = 0;
    goto LABEL_20;
  }
  if ( v6 >= 0x1000 )
  {
    if ( v6 + 39 >= v6 )
    {
      v8 = sub_180093150(v6 + 39);
      if ( !v8 )
        goto LABEL_31;
      v7 = (v8 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
      *(_QWORD *)(v7 - 8) = v8;
      goto LABEL_19;
    }
LABEL_46:
    Concurrency::cancel_current_task();
  }
  v7 = sub_180093150(8 * v4);
LABEL_19:
  v3 = qword_18010C520;
LABEL_20:
  v9 = 8 * v5;
  for ( i = v4 >> 1; v4 <= i; v4 *= 2LL )
    ;
  v11 = v4 - v3;
  v12 = qword_18010C518 + 8 * v3 - (v9 + qword_18010C518);
  sub_1800B8BD0(8 * v5 + v7, v9 + qword_18010C518, v12);
  v13 = v12 + 8 * v5 + v7;
  if ( v5 > v11 )
  {
    sub_1800B8BD0(v13, qword_18010C518, 8 * v11);
    v16 = v9 + qword_18010C518 - (8 * v11 + qword_18010C518);
    sub_1800B8BD0(v7, 8 * v11 + qword_18010C518, v16);
    v15 = v7 + v16;
    v14 = 8 * v11;
  }
  else
  {
    sub_1800B8BD0(v13, qword_18010C518, 8 * v5);
    sub_1800B9280(v13 + v9, 0, 8 * (v11 - v5));
    v14 = 8 * v5;
    v15 = v7;
  }
  sub_1800B9280(v15, 0, v14);
  v17 = (void *)qword_18010C518;
  if ( !qword_18010C518 )
    goto LABEL_30;
  if ( (unsigned __int64)(8 * qword_18010C520) >= 0x1000 )
  {
    if ( (unsigned __int64)(qword_18010C518 - *(_QWORD *)(qword_18010C518 - 8) - 8) <= 0x1F )
    {
      v17 = *(void **)(qword_18010C518 - 8);
      goto LABEL_29;
    }
LABEL_31:
    __fastfail(5u);
  }
LABEL_29:
  sub_1800931A0(v17);
LABEL_30:
  qword_18010C518 = v7;
  v3 = v11 + qword_18010C520;
  qword_18010C520 += v11;
  v2 = qword_18010C530;
LABEL_33:
  qword_18010C528 &= v3 - 1;
  v18 = qword_18010C528 + v2;
  v19 = (qword_18010C528 + v2) & (v3 - 1);
  if ( !*(_QWORD *)(v7 + 8 * v19) )
  {
    *(_QWORD *)(qword_18010C518 + 8 * v19) = sub_180093150(32);
    v3 = qword_18010C520;
    v7 = qword_18010C518;
  }
  sub_180015AE0(*(_QWORD *)(v7 + 8 * (v18 & (v3 - 1))), a1);
  dword_18010C5B8 = ++qword_18010C530;
  sub_18008E9E0(&unk_18010B660);
  sub_1800229B0(v25, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", *(_QWORD *)(a1 + 16));
  v22 = 0;
  v23 = 0;
  v24 = 0;
  v20 = sub_1800B9730(v25);
  sub_180015BF0(&v22, v25, v20);
  sub_1800291C0(&v22);
  if ( v24 > 0xF )
  {
    v21 = (void *)v22;
    if ( v24 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v22 - *(_QWORD *)(v22 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v21 = *(void **)(v22 - 8);
    }
    sub_1800931A0(v21);
  }
  sub_180029000(v25);
}
