void sub_180017710()
{
  __int64 v0; // rbx
  __int64 v1; // rax
  _BYTE *v2; // rax
  __int64 v3; // rcx
  __int64 v4; // rdx
  __int64 v5; // rcx
  __int64 v6; // rdi
  __int64 v7; // rbx
  __int64 v8; // rax
  __int64 v9; // rax
  void *v10; // rcx
  void *v11; // rcx
  __int128 v12; // [rsp+20h] [rbp-E0h] BYREF
  size_t v13; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v14; // [rsp+38h] [rbp-C8h]
  __int128 v15; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v16; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v17; // [rsp+58h] [rbp-A8h]
  char v18[128]; // [rsp+60h] [rbp-A0h] BYREF
  _BYTE v19[544]; // [rsp+E0h] [rbp-20h] BYREF
  char v20; // [rsp+320h] [rbp+220h] BYREF
  void *v21; // [rsp+328h] [rbp+228h]

  if ( qword_18010C5A0 )
  {
    if ( !byte_18010C95D )
    {
      if ( dword_18010C960 )
      {
        if ( GetTickCount() - dword_18010C960 >= 0x2710 )
        {
          byte_18010C95D = 1;
          v0 = sub_180017A10(&v20, v19);
          v12 = 0;
          v13 = 0;
          v14 = 0;
          v1 = sub_1800B9730(v0);
          sub_180015BF0(&v12, v0, v1);
          if ( v19[537] )
          {
            v2 = v19;
            v3 = 537;
            do
            {
              *v2++ = 0;
              --v3;
            }
            while ( v3 );
          }
          if ( v13 )
          {
            v21 = &unk_18010B660;
            if ( (unsigned int)sub_18008E8C0(&unk_18010B660) )
              sub_18008EE80(5);
            if ( dword_18010B6AC == 0x7FFFFFFF )
            {
              dword_18010B6AC = 2147483646;
              sub_18008EE80(6);
            }
            v4 = qword_18010C530;
            v5 = qword_18010C520;
            if ( qword_18010C520 <= (unsigned __int64)(qword_18010C530 + 1) )
            {
              sub_18002DD60(&qword_18010C510);
              v4 = qword_18010C530;
              v5 = qword_18010C520;
            }
            qword_18010C528 &= v5 - 1;
            v6 = qword_18010C528 + v4;
            v7 = (qword_18010C528 + v4) & (v5 - 1);
            v8 = qword_18010C518;
            if ( !*(_QWORD *)(qword_18010C518 + 8 * v7) )
            {
              *(_QWORD *)(qword_18010C518 + 8 * v7) = sub_180093150(32);
              v5 = qword_18010C520;
              v8 = qword_18010C518;
            }
            sub_180015AE0(*(_QWORD *)(v8 + 8 * (v6 & (v5 - 1))), &v12);
            dword_18010C5B8 = ++qword_18010C530;
            sub_18008E9E0(&unk_18010B660);
            sub_1800229B0(v18, 128, "[QUEUE] Queued script (%zu bytes) for GameManager::CommonUpdate", v13);
            v15 = 0;
            v16 = 0;
            v17 = 0;
            v9 = sub_1800B9730(v18);
            sub_180015BF0(&v15, v18, v9);
            sub_1800291C0(&v15);
            if ( v17 > 0xF )
            {
              v10 = (void *)v15;
              if ( v17 + 1 >= 0x1000 )
              {
                if ( (unsigned __int64)(v15 - *(_QWORD *)(v15 - 8) - 8) > 0x1F )
                  __fastfail(5u);
                v10 = *(void **)(v15 - 8);
              }
              sub_1800931A0(v10);
            }
            sub_180029000(v18);
          }
          if ( v14 > 0xF )
          {
            v11 = (void *)v12;
            if ( v14 + 1 >= 0x1000 )
            {
              if ( (unsigned __int64)(v12 - *(_QWORD *)(v12 - 8) - 8) > 0x1F )
                __fastfail(5u);
              v11 = *(void **)(v12 - 8);
            }
            sub_1800931A0(v11);
          }
        }
      }
      else
      {
        dword_18010C960 = GetTickCount();
      }
    }
    if ( !byte_18010C95C )
    {
      byte_18010C95C = 1;
      if ( byte_1800FAC16 )
        sub_180016B50(1);
    }
  }
}
