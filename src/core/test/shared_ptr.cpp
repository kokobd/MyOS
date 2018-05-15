#include <catch2/catch.hpp>
#include <myos/core/memory.hpp>

using myos::core::memory::shared_ptr;

namespace {

class Demo {
public:
    struct Stat {
        bool dtor_called = false;
    public:
        Stat() = default;
    };

    explicit Demo(Stat &stat) : stat(stat) {}

    ~Demo() {
        stat.dtor_called = true;
    }

private:
    Stat &stat;
};

}

TEST_CASE("memory::shared_ptr", "[unit]") {
    Demo::Stat s1, s2;
    shared_ptr<Demo> p1(new Demo(s1));
    shared_ptr<Demo> p2(new Demo(s2));
    REQUIRE_FALSE(s1.dtor_called);
    REQUIRE_FALSE(s2.dtor_called);
    p2 = p1;
    REQUIRE(s2.dtor_called);
}
