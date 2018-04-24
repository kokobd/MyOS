#pragma once

#ifdef DEBUG

namespace myos::kernel::test {

class TestBase {
    friend class TestMain;

public:
    TestBase();

    virtual ~TestBase() = default;

    void run();

private:
    TestBase *nextTest;

    bool passed;

protected:
    virtual void init() {}

    virtual void test() = 0;

    void assertTrue(bool condition, const char *assertionName);

    template<typename T>
    void assertEquals(const T &expected, const T &actual, const char *assertionName) {
        assertTrue(expected == actual, assertionName);
    }
};

}

#endif
