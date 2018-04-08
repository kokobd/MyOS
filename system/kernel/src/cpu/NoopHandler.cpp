#include <myos/kernel/cpu/NoopHandler.hpp>

namespace myos::kernel::cpu {

void NoopHandler::handleInterrupt(InterruptType interrupt, const RegisterState &registerState) {
    // do nothing
}

}
