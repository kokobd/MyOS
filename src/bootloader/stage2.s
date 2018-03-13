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
    ; load GDT
    lgdt [toc]
    ; enter protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:stage3 ; fix 'cs'

BITS 32 ; We make it into 32 bit!
stage3:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov esp, 0x90000 ; stack's base address

stop:
    cli
    hlt