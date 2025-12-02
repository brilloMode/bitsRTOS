ENTRY(_start)
MEMORY {
    OCRAM (rwx) : ORIGIN = 0x00900000, LENGTH = 512K
    DDR   (rwx) : ORIGIN = 0x40000000, LENGTH = 2G
}
SECTIONS {
    . = 0x910000;
    .text : { *(.text*) } > OCRAM
    .data : { *(.data*) } > OCRAM
    .bss  : { *(.bss*)  *(COMMON) } > OCRAM
}
