#include <stdint.h>
#include "params.h"
#include "sign.h"
#include "packing.h"
#include "polyvec.h"
#include "poly.h"
#include "randombytes.h"
#include "symmetric.h"
#include "smallpoly.h"
/* #include "fips202.h" */
/* #include "fips202.c" */

/*************************************************
* Name:        crypto_sign_keypair
*
* Description: Generates public and private key.
*
* Arguments:   - uint8_t *pk: pointer to output public key (allocated
*                             array of CRYPTO_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key (allocated
*                             array of CRYPTO_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int crypto_sign_keypair(uint8_t *pk, uint8_t *sk) {
  uint8_t seedbuf[2*SEEDBYTES + CRHBYTES];
  uint8_t tr[TRBYTES];
  const uint8_t *rho, *rhoprime, *key;
  polyvecl mat[K];
  polyvecl s1, s1hat;
  polyveck s2, t1, t0;

  /* Get randomness for rho, rhoprime and key */
  //randombytes(seedbuf, SEEDBYTES);
  char seedbufcha[2*(2*SEEDBYTES+CRHBYTES)] ="E99CB21815AA2F4A54759D507C2E5B4B0DDB0B78A179FEBB90E13C1ACAC329431FDB456AD904F9B2DD76E7501DCBB52E779525B566D767DF08301BE9637D2C77F872434B0F8E8A3B11F9B79ADD7BA0B66DC737A56DBC33C84A66B07247D52EC44B7F2E8D1C9A5F3D2B6E4C7D1F2A3B5C9D6E8F3D8E2F5A9B7C4D1E6F3A2B8C5D";
	uint8_t cacheintsk[6*SEEDBYTES];
	for (int i = 0; i <2 * SEEDBYTES; i++)
	{
		if (seedbufcha[i] - 'A' >= 0)
			cacheintsk[i] = 10 + seedbufcha[i] - 'A';
		else
			cacheintsk[i] = seedbufcha[i] - '0';
	}
	for (int i = 0; i < SEEDBYTES; i++)
		seedbuf[i] = cacheintsk[2*i] * 16 + cacheintsk[2*i + 1];
  
  //
  shake256(seedbuf, 2*SEEDBYTES + CRHBYTES, seedbuf, SEEDBYTES);
  rho = seedbuf;
  rhoprime = rho + SEEDBYTES;
  key = rhoprime + CRHBYTES;

  /* Expand matrix */
  polyvec_matrix_expand(mat, rho);

  /* Sample short vectors s1 and s2 */
  polyvecl_uniform_eta(&s1, rhoprime, 0);
  polyveck_uniform_eta(&s2, rhoprime, L);

  /* Matrix-vector multiplication */
  s1hat = s1;
  polyvecl_ntt(&s1hat);
  polyvec_matrix_pointwise_montgomery(&t1, mat, &s1hat);
  polyveck_reduce(&t1);
  polyveck_invntt_tomont(&t1);

  /* Add error vector s2 */
  polyveck_add(&t1, &t1, &s2);

  /* Extract t1 and write public key */
  polyveck_caddq(&t1);
  polyveck_power2round(&t1, &t0, &t1);
  pack_pk(pk, rho, &t1);

  /* Compute H(rho, t1) and write secret key */
  shake256(tr, TRBYTES, pk, CRYPTO_PUBLICKEYBYTES);
  pack_sk(sk, rho, tr, key, &t0, &s1, &s2);

  return 0;
}
void test_fun(uint8_t *p){
	uint8_t buf[136];
	size_t len=136;
	
	uint64_t s_inc[26];
	s_inc[25]=0;
	s_inc[0]=0xffffffffffffffff;
	s_inc[1]=0xffffffffffffffff;
	s_inc[2]=0xffffffffffffffff;
	s_inc[3]=0xffffffffffffffff;
	s_inc[4]=0xffffffffffffffff;
	s_inc[5]=0xffffffffffffffff;
	s_inc[6]=0xffffffffffffffff;
	s_inc[7]=0xffffffffffffffff;
	s_inc[8]=0xffffffffffffffff;
	s_inc[9]=0xffffffffffffffff;
	s_inc[10]=0xffffffffffffffff;
	s_inc[11]=0xffffffffffffffff;
	s_inc[12]=0xffffffffffffffff;
	s_inc[13]=0xffffffffffffffff;
	s_inc[14]=0xffffffffffffffff;
	s_inc[15]=0xffffffffffffffff;
	s_inc[16]=0xffffffffffffffff;
	s_inc[17]=0xffffffffffffffff;
	s_inc[18]=0xffffffffffffffff;
	s_inc[19]=0xffffffffffffffff;
	s_inc[20]=0xffffffffffffffff;
	s_inc[21]=0xffffffffffffffff;
	s_inc[22]=0xffffffffffffffff;
	s_inc[23]=0xffffffffffffffff;
	s_inc[24]=0xffffffffffffffff;
	trigger_high();
	/* uint8_t outlen=137
	if(outlen < 136)
    {
           len = outlen;
    }
    else
    {
          len = 136;
    } */
	KeccakF1600_StateExtractBytes(s_inc, buf, 0, len);
	trigger_low();
	
	p[0]= buf[0];
	p[1]= buf[1];
	p[2]= buf[2];
	p[3]= buf[3];
	p[4]= buf[4];
	p[5]= buf[5];
	p[6]= buf[6];
	p[7]= buf[7];
}


