include $(dir $(lastword $(MAKEFILE_LIST)))../top.mk
include $(MTOP)/c.mk

LIB     := gtparser
DLL     := gtparser
SRC     := parser_base.c parser_err.c name_scanner.c int_scanner.c cstring_parser.c
INCLUDE := ..
SOVER   := 1
DLL_DEFINES := GTPARSER_EXPORTS=$(DLL_EXPORTS_DEFINE)

$(DEFINE_TARGETS)

# installation

install_libgtparser: $(call FORM_TRG,LIB) $(call FORM_TRG,DLL)

install_libgtparser uninstall_libgtparser: LIB   := $(LIB)
install_libgtparser uninstall_libgtparser: DLL   := $(DLL)
install_libgtparser uninstall_libgtparser: SOVER := $(SOVER)

install_libgtparser: HEADERS := \
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

PC_DESC := Generic Text parsing functions library

define PC_COMMENT
Author:  $(VENDOR_NAME)
License: LGPL version 2.1 or any later version
endef

install_libgtparser: PC_TEXT := $(call PKGCONFIG_DEF_TEMPLATE,$(DLL),$(SOVER),$(PC_DESC),$(PC_COMMENT),$(VENDOR_URL))
install_libgtparser: LA_TEXT := $(call LIBTOOL_LA_TEMPLATE,$(DLL),$(SOVER),$(LIB))

install_libgtparser:
	$(INSTALL) -d '$(DESTDIR)$(PREFIX)/include/gtparser'
	$(INSTALL) -m 644 $(addprefix $(TOP)/gtparser/,$(HEADERS)) '$(DESTDIR)$(PREFIX)/include/gtparser'
	$(INSTALL) -d '$(DESTDIR)$(LIBDIR)'
	$(INSTALL) -m 644 $(LIB_DIR)/lib$(LIB).a '$(DESTDIR)$(LIBDIR)'
	$(INSTALL) -m 755 $(LIB_DIR)/lib$(DLL).so '$(DESTDIR)$(LIBDIR)/lib$(DLL).so.$(SOVER)'
	ln -sf$(if $(VERBOSE),v) lib$(DLL).so.$(SOVER) '$(DESTDIR)$(LIBDIR)/lib$(DLL).so'
	$(call ECHO,$(LA_TEXT)) > '$(DESTDIR)$(LIBDIR)/lib$(DLL).la'
	chmod$(if $(VERBOSE), -v) 755 '$(DESTDIR)$(LIBDIR)/lib$(DLL).la'
	$(INSTALL) -d '$(DESTDIR)$(PKG_CONFIG_DIR)'
	$(call ECHO,$(PC_TEXT)) > '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(DLL).pc'
	chmod$(if $(VERBOSE), -v) 644 '$(DESTDIR)$(PKG_CONFIG_DIR)/lib$(DLL).pc'
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

else ifeq (WINXX,$(OS))

DST_INC_DIR := $(subst $(space),\$(space),$(DESTDIR)$(PREFIX)/include/gtparser)
DST_LIB_DIR := $(subst $(space),\$(space),$(DESTDIR)$(LIBDIR))

$(DST_INC_DIR): | $(DST_LIB_DIR)
$(DST_INC_DIR) $(DST_LIB_DIR):
	$(call MKDIR,"$(subst \ , ,$@)")

install_libgtparser: | $(DST_INC_DIR) $(DST_LIB_DIR)
	$(foreach f,$(HEADERS),$(call CP,$(TOP)/gtparser/$f,"$(DESTDIR)$(PREFIX)/include/gtparser")$(newline))
	$(call CP,$(LIB_DIR)/$(LIB)$(LIB_SUFFIX),"$(DESTDIR)$(LIBDIR)")
	$(call CP,$(IMP_DIR)/$(DLL)$(IMP_SUFFIX),"$(DESTDIR)$(LIBDIR)")
	$(call CP,$(DLL_DIR)/$(DLL)$(DLL_SUFFIX),"$(DESTDIR)$(LIBDIR)")

uninstall_libgtparser:
	$(call DEL_DIR,"$(DESTDIR)$(PREFIX)/include/gtparser")
	$(call DEL,"$(DESTDIR)$(LIBDIR)/$(LIB)$(LIB_SUFFIX)")
	$(call DEL,"$(DESTDIR)$(LIBDIR)/$(DLL)$(IMP_SUFFIX)")
	$(call DEL,"$(DESTDIR)$(LIBDIR)/$(DLL)$(DLL_SUFFIX)")

endif # WINXX

.PHONY: install_libgtparser uninstall_libgtparser
