#!/bin/bash

MODULES=()

set -o errexit

if [ -z "$1" ]; then
    echo "Target directory must not be empty"
    exit 1
fi

tar x -C scripts/bin -f scripts/bin/myos.tar.gz

BUILD_DIR="$1"

rm -f "${BUILD_DIR}/myos.img"
cp scripts/bin/myos.img "${BUILD_DIR}"
cp scripts/grub.cfg "${BUILD_DIR}"

cd "${BUILD_DIR}"

mkdir -p myos
mount -o loop,offset=1048576 myos.img myos
mkdir -p myos/boot/myos
cp src/kernel/kernel myos/boot/myos/
for item in ${MODULES[*]}; do
    cp $item myos/boot/myos/
done
cp -f grub.cfg myos/boot/grub/

umount myos
rmdir myos

user=$(stat -c "%U" .)
chown ${user}: myos.img
