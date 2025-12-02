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
# ────────────────────── i.MX RT Series (Cortex-M7) ──────────────────────
ifeq ($(TARGET),imxrt1060)
    CROSS_COMPILE := arm-none-eabi-
    ARCH          := armv7m
    BSP           := imxrt1060
    CFLAGS        += -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16
endif

ifeq ($(TARGET),imxrt1170)
    CROSS_COMPILE := arm-none-eabi-
    ARCH          := armv7m
    BSP           := imxrt1170
    CFLAGS        += -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16
endif

# ────────────────────── i.MX 8M Series (64-bit A53) ──────────────────────
ifeq ($(TARGET),imx8mm)
    CROSS_COMPILE := aarch64-none-elf-
    ARCH          := armv8a
    BSP           := imx8mm
    CFLAGS        += -mcpu=cortex-a53 -mstrict-align
endif

ifeq ($(TARGET),imx8mp)
    CROSS_COMPILE := aarch64-none-elf-
    ARCH          := armv8a
    BSP           := imx8mp
    CFLAGS        += -mcpu=cortex-a53 -mstrict-align
endif

# ────────────────────── i.MX 93 (A55 + M33) ──────────────────────
ifeq ($(TARGET),imx93)
    CROSS_COMPILE := aarch64-none-elf-
    ARCH          := armv8a
    BSP           := imx93
    CFLAGS        += -mcpu=cortex-a55 -mstrict-align
endif

CC := $(CROSS_COMPILE)gcc
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE := $(CROSS_COMPILE)size

CONFIG_FILE ?= config/defconfig_$(TARGET)
include $(CONFIG_FILE)

# Generate config.h from defconfig
build/config.h: $(CONFIG_FILE)
	@mkdir -p build
	@echo "/* Auto-generated from $(CONFIG_FILE) */" > $@
	@echo "#ifndef BITSRTOS_CONFIG_H" >> $@
	@echo "#define BITSRTOS_CONFIG_H" >> $@
	@sed -n 's/^CONFIG_\([A-Z_]*\)=y$$/#define \1 1/p' $(CONFIG_FILE) >> $@
	@sed -n '/^CONFIG_[A-Z_]*=y$$/!s/^CONFIG_\([A-Z_]*\)=\(.*\)/#define \1 \2/p' $(CONFIG_FILE) >> $@
	@echo "#endif" >> $@

CFLAGS += -std=c11 -Os -Wall -Wextra -ffreestanding -nostdlib -g -DBITSRTOS_VERSION=\"v0.7-smp\" -Iinclude -Ibuild
LDFLAGS += -T bsp/$(BSP)/linker.ld -nostdlib -lgcc

SRCS := $(wildcard kernel/*.c) $(wildcard port/arch/$(ARCH)/*.c) $(wildcard bsp/$(BSP)/*.c)
OBJS := $(SRCS:.c=.o) $(wildcard port/arch/$(ARCH)/*.S)

ifeq ($(CONFIG_BITSRTOS_SMP),y)
    CFLAGS += -DBITSRTOS_SMP
endif
ifeq ($(CONFIG_ENABLE_PTHREADS),y)
    CFLAGS += -DBITSRTOS_PTHREADS
endif

# Architecture defines
ifeq ($(ARCH),riscv64)
    CFLAGS += -DARCH_RISCV64
endif
ifeq ($(ARCH),armv7m)
    CFLAGS += -DARCH_ARMV7M
endif
ifeq ($(ARCH),armv8m)
    CFLAGS += -DARCH_ARMV8M
endif
ifeq ($(ARCH),armv8a)
    CFLAGS += -DARCH_ARMV8A
endif

all: build/config.h build/bitsRTOS.elf build/bitsRTOS.bin
	$(SIZE) build/bitsRTOS.elf

build/bitsRTOS.elf: build/config.h $(OBJS)
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