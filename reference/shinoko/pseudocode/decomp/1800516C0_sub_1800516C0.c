// sub_1800516C0 size=203
__int64 sub_1800516C0()
{
  __int64 v0; // rbx
  __int64 result; // rax
  void *v2; // rcx

  v0 = qword_18010C470;
  if ( *(_BYTE *)(qword_18010C470 + 8656) && (*(_BYTE *)(qword_18010C470 + 10228) & 2) != 0 )
    sub_180052F00("[dragdrop] ClearDragDrop()\n");
  *(_BYTE *)(v0 + 8656) = 0;
  *(_QWORD *)(v0 + 8684) = 0;
  result = 0;
  *(_QWORD *)(v0 + 8672) = 0;
  *(_DWORD *)(v0 + 8680) = 0;
  *(_OWORD *)(v0 + 8696) = 0;
  *(_OWORD *)(v0 + 8712) = 0;
  *(_WORD *)(v0 + 8728) = 0;
  *(_DWORD *)(v0 + 8692) = -1;
  *(_BYTE *)(v0 + 8730) = 0;
  *(_DWORD *)(v0 + 8776) = 0;
  *(_QWORD *)(v0 + 8784) = 0;
  *(_DWORD *)(v0 + 8780) = 2139095039;
  *(_DWORD *)(v0 + 8792) = -1;
  v2 = *(void **)(v0 + 8808);
  if ( v2 )
  {
    *(_QWORD *)(v0 + 8800) = 0;
    result = sub_18003A8D0(v2);
    *(_QWORD *)(v0 + 8808) = 0;
  }
  *(_OWORD *)(v0 + 8816) = 0;
  return result;
}
