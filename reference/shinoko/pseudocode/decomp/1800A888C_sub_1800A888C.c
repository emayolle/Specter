// sub_1800A888C size=98
__int64 __fastcall sub_1800A888C(__int64 a1, unsigned int a2)
{
  __int64 (__fastcall *v2)(__int64, _QWORD); // rax

  v2 = (__int64 (__fastcall *)(__int64, _QWORD))qword_1801190A0;
  if ( qword_1801190A0 != -1
    && (qword_1801190A0
     || (v2 = (__int64 (__fastcall *)(__int64, _QWORD))sub_1800A8508(
                                                         20,
                                                         "LocaleNameToLCID",
                                                         &unk_1800C2CE0,
                                                         "LocaleNameToLCID")) != nullptr) )
  {
    return v2(a1, a2);
  }
  else
  {
    return sub_1800AFD28(a1);
  }
}
