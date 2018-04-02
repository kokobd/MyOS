#include <stdbool.h>
#include <stdint.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"
#include "shell.h"

static void initHardware();

int main() {
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
