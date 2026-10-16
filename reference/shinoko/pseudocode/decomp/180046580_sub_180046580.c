// sub_180046580 size=85
__int64 sub_180046580()
{
  __int64 v0; // rbx
  __int64 v1; // rax
  __int64 result; // rax

  v0 = qword_18010C470;
  v1 = *(int *)(qword_18010C470 + 7984);
  if ( (int)v1 <= 0 )
    return sub_180049A30("Calling PopFont() too many times!");
  result = sub_180046120(*(_QWORD *)(*(_QWORD *)(qword_18010C470 + 7992) + 16 * v1 - 16));
  --*(_DWORD *)(v0 + 7984);
  return result;
}
