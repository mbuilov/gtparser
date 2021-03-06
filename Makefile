include $(dir $(lastword $(MAKEFILE_LIST)))project.mk
include $(MTOP)/parallel.mk

ifeq (,$(filter distclean,$(MAKECMDGOALS)))

TO_MAKE := src

ifeq (WINXX,$(OS))
TO_MAKE += $(MTOP)/exts/version
endif

ifneq (,$(filter check tests clean,$(MAKECMDGOALS)))
TO_MAKE += tests
endif

$(call PROCESS_SUBMAKES,$(TO_MAKE))

endif # !distclean
