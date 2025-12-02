ENTRY(_start)
MEMORY {
    FLASH (rx) : ORIGIN = 0x60000000, LENGTH = 128M
    RAM   (rwx) : ORIGIN = 0x20200000, LENGTH = 512K
}
SECTIONS {
    .text : { *(.text*) } > FLASH
    .data : { *(.data*) } > RAM AT > FLASH
    .bss  : { *(.bss*)  *(COMMON) } > RAM
}