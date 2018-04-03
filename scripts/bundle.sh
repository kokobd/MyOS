#!/bin/bash

set -o errexit

if [ -z "$1" ]; then
    echo "Target directory must not be empty"
    exit 1
fi

BUILD_DIR="$1"

cd "${BUILD_DIR}"
rm -f myos.img
rm -rf myos

mkfs.vfat -C myos.img 1440
dd if=system/bootloader/bootloader of=myos.img conv=notrunc
mkdir -p myos
mount myos.img myos
cp system/bootloader/krnldr.sys myos/KRNLDR.SYS
cp system/kernel/kernel myos/KERNEL.SYS
cp apps/welcome myos/WELCOME.EXE
sync myos/*
umount myos
rmdir myos
