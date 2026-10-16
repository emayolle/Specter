// sub_18005E5F0 size=265
__int64 __fastcall sub_18005E5F0(int a1)
{
  int v2; // r8d
  int v3; // r9d
  _OWORD v5[3]; // [rsp+30h] [rbp-D0h] BYREF
  __int128 v6; // [rsp+60h] [rbp-A0h]
  __int128 v7; // [rsp+70h] [rbp-90h]
  __int128 v8; // [rsp+80h] [rbp-80h]
  __int128 v9; // [rsp+90h] [rbp-70h]
  __int128 v10; // [rsp+A0h] [rbp-60h]
  __int128 v11; // [rsp+B0h] [rbp-50h]
  __int128 v12; // [rsp+F0h] [rbp-10h]
  __int128 v13; // [rsp+110h] [rbp+10h]
  __int128 v14; // [rsp+120h] [rbp+20h]
  __int128 v15; // [rsp+130h] [rbp+30h]

  v12 = 0;
  BYTE4(v12) = 1;
  v13 = 0;
  DWORD2(v12) = 0;
  HIDWORD(v13) = 2139095039;
  v14 = 0;
  HIDWORD(v14) = 1065353216;
  v6 = v12;
  WORD4(v6) = 257;
  v15 = 0;
  LODWORD(v15) = 1065353216;
  v8 = v13;
  BYTE6(v6) = 1;
  memset(v5, 0, sizeof(v5));
  v10 = v15;
  v7 = 0;
  v9 = v14;
  v11 = 0;
  HIDWORD(v6) = 1095761920;
  sub_180035ED0(v5, 40, "ProggyClean.ttf");
  WORD5(v6) = 133;
  *((float *)&v8 + 1) = *((float *)&v8 + 1) + (float)(int)(float)(*((float *)&v6 + 3) / 13.0);
  return sub_18005E700(a1, (unsigned int)&unk_1800D6040, v2, v3, (__int64)v5);
}
