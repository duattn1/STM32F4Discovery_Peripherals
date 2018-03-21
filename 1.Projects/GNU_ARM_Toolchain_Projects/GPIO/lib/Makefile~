######################################
# Source
######################################
# C sources
SRCS = misc.c stm32f4xx_dma.c stm32f4xx_rcc.c stm32f4xx_adc.c \
	stm32f4xx_exti.c stm32f4xx_rng.c stm32f4xx_can.c stm32f4xx_flash.c \
	stm32f4xx_rtc.c stm32f4xx_crc.c stm32f4xx_fsmc.c stm32f4xx_sdio.c \
	stm32f4xx_cryp_aes.c stm32f4xx_gpio.c stm32f4xx_spi.c \
	stm32f4xx_cryp.c stm32f4xx_hash.c stm32f4xx_syscfg.c \
	stm32f4xx_cryp_des.c stm32f4xx_hash_md5.c stm32f4xx_tim.c \
	stm32f4xx_cryp_tdes.c stm32f4xx_hash_sha1.c  stm32f4xx_usart.c \
	stm32f4xx_dac.c stm32f4xx_i2c.c stm32f4xx_wwdg.c \
	stm32f4xx_dbgmcu.c stm32f4xx_iwdg.c \
	stm32f4xx_dcmi.c stm32f4xx_pwr.c


#######################################
# Binaries
#######################################
# Toolchain binaries location
BINPATH=~/gcc-arm-none-eabi-5_4-2016q3/bin

CC=$(BINPATH)/arm-none-eabi-gcc
AR=$(BINPATH)/arm-none-eabi-ar

#######################################
# CFLAGS
#######################################
CFLAGS  = -g -O2 -Wall
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4

CFLAGS += -mfpu=fpv4-sp-d16 
CFLAGS += -mfloat-abi=hard

CFLAGS += -ffreestanding -nostdlib
CFLAGS += -Iinc -Iinc/core -Iinc/peripherals

#######################################
# Operations
#######################################
# List of objects
vpath %.c src src/peripherals
OBJS = $(SRCS:.c=.o)

# Build the libraries
.PHONY: libstm32f4.a

all: libstm32f4.a

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libstm32f4.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

# Clean up
clean:
	rm -f $(OBJS) libstm32f4.a
