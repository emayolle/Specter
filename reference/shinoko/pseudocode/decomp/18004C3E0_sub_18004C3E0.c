// sub_18004C3E0 size=217
void __fastcall sub_18004C3E0(__int64 a1, unsigned __int8 a2)
{
  int v3; // r10d
  int v4; // ebx
  __int64 v5; // r11
  int v6; // r8d
  __int64 v7; // rdx
  __int64 v8; // rax
  const char *v9; // rdx

  v3 = *(_DWORD *)(qword_18010C470 + 8048);
  if ( v3 )
  {
    v4 = 0;
    if ( a1 && v3 > 0 )
    {
      v5 = *(_QWORD *)(qword_18010C470 + 8056);
      do
      {
        if ( *(_QWORD *)(v5 + 56LL * (unsigned int)v4 + 8) )
        {
          v6 = v4;
          while ( 1 )
          {
            v7 = *(_QWORD *)(v5 + 56LL * v6 + 8);
            if ( v7 )
              break;
LABEL_11:
            if ( ++v6 >= v3 )
              goto LABEL_15;
          }
          v8 = a1;
          if ( *(_QWORD *)(a1 + 960) != v7 )
          {
            while ( v8 != v7 )
            {
              v8 = *(_QWORD *)(v8 + 952);
              if ( !v8 )
                goto LABEL_11;
            }
          }
        }
        ++v4;
      }
      while ( v4 < v3 );
    }
    if ( v4 < v3 )
    {
LABEL_15:
      if ( (*(_BYTE *)(qword_18010C470 + 10228) & 8) != 0 )
      {
        if ( a1 )
          v9 = *(const char **)(a1 + 8);
        else
          v9 = "<NULL>";
        sub_180052F00("[popup] ClosePopupsOverWindow(\"%s\")\n", v9);
      }
      sub_18004C4C0((unsigned int)v4, a2);
    }
  }
}
