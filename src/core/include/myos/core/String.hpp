#pragma once

#include <myos/core/collections/ArrayList.hpp>

namespace myos::core {

class String {
public:
    String(const char *c_str);

    String() = default;

    friend bool operator==(const String &lhs, const String &rhs);

    friend bool operator!=(const String &lhs, const String &rhs) {
        return !(lhs == rhs);
    }

    size_t size() const { return data.size(); }

    size_t length() const { return data.size(); }

    char &operator[](size_t index) { return data[index]; }

    const char operator[](size_t index) const { return data[index]; }

    char &first() { return data.first(); }

    const char &first() const { return data.first(); }

    char &last() { return data.last(); }

    const char &last() const { return data.last(); }

private:
    collections::ArrayList<char> data;
};

}
