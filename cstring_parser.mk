include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk
LIB     := cstring_parser
SRC     := cstring_parser.c
$(DEFINE_TARGETS)
