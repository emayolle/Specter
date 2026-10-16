__int64 sub_180029000(const char *a1, ...)
{
  int v1; // eax
  CHAR *v2; // rbx
  int v3; // edi
  _DWORD *v4; // rax
  unsigned __int64 v5; // rax
  __int64 v7; // [rsp+40h] [rbp-C0h] BYREF
  struct _SYSTEMTIME SystemTime; // [rsp+48h] [rbp-B8h] BYREF
  CHAR Buffer[272]; // [rsp+60h] [rbp-A0h] BYREF
  CHAR OutputString[1056]; // [rsp+170h] [rbp+70h] BYREF
  int v11; // [rsp+5A0h] [rbp+4A0h]
  va_list va; // [rsp+5A8h] [rbp+4A8h] BYREF

  va_start(va, a1);
  v11 = (int)a1;
  GetLocalTime(&SystemTime);
  v1 = sub_1800229B0(
         OutputString,
         1024,
         "[Shinoko][%02d:%02d:%02d.%03d] ",
         SystemTime.wHour,
         SystemTime.wMinute,
         SystemTime.wSecond,
         SystemTime.wMilliseconds);
  v2 = &OutputString[v1];
  v3 = 1022 - v1;
  v4 = (_DWORD *)sub_180002960();
  sub_18009C09C(*v4 | 2, (_DWORD)v2, v3, v11, 0, (__int64)va);
  v5 = sub_1800B9730(OutputString);
  if ( v5 < 0x3FE )
    *(_WORD *)&OutputString[v5] = 10;
  OutputDebugStringA(OutputString);
  if ( (unsigned int)sub_18008E8C0(&unk_1800FAAD0) )
    sub_18008EE80(5);
  if ( dword_1800FAB1C == 0x7FFFFFFF )
  {
    dword_1800FAB1C = 2147483646;
    sub_18008EE80(6);
  }
  v7 = 0;
  sub_18009CE20(&v7, "C:\\Shinoko\\ShinokoTemplateAniimo\\debug.log", "a");
  if ( v7 )
    goto LABEL_9;
  if ( GetTempPathA(0x104u, Buffer) )
  {
    sub_18009D0F0(Buffer, 260, "shinoko_debug.log");
    sub_18009CE20(&v7, Buffer, "a");
  }
  if ( v7 )
  {
LABEL_9:
    sub_18009CF3C(OutputString);
    sub_18009C934(v7);
    sub_18009CAC0(v7);
  }
  return sub_18008E9E0(&unk_1800FAAD0);
}
