// sub_180079E10 size=18218
char __fastcall sub_180079E10(
        char *a1,
        const char *a2,
        const char *a3,
        signed int a4,
        _QWORD *a5,
        int a6,
        __int64 a7,
        __int64 a8)
{
  __int64 v9; // r14
  __int64 v10; // r15
  unsigned int v11; // r12d
  int v12; // r9d
  float v13; // xmm1_4
  float v14; // xmm6_4
  float v15; // xmm7_4
  float v16; // xmm9_4
  char v17; // al
  int v18; // edi
  char v19; // bl
  __int64 v20; // r9
  char result; // al
  __int64 v22; // rdi
  float v23; // xmm14_4
  char v24; // al
  __int64 v25; // r8
  unsigned __int8 v26; // al
  char *v27; // r9
  __int64 v28; // r10
  __int64 v29; // r15
  __int64 v30; // r13
  int v31; // r8d
  float v32; // xmm1_4
  __int64 v33; // rax
  __int64 v34; // rcx
  float v35; // xmm13_4
  int v36; // eax
  bool v37; // r12
  int v38; // r8d
  int *v39; // rbx
  _QWORD *v40; // rdi
  unsigned int v41; // esi
  char v42; // si
  __int64 v43; // rax
  unsigned int v44; // ebx
  char v45; // bl
  float v46; // xmm11_4
  char v47; // dl
  char v48; // r14
  char v49; // si
  int v50; // r12d
  int v51; // edi
  __int64 v52; // r14
  int v53; // edx
  __int64 i; // rbx
  int v55; // edi
  int j; // r8d
  int v57; // esi
  unsigned __int64 v58; // rax
  int v59; // r8d
  unsigned __int64 v60; // rdx
  int *v61; // rbx
  int v62; // edx
  int v63; // edx
  int v64; // edx
  bool v65; // di
  __int64 v66; // r13
  __int64 v67; // r15
  unsigned int v68; // r11d
  char v69; // r10
  __int64 v70; // r9
  __int64 v71; // rax
  int v72; // ecx
  __int64 v73; // rax
  __int64 v74; // rax
  unsigned int v75; // eax
  const char *v76; // rax
  int v77; // eax
  __int64 v78; // rbx
  int v79; // ecx
  __int64 v80; // rcx
  unsigned int v81; // edi
  unsigned int *v82; // rbx
  __int64 v83; // rcx
  char v84; // si
  int v85; // edi
  __int16 v86; // r8
  float v87; // xmm6_4
  float *v88; // rax
  unsigned int *v89; // rdx
  unsigned int v90; // ecx
  unsigned int v91; // edx
  __int64 v92; // rcx
  unsigned int v93; // edx
  __int64 v94; // rcx
  int v95; // ecx
  int v96; // edx
  char v97; // r12
  __int64 v98; // rsi
  char v99; // r8
  char v100; // al
  const char *v101; // rax
  bool v102; // al
  __int64 v103; // rbx
  __int64 v104; // r8
  int v105; // edx
  int v106; // edx
  __int64 v107; // rcx
  __int64 v108; // rdx
  __int64 v109; // rcx
  float v110; // xmm9_4
  int v111; // r14d
  char v112; // cl
  float v113; // xmm7_4
  char *v114; // r13
  float v115; // xmm8_4
  __int64 v116; // r12
  int v117; // edi
  float v118; // xmm6_4
  int v119; // ebx
  bool v120; // r15
  int v121; // r14d
  int *v122; // rdx
  __int64 v123; // rcx
  bool v124; // cl
  float v125; // xmm6_4
  unsigned int v126; // edi
  double v127; // xmm0_8
  int v128; // esi
  __int64 v129; // rcx
  int v130; // edi
  __int64 v131; // rdx
  __int64 v132; // r13
  int *v133; // rcx
  int v134; // eax
  __int64 v135; // rbx
  __int64 v136; // r14
  int v137; // edi
  bool v138; // cc
  unsigned __int64 v139; // rcx
  unsigned __int64 v140; // rdx
  unsigned __int64 v141; // rbx
  const char *v142; // rax
  char v143; // r8
  bool v144; // dl
  const char *v145; // rax
  char v146; // al
  bool v147; // zf
  __int64 v148; // rcx
  _DWORD *v149; // rcx
  int v150; // eax
  int v151; // r8d
  int v152; // edx
  char v153; // bl
  __int64 v154; // rdx
  int v155; // ecx
  char v156; // al
  __int64 v157; // r12
  char v158; // al
  int v159; // edi
  float v160; // xmm6_4
  int v161; // ebx
  bool v162; // r15
  int v163; // r14d
  float v164; // xmm6_4
  unsigned int v165; // edi
  double v166; // xmm0_8
  int v167; // esi
  __int64 v168; // rcx
  int v169; // edi
  int v170; // ebx
  unsigned int v171; // ebx
  __int64 v172; // rdx
  int v173; // eax
  int v174; // edi
  float v175; // xmm6_4
  int v176; // r14d
  float v177; // xmm6_4
  unsigned int v178; // edi
  double v179; // xmm0_8
  int v180; // esi
  __int64 v181; // rcx
  int v182; // edi
  __int64 v183; // rdx
  float v184; // xmm6_4
  __int64 v185; // r12
  int v186; // edi
  int v187; // ebx
  int v188; // r14d
  unsigned int v189; // edx
  char v190; // al
  bool v191; // al
  float v192; // xmm6_4
  unsigned int v193; // edi
  double v194; // xmm0_8
  int v195; // esi
  __int64 v196; // rcx
  int v197; // edi
  __int64 v198; // rdx
  int v199; // ebx
  int v200; // ecx
  int v201; // ecx
  __int64 v202; // rdx
  char v203; // dl
  float v204; // xmm8_4
  int v205; // ebx
  int v206; // ecx
  __int64 v207; // rax
  unsigned int v208; // r12d
  int v209; // eax
  unsigned int v210; // r13d
  int v211; // r14d
  char v212; // r14
  bool v213; // r13
  bool v214; // si
  bool v215; // r15
  int v216; // edi
  __int64 v217; // rcx
  char v218; // bl
  int v219; // eax
  __int64 v220; // rdx
  int v221; // r12d
  __int64 v222; // r10
  __int64 v223; // rax
  __int64 v224; // rdx
  __int64 v225; // rdx
  unsigned int v226; // eax
  unsigned __int8 v227; // si
  int v228; // r9d
  __int64 v229; // rdx
  char v230; // r9
  char v231; // r8
  __int64 (*v232)(void); // rax
  char *v233; // rdi
  int v234; // eax
  int v235; // r14d
  void *v236; // rsi
  __int32 v237; // ebx
  int v238; // r9d
  int v239; // ebx
  __int32 v240; // ebx
  __int32 v241; // eax
  __int64 v242; // rax
  unsigned __int64 v243; // rdi
  __int32 v244; // r14d
  signed int *v245; // rbx
  signed int v246; // eax
  signed int v247; // edx
  signed int v248; // ecx
  __int64 v249; // rax
  int v250; // edi
  int v251; // ecx
  int v252; // ebx
  int v253; // ebx
  void (__fastcall *v254)(_QWORD, _QWORD); // rax
  __int64 v255; // rcx
  __int64 v256; // rbx
  char *v257; // r12
  int v258; // r13d
  unsigned int v259; // r14d
  __int64 v260; // rdi
  __int64 v261; // rbx
  unsigned __int64 v262; // r9
  int v263; // r8d
  unsigned __int64 v264; // r10
  unsigned __int64 v265; // rdx
  __int64 v266; // rax
  unsigned __int64 v267; // rcx
  __int64 v268; // r8
  char *v269; // rsi
  __int64 v270; // rdi
  __int64 v271; // rbx
  unsigned __int64 v272; // r9
  int v273; // r8d
  unsigned __int64 v274; // r10
  unsigned __int64 v275; // rdx
  __int64 v276; // rax
  unsigned __int64 v277; // rcx
  __int64 v278; // r9
  void *v279; // r8
  char v280; // al
  int v281; // eax
  int v282; // ebx
  int v283; // edi
  const char *v284; // rbx
  int *v285; // r14
  _DWORD *v286; // rax
  int v287; // ebx
  int v288; // edi
  int v289; // esi
  char v290; // r8
  int v291; // edx
  __int64 v292; // r9
  int v293; // ecx
  int v294; // edx
  int v295; // edi
  int v296; // r10d
  __int64 v297; // r14
  int v298; // edx
  __int64 k; // rbx
  int v300; // edi
  int m; // r8d
  int v302; // esi
  unsigned __int64 v303; // rax
  int v304; // r8d
  unsigned __int64 v305; // rdx
  __int64 v306; // rdx
  const char *v307; // rdi
  char *v308; // rbx
  int v309; // eax
  int v310; // eax
  int v311; // eax
  char *v312; // rbx
  int v313; // eax
  signed int v314; // ebx
  int v315; // r9d
  int v316; // eax
  float v317; // xmm6_4
  float v318; // xmm15_4
  float v319; // xmm14_4
  float v320; // xmm1_4
  float v321; // xmm15_4
  const char *v322; // r15
  char v323; // r9
  char v324; // al
  __int64 v325; // r8
  __int64 v326; // rdx
  int v327; // ecx
  int v328; // ecx
  __int64 v329; // rcx
  __int64 v330; // rcx
  __int64 v331; // rbx
  __int64 v332; // rax
  __int64 v333; // r8
  int v334; // edx
  int v335; // edx
  __int64 v336; // rcx
  __int64 v337; // r8
  int v338; // edx
  __int64 v339; // rdx
  __int64 v340; // rbx
  const char *n; // rdi
  int v342; // r13d
  int v343; // eax
  int v344; // ebx
  int v345; // eax
  __int64 v346; // rcx
  int *v347; // r14
  int v348; // r8d
  int v349; // ebx
  __int64 v350; // rax
  __int64 v351; // rsi
  int v352; // r12d
  __int64 *v353; // rbx
  int v354; // esi
  const char *v355; // r13
  unsigned __int64 v356; // rbx
  __int64 v357; // r13
  int v358; // eax
  int v359; // ecx
  int v360; // r8d
  int v361; // eax
  _BYTE *v362; // rax
  int v363; // eax
  int v364; // ecx
  int v365; // r8d
  int v366; // eax
  __int64 v367; // rax
  int v368; // eax
  int v369; // ecx
  int v370; // r8d
  int v371; // eax
  __int64 v372; // rax
  __int64 v373; // rdx
  int v374; // ecx
  int v375; // r8d
  int v376; // eax
  __int64 v377; // rbx
  int v378; // r13d
  int v379; // ecx
  int v380; // r8d
  int v381; // eax
  int v382; // esi
  float v383; // xmm13_4
  __int64 v384; // rcx
  __int64 v385; // r8
  _DWORD *v386; // r9
  unsigned __int64 v387; // rsi
  _DWORD *v388; // rbx
  unsigned __int64 v389; // rdx
  unsigned __int64 v390; // rcx
  bool v391; // zf
  char v392; // al
  __int64 v393; // rbx
  int v394; // ecx
  float v395; // xmm11_4
  float v396; // xmm12_4
  __int64 v397; // rbx
  __int64 v398; // rax
  __int64 v399; // r9
  __int64 v400; // r10
  int v401; // eax
  int v402; // r13d
  char v403; // al
  float v404; // xmm10_4
  __int64 v405; // rcx
  float v406; // xmm5_4
  float v407; // xmm2_4
  float v408; // xmm3_4
  float v409; // xmm4_4
  float v410; // xmm1_4
  int v411; // edx
  float v412; // xmm0_4
  float v413; // xmm3_4
  float v414; // xmm3_4
  int v415; // esi
  int v416; // eax
  int v417; // ecx
  float v418; // xmm1_4
  float v419; // eax
  float v420; // xmm8_4
  float v421; // xmm9_4
  __int64 v422; // r8
  __int64 v423; // rbx
  float v424; // xmm0_4
  __int64 v425; // rax
  __int64 v426; // rax
  float v427; // xmm7_4
  __int64 v428; // rax
  int v429; // edx
  int v430; // ecx
  int v431; // eax
  const char *v432; // r12
  const char *v433; // r11
  int v434; // ebx
  int v435; // r13d
  float v436; // xmm13_4
  float v437; // xmm11_4
  int v438; // r9d
  __int64 v439; // rcx
  int v440; // edx
  __int64 v441; // rax
  __int64 v442; // r8
  const char *v443; // r10
  int v444; // ecx
  const char *v445; // rbx
  char v446; // si
  const char *v447; // r12
  const char *v448; // r8
  float *v449; // rax
  float v450; // xmm6_4
  float *v451; // rax
  float v452; // xmm4_4
  float v453; // xmm3_4
  float v454; // xmm2_4
  __m128 v455; // xmm8
  float *v456; // rax
  int v457; // edx
  __int64 v458; // r10
  int v459; // edx
  __int64 v460; // rsi
  float v461; // xmm2_4
  __int64 v462; // rbx
  float v463; // xmm0_4
  bool v464; // cl
  float v465; // xmm6_4
  float v466; // xmm7_4
  float v467; // xmm0_4
  int v468; // eax
  unsigned int v469; // r13d
  float v470; // xmm0_4
  int v471; // r9d
  __int64 v472; // r8
  __int64 v473; // rdx
  int v474; // ecx
  int v475; // ecx
  __int64 v476; // rcx
  __int64 v477; // rdx
  __int64 v478; // rcx
  float v479; // xmm3_4
  float v480; // xmm13_4
  __int64 v481; // rcx
  __int64 v482; // rax
  int v483; // ebx
  unsigned int v484; // esi
  __int64 v485; // rsi
  __int64 v486; // r14
  float v487; // xmm0_4
  float v488; // xmm1_4
  int v489; // eax
  int v490; // r14d
  __int64 v491; // rax
  const char *v492; // rbx
  int v493; // edx
  __m128 v494; // xmm0
  char v495; // dl
  __int64 v496; // rax
  int v497; // ecx
  int v498; // [rsp+28h] [rbp-E0h]
  bool v499; // [rsp+68h] [rbp-A0h]
  char v500; // [rsp+68h] [rbp-A0h]
  char v501; // [rsp+68h] [rbp-A0h]
  char v502; // [rsp+69h] [rbp-9Fh]
  char v503; // [rsp+6Ah] [rbp-9Eh]
  char v504; // [rsp+6Bh] [rbp-9Dh]
  char v505; // [rsp+6Bh] [rbp-9Dh]
  __int64 v506; // [rsp+70h] [rbp-98h]
  unsigned int v507; // [rsp+78h] [rbp-90h]
  __int64 v508; // [rsp+80h] [rbp-88h]
  bool v509; // [rsp+88h] [rbp-80h]
  char v510; // [rsp+88h] [rbp-80h]
  unsigned int v511; // [rsp+8Ch] [rbp-7Ch]
  int v512; // [rsp+90h] [rbp-78h]
  int v513; // [rsp+94h] [rbp-74h]
  char v514; // [rsp+98h] [rbp-70h]
  float v515; // [rsp+9Ch] [rbp-6Ch]
  int v516; // [rsp+9Ch] [rbp-6Ch]
  int v517; // [rsp+9Ch] [rbp-6Ch]
  char v518; // [rsp+A0h] [rbp-68h]
  unsigned __int8 v519; // [rsp+A1h] [rbp-67h]
  _BYTE v520[20]; // [rsp+A8h] [rbp-60h] BYREF
  int v521; // [rsp+BCh] [rbp-4Ch]
  bool v522; // [rsp+C0h] [rbp-48h]
  char v523; // [rsp+C1h] [rbp-47h]
  char v524; // [rsp+C2h] [rbp-46h]
  int v525; // [rsp+C4h] [rbp-44h]
  float v526; // [rsp+C8h] [rbp-40h]
  __int64 v527; // [rsp+D0h] [rbp-38h]
  float v528; // [rsp+D8h] [rbp-30h] BYREF
  float v529; // [rsp+DCh] [rbp-2Ch]
  __m128 v530; // [rsp+E0h] [rbp-28h] BYREF
  char v531; // [rsp+F0h] [rbp-18h]
  int v532; // [rsp+F4h] [rbp-14h]
  __int64 v533; // [rsp+F8h] [rbp-10h] BYREF
  int v534; // [rsp+100h] [rbp-8h]
  __int64 v535; // [rsp+108h] [rbp+0h]
  float v536; // [rsp+110h] [rbp+8h]
  __int64 v537; // [rsp+118h] [rbp+10h] BYREF
  int v538; // [rsp+120h] [rbp+18h]
  float v539; // [rsp+124h] [rbp+1Ch]
  __int64 *v540; // [rsp+128h] [rbp+20h] BYREF
  float v541; // [rsp+130h] [rbp+28h] BYREF
  float v542; // [rsp+134h] [rbp+2Ch]
  float v543; // [rsp+138h] [rbp+30h]
  float v544; // [rsp+13Ch] [rbp+34h]
  __int64 v545; // [rsp+140h] [rbp+38h]
  int *v546; // [rsp+148h] [rbp+40h]
  _QWORD *v547; // [rsp+150h] [rbp+48h]
  __int64 v548; // [rsp+158h] [rbp+50h]
  float v549; // [rsp+160h] [rbp+58h]
  float v550; // [rsp+164h] [rbp+5Ch]
  __int64 v551; // [rsp+168h] [rbp+60h]
  float v552; // [rsp+170h] [rbp+68h]
  __int64 v553; // [rsp+178h] [rbp+70h] BYREF
  int v554; // [rsp+180h] [rbp+78h]
  int v555; // [rsp+184h] [rbp+7Ch]
  __int64 v556; // [rsp+188h] [rbp+80h]
  __int64 v557; // [rsp+190h] [rbp+88h]
  __int128 v558; // [rsp+198h] [rbp+90h]
  __int128 v559; // [rsp+1A8h] [rbp+A0h]
  const char *v560; // [rsp+1B8h] [rbp+B0h] BYREF
  const char *v561; // [rsp+1C0h] [rbp+B8h]
  __int64 v562; // [rsp+1C8h] [rbp+C0h]
  char v563; // [rsp+1D0h] [rbp+C8h] BYREF
  __int64 v564; // [rsp+1D8h] [rbp+D0h] BYREF
  int v565; // [rsp+1E0h] [rbp+D8h]
  int v566; // [rsp+1E4h] [rbp+DCh]
  __int64 v567; // [rsp+1E8h] [rbp+E0h]
  __int64 v568; // [rsp+1F0h] [rbp+E8h]
  const char *v569; // [rsp+1F8h] [rbp+F0h]
  int v570; // [rsp+200h] [rbp+F8h]
  signed int v571; // [rsp+204h] [rbp+FCh]
  __int128 v572; // [rsp+208h] [rbp+100h]
  __int128 v573; // [rsp+218h] [rbp+110h]
  __int128 v574; // [rsp+228h] [rbp+120h]
  __int128 v575; // [rsp+238h] [rbp+130h]
  __int128 v576; // [rsp+248h] [rbp+140h]
  __int128 v577; // [rsp+258h] [rbp+150h]
  char v578; // [rsp+268h] [rbp+160h] BYREF
  _OWORD v579[2]; // [rsp+270h] [rbp+168h] BYREF
  char v580; // [rsp+290h] [rbp+188h] BYREF

  v9 = qword_18010C470;
  v508 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  v10 = *(_QWORD *)(v9 + 5216);
  v551 = v10;
  if ( *(_BYTE *)(v10 + 209) )
    return 0;
  v512 = a6 & 0x4000000;
  if ( (a6 & 0x4000000) != 0 )
    sub_18004AFD0();
  v11 = sub_1800465E0(v10, a1);
  v507 = v11;
  LOBYTE(v12) = 1;
  sub_18003DF30((unsigned int)&a7, (_DWORD)a1, 0, v12, -1082130432);
  sub_18004AE40();
  sub_18004AEC0(&a8, *a5);
  v515 = *((float *)&a8 + 1);
  v552 = *(float *)&a7;
  if ( *(float *)&a7 <= 0.0 )
    v13 = 0.0;
  else
    v13 = *(float *)&a7 + *(float *)(v9 + 3236);
  v14 = *(float *)(v10 + 280);
  v541 = v14;
  v15 = *(float *)(v10 + 284);
  v542 = v15;
  v16 = *(float *)&a8;
  v543 = v14 + *(float *)&a8;
  v544 = *((float *)&a8 + 1) + v15;
  v530.m128_u64[0] = __PAIR64__(LODWORD(v15), LODWORD(v14));
  v530.m128_f32[2] = v14 + (float)(v13 + *(float *)&a8);
  v530.m128_f32[3] = v15 + *((float *)&a8 + 1);
  v573 = 0;
  v574 = 0;
  v575 = 0;
  v576 = 0;
  v577 = 0;
  *(float *)&a7 = v530.m128_f32[2] - v14;
  *((float *)&a7 + 1) = (float)(v15 + *((float *)&a8 + 1)) - v15;
  if ( (a6 & 0x4000000) != 0 )
  {
    sub_18004AAD0(&a7);
    sub_18004A070(&v530, v11, &v541, 0x100000);
    if ( !v17 )
    {
LABEL_17:
      sub_18004B190();
      return 0;
    }
    v573 = *(_OWORD *)(v9 + 7744);
    v574 = *(_OWORD *)(v9 + 7760);
    v575 = *(_OWORD *)(v9 + 7776);
    v576 = *(_OWORD *)(v9 + 7792);
    v577 = *(_OWORD *)(v9 + 7808);
    *(float *)(v10 + 280) = v14;
    *(float *)(v10 + 284) = v15;
    v18 = *(_DWORD *)(v9 + 8136);
    if ( v18 == v11 && (*(_DWORD *)(v9 + 8148) & 0x28) == 8 && (a6 & 0x20) != 0 )
    {
      *(_DWORD *)(v9 + 8136) = 0;
      v18 = 0;
    }
    if ( *(_DWORD *)(v9 + 5332) == v11 )
      *(_DWORD *)(v9 + 8136) = 0;
    sub_180036E50(3, v9 + 3536);
    sub_180036FE0(7, *(float *)(v9 + 3220));
    sub_180036FE0(8, *(float *)(v9 + 3224));
    a7 = 0;
    sub_180037110(2, &a7);
    *(float *)&a7 = v543 - v541;
    *((float *)&a7 + 1) = v544 - v542;
    v19 = sub_18003E470(a1, v11, &a7, 1, 4);
    *(_DWORD *)(v9 + 8136) = v18;
    sub_1800371B0(3);
    sub_180036F60(1);
    if ( !v19 )
    {
      sub_18003E7F0();
      goto LABEL_17;
    }
    v22 = *(_QWORD *)(v9 + 5216);
    v527 = v22;
    *(_WORD *)(v22 + 374) |= 1 << *(_BYTE *)(v22 + 368);
    *(float *)(v22 + 280) = *(float *)(v9 + 3212) + *(float *)(v22 + 280);
    *(float *)(v22 + 284) = *(float *)(v9 + 3216) + *(float *)(v22 + 284);
    v23 = v16 - *(float *)(v22 + 192);
    v549 = v23;
  }
  else
  {
    v23 = *(float *)&a8;
    v549 = *(float *)&a8;
    v22 = v10;
    v527 = v10;
    sub_18004AAD0(&a7);
    if ( (a6 & 0x8000000) == 0 )
    {
      sub_18004A070(&v530, v11, &v541, 0x100000);
      if ( !v24 )
        return 0;
    }
  }
  v25 = *(unsigned int *)(v9 + 7748);
  LODWORD(v25) = v25 | 0x8000;
  v26 = sub_18003A530(&v541, v11, v25, v20);
  if ( v26 )
  {
    *(_DWORD *)(qword_18010C470 + 9240) = 1;
    LODWORD(v27) = 0;
    if ( !*(_BYTE *)(v9 + 8113) )
      LODWORD(v27) = v26;
  }
  else
  {
    LODWORD(v27) = 0;
  }
  v526 = *(float *)&v27;
  if ( v11 && *(_DWORD *)(qword_18010C470 + 9276) == v11 )
  {
    v28 = qword_18010C470 + 9256;
    v29 = qword_18010C470 + 9372;
    v30 = qword_18010C470 + 9264;
    v535 = qword_18010C470 + 9280;
    v545 = qword_18010C470 + 9296;
    v533 = qword_18010C470 + 9304;
    v537 = qword_18010C470 + 9376;
    v548 = qword_18010C470 + 9380;
  }
  else
  {
    v28 = 0;
    v29 = 116;
    v30 = 8;
    v535 = 24;
    v545 = 40;
    v533 = 48;
    v537 = 120;
    v548 = 124;
  }
  v506 = v28;
  v31 = a6 | 0x200;
  if ( (*(_DWORD *)(v9 + 7748) & 0x800) == 0 )
    v31 = a6;
  v513 = v31;
  v511 = v31 & 0x200;
  v532 = v31 & 0x400;
  v534 = v31 & 0x1000000;
  if ( (v31 & 0x1000000) != 0 )
  {
    if ( *(_BYTE *)(v22 + 201) )
      v32 = 0.0;
    else
      v32 = -*(float *)(v9 + 3268);
    v33 = *(_QWORD *)(qword_18010C470 + 5216);
    if ( *(_QWORD *)(v33 + 456) || (v34 = 632, *(_QWORD *)(qword_18010C470 + 8856)) )
      v34 = 584;
    v35 = fmaxf(1.0, v32 + (float)(*(float *)(v33 + v34) - *(float *)(v33 + 280)));
  }
  else
  {
    v35 = 0.0;
  }
  v550 = v35;
  v36 = *(_DWORD *)(v9 + 5332);
  v499 = v36 != v11
      && *(_DWORD *)(v9 + 8136) == v11
      && ((*(_BYTE *)(v9 + 8148) & 1) != 0 || *(_DWORD *)(v9 + 8184) == 2);
  v37 = (_BYTE)v27 && *(_BYTE *)(v9 + 2832);
  v509 = v37;
  v38 = a6 & 0x4000000;
  if ( !v512 || !v28 || v36 )
  {
LABEL_60:
    v43 = v527;
    v39 = (int *)(v527 + 264);
    v40 = (_QWORD *)(v527 + 272);
    v42 = 0;
    v547 = (_QWORD *)(v527 + 272);
    v546 = (int *)(v527 + 264);
    if ( !v38 || !v506 )
      goto LABEL_66;
    goto LABEL_62;
  }
  v39 = (int *)(v22 + 264);
  v40 = (_QWORD *)(v22 + 272);
  v41 = sub_1800360F0("#SCROLLY", 0, *(unsigned int *)(*v40 + 4LL * *v39 - 4));
  if ( *(_DWORD *)(*(_QWORD *)v527 + 5304LL) == v41 )
    sub_180053310(v41, 11, "#SCROLLY");
  if ( *(_DWORD *)(v9 + 5380) != v41 )
  {
    v38 = a6 & 0x4000000;
    goto LABEL_60;
  }
  v42 = 1;
  v547 = v40;
  v546 = v39;
LABEL_62:
  v44 = sub_1800360F0("#SCROLLY", 0, *(unsigned int *)(*v40 + 4LL * *v39 - 4));
  v43 = v527;
  if ( *(_DWORD *)(*(_QWORD *)v527 + 5304LL) == v44 )
  {
    sub_180053310(v44, 11, "#SCROLLY");
    v43 = v527;
  }
  v38 = a6 & 0x4000000;
  if ( *(_DWORD *)(v9 + 5332) == v44 )
  {
    v45 = 1;
    LOBYTE(a7) = 1;
    v46 = *(float *)(v43 + 156);
    v536 = v46;
    goto LABEL_69;
  }
LABEL_66:
  v45 = 0;
  LOBYTE(a7) = 0;
  if ( v38 )
  {
    v46 = *(float *)(v43 + 156);
    v536 = v46;
  }
  else
  {
    v46 = 3.4028235e38;
    v536 = 3.4028235e38;
    LOBYTE(a7) = 0;
  }
LABEL_69:
  if ( v506 && *(_BYTE *)v29 )
  {
    v47 = 1;
  }
  else
  {
    v47 = 0;
    if ( !v506 )
      goto LABEL_75;
  }
  if ( *(_BYTE *)(*(_QWORD *)v30 + 23LL) != (v38 == 0) )
  {
    v48 = 1;
    goto LABEL_76;
  }
LABEL_75:
  v48 = 0;
LABEL_76:
  if ( (unsigned __int8)(v499 | v42) | v37 )
  {
    v504 = 1;
  }
  else
  {
    v504 = 0;
    if ( !v45 )
    {
      v49 = 0;
      goto LABEL_81;
    }
  }
  v49 = 1;
LABEL_81:
  LOBYTE(a8) = v49;
  if ( v47 )
  {
    LOBYTE(a7) = v45;
    v50 = sub_1800B9730(a3);
    *(_BYTE *)v29 = 0;
    v51 = *(_DWORD *)v535;
    v52 = *(_QWORD *)v533;
    v53 = v50;
    if ( *(_DWORD *)v535 < v50 )
      v53 = *(_DWORD *)v535;
    for ( i = 0; (int)i < v53; i = (unsigned int)(i + 1) )
    {
      if ( *(_BYTE *)(v52 + i) != a3[i] )
        break;
    }
    if ( (_DWORD)i != v51 || (_DWORD)i != v50 )
    {
      v55 = v51 - 1;
      for ( j = v50 - 1; v55 >= (int)i; --j )
      {
        if ( j < (int)i )
          break;
        if ( *(_BYTE *)(v52 + v55) != a3[j] )
          break;
        --v55;
      }
      v57 = v55 - i + 1;
      if ( j - (int)i + 1 > 0 || v57 > 0 )
      {
        v58 = sub_180079410(*(_QWORD *)v30 + 32LL, (unsigned int)i, (unsigned int)v57);
        if ( v58 )
        {
          if ( v57 > 0 )
          {
            v59 = 0;
            if ( (unsigned int)v57 < 0x10 || (v60 = v52 + (int)i, v58 <= v52 + v55) && v58 + v55 - (int)i >= v60 )
            {
              do
              {
                *(_BYTE *)(v58 + v59) = *(_BYTE *)(v52 + v59 + (int)i);
                ++v59;
              }
              while ( v59 < v57 );
            }
            else
            {
              sub_1800B8BD0(v58, v60, v57);
            }
          }
        }
      }
    }
    sub_1800542F0(v545, (unsigned int)(a4 + 1));
    v61 = (int *)v535;
    *(_DWORD *)v535 = v50;
    sub_1800B8BD0(*(_QWORD *)v533, a3, v50 + 1);
    *(_DWORD *)(*(_QWORD *)v30 + 4LL) = *(_DWORD *)v537;
    *(_DWORD *)(*(_QWORD *)v30 + 8LL) = *(_DWORD *)v548;
    **(_DWORD **)v30 = *(_DWORD *)(*(_QWORD *)v30 + 8LL);
    v62 = *v61;
    if ( **(_DWORD **)v30 < *v61 )
      v62 = **(_DWORD **)v30;
    **(_DWORD **)v30 = v62;
    v63 = *v61;
    if ( *(_DWORD *)(*(_QWORD *)v30 + 4LL) < *v61 )
      v63 = *(_DWORD *)(*(_QWORD *)v30 + 4LL);
    *(_DWORD *)(*(_QWORD *)v30 + 4LL) = v63;
    v64 = *v61;
    if ( *(_DWORD *)(*(_QWORD *)v30 + 8LL) < *v61 )
      v64 = *(_DWORD *)(*(_QWORD *)v30 + 8LL);
    *(_DWORD *)(*(_QWORD *)v30 + 8LL) = v64;
    v65 = 0;
    v45 = a7;
    v37 = v509;
    v49 = a8;
    goto LABEL_109;
  }
  if ( !v49 || *(_DWORD *)(v508 + 5332) == v507 )
  {
    v65 = 0;
    if ( !v48 )
    {
LABEL_109:
      v66 = v506;
      goto LABEL_110;
    }
  }
  v66 = v508 + 9256;
  v506 = v508 + 9256;
  *(_DWORD *)(v508 + 9364) = -1097229926;
  v77 = *(_DWORD *)(v508 + 9276);
  if ( v77 )
  {
    v78 = qword_18010C470;
    v79 = *(_DWORD *)(qword_18010C470 + 9276);
    if ( v79 == v77 )
    {
      *(_DWORD *)(qword_18010C470 + 9408) = v79;
      v80 = v78 + 9416;
      if ( (*(_DWORD *)(v78 + 9272) & 0x200) != 0 )
      {
        sub_1800542F0(v80, 0);
      }
      else
      {
        sub_1800542F0(v80, (unsigned int)(*(_DWORD *)(v78 + 9280) + 1));
        sub_1800B8BD0(*(_QWORD *)(v78 + 9424), *(_QWORD *)(v78 + 9304), *(_DWORD *)(v78 + 9280) + 1);
      }
    }
  }
  v81 = sub_1800B9730(a3);
  sub_1800542F0(v508 + 9312, v81 + 1);
  sub_1800B8BD0(*(_QWORD *)(v508 + 9320), a3, (int)(v81 + 1));
  if ( *(_DWORD *)(v508 + 9276) != v507 || v48 )
  {
    v82 = (unsigned int *)(v508 + 9280);
LABEL_145:
    v84 = 0;
    goto LABEL_146;
  }
  v82 = (unsigned int *)(v508 + 9280);
  if ( *(_DWORD *)(v508 + 9280) != v81 )
    goto LABEL_145;
  v83 = *(_QWORD *)(v508 + 9304);
  if ( !v83 || (unsigned int)sub_1800B96A0(v83, a3, v81) )
    goto LABEL_145;
  v84 = 1;
LABEL_146:
  *(_DWORD *)(v508 + 9276) = v507;
  *v82 = v81;
  if ( v511 )
  {
    v85 = (int)a3;
  }
  else
  {
    sub_1800542F0(v508 + 9296, (unsigned int)(a4 + 1));
    v85 = (int)a3;
    sub_1800B8BD0(*(_QWORD *)(v508 + 9304), a3, (int)(*v82 + 1));
  }
  LODWORD(v27) = 0;
  *(_QWORD *)(v508 + 9348) = 0;
  v86 = v513;
  if ( (v513 & 0x20000) != 0 )
  {
    v87 = *(float *)(v508 + 3212);
    sub_18003DF30((unsigned int)&v560, v85, 0, 0, -1082130432);
    *(float *)(v508 + 9348) = fmaxf(0.0, (float)(*v88 - v16) + (float)(v87 + v87)) + *(float *)(v508 + 9348);
    v86 = v513;
    LODWORD(v27) = 0;
  }
  v89 = *(unsigned int **)(v508 + 9264);
  if ( v84 )
  {
    v90 = *v82;
    if ( (int)*v89 < (int)*v82 )
      v90 = *v89;
    *v89 = v90;
    v91 = *v82;
    v92 = *(_QWORD *)(v508 + 9264);
    if ( *(_DWORD *)(v92 + 4) < (signed int)*v82 )
      v91 = *(_DWORD *)(v92 + 4);
    *(_DWORD *)(v92 + 4) = v91;
    v93 = *v82;
    v94 = *(_QWORD *)(v508 + 9264);
    if ( *(_DWORD *)(v94 + 8) < (signed int)*v82 )
      v93 = *(_DWORD *)(v94 + 8);
    *(_DWORD *)(v94 + 8) = v93;
    v95 = a6 & 0x4000000;
  }
  else
  {
    *((_QWORD *)v89 + 327) = 6488064;
    v89[656] = 999;
    *(_QWORD *)(v89 + 1) = 0;
    *v89 = 0;
    *(_WORD *)((char *)v89 + 21) = 1;
    v89[7] = 0;
    *((_BYTE *)v89 + 20) = 0;
    v95 = a6 & 0x4000000;
    *((_BYTE *)v89 + 23) = v512 == 0;
    *((_BYTE *)v89 + 12) = 0;
    v89[4] = 0;
  }
  v65 = 0;
  if ( !v95 )
  {
    v65 = (v86 & 0x1000) != 0;
    if ( v499 && (!v84 || (*(_BYTE *)(v508 + 8148) & 4) == 0) )
      v65 = 1;
    if ( v37 && *(_BYTE *)(v508 + 252) )
      v65 = 1;
  }
  v45 = a7;
  v49 = a8;
  if ( (v86 & 0x800) != 0 )
    *(_BYTE *)(*(_QWORD *)(v508 + 9264) + 12LL) = 1;
LABEL_110:
  v67 = v508;
  v514 = *(_BYTE *)(v508 + 89);
  v68 = v507;
  if ( *(_DWORD *)(v508 + 5332) == v507 )
    goto LABEL_114;
  if ( v504 )
  {
    sub_180039FD0(v507, v551);
    sub_18004DB20(v507, v551);
    sub_18004D450(v551, 0);
    v68 = v507;
  }
  if ( *(_DWORD *)(v508 + 5332) == v68 )
  {
LABEL_114:
    v579[0] = _mm_load_si128((const __m128i *)&xmmword_1800E68F0);
    v579[1] = _mm_load_si128((const __m128i *)&xmmword_1800E68E0);
    v27 = (char *)v579;
    do
    {
      sub_180048BE0(*(unsigned int *)v27, v68);
      v27 = (char *)(v70 + 4);
    }
    while ( v27 != &v580 );
    if ( v37 )
    {
      v71 = qword_18010C470;
      *(_DWORD *)(qword_18010C470 + 7192) = v68;
      *(_DWORD *)(v71 + 7188) = v68;
      *(_WORD *)(v71 + 7196) = 0;
    }
    v72 = *(_DWORD *)(v508 + 7664);
    *(_DWORD *)(v508 + 7664) = v72 | 3;
    if ( v512 || (v513 & 0x80000) != 0 )
    {
      *(_DWORD *)(v508 + 7664) = v72 | 0xF;
      v73 = qword_18010C470;
      *(_DWORD *)(qword_18010C470 + 5500) = v68;
      *(_DWORD *)(v73 + 5496) = v68;
      *(_WORD *)(v73 + 5504) = 0;
      *(_DWORD *)(v73 + 5512) = v68;
      *(_DWORD *)(v73 + 5508) = v68;
      *(_WORD *)(v73 + 5516) = 0;
      if ( v512 )
      {
        *(_DWORD *)(v73 + 5524) = v68;
        *(_DWORD *)(v73 + 5520) = v68;
        *(_WORD *)(v73 + 5528) = 0;
        *(_DWORD *)(v73 + 5536) = v68;
        *(_DWORD *)(v73 + 5532) = v68;
        *(_WORD *)(v73 + 5540) = 0;
      }
    }
    if ( v69 )
    {
      v74 = qword_18010C470;
      *(_DWORD *)(qword_18010C470 + 7300) = v68;
      *(_DWORD *)(v74 + 7296) = v68;
      *(_WORD *)(v74 + 7304) = 0;
    }
    if ( v512 && v66 )
      *(_DWORD *)(v66 + 96) = *(_DWORD *)(v527 + 156);
    v75 = v511;
    if ( v511 )
    {
      if ( v66 )
      {
        *(_DWORD *)(v66 + 24) = sub_1800B9730(a3);
        v68 = v507;
        v76 = a3;
LABEL_175:
        *(_QWORD *)(v66 + 32) = v76;
        goto LABEL_176;
      }
      goto LABEL_176;
    }
  }
  else
  {
    v75 = v511;
  }
  if ( v66 )
  {
    if ( v75 )
      v76 = a3;
    else
      v76 = *(const char **)(v66 + 48);
    goto LABEL_175;
  }
LABEL_176:
  if ( *(_DWORD *)(v508 + 5332) == v68 && !v66 )
  {
    sub_180039FD0(0, 0);
    v68 = v507;
  }
  v96 = *(_DWORD *)(v508 + 5332);
  if ( v96 == v68 )
  {
    v97 = 0;
    v503 = 0;
    if ( !*(_BYTE *)(v508 + 2832) || (v503 = 0, v49) )
    {
      v98 = v506;
    }
    else
    {
      v503 = 0;
      v98 = v506;
      if ( !v504 )
      {
        v97 = 1;
        v503 = 1;
        v99 = 1;
        goto LABEL_187;
      }
    }
  }
  else
  {
    v98 = v506;
    if ( !v506 || (v97 = 0, v503 = 0, !v45) )
    {
      v99 = 0;
      v97 = 0;
      v503 = 0;
      goto LABEL_187;
    }
  }
  v99 = 1;
LABEL_187:
  LOBYTE(a7) = v99;
  if ( v98 && (*(_DWORD *)(*(_QWORD *)(v98 + 8) + 4LL) != *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL) || v65) && v99 )
  {
    v502 = 1;
  }
  else
  {
    v502 = 0;
    if ( !v99 )
    {
      v502 = 0;
      if ( v96 != v68 )
        goto LABEL_199;
    }
  }
  if ( v511 || !v98 )
  {
LABEL_199:
    v100 = 0;
    goto LABEL_200;
  }
  v100 = 1;
