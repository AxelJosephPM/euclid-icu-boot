#ifndef ISOCHECK_H_INCLUDED
#define ISOCHECK_H_INCLUDED

#include "user_types.h"

u16 calculate_iso_checksum(const u8 data_octets[], const u32 number_of_octets);


#endif // ISOCHECK_H_INCLUDED