void test_fun2(uint8_t *p){
	stream256_state state;
	uint8_t buf[136*136],seed[64];
	size_t len=136;
	seed[0]=17;
	seed[10]=17;
	seed[20]=17;
	seed[30]=17;
	seed[50]=17;
	seed[17]=17;
	
	for(int i=0; i < 64;i++)
		seed[i] = 17;
	/* uint64_t s_inc[26]; */
	stream256_init(&state, seed, 0);
	buf[0]=17;
	buf[1]=17;
	buf[2]=17;
	buf[3]=17;
	buf[4]=17;
	buf[5]=17;
	buf[6]=17;
	buf[7]=17;
	for(int ii=0; ii < 136 ;ii++){
		buf[ii] = 17;
	}
	trigger_high();
	stream256_squeezeblocks(buf,136,&state);
	trigger_low();
	
	for(int kk=0; kk < 136 ;kk++)
		p[kk] = buf[kk];
}


void test_fun3(uint8_t *p,uint8_t *seed){
	stream256_state state;
	uint8_t buf[136*136];
	size_t len=136;
	
	

	stream256_init(&state, seed, 0);
	
	for(int ii=0; ii < 136 ;ii++){
		buf[ii] = 17;
	}
	trigger_high();
	stream256_squeezeblocks(buf,136,&state);
	trigger_low();
	
	for(int kk=0; kk < 136 ;kk++)
		p[kk] = buf[kk];
}
/*************************************************
* Name:        crypto_sign_signature
*
* Description: Computes signature.
*
* Arguments:   - uint8_t *sig:   pointer to output signature (of length CRYPTO_BYTES)
*              - size_t *siglen: pointer to output length of signature
*              - uint8_t *m:     pointer to message to be signed
*              - size_t mlen:    length of message
*              - uint8_t *sk:    pointer to bit-packed secret key
*
* Returns 0 (success)
**************************************************/
int crypto_sign_signature(uint8_t *sig,
                          size_t *siglen,
                          const uint8_t *m,
                          size_t mlen,
                          const uint8_t *sk,uint8_t *p)
{
  uint8_t seedbuf[2 * SEEDBYTES + TRBYTES + RNDBYTES + 2 * CRHBYTES];
  uint8_t *rho, *tr, *key, *mu, *rhoprime, *rnd;
  uint16_t nonce = 0;
  unsigned int n;
  polyvecl mat[K], y, z;
  polyveck t0, w1, w0;
  poly cp;
  shake256incctx state;

  smallpoly s1_prime[L];
  smallpoly s2_prime[K];
  smallpoly cp_small;
  smallhalfpoly cp_small_prime;

  rho = seedbuf;
  tr = rho + SEEDBYTES;
  key = tr + TRBYTES;
  rnd = key + SEEDBYTES;
  mu = rnd + RNDBYTES;
  rhoprime = mu + CRHBYTES;
  unpack_sk(rho, tr, key, &t0, s1_prime, s2_prime, sk);

  /* Compute mu = CRH(tr, msg) */
  shake256_inc_init(&state);
  shake256_inc_absorb(&state, tr, TRBYTES);
  shake256_inc_absorb(&state, m, mlen);
  shake256_inc_finalize(&state);
  shake256_inc_squeeze(mu, CRHBYTES, &state);

  for (n = 0; n < RNDBYTES; n++) {
     rnd[n] = 0;
  }
  
  shake256(rhoprime, CRHBYTES, key, SEEDBYTES + RNDBYTES + CRHBYTES);
  
  /* Expand matrix and transform vectors */
  polyvec_matrix_expand(mat, rho);
  polyvecl_small_ntt(s1_prime);
  polyveck_small_ntt(s2_prime);

  polyveck_ntt(&t0);

rej:
  /* Sample intermediate vector y */
  //trigger_high();
  polyvecl_uniform_gamma1(&y, rhoprime, nonce++);
  //trigger_low();
  /* Matrix-vector multiplication */
  z = y;
  polyvecl_ntt(&z);
  polyvec_matrix_pointwise_montgomery(&w1, mat, &z);
  polyveck_reduce(&w1);
  polyveck_invntt_tomont(&w1);

  /* Decompose w and call the random oracle */
  polyveck_caddq(&w1);
  polyveck_decompose(&w1, &w0, &w1);
  polyveck_pack_w1(sig, &w1);

  shake256_inc_init(&state);
  shake256_inc_absorb(&state, mu, CRHBYTES);
  shake256_inc_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
  shake256_inc_finalize(&state);
  shake256_inc_squeeze(sig, CTILDEBYTES, &state);
  poly_challenge(&cp, sig);
  
  poly_small_ntt_precomp(&cp_small, &cp_small_prime, &cp);
  poly_ntt(&cp);

  /* Compute z, reject if it reveals secret */
  polyvecl_small_basemul_invntt(&z, &cp_small, &cp_small_prime, s1_prime);

  polyvecl_add(&z, &z, &y);
  polyvecl_reduce(&z);
  if(polyvecl_chknorm(&z, GAMMA1 - BETA))
    goto rej;


  /* Write signature */
  pack_sig_z(sig, &z);
  unsigned int hint_n = 0;
  unsigned int hints_written = 0;
  /* Check that subtracting cs2 does not change high bits of w and low bits
   * do not reveal secret information */
  for(unsigned int i = 0; i < K; ++i) {
    poly *tmp = &z.vec[0];
    poly_small_basemul_invntt(tmp, &cp_small, &cp_small_prime, &s2_prime[i]);

    poly_sub(&w0.vec[i], &w0.vec[i], tmp);
    poly_reduce(&w0.vec[i]);
    if(poly_chknorm(&w0.vec[i], GAMMA2 - BETA))
      goto rej;

    /* Compute hints for w1 */
    poly_pointwise_montgomery(tmp, &cp, &t0.vec[i]);

    poly_invntt_tomont(tmp);
    poly_reduce(tmp);

    if(poly_chknorm(tmp, GAMMA2))
      goto rej;
    poly_add(&w0.vec[i], &w0.vec[i], tmp);
    hint_n += poly_make_hint(tmp, &w0.vec[i], &w1.vec[i]);
    if (hint_n > OMEGA) {
      goto rej;
    }
    pack_sig_h(sig, tmp, i, &hints_written);
  }
  pack_sig_h_zero(sig, &hints_written);
  *siglen = CRYPTO_BYTES;
  return 0;
}

