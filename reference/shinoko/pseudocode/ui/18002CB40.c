__int64 sub_18002CB40()
{
  char v0; // al
  __int64 v1; // rax
  void *v2; // rcx
  char v3; // al
  __int64 v4; // rax
  void (__fastcall *v5)(__int64, char *); // r8
  char v6; // al
  __int64 (*v7)(void); // rax
  void *v8; // rax
  char v9; // al
  __int64 v10; // rcx
  char v11; // al
  char v12; // al
  __int64 v13; // r15
  __int64 v14; // r12
  unsigned __int8 v15; // bl
  unsigned __int8 v16; // di
  _QWORD *v17; // r9
  unsigned __int64 v18; // r14
  __int64 v19; // rcx
  __m128i *v20; // rsi
  __int8 *v21; // rsi
  __int64 v22; // rcx
  __m128i *v23; // rax
  __m128i *v24; // rax
  void *v25; // rcx
  unsigned __int64 v26; // rdx
  void (__fastcall *v27)(__int64, __m128i *); // r9
  char *v28; // rsi
  __int64 v29; // rax
  int v30; // ebx
  int v31; // eax
  __int64 v32; // rdx
  char *v33; // r14
  int v34; // eax
  __int64 v35; // rdx
  int v36; // eax
  char *v37; // rdi
  int v38; // ecx
  int v39; // eax
  __int64 v40; // rcx
  __int64 v41; // rax
  __int64 v42; // rcx
  __int64 v43; // r10
  unsigned __int64 v44; // r9
  _BYTE *v45; // rax
  _BYTE *v46; // rdx
  _BYTE *v47; // rax
  __int64 v48; // rcx
  __int64 v49; // r9
  unsigned int v50; // ebx
  char *v51; // rdx
  unsigned __int8 v52; // al
  unsigned int v53; // ebx
  __int64 v54; // rdx
  __m128i v55; // xmm6
  __m128i v56; // xmm7
  __m128i v57; // xmm8
  __m128i v58; // xmm9
  __m128i v59; // xmm10
  __int64 v60; // rcx
  __int64 v61; // r13
  char *v62; // rcx
  char *v63; // r9
  char *v64; // r12
  char **v65; // r8
  __int64 v66; // r10
  char *v67; // rbx
  char *v68; // rsi
  char v69; // r14
  char *v70; // rdi
  char *v71; // r14
  char v72; // dl
  char v73; // r14
  char *v74; // rsi
  __int64 v75; // rdi
  __int64 v76; // rax
  char v77; // cl
  char *v78; // r10
  char *i; // r11
  char v80; // r9
  char v81; // r8
  char v82; // cl
  char v83; // r15
  char *v84; // rsi
  char v85; // cl
  char *v86; // r10
  char *j; // r11
  char v88; // r9
  char v89; // r8
  char v90; // cl
  __int64 v91; // rdi
  __int64 v92; // rax
  __int64 v93; // rdi
  __int64 v94; // rax
  __int64 v95; // rdi
  __int64 v96; // rax
  __int64 v97; // rdi
  __int64 v98; // rax
  __int64 v99; // rdi
  __int64 v100; // rax
  __int64 v101; // rdi
  __int64 v102; // rax
  float *v103; // rax
  __int64 v104; // rdx
  float v105; // xmm3_4
  float v106; // xmm2_4
  __int64 v108; // [rsp+48h] [rbp-89h]
  __m128i si128; // [rsp+50h] [rbp-81h] BYREF
  __m128i v110; // [rsp+60h] [rbp-71h] BYREF
  __int64 v111; // [rsp+70h] [rbp-61h]
  unsigned __int64 v112; // [rsp+78h] [rbp-59h]
  __int64 v113; // [rsp+138h] [rbp+67h] BYREF
  __int64 v114; // [rsp+140h] [rbp+6Fh] BYREF
  __int64 v115; // [rsp+148h] [rbp+77h]
  __int64 v116; // [rsp+150h] [rbp+7Fh]

  v113 = 3212836864LL;
  sub_180002F70((__int64)"Lua Script Editor", (float *)&v113);
  v113 = 0x435C0000BF800000LL;
  sub_180079E10((unsigned int)"##luascript_input", 0, (unsigned int)aHaii, 0x10000, (__int64)&v113, 67108896, 0, 0);
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6A70);
  sub_180036E50(21, &si128);
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6AC0);
  sub_180036E50(22, &si128);
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6A20);
  sub_180036E50(23, &si128);
  v113 = 0x41E0000043020000LL;
  sub_18006FED0((__int64)"Execute Script##lua_exec", &v113);
  if ( v0 )
  {
    v110 = 0;
    v111 = 0;
    v112 = 0;
    v1 = sub_1800B9730(aHaii);
    sub_180015BF0(&v110, aHaii, v1);
    sub_18002C7A0((__int64)&v110);
    if ( v112 > 0xF )
    {
      v2 = (void *)v110.m128i_i64[0];
      if ( v112 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v110.m128i_i64[0] - *(_QWORD *)(v110.m128i_i64[0] - 8) - 8) > 0x1F )
          goto LABEL_58;
        v2 = *(void **)(v110.m128i_i64[0] - 8);
      }
      sub_1800931A0(v2);
    }
  }
  sub_180036F60(3);
  sub_18004AC40();
  v113 = 0x41E0000042960000LL;
  sub_18006FED0((__int64)"Copy##lua_copy", &v113);
  if ( v3 )
  {
    v4 = qword_18010C470;
    v5 = *(void (__fastcall **)(__int64, char *))(qword_18010C470 + 3048);
    if ( v5 )
    {
      v5(qword_18010C470, aHaii);
      v4 = qword_18010C470;
    }
    *(float *)&dword_18010C96C = (float)*(double *)(v4 + 5024) + 1.8;
  }
  sub_18004AC40();
  v113 = 0x41E0000042960000LL;
  sub_18006FED0((__int64)"Paste##lua_paste", &v113);
  if ( v6 )
  {
    v7 = *(__int64 (**)(void))(qword_18010C470 + 3040);
    if ( v7 )
    {
      v8 = (void *)v7();
      if ( !v8 )
        goto LABEL_17;
    }
    else
    {
      v8 = &byte_1800D411C;
    }
    sub_18009CB60(aHaii, 0x10000, v8, 0xFFFF);
  }
