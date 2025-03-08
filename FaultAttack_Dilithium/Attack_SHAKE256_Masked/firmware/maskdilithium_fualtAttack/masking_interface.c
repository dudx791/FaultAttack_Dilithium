#include "masking_interface.h"
//#include "dilithium_gadgets.h"
#include "params.h"
//#include "polyvec.h"
#include "fips202.h"





int32_t canon_to_centered(uint32_t x){
  int32_t res = (int32_t) x;
  if (res >= Q/2) res -= Q;
  return res;
}

int32_t center(int32_t x){
  /* Maps elements of Z_q in [-Q, ..., Q] to representatives in [-Q/2, ..., Q/2[ */
  x += Q;
  x %= Q;
  if (x > Q/2) x -= Q;
  return x;
}

uint32_t center_to_canon(int32_t x){
  /* Maps elements of Z_q in [-Q/2, ..., Q/2[ to representatives in  [0, ..., Q[*/
  if (x < 0) x += Q; 
  return x;
}


