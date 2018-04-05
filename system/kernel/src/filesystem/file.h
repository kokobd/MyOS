#pragma once

#include <stdint.h>
#include <stddef.h>

#pragma push_macro("NS")
#define NS(X) kernel_filesystem_file_ ## X

void NS(init)();

int32_t NS(fopen)(const char *fileName, uint32_t flags);

/**
 * Read a file from the filesystem.
 * For now, limit MUST be equal or larger than the size of file.
 * Otherwise, -1 will be returned.
 */
int32_t NS(fread)(int32_t fileHandle, uint8_t *dest, size_t limit);

int32_t NS(fclose)(int32_t fileHandle);

const char *NS(fGetName)(int32_t fileHandle);

size_t NS(fGetSize)(int32_t fileHandle);

#pragma pop_macro("NS")
