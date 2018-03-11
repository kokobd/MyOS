bits 16
org 0x0

cli
push cs
pop ds
call showInfo

mov ax,0xB800
mov es,ax

;set background color
xor ax, ax
loop1:
    cmp ax, 24
    jg exit1
    xor bx, bx
    loop2:
        cmp bx, 79
        jg exit2
        mov si, 80
        imul si, ax
        add si, bx
        imul si, 2 ; si = ((80 * ax) + bx) * 2
        mov byte [es:si + 1], 0x70
        inc bx
        jmp loop2
    exit2:
    inc ax
    jmp loop1
exit1:
    ;trace of 'A' 
    mov byte [es:((80 * 2) + 0) * 2 ], 'A'
    mov byte [es:((80 * 2) + 0) * 2 + 1 ], 0xF0
    mov ax, 0
    mov bx, 2
    mov cx, 1
    mov dx, 1
    mov di, 0x00F1
loop3:
    trace:
        add ax, cx
        add bx, dx
        mov si, 80
        imul si, bx
        add si, ax
        imul si, 2 ; si = ((80 * bx) + ax) * 2        
        call waitForASecond
        mov byte [es:si], 'A'
        ;color
        push ax
        mov ax, di
        or al, 0xF0
        mov byte [es:si + 1], al
        pop ax
        inc di
    cmpax:
        cmp ax, 79
        jl cmpax2
        imul cx, -1
    cmpax2:
        cmp ax, 0
        jg cmpbx
        imul cx, -1
        cmpbx:
            cmp bx, 24
            jl cmpbx2
            imul dx, -1
            jmp trace
        cmpbx2:
            cmp bx, 2
            jg trace
            imul dx, -1   
    jmp loop3
exit3:
    ;halt
    cli
    hlt

    ; start waiting
waitForASecond:
    push ax
    push bx
    push cx
    push dx
    mov ah, 00h
    int 1ah
    mov bx, dx
.waiting:
    mov ah, 00h
    int 1ah
    sub dx, bx
    cmp dx, 1 ;wait for 1 * 55ms
    jle .waiting
    pop dx
    pop cx
    pop bx
    pop ax
    ret
    ; end waiting
    times 510-($-$$) db 0 ; Pad remainder of boot sector with 0s
    dw 0xAA55 ; The standard PC boot signature

showInfo:
    mov si, info
    call print
    mov si, split
    call print


    ret
print:
    lodsb        
    or al, al
    jz print_done ;done if al is 0
    mov ah, 0eh
    int 10h
    jmp	print
print_done:
    ret

info DB "16337060 zelin, 16337063 kaifeng |", 10, 13, 0
split DB "----------------------------------", 10, 13, 0