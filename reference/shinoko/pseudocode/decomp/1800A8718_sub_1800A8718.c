// sub_1800A8718 size=74
__int64 sub_1800A8718()
{
  __int64 (*v0)(void); // rax

  v0 = (__int64 (*)(void))qword_180119000;
  if ( qword_180119000 != -1
    && (qword_180119000
     || (v0 = (__int64 (*)(void))sub_1800A8508(0, "AreFileApisANSI", &unk_1800C2C98, &unk_1800C2C9C)) != nullptr) )
  {
    return v0();
  }
  else
  {
    return 1;
  }
}
