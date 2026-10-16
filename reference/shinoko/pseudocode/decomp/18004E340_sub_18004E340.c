// sub_18004E340 size=295
char __fastcall sub_18004E340(__int64 a1, char a2)
{
  int v2; // eax
  __int64 v4; // rdi
  bool v6; // si
  __int64 v7; // r8
  __int64 v8; // rdx
  _BYTE *v9; // rcx
  __int128 v10; // [rsp+20h] [rbp-18h] BYREF

  v2 = *(_DWORD *)(a1 + 20);
  v4 = qword_18010C470;
  if ( (v2 & 0x10000) != 0 )
  {
    *(_DWORD *)(qword_18010C470 + 8116) = 0;
    return sub_180045650(*(unsigned int *)(a1 + 1064));
  }
  else
  {
    v6 = a1 == *(_QWORD *)(a1 + 960) || (v2 & 0x4000000) != 0 || !*(_DWORD *)(a1 + 1008) || a2;
    if ( (*(_BYTE *)(qword_18010C470 + 10228) & 0x10) != 0 )
      sub_180052F00(
        "[nav] NavInitRequest: from NavInitWindow(), init_for_nav=%d, window=\"%s\", layer=%d\n",
        v6,
        *(const char **)(a1 + 8),
        *(_DWORD *)(qword_18010C470 + 8132));
    if ( v6 )
    {
      v7 = *(unsigned int *)(a1 + 1064);
      v8 = *(unsigned int *)(v4 + 8132);
      v10 = 0;
      sub_18004DA70(0, v8, v7, &v10);
      v9 = (_BYTE *)qword_18010C470;
      *(_WORD *)(v4 + 8202) = 1;
      *(_DWORD *)(v4 + 8216) = 0;
      if ( v9[8265] || v9[8202] )
      {
        v9[8201] = 1;
        return 1;
      }
      else
      {
        v9[8201] = 0;
        return 0;
      }
    }
    else
    {
      *(_DWORD *)(v4 + 8116) = *(_DWORD *)(a1 + 1008);
      return sub_180045650(*(unsigned int *)(a1 + 1064));
    }
  }
}
