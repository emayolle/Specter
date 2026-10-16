// sub_180037110 size=152
__int64 __fastcall sub_180037110(int a1, _QWORD *a2)
{
  unsigned int v3; // eax
  __int64 v4; // rax
  __int64 v5; // rdi
  __int64 v6; // rbx
  int v7; // xmm1_4
  __int64 result; // rax
  _DWORD v9[6]; // [rsp+20h] [rbp-18h] BYREF

  if ( *((_BYTE *)&unk_1800D5FA0 + 4 * a1 + 1) != 8 )
    return sub_180049A30("Calling PushStyleVar() variant with wrong type!");
  v3 = *((_DWORD *)&unk_1800D5FA0 + a1);
  if ( (_BYTE)v3 != 2 )
    return sub_180049A30("Calling PushStyleVar() variant with wrong type!");
  v4 = HIWORD(v3);
  v9[0] = a1;
  v5 = qword_18010C470;
  v6 = (unsigned int)v4;
  v7 = *(_DWORD *)(v4 + qword_18010C470 + 3140);
  v9[1] = *(_DWORD *)(v4 + qword_18010C470 + 3136);
  v9[2] = v7;
  result = sub_180053EB0(qword_18010C470 + 7968, v9);
  *(_QWORD *)(v6 + v5 + 3136) = *a2;
  return result;
}
