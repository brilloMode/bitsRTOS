#include <bitsrt/rtx.h>
#include <stdio.h>

void bsp_init(void) {
    // UART setup stub for QEMU
    // Note: printf should be implemented by BSP for QEMU semihost @ 0x10000000
    rtx_smp_init();
    rtx_mpu_init();
}

void _start(void) {
    bsp_init();
    main();
}