LABEL_200:
  v524 = v100;
  v102 = false;
  if ( a2 )
  {
    v101 = v100 ? *(const char **)(v98 + 48) : a3;
    if ( !*v101 )
      v102 = true;
  }
  v505 = v102;
  if ( v532 && !v102 )
  {
    v103 = qword_18010C470;
    v27 = (char *)sub_180065F80(*(_QWORD *)(qword_18010C470 + 4424), 42);
    *(_DWORD *)(v103 + 9536) = *(_DWORD *)(*(_QWORD *)(v103 + 4416) + 16LL);
    v104 = *(_QWORD *)(v103 + 4424);
    *(_DWORD *)(v103 + 9496) = *(_DWORD *)(v104 + 64);
    *(_DWORD *)(v103 + 9448) = *(_DWORD *)(v104 + 16);
    v105 = *(_DWORD *)(v104 + 32);
    *(_DWORD *)(v104 + 32) = *(_DWORD *)(v103 + 9464);
    *(_DWORD *)(v103 + 9464) = v105;
    v106 = *(_DWORD *)(v104 + 36);
    *(_DWORD *)(v104 + 36) = *(_DWORD *)(v103 + 9468);
    *(_DWORD *)(v103 + 9468) = v106;
    v107 = *(_QWORD *)(v104 + 40);
    *(_QWORD *)(v104 + 40) = *(_QWORD *)(v103 + 9472);
    *(_QWORD *)(v103 + 9472) = v107;
    v108 = *(_QWORD *)(v103 + 4424);
    LODWORD(v107) = *(_DWORD *)v108;
    *(_DWORD *)v108 = *(_DWORD *)(v103 + 9432);
    *(_DWORD *)(v103 + 9432) = v107;
    LODWORD(v107) = *(_DWORD *)(v108 + 4);
    *(_DWORD *)(v108 + 4) = *(_DWORD *)(v103 + 9436);
    *(_DWORD *)(v103 + 9436) = v107;
    v109 = *(_QWORD *)(v108 + 8);
    *(_QWORD *)(v108 + 8) = *(_QWORD *)(v103 + 9440);
    *(_QWORD *)(v103 + 9440) = v109;
    *(_DWORD *)(*(_QWORD *)(v103 + 4416) + 16LL) |= 4u;
    *(_DWORD *)(*(_QWORD *)(v103 + 4424) + 64LL) = (__int64)&v27[-*(_QWORD *)(*(_QWORD *)(v103 + 4424) + 56LL)] / 44;
    *(_DWORD *)(*(_QWORD *)(v103 + 4424) + 16LL) = *((_DWORD *)v27 + 1);
    v68 = v507;
  }
  if ( v534 && v98 && *(_DWORD *)(v98 + 20) == v68 && *(float *)(v98 + 104) != v35 )
  {
    *(_BYTE *)(v98 + 113) = 1;
    *(float *)(v98 + 104) = v35;
    LOBYTE(a7) = 1;
  }
  v525 = 2097156;
  v110 = v541;
  v539 = v541;
  v111 = v513;
  if ( *(_DWORD *)(v508 + 5332) == v68 )
  {
    *(_BYTE *)(v98 + 115) = 0;
    *(_DWORD *)(v98 + 88) = a4;
    *(_DWORD *)(v98 + 16) = v513;
    *(float *)(v98 + 104) = v35;
    v112 = *(_BYTE *)(v508 + 232);
    *(_BYTE *)(v508 + 5345) = v112 == 0;
    if ( v512 )
      v113 = *(float *)(v508 + 228) - *(float *)(v527 + 284);
    else
      v113 = *(float *)(v508 + 4432) * 0.5;
    if ( v65 )
    {
      *(_DWORD *)(*(_QWORD *)(v98 + 8) + 4LL) = 0;
      *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL) = *(_DWORD *)(v98 + 24);
      **(_DWORD **)(v98 + 8) = *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL);
      *(_BYTE *)(*(_QWORD *)(v98 + 8) + 22LL) = 0;
      v114 = (char *)(v98 + 114);
      *(_BYTE *)(v98 + 114) = 1;
      goto LABEL_395;
    }
    v115 = (float)((float)(*(float *)(v508 + 224) - v110) - *(float *)(v508 + 3212)) + *(float *)(v98 + 92);
    if ( LOBYTE(v526) && *(_WORD *)(v508 + 2842) >= 2u && !*(_BYTE *)(v508 + 253) )
    {
      v116 = *(_QWORD *)(v98 + 8);
      if ( *(_BYTE *)(v116 + 23) )
      {
        sub_180077A20(v520, v98, 0);
        v113 = *(float *)&v520[12];
      }
      v117 = *(_DWORD *)(v98 + 24);
      v118 = 0.0;
      v119 = 0;
      *(_QWORD *)v520 = 0;
      *(_QWORD *)&v520[12] = 0;
      v521 = 0;
      v120 = 0;
      if ( v117 <= 0 )
      {
LABEL_232:
        v120 = 1;
      }
      else
      {
        while ( 1 )
        {
          sub_180077A20(v520, v98, (unsigned int)v119);
          v121 = v521;
          if ( v521 <= 0 )
            break;
          if ( !v119 && (float)(*(float *)&v520[12] + v118) > v113 )
          {
            v119 = 0;
            goto LABEL_234;
          }
          if ( (float)(*(float *)&v520[16] + v118) > v113 )
          {
            if ( v119 >= v117 )
              goto LABEL_232;
            v125 = *(float *)v520;
            if ( *(float *)v520 <= v115 )
            {
              if ( *(float *)&v520[4] <= v115 )
              {
LABEL_248:
                v120 = 1;
                v119 += v121;
                if ( *(_BYTE *)(*(_QWORD *)(v98 + 32) + v119 - 1LL) == 10 )
                  --v119;
              }
              else
              {
                v126 = 0;
                while ( 1 )
                {
                  v127 = sub_180077920(v98, (unsigned int)v119, v126);
                  v128 = v126 + v119;
                  if ( (float)(*(float *)&v127 + v125) > v115 )
                    break;
                  v125 = *(float *)&v127 + v125;
                  v129 = *(int *)(v506 + 24);
                  if ( v128 < (int)v129 )
                    v130 = v128 + sub_180036320(&a8, *(_QWORD *)(v506 + 32) + v128, *(_QWORD *)(v506 + 32) + v129);
                  else
                    v130 = v129 + 1;
                  v126 = v130 - v119;
                  v98 = v506;
                  if ( (int)v126 >= v121 )
                    goto LABEL_248;
                }
                v120 = v126 != 0;
                if ( (float)((float)(*(float *)&v127 * 0.5) + v125) <= v115 )
                {
                  v131 = (unsigned int)v128;
                  v98 = v506;
                  v119 = sub_180077C80(v506, v131);
                }
                else
                {
                  v119 += v126;
                  v98 = v506;
                }
              }
            }
            goto LABEL_234;
          }
          v119 += v521;
          v118 = v118 + *(float *)&v520[8];
          if ( v119 >= v117 )
            goto LABEL_232;
        }
      }
      v119 = v117;
LABEL_234:
      *(_DWORD *)v116 = v119;
      *(_DWORD *)(v116 + 4) = v119;
      *(_DWORD *)(v116 + 8) = v119;
      *(_BYTE *)(v116 + 22) = 0;
      *(_BYTE *)(v98 + 117) = v120;
      v122 = *(int **)(v98 + 8);
      v123 = *v122;
      v67 = v508;
      if ( (((unsigned __int8)*(_WORD *)(v508 + 2842) - 2) & 1) != 0 )
      {
        v153 = *(_BYTE *)(v123 + *(_QWORD *)(v98 + 32));
        v98 = v506;
        *(_DWORD *)(v506 + 104) = 0;
        sub_180079A30(v506, 2097156);
        sub_180079A30(v506, 6291461);
        sub_180079A30(v506, 6291457);
        *(float *)(v506 + 104) = v35;
        if ( v153 != 10 && v512 )
        {
          v154 = *(_QWORD *)(v506 + 8);
          v155 = *(_DWORD *)(v154 + 4);
          *(_DWORD *)(v154 + 4) = *(_DWORD *)(v154 + 8);
          *(_DWORD *)(v154 + 8) = v155;
          **(_DWORD **)(v506 + 8) = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL);
        }
        *(_BYTE *)(v506 + 112) = 0;
      }
      else
      {
        v124 = !(_DWORD)v123 || *(_BYTE *)(v123 + *(_QWORD *)(v98 + 32) - 1) == 10;
        if ( v122[1] == v122[2] && v124 )
        {
          v132 = v506;
        }
        else
        {
          v132 = v506;
          sub_180079A30(v506, 2097164);
        }
        v133 = *(int **)(v132 + 8);
        if ( v133[1] == v133[2] )
        {
          v134 = *v133;
          v133[2] = *v133;
          v133[1] = v134;
        }
        v135 = **(int **)(v132 + 8);
        v136 = *(int *)(v132 + 24);
        if ( (int)v135 < (int)v136 )
          v137 = v135 + sub_180036320(&a8, *(_QWORD *)(v98 + 32) + v135, *(_QWORD *)(v98 + 32) + v136);
        else
          v137 = v136 + 1;
        v138 = v137 <= (int)v136;
        if ( v137 < (int)v136 )
        {
          while ( 1 )
          {
            if ( (*(_DWORD *)(v132 + 16) & 0x400) == 0 && v137 > 0 )
            {
              v139 = *(_QWORD *)(v98 + 32);
              v140 = v139 + v137;
              v141 = v140;
              if ( v140 <= v139 )
              {
LABEL_269:
                v141 = *(_QWORD *)(v98 + 32);
              }
              else
              {
                while ( (*(_BYTE *)--v141 & 0xC0) == 0x80 )
                {
                  if ( v141 <= v139 )
                    goto LABEL_269;
                }
              }
              sub_180036320(&a8, v140, v139 + *(int *)(v132 + 24));
              sub_180036320(&v537, v141, *(_QWORD *)(v98 + 32) + *(int *)(v132 + 24));
              LOBYTE(v27) = (_DWORD)a8 == 32 || (_DWORD)a8 == 9 || (_DWORD)a8 == 12288;
              v142 = ",";
              while ( (_DWORD)a8 != *(_DWORD *)v142 )
              {
                v142 += 4;
                if ( v142 == (const char *)&unk_1800DABA4 )
                {
                  v143 = 0;
                  goto LABEL_280;
                }
              }
              v143 = 1;
LABEL_280:
              v144 = (_DWORD)v537 == 32 || (_DWORD)v537 == 9 || (_DWORD)v537 == 12288;
              v145 = ",";
              while ( (_DWORD)v537 != *(_DWORD *)v145 )
              {
                v145 += 4;
                if ( v145 == (const char *)&unk_1800DABA4 )
                {
                  v146 = 0;
                  goto LABEL_290;
                }
              }
              v146 = 1;
LABEL_290:
              if ( (_BYTE)v27 )
              {
                if ( v146 )
LABEL_294:
                  v147 = v143 == 0;
                else
                  v147 = !v144;
                if ( v147 )
                  goto LABEL_300;
                goto LABEL_296;
              }
              if ( v146 )
                goto LABEL_294;
            }
LABEL_296:
            v148 = *(int *)(v132 + 24);
            if ( v137 < (int)v148 )
              v137 += sub_180036320(&v533, *(_QWORD *)(v98 + 32) + v137, *(_QWORD *)(v98 + 32) + v148);
            else
              v137 = v148 + 1;
            if ( v137 >= (int)v136 )
            {
LABEL_300:
              v138 = v137 <= (int)v136;
              break;
            }
          }
        }
        if ( !v138 )
          v137 = v136;
        v98 = v506;
        **(_DWORD **)(v506 + 8) = v137;
        *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = **(_DWORD **)(v506 + 8);
        v149 = *(_DWORD **)(v506 + 8);
        v150 = *(_DWORD *)(v506 + 24);
        v151 = v149[2];
        v152 = v149[1];
        if ( v152 != v151 )
        {
          if ( v152 > v150 )
          {
            v149[1] = v150;
            v152 = v150;
          }
          if ( v151 > v150 )
          {
            v149[2] = v150;
            v151 = v150;
          }
          if ( v152 == v151 )
            *v149 = v152;
        }
        if ( *v149 > v150 )
        {
          *v149 = v150;
          v114 = (char *)(v506 + 114);
          goto LABEL_393;
        }
      }
      v114 = (char *)(v98 + 114);
      goto LABEL_393;
    }
    v114 = (char *)(v98 + 114);
    v156 = *(_BYTE *)(v98 + 114);
    if ( !*(_BYTE *)(v508 + 2832) || v156 )
    {
      if ( !v112 )
        goto LABEL_394;
      if ( v156 )
        goto LABEL_395;
      v184 = 0.0;
      if ( *(float *)(v508 + 204) == 0.0 && *(float *)(v508 + 208) == 0.0 )
      {
LABEL_397:
        v189 = v511;
        if ( (v111 & 0x20) != 0 && !v511 )
        {
          if ( sub_180048D00(512, 1, v68) )
          {
            LODWORD(a8) = 9;
            if ( (unsigned __int8)sub_180079BC0(v67, (unsigned int)&a8, v111, (_DWORD)v27, v498, 0) )
              sub_180079AB0(v98, (unsigned int)a8);
          }
          v189 = v511;
        }
        v190 = *(_BYTE *)(v67 + 252);
        v191 = v190 && !*(_BYTE *)(v67 + 254) || v514 && v190;
        if ( *(int *)(v67 + 2992) > 0 )
        {
          if ( !v191 && !(v499 | v189) )
          {
            v199 = 0;
            do
            {
              LODWORD(a8) = *(unsigned __int16 *)(*(_QWORD *)(v67 + 3000) + 2LL * v199);
              if ( (_DWORD)a8 != 9 && (unsigned __int8)sub_180079BC0(v67, (unsigned int)&a8, v111, (_DWORD)v27, v498, 0) )
                sub_180079AB0(v98, (unsigned int)a8);
              ++v199;
            }
            while ( v199 < *(_DWORD *)(v67 + 2992) );
          }
          v200 = *(_DWORD *)(v67 + 2996);
          if ( v200 < 0 )
          {
            v201 = v200 / 2 + v200;
            v202 = 0;
            if ( v201 > 0 )
              v202 = (unsigned int)v201;
            sub_180054650(v67 + 2992, v202);
          }
          *(_DWORD *)(v67 + 2992) = 0;
        }
        v68 = v507;
        goto LABEL_438;
      }
      v185 = *(_QWORD *)(v98 + 8);
      if ( *(_BYTE *)(v185 + 23) )
      {
        sub_180077A20(v520, v98, 0);
        v113 = *(float *)&v520[12];
      }
      if ( *(_DWORD *)(v185 + 4) == *(_DWORD *)(v185 + 8) )
        *(_DWORD *)(v185 + 4) = *(_DWORD *)v185;
      v186 = *(_DWORD *)(v98 + 24);
      v187 = 0;
      *(_QWORD *)v520 = 0;
      *(_QWORD *)&v520[12] = 0;
      v521 = 0;
      v162 = 0;
      if ( v186 <= 0 )
      {
LABEL_389:
        v162 = 1;
      }
      else
      {
        while ( 1 )
        {
          sub_180077A20(v520, v98, (unsigned int)v187);
          v188 = v521;
          if ( v521 <= 0 )
            break;
          if ( !v187 && (float)(*(float *)&v520[12] + v184) > v113 )
          {
            v187 = 0;
            goto LABEL_391;
          }
          if ( (float)(*(float *)&v520[16] + v184) > v113 )
          {
            if ( v187 >= v186 )
              goto LABEL_389;
            v192 = *(float *)v520;
            if ( *(float *)v520 <= v115 )
            {
              if ( *(float *)&v520[4] <= v115 )
              {
LABEL_418:
                v162 = 1;
                v187 += v188;
                if ( *(_BYTE *)(*(_QWORD *)(v98 + 32) + v187 - 1LL) == 10 )
                  --v187;
              }
              else
              {
                v193 = 0;
                while ( 1 )
                {
                  v194 = sub_180077920(v98, (unsigned int)v187, v193);
                  v195 = v193 + v187;
                  if ( (float)(*(float *)&v194 + v192) > v115 )
                    break;
                  v192 = *(float *)&v194 + v192;
                  v196 = *(int *)(v506 + 24);
                  if ( v195 < (int)v196 )
                    v197 = v195 + sub_180036320(&a8, *(_QWORD *)(v506 + 32) + v195, *(_QWORD *)(v506 + 32) + v196);
                  else
                    v197 = v196 + 1;
                  v193 = v197 - v187;
                  v98 = v506;
                  if ( (int)v193 >= v188 )
                    goto LABEL_418;
                }
                v162 = v193 != 0;
                if ( (float)((float)(*(float *)&v194 * 0.5) + v192) <= v115 )
                {
                  v198 = (unsigned int)v195;
                  v98 = v506;
                  v187 = sub_180077C80(v506, v198);
                }
                else
                {
                  v187 += v193;
                  v98 = v506;
                }
              }
            }
            goto LABEL_391;
          }
          v187 += v521;
          v184 = v184 + *(float *)&v520[8];
          if ( v187 >= v186 )
            goto LABEL_389;
        }
      }
      v187 = v186;
LABEL_391:
      *(_DWORD *)(v185 + 8) = v187;
      *(_DWORD *)v185 = v187;
      *(_BYTE *)(v98 + 112) = 1;
    }
    else
    {
      if ( !LOBYTE(v526) )
        goto LABEL_397;
      v157 = *(_QWORD *)(v98 + 8);
      v158 = *(_BYTE *)(v157 + 23);
      if ( *(_BYTE *)(v508 + 253) )
      {
        if ( v158 )
        {
          sub_180077A20(v520, v98, 0);
          v113 = *(float *)&v520[12];
        }
        if ( *(_DWORD *)(v157 + 4) == *(_DWORD *)(v157 + 8) )
          *(_DWORD *)(v157 + 4) = *(_DWORD *)v157;
        v159 = *(_DWORD *)(v98 + 24);
        v160 = 0.0;
        v161 = 0;
        *(_QWORD *)v520 = 0;
        *(_QWORD *)&v520[12] = 0;
        v521 = 0;
        v162 = 0;
        if ( v159 <= 0 )
        {
LABEL_331:
          v162 = 1;
        }
        else
        {
          while ( 1 )
          {
            sub_180077A20(v520, v98, (unsigned int)v161);
            v163 = v521;
            if ( v521 <= 0 )
              break;
            if ( !v161 && (float)(*(float *)&v520[12] + v160) > v113 )
            {
              *(_DWORD *)v157 = 0;
              *(_DWORD *)(v157 + 8) = 0;
              goto LABEL_392;
            }
            if ( (float)(*(float *)&v520[16] + v160) > v113 )
            {
              if ( v161 >= v159 )
                goto LABEL_331;
              v164 = *(float *)v520;
              if ( *(float *)v520 > v115 )
                goto LABEL_359;
              if ( *(float *)&v520[4] <= v115 )
              {
LABEL_343:
                v162 = 1;
                v161 += v163;
                if ( *(_BYTE *)(*(_QWORD *)(v98 + 32) + v161 - 1LL) != 10 )
                  goto LABEL_359;
                v170 = v161 - 1;
                *(_DWORD *)v157 = v170;
                *(_DWORD *)(v157 + 8) = v170;
              }
              else
              {
                v165 = 0;
                while ( 1 )
                {
                  v166 = sub_180077920(v98, (unsigned int)v161, v165);
                  v167 = v165 + v161;
                  if ( (float)(*(float *)&v166 + v164) > v115 )
                    break;
                  v164 = *(float *)&v166 + v164;
                  v168 = *(int *)(v506 + 24);
                  if ( v167 < (int)v168 )
                    v169 = v167 + sub_180036320(&a8, *(_QWORD *)(v506 + 32) + v167, *(_QWORD *)(v506 + 32) + v168);
                  else
                    v169 = v168 + 1;
                  v165 = v169 - v161;
                  v98 = v506;
                  if ( (int)v165 >= v163 )
                    goto LABEL_343;
                }
                v162 = v165 != 0;
                if ( (float)((float)(*(float *)&v166 * 0.5) + v164) <= v115 )
                {
                  v172 = (unsigned int)v167;
                  v98 = v506;
                  v173 = sub_180077C80(v506, v172);
                  *(_DWORD *)v157 = v173;
                  *(_DWORD *)(v157 + 8) = v173;
                }
                else
                {
                  v171 = v165 + v161;
                  v98 = v506;
                  *(_DWORD *)v157 = v171;
                  *(_DWORD *)(v157 + 8) = v171;
                }
              }
              goto LABEL_392;
            }
            v161 += v521;
            v160 = v160 + *(float *)&v520[8];
            if ( v161 >= v159 )
              goto LABEL_331;
          }
        }
        *(_DWORD *)v157 = v159;
        *(_DWORD *)(v157 + 8) = v159;
      }
      else
      {
        if ( v158 )
        {
          sub_180077A20(v520, v98, 0);
          v113 = *(float *)&v520[12];
        }
        v174 = *(_DWORD *)(v98 + 24);
        v175 = 0.0;
        v161 = 0;
        *(_QWORD *)v520 = 0;
        *(_QWORD *)&v520[12] = 0;
        v521 = 0;
        v162 = 0;
        if ( v174 <= 0 )
        {
LABEL_356:
          v162 = 1;
        }
        else
        {
          while ( 1 )
          {
            sub_180077A20(v520, v98, (unsigned int)v161);
            v176 = v521;
            if ( v521 <= 0 )
              break;
            if ( !v161 && (float)(*(float *)&v520[12] + v175) > v113 )
            {
              v161 = 0;
              goto LABEL_358;
            }
            if ( (float)(*(float *)&v520[16] + v175) > v113 )
            {
              if ( v161 >= v174 )
                goto LABEL_356;
              v177 = *(float *)v520;
              if ( *(float *)v520 <= v115 )
              {
                if ( *(float *)&v520[4] <= v115 )
                {
LABEL_370:
                  v162 = 1;
                  v161 += v176;
                  if ( *(_BYTE *)(*(_QWORD *)(v98 + 32) + v161 - 1LL) == 10 )
                    --v161;
                }
                else
                {
                  v178 = 0;
                  while ( 1 )
                  {
                    v179 = sub_180077920(v98, (unsigned int)v161, v178);
                    v180 = v178 + v161;
                    if ( (float)(*(float *)&v179 + v177) > v115 )
                      break;
                    v177 = *(float *)&v179 + v177;
                    v181 = *(int *)(v506 + 24);
                    if ( v180 < (int)v181 )
                      v182 = v180 + sub_180036320(&a8, *(_QWORD *)(v506 + 32) + v180, *(_QWORD *)(v506 + 32) + v181);
                    else
                      v182 = v181 + 1;
                    v178 = v182 - v161;
                    v98 = v506;
                    if ( (int)v178 >= v176 )
                      goto LABEL_370;
                  }
                  v162 = v178 != 0;
                  if ( (float)((float)(*(float *)&v179 * 0.5) + v177) <= v115 )
                  {
                    v183 = (unsigned int)v180;
                    v98 = v506;
                    v161 = sub_180077C80(v506, v183);
                  }
                  else
                  {
                    v161 += v178;
                    v98 = v506;
                  }
                }
              }
              goto LABEL_358;
            }
            v161 += v521;
            v175 = v175 + *(float *)&v520[8];
            if ( v161 >= v174 )
              goto LABEL_356;
          }
        }
        v161 = v174;
LABEL_358:
        *(_DWORD *)(v157 + 4) = v161;
        *(_BYTE *)(v157 + 22) = 0;
LABEL_359:
        *(_DWORD *)v157 = v161;
        *(_DWORD *)(v157 + 8) = v161;
      }
    }
