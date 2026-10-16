// sub_1800A8920 size=66
bool sub_1800A8920()
{
  __int64 v0; // rax
  bool v1; // zf

  if ( qword_180119018 == -1 )
  {
    v0 = 0;
LABEL_5:
    v1 = v0 == 0;
    return !v1;
  }
  v1 = qword_180119018 == 0;
  if ( !qword_180119018 )
  {
    v0 = sub_1800A8508(3, "FlsGetValue2", &unk_1800C2CB0, "FlsGetValue2");
    goto LABEL_5;
  }
  return !v1;
}
