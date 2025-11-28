ENTRY(Reset_Handler)
MEMORY {
    FLASH : ORIGIN = 0x00000000, LENGTH = 1024K
    RAM : ORIGIN = 0x20000000, LENGTH = 256K
}
SECTIONS {
    .text : { *(.text) } > FLASH
    .data : { *(.data) } > RAM
    .bss : { *(.bss) } > RAM
}