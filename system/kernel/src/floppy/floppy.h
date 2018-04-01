#pragma once

#include <stdint.h>

#pragma push_macro("NS")
#define NS(X) kernel_floppy_ ## X

/**
 * Load a single sector (512 bytes) from floppy disk
 * @param buffer where the data should be placed in memory
 * @param lba logical block address, i.e., the sector index,
 * counting from 0
 * @return 0 on success, other values on failure.
 */
int32_t NS(loadSector)(uint8_t *buffer, uint32_t lba);

#pragma pop_macro("NS")
