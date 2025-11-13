
#include "isocheck.h"

u16 calculate_iso_checksum(const u8 data_octets[], const u32 num_octets)
{
  u16 checksum;
  u8 C0 = 0x00;
  u8 C1 = 0x00;
  u8 CK1, CK2;

  for (u32 i = 0; i < num_octets; i++)
  {
    C0 = (C0 + data_octets[i]) % 255;
    C1 = (C1 + C0) % 255;

    CK1 = ~((C0 + C1) % 255);
    CK2 = C1;
    if (CK1 == 0)
    {
      CK1 = 0xFF;
    }
    if (CK2 == 0)
    {
      CK2 = 0xFF;
    }
  }
  checksum = (CK1 << 8) | CK2;

  return checksum;
}



