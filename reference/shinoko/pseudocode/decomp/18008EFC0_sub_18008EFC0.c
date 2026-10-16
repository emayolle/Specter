// sub_18008EFC0 size=42
const char *__fastcall sub_18008EFC0(int a1)
{
  _QWORD *v1; // rax

  v1 = &unk_1800BED40;
  while ( *(_DWORD *)v1 != a1 )
  {
    v1 += 2;
    if ( v1 == (_QWORD *)&unk_1800BF230 )
      return "unknown error";
  }
  return (const char *)v1[1];
}
