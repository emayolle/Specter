// sub_18004C770 size=147
char sub_18004C770()
{
  __int64 v0; // rbx
  __int64 v1; // rax
  int v2; // edi
  char result; // al

  v0 = qword_18010C470;
  v1 = *(_QWORD *)(qword_18010C470 + 5216);
  if ( (*(_DWORD *)(v1 + 20) & 0x4000000) == 0 || !*(_DWORD *)(qword_18010C470 + 8064) )
    return sub_180049A30("Calling EndPopup() too many times or in wrong window!");
  if ( *(_QWORD *)(qword_18010C470 + 8120) == v1
    && *(_BYTE *)(qword_18010C470 + 8265)
    && !*(_DWORD *)(qword_18010C470 + 8132) )
  {
    *(_DWORD *)(qword_18010C470 + 8268) &= 0xFFFFFFF2;
    *(_DWORD *)(v0 + 8268) |= 2u;
  }
  v2 = *(_DWORD *)(v0 + 5044);
  if ( (*(_DWORD *)(v1 + 20) & 0x1000000) != 0 )
    *(_DWORD *)(v0 + 5044) = *(_DWORD *)(v1 + 16);
  result = sub_180044DF0();
  *(_DWORD *)(v0 + 5044) = v2;
  return result;
}
