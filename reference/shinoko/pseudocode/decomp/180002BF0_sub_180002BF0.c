// sub_180002BF0 size=550
__int64 __fastcall sub_180002BF0(__int64 a1, int a2)
{
  unsigned __int64 v2; // r14
  unsigned int v3; // r8d
  unsigned int v5; // r8d
  char *v6; // rbx
  _WORD *v7; // rbx
  _WORD *v8; // r9
  unsigned int v9; // edx
  __int64 v10; // rax
  char *v11; // r9
  unsigned int v12; // edx
  __int64 v13; // rax
  __int64 v14; // rbp
  unsigned __int64 v15; // rsi
  unsigned __int64 v16; // rcx
  __int64 v17; // rax
  __int64 v19; // [rsp+0h] [rbp-48h] BYREF
  char v20; // [rsp+3Ch] [rbp-Ch] BYREF
  _BYTE v21[11]; // [rsp+3Dh] [rbp-Bh] BYREF

  v2 = 0;
  v3 = a2;
  if ( a2 >= 0 )
  {
    if ( (unsigned int)a2 >= 0xA )
    {
      v6 = v21;
      do
      {
        v11 = v6;
        v6 -= 2;
        v12 = v3 / 0x64;
        v13 = v3 % 0x64;
        v3 = v12;
        *(_WORD *)v6 = *(_WORD *)&a00010203040506[2 * v13];
      }
      while ( v12 >= 0xA );
      if ( v12 )
      {
        v6 = v11 - 3;
        *(v11 - 3) = v12 + 48;
      }
    }
    else
    {
      v6 = &v20;
      v20 = a2 + 48;
    }
  }
  else
  {
    v5 = -a2;
    if ( (unsigned int)-a2 >= 0xA )
    {
      v7 = v21;
      do
      {
        v8 = v7--;
        v9 = v5 / 0x64;
        v10 = v5 % 0x64;
        v5 = v9;
        *v7 = *(_WORD *)&a00010203040506[2 * v10];
      }
      while ( v9 >= 0xA );
      if ( v9 )
      {
        v7 = (_WORD *)((char *)v8 - 3);
        *((_BYTE *)v8 - 3) = v9 + 48;
      }
      v6 = (char *)v7 - 1;
      *v6 = 45;
    }
    else
    {
      v6 = (char *)&v19 + 59;
      v20 = 48 - a2;
      *v6 = 45;
    }
  }
  *(_OWORD *)a1 = 0;
  *(_QWORD *)(a1 + 16) = 0;
  *(_QWORD *)(a1 + 24) = 0;
  if ( v6 != v21 )
  {
    v14 = 0x7FFFFFFFFFFFFFFFLL;
    v15 = v21 - v6;
    if ( (unsigned __int64)(v21 - v6) > 0x7FFFFFFFFFFFFFFFLL )
      std::vector<void *>::_Xlen();
    if ( v15 <= 0xF )
    {
      *(_QWORD *)(a1 + 16) = v15;
      *(_QWORD *)(a1 + 24) = 15;
      sub_1800B8BD0(a1, v6, v21 - v6);
      *(_BYTE *)(a1 + v15) = 0;
      return a1;
    }
    if ( (v15 | 0xF) <= 0x7FFFFFFFFFFFFFFFLL )
    {
      v14 = v15 | 0xF;
      if ( (v15 | 0xF) < 0x16 )
        v14 = 22;
      if ( v14 == -1 )
        goto LABEL_32;
      if ( (unsigned __int64)(v14 + 1) < 0x1000 )
      {
        v2 = sub_180093150(v14 + 1);
LABEL_32:
        *(_QWORD *)a1 = v2;
        *(_QWORD *)(a1 + 16) = v15;
        *(_QWORD *)(a1 + 24) = v14;
        sub_1800B8BD0(v2, v6, v21 - v6);
        *(_BYTE *)(v2 + v15) = 0;
        return a1;
      }
      v16 = v14 + 40;
      if ( v14 + 40 < (unsigned __int64)(v14 + 1) )
        Concurrency::cancel_current_task();
    }
    else
    {
      v16 = 0x8000000000000027uLL;
    }
    v17 = sub_180093150(v16);
    if ( !v17 )
      __fastfail(5u);
    v2 = (v17 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
    *(_QWORD *)(v2 - 8) = v17;
    goto LABEL_32;
  }
  *(_QWORD *)(a1 + 24) = 15;
  *(_BYTE *)a1 = 0;
  return a1;
}
