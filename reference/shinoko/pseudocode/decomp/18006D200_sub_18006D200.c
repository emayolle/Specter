// sub_18006D200 size=267
__int64 __fastcall sub_18006D200(__int64 a1)
{
  __int64 v2; // rdi
  __int64 v3; // rsi
  __int64 v4; // rcx
  bool v5; // cf
  __int64 v6; // rax
  __int64 result; // rax

  v2 = *(_QWORD *)(a1 + 392);
  v3 = *(_QWORD *)(a1 + 24) + 116LL * *(int *)(a1 + 116);
  if ( *(_BYTE *)(v2 + 345) )
  {
    v4 = *(_QWORD *)(qword_18010C470 + 5216);
    v5 = *(float *)(v4 + 304) < *(float *)(v4 + 280);
    *(_BYTE *)(v4 + 345) = 0;
    if ( (v5 || *(float *)(v4 + 308) < *(float *)(v4 + 284)) && !*(_BYTE *)(v4 + 209) )
      sub_180049A30(
        "Code uses SetCursorPos()/SetCursorScreenPos() to extend window/parent boundaries.\n"
        "Please submit an item e.g. Dummy() afterwards in order to grow window/parent boundaries.");
  }
  if ( (*(_BYTE *)(a1 + 148) & 1) != 0 )
  {
    v6 = 76;
  }
  else
  {
    v6 = 72;
    if ( !*(_BYTE *)(a1 + 579) )
      v6 = 68;
  }
  *(float *)(v6 + v3) = fmaxf(*(float *)(v6 + v3), *(float *)(v2 + 304));
  if ( *(_BYTE *)(v3 + 102) )
    *(float *)(a1 + 128) = fmaxf(*(float *)(a1 + 128), *(float *)(v2 + 308) + *(float *)(a1 + 136));
  result = *(unsigned int *)(v2 + 488);
  *(_DWORD *)(v3 + 64) = result;
  *(float *)(a1 + 140) = fmaxf(*(float *)(a1 + 140), *(float *)(v2 + 340));
  return result;
}
