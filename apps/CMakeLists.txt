project(myos-apps LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -fno-builtin -nostdlib -nostdinc -nostartfiles -m32 -masm=intel -fPIE")

add_executable(file file.c)
target_link_libraries(file stdlib)

add_executable(clear clear.c)
target_link_libraries(clear stdlib)

add_executable(welcome welcome.c)
target_link_libraries(welcome stdlib)