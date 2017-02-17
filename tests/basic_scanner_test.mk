include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk
include $(MTOP)/ctest.mk

EXE     := basic_scanner_test
SRC     := basic_scanner_test.c
INCLUDE := ..
RPATH   := $(LIB_DIR)

ifndef NO_STATIC
LIBS    := gtparser
else ifndef NO_SHARED
DLLS    := gtparser
DEFINES := GTPARSER_EXPORTS=$(DLL_IMPORTS_DEFINE)
else
$(error cannot link gtparser library for tests)
endif

SHLIBS := $(DLLS:=.$(call ver_major,$(PRODUCT_VER)))
$(call TEST_NEED_SIMLINKS,$(SHLIBS))
$(call DO_TEST_EXE,$(SHLIBS))

$(DEFINE_TARGETS)
