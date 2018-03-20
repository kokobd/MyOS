all: build

.PHONY: image build clean

image: build build/myos.img
	mkdir -p build/myos
	mount build/myos.img build/myos
	cp $(FILES) build/myos/
	umount build/myos
	rm -rf build/myos

build/myos.img: bin/empty.img build/bootloader/stage1.o
	mkdir -p $(@D)
	rm -f $@
	cp -f bin/empty.img $@
	dd if=build/bootloader/stage1.o of=$@ conv=notrunc

# Bootloader
KRNLDR = build/bootloader/KRNLDR.SYS
$(KRNLDR): build/bootloader/stage2.o
	cp $< $@
build/bootloader/%.o: src/bootloader/%.s
	mkdir -p $(@D)
	nasm -f bin -o $@ -Isrc/bootloader/ $<

CCFLAGS = -I$(STDLIB_INCLUDE_DIR) -fno-builtin -nostdlib -nostartfiles -m32 -masm=intel -fPIC

# My Standard Library
STDLIB_OBJS = build/stdlib/stdio.o build/stdlib/floppy.o
STDLIB_INCLUDE_DIR = src/stdlib/include
build/stdlib/%.o: src/stdlib/%.c
	mkdir -p $(@D)
	gcc -c $(CCFLAGS) -o $@ -nostdlib $<

# Kernel
KERNEL = build/kernel/KERNEL.SYS

build/kernel/KERNEL.SYS: build/kernel/main.o $(STDLIB_OBJS)
	gcc -o $(@D)/kernel $(CCFLAGS) $< $(STDLIB_OBJS)
	objcopy -O binary -j .text $(@D)/kernel $@

build/kernel/%.o: src/kernel/%.c
	mkdir -p $(@D)
	gcc -c $(CCFLAGS) -o $@ $<

# Apps
APPS = build/apps/app1.exe build/apps/app2.exe build/apps/app3.exe build/apps/app4.exe
build/apps/app1.exe: src/apps/app1.c
	mkdir -p build/apps
	gcc $(CCFLAGS) -o $(@D)/app1 $< $(STDLIB_OBJS)
	objcopy -O binary -j .text $(@D)/app1 $@

build/apps/app2.exe: src/apps/app2.c
	mkdir -p build/apps
	gcc $(CCFLAGS) -o $(@D)/app2 $< $(STDLIB_OBJS)
	objcopy -O binary -j .text $(@D)/app2 $@

build/apps/app3.exe: src/apps/app3.c
	mkdir -p build/apps
	gcc $(CCFLAGS) -o $(@D)/app3 $< $(STDLIB_OBJS)
	objcopy -O binary -j .text $(@D)/app3 $@

build/apps/app4.exe: src/apps/app4.c
	mkdir -p build/apps
	gcc $(CCFLAGS) -o $(@D)/app4 $< $(STDLIB_OBJS)
	objcopy -O binary -j .text $(@D)/app4 $@

FILES = $(KRNLDR) $(KERNEL) $(APPS)

build: build/bootloader/stage1.o $(FILES)

clean:
	rm -rf build/*
