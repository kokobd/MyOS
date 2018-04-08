BITS 32

[SECTION .text]

global cpu_init8259A

cpu_init8259A:
    mov al, 0x11
    out 0x20, al
    call io_delay

    out 0xA0, al
    call io_delay

    mov al, 0x20
    out 0x21, al
    call io_delay

    mov al, 0x28
    out 0xA1, al
    call io_delay

    mov al, 0x04
    out 0x21, al
    call io_delay

    mov al, 0x02
    out 0xA1, al
    call io_delay

    mov al, 0x01
    out 0x21, al
    call io_delay

    out 0xA1, al
    call io_delay

    mov al, 0b00000000
    out 0x21, al
    call io_delay

    mov al, 0b00000000
    out 0xA1, al
    call io_delay

    ret

io_delay:
    nop
    nop
    nop
    nop
    ret
