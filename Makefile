##############################################################################
BUILD = build
BIN = Demo

##############################################################################
.PHONY: all directory clean size

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

#ifeq ($(OS), Windows_NT)
  #MKDIR = gmkdir
#else
  MKDIR = mkdir
#endif

CFLAGS += -W -Wall --std=gnu99 -Os
CFLAGS += -fno-diagnostics-show-caret
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -funsigned-char -funsigned-bitfields
CFLAGS += -mcpu=cortex-m7 -mthumb
CFLAGS += -mfloat-abi=hard -mfpu=fpv5-d16
CFLAGS += -MD -MP -MT $(BUILD)/$(*F).o -MF $(BUILD)/$(@F).d

LDFLAGS += -mcpu=cortex-m7 -mthumb
LDFLAGS += -mfloat-abi=hard -mfpu=fpv5-d16
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--script=third_party/atmel-SAMV71_DFP/samv71b/gcc/gcc/samv71q21b_flash.ld
#LDFLAGS += -Wl,--script=third_party/atmel-SAMV71_DFP/samv71b/gcc/gcc/samv71q21b_sram.ld

OPENOCD       ?= openocd
OCD_POD       ?= cmsis-dap

INCLUDES += -I. -Ithird_party/arm-CMSIS_5/CMSIS/Core/Include -Ithird_party/atmel-SAMV71_DFP/samv71b/include -Ithird_party/atmel-SAMV71_DFP/samv71b/include_mcc -Ithird_party/FreeRTOS-Kernel/include -Ithird_party/FreeRTOS-Kernel/portable/GCC/ARM_CM7/r0p1

SRCS += \
  ./main.c \
  ./config/interrupts.c \
  #./config/peripheral/pio/plib_pio.c

DEFINES += \
  -D__SAMV71Q21B__ \
   -D__SAMV71B__ \
   -D__SAMV71Q21B__ \
   -DDONT_USE_CMSIS_INIT \
  -DF_CPU=150000000 # peripheral frequency

CFLAGS += $(INCLUDES) $(DEFINES)

OBJS = $(addprefix $(BUILD)/, $(notdir %/$(subst .c,.o, $(SRCS))))

all: directory $(BUILD)/$(BIN).elf $(BUILD)/$(BIN).hex $(BUILD)/$(BIN).bin size

$(BUILD)/$(BIN).elf: $(OBJS)
	@echo LD $@
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

$(BUILD)/$(BIN).hex: $(BUILD)/$(BIN).elf
	@echo OBJCOPY $@
	@$(OBJCOPY) -O ihex $^ $@

$(BUILD)/$(BIN).bin: $(BUILD)/$(BIN).elf
	@echo OBJCOPY $@
	@$(OBJCOPY) -O binary $^ $@

%.o:
	@echo CC $@
	@echo $(CC) $(CFLAGS) $(filter %/$(subst .o,.c,$(notdir $@)), $(SRCS)) -c -o $@
	@$(CC) $(CFLAGS) $(filter %/$(subst .o,.c,$(notdir $@)), $(SRCS)) -c -o $@

directory:
	@$(MKDIR) -p $(BUILD)

size: $(BUILD)/$(BIN).elf
	@echo size:
	@$(SIZE) -t $^

clean:
	@echo clean
	@-rm -rf $(BUILD)
	
flash: all
	$(OPENOCD) -f interface/$(OCD_POD).cfg -f board/atmel_samv71_xplained_ultra.cfg -f openocd_scripts/flash.cfg

-include $(wildcard $(BUILD)/*.d)

