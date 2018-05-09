BITS 32

extern main

global kernel_start

[section .text]
kernel_start:
    mov ebp, 0x1FFFFF
    mov esp, ebp

    call main

    cli
    hlt