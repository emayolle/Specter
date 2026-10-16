// sub_1800A9D90 size=705
unsigned __int64 __fastcall sub_1800A9D90(unsigned __int64 k, char *a2)
{
  char *v2; // r8
  unsigned __int64 v3; // rbx
  char i; // al
  char v5; // r9
  char v6; // di
  char v7; // r10
  char v8; // r11
  int v9; // eax
  _BYTE *v10; // rdi
  bool v11; // zf
  _BYTE *j; // rdi
  __int64 v13; // rsi

  v2 = a2;
  *(_QWORD *)k = 0;
  v3 = k;
  *(_DWORD *)(k + 8) = 0;
  *(_DWORD *)(k + 4) = dword_18010C42C;
  for ( i = *a2; i == 32; i = *v2 )
    ++v2;
  if ( i == 97 )
  {
    *(_DWORD *)k = 265;
LABEL_10:
    *(_DWORD *)(k + 4) = 2;
    goto LABEL_11;
  }
  if ( i != 114 )
  {
    if ( i != 119 )
      goto LABEL_81;
    *(_DWORD *)k = 769;
    goto LABEL_10;
  }
  *(_DWORD *)(k + 4) = 1;
LABEL_11:
  ++v2;
  v5 = 0;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  LOBYTE(a2) = 1;
  while ( *v2 )
  {
    k = (unsigned int)*v2;
    if ( (int)k > 83 )
    {
      k = (unsigned int)(k - 84);
      if ( !(_DWORD)k )
      {
        if ( (*(_DWORD *)v3 & 0x1000) == 0 )
        {
          v9 = *(_DWORD *)v3 | 0x1000;
LABEL_53:
          *(_DWORD *)v3 = v9;
LABEL_54:
          LOBYTE(a2) = 1;
          goto LABEL_55;
        }
        goto LABEL_51;
      }
      k = (unsigned int)(k - 14);
      if ( !(_DWORD)k )
      {
        if ( (*(_DWORD *)v3 & 0xC000) == 0 )
        {
          v9 = *(_DWORD *)v3 | 0x8000;
          goto LABEL_53;
        }
        goto LABEL_51;
      }
      k = (unsigned int)(k - 1);
      if ( (_DWORD)k )
      {
        k = (unsigned int)(k - 11);
        if ( (_DWORD)k )
        {
          k = (unsigned int)(k - 6);
          if ( (_DWORD)k )
          {
            if ( (_DWORD)k != 4 )
              goto LABEL_81;
            if ( (*(_DWORD *)v3 & 0x200) != 0 )
            {
              v9 = *(_DWORD *)v3 | 0x400;
              goto LABEL_53;
            }
          }
          else if ( (*(_DWORD *)v3 & 0xC000) == 0 )
          {
            v9 = *(_DWORD *)v3 | 0x4000;
            goto LABEL_53;
          }
          goto LABEL_51;
        }
        if ( v5 )
          goto LABEL_51;
        *(_DWORD *)(v3 + 4) &= ~0x800u;
      }
      else
      {
        if ( v5 )
          goto LABEL_51;
        *(_DWORD *)(v3 + 4) |= 0x800u;
      }
      v5 = 1;
      LOBYTE(a2) = 1;
    }
    else
    {
      if ( (_DWORD)k == 83 )
      {
        if ( v7 )
          goto LABEL_51;
        *(_DWORD *)v3 |= 0x20u;
LABEL_32:
        v7 = 1;
        LOBYTE(a2) = 1;
        goto LABEL_55;
      }
      k = (unsigned int)(k - 32);
      if ( (_DWORD)k )
      {
        k = (unsigned int)(k - 11);
        if ( (_DWORD)k )
        {
          k = (unsigned int)(k - 1);
          if ( !(_DWORD)k )
          {
            v8 = 1;
LABEL_51:
            LOBYTE(a2) = 0;
            goto LABEL_55;
          }
          k = (unsigned int)(k - 24);
          if ( !(_DWORD)k )
          {
            if ( (*(_DWORD *)v3 & 0x40) == 0 )
            {
              v9 = *(_DWORD *)v3 | 0x40;
              goto LABEL_53;
            }
            goto LABEL_51;
          }
          k = (unsigned int)(k - 10);
          if ( !(_DWORD)k )
          {
            *(_DWORD *)v3 |= 0x80u;
            goto LABEL_54;
          }
          if ( (_DWORD)k != 4 )
            goto LABEL_81;
          if ( v7 )
            goto LABEL_51;
          *(_DWORD *)v3 |= 0x10u;
          goto LABEL_32;
        }
        if ( v6 )
          goto LABEL_51;
        v6 = 1;
        if ( (*(_DWORD *)v3 & 2) != 0 )
          goto LABEL_51;
        LOBYTE(a2) = 1;
        *(_DWORD *)v3 = *(_DWORD *)v3 & 0xFFFFFFFC | 2;
        *(_DWORD *)(v3 + 4) = *(_DWORD *)(v3 + 4) & 0xFFFFFFF8 | 4;
      }
    }
LABEL_55:
    v2 += (_BYTE)a2 != 0;
    if ( !(_BYTE)a2 )
      break;
  }
  v10 = v2 + 1;
  if ( !v8 )
    v10 = v2;
  while ( *v10 == 32 )
    ++v10;
  if ( !v8 )
  {
    v11 = *v10 == 0;
    goto LABEL_63;
  }
  if ( (unsigned int)sub_1800B96A0(v10, &unk_1800C2D50, 3) )
    goto LABEL_81;
  for ( j = v10 + 3; *j == 32; ++j )
    ;
  if ( *j != 61 )
    goto LABEL_81;
  do
    ++j;
  while ( *j == 32 );
  v13 = 5;
  if ( !(unsigned int)sub_1800B0100(j, "UTF-8", 5) )
  {
    *(_DWORD *)v3 |= 0x40000u;
    goto LABEL_77;
  }
  v13 = 8;
  if ( !(unsigned int)sub_1800B0100(j, "UTF-16LEUNICODE", 8) )
  {
    *(_DWORD *)v3 |= 0x20000u;
    goto LABEL_77;
  }
  v13 = 7;
  if ( (unsigned int)sub_1800B0100(j, "UNICODE", 7) )
    goto LABEL_81;
  *(_DWORD *)v3 |= 0x10000u;
LABEL_77:
  for ( k = (unsigned __int64)&j[v13]; *(_BYTE *)k == 32; ++k )
    ;
  v11 = *(_BYTE *)k == 0;
LABEL_63:
  if ( !v11 )
  {
LABEL_81:
    *(_DWORD *)sub_1800A5DDC(k, a2, v2) = 22;
    invalid_parameter_noinfo();
    return v3;
  }
  *(_BYTE *)(v3 + 8) = 1;
  return v3;
}
