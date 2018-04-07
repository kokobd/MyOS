BITS 32

extern interruptDispatcher
global interruptHandlerPrim
global interruptHandlerPrimOffset

[SECTION .text]

interruptHandlerPrim:
    .entry0:
    mov dword [interruptNumber], 0x00
    jmp near .end
    .entry1:
    mov dword [interruptNumber], 0x01
    jmp near .end
    mov dword [interruptNumber], 0x02
    jmp near .end
    mov dword [interruptNumber], 0x03
    jmp near .end
    mov dword [interruptNumber], 0x04
    jmp near .end
    mov dword [interruptNumber], 0x05
    jmp near .end
    mov dword [interruptNumber], 0x06
    jmp near .end
    mov dword [interruptNumber], 0x07
    jmp near .end
    mov dword [interruptNumber], 0x08
    jmp near .end
    mov dword [interruptNumber], 0x09
    jmp near .end
    mov dword [interruptNumber], 0x0A
    jmp near .end
    mov dword [interruptNumber], 0x0B
    jmp near .end
    mov dword [interruptNumber], 0x0C
    jmp near .end
    mov dword [interruptNumber], 0x0D
    jmp near .end
    mov dword [interruptNumber], 0x0E
    jmp near .end
    mov dword [interruptNumber], 0x0F
    jmp near .end
    mov dword [interruptNumber], 0x10
    jmp near .end
    mov dword [interruptNumber], 0x11
    jmp near .end
    mov dword [interruptNumber], 0x12
    jmp near .end
    mov dword [interruptNumber], 0x13
    jmp near .end
    mov dword [interruptNumber], 0x14
    jmp near .end
    mov dword [interruptNumber], 0x15
    jmp near .end
    mov dword [interruptNumber], 0x16
    jmp near .end
    mov dword [interruptNumber], 0x17
    jmp near .end
    mov dword [interruptNumber], 0x18
    jmp near .end
    mov dword [interruptNumber], 0x19
    jmp near .end
    mov dword [interruptNumber], 0x1A
    jmp near .end
    mov dword [interruptNumber], 0x1B
    jmp near .end
    mov dword [interruptNumber], 0x1C
    jmp near .end
    mov dword [interruptNumber], 0x1D
    jmp near .end
    mov dword [interruptNumber], 0x1E
    jmp near .end
    mov dword [interruptNumber], 0x1F
    jmp near .end
    mov dword [interruptNumber], 0x20
    jmp near .end
    mov dword [interruptNumber], 0x21
    jmp near .end
    mov dword [interruptNumber], 0x22
    jmp near .end
    mov dword [interruptNumber], 0x23
    jmp near .end
    mov dword [interruptNumber], 0x24
    jmp near .end
    mov dword [interruptNumber], 0x25
    jmp near .end
    mov dword [interruptNumber], 0x26
    jmp near .end
    mov dword [interruptNumber], 0x27
    jmp near .end
    mov dword [interruptNumber], 0x28
    jmp near .end
    mov dword [interruptNumber], 0x29
    jmp near .end
    mov dword [interruptNumber], 0x2A
    jmp near .end
    mov dword [interruptNumber], 0x2B
    jmp near .end
    mov dword [interruptNumber], 0x2C
    jmp near .end
    mov dword [interruptNumber], 0x2D
    jmp near .end
    mov dword [interruptNumber], 0x2E
    jmp near .end
    mov dword [interruptNumber], 0x2F
    jmp near .end
    mov dword [interruptNumber], 0x30
    jmp near .end
    mov dword [interruptNumber], 0x31
    jmp near .end
    mov dword [interruptNumber], 0x32
    jmp near .end
    mov dword [interruptNumber], 0x33
    jmp near .end
    mov dword [interruptNumber], 0x34
    jmp near .end
    mov dword [interruptNumber], 0x35
    jmp near .end
    mov dword [interruptNumber], 0x36
    jmp near .end
    mov dword [interruptNumber], 0x37
    jmp near .end
    mov dword [interruptNumber], 0x38
    jmp near .end
    mov dword [interruptNumber], 0x39
    jmp near .end
    mov dword [interruptNumber], 0x3A
    jmp near .end
    mov dword [interruptNumber], 0x3B
    jmp near .end
    mov dword [interruptNumber], 0x3C
    jmp near .end
    mov dword [interruptNumber], 0x3D
    jmp near .end
    mov dword [interruptNumber], 0x3E
    jmp near .end
    mov dword [interruptNumber], 0x3F
    jmp near .end
    mov dword [interruptNumber], 0x40
    jmp near .end
    mov dword [interruptNumber], 0x41
    jmp near .end
    mov dword [interruptNumber], 0x42
    jmp near .end
    mov dword [interruptNumber], 0x43
    jmp near .end
    mov dword [interruptNumber], 0x44
    jmp near .end
    mov dword [interruptNumber], 0x45
    jmp near .end
    mov dword [interruptNumber], 0x46
    jmp near .end
    mov dword [interruptNumber], 0x47
    jmp near .end
    mov dword [interruptNumber], 0x48
    jmp near .end
    mov dword [interruptNumber], 0x49
    jmp near .end
    mov dword [interruptNumber], 0x4A
    jmp near .end
    mov dword [interruptNumber], 0x4B
    jmp near .end
    mov dword [interruptNumber], 0x4C
    jmp near .end
    mov dword [interruptNumber], 0x4D
    jmp near .end
    mov dword [interruptNumber], 0x4E
    jmp near .end
    mov dword [interruptNumber], 0x4F
    jmp near .end
    mov dword [interruptNumber], 0x50
    jmp near .end
    mov dword [interruptNumber], 0x51
    jmp near .end
    mov dword [interruptNumber], 0x52
    jmp near .end
    mov dword [interruptNumber], 0x53
    jmp near .end
    mov dword [interruptNumber], 0x54
    jmp near .end
    mov dword [interruptNumber], 0x55
    jmp near .end
    mov dword [interruptNumber], 0x56
    jmp near .end
    mov dword [interruptNumber], 0x57
    jmp near .end
    mov dword [interruptNumber], 0x58
    jmp near .end
    mov dword [interruptNumber], 0x59
    jmp near .end
    mov dword [interruptNumber], 0x5A
    jmp near .end
    mov dword [interruptNumber], 0x5B
    jmp near .end
    mov dword [interruptNumber], 0x5C
    jmp near .end
    mov dword [interruptNumber], 0x5D
    jmp near .end
    mov dword [interruptNumber], 0x5E
    jmp near .end
    mov dword [interruptNumber], 0x5F
    jmp near .end
    mov dword [interruptNumber], 0x60
    jmp near .end
    mov dword [interruptNumber], 0x61
    jmp near .end
    mov dword [interruptNumber], 0x62
    jmp near .end
    mov dword [interruptNumber], 0x63
    jmp near .end
    mov dword [interruptNumber], 0x64
    jmp near .end
    mov dword [interruptNumber], 0x65
    jmp near .end
    mov dword [interruptNumber], 0x66
    jmp near .end
    mov dword [interruptNumber], 0x67
    jmp near .end
    mov dword [interruptNumber], 0x68
    jmp near .end
    mov dword [interruptNumber], 0x69
    jmp near .end
    mov dword [interruptNumber], 0x6A
    jmp near .end
    mov dword [interruptNumber], 0x6B
    jmp near .end
    mov dword [interruptNumber], 0x6C
    jmp near .end
    mov dword [interruptNumber], 0x6D
    jmp near .end
    mov dword [interruptNumber], 0x6E
    jmp near .end
    mov dword [interruptNumber], 0x6F
    jmp near .end
    mov dword [interruptNumber], 0x70
    jmp near .end
    mov dword [interruptNumber], 0x71
    jmp near .end
    mov dword [interruptNumber], 0x72
    jmp near .end
    mov dword [interruptNumber], 0x73
    jmp near .end
    mov dword [interruptNumber], 0x74
    jmp near .end
    mov dword [interruptNumber], 0x75
    jmp near .end
    mov dword [interruptNumber], 0x76
    jmp near .end
    mov dword [interruptNumber], 0x77
    jmp near .end
    mov dword [interruptNumber], 0x78
    jmp near .end
    mov dword [interruptNumber], 0x79
    jmp near .end
    mov dword [interruptNumber], 0x7A
    jmp near .end
    mov dword [interruptNumber], 0x7B
    jmp near .end
    mov dword [interruptNumber], 0x7C
    jmp near .end
    mov dword [interruptNumber], 0x7D
    jmp near .end
    mov dword [interruptNumber], 0x7E
    jmp near .end
    mov dword [interruptNumber], 0x7F
    jmp near .end
    mov dword [interruptNumber], 0x80
    jmp near .end
    mov dword [interruptNumber], 0x81
    jmp near .end
    mov dword [interruptNumber], 0x82
    jmp near .end
    mov dword [interruptNumber], 0x83
    jmp near .end
    mov dword [interruptNumber], 0x84
    jmp near .end
    mov dword [interruptNumber], 0x85
    jmp near .end
    mov dword [interruptNumber], 0x86
    jmp near .end
    mov dword [interruptNumber], 0x87
    jmp near .end
    mov dword [interruptNumber], 0x88
    jmp near .end
    mov dword [interruptNumber], 0x89
    jmp near .end
    mov dword [interruptNumber], 0x8A
    jmp near .end
    mov dword [interruptNumber], 0x8B
    jmp near .end
    mov dword [interruptNumber], 0x8C
    jmp near .end
    mov dword [interruptNumber], 0x8D
    jmp near .end
    mov dword [interruptNumber], 0x8E
    jmp near .end
    mov dword [interruptNumber], 0x8F
    .end:
    ; For some interrupts, [esp] is the error code
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax
    push dword [interruptNumber]
    call interruptDispatcher

    add esp, 4

    cmp dword [interruptNumber], 0x80 ; Is system call ?
    je .preserveCurrentEAX
    .notPreserveCurrentEAX:
    pop eax
    jmp .restoreOtherRegs
    .preserveCurrentEAX:
    add esp, 4
    .restoreOtherRegs:

    pop ebx
    pop ecx
    pop edx
    pop esi
    pop edi
    iret

[SECTION .data]
interruptHandlerPrimOffset DD (interruptHandlerPrim.entry1 - interruptHandlerPrim.entry0)
interruptNumber DD 0
