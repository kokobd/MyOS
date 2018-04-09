#include <Queue.hpp>
#include <catch2/catch.hpp>

using namespace std::ext;

TEST_CASE("Queue") {
    Queue<int> queue;

    SECTION("Basic") {
        REQUIRE(queue.empty());
        queue.pushBack(2);
        REQUIRE(queue.size() == 1);
        REQUIRE(queue.back() == 2);
    }

    SECTION("Overlap") {
        for (int i = 0; i < queue.maxSize(); ++i) {
            queue.pushBack(i);
        }
        REQUIRE(!queue.empty());
        REQUIRE(queue.size() == queue.maxSize());
        REQUIRE(queue.front() == 0);
        REQUIRE(queue.back() == queue.maxSize() - 1);

        queue.popFront();
        queue.popFront();
        REQUIRE(queue.front() == 2);
        queue.pushBack(5);
        REQUIRE(queue.back() == 5);
        queue.pushBack(7);
        REQUIRE(queue.back() == 7);
        REQUIRE(queue.size() == queue.maxSize());
    }
}