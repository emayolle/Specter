// sub_180097AA0 size=33
_QWORD *__fastcall sub_180097AA0(_QWORD *a1)
{
  a1[2] = 0;
  a1[1] = "bad exception";
  *a1 = &std::bad_exception::`vftable';
  return a1;
}
