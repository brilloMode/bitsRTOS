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

MIT License. Author: brilloMode.
