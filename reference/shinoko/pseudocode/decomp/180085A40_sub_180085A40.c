// sub_180085A40 size=230
void __fastcall sub_180085A40(__int64 a1, int *a2)
{
  __int64 v2; // rax
  __int64 v3; // rbx
  __int64 v4; // rdi
  __int64 v5; // rsi
  int v6; // eax
  __int64 v7; // r8
  const char *v8; // r9

  v2 = *a2;
  v3 = *((_QWORD *)a2 + 1);
  v4 = qword_18010C470;
  v5 = 24 * v2 + v3;
  if ( 24 * v2 )
  {
    do
    {
      v6 = *(_DWORD *)v3;
      if ( *(_DWORD *)v3 == 1 )
      {
        if ( (*(_BYTE *)(v4 + 10228) & 0x40) != 0 )
        {
          v7 = *(unsigned __int8 *)(v3 + 4);
          v8 = "Clear";
          if ( (_BYTE)v7 )
            v8 = "SelectAll";
          sub_180052F00("[selection] %s: Request: SetAll %d (= %s)\n", "EndMultiSelect", v7, v8);
          v6 = *(_DWORD *)v3;
        }
        else
        {
          v6 = 1;
        }
      }
      if ( v6 == 2 && (*(_BYTE *)(v4 + 10228) & 0x40) != 0 )
        sub_180052F00(
          "[selection] %s: Request: SetRange %I64d..%I64d (0x%I64X..0x%I64X) = %d (dir %d)\n",
          "EndMultiSelect",
          *(_QWORD *)(v3 + 8),
          *(_QWORD *)(v3 + 16),
          *(_QWORD *)(v3 + 8),
          *(_QWORD *)(v3 + 16),
          *(unsigned __int8 *)(v3 + 4),
          *(char *)(v3 + 5));
      v3 += 24;
    }
    while ( v3 != v5 );
  }
}
