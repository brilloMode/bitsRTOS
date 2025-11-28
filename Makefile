# bitsRTOS Build System
CROSS_COMPILE_RISCV ?= riscv64-unknown-elf-
CROSS_COMPILE_ARM ?= arm-none-eabi-

ifeq ($(TARGET),qemu_riscv64)
    CROSS_COMPILE := $(CROSS_COMPILE_RISCV)
    ARCH := riscv64
    BSP := qemu_riscv64_virt
    CFLAGS += -march=rv64imac -mabi=lp64
endif
ifeq ($(TARGET),nrf91640dk)
    CROSS_COMPILE := $(CROSS_COMPILE_ARM)
    ARCH := armv8m
    BSP := nrf91640dk_nrf9160
    CFLAGS += -mcpu=cortex-m33 -mthumb
endif
ifeq ($(TARGET),hifive_unmatched)
    CROSS_COMPILE := $(CROSS_COMPILE_RISCV)
    ARCH := riscv64
    BSP := hifive_unmatched
    CFLAGS += -march=rv64imac -mabi=lp64
endif

CC := $(CROSS_COMPILE)gcc
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE := $(CROSS_COMPILE)size

CONFIG_FILE ?= config/defconfig_$(TARGET)
include $(CONFIG_FILE)

CFLAGS += -std=c11 -Os -Wall -Wextra -ffreestanding -nostdlib -g -DBITSRTOS_VERSION=\"v0.7-smp\" -Iinclude
LDFLAGS += -T bsp/$(BSP)/linker.ld -nostdlib -lgcc

SRCS := $(wildcard kernel/*.c) $(wildcard port/arch/$(ARCH)/*.c) $(wildcard bsp/$(BSP)/*.c)
OBJS := $(SRCS:.c=.o) $(wildcard port/arch/$(ARCH)/*.S)

ifeq ($(CONFIG_BITSRTOS_SMP),y)
    CFLAGS += -DBITSRTOS_SMP
endif
ifeq ($(CONFIG_ENABLE_PTHREADS),y)
    CFLAGS += -DBITSRTOS_PTHREADS
endif

all: build/bitsRTOS.elf build/bitsRTOS.bin
	$(SIZE) build/bitsRTOS.elf

build/bitsRTOS.elf: $(OBJS)
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

build/bitsRTOS.bin: build/bitsRTOS.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/

.PHONY: all clean