# MyOS

This is an experimental operating system implementation, targeting x86 processors.

To develop, you need to install:

- `make`
- `gcc`
- `nasm`

We currently only supports to build on Linux.

Run `sudo make image` to execute all build steps and create a bootable
floppy image containing the kernel and applications.
Run `make` to build, but doesn't bundle the executables into an image.

You may use any text editor you like, such as VIM, EMacs, or Atom.
We use Visual Studio Code. A handwritten workspace setting file for VSCode
is provided in the repository to ensure everyone use the same tabsize, etc.
If you choose to use another text editor, make sure you follow our existing
code style.

To run, please use the latest version of Oracle VM VirtualBox. Load the image
as a floppy drive. Select that drive as your boot drive. Then it should work.
Note that you **MUST** use a desktop keyboard.