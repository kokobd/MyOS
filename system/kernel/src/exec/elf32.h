#pragma once

#include <stdint.h>

#pragma push_macro("NS")

#define NS(X) kernel_exec_elf32_ ## X

/**
 * Load an ELF32 executable to memory.
 * Currently, .data section is NOT handled correctly,
 * as we are planning to rewrite our file API.
 * @param fileHandle the file handle
 * @param dest the base address to put the executable
 * @return -1 on error, 0 on success.
 */
int32_t NS(load)(int32_t fileHandle, uint8_t *dest);

/**
 * Start execution of the ELF32 executable.
 * @param image the base address of the image in memory.
 */
void NS(execute)(uint8_t *image);

#pragma pop_macro("NS")
