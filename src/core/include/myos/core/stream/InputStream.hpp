#pragma once

#include <myos/core/Function.hpp>

namespace myos::core::stream {

template<typename E>
class InputStream {
public:
    virtual bool hasNext() const = 0;

    virtual E &next() = 0;
};

}
