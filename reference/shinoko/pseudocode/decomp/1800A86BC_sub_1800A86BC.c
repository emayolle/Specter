// sub_1800A86BC size=92
__int64 __fastcall sub_1800A86BC(__int64 a1)
{
  __int64 (__fastcall *v1)(__int64, __int64); // rax

  v1 = (__int64 (__fastcall *)(__int64, __int64))qword_1801190D0;
  if ( qword_1801190D0 != -1
    && (qword_1801190D0
     || (v1 = (__int64 (__fastcall *)(__int64, __int64))sub_1800A8508(
                                                          26,
                                                          "AppPolicyGetProcessTerminationMethod",
                                                          &unk_1800C2CFC,
                                                          "AppPolicyGetProcessTerminationMethod")) != nullptr) )
  {
    return v1(-6, a1);
  }
  else
  {
    return 3221226021LL;
  }
}
