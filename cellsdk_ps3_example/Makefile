CELL_MK_DIR = $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_SRCS = main.c
PPU_TARGET = libntfs.elf

PPU_INCDIRS = -Iinclude
PPU_LIBS	= ../libntfs_ext.a
#PPU_LDLIBS 	+= -lsysmodule_stub -lc -lfs_stub -lfont_stub -lgcm_sys_stub -lio_stub -lsysutil_stub -lrtc_stub -llv2_stub -lsysmodule_stub -lm

PPU_CFLAGS += -O2 -std=gnu99

include $(CELL_MK_DIR)/sdk.target.mk
