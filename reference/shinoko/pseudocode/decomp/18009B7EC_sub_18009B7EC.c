// sub_18009B7EC size=124
char __fastcall sub_18009B7EC(__int64 a1)
{
  unsigned __int16 **v1; // rdx
  unsigned __int16 *v2; // r9
  __int64 v3; // r10
  bool v4; // al
  bool v5; // zf
  unsigned int v6; // eax

  v1 = *(unsigned __int16 ***)(a1 + 24);
  *(_QWORD *)(a1 + 24) = v1 + 1;
  v2 = *v1;
  if ( !*v1 || (v3 = *((_QWORD *)v2 + 1)) == 0 )
  {
    v6 = 6;
    *(_QWORD *)(a1 + 64) = "(null)";
    goto LABEL_13;
  }
  if ( *(_DWORD *)(a1 + 52) != 2 )
  {
    if ( *(_DWORD *)(a1 + 52) == 3 || *(_DWORD *)(a1 + 52) == 12 )
    {
      v4 = 1;
      goto LABEL_10;
    }
    if ( *(_DWORD *)(a1 + 52) != 13 )
    {
      v4 = ((*(_BYTE *)(a1 + 57) - 99) & 0xEF) != 0;
      goto LABEL_10;
    }
  }
  v4 = 0;
LABEL_10:
  *(_QWORD *)(a1 + 64) = v3;
  v5 = !v4;
  v6 = *v2;
  if ( v5 )
  {
LABEL_13:
    *(_BYTE *)(a1 + 76) = 0;
    goto LABEL_14;
  }
  *(_BYTE *)(a1 + 76) = 1;
  v6 >>= 1;
LABEL_14:
  *(_DWORD *)(a1 + 72) = v6;
  return 1;
}
