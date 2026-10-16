double sub_180028FB0(const char *a1, ...)
{
  int v1; // ebx
  _QWORD *v2; // rax
  int v4; // [rsp+50h] [rbp+8h]
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, a1);
  v4 = (int)a1;
  v1 = sub_18009C524(1);
  v2 = (_QWORD *)sub_180002960();
  return sub_18009BF78(*v2, v1, v4, 0, (__int64)va);
}
