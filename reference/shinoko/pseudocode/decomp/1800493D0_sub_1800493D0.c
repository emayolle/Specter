// sub_1800493D0 size=1623
__int64 __fastcall sub_1800493D0(__int16 *a1)
{
  __int64 v1; // rbx
  __int64 i; // rcx
  _QWORD *v4; // rax
  __int64 j; // r15
  __int64 v6; // rdx
  __int64 v7; // rbp
  __int64 v8; // r14
  __int64 v9; // rdi
  float v10; // xmm1_4
  float v11; // xmm1_4
  float v12; // xmm0_4
  bool v13; // zf
  __int64 v14; // rcx
  int v15; // eax
  int v16; // ecx
  __int64 v17; // rax
  __int64 v18; // r8
  __int64 v19; // rcx
  __int64 k; // rax
  __int64 v21; // rcx
  int v22; // eax
  __int64 v23; // rdx
  __int16 v24; // ax
  int v25; // ecx
  int v26; // r8d
  int v27; // ecx
  __int64 v28; // rdi
  int v29; // eax
  int v30; // r8d
  __int64 v31; // rdx
  int v32; // ecx
  __int64 v33; // rdi
  __int64 v34; // rax
  __int64 result; // rax
  __int64 v36; // rdx
  int v37; // r8d
  int v38; // r8d

  v1 = qword_18010C470;
  for ( i = *(_QWORD *)(qword_18010C470 + 8856); i; i = *(_QWORD *)(v1 + 8856) )
  {
    if ( *(_QWORD *)(i + 392) != *(_QWORD *)(v1 + 5216) )
      break;
    sub_180049A30("Missing EndTable()");
    sub_18006B130();
  }
  v4 = *(_QWORD **)(v1 + 8960);
  for ( j = *(_QWORD *)(v1 + 5216); v4; v4 = *(_QWORD **)(v1 + 8960) )
  {
    if ( *v4 != j )
      break;
    sub_180049A30("Missing EndTabBar()");
    v6 = qword_18010C470;
    v7 = qword_18010C470;
    v8 = *(_QWORD *)(qword_18010C470 + 5216);
    if ( !*(_BYTE *)(v8 + 209) )
    {
      v9 = *(_QWORD *)(qword_18010C470 + 8960);
      if ( v9 )
      {
        if ( *(_BYTE *)(v9 + 127) )
        {
          sub_180087890(*(_QWORD *)(qword_18010C470 + 8960));
          v6 = qword_18010C470;
        }
        if ( *(_BYTE *)(v9 + 128) || !*(_DWORD *)(v9 + 40) || *(_DWORD *)(v9 + 48) + 1 < *(_DWORD *)(v7 + 5032) )
        {
          v11 = *(float *)(v9 + 64);
          v12 = fmaxf(*(float *)(v8 + 284) - v11, *(float *)(v9 + 72));
          *(float *)(v9 + 72) = v12;
          v10 = v11 + v12;
        }
        else
        {
          v10 = *(float *)(v9 + 76) + *(float *)(v9 + 64);
        }
        *(float *)(v8 + 284) = v10;
        if ( *(char *)(v9 + 126) > 1 )
          *(_QWORD *)(v8 + 280) = *(_QWORD *)(v9 + 148);
        v13 = (*(_DWORD *)(v9 + 24) & 0x100000) == 0;
        *(_WORD *)(v9 + 134) = -1;
        if ( v13 )
        {
          v14 = *(_QWORD *)(v6 + 5216);
          v15 = *(_DWORD *)(v14 + 264);
          if ( v15 > 1 )
          {
            *(_DWORD *)(v14 + 264) = v15 - 1;
          }
          else
          {
            sub_180049A30("Calling PopID() too many times!");
            v6 = qword_18010C470;
          }
        }
        v16 = *(_DWORD *)(v7 + 9008);
        *(_DWORD *)(v7 + 9008) = v16 - 1;
        if ( v16 == 1 )
        {
          v17 = 0;
        }
        else
        {
          v18 = *(_QWORD *)(v7 + 9016);
          v19 = 2LL * (v16 - 2);
          v17 = *(_QWORD *)(v18 + 8 * v19);
          if ( !v17 )
            v17 = *(_QWORD *)(v6 + 8976) + 176LL * *(int *)(v18 + 8 * v19 + 8);
        }
        *(_QWORD *)(v7 + 8960) = v17;
      }
      else
      {
        sub_180049A30("Mismatched BeginTabBar()/EndTabBar()!");
      }
    }
  }
  for ( k = *(_QWORD *)(v1 + 9144); k; k = *(_QWORD *)(v1 + 9144) )
  {
    if ( **(_QWORD **)(k + 40) != j )
      break;
    sub_180049A30("Missing EndMultiSelect()");
    sub_180085C00();
  }
  if ( *(_BYTE *)(j + 379) )
  {
    sub_180049A30("Missing EndMenuBar()");
    sub_180086F70();
  }
  while ( *(_DWORD *)(j + 416) > a1[2] )
  {
    sub_180049A30("Missing TreePop()");
    sub_1800847B0();
  }
  while ( *(_DWORD *)(v1 + 8032) > a1[7] )
  {
    sub_180049A30("Missing EndGroup()");
    sub_18004B190();
  }
  while ( *(_DWORD *)(j + 264) > a1[1] )
  {
    sub_180049A30("Missing PopID()");
    v21 = *(_QWORD *)(qword_18010C470 + 5216);
    v22 = *(_DWORD *)(v21 + 264);
    if ( v22 > 1 )
      *(_DWORD *)(v21 + 264) = v22 - 1;
    else
      sub_180049A30("Calling PopID() too many times!");
  }
  while ( *(__int16 *)(v1 + 9696) > a1[10] )
  {
    sub_180049A30("Missing EndDisabled()");
    v23 = qword_18010C470;
    if ( (*(_DWORD *)(v1 + 7680) & 0x400) != 0 )
    {
      v24 = *(_WORD *)(qword_18010C470 + 9696);
      if ( v24 > 0 )
      {
        v13 = (*(_DWORD *)(qword_18010C470 + 7680) & 0x400) == 0;
        *(_WORD *)(qword_18010C470 + 9696) = v24 - 1;
        v25 = *(_DWORD *)(v23 + 8016);
        *(_DWORD *)(v23 + 8016) = v25 - 1;
        v26 = *(_DWORD *)(*(_QWORD *)(v23 + 8024) + 4LL * (v25 - 2));
        *(_DWORD *)(v23 + 7680) = v26;
        if ( !v13 && (v26 & 0x400) == 0 )
          *(_DWORD *)(v23 + 3148) = *(_DWORD *)(v23 + 9692);
      }
      else
      {
        sub_180049A30("Calling EndDisabled() too many times!");
      }
    }
    else
    {
      --*(_WORD *)(qword_18010C470 + 9696);
      v27 = *(_DWORD *)(v23 + 8016);
      *(_DWORD *)(v23 + 8016) = v27 - 1;
      *(_DWORD *)(v23 + 7680) = *(_DWORD *)(*(_QWORD *)(v23 + 8024) + 4LL * (v27 - 2));
      *(_DWORD *)(v23 + 3148) = *(_DWORD *)(120LL * *(int *)(v23 + 5168) + *(_QWORD *)(v23 + 5176) - 8);
      *(_BYTE *)(120LL * *(int *)(v1 + 5168) + *(_QWORD *)(v1 + 5176) - 10) = 0;
    }
  }
  if ( *(_DWORD *)(v1 + 7952) > a1[3] )
  {
    while ( 1 )
    {
      sub_180049A30("Missing PopStyleColor()");
      v28 = qword_18010C470;
      v29 = *(_DWORD *)(qword_18010C470 + 7952);
      if ( v29 >= 1 )
        break;
      sub_180049A30("Calling PopStyleColor() too many times!");
      v30 = *(_DWORD *)(v28 + 7952);
      v29 = v30;
      if ( v30 > 0 )
        goto LABEL_56;
LABEL_57:
      if ( *(_DWORD *)(v1 + 7952) <= a1[3] )
        goto LABEL_58;
    }
    v30 = 1;
    do
    {
LABEL_56:
      --v30;
      *(_OWORD *)(v28 + 16LL * *(int *)(*(_QWORD *)(v28 + 7960) + 20LL * v29 - 20) + 3424) = *(_OWORD *)(*(_QWORD *)(v28 + 7960) + 20LL * v29 - 16);
      v29 = *(_DWORD *)(v28 + 7952) - 1;
      *(_DWORD *)(v28 + 7952) = v29;
    }
    while ( v30 > 0 );
    goto LABEL_57;
  }
LABEL_58:
  while ( *(_DWORD *)(v1 + 8016) > a1[8] )
  {
    sub_180049A30("Missing PopItemFlag()");
    v31 = qword_18010C470;
    v32 = *(_DWORD *)(qword_18010C470 + 8016);
    if ( v32 > 1 )
    {
      *(_DWORD *)(qword_18010C470 + 8016) = v32 - 1;
      *(_DWORD *)(v31 + 7680) = *(_DWORD *)(*(_QWORD *)(v31 + 8024) + 4LL * (v32 - 2));
    }
    else
    {
      sub_180049A30("Calling PopItemFlag() too many times!");
    }
  }
  while ( *(_DWORD *)(v1 + 7968) > a1[4] )
  {
    sub_180049A30("Missing PopStyleVar()");
    sub_1800371B0(1);
  }
  while ( *(_DWORD *)(v1 + 7984) > a1[5] )
  {
    sub_180049A30("Missing PopFont()");
    v33 = qword_18010C470;
    v34 = *(int *)(qword_18010C470 + 7984);
    if ( (int)v34 > 0 )
    {
      sub_180046120(*(_QWORD *)(*(_QWORD *)(qword_18010C470 + 7992) + 16 * v34 - 16));
      --*(_DWORD *)(v33 + 7984);
    }
    else
    {
      sub_180049A30("Calling PopFont() too many times!");
    }
  }
  for ( result = (unsigned int)a1[6]; *(_DWORD *)(v1 + 8000) > (int)result; result = (unsigned int)a1[6] )
  {
    sub_180049A30("Missing PopFocusScope()");
    v36 = qword_18010C470;
    v37 = *(_DWORD *)(qword_18010C470 + 8000);
    if ( v37 > *(__int16 *)(*(_QWORD *)(qword_18010C470 + 10216) + 12LL) )
    {
      *(_DWORD *)(qword_18010C470 + 8000) = v37 - 1;
      if ( v37 == 1 )
        v38 = 0;
      else
        v38 = *(_DWORD *)(*(_QWORD *)(v36 + 8008) + 8LL * (v37 - 2));
      *(_DWORD *)(v36 + 7676) = v38;
    }
    else
    {
      sub_180049A30("Calling PopFocusScope() too many times!");
    }
  }
  return result;
}
