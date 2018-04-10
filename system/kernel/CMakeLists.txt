project(myos-system-kernel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_executable(kernel
        include/myos/kernel/debug/trace.hpp

        src/multiboot.asm
        src/kernel_start.asm
        src/main.cpp

        include/myos/kernel/Kernel.hpp
        src/Kernel.cpp

        include/myos/kernel/SysCall.hpp
        src/SysCall.cpp

        include/myos/kernel/cpu/CPU.hpp
        src/cpu/CPU.cpp
        src/cpu/8259A.asm
        include/myos/kernel/cpu/InterryptType.hpp
        include/myos/kernel/cpu/RegisterState.hpp
        include/myos/kernel/cpu/InterruptHandler.hpp
        include/myos/kernel/cpu/NoopHandler.hpp
        src/cpu/NoopHandler.cpp
        include/myos/kernel/cpu/GDT.hpp
        include/myos/kernel/cpu/IDT.hpp
        src/cpu/IDT.cpp
        src/cpu/int.asm

        include/myos/kernel/common/Function.hpp
        include/myos/kernel/common/Future.hpp

        include/myos/kernel/ram/sbrk.hpp
        src/ram/sbrk.cpp
        include/myos/kernel/ram/Memory.hpp
        src/ram/Memory.cpp
        include/myos/kernel/ram/Heap.hpp
        src/ram/Heap.cpp

        include/myos/kernel/process/Process.hpp
        src/process/Process.cpp

        include/myos/kernel/io/util.hpp
        src/io/util.cpp
        include/myos/kernel/io/Floppy.hpp
        src/io/Floppy.cpp
        include/myos/kernel/io/VGAScreen.hpp
        src/io/VGAScreen.cpp
        include/myos/kernel/io/Keyboard.hpp
        src/io/Keyboard.cpp

        src/floppy/floppy.cpp
        src/screen/vga.cpp
        src/shell.cpp
        src/keyboard/scanCode.cpp
        src/keyboard/key.hpp
        src/keyboard/input.cpp
        src/filesystem/fat12.cpp
        src/filesystem/file.cpp
        src/exec/elf32.cpp
        )

target_compile_options(kernel
        PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -mno-red-zone -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
        )

target_include_directories(kernel
        PRIVATE include)

set_target_properties(kernel PROPERTIES
        LINK_FLAGS "-nostdlib -m32 -ffreestanding -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )
#        LINK_FLAGS "-nostdlib -m32 -ffreestanding -Wl,-Ttext=0x100400,--verbose")

target_link_libraries(kernel
        stdlibcpp)