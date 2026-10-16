// sub_18005F180 size=1141
__int64 __fastcall sub_18005F180(__int64 a1)
{
  unsigned int v2; // edi
  unsigned int v3; // esi
  int v4; // ebx
  __int64 v5; // rbp
  unsigned int v6; // eax
  unsigned int v7; // edi
  __int64 v8; // rdx
  __int64 v9; // r8
  int v10; // r12d
  int v11; // r13d
  __int64 v12; // rdi
  int v13; // r10d
  _WORD *v14; // rdx
  _QWORD *v15; // rdx
  const __m128i *v16; // rdx
  const __m128i *v17; // r8
  __m128i si128; // xmm3
  int v19; // esi
  unsigned __int64 v20; // r11
  int v21; // r10d
  __m128i v22; // xmm0
  __m128i v23; // xmm2
  __m128i v24; // xmm0
  __m128i v25; // xmm1
  __m128i v26; // xmm0
  __int64 v27; // rcx
  char v28; // al
  int v29; // r11d
  __int64 v30; // r10
  __int64 i; // rcx
  int v32; // eax
  int v33; // eax
  __int64 v34; // r10
  int v35; // ecx
  __m128i v36; // xmm3
  unsigned __int64 v37; // r9
  int v38; // r8d
  __m128i v39; // xmm0
  __m128i v40; // xmm2
  __m128i v41; // xmm0
  __m128i v42; // xmm1
  __m128i v43; // xmm0
  __int64 v44; // rcx
  char v45; // al
  __int64 v46; // r8
  __int64 j; // rcx
  int v48; // eax
  int v49; // eax
  unsigned __int16 v51[52]; // [rsp+30h] [rbp-68h] BYREF

  v2 = 2;
  v3 = 2;
  if ( (*(_DWORD *)a1 & 2) == 0 )
    v3 = 245;
  v4 = 27;
  v5 = *(_QWORD *)(a1 + 688);
  if ( (*(_DWORD *)a1 & 2) == 0 )
    v2 = 27;
  *(_OWORD *)v51 = 0;
  if ( (unsigned __int8)sub_18005E940(a1, *(unsigned int *)(v5 + 236), v51) )
  {
    LOWORD(v10) = v51[1];
    LOWORD(v11) = v51[0];
  }
  else
  {
    if ( !*(_QWORD *)(a1 + 688) )
      sub_180061380(a1);
    v6 = sub_180061CF0(a1, v3, v2, 0);
    v7 = v6;
    if ( v6 != -1 )
    {
      sub_18005E940(a1, v6, v51);
      if ( *(_BYTE *)(a1 + 81) )
      {
        v8 = *(_QWORD *)(a1 + 688);
        v9 = (__int64)(int)(*(_DWORD *)(*(_QWORD *)(v8 + 120) + 4LL * (v7 & 0x7FFFF)) << 12) >> 12;
        sub_18005E090(
          a1,
          *(_QWORD *)(a1 + 56),
          *(unsigned __int16 *)(*(_QWORD *)(v8 + 104) + 8 * v9),
          *(unsigned __int16 *)(*(_QWORD *)(v8 + 104) + 8 * v9 + 2),
          *(_WORD *)(*(_QWORD *)(v8 + 104) + 8 * v9 + 4),
          *(_WORD *)(*(_QWORD *)(v8 + 104) + 8 * v9 + 6));
      }
    }
    v10 = v51[1];
    v11 = v51[0];
    *(_DWORD *)(v5 + 236) = v7;
    v12 = *(_QWORD *)(a1 + 56);
    v13 = *(_DWORD *)(v12 + 24);
    if ( (*(_BYTE *)a1 & 2) != 0 )
    {
      if ( v13 )
      {
        if ( v13 == 1 )
        {
          v14 = (_WORD *)(*(_QWORD *)(v12 + 40) + *(_DWORD *)(v12 + 36) * (v11 + *(_DWORD *)(v12 + 28) * v10));
          *v14 = -1;
          *(_WORD *)((char *)v14 + *(int *)(v12 + 28)) = -1;
        }
      }
      else
      {
        v15 = (_QWORD *)(*(_QWORD *)(v12 + 40) + *(_DWORD *)(v12 + 36) * (v11 + *(_DWORD *)(v12 + 28) * v10));
        *v15 = -1;
        *(_QWORD *)((char *)v15 + 4 * *(int *)(v12 + 28)) = -1;
      }
    }
    else
    {
      v16 = (const __m128i *)"..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX-"
                             "     XX          - XX       XX ..-         -X.....X-   X.X   -          X.X          -X...."
                             ".X          -          X.....X-    X..X         -X..X     X..X---         -XXX.XXX-  X...X "
                             " -         X...X         -X....X           -           X....X-    X..X         -X...X   X.."
                             ".XX           -  X.X  - X.....X -        X.....X        -X...X            -            X..."
                             "X-    X..X         - X...X X...X XX          -  X.X  -X.......X-       X.......X       -X.."
                             "X.X           -           X.X..X-    X..X         -  X...X...X  X.X         -  X.X  -XXXX.X"
                             "XXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X-    X..XXX       -   X....."
                             "X   X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X  "
                             " XX-    X..X..XXX    -    X...X    X...X       -  X.X  -   X.X   -    XX    X.X    XX    - "
                             "     X.X        -        X.X      -    X..X..X..XX  -     X.X     X....X      -  X.X  -   X"
                             ".X   -   X.X    X.X    X.X   -       X.X       -       X.X       -    X..X..X..X.X -    X.."
                             ".X    X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X   "
                             "     -XXX X..X..X..X..X-   X.....X   X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X "
                             "-         X.X   XX-XX   X.X         -X..XX........X..X-  X...X...X  X.......X   -  X.X  -  "
                             " X.X   -X.....................X-          X.X X.X-X.X X.X          -X...X...........X- X..."
                             "X X...X X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X    "
                             "       - X..............X-X...X   X...XX.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X"
                             "  -            X...X-X...X            -  X.............X-X..X     X..XX..........X-X.....X-"
                             "   X.X   -   X.X    X.X    X.X   -           X....X-X....X           -  X.............X- XX"
                             "       XX X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X "
                             "         -   X............X--------------X...X..X    ---------   X.X   -          X.X      "
                             "    -          XXXXXXX-XXXXXXX          -   X...........X -             X..X X..X   -      "
                             " -XXXX.XXXX-       XXXX.XXXX       -------------------------------------    X..........X - "
                             "            X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -"
                             "           -    X..........X -             XX    X..X  -       - X.....X -        X.....X  "
                             "      -   X.X           X.X   -           -     X........X  -                   X..X  -    "
                             "   -  X...X  -         X...X         -  X..X           X..X  -           -     X........X  "
                             "-                    XX   -       -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X"
                             " -           -     XXXXXXXXXX  -             -------------       -    X    -           X   "
                             "        -X.....................X-           -------------------                            "
                             "     ----------------------------------- X...XXXXXXXXXXXXX...X -                           "
                             "                                                                      -  X..X           X.."
                             "X  -                                                                                       "
                             "          -   X.X           X.X   -                                                        "
                             "                                         -    XX           XX    -                         "
                             "                  ";
      v17 = (const __m128i *)"..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX-"
                             "     XX          - XX       XX ..-         -X.....X-   X.X   -          X.X          -X...."
                             ".X          -          X.....X-    X..X         -X..X     X..X---         -XXX.XXX-  X...X "
                             " -         X...X         -X....X           -           X....X-    X..X         -X...X   X.."
                             ".XX           -  X.X  - X.....X -        X.....X        -X...X            -            X..."
                             "X-    X..X         - X...X X...X XX          -  X.X  -X.......X-       X.......X       -X.."
                             "X.X           -           X.X..X-    X..X         -  X...X...X  X.X         -  X.X  -XXXX.X"
                             "XXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X-    X..XXX       -   X....."
                             "X   X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X  "
                             " XX-    X..X..XXX    -    X...X    X...X       -  X.X  -   X.X   -    XX    X.X    XX    - "
                             "     X.X        -        X.X      -    X..X..X..XX  -     X.X     X....X      -  X.X  -   X"
                             ".X   -   X.X    X.X    X.X   -       X.X       -       X.X       -    X..X..X..X.X -    X.."
                             ".X    X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X   "
                             "     -XXX X..X..X..X..X-   X.....X   X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X "
                             "-         X.X   XX-XX   X.X         -X..XX........X..X-  X...X...X  X.......X   -  X.X  -  "
                             " X.X   -X.....................X-          X.X X.X-X.X X.X          -X...X...........X- X..."
                             "X X...X X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X    "
                             "       - X..............X-X...X   X...XX.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X"
                             "  -            X...X-X...X            -  X.............X-X..X     X..XX..........X-X.....X-"
                             "   X.X   -   X.X    X.X    X.X   -           X....X-X....X           -  X.............X- XX"
                             "       XX X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X "
                             "         -   X............X--------------X...X..X    ---------   X.X   -          X.X      "
                             "    -          XXXXXXX-XXXXXXX          -   X...........X -             X..X X..X   -      "
                             " -XXXX.XXXX-       XXXX.XXXX       -------------------------------------    X..........X - "
                             "            X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -"
                             "           -    X..........X -             XX    X..X  -       - X.....X -        X.....X  "
                             "      -   X.X           X.X   -           -     X........X  -                   X..X  -    "
                             "   -  X...X  -         X...X         -  X..X           X..X  -           -     X........X  "
                             "-                    XX   -       -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X"
                             " -           -     XXXXXXXXXX  -             -------------       -    X    -           X   "
                             "        -X.....................X-           -------------------                            "
                             "     ----------------------------------- X...XXXXXXXXXXXXX...X -                           "
                             "                                                                      -  X..X           X.."
                             "X  -                                                                                       "
                             "          -   X.X           X.X   -                                                        "
                             "                                         -    XX           XX    -                         "
                             "                  ";
      if ( v13 )
      {
        if ( v13 == 1 )
        {
          si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6920);
          v19 = 27;
          v20 = *(_QWORD *)(v12 + 40) + *(_DWORD *)(v12 + 36) * (v11 + *(_DWORD *)(v12 + 28) * v10);
          do
          {
            if ( v20 > (unsigned __int64)&v17[7].m128i_u64[1] + 1 || (v21 = 0, v20 + 121 < (unsigned __int64)v17) )
            {
              v21 = 64;
              v22 = _mm_loadu_si128(v17 + 1);
              *(__m128i *)v20 = _mm_cmpeq_epi8(si128, _mm_loadu_si128(v17));
              v23 = _mm_cmpeq_epi8(si128, v22);
              v24 = _mm_loadu_si128(v17 + 2);
              *(__m128i *)(v20 + 16) = v23;
              v25 = _mm_cmpeq_epi8(si128, v24);
              v26 = _mm_loadu_si128(v17 + 3);
              *(__m128i *)(v20 + 32) = v25;
              *(__m128i *)(v20 + 48) = _mm_cmpeq_epi8(si128, v26);
            }
            do
            {
              v27 = v21;
              v28 = 0;
              if ( v17->m128i_i8[v21] == 46 )
                v28 = -1;
              ++v21;
              *(_BYTE *)(v20 + v27) = v28;
            }
            while ( v21 < 122 );
            v17 = (const __m128i *)((char *)v17 + 122);
            v20 += *(int *)(v12 + 28);
            --v19;
          }
          while ( v19 );
        }
      }
      else
      {
        v29 = 27;
        v30 = *(_QWORD *)(v12 + 40) + *(_DWORD *)(v12 + 36) * (v11 + *(_DWORD *)(v12 + 28) * v10);
        do
        {
          for ( i = 0; i != 122; i += 2 )
          {
            v32 = 0;
            if ( v17->m128i_i8[i] == 46 )
              v32 = -1;
            *(_DWORD *)(v30 + 4 * i) = v32;
            v33 = 0;
            if ( v17->m128i_i8[i + 1] == 46 )
              v33 = -1;
            *(_DWORD *)(v30 + 4 * i + 4) = v33;
          }
          v17 = (const __m128i *)((char *)v17 + 122);
          v30 += 4LL * *(int *)(v12 + 28);
          --v29;
        }
        while ( v29 );
      }
      v34 = *(_QWORD *)(a1 + 56);
      v35 = *(_DWORD *)(v34 + 24);
      if ( v35 )
      {
        if ( v35 == 1 )
        {
          v36 = _mm_load_si128((const __m128i *)&xmmword_1800E6B50);
          v37 = *(_QWORD *)(v34 + 40) + *(_DWORD *)(v34 + 36) * (*(_DWORD *)(v34 + 28) * v10 + v11 + 123);
          do
          {
            if ( v37 > (unsigned __int64)&v16[7].m128i_u64[1] + 1 || (v38 = 0, v37 + 121 < (unsigned __int64)v16) )
            {
              v38 = 64;
              v39 = _mm_loadu_si128(v16 + 1);
              *(__m128i *)v37 = _mm_cmpeq_epi8(v36, _mm_loadu_si128(v16));
              v40 = _mm_cmpeq_epi8(v36, v39);
              v41 = _mm_loadu_si128(v16 + 2);
              *(__m128i *)(v37 + 16) = v40;
              v42 = _mm_cmpeq_epi8(v36, v41);
              v43 = _mm_loadu_si128(v16 + 3);
              *(__m128i *)(v37 + 32) = v42;
              *(__m128i *)(v37 + 48) = _mm_cmpeq_epi8(v36, v43);
            }
            do
            {
              v44 = v38;
              v45 = 0;
              if ( v16->m128i_i8[v38] == 88 )
                v45 = -1;
              ++v38;
              *(_BYTE *)(v37 + v44) = v45;
            }
            while ( v38 < 122 );
            v16 = (const __m128i *)((char *)v16 + 122);
            v37 += *(int *)(v34 + 28);
            --v4;
          }
          while ( v4 );
        }
      }
      else
      {
        v46 = *(_QWORD *)(v34 + 40) + *(_DWORD *)(v34 + 36) * (*(_DWORD *)(v34 + 28) * v10 + v11 + 123);
        do
        {
          for ( j = 0; j != 122; j += 2 )
          {
            v48 = 0;
            if ( v16->m128i_i8[j] == 88 )
              v48 = -1;
            *(_DWORD *)(v46 + 4 * j) = v48;
            v49 = 0;
            if ( v16->m128i_i8[j + 1] == 88 )
              v49 = -1;
            *(_DWORD *)(v46 + 4 * j + 4) = v49;
          }
          v16 = (const __m128i *)((char *)v16 + 122);
          v46 += 4LL * *(int *)(v34 + 28);
          --v4;
        }
        while ( v4 );
      }
    }
  }
  *(float *)(a1 + 92) = (float)((float)(unsigned __int16)v11 + 0.5) * *(float *)(a1 + 84);
  *(float *)(a1 + 96) = (float)((float)(unsigned __int16)v10 + 0.5) * *(float *)(a1 + 88);
  return (unsigned __int16)v10;
}