LABEL_17:
  sub_18004AC40();
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6A00);
  sub_180036E50(21, &si128);
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6A50);
  sub_180036E50(22, &si128);
  si128 = _mm_load_si128((const __m128i *)&xmmword_1800E69D0);
  sub_180036E50(23, &si128);
  v113 = 0x41E0000042B40000LL;
  sub_18006FED0((__int64)"Clear Code##lua_clear", &v113);
  if ( v9 )
    aHaii[0] = 0;
  sub_180036F60(3);
  if ( *(float *)&dword_18010C96C > (float)*(double *)(qword_18010C470 + 5024) )
  {
    sub_18004AC40();
    si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6AD0);
    sub_18006F3E0(&si128, "Copied to clipboard!");
  }
  sub_180003370();
  v10 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v10 + 5216) + 209LL) )
  {
    v113 = 0;
    sub_18004AAD0(&v113);
  }
  v113 = 3212836864LL;
  sub_180002F70((__int64)"Executor Logs", (float *)&v113);
  v113 = 0x41C0000042AA0000LL;
  sub_18006FED0((__int64)"Clear Logs##clear_logs", &v113);
  if ( v11 )
  {
    if ( (unsigned int)sub_18008E8C0(&unk_18010B6B0) )
      goto LABEL_224;
    if ( dword_18010B6FC == 0x7FFFFFFF )
      goto LABEL_219;
    sub_18002DC70(&qword_18010C4E0);
    sub_18008E9E0(&unk_18010B6B0);
  }
  sub_18004AC40();
  v113 = 0x41C0000042AA0000LL;
  sub_18006FED0((__int64)"Copy Logs##copy_logs", &v113);
  if ( v12 )
  {
    v110 = 0;
    v111 = 0;
    v112 = 15;
    v110.m128i_i8[0] = 0;
    v113 = (__int64)&unk_18010B6B0;
    if ( (unsigned int)sub_18008E8C0(&unk_18010B6B0) )
      sub_18008EE80(5);
    if ( dword_18010B6FC == 0x7FFFFFFF )
    {
      dword_18010B6FC = 2147483646;
      sub_18008EE80(6);
    }
    v13 = qword_18010C4F8;
    v14 = qword_18010C4F8 + qword_18010C500;
    if ( qword_18010C4F8 != qword_18010C4F8 + qword_18010C500 )
    {
      v15 = v113;
      v16 = v113;
      do
      {
        v17 = *(_QWORD **)(qword_18010C4E8 + 8 * (v13 & (qword_18010C4F0 - 1)));
        v18 = v17[2];
        if ( v17[3] > 0xFu )
          v17 = (_QWORD *)*v17;
        v19 = v111;
        if ( v18 > v112 - v111 )
        {
          sub_180015DF0((unsigned int)&v110, v18, v16, (_DWORD)v17, v18);
        }
        else
        {
          v111 += v18;
          v20 = &v110;
          if ( v112 > 0xF )
            v20 = (__m128i *)v110.m128i_i64[0];
          v21 = &v20->m128i_i8[v19];
          sub_1800B8BD0(v21, v17, v18);
          v21[v18] = 0;
        }
        v22 = v111;
        if ( v112 == v111 )
        {
          sub_180015DF0((unsigned int)&v110, 1, v15, (unsigned int)"\n", 1);
        }
        else
        {
          ++v111;
          v23 = &v110;
          if ( v112 > 0xF )
            v23 = (__m128i *)v110.m128i_i64[0];
          *(__int16 *)((char *)v23->m128i_i16 + v22) = 10;
        }
        ++v13;
      }
      while ( v13 != v14 );
    }
    sub_18008E9E0(&unk_18010B6B0);
    v24 = &v110;
    v25 = (void *)v110.m128i_i64[0];
    v26 = v112;
    if ( v112 > 0xF )
      v24 = (__m128i *)v110.m128i_i64[0];
    v27 = *(void (__fastcall **)(__int64, __m128i *))(qword_18010C470 + 3048);
    if ( v27 )
    {
      v27(qword_18010C470, v24);
      v26 = v112;
      v25 = (void *)v110.m128i_i64[0];
    }
    if ( v26 > 0xF )
    {
      if ( v26 + 1 < 0x1000 )
      {
LABEL_53:
        sub_1800931A0(v25);
        goto LABEL_54;
      }
      if ( (unsigned __int64)v25 - *((_QWORD *)v25 - 1) - 8 <= 0x1F )
      {
        v25 = *((void **)v25 - 1);
        goto LABEL_53;
      }
LABEL_58:
      __fastfail(5u);
    }
  }
