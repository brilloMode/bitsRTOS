.section .text
.global _start
_start:
    // Set up initial stack
    ldr x0, =0x920000
    mov sp, x0

    // Clear BSS (optional)
    bl bsp_init
    bl main
    b .