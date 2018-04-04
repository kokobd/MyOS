project(myos-system-kernel LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(kernel
        src/main.c
        src/hal/gdt.c
        src/hal/idt.c
        src/hal/io.h
        src/floppy/floppy.c
        src/screen/vga.c
        src/shell.c
        src/keyboard/scanCode.c
        src/keyboard/key.h
        src/keyboard/input.c
        src/filesystem/fat12.c
        src/filesystem/file.c
        src/syscall/syscall.c
        )

target_compile_options(kernel
        PRIVATE -m32
        PRIVATE -masm=intel
        PRIVATE -mno-red-zone
        PRIVATE -fno-builtin
        PRIVATE -fno-stack-protector
        )

set_target_properties(kernel PROPERTIES
        LINK_FLAGS "-nostdlib -m32 -fno-builtin -Wl,-Ttext=0x100400")

target_link_libraries(kernel
        stdlib)