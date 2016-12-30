CELL_SDK ?= /c/cell
CELL_MK_DIR = $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_SRCS = main.c
PPU_TARGET = libntfs_sample.elf

PPU_INCDIRS = -I../include
PPU_LIBS	= ../libntfs_ext.a
PPU_LDLIBS 	+= -lsysmodule_stub -lc -lfs_stub -lfont_stub -lgcm_sys_stub -lio_stub -lsysutil_stub -lrtc_stub -llv2_stub -lsysmodule_stub -lm

PPU_CFLAGS += -O2 -std=gnu99

MAKE_FSELF = $(CELL_HOST_PATH)/bin/make_fself_npdrm$(EXE_SUFFIX)

PACKAGER = $(CELL_HOST_PATH)/bin/make_package_npdrm$(EXE_SUFFIX)

USER_DIR = $(OBJS_DIR)/USRDIR

PKG_CONFIG = package.conf
PKG_TARGET = $(sh $(PACKAGER) --print-content-id $(PKG_CONFIG)).pkg

CONTENTS = $(OBJS_DIR)/PARAM.SFO $(OBJS_DIR)/ICON0.PNG $(USER_DIR)/EBOOT.BIN

EXTRA_TARGET = $(PKG_TARGET)
CLEANFILES = $(PKG_TARGET) $(CONTENTS)

$(PKG_TARGET): $(PKG_CONFIG) $(CONTENTS)
	@echo \# generate sample npdrm package in here.
	$(PACKAGER) $(PKG_CONFIG) $(OBJS_DIR)

$(OBJS_DIR)/PARAM.SFO: PARAM.SFO
	@mkdir -p $(@D)
	@$(CP) $< $@

$(OBJS_DIR)/ICON0.PNG: ICON0.PNG
	@mkdir -p $(@D)
	@$(CP) $< $@

$(USER_DIR)/EBOOT.BIN: $(PPU_TARGET)
	@echo \# make EBOOT.BIN in $(USER_DIR)/.
	@mkdir -p $(@D)
	$(MAKE_FSELF) $< $@

include $(CELL_MK_DIR)/sdk.target.mk
