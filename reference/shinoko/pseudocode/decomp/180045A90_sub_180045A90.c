// sub_180045A90 size=829
__int64 sub_180045A90()
{
  __int64 v0; // r13
  bool v1; // r12
  __int64 v2; // r15
  __int64 result; // rax
  __int64 v4; // rsi
  int v5; // ebx
  __int64 v6; // rbp
  _QWORD **v7; // rcx
  _QWORD **i; // rdx
  int v9; // r8d
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  int v13; // ecx
  __int64 v14; // r10
  __int64 v15; // r9
  int v16; // ecx
  int v17; // eax
  __int64 v18; // rdx
  int j; // edi
  __int64 v20; // rbx
  int v21; // eax
  int v22; // ecx
  int v23; // eax
  __int64 v24; // rdx
  char v25; // cl
  void *v26; // rcx
  void *v27; // rcx
  __int64 v28; // rcx
  __int64 v29; // [rsp+70h] [rbp+8h]

  v0 = qword_18010C470;
  v1 = (*(_DWORD *)(qword_18010C470 + 12) & 0x10) != 0;
  v2 = *(_QWORD *)(qword_18010C470 + 4408);
  result = 8LL * *(int *)(qword_18010C470 + 4400);
  v29 = result + v2;
  if ( result )
  {
    result += v2;
    do
    {
      v4 = *(_QWORD *)v2;
      if ( *(_QWORD *)(*(_QWORD *)v2 + 728LL) != v0 )
        goto LABEL_58;
      v5 = *(_DWORD *)(v0 + 5032);
      *(_BYTE *)(v4 + 81) = v1;
      if ( v1 )
      {
        *(_BYTE *)(v4 + 82) = 1;
        if ( !*(_QWORD *)(v4 + 688) )
          sub_18005EA50(v4);
      }
      if ( !*(_BYTE *)(v4 + 81) )
      {
        if ( *(_BYTE *)(v4 + 82) )
          goto LABEL_11;
        sub_180049A30(
          "Backend does not support ImGuiBackendFlags_RendererHasTextures, and font atlas is not built! Update backend OR"
          " make sure you called ImGui_ImplXXXX_NewFrame() function for renderer backend, which should call io.Fonts->Get"
          "TexDataAsRGBA32() / GetTexDataAsAlpha8().");
      }
      if ( *(_BYTE *)(v4 + 82) )
      {
LABEL_11:
        if ( *(_BYTE *)(*(_QWORD *)(v4 + 688) + 185LL) && *(_BYTE *)(v4 + 81) )
          sub_180049A30(
            "Called ImFontAtlas::Build() before ImGuiBackendFlags_RendererHasTextures got set! With new backends: you don"
            "'t need to call Build().");
      }
      v6 = *(_QWORD *)(v4 + 688);
      *(_DWORD *)(v6 + 164) = v5;
      v7 = *(_QWORD ***)(v4 + 112);
      for ( i = &v7[*(int *)(v4 + 104)]; v7 != i; ++v7 )
        **v7 = 0;
      if ( *(int *)(v6 + 232) > 0 )
      {
        v9 = *(_DWORD *)(v6 + 192);
        if ( v9 > 0 )
        {
          v10 = 0;
          v11 = 0;
          do
          {
            v12 = v10 & 0x1F;
            v13 = v10;
            if ( v10 < 0 )
            {
              v13 = v10 + 31;
              v12 -= 32;
            }
            v14 = *(_QWORD *)(v6 + 208);
            v15 = 104LL * v12 + *(_QWORD *)(v14 + 8LL * (v13 >> 5));
            if ( (*(_DWORD *)(v15 + 76) & 0x4000000) == 0 )
            {
              v16 = v11 & 0x1F;
              v17 = v11;
              if ( v11 < 0 )
              {
                v17 = v11 + 31;
                v16 -= 32;
              }
              v18 = 104LL * v16 + *(_QWORD *)(v14 + 8LL * (v17 >> 5));
              ++v11;
              if ( v18 != v15 )
              {
                *(_OWORD *)v18 = *(_OWORD *)v15;
                *(_OWORD *)(v18 + 16) = *(_OWORD *)(v15 + 16);
                *(_OWORD *)(v18 + 32) = *(_OWORD *)(v15 + 32);
                *(_OWORD *)(v18 + 48) = *(_OWORD *)(v15 + 48);
                *(_OWORD *)(v18 + 64) = *(_OWORD *)(v15 + 64);
                *(_OWORD *)(v18 + 80) = *(_OWORD *)(v15 + 80);
                *(_QWORD *)(v18 + 96) = *(_QWORD *)(v15 + 96);
                sub_1800369D0(v6 + 216, *(unsigned int *)(v18 + 84), v18);
                v9 = *(_DWORD *)(v6 + 192);
              }
            }
            ++v10;
          }
          while ( v10 < v9 );
        }
        *(_DWORD *)(v6 + 192) = v9 - *(_DWORD *)(v6 + 232);
        *(_DWORD *)(v6 + 232) = 0;
      }
      for ( j = 0; j < *(_DWORD *)(v4 + 64); ++j )
      {
        v20 = *(_QWORD *)(*(_QWORD *)(v4 + 72) + 8LL * j);
        v21 = *(_DWORD *)(v20 + 4);
        if ( !v21 )
        {
          v22 = *(_DWORD *)(v20 + 68);
          if ( v22 < 0 )
          {
            v23 = v22 + ((v22 + 1) >> 1);
            v24 = 0;
            if ( v23 > 0 )
              v24 = (unsigned int)v23;
            sub_180054080(v20 + 64, v24);
          }
          *(_QWORD *)(v20 + 60) = 0;
          *(_DWORD *)(v20 + 56) = -1;
          v21 = *(_DWORD *)(v20 + 4);
        }
        v25 = *(_BYTE *)(v20 + 87);
        if ( v25 )
        {
          if ( v21 == 1 )
          {
            v21 = 1;
LABEL_40:
            if ( v21 == 1 )
              goto LABEL_41;
            continue;
          }
          if ( v21 != 4 )
            *(_DWORD *)(v20 + 4) = 4;
        }
        else if ( v21 != 4 )
        {
          goto LABEL_40;
        }
        if ( !*(_QWORD *)(v20 + 16) && !*(_QWORD *)(v20 + 8) )
        {
          *(_DWORD *)(v20 + 4) = 1;
LABEL_41:
          if ( v25 )
          {
            v26 = *(void **)(v20 + 40);
            if ( v26 )
              sub_18003A8D0(v26);
            *(_QWORD *)(v20 + 40) = 0;
            *(_BYTE *)(v20 + 86) = 0;
            if ( v20 )
            {
              v27 = *(void **)(v20 + 72);
              if ( v27 )
                sub_18003A8D0(v27);
              sub_18003A8D0((LPVOID)v20);
            }
            v28 = *(_QWORD *)(v4 + 72) + 8LL * j;
            sub_1800B8BD0(v28, v28 + 8, 8 * (*(int *)(v4 + 64) - (__int64)j) - 8);
            --*(_DWORD *)(v4 + 64);
            --j;
          }
          else
          {
            *(_DWORD *)(v20 + 4) = 2;
          }
          continue;
        }
        ++*(_DWORD *)(v20 + 80);
      }
      result = v29;
LABEL_58:
      v2 += 8;
    }
    while ( v2 != result );
  }
  return result;
}
