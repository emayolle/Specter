// sub_180061CF0 size=1817
__int64 __fastcall sub_180061CF0(__int64 a1, int a2, int a3, unsigned int *a4)
{
  int v4; // r9d
  __int64 v5; // r14
  int v6; // eax
  int v7; // r15d
  int v8; // ecx
  int v9; // eax
  int v10; // r9d
  int v11; // r10d
  int v12; // r15d
  int *v13; // r12
  int **v14; // r11
  int v15; // ebx
  int v16; // r13d
  int **v17; // rdx
  int v18; // r9d
  int v19; // edi
  int v20; // esi
  int **v21; // r8
  int v22; // ecx
  int v23; // eax
  int v24; // ebp
  int *v25; // r11
  int v26; // r10d
  int v27; // eax
  int v28; // r8d
  int v29; // ecx
  int v30; // ebx
  int *v31; // r8
  int v32; // edx
  int v33; // ecx
  int v34; // r12d
  int *v35; // rdx
  int *v36; // rbp
  int v37; // r8d
  int v38; // ecx
  int v39; // r15d
  int v40; // edi
  int **v41; // rcx
  int v42; // r11d
  int v43; // r14d
  int v44; // ebx
  _DWORD *v45; // r9
  int v46; // r10d
  int v47; // ecx
  int v48; // eax
  int v49; // eax
  int v50; // esi
  _DWORD *v51; // r8
  int v52; // edx
  int v53; // r9d
  __int64 v54; // r8
  __int64 v55; // rax
  int *v56; // rax
  int *v57; // rcx
  __int64 v58; // rdx
  int v59; // edi
  __int64 v60; // rbp
  __int64 v61; // rbx
  int v63; // edx
  int v64; // edx
  int v65; // r8d
  int v66; // ecx
  int v67; // ecx
  int v68; // eax
  __int64 v69; // rcx
  __int64 v70; // rax
  int v71; // esi
  __int64 v72; // rdi
  unsigned int v73; // ecx
  __int64 v74; // rdx
  unsigned int *v75; // r8
  unsigned int v76; // ecx
  unsigned int v77; // eax
  int i; // [rsp+20h] [rbp-D8h]
  int **v79; // [rsp+28h] [rbp-D0h]
  int v80; // [rsp+30h] [rbp-C8h]
  int v81; // [rsp+34h] [rbp-C4h]
  int v82; // [rsp+38h] [rbp-C0h]
  int v83; // [rsp+3Ch] [rbp-BCh]
  int v84; // [rsp+40h] [rbp-B8h]
  int **v85; // [rsp+48h] [rbp-B0h]
  int *v86; // [rsp+48h] [rbp-B0h]
  int *v87; // [rsp+50h] [rbp-A8h]
  int v88; // [rsp+60h] [rbp-98h]
  int v89; // [rsp+64h] [rbp-94h]
  int v90; // [rsp+68h] [rbp-90h]
  int **v91; // [rsp+88h] [rbp-70h]
  __int64 v92; // [rsp+90h] [rbp-68h]
  int **v93; // [rsp+98h] [rbp-60h]

  v4 = *(_DWORD *)(a1 + 8);
  v5 = *(_QWORD *)(a1 + 688);
  v6 = a2;
  v7 = v4 + a2;
  v90 = v4;
  v8 = *(_DWORD *)(v5 + 172);
  if ( *(_DWORD *)(v5 + 168) >= a2 )
    v6 = *(_DWORD *)(v5 + 168);
  v92 = v5;
  *(_DWORD *)(v5 + 168) = v6;
  v9 = a3;
  v84 = 3;
  if ( v8 >= a3 )
    v9 = v8;
  v82 = v4 + a2;
  v10 = a3 + v4;
  *(_DWORD *)(v5 + 172) = v9;
  for ( i = v10; ; v10 = i )
  {
    if ( !v7 || !v10 )
    {
      LOWORD(v34) = 0;
      LOWORD(v16) = 0;
LABEL_97:
      v60 = a1;
LABEL_98:
      v63 = v90 + (unsigned __int16)a2 + (unsigned __int16)v34;
      if ( *(_DWORD *)(v5 + 176) >= v63 )
        v63 = *(_DWORD *)(v5 + 176);
      *(_DWORD *)(v5 + 176) = v63;
      v64 = v90 + (unsigned __int16)a3 + (unsigned __int16)v16;
      if ( *(_DWORD *)(v5 + 180) >= v64 )
        v64 = *(_DWORD *)(v5 + 180);
      ++*(_DWORD *)(v5 + 148);
      *(_DWORD *)(v5 + 180) = v64;
      *(_DWORD *)(v5 + 152) += i * v7;
      v65 = *(_DWORD *)(v5 + 100);
      v66 = *(_DWORD *)(v5 + 96);
      if ( v66 == v65 )
      {
        v67 = v66 + 1;
        if ( v65 )
          v68 = v65 + v65 / 2;
        else
          v68 = 8;
        if ( v68 > v67 )
          v67 = v68;
        sub_180054080(v5 + 96, (unsigned int)v67);
      }
      v69 = *(int *)(v5 + 96);
      v70 = *(_QWORD *)(v5 + 104);
      *(_WORD *)(v70 + 8 * v69) = v34;
      *(_WORD *)(v70 + 8 * v69 + 2) = v16;
      *(_WORD *)(v70 + 8 * v69 + 4) = a2;
      *(_WORD *)(v70 + 8 * v69 + 6) = a3;
      v71 = *(_DWORD *)(v5 + 96);
      *(_DWORD *)(v5 + 96) = v71 + 1;
      v72 = *(_QWORD *)(v60 + 688);
      if ( a4 )
      {
        v73 = (*(_DWORD *)(v72 + 96) - 1) ^ (*a4 ^ (*(_DWORD *)(v72 + 96) - 1)) & 0xFFF00000;
        *a4 = v73;
        return (((v73 >> 20) & 0x3FF) << 20)
             | (unsigned int)(((__int64)a4 - *(_QWORD *)(*(_QWORD *)(v60 + 688) + 120LL)) >> 2);
      }
      else
      {
        v74 = *(int *)(v72 + 144);
        if ( (int)v74 >= 0 )
        {
          v75 = (unsigned int *)(*(_QWORD *)(v72 + 120) + 4 * v74);
          *(_DWORD *)(v72 + 144) = (int)(*v75 << 12) >> 12;
          v76 = *v75;
        }
        else
        {
          sub_180068EA0(v72 + 112, (unsigned int)(*(_DWORD *)(v72 + 112) + 1));
          LODWORD(v74) = *(_DWORD *)(v72 + 112) - 1;
          v75 = (unsigned int *)(*(_QWORD *)(v72 + 120) + 4LL * (int)v74);
          v76 = 0;
        }
        v77 = v71 ^ (v76 ^ v71) & 0xFFF00000 | 0x40000000;
        *v75 = v77;
        return (unsigned int)v74 | (((v77 >> 20) & 0x3FF) << 20);
      }
    }
    v11 = *(_DWORD *)v5;
    v88 = *(_DWORD *)v5;
    v12 = *(_DWORD *)(v5 + 8) + v7 - 1 - (*(_DWORD *)(v5 + 8) + v7 - 1) % *(_DWORD *)(v5 + 8);
    v80 = v12;
    if ( v12 > *(_DWORD *)v5 || (v83 = *(_DWORD *)(v5 + 4), v10 > v83) )
    {
      v34 = 0;
      v16 = 0;
LABEL_79:
      v7 = v82;
      v14 = nullptr;
LABEL_80:
      if ( !v14 )
        goto LABEL_84;
      goto LABEL_81;
    }
    v13 = *(int **)(v5 + 24);
    v14 = nullptr;
    v91 = (int **)(v5 + 24);
    v15 = 0x40000000;
    v79 = nullptr;
    v81 = 0x40000000;
    v16 = 0x40000000;
    v89 = *v13;
    v87 = v13;
    if ( v12 + *v13 > v11 )
      goto LABEL_37;
    v17 = (int **)(v5 + 24);
    v85 = (int **)(v5 + 24);
    do
    {
      v18 = 0;
      v19 = 0;
      v93 = v14;
      v20 = 0;
      v21 = v14;
      v22 = v16;
      v23 = v16;
      v24 = *v13 + v12;
      v25 = v13;
      if ( *v13 < v24 )
      {
        do
        {
          v26 = v25[1];
          if ( v26 <= v18 )
          {
            v31 = *((int **)v25 + 1);
            v32 = v12 - v20;
            v30 = *v31;
            v33 = *v31 - *v25;
            v25 = v31;
            if ( v33 + v20 <= v12 )
              v32 = v33;
            v20 += v32;
            v28 = v32 * (v18 - v26);
          }
          else
          {
            v27 = *v25;
            v25 = *((int **)v25 + 1);
            v28 = v20 * (v26 - v18);
            v29 = *v13;
            v18 = v26;
            v30 = *v25;
            if ( v27 >= *v13 )
              v29 = v27;
            v20 += v30 - v29;
          }
          v19 += v28;
        }
        while ( v30 < v24 );
        v17 = v85;
        v23 = v16;
        v21 = v93;
        v22 = v16;
        v11 = v88;
        v15 = v81;
      }
      v5 = v92;
      if ( *(_DWORD *)(v92 + 16) )
      {
        if ( v18 + i <= *(_DWORD *)(v92 + 4) && (v18 < v16 || v18 == v16 && v19 < v15) )
        {
          v15 = v19;
          v79 = v17;
          v81 = v19;
          v16 = v18;
          v14 = v17;
        }
        else
        {
          v14 = v79;
        }
      }
      else
      {
        v16 = v18;
        v14 = v17;
        if ( v18 >= v23 )
          v16 = v23;
        if ( v18 >= v22 )
          v14 = v21;
        v79 = v14;
      }
      v17 = (int **)(v13 + 2);
      v13 = *((int **)v13 + 1);
      v85 = v17;
    }
    while ( v12 + *v13 <= v11 );
    if ( v14 )
      v34 = **v14;
    else
LABEL_37:
      v34 = 0;
    if ( *(_DWORD *)(v5 + 16) == 1 )
    {
      v35 = v87;
      v36 = v87;
      v86 = v87;
      if ( v89 < v12 )
      {
        do
          v35 = *((int **)v35 + 1);
        while ( *v35 < v12 );
        v87 = v35;
      }
      v37 = v83;
      v38 = v12;
      do
      {
        v39 = *v35;
        v40 = *v35 - v38;
        if ( **((_DWORD **)v36 + 1) <= v40 )
        {
          do
          {
            v41 = (int **)(v36 + 2);
            v36 = *((int **)v36 + 1);
            v91 = v41;
          }
          while ( **((_DWORD **)v36 + 1) <= v40 );
          v38 = v80;
          v86 = v36;
        }
        v42 = 0;
        v43 = 0;
        v44 = 0;
        v45 = v36;
        if ( *v36 < v39 )
        {
          do
          {
            v46 = v45[1];
            if ( v46 <= v42 )
            {
              v51 = *((_DWORD **)v45 + 1);
              v50 = *v51;
              v52 = *v51 - *v45;
              v45 = v51;
              if ( v52 + v44 > v80 )
                v52 = v80 - v44;
              v43 += v52 * (v42 - v46);
              v44 += v52;
            }
            else
            {
              v47 = v40;
              v48 = v46 - v42;
              v42 = v45[1];
              v43 += v44 * v48;
              v49 = *v45;
              v45 = *((_DWORD **)v45 + 1);
              if ( v49 >= v40 )
                v47 = v49;
              v50 = *v45;
              v44 += *v45 - v47;
            }
          }
          while ( v50 < v39 );
          v36 = v86;
          v38 = v80;
          v35 = v87;
          v37 = v83;
        }
        v53 = i;
        if ( v42 + i <= v37 && v42 <= v16 && (v42 < v16 || v43 < v81 || v43 == v81 && v40 < v34) )
        {
          v16 = v42;
          v81 = v43;
          v14 = v91;
          v34 = v40;
          v79 = v91;
        }
        else
        {
          v14 = v79;
        }
        v35 = *((int **)v35 + 1);
        v87 = v35;
      }
      while ( v35 );
      v5 = v92;
    }
    else
    {
      v53 = i;
    }
    if ( !v14 )
      goto LABEL_79;
    if ( v53 + v16 > *(_DWORD *)(v5 + 4) )
      goto LABEL_79;
    v54 = *(_QWORD *)(v5 + 32);
    if ( !v54 )
      goto LABEL_79;
    *(_DWORD *)(v54 + 4) = v53 + v16;
    v55 = *(_QWORD *)(v54 + 8);
    *(_DWORD *)v54 = v34;
    *(_QWORD *)(v5 + 32) = v55;
    v56 = *v14;
    if ( **v14 >= v34 )
    {
      v57 = *v14;
      *v14 = (int *)v54;
    }
    else
    {
      v57 = *((int **)v56 + 1);
      *((_QWORD *)v56 + 1) = v54;
    }
    v7 = v82;
    if ( *((_QWORD *)v57 + 1) )
    {
      do
      {
        v58 = *((_QWORD *)v57 + 1);
        if ( *(_DWORD *)v58 > v34 + v82 )
          break;
        *((_QWORD *)v57 + 1) = *(_QWORD *)(v5 + 32);
        *(_QWORD *)(v5 + 32) = v57;
        v57 = (int *)v58;
      }
      while ( *(_QWORD *)(v58 + 8) );
    }
    *(_QWORD *)(v54 + 8) = v57;
    if ( *v57 >= v34 + v82 )
      goto LABEL_80;
    *v57 = v34 + v82;
LABEL_81:
    if ( v34 != 0x7FFFFFFF )
      goto LABEL_97;
    if ( v16 != 0x7FFFFFFF )
    {
      LOWORD(v34) = -1;
      goto LABEL_97;
    }
LABEL_84:
    v59 = v84;
    if ( !v84 || *(_BYTE *)(v5 + 184) )
      break;
    v60 = a1;
    v61 = *(_QWORD *)(a1 + 688);
    sub_180060330(a1, 2);
    if ( (float)((float)*(int *)(v61 + 152) * 0.2) <= (float)*(int *)(v61 + 160) )
      sub_1800607D0(a1, *(_DWORD *)(*(_QWORD *)(a1 + 56) + 28LL), *(_DWORD *)(*(_QWORD *)(a1 + 56) + 32LL));
    else
      sub_180061010(a1, 0xFFFFFFFFLL, 0xFFFFFFFFLL);
    --v84;
    if ( v59 - 1 < 0 )
    {
      LOWORD(v34) = -1;
      LOWORD(v16) = -1;
      goto LABEL_98;
    }
  }
  if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
    sub_180052F00("[font] Failed packing %dx%d rectangle. Returning fallback.\n", a2, a3);
  return 0xFFFFFFFFLL;
}
