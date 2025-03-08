# Hey Emacs, this is a -*- makefile -*-

TARGET = PQCgenKAT_sign
#LIB=libdilithium2_clean.a
# List C source files here.
# Header files (.h) are automatically pulled in. 
SRC += PQCgenKAT_sign.c 

SOURCES = sign.c packing.c poly.c polyvec.c rounding.c symmetric-shake.c aes.c fips202.c nistseedexpander.c sha2.c sp800-185.c reduce.c ntt.c
HEADERS = config.h api.h sign.h packing.h poly.h polyvec.h ntt.h params.h pointwise_mont.h sendfn.h nistseedexpander.h sp800-185.h sha2.h\
  reduce.h rounding.h symmetric.h randombytes.h smallntt.h vector.h randombytes.h aes.h crypto_declassify.h aes-publicinputs.h compat.h crypto_hashblocks_sha512.h fips202.h
KECCAK_SOURCES = $(SOURCES) fips202.c symmetric-shake.c
KECCAK_HEADERS = $(HEADERS) fips202.h
AES_SOURCES = $(SOURCES) 
AES_HEADERS = $(HEADERS) 

HEADERS=api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h 

SRC += $(KECCAK_SOURCES)


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





