// sub_180036F60 size=126
void __fastcall sub_180036F60(int a1)
{
  __int64 v1; // rbx
  int v2; // r8d
  int v3; // eax

  v1 = qword_18010C470;
  v2 = a1;
  if ( *(_DWORD *)(qword_18010C470 + 7952) < a1 )
  {
    sub_180049A30("Calling PopStyleColor() too many times!");
    v2 = *(_DWORD *)(v1 + 7952);
  }
  if ( v2 > 0 )
  {
    v3 = *(_DWORD *)(v1 + 7952);
    do
    {
      --v2;
      *(_OWORD *)(v1 + 16LL * *(int *)(*(_QWORD *)(v1 + 7960) + 20LL * v3 - 20) + 3424) = *(_OWORD *)(*(_QWORD *)(v1 + 7960) + 20LL * v3 - 16);
      v3 = *(_DWORD *)(v1 + 7952) - 1;
      *(_DWORD *)(v1 + 7952) = v3;
    }
    while ( v2 > 0 );
  }
}
