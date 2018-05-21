#include <catch2/catch.hpp>
#include <myos/core/memory/smart_pointers/shared_ptr.hpp>
#include <myos/core/memory/smart_pointers/unique_ptr.hpp>
#include <myos/core/memory/smart_pointers/weak_ptr.hpp>
#include <myos/core/utility.hpp>

using myos::core::memory::smart_pointers::shared_ptr;
using myos::core::memory::smart_pointers::unique_ptr;
using myos::core::memory::smart_pointers::weak_ptr;
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

    int getAnswer() const {
        return 43;
    }

private:
    Stat &stat;
};

class Sub : public Demo {
public:
    Sub(Stat &stat) : Demo(stat) {}
};

}

TEST_CASE("memory::smart_pointers", "[unit]") {
    Demo::Stat s1, s2;
    REQUIRE_FALSE(s1.dtor_called);
    REQUIRE_FALSE(s2.dtor_called);

    SECTION("shared_ptr") {
        SECTION("copy ctor") {
            {
                shared_ptr<Demo> p1(new Demo(s1));
                REQUIRE(p1.use_count() == 1);
                {
                    shared_ptr<Demo> p2(p1);
                    REQUIRE(p1.use_count() == 2);
                    REQUIRE(p2.use_count() == 2);
                    REQUIRE(&(*p1) == &(*p2));
                    REQUIRE(p1.get() == p2.get());
                }
                REQUIRE(!s1.dtor_called);
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
                REQUIRE(p1.get() == p2.get());
                REQUIRE(s2.dtor_called);
            }
            REQUIRE(s1.dtor_called);
        }
        SECTION("move ctor") {
            shared_ptr<Demo> p1(new Demo(s1));
            {
                shared_ptr<Demo> p2(move(p1));
                REQUIRE(p1.use_count() == 0);
                REQUIRE(p2.use_count() == 1);
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
            const shared_ptr<Demo> p2(new Demo(s2));
            REQUIRE((*p2).getAnswer() == 43);
            REQUIRE(p2->getAnswer() == 43);
        }
    }

    SECTION("convert unique_ptr to shared_ptr") {
        Demo *raw_obj = new Demo(s1);
        unique_ptr<Demo> p1(raw_obj);
        REQUIRE(p1 != nullptr);
        shared_ptr<Demo> p2(move(p1));
        REQUIRE(p1 == nullptr);
        REQUIRE(p2.get() == raw_obj);
    }

    SECTION("unique_ptr") {
        Demo::Stat s3;
        {
            unique_ptr<Demo> p1(new Demo(s1));
            unique_ptr<Demo> p2(new Sub(s2));
            unique_ptr<Demo> p3 = unique_ptr<Sub>(new Sub(s3));
        }
        REQUIRE(s1.dtor_called);
        REQUIRE(s2.dtor_called);
        REQUIRE(s3.dtor_called);
    }

    SECTION("weak_ptr") {
        weak_ptr<Demo> wp1;
        {
            shared_ptr<Demo> p1(new Demo(s1));
            wp1 = p1;
            shared_ptr<Demo> p2 = wp1.lock();
            REQUIRE(p2.use_count() == 2);
            REQUIRE(p1.use_count() == 2);
            REQUIRE(p1 == p2);
        }
        CHECK(s1.dtor_called);
        CHECK(wp1.expired());
        CHECK(wp1.use_count() == 0);
    }
}
