#pragma once

template<typename T>
class Optional {
public:
    Optional(const T &value) : value(value), present(true) {}

    Optional() : present(false) {}

    bool isPresent() { return present; }

    bool getValue() { return value; }

    template<typename F>
    void withValue(F &func) { func(value); }

private:
    T value;
    bool present;
};
