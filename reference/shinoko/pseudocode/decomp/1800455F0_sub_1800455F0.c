// sub_1800455F0 size=93
__int64 sub_1800455F0()
{
  __int64 v0; // rdx
  int v1; // r8d
  __int64 result; // rax

  v0 = qword_18010C470;
  v1 = *(_DWORD *)(qword_18010C470 + 8000);
  if ( v1 <= *(__int16 *)(*(_QWORD *)(qword_18010C470 + 10216) + 12LL) )
    return sub_180049A30("Calling PopFocusScope() too many times!");
  result = (unsigned int)(v1 - 1);
  *(_DWORD *)(qword_18010C470 + 8000) = result;
  if ( v1 == 1 )
  {
    *(_DWORD *)(v0 + 7676) = 0;
  }
  else
  {
    result = *(_QWORD *)(v0 + 8008);
    *(_DWORD *)(v0 + 7676) = *(_DWORD *)(result + 8LL * (v1 - 2));
  }
  return result;
}
