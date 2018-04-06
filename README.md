# MyOS

This is an experimental operating system implementation, targeting x86 processors.

You will need the following tools to compile and develop the project.

- `g++-6.3.0`
- `nasm 2.11.08`
- `cmake >= 3.9`

A Linux environment is required. We are using Ubuntu 16.04.

Other distributions and tool versions may also work, but we haven't tested it.

Jetbrains CLion is recommended, but not required, for best experience.

## Compile and bundle

```sh
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
cd ..
sudo scripts/bundle cmake-build-debug
```

You shall see a file named `myos.img` inside `cmake-build-debug`.
Set it as your VBox virtual machine startup image, then run the VM.
