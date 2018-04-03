#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"
#include "shell.h"

static void initHardware();

int main() {
    initHardware();

    kernel_shell_Terminal *terminal = kernel_shell_getGlobalTerminal();
    kernel_shell_termInit(terminal);

    char prompt[] = "MyOS> \0";
    for (char *pt = prompt; *pt != '\0'; ++pt) {
        kernel_shell_termPutChar(terminal, *pt);
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
