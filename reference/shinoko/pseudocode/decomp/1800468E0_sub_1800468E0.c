// sub_1800468E0 size=102
__int64 sub_1800468E0()
{
  __int64 v0; // rbx
  __int64 result; // rax
  unsigned int v2; // edi

  v0 = *(_QWORD *)(qword_18010C470 + 5216);
  result = sub_1800360F0("##MainListbox", 0, *(unsigned int *)(*(_QWORD *)(v0 + 272) + 4LL * *(int *)(v0 + 264) - 4));
  v2 = result;
  if ( *(_DWORD *)(*(_QWORD *)v0 + 5304LL) == (_DWORD)result )
  {
    sub_180053310((unsigned int)result, 11, "##MainListbox");
    return v2;
  }
  return result;
}
