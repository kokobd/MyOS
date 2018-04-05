#include <string.h>

size_t strlen(const char *str) {
    size_t length = 0;
    if (str == NULL)
        return length;
    while (*str != '\0') {
        ++length;
        ++str;
    }
    return length;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *rhs != '\0') {
        if (*lhs < *rhs)
            return -1;
        else if (*lhs > *rhs)
            return 1;
        ++lhs;
        ++rhs;
    }
    if (*lhs == '\0') {
        if (*rhs == '\0')
            return 0;
        else  // rhs is longer
            return -1;
    } else
        return 1;
}

void *memcpy(void *dest, const void *src, size_t count) {
    uint8_t *dest_ = (uint8_t *) dest;
    uint8_t *src_ = (uint8_t *) src;
    for (size_t i = 0; i != count; ++i) {
        dest_[i] = src_[i];
    }
    return dest;
}

void *memset(void *dest, int ch, size_t count) {
    for (size_t i = 0; i != count; ++i) {
        ((uint8_t *) dest)[i] = (uint8_t) ch;
    }
    return dest;
}