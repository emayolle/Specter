// sub_1800371B0 size=604
__int64 __fastcall sub_1800371B0(int a1)
{
  __int64 v1; // rbx
  int v2; // r9d
  __int64 result; // rax
  __int64 v4; // rdx
  __int64 v5; // rcx
  __int64 v6; // rax
  __int64 v7; // r8
  int v8; // eax
  __int64 v9; // rcx
  __int64 v10; // rcx
  __int64 v11; // rdx
  __int64 v12; // rax
  __int64 v13; // r8
  int v14; // eax
  __int64 v15; // rcx
  __int64 v16; // rcx
  __int64 v17; // rdx
  __int64 v18; // rax
  __int64 v19; // r8
  int v20; // eax
  __int64 v21; // rcx
  __int64 v22; // rcx
  __int64 v23; // rdx
  __int64 v24; // rax
  __int64 v25; // r8
  int v26; // eax
  __int64 v27; // rdx
  __int64 v28; // rcx
  __int64 v29; // rax
  __int64 v30; // r8
  int v31; // eax

  v1 = qword_18010C470;
  v2 = a1;
  if ( *(_DWORD *)(qword_18010C470 + 7968) < a1 )
  {
    sub_180049A30("Calling PopStyleVar() too many times!");
    v2 = *(_DWORD *)(v1 + 7968);
  }
  result = *(unsigned int *)(v1 + 7968);
  if ( v2 >= 4 )
  {
    do
    {
      v4 = *(_QWORD *)(v1 + 7976);
      v5 = 3LL * (int)result;
      v6 = *(int *)(v4 + 12LL * (int)result - 12);
      if ( *((_BYTE *)&unk_1800D5FA0 + 4 * v6 + 1) == 8 )
      {
        v7 = *((unsigned __int16 *)&unk_1800D5FA0 + 2 * v6 + 1);
        v8 = (unsigned __int8)*((_DWORD *)&unk_1800D5FA0 + v6);
        if ( v8 == 1 )
        {
          *(_DWORD *)(v1 + v7 + 3136) = *(_DWORD *)(v4 + 4 * v5 - 8);
        }
        else if ( v8 == 2 )
        {
          *(_DWORD *)(v1 + v7 + 3136) = *(_DWORD *)(v4 + 4 * v5 - 8);
          *(_DWORD *)(v1 + v7 + 3140) = *(_DWORD *)(v4 + 4 * v5 - 4);
        }
      }
      v9 = *(int *)(v1 + 7968);
      *(_DWORD *)(v1 + 7968) = v9 - 1;
      v10 = 3 * v9;
      v11 = *(_QWORD *)(v1 + 7976);
      v12 = *(int *)(v11 + 4 * v10 - 24);
      if ( *((_BYTE *)&unk_1800D5FA0 + 4 * v12 + 1) == 8 )
      {
        v13 = *((unsigned __int16 *)&unk_1800D5FA0 + 2 * v12 + 1);
        v14 = (unsigned __int8)*((_DWORD *)&unk_1800D5FA0 + v12);
        if ( v14 == 1 )
        {
          *(_DWORD *)(v1 + v13 + 3136) = *(_DWORD *)(v11 + 4 * v10 - 20);
        }
        else if ( v14 == 2 )
        {
          *(_DWORD *)(v1 + v13 + 3136) = *(_DWORD *)(v11 + 4 * v10 - 20);
          *(_DWORD *)(v1 + v13 + 3140) = *(_DWORD *)(v11 + 4 * v10 - 16);
        }
      }
      v15 = *(int *)(v1 + 7968);
      *(_DWORD *)(v1 + 7968) = v15 - 1;
      v16 = 3 * v15;
      v17 = *(_QWORD *)(v1 + 7976);
      v18 = *(int *)(v17 + 4 * v16 - 24);
      if ( *((_BYTE *)&unk_1800D5FA0 + 4 * v18 + 1) == 8 )
      {
        v19 = *((unsigned __int16 *)&unk_1800D5FA0 + 2 * v18 + 1);
        v20 = (unsigned __int8)*((_DWORD *)&unk_1800D5FA0 + v18);
        if ( v20 == 1 )
        {
          *(_DWORD *)(v1 + v19 + 3136) = *(_DWORD *)(v17 + 4 * v16 - 20);
        }
        else if ( v20 == 2 )
        {
          *(_DWORD *)(v1 + v19 + 3136) = *(_DWORD *)(v17 + 4 * v16 - 20);
          *(_DWORD *)(v1 + v19 + 3140) = *(_DWORD *)(v17 + 4 * v16 - 16);
        }
      }
      v21 = *(int *)(v1 + 7968);
      *(_DWORD *)(v1 + 7968) = v21 - 1;
      v22 = 3 * v21;
      v23 = *(_QWORD *)(v1 + 7976);
      v24 = *(int *)(v23 + 4 * v22 - 24);
      if ( *((_BYTE *)&unk_1800D5FA0 + 4 * v24 + 1) == 8 )
      {
        v25 = *((unsigned __int16 *)&unk_1800D5FA0 + 2 * v24 + 1);
        v26 = (unsigned __int8)*((_DWORD *)&unk_1800D5FA0 + v24);
        if ( v26 == 1 )
        {
          *(_DWORD *)(v1 + v25 + 3136) = *(_DWORD *)(v23 + 4 * v22 - 20);
        }
        else if ( v26 == 2 )
        {
          *(_DWORD *)(v1 + v25 + 3136) = *(_DWORD *)(v23 + 4 * v22 - 20);
          *(_DWORD *)(v1 + v25 + 3140) = *(_DWORD *)(v23 + 4 * v22 - 16);
        }
      }
      v2 -= 4;
      result = (unsigned int)(*(_DWORD *)(v1 + 7968) - 1);
      *(_DWORD *)(v1 + 7968) = result;
    }
    while ( v2 > 3 );
  }
  for ( ; v2 > 0; *(_DWORD *)(v1 + 7968) = result )
  {
    v27 = *(_QWORD *)(v1 + 7976);
    v28 = 3LL * (int)result;
    v29 = *(int *)(v27 + 12LL * (int)result - 12);
    if ( *((_BYTE *)&unk_1800D5FA0 + 4 * v29 + 1) == 8 )
    {
      v30 = *((unsigned __int16 *)&unk_1800D5FA0 + 2 * v29 + 1);
      v31 = (unsigned __int8)*((_DWORD *)&unk_1800D5FA0 + v29);
      if ( v31 == 1 )
      {
        *(_DWORD *)(v1 + v30 + 3136) = *(_DWORD *)(v27 + 4 * v28 - 8);
      }
      else if ( v31 == 2 )
      {
        *(_DWORD *)(v1 + v30 + 3136) = *(_DWORD *)(v27 + 4 * v28 - 8);
        *(_DWORD *)(v1 + v30 + 3140) = *(_DWORD *)(v27 + 4 * v28 - 4);
      }
    }
    --v2;
    result = (unsigned int)(*(_DWORD *)(v1 + 7968) - 1);
  }
  return result;
}
