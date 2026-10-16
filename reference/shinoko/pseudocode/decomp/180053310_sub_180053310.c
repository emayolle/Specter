// sub_180053310 size=635
void sub_180053310(unsigned int a1, int a2, const char *a3, ...)
{
  __int64 v3; // rdi
  char v5; // r15
  __int64 v7; // rax
  __int64 v8; // rsi
  int v9; // ebx
  int v10; // ecx
  int v11; // ebp
  int v12; // eax
  int v13; // r14d
  __int64 v14; // rax
  __int64 v15; // rdx
  __int64 v16; // r15
  int v17; // edx
  __int64 v18; // xmm0_8
  __int64 v19; // rax
  __int64 v20; // rcx
  __int64 v21; // rax
  int v22; // ecx
  unsigned int v23; // edx
  __int64 v24; // rax
  __int64 v25; // rbp
  __int64 v26; // rsi
  int v27; // eax
  int v28; // eax
  int v29; // edx
  __int64 v30; // r8
  _QWORD v31[2]; // [rsp+30h] [rbp-38h] BYREF
  __int64 v32; // [rsp+88h] [rbp+20h] BYREF
  va_list va; // [rsp+88h] [rbp+20h]
  va_list va1; // [rsp+90h] [rbp+28h] BYREF

  va_start(va1, a3);
  va_start(va, a3);
  v32 = va_arg(va1, _QWORD);
  v3 = qword_18010C470;
  v5 = a2;
  if ( *(_BYTE *)(qword_18010C470 + 10384) )
  {
    v7 = *(int *)(qword_18010C470 + 10356);
    v8 = *(_QWORD *)(qword_18010C470 + 5216);
    if ( (_DWORD)v7 == -1 )
    {
      v9 = 0;
      *(_DWORD *)(qword_18010C470 + 10356) = 0;
      v10 = *(_DWORD *)(v3 + 10372);
      v11 = *(_DWORD *)(v8 + 264) + 1;
      v31[0] = 0;
      if ( v11 > v10 )
      {
        if ( v10 )
          v12 = v10 + v10 / 2;
        else
          v12 = 8;
        v13 = v11;
        if ( v12 > v11 )
          v13 = v12;
        if ( v13 > v10 )
        {
          v14 = sub_18003A810(12LL * v13);
          v15 = *(_QWORD *)(v3 + 10376);
          v16 = v14;
          if ( v15 )
          {
            sub_1800B8BD0(v14, v15, 12LL * *(int *)(v3 + 10368));
            sub_18003A8D0(*(LPVOID *)(v3 + 10376));
          }
          *(_QWORD *)(v3 + 10376) = v16;
          *(_DWORD *)(v3 + 10372) = v13;
        }
      }
      v17 = *(_DWORD *)(v3 + 10368);
      if ( v11 > v17 )
      {
        v18 = v31[0];
        do
        {
          v19 = v17++;
          v20 = 3 * v19;
          v21 = *(_QWORD *)(v3 + 10376);
          *(_QWORD *)(v21 + 4 * v20) = v18;
          *(_DWORD *)(v21 + 4 * v20 + 8) = -1;
        }
        while ( v17 < v11 );
      }
      *(_DWORD *)(v3 + 10368) = v11;
      v22 = *(_DWORD *)(v8 + 264);
      if ( v22 + 1 > 0 )
      {
        do
        {
          if ( v9 >= v22 )
            v23 = a1;
          else
            v23 = *(_DWORD *)(*(_QWORD *)(v8 + 272) + 4LL * v9);
          v24 = v9++;
          *(_DWORD *)(*(_QWORD *)(v3 + 10376) + 12 * v24) = v23;
          v22 = *(_DWORD *)(v8 + 264);
        }
        while ( v9 < v22 + 1 );
      }
    }
    else if ( (_DWORD)v7 == *(_DWORD *)(v8 + 264) )
    {
      v25 = *(_QWORD *)(qword_18010C470 + 10376);
      v26 = 3 * v7;
      if ( *(_DWORD *)(v25 + 12 * v7 + 8) == -1 )
      {
        v31[0] = 0;
        v32 = 0;
        switch ( a2 )
        {
          case 4:
            sub_180035F50(v31, (__int64 *)va, "%d", (unsigned int)a3);
            break;
          case 11:
            v27 = sub_1800B9730(a3);
            sub_180035F50(v31, (__int64 *)va, "%.*s", v27, a3);
            break;
          case 12:
            sub_180035F50(v31, (__int64 *)va, "(void*)0x%p", a3);
            break;
          case 13:
            sub_180035F50(v31, (__int64 *)va, "0x%08X [override]", a1);
            break;
        }
        v28 = *(_DWORD *)(v3 + 10392);
        v29 = v28 - 1;
        if ( !v28 )
          v29 = 0;
        v30 = v32 + 1;
        *(_DWORD *)(v25 + 4 * v26 + 8) = v29;
        sub_180036C60(v3 + 10392, v31[0], v30);
      }
      *(_BYTE *)(v25 + 4 * v26 + 5) = 1;
      *(_BYTE *)(v25 + 4 * v26 + 6) = v5;
    }
  }
}
