# MyOS

This is an experimental operating system implementation, targeting x86 processors.

To develop, we assume a linux environment.

We use CMake as the build system. Additionally, **TWO** toolchains are required:

1. `gcc-6.4.0`, targeting host platform.
2. `gcc-6.4.0-i686-elf`, targeting freestanding environment.

For instructions on building a GCC cross compiler, please consult [this page](https://wiki.osdev.org/GCC_Cross-Compiler).

You may create a toolchain file like [this](https://github.com/zelinf/MyOS/wiki/Sample-CMake-toolchain-file), and tell CMake about it with `-DCMAKE_TOOLCHAIN_FILE=`.
You also need to pass in a `-DPROFILE=`, possible values are `UNIT_TEST`, `DEBUG` and `RELEASE`.

We use the Catch framework for unit testing. Unit tests are run on host platform, so you need to use
toolchain 1 and pass in `-DPROFILE=UNIT_TEST` .

Example command to bundle and run the system under QEMU:
```sh
# Assuming your build directory is cmake-build-debug
sudo scripts/bundle.sh cmake-build-debug/ \
&& qemu-system-i386 -drive format=raw,file=cmake-build-debug/myos.img
```
