// sub_180024610 size=2155
void sub_180024610()
{
  __int64 v0; // rsi
  __int64 v1; // rdi
  char *v2; // rbx
  float v3; // xmm6_4
  float v4; // xmm14_4
  float v5; // xmm6_4
  float v6; // xmm14_4
  int v7; // ecx
  int v8; // ecx
  __int128 *v9; // rcx
  unsigned int v10; // r14d
  int v11; // r13d
  unsigned int v12; // r15d
  unsigned int v13; // r12d
  int v14; // eax
  char v15; // si
  float v16; // xmm8_4
  float v17; // xmm10_4
  float v18; // xmm1_4
  char v19; // cl
  float v20; // xmm7_4
  float v21; // xmm11_4
  float v22; // xmm11_4
  float v23; // xmm6_4
  float v24; // xmm11_4
  _QWORD *v25; // rsi
  int v26; // r8d
  float v27; // xmm6_4
  float v28; // xmm7_4
  __int64 v29; // rcx
  __int64 v30; // rcx
  int v31; // r8d
  float v32; // xmm8_4
  char v33; // al
  float v34; // xmm10_4
  __int64 v35; // rcx
  __int64 v36; // rcx
  int v37; // eax
  int v38; // r8d
  int v39; // [rsp+28h] [rbp-D8h]
  __int128 v40; // [rsp+50h] [rbp-B0h] BYREF
  float v41[2]; // [rsp+60h] [rbp-A0h] BYREF
  _DWORD v42[2]; // [rsp+68h] [rbp-98h] BYREF
  _DWORD v43[2]; // [rsp+70h] [rbp-90h] BYREF
  float v44[2]; // [rsp+78h] [rbp-88h] BYREF
  float v45[2]; // [rsp+80h] [rbp-80h] BYREF
  _DWORD v46[2]; // [rsp+88h] [rbp-78h] BYREF
  _DWORD v47[2]; // [rsp+90h] [rbp-70h] BYREF
  float v48[2]; // [rsp+98h] [rbp-68h] BYREF
  float v49[2]; // [rsp+A0h] [rbp-60h] BYREF
  _DWORD v50[2]; // [rsp+A8h] [rbp-58h] BYREF
  float v51[2]; // [rsp+B0h] [rbp-50h] BYREF
  _DWORD v52[2]; // [rsp+B8h] [rbp-48h] BYREF
  _DWORD v53[4]; // [rsp+C0h] [rbp-40h] BYREF
  _DWORD v54[4]; // [rsp+D0h] [rbp-30h] BYREF
  _DWORD v55[4]; // [rsp+E0h] [rbp-20h] BYREF
  __int128 v56; // [rsp+F0h] [rbp-10h] BYREF
  __int128 v57; // [rsp+100h] [rbp+0h] BYREF
  __int128 v58; // [rsp+110h] [rbp+10h] BYREF
  __int128 v59; // [rsp+120h] [rbp+20h] BYREF
  __int128 v60; // [rsp+130h] [rbp+30h] BYREF
  __int128 v61; // [rsp+140h] [rbp+40h] BYREF
  __int128 v62; // [rsp+150h] [rbp+50h] BYREF
  float v63; // [rsp+160h] [rbp+60h] BYREF
  char *v64; // [rsp+168h] [rbp+68h]
  __int64 v65; // [rsp+170h] [rbp+70h] BYREF
  int v66; // [rsp+178h] [rbp+78h]
  char v67[4]; // [rsp+180h] [rbp+80h] BYREF
  float v68; // [rsp+184h] [rbp+84h]
  float v69; // [rsp+188h] [rbp+88h]
  __int64 v70; // [rsp+190h] [rbp+90h] BYREF
  int v71; // [rsp+198h] [rbp+98h]
  _BYTE v72[32]; // [rsp+1A0h] [rbp+A0h] BYREF
  float v73; // [rsp+2B0h] [rbp+1B0h]
  __int64 v74; // [rsp+2B8h] [rbp+1B8h]
  __int64 v75; // [rsp+2C0h] [rbp+1C0h] BYREF
  __int64 v76; // [rsp+2C8h] [rbp+1C8h] BYREF

  if ( byte_1800FAB38 )
  {
    if ( xmmword_18010C568 != *(&xmmword_18010C568 + 1) )
    {
      v74 = sub_1800047E0();
      v0 = v74;
      if ( v74 )
      {
        v1 = sub_18003A960(**(_QWORD **)(qword_18010C470 + 8104), 0, "##Background");
        v2 = (char *)xmmword_18010C568;
        v3 = *(float *)(qword_18010C470 + 20);
        v4 = *(float *)(qword_18010C470 + 16) * 0.5;
        v64 = (char *)*(&xmmword_18010C568 + 1);
        *(float *)&v43[1] = v3;
        *(float *)v43 = v4;
        if ( xmmword_18010C568 != *(&xmmword_18010C568 + 1) )
        {
          v5 = v3 + 1.0;
          v6 = v4 + 1.0;
          v73 = v5;
          do
          {
            v7 = *((_DWORD *)v2 + 16);
            if ( v7 )
            {
              v8 = v7 - 1;
              if ( v8 )
              {
                if ( v8 == 1 )
                {
                  v9 = &v57;
                  v57 = xmmword_1800FAB68;
                }
                else
                {
                  v9 = &v56;
                  v56 = xmmword_1800FAB78;
                }
              }
              else
              {
                v9 = &v58;
                v58 = xmmword_1800FAB58;
              }
            }
            else
            {
              v9 = &v59;
              v59 = xmmword_1800FAB48;
            }
            v10 = sub_180036620(v9);
            v60 = xmmword_1800FAB9C;
            v11 = sub_180036620(&v60);
            if ( byte_1800FAB98 )
            {
              v61 = xmmword_1800FAB88;
              v12 = sub_180036620(&v61);
            }
            else
            {
              v12 = v10;
            }
            if ( byte_1800FABBC )
            {
              v62 = xmmword_1800FABAC;
              v13 = sub_180036620(&v62);
            }
            else
            {
              v13 = v10;
            }
            v14 = *((_DWORD *)v2 + 12);
            v65 = *((_QWORD *)v2 + 5);
            v75 = 0;
            v66 = v14;
            sub_1800230D0(v53, v0, &v65);
            if ( *(float *)&v53[2] > 0.0 )
            {
              v15 = 1;
              v17 = *(float *)v53;
              LODWORD(v75) = v53[0];
              v16 = *(float *)(qword_18010C470 + 20) - *(float *)&v53[1];
              *((float *)&v75 + 1) = v16;
            }
            else
            {
              v15 = 0;
              v16 = 0.0;
              v17 = 0.0;
            }
            v18 = *((float *)v2 + 11) + *((float *)v2 + 13);
            v54[0] = *((_DWORD *)v2 + 10);
            v54[2] = *((_DWORD *)v2 + 12);
            *(float *)&v54[1] = v18;
            sub_1800230D0(v67, v74, v54);
            if ( v69 > 0.0 )
            {
              v19 = 1;
              v20 = *(float *)(qword_18010C470 + 20) - v68;
            }
            else
            {
              v19 = 0;
              v20 = 0.0;
            }
            if ( v15 && v19 )
            {
              v21 = fmaxf(2.0, fmaxf(2.0, v16 - v20) * 0.44999999);
              if ( byte_1800FAB41 )
              {
                *(float *)v42 = v6;
                *(float *)&v42[1] = v5;
                v41[0] = v17 + 1.0;
                v41[1] = v16 + 1.0;
                sub_18005C320(v1, (unsigned int)v42, (unsigned int)v41, -1610612736, 1069547520);
                sub_18005C320(v1, (unsigned int)v43, (unsigned int)&v75, v12, 1067030938);
              }
              if ( byte_1800FAB3E )
              {
                v22 = v21 * 0.5;
                v23 = v17 - v22;
                v24 = v22 + v17;
                v45[0] = v23 + 1.0;
                v44[0] = v24 + 1.0;
                v44[1] = v16 + 1.0;
                v45[1] = v20 + 1.0;
                sub_18005C460(v1, (unsigned int)v45, (unsigned int)v44, -1610612736, 0);
                *(float *)v46 = v24;
                *(float *)&v46[1] = v16;
                *(float *)v47 = v23;
                *(float *)&v47[1] = v20;
                sub_18005C460(v1, (unsigned int)v47, (unsigned int)v46, v13, 0);
              }
              if ( byte_1800FAB3F && *((_QWORD *)v2 + 3) )
              {
                v25 = v2 + 8;
                if ( *((_QWORD *)v2 + 4) > 0xFu )
                  v25 = (_QWORD *)*v25;
                sub_18003DF30((unsigned int)v48, (_DWORD)v25, 0, 0, -1082130432);
                v27 = v17 - (float)(v48[0] * 0.5);
                v28 = (float)(v20 - v48[1]) - 2.0;
                v49[0] = v27 + 1.0;
                v49[1] = v28 + 1.0;
                if ( v25 && *(_BYTE *)v25 )
                {
                  v29 = *(_QWORD *)(*(_QWORD *)(v1 + 56) + 24LL);
                  v40 = *(_OWORD *)(v1 + 96);
                  sub_180067670(v29, v1, v26, (unsigned int)v49, -1610612736, (__int64)&v40, (__int64)v25, 0, 0, 0);
                }
                *(float *)v50 = v27;
                *(float *)&v50[1] = v28;
                if ( (v11 & 0xFF000000) != 0 && v25 && *(_BYTE *)v25 )
                {
                  v30 = *(_QWORD *)(*(_QWORD *)(v1 + 56) + 24LL);
                  v40 = *(_OWORD *)(v1 + 96);
                  sub_180067670(v30, v1, v26, (unsigned int)v50, v11, (__int64)&v40, (__int64)v25, 0, 0, 0);
                }
              }
              if ( byte_1800FAB40 )
              {
                sub_1800229B0(v72, 32, "%.0fm", *((float *)v2 + 15));
                sub_18003DF30((unsigned int)&v63, (unsigned int)v72, 0, 0, -1082130432);
                v32 = v16 + 2.0;
                v33 = v72[0];
                v34 = v17 - (float)(v63 * 0.5);
                v51[1] = v32 + 1.0;
                v51[0] = v34 + 1.0;
                if ( v72[0] )
                {
                  v35 = *(_QWORD *)(*(_QWORD *)(v1 + 56) + 24LL);
                  v40 = *(_OWORD *)(v1 + 96);
                  sub_180067670(v35, v1, v31, (unsigned int)v51, -1610612736, (__int64)&v40, (__int64)v72, 0, 0, 0);
                  v33 = v72[0];
                }
                *(float *)v52 = v34;
                *(float *)&v52[1] = v32;
                if ( (v11 & 0xFF000000) != 0 && v33 )
                {
                  v36 = *(_QWORD *)(*(_QWORD *)(v1 + 56) + 24LL);
                  v40 = *(_OWORD *)(v1 + 96);
                  sub_180067670(v36, v1, v31, (unsigned int)v52, v11, (__int64)&v40, (__int64)v72, 0, 0, 0);
                }
              }
              if ( v2[80] )
              {
                v0 = v74;
                if ( !byte_1800FAB3E )
                {
                  v37 = *((_DWORD *)v2 + 19);
                  v70 = *(_QWORD *)(v2 + 68);
                  v76 = 0;
                  v71 = v37;
                  sub_1800230D0(v55, v74, &v70);
                  if ( *(float *)&v55[2] > 0.0 )
                  {
                    LODWORD(v76) = v55[0];
                    *((float *)&v76 + 1) = *(float *)(qword_18010C470 + 20) - *(float *)&v55[1];
                    if ( (v10 & 0xFF000000) != 0 )
                    {
                      sub_18005BB80(v1, (unsigned int)&v76, v38, 0, 48, v39);
                      --*(_DWORD *)(v1 + 80);
                      sub_180034630(v1, v10);
                    }
                  }
                }
                v5 = v73;
                goto LABEL_56;
              }
              v5 = v73;
            }
            v0 = v74;
LABEL_56:
            v2 += 88;
          }
          while ( v2 != v64 );
        }
      }
    }
  }
}
