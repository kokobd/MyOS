#pragma once

#include <stdint.h>

#pragma push_macro("NAMESPACE")
#define NAMESPACE(X) kernel_filesystem_file_ ## X

int32_t NAMESPACE(fopen)(const char *fileName, uint32_t flags);

#pragma pop_macro("NAMESPACE")
