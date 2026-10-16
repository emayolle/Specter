// sub_18009BC50 size=153
char __fastcall sub_18009BC50(__int64 a1)
{
  const char **v1; // rdx
  const char *v3; // rcx
  int v4; // r8d
  int v5; // edx
  char v6; // r9
  int v7; // edx
  int v8; // edx
  int v9; // eax

  v1 = *(const char ***)(a1 + 24);
  *(_QWORD *)(a1 + 24) = v1 + 1;
  v3 = *v1;
  v4 = *(_DWORD *)(a1 + 48);
  v5 = *(_DWORD *)(a1 + 52);
  v6 = *(_BYTE *)(a1 + 57);
  if ( v4 == -1 )
    v4 = 0x7FFFFFFF;
  *(_QWORD *)(a1 + 64) = v3;
  v7 = v5 - 2;
  if ( v7 && ((v8 = v7 - 1) == 0 || v8 == 9 || *(_DWORD *)(a1 + 52) != 13 && ((v6 - 99) & 0xEF) != 0) )
  {
    if ( !v3 )
    {
      v3 = (const char *)L"(null)";
      *(_QWORD *)(a1 + 64) = L"(null)";
    }
    *(_BYTE *)(a1 + 76) = 1;
    v9 = sub_1800A6050(v3, v4);
  }
  else
  {
    if ( !v3 )
    {
      v3 = "(null)";
      *(_QWORD *)(a1 + 64) = "(null)";
    }
    v9 = sub_1800A5EC0(v3, v4);
  }
  *(_DWORD *)(a1 + 72) = v9;
  return 1;
}
