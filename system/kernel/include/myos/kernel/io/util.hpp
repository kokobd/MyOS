#pragma once

#include <cstdint>

namespace myos::kernel::io::util {

uint8_t inb(uint32_t port);

void outb(uint32_t port, uint8_t data);

}
