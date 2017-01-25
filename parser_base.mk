include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk
LIB     := parser_base
SRC     := parser_base.c
$(DEFINE_TARGETS)
