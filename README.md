# MyOS

This is an experimental operating system implementation, targeting x86 processors.

To develop, you need to install:

- `make`
- `gcc`
- `nasm`

Unix-like shell environment is expected in the Makefile. So if you are
on Windows, please install [MSYS2](http://www.msys2.org/) or CygWin if you like.

Inside MSYS2 MINGW 64 terminal, execute the following commands if you
just did a fresh install.
```sh
pacman -Syu
pacman -S --needed gcc nasm
```
This snippet will first update your package indices and installed packages.
Then it will install gcc and nasm.

You may use any text editor you like, such as VIM, EMacs, or Atom.
We use Visual Studio Code. A handwritten workspace setting file for VSCode
is provided in the repository to ensure everyone use the same tabsize, etc.
If you choose to use another text editor, make sure you follow our existing
code style.

## Build

To build, simply execute `make` in project root. You will find `build/bootloader.flp`.
Load it as a floppy disk in your virtual machine, then you should be able to
start the VM and see the OS running. Cheers!