LABEL_54:
  sub_18004AC40();
  sub_180071070((__int64)"Auto-scroll##lua_autoscroll", &byte_1800FAB20);
  sub_18004AC40();
  v28 = (char *)&unk_18010C9A0;
  if ( dword_18010CAB8 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)TlsIndex)
                                   + 4LL) )
  {
    sub_1800930B0(&dword_18010CAB8);
    if ( dword_18010CAB8 == -1 )
    {
      sub_1800B97F0(&unk_18010C9A0, &byte_1800D411C, 255);
      byte_18010CA9F = 0;
      sub_180036A70();
      sub_180092FC0(sub_1800BB870);
      sub_180093040(&dword_18010CAB8);
    }
  }
  v29 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
  *(_DWORD *)(v29 + 7712) = 1124859904;
  v113 = 0;
  if ( (unsigned __int8)sub_180079E10(
                          (unsigned int)"Filter##lua_log_filter",
                          0,
                          (unsigned int)&unk_18010C9A0,
                          256,
                          (__int64)&v113,
                          0,
                          0,
                          0) )
  {
    v30 = dword_18010CAA4;
    if ( dword_18010CAA4 < 0 )
    {
      v31 = dword_18010CAA4 + dword_18010CAA4 / 2;
      v32 = 0;
      if ( v31 > 0 )
        v32 = (unsigned int)v31;
      sub_180054C20(&dword_18010CAA0, v32);
      v30 = dword_18010CAA4;
    }
    dword_18010CAA0 = 0;
    v33 = (char *)&unk_18010C9A0 + sub_1800B9730(&unk_18010C9A0);
    if ( v30 < 0 )
    {
      v34 = v30 + v30 / 2;
      v35 = 0;
      if ( v34 > 0 )
        v35 = (unsigned int)v34;
      sub_180054C20(&dword_18010CAA0, v35);
      v30 = dword_18010CAA4;
    }
    v36 = 0;
    dword_18010CAA0 = 0;
    v37 = (char *)&unk_18010C9A0;
    if ( &unk_18010C9A0 < (_UNKNOWN *)v33 )
    {
      do
      {
        if ( *v37 == 44 )
        {
          if ( v36 == v30 )
          {
            v38 = v36 + 1;
            if ( v30 )
              v39 = v30 + v30 / 2;
            else
              v39 = 8;
            if ( v39 > v38 )
              v38 = v39;
            sub_180054C20(&dword_18010CAA0, (unsigned int)v38);
            v36 = dword_18010CAA0;
          }
          v40 = 2LL * v36;
          v41 = qword_18010CAA8;
          *(_QWORD *)(qword_18010CAA8 + 8 * v40) = v28;
          *(_QWORD *)(v41 + 8 * v40 + 8) = v37;
          v36 = ++dword_18010CAA0;
          v28 = v37 + 1;
          v30 = dword_18010CAA4;
        }
        ++v37;
      }
      while ( v37 < v33 );
      if ( v28 != v37 )
      {
        si128.m128i_i64[0] = (__int64)v28;
        si128.m128i_i64[1] = (__int64)v37;
        sub_1800545E0(&dword_18010CAA0, &si128);
        v36 = dword_18010CAA0;
      }
    }
    dword_18010CAB0 = 0;
    v42 = qword_18010CAA8;
    v43 = qword_18010CAA8 + 16LL * v36;
    if ( qword_18010CAA8 != v43 )
    {
      do
      {
        v44 = *(_QWORD *)(v42 + 8);
        v45 = *(_BYTE **)v42;
        if ( *(_QWORD *)v42 >= v44 )
        {
          v46 = *(_BYTE **)v42;
        }
        else
        {
          do
          {
            if ( *v45 != 32 )
            {
              v46 = v45;
              if ( *v45 != 9 )
                break;
            }
            *(_QWORD *)v42 = ++v45;
            v46 = v45;
          }
          while ( (unsigned __int64)v45 < v44 );
        }
        if ( v44 > (unsigned __int64)v46 )
        {
          do
          {
            v47 = (_BYTE *)(*(_QWORD *)(v42 + 8) - 1LL);
            if ( *v47 != 32 && *v47 != 9 )
              break;
            *(_QWORD *)(v42 + 8) = v47;
          }
          while ( v47 > v46 );
        }
        if ( v46 != *(_BYTE **)(v42 + 8) && *v46 != 45 )
          ++dword_18010CAB0;
        v42 += 16;
      }
      while ( v42 != v43 );
    }
  }
  v114 = 0x430C0000BF800000LL;
  v48 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v49 = *(_QWORD *)(v48 + 5216);
  v50 = ~*(_DWORD *)(*(_QWORD *)(v49 + 272) + 4LL * *(int *)(v49 + 264) - 4);
  v51 = "#lua_log_window";
  v52 = 35;
  do
  {
    if ( v52 == 35 && *v51 == 35 && v51[1] == 35 )
      v50 = ~*(_DWORD *)(*(_QWORD *)(v49 + 272) + 4LL * *(int *)(v49 + 264) - 4);
    v50 = dword_1800D56B0[v52 ^ (unsigned __int64)(unsigned __int8)v50] ^ (v50 >> 8);
    v52 = *v51++;
  }
  while ( v52 );
  v53 = ~v50;
  if ( *(_DWORD *)(*(_QWORD *)v49 + 5304LL) == v53 )
    sub_180053310(v53, 11, "##lua_log_window");
  sub_18003E470((unsigned int)"##lua_log_window", v53, (unsigned int)&v114, 1, 0);
  si128.m128i_i64[0] = (__int64)&unk_18010B6B0;
  if ( (unsigned int)sub_18008E8C0(&unk_18010B6B0) )
