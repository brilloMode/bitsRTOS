#include <bitsrt/rtx.h>

void rtx_delay(uint32_t ms) {
    // Busy wait stub
    for (volatile uint32_t i = 0; i < ms * 1000; i++);
}