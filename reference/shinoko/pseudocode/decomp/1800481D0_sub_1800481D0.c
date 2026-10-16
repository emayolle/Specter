// sub_1800481D0 size=623
double __fastcall sub_1800481D0(const char *a1, float *a2)
{
  float v2; // r8d
  float v4; // xmm2_4
  double result; // xmm0_8
  __int64 v6; // rcx
  const char *v7; // rcx
  __int64 v8; // rcx
  const char *v9; // rcx
  const char *v10; // r9
  __int64 v11; // rcx
  const char *v12; // rcx
  const char *v13; // rax
  const char *v14; // r9
  const char *v15; // r10
  const char *v16; // [rsp+30h] [rbp-28h]
  const char *v17; // [rsp+38h] [rbp-20h]
  const char *v18; // [rsp+40h] [rbp-18h]

  v2 = *a2;
  if ( *(_DWORD *)a2 == 1 )
  {
    v4 = a2[3];
    if ( v4 == -3.4028235e38 && (*(_QWORD *)&result = *((unsigned int *)a2 + 4), *(float *)&result == -3.4028235e38) )
    {
      if ( *(char *)(qword_18010C470 + 10228) < 0 )
        return sub_180052F00("[io] %s: MousePos (-FLT_MAX, -FLT_MAX)\n", a1);
    }
    else if ( *(char *)(qword_18010C470 + 10228) < 0 )
    {
      v6 = *((int *)a2 + 5);
      v16 = "Mouse";
      v17 = "TouchScreen";
      v18 = "Pen";
      if ( (unsigned int)v6 > 2 )
        v7 = "Unknown";
      else
        v7 = (&v16)[v6];
      return sub_180052F00("[io] %s: MousePos (%.1f, %.1f) (%s)\n", a1, v4, a2[4], v7);
    }
  }
  else
  {
    switch ( LODWORD(v2) )
    {
      case 3:
        if ( *(char *)(qword_18010C470 + 10228) < 0 )
        {
          v8 = *((int *)a2 + 5);
          v16 = "Mouse";
          v17 = "TouchScreen";
          v18 = "Pen";
          if ( (unsigned int)v8 > 2 )
            v9 = "Unknown";
          else
            v9 = (&v16)[v8];
          v10 = "Up";
          if ( *((_BYTE *)a2 + 16) )
            v10 = "Down";
          return sub_180052F00("[io] %s: MouseButton %d %s (%s)\n", a1, *((_DWORD *)a2 + 3), v10, v9);
        }
        break;
      case 2:
        if ( *(char *)(qword_18010C470 + 10228) < 0 )
        {
          v11 = *((int *)a2 + 5);
          v16 = "Mouse";
          v17 = "TouchScreen";
          v18 = "Pen";
          if ( (unsigned int)v11 > 2 )
            v12 = "Unknown";
          else
            v12 = (&v16)[v11];
          return sub_180052F00("[io] %s: MouseWheel (%.3f, %.3f) (%s)\n", a1, a2[3], a2[4], v12);
        }
        break;
      case 4:
        if ( *(char *)(qword_18010C470 + 10228) < 0 )
        {
          v13 = sub_180046950(*((_DWORD *)a2 + 3));
          return sub_180052F00("[io] %s: Key \"%s\" %s\n", v15, v13, v14);
        }
        break;
      case 5:
        if ( *(char *)(qword_18010C470 + 10228) < 0 )
          return sub_180052F00("[io] %s: Text: %c (U+%08X)\n", a1, *((unsigned int *)a2 + 3), *((_DWORD *)a2 + 3));
        break;
      default:
        if ( LODWORD(v2) == 6 && *(char *)(qword_18010C470 + 10228) < 0 )
          return sub_180052F00("[io] %s: AppFocused %d\n", a1, *((unsigned __int8 *)a2 + 12));
        break;
    }
  }
  return result;
}
