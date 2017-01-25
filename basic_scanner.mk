include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk
LIB     := basic_scanner
SRC     := name_scanner.c int_scanner.c
$(DEFINE_TARGETS)
