#pragma once

#include <stdlib.h>

size_t strlen(const char *str);

int strcmp(const char *lhs, const char *rhs);

void *memcpy(void *dest, const void *src, size_t count);

void *memset(void *dest, int ch, size_t count);
