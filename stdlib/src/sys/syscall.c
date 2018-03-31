#include <sys/syscall.h>

#define issueInterrupt() \
    asm ("int 0x80")

void syscall() {
    issueInterrupt();
}
