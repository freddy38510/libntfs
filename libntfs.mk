CELL_SDK ?= /c/cell
CELL_MK_DIR ?= $(CELL_SDK)/samples/mk

include $(CELL_MK_DIR)/sdk.makedef.mk

BUILD_TYPE = release

BUILD_TAG = libntfs
PPU_LIB_TARGET	= libntfs.a
PPU_OPTIMIZE_LV := -Os

PPU_INCDIRS = -Iinclude
PPU_SRCS = $(wildcard source/*.c)
#PPU_SRCS += $(wildcard source/libext2fs/*.c)

#DEFINES += -DWITH_EXT_SUPPORT
#DEFINES += -DPS3_STDIO
DEFINES += -DBIGENDIAN -DPS3_GEKKO -DHAVE_CONFIG_H

PPU_CFLAGS := -Os -Wall -std=gnu99 -mcpu=cell -fno-strict-aliasing $(PPU_INCDIRS) $(DEFINES)

ifeq ($(BUILD_TYPE), debug)
PPU_CFLAGS 	+= -DDEBUG
PPU_LIB_TARGET	= libntfs.debug.a
endif

include $(CELL_MK_DIR)/sdk.target.mk
