// sub_1800048E0 size=1504
__int64 sub_1800048E0()
{
  __int64 v0; // rsi
  __int64 v1; // rdi
  __int64 v2; // rbx
  __int64 v3; // rax
  __int64 v4; // rbx
  __int64 v5; // rax
  __int64 v6; // rax
  __int128 v7; // xmm6
  void *v8; // rcx
  void *v9; // rcx
  _BYTE *v10; // rax
  __int64 v11; // rcx
  void *v12; // rcx
  _BYTE *v13; // rax
  __int64 v14; // rcx
  __int64 result; // rax
  __int64 v16; // rdx
  __int64 v17; // rcx
  unsigned __int64 v18; // rsi
  unsigned __int64 v19; // rdi
  unsigned __int64 v20; // rax
  unsigned __int64 v21; // r14
  __int64 v22; // rax
  __int64 v23; // r15
  unsigned __int64 i; // rax
  unsigned __int64 v25; // rsi
  __int64 v26; // rbx
  unsigned __int64 v27; // r12
  __int64 v28; // r8
  unsigned __int64 v29; // rcx
  __int64 v30; // rbx
  void *v31; // rcx
  __int64 v32; // rdi
  __int64 v33; // rbx
  __int64 v34; // rax
  void *v35; // rcx
  void *v36; // rcx
  __int128 v37; // [rsp+20h] [rbp-E0h] BYREF
  __int64 v38; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v39; // [rsp+38h] [rbp-C8h]
  _QWORD v40[3]; // [rsp+40h] [rbp-C0h] BYREF
  unsigned __int64 v41; // [rsp+58h] [rbp-A8h]
  _QWORD v42[3]; // [rsp+60h] [rbp-A0h] BYREF
  unsigned __int64 v43; // [rsp+78h] [rbp-88h]
  __int128 v44; // [rsp+80h] [rbp-80h] BYREF
  __int128 v45; // [rsp+90h] [rbp-70h]
  char v46[128]; // [rsp+A0h] [rbp-60h] BYREF
  _BYTE v47[128]; // [rsp+120h] [rbp+20h] BYREF
  _BYTE v48[560]; // [rsp+1A0h] [rbp+A0h] BYREF
  char v49; // [rsp+428h] [rbp+328h] BYREF
  char v50; // [rsp+430h] [rbp+330h] BYREF
  void *v51; // [rsp+438h] [rbp+338h]

  v0 = sub_180005340(&v49, v48);
  v1 = sub_180002E20(v42);
  v2 = sub_180004EC0(&v50, v47);
  v37 = 0;
  v38 = 0;
  v39 = 0;
  v3 = sub_1800B9730(v2);
  sub_180015BF0(&v37, v2, v3);
  v4 = sub_180015300(v40, &v37, v1);
  v5 = sub_1800B9730(v0);
  v6 = sub_180015CF0(v4, v0, v5);
  v44 = *(_OWORD *)v6;
  v7 = *(_OWORD *)(v6 + 16);
  v45 = v7;
  *(_QWORD *)(v6 + 16) = 0;
  *(_QWORD *)(v6 + 24) = 15;
  *(_BYTE *)v6 = 0;
  if ( v41 > 0xF )
  {
    v8 = (void *)v40[0];
    if ( v41 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v40[0] - *(_QWORD *)(v40[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v8 = *(void **)(v40[0] - 8LL);
    }
    sub_1800931A0(v8);
  }
  v40[2] = 0;
  v41 = 15;
  LOBYTE(v40[0]) = 0;
  if ( v39 > 0xF )
  {
    v9 = (void *)v37;
    if ( v39 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v37 - *(_QWORD *)(v37 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v9 = *(void **)(v37 - 8);
    }
    sub_1800931A0(v9);
  }
  if ( v47[123] )
  {
    v10 = v47;
    v11 = 123;
    do
    {
      *v10++ = 0;
      --v11;
    }
    while ( v11 );
  }
  if ( v43 > 0xF )
  {
    v12 = (void *)v42[0];
    if ( v43 + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(v42[0] - *(_QWORD *)(v42[0] - 8LL) - 8LL) > 0x1F )
        __fastfail(5u);
      v12 = *(void **)(v42[0] - 8LL);
    }
    sub_1800931A0(v12);
  }
  v42[2] = 0;
  v43 = 15;
  LOBYTE(v42[0]) = 0;
  if ( v48[544] )
  {
    v13 = v48;
    v14 = 544;
    do
    {
      *v13++ = 0;
      --v14;
    }
    while ( v14 );
  }
  result = v7;
  if ( (_QWORD)v7 )
  {
    v51 = &unk_18010B660;
    if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
      sub_18008EE80(5);
    if ( dword_18010B6AC == 0x7FFFFFFF )
    {
      dword_18010B6AC = 2147483646;
      sub_18008EE80(6);
    }
    v16 = qword_18010C530;
    v17 = qword_18010C520;
    if ( qword_18010C520 > (unsigned __int64)(qword_18010C530 + 1) )
    {
      v21 = qword_18010C518;
      goto LABEL_57;
    }
    v18 = 1;
    if ( qword_18010C520 )
      v18 = qword_18010C520;
    while ( v18 == qword_18010C520 || v18 < 8 )
    {
      if ( 0x7FFFFFFFFFFFFFFLL - v18 < v18 )
        std::vector<void *>::_Xlen(qword_18010C520, 0x7FFFFFFFFFFFFFFLL);
      v18 *= 2LL;
    }
    v19 = qword_18010C528;
    if ( v18 <= 0x1FFFFFFFFFFFFFFFLL )
    {
      v20 = 8 * v18;
      if ( !(8 * v18) )
      {
        v21 = 0;
LABEL_44:
        v23 = 8 * v19;
        for ( i = v18 >> 1; v18 <= i; v18 *= 2LL )
          ;
        v25 = v18 - v17;
        v26 = qword_18010C518 + 8 * v17 - (v23 + qword_18010C518);
        sub_1800B8BD0(8 * v19 + v21, v23 + qword_18010C518, v26);
        v27 = v26 + 8 * v19 + v21;
        if ( v19 > v25 )
        {
          sub_1800B8BD0(v27, qword_18010C518, 8 * v25);
          v30 = v23 + qword_18010C518 - (8 * v25 + qword_18010C518);
          sub_1800B8BD0(v21, 8 * v25 + qword_18010C518, v30);
          v29 = v21 + v30;
          v28 = 8 * v25;
        }
        else
        {
          sub_1800B8BD0(v27, qword_18010C518, 8 * v19);
          sub_1800B9280(v27 + v23, 0, 8 * (v25 - v19));
          v28 = 8 * v19;
          v29 = v21;
        }
        sub_1800B9280(v29, 0, v28);
        v31 = (void *)qword_18010C518;
        if ( !qword_18010C518 )
          goto LABEL_54;
        if ( (unsigned __int64)(8 * qword_18010C520) < 0x1000 )
        {
LABEL_53:
          sub_1800931A0(v31);
LABEL_54:
          qword_18010C518 = v21;
          v17 = v25 + qword_18010C520;
          qword_18010C520 += v25;
          v16 = qword_18010C530;
LABEL_57:
          qword_18010C528 &= v17 - 1;
          v32 = qword_18010C528 + v16;
          v33 = (qword_18010C528 + v16) & (v17 - 1);
          if ( !*(_QWORD *)(v21 + 8 * v33) )
          {
            *(_QWORD *)(qword_18010C518 + 8 * v33) = sub_180093150(32);
            v17 = qword_18010C520;
            v21 = qword_18010C518;
          }
          sub_180015AE0(*(_QWORD *)(v21 + 8 * (v32 & (v17 - 1))), &v44);
          dword_18010C5B8 = ++qword_18010C530;
          sub_18008E9E0(&unk_18010B660);
          sub_1800229B0(v46, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", (size_t)v45);
          v37 = 0;
          v38 = 0;
          v39 = 0;
          v34 = sub_1800B9730(v46);
          sub_180015BF0(&v37, v46, v34);
          sub_1800291C0(&v37);
          if ( v39 > 0xF )
          {
            v35 = (void *)v37;
            if ( v39 + 1 >= 0x1000 )
            {
              if ( (unsigned __int64)(v37 - *(_QWORD *)(v37 - 8) - 8) > 0x1F )
                __fastfail(5u);
              v35 = *(void **)(v37 - 8);
            }
            sub_1800931A0(v35);
          }
          result = sub_180029000(v46);
          goto LABEL_65;
        }
        if ( (unsigned __int64)(qword_18010C518 - *(_QWORD *)(qword_18010C518 - 8) - 8) <= 0x1F )
        {
          v31 = *(void **)(qword_18010C518 - 8);
          goto LABEL_53;
        }
LABEL_55:
        __fastfail(5u);
      }
      if ( v20 < 0x1000 )
      {
        v21 = sub_180093150(8 * v18);
LABEL_43:
        v17 = qword_18010C520;
        goto LABEL_44;
      }
      if ( v20 + 39 >= v20 )
      {
        v22 = sub_180093150(v20 + 39);
        if ( !v22 )
          goto LABEL_55;
        v21 = (v22 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
        *(_QWORD *)(v21 - 8) = v22;
        goto LABEL_43;
      }
    }
    Concurrency::cancel_current_task();
  }
LABEL_65:
  if ( *((_QWORD *)&v45 + 1) > 0xFu )
  {
    v36 = (void *)v44;
    if ( (unsigned __int64)(*((_QWORD *)&v45 + 1) + 1LL) >= 0x1000 )
    {
      if ( (unsigned __int64)(v44 - *(_QWORD *)(v44 - 8) - 8) > 0x1F )
        __fastfail(5u);
      v36 = *(void **)(v44 - 8);
    }
    return sub_1800931A0(v36);
  }
  return result;
}
