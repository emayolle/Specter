// sub_180025AD0 size=685
SHORT __fastcall sub_180025AD0(const char *a1, int *a2, _QWORD *a3)
{
  const char *v4; // rdi
  bool v6; // si
  int v7; // r8d
  const char *v8; // rbx
  char v9; // al
  SHORT result; // ax
  int v11; // ebx
  __m128i si128; // [rsp+20h] [rbp-58h] BYREF
  _BYTE v13[64]; // [rsp+30h] [rbp-48h] BYREF

  v4 = a1;
  v6 = qword_18010C598 == (_QWORD)a1;
  if ( (const char *)qword_18010C598 == a1 )
  {
    sub_180028EB0(v13, "Press...##%s", a1);
  }
  else
  {
    v7 = *a2;
    if ( *a2 )
    {
      if ( (unsigned int)(v7 - 112) > 0x17 )
      {
        switch ( v7 )
        {
          case 45:
            v8 = "Insert";
            break;
          case 46:
            v8 = "Delete";
            break;
          case 36:
            v8 = "Home";
            break;
          case 35:
            v8 = "End";
            break;
          case 33:
            v8 = "PageUp";
            break;
          case 34:
            v8 = "PageDown";
            break;
          case 9:
            v8 = "Tab";
            break;
          case 32:
            v8 = "Space";
            break;
          case 13:
            v8 = "Enter";
            break;
          case 27:
            v8 = "Esc";
            break;
          case 192:
            v8 = "~";
            break;
          default:
            if ( (unsigned int)(v7 - 65) > 0x19 )
            {
              if ( (unsigned int)(v7 - 48) > 9 )
              {
                v8 = (const char *)&unk_18010C978;
                sub_180028E50(&unk_18010C978, "0x%02X", v7);
              }
              else
              {
                byte_18010C964 = *a2;
                v8 = &byte_18010C964;
                byte_18010C965 = 0;
              }
            }
            else
            {
              byte_18010C968 = *a2;
              v8 = &byte_18010C968;
              byte_18010C969 = 0;
            }
            break;
        }
      }
      else
      {
        v8 = (const char *)&unk_18010C988;
        sub_180028E50(&unk_18010C988, "F%d", v7 - 111);
      }
    }
    else
    {
      v8 = "None";
    }
    sub_180028EB0(v13, "%s##%s", v8, v4);
  }
  if ( v6 )
  {
    si128 = _mm_load_si128((const __m128i *)&xmmword_1800E69E0);
    sub_180036E50(21, &si128);
    si128 = _mm_load_si128((const __m128i *)&xmmword_1800E6A40);
    sub_180036E50(22, &si128);
  }
  sub_18006FED0((__int64)v13, a3);
  if ( v9 )
  {
    if ( v6 )
      v4 = nullptr;
    qword_18010C598 = (__int64)v4;
  }
  result = sub_18003A270(0);
  if ( (_BYTE)result )
    result = sub_18004BCF0("Click to bind, Esc to unbind");
  if ( v6 )
  {
    sub_180036F60(2);
    v11 = 1;
    while ( 1 )
    {
      result = v11 - 1;
      if ( ((v11 - 1) & 0xFFFFFFFC) != 0 || v11 == 3 )
      {
        result = GetAsyncKeyState(v11);
        if ( (result & 1) != 0 )
          break;
      }
      if ( ++v11 >= 256 )
        return result;
    }
    result = 0;
    if ( v11 == 27 )
      v11 = 0;
    *a2 = v11;
    qword_18010C598 = 0;
  }
  return result;
}
