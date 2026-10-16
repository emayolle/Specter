// sub_180046950 size=119
const char *__fastcall sub_180046950(int a1)
{
  if ( !a1 )
    return "None";
  if ( (a1 & 0xF000) != 0 )
  {
    switch ( a1 )
    {
      case 0x1000:
        a1 = 663;
        break;
      case 0x2000:
        a1 = 664;
        break;
      case 0x4000:
        a1 = 665;
        break;
      case 0x8000:
        a1 = 666;
        break;
    }
  }
  if ( (unsigned int)(a1 - 512) <= 0x9A )
    return off_1800D5AC0[a1 - 512];
  else
    return "Unknown";
}
