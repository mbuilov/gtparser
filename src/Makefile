include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk

LIB     := gtparser
DLL     := gtparser
SRC     := parser_base.c parser_err.c name_scanner.c int_scanner.c cstring_parser.c
INCLUDE := ..
SOVER   := 1
DLL_DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)

ifeq (LINUX,$(OS))

include $(MTOP)/LINUX/pc.mk
include $(MTOP)/LINUX/la.mk

define PC_DESC
Generic Text parsing functions library
endef

define PC_COMMENT
Author:  $(VENDOR_NAME)
License: LGPL version 2.1 or any later version
endef

PC_CFLAGS := -I$${includedir}/gtparser

$(call PKGCONFIG_RULE,$(DLL),$(SOVER),$(PC_DESC),$(PC_COMMENT),$(VENDOR_URL))
$(call LIBTOOL_LA_RULE,$(DLL),$(SOVER),$(LIB))

endif # LINUX

$(DEFINE_TARGETS)

ifeq (LINUX,$(OS))

install_libgtparser uninstall_libgtparser: all
install_libgtparser uninstall_libgtparser: LIB     := $(LIB)
install_libgtparser uninstall_libgtparser: DLL     := $(DLL)
install_libgtparser uninstall_libgtparser: SOVER   := $(SOVER)
install_libgtparser uninstall_libgtparser: HEADERS := \
  gtparser.h \
  char_func.h \
  cstring_parser.h \
  int_parser.h \
  int_scanner.h \
  name_parser.h \
  name_scanner.h \
  parser_base.h \
  parser_err.h

install_libgtparser:
	$(INSTALL) -d '$(DESTDIR)$(PREFIX)/include/gtparser'
	$(INSTALL) -m 644 $(addprefix $(TOP)/gtparser/,$(HEADERS)) '$(DESTDIR)$(PREFIX)/include/gtparser'
	$(INSTALL) -d '$(DESTDIR)$(LIBDIR)'
	$(INSTALL) -m 644 $(LIB_DIR)/lib$(LIB).a '$(DESTDIR)$(LIBDIR)'
	$(INSTALL) -m 755 $(LIB_DIR)/lib$(DLL).la '$(DESTDIR)$(LIBDIR)'
	$(INSTALL) -m 755 $(LIB_DIR)/lib$(DLL).so.$(SOVER) '$(DESTDIR)$(LIBDIR)'
	ln -sf$(if $(VERBOSE),v) lib$(DLL).so.$(SOVER) '$(DESTDIR)$(LIBDIR)/lib$(DLL).so'
	$(INSTALL) -d '$(DESTDIR)$(PKG_CONFIG_DIR)'
	$(INSTALL) -m 644 $(LIB_DIR)/lib$(DLL).pc '$(DESTDIR)$(PKG_CONFIG_DIR)'
	$(LDCONFIG) -n$(if $(VERBOSE),v) '$(DESTDIR)$(LIBDIR)'

uninstall_libgtparser:
	rm -rf$(if $(VERBOSE),v) \
  '$(DESTDIR)$(PREFIX)/include/gtparser' \
  '$(DESTDIR)$(LIBDIR)/lib$(LIB).a' \
  '$(DESTDIR)$(LIBDIR)/lib$(DLL).la' \
  '$(DESTDIR)$(LIBDIR)/lib$(DLL).so' \
  '$(DESTDIR)$(LIBDIR)/lib$(DLL).so.$(SOVER)' \
  '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(DLL).pc'
	$(LDCONFIG) -n$(if $(VERBOSE),v) '$(DESTDIR)$(LIBDIR)'

.PHONY: install_libgtparser uninstall_libgtparser

endif # LINUX
