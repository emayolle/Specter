// sub_180080710 size=13338
char __fastcall sub_180080710(_BYTE *a1, float *a2, int a3, float *a4)
{
  __int64 v4; // r15
  _BYTE *v6; // r12
  __int64 v7; // r13
  __int64 v9; // rdi
  double v10; // xmm0_8
  int v11; // r14d
  float v12; // xmm8_4
  __int64 v13; // rdx
  int v14; // ebx
  int v15; // r15d
  int v16; // eax
  __int64 v17; // rdx
  __int64 v18; // r14
  __int64 v19; // rdx
  __int64 v20; // rcx
  __int64 v21; // r8
  __int64 v22; // r9
  float v23; // xmm2_4
  __int64 v24; // rcx
  unsigned int v25; // r12d
  int v26; // xmm6_4
  int v27; // xmm7_4
  __int64 v28; // rcx
  __int64 v29; // r8
  __int64 v30; // rax
  __int64 v31; // rdx
  __int64 v32; // r8
  __int64 v33; // r9
  __int64 v34; // rcx
  int v35; // eax
  unsigned int v36; // esi
  __int64 v37; // rdx
  int v38; // xmm6_4
  int v39; // xmm7_4
  __int64 v40; // rcx
  __int64 v41; // r8
  __int64 v42; // rax
  __int64 v43; // rcx
  int v44; // eax
  int v45; // ecx
  int v46; // esi
  int v47; // esi
  float v48; // xmm1_4
  char v49; // bl
  __int128 v50; // xmm6
  unsigned __int64 v51; // xmm10_8
  __m128 v52; // xmm12
  float v53; // xmm2_4
  float v54; // xmm7_4
  __m128 v55; // xmm14
  __m128 v56; // xmm15
  __m128 v57; // xmm11
  int v58; // r8d
  float v59; // xmm13_4
  __int64 v60; // rcx
  float v61; // xmm3_4
  _DWORD *v62; // r13
  __int64 v63; // rdx
  __int128 v64; // xmm7
  float v65; // xmm2_4
  float v66; // xmm3_4
  __int64 v67; // rax
  float v68; // xmm1_4
  float v69; // xmm4_4
  float v70; // xmm0_4
  int v71; // ecx
  float v72; // xmm9_4
  float v73; // xmm10_4
  float v74; // xmm7_4
  float v75; // xmm11_4
  float v76; // xmm2_4
  __int128 v77; // xmm0
  char v78; // r14
  double v79; // xmm0_8
  float v80; // xmm12_4
  double v81; // xmm0_8
  float v82; // xmm6_4
  float v83; // xmm7_4
  float v84; // xmm3_4
  float v85; // xmm2_4
  float v86; // xmm4_4
  float v87; // xmm11_4
  float v88; // xmm3_4
  float v89; // xmm1_4
  float v90; // xmm9_4
  float v91; // xmm1_4
  float v92; // xmm2_4
  float v93; // xmm10_4
  float v94; // xmm4_4
  float v95; // xmm5_4
  float v96; // xmm4_4
  float v97; // xmm2_4
  float v98; // xmm12_4
  float v99; // xmm5_4
  float v100; // xmm2_4
  float v101; // xmm5_4
  float v102; // xmm1_4
  float v103; // xmm1_4
  float v104; // xmm4_4
  float v105; // xmm6_4
  float v106; // xmm6_4
  float v107; // xmm7_4
  float v108; // xmm3_4
  float v109; // xmm0_4
  float v110; // xmm7_4
  float v111; // xmm3_4
  float v112; // xmm1_4
  float v113; // xmm4_4
  float v114; // xmm0_4
  float v115; // xmm7_4
  __int64 v116; // r14
  float v117; // xmm2_4
  __int64 v118; // rcx
  __int64 v119; // rax
  int v120; // ecx
  float v121; // xmm1_4
  float v122; // xmm2_4
  __int64 v123; // r9
  int v124; // eax
  float v125; // xmm0_4
  float v126; // xmm7_4
  float v127; // xmm0_4
  float v128; // xmm0_4
  float v129; // xmm1_4
  int v130; // eax
  int v131; // eax
  __int64 v132; // rax
  __int64 v133; // rax
  int v134; // ecx
  bool v135; // zf
  float v136; // xmm1_4
  __int128 v137; // xmm0
  _BYTE *v138; // rdx
  __int64 v139; // rcx
  int v140; // r8d
  int v141; // xmm2_4
  float *v142; // r12
  float v143; // xmm1_4
  int v144; // xmm2_4
  int v145; // xmm1_4
  float v146; // xmm11_4
  float v147; // xmm6_4
  __int64 v148; // r9
  int v149; // xmm1_4
  int v150; // eax
  __int64 v151; // r9
  char v152; // r15
  int v153; // r14d
  int v154; // ebx
  int v155; // eax
  float *v156; // r10
  unsigned int v157; // xmm7_4
  float v158; // xmm9_4
  float v159; // xmm11_4
  __int64 v160; // r10
  float v161; // xmm6_4
  float v162; // xmm0_4
  int v163; // ebx
  int v164; // r14d
  int v165; // r12d
  float v166; // eax
  unsigned __int64 v167; // r8
  int v168; // r9d
  unsigned int v169; // eax
  unsigned int v170; // r13d
  float v171; // xmm6_4
  int v172; // r15d
  int *v173; // rsi
  float v174; // xmm9_4
  float v175; // xmm10_4
  float v176; // xmm1_4
  int v177; // r13d
  int i; // r12d
  __int64 v179; // rbx
  float v180; // xmm13_4
  float v181; // xmm14_4
  float v182; // xmm11_4
  double v183; // xmm0_8
  __int64 v184; // rdx
  float v185; // xmm7_4
  unsigned __int64 v186; // r15
  float v187; // xmm12_4
  float v188; // xmm10_4
  int v189; // edx
  int v190; // ecx
  int v191; // r10d
  int v192; // r11d
  float v193; // xmm3_4
  float v194; // xmm4_4
  float v195; // xmm5_4
  float v196; // xmm6_4
  float v197; // xmm7_4
  float v198; // xmm9_4
  float v199; // xmm1_4
  float v200; // xmm2_4
  float v201; // xmm1_4
  float v202; // xmm2_4
  float v203; // xmm1_4
  float v204; // xmm2_4
  float v205; // xmm1_4
  float v206; // xmm2_4
  float v207; // xmm1_4
  float v208; // xmm2_4
  double v209; // xmm0_8
  float v210; // xmm13_4
  double v211; // xmm0_8
  float v212; // xmm14_4
  float v213; // xmm9_4
  float v214; // xmm9_4
  int v215; // eax
  int v216; // r8d
  int v217; // r9d
  float v218; // r14d
  float v219; // ebx
  __int64 v220; // rsi
  int *v221; // rax
  __int64 v222; // rbx
  int v223; // xmm6_4
  int v224; // xmm7_4
  float v225; // xmm10_4
  int v226; // r12d
  int v227; // r15d
  int v228; // r8d
  __int16 v229; // dx
  __int16 v230; // dx
  __int64 v231; // r14
  void *v232; // rcx
  int v233; // r11d
  int v234; // ecx
  int v235; // edx
  __int64 v236; // r9
  __int64 v237; // rax
  float v238; // xmm2_4
  float v239; // xmm3_4
  float v240; // xmm1_4
  float v241; // xmm0_4
  float v242; // xmm1_4
  float v243; // xmm0_4
  float v244; // xmm2_4
  float v245; // xmm3_4
  float v246; // xmm1_4
  float v247; // xmm0_4
  float v248; // xmm1_4
  float v249; // xmm0_4
  float v250; // xmm2_4
  float v251; // xmm3_4
  float v252; // xmm1_4
  float v253; // xmm0_4
  float v254; // xmm1_4
  float v255; // xmm0_4
  float v256; // xmm2_4
  float v257; // xmm3_4
  float v258; // xmm1_4
  float v259; // xmm0_4
  float v260; // xmm1_4
  float v261; // xmm0_4
  float v262; // xmm2_4
  float v263; // xmm3_4
  float v264; // xmm1_4
  float v265; // xmm0_4
  float v266; // xmm1_4
  float v267; // xmm0_4
  __int16 v268; // r13
  int v269; // r10d
  float v270; // xmm10_4
  float v271; // xmm1_4
  float v272; // xmm2_4
  float v273; // xmm3_4
  float v274; // xmm4_4
  float v275; // xmm3_4
  float v276; // xmm4_4
  __int16 v277; // r11
  float v278; // xmm4_4
  float v279; // xmm3_4
  __int16 v280; // dx
  __int64 v281; // rax
  __int16 v282; // cx
  __int16 v283; // r11
  __int64 v284; // rax
  int v285; // eax
  __int64 v286; // rdx
  __int64 v287; // xmm0_8
  __int64 v288; // rax
  int v289; // edx
  __int16 v290; // cx
  int v291; // r8d
  int v292; // xmm6_4
  float v293; // xmm9_4
  float v294; // xmm10_4
  float v295; // xmm1_4
  float v296; // xmm11_4
  float v297; // xmm12_4
  float v298; // xmm14_4
  int v299; // xmm7_4
  float *v300; // rax
  __int64 v301; // rax
  _WORD *v302; // rax
  float *v303; // rax
  float v304; // edx
  float v305; // xmm13_4
  __int64 v306; // rax
  float *v307; // rax
  __int64 v308; // rax
  int v309; // ecx
  int v310; // r8d
  int v311; // eax
  __int64 v312; // rcx
  __int64 v313; // rax
  int v314; // r8d
  int v315; // ecx
  int v316; // r8d
  int v317; // eax
  __int64 v318; // rcx
  __int64 v319; // rax
  int v320; // r8d
  int v321; // ecx
  int v322; // r8d
  int v323; // eax
  __int64 v324; // rcx
  __int64 v325; // rax
  float v326; // xmm1_4
  float v327; // xmm0_4
  float v328; // xmm11_4
  __m128 v329; // xmm9
  __m128 v330; // xmm7
  float v331; // xmm1_4
  float v332; // xmm0_4
  float v333; // xmm2_4
  float v334; // xmm0_4
  float v335; // xmm1_4
  float v336; // xmm2_4
  float v337; // xmm6_4
  __int64 v338; // rax
  int v339; // ebx
  __m128 v340; // xmm2
  float v341; // xmm12_4
  int v342; // r9d
  float v343; // xmm6_4
  int v344; // eax
  int v345; // r8d
  int v346; // r9d
  int v347; // ebx
  int v348; // r8d
  float v349; // xmm0_4
  __m128 v350; // xmm10
  __m128 v351; // xmm13
  __m128 v352; // xmm7
  float v353; // xmm11_4
  float v354; // xmm3_4
  unsigned int v355; // eax
  int v356; // r11d
  int v357; // ebx
  float v358; // xmm3_4
  float v359; // xmm12_4
  float v360; // xmm2_4
  int v361; // esi
  float v362; // xmm11_4
  float v363; // xmm15_4
  float v364; // xmm9_4
  float v365; // xmm10_4
  float j; // xmm6_4
  float v367; // xmm1_4
  float v368; // xmm0_4
  int v369; // edx
  int v370; // eax
  int v371; // eax
  int v372; // ecx
  unsigned __int64 v373; // rdx
  float v374; // xmm7_4
  float v375; // xmm1_4
  __m128 v376; // xmm9
  float v377; // xmm0_4
  float v378; // xmm7_4
  __m128 v379; // xmm13
  float v380; // xmm0_4
  __m128 v381; // xmm11
  __m128 v382; // xmm12
  int v383; // r12d
  int v384; // r8d
  int *v385; // r15
  int v386; // ecx
  int v387; // r8d
  int v388; // eax
  __int64 v389; // rcx
  __int64 v390; // rax
  int v391; // r14d
  int v392; // esi
  int *v393; // rax
  __int64 v394; // rbx
  int v395; // xmm6_4
  int v396; // xmm7_4
  float v397; // xmm10_4
  int v398; // r13d
  int v399; // r8d
  __int16 v400; // r11
  __int16 v401; // dx
  __int16 v402; // dx
  __int64 v403; // r15
  void *v404; // rcx
  int v405; // edx
  int v406; // ecx
  __int64 v407; // r9
  __int64 v408; // rax
  float v409; // xmm2_4
  float v410; // xmm3_4
  float v411; // xmm1_4
  float v412; // xmm0_4
  float v413; // xmm1_4
  float v414; // xmm0_4
  float v415; // xmm2_4
  float v416; // xmm3_4
  float v417; // xmm1_4
  float v418; // xmm0_4
  float v419; // xmm1_4
  float v420; // xmm0_4
  float v421; // xmm2_4
  float v422; // xmm3_4
  float v423; // xmm1_4
  float v424; // xmm0_4
  float v425; // xmm1_4
  float v426; // xmm0_4
  float v427; // xmm2_4
  float v428; // xmm3_4
  float v429; // xmm1_4
  float v430; // xmm0_4
  float v431; // xmm1_4
  float v432; // xmm0_4
  float v433; // xmm2_4
  float v434; // xmm3_4
  float v435; // xmm1_4
  float v436; // xmm0_4
  float v437; // xmm1_4
  float v438; // xmm0_4
  float v439; // xmm10_4
  int v440; // r10d
  float v441; // xmm1_4
  float v442; // xmm3_4
  float v443; // xmm2_4
  float v444; // xmm4_4
  float v445; // xmm2_4
  float v446; // xmm4_4
  __int16 v447; // r14
  float v448; // xmm4_4
  __int16 v449; // r8
  float v450; // xmm2_4
  __int64 v451; // rax
  __int16 v452; // cx
  __int16 v453; // r14
  __int64 v454; // rax
  int v455; // eax
  __int64 v456; // rdx
  __int64 v457; // xmm0_8
  __int64 v458; // rax
  int k; // edx
  __int16 v460; // cx
  float v461; // xmm6_4
  __m128 v462; // xmm0
  char v463; // bl
  __int64 v464; // rax
  __int64 v465; // rcx
  __int64 v466; // rdx
  int v467; // ecx
  int v468; // [rsp+20h] [rbp-E0h]
  int v469; // [rsp+28h] [rbp-D8h]
  char v470; // [rsp+40h] [rbp-C0h]
  char v471; // [rsp+41h] [rbp-BFh]
  char v472; // [rsp+42h] [rbp-BEh]
  char v473; // [rsp+43h] [rbp-BDh]
  float v474; // [rsp+44h] [rbp-BCh]
  float v475; // [rsp+48h] [rbp-B8h]
  float v476; // [rsp+4Ch] [rbp-B4h]
  float v477; // [rsp+50h] [rbp-B0h]
  float v478; // [rsp+50h] [rbp-B0h]
  float v479; // [rsp+54h] [rbp-ACh] BYREF
  __int64 v480; // [rsp+58h] [rbp-A8h]
  float v481; // [rsp+60h] [rbp-A0h] BYREF
  float v482; // [rsp+68h] [rbp-98h] BYREF
  float v483; // [rsp+70h] [rbp-90h] BYREF
  float v484; // [rsp+74h] [rbp-8Ch]
  int v485; // [rsp+78h] [rbp-88h]
  float v486; // [rsp+7Ch] [rbp-84h]
  int v487; // [rsp+80h] [rbp-80h] BYREF
  unsigned __int64 v488; // [rsp+88h] [rbp-78h] BYREF
  float v489; // [rsp+90h] [rbp-70h] BYREF
  float v490; // [rsp+94h] [rbp-6Ch]
  float v491; // [rsp+98h] [rbp-68h] BYREF
  unsigned __int64 v492; // [rsp+A0h] [rbp-60h] BYREF
  float v493; // [rsp+A8h] [rbp-58h] BYREF
  float v494; // [rsp+ACh] [rbp-54h]
  unsigned int v495; // [rsp+B0h] [rbp-50h]
  __int64 v496; // [rsp+B8h] [rbp-48h] BYREF
  float v497[2]; // [rsp+C0h] [rbp-40h] BYREF
  float v498; // [rsp+C8h] [rbp-38h] BYREF
  float v499; // [rsp+CCh] [rbp-34h]
  __int128 v500; // [rsp+D0h] [rbp-30h] BYREF
  float v501; // [rsp+E0h] [rbp-20h]
  int v502; // [rsp+E4h] [rbp-1Ch]
  float v503; // [rsp+E8h] [rbp-18h]
  unsigned int v504; // [rsp+ECh] [rbp-14h]
  unsigned int v505; // [rsp+F0h] [rbp-10h] BYREF
  float v506; // [rsp+F4h] [rbp-Ch]
  float v507; // [rsp+F8h] [rbp-8h]
  unsigned __int64 v508; // [rsp+100h] [rbp+0h] BYREF
  int v509; // [rsp+108h] [rbp+8h]
  int v510; // [rsp+10Ch] [rbp+Ch]
  int v511; // [rsp+110h] [rbp+10h]
  int v512; // [rsp+114h] [rbp+14h]
  int v513; // [rsp+118h] [rbp+18h]
  float v514; // [rsp+120h] [rbp+20h]
  float v515; // [rsp+124h] [rbp+24h]
  float v516; // [rsp+128h] [rbp+28h]
  __m128 v517; // [rsp+130h] [rbp+30h] BYREF
  float v518; // [rsp+140h] [rbp+40h] BYREF
  float v519; // [rsp+144h] [rbp+44h]
  int v520; // [rsp+148h] [rbp+48h]
  int v521; // [rsp+14Ch] [rbp+4Ch]
  int v522; // [rsp+150h] [rbp+50h]
  float v523[2]; // [rsp+158h] [rbp+58h] BYREF
  float v524[2]; // [rsp+160h] [rbp+60h] BYREF
  __int64 v525; // [rsp+168h] [rbp+68h]
  _BYTE v526[16]; // [rsp+170h] [rbp+70h] BYREF

  v4 = qword_18010C470;
  v6 = a1;
  v480 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v7 = *(_QWORD *)(v4 + 5216);
  if ( *(_BYTE *)(v7 + 209) )
    return 0;
  v9 = *(_QWORD *)(v7 + 712);
  v10 = sub_18004AE40();
  v11 = (*(_DWORD *)(v4 + 7680) | *(_DWORD *)(v4 + 7692)) & 0x800;
  *(_QWORD *)(v4 + 7688) = 0;
  v481 = *(float *)&v11;
  v12 = *(float *)&v10;
  sub_1800466C0(v6);
  v522 = *(_DWORD *)(v4 + 9564);
  if ( !v522 )
    *(_DWORD *)(v4 + 9564) = *(_DWORD *)(*(_QWORD *)(v7 + 272) + 4LL * *(int *)(v7 + 264) - 4);
  sub_18004AFD0();
  v13 = 16;
  v14 = a3 | 0x10;
  if ( (a3 & 0x100) != 0 )
    v14 = a3;
  if ( (v14 & 8) == 0 )
  {
    LODWORD(v479) = v14 & 0x10002;
    v15 = v14 & 0x6000000;
    if ( (v14 & 0x6000000) == 0 || (v14 & 0x10002) == 0 )
    {
      if ( *(_DWORD *)(qword_18010C470 + 8048) > *(_DWORD *)(qword_18010C470 + 8064) )
      {
        v16 = sub_1800465E0(*(_QWORD *)(qword_18010C470 + 5216), "context");
        if ( sub_18004C6E0(v16) )
        {
          v18 = qword_18010C470;
          LOBYTE(v17) = 1;
          sub_180045260(0x10000, v17);
          if ( !v15 )
          {
            v23 = *(float *)(qword_18010C470 + 3216);
            v498 = *(float *)(v18 + 4432) * 8.0;
            v499 = fmaxf(
                     v498
                   - (float)((float)((float)(v23 + v23) + *(float *)(qword_18010C470 + 4432)) + *(float *)(v18 + 3236)),
                     1.0);
            sub_18004ACF0();
            sub_1800467B0(0);
            v24 = *(_QWORD *)(qword_18010C470 + 5216);
            v25 = v14 & 2 | 0x20001A8;
            v26 = *(_DWORD *)(v24 + 280);
            v27 = *(_DWORD *)(v24 + 284);
            if ( (unsigned __int8)sub_180084D20("##selectable", 0, 0, &v498) )
              *(_DWORD *)(v18 + 9560) = v25 ^ (*(_DWORD *)(v18 + 9560) ^ v25) & 0xF9FFFFFF;
            v28 = qword_18010C470;
            v29 = 16;
            *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
            v30 = *(_QWORD *)(v28 + 5216);
            *(_DWORD *)(v30 + 280) = v26;
            *(_DWORD *)(v30 + 284) = v27;
            *(_BYTE *)(v30 + 345) = 1;
            if ( (v14 & 2) != 0 )
              v29 = 12;
            v517 = 0;
            sub_1800B8BD0(&v517, a2, v29);
            sub_180080710("##previewing_picker", &v517, v25, 0);
            v34 = *(_QWORD *)(qword_18010C470 + 5216);
            v35 = *(_DWORD *)(v34 + 264);
            if ( v35 > 1 )
              *(_DWORD *)(v34 + 264) = v35 - 1;
            else
              sub_180049A30("Calling PopID() too many times!");
            sub_180071F50(v34, v31, v32, v33);
            sub_1800467B0(1);
            v36 = v14 & 2 | 0x40001A8;
            v37 = *(_QWORD *)(qword_18010C470 + 5216);
            v38 = *(_DWORD *)(v37 + 280);
            v39 = *(_DWORD *)(v37 + 284);
            if ( (unsigned __int8)sub_180084D20("##selectable", 0, 0, &v498) )
              *(_DWORD *)(v18 + 9560) = v36 ^ (*(_DWORD *)(v18 + 9560) ^ v36) & 0xF9FFFFFF;
            v40 = qword_18010C470;
            v41 = 16;
            *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
            v42 = *(_QWORD *)(v40 + 5216);
            *(_DWORD *)(v42 + 280) = v38;
            *(_DWORD *)(v42 + 284) = v39;
            *(_BYTE *)(v42 + 345) = 1;
            if ( (v14 & 2) != 0 )
              v41 = 12;
            v517 = 0;
            sub_1800B8BD0(&v517, a2, v41);
            sub_180080710("##previewing_picker", &v517, v36, 0);
            v43 = *(_QWORD *)(qword_18010C470 + 5216);
            v44 = *(_DWORD *)(v43 + 264);
            if ( v44 > 1 )
              *(_DWORD *)(v43 + 264) = v44 - 1;
            else
              sub_180049A30("Calling PopID() too many times!");
            sub_18004ADF0();
            v6 = a1;
          }
          if ( v479 == 0.0 )
          {
            if ( !v15 )
              sub_180071F50(v20, v19, v21, v22);
            sub_1800717A0(v20, (int *)(v18 + 9560), v21);
          }
          sub_180045340();
          sub_18004C770();
          *(float *)&v11 = v481;
        }
        v13 = 16;
      }
      else
      {
        *(_DWORD *)(qword_18010C470 + 7824) = 0;
      }
    }
    v4 = v480;
  }
  v45 = 177209344;
  if ( (v14 & 0x6000000) != 0 )
  {
    v47 = v14;
  }
  else
  {
    v46 = 177209344;
    if ( (*(_DWORD *)(v4 + 9560) & 0x6000000) != 0 )
      v46 = *(_DWORD *)(v4 + 9560);
    v47 = v14 | v46 & 0x6000000;
  }
  if ( (v47 & 0x18000000) == 0 )
  {
    if ( (*(_DWORD *)(v4 + 9560) & 0x18000000) != 0 )
      v45 = *(_DWORD *)(v4 + 9560);
    v47 |= v45 & 0x18000000;
  }
  if ( (v47 & 8) == 0 )
    v47 |= *(_DWORD *)(v4 + 9560) & 0x10000;
  if ( (v47 & 0x10000) == 0 || (v47 & 2) != 0 )
  {
    v50 = 0x3F800000u;
    v49 = 0;
    v48 = 1.0;
  }
  else
  {
    v48 = 2.0;
    v49 = 1;
    v50 = 0x3F800000u;
  }
  v51 = *(_QWORD *)(v7 + 280);
  v52 = (__m128)v51;
  v473 = v49;
  if ( (v47 & 2) != 0 )
    v13 = 12;
  v508 = v51;
  v53 = *(float *)(qword_18010C470 + 3216);
  v525 = v13;
  v492 = v51;
  v477 = (float)(v53 + v53) + *(float *)(qword_18010C470 + 4432);
  v497[0] = *(float *)(v480 + 3236);
  v55 = (__m128)LODWORD(v497[0]);
  v57 = (__m128)LODWORD(v497[0]);
  v54 = fmaxf(v477, v12 - (float)(v48 * (float)(v497[0] + v477)));
  v52.m128_f32[0] = *(float *)&v51 + v54;
  v474 = v54;
  v55.m128_f32[0] = v497[0] + (float)(*(float *)&v51 + v54);
  v481 = *(float *)&v51 + v54;
  v516 = (float)(int)(float)(v477 * 0.2);
  v56 = v55;
  v57.m128_f32[0] = v497[0] + (float)(v55.m128_f32[0] + v477);
  v517 = v57;
  sub_1800B8BD0(v526, a2, v13);
  v59 = v54 * 0.5;
  v499 = 0.0;
  v479 = v54 * 0.5;
  v515 = v54 * 0.079999998;
  v506 = (float)(v54 * 0.5) - (float)(v54 * 0.079999998);
  v494 = (float)((float)(v54 + v477) * 0.5) + *(float *)&v51;
  v483 = v494;
  v486 = (float)(v54 * 0.5) + *((float *)&v51 + 1);
  v484 = v486;
  v498 = v506 - (float)(int)(float)(v54 * 0.027000001);
  v514 = v498 * -0.5;
  v524[0] = v498 * -0.5;
  v523[0] = v498 * -0.5;
  v507 = v498 * -0.86602497;
  v524[1] = v498 * -0.86602497;
  v60 = 2;
  v61 = a2[1];
  v62 = a2 + 1;
  v63 = 4;
  v64 = *(unsigned int *)a2;
  v65 = a2[2];
  v488 = (unsigned __int64)(a2 + 2);
  v501 = v498 * 0.86602497;
  v485 = v47 & 0x8000000;
  v523[1] = v498 * 0.86602497;
  v482 = *(float *)&v64;
  v475 = v61;
  v491 = v61;
  v476 = v65;
  v493 = v65;
  v504 = v64;
  v505 = v64;
  v503 = v61;
  *(float *)&v496 = v61;
  *(float *)&v502 = v65;
  *(float *)&v487 = v65;
  v500 = v64;
  if ( (v47 & 0x8000000) != 0 )
  {
    if ( v65 <= v61 )
    {
      v66 = 0.0;
      v67 = 1;
    }
    else
    {
      v66 = -1.0;
      v67 = 2;
      v60 = 1;
    }
    v68 = a2[v60];
    if ( a2[v67] <= *(float *)&v64 )
    {
      v476 = *(float *)&v64;
      v69 = *(float *)&v64;
      *(float *)&v64 = a2[v67];
    }
    else
    {
      v476 = a2[v67];
      v69 = v476;
      v66 = -0.33333334 - v66;
    }
    v493 = v69;
    v70 = fminf(*(float *)&v64, v68);
    v491 = (float)(v69 - v70) / (float)(v69 + 9.9999997e-21);
    v482 = fabs((float)((float)(*(float *)&v64 - v68) / (float)((float)((float)(v69 - v70) * 6.0) + 9.9999997e-21)) + v66);
    sub_18007E540(a2, &v482, &v491, &v493);
    v475 = v491;
    v500 = LODWORD(v482);
  }
  else if ( (v47 & 0x10000000) != 0 )
  {
    sub_180036790(8, 4, v58, (unsigned int)&v505, (__int64)&v496, (__int64)&v487);
    v504 = v505;
    v502 = v487;
    v503 = *(float *)&v496;
  }
  LOBYTE(v63) = 1;
  v470 = 0;
  v472 = 0;
  v471 = 0;
  sub_180045260(2, v63);
  v495 = v47 & 0x4000000;
  if ( (v47 & 0x4000000) != 0 )
  {
    v519 = v474;
    v518 = (float)(v474 + *(float *)(v480 + 3236)) + v477;
    sub_180070450("hsv", &v518);
    v71 = *(_DWORD *)(qword_18010C470 + 5332);
    if ( v71 && v71 == *(_DWORD *)(qword_18010C470 + 7744) && *(float *)&v11 == 0.0 )
    {
      v72 = *(float *)(v480 + 2752) - v494;
      v73 = *(float *)(v480 + 2756) - v486;
      v74 = *(float *)(v480 + 224) - v494;
      v75 = *(float *)(v480 + 228) - v486;
      v76 = (float)(v72 * v72) + (float)(v73 * v73);
      if ( v76 < (float)((float)(v506 - *(float *)&v50) * (float)(v506 - *(float *)&v50))
        || (float)((float)(v59 + *(float *)&v50) * (float)(v59 + *(float *)&v50)) < v76 )
      {
        v78 = 0;
      }
      else
      {
        *((_QWORD *)&v77 + 1) = 0;
        *(double *)&v77 = sub_1800B3EE0();
        *(float *)&v77 = (float)(*(float *)&v77 / 3.1415927) * 0.5;
        v482 = *(float *)&v77;
        v500 = v77;
        if ( *(float *)&v77 < 0.0 )
        {
          *(float *)&v77 = *(float *)&v77 + *(float *)&v50;
          v482 = *(float *)&v77;
          v500 = v77;
        }
        v78 = 1;
        v470 = 1;
      }
      v79 = sub_1800B4640();
      v80 = *(float *)&v79;
      v81 = sub_1800B6EF0();
      v518 = (float)(v72 * v80) - (float)(v73 * *(float *)&v81);
      v519 = (float)(v72 * *(float *)&v81) + (float)(v73 * v80);
      v472 = v78;
      if ( (unsigned __int8)sub_180035DB0(&v498, v524, v523, &v518) )
      {
        v82 = (float)(v74 * v80) - (float)(v75 * *(float *)&v81);
        v83 = (float)(v74 * *(float *)&v81) + (float)(v75 * v80);
        v518 = v82;
        v519 = v83;
        if ( (unsigned __int8)sub_180035DB0(&v498, v524, v523, &v518) )
        {
          v98 = v501;
        }
        else
        {
          v84 = v507 - 0.0;
          v85 = v514 - v498;
          v86 = (float)((float)(v514 - v498) * (float)(v82 - v498)) + (float)((float)(v507 - 0.0) * (float)(v83 - 0.0));
          if ( v86 >= 0.0 )
          {
            v89 = (float)(v85 * v85) + (float)(v84 * v84);
            if ( v86 <= v89 )
            {
              v88 = (float)((float)(v84 * v86) / v89) + 0.0;
              v87 = v498 + (float)((float)(v85 * v86) / v89);
            }
            else
            {
              v88 = v507;
              v87 = v514;
            }
          }
          else
          {
            v87 = v498;
            v88 = 0.0;
          }
          v90 = v501;
          v91 = v514 - v514;
          v92 = v501 - v507;
          v93 = v514;
          v94 = (float)((float)(v82 - v514) * (float)(v514 - v514))
              + (float)((float)(v83 - v507) * (float)(v501 - v507));
          if ( v94 >= 0.0 )
          {
            v95 = (float)(v91 * v91) + (float)(v92 * v92);
            if ( v94 <= v95 )
            {
              v93 = v514 + (float)((float)(v91 * v94) / v95);
              v90 = v507 + (float)((float)(v92 * v94) / v95);
            }
          }
          else
          {
            v90 = v507;
          }
          v96 = 0.0 - v501;
          v97 = v498 - v514;
          v98 = v501;
          v99 = (float)((float)(0.0 - v501) * (float)(v83 - v501)) + (float)((float)(v498 - v514) * (float)(v82 - v514));
          if ( v99 >= 0.0 )
          {
            v102 = (float)(v97 * v97) + (float)(v96 * v96);
            if ( v99 <= v102 )
            {
              v100 = (float)((float)(v97 * v99) / v102) + v514;
              v101 = v501 + (float)((float)(v96 * v99) / v102);
            }
            else
            {
              v100 = v498;
              v101 = 0.0;
            }
          }
          else
          {
            v100 = v514;
            v101 = v501;
          }
          v103 = (float)((float)(v82 - v87) * (float)(v82 - v87)) + (float)((float)(v83 - v88) * (float)(v83 - v88));
          v104 = (float)((float)(v82 - v93) * (float)(v82 - v93)) + (float)((float)(v83 - v90) * (float)(v83 - v90));
          v105 = fminf(
                   v103,
                   fminf(
                     v104,
                     (float)((float)(v83 - v101) * (float)(v83 - v101))
                   + (float)((float)(v82 - v100) * (float)(v82 - v100))));
          if ( v105 == v103 )
          {
            v82 = v87;
            v83 = v88;
          }
          else if ( v105 == v104 )
          {
            v82 = v93;
            v83 = v90;
          }
          else
          {
            v82 = v100;
            v83 = v101;
          }
        }
        v106 = v82 - v498;
        v107 = (float)(v83 - 0.0) * (float)(v514 - v498);
        v108 = (float)((float)(v98 - 0.0) * (float)(v514 - v498)) - (float)((float)(v514 - v498) * (float)(v507 - 0.0));
        v109 = (float)((float)(v106 * (float)(v98 - 0.0)) - v107) / v108;
        v110 = (float)(v107 - (float)(v106 * (float)(v507 - 0.0))) / v108;
        v111 = 0.000099999997;
        v112 = 1.0 - v109;
        v475 = 0.000099999997;
        if ( (float)(1.0 - v109) >= 0.000099999997 )
        {
          v113 = fminf(1.0, v112);
          v476 = v113;
        }
        else
        {
          v476 = 0.000099999997;
          v113 = 0.000099999997;
        }
        v114 = (float)(v112 - v110) / v113;
        v493 = v113;
        if ( v114 >= 0.000099999997 )
        {
          v111 = fminf(1.0, v114);
          v475 = v111;
        }
        v491 = v111;
        v471 = 1;
        v470 = 1;
      }
      v57.m128_i32[0] = v517.m128_i32[0];
      v59 = v479;
      v52 = (__m128)LODWORD(v481);
      v51 = v508;
    }
    if ( (v47 & 8) == 0 )
      sub_18004C810();
    goto LABEL_104;
  }
  if ( (v47 & 0x2000000) == 0 )
  {
LABEL_104:
    v115 = *((float *)&v492 + 1);
LABEL_105:
    v116 = v480;
    v117 = v474;
    goto LABEL_106;
  }
  *(float *)&v508 = v474;
  *((float *)&v508 + 1) = v474;
  sub_180070450("sv", &v508);
  v123 = qword_18010C470;
  v124 = *(_DWORD *)(qword_18010C470 + 5332);
  if ( v124 && v124 == *(_DWORD *)(qword_18010C470 + 7744) && *(float *)&v11 == 0.0 )
  {
    v125 = (float)(*(float *)(v480 + 224) - *(float *)&v51) / (float)(v474 - *(float *)&v50);
    if ( v125 >= 0.0 )
      v126 = fminf(*(float *)&v50, v125);
    else
      v126 = 0.0;
    v127 = *(float *)(v480 + 228);
    v475 = v126;
    v491 = v126;
    v115 = *((float *)&v492 + 1);
    v128 = (float)(v127 - *((float *)&v492 + 1)) / (float)(v474 - *(float *)&v50);
    if ( v128 >= 0.0 )
      v129 = fminf(*(float *)&v50, v128);
    else
      v129 = 0.0;
    v130 = *(_DWORD *)(qword_18010C470 + 9564);
    v476 = *(float *)&v50 - v129;
    v493 = *(float *)&v50 - v129;
    if ( *(_DWORD *)(qword_18010C470 + 9568) == v130 )
    {
      HIDWORD(v508) = *v62;
      v510 = 0;
      *(float *)&v508 = *a2;
      v509 = *((_DWORD *)a2 + 2);
      sub_180036620(&v508);
      if ( *(_DWORD *)(v123 + 9580) == v131 )
      {
        v482 = *(float *)(v123 + 9572);
        v500 = LODWORD(v482);
      }
    }
    v470 = 1;
  }
  else
  {
    v115 = *((float *)&v492 + 1);
  }
  if ( (v47 & 8) == 0 )
  {
    sub_18004C810();
    v123 = qword_18010C470;
  }
  v132 = *(_QWORD *)(v123 + 5216);
  *(float *)&v508 = v477;
  *(_BYTE *)(v132 + 206) = 1;
  v133 = *(_QWORD *)(v123 + 5216);
  *((float *)&v508 + 1) = v474;
  *(_DWORD *)(v133 + 280) = v55.m128_i32[0];
  *(float *)(v133 + 284) = v115;
  *(_BYTE *)(v133 + 345) = 1;
  sub_180070450("hue", &v508);
  v134 = *(_DWORD *)(qword_18010C470 + 5332);
  if ( !v134 || v134 != *(_DWORD *)(qword_18010C470 + 7744) )
  {
    v471 = v470;
    goto LABEL_105;
  }
  v117 = v474;
  v135 = v11 == 0;
  v116 = v480;
  if ( v135 )
  {
    v471 = v470;
    v136 = (float)(*(float *)(v480 + 228) - v115) / (float)(v474 - *(float *)&v50);
    if ( v136 >= 0.0 )
    {
      v137 = v50;
      *(float *)&v137 = fminf(*(float *)&v50, v136);
    }
    else
    {
      v137 = 0;
    }
    v482 = *(float *)&v137;
    v500 = v137;
    v472 = 1;
    v470 = 1;
  }
  else
  {
    v471 = v470;
  }
LABEL_106:
  if ( v49 )
  {
    v118 = qword_18010C470;
    v508 = __PAIR64__(LODWORD(v117), LODWORD(v477));
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v119 = *(_QWORD *)(v118 + 5216);
    *(_DWORD *)(v119 + 280) = v57.m128_i32[0];
    *(float *)(v119 + 284) = v115;
    *(_BYTE *)(v119 + 345) = 1;
    sub_180070450("alpha", &v508);
    v120 = *(_DWORD *)(qword_18010C470 + 5332);
    if ( v120 )
    {
      if ( v120 == *(_DWORD *)(qword_18010C470 + 7744) )
      {
        v121 = (float)(*(float *)(v116 + 228) - v115) / (float)(v474 - 1.0);
        if ( v121 >= 0.0 )
          v122 = fminf(1.0, v121);
        else
          v122 = 0.0;
        v470 = 1;
        a2[3] = 1.0 - v122;
      }
    }
  }
  sub_180045340();
  if ( (v47 & 0x100) == 0 )
  {
    sub_18004AC40(v139, v138);
    sub_18004AFD0();
  }
  if ( (v47 & 0x80) == 0 )
  {
    v138 = v6;
    if ( v6 != (_BYTE *)-1LL )
    {
      do
      {
        if ( !*v138 || *v138 == 35 && v138[1] == 35 )
          break;
        ++v138;
      }
      while ( v138 != (_BYTE *)-1LL );
      if ( v6 != v138 )
      {
        if ( (v47 & 0x100) != 0 )
          sub_18004AC40(v139, v138);
        sub_18006EB90(v6, v138, 0);
      }
    }
  }
  if ( (v47 & 0x100) != 0 )
  {
    v142 = (float *)v488;
  }
  else
  {
    LOBYTE(v138) = 1;
    sub_180045260(4, v138);
    if ( (v47 & 2) != 0 )
      v141 = 1065353216;
    else
      v141 = *((_DWORD *)a2 + 3);
    v142 = (float *)v488;
    v143 = *(float *)v62;
    v518 = *a2;
    v519 = v143;
    v520 = *(_DWORD *)v488;
    v521 = v141;
    if ( (v47 & 0x80) != 0 )
      sub_18006F370((__int64)"Current");
    *((float *)&v508 + 1) = v477 + v477;
    *(float *)&v508 = v477 * 3.0;
    sub_180083B30("##current", &v518, v47 & 0x18083842, &v508);
    if ( !a4 )
      goto LABEL_163;
    sub_18006F370((__int64)"Original");
    if ( (v47 & 2) != 0 )
      *(float *)&v144 = 1.0;
    else
      v144 = *((int *)a4 + 3);
    v145 = *((_DWORD *)a4 + 1);
    *(float *)&v488 = *a4;
    v489 = a4[2];
    HIDWORD(v488) = v145;
    v490 = *(float *)&v144;
    *(float *)&v508 = v477 * 3.0;
    *((float *)&v508 + 1) = v477 + v477;
    if ( (unsigned __int8)sub_180083B30("##original", &v488, v47 & 0x18083842, &v508) )
    {
      sub_1800B8BD0(a2, a4, v525);
      v470 = 1;
      sub_180045340();
      sub_18004B190();
    }
    else
    {
LABEL_163:
      sub_180045340();
      sub_18004B190();
    }
  }
  if ( v472 || v471 )
  {
    v146 = v476;
    v147 = *(float *)&v500;
    if ( v485 )
    {
      sub_180036790(v139, (_DWORD)v138, v140, (_DWORD)a2, (__int64)v62, (__int64)v142);
      v148 = v480;
      v490 = 0.0;
      *(_DWORD *)(v480 + 9568) = *(_DWORD *)(v480 + 9564);
      *(float *)(v148 + 9572) = v147;
      *(float *)(v148 + 9576) = v475;
      v149 = *v62;
      *(float *)&v488 = *a2;
      v489 = *v142;
      HIDWORD(v488) = v149;
      sub_180036620(&v488);
      *(_DWORD *)(v151 + 9580) = v150;
    }
    else if ( (v47 & 0x10000000) != 0 )
    {
      *(float *)v62 = v475;
      *v142 = v476;
      *a2 = v147;
    }
  }
  else
  {
    v147 = *(float *)&v500;
    v146 = v476;
  }
  if ( (v47 & 0x20) != 0 )
    goto LABEL_193;
  v152 = 0;
  sub_18004ACF0();
  v153 = v47 & 0x1988385A;
  if ( (v47 & 0x100000) != 0 || (v154 = v47 & 0x700000, (v47 & 0x700000) == 0) )
  {
    v154 = v47 & 0x700000;
    if ( sub_18007E600("##rgb", (__int64)a2, v153 | 0x100004) )
    {
      if ( *(_DWORD *)(v480 + 5332) && !*(_BYTE *)(v480 + 5345) )
        v152 = 1;
      v470 = 1;
    }
  }
  if ( (v47 & 0x200000) != 0 || !v154 )
    v470 |= sub_18007E600("##hsv", (__int64)a2, v153 | 0x200004);
  if ( (v47 & 0x400000) != 0 || !v154 )
    v470 |= sub_18007E600("##hex", (__int64)a2, v153 | 0x400004);
  sub_18004ADF0();
  v155 = v485;
  if ( !v152 )
    goto LABEL_194;
  v156 = a2;
  if ( v485 )
  {
    sub_1800366E0(v139, (_DWORD)v138, v140, (unsigned int)&v479, (__int64)v497, (__int64)&v481);
    if ( v479 <= 0.0 && v147 > 0.0 )
    {
      if ( v481 <= 0.0 && v146 != v481 )
      {
        sub_180036790(v139, (_DWORD)v138, v140, (_DWORD)v156, (__int64)v62, (__int64)v142);
LABEL_193:
        v155 = v485;
LABEL_194:
        v156 = a2;
        goto LABEL_198;
      }
      if ( v497[0] <= 0.0 )
      {
        sub_180036790(v139, (_DWORD)v138, v140, (_DWORD)v156, (__int64)v62, (__int64)v142);
        v156 = a2;
      }
    }
    v155 = v485;
  }
LABEL_198:
  if ( !v470 )
    goto LABEL_203;
  if ( v155 )
  {
    v157 = *(_DWORD *)v156;
    v158 = *(float *)v62;
    v159 = *v142;
    sub_1800366E0(v139, (_DWORD)v138, v140, (unsigned int)&v482, (__int64)&v491, (__int64)&v493);
    sub_18007E540(v160, &v482, &v491, &v493);
    v475 = v491;
    v476 = v493;
    v500 = LODWORD(v482);
    goto LABEL_204;
  }
  if ( (v47 & 0x10000000) != 0 )
  {
    v475 = *(float *)v62;
    v476 = *v142;
    v500 = *(unsigned int *)v156;
    sub_180036790(v139, (_DWORD)v138, v140, (unsigned int)&v505, (__int64)&v496, (__int64)&v487);
    v157 = v505;
    LODWORD(v158) = v496;
    v159 = *(float *)&v487;
  }
  else
  {
LABEL_203:
    v159 = *(float *)&v502;
    v158 = v503;
    v157 = v504;
  }
LABEL_204:
  v161 = *(float *)(v480 + 3148);
  if ( v161 >= 0.0 )
    v162 = fminf(1.0, v161);
  else
    v162 = 0.0;
  v488 = 0x3F8000003F800000LL;
  v490 = v161;
  v489 = 1.0;
  v163 = (int)(float)((float)(v162 * 255.0) + 0.5) << 24;
  v503 = *(float *)&v163;
  HIDWORD(v508) = v163 | 0xFFFF;
  LODWORD(v508) = v163 | 0xFF;
  v513 = v163 | 0xFF;
  v509 = v163 | 0xFF00;
  v164 = v163 | 0xFFFFFF;
  v510 = v163 | 0xFFFF00;
  v165 = v163 | 0x808080;
  v487 = v163 | 0xFFFFFF;
  v502 = v163 | 0x808080;
  v511 = v163 | 0xFF0000;
  v512 = v163 | 0xFF00FF;
  sub_180036790(v163 | 0xFF, (_DWORD)v138, v140, (unsigned int)&v488, (__int64)&v488 + 4, (__int64)&v489);
  sub_180036620(&v488);
  v479 = v166;
  v488 = __PAIR64__(LODWORD(v158), v157);
  v489 = v159;
  v490 = v161;
  sub_180036620(&v488);
  v170 = v169;
  v171 = 0.55000001;
  v172 = 3;
  v504 = v169;
  v496 = 0;
  if ( *(float *)&v495 != 0.0 )
  {
    v173 = (int *)(v9 + 80);
    v174 = v506;
    v175 = v494;
    v176 = 0.5 / v59;
    v497[0] = v506 + v59;
    *(float *)&v495 = 0.5 / v59;
    v481 = (float)(v506 + v59) * 0.5;
    v177 = (int)v59 / 12;
    if ( v177 <= 4 )
      v177 = 4;
    for ( i = 0; i < 6; ++i )
    {
      v179 = *(int *)(v9 + 32);
      sub_18005BE10(
        v9,
        (unsigned int)&v483,
        v167,
        v168,
        (float)((float)((float)((float)((float)i + 1.0) / 6.0) + (float)((float)((float)i + 1.0) / 6.0)) * 3.1415927)
      + v176,
        v177);
      sub_18005AD60(v9, *(_QWORD *)(v9 + 88), *v173, v164, 0, LODWORD(v515));
      *v173 = 0;
      v180 = (float)(COERCE_FLOAT(COERCE_UNSIGNED_INT64(sub_1800B4640())) * v174) + v175;
      v181 = (float)(COERCE_FLOAT(COERCE_UNSIGNED_INT64(sub_1800B6EF0())) * v174) + v486;
      v182 = (float)((float)(COERCE_FLOAT(COERCE_UNSIGNED_INT64(sub_1800B4640())) * v174) + v175) - v180;
      v183 = sub_1800B6EF0();
      v184 = *(_QWORD *)(v9 + 40);
      v185 = v486;
      v186 = v184 + 20LL * *(int *)(v9 + 32);
      v167 = v184 + 20 * v179;
      v187 = (float)((float)(*(float *)&v183 * v174) + v486) - v181;
      if ( v167 < v186 )
      {
        v188 = 1.0 / (float)((float)(v182 * v182) + (float)(v187 * v187));
        v189 = *((_DWORD *)&v508 + (unsigned int)i + 1);
        v190 = *((_DWORD *)&v508 + (unsigned int)i);
        v168 = (unsigned __int8)v189 - (unsigned __int8)v190;
        v191 = BYTE1(v189) - BYTE1(v190);
        v192 = BYTE2(v189) - BYTE2(v190);
        if ( v186 - v167 + 19 >= 0x50 )
        {
          v193 = (float)v192;
          v194 = (float)BYTE2(v190);
          v195 = (float)v191;
          v196 = (float)BYTE1(v190);
          v197 = (float)v168;
          v198 = (float)(unsigned __int8)v190;
          do
          {
            v199 = (float)((float)((float)(*(float *)(v167 + 4) - v181) * v187)
                         + (float)((float)(*(float *)v167 - v180) * v182))
                 * v188;
            if ( v199 >= 0.0 )
              v200 = fminf(1.0, v199);
            else
              v200 = 0.0;
            *(_DWORD *)(v167 + 16) &= 0xFF000000;
            *(_DWORD *)(v167 + 16) |= (int)(float)((float)(v197 * v200) + v198)
                                    | (((int)(float)((float)(v200 * v195) + v196)
                                      | ((int)(float)((float)(v193 * v200) + v194) << 8)) << 8);
            v201 = (float)((float)((float)(*(float *)(v167 + 20) - v180) * v182)
                         + (float)((float)(*(float *)(v167 + 24) - v181) * v187))
                 * v188;
            if ( v201 >= 0.0 )
              v202 = fminf(1.0, v201);
            else
              v202 = 0.0;
            *(_DWORD *)(v167 + 36) &= 0xFF000000;
            *(_DWORD *)(v167 + 36) |= (int)(float)((float)(v197 * v202) + v198)
                                    | (((int)(float)((float)(v202 * v195) + v196)
                                      | ((int)(float)((float)(v193 * v202) + v194) << 8)) << 8);
            v203 = (float)((float)((float)(*(float *)(v167 + 40) - v180) * v182)
                         + (float)((float)(*(float *)(v167 + 44) - v181) * v187))
                 * v188;
            if ( v203 >= 0.0 )
              v204 = fminf(1.0, v203);
            else
              v204 = 0.0;
            *(_DWORD *)(v167 + 56) &= 0xFF000000;
            *(_DWORD *)(v167 + 56) |= (int)(float)((float)(v197 * v204) + v198)
                                    | (((int)(float)((float)(v204 * v195) + v196)
                                      | ((int)(float)((float)(v193 * v204) + v194) << 8)) << 8);
            v205 = (float)((float)((float)(*(float *)(v167 + 60) - v180) * v182)
                         + (float)((float)(*(float *)(v167 + 64) - v181) * v187))
                 * v188;
            if ( v205 >= 0.0 )
              v206 = fminf(1.0, v205);
            else
              v206 = 0.0;
            *(_DWORD *)(v167 + 76) &= 0xFF000000;
            *(_DWORD *)(v167 + 76) |= (int)(float)((float)(v197 * v206) + v198)
                                    | (((int)(float)((float)(v206 * v195) + v196)
                                      | ((int)(float)((float)(v193 * v206) + v194) << 8)) << 8);
            v167 += 80LL;
          }
          while ( v167 < v186 - 60 );
        }
        for ( ; v167 < v186; v167 += 20LL )
        {
          v207 = (float)((float)((float)(*(float *)(v167 + 4) - v181) * v187)
                       + (float)((float)(*(float *)v167 - v180) * v182))
               * v188;
          if ( v207 >= 0.0 )
            v208 = fminf(1.0, v207);
          else
            v208 = 0.0;
          *(_DWORD *)(v167 + 16) &= 0xFF000000;
          *(_DWORD *)(v167 + 16) |= (int)(float)((float)(v208 * (float)v168) + (float)(unsigned __int8)v190)
                                  | (((int)(float)((float)(v208 * (float)v191) + (float)BYTE1(v190))
                                    | ((int)(float)((float)(v208 * (float)v192) + (float)BYTE2(v190)) << 8)) << 8);
        }
        v164 = v487;
        v173 = (int *)(v9 + 80);
        v185 = v486;
        v175 = v494;
        v174 = v506;
      }
      v176 = *(float *)&v495;
    }
    v209 = sub_1800B4640();
    v210 = *(float *)&v209;
    v211 = sub_1800B6EF0();
    v212 = *(float *)&v211;
    *(float *)&v211 = (float)((float)(v497[0] * *(float *)&v211) * 0.5) + v185;
    v497[0] = (float)((float)(v497[0] * v210) * 0.5) + v175;
    v497[1] = *(float *)&v211;
    if ( v472 )
      v213 = 0.64999998;
    else
      v213 = 0.55000001;
    v214 = v213 * v515;
    v215 = sub_18005A550(v9);
    v218 = v479;
    v219 = *(float *)&v215;
    v481 = *(float *)&v215;
    if ( (LODWORD(v479) & 0xFF000000) != 0 && v214 >= 0.5 )
    {
      if ( v215 > 0 )
      {
        if ( v215 >= 3 )
        {
          if ( v215 > 512 )
            v215 = 512;
        }
        else
        {
          v215 = 3;
        }
        sub_18005BE10(
          v9,
          (unsigned int)v497,
          v216,
          v217,
          (float)((float)((float)v215 - 1.0) * 6.2831855) / (float)v215,
          v215 - 1);
      }
      else
      {
        sub_18005BB80(v9, (unsigned int)v497, v216, 0, 48);
        --*v173;
      }
      v220 = *v173;
      if ( (int)v220 >= 3 )
      {
        v221 = *(int **)(v9 + 56);
        v222 = *(_QWORD *)(v9 + 88);
        v223 = *v221;
        v224 = v221[1];
        if ( (*(_BYTE *)(v9 + 48) & 4) != 0 )
        {
          v225 = *(float *)(v9 + 208);
          v495 = 2 * v220;
          v226 = LODWORD(v218) & 0xFFFFFF;
          sub_18005AB20(v9, (unsigned int)(v220 + 8 * v220 - 6), (unsigned int)(2 * v220));
          v227 = *(_DWORD *)(v9 + 52);
          v228 = 2;
          do
          {
            v229 = 2 * v228++;
            v230 = v227 + v229;
            **(_WORD **)(v9 + 72) = v227;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = v230 - 2;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = v230;
            *(_QWORD *)(v9 + 72) += 6LL;
          }
          while ( v228 < (int)v220 );
          v231 = *(_QWORD *)(v9 + 56);
          if ( (int)v220 > *(_DWORD *)(v231 + 76) )
          {
            v232 = *(void **)(v231 + 80);
            if ( v232 )
              sub_18003A8D0(v232);
            *(_QWORD *)(v231 + 80) = sub_18003A810(8 * v220);
            *(_DWORD *)(v231 + 76) = v220;
          }
          v233 = v220 - 1;
          v234 = 0;
          v235 = v220 - 1;
          v236 = *(_QWORD *)(*(_QWORD *)(v9 + 56) + 80LL);
          if ( (int)v220 < 4 )
            goto LABEL_443;
          do
          {
            v237 = v234;
            v238 = *(float *)(v222 + 8LL * v234) - *(float *)(v222 + 8LL * v235);
            v239 = *(float *)(v222 + 8LL * v234 + 4) - *(float *)(v222 + 8LL * v235 + 4);
            v240 = (float)(v239 * v239) + (float)(v238 * v238);
            if ( v240 <= 0.0 )
            {
              v242 = *(float *)(v222 + 8LL * v234 + 4) - *(float *)(v222 + 8LL * v235 + 4);
              v243 = *(float *)(v222 + 8LL * v234) - *(float *)(v222 + 8LL * v235);
            }
            else
            {
              v241 = 1.0 / fsqrt(v240);
              v242 = v241 * v239;
              v243 = v241 * v238;
            }
            *(float *)(v236 + 8LL * v235) = v242;
            *(float *)(v236 + 8LL * v235 + 4) = -v243;
            v244 = *(float *)(v222 + 8LL * v234 + 8) - *(float *)(v222 + 8LL * v234);
            v245 = *(float *)(v222 + 8LL * v234 + 12) - *(float *)(v222 + 8LL * v234 + 4);
            v246 = (float)(v245 * v245) + (float)(v244 * v244);
            if ( v246 <= 0.0 )
            {
              v248 = *(float *)(v222 + 8LL * v234 + 12) - *(float *)(v222 + 8LL * v234 + 4);
              v249 = *(float *)(v222 + 8LL * v234 + 8) - *(float *)(v222 + 8LL * v234);
            }
            else
            {
              v247 = 1.0 / fsqrt(v246);
              v248 = v247 * v245;
              v249 = v247 * v244;
            }
            *(float *)(v236 + 8LL * v234) = v248;
            *(float *)(v236 + 8LL * v234 + 4) = -v249;
            v250 = *(float *)(v222 + 8LL * v234 + 16) - *(float *)(v222 + 8LL * v234 + 8);
            v251 = *(float *)(v222 + 8LL * v234 + 20) - *(float *)(v222 + 8LL * v234 + 12);
            v252 = (float)(v251 * v251) + (float)(v250 * v250);
            if ( v252 <= 0.0 )
            {
              v254 = *(float *)(v222 + 8LL * v234 + 20) - *(float *)(v222 + 8LL * v234 + 12);
              v255 = *(float *)(v222 + 8LL * v234 + 16) - *(float *)(v222 + 8LL * v234 + 8);
            }
            else
            {
              v253 = 1.0 / fsqrt(v252);
              v254 = v253 * v251;
              v255 = v253 * v250;
            }
            *(float *)(v236 + 8LL * v234 + 8) = v254;
            *(float *)(v236 + 8LL * v234 + 12) = -v255;
            v256 = *(float *)(v222 + 8LL * v234 + 24) - *(float *)(v222 + 8LL * v234 + 16);
            v257 = *(float *)(v222 + 8LL * v234 + 28) - *(float *)(v222 + 8LL * v234 + 20);
            v258 = (float)(v257 * v257) + (float)(v256 * v256);
            if ( v258 <= 0.0 )
            {
              v260 = *(float *)(v222 + 8LL * v234 + 28) - *(float *)(v222 + 8LL * v234 + 20);
              v261 = *(float *)(v222 + 8LL * v234 + 24) - *(float *)(v222 + 8LL * v234 + 16);
            }
            else
            {
              v259 = 1.0 / fsqrt(v258);
              v260 = v259 * v257;
              v261 = v259 * v256;
            }
            v235 = v234 + 3;
            *(float *)(v236 + 8LL * v234 + 16) = v260;
            v234 += 4;
            *(float *)(v236 + 8 * v237 + 20) = -v261;
          }
          while ( v234 < (int)v220 - 3 );
          if ( v234 < (int)v220 )
          {
LABEL_443:
            do
            {
              v262 = *(float *)(v222 + 8LL * v234) - *(float *)(v222 + 8LL * v235);
              v263 = *(float *)(v222 + 8LL * v234 + 4) - *(float *)(v222 + 8LL * v235 + 4);
              v264 = (float)(v263 * v263) + (float)(v262 * v262);
              if ( v264 <= 0.0 )
              {
                v266 = *(float *)(v222 + 8LL * v234 + 4) - *(float *)(v222 + 8LL * v235 + 4);
                v267 = *(float *)(v222 + 8LL * v234) - *(float *)(v222 + 8LL * v235);
              }
              else
              {
                v265 = 1.0 / fsqrt(v264);
                v266 = v265 * v263;
                v267 = v265 * v262;
              }
              *(float *)(v236 + 8LL * v235) = v266;
              *(float *)(v236 + 8LL * v235 + 4) = -v267;
              v235 = v234++;
            }
            while ( v234 < (int)v220 );
          }
          v268 = v227 + 1;
          v269 = 0;
          v218 = v479;
          v270 = v225 * 0.5;
          do
          {
            v271 = (float)(*(float *)(v236 + 8LL * v233) + *(float *)(v236 + 8LL * v269)) * 0.5;
            v272 = (float)(*(float *)(v236 + 8LL * v269 + 4) + *(float *)(v236 + 8LL * v233 + 4)) * 0.5;
            v273 = (float)(v272 * v272) + (float)(v271 * v271);
            if ( v273 <= 0.000001 )
            {
              v275 = (float)(*(float *)(v236 + 8LL * v269 + 4) + *(float *)(v236 + 8LL * v233 + 4)) * 0.5;
              v276 = (float)(*(float *)(v236 + 8LL * v233) + *(float *)(v236 + 8LL * v269)) * 0.5;
            }
            else
            {
              v274 = fminf(100.0, 1.0 / v273);
              v275 = v274 * v272;
              v276 = v274 * v271;
            }
            v277 = 2 * v233;
            v278 = v276 * v270;
            v216 = (unsigned __int16)(2 * v269);
            v279 = v275 * v270;
            v280 = v227 + v216;
            LOWORD(v216) = v268 + v216;
            **(float **)(v9 + 64) = *(float *)(v222 + 8LL * v269) - v278;
            *(float *)(*(_QWORD *)(v9 + 64) + 4LL) = *(float *)(v222 + 8LL * v269 + 4) - v279;
            v281 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v281 + 8) = v223;
            *(_DWORD *)(v281 + 12) = v224;
            *(float *)(*(_QWORD *)(v9 + 64) + 16LL) = v218;
            *(float *)(*(_QWORD *)(v9 + 64) + 20LL) = v278 + *(float *)(v222 + 8LL * v269);
            v282 = v227 + v277;
            v283 = v268 + v277;
            *(float *)(*(_QWORD *)(v9 + 64) + 24LL) = v279 + *(float *)(v222 + 8LL * v269 + 4);
            v284 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v284 + 28) = v223;
            *(_DWORD *)(v284 + 32) = v224;
            *(_DWORD *)(*(_QWORD *)(v9 + 64) + 36LL) = v226;
            *(_QWORD *)(v9 + 64) += 40LL;
            **(_WORD **)(v9 + 72) = v280;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = v282;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = v283;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 6LL) = v283;
            v233 = v269++;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 8LL) = v216;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 10LL) = v280;
            *(_QWORD *)(v9 + 72) += 12LL;
          }
          while ( v269 < (int)v220 );
          v175 = v494;
          v285 = (unsigned __int16)v495;
        }
        else
        {
          sub_18005AB20(v9, (unsigned int)(3 * (v220 - 2)), (unsigned int)v220);
          v286 = 0;
          do
          {
            v287 = *(_QWORD *)(v222 + 8 * v286);
            v286 = (unsigned int)(v286 + 1);
            **(_QWORD **)(v9 + 64) = v287;
            v288 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v288 + 8) = v223;
            *(_DWORD *)(v288 + 12) = v224;
            *(float *)(*(_QWORD *)(v9 + 64) + 16LL) = v218;
            *(_QWORD *)(v9 + 64) += 20LL;
          }
          while ( (int)v286 < (int)v220 );
          v289 = 2;
          do
          {
            **(_WORD **)(v9 + 72) = *(_WORD *)(v9 + 52);
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = *(_WORD *)(v9 + 52) + v289 - 1;
            v290 = v289++;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = *(_WORD *)(v9 + 52) + v290;
            *(_QWORD *)(v9 + 72) += 6LL;
          }
          while ( v289 < (int)v220 );
          v285 = (unsigned __int16)v220;
        }
        v219 = v481;
        v185 = v486;
        *(_DWORD *)(v9 + 52) += v285;
      }
      v173 = (int *)(v9 + 80);
      *(_DWORD *)(v9 + 80) = 0;
    }
    v165 = v502;
    sub_18005CE80(v9, (unsigned int)v497, v216, v502, LODWORD(v219), 1065353216);
    sub_18005CE80(v9, (unsigned int)v497, v291, v487, LODWORD(v219), 1065353216);
    v172 = 3;
    v292 = *(_DWORD *)(qword_18010C470 + 4456);
    v293 = v175 + (float)((float)(v210 * v498) - (float)(v212 * 0.0));
    v294 = v185 + (float)((float)(v210 * 0.0) + (float)(v212 * v498));
    v295 = v212 * v514;
    v296 = (float)((float)(v210 * v507) + (float)(v212 * v514)) + v185;
    v297 = (float)((float)(v210 * v514) - (float)(v212 * v507)) + v494;
    v298 = v494 + (float)((float)(v210 * v514) - (float)(v212 * v501));
    v486 = v185 + (float)((float)(v210 * v501) + v295);
    v299 = *(_DWORD *)(qword_18010C470 + 4460);
    sub_18005AB20(v9, 3, 3);
    **(_WORD **)(v9 + 72) = *(_WORD *)(v9 + 52);
    v300 = *(float **)(v9 + 64);
    *(_QWORD *)(v9 + 72) += 2LL;
    *v300 = v293;
    v300[1] = v294;
    v301 = *(_QWORD *)(v9 + 64);
    *(_DWORD *)(v301 + 8) = v292;
    *(_DWORD *)(v301 + 12) = v299;
    *(float *)(*(_QWORD *)(v9 + 64) + 16LL) = v218;
    ++*(_DWORD *)(v9 + 52);
    v302 = *(_WORD **)(v9 + 72);
    *(_QWORD *)(v9 + 64) += 20LL;
    *v302 = *(_DWORD *)(v9 + 52);
    *(_QWORD *)(v9 + 72) += 2LL;
    v303 = *(float **)(v9 + 64);
    v304 = v503;
    v305 = v486;
    v164 = v487;
    *v303 = v297;
    v303[1] = v296;
    v306 = *(_QWORD *)(v9 + 64);
    *(_DWORD *)(v306 + 8) = v292;
    *(_DWORD *)(v306 + 12) = v299;
    *(float *)(*(_QWORD *)(v9 + 64) + 16LL) = v304;
    *(_QWORD *)(v9 + 64) += 20LL;
    **(_WORD **)(v9 + 72) = ++*(_DWORD *)(v9 + 52);
    v307 = *(float **)(v9 + 64);
    *(_QWORD *)(v9 + 72) += 2LL;
    *v307 = v298;
    v307[1] = v305;
    v308 = *(_QWORD *)(v9 + 64);
    *(_DWORD *)(v308 + 8) = v292;
    *(_DWORD *)(v308 + 12) = v299;
    *(_DWORD *)(*(_QWORD *)(v9 + 64) + 16LL) = v164;
    *(_QWORD *)(v9 + 64) += 20LL;
    ++*(_DWORD *)(v9 + 52);
    if ( v304 != 0.0 )
    {
      v309 = *(_DWORD *)(v9 + 84);
      if ( *v173 == v309 )
      {
        v310 = *v173 + 1;
        if ( v309 )
          v311 = v309 + v309 / 2;
        else
          v311 = 8;
        if ( v311 > v310 )
          v310 = v311;
        sub_180054080(v173, (unsigned int)v310);
      }
      v312 = *v173;
      v313 = *(_QWORD *)(v9 + 88);
      *(float *)(v313 + 8 * v312) = v293;
      *(float *)(v313 + 8 * v312 + 4) = v294;
      v314 = *v173;
      LODWORD(v313) = *v173 + 1;
      *v173 = v313;
      v315 = *(_DWORD *)(v9 + 84);
      if ( (_DWORD)v313 == v315 )
      {
        v316 = v314 + 2;
        if ( v315 )
          v317 = v315 + v315 / 2;
        else
          v317 = 8;
        if ( v317 > v316 )
          v316 = v317;
        sub_180054080(v173, (unsigned int)v316);
      }
      v318 = *v173;
      v319 = *(_QWORD *)(v9 + 88);
      *(float *)(v319 + 8 * v318) = v297;
      *(float *)(v319 + 8 * v318 + 4) = v296;
      v320 = *v173;
      LODWORD(v319) = *v173 + 1;
      *v173 = v319;
      v321 = *(_DWORD *)(v9 + 84);
      if ( (_DWORD)v319 == v321 )
      {
        v322 = v320 + 2;
        if ( v321 )
          v323 = v321 + v321 / 2;
        else
          v323 = 8;
        if ( v323 > v322 )
          v322 = v323;
        sub_180054080(v173, (unsigned int)v322);
      }
      v324 = *v173;
      v325 = *(_QWORD *)(v9 + 88);
      *(float *)(v325 + 8 * v324) = v298;
      *(float *)(v325 + 8 * v324 + 4) = v305;
      sub_18005AD60(v9, *(_QWORD *)(v9 + 88), ++*v173, v165, 1, 1069547520);
      *v173 = 0;
    }
    if ( (float)(1.0 - v476) >= 0.0 )
      v326 = fminf(1.0, 1.0 - v476);
    else
      v326 = 0.0;
    if ( v475 >= 0.0 )
      v327 = fminf(1.0, v475);
    else
      v327 = 0.0;
    v171 = 0.55000001;
    v170 = v504;
    *(float *)&v496 = (float)((float)(v297 - (float)((float)((float)(v293 - v298) * v327) + v298)) * v326)
                    + (float)((float)((float)(v293 - v298) * v327) + v298);
    *((float *)&v496 + 1) = (float)((float)(v296 - (float)((float)((float)(v294 - v305) * v327) + v305)) * v326)
                          + (float)((float)((float)(v294 - v305) * v327) + v305);
    goto LABEL_330;
  }
  if ( (v47 & 0x2000000) == 0 )
  {
LABEL_330:
    v341 = v477;
    v328 = v474;
    v329 = (__m128)HIDWORD(v492);
    goto LABEL_331;
  }
  v328 = v474;
  v329 = (__m128)HIDWORD(v492);
  v330 = (__m128)LODWORD(v474);
  v330.m128_f32[0] = v474 + *((float *)&v492 + 1);
  v483 = v52.m128_f32[0];
  v484 = v474 + *((float *)&v492 + 1);
  sub_18005CCC0(v9, (unsigned int)&v492, (unsigned int)&v483, v164, v168, v168, v163 | 0xFFFFFF);
  v483 = v52.m128_f32[0];
  v484 = v330.m128_f32[0];
  sub_18005CCC0(v9, (unsigned int)&v492, (unsigned int)&v483, 0, 0, v163, v163);
  sub_180038630(v51, _mm_unpacklo_ps(v52, v330).m128_u64[0]);
  v331 = *(float *)&v51 + 2.0;
  if ( v475 >= 0.0 )
    v332 = fminf(1.0, v475);
  else
    v332 = 0.0;
  v333 = (float)(int)(float)((float)((float)(v332 * v474) + *(float *)&v51) + 0.5);
  if ( v331 <= v333 )
    v331 = fminf(v52.m128_f32[0] - 2.0, v333);
  *(float *)&v496 = v331;
  if ( (float)(1.0 - v476) >= 0.0 )
    v334 = fminf(1.0, 1.0 - v476);
  else
    v334 = 0.0;
  v335 = v329.m128_f32[0] + 2.0;
  v336 = (float)(int)(float)((float)((float)(v334 * v474) + v329.m128_f32[0]) + 0.5);
  if ( (float)(v329.m128_f32[0] + 2.0) <= v336 )
    v335 = fminf(v330.m128_f32[0] - 2.0, v336);
  *((float *)&v496 + 1) = v335;
  v337 = v474 / 6.0;
  v338 = 0;
  do
  {
    v339 = v338 + 1;
    v469 = *((_DWORD *)&v508 + v338 + 1);
    v468 = *((_DWORD *)&v508 + v338);
    v483 = v55.m128_f32[0] + v477;
    LODWORD(v488) = v55.m128_i32[0];
    v484 = (float)((float)(v338 + 1) * v337) + v329.m128_f32[0];
    *((float *)&v488 + 1) = (float)((float)(int)v338 * v337) + v329.m128_f32[0];
    sub_18005CCC0(v9, (unsigned int)&v488, (unsigned int)&v483, v468, v468, v469, v469);
    v338 = (unsigned int)v339;
  }
  while ( v339 < 6 );
  v56.m128_f32[0] = v55.m128_f32[0] + v477;
  sub_180038630(_mm_unpacklo_ps(v55, v329).m128_u64[0], _mm_unpacklo_ps(v56, v330).m128_u64[0]);
  v340 = (__m128)LODWORD(v516);
  v341 = v477;
  v340.m128_f32[0] = v516 + 1.0;
  v55.m128_f32[0] = v55.m128_f32[0] - 1.0;
  sub_180080340(
    v9,
    _mm_unpacklo_ps(
      v55,
      (__m128)COERCE_UNSIGNED_INT((float)(int)(float)((float)((float)(*(float *)&v500 * v474) + v329.m128_f32[0]) + 0.5))).m128_u32[0],
    _mm_unpacklo_ps(v340, (__m128)LODWORD(v516)).m128_u32[0],
    v342,
    *(_DWORD *)(v480 + 3148));
  v171 = 0.55000001;
