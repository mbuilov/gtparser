include $(dir $(lastword $(MAKEFILE_LIST)))top.mk
include $(MTOP)/c.mk

LIB     := parser_base
SRC     := parser_base.c
LIBVER  := 1

ifeq (LINUX,$(OS))

include $(MTOP)/LINUX/pc.mk
include $(MTOP)/LINUX/la.mk

define PC_DESC
basic text parsing utilities library
endef

define PC_COMMENT
Author:  $(VENDOR_NAME)
License: LGPL version 2.1 or any later version
endef

$(call PKGCONFIG_RULE,$(LIB),$(LIBVER),$(PC_DESC),$(PC_COMMENT),$(VENDOR_URL))
$(call LIBTOOL_LA_RULE,,$(LIBVER),$(LIB))

endif # LINUX

$(DEFINE_TARGETS)
