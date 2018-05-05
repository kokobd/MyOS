#include <myos/core/String.hpp>

namespace myos::core {

String::String(const char *c_str) {
    const char *pt = c_str;
    while (*pt != '\0') {
        data.add(*pt);
        ++pt;
    }
}

bool operator==(const String &lhs, const String &rhs) {
    return lhs.data == rhs.data;
}

}
