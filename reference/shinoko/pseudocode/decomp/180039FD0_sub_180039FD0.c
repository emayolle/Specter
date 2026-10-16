// sub_180039FD0 size=469
char __fastcall sub_180039FD0(int a1, __int64 a2)
{
  __int64 v2; // rbx
  int v5; // ecx
  bool v6; // zf
  int v7; // r8d
  int v8; // eax
  __int64 v9; // rcx
  __int64 v10; // rax
  int v11; // edx
  int v12; // eax
  const char *v13; // r8
  const char *v14; // rcx
  __int64 v15; // rax

  v2 = qword_18010C470;
  v5 = *(_DWORD *)(qword_18010C470 + 5332);
  if ( v5 )
  {
    v6 = *(_DWORD *)(qword_18010C470 + 7744) == v5;
    *(_DWORD *)(qword_18010C470 + 5384) = v5;
    v7 = *(_DWORD *)(v2 + 5032);
    if ( !v6 )
      ++v7;
    *(_DWORD *)(v2 + 5388) = v7;
    *(_BYTE *)(v2 + 5392) = *(_BYTE *)(v2 + 5348);
    *(_BYTE *)(v2 + 5393) = *(_DWORD *)(v2 + 5336) == v5;
    v8 = *(_DWORD *)(v2 + 9276);
    if ( v8 == v5 )
    {
      *(_DWORD *)(v2 + 9408) = v8;
      v9 = v2 + 9416;
      if ( (*(_DWORD *)(v2 + 9272) & 0x200) != 0 )
      {
        sub_1800542F0(v9, 0);
      }
      else
      {
        sub_1800542F0(v9, (unsigned int)(*(_DWORD *)(v2 + 9280) + 1));
        sub_1800B8BD0(*(_QWORD *)(v2 + 9424), *(_QWORD *)(v2 + 9304), *(_DWORD *)(v2 + 9280) + 1);
      }
    }
    v10 = *(_QWORD *)(v2 + 5248);
    if ( v10 && *(_DWORD *)(v2 + 5332) == *(_DWORD *)(v10 + 140) )
    {
      if ( (*(_BYTE *)(v2 + 10228) & 2) != 0 )
        sub_180052F00("SetActiveID() cancel MovingWindow\n");
      *(_QWORD *)(qword_18010C470 + 5248) = 0;
    }
  }
  v11 = *(_DWORD *)(v2 + 5332);
  LOBYTE(v12) = v11 != a1;
  *(_BYTE *)(v2 + 5344) = v11 != a1;
  if ( v11 != a1 )
  {
    if ( (*(_BYTE *)(v2 + 10228) & 2) != 0 )
    {
      v13 = (const char *)&unk_1800D411C;
      if ( a2 )
        v14 = *(const char **)(a2 + 8);
      else
        v14 = (const char *)&unk_1800D411C;
      v15 = *(_QWORD *)(v2 + 5368);
      if ( v15 )
        v13 = *(const char **)(v15 + 8);
      LOBYTE(v12) = sub_180052F00(
                      "SetActiveID() old:0x%08X (window \"%s\") -> new:0x%08X (window \"%s\")\n",
                      v11,
                      v13,
                      a1,
                      v14);
    }
    *(_DWORD *)(v2 + 5356) |= 0xFFu;
    *(_DWORD *)(v2 + 5340) = 0;
    *(_WORD *)(v2 + 5347) = 0;
    if ( a1 )
    {
      *(_DWORD *)(v2 + 5404) = a1;
      *(_DWORD *)(v2 + 5408) = 0;
    }
  }
  *(_DWORD *)(v2 + 5332) = a1;
  *(_WORD *)(v2 + 5345) = 0;
  *(_QWORD *)(v2 + 5368) = a2;
  *(_WORD *)(v2 + 5349) = 0;
  *(_DWORD *)(v2 + 5352) = 0;
  if ( a1 )
  {
    *(_DWORD *)(v2 + 5336) = a1;
    if ( *(_DWORD *)(v2 + 8136) == a1 || (v12 = 1, *(_DWORD *)(v2 + 8564) == a1) )
      v12 = *(_DWORD *)(v2 + 8184);
    *(_DWORD *)(v2 + 5376) = v12;
  }
  *(_BYTE *)(v2 + 7668) = 0;
  *(_DWORD *)(v2 + 7664) = 0;
  return v12;
}