LABEL_392:
    *(_BYTE *)(v98 + 117) = v162;
    v67 = v508;
LABEL_393:
    *(_DWORD *)(v98 + 108) = -1097229926;
    v156 = *v114;
    v97 = v503;
    v68 = v507;
    v111 = v513;
LABEL_394:
    if ( v156 )
    {
LABEL_395:
      if ( !*(_BYTE *)(v67 + 232) )
        *v114 = 0;
      goto LABEL_397;
    }
    goto LABEL_397;
  }
LABEL_438:
  v203 = 0;
  if ( *(_DWORD *)(v67 + 5332) != v68 || *(_BYTE *)(v67 + 5344) )
  {
    v204 = v515;
    goto LABEL_654;
  }
  v204 = v515;
  if ( v97 )
  {
LABEL_654:
    v501 = 0;
    LOBYTE(a8) = 0;
    goto LABEL_655;
  }
  v205 = v111 & 0x10000;
  v206 = 1;
  if ( (int)(float)((float)(v515 - *(float *)(v67 + 3216)) / *(float *)(v67 + 4432)) >= 1 )
    v206 = (int)(float)((float)(v515 - *(float *)(v67 + 3216)) / *(float *)(v67 + 4432));
  LODWORD(v548) = v206;
  *(_DWORD *)(*(_QWORD *)(v98 + 8) + 16LL) = v206;
  LOBYTE(a8) = *(_BYTE *)(v67 + 253);
  v516 = (_BYTE)a8 != 0 ? 0x400000 : 0;
  v207 = 254;
  if ( !v514 )
    v207 = 252;
  v500 = *(_BYTE *)(v207 + v67);
  v208 = 2097159;
  if ( !v514 || !*(_BYTE *)(v67 + 252) || *(_BYTE *)(v67 + 255) || *(_BYTE *)(v67 + 254) )
  {
    v518 = 0;
    v209 = 2097154;
    v538 = 2097155;
  }
  else
  {
    v518 = 1;
    v209 = 2097158;
    v538 = 2097159;
  }
  v526 = *(float *)&v209;
  if ( sub_180048D00(4665, 1, v68) || sub_180048D00(8714, 1, v507) )
  {
    v210 = v511;
    v211 = a6 & 0x4000000;
    if ( !(v532 | v511) && (!v512 || *(_DWORD *)(*(_QWORD *)(v98 + 8) + 4LL) != *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL)) )
    {
      v519 = 1;
      goto LABEL_459;
    }
  }
  else
  {
    v211 = a6 & 0x4000000;
    v210 = v511;
  }
  v519 = 0;
