#include <catch2/catch.hpp>
#include <myos/core/collections/Queue.hpp>
#include <cstdint>

using myos::base::collections::Queue;

TEST_CASE("collections::Queue") {
    constexpr size_t MAX_SIZE = 32;
    Queue<int32_t, MAX_SIZE> queue;

    SECTION("Empty queue") {
        REQUIRE(queue.size() == 0);
        REQUIRE(queue.empty());
        REQUIRE(queue.maxSize() == MAX_SIZE);
    }

    SECTION("With some elements") {
        for (size_t i = 0; i < MAX_SIZE; ++i) {
            queue.pushBack(static_cast<int32_t>(i));
            REQUIRE(queue.size() == i + 1);
            REQUIRE(queue.back() == i);
            REQUIRE(!queue.empty());
        }
        REQUIRE(queue.size() == queue.maxSize());
        REQUIRE(queue.front() == 0);

        queue.popFront();
        queue.popFront();
        queue.popFront();
        REQUIRE(queue.size() == queue.maxSize() - 3);
        REQUIRE(!queue.empty());
        REQUIRE(queue.front() == 3);

        queue.pushBack(123);
        REQUIRE(queue.back() == 123);
        queue.pushBack(234);
        REQUIRE(queue.back() == 234);
    }
}
