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

# dd if=system/bootloader/bootloader of=myos.img conv=notrunc
# cp system/bootloader/krnldr.sys myos/KRNLDR.SYS

mcopy -i myos.img system/kernel/kernel ::/boot/kernel.bin
mcopy -i myos.img apps/welcome ::/WELCOME.EXE
mcopy -i myos.img apps/clear ::/CLEAR.EXE
mcopy -i myos.img apps/file ::/FILE.EXE
