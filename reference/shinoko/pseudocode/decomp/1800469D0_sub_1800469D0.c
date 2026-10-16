// sub_1800469D0 size=313
__int64 __fastcall sub_1800469D0(int a1)
{
  __int64 v1; // rbp
  unsigned int v2; // ebx
  int v3; // edi
  int v4; // eax
  __int64 v5; // rax

  v1 = qword_18010C470;
  v2 = a1 & 0xFFFF0FFF;
  v3 = a1;
  if ( (a1 & 0xFFFF0FFF) - 527 <= 7 )
  {
    if ( ((v2 - 527) & 0xFFFFFFFB) != 0 )
    {
      if ( ((v2 - 528) & 0xFFFFFFFB) != 0 )
      {
        if ( ((v2 - 529) & 0xFFFFFFFB) != 0 )
        {
          v4 = -32769;
          if ( ((v2 - 530) & 0xFFFFFFFB) != 0 )
            v4 = -1;
        }
        else
        {
          v4 = -16385;
        }
      }
      else
      {
        v4 = -8193;
      }
    }
    else
    {
      v4 = -4097;
    }
    v3 = v4 & a1;
  }
  if ( v2 || !v3 )
    sub_180046950(v2);
  sub_180035ED0(v1 + 10768, 64, "%s%s%s%s%s");
  if ( !v2 )
  {
    if ( v3 )
    {
      v5 = sub_1800B9730(v1 + 10768);
      if ( v5 )
        *(_BYTE *)(v5 + v1 + 10767) = 0;
    }
  }
  return v1 + 10768;
}
