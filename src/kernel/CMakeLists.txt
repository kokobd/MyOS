project(myos-system-kernel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_library(kernel-lib STATIC
        src/ram/PageManager.cpp
        include/myos/kernel/ram/PageManager.hpp
        include/myos/kernel/ram/page.hpp
        )
target_link_libraries(kernel-lib
        core
        )
target_include_directories(kernel-lib
        PUBLIC include
        )

if (NOT PROFILE MATCHES UNIT_TEST)
    enable_language(ASM_NASM)

    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
    set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

    add_executable(kernel
            exe/multiboot.asm
            exe/multiboot2.asm
            exe/kernel_start.asm
            exe/main.cpp

            exe_include/myos/kernel/Kernel.hpp
            exe/Kernel.cpp

            exe_include/myos/kernel/SysCall.hpp
            exe/SysCall.cpp

            exe_include/myos/kernel/cpu/CPU.hpp
            exe/cpu/CPU.cpp
            exe/cpu/8259A.asm
            exe_include/myos/kernel/cpu/InterryptType.hpp
            exe_include/myos/kernel/cpu/RegisterState.hpp
            exe_include/myos/kernel/cpu/InterruptHandler.hpp
            exe_include/myos/kernel/cpu/IDT.hpp
            exe/cpu/IDT.cpp
            exe/cpu/int.asm
            exe/cpu/cpu.asm

            exe_include/myos/kernel/ram/Memory.hpp
            exe/ram/Memory.cpp
            exe_include/myos/kernel/ram/VirtualMemoryMapping.hpp
            exe/ram/VirtualMemoryMapping.cpp

            exe_include/myos/kernel/process/Process.hpp
            exe/process/Process.cpp
            exe_include/myos/kernel/process/Scheduler.hpp
            exe/process/Scheduler.cpp
            )

    target_compile_options(kernel
            PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-mno-red-zone -Wall>
            )

    target_include_directories(kernel
            PRIVATE exe_include
            )

    set_target_properties(kernel PROPERTIES
            LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
            LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
            )

    target_link_libraries(kernel
            kernel-lib
            core
            )
else ()
    add_executable(kernel-test
            test/main.cpp
            test/ram/PageFrameManager.cpp
            )
    target_link_libraries(kernel-test
            kernel-lib
            catch2
            )
    add_test(kernel-test kernel-test)
endif ()
