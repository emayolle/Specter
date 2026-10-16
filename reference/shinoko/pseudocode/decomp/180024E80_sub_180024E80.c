// sub_180024E80 size=1264
__int64 sub_180024E80()
{
  __int64 v0; // rcx
  __int64 v1; // rcx
  char v2; // al
  double v4; // [rsp+28h] [rbp-30h]
  __int64 v5; // [rsp+60h] [rbp+8h] BYREF

  v5 = 3212836864LL;
  sub_180002F70((__int64)"ESP", (float *)&v5);
  sub_180071070((__int64)"Enable ESP##esp_enable", &byte_1800FAB38);
  sub_180003720((__int64)"Draw ESP boxes, names, distances and snaplines over entities.");
  if ( byte_1800FAB38 )
  {
    sub_180071F50();
    sub_18006F370((__int64)"Filters");
    sub_180071070((__int64)"  Players##esp_players", &byte_1800FAB39);
    sub_180003720((__int64)"Show other players (marked as Players).");
    sub_18004AC40();
    sub_180071070((__int64)"  NPC##esp_npc", &byte_1800FAB3A);
    sub_180003720((__int64)"Show NPCs (marked as NPC).");
    sub_18004AC40();
    sub_180071070((__int64)"  Pets##esp_pets", &byte_1800FAB3B);
    sub_180003720((__int64)"Show pets (marked as Pets).");
    sub_180071070((__int64)"  Loot##esp_loot", &byte_1800FAB3C);
    sub_180003720((__int64)"Show loot and items.");
    sub_18004AC40();
    sub_180071070((__int64)"  All Objects##esp_allobjs", &byte_1800FAB3D);
    sub_180003720((__int64)"Show all other world objects.");
    sub_180071F50();
    sub_18006F370((__int64)"Display");
    sub_180071070((__int64)"  Box##esp_box", &byte_1800FAB3E);
    sub_180003720((__int64)"Draw 2D bounding box.");
    sub_18004AC40();
    sub_180071070((__int64)"  Lines##esp_lines", &byte_1800FAB41);
    sub_180003720((__int64)"Draw snaplines from bottom of screen to targets.");
    sub_18004AC40();
    sub_180071070((__int64)"  Name##esp_name", &byte_1800FAB3F);
    sub_180003720((__int64)"Draw entity name.");
    sub_18004AC40();
    sub_180071070((__int64)"  Distance##esp_dist", &byte_1800FAB40);
    sub_180003720((__int64)"Draw distance in metres.");
    sub_180071F50();
    sub_18006F370((__int64)"ESP Colors");
    sub_18007E600("##col_players", &xmmword_1800FAB48, 65568);
    sub_18004AC40();
    sub_18006F370((__int64)"Players");
    sub_18007E600("##col_npc", &xmmword_1800FAB58, 65568);
    sub_18004AC40();
    sub_18006F370((__int64)"NPC / Monsters");
    sub_18007E600("##col_pets", &xmmword_1800FAB68, 65568);
    sub_18004AC40();
    sub_18006F370((__int64)"Pets / Aniimo");
    sub_18007E600("##col_loot", &xmmword_1800FAB78, 65568);
    sub_18004AC40();
    sub_18006F370((__int64)"Loot / Drops");
    sub_18007E600("##col_text", &xmmword_1800FAB9C, 65568);
    sub_18004AC40();
    sub_18006F370((__int64)"Text & Distance");
    v0 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v0 + 5216) + 209LL) )
    {
      v5 = 0;
      sub_18004AAD0(&v5);
    }
    sub_180071070((__int64)"Custom Line Color##chk_col_lines", &byte_1800FAB98);
    if ( byte_1800FAB98 )
    {
      sub_18004AC40();
      sub_18007E600("##col_lines", &xmmword_1800FAB88, 65568);
    }
    sub_180071070((__int64)"Custom Box Color##chk_col_box", &byte_1800FABBC);
    if ( byte_1800FABBC )
    {
      sub_18004AC40();
      sub_18007E600("##col_box", &xmmword_1800FABAC, 65568);
    }
    v1 = qword_18010C470;
    *(_BYTE *)(*(_QWORD *)(qword_18010C470 + 5216) + 206LL) = 1;
    if ( !*(_BYTE *)(*(_QWORD *)(v1 + 5216) + 209LL) )
    {
      v5 = 0;
      sub_18004AAD0(&v5);
    }
    v5 = 0x41D00000BF800000LL;
    sub_18006FED0((__int64)"Reset Colors to Default##rst_esp_colors", &v5);
    if ( v2 )
    {
      *(__m128i *)((char *)&xmmword_1800FAB48 + 8) = _mm_load_si128((const __m128i *)&xmmword_1800E69A0);
      *(__m128i *)((char *)&xmmword_1800FAB68 + 8) = _mm_load_si128((const __m128i *)&xmmword_1800E69B0);
      *(__m128i *)((char *)&xmmword_1800FAB58 + 8) = _mm_load_si128((const __m128i *)&xmmword_1800E6990);
      *(__m128i *)((char *)&xmmword_1800FAB9C + 4) = _mm_load_si128((const __m128i *)&xmmword_1800E6AF0);
      *(_QWORD *)&xmmword_1800FAB48 = 0x3E75C28F3F6B851FLL;
      *(__m128i *)((char *)&xmmword_1800FAB78 + 8) = _mm_load_si128((const __m128i *)&xmmword_1800E6B10);
      *((_QWORD *)&xmmword_1800FAB88 + 1) = 0x3F4CCCCD3F800000LL;
      LODWORD(xmmword_1800FAB9C) = 1065353216;
      *(_QWORD *)((char *)&xmmword_1800FABAC + 4) = 0x3F8000003F800000LL;
      HIDWORD(xmmword_1800FABAC) = 1063675494;
      byte_1800FAB98 = 0;
      byte_1800FABBC = 0;
    }
    sub_180071F50();
    sub_180003890((__int64)"Max Distance##esp_maxdist", (int)&dword_1800FAB44, 10.0, 2000.0, "%.0f m", v4);
  }
  return sub_180003370();
}