LABEL_331:
  if ( !v471 )
    v171 = 0.40000001;
  v343 = v171 * v515;
  v344 = sub_18005A550(v9);
  v347 = v344;
  if ( (v170 & 0xFF000000) != 0 && v343 >= 0.5 )
  {
    if ( v344 > 0 )
    {
      if ( v344 >= 3 )
      {
        v172 = v344;
        if ( v344 > 512 )
          v172 = 512;
      }
      sub_18005BE10(
        v9,
        (unsigned int)&v496,
        v345,
        v346,
        (float)((float)((float)v172 - 1.0) * 6.2831855) / (float)v172,
        v172 - 1);
    }
    else
    {
      sub_18005BB80(v9, (unsigned int)&v496, v345, 0, 48);
      --*(_DWORD *)(v9 + 80);
    }
    sub_180034630(v9, v170);
  }
  sub_18005CE80(v9, (unsigned int)&v496, v345, v165, v347, 1065353216);
  sub_18005CE80(v9, (unsigned int)&v496, v348, v164, v347, 1065353216);
  if ( v473 )
  {
    v349 = a2[3];
    if ( v349 >= 0.0 )
      v479 = fminf(1.0, v349);
    else
      v479 = 0.0;
    v350 = v517;
    v351 = v329;
    v351.m128_f32[0] = v329.m128_f32[0] + v328;
    *(_QWORD *)&v500 = __PAIR64__(v329.m128_u32[0], v517.m128_u32[0]);
    v352 = v517;
    v352.m128_f32[0] = v517.m128_f32[0] + v341;
    v488 = __PAIR64__(v329.m128_u32[0], v517.m128_u32[0]);
    *((float *)&v500 + 3) = v329.m128_f32[0] + v328;
    v484 = v329.m128_f32[0] + v328;
    *((float *)&v500 + 2) = v517.m128_f32[0] + v341;
    v353 = (float)(v517.m128_f32[0] + v341) - v517.m128_f32[0];
    v483 = v517.m128_f32[0] + v341;
    sub_180036570(4291611852LL, 0);
    v354 = *(float *)(qword_18010C470 + 3148);
    v355 = sub_180036570(4286611584LL, 0);
    v357 = v355;
    if ( v354 < 1.0 )
      v357 = v355 & 0xFFFFFF | ((int)(float)((float)HIBYTE(v355) * v354) << 24);
    sub_18005C870(v9, (unsigned int)&v488, (unsigned int)&v483, v356, 0, 240);
    v358 = *((float *)&v492 + 1);
    v359 = *((float *)&v492 + 1) + 0.0;
    if ( v351.m128_f32[0] > (float)(*((float *)&v492 + 1) + 0.0) )
    {
      v360 = v517.m128_f32[0];
      v361 = 0;
      v362 = v353 * 0.5;
      v363 = v517.m128_f32[0] + 0.0;
      do
      {
        if ( v358 <= v359 )
          v364 = fminf(v351.m128_f32[0], v359);
        else
          v364 = v358;
        v359 = v359 + v362;
        v365 = fminf(v359, v351.m128_f32[0]);
        if ( v364 < v365 )
        {
          for ( j = (float)((float)(v361 & 1) * v362) + v363; v352.m128_f32[0] > j; j = j + (float)(v362 + v362) )
          {
            if ( v360 <= j )
              v367 = fminf(v352.m128_f32[0], j);
            else
              v367 = v360;
            v368 = fminf(j + v362, v352.m128_f32[0]);
            if ( v367 < v368 )
            {
              v369 = 256;
              if ( v358 >= v364 )
              {
                v370 = 256;
                if ( v360 >= v367 )
                  v370 = 272;
                v369 = v370 | 0x20;
                if ( v368 < v352.m128_f32[0] )
                  v369 = v370;
              }
              if ( v365 >= v351.m128_f32[0] )
              {
                v371 = v369 | 0x40;
                if ( v360 < v367 )
                  v371 = v369;
                v369 = v371 | 0x80;
                if ( v368 < v352.m128_f32[0] )
                  v369 = v371;
              }
              v483 = v368;
              v484 = v365;
              v372 = 256;
              v488 = __PAIR64__(LODWORD(v364), LODWORD(v367));
              if ( v369 != 256 )
                v372 = v369 & 0xF0;
              sub_18005C870(v9, (unsigned int)&v488, (unsigned int)&v483, v357, 0, v372);
              v360 = v517.m128_f32[0];
              v358 = *((float *)&v492 + 1);
            }
          }
        }
        ++v361;
      }
      while ( v351.m128_f32[0] > v359 );
      v350 = v517;
    }
    sub_18005CCC0(v9, (unsigned int)&v500, (unsigned int)&v500 + 8, v170, v170, v170 & 0xFFFFFF, v170 & 0xFFFFFF);
    v373 = _mm_unpacklo_ps(v352, v351).m128_u64[0];
    v374 = *((float *)&v492 + 1);
    sub_180038630(_mm_unpacklo_ps(v350, (__m128)HIDWORD(v492)).m128_u64[0], v373);
    v350.m128_f32[0] = v350.m128_f32[0] - 1.0;
    v375 = *(float *)(v480 + 3148);
    v376 = (__m128)LODWORD(v516);
    v376.m128_f32[0] = v516 + 1.0;
    v517 = v350;
    v377 = (float)((float)(1.0 - v479) * v474) + v374;
    v378 = v477 + 2.0;
    v478 = v477 + 2.0;
    v379 = (__m128)COERCE_UNSIGNED_INT((float)(int)(float)(v377 + 0.5));
    if ( v375 >= 0.0 )
      v380 = fminf(1.0, v375);
    else
      v380 = 0.0;
    v381 = v350;
    v381.m128_f32[0] = v350.m128_f32[0] + v376.m128_f32[0];
    v382 = v376;
    v383 = (int)(float)((float)(v380 * 255.0) + 0.5) << 24;
    *(float *)&v488 = (float)((float)(v350.m128_f32[0] + v376.m128_f32[0]) + 1.0) - (float)(v376.m128_f32[0] + 2.0);
    v483 = *(float *)&v488;
    *((float *)&v488 + 1) = v379.m128_f32[0] - v376.m128_f32[0];
    v484 = v376.m128_f32[0] + v379.m128_f32[0];
    if ( v383 )
    {
      sub_1800345B0(v9, &v483);
      sub_1800345B0(v9, &v488);
      v384 = *(_DWORD *)(v9 + 80);
      v385 = (int *)(v9 + 80);
      v386 = *(_DWORD *)(v9 + 84);
      if ( v384 == v386 )
      {
        v387 = v384 + 1;
        if ( v386 )
          v388 = v386 + v386 / 2;
        else
          v388 = 8;
        if ( v388 > v387 )
          v387 = v388;
        sub_180054080(v9 + 80, (unsigned int)v387);
      }
      v389 = *v385;
      v390 = *(_QWORD *)(v9 + 88);
      *(float *)(v390 + 8 * v389) = (float)(v350.m128_f32[0] + v376.m128_f32[0]) + 1.0;
      *(_DWORD *)(v390 + 8 * v389 + 4) = v379.m128_i32[0];
      v391 = *v385;
      v392 = *v385 + 1;
      *v385 = v392;
      if ( v392 >= 3 )
      {
        v393 = *(int **)(v9 + 56);
        v394 = *(_QWORD *)(v9 + 88);
        v395 = *v393;
        v396 = v393[1];
        if ( (*(_BYTE *)(v9 + 48) & 4) != 0 )
        {
          v397 = *(float *)(v9 + 208);
          v495 = 2 * v391 + 2;
          sub_18005AB20(v9, (unsigned int)(v391 + 8 * v391 + 3), v495);
          v398 = *(_DWORD *)(v9 + 52);
          v399 = 2;
          v400 = v398 + 1;
          do
          {
            v401 = 2 * v399++;
            v402 = v398 + v401;
            **(_WORD **)(v9 + 72) = v398;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = v402 - 2;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = v402;
            *(_QWORD *)(v9 + 72) += 6LL;
          }
          while ( v399 < v392 );
          v403 = *(_QWORD *)(v9 + 56);
          if ( v392 > *(_DWORD *)(v403 + 76) )
          {
            v404 = *(void **)(v403 + 80);
            if ( v404 )
              sub_18003A8D0(v404);
            *(_QWORD *)(v403 + 80) = sub_18003A810(8LL * v392);
            v400 = v398 + 1;
            *(_DWORD *)(v403 + 76) = v392;
          }
          v405 = v391;
          v406 = 0;
          v407 = *(_QWORD *)(*(_QWORD *)(v9 + 56) + 80LL);
          if ( v392 < 4 )
            goto LABEL_444;
          do
          {
            v408 = v406;
            v409 = *(float *)(v394 + 8LL * v406) - *(float *)(v394 + 8LL * v405);
            v410 = *(float *)(v394 + 8LL * v406 + 4) - *(float *)(v394 + 8LL * v405 + 4);
            v411 = (float)(v410 * v410) + (float)(v409 * v409);
            if ( v411 <= 0.0 )
            {
              v413 = *(float *)(v394 + 8LL * v406 + 4) - *(float *)(v394 + 8LL * v405 + 4);
              v414 = *(float *)(v394 + 8LL * v406) - *(float *)(v394 + 8LL * v405);
            }
            else
            {
              v412 = 1.0 / fsqrt(v411);
              v413 = v412 * v410;
              v414 = v412 * v409;
            }
            *(float *)(v407 + 8LL * v405) = v413;
            *(float *)(v407 + 8LL * v405 + 4) = -v414;
            v415 = *(float *)(v394 + 8LL * v406 + 8) - *(float *)(v394 + 8LL * v406);
            v416 = *(float *)(v394 + 8LL * v406 + 12) - *(float *)(v394 + 8LL * v406 + 4);
            v417 = (float)(v416 * v416) + (float)(v415 * v415);
            if ( v417 <= 0.0 )
            {
              v419 = *(float *)(v394 + 8LL * v406 + 12) - *(float *)(v394 + 8LL * v406 + 4);
              v420 = *(float *)(v394 + 8LL * v406 + 8) - *(float *)(v394 + 8LL * v406);
            }
            else
            {
              v418 = 1.0 / fsqrt(v417);
              v419 = v418 * v416;
              v420 = v418 * v415;
            }
            *(float *)(v407 + 8LL * v406) = v419;
            *(float *)(v407 + 8LL * v406 + 4) = -v420;
            v421 = *(float *)(v394 + 8LL * v406 + 16) - *(float *)(v394 + 8LL * v406 + 8);
            v422 = *(float *)(v394 + 8LL * v406 + 20) - *(float *)(v394 + 8LL * v406 + 12);
            v423 = (float)(v422 * v422) + (float)(v421 * v421);
            if ( v423 <= 0.0 )
            {
              v425 = *(float *)(v394 + 8LL * v406 + 20) - *(float *)(v394 + 8LL * v406 + 12);
              v426 = *(float *)(v394 + 8LL * v406 + 16) - *(float *)(v394 + 8LL * v406 + 8);
            }
            else
            {
              v424 = 1.0 / fsqrt(v423);
              v425 = v424 * v422;
              v426 = v424 * v421;
            }
            *(float *)(v407 + 8LL * v406 + 8) = v425;
            *(float *)(v407 + 8LL * v406 + 12) = -v426;
            v427 = *(float *)(v394 + 8LL * v406 + 24) - *(float *)(v394 + 8LL * v406 + 16);
            v428 = *(float *)(v394 + 8LL * v406 + 28) - *(float *)(v394 + 8LL * v406 + 20);
            v429 = (float)(v428 * v428) + (float)(v427 * v427);
            if ( v429 <= 0.0 )
            {
              v431 = *(float *)(v394 + 8LL * v406 + 28) - *(float *)(v394 + 8LL * v406 + 20);
              v432 = *(float *)(v394 + 8LL * v406 + 24) - *(float *)(v394 + 8LL * v406 + 16);
            }
            else
            {
              v430 = 1.0 / fsqrt(v429);
              v431 = v430 * v428;
              v432 = v430 * v427;
            }
            v405 = v406 + 3;
            *(float *)(v407 + 8LL * v406 + 16) = v431;
            v406 += 4;
            *(float *)(v407 + 8 * v408 + 20) = -v432;
          }
          while ( v406 < v391 - 2 );
          if ( v406 < v392 )
          {
LABEL_444:
            do
            {
              v433 = *(float *)(v394 + 8LL * v406) - *(float *)(v394 + 8LL * v405);
              v434 = *(float *)(v394 + 8LL * v406 + 4) - *(float *)(v394 + 8LL * v405 + 4);
              v435 = (float)(v434 * v434) + (float)(v433 * v433);
              if ( v435 <= 0.0 )
              {
                v437 = *(float *)(v394 + 8LL * v406 + 4) - *(float *)(v394 + 8LL * v405 + 4);
                v438 = *(float *)(v394 + 8LL * v406) - *(float *)(v394 + 8LL * v405);
              }
              else
              {
                v436 = 1.0 / fsqrt(v435);
                v437 = v436 * v434;
                v438 = v436 * v433;
              }
              *(float *)(v407 + 8LL * v405) = v437;
              *(float *)(v407 + 8LL * v405 + 4) = -v438;
              v405 = v406++;
            }
            while ( v406 < v392 );
          }
          v439 = v397 * 0.5;
          v440 = 0;
          do
          {
            v441 = (float)(*(float *)(v407 + 8LL * v391) + *(float *)(v407 + 8LL * v440)) * 0.5;
            v442 = (float)(*(float *)(v407 + 8LL * v440 + 4) + *(float *)(v407 + 8LL * v391 + 4)) * 0.5;
            v443 = (float)(v442 * v442) + (float)(v441 * v441);
            if ( v443 <= 0.000001 )
            {
              v445 = (float)(*(float *)(v407 + 8LL * v440 + 4) + *(float *)(v407 + 8LL * v391 + 4)) * 0.5;
              v446 = (float)(*(float *)(v407 + 8LL * v391) + *(float *)(v407 + 8LL * v440)) * 0.5;
            }
            else
            {
              v444 = fminf(100.0, 1.0 / v443);
              v445 = v444 * v442;
              v446 = v444 * v441;
            }
            v447 = 2 * v391;
            v448 = v446 * v439;
            v449 = 2 * v440;
            v450 = v445 * v439;
            **(float **)(v9 + 64) = *(float *)(v394 + 8LL * v440) - v448;
            *(float *)(*(_QWORD *)(v9 + 64) + 4LL) = *(float *)(v394 + 8LL * v440 + 4) - v450;
            v451 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v451 + 8) = v395;
            *(_DWORD *)(v451 + 12) = v396;
            *(_DWORD *)(*(_QWORD *)(v9 + 64) + 16LL) = v383;
            *(float *)(*(_QWORD *)(v9 + 64) + 20LL) = v448 + *(float *)(v394 + 8LL * v440);
            v452 = v447 + v398;
            v453 = v400 + v447;
            *(float *)(*(_QWORD *)(v9 + 64) + 24LL) = v450 + *(float *)(v394 + 8LL * v440 + 4);
            v454 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v454 + 28) = v395;
            *(_DWORD *)(v454 + 32) = v396;
            *(_DWORD *)(*(_QWORD *)(v9 + 64) + 36LL) = 0;
            *(_QWORD *)(v9 + 64) += 40LL;
            **(_WORD **)(v9 + 72) = 2 * v440 + v398;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = v452;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = v453;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 6LL) = v453;
            v391 = v440++;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 8LL) = v400 + v449;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 10LL) = v449 + v398;
            *(_QWORD *)(v9 + 72) += 12LL;
          }
          while ( v440 < v392 );
          v455 = (unsigned __int16)v495;
          v385 = (int *)(v9 + 80);
          v350 = v517;
        }
        else
        {
          sub_18005AB20(v9, (unsigned int)(3 * (v391 - 1)), (unsigned int)v392);
          v456 = 0;
          do
          {
            v457 = *(_QWORD *)(v394 + 8 * v456);
            v456 = (unsigned int)(v456 + 1);
            **(_QWORD **)(v9 + 64) = v457;
            v458 = *(_QWORD *)(v9 + 64);
            *(_DWORD *)(v458 + 8) = v395;
            *(_DWORD *)(v458 + 12) = v396;
            *(_DWORD *)(*(_QWORD *)(v9 + 64) + 16LL) = v383;
            *(_QWORD *)(v9 + 64) += 20LL;
          }
          while ( (int)v456 < v392 );
          for ( k = 2; k < v392; ++k )
          {
            **(_WORD **)(v9 + 72) = *(_WORD *)(v9 + 52);
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 2LL) = *(_WORD *)(v9 + 52) + k - 1;
            v460 = k;
            *(_WORD *)(*(_QWORD *)(v9 + 72) + 4LL) = *(_WORD *)(v9 + 52) + v460;
            *(_QWORD *)(v9 + 72) += 6LL;
          }
          v455 = (unsigned __int16)v392;
        }
        v378 = v478;
        *(_DWORD *)(v9 + 52) += v455;
      }
      *v385 = 0;
    }
    v461 = _mm_unpacklo_ps(v376, (__m128)LODWORD(v516)).m128_f32[0];
    sub_1800681E0(v9, _mm_unpacklo_ps(v381, v379).m128_u32[0], LODWORD(v461), 1, v383 | 0xFFFFFF);
    v350.m128_f32[0] = (float)(v350.m128_f32[0] + v378) - v376.m128_f32[0];
    v462 = v350;
    v462.m128_f32[0] = v350.m128_f32[0] - 1.0;
    v382.m128_f32[0] = v376.m128_f32[0] + 2.0;
    sub_1800681E0(v9, _mm_unpacklo_ps(v462, v379).m128_u32[0], _mm_unpacklo_ps(v382, v376).m128_u32[0], 0, v383);
    sub_1800681E0(v9, _mm_unpacklo_ps(v350, v379).m128_u32[0], LODWORD(v461), 0, v383 | 0xFFFFFF);
  }
  sub_18004B190();
  v463 = v470;
  if ( v470 )
  {
    v135 = (unsigned int)sub_1800B8AD0(v526, a2, v525) == 0;
    v464 = v480;
    if ( v135 )
      v463 = 0;
    if ( !v463 )
      goto LABEL_435;
    v465 = *(unsigned int *)(v480 + 7744);
    if ( !(_DWORD)v465 )
      goto LABEL_435;
    sub_18003A1B0(v465);
  }
  else
  {
    v463 = 0;
  }
  v464 = v480;
LABEL_435:
  if ( !v522 )
    *(_DWORD *)(v464 + 9564) = 0;
  v466 = *(_QWORD *)(qword_18010C470 + 5216);
  v467 = *(_DWORD *)(v466 + 264);
  if ( v467 > 1 )
    *(_DWORD *)(v466 + 264) = v467 - 1;
  else
    sub_180049A30("Calling PopID() too many times!");
  return v463;
}
