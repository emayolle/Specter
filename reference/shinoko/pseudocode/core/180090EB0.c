__int64 __fastcall sub_180090EB0(_QWORD *a1, __int64 a2)
{
  DWORD LastError; // [rsp+20h] [rbp-48h]
  int v4; // [rsp+24h] [rbp-44h]
  DWORD flOldProtect; // [rsp+28h] [rbp-40h] BYREF
  _DWORD *v6; // [rsp+30h] [rbp-38h]
  __int64 v7; // [rsp+38h] [rbp-30h]
  LPVOID lpAddress; // [rsp+40h] [rbp-28h]
  _DWORD *v9; // [rsp+48h] [rbp-20h]
  LPVOID lpMem; // [rsp+50h] [rbp-18h]
  __int64 v13; // [rsp+78h] [rbp+10h]

  if ( dword_18010B928 != GetCurrentThreadId() )
    return 4317;
  if ( dword_18010B92C )
    return (unsigned int)dword_18010B92C;
  if ( !a2 )
    return 87;
  if ( !a1 )
    return 6;
  if ( !*a1 )
  {
    dword_18010B92C = 6;
    qword_18010B930 = (__int64)a1;
    return 6;
  }
  v9 = (_DWORD *)sub_180093150(48);
  v6 = v9;
  if ( v9 )
  {
    v7 = sub_180090E80(*a1, 0);
    v13 = sub_180090E80(a2, 0);
    v4 = *(unsigned __int8 *)(v7 + 62);
    lpAddress = (LPVOID)(*(_QWORD *)(v7 + 72) - *(unsigned __int8 *)(v7 + 62));
    if ( v4 && (unsigned __int64)v4 <= 0x1E )
    {
      if ( *(_QWORD *)(v7 + 80) == v13 )
      {
        flOldProtect = 0;
        if ( VirtualProtect(lpAddress, v4, 0x40u, &flOldProtect) )
        {
          v6[2] = 1;
          *((_QWORD *)v6 + 2) = a1;
          *((_QWORD *)v6 + 4) = v7;
          *((_QWORD *)v6 + 3) = lpAddress;
          v6[10] = flOldProtect;
          *(_QWORD *)v6 = qword_18010B940;
          qword_18010B940 = (__int64)v6;
          return 0;
        }
        LastError = GetLastError();
      }
      else
      {
        LastError = 9;
        if ( dword_18010B920 )
          goto LABEL_14;
      }
    }
    else
    {
      LastError = 9;
      if ( dword_18010B920 )
        goto LABEL_14;
    }
  }
  else
  {
    LastError = 8;
  }
  dword_18010B92C = LastError;
LABEL_14:
  if ( v6 )
  {
    lpMem = v6;
    sub_1800931A0(v6);
    v6 = nullptr;
  }
  qword_18010B930 = (__int64)a1;
  return LastError;
}