LABEL_459:
  v522 = (sub_180048D00(4644, 0, v507) || sub_180048D00(4617, 0, v507))
      && !v532
      && (!v211 || *(_DWORD *)(*(_QWORD *)(v98 + 8) + 4LL) != *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL));
  v212 = 1;
  if ( !sub_180048D00(4663, 1, v507) && !sub_180048D00(8713, 1, v507) || (v523 = 1, v210) )
    v523 = 0;
  if ( !sub_180048D00(4667, 1, v507) || v205 | v210 )
  {
    v510 = 0;
    LODWORD(v537) = 2097163;
  }
  else
  {
    v510 = 1;
    LODWORD(v537) = 2097162;
  }
  v213 = (sub_180048D00(4666, 1, v507) || sub_180048D00(12859, 1, v507)) && !(v205 | v210);
  v531 = sub_180048D00(4642, 0, v507);
  v214 = (*(_BYTE *)(v67 + 8) & 2) != 0 && (*(_BYTE *)(v67 + 12) & 1) != 0;
  v215 = (unsigned __int8)sub_180046DB0(525, 1, 0) || (unsigned __int8)sub_180046DB0(627, 1, 0);
  v216 = 635;
  if ( !v214 )
    goto LABEL_492;
  v217 = 637;
  if ( *(_BYTE *)(v508 + 81) )
    v217 = 635;
  if ( !(unsigned __int8)sub_180046DB0(v217, 0, 0) && !(unsigned __int8)sub_180046DB0(636, 0, 0) )
