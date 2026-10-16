// sub_18004FA90 size=1084
void sub_18004FA90()
{
  __int64 v0; // rbx
  __int64 v1; // rdi
  int v2; // ecx
  __int64 v3; // r8
  unsigned __int64 *v4; // r14
  __int64 *v5; // r15
  int v6; // eax
  float v7; // xmm0_4
  float v8; // xmm1_4
  __int64 v9; // rdx
  __int64 v10; // r9
  __m128 v11; // xmm3
  int v12; // xmm0_4
  _DWORD *v13; // rax
  __int64 v14; // r9
  int v15; // edx
  int v16; // ecx
  __int64 v17; // rdx
  __int64 v18; // r8
  __int64 v19; // rcx
  __int64 v20; // rax
  __int64 v21; // rdx
  int v22; // ecx
  int v23; // eax
  __int64 v24; // rax
  _QWORD v25[2]; // [rsp+20h] [rbp-28h] BYREF
  __int64 v26; // [rsp+50h] [rbp+8h] BYREF
  unsigned __int64 v27; // [rsp+58h] [rbp+10h] BYREF

  v0 = qword_18010C470;
  if ( *(_DWORD *)(qword_18010C470 + 8344) )
  {
    v1 = qword_18010C470 + 8336;
  }
  else if ( *(_DWORD *)(qword_18010C470 + 8456) )
  {
    v1 = qword_18010C470 + 8448;
  }
  else
  {
    v1 = 0;
  }
  v2 = *(_DWORD *)(qword_18010C470 + 8268);
  if ( (v2 & 0x400) != 0
    && !v1
    && (*(_DWORD *)(qword_18010C470 + 8332) == 1 || !*(_DWORD *)(qword_18010C470 + 8328))
    && *(_DWORD *)(qword_18010C470 + 8512) )
  {
    v1 = qword_18010C470 + 8504;
  }
  if ( (unsigned int)(*(_DWORD *)(qword_18010C470 + 8280) - 2) <= 1 )
  {
    v3 = 4;
    v4 = (unsigned __int64 *)((char *)&v27 + 4);
    v5 = (__int64 *)((char *)&v26 + 4);
  }
  else
  {
    v3 = 0;
    v4 = &v27;
    v5 = &v26;
  }
  if ( v1 )
  {
    if ( (v2 & 0x20) != 0 )
    {
      v6 = *(_DWORD *)(qword_18010C470 + 8400);
      if ( v6 )
      {
        if ( v6 != *(_DWORD *)(qword_18010C470 + 8116) )
          v1 = qword_18010C470 + 8392;
      }
    }
    if ( v1 != qword_18010C470 + 8448 )
    {
      if ( *(_DWORD *)(qword_18010C470 + 8456) )
      {
        if ( *(_QWORD *)(*(_QWORD *)(qword_18010C470 + 8448) + 944LL) == *(_QWORD *)(qword_18010C470 + 8120) )
        {
          v7 = *(float *)(v1 + 36);
          v8 = *(float *)(qword_18010C470 + 8484);
          if ( v7 > v8 || v8 == v7 && *(float *)(v1 + 40) > *(float *)(qword_18010C470 + 8488) )
            v1 = qword_18010C470 + 8448;
        }
      }
    }
    if ( !*(_DWORD *)(qword_18010C470 + 8132) )
    {
      v9 = *(_QWORD *)v1;
      v10 = *(unsigned int *)(qword_18010C470 + 8272);
      v11 = (__m128)*(unsigned __int64 *)(*(_QWORD *)v1 + 296LL);
      v25[0] = _mm_add_ps((__m128)*(unsigned __int64 *)(v1 + 16), v11).m128_u64[0];
      v25[1] = _mm_add_ps((__m128)*(unsigned __int64 *)(v1 + 24), v11).m128_u64[0];
      ((void (__fastcall *)(__int64 *, __int64, _QWORD *, __int64))sub_18004B660)(&v26, v9, v25, v10);
      if ( (*(_BYTE *)(v0 + 8268) & 0x40) != 0 )
      {
        if ( *(_DWORD *)(v0 + 8280) == 2 )
          v12 = *(_DWORD *)(*(_QWORD *)v1 + 164LL);
        else
          v12 = 0;
        v13 = *(_DWORD **)v1;
        v13[43] = v12;
        v13[45] = 0;
        v13[47] = 0;
      }
    }
    v14 = *(_QWORD *)(v0 + 8120);
    if ( v14 != *(_QWORD *)v1 )
    {
      if ( (*(_BYTE *)(v0 + 10228) & 4) != 0 )
        sub_180052F00("[focus] NavMoveRequest: SetNavWindow(\"%s\")\n", *(const char **)(*(_QWORD *)v1 + 8LL));
      v14 = *(_QWORD *)v1;
      *(_QWORD *)(v0 + 8120) = *(_QWORD *)v1;
      *(_QWORD *)(v0 + 0x2000) = -1;
    }
    if ( *(_DWORD *)(v0 + 5332) != *(_DWORD *)(v1 + 8) && (*(_DWORD *)(v0 + 8268) & 0x8000) == 0 )
    {
      sub_180039FD0(0, 0);
      v14 = *(_QWORD *)(v0 + 8120);
    }
    v15 = *(_DWORD *)(v1 + 8);
    v16 = *(_DWORD *)(v0 + 8268);
    if ( (*(_DWORD *)(v0 + 8116) != v15 || (v16 & 0x800) != 0) && (v16 & 0x2000) == 0 )
    {
      *(_DWORD *)(v0 + 8560) = *(_DWORD *)(v0 + 8128);
      *(_DWORD *)(v0 + 8564) = *(_DWORD *)(v1 + 8);
      *(_DWORD *)(v0 + 8568) = *(_DWORD *)(v1 + 12);
      *(_DWORD *)(v0 + 8572) = *(_DWORD *)(v0 + 8276);
      *(_BYTE *)(v0 + 8576) = (v16 & 0x400) != 0;
      *(_BYTE *)(v0 + 8577) = (*(_DWORD *)(v1 + 32) & 0x200000) != 0;
      v15 = *(_DWORD *)(v1 + 8);
    }
    if ( (*(_BYTE *)(v0 + 10228) & 0x10) != 0 )
      sub_180052F00(
        "[nav] NavMoveRequest: result NavID 0x%08X in Layer %d Window \"%s\"\n",
        v15,
        *(_DWORD *)(v0 + 8132),
        *(const char **)(v14 + 8));
    v17 = *(int *)(v0 + 8132);
    v18 = *(unsigned int *)(v1 + 12);
    v19 = *(unsigned int *)(v1 + 8);
    v26 = *(_QWORD *)(*(_QWORD *)(*(_QWORD *)(v0 + 8120) + 984LL) + 8 * v17 + 1048);
    sub_18004DA70(v19, v17, v18, v1 + 16);
    v20 = *(_QWORD *)(v1 + 48);
    if ( v20 != -1 )
      *(_QWORD *)(v0 + 0x2000) = v20;
    if ( (*(_DWORD *)(v0 + 8268) & 0x400) == 0 )
    {
      v21 = *(int *)(v0 + 8132);
      v27 = _mm_mul_ps(
              _mm_add_ps((__m128)*(unsigned __int64 *)(v1 + 24), (__m128)*(unsigned __int64 *)(v1 + 16)),
              (__m128)xmmword_1800E6960).m128_u64[0];
      *(_DWORD *)v5 = *(_DWORD *)v4;
      *(_QWORD *)(*(_QWORD *)(*(_QWORD *)(v0 + 8120) + 984LL) + 8 * v21 + 1048) = v26;
    }
    v22 = *(_DWORD *)(v0 + 8268);
    if ( (v22 & 0x400) != 0 && (*(_DWORD *)(v1 + 32) & 0x100000) == 0 )
    {
      v22 &= ~0x1000u;
      *(_DWORD *)(v0 + 8268) = v22;
    }
    if ( (v22 & 0x1000) != 0 )
    {
      *(_DWORD *)(v0 + 8176) = *(_DWORD *)(v1 + 8);
      v23 = 0;
      *(_DWORD *)(v0 + 8180) = 0;
      if ( (v22 & 0x200) != 0 )
      {
        v23 = 32;
        *(_DWORD *)(v0 + 8180) = 32;
      }
      if ( (v22 & 0x400) != 0 )
        *(_DWORD *)(v0 + 8180) = v23 | 0xD;
    }
    if ( (v22 & 0x4000) == 0 )
    {
      v24 = qword_18010C470;
      if ( *(_BYTE *)(qword_18010C470 + 86) )
        *(_BYTE *)(qword_18010C470 + 8112) = 1;
      *(_WORD *)(v24 + 8113) = 257;
    }
  }
  else
  {
    if ( (*(_DWORD *)(qword_18010C470 + 8268) & 0x400) != 0 )
      *(_DWORD *)(qword_18010C470 + 8268) = v2 | 0x4000;
    if ( *(_DWORD *)(v0 + 8116) && (*(_DWORD *)(v0 + 8268) & 0x4000) == 0 )
    {
      if ( *(_BYTE *)(v0 + 86) )
        *(_BYTE *)(v0 + 8112) = 1;
      *(_WORD *)(v0 + 8113) = 257;
    }
    *(_DWORD *)(v3 + 8LL * *(int *)(v0 + 8132) + *(_QWORD *)(*(_QWORD *)(v0 + 8120) + 984LL) + 1048) = 2139095039;
    if ( (*(_BYTE *)(v0 + 10228) & 0x10) != 0 )
      sub_180052F00("[nav] NavMoveSubmitted but not led to a result!\n");
  }
}
