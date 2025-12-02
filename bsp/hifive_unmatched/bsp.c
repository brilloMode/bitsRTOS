#include <bitsrt/rtx.h>
#include <stdio.h>

void bsp_init(void) {
    printf("Target: hifive_unmatched\n");
    rtx_smp_init();
    rtx_mpu_init();
}

void _start(void) {
    bsp_init();
    main();
}