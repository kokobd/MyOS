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
        include/myos/kernel/cpu/IDT.hpp
        src/cpu/IDT.cpp
        src/cpu/int.asm
        src/cpu/cpu.asm

        include/myos/kernel/common/Function.hpp
        include/myos/kernel/common/Future.hpp
        include/myos/kernel/common/Queue.hpp
        include/myos/kernel/common/BitSet.hpp
        src/common/BitSet.cpp

        include/myos/kernel/ram/sbrk.hpp
        src/ram/sbrk.cpp
        include/myos/kernel/ram/Memory.hpp
        src/ram/Memory.cpp
        include/myos/kernel/ram/Heap.hpp
        src/ram/Heap.cpp
        include/myos/kernel/ram/VirtualMemoryMapping.hpp
        src/ram/VirtualMemoryMapping.cpp
        include/myos/kernel/ram/PageFrameManager.hpp
        src/ram/PageFrameManager.cpp
        src/ram/util.hpp

        include/myos/kernel/process/Process.hpp
        src/process/Process.cpp

        #        include/myos/kernel/terminal/Terminal.hpp
        #        src/terminal/Terminal.cpp

        include/myos/kernel/drivers/util.hpp
        src/drivers/util.cpp
        include/myos/kernel/drivers/Floppy.hpp
        src/drivers/Floppy.cpp
        include/myos/kernel/drivers/VGAScreen.hpp
        src/drivers/VGAScreen.cpp
        include/myos/kernel/drivers/Keyboard.hpp
        src/drivers/Keyboard.cpp

        src/test/TestMain.hpp
        src/test/TestMain.cpp
        src/test/TestBase.hpp
        src/test/TestBase.cpp
        src/test/ram/HeapTest.hpp
        src/test/ram/HeapTest.cpp
        )

target_compile_options(kernel
        PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-mno-red-zone -Wall>
        )

target_include_directories(kernel
        PRIVATE include
        )

set_target_properties(kernel PROPERTIES
        LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )

target_link_libraries(kernel
        base)