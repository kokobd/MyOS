#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);

#ifdef __cplusplus
}
#endif

