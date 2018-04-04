#pragma once

#include <stdint.h>

int putchar(int ch);

int getchar();

int puts(const char *str);

/**
 * Non standard function.
 * @return the file size. 0 if it doesn't exist.
 */
size_t getFileSize(const char *fileName);

const char *getArgs();