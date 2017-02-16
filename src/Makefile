include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk

LIB     := $(if $(NO_STATIC),,gtparser)
DLL     := $(if $(NO_SHARED),,gtparser)
SRC     := parser_base.c parser_err.c name_scanner.c int_scanner.c cstring_parser.c
INCLUDE := ..
DLL_DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)

$(DEFINE_TARGETS)

# installation

install_libgtparser_check_libs:
	$(if $(DLL)$(LIB),,$(error no libs to install))

install_libgtparser: install_libgtparser_check_libs $(call FORM_TRG,LIB) $(call FORM_TRG,DLL)

install_libgtparser uninstall_libgtparser: LIB      := $(LIB)
install_libgtparser uninstall_libgtparser: DLL      := $(DLL)
install_libgtparser uninstall_libgtparser: MODVER   := $(MODVER)
install_libgtparser uninstall_libgtparser: LIB_NAME := $(firstword $(DLL) $(LIB))

install_libgtparser_headers: HEADERS := \
  gtparser.h \
  char_func.h \
  cstring_parser.h \
  int_parser.h \
  int_scanner.h \
  name_parser.h \
  name_scanner.h \
  parser_base.h \
  parser_err.h

ifeq (LINUX,$(OS))

include $(MTOP)/LINUX/pc.mk
include $(MTOP)/LINUX/la.mk

define PC_COMMENT
Author:  $(VENDOR_NAME)
License: LGPL version 2.1 or any later version
endef

install_libgtparser: LA_TEXT := $(call LIBTOOL_LA_TEMPLATE,$(DLL),$(MODVER),$(LIB))
install_libgtparser: PC_TEXT := $(call \
  PKGCONFIG_DEF_TEMPLATE,$(LIB_NAME),$(MODVER),$(PRODUCT_NAME),$(PC_COMMENT),$(VENDOR_URL))

install_libgtparser_headers:
	$(INSTALL) -d '$(DESTDIR)$(PREFIX)/include/gtparser'
	$(INSTALL) -m 644 $(addprefix $(TOP)/gtparser/,$(HEADERS)) '$(DESTDIR)$(PREFIX)/include/gtparser'

install_libgtparser: install_libgtparser_headers
	$(INSTALL) -d '$(DESTDIR)$(LIBDIR)'
	$(if $(LIB),$(INSTALL) -m 644 $(LIB_DIR)/lib$(LIB).a '$(DESTDIR)$(LIBDIR)')
	$(if $(DLL),$(INSTALL) -m 755 $(LIB_DIR)/lib$(DLL).so '$(DESTDIR)$(LIBDIR)/lib$(DLL).so.$(MODVER)')
	$(if $(DLL),ln -sf$(if $(VERBOSE),v) lib$(DLL).so.$(MODVER) '$(DESTDIR)$(LIBDIR)/lib$(DLL).so')
	$(call ECHO,$(LA_TEXT)) > '$(DESTDIR)$(LIBDIR)/lib$(LIB_NAME).la'
	chmod$(if $(VERBOSE), -v) 755 '$(DESTDIR)$(LIBDIR)/lib$(LIB_NAME).la'
	$(INSTALL) -d '$(DESTDIR)$(PKG_CONFIG_DIR)'
	$(call ECHO,$(PC_TEXT)) > '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(LIB_NAME).pc'
	chmod$(if $(VERBOSE), -v) 644 '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(LIB_NAME).pc'
	$(LDCONFIG) -n$(if $(VERBOSE),v) '$(DESTDIR)$(LIBDIR)'

uninstall_libgtparser:
	rm -rf$(if $(VERBOSE),v) \
  '$(DESTDIR)$(PREFIX)/include/gtparser' \
  $(if $(LIB),'$(DESTDIR)$(LIBDIR)/lib$(LIB).a') \
  $(if $(DLL),'$(DESTDIR)$(LIBDIR)/lib$(DLL).so') \
  $(if $(DLL),'$(DESTDIR)$(LIBDIR)/lib$(DLL).so.$(MODVER)') \
  '$(DESTDIR)$(LIBDIR)/lib$(LIB_NAME).la' \
  '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(LIB_NAME).pc'
	$(LDCONFIG) -n$(if $(VERBOSE),v) '$(DESTDIR)$(LIBDIR)'

else ifeq (WINXX,$(OS))

DST_INC_DIR := $(subst $(space),\$(space),$(DESTDIR)$(PREFIX)/include/gtparser)
DST_LIB_DIR := $(subst $(space),\$(space),$(DESTDIR)$(LIBDIR))

$(DST_INC_DIR): | $(DST_LIB_DIR)
$(DST_INC_DIR) $(DST_LIB_DIR):
	$(call MKDIR,"$(subst \ , ,$@)")

install_libgtparser_headers: | $(DST_INC_DIR)
	$(foreach f,$(HEADERS),$(call CP,$(TOP)/gtparser/$f,"$(DESTDIR)$(PREFIX)/include/gtparser")$(newline))

install_libgtparser: install_libgtparser_headers | $(DST_LIB_DIR)
	$(if $(LIB),$(call CP,$(LIB_DIR)/$(LIB)$(LIB_SUFFIX),"$(DESTDIR)$(LIBDIR)"))
	$(if $(DLL),$(call CP,$(IMP_DIR)/$(DLL)$(IMP_SUFFIX),"$(DESTDIR)$(LIBDIR)"))
	$(if $(DLL),$(call CP,$(DLL_DIR)/$(DLL)$(DLL_SUFFIX),"$(DESTDIR)$(LIBDIR)"))

uninstall_libgtparser:
	$(call DEL_DIR,"$(DESTDIR)$(PREFIX)/include/gtparser")
	$(if $(LIB),$(call DEL,"$(DESTDIR)$(LIBDIR)/$(LIB)$(LIB_SUFFIX)"))
	$(if $(DLL),$(call DEL,"$(DESTDIR)$(LIBDIR)/$(DLL)$(IMP_SUFFIX)"))
	$(if $(DLL),$(call DEL,"$(DESTDIR)$(LIBDIR)/$(DLL)$(DLL_SUFFIX)"))

endif # WINXX

.PHONY: install_libgtparser_check_libs install_libgtparser_headers uinstall_libgtparser uninstall_libgtparser
