// _write_nolock size=6740
__int64 write_nolock()
{
  char v0; // bl
  const char *v1; // r14
  char v2; // di
  __int64 v3; // rbx
  __int64 v4; // rax
  const char *v5; // rsi
  __int64 v6; // rax
  __int64 v7; // rbx
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rbx
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  void *v15; // rcx
  void *v16; // rcx
  void *v17; // rcx
  void *v18; // rcx
  _BYTE *v19; // rax
  __int64 v20; // rcx
  void *v21; // rcx
  void *v22; // rcx
  _BYTE *v23; // rax
  __int64 v24; // rcx
  void *v25; // rcx
  void *v26; // rcx
  _BYTE *v27; // rax
  __int64 v28; // rcx
  void *v29; // rcx
  __int64 v30; // rcx
  char v31; // bl
  __int64 v32; // rcx
  char v33; // bl
  int v34; // r8d
  int v35; // r9d
  __int64 v36; // rcx
  int v37; // r8d
  int v38; // r9d
  __int64 v39; // rcx
  char v40; // bl
  int v41; // r8d
  int v42; // r9d
  __int64 v43; // rcx
  int v44; // r8d
  int v45; // r9d
  __int64 v46; // rcx
  char v47; // bl
  int v48; // r8d
  int v49; // r9d
  __int64 v50; // rcx
  int v51; // r8d
  int v52; // r9d
  __int64 v53; // rcx
  char v54; // bl
  __int64 v55; // rcx
  char v56; // bl
  __int64 v57; // rcx
  char v58; // bl
  __int64 v59; // rbx
  __int64 v60; // rax
  void *v61; // rcx
  _BYTE *v62; // rax
  __int64 v63; // rcx
  __int64 v64; // rbx
  __int64 v65; // rax
  void *v66; // rcx
  _BYTE *v67; // rax
  __int64 v68; // rcx
  __int64 v69; // rcx
  char v70; // bl
  __int64 v71; // rcx
  float *v72; // rax
  float v73; // xmm0_4
  char v74; // bl
  char v75; // bl
  __int64 v76; // rcx
  float *v77; // rax
  float v78; // xmm0_4
  __int64 v79; // rcx
  char v80; // bl
  __int64 v81; // rsi
  char v82; // di
  __int64 v83; // rbx
  __int64 v84; // rax
  const char *v85; // rbx
  __int64 v86; // rax
  __int64 v87; // rbx
  __int64 v88; // rax
  __int64 v89; // rax
  _BYTE *v90; // rax
  __int64 v91; // rcx
  _BYTE *v92; // rax
  __int64 v93; // rcx
  __int64 v94; // rcx
  char v95; // bl
  char v96; // di
  __int64 v97; // rbx
  __int64 v98; // rax
  __int64 v99; // rax
  __int64 v100; // rbx
  __int64 v101; // rax
  __int64 v102; // rax
  _BYTE *v103; // rax
  _BYTE *v104; // rax
  __int64 v105; // rcx
  __int64 v106; // rcx
  char v107; // bl
  __int64 v108; // rbx
  __int64 v109; // rax
  _BYTE *v110; // rax
  __int64 v111; // rcx
  __int64 v112; // rbx
  __int64 v113; // rax
  _BYTE *v114; // rax
  __int64 v115; // rcx
  __int64 v116; // rcx
  char v117; // bl
  int v118; // r8d
  int v119; // r9d
  __int64 v120; // rcx
  __int64 v121; // rax
  int v122; // edx
  int v123; // ecx
  __int64 v124; // rsi
  __int64 v125; // rdi
  __int64 v126; // rbx
  __int64 v127; // rax
  __int64 v128; // rax
  __int64 v129; // rax
  void *v130; // rcx
  _BYTE *v131; // rax
  __int64 v132; // rcx
  void *v133; // rcx
  __int128 *v134; // rax
  __int64 v135; // rcx
  double v137; // [rsp+28h] [rbp-D8h]
  double v138; // [rsp+28h] [rbp-D8h]
  double v139; // [rsp+28h] [rbp-D8h]
  double v140; // [rsp+28h] [rbp-D8h]
  const char *v141; // [rsp+30h] [rbp-D0h]
  __int128 v142; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v143; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v144; // [rsp+58h] [rbp-A8h]
  __int128 v145; // [rsp+60h] [rbp-A0h] BYREF
  __int64 v146; // [rsp+70h] [rbp-90h]
  unsigned __int64 v147; // [rsp+78h] [rbp-88h]
  __int128 v148; // [rsp+80h] [rbp-80h] BYREF
  __int64 v149; // [rsp+90h] [rbp-70h]
  unsigned __int64 v150; // [rsp+98h] [rbp-68h]
  __int128 v151; // [rsp+A0h] [rbp-60h] BYREF
  __int64 v152; // [rsp+B0h] [rbp-50h]
  unsigned __int64 v153; // [rsp+B8h] [rbp-48h]
  _QWORD v154[2]; // [rsp+C0h] [rbp-40h] BYREF
  __int64 v155; // [rsp+D0h] [rbp-30h]
  unsigned __int64 v156; // [rsp+D8h] [rbp-28h]
  _QWORD v157[3]; // [rsp+E0h] [rbp-20h] BYREF
  unsigned __int64 v158; // [rsp+F8h] [rbp-8h]
  _QWORD v159[3]; // [rsp+100h] [rbp+0h] BYREF
  unsigned __int64 v160; // [rsp+118h] [rbp+18h]
  __int128 v161; // [rsp+120h] [rbp+20h] BYREF
  __int64 v162; // [rsp+130h] [rbp+30h]
  unsigned __int64 v163; // [rsp+138h] [rbp+38h]
  _QWORD v164[3]; // [rsp+140h] [rbp+40h] BYREF
  unsigned __int64 v165; // [rsp+158h] [rbp+58h]
  char v166; // [rsp+171h] [rbp+71h]
  char v167; // [rsp+1B3h] [rbp+B3h]
  _BYTE v168[400]; // [rsp+1C0h] [rbp+C0h] BYREF
  _BYTE v169[1120]; // [rsp+350h] [rbp+250h] BYREF
  _BYTE v170[4976]; // [rsp+7B0h] [rbp+6B0h] BYREF
  __int64 v171; // [rsp+1B80h] [rbp+1A80h] BYREF
  int v172; // [rsp+1B88h] [rbp+1A88h] BYREF
  char v173; // [rsp+1B90h] [rbp+1A90h] BYREF

  v171 = 3212836864LL;
  sub_180002F70("God Mode", &v171);
  v0 = sub_180071070("God Mode##chk_god_mode", &byte_1800FABEA);
  sub_180003720("Full invincibility: blocks combat damage, fall damage, rob egg damage, and enemy targeting.");
  v1 = "false";
  if ( v0 )
  {
    v2 = byte_1800FABEA;
    v3 = sub_180009470(&v171, v168);
    v145 = 0;
    v146 = 0;
    v147 = 0;
    v4 = sub_1800B9730(v3);
    sub_180015BF0(&v145, v3, v4);
    v5 = "false";
    if ( v2 )
      v5 = "true";
    v161 = 0;
    v162 = 0;
    v163 = 0;
    v6 = sub_1800B9730(v5);
    sub_180015BF0(&v161, v5, v6);
    v7 = sub_180009000(&v172, v170);
    v148 = 0;
    v149 = 0;
    v150 = 0;
    v8 = sub_1800B9730(v7);
    sub_180015BF0(&v148, v7, v8);
    v151 = 0;
    v152 = 0;
    v153 = 0;
    v9 = sub_1800B9730(v5);
    sub_180015BF0(&v151, v5, v9);
    v10 = sub_180008B90(&v173, v169);
    v142 = 0;
    v143 = 0;
    v144 = 0;
    v11 = sub_1800B9730(v10);
    sub_180015BF0(&v142, v10, v11);
    v12 = sub_180015300(v154, &v142, &v151);
    v13 = sub_180015300(v159, v12, &v148);
    v14 = sub_180015300(v164, v13, &v161);
    sub_180015300(v157, v14, &v145);
    if ( v165 > 0xF )
    {
      v15 = (void *)v164[0];
      if ( v165 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v164[0] - *(_QWORD *)(v164[0] - 8LL) - 8LL) > 0x1F )
          __fastfail(5u);
        v15 = *(void **)(v164[0] - 8LL);
      }
      sub_1800931A0(v15);
    }
    v164[2] = 0;
    v165 = 15;
    LOBYTE(v164[0]) = 0;
    if ( v160 > 0xF )
    {
      v16 = (void *)v159[0];
      if ( v160 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v159[0] - *(_QWORD *)(v159[0] - 8LL) - 8LL) > 0x1F )
          __fastfail(5u);
        v16 = *(void **)(v159[0] - 8LL);
      }
      sub_1800931A0(v16);
    }
    v159[2] = 0;
    v160 = 15;
    LOBYTE(v159[0]) = 0;
    if ( v156 > 0xF )
    {
      v17 = (void *)v154[0];
      if ( v156 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v154[0] - *(_QWORD *)(v154[0] - 8LL) - 8LL) > 0x1F )
          __fastfail(5u);
        v17 = *(void **)(v154[0] - 8LL);
      }
      sub_1800931A0(v17);
    }
    v155 = 0;
    v156 = 15;
    LOBYTE(v154[0]) = 0;
    if ( v144 > 0xF )
    {
      v18 = (void *)v142;
      if ( v144 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v142 - *(_QWORD *)(v142 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v18 = *(void **)(v142 - 8);
      }
      sub_1800931A0(v18);
    }
    if ( v169[960] )
    {
      v19 = v169;
      v20 = 960;
      do
      {
        *v19++ = 0;
        --v20;
      }
      while ( v20 );
    }
    if ( v153 > 0xF )
    {
      v21 = (void *)v151;
      if ( v153 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v151 - *(_QWORD *)(v151 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v21 = *(void **)(v151 - 8);
      }
      sub_1800931A0(v21);
    }
    if ( v150 > 0xF )
    {
      v22 = (void *)v148;
      if ( v150 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v148 - *(_QWORD *)(v148 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v22 = *(void **)(v148 - 8);
      }
      sub_1800931A0(v22);
    }
    if ( v170[4972] )
    {
      v23 = v170;
      v24 = 4972;
      do
      {
        *v23++ = 0;
        --v24;
      }
      while ( v24 );
    }
    if ( v163 > 0xF )
    {
      v25 = (void *)v161;
      if ( v163 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v161 - *(_QWORD *)(v161 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v25 = *(void **)(v161 - 8);
      }
      sub_1800931A0(v25);
    }
    if ( v147 > 0xF )
    {
      v26 = (void *)v145;
      if ( v147 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v145 - *(_QWORD *)(v145 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v26 = *(void **)(v145 - 8);
      }
      sub_1800931A0(v26);
    }
    if ( v168[217] )
    {
      v27 = v168;
      v28 = 217;
      do
      {
        *v27++ = 0;
        --v28;
      }
      while ( v28 );
    }
    sub_18002C7A0(v157);
    if ( v158 > 0xF )
    {
      v29 = (void *)v157[0];
      if ( v158 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v157[0] - *(_QWORD *)(v157[0] - 8LL) - 8LL) > 0x1F )
          __fastfail(5u);
        v29 = *(void **)(v157[0] - 8LL);
      }
      sub_1800931A0(v29);
    }
  }
  sub_180003370();
  v30 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v30 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("One Hit Kill", &v171);
  v31 = sub_180071070("One Hit Kill##chk_one_hit", &byte_1800FAC14);
  sub_180003720("Instantly eliminates enemies upon weapon attack.");
  if ( v31 )
    sub_18000FFD0((unsigned __int8)byte_1800FAC14);
  sub_180003370();
  v32 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v32 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Kill Aura", &v171);
  v33 = sub_180071070("Kill Aura##chk_kill_aura", &byte_1800FABF2);
  sub_180003720("Kill all enemy monsters in range.");
  if ( v33 )
    sub_18000CEA0((unsigned __int8)byte_1800FABF2);
  if ( byte_1800FABF2 )
  {
    v36 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v36 + 5216) + 209LL) )
    {
      v171 = 0;
      sub_18004AAD0(&v171);
    }
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Radius##val_kill_aura_rad",
                            (unsigned int)&dword_1800FABF4,
                            v34,
                            v35,
                            "%.1f m",
                            v137) )
      sub_18000CEA0((unsigned __int8)byte_1800FABF2);
    v141 = "Timer tick interval in seconds.";
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Interval##val_kill_aura_int",
                            (unsigned int)&dword_1800FABF8,
                            v37,
                            v38,
                            "%.2f s",
                            v138) )
      sub_18000CEA0((unsigned __int8)byte_1800FABF2);
  }
  sub_180003370();
  v39 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v39 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Catch Aura", &v171);
  v40 = sub_180071070("Catch Aura##chk_catch_aura", &byte_1800FABFC);
  sub_180003720("Periodically detects and quick-captures catchable wild puppets in range.");
  if ( v40 )
    sub_18000E740((unsigned __int8)byte_1800FABFC);
  if ( byte_1800FABFC )
  {
    v43 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v43 + 5216) + 209LL) )
    {
      v171 = 0;
      sub_18004AAD0(&v171);
    }
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Radius##val_catch_aura_rad",
                            (unsigned int)&dword_1800FAC00,
                            v41,
                            v42,
                            "%.1f m",
                            v137) )
      sub_18000E740((unsigned __int8)byte_1800FABFC);
    v141 = "Timer tick interval in seconds.";
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Interval##val_catch_aura_int",
                            (unsigned int)&dword_1800FAC04,
                            v44,
                            v45,
                            "%.2f s",
                            v139) )
      sub_18000E740((unsigned __int8)byte_1800FABFC);
  }
  sub_180003370();
  v46 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v46 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Auto Loot", &v171);
  v47 = sub_180071070("Auto Loot##chk_auto_loot", &byte_1800FAC08);
  sub_180003720("Automatically interacts with dropped items, chests, and resource boxes in range.");
  if ( v47 )
    sub_180011730((unsigned __int8)byte_1800FAC08);
  if ( byte_1800FAC08 )
  {
    v50 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v50 + 5216) + 209LL) )
    {
      v171 = 0;
      sub_18004AAD0(&v171);
    }
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Radius##val_auto_loot_rad",
                            (unsigned int)&dword_1800FAC0C,
                            v48,
                            v49,
                            "%.1f m",
                            v137) )
      sub_180011730((unsigned __int8)byte_1800FAC08);
    v141 = "Interaction check timer interval in seconds.";
    if ( (unsigned __int8)sub_180003890(
                            (unsigned int)"Interval##val_auto_loot_int",
                            (unsigned int)&dword_1800FAC10,
                            v51,
                            v52,
                            "%.2f s",
                            v140) )
      sub_180011730((unsigned __int8)byte_1800FAC08);
  }
  sub_180003370();
  v53 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v53 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Unlimited Dash", &v171);
  v54 = sub_180071070("Unlimited Dash##chk_unlim_dash", &byte_1800FAC15);
  sub_180003720("Removes dash limit, resets dash count and cooldown on press.");
  if ( v54 )
    sub_180010B80((unsigned __int8)byte_1800FAC15);
  sub_180003370();
  v55 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v55 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Multi-Hit", &v171);
  v56 = sub_180071070("Multi-Hit##chk_multi_hit", &byte_1800FABEB);
  sub_180003720("Multiplies weapon attacks and projectile hits.");
  if ( v56 )
    sub_1800098E0((unsigned __int8)byte_1800FABEB, (unsigned int)dword_1800FABEC);
  if ( byte_1800FABEB )
  {
    sub_180071E90();
    v141 = "Number of times to replicate attack/projectile hits.";
    if ( (unsigned __int8)sub_180003B60(
                            (unsigned int)"Hit Multiplier##val_multi_hit",
                            (unsigned int)&dword_1800FABEC,
                            2,
                            50,
                            "%dx",
                            LODWORD(v137)) )
      sub_1800098E0((unsigned __int8)byte_1800FABEB, (unsigned int)dword_1800FABEC);
  }
  sub_180003370();
  v57 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v57 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("No Fall Damage", &v171);
  v58 = sub_180071070("No Fall Damage##chk_nofall", &byte_1800FABE8);
  sub_180003720("Blocks all fall damage when hitting the ground.");
  if ( v58 )
  {
    if ( byte_1800FABE8 )
    {
      v59 = sub_1800079D0(&v171, v168);
      v145 = 0;
      v146 = 0;
      v147 = 0;
      v60 = sub_1800B9730(v59);
      sub_180015BF0(&v145, v59, v60);
      sub_18002C7A0(&v145);
      if ( v147 > 0xF )
      {
        v61 = (void *)v145;
        if ( v147 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v145 - *(_QWORD *)(v145 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v61 = *(void **)(v145 - 8);
        }
        sub_1800931A0(v61);
      }
      if ( v168[389] )
      {
        v62 = v168;
        v63 = 389;
        do
        {
          *v62++ = 0;
          --v63;
        }
        while ( v63 );
      }
    }
    else
    {
      v64 = sub_180007E40(&v171, v168);
      v145 = 0;
      v146 = 0;
      v147 = 0;
      v65 = sub_1800B9730(v64);
      sub_180015BF0(&v145, v64, v65);
      sub_18002C7A0(&v145);
      if ( v147 > 0xF )
      {
        v66 = (void *)v145;
        if ( v147 + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(v145 - *(_QWORD *)(v145 - 8) - 8) > 0x1F )
            __fastfail(5u);
          v66 = *(void **)(v145 - 8);
        }
        sub_1800931A0(v66);
      }
      if ( v168[338] )
      {
        v67 = v168;
        v68 = 338;
        do
        {
          *v67++ = 0;
          --v68;
        }
        while ( v68 );
      }
    }
  }
  sub_180003370();
  v69 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v69 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("No Cooldown", &v171);
  v70 = sub_180071070("No Cooldown##chk_nocd_full", &byte_1800FAC17);
  sub_180003720("Removes all skill cooldowns for both the player character and pet abilities.");
  if ( v70 )
  {
    byte_1800FAC18 = byte_1800FAC17;
    byte_1800FAC19 = byte_1800FAC17;
    sub_18000BCB0((unsigned __int8)byte_1800FAC17, (unsigned __int8)byte_1800FAC17);
  }
  if ( byte_1800FAC17 || byte_1800FAC18 || byte_1800FAC19 )
  {
    v71 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v71 + 5216) + 209LL) )
    {
      v171 = 0;
      sub_18004AAD0(&v171);
      v71 = qword_18010C470;
    }
    *(_BYTE *)(*(_QWORD *)(v71 + 5216) + 206LL) = 1;
    v72 = *(float **)(v71 + 5216);
    v73 = v72[87] + 15.0;
    v72[87] = v73;
    v72[70] = (float)(v73 + v72[10]) + v72[88];
    v74 = sub_180071070("Player No Cooldown##chk_nocd_player", &byte_1800FAC18);
    sub_180003720("Removes cooldowns for player weapon and character skills.");
    if ( v74 )
    {
      if ( !byte_1800FAC18 || (byte_1800FAC17 = 1, !byte_1800FAC19) )
        byte_1800FAC17 = 0;
      sub_18000BCB0((unsigned __int8)byte_1800FAC18, (unsigned __int8)byte_1800FAC19);
    }
    v75 = sub_180071070("Pet No CD##chk_nocd_pet", &byte_1800FAC19);
    sub_180003720("Removes cooldowns for pet support abilities.");
    if ( v75 )
    {
      if ( !byte_1800FAC18 || (byte_1800FAC17 = 1, !byte_1800FAC19) )
        byte_1800FAC17 = 0;
      sub_18000BCB0((unsigned __int8)byte_1800FAC18, (unsigned __int8)byte_1800FAC19);
    }
    v76 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v77 = *(float **)(v76 + 5216);
    v78 = v77[87] - 15.0;
    v77[87] = v78;
    v77[70] = (float)(v78 + v77[10]) + v77[88];
  }
  sub_180003370();
  v79 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v79 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Infinite Stamina", &v171);
  v80 = sub_180071070("Infinite Stamina##chk_inf_stamina", &byte_1800FABF0);
  sub_180003720("Blocks all stamina consumption for local player and pet while running, climbing, dodging.");
  v81 = 115;
  if ( v80 )
  {
    v82 = byte_1800FABF0;
    v83 = sub_18000AF50(&v171, v169);
    v142 = 0;
    v143 = 0;
    v144 = 0;
    v84 = sub_1800B9730(v83);
    sub_180015BF0(&v142, v83, v84);
    v85 = "false";
    if ( v82 )
      v85 = "true";
    v151 = 0;
    v152 = 0;
    v153 = 0;
    v86 = sub_1800B9730(v85);
    sub_180015BF0(&v151, v85, v86);
    v87 = sub_18000AAD0(&v172, v164);
    v148 = 0;
    v149 = 0;
    v150 = 0;
    v88 = sub_1800B9730(v87);
    sub_180015BF0(&v148, v87, v88);
    v89 = sub_180015300(v154, &v148, &v151);
    sub_180015300(v157, v89, &v142);
    sub_180015D80(v154);
    if ( v150 > 0xF )
      sub_180016150(&v148, v148);
    if ( v167 )
    {
      v90 = v164;
      v91 = 115;
      do
      {
        *v90++ = 0;
        --v91;
      }
      while ( v91 );
    }
    if ( v153 > 0xF )
      sub_180016150(&v151, v151);
    if ( v144 > 0xF )
      sub_180016150(&v142, v142);
    if ( v169[966] )
    {
      v92 = v169;
      v93 = 966;
      do
      {
        *v92++ = 0;
        --v93;
      }
      while ( v93 );
    }
    sub_18002C7A0(v157);
    sub_180015D80(v157);
  }
  sub_180003370();
  v94 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v94 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Infinite Energy", &v171);
  v95 = sub_180071070("Infinite Energy (EP + SP)##chk_inf_energy", &byte_1800FABF1);
  sub_180003720("Locks Energy Points and Special / Ultimate Points to maximum capacity.");
  if ( v95 )
  {
    v96 = byte_1800FABF1;
    v97 = sub_18000B840(&v171, v169);
    v148 = 0;
    v149 = 0;
    v150 = 0;
    v98 = sub_1800B9730(v97);
    sub_180015BF0(&v148, v97, v98);
    if ( v96 )
      v1 = "true";
    v151 = 0;
    v152 = 0;
    v153 = 0;
    v99 = sub_1800B9730(v1);
    sub_180015BF0(&v151, v1, v99);
    v100 = sub_18000B3C0(&v172, v164);
    v142 = 0;
    v143 = 0;
    v144 = 0;
    v101 = sub_1800B9730(v100);
    sub_180015BF0(&v142, v100, v101);
    v102 = sub_180015300(v154, &v142, &v151);
    sub_180015300(v157, v102, &v148);
    sub_180015D80(v154);
    if ( v144 > 0xF )
      sub_180016150(&v142, v142);
    if ( v167 )
    {
      v103 = v164;
      do
      {
        *v103++ = 0;
        --v81;
      }
      while ( v81 );
    }
    if ( v153 > 0xF )
      sub_180016150(&v151, v151);
    if ( v150 > 0xF )
      sub_180016150(&v148, v148);
    if ( v169[1109] )
    {
      v104 = v169;
      v105 = 1109;
      do
      {
        *v104++ = 0;
        --v105;
      }
      while ( v105 );
    }
    sub_18002C7A0(v157);
    sub_180015D80(v157);
  }
  sub_180003370();
  v106 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v106 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Dumb Enemy", &v171);
  v107 = sub_180071070("Dumb Enemy##chk_dumb_enemy", &byte_1800FABE9);
  sub_180003720("Disables AI global tick so enemies stop attacking and moving.");
  if ( v107 )
  {
    if ( byte_1800FABE9 )
    {
      v108 = sub_1800082B0(&v171, v168);
      v142 = 0;
      v143 = 0;
      v144 = 0;
      v109 = sub_1800B9730(v108);
      sub_180015BF0(&v142, v108, v109);
      sub_18002C7A0(&v142);
      if ( v144 > 0xF )
        sub_180016150(&v142, v142);
      if ( v168[294] )
      {
        v110 = v168;
        v111 = 294;
        do
        {
          *v110++ = 0;
          --v111;
        }
        while ( v111 );
      }
    }
    else
    {
      v112 = sub_180008720(&v171, v168);
      v142 = 0;
      v143 = 0;
      v144 = 0;
      v113 = sub_1800B9730(v112);
      sub_180015BF0(&v142, v112, v113);
      sub_18002C7A0(&v142);
      if ( v144 > 0xF )
        sub_180016150(&v142, v142);
      if ( v168[293] )
      {
        v114 = v168;
        v115 = 293;
        do
        {
          *v114++ = 0;
          --v115;
        }
        while ( v115 );
      }
    }
  }
  sub_180003370();
  v116 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v116 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Mob Vacuum", &v171);
  v117 = sub_180071070("Mob Vacuum##chk_mob_vacuum", &byte_1800FABDC);
  sub_180003720("Pulls wild enemies in front of you.");
  if ( v117 )
  {
    if ( !byte_1800FABDC )
      goto LABEL_217;
    sub_1800048E0();
  }
  if ( byte_1800FABDC )
  {
    sub_180071E90();
    v141 = "Distance ahead of player to pull enemies.";
    sub_180003890(
      (unsigned int)"Distance in front##val_vacuum_dist",
      (unsigned int)&dword_1800FABE0,
      v118,
      v119,
      "%.1f m",
      v137);
    sub_180071070("Continuous Auto Vacuum##chk_auto_vacuum", &byte_1800FABDD);
    sub_180003720("Continuously pulls enemies in front as you move.");
    v171 = 0x41D00000BF800000LL;
    if ( (unsigned __int8)sub_18006FED0("Pull Mobs Now##btn_vacuum_pull", &v171) )
      sub_1800048E0();
  }
