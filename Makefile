CELL_SDK ?= /c/cell
CELL_MK_DIR ?= $(CELL_SDK)/samples/mk

include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_LIB_TARGET	= libntfs_ext.a
PPU_INCDIRS = -Iinclude
PPU_SRCS = $(wildcard source/*.c) $(wildcard source/libext2fs/*.c)

DEFINES += -DBIGENDIAN -D__CELLOS_LV2__ -DPS3_GEKKO -DHAVE_CONFIG_H -DPS3_STDIO# -DDEBUG

PPU_CFLAGS := -O2 -Wall -mcpu=cell -fno-strict-aliasing $(PPU_INCDIRS) $(DEFINES) -std=gnu99

include $(CELL_MK_DIR)/sdk.target.mk


