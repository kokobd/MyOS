#pragma once

namespace myos::core {

template<typename>
class Function;

template<typename R, typename... Args>
class Function<R(Args...)> {
public:
    template<typename F>
    Function(const F &f) {
        callable = new CallableF<F>(f);
    }

    Function(const Function<R(Args...)> &that) = delete;

    Function<R(Args...)> &operator=(const Function<R(Args...)> &that) = delete;

    Function(Function<R(Args...)> &&that) noexcept {
        callable = that.callable;
        that.callable = nullptr;
    }

    Function<R(Args...)> &operator=(Function<R(Args...)> &&that) {
        if (this != &that) {
            delete callable;
            callable = that.callable;
            that.callable = nullptr;
        }
        return *this;
    }

    R operator()(Args... args) {
        return callable->invoke(args...);
    }

    ~Function() {
        delete callable;
    }

private:
    class ICallable {
    public:
        virtual ~ICallable() = default;
        virtual R invoke(Args... args) = 0;
    };

    template<typename F>
    class CallableF : public ICallable {
    public:
        explicit CallableF(const F &f) : f(f) {}

        ~CallableF() override = default;

        R invoke(Args... args) override {
            return f(args...);
        }
    private:
        F f;
    };

    ICallable *callable;
};

}
