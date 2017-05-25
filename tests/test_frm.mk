# this file is included by basic_scanner_test.mk and cstring_parser_test.mk
# GTPARSER_TEST_SRC variable must be defined

include $(MTOP)/c.mk
include $(MTOP)/exts/ctest.mk

INCLUDE := ..
SRC     := $(GTPARSER_TEST_SRC)
RPATH   := $(LIB_DIR)

# don't test D-variant of static library - this variant is for linking static library to dll
TEST_LIB_VARIANTS := $(addsuffix -lib,$(if $(NO_STATIC),,$(filter-out D,$(call FILTER_VARIANTS_LIST,LIB,$(GTPARSER_LIB_VARIANTS)))))
TEST_DLL_VARIANTS := $(addsuffix -dll,$(if $(NO_SHARED),,$(call FILTER_VARIANTS_LIST,DLL,$(GTPARSER_DLL_VARIANTS))))

# form test executable name
# $1 - dyn or <empty>
# $v - variant
FORM_EXE_NAME = $(subst .,_,$(SRC))$(addprefix -,$1)$(addprefix -,$(call tolower,$(filter-out R,$v))) $v

# $v - static library variant to test
define TEST_LIB_TEMPLATE
LIBS    := $(GTPARSER_LIB_NAME)
EXE     := $(FORM_EXE_NAME)
$$(DO_TEST_EXE)
endef

# $v - dynamic library variant to test
# note: add $(LIB_DIR) to $(PATH) to run tests under cygwin
define TEST_DLL_TEMPLATE
DLLS    := $(GTPARSER_LIB_NAME)
EXE     := $(call FORM_EXE_NAME,dyn)
DEFINES := GTPARSER_EXPORTS=$(DLL_IMPORTS_DEFINE)
$$(call DO_TEST_EXE,$$(DLLS:=.$(call ver_major,$(PRODUCT_VER))),,,PATH=$$$$(PATH)$$(PATHSEP)$$(LIB_DIR))
endef

# expand $(TEST_LIB_TEMPLATE) or $(TEST_DLL_TEMPLATE)
# $x - r-lib, r-dll, s-lib, ...
EXPAND_TEST_TEMPLATE = $(foreach v,$(firstword $(subst -, ,$x)),$(if $(filter %-lib,$x),$(TEST_LIB_TEMPLATE),$(TEST_DLL_TEMPLATE)))

$(foreach x,$(TEST_LIB_VARIANTS) $(TEST_DLL_VARIANTS),$(eval \
  $(EXPAND_TEST_TEMPLATE))$(call MAKE_CONTINUE,INCLUDE SRC RPATH))

$(DEFINE_TARGETS)
