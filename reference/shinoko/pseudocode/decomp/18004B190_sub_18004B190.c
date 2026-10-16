// sub_18004B190 size=698
__int64 sub_18004B190()
{
  __int64 v0; // rbx
  __int64 v1; // rdi
  __int64 v2; // rbp
  __int64 v3; // rsi
  float v4; // xmm5_4
  float v5; // xmm4_4
  float v6; // xmm3_4
  __int64 v7; // xmm0_8
  float v8; // xmm6_4
  float v9; // xmm4_4
  float v10; // xmm3_4
  float v11; // xmm2_4
  __int64 result; // rax
  float v13; // xmm0_4
  int v14; // eax
  bool v15; // cl
  bool v16; // dl
  int v17; // ecx
  __int128 v18; // [rsp+40h] [rbp-48h] BYREF
  float v19; // [rsp+90h] [rbp+8h] BYREF
  float v20; // [rsp+94h] [rbp+Ch]

  v0 = qword_18010C470;
  v1 = *(_QWORD *)(qword_18010C470 + 5216);
  v2 = *(_QWORD *)(qword_18010C470 + 8040);
  v3 = 56LL * *(int *)(qword_18010C470 + 8032);
  if ( *(_BYTE *)(v1 + 345) )
  {
    *(_BYTE *)(v1 + 345) = 0;
    if ( (*(float *)(v1 + 304) < *(float *)(v1 + 280) || *(float *)(v1 + 308) < *(float *)(v1 + 284))
      && !*(_BYTE *)(v1 + 209) )
    {
      sub_180049A30(
        "Code uses SetCursorPos()/SetCursorScreenPos() to extend window/parent boundaries.\n"
        "Please submit an item e.g. Dummy() afterwards in order to grow window/parent boundaries.");
    }
  }
  v5 = fmaxf(*(float *)(v1 + 308), *(float *)(v0 + 7768));
  v6 = fmaxf(*(float *)(v1 + 304), *(float *)(v0 + 7764));
  v7 = *(_QWORD *)(v3 + v2 - 52);
  v8 = *(float *)(v3 + v2 - 48);
  LODWORD(v18) = *(_DWORD *)(v3 + v2 - 52);
  v4 = *(float *)&v18;
  v9 = fmaxf(v5, *(float *)(v3 + v2 - 48));
  *(_QWORD *)(v1 + 280) = v7;
  v10 = fmaxf(v6, v4);
  *(_QWORD *)(v1 + 288) = *(_QWORD *)(v3 + v2 - 36);
  v11 = *(float *)(v3 + v2 - 40);
  *(float *)&v7 = fmaxf(*(float *)(v3 + v2 - 44), v10);
  *(_QWORD *)((char *)&v18 + 4) = __PAIR64__(LODWORD(v10), LODWORD(v8));
  *((float *)&v18 + 3) = v9;
  *(_DWORD *)(v1 + 304) = v7;
  *(float *)(v1 + 308) = fmaxf(v11, v9);
  *(_DWORD *)(v1 + 348) = *(_DWORD *)(v3 + v2 - 28);
  *(_DWORD *)(v1 + 356) = *(_DWORD *)(v3 + v2 - 24);
  *(_QWORD *)(v1 + 320) = *(_QWORD *)(v3 + v2 - 20);
  *(_DWORD *)(v1 + 336) = *(_DWORD *)(v3 + v2 - 12);
  result = *(unsigned __int8 *)(v3 + v2 - 2);
  *(_BYTE *)(v1 + 344) = result;
  if ( *(_BYTE *)(v0 + 10080) )
    *(_DWORD *)(v0 + 10136) = -8388609;
  if ( !*(_BYTE *)(v3 + v2 - 1) )
  {
    --*(_DWORD *)(v0 + 8032);
    return result;
  }
  v13 = fmaxf(*(float *)(v1 + 340), *(float *)(v3 + v2 - 12));
  v19 = v10 - v4;
  *(float *)(v1 + 336) = v13;
  v20 = v9 - v8;
  sub_18004AAD0(&v19);
  sub_18004A070(&v18, 0, 0, 1);
  v14 = *(_DWORD *)(v0 + 5332);
  v15 = *(_DWORD *)(v3 + v2 - 8) != v14 && *(_DWORD *)(v0 + 5336) == v14 && v14;
  v16 = !*(_BYTE *)(v3 + v2 - 4) && *(_BYTE *)(v0 + 5393) == 1;
  if ( !v15 )
  {
    if ( !v16 )
      goto LABEL_23;
    v14 = *(_DWORD *)(v0 + 5384);
  }
  *(_DWORD *)(v0 + 7744) = v14;
LABEL_23:
  *(_OWORD *)(v0 + 7756) = v18;
  if ( !*(_BYTE *)(v3 + v2 - 3) && *(_DWORD *)(v0 + 5308) )
    *(_DWORD *)(v0 + 7752) |= 0x80u;
  if ( v15 && *(_BYTE *)(v0 + 5349) )
    *(_DWORD *)(v0 + 7752) |= 4u;
  v17 = *(_DWORD *)(v0 + 7752);
  result = v17 | 0x20u;
  *(_DWORD *)(v0 + 7752) = result;
  if ( v16 )
    *(_DWORD *)(v0 + 7752) = v17 | 0x60;
  --*(_DWORD *)(v0 + 8032);
  if ( *(_BYTE *)(v0 + 7944) )
    return sub_18005C460(*(_QWORD *)(v1 + 712), (unsigned int)&v18, (unsigned int)&v18 + 8, -65281, 0);
  return result;
}