LABEL_492:
    v212 = 0;
  if ( sub_180048D00(526, 1, v507) )
    goto LABEL_499;
  if ( !v214 )
    goto LABEL_498;
  if ( *(_BYTE *)(v508 + 81) )
    v216 = 637;
  if ( sub_180048D00(v216, 1, v507) )
LABEL_499:
    v218 = 1;
  else
LABEL_498:
    v218 = 0;
  if ( (unsigned __int8)sub_180046DB0(513, 1, 0) )
  {
    if ( !v518 )
    {
      v219 = 0x200000;
      if ( v500 )
        v219 = 2097164;
      v525 = v219;
    }
    v220 = v525 | (unsigned int)v516;
    v98 = v506;
LABEL_506:
    sub_180079A30(v98, v220);
    v501 = 0;
    v67 = v508;
LABEL_646:
    LOBYTE(a8) = 0;
    goto LABEL_647;
  }
  if ( (unsigned __int8)sub_180046DB0(514, 1, 0) )
  {
    if ( v518 )
    {
      v221 = 2097157;
    }
    else
    {
      v221 = 2097153;
      if ( v500 )
        v221 = 2097165;
    }
    v98 = v506;
    sub_180079A30(v506, v221 | (unsigned int)v516);
    v501 = 0;
    v67 = v508;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(515, 1, 0) && v512 )
  {
    v67 = v508;
    v98 = v506;
    if ( *(_BYTE *)(v508 + 252) )
    {
      v222 = v527;
      *(float *)(v527 + 172) = fmaxf(*(float *)(v527 + 156) - *(float *)(v508 + 4432), 0.0);
      *(_DWORD *)(v222 + 180) = 0;
      *(_DWORD *)(v222 + 188) = 0;
      LOBYTE(a8) = 0;
      v501 = 0;
      goto LABEL_647;
    }
    sub_180079A30(v506, (unsigned int)v516 | LODWORD(v526));
LABEL_518:
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(516, 1, 0) && v512 )
  {
    v67 = v508;
    v98 = v506;
    if ( !*(_BYTE *)(v508 + 252) )
    {
      sub_180079A30(v506, v516 | (unsigned int)v538);
      v501 = 0;
      goto LABEL_646;
    }
    v223 = v527;
    *(float *)(v527 + 172) = fminf(
                               *(float *)(v527 + 156) + *(float *)(v508 + 4432),
                               *(float *)(*(_QWORD *)(qword_18010C470 + 5216) + 164LL));
    *(_DWORD *)(v223 + 180) = 0;
    *(_DWORD *)(v223 + 188) = 0;
    LOBYTE(a8) = 0;
    v501 = 0;
LABEL_647:
    v203 = 0;
    goto LABEL_648;
  }
  if ( (unsigned __int8)sub_180046DB0(517, 1, 0) && v512 )
  {
    v224 = 2097166;
    if ( (_BYTE)a8 )
      v224 = 6291470;
    v98 = v506;
    sub_180079A30(v506, v224);
    v67 = v508;
    v536 = v46 - (float)((float)(int)v548 * *(float *)(v508 + 4432));
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(518, 1, 0) && v512 )
  {
    v225 = 2097167;
    if ( (_BYTE)a8 )
      v225 = 6291471;
    v98 = v506;
    sub_180079A30(v506, v225);
    v67 = v508;
    v536 = v46 + (float)((float)(int)v548 * *(float *)(v508 + 4432));
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(519, 1, 0) )
  {
    v67 = v508;
    if ( *(_BYTE *)(v508 + 252) )
    {
      v226 = 2097158;
      if ( (_BYTE)a8 )
        v226 = 6291462;
    }
    else
    {
      v226 = 2097156;
      if ( (_BYTE)a8 )
        v226 = 6291460;
    }
    v98 = v506;
    sub_180079A30(v506, v226);
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(520, 1, 0) )
  {
    v67 = v508;
    if ( *(_BYTE *)(v508 + 252) )
    {
      if ( (_BYTE)a8 )
        v208 = 6291463;
    }
    else
    {
      v208 = 2097157;
      if ( (_BYTE)a8 )
        v208 = 6291461;
    }
    v98 = v506;
    sub_180079A30(v506, v208);
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)sub_180046DB0(522, 1, 0) )
  {
    v227 = v519;
    if ( !(v519 | v511) )
    {
      v98 = v506;
      if ( *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL) == *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) && v500 )
        sub_180079A30(v506, 6291469);
      v220 = 2097160;
      if ( (_BYTE)a8 )
        v220 = 6291464;
      goto LABEL_506;
    }
  }
  else
  {
    v227 = v519;
  }
  if ( (unsigned __int8)sub_180046DB0(523, 1, 0) && !v511 )
  {
    v98 = v506;
    if ( *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL) == *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) )
    {
      if ( v500 )
      {
        sub_180079A30(v506, 6291468);
      }
      else if ( v514 )
      {
        v67 = v508;
        if ( *(_BYTE *)(v508 + 252) && !*(_BYTE *)(v508 + 254) && !*(_BYTE *)(v508 + 255) )
          sub_180079A30(v506, 6291460);
        goto LABEL_565;
      }
    }
    v67 = v508;
LABEL_565:
    v229 = 2097161;
    if ( (_BYTE)a8 )
      v229 = 6291465;
    sub_180079A30(v506, v229);
    v501 = 0;
    goto LABEL_646;
  }
  if ( (unsigned __int8)v212 | v215 )
  {
    v67 = v508;
    if ( !v512 || v212 || ((v513 & 0x100) != 0) != *(_BYTE *)(v508 + 252) )
    {
      v501 = 1;
      if ( *(_BYTE *)(v508 + 92) && !v512 )
      {
        v98 = v506;
        *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL) = 0;
        *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = *(_DWORD *)(v506 + 24);
        **(_DWORD **)(v506 + 8) = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL);
        *(_BYTE *)(*(_QWORD *)(v506 + 8) + 22LL) = 0;
        goto LABEL_646;
      }
      v503 = 1;
LABEL_645:
      v98 = v506;
      goto LABEL_646;
    }
    if ( !v511 )
    {
      LODWORD(a8) = 10;
      v98 = v506;
      if ( (unsigned __int8)sub_180079BC0(v508, (unsigned int)&a8, v513, v228, v498, 0) )
      {
        sub_180079AB0(v506, (unsigned int)a8);
        v501 = 0;
        goto LABEL_646;
      }
      goto LABEL_518;
    }
    goto LABEL_620;
  }
  if ( !v218 )
  {
    if ( v213 | (unsigned __int8)v510 )
    {
      v98 = v506;
      sub_180079A30(v506, (unsigned int)v537);
      *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = **(_DWORD **)(v506 + 8);
      *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL) = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL);
      v501 = 0;
      v67 = v508;
      goto LABEL_646;
    }
    if ( v531 )
    {
      v98 = v506;
      *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL) = 0;
      *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = *(_DWORD *)(v506 + 24);
      **(_DWORD **)(v506 + 8) = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL);
      *(_BYTE *)(*(_QWORD *)(v506 + 8) + 22LL) = 0;
      *(_BYTE *)(v506 + 112) = 1;
      v501 = 0;
      v67 = v508;
      goto LABEL_646;
    }
    if ( v522 | v227 )
    {
      v67 = v508;
      LOBYTE(a8) = 0;
      v501 = 0;
      if ( *(_QWORD *)(v508 + 3048) )
      {
        v249 = *(_QWORD *)(v506 + 8);
        v250 = *(_DWORD *)(v249 + 8);
        v251 = *(_DWORD *)(v249 + 4);
        if ( v251 == v250 )
        {
          v252 = *(_DWORD *)(v506 + 24);
          v250 = 0;
        }
        else
        {
          v252 = *(_DWORD *)(v249 + 8);
          if ( v251 < v250 )
            v250 = *(_DWORD *)(v249 + 4);
          else
            v252 = *(_DWORD *)(v249 + 4);
        }
        v253 = v252 - v250;
        sub_180054440(v508 + 10752, (unsigned int)(v253 + 1));
        sub_1800B8BD0(*(_QWORD *)(v508 + 10760), *(_QWORD *)(v506 + 32) + v250, v253);
        *(_BYTE *)(v253 + *(_QWORD *)(v508 + 10760)) = 0;
        v254 = *(void (__fastcall **)(_QWORD, _QWORD))(qword_18010C470 + 3048);
        if ( v254 )
          v254(qword_18010C470, *(_QWORD *)(v508 + 10760));
      }
      v147 = v227 == 0;
      v98 = v506;
      if ( !v147 )
      {
        v255 = *(_QWORD *)(v506 + 8);
        if ( *(_DWORD *)(v255 + 4) == *(_DWORD *)(v255 + 8) )
        {
          *(_DWORD *)(v255 + 4) = 0;
          *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = *(_DWORD *)(v506 + 24);
          **(_DWORD **)(v506 + 8) = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL);
          *(_BYTE *)(*(_QWORD *)(v506 + 8) + 22LL) = 0;
        }
        *(_BYTE *)(v506 + 112) = 1;
        v256 = *(_QWORD *)(v506 + 8);
        if ( *(_DWORD *)(v256 + 4) != *(_DWORD *)(v256 + 8) )
        {
          sub_180078720(v506, *(_QWORD *)(v506 + 8));
          *(_BYTE *)(v256 + 22) = 0;
        }
      }
      goto LABEL_647;
    }
    if ( !v523 )
      goto LABEL_587;
    v232 = *(__int64 (**)(void))(qword_18010C470 + 3040);
    if ( v232 )
    {
      v233 = (char *)v232();
      if ( !v233 )
      {
LABEL_587:
        v501 = 0;
        v67 = v508;
        goto LABEL_645;
      }
    }
    else
    {
      v233 = byte_1800D411C;
    }
    v234 = sub_1800B9730(v233);
    v530 = 0u;
    v235 = 0;
    v236 = nullptr;
    v237 = v234 + 1;
    if ( v234 + 1 > 0 )
    {
      v236 = (void *)sub_18003A810(v237);
      v530.m128_u64[1] = (unsigned __int64)v236;
      v530.m128_i32[1] = v237;
    }
    v67 = v508;
    if ( *v233 )
    {
      do
      {
        v233 += (int)sub_180036320(&a8, v233, 0);
        if ( (unsigned __int8)sub_180079BC0(v508, (unsigned int)&a8, v513, v238, v498, 1) )
        {
          sub_1800364B0(&v533, (unsigned int)a8);
          v239 = sub_1800B9730(&v533);
          sub_1800542F0(&v530, (unsigned int)(v235 + v239));
          v235 = v530.m128_i32[0];
          v236 = (void *)v530.m128_u64[1];
          sub_1800B8BD0(v530.m128_u64[1] + v530.m128_i32[0] - (__int64)v239, &v533, v239);
        }
      }
      while ( *v233 );
      if ( v235 > 0 )
      {
        if ( v235 == v530.m128_i32[1] )
        {
          v240 = v235 + 1;
          if ( v530.m128_i32[1] )
            v241 = v530.m128_i32[1] + v530.m128_i32[1] / 2;
          else
            v241 = 8;
          if ( v241 > v240 )
            v240 = v241;
          if ( v240 > v530.m128_i32[1] )
          {
            v242 = sub_18003A810(v240);
            v243 = v242;
            if ( v236 )
            {
              sub_1800B8BD0(v242, v236, v235);
              sub_18003A8D0(v236);
            }
            v236 = (void *)v243;
            v530.m128_u64[1] = v243;
            v530.m128_i32[1] = v240;
          }
        }
        *((_BYTE *)v236 + v235) = 0;
        v244 = v235 + 1;
        v530.m128_i32[0] = v244;
        v245 = *(signed int **)(v506 + 8);
        v246 = *(_DWORD *)(v506 + 24);
        v247 = v245[2];
        v248 = v245[1];
        if ( v248 != v247 )
        {
          if ( v248 > v246 )
          {
            v245[1] = v246;
            v248 = v246;
          }
          if ( v247 > v246 )
          {
            v245[2] = v246;
            v247 = v246;
          }
          if ( v248 == v247 )
            *v245 = v248;
        }
        if ( *v245 > v246 )
          *v245 = v246;
        sub_180078720(v506, v245);
        if ( (unsigned __int8)sub_180078390(v506, (unsigned int)*v245, v236, (unsigned int)(v244 - 1)) )
        {
          sub_180079410(v245 + 8, (unsigned int)*v245, 0);
          *v245 += v244 - 1;
          *((_BYTE *)v245 + 22) = 0;
        }
        *(_BYTE *)(v506 + 112) = 1;
      }
    }
    if ( v236 )
      sub_18003A8D0(v236);
