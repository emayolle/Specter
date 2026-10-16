// sub_180076EF0 size=2606
char sub_180076EF0(__int64 a1, int a2, signed int *a3, int *a4, int *a5, const char *a6, ...)
{
  __int64 v6; // rdi
  const char *v10; // rbx
  char v11; // r12
  __m128 v12; // xmm9
  float v13; // xmm2_4
  float v14; // xmm0_4
  __int64 v15; // rax
  __int64 v16; // rdx
  int v17; // xmm11_4
  int v18; // xmm12_4
  int v19; // r9d
  __int64 v20; // r14
  __int64 v21; // r15
  char *v22; // rdx
  unsigned __int8 v23; // al
  unsigned int v24; // ebx
  unsigned __int64 v25; // rcx
  unsigned int v26; // ebx
  float v27; // xmm6_4
  float v28; // xmm7_4
  char v29; // al
  char v30; // r15
  __int64 v31; // rax
  int v32; // r9d
  int v33; // eax
  __int64 v34; // rax
  float v35; // xmm3_4
  float v36; // xmm2_4
  int *v37; // rdx
  int v38; // edx
  signed int v39; // ecx
  unsigned int v40; // ecx
  __int64 v41; // r10
  __int64 v42; // r14
  __int64 v43; // r15
  char *v44; // r8
  unsigned __int8 v45; // al
  int v46; // r9d
  unsigned int v47; // ebx
  unsigned __int64 v48; // rcx
  unsigned int v49; // ebx
  float v50; // xmm6_4
  float v51; // xmm7_4
  char v52; // al
  char v53; // r15
  __int64 v54; // rax
  int v55; // r9d
  int v56; // eax
  __int64 v57; // rax
  float v58; // xmm3_4
  float v59; // xmm2_4
  int *v60; // rax
  int v61; // ecx
  signed int v62; // edx
  unsigned int v63; // eax
  __int64 v64; // rdx
  int v65; // ecx
  const char *v66; // rdx
  _BYTE *v67; // rdx
  _BYTE *v68; // r9
  __int64 v69; // rax
  __int64 v70; // rcx
  int v71; // eax
  __int64 v72; // rax
  int v73; // ecx
  int v74; // edx
  __int64 v75; // [rsp+40h] [rbp-C0h] BYREF
  __m128 v76; // [rsp+48h] [rbp-B8h] BYREF
  float v77; // [rsp+58h] [rbp-A8h] BYREF
  float v78; // [rsp+5Ch] [rbp-A4h]
  float v79; // [rsp+60h] [rbp-A0h]
  float v80; // [rsp+64h] [rbp-9Ch]
  _BYTE v81[64]; // [rsp+70h] [rbp-90h] BYREF
  __int64 v82; // [rsp+160h] [rbp+60h] BYREF
  int v83; // [rsp+168h] [rbp+68h] BYREF
  int *v84; // [rsp+178h] [rbp+78h]
  __int64 v85; // [rsp+190h] [rbp+90h] BYREF
  va_list va; // [rsp+190h] [rbp+90h]
  va_list va1; // [rsp+198h] [rbp+98h] BYREF

  va_start(va1, a6);
  va_start(va, a6);
  v85 = va_arg(va1, _QWORD);
  v84 = a4;
  v83 = a2;
  v82 = a1;
  v6 = qword_18010C470;
  *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
  if ( *(_BYTE *)(*(_QWORD *)(v6 + 5216) + 209LL) )
    return 0;
  v10 = a6;
  if ( !a6 )
    v10 = "%d";
  sub_180073690((unsigned int)v81, 64, 4, (_DWORD)a3, (__int64)v10);
  *(_DWORD *)(v6 + 7692) |= 0x10000u;
  v11 = 0;
  if ( a4 )
  {
    v12 = (__m128)*(unsigned int *)(qword_18010C470 + 3216);
    v12.m128_f32[0] = (float)(v12.m128_f32[0] + v12.m128_f32[0]) + *(float *)(qword_18010C470 + 4432);
    sub_18004AFD0();
    sub_1800466C0("##tp_scene_id");
    v13 = v12.m128_f32[0] + *(float *)(v6 + 3236);
    v14 = sub_18004AE40();
    v15 = qword_18010C470;
    v82 = 0;
    *(_DWORD *)(qword_18010C470 + 7688) |= 1u;
    *(float *)(v15 + 7712) = fmaxf(1.0, v14 - (float)(v13 + v13));
    if ( (unsigned __int8)sub_180079E10(
                            (unsigned int)&unk_1800D411C,
                            0,
                            (unsigned int)v81,
                            64,
                            (__int64)&v82,
                            268439552,
                            0,
                            0) )
      v11 = sub_180073770((unsigned int)v81, 4, (_DWORD)a3, (_DWORD)v10, 0);
    v17 = *(_DWORD *)(v6 + 3212);
    LOBYTE(v16) = 1;
    v18 = *(_DWORD *)(v6 + 3216);
    *(_DWORD *)(v6 + 3212) = v18;
    sub_180045260(8, v16);
    sub_18004AC40();
    v20 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    v21 = *(_QWORD *)(v20 + 5216);
    if ( *(_BYTE *)(v21 + 209) )
      goto LABEL_38;
    v22 = "";
    v23 = 45;
    v24 = ~*(_DWORD *)(*(_QWORD *)(v21 + 272) + 4LL * *(int *)(v21 + 264) - 4);
    do
    {
      if ( v23 == 35 && *v22 == 35 && v22[1] == 35 )
        v24 = ~*(_DWORD *)(*(_QWORD *)(v21 + 272) + 4LL * *(int *)(v21 + 264) - 4);
      v25 = v23 ^ (unsigned __int64)(unsigned __int8)v24;
      v23 = *v22++;
      v24 = dword_1800D56B0[v25] ^ (v24 >> 8);
    }
    while ( v23 );
    v26 = ~v24;
    if ( *(_DWORD *)(*(_QWORD *)v21 + 5304LL) == v26 )
      sub_180053310(v26, 11, "-");
    LOBYTE(v19) = 1;
    sub_18003DF30((unsigned int)&v75, (unsigned int)"-", 0, v19, -1082130432);
    v27 = *(float *)(v21 + 280);
    v28 = *(float *)(v21 + 284);
    sub_18004AEC0(&v82, _mm_unpacklo_ps(v12, v12).m128_u64[0]);
    v77 = v27;
    v78 = v28;
    v80 = *((float *)&v82 + 1) + v28;
    v79 = v27 + *(float *)&v82;
    sub_18004AAD0(&v82);
    sub_18004A070(&v77, v26, 0, 0);
    if ( !v29 )
      goto LABEL_38;
    v30 = sub_18006F740((unsigned int)&v77, v26, (unsigned int)&v83, (unsigned int)va, 0);
    if ( (_BYTE)v85 && (_BYTE)v83 )
      v31 = 23;
    else
      v31 = ((_BYTE)v83 != 0) + 21LL;
    v76 = *(__m128 *)(qword_18010C470 + 16 * (v31 + 18) + 3136);
    v76.m128_f32[3] = _mm_shuffle_ps(v76, v76, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
    sub_180038770(&v77, v26, 0);
    sub_180036620(&v76);
    LOBYTE(v32) = 1;
    sub_180038470(LODWORD(v77), LODWORD(v79), v33, v32, *(_DWORD *)(v20 + 3220));
    if ( *(_BYTE *)(v20 + 10080) )
    {
      v34 = qword_18010C470;
      *(_QWORD *)(qword_18010C470 + 10120) = "[";
      *(_QWORD *)(v34 + 10128) = "]";
    }
    v35 = *(float *)(v20 + 3212);
    v36 = *(float *)(v20 + 3216);
    *(float *)&v82 = v79 - v35;
    *((float *)&v82 + 1) = v80 - v36;
    v76.m128_f32[0] = v77 + v35;
    v76.m128_f32[1] = v78 + v36;
    sub_180037980(v76.m128_f32, (float *)&v82, "-", 0, &v75, (float *)(v20 + 3356), &v77);
    if ( !v30 )
    {
LABEL_38:
      sub_18004AC40();
      v42 = qword_18010C470;
      *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
      v43 = *(_QWORD *)(v42 + 5216);
      if ( *(_BYTE *)(v43 + 209) )
        goto LABEL_65;
      v44 = "";
      v45 = 43;
      v46 = ~*(_DWORD *)(*(_QWORD *)(v43 + 272) + 4LL * *(int *)(v43 + 264) - 4);
      v47 = v46;
      do
      {
        if ( v45 == 35 && *v44 == 35 && v44[1] == 35 )
          v47 = ~*(_DWORD *)(*(_QWORD *)(v43 + 272) + 4LL * *(int *)(v43 + 264) - 4);
        v48 = v45 ^ (unsigned __int64)(unsigned __int8)v47;
        v45 = *v44++;
        v47 = *(_DWORD *)(v41 + 4 * v48) ^ (v47 >> 8);
      }
      while ( v45 );
      v49 = ~v47;
      if ( *(_DWORD *)(*(_QWORD *)v43 + 5304LL) == v49 )
        sub_180053310(v49, 11, "+");
      LOBYTE(v46) = 1;
      sub_18003DF30((unsigned int)&v75, (unsigned int)"+", 0, v46, -1082130432);
      v50 = *(float *)(v43 + 280);
      v51 = *(float *)(v43 + 284);
      sub_18004AEC0(&v82, _mm_unpacklo_ps(v12, v12).m128_u64[0]);
      v77 = v50;
      v78 = v51;
      v80 = *((float *)&v82 + 1) + v51;
      v79 = v50 + *(float *)&v82;
      sub_18004AAD0(&v82);
      sub_18004A070(&v77, v49, 0, 0);
      if ( !v52 )
        goto LABEL_65;
      v53 = sub_18006F740((unsigned int)&v77, v49, (unsigned int)&v83, (unsigned int)va, 0);
      if ( (_BYTE)v85 && (_BYTE)v83 )
        v54 = 23;
      else
        v54 = ((_BYTE)v83 != 0) + 21LL;
      v76 = *(__m128 *)(qword_18010C470 + 16 * (v54 + 18) + 3136);
      v76.m128_f32[3] = _mm_shuffle_ps(v76, v76, 255).m128_f32[0] * *(float *)(qword_18010C470 + 3148);
      sub_180038770(&v77, v49, 0);
      sub_180036620(&v76);
      LOBYTE(v55) = 1;
      sub_180038470(LODWORD(v77), LODWORD(v79), v56, v55, *(_DWORD *)(v42 + 3220));
      if ( *(_BYTE *)(v42 + 10080) )
      {
        v57 = qword_18010C470;
        *(_QWORD *)(qword_18010C470 + 10120) = "[";
        *(_QWORD *)(v57 + 10128) = "]";
      }
      v58 = *(float *)(v42 + 3212);
      v59 = *(float *)(v42 + 3216);
      *(float *)&v82 = v79 - v58;
      *((float *)&v82 + 1) = v80 - v59;
      v76.m128_f32[0] = v77 + v58;
      v76.m128_f32[1] = v78 + v59;
      sub_180037980(v76.m128_f32, (float *)&v82, "+", 0, &v75, (float *)(v42 + 3356), &v77);
      if ( !v53 )
        goto LABEL_65;
      if ( !*(_BYTE *)(v6 + 252) || (v60 = a5) == nullptr )
        v60 = v84;
      v61 = *v60;
      v62 = *a3;
      if ( *v60 >= 0 )
      {
        if ( v61 > 0 )
        {
          v63 = 0x7FFFFFFF;
          if ( v62 > 0x7FFFFFFF - v61 )
            goto LABEL_64;
        }
      }
      else if ( v62 < (int)(0x80000000 - v61) )
      {
        v63 = 0x80000000;
LABEL_64:
        *a3 = v63;
        v11 = 1;
LABEL_65:
        v64 = qword_18010C470;
        v65 = *(_DWORD *)(qword_18010C470 + 8016);
        if ( v65 > 1 )
        {
          *(_DWORD *)(qword_18010C470 + 8016) = v65 - 1;
          *(_DWORD *)(v64 + 7680) = *(_DWORD *)(*(_QWORD *)(v64 + 8024) + 4LL * (v65 - 2));
        }
        else
        {
          sub_180049A30("Calling PopItemFlag() too many times!");
        }
        v66 = "##tp_scene_id";
        if ( "##tp_scene_id" != (char *)-1LL )
        {
          do
          {
            if ( !*v66 || *v66 == 35 && v66[1] == 35 )
              break;
            ++v66;
          }
          while ( v66 != (const char *)-1LL );
          if ( "##tp_scene_id" != v66 )
          {
            sub_18004AC40();
            sub_18006EB90(v68, v67, 0);
          }
        }
        v69 = qword_18010C470;
        *(_DWORD *)(v6 + 3212) = v17;
        *(_DWORD *)(v6 + 3216) = v18;
        v70 = *(_QWORD *)(v69 + 5216);
        v71 = *(_DWORD *)(v70 + 264);
        if ( v71 > 1 )
          *(_DWORD *)(v70 + 264) = v71 - 1;
        else
          sub_180049A30("Calling PopID() too many times!");
        sub_18004B190();
        goto LABEL_79;
      }
      v63 = v62 + v61;
      goto LABEL_64;
    }
    if ( !*(_BYTE *)(v6 + 252) || (v37 = a5) == nullptr )
      v37 = v84;
    v38 = *v37;
    v39 = *a3;
    if ( v38 <= 0 )
    {
      if ( v38 < 0 && v39 > v38 + 0x7FFFFFFF )
      {
        v40 = 0x7FFFFFFF;
        goto LABEL_37;
      }
    }
    else if ( v39 < (int)(v38 + 0x80000000) )
    {
      v40 = 0x80000000;
LABEL_37:
      *a3 = v40;
      v11 = 1;
      goto LABEL_38;
    }
    v40 = v39 - v38;
    goto LABEL_37;
  }
  v82 = 0;
  if ( (unsigned __int8)sub_180079E10(
                          (unsigned int)"##tp_scene_id",
                          0,
                          (unsigned int)v81,
                          64,
                          (__int64)&v82,
                          268439552,
                          0,
                          0) )
    v11 = sub_180073770((unsigned int)v81, 4, (_DWORD)a3, (_DWORD)v10, 0);
LABEL_79:
  *(_DWORD *)(v6 + 7748) &= ~0x10000u;
  if ( v11 )
  {
    v72 = qword_18010C470;
    if ( (*(_DWORD *)(qword_18010C470 + 7748) & 0x10000) == 0 )
    {
      v73 = *(_DWORD *)(v6 + 7744);
      v74 = *(_DWORD *)(qword_18010C470 + 5332);
      if ( v74 == v73 || !v74 )
      {
        *(_WORD *)(qword_18010C470 + 5348) = 257;
        if ( *(_DWORD *)(v72 + 5384) == v73 )
          *(_BYTE *)(v72 + 5392) = 1;
      }
      *(_DWORD *)(v72 + 7752) |= 4u;
    }
  }
  return v11;
}
