#include <catch2/catch.hpp>
#include <myos/core/memory.hpp>
#include <myos/core/utility.hpp>

using myos::core::memory::shared_ptr;
using myos::core::utility::move;

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

    int getAnswer() {
        return 42;
    }

private:
    Stat &stat;
};

}

TEST_CASE("memory::shared_ptr", "[unit]") {
    SECTION("destructor") {
        Demo::Stat s1, s2;
        REQUIRE_FALSE(s1.dtor_called);
        REQUIRE_FALSE(s2.dtor_called);

        SECTION("copy ctor") {
            {
                shared_ptr<Demo> p1(new Demo(s1));
                {
                    shared_ptr<Demo> p2(p1);
                    REQUIRE(&(*p1) == &(*p2));
                }
                REQUIRE_FALSE(s1.dtor_called);
            }
            REQUIRE(s1.dtor_called);
        }
        SECTION("copy assignment") {
            {
                shared_ptr<Demo> p1(new Demo(s1));
                shared_ptr<Demo> p2(new Demo(s2));
                REQUIRE_FALSE(s1.dtor_called);
                REQUIRE_FALSE(s2.dtor_called);
                p2 = p1;
                REQUIRE(s2.dtor_called);
            }
            REQUIRE(s1.dtor_called);
        }
        SECTION("move ctor") {
            shared_ptr<Demo> p1(new Demo(s1));
            {
                shared_ptr<Demo> p2(move(p1));
            }
            REQUIRE(s1.dtor_called);
        }
        SECTION("move assignment") {
            {
                shared_ptr<Demo> p1(new Demo(s1));
                shared_ptr<Demo> p2(move(p1));
                REQUIRE(p1 == nullptr);
                REQUIRE_FALSE(s1.dtor_called);
            }
            REQUIRE(s1.dtor_called);
        }
        SECTION("* and ->") {
            shared_ptr<Demo> p1(new Demo(s1));
            REQUIRE((*p1).getAnswer() == 42);
            REQUIRE(p1->getAnswer() == 42);
        }
    }
}
