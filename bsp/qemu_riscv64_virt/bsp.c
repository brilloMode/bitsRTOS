#include <bitsrt/rtx.h>

void bsp_init(void) {
    // UART setup stub for QEMU
    printf = (void (*)(const char*, ...))0x10000000;  // QEMU semihost stub
    rtx_smp_init();
    rtx_mpu_init();
}

void _start(void) {
    bsp_init();
    main();
}