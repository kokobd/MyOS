all: build

.PHONY: image build clean

image: build build/myos.img
	mkdir -p build/myos
	mount build/myos.img build/myos
	cp build/bootloader/stage2.o build/myos/KRNLDR.SYS
	umount build/myos
	rm -rf build/myos

build/myos.img: bin/empty.img build/bootloader/stage1.o
	mkdir -p $(@D)
	rm -f $@
	cp -f bin/empty.img $@
	dd if=build/bootloader/stage1.o of=$@ conv=notrunc

build: build/bootloader/stage1.o build/bootloader/stage2.o
	
build/%.o: src/%.s
	mkdir -p $(@D)
	nasm -f bin -o $@ $<

clean:
	rm -rf build/*
