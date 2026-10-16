// sub_1800A478C size=100
int __fastcall sub_1800A478C(unsigned int a1)
{
  FARPROC CorExitProcess; // rax
  HMODULE v3; // rcx
  HMODULE phModule; // [rsp+48h] [rbp+10h] BYREF

  phModule = nullptr;
  LODWORD(CorExitProcess) = GetModuleHandleExW(0, L"mscoree.dll", &phModule);
  v3 = phModule;
  if ( (_DWORD)CorExitProcess )
  {
    CorExitProcess = GetProcAddress(phModule, "CorExitProcess");
    if ( CorExitProcess )
      LODWORD(CorExitProcess) = ((__int64 (__fastcall *)(_QWORD))CorExitProcess)(a1);
    v3 = phModule;
  }
  if ( v3 )
    LODWORD(CorExitProcess) = FreeLibrary(v3);
  return (int)CorExitProcess;
}
