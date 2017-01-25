include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk
LIB     := parser_err
SRC     := parser_err.c
$(DEFINE_TARGETS)
