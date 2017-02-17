include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk
include $(MTOP)/ctest.mk

EXE     := cstring_parser_test
SRC     := cstring_parser_test.c
INCLUDE := ..
RPATH   := $(LIB_DIR)

ifndef NO_STATIC
LIBS    := gtparser
else ifndef NO_SHARED
DLLS    := gtparser
else
$(error cannot link gtparser library for tests)
endif

SHLIBS := $(DLLS:=.$(call ver_major,$(PRODUCT_VER)))
$(call TEST_NEED_SIMLINKS,$(SHLIBS))
$(call DO_TEST_EXE,$(SHLIBS))

$(DEFINE_TARGETS)
