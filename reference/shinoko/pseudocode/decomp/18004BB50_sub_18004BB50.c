// sub_18004BB50 size=407
char __fastcall sub_18004BB50(char a1)
{
  __int64 v1; // rbx
  char v3; // cl
  int v4; // eax
  float v5; // xmm3_4
  float v6; // xmm5_4
  int v7; // xmm2_4
  float v8; // xmm0_4
  int v9; // xmm4_4
  float v10; // xmm1_4
  float v11; // xmm0_4
  float v12; // xmm0_4
  const char *v13; // rdi
  _BYTE *v14; // rax
  unsigned __int8 v16[40]; // [rsp+20h] [rbp-28h] BYREF

  v1 = qword_18010C470;
  if ( *(_BYTE *)(qword_18010C470 + 8657) || *(_BYTE *)(qword_18010C470 + 8658) )
  {
    v4 = *(_DWORD *)(qword_18010C470 + 7824);
    v3 = 1;
    if ( (v4 & 1) == 0 )
    {
      v5 = *(float *)(qword_18010C470 + 3408);
      v6 = *(float *)(qword_18010C470 + 228);
      if ( *(_DWORD *)(qword_18010C470 + 248) == 1 )
      {
        v7 = 1056964608;
        v8 = 0.0;
        v9 = 1065353216;
        v10 = -20.0;
      }
      else
      {
        v8 = 16.0;
        v7 = 0;
        v10 = 10.0;
        v9 = 0;
      }
      v4 |= 1u;
      v11 = (float)(v8 * v5) + *(float *)(qword_18010C470 + 224);
      *(_DWORD *)(qword_18010C470 + 7848) = v7;
      *(_DWORD *)(v1 + 7852) = v9;
      *(_DWORD *)(v1 + 7828) = 1;
      *(float *)(v1 + 7840) = v11;
      *(float *)(v1 + 7844) = (float)(v10 * v5) + v6;
    }
    v12 = *(float *)(v1 + 3500) * 0.60000002;
    a1 = 2;
    *(_DWORD *)(v1 + 7824) = v4 | 0x40;
    *(float *)(v1 + 7928) = v12;
  }
  else
  {
    v3 = 0;
  }
  v13 = "##Tooltip_%02d";
  if ( v3 )
    v13 = "##Tooltip_DragDrop_%02d";
  sub_180035ED0(v16, 32, v13, (unsigned int)*(__int16 *)(v1 + 9698));
  if ( (a1 & 2) != 0 )
  {
    v14 = *(_BYTE **)(v1 + 9704);
    if ( v14 )
    {
      if ( v14[204] )
      {
        v14[209] = 1;
        v14[212] = 1;
        v14[236] = 1;
        sub_180035ED0(v16, 32, v13, (unsigned int)(__int16)++*(_WORD *)(v1 + 9698));
      }
    }
  }
  sub_180040700(v16, 0, 33751879);
  return 1;
}
