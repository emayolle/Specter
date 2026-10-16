// sub_180036FE0 size=144
__int64 __fastcall sub_180036FE0(int a1, float a2)
{
  unsigned int v2; // eax
  __int64 v3; // rax
  __int64 v4; // rdi
  __int64 v5; // rbx
  __int64 result; // rax
  _DWORD v7[4]; // [rsp+20h] [rbp-28h] BYREF

  if ( *((_BYTE *)&unk_1800D5FA0 + 4 * a1 + 1) != 8 )
    return sub_180049A30("Calling PushStyleVar() variant with wrong type!");
  v2 = *((_DWORD *)&unk_1800D5FA0 + a1);
  if ( (_BYTE)v2 != 1 )
    return sub_180049A30("Calling PushStyleVar() variant with wrong type!");
  v3 = HIWORD(v2);
  v7[0] = a1;
  v4 = qword_18010C470;
  v5 = (unsigned int)v3;
  v7[1] = *(_DWORD *)(v3 + qword_18010C470 + 3136);
  result = sub_180053EB0(qword_18010C470 + 7968, v7);
  *(float *)(v5 + v4 + 3136) = a2;
  return result;
}
