BITS 32

extern cpu_init8259A
global cpu_initialize

; void enterUserCode(void *targetAddr, void *targetESP)
global cpu_enterUserCode

[SECTION .text]
cpu_initialize:
    ; Setting up GDT
    mov eax, tss
    mov word [gdt + 0x28 + 2], ax
    shr eax, 16
    mov byte [gdt + 0x28 + 4], al
    mov byte [gdt + 0x28 + 7], ah

    lgdt [gdtr]
    jmp 0x08:.fixSegRegs
    .fixSegRegs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Load TSS
    mov ax, 0x28
    ltr ax

    ; Init 8259A
    call cpu_init8259A

    ret

cpu_enterUserCode:
    add esp, 4
    pop esi ; Target address
    pop edi ; Target stack base

    mov [tss + 4], esp

    push 0x23 ; ss
    push edi ; esp
    push 0x3246 ; eflags
    push 0x1B ; cs
    push esi ; eip

    xor eax, eax
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax

    sti
    int 0x20

[SECTION .data]
tss:
    ; See https://wiki.osdev.org/Task_State_Segment
    DW 0 ; null
    DW 0 ; reserved
    DD 0 ; esp0, must be specified
    DW 0x10 ; ss0
    DW 0 ; reserved
    TIMES 22 DD 0 ; garbage
    DW 0
    DW 0x68

gdt:
    ; null descriptor
    ; Selector: 0x00
    DD 0
    DD 0

    ; kernel code descriptor
    ; Selector: 0x08
    DW 0xFFFF
    DW 0
    DB 0
    DB 0b10011010
    DB 0b11001111
    DB 0

    ; kernel data descriptor
    ; Selector: 0x10
    DW 0xFFFF
    DW 0
    DB 0
    DB 0b10010010
    DB 0b11001111
    DB 0

    ; user code descriptor
    ; Selector: 0x1B
    DW 0xFFFF
    DW 0
    DB 0
    DB 0b11111010
    DB 0b11001111
    DB 0

    ; user data descriptor
    ; Selector: 0x23
    DW 0xFFFF
    DW 0
    DB 0
    DB 0b11110010
    DB 0b11001111
    DB 0

    ; tss descriptor
    ; Selector: 0x28
    DW 0x68 ; size of TSS
    DW 0 ; base 0:15
    DB 0 ; base 16:23
    DB 0x89
    DB 0x40
    DB 0 ; base 24:31

gdtr:
    DW gdtr - gdt - 1
    DD gdt

