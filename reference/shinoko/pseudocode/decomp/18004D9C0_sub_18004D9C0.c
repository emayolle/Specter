// sub_18004D9C0 size=166
_BYTE *__fastcall sub_18004D9C0(__int64 a1)
{
  _BYTE *result; // rax
  __int64 v3; // rbx
  const char *v4; // rdx

  result = (_BYTE *)qword_18010C470;
  v3 = qword_18010C470;
  if ( *(_QWORD *)(qword_18010C470 + 8120) != a1 )
  {
    if ( (*(_BYTE *)(qword_18010C470 + 10228) & 4) != 0 )
    {
      if ( a1 )
        v4 = *(const char **)(a1 + 8);
      else
        v4 = "<NULL>";
      sub_180052F00("[focus] SetNavWindow(\"%s\")\n", v4);
      result = (_BYTE *)qword_18010C470;
    }
    *(_QWORD *)(v3 + 8120) = a1;
    *(_QWORD *)(v3 + 0x2000) = -1;
  }
  *(_WORD *)(v3 + 8264) = 0;
  *(_BYTE *)(v3 + 8202) = 0;
  result[8201] = result[8265] || result[8202];
  return result;
}
