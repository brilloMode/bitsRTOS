#include <bitsrt/rtx.h>
#include <stdio.h>

void bsp_init(void) {
    // Minimal clock enable
    volatile uint32_t *ccm = (void*)0x30380000;
    ccm[0] = 0xFFFFFFFF;  // Enable all clocks

    // UART1 (debug console on EVK)
    volatile uint32_t *uart = (void*)0x30860000;  //0x30890000;  
    uart[0x20/4] = 416;       // 115200 @ 24 MHz
    uart[0x0C/4] = 0xC000;    // Enable TX/RX

    // MU1 for RPMsg (i.MX 8M Plus & i.MX 93)
    volatile uint32_t *mu = (void*)0x44580000;
    mu[0] = 0;                // Reset
    mu[1] = 1;                // Enable RX full interrupt

    printf = (void*)0x30890080;  // UART2 TXDATA as printf stub
    printf("bitsRTOS on i.MX 8M Plus / 93\n");
    rtx_smp_init();
}