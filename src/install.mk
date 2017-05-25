include $(dir $(lastword $(MAKEFILE_LIST)))../project.mk
include $(MTOP)/defs.mk
include $(MTOP)/exts/install_lib.mk

DLL := $(if $(NO_SHARED),,$(GTPARSER_LIB_NAME) $(GTPARSER_DLL_VARIANTS))
LIB := $(if $(NO_STATIC),,$(GTPARSER_LIB_NAME) $(GTPARSER_LIB_VARIANTS))

DEFINES:=

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
GTPARSER_PC_GENERATOR = $(call PKGCONF_DEF_TEMPLATE,$1,$(if \
 ,)$(PRODUCT_VER),$(if \
 ,)$(PRODUCT_NAME),$(if \
 ,)$(GTPARSER_PC_COMMENT),$(if \
 ,)$(VENDOR_URL)$(if \
 ,),,,,$(addprefix -D,$(DEFINES))$(call VARIANT_CFLAGS,$2))

LIBRARY_PC_GEN := GTPARSER_PC_GENERATOR

$(call INSTALL_LIBS_TEMPLATE,gtparser)

$(DEFINE_TARGETS)
