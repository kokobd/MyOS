all: build/myos.img

build/myos.img: bin/empty.img build/bootloader/stage1.o build/bootloader/stage2.o
	mkdir -p $(@D)
	rm -f $@
	cp -f bin/empty.img $@
	dd if=build/bootloader/stage1.o of=$@ conv=notrunc

	mkdir -p build/myos
	mount build/myos.img build/myos
	cp build/bootloader/stage2.o build/myos/KRNLDR.SYS
	umount build/myos
	
build/%.o: src/%.s
	mkdir -p $(@D)
	nasm -f bin -o $@ $<

clean:
	rm -rf build/*
