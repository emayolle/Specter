// sub_18004C4C0 size=539
__int64 __fastcall sub_18004C4C0(int a1, unsigned __int8 a2)
{
  __int64 v2; // rdi
  __int64 v4; // r14
  int i; // ebx
  __int64 v6; // rcx
  __int64 v7; // rax
  const char *v8; // r8
  __int64 result; // rax
  __int64 v10; // rbx
  __int64 v11; // rsi
  int v12; // ecx
  int v13; // ebp
  __int64 v14; // rdx
  __int64 v15; // r15
  int v16; // eax
  int v17; // ecx
  __int64 v18; // rdx
  __int64 v19; // rcx

  v2 = qword_18010C470;
  v4 = a1;
  if ( (*(_BYTE *)(qword_18010C470 + 10228) & 8) != 0 )
  {
    sub_180052F00("[popup] ClosePopupToLevel(%d), restore_under=%d\n", a1, a2);
    if ( (*(_BYTE *)(v2 + 10228) & 8) != 0 )
    {
      for ( i = v4; i < *(_DWORD *)(v2 + 8048); ++i )
      {
        if ( (*(_BYTE *)(v2 + 10228) & 8) != 0 )
        {
          v6 = *(_QWORD *)(v2 + 8056);
          v7 = *(_QWORD *)(v6 + 56LL * i + 8);
          if ( v7 )
            v8 = *(const char **)(v7 + 8);
          else
            v8 = nullptr;
          sub_180052F00("[popup] - Closing PopupID 0x%08X Window \"%s\"\n", *(_DWORD *)(v6 + 56LL * i), v8);
        }
      }
    }
  }
  result = *(_QWORD *)(v2 + 8056);
  v10 = *(_QWORD *)(56 * v4 + result + 8);
  v11 = *(_QWORD *)(56 * v4 + result + 16);
  v12 = *(_DWORD *)(v2 + 8052);
  if ( (int)v4 > v12 )
  {
    if ( v12 )
      result = (unsigned int)(v12 + v12 / 2);
    else
      result = 8;
    v13 = v4;
    if ( (int)result > (int)v4 )
      v13 = result;
    if ( v13 > v12 )
    {
      result = sub_18003A810(56LL * v13);
      v14 = *(_QWORD *)(v2 + 8056);
      v15 = result;
      if ( v14 )
      {
        sub_1800B8BD0(result, v14, 56LL * *(int *)(v2 + 8048));
        result = sub_18003A8D0(*(LPVOID *)(v2 + 8056));
      }
      *(_QWORD *)(v2 + 8056) = v15;
      *(_DWORD *)(v2 + 8052) = v13;
    }
  }
  *(_DWORD *)(v2 + 8048) = v4;
  if ( a2 && v10 )
  {
    v16 = *(_DWORD *)(v10 + 20);
    if ( (v16 & 0x10000000) != 0 )
      v11 = *(_QWORD *)(v10 + 944);
    if ( !v11 || *(_BYTE *)(v11 + 205) )
    {
      return sub_18004D450(v11, *(_DWORD *)(v2 + 8132) == 0);
    }
    else
    {
      v17 = -1;
      if ( (v16 & 0x1000000) != 0 )
      {
        do
        {
          v10 = *(_QWORD *)(v10 + 944);
          v17 = 0;
        }
        while ( (*(_DWORD *)(v10 + 20) & 0x1000000) != 0 );
      }
      v18 = (unsigned int)(v17 + *(__int16 *)(v10 + 226));
      if ( (int)v18 < 0 )
      {
LABEL_33:
        v19 = 0;
      }
      else
      {
        while ( 1 )
        {
          v19 = *(_QWORD *)(*(_QWORD *)(qword_18010C470 + 5144) + 8 * v18);
          if ( v19 )
          {
            if ( *(_BYTE *)(v19 + 205) && (*(_DWORD *)(v19 + 20) & 0x10200) != 0x10200 )
              break;
          }
          v18 = (unsigned int)(v18 - 1);
          if ( (int)v18 < 0 )
            goto LABEL_33;
        }
      }
      return sub_18004D450(v19, 1);
    }
  }
  return result;
}
