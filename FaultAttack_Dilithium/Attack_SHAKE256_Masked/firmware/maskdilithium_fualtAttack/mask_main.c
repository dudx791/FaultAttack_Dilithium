#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "api.h"
#include "params.h"
#include "config.h"
#include "masking_interface.h"
#include "fips202.h"

uint8_t mask_hash(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* p)
{

  size_t mlen = 33;
  uint8_t seed_y[64*N_SHARES];
  uint8_t in[(SEEDBYTES+CRHBYTES)*N_SHARES];
  uint8_t masked_key[SEEDBYTES*N_SHARES];
  
  //給消息賦值
	uint8_t m[33];
	for(int ii=0; ii < 33;ii++)
		m[ii] =p[ii];
	
	
	//固定賦值給masked_key
	for(int ii=0; ii < 96;ii++)
		masked_key[ii] =p[85+ii];
  
  
  //給tr賦值
	uint8_t tr[48];
	for(int ii=0; ii < 48;ii++)
		tr[ii] =p[35+ii];
  
  
  //計算mu
  keccak_state state;
  uint8_t mu[48];
  shake256_init(&state);
  shake256_absorb(&state, tr, CRHBYTES);
  shake256_absorb(&state, m, mlen);
  shake256_finalize(&state);
  shake256_squeeze(mu, CRHBYTES, &state);
  
  
  for(int i=0; i < SEEDBYTES; ++i){
    for(int j=0; j < N_SHARES; ++j){
      in[i + (SEEDBYTES+CRHBYTES)*j] = masked_key[i + (SEEDBYTES)*j]; 
    }
  }

  for(int i=SEEDBYTES; i < SEEDBYTES+CRHBYTES; ++i){
    in[i] = mu[i-SEEDBYTES];
    for(int j=1; j < N_SHARES; ++j){
      in[i + (SEEDBYTES+CRHBYTES)*j] = 0; 
    }
  }
  trigger_high();
  shake256_masked(seed_y, 64, in, SEEDBYTES+CRHBYTES);
  trigger_low();
  //清零p
  for(int ii=0; ii < 180;ii++)
	  p[ii] = 0;
  
  //輸出結果放入p數組中
  for(int ii=0; ii < 180 ;ii++)
	  p[ii] = seed_y[ii];

	/* for(int ii=0; ii < 33 ;ii++)
	  p[ii] = m[ii];

	for(int ii=0; ii < 48 ;ii++)
	  p[35+ii] = tr[ii];
  
    for(int ii=0; ii < 96 ;ii++)
	  p[83+ii] = masked_key[ii]; */
  simpleserial_put('r', 180, p);
   return 0x00;
}



int main(void){

    platform_init();
    init_uart();

    trigger_setup();
    
    /* Device reset detected */
    putch('r');
    putch('R');
    putch('E');
    putch('S');
    putch('E');
    putch('T');
    putch(' ');
    putch(' ');
    putch(' ');
    putch('\n');
    
    simpleserial_init();
	
	simpleserial_addcmd('3', 183, mask_hash);
	
	while(1)
        simpleserial_get();
    
}