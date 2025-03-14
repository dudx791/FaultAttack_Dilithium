#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include <stdint.h>
#include "params.h"

#ifdef DILITHIUM_USE_AES

#include "aes256ctr.h"
#include "fips202.h"

typedef aes256ctr_ctx stream128_state;
typedef aes256ctr_ctx stream256_state;

#define dilithium_aes256ctr_init DILITHIUM_NAMESPACE(dilithium_aes256ctr_init)
void dilithium_aes256ctr_init(aes256ctr_ctx *state,
                              const uint8_t key[32],
                              uint16_t nonce);

#define STREAM128_BLOCKBYTES AES256CTR_BLOCKBYTES
#define STREAM256_BLOCKBYTES AES256CTR_BLOCKBYTES

#define stream128_init(STATE, SEED, NONCE) \
        dilithium_aes256ctr_init(STATE, SEED, NONCE)
#define stream128_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define stream256_init(STATE, SEED, NONCE) \
        dilithium_aes256ctr_init(STATE, SEED, NONCE)
#define stream256_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)

#else

#include "fips202.h"
typedef shake128incctx stream128_state;
typedef shake256incctx stream256_state;

#define shake256_inc_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        shake256_inc_squeeze(OUT, OUTBLOCKS*SHAKE256_RATE, STATE)

#define dilithium_shake128_stream_init DILITHIUM_NAMESPACE(dilithium_shake128_stream_init)
void dilithium_shake128_stream_init(stream128_state *state,
                                    const uint8_t seed[SEEDBYTES],
                                    uint16_t nonce);

#define dilithium_shake256_stream_init DILITHIUM_NAMESPACE(dilithium_shake256_stream_init)
void dilithium_shake256_stream_init(stream256_state *state,
                                    const uint8_t seed[CRHBYTES],
                                    uint16_t nonce);

#define STREAM128_BLOCKBYTES SHAKE128_RATE
#define STREAM256_BLOCKBYTES SHAKE256_RATE

#define stream128_init(STATE, SEED, NONCE) \
        dilithium_shake128_stream_init(STATE, SEED, NONCE)
#define stream128_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        shake128_inc_squeeze(OUT, OUTBLOCKS*SHAKE128_RATE, STATE)
#define stream256_init(STATE, SEED, NONCE) \
        dilithium_shake256_stream_init(STATE, SEED, NONCE)
#define stream256_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        shake256_inc_squeeze(OUT, OUTBLOCKS*SHAKE256_RATE, STATE)
#define stream256_squeezeblocks1(OUT, OUTBLOCKS, STATE) \
        shake256_inc_squeeze1(OUT, OUTBLOCKS*SHAKE256_RATE, STATE)
#endif

#endif
