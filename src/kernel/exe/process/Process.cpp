#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/Kernel.hpp>
#include <cstring>
#include <myos/kernel/ram/Memory.hpp>

using myos::kernel::ram::Memory;

#define PAGE_SIZE (ram::IPageTable<PageTable>::pageSize())
#define PAGE_SHIFT (ram::IPageTable<PageTable>::pageShift())

namespace myos::kernel::process {

Process::Process(const uint8_t *imageAddress, ram::PageManager &pageManager)
        : pageTable(ram::IPageTable<PageTable>::newInstance(Memory::userSpaceEnd())),
          occupiedPages(128),
          pageManager(pageManager) {
    ELFImage image(reinterpret_cast<uintptr_t>(imageAddress));
    // 1. 算出需要的页框数量，申请这些页框。
    // 2. 把0x400000开始的足够多的虚内存映射到这些页框
    initPages(image);
    // 3. 安装页表
    pageTable->installToCPU();
    // 4. 根据ProgramHeader中的信息，把imageAddress处的内容复制到0x400000
    bool loadSucceeded =
            image.loadWithCheck(Memory::userSpaceStart(), Memory::userSpaceStart() + programBreak);
    valid = loadSucceeded;
}

void Process::replace(const uint8_t *loadedImageAddress, size_t loadedImageSize) {
// 另一种加载进程的情形：exec系统调用
// 1. 进程执行用户级代码，将映像载入进程自有内存，并保证载入地址对齐到页大小
// 2. 调用exec系统调用，OS内核负责调整页表：
//    a. 内核查询页表，得到新映像占据的页框(记为集合S)
//    b. 告知PageManager释放全部页框（除去栈和S）
//    c. 把新映像对应的页表项拷贝到0x400000开始的页表项

    // 这个方法实现的是调整页表的步骤
    // 我们先释放掉旧页框，再把新程序重映射到进程起始地址。

    const uintptr_t loadedImageBegin = reinterpret_cast<const uintptr_t>(loadedImageAddress);
    const uintptr_t loadedImageEnd = loadedImageBegin + loadedImageSize;

    // traverse all pages before program-break,
    // and release the old pages.
    for (uintptr_t vaddr = Memory::userSpaceStart(); vaddr < programBreak; vaddr += PAGE_SIZE) {
        // if the page is in use by the loaded image
        if (vaddr < loadedImageEnd
            && vaddr >= loadedImageBegin) {
            // ignore it
            continue;
        } else {
            // release the page frame
            releasePage(vaddr);
        }
    }

    // remap the loaded image
    uintptr_t dest = Memory::userSpaceStart();
    for (uintptr_t vaddr = loadedImageBegin; vaddr < loadedImageEnd; vaddr += PAGE_SIZE) {
        movePage(vaddr, dest);
        dest += PAGE_SIZE;
    }
}

Process::Process(const Process &that)
        : registerState(that.registerState),
          pageTable(ram::IPageTable<PageTable>::copyInstance(that.pageTable)),
          occupiedPages(that.occupiedPages),
          pageManager(that.pageManager) {
    // TODO Copy-on-Write -- 进程复制阶段
    // 1. 复制一份页表。
    // 2. 调用PageManager的方法，将当前进程添加到正在使用的每个页框的进程列表中。
    //    如果某个列表长度变成2，设置两个进程的页表中该页框为“只读“
    // 3. 设置父进程的eax为子进程PID，设置子进程的eax为0.（eax是系统调用的返回值）

    // fork 系统调用的执行过程
    // 1. 用户进程X发起fork，控制权交给内核
    // 2. 复制一个Process对象Y，将新的shared_ptr<Process>插入就绪队列中
    // 3. 中断处理完毕，退回进程X。X看到自己的eax是Y的PID
    // 4. 发生时钟中断，调度下一个进程来执行。
    // ...
    // 5. 轮到Y来执行，Y会看到自己的eax是0，进而知道自己是子进程
}

Process::~Process() {
    // TODO Copy-on-Write -- 进程退出阶段
    // 告知PageManager，遍历当前进程占有的每个页框，将本进程从各个页框的进程列表中移除。并检查，
    //   如果某个进程列表中只剩一个进程，设置那个进程的页表中该页框的属性为“可读可写”
}

// TODO Copy-on-Write -- 写入阶段
// 这部分代码应当放在页错误的处理函数中。
//   1. 获取发生页错误的页
//   2. 根据当前进程查询该页的属性以及页框，如果属性为“只读”，并且该页框有多个进程
//      在同时使用，则申请一个新的页框，把这个页框的内容复制过去，然后把当前进程的
//      页表中当前页指向新页框，接着返回用户进程。

void Process::allocPage(uintptr_t vaddr) {
    uintptr_t pf = pageManager.newPage();
    occupiedPages.set(pf >> PAGE_SHIFT);
    pageTable->setPageAddress(vaddr, pf);
    pageTable->setPageFlags(vaddr, (ram::IPageTable<PageTable>::Flags)
            (ram::IPageTable<PageTable>::WRITABLE |
             ram::IPageTable<PageTable>::PRESENT));
}

void Process::releasePage(uintptr_t vaddr) {
    ram::IPageTable<PageTable>::Flags flags;
    uintptr_t paddr = pageTable->getPage(vaddr, flags);
    pageTable->setPageFlags(vaddr, ram::IPageTable<PageTable>::NONE);

    occupiedPages.set(paddr >> PAGE_SHIFT, false);
    pageManager.releasePage(paddr);
}

void Process::initPages(const ELFImage &image) {
    // number of pages required, excluding stack.
    const size_t pagesRequired = image.sizeInMemory() >> PAGE_SHIFT;
    uintptr_t vaddr = Memory::userSpaceStart();
    for (size_t i = 0; i < pagesRequired; ++i) {
        allocPage(vaddr);
        vaddr += PAGE_SIZE;
    }
    programBreak = vaddr;

    uintptr_t stackVaddr = Memory::userSpaceEnd() - PAGE_SIZE + 1;
    allocPage(stackVaddr);
}

Process::operator bool() {
    return valid;
}

void Process::movePage(uintptr_t from, uintptr_t to) {
    ram::IPageTable<PageTable>::Flags flags;
    uintptr_t pf = pageTable->getPage(from, flags);
    pageTable->setPageAddress(to, pf);
    pageTable->setPageFlags(to, flags);
    pageTable->setPageFlags(from, ram::IPageTable<PageTable>::NONE);
}


}