LABEL_620:
    v501 = 0;
    goto LABEL_645;
  }
  v98 = v506;
  v67 = v508;
  if ( (v513 & 0x80u) == 0 )
  {
    v503 = 1;
    v230 = 0;
    LOBYTE(a7) = 0;
    v231 = 0;
    v203 = 1;
    LOBYTE(a8) = 0;
    v501 = 0;
  }
  else
  {
    if ( **(_BYTE **)(v506 + 48) )
    {
      v203 = 1;
      LOBYTE(a8) = 0;
      v501 = 0;
LABEL_648:
      v230 = a7;
      v231 = v502;
      goto LABEL_649;
    }
    v503 = 1;
    v230 = 0;
    LOBYTE(a7) = 0;
    v231 = 0;
    v203 = 0;
    LOBYTE(a8) = 0;
    v501 = 0;
  }
LABEL_649:
  if ( *(_DWORD *)(*(_QWORD *)(v98 + 8) + 4LL) == *(_DWORD *)(*(_QWORD *)(v98 + 8) + 8LL) || !v230 )
  {
    v502 = v231;
    v68 = v507;
  }
  else
  {
    v502 = v231 | 1;
    v68 = v507;
  }
LABEL_655:
  v257 = nullptr;
  v258 = 0;
  if ( *(_DWORD *)(v67 + 5332) != v68 )
  {
    v307 = a3;
    v306 = v511;
    goto LABEL_740;
  }
  v259 = v511;
  if ( v203 && !v511 )
  {
    if ( (v513 & 0x80u) != 0 )
    {
      v257 = byte_1800D411C;
      LOBYTE(a8) = 1;
      v260 = *(_QWORD *)(v98 + 8);
      v261 = *(int *)(v98 + 24);
      v262 = sub_180079410(v260 + 32, 0, *(unsigned int *)(v98 + 24));
      if ( v262 && (int)v261 > 0 )
      {
        v263 = 0;
        if ( (unsigned int)v261 < 0x10
          || (v264 = v98 + 32,
              v265 = *(_QWORD *)(v98 + 32),
              v266 = (int)v261 - 1,
              v267 = v266 + v262,
              v262 <= v265 + v266)
          && v267 >= v265
          || v262 <= v264 && v267 >= v264 )
        {
          do
          {
            *(_BYTE *)(v262 + v263) = *(_BYTE *)(v263 + *(_QWORD *)(v98 + 32));
            ++v263;
          }
          while ( v263 < (int)v261 );
        }
        else
        {
          sub_1800B8BD0(v262, v265, v261);
        }
      }
      v268 = *(int *)(v98 + 24);
      **(_BYTE **)(v98 + 48) = *(_BYTE *)(v268 + *(_QWORD *)(v98 + 48));
      *(_BYTE *)(v98 + 115) = 1;
      *(_DWORD *)(v98 + 24) -= v268;
      *(_QWORD *)(v260 + 4) = 0;
      *(_DWORD *)v260 = 0;
      goto LABEL_683;
    }
    v269 = *(void **)(v98 + 64);
    if ( !(unsigned int)sub_1800B9620(*(_QWORD *)(v506 + 48), (char *)v269) )
      goto LABEL_682;
    v257 = (char *)v269;
    v258 = *(_DWORD *)(v506 + 56) - 1;
    LOBYTE(a8) = 1;
    v270 = *(_QWORD *)(v506 + 8);
    v271 = *(int *)(v506 + 24);
    v272 = sub_180079410(v270 + 32, 0, *(unsigned int *)(v506 + 24));
    if ( v272 && (int)v271 > 0 )
    {
      v273 = 0;
      if ( (unsigned int)v271 < 0x10
        || (v274 = v506 + 32,
            v275 = *(_QWORD *)(v506 + 32),
            v276 = (int)v271 - 1,
            v277 = v276 + v272,
            v272 <= v275 + v276)
        && v277 >= v275
        || v272 <= v274 && v277 >= v274 )
      {
        do
        {
          *(_BYTE *)(v272 + v273) = *(_BYTE *)(v273 + *(_QWORD *)(v506 + 32));
          ++v273;
        }
        while ( v273 < (int)v271 );
      }
      else
      {
        sub_1800B8BD0(v272, v275, v271);
      }
    }
    v278 = *(int *)(v506 + 24);
    **(_BYTE **)(v506 + 48) = *(_BYTE *)(v278 + *(_QWORD *)(v506 + 48));
    *(_BYTE *)(v506 + 115) = 1;
    *(_DWORD *)(v506 + 24) -= v278;
    *(_QWORD *)(v270 + 4) = 0;
    *(_DWORD *)v270 = 0;
    if ( v258 <= 0 )
    {
LABEL_682:
      v98 = v506;
      v259 = v511;
LABEL_683:
      v68 = v507;
      goto LABEL_684;
    }
    v279 = v269;
    v98 = v506;
    v280 = sub_180078390(v506, 0, v279, (unsigned int)v258);
    v68 = v507;
    v259 = v511;
    if ( v280 )
    {
      *(_DWORD *)(v270 + 8) = v258;
      *(_DWORD *)(v270 + 4) = v258;
      *(_DWORD *)v270 = v258;
      *(_BYTE *)(v270 + 22) = 0;
    }
  }
LABEL_684:
  v281 = v513;
  if ( (v513 & 0x9C0000) != 0 )
  {
    v282 = 0x40000;
    if ( (v513 & 0x40000) != 0 )
    {
      v283 = 512;
      v147 = sub_180048D00(512, 0, v68) == 0;
      v281 = v513;
      if ( !v147 )
        goto LABEL_696;
    }
    if ( (v281 & 0x80000) != 0 )
    {
      if ( (unsigned __int8)sub_180046DB0(515, 1, 0) )
      {
        v282 = 0x80000;
        v283 = 515;
        v281 = v513;
LABEL_696:
        v557 = 0;
        v558 = 0;
        v559 = 0;
        v553 = v67;
        v554 = v282;
        v555 = v281;
        v556 = 0;
        v284 = a3;
        if ( !v259 )
          v284 = *(const char **)(v98 + 48);
        v285 = (int *)(v98 + 72);
        sub_1800542F0(v98 + 72, (unsigned int)(*(_DWORD *)(v98 + 24) + 1));
        sub_1800B8BD0(*(_QWORD *)(v98 + 80), v284, *(_DWORD *)(v98 + 24) + 1);
        HIDWORD(v557) = v283;
        *(_QWORD *)&v558 = v284;
        DWORD2(v558) = *(_DWORD *)(v98 + 24);
        HIDWORD(v558) = *(_DWORD *)(v98 + 88);
        LOBYTE(v559) = 0;
        v286 = *(_DWORD **)(v98 + 8);
        DWORD1(v559) = *v286;
        v287 = DWORD1(v559);
        v288 = v286[1];
        DWORD2(v559) = v288;
        v289 = v286[2];
        HIDWORD(v559) = v289;
        MEMORY[0](&v553);
        v290 = v559;
        v291 = DWORD1(v559);
        if ( DWORD1(v559) == v287 && !(_BYTE)v559 )
        {
          v292 = v506;
        }
        else
        {
          v292 = v506;
          **(_DWORD **)(v506 + 8) = DWORD1(v559);
          *(_BYTE *)(v506 + 112) = 1;
          v291 = DWORD1(v559);
        }
        v293 = DWORD2(v559);
        if ( DWORD2(v559) != v288 || v290 )
        {
          if ( DWORD2(v559) == v291 )
            v293 = **(_DWORD **)(v292 + 8);
          *(_DWORD *)(*(_QWORD *)(v292 + 8) + 4LL) = v293;
          v293 = DWORD2(v559);
        }
        v294 = HIDWORD(v559);
        if ( HIDWORD(v559) == v289 && !v290 )
        {
          v98 = v506;
        }
        else
        {
          v98 = v506;
          if ( HIDWORD(v559) == v293 )
            v294 = *(_DWORD *)(*(_QWORD *)(v506 + 8) + 4LL);
          *(_DWORD *)(*(_QWORD *)(v506 + 8) + 8LL) = v294;
          if ( v290 )
          {
            v295 = *v285;
            v296 = *v285 - 1;
            v297 = *(_QWORD *)(v506 + 80);
            v298 = DWORD2(v558);
            if ( v296 < SDWORD2(v558) )
              v298 = v296;
            for ( k = 0; (int)k < v298; k = (unsigned int)(k + 1) )
            {
              if ( *(_BYTE *)(v297 + k) != *(_BYTE *)(v558 + k) )
                break;
            }
            if ( (_DWORD)k != v296 || (_DWORD)k != DWORD2(v558) )
            {
              v300 = v295 - 2;
              for ( m = DWORD2(v558) - 1; v300 >= (int)k; --m )
              {
                if ( m < (int)k )
                  break;
                if ( *(_BYTE *)(v297 + v300) != *(_BYTE *)(v558 + m) )
                  break;
                --v300;
              }
              v302 = v300 - k + 1;
              if ( m - (int)k + 1 > 0 || v302 > 0 )
              {
                v303 = sub_180079410(*(_QWORD *)(v506 + 8) + 32LL, (unsigned int)k, (unsigned int)v302);
                if ( v303 )
                {
                  if ( v302 > 0 )
                  {
                    v304 = 0;
                    if ( (unsigned int)v302 < 0x10
                      || (v305 = v297 + (int)k, v303 <= v297 + v300) && v303 + v300 - (int)k >= v305 )
                    {
                      do
                      {
                        *(_BYTE *)(v303 + v304) = *(_BYTE *)(v297 + v304 + (int)k);
                        ++v304;
                      }
                      while ( v304 < v302 );
                    }
                    else
                    {
                      sub_1800B8BD0(v303, v305, v302);
                    }
                  }
                }
              }
              v67 = v508;
              v98 = v506;
            }
            *(_DWORD *)(v98 + 24) = DWORD2(v558);
            *(_DWORD *)(v98 + 108) = -1097229926;
          }
        }
        goto LABEL_735;
      }
      v147 = (unsigned __int8)sub_180046DB0(516, 1, 0) == 0;
      v281 = v513;
      if ( !v147 )
      {
        v282 = 0x80000;
        v283 = 516;
        goto LABEL_696;
      }
    }
    v283 = 0;
    v282 = 0x800000;
    if ( (v281 & 0x800000) != 0 && *(_BYTE *)(v98 + 115) )
      goto LABEL_696;
    if ( (v281 & 0x100000) != 0 )
    {
      v282 = 0x100000;
      goto LABEL_696;
    }
  }
LABEL_735:
  v306 = v511;
  v307 = a3;
  if ( v511 )
  {
    v68 = v507;
  }
  else
  {
    v308 = *(void **)(v98 + 32);
    v309 = sub_1800B9620((char *)v308, a3);
    v68 = v507;
    v306 = 0;
    if ( v309 )
    {
      v257 = (char *)v308;
      v258 = *(_DWORD *)(v98 + 24);
      LOBYTE(a8) = 1;
    }
  }
LABEL_740:
  if ( *(_DWORD *)(v67 + 9408) != v68 )
    goto LABEL_753;
  if ( *(_DWORD *)(v67 + 5332) != v68 )
  {
    v310 = *(_DWORD *)(qword_18010C470 + 7752);
    if ( (v310 & 0x20) != 0 )
    {
      if ( (v310 & 0x40) != 0 )
        goto LABEL_748;
    }
    else
    {
      v311 = *(_DWORD *)(qword_18010C470 + 7744);
      if ( *(_DWORD *)(qword_18010C470 + 5384) == v311
        && v311
        && *(_DWORD *)(qword_18010C470 + 5388) >= *(_DWORD *)(qword_18010C470 + 5032) )
      {
LABEL_748:
        if ( *(_BYTE *)(qword_18010C470 + 5392) )
        {
          if ( !(_DWORD)v306 )
          {
            v312 = *(void **)(v67 + 9424);
            if ( (unsigned int)sub_1800B9620((char *)v312, v307) )
            {
              v257 = (char *)v312;
              v258 = *(_DWORD *)(v67 + 9416) - 1;
              LOBYTE(a8) = 1;
            }
          }
        }
      }
    }
  }
  *(_DWORD *)(v67 + 9408) = 0;
LABEL_753:
  if ( v257 )
  {
    if ( (v513 & 0x400000) != 0 )
    {
      v568 = 0;
      v572 = 0;
      v564 = v67;
      v565 = 0x400000;
      v566 = v513;
      v569 = v307;
      v570 = v258;
      v313 = v258 + 1;
      if ( a4 >= v258 + 1 )
        v313 = a4;
      v571 = v313;
      v567 = 0;
      MEMORY[0](&v564, v306);
      v307 = v569;
      v314 = v571;
      v258 = v571 - 1;
      if ( v570 < v571 - 1 )
        v258 = v570;
    }
    else
    {
      v314 = a4;
    }
    if ( v258 + 1 < v314 )
      v314 = v258 + 1;
    if ( v314 )
    {
      if ( (unsigned int)v314 > 1 )
        sub_1800B97F0(v307, v257, (unsigned int)(v314 - 1));
      v307[v314 - 1] = 0;
    }
  }
  if ( *(_DWORD *)(v67 + 5332) == v507 && v503 )
    sub_180039FD0(0, 0);
  if ( v512 )
  {
    v320 = *(float *)(v527 + 284);
    v528 = *(float *)(v527 + 280);
    v529 = v320;
    v321 = v110 + v23;
    v110 = fmaxf(v110, *(float *)(v527 + 608));
    v539 = v110;
    v317 = fmaxf(v542, *(float *)(v527 + 612));
    v526 = v317;
    v530.m128_f32[1] = v317;
    v318 = fminf(v321, *(float *)(v527 + 616));
    v319 = fminf(v542 + v204, *(float *)(v527 + 620));
  }
  else
  {
    sub_180038770(&v541, v507, 0);
    *(_OWORD *)v520 = *(_OWORD *)(qword_18010C470 + 3536);
    *(float *)&v520[12] = _mm_shuffle_ps(*(__m128 *)v520, *(__m128 *)v520, 255).m128_f32[0]
                        * *(float *)(qword_18010C470 + 3148);
    sub_180036620(v520);
    LOBYTE(v315) = 1;
    sub_180038470(LODWORD(v541), LODWORD(v543), v316, v315, *(_DWORD *)(v67 + 3220));
    v528 = v110 + *(float *)(v67 + 3212);
    v529 = v542 + *(float *)(v67 + 3216);
    v317 = v542;
    v526 = v542;
    v530.m128_f32[1] = v542;
    v318 = v110 + v23;
    v319 = v542 + v204;
  }
  v530.m128_u64[1] = __PAIR64__(LODWORD(v319), LODWORD(v318));
  v530.m128_f32[0] = v110;
  if ( v524 )
    v322 = *(const char **)(v98 + 48);
  else
    v322 = v307;
  if ( !a2 )
    goto LABEL_781;
  if ( v524 )
    v307 = *(const char **)(v98 + 48);
  if ( *v307 )
