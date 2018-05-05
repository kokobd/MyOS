BITS 32

section .multiboot2

%define MAGIC_NUMBER 0xE85250D6

header_start:
    dd MAGIC_NUMBER ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode i386)
    dd header_end - header_start
    ; checksum
    dd 0x100000000 - (MAGIC_NUMBER + (header_end - header_start))

    dw 0 ; type
    dw 0 ; flags
    dd 8 ; size
header_end:
