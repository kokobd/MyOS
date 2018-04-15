BITS 32

extern c_main

global kernel_start

[section .text]
kernel_start:
    mov ebp, 0x1FFFFF
    mov esp, ebp

    call c_main

    cli
    hlt