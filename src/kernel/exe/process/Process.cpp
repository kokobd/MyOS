#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/Kernel.hpp>
#include <cstring>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/process/ELFImage.hpp>

using myos::kernel::ram::Memory;

namespace myos::kernel::process {

Process::Process(const char *imageAddress, ram::PageManager &pageManager)
        : pageTable(ram::IPageTable<PageTable>::newInstance(Memory::userSpaceEnd())),
          occupiedPages(128),
          pageManager(pageManager) {
    ELFImage image(reinterpret_cast<uintptr_t>(imageAddress));

    // TODO
    // 1. 算出需要的页框数量，申请这些页框。
    // 2. 把0x400000开始的足够多的虚内存映射到这些页框
    // 3. 如果还没启用分页，现在启用
    // 4. 安装页表
    // 5. 根据ProgramHeader中的信息，把imageAddress处的内容复制到0x400000

    // 另一种加载进程的情形：exec系统调用
    // 1. 进程执行用户级代码，将映像载入进程自有内存，并保证载入地址对齐到页大小
    // 2. 调用exec系统调用，OS内核负责调整页表：
    //    a. 内核查询页表，得到新映像占据的页框(记为集合S)
    //    b. 调用PageManager的方法，释放所有页框，然后声明占有S中的所有页框
    //    c. 把新映像对应的页表项拷贝到0x400000开始的页表项
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

}
