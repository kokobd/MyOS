#include <catch2/catch.hpp>
#include <array>
#include <myos/core/memory/SimpleHeap.hpp>

using myos::core::memory::Heap;
using myos::core::memory::SimpleHeap;

namespace {

template<typename T>
T *allocate(Heap &heap) {
    return reinterpret_cast<T *>(heap.allocate(sizeof(T)));
}

}

TEST_CASE("memory::SimpleHeap", "[unit]") {
    constexpr size_t MAX_SIZE = 2048;
    std::vector<uint8_t> mem(MAX_SIZE);

    SimpleHeap heap(mem.data(), MAX_SIZE);
    SECTION("allocate and deallocate") {
        auto *x = allocate<uint32_t>(heap);
        *x = 12;
        auto *y = allocate<uint32_t>(heap);
        *y = 42;
        REQUIRE(*x == 12);
        REQUIRE(*y == 42);
        REQUIRE(x != y);

        heap.deallocate(x);
        REQUIRE(*y == 42);
        heap.deallocate(y);

        x = allocate<uint32_t>(heap);
        y = allocate<uint32_t>(heap);
        *x = 5;
        *y = 20;
        REQUIRE(x != y);
        REQUIRE(*x == 5);
        REQUIRE(*y == 20);
    }

    SECTION("memory exhausted") {
        allocate<uint32_t>(heap);
        auto *y = heap.allocate(2048);
        REQUIRE(y == nullptr);
        auto *x = allocate<uint32_t>(heap);
        REQUIRE(x != nullptr);
    }
}