LABEL_217:
  sub_180003370();
  v120 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( !*(_BYTE *)(*(_QWORD *)(v120 + 5216) + 209LL) )
  {
    v171 = 0;
    sub_18004AAD0(&v171);
  }
  v171 = 3212836864LL;
  sub_180002F70("Scene Teleport", &v171);
  sub_18006F370("Scene ID:");
  v121 = qword_18010C470;
  *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
  *(_DWORD *)(v121 + 7712) = -1082130432;
  LODWORD(v171) = 100;
  v172 = 1;
  sub_180076EF0(v123, v122, (unsigned int)&dword_1800FABE4, (unsigned int)&v172, (__int64)&v171, "%d", (_DWORD)v141);
  v171 = 0x41D00000BF800000LL;
  if ( (unsigned __int8)sub_18006FED0("Teleport to Scene ID##tp_scene_btn", &v171) )
  {
    v124 = sub_180014EA0(&v171, &v148);
    v125 = sub_180002BF0(v154, (unsigned int)dword_1800FABE4);
    v126 = sub_180014A30(&v172, v164);
    v145 = 0;
    v146 = 0;
    v147 = 0;
    v127 = sub_1800B9730(v126);
    sub_180015BF0(&v145, v126, v127);
    v128 = sub_180015300(v159, &v145, v125);
    v129 = sub_1800154F0(v157, v128, v124);
    sub_18002C7A0(v129);
    sub_180015D80(v157);
    sub_180015D80(v159);
    if ( v147 > 0xF )
    {
      v130 = (void *)v145;
      if ( v147 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v145 - *(_QWORD *)(v145 - 8) - 8) > 0x1F )
          __fastfail(5u);
        v130 = *(void **)(v145 - 8);
      }
      sub_1800931A0(v130);
    }
    if ( v166 )
    {
      v131 = v164;
      v132 = 49;
      do
      {
        *v131++ = 0;
        --v132;
      }
      while ( v132 );
    }
    if ( v156 > 0xF )
    {
      v133 = (void *)v154[0];
      if ( v156 + 1 >= 0x1000 )
      {
        if ( (unsigned __int64)(v154[0] - *(_QWORD *)(v154[0] - 8LL) - 8LL) > 0x1F )
          __fastfail(5u);
        v133 = *(void **)(v154[0] - 8LL);
      }
      sub_1800931A0(v133);
    }
    v155 = 0;
    v156 = 15;
    LOBYTE(v154[0]) = 0;
    if ( BYTE11(v148) )
    {
      v134 = &v148;
      v135 = 11;
      do
      {
        *(_BYTE *)v134 = 0;
        v134 = (__int128 *)((char *)v134 + 1);
        --v135;
      }
      while ( v135 );
    }
  }
  return sub_180003370();
}
