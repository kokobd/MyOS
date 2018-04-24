#ifdef DEBUG

#include "TestMain.hpp"
#include "TestBase.hpp"
//#include <myos/kernel/debug/trace.hpp>

namespace myos::kernel::test {

void TestMain::runAllTests() {
    for (TestBase *pt = firstTest; pt != nullptr; pt = pt->nextTest) {
        pt->run();
    }
}

void TestMain::addTest(TestBase *next) {
    if (firstTest == nullptr) {
        firstTest = lastTest = next;
    } else {
        lastTest->nextTest = next;
        lastTest = lastTest->nextTest;
    }
}

}

#endif
