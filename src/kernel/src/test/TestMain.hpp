#pragma once

#ifdef DEBUG

namespace myos::kernel::test {

class TestBase;

class TestMain {
private:
    static TestMain testMain;

public:
    static TestMain &instance() {
        return testMain;
    }

    void runAllTests();

    void addTest(TestBase *next);

private:
    TestMain() : firstTest(nullptr), lastTest(nullptr) {}

    TestBase *firstTest;
    TestBase *lastTest;
};

}

#endif