// sub_18005FF00 size=1066
void __fastcall sub_18005FF00(__int64 a1, __int64 a2)
{
  __int64 v2; // r8
  int i; // r12d
  int v6; // eax
  int v7; // edx
  __int64 v8; // rbx
  const char *v9; // r8
  __int64 v10; // r9
  __int64 j; // rbp
  int v12; // edx
  __int64 v13; // r8
  __int64 v14; // r11
  int v15; // edi
  __int64 v16; // r10
  __int64 v17; // rdx
  unsigned int v18; // eax
  unsigned int v19; // edi
  int v20; // esi
  unsigned int v21; // edi
  int v22; // eax
  int v23; // ecx
  _QWORD *v24; // rsi
  __int64 v25; // rbp
  _QWORD *k; // r14
  __int64 v27; // rdi
  void (__fastcall *v28)(__int64, _QWORD, __int64, __int64); // rax
  void *v29; // r9
  __int64 v30; // r8
  __int64 v31; // rdx
  int v32; // r10d
  __int64 v33; // rcx
  __int16 v34; // cx
  unsigned int v35; // r8d
  __int64 v36; // r9
  unsigned __int64 v37; // rdx
  __int64 v38; // rax
  void *v39; // rcx
  void *v40; // rcx
  void *v41; // rcx
  int v42; // [rsp+20h] [rbp-48h] BYREF
  __int64 v43; // [rsp+28h] [rbp-40h]
  __int64 v44; // [rsp+70h] [rbp+8h]
  __int64 v45; // [rsp+88h] [rbp+20h]

  v2 = *(_QWORD *)(a1 + 688);
  v45 = v2;
  if ( v2 )
  {
    for ( i = 0; i < *(_DWORD *)(v2 + 192); ++i )
    {
      v6 = i;
      v7 = i & 0x1F;
      if ( i < 0 )
      {
        v6 = i + 31;
        v7 -= 32;
      }
      v8 = 104LL * v7 + *(_QWORD *)(*(_QWORD *)(v2 + 208) + 8LL * (v6 >> 5));
      v44 = *(_QWORD *)(a1 + 688);
      if ( *(_DWORD *)(v8 + 80) <= *(_DWORD *)(v44 + 164)
        && *(_QWORD *)(v8 + 88) == a2
        && (*(_DWORD *)(v8 + 76) & 0x4000000) == 0 )
      {
        if ( qword_18010C470 && (*(_DWORD *)(qword_18010C470 + 10228) & 0x100) != 0 )
        {
          if ( *(_DWORD *)(a2 + 32) )
            v9 = **(const char ***)(a2 + 40);
          else
            v9 = "<unknown>";
          sub_180052F00("[font] Discard baked %.2f for \"%s\"\n", *(float *)(v8 + 20), v9);
        }
        v10 = *(_QWORD *)(v8 + 56);
        for ( j = v10 + 44LL * *(int *)(v8 + 48); v10 != j; v10 += 44 )
        {
          v12 = *(_DWORD *)(v10 + 40);
          if ( v12 != -1 )
          {
            v13 = *(_QWORD *)(a1 + 688);
            v14 = *(_QWORD *)(v13 + 120);
            v15 = *(_DWORD *)(v14 + 4LL * (v12 & 0x7FFFF));
            v16 = *(_QWORD *)(v13 + 104) + 8 * ((__int64)(v15 << 12) >> 12);
            if ( v16 )
            {
              v17 = v12 & 0x7FFFF;
              v18 = v15 & 0xBFFFFFFF;
              v19 = v15 & 0xBFF00000;
              *(_DWORD *)(v14 + 4 * v17) = v18;
              v20 = v19 | *(_DWORD *)(v13 + 144) & 0xFFFFF;
              v21 = v19 + 0x100000;
              v22 = v20 ^ (v20 ^ v21) & 0x3FF00000;
              *(_DWORD *)(v14 + 4 * v17) = v22;
              if ( (v22 & 0x3FF00000) == 0 )
                *(_DWORD *)(v14 + 4 * v17) = v20 ^ (v21 ^ (v20 ^ v21) & 0x3FF00000 ^ (v22 + 0x100000)) & 0x3FF00000;
              v23 = *(_DWORD *)(a1 + 8);
              ++*(_DWORD *)(v13 + 156);
              *(_DWORD *)(v13 + 144) = v17;
              *(_DWORD *)(v13 + 160) += (v23 + *(unsigned __int16 *)(v16 + 4)) * (v23 + *(unsigned __int16 *)(v16 + 6));
              *(_DWORD *)(v16 + 4) = 0;
            }
          }
        }
        v24 = *(_QWORD **)(a2 + 40);
        v25 = *(_QWORD *)(v8 + 96);
        for ( k = &v24[*(int *)(a2 + 32)]; v24 != k; ++v24 )
        {
          v27 = *(_QWORD *)(*v24 + 128LL);
          if ( !v27 )
            v27 = *(_QWORD *)(a1 + 696);
          v28 = *(void (__fastcall **)(__int64, _QWORD, __int64, __int64))(v27 + 56);
          if ( v28 )
            v28(a1, *v24, v8, v25);
          v25 += *(_QWORD *)(v27 + 72);
        }
        v29 = *(void **)(v8 + 96);
        if ( v29 )
        {
          v30 = qword_18010C470;
          if ( qword_18010C470 )
          {
            v31 = *(__int16 *)(qword_18010C470 + 10432);
            v32 = *(_DWORD *)(qword_18010C470 + 5032);
            v33 = 8 * v31;
            if ( *(_DWORD *)(8 * v31 + qword_18010C470 + 10436) != v32 )
            {
              v34 = ((int)v31 + 1) % 6;
              *(_WORD *)(qword_18010C470 + 10432) = v34;
              v33 = 8LL * v34;
              *(_DWORD *)(v33 + v30 + 10440) = 0;
              *(_DWORD *)(v33 + v30 + 10436) = v32;
            }
            ++*(_WORD *)(v33 + v30 + 10442);
            ++*(_DWORD *)(v30 + 10428);
          }
          sub_18009E210(v29);
          *(_QWORD *)(v8 + 96) = 0;
        }
        v35 = *(_DWORD *)(v8 + 84);
        v36 = *(_QWORD *)(v44 + 224);
        v37 = *(int *)(v44 + 216);
        if ( (_DWORD)v37 )
        {
          do
          {
            v38 = 16 * (v37 >> 1);
            if ( *(_DWORD *)(v38 + v36) >= v35 )
            {
              v37 >>= 1;
            }
            else
            {
              v36 += v38 + 16;
              v37 += -1LL - (v37 >> 1);
            }
          }
          while ( v37 );
        }
        if ( v36 == *(_QWORD *)(v44 + 224) + 16LL * *(int *)(v44 + 216) || *(_DWORD *)v36 != v35 )
        {
          v42 = *(_DWORD *)(v8 + 84);
          v43 = 0;
          sub_1800543A0(v44 + 216, v36, &v42);
        }
        else
        {
          *(_QWORD *)(v36 + 8) = 0;
        }
        ++*(_DWORD *)(v44 + 232);
        *(_DWORD *)(v8 + 16) = 0;
        v39 = *(void **)(v8 + 56);
        if ( v39 )
        {
          *(_QWORD *)(v8 + 48) = 0;
          sub_18003A8D0(v39);
          *(_QWORD *)(v8 + 56) = 0;
        }
        v40 = *(void **)(v8 + 8);
        if ( v40 )
        {
          *(_QWORD *)v8 = 0;
          sub_18003A8D0(v40);
          *(_QWORD *)(v8 + 8) = 0;
        }
        v41 = *(void **)(v8 + 40);
        if ( v41 )
        {
          *(_QWORD *)(v8 + 32) = 0;
          sub_18003A8D0(v41);
          *(_QWORD *)(v8 + 40) = 0;
        }
        *(_DWORD *)(v8 + 76) &= 0xFC000000;
        *(_DWORD *)(v8 + 76) |= 0x4000000u;
        v2 = v45;
        *(_DWORD *)(v8 + 64) = -1;
        *(_QWORD *)(v8 + 68) = 0;
        *(_QWORD *)a2 = 0;
      }
    }
  }
}
