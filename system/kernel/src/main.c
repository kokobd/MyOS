#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"
#include "shell.h"
#include "filesystem/file.h"
#include "screen/vga.h"

static void initAll();


int main() {
    initAll();

    kernel_shell_Terminal *terminal = kernel_shell_getGlobalTerminal();
    kernel_shell_termInit(terminal);

    size_t INPUT_LIMIT = 120;
    char input[INPUT_LIMIT];
    input[INPUT_LIMIT - 1] = '\0';
    while (strcmp(input, "EXIT") != 0) {
        kernel_shell_termPutString(terminal, "MyOS 0.1> ");
        kernel_shell_termReadLine(terminal, input, INPUT_LIMIT - 1);
        kernel_shell_termPutString(terminal, input);
    }

    kernel_shell_termPutString(terminal, "Exited.\n");
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
