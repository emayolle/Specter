// sub_180035F70 size=382
char *__fastcall sub_180035F70(_QWORD *a1, char **a2, _BYTE *a3, char **a4)
{
  int v5; // edi
  char v8; // al
  char *result; // rax
  const char *v10; // rbx
  char *v11; // rbx
  int v12; // ecx
  int v13; // eax
  __int64 v14; // rbp
  int v15; // r13d
  __int64 v16; // r12
  _DWORD *v17; // rax
  int v18; // ecx

  v5 = (int)a3;
  if ( *a3 != 37 )
    goto LABEL_17;
  v8 = a3[1];
  if ( v8 == 115 )
  {
    if ( !a3[2] )
    {
      result = *a4;
      v10 = "(null)";
      if ( *a4 )
        v10 = *a4;
      *a1 = v10;
      if ( a2 )
      {
        result = (char *)sub_1800B9730(v10);
        *a2 = (char *)&v10[(_QWORD)result];
      }
      return result;
    }
    goto LABEL_17;
  }
  if ( v8 != 46 || a3[2] != 42 || a3[3] != 115 || a3[4] )
  {
LABEL_17:
    v14 = qword_18010C470;
    v15 = *(_DWORD *)(qword_18010C470 + 10752);
    v16 = *(_QWORD *)(qword_18010C470 + 10760);
    v17 = (_DWORD *)sub_180002960();
    v18 = sub_18009C09C(*v17 | 1u, v16, v15, v5, 0, (__int64)a4);
    if ( v18 < 0 )
      v18 = -1;
    if ( v16 )
    {
      if ( v18 == -1 || v18 >= v15 )
        v18 = v15 - 1;
      *(_BYTE *)(v18 + v16) = 0;
    }
    result = *(char **)(v14 + 10760);
    *a1 = result;
    if ( a2 )
    {
      result = (char *)(*(_QWORD *)(v14 + 10760) + v18);
      *a2 = result;
    }
    return result;
  }
  v11 = a4[1];
  v12 = *(_DWORD *)a4;
  if ( v11 )
  {
    *a1 = v11;
    result = &v11[v12];
    *a2 = result;
  }
  else
  {
    v13 = 6;
    *a1 = "(null)";
    if ( v12 < 6 )
      v13 = v12;
    result = &aNull_0[v13];
    *a2 = result;
  }
  return result;
}
