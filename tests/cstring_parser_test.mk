include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk
include $(MTOP)/ctest.mk
EXE     := cstring_parser_test
LIBS    := cstring_parser
SRC     := cstring_parser_test.c
INCLUDE := ..
$(DO_TEST_EXE)
$(DEFINE_TARGETS)
