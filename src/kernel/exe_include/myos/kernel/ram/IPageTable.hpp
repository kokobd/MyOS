#pragma once

#include <cstddef>
#include <myos/core/memory/smart_pointers/unique_ptr.hpp>
#include <myos/core/cstdint>

namespace myos::kernel::ram {

/**
 * Interface that describes a page table.
 * This class uses static polymorphism, rather than virtual methods.
 * @tparam Impl the actual Implementation class
 */

template<typename Impl>
class IPageTable {
    template<typename T>
    using unique_ptr = core::memory::smart_pointers::unique_ptr<T>;
public:
    /**
     * Construct a page table instance.
     * By default, all physical addresses are mapped identically,
     * marked non-writable and only accessible to kernel.
     * @return pointer to a new page table instance
     */
    static unique_ptr<IPageTable<Impl>> newInstance(uintptr_t maxAddress) {
        return unique_ptr<IPageTable<Impl>>(new Impl(maxAddress));
    }

    static unique_ptr<IPageTable<Impl>> copyInstance(const unique_ptr<IPageTable<Impl>> &that) {
        return unique_ptr<IPageTable<Impl>>(new Impl(
                static_cast<const Impl &>(*that.get())
        ));
    }

    static constexpr size_t pageSize() {
        return Impl::pageSize_impl();
    }

    static constexpr size_t pageShift() {
        return Impl::pageShift_impl();
    }

private:
    Impl &subInstance() {
        return *(static_cast<Impl *>(this));
    }

    const Impl &subInstance() const {
        return *(static_cast<const Impl *>(this));
    }

public:
    virtual ~IPageTable() = default;

    enum Flags {
        NONE = 0b00,
        WRITABLE = 0b01,
        KERNEL = 0b10 // kernel pages, not accessible by user code
    };

    bool setPageAddress(void *vaddr, void *paddr) {
        return subInstance().setPageAddress_impl(vaddr, paddr);
    }

    bool setPageFlags(void *vaddr, Flags flags) {
        return subInstance().setPageFlags_impl(vaddr, flags);
    }

    void *getPage(void *vaddr, Flags &flags) {
        return subInstance().getPage_impl(vaddr, flags);
    }

    void installToCPU() const {
        return subInstance().installToCPU_impl();
    }
};

}
