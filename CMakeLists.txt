cmake_minimum_required(VERSION 3.9)

project(myos LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (PROFILE MATCHES UNIT_TEST)
    add_subdirectory(deps/catch2-cmake)
endif ()

enable_testing()

add_subdirectory(src/core)
add_subdirectory(src/kernel)

if (NOT PROFILE MATCHES UNIT_TEST)
    add_custom_target(myos
            DEPENDS kernel
            )
endif ()
