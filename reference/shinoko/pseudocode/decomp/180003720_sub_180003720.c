// sub_180003720 size=367
void __fastcall sub_180003720(__int64 a1)
{
  __int64 v2; // rbx
  float v3; // xmm6_4
  int v4; // ecx
  int v5; // edi
  int v6; // edi
  int v7; // eax
  __int64 v8; // rax
  __int64 v9; // rdx
  __int64 v10; // rbp
  __int64 v11; // rdx
  __int64 v12; // r8
  int v13; // ecx

  if ( a1 && (unsigned __int8)sub_18003A270(0) )
  {
    sub_18004BB50(0);
    v2 = *(_QWORD *)(qword_18010C470 + 5216);
    v3 = *(float *)(qword_18010C470 + 4432) * 35.0;
    v4 = *(_DWORD *)(v2 + 516);
    v5 = *(_DWORD *)(v2 + 512);
    if ( v5 == v4 )
    {
      v6 = v5 + 1;
      if ( v4 )
        v7 = v4 + v4 / 2;
      else
        v7 = 8;
      if ( v7 > v6 )
        v6 = v7;
      if ( v6 > v4 )
      {
        v8 = sub_18003A810(4LL * v6);
        v9 = *(_QWORD *)(v2 + 520);
        v10 = v8;
        if ( v9 )
        {
          sub_1800B8BD0(v8, v9, 4LL * *(int *)(v2 + 512));
          sub_18003A8D0(*(LPVOID *)(v2 + 520));
        }
        *(_QWORD *)(v2 + 520) = v10;
        *(_DWORD *)(v2 + 516) = v6;
      }
    }
    *(_DWORD *)(*(_QWORD *)(v2 + 520) + 4LL * (int)(*(_DWORD *)(v2 + 512))++) = *(_DWORD *)(v2 + 492);
    *(float *)(v2 + 492) = v3;
    sub_18006EB90(a1, 0, 1);
    v11 = *(_QWORD *)(qword_18010C470 + 5216);
    v12 = *(int *)(v11 + 512);
    if ( (int)v12 > 0 )
    {
      v13 = *(_DWORD *)(*(_QWORD *)(v11 + 520) + 4 * v12 - 4);
      *(_DWORD *)(v11 + 512) = v12 - 1;
      *(_DWORD *)(v11 + 492) = v13;
      sub_180044DF0();
    }
    else
    {
      sub_180049A30("Calling PopTextWrapPos() too many times!");
      sub_180044DF0();
    }
  }
}
