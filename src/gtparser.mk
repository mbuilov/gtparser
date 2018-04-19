include $(dir $(lastword $(MAKEFILE_LIST)))../project.mk
include $(MTOP)/c.mk

INCLUDE := ..
SRC     := \
  parser_base.c \
  parser_z_base.c \
  parser_err.c \
  name_scanner.c \
  int_scanner.c \
  int_scanner_w.c \
  cstring_parser.c

ifndef NO_STATIC
LIB     := $(GTPARSER_LIB_NAME) $(GTPARSER_LIB_VARIANTS)
$(call MAKE_CONTINUE,INCLUDE SRC)
endif

ifndef NO_SHARED
DLL     := $(GTPARSER_LIB_NAME) $(GTPARSER_DLL_VARIANTS)
DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)
endif

$(DEFINE_TARGETS)
