include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk
include $(MTOP)/ctest.mk
EXE     := basic_scanner_test
LIBS    := gtparser
SRC     := basic_scanner_test.c
INCLUDE := ..
$(DO_TEST_EXE)
$(DEFINE_TARGETS)
