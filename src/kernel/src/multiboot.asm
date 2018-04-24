BITS 32

section .multiboot

header_start:
    dd 0x1BADB002 ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode i386)
    ; checksum
    dd (0 - 0x1BADB002)

    dd header_end - header_start ; header length

    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
header_end:
