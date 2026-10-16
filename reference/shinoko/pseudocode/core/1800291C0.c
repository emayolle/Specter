__int64 __fastcall sub_1800291C0(__int64 a1)
{
  __int64 v2; // rdx
  unsigned __int64 v3; // rsi
  __int64 v4; // rcx
  unsigned __int64 v5; // rbx
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

  if ( (unsigned int)sub_18008E8C0(&unk_18010B6B0) )
    sub_18008EE80(5);
  if ( dword_18010B6FC == 0x7FFFFFFF )
  {
    dword_18010B6FC = 2147483646;
    sub_18008EE80(6);
  }
  v2 = qword_18010C500;
  if ( (unsigned __int64)qword_18010C500 < 0xC8 )
  {
    v3 = qword_18010C4F8;
  }
  else
  {
    sub_180015D80(*(_QWORD *)(qword_18010C4E8 + 8 * (qword_18010C4F8 & (qword_18010C4F0 - 1))));
    v2 = --qword_18010C500;
    if ( qword_18010C500 )
    {
      v3 = ++qword_18010C4F8;
    }
    else
    {
      v3 = 0;
      qword_18010C4F8 = 0;
    }
  }
  v4 = qword_18010C4F0;
  if ( qword_18010C4F0 <= (unsigned __int64)(v2 + 1) )
  {
    v5 = 1;
    if ( qword_18010C4F0 )
      v5 = qword_18010C4F0;
    while ( v5 == qword_18010C4F0 || v5 < 8 )
    {
      if ( 0x7FFFFFFFFFFFFFFLL - v5 < v5 )
        std::vector<void *>::_Xlen();
      v5 *= 2LL;
    }
    if ( v5 <= 0x1FFFFFFFFFFFFFFFLL )
    {
      v6 = 8 * v5;
      if ( !(8 * v5) )
      {
        v7 = 0;
LABEL_24:
        v9 = 8 * v3;
        for ( i = v5 >> 1; v5 <= i; v5 *= 2LL )
          ;
        v11 = v5 - v4;
        v12 = qword_18010C4E8 + 8 * v4 - (v9 + qword_18010C4E8);
        sub_1800B8BD0(8 * v3 + v7, v9 + qword_18010C4E8, v12);
        v13 = v12 + 8 * v3 + v7;
        if ( v3 > v11 )
        {
          sub_1800B8BD0(v13, qword_18010C4E8, 8 * v11);
          v16 = v9 + qword_18010C4E8 - (8 * v11 + qword_18010C4E8);
          sub_1800B8BD0(v7, 8 * v11 + qword_18010C4E8, v16);
          v15 = v7 + v16;
          v14 = 8 * v11;
        }
        else
        {
          sub_1800B8BD0(v13, qword_18010C4E8, 8 * v3);
          sub_1800B9280(v13 + v9, 0, 8 * (v11 - v3));
          v14 = 8 * v3;
          v15 = v7;
        }
        sub_1800B9280(v15, 0, v14);
        v17 = (void *)qword_18010C4E8;
        if ( !qword_18010C4E8 )
          goto LABEL_34;
        if ( (unsigned __int64)(8 * qword_18010C4F0) < 0x1000 )
        {
LABEL_33:
          sub_1800931A0(v17);
LABEL_34:
          qword_18010C4E8 = v7;
          v4 = v11 + qword_18010C4F0;
          qword_18010C4F0 += v11;
          v2 = qword_18010C500;
          v3 = qword_18010C4F8;
          goto LABEL_37;
        }
        if ( (unsigned __int64)(qword_18010C4E8 - *(_QWORD *)(qword_18010C4E8 - 8) - 8) <= 0x1F )
        {
          v17 = *(void **)(qword_18010C4E8 - 8);
          goto LABEL_33;
        }
LABEL_35:
        __fastfail(5u);
      }
      if ( v6 < 0x1000 )
      {
        v7 = sub_180093150(8 * v5);
LABEL_23:
        v4 = qword_18010C4F0;
        goto LABEL_24;
      }
      if ( v6 + 39 >= v6 )
      {
        v8 = sub_180093150(v6 + 39);
        if ( !v8 )
          goto LABEL_35;
        v7 = (v8 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
        *(_QWORD *)(v7 - 8) = v8;
        goto LABEL_23;
      }
    }
    Concurrency::cancel_current_task();
  }
  v7 = qword_18010C4E8;
LABEL_37:
  qword_18010C4F8 = (v4 - 1) & v3;
  v18 = qword_18010C4F8 + v2;
  v19 = (qword_18010C4F8 + v2) & (v4 - 1);
  if ( !*(_QWORD *)(v7 + 8 * v19) )
  {
    *(_QWORD *)(qword_18010C4E8 + 8 * v19) = sub_180093150(32);
    v4 = qword_18010C4F0;
    v7 = qword_18010C4E8;
  }
  sub_180015AE0(*(_QWORD *)(v7 + 8 * (v18 & (v4 - 1))), a1);
  ++qword_18010C500;
  return sub_18008E9E0(&unk_18010B6B0);
}
