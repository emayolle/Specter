// sub_18004FED0 size=549
void sub_18004FED0()
{
  __int64 v0; // rbx
  int v1; // eax
  bool v2; // di
  __int64 v3; // rdx
  __int64 v4; // rcx
  __int64 v5; // rax
  __int64 v6; // rdx
  __int64 v7; // rdi
  __int64 v8; // rsi
  __m128 v9; // xmm2
  __m128 v10; // xmm3
  __int64 v11; // rcx
  __m128 v12; // xmm1
  __int64 v13; // r8
  __int64 v14; // r9
  char v15; // al
  char v16; // cl
  _QWORD v17[3]; // [rsp+20h] [rbp-18h] BYREF

  v0 = qword_18010C470;
  v1 = *(_DWORD *)(qword_18010C470 + 8);
  v2 = (v1 & 2) != 0 && (*(_BYTE *)(qword_18010C470 + 12) & 1) != 0;
  if ( (v1 & 1) != 0 && (unsigned __int8)sub_180046DB0(526, 0, 0xFFFFFFFFLL) )
    goto LABEL_11;
  if ( v2 )
  {
    v4 = 635;
    if ( *(_BYTE *)(v0 + 81) )
      v4 = 637;
    if ( (unsigned __int8)sub_180046DB0(v4, 0, 0xFFFFFFFFLL) )
    {
LABEL_11:
      if ( (*(_BYTE *)(v0 + 10228) & 0x10) != 0 )
        sub_180052F00("[nav] NavUpdateCancelRequest()\n");
      if ( *(_DWORD *)(v0 + 5332) )
      {
        sub_180039FD0(0, 0);
        return;
      }
      if ( *(_DWORD *)(v0 + 8132) )
      {
        sub_18004E250(0, v3);
        v5 = qword_18010C470;
        if ( *(_BYTE *)(qword_18010C470 + 86) )
          *(_BYTE *)(qword_18010C470 + 8112) = 1;
        *(_WORD *)(v5 + 8113) = 257;
      }
      else
      {
        v6 = *(_QWORD *)(v0 + 8120);
        if ( v6 )
        {
          if ( v6 != *(_QWORD *)(v6 + 960) )
          {
            v7 = *(_QWORD *)(v6 + 984);
            if ( (*(_DWORD *)(v7 + 20) & 0x4000000) == 0 )
            {
              v8 = *(_QWORD *)(v7 + 944);
              if ( v8 )
              {
                sub_18004D450(*(_QWORD *)(v7 + 944), 0);
                v9 = (__m128)*(unsigned __int64 *)(v8 + 296);
                v10 = (__m128)*(unsigned __int64 *)(v7 + 40);
                v11 = *(unsigned int *)(v7 + 144);
                v12 = _mm_add_ps((__m128)*(unsigned __int64 *)(v7 + 48), v10);
                v17[0] = _mm_sub_ps(v10, v9).m128_u64[0];
                v17[1] = _mm_sub_ps(v12, v9).m128_u64[0];
                sub_18004DA70(v11, 0, 0, v17);
                sub_18004D990();
                return;
              }
            }
          }
        }
        v13 = *(int *)(v0 + 8048);
        if ( (int)v13 > 0 )
        {
          v14 = *(_QWORD *)(56 * (v13 - 1) + *(_QWORD *)(v0 + 8056) + 8);
          if ( v14 )
          {
            if ( (*(_DWORD *)(v14 + 20) & 0x8000000) == 0 )
            {
              sub_18004C4C0(v13 - 1, 1u);
              return;
            }
          }
        }
        if ( *(_BYTE *)(v0 + 84) || (v15 = *(_BYTE *)(v0 + 85)) != 0 )
        {
          v15 = *(_BYTE *)(v0 + 85);
          if ( v6 && (*(_DWORD *)(v6 + 20) & 0x4000000) != 0 )
          {
            *(_DWORD *)(v6 + 1008) = 0;
            v16 = *(_BYTE *)(v0 + 85);
            v15 = v16;
          }
          else
          {
            v16 = *(_BYTE *)(v0 + 85);
          }
        }
        else
        {
          v16 = 0;
        }
        if ( *(_BYTE *)(v0 + 84) )
        {
          v15 = v16;
        }
        else if ( !v15 )
        {
          return;
        }
        *(_DWORD *)(v0 + 8116) = 0;
        if ( v15 )
          sub_18004D450(0, 0);
      }
    }
  }
}
