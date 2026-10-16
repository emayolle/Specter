// sub_18003E470 size=882
__int64 __fastcall sub_18003E470(const char *a1, int a2, _QWORD *a3, int a4, int a5)
{
  int v5; // ebp
  int v8; // r10d
  int v9; // ebx
  __int64 v11; // r13
  __int64 v12; // rdi
  int v13; // edx
  unsigned int v14; // ecx
  unsigned int v15; // esi
  unsigned int v16; // ebp
  __int64 v17; // r11
  float v18; // xmm0_4
  unsigned int v19; // eax
  int v20; // eax
  const char *v21; // r9
  int v22; // xmm6_4
  unsigned __int8 v23; // al
  unsigned __int8 v24; // r14
  __int64 v25; // rbp
  bool v26; // zf
  char *v27; // rdx
  unsigned int v28; // ebx
  unsigned __int8 v29; // al
  unsigned __int64 v30; // rcx
  int v31; // ebx
  __int64 v33; // [rsp+90h] [rbp+8h] BYREF

  v5 = a5;
  v8 = a4 | 2;
  v9 = 16777281;
  v11 = *(_QWORD *)(qword_18010C470 + 5216);
  v12 = qword_18010C470;
  if ( (a5 & 0x40000000) == 0 )
    v8 = a4;
  v13 = v8 | 0x100;
  if ( (a5 & 0x20000000) == 0 )
    v13 = v8;
  v14 = v13 & 0xFFFFFFFB;
  if ( (v13 & 0x10) == 0 )
    v14 = v13;
  v15 = v14 & 0xFFFFFFF7;
  if ( (v14 & 0x20) == 0 )
    v15 = v14;
  if ( (v15 & 0x70) == 0 )
    v9 = 16777217;
  if ( (v15 & 0xC) == 0 )
  {
    v9 = 16777539;
    if ( (v15 & 0x70) == 0 )
      v9 = 16777475;
  }
  if ( (v15 & 0x80u) == 0 )
  {
    v16 = v9 | *(_DWORD *)(v11 + 20) & 4 | a5;
  }
  else
  {
    sub_180036E50(3, qword_18010C470 + 3536);
    sub_180036FE0(7, *(float *)(v12 + 3220));
    sub_180036FE0(8, *(float *)(v12 + 3224));
    sub_180037110(2, (_QWORD *)(v12 + 3212));
    v15 |= 3u;
    v16 = v9 | 4 | v5;
  }
  sub_18004AEC0(&v33, *a3);
  if ( (*(_BYTE *)(v12 + 7824) & 2) != 0 && (*(_BYTE *)(v12 + 7832) & 1) != 0 )
  {
    v18 = *(float *)(v12 + 7856);
    if ( v18 > 0.0 )
      LODWORD(v33) = *(_DWORD *)(v12 + 7856);
    v19 = v15 & 0xFFFFFFFB;
    if ( v18 <= 0.0 )
      v19 = v15;
    v15 = v19;
    if ( *(float *)(v12 + 7860) > 0.0 )
    {
      HIDWORD(v33) = *(_DWORD *)(v12 + 7860);
      v15 = v19 & 0xFFFFFFF7;
    }
  }
  *(_DWORD *)(v17 + 7824) |= 2u;
  *(_QWORD *)(v17 + 7856) = v33;
  *(_DWORD *)(v17 + 7832) = 1;
  v20 = *(_DWORD *)(v12 + 7824);
  if ( (v20 & 0x200) != 0 )
    *(_DWORD *)(v12 + 7884) |= v15;
  else
    *(_DWORD *)(v12 + 7884) = v15;
  *(_DWORD *)(v12 + 7824) = v20 | 0x200;
  v21 = *(const char **)(v11 + 8);
  if ( a1 )
    sub_180035F50(&v33, 0, "%s/%s_%08X", v21, a1, a2);
  else
    sub_180035F50(&v33, 0, "%s/%08X", v21, a2);
  v22 = *(_DWORD *)(v12 + 3200);
  if ( (v15 & 1) == 0 )
    *(_DWORD *)(v12 + 3200) = 0;
  v23 = sub_180040700(v33, 0, v16);
  *(_DWORD *)(v12 + 3200) = v22;
  v24 = v23;
  if ( (v15 & 0x80u) != 0 )
  {
    sub_1800371B0(3);
    sub_180036F60(1);
  }
  v25 = *(_QWORD *)(v12 + 5216);
  v26 = *(_WORD *)(v25 + 218) == 1;
  *(_DWORD *)(v25 + 144) = a2;
  if ( v26 )
    *(_QWORD *)(v11 + 280) = *(_QWORD *)(v25 + 40);
  v27 = "#Child";
  v28 = ~a2;
  v29 = 35;
  do
  {
    if ( v29 == 35 && *v27 == 35 && v27[1] == 35 )
      v28 = ~a2;
    v30 = v29 ^ (unsigned __int64)(unsigned __int8)v28;
    v29 = *v27++;
    v28 = dword_1800D56B0[v30] ^ (v28 >> 8);
  }
  while ( v29 );
  v31 = ~v28;
  if ( *(_DWORD *)(v12 + 5332) == v31 )
    sub_180039FD0(0, 0);
  if ( *(_DWORD *)(v12 + 8136) == a2 && (v15 & 0x100) == 0 && (*(_WORD *)(v25 + 372) || *(_BYTE *)(v25 + 378)) )
  {
    sub_18004D450(v25, 0);
    sub_18004E340(v25, 0);
    sub_180039FD0(v31, v25);
    *(_DWORD *)(v12 + 5376) = *(_DWORD *)(v12 + 8184);
  }
  return v24;
}
