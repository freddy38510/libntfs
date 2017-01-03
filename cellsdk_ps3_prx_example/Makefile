CELL_MK_DIR = $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

PRX_DIR		= .
PPU_LIBS	= ../libntfs_ext.a

PPU_SRCS = main.c
PPU_PRX_TARGET = test.prx

PPU_PRX_LDLIBS 	+= -lfs_stub -lsysmodule_stub -lc_stub -lm_stub # -lfs_stub, -lc_stub and -lm_stub are needed for libtnfs_ext.a
PPU_CFLAGS += -Os  -fno-builtin-printf -std=gnu99

CLEANFILES = $(PRX_DIR)/$(PPU_SPRX_TARGET)

include $(CELL_MK_DIR)/sdk.target.mk



