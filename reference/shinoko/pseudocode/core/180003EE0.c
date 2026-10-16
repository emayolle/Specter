__int64 __fastcall sub_180003EE0(__int64 a1, unsigned __int64 a2, __int64 a3, int a4)
{
  __int64 (__fastcall ***v7)(_QWORD, _BYTE *); // rcx
  _QWORD *v8; // rbx
  _QWORD *v9; // rsi
  unsigned __int64 v10; // r14
  __int64 v11; // r15
  unsigned __int64 v12; // rdx
  __int64 v13; // r8
  _QWORD *v14; // rcx
  LPVOID v15; // rax
  unsigned __int64 v16; // rdx
  __int64 v17; // rdi
  __int64 v18; // rcx
  __int64 v19; // rdx
  __int64 v20; // r14
  __int64 v21; // rax
  unsigned __int64 v22; // r12
  unsigned __int64 v23; // rcx
  unsigned __int64 v24; // r13
  __int64 v25; // rcx
  unsigned __int64 v26; // rax
  unsigned __int64 v27; // rcx
  unsigned __int64 v28; // rsi
  unsigned __int64 v29; // rcx
  __int64 v30; // rax
  unsigned __int64 v31; // r14
  __int64 *v32; // rax
  __int64 v33; // rdx
  __int64 v34; // rcx
  unsigned __int64 v35; // r8
  __int64 v36; // rdi
  __int64 i; // r14
  __int64 v38; // rcx
  __int64 v39; // rax
  void *v40; // rcx
  __int64 v41; // rbx
  __int64 v42; // r15
  unsigned __int64 v43; // r13
  __int64 v44; // rdi
  __int64 v45; // rdx
  unsigned __int64 v46; // r8
  unsigned __int64 v47; // rcx
  unsigned __int64 v48; // rdx
  unsigned __int64 v49; // rsi
  unsigned __int64 v50; // r12
  __int64 v51; // rcx
  _QWORD *v52; // r15
  __int64 v53; // rax
  char *v54; // r14
  char *v55; // rdi
  __int64 v56; // rdx
  _QWORD *v57; // rbx
  _QWORD *v58; // rdi
  _QWORD *v59; // rcx
  _BYTE *v60; // rcx
  __int64 v61; // rsi
  __int64 v62; // rcx
  __int64 v63; // rcx
  void *v64; // rbx
  __int64 v65; // rdx
  signed __int64 v66; // rsi
  signed __int64 v67; // r14
  unsigned __int64 v68; // r14
  unsigned __int64 v69; // rcx
  __int64 v70; // rcx
  unsigned __int64 v71; // rax
  unsigned __int64 v72; // rcx
  _QWORD *v73; // rdi
  unsigned __int64 v74; // rcx
  __int64 v75; // rax
  char *v76; // rdx
  char *v77; // rsi
  __int64 v78; // rdx
  char *v79; // r8
  LPVOID v80; // rcx
  char *v81; // rbx
  char *v82; // rsi
  _BYTE *v83; // rcx
  _QWORD *v84; // rbx
  _QWORD *v85; // rdi
  _QWORD *v86; // rcx
  _BYTE *v87; // rcx
  void *v88; // rcx
  _BYTE *v89; // rdx
  __int64 v90; // rcx
  __int64 v92; // [rsp+20h] [rbp-A9h]
  __int64 v93; // [rsp+20h] [rbp-A9h]
  __int128 v94; // [rsp+30h] [rbp-99h] BYREF
  __int64 v95; // [rsp+40h] [rbp-89h]
  unsigned __int64 v96; // [rsp+48h] [rbp-81h]
  int v97; // [rsp+50h] [rbp-79h]
  LPVOID lpMem; // [rsp+58h] [rbp-71h] BYREF
  __int128 v99; // [rsp+60h] [rbp-69h]
  LPVOID *p_lpMem; // [rsp+70h] [rbp-59h]
  _QWORD *v101; // [rsp+78h] [rbp-51h]
  unsigned __int64 v102; // [rsp+80h] [rbp-49h]
  char *v103; // [rsp+88h] [rbp-41h]
  char *v104; // [rsp+90h] [rbp-39h]
  _BYTE v105[56]; // [rsp+98h] [rbp-31h] BYREF
  _BYTE *v106; // [rsp+D0h] [rbp+7h]
  _BYTE *v107; // [rsp+D8h] [rbp+Fh]
  char *v108; // [rsp+E0h] [rbp+17h]

  if ( dword_18010C930 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)TlsIndex)
                                   + 4LL) )
  {
    sub_1800930B0(&dword_18010C930);
    if ( dword_18010C930 == -1 )
    {
      sub_180092FC0(sub_1800BB650);
      sub_180093040(&dword_18010C930);
    }
  }
  v106 = nullptr;
  v7 = *(__int64 (__fastcall ****)(_QWORD, _BYTE *))(a3 + 56);
  if ( v7 )
    v106 = (_BYTE *)(**v7)(v7, v105);
  v107 = v105;
  v9 = *(&::lpMem + 1);
  v8 = ::lpMem;
  if ( ::lpMem == *(&::lpMem + 1) )
  {
LABEL_15:
    v94 = 0;
    v95 = 0;
    v96 = 15;
    LOBYTE(v94) = 0;
    v97 = 0;
    v15 = nullptr;
    lpMem = nullptr;
    v99 = 0;
    if ( &v94 != (__int128 *)a2 )
    {
      if ( *(_QWORD *)(a2 + 24) <= 0xFu )
        v16 = a2;
      else
        v16 = *(_QWORD *)a2;
      sub_180015F80(&v94, v16, *(_QWORD *)(a2 + 16));
      v15 = lpMem;
    }
    v97 = a4;
    v41 = v99;
    v42 = 0x3FFFFFFFFFFFFFFLL;
    v43 = -64;
    if ( (_QWORD)v99 != *((_QWORD *)&v99 + 1) )
    {
      *(_QWORD *)(v99 + 56) = 0;
      if ( v106 )
        *(_QWORD *)(v41 + 56) = (**(__int64 (__fastcall ***)(_BYTE *, __int64))v106)(v106, v41);
      *(_QWORD *)&v99 = v99 + 64;
LABEL_95:
      v64 = *(&::lpMem + 1);
      if ( *(&::lpMem + 1) != (LPVOID)qword_18010C950 )
      {
        sub_180016190(qword_18010C950, *(&::lpMem + 1), &v94);
        *(&::lpMem + 1) = (char *)*(&::lpMem + 1) + 64;
        goto LABEL_123;
      }
      v66 = (_BYTE *)*(&::lpMem + 1) - (_BYTE *)::lpMem;
      v67 = ((_BYTE *)*(&::lpMem + 1) - (_BYTE *)::lpMem) >> 6;
      if ( v67 == 0x3FFFFFFFFFFFFFFLL )
        std::vector<void *>::_Xlen(qword_18010C950);
      v68 = v67 + 1;
      v69 = (qword_18010C950 - (__int64)::lpMem) >> 6;
      if ( v69 > 0x3FFFFFFFFFFFFFFLL - (v69 >> 1) )
      {
        v70 = -25;
        goto LABEL_107;
      }
      v71 = (v69 >> 1) + v69;
      v72 = v68;
      if ( v71 >= v68 )
        v72 = v71;
      if ( v72 <= 0x3FFFFFFFFFFFFFFLL )
      {
        v43 = v72 << 6;
        v42 = v72;
        if ( !(v72 << 6) )
        {
          v73 = nullptr;
          goto LABEL_111;
        }
        v74 = v72 << 6;
        if ( v43 < 0x1000 )
        {
          v73 = (_QWORD *)sub_180093150(v74);
          goto LABEL_111;
        }
        v70 = v43 | 0x27;
        if ( (v43 | 0x27) > v43 )
        {
LABEL_107:
          v75 = sub_180093150(v70);
          if ( !v75 )
LABEL_108:
            __fastfail(5u);
          v73 = (_QWORD *)((v75 + 39) & 0xFFFFFFFFFFFFFFE0uLL);
          *(v73 - 1) = v75;
LABEL_111:
          v76 = (char *)v73 + (v66 & 0xFFFFFFFFFFFFFFC0uLL);
          v77 = v76 + 64;
          p_lpMem = &::lpMem;
          v101 = v73;
          v102 = v42;
          v103 = v76 + 64;
          v104 = v76 + 64;
          sub_180016190(v72, v76, &v94);
          v78 = (__int64)*(&::lpMem + 1);
          v79 = (char *)v73;
          v80 = ::lpMem;
          if ( v64 != *(&::lpMem + 1) )
          {
            sub_1800162E0(::lpMem, v64, v73);
            v79 = v77;
            v78 = (__int64)*(&::lpMem + 1);
            v80 = v64;
          }
          sub_1800162E0(v80, v78, v79);
          v81 = (char *)::lpMem;
          if ( ::lpMem )
          {
            v82 = (char *)*(&::lpMem + 1);
            if ( ::lpMem != *(&::lpMem + 1) )
            {
              do
              {
                sub_180015A20(v81 + 40);
                sub_180015D80(v81);
                v81 += 64;
              }
              while ( v81 != v82 );
              v81 = (char *)::lpMem;
            }
            if ( ((qword_18010C950 - (_QWORD)v81) & 0xFFFFFFFFFFFFFFC0uLL) < 0x1000 )
            {
              v83 = v81;
            }
            else
            {
              v83 = *((_BYTE **)v81 - 1);
              if ( (unsigned __int64)(v81 - v83 - 8) > 0x1F )
                __fastfail(5u);
            }
            sub_1800931A0(v83);
          }
          ::lpMem = v73;
          *(&::lpMem + 1) = &v73[8 * v68];
          qword_18010C950 = (__int64)v73 + v43;
LABEL_123:
          v84 = lpMem;
          if ( lpMem )
          {
            v85 = (_QWORD *)v99;
            if ( lpMem != (LPVOID)v99 )
            {
              do
              {
                v86 = (_QWORD *)v84[7];
                if ( v86 )
                {
                  LOBYTE(v65) = v86 != v84;
                  (*(void (__fastcall **)(_QWORD *, __int64))(*v86 + 32LL))(v86, v65);
                  v84[7] = 0;
                }
                v84 += 8;
              }
              while ( v84 != v85 );
              v84 = lpMem;
            }
            if ( ((*((_QWORD *)&v99 + 1) - (_QWORD)v84) & 0xFFFFFFFFFFFFFFC0uLL) < 0x1000 )
            {
              v87 = v84;
            }
            else
            {
              v87 = (_BYTE *)*(v84 - 1);
              if ( (unsigned __int64)((char *)v84 - v87 - 8) > 0x1F )
                goto LABEL_145;
            }
            sub_1800931A0(v87);
            lpMem = nullptr;
            v99 = 0;
          }
          v12 = v96;
          if ( v96 > 0xF )
          {
            v88 = (void *)v94;
            if ( v96 + 1 >= 0x1000 )
            {
              if ( (unsigned __int64)(v94 - *(_QWORD *)(v94 - 8) - 8) > 0x1F )
                goto LABEL_145;
              v88 = *(void **)(v94 - 8);
            }
            sub_1800931A0(v88);
          }
          v95 = 0;
          v96 = 15;
          LOBYTE(v94) = 0;
          goto LABEL_140;
        }
      }
LABEL_147:
      Concurrency::cancel_current_task();
    }
    v44 = v99 - (_QWORD)v15;
    v45 = (__int64)(v99 - (_QWORD)v15) >> 6;
    if ( v45 == 0x3FFFFFFFFFFFFFFLL )
      std::vector<void *>::_Xlen(*((_QWORD *)&v99 + 1));
    v46 = v45 + 1;
    v93 = v45 + 1;
    v47 = (__int64)(*((_QWORD *)&v99 + 1) - (_QWORD)v15) >> 6;
    v48 = v47 >> 1;
    if ( v47 > 0x3FFFFFFFFFFFFFFLL - (v47 >> 1) )
    {
      v49 = 0x3FFFFFFFFFFFFFFLL;
      v50 = -64;
      v51 = -25;
LABEL_66:
      v53 = sub_180093150(v51);
      if ( !v53 )
        goto LABEL_108;
      v52 = (_QWORD *)((v53 + 39) & 0xFFFFFFFFFFFFFFE0uLL);
      *(v52 - 1) = v53;
      goto LABEL_69;
    }
    v49 = v46;
    if ( v48 + v47 >= v46 )
      v49 = v48 + v47;
    if ( v49 > 0x3FFFFFFFFFFFFFFLL )
      goto LABEL_147;
    v50 = v49 << 6;
    if ( v49 << 6 )
    {
      if ( v50 >= 0x1000 )
      {
        v51 = v50 | 0x27;
        if ( (v50 | 0x27) <= v50 )
          goto LABEL_147;
        goto LABEL_66;
      }
      v52 = (_QWORD *)sub_180093150(v49 << 6);
    }
    else
    {
      v52 = nullptr;
    }
LABEL_69:
    v54 = (char *)v52 + (v44 & 0xFFFFFFFFFFFFFFC0uLL);
    v55 = v54 + 64;
    p_lpMem = &lpMem;
    v101 = v52;
    v102 = v49;
    v103 = v54 + 64;
    v104 = v54 + 64;
    v108 = v54;
    *((_QWORD *)v54 + 7) = 0;
    if ( v106 )
      *((_QWORD *)v54 + 7) = (**(__int64 (__fastcall ***)(_BYTE *, char *))v106)(v106, v54);
    if ( v41 == (_QWORD)v99 )
    {
      sub_180016380(lpMem, v99, v52);
LABEL_73:
      v57 = lpMem;
      if ( lpMem )
      {
        v58 = (_QWORD *)v99;
        if ( lpMem != (LPVOID)v99 )
        {
          do
          {
            v59 = (_QWORD *)v57[7];
            if ( v59 )
            {
              LOBYTE(v56) = v59 != v57;
              (*(void (__fastcall **)(_QWORD *, __int64))(*v59 + 32LL))(v59, v56);
              v57[7] = 0;
            }
            v57 += 8;
          }
          while ( v57 != v58 );
          v57 = lpMem;
        }
        if ( ((*((_QWORD *)&v99 + 1) - (_QWORD)v57) & 0xFFFFFFFFFFFFFFC0uLL) < 0x1000 )
        {
          v60 = v57;
        }
        else
        {
          v60 = (_BYTE *)*(v57 - 1);
          if ( (unsigned __int64)((char *)v57 - v60 - 8) > 0x1F )
            __fastfail(5u);
        }
        sub_1800931A0(v60);
      }
      lpMem = v52;
      *(_QWORD *)&v99 = &v52[8 * v93];
      *((_QWORD *)&v99 + 1) = (char *)v52 + v50;
      v42 = 0x3FFFFFFFFFFFFFFLL;
      goto LABEL_95;
    }
    sub_180016380(lpMem, v41, v52);
    v61 = v99;
    if ( v41 == (_QWORD)v99 )
      goto LABEL_73;
    while ( 1 )
    {
      *((_QWORD *)v55 + 7) = 0;
      v62 = *(_QWORD *)(v41 + 56);
      if ( v62 )
      {
        if ( v62 != v41 )
        {
          *((_QWORD *)v55 + 7) = v62;
          goto LABEL_88;
        }
        *((_QWORD *)v55 + 7) = (*(__int64 (__fastcall **)(__int64, char *))(*(_QWORD *)v62 + 8LL))(v62, v55);
        v63 = *(_QWORD *)(v41 + 56);
        if ( v63 )
        {
          LOBYTE(v56) = v63 != v41;
          (*(void (__fastcall **)(__int64, __int64))(*(_QWORD *)v63 + 32LL))(v63, v56);
LABEL_88:
          *(_QWORD *)(v41 + 56) = 0;
        }
      }
      v55 += 64;
      v41 += 64;
      if ( v41 == v61 )
        goto LABEL_73;
    }
  }
  v10 = *(_QWORD *)(a2 + 24);
  v11 = *(_QWORD *)(a2 + 16);
  while ( 1 )
  {
    v12 = a2;
    if ( v10 > 0xF )
      v12 = *(_QWORD *)a2;
    v13 = v8[2];
    v14 = v8[3] <= 0xFu ? v8 : (_QWORD *)*v8;
    if ( v13 == v11 && (!v13 || !(unsigned int)sub_1800B8AD0(v14, v12, v13)) )
      break;
    v8 += 8;
    if ( v8 == v9 )
      goto LABEL_15;
  }
  v17 = v8[6];
  v18 = v8[7];
  if ( v17 != v18 )
  {
    *(_QWORD *)(v17 + 56) = 0;
    if ( v106 )
      *(_QWORD *)(v17 + 56) = (**(__int64 (__fastcall ***)(_BYTE *, __int64))v106)(v106, v17);
    v8[6] += 64LL;
    goto LABEL_140;
  }
  v19 = v8[5];
  v20 = v17 - v19;
  v21 = (v17 - v19) >> 6;
  v92 = 0x3FFFFFFFFFFFFFFLL;
  if ( v21 == 0x3FFFFFFFFFFFFFFLL )
    ((void (__noreturn *)(void))std::vector<void *>::_Xlen)();
  v22 = v21 + 1;
  v23 = (v18 - v19) >> 6;
  if ( v23 > 0x3FFFFFFFFFFFFFFLL - (v23 >> 1) )
  {
    v24 = -64;
    v25 = -25;
    goto LABEL_32;
  }
  v26 = (v23 >> 1) + v23;
  v27 = v22;
  if ( v26 >= v22 )
    v27 = v26;
  if ( v27 > 0x3FFFFFFFFFFFFFFLL )
