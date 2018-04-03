#pragma once

#include <stdint.h>

#pragma push_macro("NS")
#define NS(X) kernel_filesystem_file_ ## X

void NS(init)();

int32_t NS(fopen)(const char *fileName, uint32_t flags);

int32_t NS(fread)(int32_t fileHandle, uint8_t *dest, size_t limit);

int32_t NS(fclose)(int32_t fileHandle);

#pragma pop_macro("NS")
