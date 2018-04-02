#include <stdbool.h>
#include <stdint.h>
#include "hal/gdt.h"
#include "hal/idt.h"
#include "syscall/syscall.h"
#include "keyboard/input.h"

void _start() {
    gdtInitialize();
    idtInitialize();
    kernel_syscall_initialize();
    kernel_keyboard_input_initialize();

}
