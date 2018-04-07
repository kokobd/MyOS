#!/bin/bash

set -o errexit

if [ -z "$1" ]; then
    echo "Target directory must not be empty"
    exit 1
fi

BUILD_DIR="$1"

rm -f "${BUILD_DIR}/myos.img"
cp scripts/bin/myos.img "${BUILD_DIR}"

cd "${BUILD_DIR}"
rm -rf myos

# dd if=system/bootloader/bootloader of=myos.img conv=notrunc
mkdir -p myos
mount myos.img myos
# cp system/bootloader/krnldr.sys myos/KRNLDR.SYS
cp system/kernel/kernel myos/boot/kernel.bin
cp apps/welcome myos/WELCOME.EXE
cp apps/clear myos/CLEAR.EXE
cp apps/file myos/FILE.EXE
sync myos/*
umount myos
rmdir myos
