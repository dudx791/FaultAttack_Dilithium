# Hey Emacs, this is a -*- makefile -*-

TARGET = PQCgenKAT_sign
#LIB=libdilithium2_clean.a
# List C source files here.
# Header files (.h) are automatically pulled in. 
SRC += PQCgenKAT_sign.c 
#aes.c fips202.c nistseedexpander.c sha2.c sp800-185.c 
SOURCES = sign.c packing.c poly.c polyvec.c rounding.c symmetric-shake.c smallpoly.c fips202.c
HEADERS = config.h api.h sign.h packing.h poly.h polyvec.h params.h pointwise_mont1.h smallploy.h rounding.h symmetric.h smallntt.h vector1.h ntt1.h  fips202.h
#sendfn.h nistseedexpander.h sp800-185.h sha2.h 
   #randombytes.h randombytes.h aes.h crypto_declassify.h aes-publicinputs.h compat.h crypto_hashblocks_sha512.h fips202.h
#KECCAK_SOURCES = $(SOURCES) fips202.c symmetric-shake.c
#KECCAK_HEADERS = $(HEADERS) fips202.h
KECCAK_SOURCES = $(SOURCES)
KECCAK_HEADERS = $(HEADERS)
AES_SOURCES = $(SOURCES) 
AES_HEADERS = $(HEADERS) 
#asrc =__asm_iNTT.S __asm_NTT.S __asm_poly.S basemul_257.S fnt_257.S ifnt_257.S ntt.S pointwise_mont.s vector.s keccakf1600.S
asrc = basemul_257.S fnt_257.S ifnt_257.S ntt.S pointwise_mont123.S vector123.S keccakf1600.S
# crypto_hashblocks_sha512_inner32.s aes-publicinputs.S aes-keyschedule.S aes-encrypt.S
#HEADERS=api.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h 

SRC += $(KECCAK_SOURCES)
ASRC += $(asrc)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
EXTRA_OPTS = NO_EXTRA_OPTS
CFLAGS += -D$(EXTRA_OPTS)


ifeq ($(CRYPTO_TARGET),)
  ${info No CRYPTO_TARGET passed - defaulting to TINYAES128C}
  CRYPTO_TARGET = TINYAES128C
endif

${info Building for platform ${PLATFORM} with CRYPTO_TARGET=$(CRYPTO_TARGET)}

#Add simpleserial project to build
include ../simpleserial/Makefile.simpleserial

FIRMWAREPATH = ../.
include $(FIRMWAREPATH)/Makefile.inc