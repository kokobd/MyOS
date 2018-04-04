#include "elf32.h"
#include "../filesystem/file.h"
#include "../screen/vga.h"

#define NS(X) kernel_exec_elf32_ ## X

int32_t NS(load)(int32_t fileHandle, uint8_t *dest) {
    size_t fileSize = kernel_filesystem_file_fGetSize(fileHandle);
    kernel_filesystem_file_fread(fileHandle, dest, fileSize);
}

void NS(execute)(uint8_t *image) {
    uint32_t entry = *(uint32_t *) (image + 0x18);
    void (*program)() = (void (*)()) entry - 0x08048000 + 0x200000;
    program();
}
