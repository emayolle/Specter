// sub_1800B72E0 size=508
// local variable allocation has failed, the output may be wrong!
__m128 __fastcall sub_1800B72E0(__int64 _RCX, __int64 a2, __int64 a3, double _XMM3_8)
{
  __m128 result; // xmm0
  __int64 v6; // rdx
  int v51; // [rsp+30h] [rbp-38h]
  int v52; // [rsp+38h] [rbp-30h]

  __asm { vmovd   ecx, xmm0 }
  v6 = (unsigned __int8)((unsigned int)_RCX >> 23);
  __asm
  {
    vmovaps xmm4, xmm0
    vxorps  xmm3, xmm3, xmm3
  }
  if ( ((unsigned int)_RCX & 0x7FFFFFFF) <= 0x7F800000 )
  {
    if ( (unsigned int)v6 >= 0x65 )
    {
      if ( (unsigned int)v6 < 0x7F )
      {
        __asm { vmovaps [rsp+68h+var_18], xmm6 }
        if ( (int)_RCX >= 0 )
          __asm { vmovaps xmm2, xmm4 }
        else
          __asm { vxorps  xmm2, xmm4, cs:xmmword_1800E6B90 }
        if ( (unsigned int)v6 < 0x7E )
        {
          __asm { vmulss  xmm5, xmm2, xmm2 }
        }
        else
        {
          __asm
          {
            vmovss  xmm0, cs:dword_1800DB2F8
            vsubss  xmm1, xmm0, xmm2
            vmulss  xmm5, xmm1, cs:dword_1800DB2C0
            vmovaps xmm2, xmm5
            vsqrtss xmm3, xmm2, xmm5
            vmovaps xmm2, xmm3
          }
        }
        __asm
        {
          vmovss  xmm0, cs:dword_1800E6BB8
          vfnmadd213ss xmm0, xmm5, cs:dword_1800E6BF0
          vfmsub213ss xmm0, xmm5, cs:dword_1800E6BC8
          vfmadd213ss xmm0, xmm5, cs:dword_1800E6BCC
          vmulss  xmm1, xmm0, xmm5
          vmovss  xmm0, cs:dword_1800E6BD0
          vfnmadd213ss xmm0, xmm5, cs:dword_1800E6BD4
          vdivss  xmm6, xmm1, xmm0
        }
        if ( (unsigned int)v6 < 0x7E )
        {
          __asm
          {
            vmovsd  xmm1, cs:qword_1800E6BC0
            vmulss  xmm0, xmm6, xmm4
            vmovaps xmm6, [rsp+68h+var_18]
            vcvtss2sd xmm2, xmm0, xmm0
            vsubsd  xmm0, xmm1, xmm2
            vmovsd  xmm2, cs:qword_1800E6BE0
            vcvtss2sd xmm3, xmm4, xmm4
            vsubsd  xmm3, xmm3, xmm0
            vsubsd  xmm0, xmm2, xmm3
            vcvtsd2ss xmm0, xmm0, xmm0
          }
        }
        else if ( (int)_RCX >= 0 )
        {
          __asm { vmovd   eax, xmm3 }
          _EAX &= 0xFFFF0000;
          __asm
          {
            vmovd   xmm4, eax
            vaddss  xmm0, xmm4, xmm3
            vmovaps xmm1, xmm5
            vfnmadd231ss xmm1, xmm4, xmm4
            vdivss  xmm1, xmm1, xmm0
            vaddss  xmm3, xmm1, xmm1
            vaddss  xmm2, xmm2, xmm2
            vfmadd231ss xmm3, xmm6, xmm2
            vmovaps xmm6, [rsp+68h+var_18]
            vaddss  xmm0, xmm4, xmm4
            vaddss  xmm0, xmm3, xmm0
          }
        }
        else
        {
          __asm
          {
            vmulss  xmm0, xmm2, xmm6
            vmovaps xmm6, [rsp+68h+var_18]
            vcvtss2sd xmm1, xmm0, xmm0
            vsubsd  xmm2, xmm1, cs:qword_1800E6BC0
            vcvtss2sd xmm0, xmm3, xmm3
            vmovsd  xmm3, cs:qword_1800E6BE8
            vaddsd  xmm1, xmm2, xmm0
            vaddsd  xmm4, xmm1, xmm1
            vsubsd  xmm0, xmm3, xmm4
            vcvtsd2ss xmm0, xmm0, xmm0
          }
        }
      }
      else
      {
        __asm { vucomiss xmm4, cs:dword_1800DB2F8 }
        if ( __SETP__(v6, 127) || (_DWORD)v6 != 127 )
        {
          __asm { vucomiss xmm4, cs:dword_1800DB40C }
          if ( __SETP__(v6, 127) || (_DWORD)v6 != 127 )
          {
            __asm
            {
              vmovss  [rsp+68h+var_30], xmm3
              vmovss  [rsp+68h+var_38], xmm4
            }
            sub_1800B2F60((unsigned int)"acosf", 13, -4194304, 1, 8, 33, v51, v52, 1);
          }
          else
          {
            sub_1800B34C0(32);
            __asm { vmovss  xmm0, cs:dword_1800DB32C }
          }
        }
        else
        {
          __asm { vxorps  xmm0, xmm0, xmm0 }
        }
      }
    }
    else
    {
      sub_1800B34C0(32);
      __asm { vmovss  xmm0, cs:dword_1800E6BD8 }
    }
  }
  else
  {
    sub_1800B89B0(_RCX, v6);
  }
  return result;
}
