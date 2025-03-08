# Hey Emacs, this is a -*- makefile -*-

TARGET = maskmain
#LIB=libdilithium2_clean.a
# List C source files here.
# Header files (.h) are automatically pulled in. 
SRC += mask_main.c 

SOURCES = fips202.c masked_fips202.c masking_interface.c 
HEADERS = fips202.h api.h config.h masking_interface.h
KECCAK_SOURCES = $(SOURCES) 

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





