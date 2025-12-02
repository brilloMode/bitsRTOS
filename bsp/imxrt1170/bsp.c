#include <bitsrt/rtx.h>
#include <stdio.h>

void bsp_init(void) {
    // Enable clocks (very small subset)
    volatile uint32_t *ccm = (void*)0x400FC000;
    ccm[0x68/4] = 0xFFFFFFFF;  // Enable all peripheral clocks

    // LPUART1 @ 115200 (pins already muxed by default on EVK)
    volatile uint32_t *uart = (void*)0x40C0C000;
    uart[0x20/4] = 0x0F;      // BAUD: 115200
    uart[0x0C/4] = 0xC000;    // CTRL: enable TX/RX

    // Note: printf should be implemented by BSP to use UART TXDATA
    printf("bitsRTOS on i.MX RT1170\n");
}