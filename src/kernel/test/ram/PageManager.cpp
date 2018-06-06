#include <catch2/catch.hpp>
#include <myos/kernel/ram/PageManager.hpp>

using myos::kernel::ram::PageManager;

TEST_CASE("ram::PageManager") {
    const uintptr_t START = 0x200000;
    const size_t PAGE_SIZE = 4096;
    const size_t PAGE_COUNT = 256;
    PageManager pageManager(START, PAGE_SIZE, PAGE_COUNT);

    SECTION("basic allocate and release") {
        uintptr_t f1 = pageManager.newPage();
        uintptr_t f2 = pageManager.newPage();
        REQUIRE(f1 == START);
        REQUIRE(f2 == START + PAGE_SIZE);
        pageManager.releasePage(f1);
        REQUIRE(pageManager.newPage() == START);
        pageManager.releasePage(f2);
    }

    SECTION("share page frame") {
        uintptr_t f1 = pageManager.newPage();
        REQUIRE(pageManager.processCount(f1) == 1);
        ++pageManager.processCount(f1);
        REQUIRE(pageManager.processCount(f1) == 2);
        pageManager.processCount(f1) -= 2;
        REQUIRE(pageManager.processCount(f1) == 0);
        REQUIRE(pageManager.newPage() == f1);
    }
}