LABEL_151:
    Concurrency::cancel_current_task();
  v24 = v27 << 6;
  v92 = v27;
  if ( v27 << 6 )
  {
    v29 = v27 << 6;
    if ( v24 < 0x1000 )
    {
      v28 = sub_180093150(v29);
      goto LABEL_35;
    }
    v25 = v24 | 0x27;
    if ( (v24 | 0x27) > v24 )
    {
LABEL_32:
      v30 = sub_180093150(v25);
      if ( v30 )
      {
        v28 = (v30 + 39) & 0xFFFFFFFFFFFFFFE0uLL;
        *(_QWORD *)(v28 - 8) = v30;
        goto LABEL_35;
      }
LABEL_145:
      __fastfail(5u);
    }
    goto LABEL_151;
  }
  v28 = 0;
  v92 = v27;
LABEL_35:
  v31 = v28 + (v20 & 0xFFFFFFFFFFFFFFC0uLL);
  v32 = v8 + 5;
  p_lpMem = (LPVOID *)(v8 + 5);
  v101 = (_QWORD *)v28;
  v102 = v92;
  v103 = (char *)(v31 + 64);
  v104 = (char *)(v31 + 64);
  *(_QWORD *)(v31 + 56) = 0;
  if ( v106 )
  {
    *(_QWORD *)(v31 + 56) = (**(__int64 (__fastcall ***)(_BYTE *, unsigned __int64))v106)(v106, v31);
    v32 = v8 + 5;
  }
  v33 = v8[6];
  v34 = *v32;
  v35 = v28;
  if ( v17 != v33 )
  {
    sub_180016380(v34, v17, v28);
    v35 = v31 + 64;
    v33 = v8[6];
    v34 = v17;
  }
  sub_180016380(v34, v33, v35);
  v36 = v8[5];
  if ( v36 )
  {
    for ( i = v8[6]; v36 != i; v36 += 64 )
    {
      v38 = *(_QWORD *)(v36 + 56);
      if ( v38 )
      {
        LOBYTE(v12) = v38 != v36;
        (*(void (__fastcall **)(__int64, unsigned __int64))(*(_QWORD *)v38 + 32LL))(v38, v12);
        *(_QWORD *)(v36 + 56) = 0;
      }
    }
    v39 = v8[5];
    if ( ((v8[7] - v39) & 0xFFFFFFFFFFFFFFC0uLL) < 0x1000 )
    {
      v40 = (void *)v8[5];
    }
    else
    {
      v40 = *(void **)(v39 - 8);
      if ( (unsigned __int64)(v39 - (_QWORD)v40 - 8) > 0x1F )
        __fastfail(5u);
    }
    sub_1800931A0(v40);
  }
  v8[5] = v28;
  v8[6] = v28 + (v22 << 6);
  v8[7] = v28 + v24;
LABEL_140:
  if ( v106 )
  {
    v89 = v105;
    LOBYTE(v89) = v106 != v105;
    (*(void (__fastcall **)(_BYTE *, _BYTE *))(*(_QWORD *)v106 + 32LL))(v106, v89);
  }
  v90 = *(_QWORD *)(a3 + 56);
  if ( v90 )
  {
    LOBYTE(v12) = v90 != a3;
    (*(void (__fastcall **)(__int64, unsigned __int64))(*(_QWORD *)v90 + 32LL))(v90, v12);
    *(_QWORD *)(a3 + 56) = 0;
  }
  return a1;
}
