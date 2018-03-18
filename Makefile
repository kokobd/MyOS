all: build

.PHONY: image build clean

image: build build/myos.img
	mkdir -p build/myos
	mount build/myos.img build/myos
	cp build/bootloader/stage2.o build/myos/KRNLDR.SYS
	cp build/kernel/KERNEL.SYS build/myos/
	umount build/myos
	rm -rf build/myos

build/myos.img: bin/empty.img build/bootloader/stage1.o
	mkdir -p $(@D)
	rm -f $@
	cp -f bin/empty.img $@
	dd if=build/bootloader/stage1.o of=$@ conv=notrunc

build: build/bootloader/stage1.o \
  build/bootloader/stage2.o \
  build/kernel/KERNEL.SYS
	
build/bootloader/%.o: src/bootloader/%.s
	mkdir -p $(@D)
	nasm -f bin -o $@ -Isrc/bootloader/ $<

build/kernel/KERNEL.SYS: build/kernel/main.o
	gcc -o $(@D)/kernel -nostdlib -nostartfiles $<
	objcopy -O binary -j .text $(@D)/kernel $@

build/kernel/%.o: src/kernel/%.c
	mkdir -p $(@D)
	gcc -c -Isrc/include -nostdlib -o $@ $<

clean:
	rm -rf build/*
