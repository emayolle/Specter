// sub_18004BE60 size=124
__int64 __fastcall sub_18004BE60(const char *a1)
{
  __int64 v1; // rbp
  __int64 v3; // rbx
  unsigned int v4; // eax
  unsigned int v5; // edi

  v1 = qword_18010C470;
  v3 = *(_QWORD *)(qword_18010C470 + 5216);
  v4 = sub_1800360F0(a1, 0, *(unsigned int *)(*(_QWORD *)(v3 + 272) + 4LL * *(int *)(v3 + 264) - 4));
  v5 = v4;
  if ( *(_DWORD *)(*(_QWORD *)v3 + 5304LL) == v4 )
    sub_180053310(v4, 11, a1);
  if ( (*(_BYTE *)(v1 + 10228) & 8) != 0 )
    sub_180052F00("[popup] OpenPopup(\"%s\" -> 0x%08X)\n", a1, v5);
  return sub_18004BEE0(v5, 0);
}
