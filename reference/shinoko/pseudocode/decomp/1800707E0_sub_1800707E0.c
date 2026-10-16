// sub_1800707E0 size=113
__int64 __fastcall sub_1800707E0(__int64 a1, int a2)
{
  const char *v2; // rsi
  __int64 result; // rax
  unsigned int v5; // edi

  v2 = "#SCROLLY";
  if ( !a2 )
    v2 = "#SCROLLX";
  result = sub_1800360F0(v2, 0, *(unsigned int *)(*(_QWORD *)(a1 + 272) + 4LL * *(int *)(a1 + 264) - 4));
  v5 = result;
  if ( *(_DWORD *)(*(_QWORD *)a1 + 5304LL) == (_DWORD)result )
  {
    sub_180053310(result, 11, v2);
    return v5;
  }
  return result;
}
