#include "TestBase.hpp"

namespace myos::kernel::test {

TestBase::TestBase()
        : passed(true) {
    init();
}

void TestBase::run() {
    test();
    if (passed) {
        // TODO print message to show that the test succeeds.
    } else {
        // TODO print message to show that the test fails.
    }
}

void TestBase::assertTrue(bool condition, const char *assertionName) {
    // TODO print errorMessage
    if (condition) {

    } else {

        passed = false;
    }
}

}
