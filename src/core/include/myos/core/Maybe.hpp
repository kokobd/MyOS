#pragma once

#include <myos/core/Function.hpp>

namespace myos::core {

template<typename E>
class Maybe {
public:
    static Maybe just(const E &value);

    static Maybe nothing();

    Maybe(const Maybe &that);

    Maybe &operator=(const Maybe &that);

    ~Maybe();

    void match(Function<void(const E &value)> &onJust, Function<void()> &onNothing);

    bool isJust() const {
        return present;
    }

    bool isNothing() const {
        return !present;
    }

private:
    Maybe();

    uint8_t data[sizeof(E)];
    bool present;

    E &dataToValue();

    const E &dataToValue() const;

    void assignValue(const E &value);

    template<typename U>
    friend Maybe<U> fmap(const Maybe<U> &maybe, Function<U(const U &)> &f);
};

template<typename E>
E &Maybe<E>::dataToValue() {
    return *reinterpret_cast<E *>(data);
}

template<typename E>
const E &Maybe<E>::dataToValue() const {
    return *reinterpret_cast<const E *>(data);
}

template<typename E>
Maybe<E> Maybe<E>::just(const E &value) {
    Maybe ret;
    ret.assignValue(value);
    ret.present = true;
    return ret;
}

template<typename E>
Maybe<E> Maybe<E>::nothing() {
    return Maybe();
}

template<typename E>
Maybe<E>::Maybe()
        : present(false) {
}

template<typename E>
void Maybe<E>::assignValue(const E &value) {
    new(data) E(value);
}

template<typename E>
Maybe<E>::Maybe(const Maybe &that) {
    this->present = that.present;
    if (that.present)
        assignValue(that.dataToValue());
}

template<typename E>
Maybe<E> &Maybe<E>::operator=(const Maybe &that) {
    if (this != &that) {
        if (this->present)
            dataToValue().~E();

        this->present = that.present;
        if (that.present)
            assignValue(that.dataToValue());
    }

    return *this;
}

template<typename E>
Maybe<E>::~Maybe() {
    if (present) {
        dataToValue().~E();
    }
}

template<typename E>
void Maybe<E>::match(Function<void(const E &)> &onJust, Function<void()> &onNothing) {
    if (present) {
        onJust(dataToValue());
    } else {
        onNothing();
    }
}

template<typename E>
Maybe<E> fmap(const Maybe<E> &maybe, Function<E(const E &)> &f) {
    return maybe.present ?
           Maybe<E>::just(f(maybe.dataToValue())) :
           Maybe<E>::nothing();
}

}
