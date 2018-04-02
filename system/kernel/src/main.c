#include <stdbool.h>
#include <stdint.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"
#include "shell.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

static void initHardware();

// TODO remove this function
// prints x in reverse order.
void itoa(uint8_t x, char *buf) {
    int i = 0;
    if (x == 0) {
        buf[i++] = '0';
    }
    while (x > 0) {
        int digit = x % 10;
        buf[i++] = (char) (digit + '0');
        x /= 10;
    }
    buf[i] = '\0';
}


void _start() {
    initHardware();

    kernel_shell_Terminal terminal;
    kernel_shell_termInit(&terminal);

    char prompt[] = "MyOS> \0";
    for (char *pt = prompt; *pt != '\0'; ++pt) {
        kernel_shell_termPutChar(&terminal, *pt);
    }

    char ch = '\0';
    while (ch != '\n') {
        ch = kernel_shell_termGetChar(&terminal);
        kernel_shell_termPutChar(&terminal, ch);
    }

    asm(
    "cli\n"
    "hlt"
    );
}

static void initHardware() {
    gdtInitialize();
    idtInitialize();
    kernel_syscall_initialize();
    kernel_keyboard_input_initialize();
}


#pragma clang diagnostic pop