LABEL_781:
    v323 = 0;
  else
    v323 = 1;
  v324 = v505;
  if ( v323 != v505 )
  {
    if ( !v532 || v505 )
    {
      v324 = v323;
      v505 = v323;
      if ( !v532 )
        goto LABEL_794;
    }
    else
    {
      v325 = qword_18010C470;
      *(_DWORD *)(*(_QWORD *)(qword_18010C470 + 4416) + 16LL) = *(_DWORD *)(qword_18010C470 + 9536);
      *(_DWORD *)(*(_QWORD *)(v325 + 4424) + 64LL) = *(_DWORD *)(v325 + 9496);
      *(_DWORD *)(*(_QWORD *)(v325 + 4424) + 16LL) = *(_DWORD *)(v325 + 9448);
      v326 = *(_QWORD *)(v325 + 4424);
      v327 = *(_DWORD *)(v325 + 9464);
      *(_DWORD *)(v325 + 9464) = *(_DWORD *)(v326 + 32);
      *(_DWORD *)(v326 + 32) = v327;
      v328 = *(_DWORD *)(v325 + 9468);
      *(_DWORD *)(v325 + 9468) = *(_DWORD *)(v326 + 36);
      *(_DWORD *)(v326 + 36) = v328;
      v329 = *(_QWORD *)(v325 + 9472);
      *(_QWORD *)(v325 + 9472) = *(_QWORD *)(v326 + 40);
      *(_QWORD *)(v326 + 40) = v329;
      v306 = *(_QWORD *)(v325 + 4424);
      LODWORD(v329) = *(_DWORD *)(v325 + 9432);
      *(_DWORD *)(v325 + 9432) = *(_DWORD *)v306;
      *(_DWORD *)v306 = v329;
      LODWORD(v329) = *(_DWORD *)(v325 + 9436);
      *(_DWORD *)(v325 + 9436) = *(_DWORD *)(v306 + 4);
      *(_DWORD *)(v306 + 4) = v329;
      v330 = *(_QWORD *)(v325 + 9440);
      *(_QWORD *)(v325 + 9440) = *(_QWORD *)(v306 + 8);
      *(_QWORD *)(v306 + 8) = v330;
      v324 = v323;
      v505 = v323;
    }
    if ( !v323 )
    {
      v331 = qword_18010C470;
      v332 = sub_180065F80(*(_QWORD *)(qword_18010C470 + 4424), 42);
      *(_DWORD *)(v331 + 9536) = *(_DWORD *)(*(_QWORD *)(v331 + 4416) + 16LL);
      v333 = *(_QWORD *)(v331 + 4424);
      *(_DWORD *)(v331 + 9496) = *(_DWORD *)(v333 + 64);
      *(_DWORD *)(v331 + 9448) = *(_DWORD *)(v333 + 16);
      v334 = *(_DWORD *)(v333 + 32);
      *(_DWORD *)(v333 + 32) = *(_DWORD *)(v331 + 9464);
      *(_DWORD *)(v331 + 9464) = v334;
      v335 = *(_DWORD *)(v333 + 36);
      *(_DWORD *)(v333 + 36) = *(_DWORD *)(v331 + 9468);
      *(_DWORD *)(v331 + 9468) = v335;
      v336 = *(_QWORD *)(v333 + 40);
      *(_QWORD *)(v333 + 40) = *(_QWORD *)(v331 + 9472);
      *(_QWORD *)(v331 + 9472) = v336;
      v337 = *(_QWORD *)(v331 + 4424);
      LODWORD(v336) = *(_DWORD *)v337;
      *(_DWORD *)v337 = *(_DWORD *)(v331 + 9432);
      *(_DWORD *)(v331 + 9432) = v336;
      v338 = *(_DWORD *)(v337 + 4);
      *(_DWORD *)(v337 + 4) = *(_DWORD *)(v331 + 9436);
      *(_DWORD *)(v331 + 9436) = v338;
      v339 = *(_QWORD *)(v337 + 8);
      *(_QWORD *)(v337 + 8) = *(_QWORD *)(v331 + 9440);
      *(_QWORD *)(v331 + 9440) = v339;
      *(_DWORD *)(*(_QWORD *)(v331 + 4416) + 16LL) |= 4u;
      v306 = (v332 - *(_QWORD *)(*(_QWORD *)(v331 + 4424) + 56LL)) / 44;
      *(_DWORD *)(*(_QWORD *)(v331 + 4424) + 64LL) = v306;
      *(_DWORD *)(*(_QWORD *)(v331 + 4424) + 16LL) = *(_DWORD *)(v332 + 4);
      goto LABEL_789;
    }
  }
LABEL_794:
  if ( v324 )
  {
    v322 = a2;
    n = &a2[sub_1800B9730(a2)];
    v340 = v508;
    goto LABEL_798;
  }
LABEL_789:
  v340 = v508;
  if ( (unsigned __int8)v502 | (unsigned __int8)a7 || *(_DWORD *)(v508 + 5332) == v507 )
  {
    n = &v322[*(int *)(v98 + 24)];
LABEL_798:
    v533 = (__int64)n;
    v517 = 0;
    v342 = 1;
    LODWORD(v537) = 1;
    if ( !v512 )
      goto LABEL_804;
    goto LABEL_799;
  }
  if ( !v512 || v534 )
  {
    n = &v322[sub_1800B9730(v322)];
    goto LABEL_798;
  }
  n = nullptr;
  v533 = 0;
LABEL_799:
  v343 = (int)(float)((float)(v317 - v529) / *(float *)(v340 + 4432));
  v344 = 0;
  if ( v343 >= 0 )
    v344 = v343;
  v517 = v344;
  v345 = (int)sub_1800B4300();
  v342 = v344;
  if ( v345 >= v344 )
    v342 = v345;
  LODWORD(v537) = v342;
LABEL_804:
  v346 = v508;
  v535 = v508;
  v347 = (int *)(v508 + 9384);
  v348 = *(_DWORD *)(v508 + 9388);
  if ( v348 < 0 )
  {
    LODWORD(v306) = v348 >> 31;
    v349 = 0;
    if ( v348 / 2 + v348 > 0 )
      v349 = v348 / 2 + v348;
    if ( v349 <= v348 )
    {
      v346 = v508;
    }
    else
    {
      v350 = sub_18003A810(4LL * v349);
      v351 = v350;
      v346 = v508;
      v306 = *(_QWORD *)(v508 + 9392);
      if ( v306 )
      {
        sub_1800B8BD0(v350, v306, 4LL * *v347);
        sub_18003A8D0(*(LPVOID *)(v508 + 9392));
        v346 = v508;
      }
      *(_QWORD *)(v346 + 9392) = v351;
      *(_DWORD *)(v346 + 9388) = v349;
      v98 = v506;
    }
  }
  *v347 = 0;
  v352 = 1;
  if ( v512 )
  {
    v353 = &v533;
    if ( n )
      v353 = nullptr;
    v540 = v353;
    if ( !(_BYTE)a7 || !v98 || (v147 = *(_BYTE *)(v98 + 112) == 0, v354 = 0x7FFFFFFF, v147) )
      v354 = v342 + 1;
    v525 = v354;
    v355 = n;
    v545 = (__int64)n;
    v352 = 0;
    v356 = (unsigned __int64)v322;
    if ( v534 )
    {
      v357 = qword_18010C470;
      if ( v322 < n )
      {
        while ( 1 )
        {
          v358 = v352++;
          if ( v358 <= v354 )
          {
            v359 = *(_DWORD *)(v346 + 9388);
            if ( *v347 == v359 )
            {
              v360 = *v347 + 1;
              if ( v359 )
                v361 = v359 + v359 / 2;
              else
                v361 = 8;
              if ( v361 > v360 )
                v360 = v361;
              sub_180054C90(v347, (unsigned int)v360);
            }
            *(_DWORD *)(*(_QWORD *)(v508 + 9392) + 4LL * (*v347)++) = v356 - (_DWORD)v322;
            v354 = v525;
          }
          v362 = (_BYTE *)sub_180066AF0(*(_QWORD *)(v357 + 4416), v306, v356, (_DWORD)n, LODWORD(v35), 2);
          v356 = (unsigned __int64)v362;
          if ( *v362 == 10 )
            v356 = (unsigned __int64)(v362 + 1);
          if ( v356 >= (unsigned __int64)n )
            break;
          v346 = v508;
        }
      }
    }
    else
    {
      if ( n )
      {
        if ( v322 < n )
        {
          while ( 1 )
          {
            v363 = v352++;
            if ( v363 <= v354 )
            {
              v364 = *(_DWORD *)(v346 + 9388);
              if ( *v347 == v364 )
              {
                v365 = *v347 + 1;
                if ( v364 )
                  v366 = v364 + v364 / 2;
                else
                  v366 = 8;
                if ( v366 > v365 )
                  v365 = v366;
                sub_180054C90(v347, (unsigned int)v365);
              }
              *(_DWORD *)(*(_QWORD *)(v508 + 9392) + 4LL * (*v347)++) = v356 - (_DWORD)v322;
              v354 = v525;
            }
            v367 = sub_1800B8A30(v356, 10, &n[-v356]);
            if ( !v367 )
              break;
            v356 = v367 + 1;
            if ( v367 + 1 >= (unsigned __int64)n )
              goto LABEL_864;
            v346 = v508;
          }
          v356 = (unsigned __int64)n;
        }
        goto LABEL_864;
      }
      while ( 1 )
      {
        v368 = v352++;
        if ( v368 <= v354 )
        {
          v369 = *(_DWORD *)(v346 + 9388);
          if ( *v347 == v369 )
          {
            v370 = *v347 + 1;
            if ( v369 )
              v371 = v369 + v369 / 2;
            else
              v371 = 8;
            if ( v371 > v370 )
              v370 = v371;
            sub_180054C90(v347, (unsigned int)v370);
          }
          *(_DWORD *)(*(_QWORD *)(v508 + 9392) + 4LL * (*v347)++) = v356 - (_DWORD)v322;
          v354 = v525;
        }
        v372 = sub_180095290(v356, 10);
        if ( !v372 )
          break;
        v356 = v372 + 1;
        v346 = v508;
      }
      v356 += sub_1800B9730(v356);
    }
    v355 = (const char *)v545;
LABEL_864:
    if ( v540 )
    {
      v355 = (const char *)v356;
      *v540 = v356;
      n = (const char *)v533;
    }
    v373 = v508;
    if ( !v352 )
    {
      v374 = *(_DWORD *)(v508 + 9388);
      if ( *v347 == v374 )
      {
        v375 = *v347 + 1;
        if ( v374 )
          v376 = v374 + v374 / 2;
        else
          v376 = 8;
        if ( v376 > v375 )
          v375 = v376;
        sub_180054C90(v347, (unsigned int)v375);
        v373 = v508;
      }
      *(_DWORD *)(*(_QWORD *)(v373 + 9392) + 4LL * (*v347)++) = 0;
      v352 = 1;
    }
    v377 = v373;
    if ( v355 > v322 && *(v355 - 1) == 10 && v352 <= v354 )
    {
      v378 = (_DWORD)v355 - (_DWORD)v322;
      v379 = *(_DWORD *)(v373 + 9388);
      if ( *v347 == v379 )
      {
        v380 = *v347 + 1;
        if ( v379 )
          v381 = v379 + v379 / 2;
        else
          v381 = 8;
        if ( v381 > v380 )
          v380 = v381;
        sub_180054C90(v347, (unsigned int)v380);
      }
      *(_DWORD *)(*(_QWORD *)(v377 + 9392) + 4LL * (*v347)++) = v378;
      ++v352;
    }
  }
  *(_DWORD *)(v508 + 9400) = (_DWORD)n - (_DWORD)v322;
  v382 = v352;
  if ( (int)v537 < v352 )
    v382 = v537;
  v534 = v382;
  v383 = *(float *)(v535 + 4432) * (float)v352;
  *(float *)&v533 = v383;
  if ( !(_BYTE)a7 || (v384 = v506) == 0 )
  {
    v395 = 0.0;
    LODWORD(v548) = 0;
    v396 = 0.0;
    goto LABEL_912;
  }
  v385 = **(int **)(v506 + 8);
  v386 = *(_DWORD **)(v508 + 9392);
  v387 = *v347;
  v388 = v386;
  v389 = v387;
  if ( (_DWORD)v387 )
  {
    do
    {
      v390 = v389 >> 1;
      if ( v388[v389 >> 1] >= (int)v385 )
      {
        v389 >>= 1;
      }
      else
      {
        v388 += v390 + 1;
        v389 += -1LL - v390;
      }
    }
    while ( v389 );
    v384 = v506;
  }
  v391 = v388 == v386;
  if ( v388 > v386 )
  {
    if ( v388 != &v386[v387] && *v388 == (_DWORD)v385 )
    {
      if ( *(float *)(v384 + 104) <= 0.0 )
        goto LABEL_906;
      if ( *(_BYTE *)(v384 + 117) != 1 )
        goto LABEL_906;
      v392 = v322[v385 - 1];
      if ( v392 == 10 || !v392 )
        goto LABEL_906;
    }
    v391 = --v388 == v386;
  }
  if ( !v391 )
  {
LABEL_906:
    v393 = v388 - v386;
    goto LABEL_907;
  }
  LODWORD(v393) = 0;
LABEL_907:
  if ( (_DWORD)v387 )
    v394 = v386[(int)v393];
  else
    v394 = 0;
  sub_180066D80(
    (unsigned int)&v540,
    *(_QWORD *)(v508 + 4416),
    v385,
    (_DWORD)v386,
    *(_DWORD *)(v508 + 9360),
    (__int64)&v322[v394],
    (__int64)&v322[v385],
    (__int64)n,
    0);
  v395 = *(float *)&v540;
  LODWORD(v548) = (_DWORD)v540;
  v396 = (float)(v393 + 1) * *(float *)(v535 + 4432);
  v382 = v534;
LABEL_912:
  *(float *)&v538 = v396;
  v397 = qword_18010C470;
  v398 = 288;
  if ( v505 )
    v398 = 304;
  *(_OWORD *)v520 = *(_OWORD *)(v398 + qword_18010C470 + 3136);
  *(float *)&v520[12] = _mm_shuffle_ps(*(__m128 *)v520, *(__m128 *)v520, 255).m128_f32[0]
                      * *(float *)(qword_18010C470 + 3148);
  sub_180036620(v520);
  v402 = v401;
  v525 = v401;
  v403 = a7;
  if ( !(_BYTE)a7 )
  {
    v404 = 0.0;
    if ( !v502 )
      goto LABEL_995;
  }
  v405 = v506;
  *(_DWORD *)(v506 + 100) = v352;
  v406 = v536;
  v407 = v536;
  if ( v403 && *(_BYTE *)(v506 + 112) )
  {
    if ( (v513 & 0x8000) != 0 )
    {
      *(_DWORD *)(v506 + 92) = 0;
    }
    else
    {
      v408 = v549 * 0.25;
      v409 = *(float *)(v506 + 92);
      if ( v409 <= v395 )
      {
        v410 = v395 - (float)(v549 - *(float *)(v400 + 3212));
        if ( v410 >= v409 )
        {
          *(float *)(v506 + 92) = (float)(int)(float)(v408 + v410);
          v403 = a7;
        }
      }
      else
      {
        *(float *)(v506 + 92) = (float)(int)fmaxf(0.0, v395 - v408);
        v403 = a7;
      }
    }
    v411 = a6 & 0x4000000;
    if ( v512 )
    {
      v412 = v396 - *(float *)(v399 + 4432);
      if ( v406 > v412 )
      {
        v407 = fmaxf(0.0, v412);
        *(_BYTE *)(v506 + 112) = 0;
        goto LABEL_931;
      }
      v413 = *(float *)(v400 + 3216) + *(float *)(v400 + 3216);
      if ( (float)(v396 - (float)(v204 - v413)) >= v406 )
        v407 = (float)(v396 - v204) + v413;
    }
    *(_BYTE *)(v506 + 112) = 0;
  }
  else
  {
    v411 = a6 & 0x4000000;
  }
