cmake_minimum_required(VERSION 3.9)

project(myos LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(stdlibc)
add_subdirectory(stdlibcpp)
add_subdirectory(system)
add_subdirectory(apps)
