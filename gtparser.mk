include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk
DLL     := gtparser
SRC     := parser_base.c parser_err.c name_scanner.c int_scanner.c cstring_parser.c
SOVER   := 1
DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)
$(DEFINE_TARGETS)
