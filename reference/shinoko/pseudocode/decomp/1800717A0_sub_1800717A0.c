// sub_1800717A0 size=78
char __fastcall sub_1800717A0(__int64 a1, int *a2, int a3)
{
  char result; // al
  int v5; // ecx
  int v6; // [rsp+40h] [rbp+18h] BYREF

  v6 = a3;
  LOBYTE(v6) = (*a2 & 0x10000) != 0;
  result = sub_180071070((__int64)"Alpha Bar", (char *)&v6);
  if ( result )
  {
    v5 = *a2;
    if ( (_BYTE)v6 )
      *a2 = v5 | 0x10000;
    else
      *a2 = v5 & 0xFFFEFFFF;
  }
  return result;
}
