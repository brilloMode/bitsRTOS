# bitsRTOS - very much a work in progress and use at own risk!

Ultra-compact RTOS for 32/64-bit embedded systems (<16KB footprint).
Inspired by Nucleus RTOS: POSIX pthreads, SMP/AMP, MPU protection, ELF dynamic loading.

## Targets
- QEMU riscv64-virt
- nRF9160-DK (Cortex-M33)
- HiFive Unmatched (RV64)

## Quick Build
make TARGET=nrf91640dk && make -j

## Features
- Preemptive scheduler (32 prio levels)
- Semaphores, mutexes (prio inheritance)
- POSIX pthreads
- SMP (up to 8 cores) + AMP
- MPU/PMP isolation
- Tiny ELF loader
- Tickless idle


## Test it (e.g., QEMU SMP demo)

Install riscv64 toolchain if needed: sudo apt install gcc-riscv64-unknown-elf qemu-system-riscv64
make TARGET=qemu_riscv64 -j12
qemu-system-riscv64 -M virt -cpu rv64 -smp 4 -kernel build/bitsRTOS.elf -nographic

Expected output:

bitsRTOS v0.7-smp
Copyright (c) 2025 brilloMode - MIT License
SMP: 4 cores online
Core 0: SMP demo running
Core 1: SMP demo running
...

MIT License. Author: brilloMode.
