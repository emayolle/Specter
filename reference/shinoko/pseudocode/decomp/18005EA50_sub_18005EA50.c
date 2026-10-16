// sub_18005EA50 size=1465
char __fastcall sub_18005EA50(__int64 a1)
{
  __int64 v1; // r8
  __int64 v2; // r12
  _DWORD *v3; // rdx
  int v4; // ecx
  int v5; // r14d
  int v6; // edi
  int v7; // ecx
  int v8; // esi
  int v9; // ebx
  int v10; // eax
  int v11; // r12d
  int v12; // eax
  int v13; // eax
  int v14; // r13d
  int v15; // r15d
  float v16; // xmm0_4
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  __int64 v22; // rbx
  __int64 v23; // rcx
  __int64 v24; // rdi
  __int64 v25; // rax
  void (__fastcall *v26)(__int64, __int64); // r8
  __int64 *v27; // r14
  __int64 v28; // rax
  __int64 *v29; // r15
  __int64 v30; // rdi
  _QWORD *v31; // rbx
  _QWORD *i; // rsi
  int v33; // r8d
  int v34; // r9d
  __int64 v35; // rcx
  __int64 v36; // rax
  __int64 v37; // rdx
  _QWORD *v38; // r13
  _QWORD *v39; // r12
  __int64 v40; // rbx
  __int64 v41; // rax
  unsigned __int64 v42; // rdx
  __int64 v43; // rdi
  unsigned __int64 v44; // rdx
  __int64 *v45; // r14
  __int64 *v46; // r15
  unsigned __int16 *v47; // rsi
  unsigned int v48; // ebx
  _OWORD v50[3]; // [rsp+30h] [rbp-D0h] BYREF
  __int128 v51; // [rsp+60h] [rbp-A0h]
  __int128 v52; // [rsp+70h] [rbp-90h]
  __int128 v53; // [rsp+80h] [rbp-80h]
  __int128 v54; // [rsp+90h] [rbp-70h]
  __int128 v55; // [rsp+A0h] [rbp-60h]
  __int128 v56; // [rsp+B0h] [rbp-50h]
  __int128 v57; // [rsp+F0h] [rbp-10h]
  __int128 v58; // [rsp+110h] [rbp+10h]
  __int128 v59; // [rsp+120h] [rbp+20h]
  __int128 v60; // [rsp+130h] [rbp+30h]

  v1 = *(_QWORD *)(a1 + 56);
  v2 = a1;
  if ( v1 && *(_DWORD *)(v1 + 24) != *(_DWORD *)(a1 + 4) )
  {
    v3 = *(_DWORD **)(a1 + 688);
    v4 = (*(_DWORD *)(a1 + 12) - 1)
       | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
       | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)
       | (((*(_DWORD *)(a1 + 12) - 1)
         | ((*(_DWORD *)(a1 + 12) - 1) >> 1)
         | (((*(_DWORD *)(a1 + 12) - 1) | ((*(_DWORD *)(a1 + 12) - 1) >> 1)) >> 2)) >> 4);
    v5 = v4 | (v4 >> 8) | ((v4 | (v4 >> 8)) >> 16);
    v6 = v5 + 1;
    v7 = (*(_DWORD *)(v2 + 16) - 1)
       | ((*(_DWORD *)(v2 + 16) - 1) >> 1)
       | (((*(_DWORD *)(v2 + 16) - 1) | ((*(_DWORD *)(v2 + 16) - 1) >> 1)) >> 2)
       | (((*(_DWORD *)(v2 + 16) - 1)
         | ((*(_DWORD *)(v2 + 16) - 1) >> 1)
         | (((*(_DWORD *)(v2 + 16) - 1) | ((*(_DWORD *)(v2 + 16) - 1) >> 1)) >> 2)) >> 4);
    v8 = v7 | (v7 >> 8) | ((v7 | (v7 >> 8)) >> 16);
    v9 = v8 + 1;
    if ( v3 && *(_DWORD *)(v1 + 4) != 4 )
    {
      v10 = (v3[42] - 1)
          | ((v3[42] - 1) >> 1)
          | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)
          | (((v3[42] - 1) | ((v3[42] - 1) >> 1) | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)) >> 4)
          | (((v3[42] - 1)
            | ((v3[42] - 1) >> 1)
            | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)
            | (((v3[42] - 1) | ((v3[42] - 1) >> 1) | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)) >> 4)) >> 8);
      if ( (v10 | (v10 >> 16)) + 1 >= v6 )
        v5 = v10
           | (((v3[42] - 1)
             | ((v3[42] - 1) >> 1)
             | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)
             | (((v3[42] - 1) | ((v3[42] - 1) >> 1) | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)) >> 4)
             | (((v3[42] - 1)
               | ((v3[42] - 1) >> 1)
               | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)
               | (((v3[42] - 1) | ((v3[42] - 1) >> 1) | (((v3[42] - 1) | ((v3[42] - 1) >> 1)) >> 2)) >> 4)) >> 8)) >> 16);
      v11 = v5 + 1;
      v12 = (v3[43] - 1) | ((v3[43] - 1) >> 1) | (((v3[43] - 1) | ((v3[43] - 1) >> 1)) >> 2);
      v13 = v12 | (v12 >> 4) | ((v12 | (v12 >> 4)) >> 8);
      if ( (v13 | (v13 >> 16)) + 1 >= v9 )
        v8 = v13 | (v13 >> 16);
      v14 = v3[38] - v3[40];
      v15 = v8 + 1;
      if ( (float)v14 < 0.0 )
        v16 = sub_1800B7240();
      else
        v16 = fsqrt((float)v14);
      v17 = ((int)v16 - 1)
          | (((int)v16 - 1) >> 1)
          | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)
          | ((((int)v16 - 1) | (((int)v16 - 1) >> 1) | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)) >> 4)
          | ((((int)v16 - 1)
            | (((int)v16 - 1) >> 1)
            | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)
            | ((((int)v16 - 1) | (((int)v16 - 1) >> 1) | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)) >> 4)) >> 8)
          | ((((int)v16 - 1)
            | (((int)v16 - 1) >> 1)
            | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)
            | ((((int)v16 - 1) | (((int)v16 - 1) >> 1) | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)) >> 4)
            | ((((int)v16 - 1)
              | (((int)v16 - 1) >> 1)
              | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)
              | ((((int)v16 - 1) | (((int)v16 - 1) >> 1) | ((((int)v16 - 1) | (((int)v16 - 1) >> 1)) >> 2)) >> 4)) >> 8)) >> 16);
      v18 = *(_DWORD *)a1 & 1;
      v19 = v17 + 1;
      if ( v11 < v15 )
      {
        if ( v15 >= v19 )
          v17 = v8;
        if ( !v18 )
        {
          v21 = v17 | (v17 >> 1) | ((v17 | (v17 >> 1)) >> 2) | ((v17 | (v17 >> 1) | ((v17 | (v17 >> 1)) >> 2)) >> 4);
          v17 = v21 | (v21 >> 8) | ((v21 | (v21 >> 8)) >> 16);
        }
        v9 = v17 + 1;
        v6 = (v17 + v14) / (v17 + 1);
        if ( v11 >= v6 )
          v6 = v5 + 1;
      }
      else
      {
        if ( v11 >= v19 )
          v17 = v5;
        v6 = v17 + 1;
        v9 = (v17 + v14) / (v17 + 1);
        if ( v15 >= v9 )
          v9 = v8 + 1;
        if ( !v18 )
        {
          v20 = (v9 - 1)
              | ((v9 - 1) >> 1)
              | (((v9 - 1) | ((v9 - 1) >> 1)) >> 2)
              | (((v9 - 1) | ((v9 - 1) >> 1) | (((v9 - 1) | ((v9 - 1) >> 1)) >> 2)) >> 4);
          v9 = (v20 | (v20 >> 8) | ((v20 | (v20 >> 8)) >> 16)) + 1;
        }
      }
      v2 = a1;
    }
    sub_180061B10(v2);
    sub_180060520(v2, (unsigned int)v6, (unsigned int)v9);
    sub_180061380(v2);
    v22 = *(_QWORD *)(v2 + 128);
    v23 = 144LL * *(int *)(v2 + 120);
    v24 = v23 + v22;
    if ( v23 )
    {
      do
      {
        v25 = *(_QWORD *)(v22 + 128);
        if ( !v25 )
          v25 = *(_QWORD *)(v2 + 696);
        v26 = *(void (__fastcall **)(__int64, __int64))(v25 + 24);
        if ( v26 )
          v26(v2, v22);
        v22 += 144;
      }
      while ( v22 != v24 );
    }
    v27 = *(__int64 **)(v2 + 112);
    v28 = *(int *)(v2 + 104);
    v29 = &v27[v28];
    if ( v28 * 8 )
    {
      do
      {
        v30 = *v27;
        v31 = *(_QWORD **)(*v27 + 40);
        for ( i = &v31[*(int *)(*v27 + 32)]; v31 != i; ++v31 )
          sub_18005FA90(v2, v30, *v31);
        ++v27;
      }
      while ( v27 != v29 );
    }
  }
  if ( !*(_QWORD *)(v2 + 688) )
    sub_180061380(v2);
  if ( !*(_DWORD *)(v2 + 120) )
  {
    v57 = 0;
    BYTE4(v57) = 1;
    v58 = 0;
    DWORD2(v57) = 0;
    HIDWORD(v58) = 2139095039;
    v59 = 0;
    HIDWORD(v59) = 1065353216;
    v51 = v57;
    WORD4(v51) = 257;
    v60 = 0;
    LODWORD(v60) = 1065353216;
    v53 = v58;
    BYTE6(v51) = 1;
    memset(v50, 0, sizeof(v50));
    v55 = v60;
    v52 = 0;
    v54 = v59;
    v56 = 0;
    HIDWORD(v51) = 1095761920;
    sub_180035ED0(v50, 40, "ProggyClean.ttf");
    WORD5(v51) = 133;
    *((float *)&v53 + 1) = *((float *)&v53 + 1) + (float)(int)(float)(*((float *)&v51 + 3) / 13.0);
    sub_18005E700(v2, (unsigned int)&unk_1800D6040, v33, v34, (__int64)v50);
  }
  v35 = *(_QWORD *)(v2 + 680);
  v36 = 8LL * *(int *)(v2 + 672);
  v37 = v36 + v35;
  if ( v36 )
  {
    while ( 1 )
    {
      v36 = *(_QWORD *)(*(_QWORD *)v35 + 104LL);
      if ( v36 )
        break;
      v35 += 8;
      if ( v35 == v37 )
        goto LABEL_45;
    }
    LOBYTE(v36) = (*(_DWORD *)(v36 + 12) & 0x10) != 0;
    *(_BYTE *)(v2 + 81) = v36;
  }
