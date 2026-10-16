LPVOID *sub_180003E20()
{
  if ( dword_18010C930 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)TlsIndex)
                                   + 4LL) )
  {
    sub_1800930B0(&dword_18010C930);
    if ( dword_18010C930 == -1 )
    {
      sub_180092FC0(sub_1800BB650);
      sub_180093040(&dword_18010C930);
    }
  }
  return &lpMem;
}
