#pragma once

/**
 * Register system calls to interrupt 0x80.
 * IDT must be initialized before colling this function.
 */
void syscallInitialize();

