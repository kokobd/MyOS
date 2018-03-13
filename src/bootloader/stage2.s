bits 16
org 0x0

_start:
    jmp main

; define GDT
gdt_data:
    ; null descriptor
    dd 0
    dd 0
    ; code descriptor
    dw 0xFFFF
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0
    ; data descriptor
    dw 0xFFFF
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0
end_of_gdt:

toc:
    dw end_of_gdt - gdt_data - 1
    dd gdt_data

main:
    cli
    push cs
    pop ds
    lgdt [toc]

    cli
    hlt