CELL_MK_DIR = $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

LIBSTUB_DIR		= ./lib
PRX_DIR			= .
INSTALL			= cp
PEXPORTPICKUP		= ppu-lv2-prx-exportpickup
PRX_LDFLAGS_EXTRA	= -L ./lib -Wl,--strip-unused-data

PPU_SRCS = 		libc.c main.c
PPU_PRX_TARGET = 	test.prx
PPU_PRX_LDFLAGS += 	$(PRX_LDFLAGS_EXTRA)
PPU_PRX_STRIP_FLAGS = 	-s

PPU_PRX_LOADLIBS 	+= 	-lallocator_export_stub -lstdc_export_stub ../libntfs_prx.a

PPU_CFLAGS += -Os -ffunction-sections -fdata-sections -fno-builtin-printf -nodefaultlibs -std=gnu99 -Wno-shadow -Wno-unused-parameter

CLEANFILES = $(PRX_DIR)/$(PPU_SPRX_TARGET)

all:
	$(MAKE) $(PPU_OBJS_DEPENDS)
	$(PPU_PRX_STRIP) --strip-debug --strip-section-header $(PPU_PRX_TARGET)
	scetool -0 SELF -1 TRUE -s FALSE -2 04 -3 1010000001000003 -4 01000002 -5 APP -6 0003004000000000 -A 0001000000000000 -e $(PPU_PRX_TARGET) $(PPU_SPRX_TARGET)

include $(CELL_MK_DIR)/sdk.target.mk
