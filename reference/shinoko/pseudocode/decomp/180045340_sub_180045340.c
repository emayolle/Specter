// sub_180045340 size=62
__int64 sub_180045340()
{
  __int64 v0; // rdx
  int v1; // ecx
  __int64 result; // rax

  v0 = qword_18010C470;
  v1 = *(_DWORD *)(qword_18010C470 + 8016);
  if ( v1 <= 1 )
    return sub_180049A30("Calling PopItemFlag() too many times!");
  *(_DWORD *)(qword_18010C470 + 8016) = v1 - 1;
  result = *(_QWORD *)(v0 + 8024);
  *(_DWORD *)(v0 + 7680) = *(_DWORD *)(result + 4LL * (v1 - 2));
  return result;
}
