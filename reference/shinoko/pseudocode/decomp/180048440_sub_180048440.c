// sub_180048440 size=1728
__int64 __fastcall sub_180048440(char a1)
{
  __int64 v1; // rbx
  __int64 v3; // rdx
  bool v4; // r12
  unsigned __int8 v5; // r13
  int *v6; // r15
  int v7; // r14d
  unsigned __int8 v8; // r11
  char v9; // cl
  char v10; // di
  int *v11; // r10
  unsigned int v12; // esi
  __int64 v13; // r9
  __int64 v14; // r8
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  __int64 v18; // r10
  float v19; // xmm1_4
  _BYTE *v20; // rax
  __int64 v21; // rcx
  __int64 v22; // r8
  __int64 v23; // r9
  _BYTE *v24; // rdi
  __int64 v25; // r10
  __int64 v26; // rax
  int v27; // eax
  __int64 v28; // r8
  __int64 v29; // r9
  int v30; // r10d
  int v31; // r11d
  int v32; // eax
  unsigned int v33; // ecx
  int v34; // eax
  char v35; // r11
  char v36; // al
  int v37; // ebp
  int v38; // ecx
  int v39; // r8d
  _OWORD *v40; // rsi
  int v41; // r8d
  int v42; // eax
  unsigned int v43; // eax
  __int16 v44; // di
  int v45; // r8d
  int v46; // ecx
  int v47; // ecx
  int v48; // eax
  __int64 v49; // rcx
  __int64 v50; // rax
  int i; // edi
  const char *v52; // rcx
  __int64 result; // rax
  int v54; // ecx
  __int64 v55; // rdx
  int v56; // ecx
  __int128 v57; // [rsp+20h] [rbp-68h]
  int v58; // [rsp+30h] [rbp-58h]
  char v59; // [rsp+90h] [rbp+8h]
  char v60; // [rsp+98h] [rbp+10h]
  char v61; // [rsp+A0h] [rbp+18h]
  char v62; // [rsp+A8h] [rbp+20h]

  v1 = qword_18010C470;
  v3 = qword_18010C470 + 8;
  v4 = a1 && *(_DWORD *)(qword_18010C470 + 10744) == 1;
  v5 = 0;
  v6 = (int *)(qword_18010C470 + 5080);
  v58 = 0;
  v7 = 0;
  v57 = 0;
  if ( *(int *)(qword_18010C470 + 5080) > 0 )
  {
    v8 = 0;
    v61 = 0;
    v9 = 0;
    v60 = 0;
    v10 = 0;
    v62 = 0;
    v59 = 0;
    v11 = (int *)(qword_18010C470 + 2992);
    v12 = 0;
    do
    {
      v13 = *(_QWORD *)(v1 + 5088);
      v14 = 28LL * v7;
      v15 = *(_DWORD *)(v13 + v14);
      if ( v15 == 1 )
      {
        if ( !*(_BYTE *)(v1 + 179) )
        {
          if ( a1 )
          {
            v16 = (unsigned __int8)(v10 | v61);
            v3 = v16 | v8 | v12;
            if ( v16 | v8 | v12 )
              break;
          }
          v17 = *(_DWORD *)(v13 + v14 + 12);
          v5 = 1;
          *(_DWORD *)(v1 + 228) = *(_DWORD *)(v13 + v14 + 16);
          *(_DWORD *)(v1 + 224) = v17;
          *(_DWORD *)(v1 + 248) = *(_DWORD *)(v13 + v14 + 20);
        }
      }
      else if ( v15 == 3 )
      {
        v18 = *(int *)(v13 + v14 + 12);
        if ( a1 )
        {
          v3 = v8 | v12 & (1 << v18);
          if ( v8 | v12 & (1 << v18) || *(_DWORD *)(v13 + v14 + 20) == 1 && v5 )
            break;
        }
        v12 |= 1 << v18;
        *(_BYTE *)(v1 + v18 + 232) = *(_BYTE *)(v13 + v14 + 16);
        v11 = (int *)(v1 + 2992);
        *(_DWORD *)(v1 + 248) = *(_DWORD *)(v13 + v14 + 20);
      }
      else if ( v15 == 2 )
      {
        if ( a1 && v12 | v5 )
          break;
        v8 = 1;
        v19 = *(float *)(v1 + 240);
        v60 = 1;
        *(float *)(v1 + 244) = *(float *)(v1 + 244) + *(float *)(v13 + v14 + 12);
        *(float *)(v1 + 240) = v19 + *(float *)(v13 + v14 + 16);
        *(_DWORD *)(v1 + 248) = *(_DWORD *)(v13 + v14 + 20);
      }
      else if ( v15 == 4 )
      {
        if ( (*(_BYTE *)v3 & 0x40) == 0 )
        {
          v20 = (_BYTE *)sub_180034F60(*(unsigned int *)(v13 + v14 + 12));
          v24 = v20;
          v25 = (__int64)&v20[-v1 - 260] >> 4;
          if ( a1 )
          {
            v21 = *(unsigned __int8 *)(v23 + v22 + 16);
            if ( *v20 != (_BYTE)v21 )
            {
              v21 = (unsigned int)v25;
              v26 = (__int64)(int)v25 >> 5;
              v3 = v12 | *((_DWORD *)&v57 + v26) & (1 << v25);
              if ( v12 | *((_DWORD *)&v57 + v26) & (1 << v25) )
                break;
            }
          }
          if ( (v27 = sub_180047200(v21, v3, v22), v32 = v31 | v27, (v32 & 0x1000) != 0) && (v32 & 0x4000) == 0
            || *(_BYTE *)(qword_18010C470 + 89) && (v32 & 0x1000) != 0 )
          {
            LOBYTE(v3) = 0;
          }
          else
          {
            v3 = v32 & 0xFFFF0FFF;
            if ( (v32 & 0xFFFF0FFF) != 0 )
            {
              v33 = v32 & 0x1F;
              v34 = *(_DWORD *)(qword_18010C470 + 4 * (((int)v3 - 512LL) >> 5) + 5440);
              LOBYTE(v3) = _bittest(&v34, v33);
            }
          }
          if ( v4 && v59 && !(_BYTE)v3 )
            break;
          v35 = *(_BYTE *)(v29 + v28 + 16);
          if ( *v24 != v35 )
          {
            v61 = 1;
            *((_DWORD *)&v57 + ((__int64)v30 >> 5)) |= 1 << (v30 & 0x1F);
            if ( v4 )
            {
              v36 = v62;
              if ( !(_BYTE)v3 )
                v36 = 1;
              v62 = v36;
            }
          }
          *v24 = v35;
          v11 = (int *)(v1 + 2992);
          v8 = v60;
          *((_DWORD *)v24 + 3) = *(_DWORD *)(v29 + v28 + 20);
LABEL_43:
          v10 = v59;
        }
      }
      else
      {
        if ( v15 != 5 )
        {
          if ( v15 == 6 )
            *(_BYTE *)(v1 + 2988) = *(_BYTE *)(v13 + v14 + 12) == 0;
          goto LABEL_44;
        }
        if ( (*(_BYTE *)v3 & 0x40) == 0 )
        {
          if ( a1 )
          {
            if ( (unsigned __int8)(v8 | v5) | v12 )
              break;
            v9 = v62;
          }
          if ( v4 && v9 )
            break;
          v43 = *(_DWORD *)(v13 + v14 + 12);
          v44 = -3;
          v45 = *(_DWORD *)(v1 + 2996);
          v46 = *v11;
          if ( v43 <= 0xFFFF )
            v44 = v43;
          if ( v46 == v45 )
          {
            v47 = v46 + 1;
            if ( v45 )
              v48 = v45 + v45 / 2;
            else
              v48 = 8;
            if ( v48 > v47 )
              v47 = v48;
            sub_180054650(v11, (unsigned int)v47);
            v8 = v60;
            v11 = (int *)(v1 + 2992);
          }
          *(_WORD *)(*(_QWORD *)(v1 + 3000) + 2LL * (*v11)++) = v44;
          if ( v4 )
          {
            v10 = 1;
            v59 = 1;
            goto LABEL_44;
          }
          goto LABEL_43;
        }
      }
LABEL_44:
      v9 = v62;
      v3 = v1 + 8;
      ++v7;
    }
    while ( v7 < *v6 );
  }
  v37 = 0;
  if ( v7 <= 0 )
  {
    if ( !v7 )
      goto LABEL_81;
  }
  else
  {
    do
    {
      v38 = *(_DWORD *)(v1 + 5100);
      v39 = *(_DWORD *)(v1 + 5096);
      v40 = (_OWORD *)(*(_QWORD *)(v1 + 5088) + 28LL * (unsigned int)v37);
      if ( v39 == v38 )
      {
        v41 = v39 + 1;
        if ( v38 )
          v42 = v38 + v38 / 2;
        else
          v42 = 8;
        if ( v42 > v41 )
          v41 = v42;
        sub_180054B50(v1 + 5096, (unsigned int)v41);
      }
      ++v37;
      v49 = 28LL * *(int *)(v1 + 5096);
      v50 = *(_QWORD *)(v1 + 5104);
      *(_OWORD *)(v49 + v50) = *v40;
      *(_OWORD *)(v49 + v50 + 12) = *(_OWORD *)((char *)v40 + 12);
      ++*(_DWORD *)(v1 + 5096);
    }
    while ( v37 < v7 );
  }
  if ( *(char *)(v1 + 10228) < 0 )
  {
    for ( i = 0; i < *v6; ++i )
    {
      v52 = "Remaining";
      if ( i < v7 )
        v52 = "Processed";
      sub_1800481D0(v52, (float *)(*(_QWORD *)(v1 + 5088) + 28LL * i));
    }
  }
LABEL_81:
  result = *v6;
  if ( v7 == (_DWORD)result )
  {
    v54 = *(_DWORD *)(v1 + 5084);
    if ( v54 < 0 )
    {
      v55 = 0;
      v56 = v54 / 2 + v54;
      if ( v56 > 0 )
        v55 = (unsigned int)v56;
      result = sub_180054B50(v1 + 5080, v55);
    }
    *v6 = 0;
  }
  else
  {
    result = sub_1800B8BD0(*(_QWORD *)(v1 + 5088), *(_QWORD *)(v1 + 5088) + 28LL * v7, 28 * (result - v7));
    *v6 -= v7;
  }
  if ( *(_BYTE *)(v1 + 2988) )
  {
    result = sub_1800357D0(v1 + 8, v3);
    *(_BYTE *)(v1 + 2564) = 0;
    *(_DWORD *)(v1 + 2568) = -1082130432;
    *(_DWORD *)(v1 + 2572) = -1082130432;
    *(_BYTE *)(v1 + 2580) = 0;
    *(_DWORD *)(v1 + 2584) = -1082130432;
    *(_DWORD *)(v1 + 2588) = -1082130432;
    *(_BYTE *)(v1 + 2596) = 0;
    *(_DWORD *)(v1 + 2600) = -1082130432;
    *(_DWORD *)(v1 + 2604) = -1082130432;
    *(_BYTE *)(v1 + 2612) = 0;
    *(_DWORD *)(v1 + 2616) = -1082130432;
    *(_DWORD *)(v1 + 2620) = -1082130432;
    *(_BYTE *)(v1 + 2628) = 0;
    *(_DWORD *)(v1 + 2632) = -1082130432;
    *(_DWORD *)(v1 + 2636) = -1082130432;
    *(_BYTE *)(v1 + 2644) = 0;
    *(_DWORD *)(v1 + 2648) = -1082130432;
    *(_DWORD *)(v1 + 2652) = -1082130432;
    *(_BYTE *)(v1 + 2660) = 0;
    *(_DWORD *)(v1 + 2664) = -1082130432;
    *(_DWORD *)(v1 + 2668) = -1082130432;
    *(_DWORD *)(v1 + 224) = -8388609;
    *(_DWORD *)(v1 + 228) = -8388609;
    *(_DWORD *)(v1 + 232) = 0;
    *(_DWORD *)(v1 + 2944) = -1082130432;
    *(_DWORD *)(v1 + 2924) = -1082130432;
    *(_DWORD *)(v1 + 2948) = -1082130432;
    *(_DWORD *)(v1 + 2928) = -1082130432;
    *(_DWORD *)(v1 + 2952) = -1082130432;
    *(_DWORD *)(v1 + 2932) = -1082130432;
    *(_DWORD *)(v1 + 2956) = -1082130432;
    *(_DWORD *)(v1 + 2936) = -1082130432;
    *(_BYTE *)(v1 + 236) = 0;
    *(_DWORD *)(v1 + 2960) = -1082130432;
    *(_DWORD *)(v1 + 2940) = -1082130432;
    *(_QWORD *)(v1 + 240) = 0;
  }
  return result;
}