LABEL_45:
  if ( !*(_BYTE *)(v2 + 81) )
  {
    *(_BYTE *)(*(_QWORD *)(v2 + 688) + 185LL) = 1;
    v38 = *(_QWORD **)(v2 + 112);
    v36 = 8LL * *(int *)(v2 + 104);
    if ( v36 )
    {
      v39 = (_QWORD *)((char *)v38 + v36);
      do
      {
        v40 = *v38;
        v41 = sub_180066070(*v38);
        v42 = *(unsigned __int16 *)(v40 + 50);
        v43 = v41;
        if ( (_WORD)v42 && (v42 >= *(int *)(v41 + 32) || *(_WORD *)(*(_QWORD *)(v41 + 40) + 2 * v42) == 0xFFFF) )
          sub_180062410(v41, v42, 0);
        v44 = *(unsigned __int16 *)(v40 + 48);
        if ( (_WORD)v44 && (v44 >= *(int *)(v43 + 32) || *(_WORD *)(*(_QWORD *)(v43 + 40) + 2 * v44) == 0xFFFF) )
          sub_180062410(v43, v44, 0);
        v45 = *(__int64 **)(v40 + 40);
        v36 = *(int *)(v40 + 32);
        v46 = &v45[v36];
        if ( v45 != v46 )
        {
          while ( 1 )
          {
            v36 = *v45;
            v47 = *(unsigned __int16 **)(*v45 + 64);
            if ( !v47 )
              break;
            if ( *v47 )
              goto LABEL_61;
LABEL_68:
            if ( ++v45 == v46 )
              goto LABEL_69;
          }
          v47 = (unsigned __int16 *)&unk_1800DA3C4;
          do
          {
LABEL_61:
            v48 = *v47;
            if ( (unsigned __int16)v48 <= v47[1] )
            {
              do
              {
                if ( v48 > 0xFFFF )
                  break;
                if ( (unsigned __int16)v48 >= (unsigned __int64)*(int *)(v43 + 32)
                  || *(_WORD *)(*(_QWORD *)(v43 + 40) + 2LL * (unsigned __int16)v48) == 0xFFFF )
                {
                  sub_180062410(v43, (unsigned __int16)v48, 0);
                }
                LODWORD(v36) = v47[1];
                ++v48;
              }
              while ( v48 <= (unsigned int)v36 );
            }
            v47 += 2;
          }
          while ( *v47 );
          goto LABEL_68;
        }
LABEL_69:
        ++v38;
      }
      while ( v38 != v39 );
      v2 = a1;
    }
  }
  *(_BYTE *)(v2 + 82) = 1;
  return v36;
}
