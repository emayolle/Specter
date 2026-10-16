// sub_180048D00 size=1668
char __fastcall sub_180048D00(int a1, int a2, unsigned int a3)
{
  __int64 v3; // rbx
  unsigned int v4; // ebp
  int v5; // r13d
  int v6; // edi
  __int64 v7; // r15
  int v8; // r14d
  __int64 v9; // rdx
  signed int v10; // r12d
  int v11; // esi
  int v12; // esi
  int v13; // r10d
  int v14; // r11d
  const char *v15; // rax
  int v16; // eax
  int v17; // eax
  const char *v18; // rax
  unsigned int v20; // eax
  __int64 v21; // r8
  int v22; // edi
  __int64 v23; // rcx
  const char *v24; // rax
  int v25; // eax
  __int64 v26; // r13
  int v27; // esi
  signed int v28; // eax
  _WORD *v29; // r9
  __int16 v30; // ax
  __int64 v31; // r14
  int v32; // ecx
  int *v33; // r14
  __int64 v34; // r12
  int v35; // r8d
  int v36; // eax
  __int64 v37; // rcx
  unsigned __int8 v38; // dl
  int v39; // ecx
  int v40; // ecx
  unsigned int v41; // eax
  __int64 v42; // rcx
  unsigned int v44; // [rsp+88h] [rbp+10h]
  char v45; // [rsp+90h] [rbp+18h]
  _WORD *v46; // [rsp+98h] [rbp+20h]

  v3 = qword_18010C470;
  v4 = a3;
  v5 = a2 | 0x800;
  v6 = a1;
  v7 = qword_18010C470;
  if ( (a2 & 0x3C00) != 0 )
    v5 = a2;
  v45 = v5;
  if ( ((a3 + 1) & 0xFFFFFFFE) == 0 )
    v4 = *(_DWORD *)(qword_18010C470 + 7676);
  if ( (*(_DWORD *)(qword_18010C470 + 7680) & 0x400) != 0 )
    return 0;
  v8 = v5 | 0xD000;
  v9 = 4294966766LL;
  if ( (v5 & 0x3C00) != 0 )
    v8 = v5;
  v10 = a1 & 0xFFFF0FFF;
  v44 = a1 & 0xFFFF0FFF;
  if ( (a1 & 0xFFFF0FFF) - 527 > 7 )
  {
    v12 = a1;
  }
  else if ( ((v10 - 527) & 0xFFFFFFFB) != 0 )
  {
    if ( ((v10 - 528) & 0xFFFFFFFB) != 0 )
    {
      if ( ((v10 - 529) & 0xFFFFFFFB) != 0 )
      {
        v11 = 0x8000;
        if ( ((v10 - 530) & 0xFFFFFFFB) != 0 )
          v11 = 0;
        v12 = a1 | v11;
      }
      else
      {
        v12 = a1 | 0x4000;
      }
    }
    else
    {
      v12 = a1 | 0x2000;
    }
  }
  else
  {
    v12 = a1 | 0x1000;
  }
  if ( *(_DWORD *)(qword_18010C470 + 7672) == v12 )
    __debugbreak();
  if ( (v8 & 0x10000) != 0 && !*(_QWORD *)(qword_18010C470 + 8120) )
    return 0;
  v13 = 663;
  v14 = 666;
  if ( (v8 & 0x2000) != 0 )
  {
    if ( (*(_DWORD *)(qword_18010C470 + 10228) & 0x200) != 0 )
    {
      v15 = (const char *)sub_1800469D0(v12);
      sub_180052F00("SetShortcutRouting(%s, flags=%04X, owner_id=0x%08X) -> always, no register\n", v15, v8, v4);
      v3 = qword_18010C470;
    }
    goto LABEL_103;
  }
  v16 = *(_DWORD *)(qword_18010C470 + 5332);
  if ( v16 && v16 != v4 )
  {
    if ( (v8 & 0x400) != 0 )
      return 0;
    if ( *(_BYTE *)(qword_18010C470 + 178)
      && ((v12 & 0x1000) == 0 || (v12 & 0x4000) != 0)
      && (!*(_BYTE *)(qword_18010C470 + 89) || (v12 & 0x1000) == 0) )
    {
      v9 = v12 & 0xFFFF0FFF;
      if ( (v12 & 0xFFFF0FFF) != 0 )
      {
        v17 = *(_DWORD *)(qword_18010C470 + 4 * (((int)v9 - 512LL) >> 5) + 5440);
        if ( _bittest(&v17, v12 & 0x1F) )
        {
          if ( (*(_DWORD *)(qword_18010C470 + 10228) & 0x200) != 0 )
          {
            v18 = (const char *)sub_1800469D0(v12);
            sub_180052F00(
              "SetShortcutRouting(%s, flags=%04X, owner_id=0x%08X) -> filtered as potential char input\n",
              v18,
              v8,
              v4);
          }
          return 0;
        }
      }
    }
    if ( (v8 & 0x8000) == 0 && *(_BYTE *)(qword_18010C470 + 7668) )
    {
      v20 = v12 & 0xFFFF0FFF;
      if ( (v12 & 0xFFFF0FFF) == 0 )
        v20 = sub_180034F20((unsigned __int16)v12 & 0xF000, v9, 4294966769LL, 4294966768LL);
      if ( v20 - 512 <= 0x77 )
        return 0;
    }
  }
  if ( (v8 & 0x20000) != 0 )
    v21 = *(unsigned int *)(*(_QWORD *)(*(_QWORD *)(v3 + 5216) + 960LL) + 16LL);
  else
    v21 = *(unsigned int *)(v3 + 7676);
  if ( (v8 & 0x800) != 0 )
  {
    if ( v4 && *(_DWORD *)(v3 + 5332) == v4 )
    {
      v22 = 300;
      goto LABEL_57;
    }
    if ( (_DWORD)v21 )
    {
      v9 = *(unsigned int *)(v3 + 8152);
      if ( (int)v9 > 0 )
      {
        v23 = 0;
        while ( *(_DWORD *)(*(_QWORD *)(v3 + 8160) + 8 * v23) != (_DWORD)v21 )
        {
          v23 = (unsigned int)(v23 + 1);
          if ( (int)v23 >= (int)v9 )
            goto LABEL_56;
        }
        if ( (v8 & 0x8000) != 0 )
          v22 = 599 - v23;
        else
          v22 = 199 - v23;
        goto LABEL_57;
      }
    }
    goto LABEL_56;
  }
  if ( (v8 & 0x400) != 0 )
  {
    if ( v4 && *(_DWORD *)(v3 + 5332) == v4 )
    {
      v22 = 300;
      goto LABEL_57;
    }
LABEL_56:
    v22 = 0;
    goto LABEL_57;
  }
  if ( (v8 & 0x1000) == 0 )
    goto LABEL_56;
  if ( (v8 & 0x8000) != 0 )
  {
    v22 = 400;
  }
  else if ( v4 && *(_DWORD *)(v3 + 5332) == v4 )
  {
    v22 = 300;
  }
  else
  {
    v22 = 1;
    if ( (v8 & 0x4000) != 0 )
      v22 = 200;
  }
LABEL_57:
  if ( (*(_DWORD *)(v3 + 10228) & 0x200) != 0 )
  {
    v24 = (const char *)sub_1800469D0(v12);
    sub_180052F00("SetShortcutRouting(%s, flags=%04X, owner_id=0x%08X) -> score %d\n", v24, v8, v4, v22);
    v3 = qword_18010C470;
    v13 = 663;
    v14 = 666;
  }
  if ( !v22 )
    return 0;
  v25 = v12;
  v26 = v3 + 7320;
  v27 = v12 & 0xF000;
  v28 = v25 & 0xFFFF0FFF;
  if ( !v28 )
  {
    switch ( v27 )
    {
      case 0x1000:
        v28 = v13;
        break;
      case 0x2000:
        v28 = 664;
        break;
      case 0x4000:
        v28 = 665;
        break;
      default:
        v28 = v27;
        if ( v27 == 0x8000 )
          v28 = v14;
        break;
    }
  }
  v29 = (_WORD *)(v26 + 2LL * v28 - 1024);
  v46 = v29;
  v30 = *v29;
  if ( *v29 == 0xFFFF )
  {
LABEL_88:
    v32 = *(_DWORD *)(v3 + 7636);
    v33 = (int *)(v3 + 7632);
    v21 = *(unsigned int *)(v3 + 7632);
    v34 = *(__int16 *)(v3 + 7632);
    if ( (_DWORD)v21 == v32 )
    {
      v35 = v21 + 1;
      if ( v32 )
        v36 = v32 + v32 / 2;
      else
        v36 = 8;
      if ( v36 > v35 )
        v35 = v36;
      sub_180054C20(v3 + 7632, (unsigned int)v35);
      v29 = v46;
      v3 = qword_18010C470;
    }
    v37 = *(_QWORD *)(v26 + 320);
    v9 = 2LL * *v33;
    *(_QWORD *)(v37 + 8 * v9) = 0xFFFF;
    *(_QWORD *)(v37 + 8 * v9 + 8) = -1;
    ++*v33;
    v31 = *(_QWORD *)(v26 + 320) + 16 * v34;
    *(_WORD *)(v31 + 2) = v27;
    *(_WORD *)v31 = *v29;
    *v29 = v34;
    v10 = v44;
  }
  else
  {
    while ( 1 )
    {
      v31 = *(_QWORD *)(v3 + 7640) + 16LL * v30;
      if ( *(unsigned __int16 *)(v31 + 2) == v27 )
        break;
      v30 = *(_WORD *)v31;
      if ( *(_WORD *)v31 == 0xFFFF )
        goto LABEL_88;
    }
  }
  if ( v22 > *(unsigned __int16 *)(v31 + 6) )
  {
    *(_DWORD *)(v31 + 12) = v4;
    *(_WORD *)(v31 + 6) = v22;
  }
  if ( *(_DWORD *)(v31 + 8) != v4 )
    return 0;
  if ( (*(_DWORD *)(v7 + 10228) & 0x200) != 0 )
  {
    sub_180052F00("--> granting current route\n", v9, v21);
    v3 = qword_18010C470;
  }
  if ( *(_DWORD *)(v31 + 8) != v4 )
    return 0;
  v6 = a1;
  LOBYTE(v5) = v45;
LABEL_103:
  v38 = v5 | 0x20;
  v39 = v6;
  if ( (v5 & 0xF1) != 1 )
    v38 = v5;
  if ( v10 >= 527 && v10 <= 534 )
  {
    if ( ((v10 - 527) & 0xFFFFFFFB) != 0 )
    {
      if ( ((v10 - 528) & 0xFFFFFFFB) != 0 )
      {
        if ( ((v10 - 529) & 0xFFFFFFFB) != 0 )
        {
          v40 = 0x8000;
          if ( ((v10 - 530) & 0xFFFFFFFB) != 0 )
            v40 = 0;
        }
        else
        {
          v40 = 0x4000;
        }
      }
      else
      {
        v40 = 0x2000;
      }
    }
    else
    {
      v40 = 4096;
    }
    v39 = v6 | v40;
  }
  v41 = v39 & 0xF000;
  if ( *(_DWORD *)(v3 + 256) != v41 )
    return 0;
  v42 = v39 & 0xFFFF0FFF;
  if ( !(_DWORD)v42 )
  {
    switch ( v41 )
    {
      case 0x1000u:
        v42 = 663;
        break;
      case 0x2000u:
        v42 = 664;
        break;
      case 0x4000u:
        v42 = 665;
        break;
      default:
        v42 = v41;
        if ( v41 == 0x8000 )
          v42 = 666;
        break;
    }
  }
  if ( !(unsigned __int8)sub_180046DB0(v42, v38, v4) )
    return 0;
  if ( (v6 & 0x1000) != 0 )
  {
    *(_DWORD *)(v3 + 7276) = v4;
    *(_DWORD *)(v3 + 7272) = v4;
    *(_WORD *)(v3 + 7280) = 0;
  }
  if ( (v6 & 0x2000) != 0 )
  {
    *(_DWORD *)(v3 + 7288) = v4;
    *(_DWORD *)(v3 + 7284) = v4;
    *(_WORD *)(v3 + 7292) = 0;
  }
  if ( (v6 & 0x4000) != 0 )
  {
    *(_DWORD *)(v3 + 7300) = v4;
    *(_DWORD *)(v3 + 7296) = v4;
    *(_WORD *)(v3 + 7304) = 0;
  }
  if ( (v6 & 0x8000) != 0 )
  {
    *(_DWORD *)(v3 + 7312) = v4;
    *(_DWORD *)(v3 + 7308) = v4;
    *(_WORD *)(v3 + 7316) = 0;
  }
  return 1;
}