/*************************************************
* Name:        crypto_sign
*
* Description: Compute signed message.
*
* Arguments:   - uint8_t *sm: pointer to output signed message (allocated
*                             array with CRYPTO_BYTES + mlen bytes),
*                             can be equal to m
*              - size_t *smlen: pointer to output length of signed
*                               message
*              - const uint8_t *m: pointer to message to be signed
*              - size_t mlen: length of message
*              - const uint8_t *sk: pointer to bit-packed secret key
*
* Returns 0 (success)
**************************************************/
int crypto_sign(uint8_t *sm,
                size_t *smlen,
                const uint8_t *m,
                size_t mlen,
                const uint8_t *sk,uint8_t *p)
{
  size_t i;

  for(i = 0; i < mlen; ++i)
    sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
  crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, sk,p);
  *smlen += mlen;
  return 0;
}

/*************************************************
* Name:        crypto_sign_verify
*
* Description: Verifies signature.
*
* Arguments:   - uint8_t *m: pointer to input signature
*              - size_t siglen: length of signature
*              - const uint8_t *m: pointer to message
*              - size_t mlen: length of message
*              - const uint8_t *pk: pointer to bit-packed public key
*
* Returns 0 if signature could be verified correctly and -1 otherwise
**************************************************/
int crypto_sign_verify(const uint8_t *sig,
                       size_t siglen,
                       const uint8_t *m,
                       size_t mlen,
                       const uint8_t *pk)
{
  unsigned int i;
  uint8_t buf[K*POLYW1_PACKEDBYTES];
  uint8_t rho[SEEDBYTES];
  uint8_t mu[CRHBYTES];
  uint8_t c[CTILDEBYTES];
  uint8_t c2[CTILDEBYTES];
  poly cp;
  polyvecl mat[K], z;
  polyveck t1, w1, h;
  shake256incctx state;

  if(siglen != CRYPTO_BYTES)
    return -1;

  unpack_pk(rho, &t1, pk);
  if(unpack_sig(c, &z, &h, sig))
    return -1;
  if(polyvecl_chknorm(&z, GAMMA1 - BETA))
    return -1;

  /* Compute CRH(h(rho, t1), msg) */
  shake256(mu, CRHBYTES, pk, CRYPTO_PUBLICKEYBYTES);
  shake256_inc_init(&state);
  shake256_inc_absorb(&state, mu, CRHBYTES);
  shake256_inc_absorb(&state, m, mlen);
  shake256_inc_finalize(&state);
  shake256_inc_squeeze(mu, CRHBYTES, &state);

  /* Matrix-vector multiplication; compute Az - c2^dt1 */
  poly_challenge(&cp, c);
  polyvec_matrix_expand(mat, rho);

  polyvecl_ntt(&z);
  polyvec_matrix_pointwise_montgomery(&w1, mat, &z);

  poly_ntt(&cp);
  polyveck_shiftl(&t1);
  polyveck_ntt(&t1);
  polyveck_pointwise_poly_montgomery(&t1, &cp, &t1);

  polyveck_sub(&w1, &w1, &t1);
  polyveck_reduce(&w1);
  polyveck_invntt_tomont(&w1);

  /* Reconstruct w1 */
  polyveck_caddq(&w1);
  polyveck_use_hint(&w1, &w1, &h);
  polyveck_pack_w1(buf, &w1);

  /* Call random oracle and verify challenge */
  shake256_inc_init(&state);
  shake256_inc_absorb(&state, mu, CRHBYTES);
  shake256_inc_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
  shake256_inc_finalize(&state);
  shake256_inc_squeeze(c2, CTILDEBYTES, &state);
  for(i = 0; i < CTILDEBYTES; ++i)
    if(c[i] != c2[i])
      return -1;

  return 0;
}

/*************************************************
* Name:        crypto_sign_open
*
* Description: Verify signed message.
*
* Arguments:   - uint8_t *m: pointer to output message (allocated
*                            array with smlen bytes), can be equal to sm
*              - size_t *mlen: pointer to output length of message
*              - const uint8_t *sm: pointer to signed message
*              - size_t smlen: length of signed message
*              - const uint8_t *pk: pointer to bit-packed public key
*
* Returns 0 if signed message could be verified correctly and -1 otherwise
**************************************************/
int crypto_sign_open(uint8_t *m,
                     size_t *mlen,
                     const uint8_t *sm,
                     size_t smlen,
                     const uint8_t *pk)
{
  size_t i;

  if(smlen < CRYPTO_BYTES)
    goto badsig;

  *mlen = smlen - CRYPTO_BYTES;
  if(crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, pk))
    goto badsig;
  else {
    /* All good, copy msg, return 0 */
    for(i = 0; i < *mlen; ++i)
      m[i] = sm[CRYPTO_BYTES + i];
    return 0;
  }

badsig:
  /* Signature verification failed */
  *mlen = -1;
  for(i = 0; i < smlen; ++i)
    m[i] = 0;

  return -1;
}
