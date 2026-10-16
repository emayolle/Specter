// sub_18004E250 size=190
__int64 __fastcall sub_18004E250(int a1, __int64 a2)
{
  __int64 v2; // rbx
  __int64 v3; // rdi
  __int64 v4; // r8
  __int64 v5; // rcx
  unsigned int v6; // r10d

  v2 = qword_18010C470;
  v3 = a1;
  if ( !a1 )
  {
    a2 = *(_QWORD *)(qword_18010C470 + 8120);
    v4 = *(_QWORD *)(a2 + 1000);
    if ( !v4 || !*(_BYTE *)(v4 + 205) )
      v4 = *(_QWORD *)(qword_18010C470 + 8120);
    *(_QWORD *)(qword_18010C470 + 8120) = v4;
    *(_QWORD *)(v2 + 0x2000) = -1;
    if ( a2 && (*(_BYTE *)(v2 + 10228) & 4) != 0 )
      sub_180052F00(
        "[focus] NavRestoreLayer: from \"%s\" to SetNavWindow(\"%s\")\n",
        *(const char **)(a2 + 8),
        *(const char **)(v4 + 8));
  }
  v5 = *(_QWORD *)(v2 + 8120);
  v6 = *(_DWORD *)(v5 + 4 * v3 + 1008);
  if ( v6 )
    return sub_18004DA70(v6, (unsigned int)v3, 0, 16 * v3 + v5 + 1016);
  LOBYTE(a2) = 1;
  *(_DWORD *)(v2 + 8132) = v3;
  return sub_18004E340(v5, a2);
}