LABEL_224:
    sub_18008EE80(5);
  if ( dword_18010B6FC == 0x7FFFFFFF )
  {
LABEL_219:
    dword_18010B6FC = 2147483646;
    sub_18008EE80(6);
  }
  v54 = qword_18010C4F8;
  v116 = qword_18010C4F8;
  v108 = qword_18010C4F8 + qword_18010C500;
  if ( qword_18010C4F8 == qword_18010C4F8 + qword_18010C500 )
    goto LABEL_215;
  v55 = _mm_load_si128((const __m128i *)&xmmword_1800E6A90);
  v56 = _mm_load_si128((const __m128i *)&xmmword_1800E6B00);
  v57 = _mm_load_si128((const __m128i *)&xmmword_1800E6AE0);
  v58 = _mm_load_si128((const __m128i *)&xmmword_1800E6A80);
  v59 = _mm_load_si128((const __m128i *)&xmmword_1800E6AA0);
  do
  {
    v60 = qword_18010C4E8 + 8 * (v54 & (qword_18010C4F0 - 1));
    v61 = *(_QWORD *)v60;
    if ( *(_QWORD *)(*(_QWORD *)v60 + 24LL) > 0xFu )
      v60 = *(_QWORD *)v60;
    if ( !dword_18010CAA0 )
    {
LABEL_126:
      v75 = v61;
      if ( *(_QWORD *)(v61 + 24) > 0xFu )
        v75 = *(_QWORD *)v61;
      if ( *(_QWORD *)(v61 + 16) < 6u || (v76 = sub_18008E8B0(v75, v75 + 6, "[HOOK]", 6), v76 == v75 + 6) || v76 != v75 )
      {
        v91 = v61;
        if ( *(_QWORD *)(v61 + 24) > 0xFu )
          v91 = *(_QWORD *)v61;
        if ( *(_QWORD *)(v61 + 16) >= 7u )
        {
          v92 = sub_18008E8B0(v91, v91 + 7, "[ERROR]", 7);
          if ( v92 != v91 + 7 && v92 == v91 )
            goto LABEL_183;
        }
        v93 = v61;
        if ( *(_QWORD *)(v61 + 24) > 0xFu )
          v93 = *(_QWORD *)v61;
        if ( *(_QWORD *)(v61 + 16) >= 0xEu )
        {
          v94 = sub_18008E8B0(v93, v93 + 14, "[SYNTAX ERROR]", 14);
          if ( v94 != v93 + 14 && v94 == v93 )
            goto LABEL_183;
        }
        v95 = v61;
        if ( *(_QWORD *)(v61 + 24) > 0xFu )
          v95 = *(_QWORD *)v61;
        if ( *(_QWORD *)(v61 + 16) < 0xBu
          || (v96 = sub_18008E8B0(v95, v95 + 11, "[LUA ERROR]", 11), v96 == v95 + 11)
          || v96 != v95 )
        {
          v97 = v61;
          if ( *(_QWORD *)(v61 + 24) > 0xFu )
            v97 = *(_QWORD *)v61;
          if ( *(_QWORD *)(v61 + 16) < 6u
            || (v98 = sub_18008E8B0(v97, v97 + 6, "[EXEC]", 6), v98 == v97 + 6)
            || v98 != v97 )
          {
            v99 = v61;
            if ( *(_QWORD *)(v61 + 24) > 0xFu )
              v99 = *(_QWORD *)v61;
            if ( *(_QWORD *)(v61 + 16) < 5u
              || (v100 = sub_18008E8B0(v99, v99 + 5, "[LUA]", 5), v100 == v99 + 5)
              || v100 != v99 )
            {
              v101 = v61;
              if ( *(_QWORD *)(v61 + 24) > 0xFu )
                v101 = *(_QWORD *)v61;
              if ( *(_QWORD *)(v61 + 16) < 7u
                || (v102 = sub_18008E8B0(v101, v101 + 7, "[QUEUE]", 7), v102 == v101 + 7)
                || v102 != v101 )
              {
                if ( *(_QWORD *)(v61 + 24) > 0xFu )
                  v61 = *(_QWORD *)v61;
                sub_18006EB90(v61, 0, 1);
                goto LABEL_214;
              }
              if ( *(_QWORD *)(v61 + 24) > 0xFu )
                v61 = *(_QWORD *)v61;
              v110 = v55;
            }
            else
            {
              if ( *(_QWORD *)(v61 + 24) > 0xFu )
                v61 = *(_QWORD *)v61;
              v110 = v56;
            }
          }
          else
          {
            if ( *(_QWORD *)(v61 + 24) > 0xFu )
              v61 = *(_QWORD *)v61;
            v110 = v57;
          }
        }
        else
        {
LABEL_183:
          if ( *(_QWORD *)(v61 + 24) > 0xFu )
            v61 = *(_QWORD *)v61;
          v110 = v58;
        }
      }
      else
      {
        if ( *(_QWORD *)(v61 + 24) > 0xFu )
          v61 = *(_QWORD *)v61;
        v110 = v59;
      }
      sub_18006F3E0(&v110, "%s", (const char *)v61);
      goto LABEL_214;
    }
    v62 = *(char **)v60;
    v63 = (char *)&byte_1800D411C;
    if ( v62 )
      v63 = v62;
    v114 = (__int64)v63;
    v64 = (char *)&byte_1800D411C;
    if ( v62 )
      v64 = nullptr;
    v65 = (char **)qword_18010CAA8;
    v113 = qword_18010CAA8;
    v66 = 16LL * dword_18010CAA0 + qword_18010CAA8;
    v115 = v66;
    if ( !(16LL * dword_18010CAA0) )
      goto LABEL_125;
    do
    {
      v67 = v65[1];
      v68 = *v65;
      if ( *v65 == v67 )
        goto LABEL_124;
      v69 = *v68;
      v70 = v63;
      if ( *v68 == 45 )
      {
        v71 = v68 + 1;
        if ( !v67 )
          v67 = &v71[sub_1800B9730(v68 + 1)];
        v72 = *v71;
        v73 = *v71 & 0xDF;
        if ( (unsigned __int8)(v72 - 97) > 0x19u )
          v73 = v72;
        v74 = v68 + 2;
        while ( 1 )
        {
          if ( v64 )
          {
            if ( v70 >= v64 )
              goto LABEL_123;
          }
          else if ( !*v70 )
          {
            goto LABEL_123;
          }
          v77 = *v70 & 0xDF;
          if ( (unsigned __int8)(*v70 - 97) > 0x19u )
            v77 = *v70;
          if ( v77 == v73 )
          {
            v78 = v74;
            for ( i = v70 + 1; v78 < v67; ++v78 )
            {
              v80 = *i;
              v81 = *v78 & 0xDF;
              if ( (unsigned __int8)(*v78 - 97) > 0x19u )
                v81 = *v78;
              v82 = v80 & 0xDF;
              if ( (unsigned __int8)(v80 - 97) > 0x19u )
                v82 = *i;
              if ( v82 != v81 )
                break;
              ++i;
            }
            if ( v78 == v67 )
              goto LABEL_214;
          }
          ++v70;
        }
      }
      if ( !v67 )
        v67 = &v68[sub_1800B9730(*v65)];
      v83 = v69 & 0xDF;
      if ( (unsigned __int8)(v69 - 97) > 0x19u )
        v83 = v69;
      v84 = v68 + 1;
      while ( !v64 )
      {
        if ( !*v70 )
          goto LABEL_123;
LABEL_156:
        v85 = *v70 & 0xDF;
        if ( (unsigned __int8)(*v70 - 97) > 0x19u )
          v85 = *v70;
        if ( v85 == v83 )
        {
          v86 = v84;
          for ( j = v70 + 1; v86 < v67; ++v86 )
          {
            v88 = *j;
            v89 = *v86 & 0xDF;
            if ( (unsigned __int8)(*v86 - 97) > 0x19u )
              v89 = *v86;
            v90 = v88 & 0xDF;
            if ( (unsigned __int8)(v88 - 97) > 0x19u )
              v90 = *j;
            if ( v90 != v89 )
              break;
            ++j;
          }
          if ( v86 == v67 )
            goto LABEL_126;
        }
        ++v70;
      }
      if ( v70 < v64 )
        goto LABEL_156;
LABEL_123:
      v66 = v115;
      v63 = (char *)v114;
      v65 = (char **)v113;
LABEL_124:
      v65 += 2;
      v113 = (__int64)v65;
    }
    while ( v65 != (char **)v66 );
LABEL_125:
    if ( !dword_18010CAB0 )
      goto LABEL_126;
LABEL_214:
    v54 = v116 + 1;
    v116 = v54;
  }
  while ( v54 != v108 );
LABEL_215:
  if ( byte_1800FAB20 )
  {
    v103 = *(float **)(qword_18010C470 + 5216);
    if ( v103[39] >= v103[41] )
    {
      v104 = *(_QWORD *)(qword_18010C470 + 5216);
      v105 = v103[23];
      v106 = fmaxf(v105, *(float *)(qword_18010C470 + 3232));
      *(float *)(v104 + 172) = (float)(int)(float)((float)((float)((float)((float)((float)((float)((float)(v103[73] + v103[83])
                                                                                                 + v106)
                                                                                         - (float)(v103[73] - v106))
                                                                                 + (float)(v103[73] - v106))
                                                                         - v103[11])
                                                                 - v103[29])
                                                         - v103[33])
                                                 + v103[39]);
      *(_DWORD *)(v104 + 180) = 1065353216;
      *(float *)(v104 + 188) = fmaxf(0.0, v105 - v106);
    }
  }
  sub_18008E9E0(&unk_18010B6B0);
  sub_18003E7F0();
  return sub_180003370();
}
