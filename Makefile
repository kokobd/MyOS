all: pre build/bootloader.flp

pre:
	mkdir -p build

build/bootloader.flp: src/bootloader.s
	nasm -o build/bootloader.flp src/bootloader.s

clean:
	rm -rf build/*
