#ifndef KERNEL_HAL_ASMUTIL_H_
#define KERNEL_HAL_ASMUTIL_H_

#define KERNEL_HAL_ASMUTIL_stringify(X) #X

#define label_(X) \
    KERNEL_HAL_ASMUTIL_stringify((X) - 0x08048000 + 0x100000)

#endif