// sub_180044DF0 size=1131
char sub_180044DF0()
{
  __int64 v0; // rbx
  __int64 v1; // rax
  __int64 v2; // rax
  __int64 v3; // rsi
  __int64 v4; // r14
  __int64 v5; // rbp
  __int64 v6; // rdx
  int v7; // r8d
  int v8; // r8d
  __int64 v9; // rdx
  int v10; // ecx
  __int64 v11; // rdi
  void *v12; // rdx
  void (__fastcall *v13)(__int64, void *); // rax
  void *v14; // rcx
  __int64 v15; // rcx
  bool v16; // cf
  __int64 v17; // rcx
  __int64 v18; // rdx
  __int64 v19; // rbx
  char v20; // di
  __int64 v21; // rax
  __int64 v22; // rax
  __int64 v23; // rcx

  v0 = qword_18010C470;
  v1 = *(int *)(qword_18010C470 + 5168);
  if ( (int)v1 <= 1 && *(_BYTE *)(qword_18010C470 + 5049) )
  {
    LOBYTE(v2) = sub_180049A30("Calling End() too many times!");
    return v2;
  }
  v3 = *(_QWORD *)(qword_18010C470 + 5216);
  v4 = *(_QWORD *)(qword_18010C470 + 5176);
  v5 = 120 * v1;
  if ( (*(_DWORD *)(v3 + 20) & 0x1000000) != 0 && *(_DWORD *)(qword_18010C470 + 5044) != *(_DWORD *)(v3 + 16) )
    sub_180049A30("Must call EndChild() and not End()!");
  if ( *(_QWORD *)(v3 + 456) )
    sub_18006E600();
  if ( !*(_BYTE *)(v3 + 210) )
    sub_18003CD50();
  v6 = qword_18010C470;
  v7 = *(_DWORD *)(qword_18010C470 + 8000);
  if ( v7 > *(__int16 *)(*(_QWORD *)(qword_18010C470 + 10216) + 12LL) )
  {
    *(_DWORD *)(qword_18010C470 + 8000) = v7 - 1;
    if ( v7 == 1 )
      v8 = 0;
    else
      v8 = *(_DWORD *)(*(_QWORD *)(v6 + 8008) + 8LL * (v7 - 2));
    *(_DWORD *)(v6 + 7676) = v8;
  }
  else
  {
    sub_180049A30("Calling PopFocusScope() too many times!");
  }
  if ( *(_BYTE *)(v4 + v5 - 10) && *(_QWORD *)(v3 + 960) == v3 )
  {
    v9 = qword_18010C470;
    --*(_WORD *)(qword_18010C470 + 9696);
    v10 = *(_DWORD *)(v9 + 8016);
    *(_DWORD *)(v9 + 8016) = v10 - 1;
    *(_DWORD *)(v9 + 7680) = *(_DWORD *)(*(_QWORD *)(v9 + 8024) + 4LL * (v10 - 2));
    *(_DWORD *)(v9 + 3148) = *(_DWORD *)(120 * (*(int *)(v9 + 5168) - 1LL) + *(_QWORD *)(v9 + 5176) + 112);
  }
  if ( *(_BYTE *)(v3 + 210) )
    *(_QWORD *)(v3 + 712) = v3 + 720;
  if ( *(_QWORD *)(v0 + 10088) == v3 )
  {
    v11 = qword_18010C470;
    if ( *(_BYTE *)(qword_18010C470 + 10080) )
    {
      sub_180051790("\r\n");
      if ( (*(_DWORD *)(v11 + 10084) & 0xF) == 1 )
      {
        sub_18009C934(*(_QWORD *)(v11 + 10096));
      }
      else if ( (*(_DWORD *)(v11 + 10084) & 0xF) == 2 )
      {
        sub_18009CAC0(*(_QWORD *)(v11 + 10096));
      }
      else if ( (*(_DWORD *)(v11 + 10084) & 0xF) == 8 && *(int *)(v11 + 10104) > 1 )
      {
        v12 = &unk_18010C451;
        if ( *(_QWORD *)(v11 + 10112) )
          v12 = *(void **)(v11 + 10112);
        v13 = *(void (__fastcall **)(__int64, void *))(qword_18010C470 + 3048);
        if ( v13 )
          v13(qword_18010C470, v12);
      }
      *(_BYTE *)(v11 + 5330) = 0;
      *(_BYTE *)(v11 + 10080) = 0;
      *(_DWORD *)(v11 + 10084) = 0;
      *(_QWORD *)(v11 + 10096) = 0;
      v14 = *(void **)(v11 + 10112);
      if ( v14 )
      {
        *(_QWORD *)(v11 + 10104) = 0;
        sub_18003A8D0(v14);
        *(_QWORD *)(v11 + 10112) = 0;
      }
    }
  }
  if ( *(_BYTE *)(v3 + 345) )
  {
    v15 = *(_QWORD *)(qword_18010C470 + 5216);
    v16 = *(float *)(v15 + 304) < *(float *)(v15 + 280);
    *(_BYTE *)(v15 + 345) = 0;
    if ( (v16 || *(float *)(v15 + 308) < *(float *)(v15 + 284)) && !*(_BYTE *)(v15 + 209) )
      sub_180049A30(
        "Code uses SetCursorPos()/SetCursorScreenPos() to extend window/parent boundaries.\n"
        "Please submit an item e.g. Dummy() afterwards in order to grow window/parent boundaries.");
  }
  *(_OWORD *)(v0 + 7744) = *(_OWORD *)(v4 + v5 - 112);
  *(_OWORD *)(v0 + 7760) = *(_OWORD *)(v4 + v5 - 96);
  *(_OWORD *)(v0 + 7776) = *(_OWORD *)(v4 + v5 - 80);
  *(_OWORD *)(v0 + 7792) = *(_OWORD *)(v4 + v5 - 64);
  *(_OWORD *)(v0 + 7808) = *(_OWORD *)(v4 + v5 - 48);
  if ( (*(_DWORD *)(v3 + 20) & 0x10000000) != 0 )
    --*(_DWORD *)(v0 + 9552);
  if ( (*(_DWORD *)(v3 + 20) & 0x4000000) != 0 )
    --*(_DWORD *)(v0 + 8064);
  if ( *(_BYTE *)(v0 + 124) )
    sub_1800493D0(v5 + v4 - 32);
  v17 = *(unsigned int *)(v0 + 5168);
  *(_DWORD *)(v0 + 5168) = v17 - 1;
  if ( (_DWORD)v17 == 1 )
  {
    v18 = qword_18010C470;
    v19 = 0;
    *(_QWORD *)(qword_18010C470 + 5216) = 0;
LABEL_49:
    LOBYTE(v2) = v18;
    *(_QWORD *)(v18 + 10216) = 0;
    goto LABEL_50;
  }
  v17 = (int)v17 - 2;
  v19 = *(_QWORD *)(120 * v17 + *(_QWORD *)(v0 + 5176));
  v18 = qword_18010C470;
  *(_QWORD *)(qword_18010C470 + 5216) = v19;
  if ( !v19 )
    goto LABEL_49;
  v17 = *(_QWORD *)(v18 + 5176) + 88LL + 120LL * (*(_DWORD *)(v18 + 5168) - 1);
  *(_QWORD *)(v18 + 10216) = v17;
  v2 = *(int *)(v19 + 464);
  if ( (_DWORD)v2 == -1 )
  {
LABEL_50:
    *(_QWORD *)(v18 + 8856) = 0;
    *(_DWORD *)(v18 + 4448) = 1065353216;
    if ( !v19 )
      return v2;
    goto LABEL_51;
  }
  v17 = *(_QWORD *)(v18 + 8896) + 592 * v2;
  *(_QWORD *)(v18 + 8856) = v17;
  *(_DWORD *)(v18 + 4448) = 1065353216;
LABEL_51:
  v20 = *(_BYTE *)(v19 + 209);
  *(_BYTE *)(v19 + 209) = 0;
  if ( (*(_BYTE *)(v18 + 12) & 0x10) != 0 )
  {
    v21 = *(_QWORD *)(v19 + 32);
    if ( *(float *)(v21 + 24) == 0.0 )
      v21 = v18;
    *(_DWORD *)(v18 + 4444) = *(_DWORD *)(v21 + 24);
  }
  sub_1800462C0(v17, v18);
  v22 = qword_18010C470;
  *(_BYTE *)(v19 + 209) = v20;
  v23 = *(_QWORD *)(v22 + 5216);
  LOBYTE(v2) = !*(_QWORD *)(v22 + 8856) && !*(_QWORD *)(v23 + 456);
  *(_BYTE *)(v23 + 376) = v2;
  return v2;
}
