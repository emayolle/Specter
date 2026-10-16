// sub_18003D360 size=1656
__int64 sub_18003D360()
{
  __int64 v0; // rbx
  __int64 result; // rax
  __int64 v2; // rdi
  __int64 v3; // rax
  __int64 v4; // rsi
  __int64 v5; // rdi
  int v6; // ecx
  int i; // edx
  __int64 v8; // rax
  __int64 v9; // rcx
  __int64 v10; // rdi
  void (__fastcall *v11)(__int64, const char *); // rax
  bool v12; // zf
  __int64 v13; // rax
  __int64 v14; // rdi
  int v15; // eax
  bool v16; // al
  int v17; // eax
  __int64 v18; // rdi
  __int64 v19; // rax
  int v20; // ecx
  int *v21; // rsi
  __int64 v22; // rdx
  int v23; // ecx
  __int64 v24; // rdi
  __int64 v25; // rax
  __int64 v26; // rbp
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  __int64 v30; // rax
  __int64 v31; // rcx
  __int64 *v32; // rcx
  __int64 v33; // rax
  __int64 *v34; // rdx
  __int64 v35; // rax
  int v36; // ecx
  __int64 v37; // rdx
  int v38; // ecx
  __int64 v39; // rdi
  __int64 v40; // rsi

  v0 = qword_18010C470;
  result = *(unsigned int *)(qword_18010C470 + 5032);
  if ( *(_DWORD *)(qword_18010C470 + 5036) != (_DWORD)result )
  {
    if ( *(_BYTE *)(qword_18010C470 + 5048) )
    {
      v2 = *(_QWORD *)(qword_18010C470 + 9984);
      v3 = 32LL * *(int *)(qword_18010C470 + 9976);
      v4 = v3 + v2;
      if ( v3 )
      {
        do
        {
          if ( *(_DWORD *)(v2 + 4) == 2 )
            (*(void (__fastcall **)(__int64, __int64))(v2 + 16))(v0, v2);
          v2 += 32;
        }
        while ( v2 != v4 );
      }
      if ( *(_BYTE *)(v0 + 124) )
      {
        v5 = qword_18010C470;
        v6 = *(__int16 *)(v0 + 10192);
        for ( i = *(_DWORD *)(qword_18010C470 + 5168); i > v6; i = *(_DWORD *)(v5 + 5168) )
        {
          v8 = *(_QWORD *)(v5 + 5216);
          if ( (*(_DWORD *)(v8 + 20) & 0x1000000) != 0 )
          {
            v9 = *(_QWORD *)(v5 + 8856);
            if ( v9 && *(_QWORD *)(v9 + 392) == v8 )
            {
              sub_180049A30("Missing EndTable()");
              sub_18006B130();
            }
            else
            {
              sub_180049A30("Missing EndChild()");
              sub_18003E7F0();
            }
          }
          else
          {
            sub_180049A30("Missing End()");
            sub_180044DF0();
          }
          v6 = *(__int16 *)(v0 + 10192);
        }
        if ( i == (__int16)v6 )
          sub_1800493D0(v0 + 10192);
      }
      v10 = qword_18010C470;
      if ( *(_DWORD *)(qword_18010C470 + 5300) )
      {
        if ( !*(_BYTE *)(qword_18010C470 + 252) )
          *(_DWORD *)(qword_18010C470 + 10224) = *(_DWORD *)(qword_18010C470 + 5316);
        if ( !*(_BYTE *)(v10 + 10289) && (unsigned __int8)sub_180049DB0() )
        {
          sub_18006F370((__int64)"Programmer error: %d visible items with conflicting ID!", *(_DWORD *)(v10 + 10224));
          sub_18006F510("Code should use PushID()/PopID() in loops, or append \"##xx\" to same-label identifiers!");
          sub_18006F510("Empty label e.g. Button(\"\") == same ID as parent widget/node. Use Button(\"##xx\") instead!");
          sub_18006F510("Set io.ConfigDebugHighlightIdConflicts=false to disable this warning in non-programmers builds.");
          sub_180071F50();
          if ( *(_BYTE *)(v10 + 130) )
          {
            sub_18006F370((__int64)"(Hold CTRL to: use ");
            sub_18004AC40();
            if ( (unsigned __int8)sub_180070160("Item Picker") )
              *(_BYTE *)(qword_18010C470 + 10289) = 1;
            sub_18004AC40();
            sub_18006F370((__int64)" to break in item call-stack, or ");
          }
          else
          {
            sub_18006F370((__int64)"(Hold CTRL to ");
          }
          sub_18004AC40();
          if ( (unsigned __int8)sub_180070160("Open FAQ->About ID Stack System") )
          {
            v11 = *(void (__fastcall **)(__int64, const char *))(v10 + 3064);
            if ( v11 )
              v11(v10, "https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#qa-usage");
          }
          sub_18004AC40();
          sub_18006F370((__int64)")");
          sub_180044DF0();
        }
      }
      if ( *(int *)(v10 + 10188) > 0 && (unsigned __int8)sub_180049DB0() )
      {
        sub_180071F50();
        sub_18006F370((__int64)"(Hold CTRL to:");
        sub_18004AC40();
        if ( (unsigned __int8)sub_180070160("Enable Asserts") )
          *(_BYTE *)(v10 + 125) = 1;
        sub_18004AC40();
        sub_18006F370((__int64)")");
        sub_180044DF0();
      }
      if ( *(_QWORD *)(v0 + 3080)
        && (*(_QWORD *)(v0 + 9848) != *(_QWORD *)(v0 + 9868)
         || *(_QWORD *)(v0 + 9856) != *(_QWORD *)(v0 + 9876)
         || *(_DWORD *)(v0 + 9864) != *(_DWORD *)(v0 + 9884)) )
      {
        if ( *(char *)(v0 + 10228) < 0 )
          sub_180052F00(
            "[io] Calling Platform_SetImeDataFn(): WantVisible: %d, InputPos (%.2f,%.2f)\n",
            *(unsigned __int8 *)(v0 + 9848),
            *(float *)(v0 + 9852),
            *(float *)(v0 + 9856));
        (*(void (__fastcall **)(__int64, _QWORD, __int64))(v0 + 3080))(
          v0,
          **(_QWORD **)(qword_18010C470 + 8104),
          v0 + 9848);
      }
      v12 = *(_BYTE *)(v0 + 9849) == 0;
      *(_BYTE *)(v0 + 5049) = 0;
      *(_DWORD *)(v0 + 10744) = !v12;
      v13 = *(_QWORD *)(v0 + 5216);
      if ( v13 && !*(_BYTE *)(v13 + 206) )
        *(_BYTE *)(v13 + 204) = 0;
      sub_180044DF0();
      v14 = qword_18010C470;
      if ( *(_QWORD *)(qword_18010C470 + 8592) )
        sub_1800513E0();
      if ( *(_QWORD *)(v14 + 8120) )
      {
        if ( *(_BYTE *)(qword_18010C470 + 8265) )
        {
          if ( !*(_DWORD *)(qword_18010C470 + 8344) && !*(_DWORD *)(qword_18010C470 + 8456) )
          {
            v15 = *(_DWORD *)(v14 + 8268);
            if ( (v15 & 0xF) != 0 && (v15 & 0x80u) == 0 )
              sub_180050440();
          }
        }
      }
      if ( *(_BYTE *)(v0 + 8656) )
      {
        v16 = *(_DWORD *)(v0 + 8664) + 1 < *(_DWORD *)(v0 + 5032)
           && ((*(_BYTE *)(v0 + 8660) & 0x20) != 0 || *(_DWORD *)(v0 + 8668) == -1 || !(unsigned __int8)sub_180046F40());
        if ( *(_BYTE *)(v0 + 8730) || v16 )
          sub_1800516C0();
        if ( *(_BYTE *)(v0 + 8656)
          && *(_DWORD *)(v0 + 8664) + 1 < *(_DWORD *)(v0 + 5032)
          && (*(_BYTE *)(v0 + 8660) & 1) == 0 )
        {
          *(_BYTE *)(v0 + 8657) = 1;
          sub_18004BCF0("...");
          *(_BYTE *)(v0 + 8657) = 0;
        }
      }
      v17 = *(_DWORD *)(v0 + 5032);
      v18 = qword_18010C470;
      *(_BYTE *)(v0 + 5048) = 0;
      *(_DWORD *)(v0 + 5036) = v17;
      v19 = *(int *)(v18 + 7984);
      if ( (int)v19 > 0 )
      {
        sub_180046120(*(_QWORD *)(*(_QWORD *)(v18 + 7992) + 16 * v19 - 16));
        --*(_DWORD *)(v18 + 7984);
      }
      else
      {
        sub_180049A30("Calling PopFont() too many times!");
      }
      sub_18003AEC0();
      v20 = *(_DWORD *)(v0 + 5156);
      v21 = (int *)(v0 + 5152);
      if ( v20 < 0 )
      {
        v22 = 0;
        v23 = v20 / 2 + v20;
        if ( v23 > 0 )
          v22 = (unsigned int)v23;
        sub_180054080(v0 + 5152, v22);
      }
      *v21 = 0;
      sub_180054080(v0 + 5152, *(unsigned int *)(v0 + 5120));
      v24 = *(_QWORD *)(v0 + 5128);
      v25 = 8LL * *(int *)(v0 + 5120);
      v26 = v25 + v24;
      if ( v25 )
      {
        do
        {
          if ( !*(_BYTE *)(*(_QWORD *)v24 + 204LL) || (*(_DWORD *)(*(_QWORD *)v24 + 20LL) & 0x1000000) == 0 )
            sub_18003CB30(v0 + 5152);
          v24 += 8;
        }
        while ( v24 != v26 );
      }
      v27 = *v21;
      *v21 = *(_DWORD *)(v0 + 5120);
      v28 = *(_DWORD *)(v0 + 5124);
      *(_DWORD *)(v0 + 5120) = v27;
      v29 = *(_DWORD *)(v0 + 5156);
      *(_DWORD *)(v0 + 5156) = v28;
      v30 = *(_QWORD *)(v0 + 5128);
      *(_DWORD *)(v0 + 5124) = v29;
      v31 = *(_QWORD *)(v0 + 5160);
      *(_QWORD *)(v0 + 5160) = v30;
      *(_DWORD *)(v0 + 200) = *(_DWORD *)(v0 + 5200);
      *(_QWORD *)(v0 + 5128) = v31;
      sub_180045DD0();
      v32 = *(__int64 **)(v0 + 4408);
      v33 = *(int *)(v0 + 4400);
      v34 = &v32[v33];
      if ( v33 * 8 )
      {
        do
        {
          v35 = *v32++;
          *(_BYTE *)(v35 + 80) = 0;
        }
        while ( v32 != v34 );
      }
      *(_QWORD *)(v0 + 2744) = *(_QWORD *)(v0 + 224);
      *(_BYTE *)(v0 + 2988) = 0;
      *(_QWORD *)(v0 + 240) = 0;
      v36 = *(_DWORD *)(v0 + 2996);
      if ( v36 < 0 )
      {
        v37 = 0;
        v38 = v36 / 2 + v36;
        if ( v38 > 0 )
          v37 = (unsigned int)v38;
        sub_180054650(v0 + 2992, v37);
      }
      *(_DWORD *)(v0 + 2992) = 0;
      v39 = *(_QWORD *)(v0 + 9984);
      result = 32LL * *(int *)(v0 + 9976);
      v40 = result + v39;
      if ( result )
      {
        do
        {
          if ( *(_DWORD *)(v39 + 4) == 3 )
            result = (*(__int64 (__fastcall **)(__int64, __int64))(v39 + 16))(v0, v39);
          v39 += 32;
        }
        while ( v39 != v40 );
      }
    }
    else
    {
      return sub_180049A30("Forgot to call ImGui::NewFrame()?");
    }
  }
  return result;
}
