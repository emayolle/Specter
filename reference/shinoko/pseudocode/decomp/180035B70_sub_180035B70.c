// sub_180035B70 size=437
void __fastcall sub_180035B70(__int64 a1, int a2, char a3)
{
  __int64 i; // r11
  char v7; // bl
  __int64 v8; // r8
  unsigned int v9; // edx
  __int64 v10; // r9
  __int64 v11; // rcx
  char v12; // al
  __int64 v13; // rcx
  __int64 v14; // rax
  __int64 v15; // rdx
  _DWORD v16[2]; // [rsp+20h] [rbp-28h] BYREF
  int v17; // [rsp+28h] [rbp-20h]
  int v18; // [rsp+2Ch] [rbp-1Ch]
  char v19; // [rsp+30h] [rbp-18h]
  __int16 v20; // [rsp+31h] [rbp-17h]
  char v21; // [rsp+33h] [rbp-15h]
  int v22; // [rsp+34h] [rbp-14h]
  int v23; // [rsp+38h] [rbp-10h]

  for ( i = *(_QWORD *)(a1 + 208); *(_BYTE *)(a1 + 2981); i = *(_QWORD *)(a1 + 208) )
  {
    v7 = *(_BYTE *)(a1 + 81);
    if ( v7 )
    {
      if ( !a2 )
      {
        if ( *(_BYTE *)(a1 + 2915) )
        {
          a2 = 1;
          if ( !a3 )
            *(_BYTE *)(a1 + 2915) = 0;
        }
      }
    }
    v8 = (unsigned int)(*(_DWORD *)(i + 5080) - 1);
    v9 = v8;
    if ( (int)v8 < 0 )
    {
LABEL_12:
      v12 = *(_BYTE *)(i + a2 + 232);
    }
    else
    {
      v10 = *(_QWORD *)(i + 5088);
      while ( 1 )
      {
        v11 = 28LL * v9;
        if ( *(_DWORD *)(v11 + v10) == 3 && *(_DWORD *)(v11 + v10 + 12) == a2 )
          break;
        if ( (--v9 & 0x80000000) != 0 )
          goto LABEL_12;
      }
      v12 = *(_BYTE *)(v11 + v10 + 16);
    }
    if ( v12 == a3 )
      break;
    if ( !v7 || a2 || !a3 )
      goto LABEL_30;
    if ( (int)v8 < 0 )
    {
LABEL_22:
      v15 = *(unsigned __int8 *)(i + 255);
    }
    else
    {
      v13 = *(_QWORD *)(i + 5088);
      while ( 1 )
      {
        v14 = 28LL * (unsigned int)v8;
        if ( *(_DWORD *)(v14 + v13) == 4 && *(_DWORD *)(v14 + v13 + 12) == 0x8000 )
          break;
        v8 = (unsigned int)(v8 - 1);
        if ( (int)v8 < 0 )
          goto LABEL_22;
      }
      v15 = *(unsigned __int8 *)(v14 + v13 + 16);
    }
    if ( !(_BYTE)v15 )
    {
LABEL_30:
      v16[0] = 3;
      v20 = 0;
      v21 = 0;
      v23 = 0;
      v17 = *(_DWORD *)(i + 5116);
      *(_DWORD *)(i + 5116) = v17 + 1;
      v22 = *(_DWORD *)(i + 5112);
      v16[1] = 1;
      v18 = a2;
      v19 = a3;
      sub_1800540F0(i + 5080, v16);
      return;
    }
    if ( *(char *)(i + 10228) < 0 )
      sub_180052F00("[io] Super+Left Click aliased into Right Click\n", v15, v8);
    *(_BYTE *)(a1 + 2915) = 1;
    a3 = 1;
    a2 = 1;
  }
}
