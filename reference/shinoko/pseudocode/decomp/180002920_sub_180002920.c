// sub_180002920 size=62
__int64 __fastcall sub_180002920(__int64 a1, int a2)
{
  if ( a2 == 1 )
  {
    sub_180029000("=== DllMain: DLL_PROCESS_ATTACH ===");
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)StartAddress, nullptr, 0, nullptr);
  }
  return 1;
}
