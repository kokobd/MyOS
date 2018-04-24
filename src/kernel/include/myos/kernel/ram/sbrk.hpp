#pragma once

#include <cstdint>

namespace myos::kernel::ram::sbrk {

void *sbrk(intptr_t diff);

}
