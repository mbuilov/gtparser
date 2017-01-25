include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/defs.mk

ifneq ($(filter distclean,$(MAKECMDGOALS)),)
distclean:
	$(call RM,$(CLOBBER_DIRS))
else

TO_MAKE := parser_base.mk parser_err.mk basic_scanner.mk cstring_parser.mk gtparser.mk

ifneq ($(filter WINXX,$(OS)),)
TO_MAKE += version
endif

ifneq ($(filter check tests,$(MAKECMDGOALS)),)
check tests: all
TO_MAKE += tests
endif

include $(MTOP)/parallel.mk

endif # !distclean
