org 0x10000 ; our kernel starts at 1MB
BITS 32

jmp main

msg db "Welcome to Kernel Land!!", 10, 13, 0

main:
    