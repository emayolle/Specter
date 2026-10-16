// sub_180028550 size=2298
__int64 sub_180028550()
{
  __int64 v0; // rcx
  __int64 v1; // rdx
  float v2; // xmm7_4
  char v3; // al
  __int64 v4; // rbx
  __int64 v5; // rax
  __int64 v6; // rdx
  __int64 v7; // rcx
  unsigned __int64 v8; // rsi
  unsigned __int64 v9; // rdi
  unsigned __int64 v10; // rax
  unsigned __int64 v11; // r14
  __int64 v12; // rax
  __int64 v13; // r15
  unsigned __int64 i; // rax
  unsigned __int64 v15; // rsi
  __int64 v16; // rbx
  unsigned __int64 v17; // r12
  __int64 v18; // r8
  unsigned __int64 v19; // rcx
  __int64 v20; // rbx
  void *v21; // rcx
  __int64 v22; // rdi
  __int64 v23; // rbx
  __int64 v24; // rax
  void *v25; // rcx
  void *v26; // rcx
  _BYTE *v27; // rax
  __int64 v28; // rcx
  __int64 v29; // rcx
  __int64 v30; // rcx
  char v31; // al
  __int64 v32; // rcx
  __int64 v33; // rcx
  char v34; // al
  __int64 v35; // rcx
  __int64 v36; // rcx
  char v37; // al
  __int64 v38; // rcx
  __int64 v39; // rcx
  __int128 v41; // [rsp+20h] [rbp-E0h] BYREF
  size_t v42; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v43; // [rsp+38h] [rbp-C8h]
  __int128 v44; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v45; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v46; // [rsp+58h] [rbp-A8h]
  char v47[128]; // [rsp+60h] [rbp-A0h] BYREF
  _BYTE v48[144]; // [rsp+E0h] [rbp-20h] BYREF
  __int64 v49; // [rsp+1B0h] [rbp+B0h] BYREF
  void *v50; // [rsp+1B8h] [rbp+B8h]

  v49 = 3212836864LL;
  sub_180002F70((__int64)"GM Tools", (float *)&v49);
  v0 = *(_QWORD *)(qword_18010C470 + 5216);
  if ( *(_QWORD *)(v0 + 456) || (v1 = 632, *(_QWORD *)(qword_18010C470 + 8856)) )
    v1 = 584;
  v2 = fmaxf(
         80.0,
         (float)((float)(*(float *)(v1 + v0) - *(float *)(v0 + 280)) - 75.0) - *(float *)(qword_18010C470 + 3228));
  v49 = LODWORD(v2) | 0x41D0000000000000LL;
  sub_18006FED0((__int64)"Debug Console##btn_gm_console", &v49);
  if ( v3 )
  {
    v4 = sub_180026010(&v49, v48);
    v41 = 0;
    v42 = 0;
    v43 = 0;
    v5 = sub_1800B9730(v4);
    sub_180015BF0(&v41, v4, v5);
    if ( !v42 )
    {
LABEL_45:
      if ( v43 > 0xF )
      {
        v26 = (void *)v41;
        if ( v43 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v41 - *(_QWORD *)(v41 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v26 = *(void **)(v41 - 8);
        }
        sub_1800931A0(v26);
      }
      if ( v48[104] )
      {
        v27 = v48;
        v28 = 104;
        do
        {
          *v27++ = 0;
          --v28;
        }
        while ( v28 );
      }
      goto LABEL_53;
    }
    v50 = &unk_18010B660;
    if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
      sub_18008EE80(5);
    if ( dword_18010B6AC == 0x7FFFFFFF )
    {
      dword_18010B6AC = 2147483646;
      sub_18008EE80(6);
    }
    v6 = qword_18010C530;
    v7 = qword_18010C520;
    if ( qword_18010C520 > (unsigned __int64)(qword_18010C530 + 1) )
    {
      v11 = qword_18010C518;
      goto LABEL_37;
    }
    v8 = 1;
    if ( qword_18010C520 )
      v8 = qword_18010C520;
    while ( v8 == qword_18010C520 || v8 < 8 )
    {
      if ( 0x7FFFFFFFFFFFFFFLL - v8 < v8 )
        std::vector<void *>::_Xlen(qword_18010C520, 0x7FFFFFFFFFFFFFFLL);
      v8 *= 2LL;
    }
    v9 = qword_18010C528;
    if ( v8 <= 0x1FFFFFFFFFFFFFFFLL )
    {
      v10 = 8 * v8;
      if ( !(8 * v8) )
      {
        v11 = 0;
LABEL_24:
        v13 = 8 * v9;
        for ( i = v8 >> 1; v8 <= i; v8 *= 2LL )
          ;
        v15 = v8 - v7;
        v16 = qword_18010C518 + 8 * v7 - (v13 + qword_18010C518);
        sub_1800B8BD0(8 * v9 + v11, v13 + qword_18010C518, v16);
        v17 = v16 + 8 * v9 + v11;
        if ( v9 > v15 )
        {
          sub_1800B8BD0(v17, qword_18010C518, 8 * v15);
          v20 = v13 + qword_18010C518 - (8 * v15 + qword_18010C518);
          sub_1800B8BD0(v11, 8 * v15 + qword_18010C518, v20);
          v19 = v11 + v20;
          v18 = 8 * v15;
        }
        else
        {
          sub_1800B8BD0(v17, qword_18010C518, 8 * v9);
          sub_1800B9280(v17 + v13, 0, 8 * (v15 - v9));
          v18 = 8 * v9;
          v19 = v11;
        }
        sub_1800B9280(v19, 0, v18);
        v21 = (void *)qword_18010C518;
        if ( !qword_18010C518 )
          goto LABEL_34;
        if ( (unsigned __int64)(8 * qword_18010C520) < 0x1000 )
        {
LABEL_33:
          sub_1800931A0(v21);
LABEL_34:
          qword_18010C518 = v11;
          v7 = v15 + qword_18010C520;
          qword_18010C520 += v15;
          v6 = qword_18010C530;
LABEL_37:
          qword_18010C528 &= v7 - 1;
          v22 = qword_18010C528 + v6;
          v23 = (qword_18010C528 + v6) & (v7 - 1);
          if ( !*(_QWORD *)(v11 + 8 * v23) )
          {
            *(_QWORD *)(qword_18010C518 + 8 * v23) = sub_180093150(32);
            v7 = qword_18010C520;
            v11 = qword_18010C518;
          }
          sub_180015AE0(*(_QWORD *)(v11 + 8 * (v22 & (v7 - 1))), &v41);
          dword_18010C5B8 = ++qword_18010C530;
          sub_18008E9E0(&unk_18010B660);
          sub_1800229B0(v47, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", v42);
          v44 = 0;
          v45 = 0;
          v46 = 0;
          v24 = sub_1800B9730(v47);
          sub_180015BF0(&v44, v47, v24);
          sub_1800291C0(&v44);
          if ( v46 > 0xF )
          {
            v25 = (void *)v44;
            if ( v46 + 1 >= 0x1000 )
            {
              if ( (unsigned __int64)(v44 - *(_QWORD *)(v44 - 8) - 8) > 0x1F )
                __fastfail(5u);
              v25 = *(void **)(v44 - 8);
            }
            sub_1800931A0(v25);
          }
          sub_180029000(v47);
          goto LABEL_45;
        }
        if ( (unsigned __int64)(qword_18010C518 - *(_QWORD *)(qword_18010C518 - 8) - 8) <= 0x1F )
        {
          v21 = *(void **)(qword_18010C518 - 8);
          goto LABEL_33;
        }
LABEL_35:
        __fastfail(5u);
      }
      if ( v10 < 0x1000 )
      {
        v11 = sub_180093150(8 * v8);
LABEL_23:
        v7 = qword_18010C520;
        goto LABEL_24;
      }
      if ( v10 + 39 >= v10 )
      {
        v12 = sub_180093150(v10 + 39);
        if ( !v12 )
          goto LABEL_35;
        v11 = (v12 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
        *(_QWORD *)(v11 - 8) = v12;
        goto LABEL_23;
      }
    }
    Concurrency::cancel_current_task();
  }
LABEL_53:
  sub_18004AC40();
  v49 = 0x41D0000042960000LL;
  sub_180025AD0("bind_console", &vKey, &v49);
  v29 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v29 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  sub_180071F50();
  v30 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v30 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  v49 = LODWORD(v2) | 0x41D0000000000000LL;
  sub_18006FED0((__int64)"Hierarchy##btn_gm_hierarchy", &v49);
  if ( v31 )
    sub_180026490();
  sub_18004AC40();
  v49 = 0x41D0000042960000LL;
  sub_180025AD0("bind_hierarchy", &dword_1800FAC20, &v49);
  v32 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v32 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  sub_180071F50();
  v33 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v33 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  v49 = LODWORD(v2) | 0x41D0000000000000LL;
  sub_18006FED0((__int64)"Inspector##btn_gm_inspector", &v49);
  if ( v34 )
    sub_180026B90();
  sub_18004AC40();
  v49 = 0x41D0000042960000LL;
  sub_180025AD0("bind_inspector", &dword_1800FAC24, &v49);
  v35 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v35 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  sub_180071F50();
  v36 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v36 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  v49 = LODWORD(v2) | 0x41D0000000000000LL;
  sub_18006FED0((__int64)"AI Debug##btn_gm_aidebug", &v49);
  if ( v37 )
    sub_180027290();
  sub_18004AC40();
  v49 = 0x41D0000042960000LL;
  sub_180025AD0("bind_aidebug", &dword_1800FAC28, &v49);
  v38 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v38 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  sub_180071F50();
  v39 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v39 + 5216) + 209LL) )
  {
    v49 = 0;
    sub_18004AAD0(&v49);
  }
  LOBYTE(v49) = byte_1800FAC2C;
  if ( sub_180071070((__int64)"Ability Data Inspect##chk_gm_ability", (char *)&v49) )
    sub_180027990();
  sub_18004AC40();
  v49 = 0x41D0000042960000LL;
  sub_180025AD0("bind_ability", &dword_1800FAC30, &v49);
  return sub_180003370();
}
