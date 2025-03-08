#ifndef MASKING_INTERFACE_H
#define MASKING_INTERFACE_H

#ifndef MASKING_ORDER
#define MASKING_ORDER 2
#endif
#define N_SHARES (MASKING_ORDER + 1)

#include <stdint.h>
#include "fips202.h"

#define FAST
//#define MLDSA_Y





int32_t canon_to_centered(uint32_t x);
int32_t center(int32_t x);



#endif
