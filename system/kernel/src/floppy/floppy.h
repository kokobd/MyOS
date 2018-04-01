#pragma once

#include <stdint.h>

/**
 * Load a single sector (512 bytes) from floppy disk
 * @param buffer where the data should be placed in memory
 * @param lba logical block address, i.e., the sector index,
 * counting from 0
 * @return 0 on success, other values on failure.
 */
void loadSector(uint8_t *buffer, uint32_t lba);
