// sub_18008DE30 size=33
_QWORD *__fastcall sub_18008DE30(_QWORD *a1)
{
  a1[2] = 0;
  a1[1] = "bad allocation";
  *a1 = &std::bad_alloc::`vftable';
  return a1;
}
