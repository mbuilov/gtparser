include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
GTPARSER_TEST_SRC := cstring_parser_test.c
include $(TOP)/tests/test_frm.mk
