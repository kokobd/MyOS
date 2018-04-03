#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"
#include "shell.h"
#include "filesystem/file.h"
#include "screen/vga.h"

static void initAll();

static char prompt[20] = "MyOS> \0";

int main() {
    initAll();

    kernel_shell_Terminal *terminal = kernel_shell_getGlobalTerminal();
    kernel_shell_termInit(terminal);

    for (char *pt = prompt; *pt != '\0'; ++pt) {
        kernel_shell_termPutChar(terminal, *pt);
    }

    asm(
    "cli\n"
    "hlt"
    );
}

static void initAll() {
    gdtInitialize();
    idtInitialize();
    kernel_syscall_initialize();
    kernel_keyboard_input_initialize();
    kernel_filesystem_file_init();
}

void runProgram(const char *name) {
    int32_t fileHandle = kernel_filesystem_file_fopen(name, 0);

}
