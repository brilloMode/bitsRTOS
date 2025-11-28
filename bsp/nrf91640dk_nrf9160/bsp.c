#include <bitsrt/rtx.h>

void bsp_init(void) {
    // nRF UART setup stub
    printf("Target: nrf91640dk\n");
    rtx_smp_init();
    rtx_mpu_init();
}

void Reset_Handler(void) {
    bsp_init();
    main();
}