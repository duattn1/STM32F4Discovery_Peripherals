######################################
# Project name
######################################
PROJ_NAME=GPIO

#######################################
# Paths
#######################################
# Source path

# Build path
OUTPATH=build

######################################
# Source
######################################
# C sources
SRCS += main.c system_stm32f4xx.c syscalls.c #utils.c #stm32f4xx_it.c

# ASM sources
SRCS += lib/startup_stm32f4xx.s

#######################################
# CFLAGS
#######################################
CFLAGS  += -std=gnu99 -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -nostartfiles -mcpu=cortex-m4

# fpu
CFLAGS += -mfpu=fpv4-sp-d16

# float-abi
CFLAGS += -mfloat-abi=hard

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

#######################################
# Binaries
#######################################
# Toolchain binaries location
BINPATH=~/gcc-arm-none-eabi-5_4-2016q3/bin

CC=$(BINPATH)/arm-none-eabi-gcc
OBJCOPY=$(BINPATH)/arm-none-eabi-objcopy
SIZE=$(BINPATH)/arm-none-eabi-size

# stlink binaries location
STLINK=~/stlink
#######################################
# Operations
#######################################
# List of objects
vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)
OBJS = $(SRCS:.c=.o)

# Build the application
.PHONY: lib proj

all: lib proj
	$(SIZE) $(OUTPATH)/$(PROJ_NAME).elf

lib:
	$(MAKE) -C lib

proj: 	$(OUTPATH)/$(PROJ_NAME).elf

$(OUTPATH)/$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -Llib -lstm32f4 -lm
	$(OBJCOPY) -O ihex $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).bin

# Clean up
clean:
	rm -f *.o
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
	$(MAKE) clean -C lib # Remove this line if you don't want to clean the libs as well

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write build/$(PROJ_NAME).bin 0x8000000
	
