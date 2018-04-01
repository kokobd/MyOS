#pragma once

#pragma push_macro("NAMESPACE")
#define NAMESPACE(X) kernel_syscall_ ## X

/**
 * Register system calls to interrupt 0x80.
 * IDT must be initialized before colling this function.
 */
void NAMESPACE(initialize)();

#pragma pop_macro("NAMESPACE")
