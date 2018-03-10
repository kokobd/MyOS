bits 16
org 0x0

jmp main

print:
    lodsb
    or al, al
    jz print_done
    mov ah, 0eh
    int 10h
    jmp print
print_done:
    ret

main:
    cli
    push cs
    pop ds

    mov si, msg
    call print

    call waitForASecond

    mov si, msg
    call print

    mov si, greeting
    call print

    cli
    hlt

    ; start waiting
waitForASecond:
    push ax
    push bx
    push dx
    mov ah, 00h
    int 1ah
    mov bx, dx
.waiting:
    mov ah, 00h
    int 1ah
    sub dx, bx
    cmp dx, 18 ;wait for 18 * 55ms
    jle .waiting
    pop dx
    pop bx
    pop ax
    ret
    ; end waiting

msg db "Preparing to load operating system...", 13, 10, 0

greeting db "Hello!", 13, 10, 0