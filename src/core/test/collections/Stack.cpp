#include <catch2/catch.hpp>
#include <myos/core/collections/Stack.hpp>
#include <cstdint>

using myos::core::collections::Stack;

TEST_CASE("collections::Stack") {
    constexpr size_t MAX_SIZE = 32;
    Stack<int32_t, MAX_SIZE> stack;

    SECTION("empty") {
        REQUIRE(stack.empty());
        REQUIRE(stack.size() == 0);
        REQUIRE_FALSE(stack.full());
    }

    SECTION("push, check, pop") {
        for (size_t i = 0; i < MAX_SIZE; ++i) {
            stack.push(static_cast<const int32_t &>(i));
            REQUIRE(stack.size() == i + 1);
            REQUIRE_FALSE(stack.empty());
            REQUIRE(stack.top() == i);
        }

        REQUIRE(stack.full());

        stack.pop();
        REQUIRE(!stack.full());
        REQUIRE(stack.top() == MAX_SIZE - 2);
        stack.pop();
        REQUIRE(stack.top() == MAX_SIZE - 3);

        for (size_t i = 0; i < MAX_SIZE - 2; ++i) {
            REQUIRE_FALSE(stack.empty());
            stack.pop();
        }
        REQUIRE(stack.empty());
    }
}
