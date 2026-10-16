// sub_18006D6E0 size=866
__int64 __fastcall sub_18006D6E0(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v4; // r8
  __int64 v5; // rsi
  int v6; // r14d
  __int64 v7; // rax
  __int64 v8; // rcx
  int v9; // ebx
  __int16 v10; // di
  __int64 v11; // rcx
  int v12; // r9d
  char v13; // al
  char v14; // al
  char v15; // al
  char v16; // al
  char v17; // al
  __int64 v18; // rbx
  int v19; // ebp
  unsigned int v20; // edi
  __int64 v21; // r10
  __int64 v22; // r11
  __int64 v23; // rbx
  int v24; // r8d
  __int64 v25; // rcx
  char v26; // al
  char v27; // al
  char v28; // al
  char v29; // al
  char v30; // al
  int v31; // [rsp+20h] [rbp-28h] BYREF
  int v32; // [rsp+68h] [rbp+20h] BYREF

  v32 = 0;
  v31 = 0;
  if ( (int)sub_180034BF0(a3, "0x%08X,%d", (unsigned int)&v32, (unsigned int)&v31) < 2 )
    return 0;
  v4 = 0;
  v5 = qword_18010C470;
  v6 = v32;
  v7 = *(_QWORD *)(qword_18010C470 + 9968);
  if ( v7 )
    v4 = v7 + 4;
  if ( !v4 )
    goto LABEL_28;
  while ( *(_DWORD *)v4 != v32 )
  {
    v8 = v4 + *(int *)(v4 - 4);
    v4 = 0;
    if ( v8 != v7 + 4 + *(int *)(qword_18010C470 + 9960) )
      v4 = v8;
    if ( !v4 )
      goto LABEL_28;
  }
  v9 = *(__int16 *)(v4 + 14);
  v10 = v31;
  if ( v9 < v31 )
  {
    *(_DWORD *)v4 = 0;
    v6 = v32;
LABEL_28:
    v18 = *(int *)(v5 + 9960);
    v19 = v31;
    v20 = (16 * v31 + 27) & 0xFFFFFFFC;
    sub_1800542F0(v5 + 9960, v20 + (unsigned int)v18);
    v21 = v18;
    *(_DWORD *)(v18 + *(_QWORD *)(v5 + 9968)) = v20;
    v22 = *(_QWORD *)(v5 + 9968);
    v23 = v18 + v22 + 4;
    if ( v23 )
    {
      *(_OWORD *)v23 = 0;
      *(_DWORD *)(v23 + 16) = 0;
    }
    v24 = 0;
    v25 = v21 + v22 + 24;
    if ( v19 >= 4 )
    {
      do
      {
        if ( v25 )
        {
          v26 = *(_BYTE *)(v25 + 14);
          *(_QWORD *)v25 = 0;
          *(_DWORD *)(v25 + 8) = -1;
          *(_WORD *)(v25 + 12) = -1;
          *(_BYTE *)(v25 + 14) = v26 & 0xE0 | 0xC;
        }
        if ( v25 != -16 )
        {
          *(_DWORD *)(v25 + 16) = 0;
          v27 = *(_BYTE *)(v25 + 30);
          *(_DWORD *)(v25 + 20) = 0;
          *(_DWORD *)(v25 + 24) = -1;
          *(_WORD *)(v25 + 28) = -1;
          *(_BYTE *)(v25 + 30) = v27 & 0xE0 | 0xC;
        }
        if ( v25 != -32 )
        {
          *(_DWORD *)(v25 + 32) = 0;
          v28 = *(_BYTE *)(v25 + 46);
          *(_DWORD *)(v25 + 36) = 0;
          *(_DWORD *)(v25 + 40) = -1;
          *(_WORD *)(v25 + 44) = -1;
          *(_BYTE *)(v25 + 46) = v28 & 0xE0 | 0xC;
        }
        if ( v25 != -48 )
        {
          *(_DWORD *)(v25 + 48) = 0;
          v29 = *(_BYTE *)(v25 + 62);
          *(_DWORD *)(v25 + 52) = 0;
          *(_DWORD *)(v25 + 56) = -1;
          *(_WORD *)(v25 + 60) = -1;
          *(_BYTE *)(v25 + 62) = v29 & 0xE0 | 0xC;
        }
        v25 += 64;
        v24 += 4;
      }
      while ( v24 < v19 - 3 );
    }
    for ( ; v24 < v19; ++v24 )
    {
      if ( v25 )
      {
        v30 = *(_BYTE *)(v25 + 14);
        *(_QWORD *)v25 = 0;
        *(_DWORD *)(v25 + 8) = -1;
        *(_WORD *)(v25 + 12) = -1;
        *(_BYTE *)(v25 + 14) = v30 & 0xE0 | 0xC;
      }
      v25 += 16;
    }
    *(_WORD *)(v22 + v21 + 16) = v19;
    *(_WORD *)(v22 + v21 + 18) = v19;
    *(_DWORD *)v23 = v6;
    *(_BYTE *)(v22 + v21 + 20) = 1;
    return v23;
  }
  v11 = v4 + 20;
  v12 = 0;
  *(_OWORD *)v4 = 0;
  *(_DWORD *)(v4 + 16) = 0;
  if ( v9 >= 4 )
  {
    do
    {
      if ( v11 )
      {
        v13 = *(_BYTE *)(v11 + 14);
        *(_QWORD *)v11 = 0;
        *(_DWORD *)(v11 + 8) = -1;
        *(_WORD *)(v11 + 12) = -1;
        *(_BYTE *)(v11 + 14) = v13 & 0xE0 | 0xC;
      }
      if ( v11 != -16 )
      {
        *(_DWORD *)(v11 + 16) = 0;
        v14 = *(_BYTE *)(v11 + 30);
        *(_DWORD *)(v11 + 20) = 0;
        *(_DWORD *)(v11 + 24) = -1;
        *(_WORD *)(v11 + 28) = -1;
        *(_BYTE *)(v11 + 30) = v14 & 0xE0 | 0xC;
      }
      if ( v11 != -32 )
      {
        *(_DWORD *)(v11 + 32) = 0;
        v15 = *(_BYTE *)(v11 + 46);
        *(_DWORD *)(v11 + 36) = 0;
        *(_DWORD *)(v11 + 40) = -1;
        *(_WORD *)(v11 + 44) = -1;
        *(_BYTE *)(v11 + 46) = v15 & 0xE0 | 0xC;
      }
      if ( v11 != -48 )
      {
        *(_DWORD *)(v11 + 48) = 0;
        v16 = *(_BYTE *)(v11 + 62);
        *(_DWORD *)(v11 + 52) = 0;
        *(_DWORD *)(v11 + 56) = -1;
        *(_WORD *)(v11 + 60) = -1;
        *(_BYTE *)(v11 + 62) = v16 & 0xE0 | 0xC;
      }
      v11 += 64;
      v12 += 4;
    }
    while ( v12 < v9 - 3 );
  }
  for ( ; v12 < v9; ++v12 )
  {
    if ( v11 )
    {
      v17 = *(_BYTE *)(v11 + 14);
      *(_QWORD *)v11 = 0;
      *(_DWORD *)(v11 + 8) = -1;
      *(_WORD *)(v11 + 12) = -1;
      *(_BYTE *)(v11 + 14) = v17 & 0xE0 | 0xC;
    }
    v11 += 16;
  }
  *(_DWORD *)v4 = v6;
  *(_WORD *)(v4 + 12) = v10;
  *(_WORD *)(v4 + 14) = v9;
  *(_BYTE *)(v4 + 16) = 1;
  return v4;
}
