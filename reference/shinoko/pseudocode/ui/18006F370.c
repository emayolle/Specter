__int64 sub_18006F370(__int64 a1, ...)
{
  __int64 v2; // rcx
  __int64 result; // rax
  __int64 v4; // [rsp+20h] [rbp-18h] BYREF
  __int64 v5; // [rsp+28h] [rbp-10h] BYREF
  va_list va; // [rsp+48h] [rbp+10h] BYREF

  va_start(va, a1);
  v2 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  result = *(_QWORD *)(v2 + 5216);
  if ( !*(_BYTE *)(result + 209) )
  {
    sub_180035F70(&v5, &v4, a1, (__int64 *)va);
    return sub_18006EB90(v5, v4, 1);
  }
  return result;
}
