include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk

SRC     := \
  parser_base.c \
  parser_err.c \
  name_scanner.c \
  int_scanner.c \
  cstring_parser.c
INCLUDE := ..

ifndef NO_SHARED
DLL     := $(GTPARSER_LIB_NAME) $(GTPARSER_DLL_VARIANTS)
DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)
endif

$(call MAKE_CONTINUE,SRC INCLUDE)

ifndef NO_STATIC
LIB     := $(GTPARSER_LIB_NAME) $(GTPARSER_LIB_VARIANTS)
endif

$(DEFINE_TARGETS)

# installation

DLL := $(if $(NO_SHARED),,$(GTPARSER_LIB_NAME) $(GTPARSER_DLL_VARIANTS))
LIB := $(if $(NO_STATIC),,$(GTPARSER_LIB_NAME) $(GTPARSER_LIB_VARIANTS))

LIBRARY_NAME := gtparser
LIBRARY_HDIR := gtparser

LIBRARY_HEADERS := $(addprefix $(TOP)/gtparser/,\
  gtparser.h \
  char_func.h \
  cstring_parser.h \
  int_parser.h \
  int_scanner.h \
  name_parser.h \
  name_scanner.h \
  parser_base.h \
  parser_err.h)

define GTPARSER_PC_COMMENT
Author:  $(VENDOR_NAME)
License: $(PRODUCT_LICENCE)
endef

# generate contents of pkg-config .pc-file
# $1 - static or dynamic library name
# $2 - library variant
GTPARSER_PC_GENERATOR = $(call PKGCONF_DEF_TEMPLATE,$1,$(MODVER),$(PRODUCT_NAME),$(GTPARSER_PC_COMMENT),$(VENDOR_URL),,,,$(addprefix \
  -D,$(DEFINES))$(call VARIANT_CFLAGS,$2))

LIBRARY_PC_GEN := GTPARSER_PC_GENERATOR

include $(MTOP)/exts/install_lib.mk
