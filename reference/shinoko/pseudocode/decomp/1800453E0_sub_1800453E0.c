// sub_1800453E0 size=112
__int64 sub_1800453E0()
{
  __int64 v0; // rdx
  __int16 v1; // ax
  __int64 result; // rax
  int v3; // ecx
  bool v4; // zf
  int v5; // r8d

  v0 = qword_18010C470;
  v1 = *(_WORD *)(qword_18010C470 + 9696);
  if ( v1 <= 0 )
    return sub_180049A30("Calling EndDisabled() too many times!");
  v3 = *(_DWORD *)(qword_18010C470 + 8016);
  v4 = (*(_DWORD *)(qword_18010C470 + 7680) & 0x400) == 0;
  *(_WORD *)(qword_18010C470 + 9696) = v1 - 1;
  *(_DWORD *)(v0 + 8016) = v3 - 1;
  result = *(_QWORD *)(v0 + 8024);
  v5 = *(_DWORD *)(result + 4LL * (v3 - 2));
  *(_DWORD *)(v0 + 7680) = v5;
  if ( !v4 && (v5 & 0x400) == 0 )
  {
    result = *(unsigned int *)(v0 + 9692);
    *(_DWORD *)(v0 + 3148) = result;
  }
  return result;
}