LABEL_931:
  if ( *(_BYTE *)(v506 + 113) )
  {
    if ( v411 )
      v407 = (float)(v396 - *(float *)(v399 + 4432)) - (float)((float)(v204 * 0.5) - *(float *)(v400 + 3216));
    *(_BYTE *)(v506 + 113) = 0;
    v403 = 0;
    LOBYTE(a7) = 0;
  }
  if ( v407 != v406 )
  {
    if ( v407 >= 0.0 )
      v414 = fminf(fmaxf((float)((float)(*(float *)(v400 + 3216) + *(float *)(v400 + 3216)) + v383) - v204, 0.0), v407);
    else
      v414 = 0.0;
    v529 = v529 + (float)(*(float *)(v527 + 156) - v414);
    *(float *)(v527 + 156) = v414;
    v415 = 0;
    if ( (int)(float)((float)(v317 - v529) / *(float *)(v399 + 4432)) >= 0 )
      v415 = (int)(float)((float)(v317 - v529) / *(float *)(v399 + 4432));
    v517 = v415;
    v416 = (int)sub_1800B4300();
    v417 = v415;
    if ( v416 >= v415 )
      v417 = v416;
    v382 = v352;
    if ( v417 < v352 )
      v382 = v417;
    v534 = v382;
    v405 = v506;
    v403 = a7;
  }
  v404 = *(float *)(v405 + 92);
  if ( !v502 )
    goto LABEL_995;
  if ( v403 )
    v418 = 1.0;
  else
    v418 = 0.60000002;
  *(_OWORD *)v520 = *(_OWORD *)(v397 + 4240);
  *(float *)&v520[12] = _mm_shuffle_ps(*(__m128 *)v520, *(__m128 *)v520, 255).m128_f32[0]
                      * (float)(v418 * *(float *)(v397 + 3148));
  sub_180036620(v520);
  v536 = v419;
  if ( v512 )
  {
    v420 = 0.0;
    v421 = 0.0;
  }
  else
  {
    v420 = -1.0;
    v421 = 2.0;
  }
  v422 = v508;
  v423 = *(_QWORD *)(v508 + 4424);
  if ( *(int *)v423 <= 32 || (v424 = *(float *)(*(_QWORD *)(v423 + 8) + 128LL), v424 < 0.0) )
  {
    if ( *(float *)(v423 + 20) >= 128.0 || (*(_DWORD *)(v423 + 76) & 0x10000000) != 0 )
    {
      LODWORD(v537) = 0;
      v426 = sub_180062410(v423, 32, &v537);
      if ( v426 )
        v424 = *(float *)(v426 + 4);
      else
        v424 = *(float *)&v537;
    }
    else
    {
      v425 = sub_180062410(*(_QWORD *)(v508 + 4424), 32, 0);
      if ( v425 )
        v424 = *(float *)(v425 + 4);
      else
        v424 = *(float *)(v423 + 16);
    }
    v422 = v508;
  }
  v427 = (float)(int)(float)(v424 * 0.5);
  v428 = *(_QWORD *)(v506 + 8);
  v429 = *(_DWORD *)(v428 + 8);
  v430 = *(_DWORD *)(v428 + 4);
  v431 = v429;
  if ( v430 < v429 )
    v431 = v430;
  v562 = v431;
  v432 = &v322[v431];
  v540 = (__int64 *)v432;
  if ( v430 >= v429 )
    v429 = v430;
  v433 = &v322[v429];
  v561 = v433;
  v434 = v517;
  v435 = v517;
  if ( v517 < v382 )
  {
    v436 = v526;
    v437 = v539;
    do
    {
      v438 = *v347;
      v439 = 4LL * v435;
      if ( *v347 )
        v440 = *(_DWORD *)(v439 + *(_QWORD *)(v422 + 9392));
      else
        v440 = 0;
      v441 = v422;
      v442 = v440;
      v443 = &v322[v440];
      v560 = v443;
      LODWORD(v545) = v435 + 1;
      if ( v435 + 1 >= v438 )
        v444 = *(_DWORD *)(v508 + 9400);
      else
        v444 = *(_DWORD *)(*(_QWORD *)(v441 + 9392) + v439 + 4) - 1;
      v445 = &v322[v444];
      if ( v445 >= n || *v445 == 10 )
      {
        v446 = 0;
      }
      else
      {
        v446 = 1;
        ++v445;
      }
      if ( v432 > v443 )
        v442 = v562;
      v447 = &v322[v442];
      v448 = v445;
      if ( v433 < v445 )
        v448 = v433;
      if ( v447 >= v448 )
      {
        v450 = 0.0;
      }
      else
      {
        sub_18003DF30((unsigned int)&v578, (_DWORD)v447, (_DWORD)v448, 0, -1082130432);
        v450 = *v449 + 0.0;
        LODWORD(v443) = (_DWORD)v560;
        v433 = v561;
      }
      if ( v540 <= (__int64 *)v445 && v433 > v445 && !v446 )
        v450 = v450 + v427;
      if ( v450 != 0.0 )
      {
        sub_18003DF30((unsigned int)&v563, (_DWORD)v443, (_DWORD)v447, 0, -1082130432);
        v452 = (float)(v528 - v404) + *v451;
        v453 = *(float *)(v535 + 4432);
        v454 = (float)((float)v435 * v453) + (float)(v529 - 0.0);
        *(_DWORD *)v520 = fmaxf(v452, v437);
        *(_DWORD *)&v520[4] = fmaxf(v454 - v420, v436);
        *(_DWORD *)&v520[8] = fminf(v452 + v450, v318);
        *(_DWORD *)&v520[12] = fminf((float)(v421 + v454) + v453, v319);
        sub_18005C870(*(_QWORD *)(v527 + 712), (unsigned int)v520, (unsigned int)&v520[8], LODWORD(v536), 0, 0);
      }
      v435 = v545;
      v382 = v534;
      v433 = v561;
      v432 = (const char *)v540;
      v422 = v508;
    }
    while ( (int)v545 < v534 );
    v395 = *(float *)&v548;
    v396 = *(float *)&v538;
    v383 = *(float *)&v533;
    v110 = v539;
    v402 = v525;
LABEL_995:
    v434 = v517;
    goto LABEL_996;
  }
  v110 = v539;
  v402 = v525;
LABEL_996:
  v455 = (__m128)LODWORD(v543);
  if ( *(_DWORD *)(v508 + 5332) != v507 && (v513 & 0x20000) != 0 )
  {
    sub_18003DF30((unsigned int)&v563, (_DWORD)v322, 0, 0, -1082130432);
    v528 = fminf(v528, (float)(v455.m128_f32[0] - *v456) - *(float *)(v508 + 3212));
  }
  if ( (v512 || n - v322 < 0x200000) && (v402 & 0xFF000000) != 0 && v434 < v382 )
  {
    if ( v382 >= *v347 )
      v457 = *(_DWORD *)(v508 + 9400);
    else
      v457 = *(_DWORD *)(*(_QWORD *)(v508 + 9392) + 4LL * v382) - 1;
    v458 = (__int64)&v322[v457];
    if ( *v347 )
      v459 = *(_DWORD *)(*(_QWORD *)(v508 + 9392) + 4LL * v434);
    else
      v459 = 0;
    v460 = v535;
    v461 = *(float *)(v535 + 4432);
    *(float *)&v540 = (float)(v528 - v404) + 0.0;
    *((float *)&v540 + 1) = (float)(v529 - 0.0) + (float)((float)v434 * v461);
    v462 = v527;
    sub_180067670(
      *(_QWORD *)(v508 + 4416),
      *(_QWORD *)(v527 + 712),
      v508,
      (unsigned int)&v540,
      v402,
      (__int64)&v530,
      (__int64)&v322[v459],
      v458,
      LODWORD(v550),
      3);
  }
  else
  {
    v460 = v535;
    v462 = v527;
  }
  if ( (_BYTE)a7 )
  {
    v463 = *(float *)(v508 + 32) + *(float *)(v506 + 108);
    *(float *)(v506 + 108) = v463;
    v464 = !*(_BYTE *)(v508 + 91) || v463 <= 0.0 || sub_1800B4860() <= 0.80000001;
    v465 = (float)(int)(float)((float)(v395 + v528) - v404);
    v466 = (float)(int)(float)((float)(v529 + v396) - 0.0);
    *(float *)v520 = v465;
    v467 = (float)(v466 - *(float *)(v460 + 4432)) + 0.5;
    *(float *)&v520[4] = v467;
    *(float *)&v520[8] = v465 + 1.0;
    *(float *)&v520[12] = v466 - 1.5;
    if ( v464 && (float)(v466 - 1.5) > v526 && v319 > v467 && (float)(v465 + 1.0) > v110 && v318 > v465 )
    {
      v530 = *(__m128 *)(qword_18010C470 + 3952);
      v530.m128_f32[3] = _mm_shuffle_ps(v530, v530, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      *(float *)&a7 = (float)(int)(float)((float)(v395 + v528) - v404);
      *((float *)&a7 + 1) = v466 - 1.5;
      sub_180036620(&v530);
      sub_18005C320(*(_QWORD *)(v462 + 712), (unsigned int)v520, (unsigned int)&a7, v468, 1065353216);
    }
    v469 = v507;
    if ( !v511 && *(_DWORD *)(v508 + 5332) == v507 )
    {
      *(_WORD *)(v508 + 9848) = 257;
      v470 = *(float *)(v460 + 4432);
      *(float *)(v508 + 9852) = v465 - 1.0;
      *(float *)(v508 + 9856) = v466 - v470;
      *(float *)(v508 + 9860) = v470;
      *(_DWORD *)(v508 + 9864) = **(_DWORD **)(v551 + 32);
    }
  }
  else
  {
    v469 = v507;
  }
  v471 = v532;
  if ( v532 && !v505 )
  {
    v472 = qword_18010C470;
    *(_DWORD *)(*(_QWORD *)(qword_18010C470 + 4416) + 16LL) = *(_DWORD *)(qword_18010C470 + 9536);
    *(_DWORD *)(*(_QWORD *)(v472 + 4424) + 64LL) = *(_DWORD *)(v472 + 9496);
    *(_DWORD *)(*(_QWORD *)(v472 + 4424) + 16LL) = *(_DWORD *)(v472 + 9448);
    v473 = *(_QWORD *)(v472 + 4424);
    v474 = *(_DWORD *)(v472 + 9464);
    *(_DWORD *)(v472 + 9464) = *(_DWORD *)(v473 + 32);
    *(_DWORD *)(v473 + 32) = v474;
    v475 = *(_DWORD *)(v472 + 9468);
    *(_DWORD *)(v472 + 9468) = *(_DWORD *)(v473 + 36);
    *(_DWORD *)(v473 + 36) = v475;
    v476 = *(_QWORD *)(v472 + 9472);
    *(_QWORD *)(v472 + 9472) = *(_QWORD *)(v473 + 40);
    *(_QWORD *)(v473 + 40) = v476;
    v477 = *(_QWORD *)(v472 + 4424);
    LODWORD(v476) = *(_DWORD *)(v472 + 9432);
    *(_DWORD *)(v472 + 9432) = *(_DWORD *)v477;
    *(_DWORD *)v477 = v476;
    LODWORD(v476) = *(_DWORD *)(v472 + 9436);
    *(_DWORD *)(v472 + 9436) = *(_DWORD *)(v477 + 4);
    *(_DWORD *)(v477 + 4) = v476;
    v478 = *(_QWORD *)(v472 + 9440);
    *(_QWORD *)(v472 + 9440) = *(_QWORD *)(v477 + 8);
    *(_QWORD *)(v477 + 8) = v478;
  }
  if ( v512 )
  {
    v479 = v549;
    *(float *)&a7 = v549;
    v480 = v383 + *(float *)(v508 + 3216);
    *((float *)&a7 + 1) = v480;
    v481 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v482 = *(_QWORD *)(v481 + 5216);
    if ( !*(_BYTE *)(v482 + 209) )
    {
      *(_QWORD *)v520 = *(_QWORD *)(v482 + 280);
      *(float *)&v520[8] = *(float *)v520 + v479;
      *(float *)&v520[12] = v480 + *(float *)&v520[4];
      sub_18004AAD0(&a7);
      sub_18004A070(v520, 0, 0, 0);
    }
    *(_DWORD *)(v508 + 7692) |= 0x100001u;
    sub_18003E7F0();
    v483 = *(_DWORD *)(v508 + 7752) & 0x80 | DWORD2(v573);
    sub_18004B190();
    if ( !*(_DWORD *)(v508 + 7744) )
      goto LABEL_1038;
    v484 = sub_1800360F0("#SCROLLY", 0, *(unsigned int *)(*v547 + 4LL * *v546 - 4));
    if ( *(_DWORD *)(*(_QWORD *)v527 + 5304LL) == v484 )
      sub_180053310(v484, 11, "#SCROLLY");
    if ( *(_DWORD *)(v508 + 7744) != v484 )
    {
LABEL_1038:
      *(_DWORD *)(v508 + 7744) = v469;
      *(_DWORD *)(v508 + 7748) = DWORD1(v573);
      *(_DWORD *)(v508 + 7752) = v483;
    }
    v471 = v532;
  }
  if ( v506 )
    *(_QWORD *)(v506 + 32) = 0;
  if ( *(_BYTE *)(v508 + 10080) && (!v471 || v505) )
  {
    v485 = qword_18010C470;
    v486 = *(_QWORD *)(qword_18010C470 + 5216);
    *(_QWORD *)(qword_18010C470 + 10128) = 0;
    *(_QWORD *)(v485 + 10120) = 0;
    if ( !n )
    {
      for ( n = v322; n != (const char *)-1LL; ++n )
      {
        if ( !*n || *n == 35 && n[1] == 35 )
          break;
      }
    }
    v487 = (float)(*(float *)(v485 + 10136) + *(float *)(v485 + 3216)) + 1.0;
    v488 = v529;
    *(float *)(v485 + 10136) = v529;
    if ( v488 > v487 )
    {
      sub_180051790("\r\n");
      *(_BYTE *)(v485 + 10140) = 1;
    }
    sub_180051A10((__int64)&v528, "{", "");
    v489 = *(_DWORD *)(v486 + 416);
    if ( *(_DWORD *)(v485 + 10144) <= v489 )
      v489 = *(_DWORD *)(v485 + 10144);
    else
      *(_DWORD *)(v485 + 10144) = v489;
    v490 = 4 * (*(_DWORD *)(v486 + 416) - v489);
    while ( 1 )
    {
      v491 = sub_1800B8A30(v322, 10, n - v322);
      v492 = n;
      if ( v491 )
        v492 = (const char *)v491;
      if ( v322 == v492 && v492 == n )
        break;
      v493 = 1;
      if ( *(_BYTE *)(v485 + 10140) )
        v493 = v490;
      sub_180051790("%*s%.*s", v493, byte_1800D411C, (_DWORD)v492 - (_DWORD)v322, v322);
      *(_BYTE *)(v485 + 10140) = 0;
      if ( *v492 == 10 )
      {
        sub_180051790("\r\n");
        *(_BYTE *)(v485 + 10140) = 1;
      }
      if ( v492 == n )
        break;
      v322 = v492 + 1;
    }
    sub_180051A10((__int64)&v528, "}", "");
    v469 = v507;
  }
  if ( v552 > 0.0 )
  {
    v455.m128_f32[0] = v455.m128_f32[0] + *(float *)(v508 + 3236);
    v494 = (__m128)LODWORD(v542);
    v494.m128_f32[0] = v542 + *(float *)(v508 + 3216);
    sub_180037440(_mm_unpacklo_ps(v455, v494).m128_i64[0], a1, nullptr, 1);
  }
  v495 = a8;
  if ( (_BYTE)a8 )
  {
    v496 = qword_18010C470;
    if ( (*(_DWORD *)(qword_18010C470 + 7748) & 0x10000) == 0 )
    {
      v497 = *(_DWORD *)(qword_18010C470 + 5332);
      if ( v497 == v469 || !v497 )
      {
        *(_WORD *)(qword_18010C470 + 5348) = 257;
        if ( *(_DWORD *)(v496 + 5384) == v469 )
          *(_BYTE *)(v496 + 5392) = 1;
      }
      *(_DWORD *)(v496 + 7752) |= 4u;
    }
  }
  result = v495;
  if ( (v513 & 0x40) != 0 )
    return v501;
  return result;
}
