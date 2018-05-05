#pragma once

#include "../Kernel.hpp"
namespace myos::kernel::debug {

inline void traceConsole(const char *c_str) {
#ifdef DEBUG
    Kernel::getCurrentKernel().getShell().putString(c_str);
#endif
}

}
