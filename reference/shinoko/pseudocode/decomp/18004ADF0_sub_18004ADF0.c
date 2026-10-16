// sub_18004ADF0 size=67
__int64 sub_18004ADF0()
{
  __int64 v0; // rdx
  __int64 v1; // r8
  __int64 result; // rax
  int v3; // ecx

  v0 = *(_QWORD *)(qword_18010C470 + 5216);
  v1 = *(int *)(v0 + 496);
  if ( (int)v1 <= 0 )
    return sub_180049A30("Calling PopItemWidth() too many times!");
  v3 = *(_DWORD *)(*(_QWORD *)(v0 + 504) + 4 * v1 - 4);
  result = (unsigned int)(v1 - 1);
  *(_DWORD *)(v0 + 496) = result;
  *(_DWORD *)(v0 + 488) = v3;
  return result;
}
