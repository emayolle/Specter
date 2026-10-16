// sub_180049A30 size=893
__int64 __fastcall sub_180049A30(const char *a1)
{
  __int64 v1; // rdi
  __int64 v3; // rsi
  char *v4; // r8
  __int64 v5; // rbp
  unsigned int v6; // ecx
  unsigned __int8 v7; // al
  unsigned __int64 v8; // rdx
  __int64 v9; // rax
  bool v10; // bl
  __m128 v11; // xmm1
  __int64 v12; // rax
  __int64 v13; // xmm0_8
  bool v14; // bl
  __int64 v15; // rax
  int v16; // xmm0_4
  bool v17; // zf
  unsigned int v18; // eax
  float v19; // xmm1_4
  void (__fastcall *v20)(__int64, _QWORD, const char *); // r9
  float v22; // [rsp+40h] [rbp-38h] BYREF
  unsigned __int64 v23; // [rsp+44h] [rbp-34h]
  float v24; // [rsp+4Ch] [rbp-2Ch]
  float v25; // [rsp+88h] [rbp+10h] BYREF
  float v26; // [rsp+8Ch] [rbp+14h]

  v1 = qword_18010C470;
  v3 = *(_QWORD *)(qword_18010C470 + 5216);
  if ( *(_BYTE *)(qword_18010C470 + 126) )
  {
    if ( *(_BYTE *)(qword_18010C470 + 10184) )
    {
      if ( (*(_BYTE *)(qword_18010C470 + 10228) & 1) != 0 )
        sub_180052F00(
          "[imgui-error] (current settings: Assert=%d, Log=%d, Tooltip=%d)\n",
          *(unsigned __int8 *)(qword_18010C470 + 125),
          *(unsigned __int8 *)(qword_18010C470 + 126),
          *(unsigned __int8 *)(qword_18010C470 + 127));
      else
        ++*(_DWORD *)(qword_18010C470 + 10272);
    }
    if ( (*(_BYTE *)(v1 + 10228) & 1) != 0 )
    {
      if ( v3 )
        sub_180052F00("[imgui-error] In window '%s': %s\n", *(const char **)(v3 + 8), a1);
      else
        sub_180052F00("[imgui-error] In window '%s': %s\n", "NULL", a1);
    }
    else
    {
      ++*(_DWORD *)(v1 + 10272);
    }
  }
  v17 = *(_BYTE *)(v1 + 127) == 0;
  *(_BYTE *)(v1 + 10184) = 0;
  if ( !v17 )
  {
    if ( *(_BYTE *)(v1 + 5048) )
    {
      v4 = "#Tooltip_Error";
      v5 = qword_18010C470;
      v6 = -1;
      v7 = 35;
      do
      {
        if ( v7 == 35 && *v4 == 35 && v4[1] == 35 )
          v6 = -1;
        v8 = v7 ^ (unsigned __int64)(unsigned __int8)v6;
        v7 = *v4++;
        v6 = dword_1800D56B0[v8] ^ (v6 >> 8);
      }
      while ( v7 );
      v9 = sub_18003EA40(~v6, v8, v4, 0xFFFFFFFFLL);
      v10 = *(_BYTE *)(v5 + 252) && v9 && *(_BYTE *)(v9 + 205);
      v11 = (__m128)*(unsigned __int64 *)(v5 + 3492);
      v22 = (float)((float)(1.0 - *(float *)(v5 + 3488)) * 0.15000001) + *(float *)(v5 + 3488);
      v23 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps((__m128)0LL, v11), (__m128)xmmword_1800E6930), v11).m128_u64[0];
      v24 = (float)((float)(1.0 - *(float *)(v5 + 3500)) * 0.15000001) + *(float *)(v5 + 3500);
      sub_180036E50(4, &v22);
      if ( v10 )
      {
        v12 = qword_18010C470;
        *(_DWORD *)(qword_18010C470 + 7824) |= 1u;
        v13 = *(_QWORD *)(v5 + 10176);
        *(_QWORD *)(v12 + 7848) = 0;
        *(_QWORD *)(v12 + 7840) = v13;
        *(_DWORD *)(v12 + 7828) = 1;
      }
      v14 = sub_180040700("##Tooltip_Error", 0, 33554799);
      sub_180036F60(1);
      if ( v14 )
      {
        if ( *(_WORD *)(*(_QWORD *)(v5 + 5216) + 218LL) == 1 )
        {
          sub_180072500("MESSAGE FROM DEAR IMGUI");
          sub_18004D3B0(*(_QWORD *)(v5 + 5216));
          sub_18004D320(*(_QWORD *)(v5 + 5216));
          v15 = *(_QWORD *)(qword_18010C470 + 5216);
          v16 = *(_DWORD *)(v15 + 44);
          LODWORD(v15) = *(_DWORD *)(v15 + 40);
          *(_DWORD *)(v5 + 10180) = v16;
          *(_DWORD *)(v5 + 10176) = v15;
        }
        v17 = *(_DWORD *)(v1 + 10188) == 20;
        if ( *(int *)(v1 + 10188) < 20 )
        {
          if ( v3 )
          {
            sub_18006F370((__int64)"In window '%s': %s", *(const char **)(v3 + 8), a1);
            if ( !*(_BYTE *)(v3 + 213) || *(_BYTE *)(v3 + 205) )
            {
              v18 = (unsigned int)sub_18003AA50(**(_QWORD **)(qword_18010C470 + 8104));
              v19 = *(float *)(v3 + 52) + *(float *)(v3 + 44);
              v25 = *(float *)(v3 + 48) + *(float *)(v3 + 40);
              v26 = v19;
              sub_18005C460(v18, v3 + 40, (unsigned int)&v25, -16776961, 0);
            }
          }
          else
          {
            sub_18006F370((__int64)"In window '%s': %s", "NULL", a1);
          }
          v17 = *(_DWORD *)(v1 + 10188) == 20;
        }
        if ( v17 )
          sub_18006F370((__int64)"(and more errors)");
      }
      sub_180044DF0();
    }
    ++*(_DWORD *)(v1 + 10188);
  }
  v20 = *(void (__fastcall **)(__int64, _QWORD, const char *))(v1 + 10160);
  if ( v20 )
    v20(v1, *(_QWORD *)(v1 + 10168), a1);
  return *(unsigned __int8 *)(v1 + 125);
}
