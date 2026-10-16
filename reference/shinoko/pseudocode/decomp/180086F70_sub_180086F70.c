// sub_180086F70 size=604
__int64 sub_180086F70()
{
  __int64 v0; // rbx
  __int64 result; // rax
  __int64 v2; // rdi
  __int64 v3; // rcx
  __int64 v4; // rax
  __int64 v5; // r8
  int v6; // r9d
  int v7; // r10d
  int v8; // edx
  int v9; // ecx
  bool v10; // zf
  __int64 v11; // rcx
  int v12; // eax
  __int64 v13; // rcx
  __int64 v14; // rax
  int v15; // xmm6_4
  int v16; // xmm7_4

  v0 = qword_18010C470;
  result = *(_QWORD *)(qword_18010C470 + 5216);
  *(_BYTE *)(result + 206) = 1;
  v2 = *(_QWORD *)(v0 + 5216);
  if ( !*(_BYTE *)(v2 + 209) )
  {
    if ( *(_BYTE *)(v0 + 8265) )
    {
      if ( !*(_DWORD *)(v0 + 8344) && !*(_DWORD *)(v0 + 8456) && *(_DWORD *)(v0 + 8280) <= 1u )
      {
        v3 = *(_QWORD *)(v0 + 8120);
        if ( (*(_DWORD *)(v3 + 20) & 0x10000000) != 0 )
        {
          if ( *(_QWORD *)(v3 + 944) )
          {
            do
            {
              v4 = *(_QWORD *)(v3 + 944);
              if ( (*(_DWORD *)(v4 + 20) & 0x10000000) == 0 )
                break;
              v3 = *(_QWORD *)(v3 + 944);
              v4 = *(_QWORD *)(v4 + 944);
            }
            while ( v4 );
          }
          else
          {
            v4 = 0;
          }
          if ( v4 == v2 && !*(_DWORD *)(v3 + 472) && *(char *)(v0 + 8268) >= 0 )
          {
            sub_18004D450(v2, 0);
            sub_18004DA70(*(unsigned int *)(v2 + 1012), 1, 0, v2 + 1032);
            if ( *(_BYTE *)(v0 + 8112) )
            {
              *(_BYTE *)(v0 + 8112) = 0;
              *(_BYTE *)(v0 + 8200) = 2;
            }
            v5 = qword_18010C470;
            v6 = *(_DWORD *)(v0 + 8268);
            v7 = *(_DWORD *)(v0 + 8272);
            v8 = *(_DWORD *)(v0 + 8288);
            v9 = *(_DWORD *)(v0 + 8280);
            *(_WORD *)(v0 + 8113) = 257;
            v10 = *(_BYTE *)(v5 + 8202) == 0;
            *(_WORD *)(v5 + 8264) = 0;
            *(_BYTE *)(v5 + 8266) = 1;
            *(_BYTE *)(v5 + 8201) = !v10;
            *(_DWORD *)(v5 + 8268) = v6 | 0x80;
            *(_DWORD *)(v5 + 8280) = v9;
            *(_DWORD *)(v5 + 8288) = v8;
            *(_DWORD *)(v5 + 8272) = v7;
          }
        }
      }
    }
    sub_18003CD50();
    v11 = *(_QWORD *)(qword_18010C470 + 5216);
    v12 = *(_DWORD *)(v11 + 264);
    if ( v12 > 1 )
      *(_DWORD *)(v11 + 264) = v12 - 1;
    else
      sub_180049A30("Calling PopID() too many times!");
    *(float *)(v2 + 380) = *(float *)(v2 + 280) - *(float *)(v2 + 40);
    v13 = 56LL * *(int *)(v0 + 8032);
    v14 = *(_QWORD *)(v0 + 8040);
    v15 = *(_DWORD *)(v13 + v14 - 44);
    v16 = *(_DWORD *)(v13 + v14 - 40);
    *(_BYTE *)(v13 + v14 - 1) = 0;
    *(float *)(v2 + 312) = fmaxf(*(float *)(v2 + 312), *(float *)(v2 + 304) - *(float *)(v2 + 152));
    result = sub_18004B190();
    *(_DWORD *)(v2 + 304) = v15;
    *(_DWORD *)(v2 + 308) = v16;
    *(_DWORD *)(v2 + 468) = 1;
    *(_BYTE *)(v2 + 344) = 0;
    *(_DWORD *)(v2 + 368) = 0;
    *(_BYTE *)(v2 + 379) = 0;
  }
  return result;
}
