# Makefile for stbone STM32L432 with openocd
# 03-30-2017 E. Brombaugh

# sub directories
VPATH = .:CMSIS:HAL

# Object files
OBJECTS = 	startup_stm32l432xx.o system_stm32l4xx.o main.o led.o \
            usart.o printf.o \
			stm32l4xx_hal.o stm32l4xx_hal_cortex.o stm32l4xx_hal_gpio.o \
            stm32l4xx_hal_rcc.o stm32l4xx_hal_pwr_ex.o stm32l4xx_hal_usart.o \
            stm32l4xx_hal_adc.o stm32l4xx_hal_adc_ex.o stm32l4xx_hal_dma.o \
            stm32l4xx_hal_rcc_ex.o 

# Linker script
LDSCRIPT = STM32L432KCUx_FLASH.ld

# Compiler Flags
CFLAGS  = -g -O0 -ffunction-sections -std=gnu99
CFLAGS += -I. -ICMSIS -IHAL
CFLAGS += -DARM_MATH_CM4 -DUSE_HAL_DRIVER
CFLAGS += -D'HSE_VALUE=((uint32_t)25000000)' -DSTM32L432xx
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
AFLAGS  = -mlittle-endian -mthumb -mcpu=cortex-m4 
LFLAGS  = $(CFLAGS) -nostartfiles -T $(LDSCRIPT) -Wl,-Map=main.map
LFLAGS += -Wl,--gc-sections
#LFLAGS += --specs=nano.specs
CPFLAGS = --output-target=binary
ODFLAGS	= -x --syms

# Executables
ARCH = arm-none-eabi
CC = $(ARCH)-gcc
LD = $(ARCH)-ld -v
AS = $(ARCH)-as
OBJCPY = $(ARCH)-objcopy
OBJDMP = $(ARCH)-objdump
GDB = $(ARCH)-gdb
OPENOCD = openocd

CPFLAGS = --output-target=binary
ODFLAGS	= -x --syms

# Targets
all: main.bin

clean:
	-rm -f $(OBJECTS) crt.lst *.lst *.elf *.bin *.map *.dmp

#flash: gdb_flash
flash: oocd_flash

oocd_flash: main.elf
	$(OPENOCD) -f openocd_stlink-v2.1.cfg -c "program main.elf verify reset exit"

gdb_flash: main.elf
	$(GDB) -x flash_cmd.gdb -batch
	stty sane

disassemble: main.elf
	$(OBJDMP) -d main.elf > main.dis
	
dist:
	tar -c *.h *.c *.s Makefile *.cmd *.cfg openocd_doflash | gzip > minimal_hello_world.tar.gz

main.ihex: main.elf
	$(OBJCPY) --output-target=ihex main.elf main.ihex

main.bin: main.elf 
	$(OBJCPY) $(CPFLAGS) main.elf main.bin
	$(OBJDMP) $(ODFLAGS) main.elf > main.dmp
	ls -l main.elf main.bin

main.elf: $(OBJECTS) $(LDSCRIPT)
	$(CC) $(LFLAGS) -o main.elf $(OBJECTS) -lnosys -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

