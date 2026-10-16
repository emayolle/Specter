// sub_180029AB0 size=1808
__int64 (__fastcall *__fastcall sub_180029AB0(__int64 a1))(_QWORD)
{
  int v2; // eax
  bool v3; // di
  __int64 v4; // rcx
  __int64 v5; // rdx
  __int64 v6; // r8
  __int128 *v7; // rbx
  void *v8; // rcx
  int v9; // eax
  void *v10; // rcx
  __int64 (__fastcall *v11)(__int64, __int128 *, _QWORD, __int64); // rbx
  __int64 v12; // rax
  __int128 *v13; // rdx
  int v14; // eax
  int v15; // ebx
  _BYTE *v16; // rcx
  __int64 v17; // rdx
  const char *v18; // rax
  const char *v19; // rbx
  __int64 v20; // rax
  int v21; // ebx
  const char *v22; // rax
  const char *v23; // rbx
  __int64 v24; // rax
  void *v25; // rcx
  void *v26; // rcx
  void *v27; // rcx
  int v28; // eax
  void *v29; // rcx
  __int64 (__fastcall *result)(_QWORD); // rax
  __int128 v31; // [rsp+20h] [rbp-E0h] BYREF
  __int64 v32; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v33; // [rsp+38h] [rbp-C8h]
  __int128 v34; // [rsp+40h] [rbp-C0h] BYREF
  __int128 v35; // [rsp+50h] [rbp-B0h]
  _BYTE v36[16]; // [rsp+60h] [rbp-A0h] BYREF
  _BYTE v37[512]; // [rsp+70h] [rbp-90h] BYREF
  char v38; // [rsp+298h] [rbp+198h] BYREF

  if ( qword_18010C5A0 && dword_18010C5B8 )
  {
    v34 = 0;
    *(_QWORD *)&v35 = 0;
    *((_QWORD *)&v35 + 1) = 15;
    LOBYTE(v34) = 0;
    v2 = sub_18008E950(&unk_18010B660);
    v3 = v2 == 0;
    if ( !v2 )
    {
      do
      {
        if ( !qword_18010C530 )
        {
          if ( v3 )
            sub_18008E9E0(&unk_18010B660);
          break;
        }
        v4 = qword_18010C520;
        v5 = qword_18010C528;
        v6 = qword_18010C518;
        v7 = *(__int128 **)(qword_18010C518 + 8 * (qword_18010C528 & (qword_18010C520 - 1)));
        if ( &v34 != v7 )
        {
          if ( *((_QWORD *)&v35 + 1) > 0xFu )
          {
            v8 = (void *)v34;
            if ( (unsigned __int64)(*((_QWORD *)&v35 + 1) + 1LL) >= 0x1000 )
            {
              if ( (unsigned __int64)(v34 - *(_QWORD *)(v34 - 8) - 8) > 0x1F )
                goto LABEL_69;
              v8 = *(void **)(v34 - 8);
            }
            sub_1800931A0(v8);
          }
          *(_QWORD *)&v35 = 0;
          *((_QWORD *)&v35 + 1) = 15;
          LOBYTE(v34) = 0;
          v34 = *v7;
          v35 = v7[1];
          *((_QWORD *)v7 + 2) = 0;
          *((_QWORD *)v7 + 3) = 15;
          *(_BYTE *)v7 = 0;
          v5 = qword_18010C528;
          v4 = qword_18010C520;
          v6 = qword_18010C518;
        }
        sub_180015D80(*(_QWORD *)(v6 + 8 * (v5 & (v4 - 1))));
        v9 = --qword_18010C530;
        if ( qword_18010C530 )
          ++qword_18010C528;
        else
          qword_18010C528 = 0;
        dword_18010C5B8 = v9;
        if ( v3 )
          sub_18008E9E0(&unk_18010B660);
        if ( (_QWORD)v35 )
        {
          if ( !qword_18010C5A0 )
          {
            sub_180028FB0("[LUA] execute: no state\n");
            sub_180029000("[LUA] execute: no state");
            v31 = 0;
            *(_QWORD *)&v31 = sub_180093150(64);
            v32 = 62;
            v33 = 63;
            strcpy((char *)v31, "[LUA] execute: no state (waiting for game to load first chunk)");
            sub_1800291C0(&v31);
            goto LABEL_20;
          }
          if ( !qword_18010C5A8 )
          {
            sub_180028FB0("[LUA] execute: no orig\n");
            sub_180029000("[LUA] execute: no orig");
            v31 = 0;
            *(_QWORD *)&v31 = sub_180093150(32);
            v32 = 22;
            v33 = 31;
            strcpy((char *)v31, "[LUA] execute: no orig");
            sub_1800291C0(&v31);
LABEL_20:
            if ( v33 > 0xF )
            {
              v10 = (void *)v31;
              if ( v33 + 1 >= 0x1000 )
              {
                if ( (unsigned __int64)(v31 - *(_QWORD *)(v31 - 8) - 8) > 0x1F )
                  goto LABEL_69;
                v10 = *(void **)(v31 - 8);
              }
              sub_1800931A0(v10);
            }
            goto LABEL_62;
          }
          sub_180028FB0("[LUA] execute size=%zu\n", (size_t)v35);
          sub_180029000("[LUA] execute size=%zu", (size_t)v35);
          v11 = (__int64 (__fastcall *)(__int64, __int128 *, _QWORD, __int64))qword_18010C5A8;
          v12 = sub_180029500(&v38, v36);
          v13 = &v34;
          if ( *((_QWORD *)&v35 + 1) > 0xFu )
            v13 = (__int128 *)v34;
          v14 = v11(qword_18010C5A0, v13, (unsigned int)v35, v12);
          v15 = v14;
          if ( v36[9] )
          {
            v16 = v36;
            v17 = 9;
            do
            {
              *v16++ = 0;
              --v17;
            }
            while ( v17 );
          }
          sub_180028FB0("[LUA] loadbuffer ret=%d\n", v14);
          sub_180029000("[LUA] loadbuffer ret=%d", v15);
          if ( v15 )
          {
            if ( qword_18010C5D0 )
              v18 = (const char *)qword_18010C5D0(qword_18010C5A0, 0xFFFFFFFFLL, 0);
            else
              v18 = "<null>";
            v19 = "<null>";
            if ( v18 )
              v19 = v18;
            sub_180028FB0("[LUA] loadbuffer error: %s\n", v19);
            sub_180029000("[LUA] loadbuffer error: %s", v19);
            sub_1800229B0(v37, 512, "[SYNTAX ERROR] loadbuffer: %s", v19);
            v31 = 0;
            v32 = 0;
            v33 = 0;
            v20 = sub_1800B9730(v37);
            sub_180015BF0(&v31, v37, v20);
            sub_1800291C0(&v31);
          }
          else
          {
            if ( qword_18010C5C0 )
              v21 = qword_18010C5C0(qword_18010C5A0, 0, 0, 0);
            else
              v21 = -1;
            sub_180028FB0("[LUA] pcall ret=%d\n", v21);
            sub_180029000("[LUA] pcall ret=%d", v21);
            if ( !v21 )
            {
              v31 = 0;
              *(_QWORD *)&v31 = sub_180093150(48);
              v32 = 36;
              v33 = 47;
              strcpy((char *)v31, "[EXEC] Script executed successfully!");
              sub_1800291C0(&v31);
              if ( v33 > 0xF )
              {
                v26 = (void *)v31;
                if ( v33 + 1 >= 0x1000 )
                {
                  if ( (unsigned __int64)(v31 - *(_QWORD *)(v31 - 8) - 8) > 0x1F )
LABEL_69:
                    __fastfail(5u);
                  v26 = *(void **)(v31 - 8);
                }
                sub_1800931A0(v26);
              }
              sub_180029000((const char *)&xmmword_1800D3B58);
              goto LABEL_62;
            }
            if ( qword_18010C5D0 )
              v22 = (const char *)qword_18010C5D0(qword_18010C5A0, 0xFFFFFFFFLL, 0);
            else
              v22 = "<null>";
            v23 = "<null>";
            if ( v22 )
              v23 = v22;
            sub_180028FB0("[LUA] exec error: %s\n", v23);
            sub_180029000("[LUA] exec error: %s", v23);
            sub_1800229B0(v37, 512, "[LUA ERROR] exec: %s", v23);
            v31 = 0;
            v32 = 0;
            v33 = 0;
            v24 = sub_1800B9730(v37);
            sub_180015BF0(&v31, v37, v24);
            sub_1800291C0(&v31);
          }
          if ( v33 > 0xF )
          {
            v25 = (void *)v31;
            if ( v33 + 1 >= 0x1000 )
            {
              if ( (unsigned __int64)(v31 - *(_QWORD *)(v31 - 8) - 8) > 0x1F )
                goto LABEL_69;
              v25 = *(void **)(v31 - 8);
            }
            sub_1800931A0(v25);
          }
          if ( qword_18010C5C8 )
            qword_18010C5C8(qword_18010C5A0, 4294967294LL);
        }
LABEL_62:
        if ( *((_QWORD *)&v35 + 1) > 0xFu )
        {
          v27 = (void *)v34;
          if ( (unsigned __int64)(*((_QWORD *)&v35 + 1) + 1LL) >= 0x1000 )
          {
            if ( (unsigned __int64)(v34 - *(_QWORD *)(v34 - 8) - 8) > 0x1F )
              goto LABEL_80;
            v27 = *(void **)(v34 - 8);
          }
          sub_1800931A0(v27);
        }
        v34 = 0;
        *(_QWORD *)&v35 = 0;
        *((_QWORD *)&v35 + 1) = 15;
        LOBYTE(v34) = 0;
        v28 = sub_18008E950(&unk_18010B660);
        v3 = v28 == 0;
      }
      while ( !v28 );
    }
    if ( *((_QWORD *)&v35 + 1) > 0xFu )
    {
      v29 = (void *)v34;
      if ( (unsigned __int64)(*((_QWORD *)&v35 + 1) + 1LL) >= 0x1000 )
      {
        if ( (unsigned __int64)(v34 - *(_QWORD *)(v34 - 8) - 8) > 0x1F )
LABEL_80:
          __fastfail(5u);
        v29 = *(void **)(v34 - 8);
      }
      sub_1800931A0(v29);
    }
  }
  result = qword_18010C5B0;
  if ( qword_18010C5B0 )
    return (__int64 (__fastcall *)(_QWORD))qword_18010C5B0(a1);
  return result;
}
