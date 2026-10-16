// sub_1800A8798 size=242
int __fastcall sub_1800A8798(
        __int64 a1,
        DWORD a2,
        const WCHAR *a3,
        unsigned int a4,
        WCHAR *lpDestStr,
        int cchDest,
        __int64 a7,
        __int64 a8,
        __int64 a9)
{
  __int64 (__fastcall *v9)(__int64, _QWORD, const WCHAR *, _QWORD, WCHAR *, int, __int64, __int64, __int64); // r10
  LCID v15; // eax

  v9 = (__int64 (__fastcall *)(__int64, _QWORD, const WCHAR *, _QWORD, WCHAR *, int, __int64, __int64, __int64))qword_180119090;
  if ( qword_180119090 != -1 )
  {
    if ( qword_180119090 )
      return v9(a1, a2, a3, a4, lpDestStr, cchDest, a7, a8, a9);
    v9 = (__int64 (__fastcall *)(__int64, _QWORD, const WCHAR *, _QWORD, WCHAR *, int, __int64, __int64, __int64))sub_1800A8508(18, "LCMapStringEx", &unk_1800C2CC8, "LCMapStringEx");
    if ( v9 )
      return v9(a1, a2, a3, a4, lpDestStr, cchDest, a7, a8, a9);
  }
  v15 = sub_1800A888C(a1, 0);
  return LCMapStringW(v15, a2, a3, a4, lpDestStr, cchDest);
}
